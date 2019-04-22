//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp
//! \author Luke Kersting, Alex Robinson
//! \brief  The standard adjoint electron-photon-relaxation data generator class def.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_ElectronElasticDataEvaluator.hpp"
#include "DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp"
#include "DataGen_AdjointPairProductionEnergyDistributionNormConstantEvaluator.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_VoidElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "MonteCarlo_StandardOccupationNumber.hpp"
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "MonteCarlo_WHIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_AdjointPhotonKinematicsHelpers.hpp"
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_GridGenerator.hpp"
#include "Utility_SloanRadauQuadrature.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_StaticOutputFormatter.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Advanced Constructor
StandardAdjointElectronPhotonRelaxationDataGenerator::StandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data,
      const double min_photon_energy,
      const double max_photon_energy,
      const double min_electron_energy,
      const double max_electron_energy )
  : AdjointElectronPhotonRelaxationDataGenerator( forward_epr_data->getAtomicNumber(),
                                                  forward_epr_data->getAtomicWeight(),
                                                  min_photon_energy,
                                                  max_photon_energy,
                                                  min_electron_energy,
                                                  max_electron_energy ),
    d_forward_epr_data( forward_epr_data )
{
  // Make sure the forward epr data is valid
  testPrecondition( forward_epr_data.get() );

  // Check if the min photon energy is below the forward table min energy
  if( min_photon_energy < forward_epr_data->getMinPhotonEnergy() )
  {
    this->setMinPhotonEnergy( forward_epr_data->getMinPhotonEnergy() );

    FRENSIE_LOG_WARNING( "the min photon energy requested is below the "
                         << "requested forward table min photon energy! The "
                         << "table's min photon energy ("
                         << forward_epr_data->getMinPhotonEnergy()
                         << ") will be used instead." );
  }

  // Check if the max photon energy is above the forward table max energy
  if( max_photon_energy > forward_epr_data->getMaxPhotonEnergy() )
  {
    this->setMaxPhotonEnergy( forward_epr_data->getMaxPhotonEnergy() );

    FRENSIE_LOG_WARNING( "the max photon energy requested is above the "
                         << "requested forward table max photon energy! The "
                         << "table's max photon energy ("
                         << forward_epr_data->getMaxPhotonEnergy()
                         << ") will be used instead." );
  }

  // Check if the min electron energy is below the forward table min energy
  if( min_electron_energy < forward_epr_data->getMinElectronEnergy() )
  {
    this->setMinElectronEnergy( forward_epr_data->getMinElectronEnergy() );

    FRENSIE_LOG_WARNING( "the min electron energy requested is above the "
                         << "requested forward table min electron energy! The "
                         << "table's min electron energy ("
                         << forward_epr_data->getMinElectronEnergy()
                         << ") will be used instead." );
  }

  // Check if the max electron energy is above the forward table max energy
  if( max_electron_energy > forward_epr_data->getMaxElectronEnergy() )
  {
    this->setMaxElectronEnergy( forward_epr_data->getMaxElectronEnergy() );

    FRENSIE_LOG_WARNING( "the max electron energy requested is above the "
                         << "requested forward table max electron energy! The "
                         << "table's max electron energy ("
                         << forward_epr_data->getMaxElectronEnergy()
                         << ") will be used instead." );
  }
}

// Basic Constructor
StandardAdjointElectronPhotonRelaxationDataGenerator::StandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data )
  : StandardAdjointElectronPhotonRelaxationDataGenerator(
                                    forward_epr_data,
                                    forward_epr_data->getMinPhotonEnergy(),
                                    forward_epr_data->getMaxPhotonEnergy(),
                                    forward_epr_data->getMinElectronEnergy(),
                                    forward_epr_data->getMaxElectronEnergy() )
{ /* ... */ }

// Constructor (existing data container)
StandardAdjointElectronPhotonRelaxationDataGenerator::StandardAdjointElectronPhotonRelaxationDataGenerator(
     const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data,
     const boost::filesystem::path& file_name_with_path )
  : AdjointElectronPhotonRelaxationDataGenerator( file_name_with_path ),
    d_forward_epr_data( forward_epr_data )
{
  // Check if the data tables are compatible
  TEST_FOR_EXCEPTION( forward_epr_data->getAtomicNumber() !=
                      this->getDataContainer().getAtomicNumber(),
                      std::runtime_error,
                      "The forward and adjoint data tables are not compatible "
                      "(Z-forward=" << forward_epr_data->getAtomicNumber() <<
                      "(Z-adjoint=" << this->getDataContainer().getAtomicNumber() <<
                      ")!" );
}

// Populate the adjoint electron-photon-relaxation data container
void StandardAdjointElectronPhotonRelaxationDataGenerator::populateEPRDataContainer(
    const bool populate_photons,
    const bool populate_electrons )
{
  // Set the relaxation data
  FRENSIE_LOG_PARTIAL_NOTIFICATION( Utility::Bold( "Setting the adjoint relaxation data" )
                                    << " ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  this->setAdjointRelaxationData();

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

  if( populate_photons )
  {
    // Set the photon data
    FRENSIE_LOG_NOTIFICATION( Utility::Bold( "Setting the adjoint photon data: " ) );

    this->setAdjointPhotonData();

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
  }
  else
  {
    // No photon data
    FRENSIE_LOG_WARNING( "No adjoint photon data will be set!" );
  }

  if ( populate_electrons )
  {
    // Set the electron data
    FRENSIE_LOG_NOTIFICATION( Utility::Bold( "Setting the adjoint electron data: " ) );

    this->setAdjointElectronData();

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
  }
  else
  {
    // No electron data
    FRENSIE_LOG_WARNING( " No adjoint electron data will be set!" );
  }
}

// Set the relaxation data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointRelaxationData()
{
  // Extract and set the subshells
  const std::set<unsigned>& subshells = d_forward_epr_data->getSubshells();

  Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Assign the set of all subshells
  data_container.setSubshells( subshells );

  // Assign the subshell data
  for( auto&& subshell : subshells )
  {
    data_container.setSubshellOccupancy(
                subshell,
                d_forward_epr_data->getSubshellOccupancy( subshell ) );

    data_container.setSubshellBindingEnergy(
                subshell,
                d_forward_epr_data->getSubshellBindingEnergy( subshell ) );
  }
}

// Set the Compton profile data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setComptonProfileData()
{
  Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Get the subshells
  const std::set<unsigned>& subshells = d_forward_epr_data->getSubshells();

  // Extract and set the Compton profiles and grids
  for( auto&& subshell : subshells )
  {
    data_container.setComptonProfileMomentumGrid(
              subshell,
              d_forward_epr_data->getComptonProfileMomentumGrid( subshell ) );

    data_container.setComptonProfile(
              subshell,
              d_forward_epr_data->getComptonProfile( subshell ) );
  }
}

// Set the occupation number data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setOccupationNumberData()
{
  Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Get the subshells
  const std::set<unsigned>& subshells = d_forward_epr_data->getSubshells();

  // Extract and set the occupation numbers and grids
  for( auto&& subshell : subshells )
  {
    data_container.setOccupationNumberMomentumGrid(
            subshell,
            d_forward_epr_data->getOccupationNumberMomentumGrid( subshell ) );

    data_container.setOccupationNumber(
            subshell,
            d_forward_epr_data->getOccupationNumber( subshell ) );
  }
}

// Set the Waller-Hartree scattering function data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setWallerHartreeScatteringFunctionData()
{
  Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Extract and set the scattering function grid
  data_container.setWallerHartreeScatteringFunctionMomentumGrid(
        d_forward_epr_data->getWallerHartreeScatteringFunctionMomentumGrid() );

  // Extract and set the scattering function
  data_container.setWallerHartreeScatteringFunction(
                    d_forward_epr_data->getWallerHartreeScatteringFunction() );
}

//! Set the Waller-Hartree atomic form factor data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setWallerHartreeAtomicFormFactorData()
{
  Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Extract and set the atomic form factor grid
  data_container.setWallerHartreeAtomicFormFactorMomentumGrid(
          d_forward_epr_data->getWallerHartreeAtomicFormFactorMomentumGrid() );

  // Extract and set the atomic form
  data_container.setWallerHartreeAtomicFormFactor(
                      d_forward_epr_data->getWallerHartreeAtomicFormFactor() );

  // Extract and set the squared atomic form factor squared momentum grid
  data_container.setWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid(
       d_forward_epr_data->getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid() );

  // Extract and set the squared atomic form factor
  data_container.setWallerHartreeSquaredAtomicFormFactor(
               d_forward_epr_data->getWallerHartreeSquaredAtomicFormFactor() );
}

// Set the photon data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointPhotonData()
{
  // Set the Compton profile data
  FRENSIE_LOG_PARTIAL_NOTIFICATION( " Setting the " <<
                                    Utility::Italicized( "Compton profile" )
                                    << " data ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  this->setComptonProfileData();

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

  // Set the occupation number data
  FRENSIE_LOG_PARTIAL_NOTIFICATION( " Setting the " <<
                                    Utility::Italicized( "occupation number" )
                                    << " data ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  this->setOccupationNumberData();

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

  // Set the Waller-Hartree scattering function data
  FRENSIE_LOG_PARTIAL_NOTIFICATION( " Setting the " <<
                                    Utility::Italicized( "Waller-Hartree scattering function" )
                                    << " data ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  this->setWallerHartreeScatteringFunctionData();

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

  // Set the Waller-Hartree atomic form factor data
  FRENSIE_LOG_PARTIAL_NOTIFICATION( " Setting the " <<
                                    Utility::Italicized( "Waller-Hartree atomic form factor" )
                                    << " data ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  this->setWallerHartreeAtomicFormFactorData();

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

  FRENSIE_LOG_NOTIFICATION( " Setting the photon cross section data:" );

  // Extract the coherent cross section
  std::shared_ptr<const Utility::UnivariateDistribution> waller_hartree_coherent_cs(
       new Utility::TabularDistribution<Utility::LinLin>(
                d_forward_epr_data->getPhotonEnergyGrid(),
                d_forward_epr_data->getWallerHartreeCoherentCrossSection() ) );

  // Extract the Waller-Hartree total forward cross section
  std::shared_ptr<const Utility::UnivariateDistribution> waller_hartree_total_forward_cs(
       new Utility::TabularDistribution<Utility::LinLin>(
                   d_forward_epr_data->getPhotonEnergyGrid(),
                   d_forward_epr_data->getWallerHartreeTotalCrossSection() ) );

  // Extract the impulse approx. total forward cross section
  std::shared_ptr<const Utility::UnivariateDistribution> impulse_approx_total_forward_cs(
       new Utility::TabularDistribution<Utility::LinLin>(
                   d_forward_epr_data->getPhotonEnergyGrid(),
                   d_forward_epr_data->getImpulseApproxTotalCrossSection() ) );

  // Create the Waller-Hartree incoherent adjoint cross section evaluator
  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
    waller_hartree_incoherent_adjoint_cs_evaluator;

  this->createWallerHartreeIncoherentAdjointCrossSectionEvaluator(
                              waller_hartree_incoherent_adjoint_cs_evaluator );

  // Create the impulse approx. incoherent adjoint cross section evaluators
  std::vector<std::pair<unsigned,std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution> > >
    impulse_approx_incoherent_adjoint_cs_evaluators;

  this->createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluators(
                             impulse_approx_incoherent_adjoint_cs_evaluators );

  // Create the doppler broadened impulse approx. incoherent adjoint cross
  // section evaluators
  std::vector<std::pair<unsigned,std::shared_ptr<const MonteCarlo::DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution> > >
    doppler_broadened_impulse_approx_incoherent_adjoint_cs_evaluators;

  this->createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluators(
           doppler_broadened_impulse_approx_incoherent_adjoint_cs_evaluators );

  // Create the union energy grid
  FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Creating " <<
                                    Utility::Italicized( "union energy grid " ) );
  FRENSIE_FLUSH_ALL_LOGS();

  std::list<double> union_energy_grid;

  this->initializeAdjointPhotonUnionEnergyGrid( union_energy_grid );

  // Calculate the union energy grid
  this->updateAdjointPhotonUnionEnergyGrid(
           union_energy_grid, waller_hartree_incoherent_adjoint_cs_evaluator );

  this->updateAdjointPhotonUnionEnergyGrid(
          union_energy_grid, impulse_approx_incoherent_adjoint_cs_evaluators );

  this->updateAdjointPhotonUnionEnergyGrid(
          union_energy_grid, doppler_broadened_impulse_approx_incoherent_adjoint_cs_evaluators );

  this->updateAdjointPhotonUnionEnergyGrid(
                               union_energy_grid, waller_hartree_coherent_cs );

  this->updateAdjointPhotonUnionEnergyGrid(
                          union_energy_grid, waller_hartree_total_forward_cs );

  this->updateAdjointPhotonUnionEnergyGrid(
                          union_energy_grid, impulse_approx_total_forward_cs );

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( " done." ) );
  FRENSIE_FLUSH_ALL_LOGS();

  Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Set the union energy grid
  std::vector<double> energy_grid;
  energy_grid.assign( union_energy_grid.begin(), union_energy_grid.end() );
  data_container.setAdjointPhotonEnergyGrid( energy_grid );

  // Create and set the 2-D cross sections
  {
    std::vector<std::vector<double> > max_energy_grid, cross_section;

    FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                      Utility::Italicized( "Waller-Hartree incoherent adjoint" )
                                      << " cross section ... " );
    FRENSIE_FLUSH_ALL_LOGS();

    this->createCrossSectionOnUnionEnergyGrid(
                                union_energy_grid,
                                waller_hartree_incoherent_adjoint_cs_evaluator,
                                max_energy_grid,
                                cross_section );

    data_container.setAdjointWallerHartreeIncoherentMaxEnergyGrid(
                                                             max_energy_grid );
    data_container.setAdjointWallerHartreeIncoherentCrossSection(
                                                               cross_section );

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

    for( unsigned i = 0u; i < impulse_approx_incoherent_adjoint_cs_evaluators.size(); ++i )
    {
      FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting " <<
                                        Utility::Italicized( "subshell " ) <<
                                        Utility::Italicized( Data::convertENDFDesignatorToSubshellEnum( impulse_approx_incoherent_adjoint_cs_evaluators[i].first ) )
                                        << Utility::Italicized(" impulse approx incoherent adjoint ")
                                        << "cross section ... " );
      FRENSIE_FLUSH_ALL_LOGS();

      unsigned threshold_index = 0;
      
      this->createCrossSectionOnUnionEnergyGrid(
                     union_energy_grid,
                     impulse_approx_incoherent_adjoint_cs_evaluators[i].second,
                     max_energy_grid,
                     cross_section,
                     threshold_index );

      data_container.setAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(
                      impulse_approx_incoherent_adjoint_cs_evaluators[i].first,
                      max_energy_grid );
      data_container.setAdjointImpulseApproxSubshellIncoherentCrossSection(
                      impulse_approx_incoherent_adjoint_cs_evaluators[i].first,
                      cross_section );
      data_container.setAdjointImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(
                      impulse_approx_incoherent_adjoint_cs_evaluators[i].first,
                      threshold_index );

      FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
    }

    FRENSIE_LOG_NOTIFICATION( "   Setting the " <<
                              Utility::Italicized( "impulse approx total incoherent adjoint" )
                              << " cross section ... " );

    this->calculateAdjointImpulseApproxTotalIncoherentCrossSection();

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
    FRENSIE_FLUSH_ALL_LOGS();

    for( unsigned i = 0u; i < doppler_broadened_impulse_approx_incoherent_adjoint_cs_evaluators.size(); ++i )
    {
      FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting " <<
                                        Utility::Italicized( "subshell " ) <<
                                        Utility::Italicized( Data::convertENDFDesignatorToSubshellEnum( doppler_broadened_impulse_approx_incoherent_adjoint_cs_evaluators[i].first ) )
                                        << Utility::Italicized(" doppler broadened impulse approx incoherent adjoint ")
                                        << "cross section ... " );
      FRENSIE_FLUSH_ALL_LOGS();

      this->createCrossSectionOnUnionEnergyGrid(
                     union_energy_grid,
                     doppler_broadened_impulse_approx_incoherent_adjoint_cs_evaluators[i].second,
                     max_energy_grid,
                     cross_section );

      data_container.setAdjointDopplerBroadenedImpulseApproxSubshellIncoherentMaxEnergyGrid(
                      doppler_broadened_impulse_approx_incoherent_adjoint_cs_evaluators[i].first,
                      max_energy_grid );
      data_container.setAdjointDopplerBroadenedImpulseApproxSubshellIncoherentCrossSection(
                      doppler_broadened_impulse_approx_incoherent_adjoint_cs_evaluators[i].first,
                      cross_section );
      data_container.setAdjointDopplerBroadenedImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(
                      doppler_broadened_impulse_approx_incoherent_adjoint_cs_evaluators[i].first,
                      0 );

      FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
    }

    FRENSIE_LOG_NOTIFICATION( "   Setting the " <<
                              Utility::Italicized( "doppler broadened impulse approx total incoherent adjoint" )
                              << " cross section ... " );

    this->calculateAdjointDopplerBroadenedImpulseApproxTotalIncoherentCrossSection();

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
    FRENSIE_FLUSH_ALL_LOGS();
  }

  

  // Create and set the 1-D cross sections
  {
    std::vector<double> cross_section;

    FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                      Utility::Italicized( "Waller-Hartree coherent adjoint" )
                                      << " cross section ... " );

    this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                               waller_hartree_coherent_cs,
                                               cross_section );

    data_container.setAdjointWallerHartreeCoherentCrossSection( cross_section );

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
    FRENSIE_FLUSH_ALL_LOGS();

    FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                      Utility::Italicized( "forward Waller-Hartree total" )
                                      << " cross section ... " );
    FRENSIE_FLUSH_ALL_LOGS();

    this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                               waller_hartree_total_forward_cs,
                                               cross_section );

    data_container.setWallerHartreeTotalCrossSection( cross_section );

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

    FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                      Utility::Italicized( "forward impulse approx. total" )
                                      << " cross section ... " );

    this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                               impulse_approx_total_forward_cs,
                                               cross_section );

    data_container.setImpulseApproxTotalCrossSection( cross_section );

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
    FRENSIE_FLUSH_ALL_LOGS();
  }

  // Set the total adjoint cross sections
  FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                    Utility::Italicized( "adjoint Waller-Hartree total" )
                                    << " cross section ... " );

  this->calculateAdjointPhotonTotalCrossSection( true, true );

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
  FRENSIE_FLUSH_ALL_LOGS();

  FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                    Utility::Italicized( "adjoint impulse approx total" )
                                    << " cross section ... " );

  this->calculateAdjointPhotonTotalCrossSection( false, false );

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
  FRENSIE_FLUSH_ALL_LOGS();

  FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                    Utility::Italicized( "adjoint doppler broadened impulse approx total" )
                                    << " cross section ... " );

  this->calculateAdjointPhotonTotalCrossSection( false, true );

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
  FRENSIE_FLUSH_ALL_LOGS();

  // Set the adjoint pair/triplet production energy distributions
  FRENSIE_LOG_NOTIFICATION( " Setting the adjoint pair/triplet production "
                            "energy distributions:" );

  {
    // Set the adjoint pair production energy distribution
    FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                      Utility::Italicized( "adjoint pair production" )
                                      << " energy distribution data ... " );

    this->setAdjointPairProductionEnergyDistribution();

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
    FRENSIE_FLUSH_ALL_LOGS();

    // Set the adjoint triplet production energy distribution
    FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                      Utility::Italicized( "adjoint triplet production" )
                                      << " energy distribution data ... " );

    this->setAdjointTripletProductionEnergyDistribution();

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
    FRENSIE_FLUSH_ALL_LOGS();
  }
}

// Set the adjoint pair production energy distributions
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointPairProductionEnergyDistribution()
{
  // Create the evaluator
  std::shared_ptr<AdjointPairProductionEnergyDistributionNormConstantEvaluator>
    evaluator = AdjointPairProductionEnergyDistributionNormConstantEvaluator::createEvaluator<Utility::LinLin,false>(
     d_forward_epr_data->getPhotonEnergyGrid(),
     d_forward_epr_data->getPairProductionCrossSection(),
     d_forward_epr_data->getPairProductionCrossSectionThresholdEnergyIndex() );

  Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Create the evaluation wrapper
  std::function<double(double)> evaluation_wrapper =
    evaluator->getEnergyDistributionNormConstantEvaluationWrapper(
      this->getAdjointPairProductionEnergyDistNormConstantEvaluationTolerance() );

  // Create the energy distribution norm constant grid
  std::vector<double> energy_grid( 2 ), energy_dist_norm_constants;

  energy_grid[0] = 2*Utility::PhysicalConstants::electron_rest_mass_energy +
     this->getAdjointPairProductionEnergyDistNormConstantNudgeValue();
  energy_grid[1] = this->getMaxPhotonEnergy();

  try{
    this->getDefaultPhotonGridGenerator().generateAndEvaluateInPlace(
                                                    energy_grid,
                                                    energy_dist_norm_constants,
                                                    evaluation_wrapper );
  }
  EXCEPTION_CATCH_RETHROW(std::runtime_error,
                          "Error: Could not generate an optimized energy grid "
                          "for the adjoint pair production energy "
                          "distribution norm constants!" );

  // Add the initial point to the grid (this operation is inefficient with
  // vectors)
  energy_grid.insert( energy_grid.begin(),
                      2*Utility::PhysicalConstants::electron_rest_mass_energy);
  energy_dist_norm_constants.insert( energy_dist_norm_constants.begin(),
                                     0.0 );

  // Set the norm constants
  data_container.setAdjointPairProductionEnergyDistributionNormConstantGrid(
                                                                 energy_grid );
  data_container.setAdjointPairProductionEnergyDistributionNormConstant(
                                                  energy_dist_norm_constants );

  // Set the energy distribution
  unsigned threshold_index =
    d_forward_epr_data->getPairProductionCrossSectionThresholdEnergyIndex();

  std::vector<double>::const_iterator start_it =
    d_forward_epr_data->getPhotonEnergyGrid().begin() + threshold_index;

  energy_grid.assign( start_it,
                      d_forward_epr_data->getPhotonEnergyGrid().end() );

  data_container.setAdjointPairProductionEnergyDistributionGrid( energy_grid );
  data_container.setAdjointPairProductionEnergyDistribution(
                         d_forward_epr_data->getPairProductionCrossSection() );
}

// Set the adjoint triplet production energy distribution
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointTripletProductionEnergyDistribution()
{
  // Create the evaluator
  std::shared_ptr<AdjointPairProductionEnergyDistributionNormConstantEvaluator>
    evaluator = AdjointPairProductionEnergyDistributionNormConstantEvaluator::createEvaluator<Utility::LinLin,false>(
     d_forward_epr_data->getPhotonEnergyGrid(),
     d_forward_epr_data->getTripletProductionCrossSection(),
     d_forward_epr_data->getTripletProductionCrossSectionThresholdEnergyIndex() );

  Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Create the evaluation wrapper
  std::function<double(double)> evaluation_wrapper =
    evaluator->getEnergyDistributionNormConstantEvaluationWrapper(
      this->getAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance() );

  // Create the energy distribution norm constant grid
  std::vector<double> energy_grid( 2 ), energy_dist_norm_constants;

  energy_grid[0] = 4*Utility::PhysicalConstants::electron_rest_mass_energy +
     this->getAdjointTripletProductionEnergyDistNormConstantNudgeValue();
  energy_grid[1] = this->getMaxPhotonEnergy();

  try{
    this->getDefaultPhotonGridGenerator().generateAndEvaluateInPlace(
                                                    energy_grid,
                                                    energy_dist_norm_constants,
                                                    evaluation_wrapper );
  }
  EXCEPTION_CATCH_RETHROW(std::runtime_error,
                          "Error: Could not generate an optimized energy grid "
                          "for the adjoint triplet production energy "
                          "distribution norm constants!" );

  // Add the initial point to the grid (this operation is inefficient with
  // vectors)
  energy_grid.insert( energy_grid.begin(),
                      4*Utility::PhysicalConstants::electron_rest_mass_energy);
  energy_dist_norm_constants.insert( energy_dist_norm_constants.begin(),
                                     0.0 );

  // Set the norm constants
  data_container.setAdjointTripletProductionEnergyDistributionNormConstantGrid(
                                                                 energy_grid );
  data_container.setAdjointTripletProductionEnergyDistributionNormConstant(
                                                  energy_dist_norm_constants );

  // Set the energy distribution
  unsigned threshold_index =
    d_forward_epr_data->getTripletProductionCrossSectionThresholdEnergyIndex();

  std::vector<double>::const_iterator start_it =
    d_forward_epr_data->getPhotonEnergyGrid().begin() + threshold_index;

  energy_grid.assign( start_it,
                      d_forward_epr_data->getPhotonEnergyGrid().end() );

  data_container.setAdjointTripletProductionEnergyDistributionGrid(
                                                                 energy_grid );
  data_container.setAdjointTripletProductionEnergyDistribution(
                      d_forward_epr_data->getTripletProductionCrossSection() );
}

// Create the Waller-Hartree incoherent adjoint cs evaluator
void StandardAdjointElectronPhotonRelaxationDataGenerator::createWallerHartreeIncoherentAdjointCrossSectionEvaluator(
         std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>& cs_evaluator ) const
{
  // Create a scattering function
  std::shared_ptr<const Utility::UnitAwareUnivariateDistribution<Utility::Units::InverseCentimeter,void> > raw_scattering_function(
         new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseCentimeter,void>(
          d_forward_epr_data->getWallerHartreeScatteringFunctionMomentumGrid(),
          d_forward_epr_data->getWallerHartreeScatteringFunction() ) );

  std::shared_ptr<const MonteCarlo::ScatteringFunction> scattering_function(
         new MonteCarlo::StandardScatteringFunction<Utility::Units::InverseCentimeter>(
                                                   raw_scattering_function ) );

  // Create the cross section evaluator
  cs_evaluator.reset(
               new MonteCarlo::WHIncoherentAdjointPhotonScatteringDistribution(
                                                    this->getMaxPhotonEnergy(),
                                                    scattering_function ) );
}

// Create the subshell impulse approx incoherent adjoint cs evaluators
void StandardAdjointElectronPhotonRelaxationDataGenerator::createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluators(
          std::vector<std::pair<unsigned,std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution> > >&
          cs_evaluators ) const
{
  // Get the subshells
  const std::set<unsigned>& subshells = d_forward_epr_data->getSubshells();

  // Resize the cs_evaluators
  cs_evaluators.resize( subshells.size() );

  int i = 0;

  for( auto&& subshell : subshells )
  {
    cs_evaluators[i].first = subshell;

    this->createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluator(
                                                     cs_evaluators[i].first,
                                                     cs_evaluators[i].second );

    ++i;
  }
}

// Create the subshell impulse approx incoherent adjoint cs evaluators
void StandardAdjointElectronPhotonRelaxationDataGenerator::createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluators(
          std::vector<std::pair<unsigned,std::shared_ptr<const MonteCarlo::DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution> > >&
          cs_evaluators ) const
{
  // Get the subshells
  const std::set<unsigned>& subshells = d_forward_epr_data->getSubshells();

  // Resize the cs_evaluators
  cs_evaluators.resize( subshells.size() );

  int i = 0;

  for( auto&& subshell : subshells )
  {
    cs_evaluators[i].first = subshell;

    this->createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluator(
                                                     cs_evaluators[i].first,
                                                     cs_evaluators[i].second );

    ++i;
  }
}

// Create a subshell impulse approx incoherent adjoint cs evaluator
void StandardAdjointElectronPhotonRelaxationDataGenerator::createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluator(
         const unsigned subshell,
         std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>& cs_evaluator ) const
{
  // Create the occupation number
  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::MeCMomentum,void> > raw_occupation_number(
    new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,void>(
               d_forward_epr_data->getOccupationNumberMomentumGrid( subshell ),
               d_forward_epr_data->getOccupationNumber( subshell ) ) );

  std::shared_ptr<MonteCarlo::OccupationNumber> occupation_number(
         new MonteCarlo::StandardOccupationNumber<Utility::Units::MeCMomentum>(
                                                     raw_occupation_number ) );

  cs_evaluator.reset(
        new MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution(
                      this->getMaxPhotonEnergy(),
                      Data::convertENDFDesignatorToSubshellEnum( subshell ),
                      d_forward_epr_data->getSubshellOccupancy( subshell ),
                      d_forward_epr_data->getSubshellBindingEnergy( subshell ),
                      occupation_number ) );
}

// Create a subshell impulse approx incoherent adjoint cs evaluator
void StandardAdjointElectronPhotonRelaxationDataGenerator::createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluator(
         const unsigned subshell,
         std::shared_ptr<const MonteCarlo::DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution>& cs_evaluator ) const
{
  // Create the occupation number
  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::MeCMomentum,void> > raw_occupation_number(
    new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,void>(
               d_forward_epr_data->getOccupationNumberMomentumGrid( subshell ),
               d_forward_epr_data->getOccupationNumber( subshell ) ) );

  std::shared_ptr<MonteCarlo::OccupationNumber> occupation_number(
         new MonteCarlo::StandardOccupationNumber<Utility::Units::MeCMomentum>(
                                                     raw_occupation_number ) );

  // Create the Compton profile
  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum> > raw_compton_profile(
       new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum>(
                 d_forward_epr_data->getComptonProfileMomentumGrid( subshell ),
                 d_forward_epr_data->getComptonProfile( subshell ) ) );

  std::shared_ptr<MonteCarlo::ComptonProfile> compton_profile(
       new MonteCarlo::StandardComptonProfile<Utility::Units::MeCMomentum,Utility::Units::InverseMeCMomentum>(
                                                       raw_compton_profile ) );

  cs_evaluator.reset(
        new MonteCarlo::DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution(
                      this->getMaxPhotonEnergy(),
                      Data::convertENDFDesignatorToSubshellEnum( subshell ),
                      d_forward_epr_data->getSubshellOccupancy( subshell ),
                      d_forward_epr_data->getSubshellBindingEnergy( subshell ),
                      occupation_number,
                      compton_profile ) );
}

// Initialize the adjoint photon union energy grid
// Note: We will start the with the forward photon energy grid and then
//       eliminate the grid points before the min photon energy and beyond the
//       max photon energy.
void StandardAdjointElectronPhotonRelaxationDataGenerator::initializeAdjointPhotonUnionEnergyGrid(
                                   std::list<double>& union_energy_grid ) const
{
  // Find the location of the first grid point that is >= the min photon energy
  std::vector<double>::const_iterator lower_location_it =
    std::lower_bound( d_forward_epr_data->getPhotonEnergyGrid().begin(),
                      d_forward_epr_data->getPhotonEnergyGrid().end(),
                      this->getMinPhotonEnergy() );

  // Find the location of the first grid point that is >= the max photon energy
  std::vector<double>::const_iterator upper_location_it =
    std::lower_bound( d_forward_epr_data->getPhotonEnergyGrid().begin(),
                      d_forward_epr_data->getPhotonEnergyGrid().end(),
                      this->getMaxPhotonEnergy() );

  // Set the union energy grid
  union_energy_grid.clear();
  union_energy_grid.assign( lower_location_it, upper_location_it );

  // Check if the min photon energy needs to be added
  if( union_energy_grid.front() != this->getMinPhotonEnergy() )
    union_energy_grid.push_front( this->getMinPhotonEnergy() );

  // Check if the last grid point is correct
  if( union_energy_grid.back() != this->getMaxPhotonEnergy() )
    union_energy_grid.push_back( this->getMaxPhotonEnergy() );

  // Add the binding energies
  this->addBindingEnergyThresholdsToUnionEnergyGrid(
                                                    this->getMinPhotonEnergy(),
                                                    this->getMaxPhotonEnergy(),
                                                    true,
                                                    union_energy_grid );

  // Sort the union energy grid
  union_energy_grid.sort();
}

// Calculate the binding energy threshold
double StandardAdjointElectronPhotonRelaxationDataGenerator::calculateBindingEnergyThreshold(
                                                 const double binding_energy,
                                                 const bool nudge_value ) const
{
  // Note: this is what will be added to the grid as it corresponds to the
  //       actual energy where the adjoint cross section becomes zero
  const double threshold_energy =
    MonteCarlo::calculateComptonLineEnergy( binding_energy, -1.0 );

  if( nudge_value )
    return threshold_energy*this->getPhotonThresholdEnergyNudgeFactor();
  else
    return threshold_energy;
}

// Add binding energies to union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::addBindingEnergyThresholdsToUnionEnergyGrid(
                                   const double min_energy,
                                   const double max_energy,
                                   const bool add_nudged_values,
                                   std::list<double>& union_energy_grid ) const
{
  const std::set<unsigned>& subshells = d_forward_epr_data->getSubshells();

  for( auto&& subshell : subshells )
  {
    const double binding_energy =
      d_forward_epr_data->getSubshellBindingEnergy( subshell );

    // Calculate the incoherent impulse approximation threshold energy
    // Note: this is what will be added to the grid as it corresponds to the
    //       actual energy where the adjoint cross section becomes zero
    const double threshold_energy =
      this->calculateBindingEnergyThreshold( binding_energy, false );

    if( threshold_energy > min_energy &&
        threshold_energy < max_energy )
      union_energy_grid.push_back( threshold_energy );

    // Since the subshell incoherent impulse approx cross sections go to
    // zero at the binding energy threshold energy we will add another grid
    // point, which is the binding energy threshold plus a small shift value.
    // Avoiding the zero value of the cross section has been shown to improve
    // grid generation times.
    if( add_nudged_values )
    {
      const double nudged_threshold_energy =
        this->calculateBindingEnergyThreshold( binding_energy, true );

      if( nudged_threshold_energy > this->getMinPhotonEnergy() &&
          nudged_threshold_energy < this->getMaxPhotonEnergy() )
        union_energy_grid.push_back( nudged_threshold_energy );
    }
  }
}

// Update the adjoint photon union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::updateAdjointPhotonUnionEnergyGrid(
         std::list<double>& union_energy_grid,
         const std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>& cs_evaluator ) const
{
  // Create an adjoint incoherent grid generator
  AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( this->getMaxPhotonEnergy(),
                    this->getAdjointIncoherentMaxEnergyNudgeValue(),
                    this->getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                    this->getAdjointIncoherentGridConvergenceTolerance(),
                    this->getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                    this->getAdjointIncoherentGridDistanceTolerance() );

  // Throw an exception if dirty convergence occurs
  grid_generator.throwExceptionOnDirtyConvergence();

  std::function<double(double,double)> cs_evaluation_wrapper =
    grid_generator.createCrossSectionEvaluator(
                cs_evaluator, this->getAdjointIncoherentEvaluationTolerance() );

  try{
    grid_generator.generateInPlace( union_energy_grid, cs_evaluation_wrapper );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Unable to generate the energy grid for the "
                           "Waller-Hartree incoherent adjoint cross section "
                           "with the provided adjoint incoherent "
                           "tolerances!" );

  FRENSIE_LOG_PARTIAL_NOTIFICATION( "." );
  FRENSIE_FLUSH_ALL_LOGS();
}

// Update the adjoint photon union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::updateAdjointPhotonUnionEnergyGrid(
         std::list<double>& union_energy_grid,
         const std::vector<std::pair<unsigned,std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution> > >&
         cs_evaluators ) const
{
  for( unsigned i = 0u; i < cs_evaluators.size(); ++i )
  {
    Data::SubshellType subshell = Data::convertENDFDesignatorToSubshellEnum(
                                                      cs_evaluators[i].first );

    const std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>& cs_evaluator =
      cs_evaluators[i].second;

    // Create an adjoint incoherent grid generator
    AdjointIncoherentGridGenerator<Utility::LinLinLin>
      grid_generator( this->getMaxPhotonEnergy(),
                      cs_evaluator->getSubshellBindingEnergy()+
                        this->getAdjointIncoherentMaxEnergyNudgeValue(),
                      cs_evaluator->getSubshellBindingEnergy()+
                        this->getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                      this->getAdjointIncoherentGridConvergenceTolerance(),
                      this->getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                      this->getAdjointIncoherentGridDistanceTolerance() );

    // Throw an exception if dirty convergence occurs
    grid_generator.throwExceptionOnDirtyConvergence();

    std::function<double(double,double)> cs_evaluation_wrapper =
      grid_generator.createCrossSectionEvaluator(
                cs_evaluator,  this->getAdjointIncoherentEvaluationTolerance() );

    // Due to the threshold energy, which the grid generator has not been
    // designed to handle, we wll have to create a copy of the union energy
    // grid at and above the threshold energy, generate the grid on the copy,
    // then merge the copy with the original union energy grid
    const double nudged_threshold_energy =
      this->calculateBindingEnergyThreshold( cs_evaluator->getSubshellBindingEnergy(), false );
    
    std::list<double>::const_iterator start =
      std::find_if( union_energy_grid.begin(),
                    union_energy_grid.end(),
                    [nudged_threshold_energy](const double grid_value){return grid_value >= nudged_threshold_energy;} );

    std::list<double> local_union_energy_grid( start, union_energy_grid.cend() );

    try{
      grid_generator.generateInPlace( local_union_energy_grid, cs_evaluation_wrapper );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Error: Unable to generate the energy grid for "
                             "the " << subshell << " subshell impulse approx. "
                             " incoherent adjoint cross section "
                             "with the provided adjoint incoherent "
                             "tolerances!" );

    union_energy_grid.merge( local_union_energy_grid );
    union_energy_grid.unique();
    
    FRENSIE_LOG_PARTIAL_NOTIFICATION( "." );
    FRENSIE_FLUSH_ALL_LOGS();
  }
}

// Update the adjoint photon union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::updateAdjointPhotonUnionEnergyGrid(
         std::list<double>& union_energy_grid,
         const std::vector<std::pair<unsigned,std::shared_ptr<const MonteCarlo::DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution> > >&
         cs_evaluators ) const
{
  for( unsigned i = 0u; i < cs_evaluators.size(); ++i )
  {
    Data::SubshellType subshell = Data::convertENDFDesignatorToSubshellEnum(
                                                      cs_evaluators[i].first );

    const std::shared_ptr<const MonteCarlo::DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution>& cs_evaluator =
      cs_evaluators[i].second;

    // Create an adjoint incoherent grid generator
    AdjointIncoherentGridGenerator<Utility::LinLinLin>
      grid_generator( this->getMaxPhotonEnergy(),
                      cs_evaluator->getSubshellBindingEnergy()+
                        this->getAdjointIncoherentMaxEnergyNudgeValue(),
                      cs_evaluator->getSubshellBindingEnergy()+
                        this->getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                      this->getAdjointIncoherentGridConvergenceTolerance(),
                      this->getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                      this->getAdjointIncoherentGridDistanceTolerance() );

    // Throw an exception if dirty convergence occurs
    grid_generator.throwExceptionOnDirtyConvergence();

    std::function<double(double,double)> cs_evaluation_wrapper =
      grid_generator.createCrossSectionEvaluator(
                cs_evaluator,  this->getAdjointIncoherentEvaluationTolerance() );

    try{
      grid_generator.generateInPlace( union_energy_grid, cs_evaluation_wrapper );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Error: Unable to generate the energy grid for "
                             "the " << subshell << " subshell impulse approx. "
                             " incoherent adjoint cross section "
                             "with the provided adjoint incoherent "
                             "tolerances!" );

    FRENSIE_LOG_PARTIAL_NOTIFICATION( "." );
    FRENSIE_FLUSH_ALL_LOGS();
  }
}

// Update the adjoint photon union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::updateAdjointPhotonUnionEnergyGrid(
                        std::list<double>& union_energy_grid,
                        const std::shared_ptr<const Utility::UnivariateDistribution>&
                        cs_evaluator ) const
{
  // Create a cross section evaluation wrapper
  std::function<double (double)> cs_evaluation_wrapper =
    std::bind<double>( &Utility::UnivariateDistribution::evaluate,
                       std::cref( *cs_evaluator ),
                       std::placeholders::_1 );

  try{
    this->getDefaultPhotonGridGenerator().generateInPlace( union_energy_grid,
                                                     cs_evaluation_wrapper );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Unable to generate the energy grid for the "
                           "1-D photon cross section with the default "
                           "tolerances!" );

  FRENSIE_LOG_PARTIAL_NOTIFICATION( "." );
  FRENSIE_FLUSH_ALL_LOGS();
}

// Create the cross section on the union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::createCrossSectionOnUnionEnergyGrid(
          const std::list<double>& union_energy_grid,
          const std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>& cs_evaluator,
          std::vector<std::vector<double> >& max_energy_grid,
          std::vector<std::vector<double> >& cross_section ) const
{
  // Resize the max energy grid and cross section arrays
  max_energy_grid.resize( union_energy_grid.size() );
  cross_section.resize( union_energy_grid.size() );

  // Create a grid generator
  AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( this->getMaxPhotonEnergy(),
                    this->getAdjointIncoherentMaxEnergyNudgeValue(),
                    this->getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                    this->getAdjointIncoherentGridConvergenceTolerance(),
                    this->getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                    this->getAdjointIncoherentGridDistanceTolerance() );

  // Throw an exception if dirty convergence occurs
  grid_generator.throwExceptionOnDirtyConvergence();

  std::function<double(double,double)> cs_evaluation_wrapper =
    grid_generator.createCrossSectionEvaluator(
                           cs_evaluator, this->getAdjointIncoherentEvaluationTolerance() );

  // Evaluate the cross section at every energy grid point
  std::list<double>::const_iterator energy_grid_it =
    union_energy_grid.begin();

  std::vector<std::vector<double> >::iterator max_energy_grid_it =
    max_energy_grid.begin();

  std::vector<std::vector<double> >::iterator cross_section_it =
    cross_section.begin();

  while( energy_grid_it != union_energy_grid.end() )
  {
    grid_generator.generateAndEvaluateSecondaryInPlace(*max_energy_grid_it,
                                                       *cross_section_it,
                                                       *energy_grid_it,
                                                       cs_evaluation_wrapper );

    // Check if the first max energy grid point is valid. The energy to
    // max energy nudge value is used to improve convergence time by ignoring
    // the secondary grid point where the cross section is zero
    // (energy = max energy). We must add it back in for the grid to be usable.
    if( max_energy_grid_it->front() > *energy_grid_it )
    {
      // This operation is inefficient with vectors!!!
      max_energy_grid_it->insert( max_energy_grid_it->begin(),
                                  *energy_grid_it );
      cross_section_it->insert( cross_section_it->begin(), 0.0 );
    }

    ++energy_grid_it;
    ++max_energy_grid_it;
    ++cross_section_it;
  }
}

// Create the cross section on the union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::createCrossSectionOnUnionEnergyGrid(
          const std::list<double>& union_energy_grid,
          const std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>& cs_evaluator,
          std::vector<std::vector<double> >& max_energy_grid,
          std::vector<std::vector<double> >& cross_section,
          unsigned& threshold_index ) const
{
  // Find the grid point that corresponds to the threshold energy
  const double threshold_energy =
    this->calculateBindingEnergyThreshold( cs_evaluator->getSubshellBindingEnergy(), false );

  std::list<double>::const_iterator start =
    std::find_if( union_energy_grid.begin(),
                  union_energy_grid.end(),
                  [threshold_energy](const double grid_value){return grid_value >= threshold_energy;} );

  threshold_index = std::distance( union_energy_grid.begin(), start );
    
  // Resize the max energy grid and cross section arrays
  max_energy_grid.resize( union_energy_grid.size() - threshold_index );
  cross_section.resize( union_energy_grid.size() - threshold_index );

  // Create a grid generator
  AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( this->getMaxPhotonEnergy(),
                    cs_evaluator->getSubshellBindingEnergy()+ this->getAdjointIncoherentMaxEnergyNudgeValue(),
                    cs_evaluator->getSubshellBindingEnergy()+ this->getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                    this->getAdjointIncoherentGridConvergenceTolerance(),
                    this->getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                    this->getAdjointIncoherentGridDistanceTolerance() );

  // Throw an exception if dirty convergence occurs
  grid_generator.throwExceptionOnDirtyConvergence();

  std::function<double(double,double)> cs_evaluation_wrapper =
    grid_generator.createCrossSectionEvaluator(
                  cs_evaluator, this->getAdjointIncoherentEvaluationTolerance() );

  // Evaluate the cross section at every energy grid point at or above the
  // threshold energy
  std::list<double>::const_iterator energy_grid_it = start;

  std::vector<std::vector<double> >::iterator max_energy_grid_it =
    max_energy_grid.begin();

  std::vector<std::vector<double> >::iterator cross_section_it =
    cross_section.begin();

  while( energy_grid_it != union_energy_grid.end() )
  {
    grid_generator.generateAndEvaluateSecondaryInPlace(*max_energy_grid_it,
                                                       *cross_section_it,
                                                       *energy_grid_it,
                                                       cs_evaluation_wrapper );

    // Check if the first max energy grid point is valid. The energy to
    // max energy nudge value is used to improve convergence time by ignoring
    // the secondary grid point where the cross section is zero
    // (energy = max energy). We must add it back in for the grid to be usable.
    if( max_energy_grid_it->front() >
        *energy_grid_it + cs_evaluator->getSubshellBindingEnergy() )
    {
      // This operation is inefficient with vectors!!!
      max_energy_grid_it->insert(
                  max_energy_grid_it->begin(),
                  *energy_grid_it + cs_evaluator->getSubshellBindingEnergy() );
      cross_section_it->insert( cross_section_it->begin(), 0.0 );
    }

    ++energy_grid_it;
    ++max_energy_grid_it;
    ++cross_section_it;
  }
}

// Create the cross section on the union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::createCrossSectionOnUnionEnergyGrid(
          const std::list<double>& union_energy_grid,
          const std::shared_ptr<const MonteCarlo::DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution>& cs_evaluator,
          std::vector<std::vector<double> >& max_energy_grid,
          std::vector<std::vector<double> >& cross_section ) const
{
  // Resize the max energy grid and cross section arrays
  max_energy_grid.resize( union_energy_grid.size() );
  cross_section.resize( union_energy_grid.size() );

  // Create a grid generator
  AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( this->getMaxPhotonEnergy(),
                    cs_evaluator->getSubshellBindingEnergy()+ this->getAdjointIncoherentMaxEnergyNudgeValue(),
                    cs_evaluator->getSubshellBindingEnergy()+ this->getAdjointIncoherentEnergyToMaxEnergyNudgeValue(),
                    this->getAdjointIncoherentGridConvergenceTolerance(),
                    this->getAdjointIncoherentGridAbsoluteDifferenceTolerance(),
                    this->getAdjointIncoherentGridDistanceTolerance() );

  // Throw an exception if dirty convergence occurs
  grid_generator.throwExceptionOnDirtyConvergence();

  std::function<double(double,double)> cs_evaluation_wrapper =
    grid_generator.createCrossSectionEvaluator(
                  cs_evaluator, this->getAdjointIncoherentEvaluationTolerance() );

  // Evaluate the cross section at every energy grid point
  std::list<double>::const_iterator energy_grid_it =
    union_energy_grid.begin();

  std::vector<std::vector<double> >::iterator max_energy_grid_it =
    max_energy_grid.begin();

  std::vector<std::vector<double> >::iterator cross_section_it =
    cross_section.begin();

  while( energy_grid_it != union_energy_grid.end() )
  {
    grid_generator.generateAndEvaluateSecondaryInPlace(*max_energy_grid_it,
                                                       *cross_section_it,
                                                       *energy_grid_it,
                                                       cs_evaluation_wrapper );

    // Check if the first max energy grid point is valid. The energy to
    // max energy nudge value is used to improve convergence time by ignoring
    // the secondary grid point where the cross section is zero
    // (energy = max energy). We must add it back in for the grid to be usable.
    if( max_energy_grid_it->front() >
        *energy_grid_it + cs_evaluator->getSubshellBindingEnergy() )
    {
      // This operation is inefficient with vectors!!!
      max_energy_grid_it->insert(
                  max_energy_grid_it->begin(),
                  *energy_grid_it + cs_evaluator->getSubshellBindingEnergy() );
      cross_section_it->insert( cross_section_it->begin(), 0.0 );
    }

    ++energy_grid_it;
    ++max_energy_grid_it;
    ++cross_section_it;
  }
}

// Create the cross section on the union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::createCrossSectionOnUnionEnergyGrid(
          const std::list<double>& union_energy_grid,
          const std::shared_ptr<const Utility::UnivariateDistribution>& cs_evaluator,
          std::vector<double>& cross_section ) const
{
  // Resize the cross section array
  cross_section.resize( union_energy_grid.size() );

  // Evaluate the cross section at every energy grid point
  std::list<double>::const_iterator energy_grid_it =
    union_energy_grid.begin();

  std::vector<double>::iterator cross_section_it = cross_section.begin();

  while( energy_grid_it != union_energy_grid.end() )
  {
    *cross_section_it = cs_evaluator->evaluate( *energy_grid_it );

    ++energy_grid_it;
    ++cross_section_it;
  }
}

// Calculate the total incoherent adjoint cross section
void StandardAdjointElectronPhotonRelaxationDataGenerator::calculateAdjointImpulseApproxTotalIncoherentCrossSection()
{
  Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Get the union energy grid
  const std::vector<double>& energy_grid =
    data_container.getAdjointPhotonEnergyGrid();

  // Initialize the max energy grid
  std::vector<std::vector<double> > max_energy_grid( energy_grid.size() );
  std::vector<std::vector<double> > cross_section( energy_grid.size() );

  // The max_energy_grid at an energy
  std::list<double> local_max_energy_grid;

  // Get the subshells
  const std::set<unsigned>& subshells = data_container.getSubshells();

  // Generate the max energy grid at each energy grid point
  for( unsigned i = 0u; i < energy_grid.size(); ++i )
  {
    local_max_energy_grid.clear();

    std::set<unsigned>::const_iterator subshell = subshells.begin();

    while( subshell != subshells.end() )
    {
      unsigned threshold_index = data_container.getAdjointImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( *subshell );

      if( i >= threshold_index )
      {
        local_max_energy_grid.insert(
          local_max_energy_grid.end(),
          data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid( *subshell )[i-threshold_index].begin(),
          data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid( *subshell )[i-threshold_index].end() );
      }

      ++subshell;
    }

    // Sort the local max energy grid
    local_max_energy_grid.sort();

    // Remove duplicate grid points from the local max energy grid
    local_max_energy_grid.unique();

    // Assign the max energy grid at this energy
    max_energy_grid[i].assign( local_max_energy_grid.begin(),
                               local_max_energy_grid.end() );
    cross_section[i].resize( max_energy_grid[i].size(), 0 );

    // Evaluate the cross section on the max energy grid at this energy
    subshell = subshells.begin();

    while( subshell != subshells.end() )
    {
      unsigned threshold_index = data_container.getAdjointImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( *subshell );

      if( i >= threshold_index )
      {
        Utility::TabularDistribution<Utility::LinLin> subshell_cs(
          data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid( *subshell )[i-threshold_index],
          data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection( *subshell )[i-threshold_index] );

        for( unsigned j = 0u; j < max_energy_grid[i].size(); ++j )
          cross_section[i][j] += subshell_cs.evaluate( max_energy_grid[i][j] );
      }

      ++subshell;
    }
  }

  // Set the adjoint impulse approx total incoherent cross section
  data_container.setAdjointImpulseApproxIncoherentMaxEnergyGrid(
                                                             max_energy_grid );
  data_container.setAdjointImpulseApproxIncoherentCrossSection(cross_section );

  // This needs to be calculated to be safe, but as long as the min energy
  // doesn't go below 1e-4, this shouldn't be an issue
  data_container.setAdjointImpulseApproxIncoherentCrossSectionThresholdEnergyIndex( 0 );
}

// Calculate the total incoherent adjoint cross section
void StandardAdjointElectronPhotonRelaxationDataGenerator::calculateAdjointDopplerBroadenedImpulseApproxTotalIncoherentCrossSection()
{
  Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Get the union energy grid
  const std::vector<double>& energy_grid =
    data_container.getAdjointPhotonEnergyGrid();

  // Initialize the max energy grid
  std::vector<std::vector<double> > max_energy_grid( energy_grid.size() );
  std::vector<std::vector<double> > cross_section( energy_grid.size() );

  // The max_energy_grid at an energy
  std::list<double> local_max_energy_grid;

  // Get the subshells
  const std::set<unsigned>& subshells = data_container.getSubshells();

  // Generate the max energy grid at each energy grid point
  for( unsigned i = 0u; i < energy_grid.size(); ++i )
  {
    local_max_energy_grid.clear();

    std::set<unsigned>::const_iterator subshell = subshells.begin();

    while( subshell != subshells.end() )
    {
      local_max_energy_grid.insert(
        local_max_energy_grid.end(),
        data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentMaxEnergyGrid( *subshell )[i].begin(),
        data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentMaxEnergyGrid( *subshell )[i].end() );

      ++subshell;
    }

    // Sort the local max energy grid
    local_max_energy_grid.sort();

    // Remove duplicate grid points from the local max energy grid
    local_max_energy_grid.unique();

    // Assign the max energy grid at this energy
    max_energy_grid[i].assign( local_max_energy_grid.begin(),
                               local_max_energy_grid.end() );
    cross_section[i].resize( max_energy_grid[i].size(), 0 );

    // Evaluate the cross section on the max energy grid at this energy
    subshell = subshells.begin();

    while( subshell != subshells.end() )
    {
      Utility::TabularDistribution<Utility::LinLin> subshell_cs(
        data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentMaxEnergyGrid( *subshell )[i],
        data_container.getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentCrossSection( *subshell )[i] );

      for( unsigned j = 0u; j < max_energy_grid[i].size(); ++j )
        cross_section[i][j] += subshell_cs.evaluate( max_energy_grid[i][j] );

      ++subshell;
    }
  }

  // Set the adjoint Doppler broadened impulse approx total incoherent cross section
  data_container.setAdjointDopplerBroadenedImpulseApproxIncoherentMaxEnergyGrid(
                                                             max_energy_grid );
  data_container.setAdjointDopplerBroadenedImpulseApproxIncoherentCrossSection(cross_section );
  data_container.setAdjointDopplerBroadenedImpulseApproxIncoherentCrossSectionThresholdEnergyIndex( 0 );
}

// Calculate the adjoint photon total cross section
void StandardAdjointElectronPhotonRelaxationDataGenerator::calculateAdjointPhotonTotalCrossSection(
           const bool use_waller_hartree_adjoint_incoherent_cs,
           const bool else_use_doppler_broadened_impulse_approx_incoherent_cs )
{
  Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Get the adjoint photon energy grid
  const std::vector<double>& energy_grid =
    data_container.getAdjointPhotonEnergyGrid();

  // Get the coherent cross section
  const std::vector<double>& coherent_cs =
    data_container.getAdjointWallerHartreeCoherentCrossSection();

  // Get the max energy grid and initialize the cross section
  std::vector<std::vector<double> > max_energy_grid;
  std::vector<std::vector<double> > total_cross_section;

  if( use_waller_hartree_adjoint_incoherent_cs )
  {
    max_energy_grid =
      data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid();

    total_cross_section =
      data_container.getAdjointWallerHartreeIncoherentCrossSection();
  }
  else if( else_use_doppler_broadened_impulse_approx_incoherent_cs )
  {
    max_energy_grid =
      data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentMaxEnergyGrid();

    total_cross_section =
      data_container.getAdjointDopplerBroadenedImpulseApproxIncoherentCrossSection();
  }
  else
  {
    max_energy_grid =
      data_container.getAdjointImpulseApproxIncoherentMaxEnergyGrid();

    total_cross_section =
      data_container.getAdjointImpulseApproxIncoherentCrossSection();
  }

  // Add the coherent cross section to the total
  for( unsigned i = 0u; i < energy_grid.size(); ++i )
  {
    for( unsigned j = 0u; j < max_energy_grid[i].size(); ++j )
      total_cross_section[i][j] += coherent_cs[i];
  }

  // Set the total cross section
  if( use_waller_hartree_adjoint_incoherent_cs )
  {
    data_container.setAdjointWallerHartreeTotalMaxEnergyGrid(max_energy_grid );
    data_container.setAdjointWallerHartreeTotalCrossSection(
                                                         total_cross_section );
  }
  else if( else_use_doppler_broadened_impulse_approx_incoherent_cs )
  {
    data_container.setAdjointDopplerBroadenedImpulseApproxTotalMaxEnergyGrid(max_energy_grid );
    data_container.setAdjointDopplerBroadenedImpulseApproxTotalCrossSection(
                                                         total_cross_section );
  }
  else
  {
    data_container.setAdjointImpulseApproxTotalMaxEnergyGrid(max_energy_grid );
    data_container.setAdjointImpulseApproxTotalCrossSection(
                                                         total_cross_section );
  }
}

// Evaluate the total cross section at an energy and max energy
double StandardAdjointElectronPhotonRelaxationDataGenerator::evaluateAdjointPhotonTotalCrossSection(
          const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
          cross_sections,
          const double max_energy ) const
{ /* ... */ }

// Set the adjoint electron data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointElectronData()
{
//---------------------------------------------------------------------------//
// Set Electron Cross Section Data Data
//---------------------------------------------------------------------------//

  FRENSIE_LOG_NOTIFICATION( " Setting the adjoint electron cross section "
                            "data:" );

  // Extract the common electron energy grid
  std::shared_ptr<std::vector<double> > forward_electron_energy_grid(
       new std::vector<double>( d_forward_epr_data->getElectronEnergyGrid() ) );

  // Create the hash-based grid searcher
  std::shared_ptr<Utility::HashBasedGridSearcher<double> > forward_grid_searcher(
       new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                         forward_electron_energy_grid,
                         forward_electron_energy_grid->front(),
                         forward_electron_energy_grid->back(),
                         forward_electron_energy_grid->size()/10 + 1 ) );

  //---------------------------------------------------------------------------//
  // Create union energy grid and calculate cross sections
  //---------------------------------------------------------------------------//

  // Create the union energy grid
  FRENSIE_LOG_NOTIFICATION( "   Creating " <<
                            Utility::Italicized( "union energy grid " ) );
  FRENSIE_FLUSH_ALL_LOGS();

  Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Create the atomic excitation evaluators
  std::function<double(const double&)> adjoint_excitation_cross_section_evaluator,
    adjoint_excitation_energy_gain_evaluator;

  double excitation_max_energy;
  this->createAdjointAtomicExcitationEvaluators(
          forward_electron_energy_grid,
          forward_grid_searcher,
          adjoint_excitation_cross_section_evaluator,
          adjoint_excitation_energy_gain_evaluator,
          excitation_max_energy );

  // Create he adjoint bremsstrahlung grid generator
  std::shared_ptr<ElectronGridGenerator> brem_grid_generator;

  this->createAdjointBremsstrahlungGridGenerator(
    forward_electron_energy_grid,
    forward_grid_searcher,
    brem_grid_generator );

  // Create the adjoint electroionization subshell grid generator
  std::map<unsigned,std::shared_ptr<ElectronGridGenerator> >
    ionization_grid_generators;

  std::set<unsigned>::iterator shell = data_container.getSubshells().begin();

  // Loop through electroionization evaluator for every subshell
  for ( auto&& shell : data_container.getSubshells() )
  {
    this->createAdjointElectroionizationSubshellGridGenerator(
      forward_electron_energy_grid,
      forward_grid_searcher,
      ionization_grid_generators[shell],
      shell );
  }

  std::list<double> union_energy_grid;

  this->initializeAdjointElectronUnionEnergyGrid( union_energy_grid,
                                                  ionization_grid_generators,
                                                  brem_grid_generator,
                                                  excitation_max_energy );

  //---------------------------------------------------------------------------//
  // Generate Grid Points For The Elastic Cross Section Data
  //---------------------------------------------------------------------------//

  // Create the electron elastic data evaluator
  ElectronElasticDataEvaluator elastic_evaluator(
                                d_forward_epr_data,
                                this->getMinElectronEnergy(),
                                this->getMaxElectronEnergy(),
                                this->getCutoffAngleCosine(),
                                this->getNumberOfMomentPreservingAngles(),
                                this->getElectronTabularEvaluationTolerance(),
                                this->getElectronTwoDGridPolicy(),
                                this->getElectronTwoDInterpPolicy(),
                                this->getAdjointElectronElasticSamplingMethod(),
                                true );

  // Create the reaction
  std::shared_ptr<MonteCarlo::ElectroatomicReaction> cutoff_elastic_reaction;
  elastic_evaluator.createCutoffCrossSectionEvaluator( cutoff_elastic_reaction );

  // Bind the reaction
  boost::function<double (double pz)> cutoff_elastic_grid_function =
    boost::bind( &MonteCarlo::ElectroatomicReaction::getCrossSection,
                 boost::cref( *cutoff_elastic_reaction ),
                 _1 );

  FRENSIE_LOG_PARTIAL_NOTIFICATION( "     Adding Cutoff Elastic data to the grid ... ");
  FRENSIE_FLUSH_ALL_LOGS();

  // Generate cutoff elastic
  this->getDefaultElectronGridGenerator().generateInPlace( union_energy_grid,
                                               cutoff_elastic_grid_function );

  FRENSIE_LOG_NOTIFICATION( "done" );
  FRENSIE_FLUSH_ALL_LOGS();

  // Create the reaction
  std::shared_ptr<MonteCarlo::ElectroatomicReaction> total_elastic_reaction;
  elastic_evaluator.createTotalCrossSectionEvaluator( total_elastic_reaction );

  // Bind the reaction
  boost::function<double (double pz)> total_elastic_grid_function =
    boost::bind( &MonteCarlo::ElectroatomicReaction::getCrossSection,
                 boost::cref( *total_elastic_reaction ),
                 _1 );

  FRENSIE_LOG_PARTIAL_NOTIFICATION( "     Adding Total Elastic data to the grid ... ");
  FRENSIE_FLUSH_ALL_LOGS();

  // Generate total elastic
  this->getDefaultElectronGridGenerator().generateInPlace( union_energy_grid,
                                               total_elastic_grid_function );

  FRENSIE_LOG_NOTIFICATION( "done" );
  FRENSIE_FLUSH_ALL_LOGS();

  //---------------------------------------------------------------------------//
  // Generate Grid Points For The Adjoint Atomic Excitation Cross Section Data
  //---------------------------------------------------------------------------//

  FRENSIE_LOG_PARTIAL_NOTIFICATION( "     Adding Atomic Excitation data to the grid ... ");
  FRENSIE_FLUSH_ALL_LOGS();

  // Generate atomic excitation
  this->getDefaultElectronGridGenerator().refineInPlace(
    union_energy_grid,
    adjoint_excitation_cross_section_evaluator,
    this->getMinElectronEnergy(),
    excitation_max_energy );

  FRENSIE_LOG_NOTIFICATION( "done" );
  FRENSIE_FLUSH_ALL_LOGS();

  //---------------------------------------------------------------------------//
  // Generate Grid Points For The Adjoint Bremsstrahlung Cross Section Data
  //---------------------------------------------------------------------------//
  // Create he adjoint bremsstrahlung grid function
  std::function<double (double)> bremsstrahlung_grid_function =
    brem_grid_generator->createAdjointCrossSectionFunction(
            this->getAdjointBremsstrahlungEvaluationTolerance() );

  // Temporarily save cross section values so they don't have to be generated again
  std::vector<double> old_adjoint_bremsstrahlung_cs;

  FRENSIE_LOG_PARTIAL_NOTIFICATION( "     Adding Bremsstrahlung data to the grid ... ");
  FRENSIE_FLUSH_ALL_LOGS();

  // Generate bremsstrahlung (temporarily keep this grid and evaluated function)
  this->getDefaultElectronGridGenerator().generateAndEvaluateInPlace(
    union_energy_grid,
    old_adjoint_bremsstrahlung_cs,
    bremsstrahlung_grid_function,
    brem_grid_generator->getMinIncomingEnergy(),
    brem_grid_generator->getMaxIncomingEnergy() );

  std::list<double> old_adjoint_bremsstrahlung_union_energy_grid(
    union_energy_grid );

  FRENSIE_LOG_NOTIFICATION( "done" );
  FRENSIE_FLUSH_ALL_LOGS();

  //---------------------------------------------------------------------------//
  // Generate Grid Points For The Adjoint Electroionization Subshell Cross Section Data
  //---------------------------------------------------------------------------//
  // Create the adjoint electroionization subshell grid functions
  std::map<unsigned,std::function<double (double)> > ionization_grid_functions;

  // Temporarily save cross section values so they don't have to be generated again
  std::map<unsigned,std::list<double> > old_adjoint_electroionization_union_energy_grid;
  std::map<unsigned,std::vector<double> > old_adjoint_electroionization_cs;

  shell = data_container.getSubshells().begin();

  // Loop through electroionization evaluator for every subshell
  for ( shell; shell != data_container.getSubshells().end(); ++shell )
  {
    ionization_grid_functions[*shell] =
      ionization_grid_generators[*shell]->createAdjointCrossSectionFunction(
            this->getAdjointElectroionizationEvaluationTolerance() );

    FRENSIE_LOG_PARTIAL_NOTIFICATION( "     Adding Electroionization subshell " << *shell << " data to the grid ... ");
    FRENSIE_FLUSH_ALL_LOGS();

    // Generate electroionization (temporarily keep this grid and evaluated function)
    this->getDefaultElectronGridGenerator().generateAndEvaluateInPlace(
      union_energy_grid,
      old_adjoint_electroionization_cs[*shell],
      ionization_grid_functions[*shell],
      ionization_grid_generators[*shell]->getMinIncomingEnergy(),
      ionization_grid_generators[*shell]->getMaxIncomingEnergy() );

    old_adjoint_electroionization_union_energy_grid[*shell] =
      union_energy_grid;

    FRENSIE_LOG_NOTIFICATION( "done" );
    FRENSIE_FLUSH_ALL_LOGS();
  }

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( " done." ) );

  //---------------------------------------------------------------------------//
  // Set the Union Energy Grid and Generate Cross Section on it.
  //---------------------------------------------------------------------------//

  // Set the union energy grid
  std::vector<double> energy_grid( union_energy_grid.begin(),
                                   union_energy_grid.end() );

  data_container.setAdjointElectronEnergyGrid( energy_grid );

  // Create and set the cross sections
  std::vector<double> cross_section;
  unsigned threshold;

//---------------------------------------------------------------------------//
// Set Elastic Data
//---------------------------------------------------------------------------//
  FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                    Utility::Italicized( "adjoint total elastic" )
                                    << " cross section ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  std::vector<double> total_cross_section;
  this->createCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      total_elastic_grid_function,
      total_cross_section,
      threshold );
  data_container.setAdjointTotalElasticCrossSection( total_cross_section );
  data_container.setAdjointTotalElasticCrossSectionThresholdEnergyIndex( threshold );

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

  FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                    Utility::Italicized( "adjoint cutoff elastic " )
                                    << " cross section and distribution ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  std::vector<double> cutoff_cross_section;
  this->createCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      cutoff_elastic_grid_function,
      cutoff_cross_section,
      threshold );
  data_container.setAdjointCutoffElasticCrossSection( cutoff_cross_section );
  data_container.setAdjointCutoffElasticCrossSectionThresholdEnergyIndex( threshold );

  // Set elastic angular distribution
  auto lower_it = std::lower_bound(d_forward_epr_data->getElasticAngularEnergyGrid().begin(), d_forward_epr_data->getElasticAngularEnergyGrid().end(), this->getMinElectronEnergy());
  auto upper_it = std::lower_bound(d_forward_epr_data->getElasticAngularEnergyGrid().begin(), d_forward_epr_data->getElasticAngularEnergyGrid().end(), this->getMaxElectronEnergy());

  std::vector<double> angular_energy_grid(lower_it, upper_it );

  // Make sure the energy grid starts with the min energy
  if( angular_energy_grid.front() != this->getMinElectronEnergy() )
    angular_energy_grid.insert(angular_energy_grid.begin(), this->getMinElectronEnergy() );

  // Make sure the energy grid ends with the max energy
  if( angular_energy_grid.back() != this->getMaxElectronEnergy() )
    angular_energy_grid.push_back(this->getMaxElectronEnergy() );

  std::map<double,std::vector<double> > elastic_angle, elastic_pdf;

  // Set the elastic moment preserving data
  std::vector<double> moment_preserving_cross_section_reduction;
  std::map<double,std::vector<double> > moment_preserving_angles, moment_preserving_weights;

  elastic_evaluator.evaluateElasticSecondaryDistribution(
                          angular_energy_grid,
                          elastic_angle,
                          elastic_pdf,
                          moment_preserving_cross_section_reduction,
                          moment_preserving_angles,
                          moment_preserving_weights,
                          this->getDefaultElectronGridConvergenceTolerance(),
                          this->getDefaultElectronGridAbsoluteDifferenceTolerance(),
                          this->getDefaultElectronGridDistanceTolerance() );

  data_container.setAdjointElasticAngularEnergyGrid( angular_energy_grid );
  data_container.setAdjointCutoffElasticAngles( elastic_angle );
  data_container.setAdjointCutoffElasticPDF( elastic_pdf );

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

  if( moment_preserving_angles.size() > 0 )
  {
    FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                      Utility::Italicized( "adjoint moment preserving elastic" )
                                      << " cross section and distribution ... " );
    FRENSIE_FLUSH_ALL_LOGS();

    // Set the cross sections reduction
    data_container.setAdjointMomentPreservingCrossSectionReduction(
        moment_preserving_cross_section_reduction );

    // Set the discrete angles
    data_container.setAdjointMomentPreservingElasticDiscreteAngles(
        moment_preserving_angles );

    // Set the discrete weights
    data_container.setAdjointMomentPreservingElasticWeights(
        moment_preserving_weights );

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
  }

  FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                    Utility::Italicized( "screened Rutherford elastic" )
                                    << " cross section ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  std::vector<double> rutherford_cross_section;
  unsigned rutherford_cross_section_threshold_energy_index;

  elastic_evaluator.evaluateScreenedRutherfordCrossSection(
      total_cross_section,
      cutoff_cross_section,
      rutherford_cross_section,
      rutherford_cross_section_threshold_energy_index );

  data_container.setAdjointScreenedRutherfordElasticCrossSection( rutherford_cross_section );
  data_container.setAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(
  rutherford_cross_section_threshold_energy_index );

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

//---------------------------------------------------------------------------//
// Set The Forward Inelastic Cross Section Data
//---------------------------------------------------------------------------//

  // Create the inelastic cross section evaluators
  std::function<double (const double&)>
    forward_brem_electron_xs_evaluator, forward_ionization_electron_xs_evaluator, forward_excitation_electron_xs_evaluator;

  this->createForwardInelasticElectronCrossSectionEvaluators(
            forward_electron_energy_grid,
            forward_grid_searcher,
            forward_brem_electron_xs_evaluator,
            forward_ionization_electron_xs_evaluator,
            forward_excitation_electron_xs_evaluator );

  FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                    Utility::Italicized( "forward inelastic electron" )
                                    << " cross section ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  std::vector<double> forward_cross_section;
  this->createCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      forward_brem_electron_xs_evaluator,
      forward_cross_section,
      threshold );

  data_container.setForwardBremsstrahlungElectronCrossSection(
    forward_cross_section );
  data_container.setForwardBremsstrahlungElectronCrossSectionThresholdEnergyIndex(
    threshold );

  this->createCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      forward_ionization_electron_xs_evaluator,
      forward_cross_section,
      threshold );

  data_container.setForwardElectroionizationElectronCrossSection(
    forward_cross_section );
  data_container.setForwardElectroionizationElectronCrossSectionThresholdEnergyIndex(
    threshold );

  this->createCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      forward_excitation_electron_xs_evaluator,
      forward_cross_section,
      threshold );

  data_container.setForwardAtomicExcitationElectronCrossSection(
    forward_cross_section );
  data_container.setForwardAtomicExcitationElectronCrossSectionThresholdEnergyIndex(
    threshold );

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

//---------------------------------------------------------------------------//
// Set Atomic Excitation Data
//---------------------------------------------------------------------------//
  FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                    Utility::Italicized( "adjoint atomic excitation" )
                                    << " cross section ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  {
    std::vector<double> excitation_cross_section;
    this->createCrossSectionOnUnionEnergyGrid(
        union_energy_grid,
        adjoint_excitation_cross_section_evaluator,
        excitation_cross_section,
        threshold );

    data_container.setAdjointAtomicExcitationCrossSection( excitation_cross_section );
    data_container.setAdjointAtomicExcitationCrossSectionThresholdEnergyIndex( threshold );


    // Make sure the energy gain is greater than zero
    unsigned size = energy_grid.size();
    while( excitation_max_energy < energy_grid[size-1] )
    {
      --size;
    }
    testPostcondition( excitation_max_energy == energy_grid[size-1] );

    std::vector<double> excitation_energy_gain( size );
    std::vector<double> excitation_energy_grid( size );
    for ( unsigned i = 0; i < size; ++i )
    {
      excitation_energy_grid[i] = energy_grid[i];
      excitation_energy_gain[i] = adjoint_excitation_energy_gain_evaluator( energy_grid[i] );
    }

    // Set the adjoint bremsstrahlung scattering distribution
    data_container.setAdjointAtomicExcitationEnergyGrid( excitation_energy_grid );
    data_container.setAdjointAtomicExcitationEnergyGain( excitation_energy_gain );
  }

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );


//---------------------------------------------------------------------------//
// Set Bremsstrahlung Data
//---------------------------------------------------------------------------//
  FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                    Utility::Italicized( "adjoint bremsstrahlung" )
                                    << " cross section and distribution ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  {
    std::vector<double> cross_section;
    unsigned threshold;
    this->updateCrossSectionOnUnionEnergyGrid(
        union_energy_grid,
        old_adjoint_bremsstrahlung_union_energy_grid,
        old_adjoint_bremsstrahlung_cs,
        bremsstrahlung_grid_function,
        cross_section,
        threshold );

    data_container.setAdjointBremsstrahlungElectronCrossSection( cross_section );
    data_container.setAdjointBremsstrahlungElectronCrossSectionThresholdEnergyIndex( threshold );

    std::map<double,std::vector<double> > brem_energies, brem_pdfs;
    brem_grid_generator->generateAndEvaluateDistributionOnPrimaryEnergyGrid(
      brem_energies,
      brem_pdfs,
      this->getAdjointBremsstrahlungEvaluationTolerance(),
      energy_grid,
      cross_section,
      threshold );

    // Check if the brem energy grid is different than the union energy grid
    if( energy_grid.size() != brem_energies.size() )
    {
      std::vector<double> brem_energy_grid;
      for ( auto element : brem_energies )
      {
        brem_energy_grid.push_back( element.first );
      }

      std::sort(brem_energy_grid.begin(), brem_energy_grid.end(),
          [] (double& a, double& b) { return a < b; });

      data_container.setAdjointElectronBremsstrahlungEnergyGrid(brem_energy_grid);
    }

    // Convert outgoing energies to energy gain
    for ( auto& element : brem_energies )
    {
      for( unsigned i = 0; i < element.second.size(); ++ i )
      {
        element.second[i] -= element.first;
      }
    }

    // Set the adjoint bremsstrahlung scattering distribution
    data_container.setAdjointElectronBremsstrahlungEnergy( brem_energies );
    data_container.setAdjointElectronBremsstrahlungPDF( brem_pdfs );
  }

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

//---------------------------------------------------------------------------//
// Set Electroionization Data
//---------------------------------------------------------------------------//
  FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                    Utility::Italicized( "adjoint electroionization subshell" )
                                    << " cross sections and distributions ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  // Loop through the electroionization subshells
  shell = data_container.getSubshells().begin();
  for( shell; shell != data_container.getSubshells().end(); ++shell )
  {
    std::vector<double> cross_section;
    unsigned threshold;

    // Update cross sections on the union energy grid
    this->updateCrossSectionOnUnionEnergyGrid(
        union_energy_grid,
        old_adjoint_electroionization_union_energy_grid[*shell],
        old_adjoint_electroionization_cs[*shell],
        ionization_grid_functions[*shell],
        cross_section,
        threshold );

    // Set the cross section for the subshell
    data_container.setAdjointElectroionizationCrossSection(
      *shell,
      cross_section );

    // Set the threshold energy index for the subshell
    data_container.setAdjointElectroionizationCrossSectionThresholdEnergyIndex(
      *shell,
      threshold );

    double binding_energy = data_container.getSubshellBindingEnergy( *shell );

    std::map<double,std::vector<double> > ionization_energies, ionization_pdf;
    ionization_grid_generators.find( *shell )->second->generateAndEvaluateDistributionOnPrimaryEnergyGrid(
      ionization_energies,
      ionization_pdf,
      this->getAdjointElectroionizationEvaluationTolerance(),
      energy_grid,
      cross_section,
      threshold );

    // Check if the ionization energy grid is different than the union energy grid
    if( energy_grid.size() != ionization_energies.size() )
    {
      std::vector<double> ionization_energy_grid;
      for ( auto element : ionization_energies )
      {
        ionization_energy_grid.push_back( element.first );
      }

      std::sort(ionization_energy_grid.begin(), ionization_energy_grid.end(),
          [] (double& a, double& b) { return a < b; });

      data_container.setAdjointElectroionizationEnergyGrid(*shell, ionization_energy_grid);
    }

    // Set the adjoint bremsstrahlung scattering distribution
    data_container.setAdjointElectroionizationRecoilPDF( *shell, ionization_pdf );
    data_container.setAdjointElectroionizationRecoilEnergy(
      *shell,
      ionization_energies );
  }

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
}

// Create the inelastic cross section distribution
void
StandardAdjointElectronPhotonRelaxationDataGenerator::createForwardInelasticElectronCrossSectionEvaluators(
    const std::shared_ptr<const std::vector<double> >& forward_electron_energy_grid,
    const std::shared_ptr<Utility::HashBasedGridSearcher<double> >& forward_grid_searcher,
    std::function<double (const double&)>& forward_brem_electron_xs_evaluator,
    std::function<double (const double&)>& forward_ionization_electron_xs_evaluator,
    std::function<double (const double&)>& forward_excitation_electron_xs_evaluator ) const
{
  // Create the atomic excitation reaction
  auto excitation_reaction =
    std::make_shared<MonteCarlo::VoidElectroatomicReaction<Utility::LogLog> >(
      forward_electron_energy_grid,
      std::make_shared<const std::vector<double> >(d_forward_epr_data->getAtomicExcitationCrossSection()),
      d_forward_epr_data->getAtomicExcitationCrossSectionThresholdEnergyIndex(),
      forward_grid_searcher );

  // Create the bremsstrahlung reaction
  auto brem_reaction =
    std::make_shared<MonteCarlo::VoidElectroatomicReaction<Utility::LogLog> >(
      forward_electron_energy_grid,
      std::make_shared<const std::vector<double> >(d_forward_epr_data->getBremsstrahlungCrossSection()),
      d_forward_epr_data->getBremsstrahlungCrossSectionThresholdEnergyIndex(),
      forward_grid_searcher );


  // Extract the total electroionization subshell reactions
  std::vector<std::shared_ptr<MonteCarlo::ElectroatomicReaction> > ionization_reactions( d_forward_epr_data->getSubshells().size() );

  // Loop through the electroionization subshells
  unsigned i = 0;
  for ( auto shell : d_forward_epr_data->getSubshells() )
  {
    ionization_reactions[i] =
      std::make_shared<MonteCarlo::VoidElectroatomicReaction<Utility::LogLog> >(
        forward_electron_energy_grid,
        std::make_shared<const std::vector<double> >(d_forward_epr_data->getElectroionizationCrossSection( shell )),
        d_forward_epr_data->getElectroionizationCrossSectionThresholdEnergyIndex( shell ),
        forward_grid_searcher );

    ++i;
  }

  // Create the forward cross section evaluators
  forward_brem_electron_xs_evaluator = [ brem_reaction ]( const double& energy ){
      return brem_reaction->getCrossSection( energy );
  };

  forward_ionization_electron_xs_evaluator =
    [ ionization_reactions ]( const double& energy ){

      double cross_section = 0.0;

      // Add electro-ionization subshell cross sections
      for ( size_t i = 0; i < ionization_reactions.size(); ++i )
        cross_section += ionization_reactions[i]->getCrossSection( energy );

      return cross_section;
  };

  forward_excitation_electron_xs_evaluator =
    [ excitation_reaction ]( const double& energy ){
      return excitation_reaction->getCrossSection( energy );
  };
}

// Create the adjoint atomic excitation evaluators
void
StandardAdjointElectronPhotonRelaxationDataGenerator::createAdjointAtomicExcitationEvaluators(
  const std::shared_ptr<const std::vector<double> >& forward_electron_energy_grid,
  const std::shared_ptr<Utility::HashBasedGridSearcher<double> >& forward_grid_searcher,
  std::function<double(const double&)>& adjoint_excitation_cross_section_evaluator,
  std::function<double(const double&)>& adjoint_excitation_energy_gain_evaluator,
  double& excitation_max_energy )
{
  std::vector<double> forward_incoming_energies =
    d_forward_epr_data->getAtomicExcitationEnergyGrid();

  auto forward_dist =
    std::make_shared<const Utility::TabularDistribution<Utility::LogLog> >(
      forward_incoming_energies,
      d_forward_epr_data->getAtomicExcitationEnergyLoss() );

  // Calculate the max energy
  if( this->isElectronScatterAboveMaxModeOn() )
  {
    excitation_max_energy = this->getMaxElectronEnergy();
  }
  else
  {
    excitation_max_energy = this->getMaxElectronEnergy() -
              forward_dist->evaluate( this->getMaxElectronEnergy() );
  }

  // Calculate the adjoint incoming energies and energy gains
  std::vector<double> adjoint_incoming_energies, adjoint_energy_gain;
  unsigned max_index = 0;
  for (unsigned i = 0; i < forward_incoming_energies.size(); ++i )
  {
    // Calculate the forward energy loss at the forward energy
    double forward_energy_loss =
      forward_dist->evaluate( forward_incoming_energies[i] );
    // Calculate the adjoint incoming energy at the forward energy
    double incoming_adjoint_energy =
      forward_incoming_energies[i] - forward_energy_loss;

    if( incoming_adjoint_energy < excitation_max_energy &&
        incoming_adjoint_energy > 0.0)
    {
      adjoint_incoming_energies.push_back( incoming_adjoint_energy );
      adjoint_energy_gain.push_back( forward_energy_loss );
      max_index = i;
    }
  }

  // Add the max energy ( or grid point right above the max energy )
  if( this->isElectronScatterAboveMaxModeOn() )
  {
    // Calculate the forward energy loss at the forward energy
    double forward_energy_loss =
      forward_dist->evaluate( forward_incoming_energies[max_index+1] );

    // Calculate the adjoint incoming energy at the forward energy
    double incoming_adjoint_energy =
      forward_incoming_energies[max_index+1] - forward_energy_loss;

    adjoint_incoming_energies.push_back( incoming_adjoint_energy );
    adjoint_energy_gain.push_back( forward_energy_loss );
  }
  else
  {
    adjoint_incoming_energies.push_back( excitation_max_energy );
    adjoint_energy_gain.push_back(
                      forward_dist->evaluate( this->getMaxElectronEnergy() ) );
  }

  // Extract the forward atomic excitation cross section data
  auto forward_cross_section = std::make_shared<std::vector<double> >(
       d_forward_epr_data->getAtomicExcitationCrossSection() );

  std::shared_ptr<MonteCarlo::ElectroatomicReaction> forward_reaction =
    std::make_shared<MonteCarlo::VoidElectroatomicReaction<Utility::LogLog> >(
        forward_electron_energy_grid,
        forward_cross_section,
        d_forward_epr_data->getAtomicExcitationCrossSectionThresholdEnergyIndex(),
        forward_grid_searcher );

  std::vector<double> adjoint_energy_grid, adjoint_cross_section;

  // calculate the adjoint incoming energy grid from the forward incoming energy grid and energy loss
  unsigned i = d_forward_epr_data->getAtomicExcitationCrossSectionThresholdEnergyIndex();
  for ( i; i < forward_cross_section->size(); ++i )
  {
    double incoming_adjoint_energy = forward_electron_energy_grid->at(i) -
                forward_dist->evaluate( forward_electron_energy_grid->at(i) );

    if( incoming_adjoint_energy < excitation_max_energy &&
        incoming_adjoint_energy > 0.0)
    {
      // Calculate the adjoint energy grid point at the forward energy
      adjoint_energy_grid.push_back( incoming_adjoint_energy );

      // Calculate the adjoint cross section at the adjoint energy grid
      adjoint_cross_section.push_back(
        forward_reaction->getCrossSection( forward_electron_energy_grid->at(i) ) );

      max_index = i;
    }
  }

  // Add the max energy ( or grid point right above the max energy )
  if( this->isElectronScatterAboveMaxModeOn() )
  {
    double incoming_adjoint_energy = forward_electron_energy_grid->at(max_index+1) -
                forward_dist->evaluate( forward_electron_energy_grid->at(max_index+1) );

    // Calculate the adjoint energy grid point at the forward energy
    adjoint_energy_grid.push_back( incoming_adjoint_energy );

    // Calculate the adjoint cross section at the adjoint energy grid
    adjoint_cross_section.push_back(
      forward_reaction->getCrossSection( forward_electron_energy_grid->at(max_index+1) ) );
  }
  else
  {
    adjoint_energy_grid.push_back( excitation_max_energy );
    adjoint_cross_section.push_back(
            forward_reaction->getCrossSection( this->getMaxElectronEnergy() ) );
  }

  Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Set the adjoint bremsstrahlung scattering distribution
  // data_container.setAdjointAtomicExcitationEnergyGrid( adjoint_incoming_energies );
  // data_container.setAdjointAtomicExcitationEnergyGain( adjoint_energy_gain );

  auto adjoint_dist =
    std::make_shared<const Utility::TabularDistribution<Utility::LogLog> >(
                                                adjoint_incoming_energies,
                                                adjoint_energy_gain );

  // Set the energy gain evaluator
  adjoint_excitation_energy_gain_evaluator = [adjoint_dist](const double& adjoint_energy){ return adjoint_dist->evaluate(adjoint_energy); };

  auto adjoint_reaction =
    std::make_shared<const Utility::TabularDistribution<Utility::LogLog> >(
                                                adjoint_energy_grid,
                                                adjoint_cross_section );


  // Set thecross section evaluator
  adjoint_excitation_cross_section_evaluator = [adjoint_reaction](const double& adjoint_energy){ return adjoint_reaction->evaluate(adjoint_energy); };
}

// Create the adjoint bremsstrahlung grid generator
/*! \details This function uses the bremsstrahlung reaction and the primary
  * (incoming) energy grid of the pdf distribution to construct the adjoint
  * electron grid generator for bremsstrahlung.
  */
void StandardAdjointElectronPhotonRelaxationDataGenerator::createAdjointBremsstrahlungGridGenerator(
    const std::shared_ptr<const std::vector<double> >& forward_electron_energy_grid,
    const std::shared_ptr<Utility::HashBasedGridSearcher<double> >& forward_grid_searcher,
    std::shared_ptr<ElectronGridGenerator>& grid_generator ) const
{
  // Create the min adjoint energy function for bremsstrahlung
  std::function<double(const double&)> min_energy_gain_function = [](const double& energy){return 1e-7;};

  // Create the bremsstrahlung reaction
  std::shared_ptr<const MonteCarlo::VoidElectroatomicReaction<Utility::LogLog, false>> reaction(
    new MonteCarlo::VoidElectroatomicReaction<Utility::LogLog, false>(
      forward_electron_energy_grid,
      std::make_shared<std::vector<double> >( d_forward_epr_data->getBremsstrahlungCrossSection() ),
      d_forward_epr_data->getBremsstrahlungCrossSectionThresholdEnergyIndex(),
      forward_grid_searcher ) );

  // Create the forward cross section evaluator
  std::function<double(const double&)> cs_evaluator =
    [reaction](const double& incoming_energy){
      return reaction->getCrossSection( incoming_energy );};

  // Create the scattering function
  std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution> distribution;

  if( this->getElectronTwoDInterpPolicy() == MonteCarlo::LOGLOGLOG_INTERPOLATION )
  {
    if( this->getElectronTwoDGridPolicy() == MonteCarlo::UNIT_BASE_CORRELATED_GRID )
    {
      MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LogLogLog,Utility::UnitBaseCorrelated>(
        *d_forward_epr_data,
        distribution,
        this->getElectronTabularEvaluationTolerance(),
        1000 );
    }
    else if( this->getElectronTwoDGridPolicy() == MonteCarlo::CORRELATED_GRID )
    {
      MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LogLogLog,Utility::Correlated>(
        *d_forward_epr_data,
        distribution,
        this->getElectronTabularEvaluationTolerance(),
        1000 );
    }
    else if( this->getElectronTwoDGridPolicy() == MonteCarlo::UNIT_BASE_GRID )
    {
      MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LogLogLog,Utility::UnitBase>(
        *d_forward_epr_data,
        distribution,
        this->getElectronTabularEvaluationTolerance(),
        1000 );
    }
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: the TwoDInterpPolicy " <<
                     this->getElectronTwoDInterpPolicy() <<
                     " is invalid or currently not supported!" );
  }


  // Create the forward pdf evaluator
  std::function<double(const double&, const double&)> pdf_evaluator =
    [distribution](const double& incoming_energy, const double& outgoing_energy){
      return distribution->evaluatePDF( incoming_energy, incoming_energy - outgoing_energy); };

  grid_generator.reset(
    new ElectronGridGenerator(
        cs_evaluator,
        pdf_evaluator,
        min_energy_gain_function,
        d_forward_epr_data->getBremsstrahlungEnergyGrid(),
        this->getMinElectronEnergy(),
        this->getMaxElectronEnergy(),
        this->getAdjointBremsstrahlungMinEnergyNudgeValue(),
        this->getAdjointBremsstrahlungMaxEnergyNudgeValue(),
        this->getAdjointBremsstrahlungGridConvergenceTolerance(),
        this->getAdjointBremsstrahlungAbsoluteDifferenceTolerance(),
        this->getAdjointBremsstrahlungDistanceTolerance(),
        this->isElectronScatterAboveMaxModeOn() ) );
}

// Create the adjoint electroionization subshell grid generator
/*! \details This function uses the electroionization subshell reaction
 * and the primary (incoming) energy grids of the pdf subshell distributions
 * to construct the adjoint grid generator for the subshell.
 */
void StandardAdjointElectronPhotonRelaxationDataGenerator::createAdjointElectroionizationSubshellGridGenerator(
    const std::shared_ptr<const std::vector<double> >& forward_electron_energy_grid,
    const std::shared_ptr<Utility::HashBasedGridSearcher<double> >& forward_grid_searcher,
    std::shared_ptr<ElectronGridGenerator>& grid_generator,
    const unsigned shell ) const
{
  // Create the ionization reaction
  std::shared_ptr<const MonteCarlo::VoidElectroatomicReaction<Utility::LogLog, false>> reaction(
    new MonteCarlo::VoidElectroatomicReaction<Utility::LogLog, false>(
      forward_electron_energy_grid,
      std::make_shared<std::vector<double> >( d_forward_epr_data->getElectroionizationCrossSection(shell) ),
      d_forward_epr_data->getElectroionizationCrossSectionThresholdEnergyIndex(shell),
      forward_grid_searcher ) );

  // Create the forward cross section evaluator
  std::function<double(const double&)> cs_evaluator =
    [reaction](const double& incoming_energy){
      return reaction->getCrossSection( incoming_energy );};

  // Get the binding energy
  double binding_energy = d_forward_epr_data->getSubshellBindingEnergy( shell );

  // Create a electroionization subshell distribution
  std::shared_ptr<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
        distribution;

  unsigned max_number_of_iterations = 1000;
  if( this->getElectronTwoDInterpPolicy() == MonteCarlo::LOGLOGLOG_INTERPOLATION )
  {
    if( this->getElectronTwoDGridPolicy() == MonteCarlo::UNIT_BASE_CORRELATED_GRID )
    {
      MonteCarlo::ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LinLinLin,Utility::UnitBaseCorrelated>(
          *d_forward_epr_data,
          shell,
          binding_energy,
          distribution,
          this->getForwardElectroionizationSamplingMode(),
          this->getElectronTabularEvaluationTolerance(),
          max_number_of_iterations,
          false );
    }
    else if( this->getElectronTwoDGridPolicy() == MonteCarlo::CORRELATED_GRID )
    {
      MonteCarlo::ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LinLinLin,Utility::UnitBaseCorrelated>(
          *d_forward_epr_data,
          shell,
          binding_energy,
          distribution,
          this->getForwardElectroionizationSamplingMode(),
          this->getElectronTabularEvaluationTolerance(),
          max_number_of_iterations,
          false );
    }
    else if( this->getElectronTwoDGridPolicy() == MonteCarlo::UNIT_BASE_GRID )
    {
      MonteCarlo::ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LinLinLin,Utility::UnitBaseCorrelated>(
          *d_forward_epr_data,
          shell,
          binding_energy,
          distribution,
          this->getForwardElectroionizationSamplingMode(),
          this->getElectronTabularEvaluationTolerance(),
          max_number_of_iterations,
          false );
    }
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                    "Error: the TwoDInterpPolicy " <<
                    this->getElectronTwoDInterpPolicy() <<
                    " is invalid or currently not supported!" );
  }

  // Get the energy grid for the secondary distribution
  std::vector<double> energy_grid = d_forward_epr_data->getElectroionizationEnergyGrid(shell);

  // Nudge first energy above the binding energy
  if( energy_grid[0] <= binding_energy )
  {
    energy_grid[0] = std::min( energy_grid[0] + 1e-6,
                               0.5*(energy_grid[0] + energy_grid[1]) );
  }

  // Create the min adjoint energy gain function
  std::function<double(const double&, const double&)> pdf_evaluator;
  std::function<double(const double&)> min_energy_gain_function;
  if ( this->getForwardElectroionizationSamplingMode() == MonteCarlo::KNOCK_ON_SAMPLING )
  {
    // Create the min adjoint energy gain function for electroionization
    std::vector<double> max_outgoing_energy_grid( energy_grid.size() );
    std::vector<double> min_energy_loss_grid( energy_grid.size() );

    for( size_t n = 0; n < energy_grid.size(); ++n )
    {
      min_energy_loss_grid[n] =
        distribution->getMinSecondaryEnergy( energy_grid[n] ) + binding_energy;
      max_outgoing_energy_grid[n] = energy_grid[n] - min_energy_loss_grid[n];
    }

    std::shared_ptr<const Utility::TabularUnivariateDistribution> min_energy_loss_distribution(
        new const Utility::TabularDistribution<Utility::LogLog>(
          max_outgoing_energy_grid,
          min_energy_loss_grid ) );

    // Create the min adjoint energy gain function
    min_energy_gain_function =
      [min_energy_loss_distribution](const double& energy){
        return min_energy_loss_distribution->evaluate(energy); };

    // Create the forward pdf evaluator
    pdf_evaluator =
      [distribution](const double& incoming_energy, const double& outgoing_energy){
        return distribution->evaluatePDF( incoming_energy, outgoing_energy ); };
  }
  else if ( this->getForwardElectroionizationSamplingMode() == MonteCarlo::OUTGOING_ENERGY_SAMPLING )
  {
    // Create the min adjoint energy gain function for electroionization
    std::vector<double> max_outgoing_energy_grid( energy_grid.size() );

    for( size_t n = 0; n < energy_grid.size(); ++n )
      max_outgoing_energy_grid[n] = distribution->getMaxSecondaryEnergy( energy_grid[n] );

    std::shared_ptr<const Utility::TabularUnivariateDistribution> min_outgoing_energy_distribution(
        new const Utility::TabularDistribution<Utility::LogLog>(
          max_outgoing_energy_grid,
          energy_grid ) );

    // Create the min adjoint energy gain function
    min_energy_gain_function =
      [min_outgoing_energy_distribution](const double& energy){
        return min_outgoing_energy_distribution->evaluate(energy) - energy; };

    // Create the forward pdf evaluator
    /*! \details When evaluating the electro-ionization pdf for outgoing energy
    *  sampling, the pdf of the primary outgoing electron and the knock-on
    *  electron must be summed in order to take into account that the adjoint
    *  electron can be either the primary outgoing electron or the knock-on
    *  electron.
    */
    pdf_evaluator =
      [distribution](const double& incoming_energy, const double& outgoing_energy){
        double primary_pdf = distribution->evaluatePDF( incoming_energy, outgoing_energy );
        double knock_on_energy = incoming_energy - outgoing_energy;
        double knock_on_pdf = distribution->evaluatePDF( incoming_energy, knock_on_energy );
        double pdf = primary_pdf + knock_on_pdf;
        return pdf; };

  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                    "the ElectroionizationSamplingType " <<
                    this->getForwardElectroionizationSamplingMode() <<
                    " is invalid or currently not supported!" );
  }

  grid_generator.reset(
    new ElectronGridGenerator(
        cs_evaluator,
        pdf_evaluator,
        min_energy_gain_function,
        energy_grid,
        this->getMinElectronEnergy(),
        this->getMaxElectronEnergy(),
        this->getAdjointElectroionizationMinEnergyNudgeValue(),
        this->getAdjointElectroionizationMaxEnergyNudgeValue(),
        this->getAdjointElectroionizationGridConvergenceTolerance(),
        this->getAdjointElectroionizationAbsoluteDifferenceTolerance(),
        this->getAdjointElectroionizationDistanceTolerance(),
        this->isElectronScatterAboveMaxModeOn() ) );
}

// Initialize the electron union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::initializeAdjointElectronUnionEnergyGrid(
     std::list<double>& union_energy_grid,
     std::map<unsigned,std::shared_ptr<ElectronGridGenerator> >& ionization_grid_generators,
     std::shared_ptr<ElectronGridGenerator>& brem_grid_generator,
     const double excitation_max_energy ) const
{
  // Add the screened Rutherford threshold energy
  std::vector<double> forward_energy_grid = d_forward_epr_data->getElectronEnergyGrid();
  unsigned rutherford_threshold = d_forward_epr_data->getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

  union_energy_grid.push_back( forward_energy_grid[rutherford_threshold] );

  // Add the max incoming energy for subshell electroionization reactions
  for( auto subshell : d_forward_epr_data->getSubshells() )
    union_energy_grid.push_back( ionization_grid_generators[subshell]->getMaxIncomingEnergy() );

  // Add the max incoming energy for a bremsstrahlung reaction
  union_energy_grid.push_back( brem_grid_generator->getMaxIncomingEnergy() );

  // Add the max energy for a atomic excitation reaction
  union_energy_grid.push_back( excitation_max_energy );

  // Remove all energies less than or equal to the min electron energy
  union_energy_grid.remove_if([max = this->getMaxElectronEnergy()](double n){ return n >= max; });

  // Remove all energies greater than or equal to the max electron energy
  union_energy_grid.remove_if([min = this->getMinElectronEnergy()](double n){ return n <= min; });

  // Add the min electron energy to the union energy grid
  union_energy_grid.push_back( this->getMinElectronEnergy() );

  // Add the max electron energy
  union_energy_grid.push_back( this->getMaxElectronEnergy() );

  // Sort the union energy grid
  union_energy_grid.sort();

  // Make sure there are no repeated elements
  union_energy_grid.unique();
}

// Find the lower and upper bin boundary for a min and max energy
void StandardAdjointElectronPhotonRelaxationDataGenerator::findLowerAndUpperBinBoundary(
    const double min_energy,
    const double max_energy,
    const std::vector<double>& energy_distribution,
    std::vector<double>::const_iterator& lower_energy_boundary,
    std::vector<double>::const_iterator& upper_energy_boundary ) const
{

  if ( min_energy <= energy_distribution.front() )
  {
    lower_energy_boundary = energy_distribution.begin();
  }
  else
  {
    // Get energy iterator below/equal to min_energy
    lower_energy_boundary = Utility::Search::binaryLowerBound(
                energy_distribution.begin(),
                energy_distribution.end(),
                min_energy );
  }

  // Get energy iterator above/equal to max_electron_energy
  upper_energy_boundary = Utility::Search::binaryUpperBound(
              lower_energy_boundary,
              energy_distribution.end(),
              max_energy );
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
