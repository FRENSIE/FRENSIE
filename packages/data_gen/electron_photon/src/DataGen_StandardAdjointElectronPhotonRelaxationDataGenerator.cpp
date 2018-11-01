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
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_VoidElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "MonteCarlo_StandardOccupationNumber.hpp"
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "MonteCarlo_WHIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
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

      this->createCrossSectionOnUnionEnergyGrid(
                     union_energy_grid,
                     impulse_approx_incoherent_adjoint_cs_evaluators[i].second,
                     max_energy_grid,
                     cross_section );

      data_container.setAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(
                      impulse_approx_incoherent_adjoint_cs_evaluators[i].first,
                      max_energy_grid );
      data_container.setAdjointImpulseApproxSubshellIncoherentCrossSection(
                      impulse_approx_incoherent_adjoint_cs_evaluators[i].first,
                      cross_section );

      FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
    }

    FRENSIE_LOG_NOTIFICATION( "   Setting the " <<
                              Utility::Italicized( "impulse approx total incoherent adjoint" )
                              << " cross section ... " );
    FRENSIE_FLUSH_ALL_LOGS();

    this->calculateAdjointImpulseApproxTotalIncoherentCrossSection();

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

  }

  // Create and set the 1-D cross sections
  {
    std::vector<double> cross_section;

    FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                      Utility::Italicized( "Waller-Hartree coherent adjoint" )
                                      << " cross section ... " );
    FRENSIE_FLUSH_ALL_LOGS();

    this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                               waller_hartree_coherent_cs,
                                               cross_section );

    data_container.setAdjointWallerHartreeCoherentCrossSection( cross_section );

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

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
    FRENSIE_FLUSH_ALL_LOGS();

    this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                               impulse_approx_total_forward_cs,
                                               cross_section );

    data_container.setImpulseApproxTotalCrossSection( cross_section );

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
  }

  // Set the total adjoint cross sections
  FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                    Utility::Italicized( "adjoint Waller-Hartree total" )
                                    << " cross section ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  this->calculateAdjointPhotonTotalCrossSection( true );

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

  FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                    Utility::Italicized( "adjoint impulse approx total" )
                                    << " cross section ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  this->calculateAdjointPhotonTotalCrossSection( false );

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

  // Set the adjoint pair/triplet production energy distributions
  FRENSIE_LOG_NOTIFICATION( " Setting the adjoint pair/triplet production "
                            "energy distributions:" );

  {
    // Set the adjoint pair production energy distribution
    FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                      Utility::Italicized( "adjoint pair production" )
                                      << " energy distribution data ... " );
    FRENSIE_FLUSH_ALL_LOGS();

    this->setAdjointPairProductionEnergyDistribution();

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

    // Set the adjoint triplet production energy distribution
    FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                      Utility::Italicized( "adjoint triplet production" )
                                      << " energy distribution data ... " );
    FRENSIE_FLUSH_ALL_LOGS();

    this->setAdjointTripletProductionEnergyDistribution();

    FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
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
      local_max_energy_grid.insert(
        local_max_energy_grid.end(),
        data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid( *subshell )[i].begin(),
        data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid( *subshell )[i].end() );

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
        data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid( *subshell )[i],
        data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection( *subshell )[i] );

      for( unsigned j = 0u; j < max_energy_grid[i].size(); ++j )
        cross_section[i][j] += subshell_cs.evaluate( max_energy_grid[i][j] );

      ++subshell;
    }
  }

  // Set the adjoint impulse approx total incoherent cross section
  data_container.setAdjointImpulseApproxIncoherentMaxEnergyGrid(
                                                             max_energy_grid );
  data_container.setAdjointImpulseApproxIncoherentCrossSection(cross_section );
}

// Calculate the adjoint photon total cross section
void StandardAdjointElectronPhotonRelaxationDataGenerator::calculateAdjointPhotonTotalCrossSection(
    const bool use_waller_hartree_adjoint_incoherent_cs )
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
{

}

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
  for ( shell; shell != data_container.getSubshells().end(); ++shell )
  {
    this->createAdjointElectroionizationSubshellGridGenerator(
      forward_electron_energy_grid,
      forward_grid_searcher,
      ionization_grid_generators[*shell],
      *shell );
  }

  std::list<double> union_energy_grid;

  this->initializeAdjointElectronUnionEnergyGrid( union_energy_grid,
                                                  ionization_grid_generators,
                                                  brem_grid_generator );

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
                                      MonteCarlo::MODIFIED_TWO_D_UNION,
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
  // Generate Grid Points For The Forward Inelastic Electron Cross Section Data
  //---------------------------------------------------------------------------//

  // Create the inelastic cross section distribution
  std::shared_ptr<const Utility::UnivariateDistribution>
    forward_inelastic_electron_cross_section;

  this->createForwardInelasticElectronCrossSectionDistribution(
            forward_inelastic_electron_cross_section );

  // Bind the distribution
  boost::function<double (double pz)> forward_inelastic_grid_function =
    boost::bind( &Utility::UnivariateDistribution::evaluate,
                 boost::cref( *forward_inelastic_electron_cross_section ),
                 _1 );

  //---------------------------------------------------------------------------//
  // Generate Grid Points For The Adjoint Atomic Excitation Cross Section Data
  //---------------------------------------------------------------------------//

  // Create the cross section distribution
  std::shared_ptr<const Utility::UnivariateDistribution> adjoint_excitation_cross_section;
  this->createAdjointAtomicExcitationCrossSectionDistribution(
          forward_electron_energy_grid,
          forward_grid_searcher,
          adjoint_excitation_cross_section );

  // Bind the distribution
  boost::function<double (double pz)> atomic_excitation_grid_function =
    boost::bind( &Utility::UnivariateDistribution::evaluate,
                 boost::cref( *adjoint_excitation_cross_section ),
                 _1 );

  FRENSIE_LOG_PARTIAL_NOTIFICATION( "     Adding Atomic Excitation data to the grid ... ");
  FRENSIE_FLUSH_ALL_LOGS();

  // Generate atomic excitation (don't generate new grid points above the last grid point)
  this->getDefaultElectronGridGenerator().refineInPlace(
    union_energy_grid,
    atomic_excitation_grid_function,
    this->getMinElectronEnergy(),
    data_container.getAdjointAtomicExcitationEnergyGrid().back() );

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
    this->getMinElectronEnergy(),
    brem_grid_generator->getNudgedMaxEnergy() );

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
      this->getMinElectronEnergy(),
      ionization_grid_generators[*shell]->getNudgedMaxEnergy() );

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
  std::vector<double> angular_energy_grid;
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
                          moment_preserving_weights );

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
  FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                    Utility::Italicized( "forward inelastic electron" )
                                    << " cross section ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  std::vector<double> forward_inelastic_cross_section;
  this->createCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      forward_inelastic_grid_function,
      forward_inelastic_cross_section,
      threshold );

  data_container.setForwardInelasticElectronCrossSection(
    forward_inelastic_cross_section );
  data_container.setForwardInelasticElectronCrossSectionThresholdEnergyIndex(
    threshold );

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );

//---------------------------------------------------------------------------//
// Set Atomic Excitation Data
//---------------------------------------------------------------------------//
  FRENSIE_LOG_PARTIAL_NOTIFICATION( "   Setting the " <<
                                    Utility::Italicized( "adjoint atomic excitation" )
                                    << " cross section ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  std::vector<double> excitation_cross_section;
  this->createCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      atomic_excitation_grid_function,
      excitation_cross_section,
      threshold );

  data_container.setAdjointAtomicExcitationCrossSection( excitation_cross_section );
  data_container.setAdjointAtomicExcitationCrossSectionThresholdEnergyIndex( threshold );
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

    std::map<double,std::vector<double> > brem_energy_grid, brem_pdf;
    brem_grid_generator->generateAndEvaluateDistributionOnPrimaryEnergyGrid(
      brem_energy_grid,
      brem_pdf,
      this->getAdjointBremsstrahlungEvaluationTolerance(),
      energy_grid,
      cross_section,
      threshold );

    /* It is impossible for the adjoint electron to scatter above the max
     * energy. Therefore, the distribution at the max energy will always be zero
     * To handle this the distribution is thrown out.
     */
    brem_energy_grid.erase(this->getMaxElectronEnergy() );
    brem_pdf.erase(this->getMaxElectronEnergy() );

    // Set the adjoint bremsstrahlung scattering distribution
    data_container.setAdjointElectronBremsstrahlungEnergy( brem_energy_grid );
    data_container.setAdjointElectronBremsstrahlungPDF( brem_pdf );
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

    std::map<double,std::vector<double> > ionization_energy_grid, ionization_pdf;
    ionization_grid_generators.find( *shell )->second->generateAndEvaluateDistributionOnPrimaryEnergyGrid(
      ionization_energy_grid,
      ionization_pdf,
      this->getAdjointElectroionizationEvaluationTolerance(),
      energy_grid,
      cross_section,
      threshold );

    /* It is impossible for the adjoint electron to scatter above the max
     * energy. Therefore, the distribution at the max energy will always be zero
     * To handle this the distribution is thrown out.
     */
    ionization_energy_grid.erase(this->getMaxElectronEnergy() );
    ionization_pdf.erase(this->getMaxElectronEnergy() );

    // Set the adjoint bremsstrahlung scattering distribution
    data_container.setAdjointElectroionizationRecoilPDF( *shell, ionization_pdf );
    data_container.setAdjointElectroionizationRecoilEnergy(
      *shell,
      ionization_energy_grid );
  }

  FRENSIE_LOG_NOTIFICATION( Utility::BoldGreen( "done." ) );
}

// Create the inelastic cross section distribution
void
StandardAdjointElectronPhotonRelaxationDataGenerator::createForwardInelasticElectronCrossSectionDistribution(
    std::shared_ptr<const Utility::UnivariateDistribution>&
        forward_inelastic_electron_cross_section_distribution ) const
{
  // Extract the atomic excitation cross section data
  std::vector<double> ae_cross_section =
    d_forward_epr_data->getAtomicExcitationCrossSection();
  unsigned ae_threshold_index =
    d_forward_epr_data->getAtomicExcitationCrossSectionThresholdEnergyIndex();

  // Extract the bremsstrahlung cross section data
  std::vector<double> brem_cross_section =
    d_forward_epr_data->getBremsstrahlungCrossSection();
  unsigned brem_threshold_index =
    d_forward_epr_data->getBremsstrahlungCrossSectionThresholdEnergyIndex();

  // Extract the total elastic cross section data
  std::map<unsigned,std::vector<double> > i_cross_sections;
  std::map<unsigned,unsigned> i_threshold_index;

  // Loop through the electroionization subshells
  std::set<unsigned>::iterator shell = d_forward_epr_data->getSubshells().begin();

  for ( shell; shell != d_forward_epr_data->getSubshells().end(); ++shell )
  {
    i_cross_sections[*shell] =
      d_forward_epr_data->getElectroionizationCrossSection( *shell );

    i_threshold_index[*shell] =
      d_forward_epr_data->getElectroionizationCrossSectionThresholdEnergyIndex( *shell );
  }

  // Calculate the forward inelastic electron cross section
  std::vector<double> forward_inelastic_electron_cross_section(
    d_forward_epr_data->getElectronEnergyGrid().size() );

  for( size_t i = 0; i < forward_inelastic_electron_cross_section.size(); ++i )
  {
    // Add atomic excitation cross section if above threshold
    if ( i >= ae_threshold_index )
    {
      forward_inelastic_electron_cross_section[i] +=
        ae_cross_section[i-ae_threshold_index];
    }

    // Add bremsstrahlung cross section if above threshold
    if ( i >= brem_threshold_index )
    {
      forward_inelastic_electron_cross_section[i] +=
        brem_cross_section[i-brem_threshold_index];
    }

    shell = d_forward_epr_data->getSubshells().begin();
    for ( shell; shell != d_forward_epr_data->getSubshells().end(); ++shell )
    {
      // Add electroionization subshell cross section if above threshold
      if ( i >= i_threshold_index[*shell] )
      {
        forward_inelastic_electron_cross_section[i] +=
            i_cross_sections[*shell].at( i - i_threshold_index[*shell]);
      }
    }
  }

  // Set the distribution
  forward_inelastic_electron_cross_section_distribution.reset(
    new Utility::TabularDistribution<Utility::LogLog>(
      d_forward_epr_data->getElectronEnergyGrid(),
      forward_inelastic_electron_cross_section ) );
}

// Create the adjoint atomic excitation cross section reaction
void StandardAdjointElectronPhotonRelaxationDataGenerator::createAdjointAtomicExcitationCrossSectionDistribution(
    const std::shared_ptr<const std::vector<double> >& forward_electron_energy_grid,
    const std::shared_ptr<Utility::HashBasedGridSearcher<double> >& forward_grid_searcher,
    std::shared_ptr<const Utility::UnivariateDistribution>&
      adjoint_excitation_cross_section_distribution )
{
  // Extract the atomic excitation cross section data
  std::shared_ptr<std::vector<double> > atomic_excitation_cross_section(
       new std::vector<double>( d_forward_epr_data->getAtomicExcitationCrossSection() ) );

  std::shared_ptr<MonteCarlo::ElectroatomicReaction> atomic_excitation_reaction(
    new MonteCarlo::VoidElectroatomicReaction<Utility::LogLog>(
        forward_electron_energy_grid,
        atomic_excitation_cross_section,
        d_forward_epr_data->getAtomicExcitationCrossSectionThresholdEnergyIndex(),
        forward_grid_searcher ) );

  // Find the upper and lower boundary bins for the min and max energy
  std::vector<double>::const_iterator energy_grid_start, energy_grid_end;
  this->findLowerAndUpperBinBoundary(
          this->getMinElectronEnergy(),
          this->getMaxElectronEnergy(),
          d_forward_epr_data->getAtomicExcitationEnergyGrid(),
          energy_grid_start,
          energy_grid_end );
  ++energy_grid_end;

  // Get the index of the energy_grid_start
  unsigned start_index = std::distance(
    d_forward_epr_data->getAtomicExcitationEnergyGrid().begin(),
    energy_grid_start );

  std::vector<double>::const_iterator energy_gain_start =
    d_forward_epr_data->getAtomicExcitationEnergyLoss().begin();

  // Advance the energy_gain_start to the same index as the energy_grid_start
  std::advance( energy_gain_start, start_index );

  // Make sure the first adjoint energy grid point is above the min electron energy
  while ( *energy_grid_start - *energy_gain_start < this->getMinElectronEnergy() )
  {
    ++energy_grid_start;
    ++energy_gain_start;
  }

  // Include the energy right below the min electron energy for interpolation purposes
  --energy_grid_start;
  --energy_gain_start;

  // Get the index of the energy_grid_start
  unsigned end_index = std::distance(
    d_forward_epr_data->getAtomicExcitationEnergyGrid().begin(),
    energy_grid_end );

  std::vector<double>::const_iterator energy_gain_end =
    d_forward_epr_data->getAtomicExcitationEnergyLoss().begin();

  // Advance the energy_gain_end to the same index as the energy_grid_end
  std::advance( energy_gain_end, end_index );

  std::vector<double> adjoint_excitation_energy_gain(
    energy_gain_start,
    energy_gain_end );

  std::vector<double> adjoint_excitation_energy_grid(
    energy_grid_start,
    energy_grid_end );

  std::vector<double> adjoint_excitation_cross_section(
    adjoint_excitation_energy_gain.size() );

  // calculate the adjoint incoming energy grid from the forward incoming energy grid and energy loss
  for ( int i = 0; i < adjoint_excitation_energy_grid.size(); ++i )
  {
    // Evaluate the cross section at the forward energy
    adjoint_excitation_cross_section[i] =
      atomic_excitation_reaction->getCrossSection( adjoint_excitation_energy_grid[i] );

    // Calculate the adjoint energy grid point at the forward energy
    adjoint_excitation_energy_grid[i] -= adjoint_excitation_energy_gain[i];
  }

  Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Set atomic excitation energy grid (adjoint energy grid = forward energy grid - forward energy loss)
  data_container.setAdjointAtomicExcitationEnergyGrid(
    adjoint_excitation_energy_grid );

  // Set atomic excitation energy gain (adjoint energy gain = forward energy loss)
  data_container.setAdjointAtomicExcitationEnergyGain(
    adjoint_excitation_energy_gain );

  // Make sure the adjoint cross section data included data up to the max electron energy
  for ( energy_grid_end; energy_grid_end != d_forward_epr_data->getAtomicExcitationEnergyGrid().end(); )
  {
    // Evaluate the cross section at the forward energy
    adjoint_excitation_cross_section.push_back(
      atomic_excitation_reaction->getCrossSection( *energy_grid_end ) );

    // Calculate the adjoint energy grid point at the forward energy
    adjoint_excitation_energy_grid.push_back( *energy_grid_end - *energy_gain_end );

    if( adjoint_excitation_energy_grid.back() >= this->getMaxElectronEnergy() )
      break;
    else
    {
      ++energy_grid_end;
      ++energy_gain_end;
    }
  }

  adjoint_excitation_cross_section_distribution.reset(
    new Utility::TabularDistribution<Utility::LogLog>(
      adjoint_excitation_energy_grid,
      adjoint_excitation_cross_section ) );

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

  // Create the brem distribution
  std::vector<double> energy_grid = d_forward_epr_data->getBremsstrahlungEnergyGrid();
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
      secondary_dists( energy_grid.size() );

  for( size_t n = 0; n < energy_grid.size(); ++n )
  {
    double energy = energy_grid[n];

    // Get the energy of the bremsstrahlung photon at the incoming energy
    std::vector<double> energy_bins(
        d_forward_epr_data->getBremsstrahlungPhotonEnergy( energy ) );

    // Get the bremsstrahlung photon pdf at the incoming energy
    std::vector<double> pdf(
        d_forward_epr_data->getBremsstrahlungPhotonPDF( energy ) );

    secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LinLin>( energy_bins,
                                                               pdf ) );
  }

  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> distribution;

  if( this->getElectronTwoDInterpPolicy() == MonteCarlo::LINLINLIN_INTERPOLATION )
  {
    distribution.reset(
      new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LinLinLin> >(
                  energy_grid,
                  secondary_dists,
                  1e-6,
                  this->getElectronTabularEvaluationTolerance() ) );
  }
  else if( this->getElectronTwoDInterpPolicy() == MonteCarlo::LOGLOGLOG_INTERPOLATION )
  {
    distribution.reset(
      new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LogLogLog> >(
                  energy_grid,
                  secondary_dists,
                  1e-6,
                  this->getElectronTabularEvaluationTolerance() ) );
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
      return distribution->evaluateSecondaryConditionalPDF( incoming_energy, incoming_energy - outgoing_energy); };

  grid_generator.reset(
    new ElectronGridGenerator(
        cs_evaluator,
        pdf_evaluator,
        min_energy_gain_function,
        energy_grid,
        this->getMinElectronEnergy(),
        this->getMaxElectronEnergy(),
        this->getAdjointBremsstrahlungMinEnergyNudgeValue(),
        this->getAdjointBremsstrahlungMaxEnergyNudgeValue(),
        this->getAdjointBremsstrahlungGridConvergenceTolerance(),
        this->getAdjointBremsstrahlungAbsoluteDifferenceTolerance(),
        this->getAdjointBremsstrahlungDistanceTolerance() ) );
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

  // Create the electroionization secondary distribution
  std::vector<double> energy_grid = d_forward_epr_data->getElectroionizationEnergyGrid(shell);
  std::vector<double> min_energy_grid( energy_grid.size() );
  std::vector<double> max_energy_grid( energy_grid.size() );

  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );

  // Get the binding energy
  double binding_energy = d_forward_epr_data->getSubshellBindingEnergy( shell );

  for( size_t n = 0; n < energy_grid.size(); ++n )
  {
    double energy = energy_grid[n];

      // Get the energy of the knock-on electron energy at the incoming energy
      std::vector<double> knock_on_energy(
          d_forward_epr_data->getElectroionizationRecoilEnergy( shell, energy ) );

      // Get the knock-on electron pdf at the incoming energy
      std::vector<double> knock_on_pdf(
          d_forward_epr_data->getElectroionizationRecoilPDF( shell, energy ) );

      double energy_2k;
      // If the grid point is not greater than the binding energy assumes for interpolation only
      if( energy <= binding_energy )
      {
        energy_2k = 2.0*knock_on_energy.back();
      }
      // Make sure the max knock-on energy matches the incoming energy
      else
      {
        energy_2k = energy - binding_energy;
        knock_on_energy.back() = energy_2k/2.0;
      }

      // Set the min knock-on energy for the incoming energy
      min_energy_grid[n] = knock_on_energy.front();
      // Set the max outgoing energy for the incoming energy
      max_energy_grid[n] = energy_2k - knock_on_energy.front();


    secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LinLin>( knock_on_energy,
                                                               knock_on_pdf ) );
  }

  std::shared_ptr<const Utility::TabularUnivariateDistribution> min_energy_distribution(
      new const Utility::TabularDistribution<Utility::LogLog>(
        max_energy_grid,
        min_energy_grid ) );

  // Create the min adjoint energy gain function for electroionization
  std::function<double(const double&)> min_energy_gain_function =
    [min_energy_distribution, binding_energy](const double& energy){
      return min_energy_distribution->evaluate(energy) + binding_energy;};

  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> distribution;

  if( this->getElectronTwoDInterpPolicy() == MonteCarlo::LINLINLIN_INTERPOLATION )
  {
    distribution.reset(
      new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LinLinLin> >(
              energy_grid,
              secondary_dists,
              1e-6,
              this->getElectronTabularEvaluationTolerance() ) );
  }
  else if( this->getElectronTwoDInterpPolicy() == MonteCarlo::LOGLOGLOG_INTERPOLATION )
  {
    distribution.reset(
      new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LogLogLog> >(
              energy_grid,
              secondary_dists,
              1e-6,
              this->getElectronTabularEvaluationTolerance() ) );
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
    [distribution, binding_energy](const double& incoming_energy, const double& outgoing_energy){
    double energy = outgoing_energy;
    double max_knock_on_energy = (incoming_energy - binding_energy)/2.0;

    if ( outgoing_energy > max_knock_on_energy )
    {
      energy = incoming_energy - binding_energy - outgoing_energy;
    }

    // Define function for the lower and upper bounds of the outgoing energy
    auto f_min = [distribution](double x){return distribution->getLowerBoundOfSecondaryConditionalIndepVar(x); };
    auto f_max = [binding_energy](double x){return (x - binding_energy)/2.0; };

    return distribution->evaluateSecondaryConditionalPDF( incoming_energy, energy, f_min, f_max );
  };

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
        this->getAdjointElectroionizationDistanceTolerance() ) );
}

// Initialize the electron union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::initializeAdjointElectronUnionEnergyGrid(
     std::list<double>& union_energy_grid,
     std::map<unsigned,std::shared_ptr<ElectronGridGenerator> > ionization_grid_generators,
     std::shared_ptr<ElectronGridGenerator> brem_grid_generator ) const
{
  // Add the screened Rutherford threshold energy
  std::vector<double> forward_energy_grid = d_forward_epr_data->getElectronEnergyGrid();
  unsigned rutherford_threshold = d_forward_epr_data->getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

  union_energy_grid.push_back( forward_energy_grid[rutherford_threshold] );

  // Add the nudged max energy for subshell electroionization reactions
  for( auto subshell : d_forward_epr_data->getSubshells() )
  {
    // Get the nudged max energy
    double nudged_max_energy =
      ionization_grid_generators[subshell]->getNudgedMaxEnergy();

    // Add to union energy grid
    union_energy_grid.push_back( nudged_max_energy );
  }

  // Add the nudged max energy for a bremsstrahlung reaction
  union_energy_grid.push_back( brem_grid_generator->getNudgedMaxEnergy() );

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
