//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp
//! \author Luke Kersting
//! \brief  The standard adjoint electron-photon-relaxation data generator class def.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp"
#include "DataGen_MomentPreservingElectronDataGenerator.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_AnalogElasticElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "MonteCarlo_StandardOccupationNumber.hpp"
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "MonteCarlo_WHIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_GridGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SloanRadauQuadrature.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"

namespace DataGen{

// Initialize the static member data
const double StandardAdjointElectronPhotonRelaxationDataGenerator::s_threshold_energy_nudge_factor = 1.0e-5;

// Advanced Constructor
StandardAdjointElectronPhotonRelaxationDataGenerator::StandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data,
      const double min_photon_energy,
      const double max_photon_energy,
      const double min_electron_energy,
      const double max_electron_energy,
      std::ostream* os_log,
      std::ostream* os_warn )
  : AdjointElectronPhotonRelaxationDataGenerator( forward_epr_data->getAtomicNumber(),
                                                  min_photon_energy,
                                                  max_photon_energy,
                                                  min_electron_energy,
                                                  max_electron_energy ),
    d_forward_epr_data( forward_epr_data ),
    d_os_log( os_log )
{
  // Make sure the forward epr data is valid
  testPrecondition( forward_epr_data.get() );
  // Make sure the log stream is valid
  testPrecondition( os_log != NULL );
  // Make sure the warning stream is valid
  testPrecondition( os_warn != NULL );

  // Check if the min photon energy is below the forward table min energy
  if( d_min_photon_energy < forward_epr_data->getMinPhotonEnergy() )
  {
    this->setMinPhotonEnergy( forward_epr_data->getMinPhotonEnergy() );

    (*os_warn) << "Warning: the min photon energy requested is below the "
               << "requested forward table min photon energy! The table's min "
               << "photon energy will be used instead."
               << std::endl;
  }

  // Check if the max photon energy is above the forward table max energy
  if( d_max_photon_energy > forward_epr_data->getMaxPhotonEnergy() )
  {
    this->setMaxPhotonEnergy( forward_epr_data->getMaxPhotonEnergy() );

    (*os_warn) << "Warning: the max photon energy requested is above the "
               << "requested forward table max photon energy! The table's max "
               << "photon energy will be used instead."
               << std::endl;
  }

  // Check if the min electron energy is below the forward table min energy
  if( d_min_electron_energy < forward_epr_data->getMinElectronEnergy() )
  {
    this->setMinElectronEnergy( forward_epr_data->getMinElectronEnergy() );

    (*os_warn) << "Warning: the min electron energy requested is above the "
               << "requested forward table min electron energy! The table's "
               << "min electron energy will be used instead."
               << std::endl;
  }

  // Check if the max electron energy is above the forward table max energy
  if( d_max_electron_energy > forward_epr_data->getMaxElectronEnergy() )
  {
    this->setMaxElectronEnergy( forward_epr_data->getMaxElectronEnergy() );

    (*os_warn) << "Warning: the max electron energy requested is above the "
               << "requested forward table max electron energy! The table's "
               << "max electron energy will be used instead."
               << std::endl;
  }

  // Initialize the table generation data
  this->initializeTableGenerationData();
}

// Basic Constructor
StandardAdjointElectronPhotonRelaxationDataGenerator::StandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data,
      std::ostream* os_log )
  : AdjointElectronPhotonRelaxationDataGenerator(
                                    forward_epr_data->getAtomicNumber(),
                                    forward_epr_data->getMinPhotonEnergy(),
                                    forward_epr_data->getMaxPhotonEnergy(),
                                    forward_epr_data->getMinElectronEnergy(),
                                    forward_epr_data->getMaxElectronEnergy() ),
    d_forward_epr_data( forward_epr_data ),
    d_os_log( os_log )
{
  // Make sure the forward epr data is valid
  testPrecondition( forward_epr_data.get() );
  // Make sure the log stream is valid
  testPrecondition( os_log != NULL );
  
  // Initialize the table generation data
  this->initializeTableGenerationData();
}

// Populate the adjoint electron-photon-relaxation data container
void StandardAdjointElectronPhotonRelaxationDataGenerator::populateEPRDataContainer(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // Set the table data
  data_container.setAtomicNumber( this->getAtomicNumber() );
  data_container.setMinPhotonEnergy( d_min_photon_energy );
  data_container.setMaxPhotonEnergy( d_max_photon_energy );
  data_container.setMinElectronEnergy( d_min_electron_energy );
  data_container.setMaxElectronEnergy( d_max_electron_energy );
  data_container.setCutoffAngleCosine( d_cutoff_angle_cosine );
  data_container.setNumberOfAdjointMomentPreservingAngles(
    d_number_of_moment_preserving_angles );
  data_container.setGridConvergenceTolerance( d_grid_convergence_tol );
  data_container.setGridAbsoluteDifferenceTolerance( d_grid_absolute_diff_tol );
  data_container.setGridDistanceTolerance( d_grid_distance_tol );

  // Set the relaxation data
  (*d_os_log) << std::endl << "Setting the adjoint relaxation data...";
  d_os_log->flush();
  this->setAdjointRelaxationData( data_container );
  (*d_os_log) << "done." << std::endl;

  // Set the Compton profile data
  (*d_os_log) << "Setting the Compton profile data...";
  d_os_log->flush();
  this->setComptonProfileData( data_container );
  (*d_os_log) << "done." << std::endl;

  // Set the occupation number data
  (*d_os_log) << "Setting the occupation number data...";
  d_os_log->flush();
  this->setOccupationNumberData( data_container );
  (*d_os_log) << "done." << std::endl;

  // Set the Waller-Hartree scattering function data
  (*d_os_log) << "Setting the Waller-Hartree scattering function data...";
  d_os_log->flush();
  this->setWallerHartreeScatteringFunctionData( data_container );
  (*d_os_log) << "done." << std::endl;

  // Set the Waller-Hartree atomic form factor data
  (*d_os_log) << "Setting the Waller-Hartree atomic form factor data...";
  d_os_log->flush();
  this->setWallerHartreeAtomicFormFactorData( data_container );
  (*d_os_log) << "done." << std::endl;

  // Set the photon data
  (*d_os_log) << "Setting the adjoint photon data... " << std::endl;
  d_os_log->flush();
  this->setAdjointPhotonData( data_container );
  (*d_os_log) << "done." << std::endl;

  // Set the electron data
  (*d_os_log) << "Setting the adjoint electron data: " << std::endl;
  this->setAdjointElectronData( data_container );
  (*d_os_log) << "done." << std::endl;

}

// Repopulate the electron moment preserving data
void StandardAdjointElectronPhotonRelaxationDataGenerator::repopulateAdjointMomentPreservingData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    const double cutoff_angle_cosine,
    const unsigned number_of_moment_preserving_angles )
{
  data_container.setCutoffAngleCosine( cutoff_angle_cosine );
  data_container.setNumberOfAdjointMomentPreservingAngles( 
    number_of_moment_preserving_angles );

  std::vector<double> adjoint_angular_energy_grid(
    data_container.getAdjointElasticAngularEnergyGrid() );

  (*d_os_log) << std::endl << "Setting the adjoint moment preserving electron data...";
  d_os_log->flush();
  StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointMomentPreservingData( 
    adjoint_angular_energy_grid, 
    data_container );
  (*d_os_log) << "done." << std::endl;
}

// Set the relaxation data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointRelaxationData(
			   Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const
{
  // Extract and set the subshells
  const std::set<unsigned>& subshells = d_forward_epr_data->getSubshells();
  
  data_container.setSubshells( subshells );

  // Extract and set the other subshell data
  std::set<unsigned>::const_iterator subshell_it =
    subshells.begin();
  
  while( subshell_it != subshells.end() )
  {
    data_container.setSubshellOccupancy(
                    *subshell_it,
                    d_forward_epr_data->getSubshellOccupancy( *subshell_it ) );

    data_container.setSubshellBindingEnergy(
                *subshell_it,
                d_forward_epr_data->getSubshellBindingEnergy( *subshell_it ) );

    ++subshell_it;
  }
}

// Set the Compton profile data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setComptonProfileData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // Get the subshells
  const std::set<unsigned>& subshells = d_forward_epr_data->getSubshells();

  std::set<unsigned>::const_iterator subshell_it =
    subshells.begin();
  
  // Extract and set the Compton profiles and grids
  while( subshell_it != subshells.end() )
  {
    data_container.setComptonProfileMomentumGrid(
           *subshell_it,
           d_forward_epr_data->getComptonProfileMomentumGrid( *subshell_it ) );

    data_container.setComptonProfile(
                       *subshell_it,
                       d_forward_epr_data->getComptonProfile( *subshell_it ) );

    ++subshell_it;
  }
}

// Set the occupation number data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setOccupationNumberData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // Get the subshells
  const std::set<unsigned>& subshells = d_forward_epr_data->getSubshells();

  std::set<unsigned>::const_iterator subshell_it =
    subshells.begin();

  // Extract and set the occupation numbers and grids
  while( subshell_it != subshells.end() )
  {
    data_container.setOccupationNumberMomentumGrid(
         *subshell_it,
         d_forward_epr_data->getOccupationNumberMomentumGrid( *subshell_it ) );

    data_container.setOccupationNumber(
                     *subshell_it,
                     d_forward_epr_data->getOccupationNumber( *subshell_it ) );

    ++subshell_it;
  }
}

// Set the Waller-Hartree scattering function data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setWallerHartreeScatteringFunctionData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // Extract and set the scattering function grid
  data_container.setWallerHartreeScatteringFunctionMomentumGrid(
        d_forward_epr_data->getWallerHartreeScatteringFunctionMomentumGrid() );

  // Extract and set the scattering function
  data_container.setWallerHartreeScatteringFunction(
                    d_forward_epr_data->getWallerHartreeScatteringFunction() );
}

//! Set the Waller-Hartree atomic form factor data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setWallerHartreeAtomicFormFactorData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // Extract and set the atomic form factor grid
  data_container.setWallerHartreeAtomicFormFactorMomentumGrid(
          d_forward_epr_data->getWallerHartreeAtomicFormFactorMomentumGrid() );

  // Extract and set the atomic form
  data_container.setWallerHartreeAtomicFormFactor(
                      d_forward_epr_data->getWallerHartreeAtomicFormFactor() );
}

// Set the photon data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointPhotonData(
			   Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const
{
  // Extract the coherent cross section
  std::shared_ptr<const Utility::OneDDistribution> waller_hartree_coherent_cs(
       new Utility::TabularDistribution<Utility::LinLin>(
                d_forward_epr_data->getPhotonEnergyGrid(),
                d_forward_epr_data->getWallerHartreeCoherentCrossSection() ) );

  // Extract the Waller-Hartree total forward cross section
  std::shared_ptr<const Utility::OneDDistribution> waller_hartree_total_forward_cs(
       new Utility::TabularDistribution<Utility::LinLin>(
                   d_forward_epr_data->getPhotonEnergyGrid(),
                   d_forward_epr_data->getWallerHartreeTotalCrossSection() ) );

  // Extract the impulse approx. total forward cross section
  std::shared_ptr<const Utility::OneDDistribution> impulse_approx_total_forward_cs(
       new Utility::TabularDistribution<Utility::LinLin>(
                   d_forward_epr_data->getPhotonEnergyGrid(),
                   d_forward_epr_data->getImpulseApproxTotalCrossSection() ) );

  // Create the Waller-Hartree incoherent adjoint cross section evaluator
  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
    waller_hartree_incoherent_adjoint_cs_evaluator;

  this->createWallerHartreeIncoherentAdjointCrossSectionEvaluator(
                               waller_hatree_incoherent_adjoint_cs_evaluator );

  // Create the impulse approx. incoherent adjoint cross section evaluators
  Teuchos::Array<std::pair<unsigned,std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution> > >
    impulse_approx_incoherent_adjoint_cs_evaluators;

  this->createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluators(
                                     impulse_approx_incoherent_cs_evaluators );

  // Create the union energy grid
  (*d_os_log) << " Creating union energy grid";
  d_os_log->flush();

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

  (*d_os_log) << "done." << std::endl;

  // Set the union energy grid
  std::vector<double> energy_grid;
  energy_grid.assign( union_energy_grid.begin(),
                      union_energy_grid.end() );

  data_container.setAdjointPhotonEnergyGrid( energy_grid );

  // Create and set the 2-D cross sections
  {
    std::vector<std::vector<double> > max_energy_grid, cross_section;

    (*d_os_log) << " Setting the Waller-Hartree incoherent adjoint "
                << " cross section...";
    d_os_log->flush();
    
    this->createCrossSectionOnUnionEnergyGrid(
                                union_energy_grid,
                                waller_hartree_incoherent_adjoint_cs_evaluator,
                                max_energy_grid,
                                cross_section );

    data_container.setAdjointWallerHartreeIncoherentMaxEnergyGrid(
                                                             max_energy_grid );
    data_container.setAdjointWallerHartreeIncoherentCrossSection(
                                                               cross_section );
    (*d_os_log) << "done." << std::endl;

    for( unsigned i = 0u; i < impulse_approx_incoherent_adjoint_cs_evaluators.size(); ++i )
    {
      (*d_os_log) << " Setting the subshell "
                  << impulse_approx_incoherent_adjoint_cs_evaluators[i].first
                  << " impulse approx incoherent adjoint cross section...";
      d_os_log->flush();

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

      (*d_os_log) << "done." << std::endl;
    }
  }

  // Create and set the 1-D cross sections
  {
    std::vector<double> cross_section;

    (*d_os_log) << " Setting the Waller-Hartree coherent adjoint "
                << " cross section...";
    d_os_log->flush();

    this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                               waller_hartree_coherent_cs,
                                               cross_section );

    data_container.setAdjointWallerHartreeCoherentCrossSection(cross_section);

    (*d_os_log) << "done." << std::endl;

    (*d_os_log) << " Setting the forward Waller-Hartree total "
                << " cross section...";
    d_os_log->flush();

    this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                               waller_hartree_total_forward_cs,
                                               cross_section );

    data_container.setWallerHartreeTotalCrossSection( cross_section );

    (*d_os_log) << "done." << std::endl;

    (*d_os_log) << " Setting the forward impulse approx. total "
                << " cross section...";
    d_os_log->flush();

    this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                               impulse_approx_total_forward_cs,
                                               cross_section );

    (*d_os_log) << "done." << std::endl;
  }
}

// Create the adjoint Waller-Hartree incoherent cs evaluator
void StandardAdjointElectronPhotonRelaxationDataGenerator::createAdjointWallerHartreeIncoherentCrossSectionEvaluator(
         std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>& cs_evaluator ) const
{
  // Create a scattering function
  std::shared_ptr<const Utility::UnitAwareOneDDistribution<Utility::Units::InverseCentimeter,void> > raw_scattering_function(
         new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseCentimeter,void>(
          d_forward_epr_data->getWallerHartreeScatteringFunctionMomentumGrid(),
          d_forward_epr_data->getWallerHartreeScatteringFunction() ) );
    
  std::shared_ptr<const MonteCarlo::ScatteringFunction> scattering_function(
         new MonteCarlo::StandardScatteringFunction<Utility::Units::InverseCentimeter>(
                                                   raw_scattering_function ) );

  // Create the cross section evaluator
  cs_evaluator.reset(
               new MonteCarlo::WHIncoherentAdjointPhotonScatteringDistribution(
                                                       d_max_photon_energy,
                                                       scattering_function ) );
}

// Create an adjoint subshell impulse approx incoherent cs evaluator
void StandardAdjointElectronPhotonRelaxationDataGenerator::createAdjointSubshellImpulseApproxIncoherentCrossSectionEvaluator(
         const unsigned subshell,
         std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>& cs_evaluator ) const
{
  // Create the occupation number
  std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::MeCMomentum,void> > raw_occupation_number(
    new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,void>(
               d_forward_epr_data->getOccupationNumberMomentumGrid( subshell ),
               d_forward_epr_data->getOccupationNumber( subshell ) ) );

  std::shared_ptr<MonteCarlo::OccupationNumber> occupation_number(
         new MonteCarlo::StandardOccupationNumber<Utility::Units::MeCMomentum>(
                                                     raw_occupation_number ) );

  cs_evaluator.reset(
        new MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution(
                  d_max_photon_energy,
                  Data::convertENDFDesignatorToSubshellEnum( subshell ),
                  d_forward_epr_data->getSubshellOccupancy( subshell ),
                  d_forward_epr_data->getSubshellBindingEnergy( subshell ),
                  occupation_number ) );
}

// Create an adjoint incoherent grid generator
// void createAdjointIncoherentGridGenerator(
//        const std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>& incoherent_cs_evaluator,
//        std::shared_ptr<const AdjointIncoherentGridGenerator>& grid_generator )
// {
  
// }


void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointElectronData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
// //---------------------------------------------------------------------------//
// // Set Electron Cross Section Data Data
// //---------------------------------------------------------------------------//
// /*! \details The cross section data is needed for caluculating the 
//  *  moment preserving data and must be set first.
//  */
//   (*d_os_log) << " Setting the adjoint electron cross section data:" << std::endl;
//   d_os_log->flush();
//   //---------------------------------------------------------------------------//
//   // Extract The Elastic Cross Section Data
//   //---------------------------------------------------------------------------//
//   // Extract the cutoff elastic cross section data
//   std::shared_ptr<const Utility::OneDDistribution> cutoff_elastic_cross_section(
//     new Utility::TabularDistribution<Utility::LogLog>(
//       d_forward_endl_data->getElasticEnergyGrid(),
//       d_forward_endl_data->getCutoffElasticCrossSection() ) );

//   // Extract the total elastic cross section data
//   std::shared_ptr<const Utility::OneDDistribution>total_elastic_cross_section(
//     new Utility::TabularDistribution<Utility::LogLog>(
//       d_forward_endl_data->getElasticEnergyGrid(),
//       d_forward_endl_data->getTotalElasticCrossSection() ) );

//   //---------------------------------------------------------------------------//
//   // Extract The Adjoint Atomic Excitation Cross Section Data
//   //---------------------------------------------------------------------------//

//   std::vector<double>::const_iterator energy_gain_start =
//     d_forward_endl_data->getAtomicExcitationEnergyLoss().begin();

//   std::vector<double>::const_iterator energy_grid_start =
//     d_forward_endl_data->getAtomicExcitationEnergyGrid().begin();

//   std::vector<double>::const_iterator cross_section_start =
//     d_forward_endl_data->getAtomicExcitationCrossSection().begin();

//   // Make sure the first energy grid point is not zero
//   if ( d_forward_endl_data->getAtomicExcitationEnergyLoss().front() ==
//        d_forward_endl_data->getAtomicExcitationEnergyGrid().front() )
//   {
//     ++energy_gain_start;
//     ++energy_grid_start;
//     ++cross_section_start;
//   }

//   // Find the index of the energy grid for the max electron energy
//   unsigned end_excitation_index =
//     Utility::Search::binaryLowerBoundIndex(
//               energy_grid_start,
//               d_forward_endl_data->getAtomicExcitationEnergyGrid().end(),
//               d_max_electron_energy );

//   std::vector<double> adjoint_excitation_energy_gain( energy_gain_start,
//     d_forward_endl_data->getAtomicExcitationEnergyLoss().end() );

//   std::vector<double> adjoint_excitation_energy_grid( energy_grid_start,
//     d_forward_endl_data->getAtomicExcitationEnergyGrid().end() );

//   std::vector<double> adjoint_excitation_cross_section( cross_section_start,
//     d_forward_endl_data->getAtomicExcitationCrossSection().end() );

//   // Calcualte the adjoint icoming energy grid from the forward incoming energy grid and energy loss
//   for ( int i = 0; i < adjoint_excitation_energy_grid.size(); i++ )
//   {
//     adjoint_excitation_energy_grid[i] -= adjoint_excitation_energy_gain[i];
//   }

//   // Set atomic excitation energy gain (adjoint energy gain = forward energy loss)
//   data_container.setAdjointAtomicExcitationEnergyGrid(
//     adjoint_excitation_energy_grid );
//   data_container.setAdjointAtomicExcitationEnergyGain(
//     adjoint_excitation_energy_gain );

//   std::shared_ptr<const Utility::OneDDistribution> atomic_excitation_cross_section(
//     new Utility::TabularDistribution<Utility::LinLin>(
//       adjoint_excitation_energy_grid,
//       adjoint_excitation_cross_section ) );

//   //---------------------------------------------------------------------------//
//   // Create The Adjoint Bremsstrahlung Cross Section Evaluator
//   //---------------------------------------------------------------------------//
//   // The adjoint bremsstrahlung cross section evaluator
//   std::shared_ptr<DataGen::AdjointBremsstrahlungCrossSectionEvaluator>
//     adjoint_bremsstrahlung_cs_evaluator;

//   this->createAdjointBremsstrahlungCrossSectionEvaluator(
//           data_container,
//           adjoint_bremsstrahlung_cs_evaluator );
// /*
//   //---------------------------------------------------------------------------//
//   // Get Electroionization Data Cross Section Data
//   //---------------------------------------------------------------------------//

//   std::set<unsigned>::iterator shell = data_container.getSubshells().begin();

//   std::vector<std::pair<unsigned,std::shared_ptr<const Utility::OneDDistribution> > >
//     electroionization_cross_section;

//   // Loop through electroionization data for every subshell
//   for ( shell; shell != data_container.getSubshells().end(); shell++ )
//   {
//   std::shared_ptr<const Utility::OneDDistribution> subshell_cross_section;

//   raw_energy_grid =
//       d_forward_endl_data->getElectroionizationCrossSectionEnergyGrid( *shell );

//   subshell_cross_section.reset(
//       new Utility::TabularDistribution<Utility::LinLin>(
//       raw_energy_grid,
//       d_forward_endl_data->getElectroionizationCrossSection( *shell ) ) );

//   // merge raw energy grid with the union energy grid
//   mergeAdjointElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

//   electroionization_cross_section.push_back(
//       std::make_pair( *shell, subshell_cross_section ) );
//   }
// */

//   //---------------------------------------------------------------------------//
//   // Create union energy grid and calculate cross sections
//   //---------------------------------------------------------------------------//

//   // Create the union energy grid
//   (*d_os_log) << "   Creating union energy grid";
//   d_os_log->flush();
//   std::list<double> union_energy_grid;

//   this->initializeAdjointElectronUnionEnergyGrid(
//           data_container,
//           union_energy_grid );

//   Utility::GridGenerator<Utility::LinLin>
//   union_energy_grid_generator( d_grid_convergence_tol,
//                                d_grid_absolute_diff_tol,
//                                d_grid_distance_tol );

//   // Calculate the union energy grid
//   boost::function<double (double pz)> grid_function =
//     boost::bind( &Utility::OneDDistribution::evaluate,
//                  boost::cref( *cutoff_elastic_cross_section ),
//                  _1 );

//   union_energy_grid_generator.generateInPlace( union_energy_grid,
//                                                grid_function );

//   (*d_os_log) << ".";
//   d_os_log->flush();

//   grid_function = 
//     boost::bind( &Utility::OneDDistribution::evaluate,
//                  boost::cref( *total_elastic_cross_section ),
//                  _1 );

//   union_energy_grid_generator.generateInPlace( union_energy_grid,
//                                                grid_function );

//   (*d_os_log) << ".";
//   d_os_log->flush();

//   grid_function = boost::bind( &Utility::OneDDistribution::evaluate,
//   		                   boost::cref( *atomic_excitation_cross_section ),
//   		                   _1 );

//   std::list<double>::iterator it =
//     Utility::Search::binaryLowerBound(
//         union_energy_grid.begin(),
//         union_energy_grid.end(),
//         adjoint_excitation_energy_grid[end_excitation_index] );

//   std::list<double> temp_union_energy_grid;
//   temp_union_energy_grid.splice(
//     temp_union_energy_grid.begin(), union_energy_grid, union_energy_grid.begin(), it );

//   union_energy_grid_generator.generateInPlace( temp_union_energy_grid,
//                                                grid_function );

//   union_energy_grid.merge( temp_union_energy_grid );

//   (*d_os_log) << ".";
//   d_os_log->flush();


//   grid_function = 
//     boost::bind( &DataGen::AdjointBremsstrahlungCrossSectionEvaluator::evaluateAdjointCrossSection,
//                  boost::cref( *adjoint_bremsstrahlung_cs_evaluator ),
//                  _1,
//                  d_adjoint_bremsstrahlung_evaluation_tolerance );

//   std::vector<double> old_adjoint_bremsstrahlung_cs;

//   union_energy_grid_generator.generateAndEvaluateInPlace(
//     union_energy_grid,
//     old_adjoint_bremsstrahlung_cs,
//     grid_function );

//   std::list<double> old_adjoint_bremsstrahlung_union_energy_grid(
//     union_energy_grid );

//   (*d_os_log) << ".";
//   d_os_log->flush();
// /*
//   for( unsigned i = 0; i < electroionization_cross_section.size(); ++i )
//   {
//   grid_function = boost::bind(
//   	   &Utility::OneDDistribution::evaluate,
//   	   boost::cref( *electroionization_cross_section[i].second ),
//   	   _1 );

//   union_energy_grid_generator.generateInPlace( union_energy_grid,
//                                               grid_function );
//   (*d_os_log) << ".";
//   d_os_log->flush();
//   }
// */
//   (*d_os_log) << "done." << std::endl;

//   // Set the union energy grid
//   std::vector<double> energy_grid(
//         union_energy_grid.begin(),
//         union_energy_grid.end() );

//   data_container.setAdjointElectronEnergyGrid( energy_grid );

//   // Create and set the cross sections
//   std::vector<double> cross_section;
//   unsigned threshold;

//   // Set the adjoint elastic cross section data
//   (*d_os_log) << "   Setting the adjoint total elastic cross section...";
//   d_os_log->flush();
//   std::vector<double> total_cross_section;
//   this->createAdjointCrossSectionOnUnionEnergyGrid(
//       union_energy_grid,
//       total_elastic_cross_section,
//       total_cross_section,
//       threshold );
//   data_container.setAdjointTotalElasticCrossSection( total_cross_section );
//   data_container.setAdjointTotalElasticCrossSectionThresholdEnergyIndex( threshold );
//   (*d_os_log) << "done." << std::endl;

//   (*d_os_log) << "   Setting the adjoint cutoff elastic cross section...";
//   d_os_log->flush();
//   std::vector<double> cutoff_cross_section;
//   this->createAdjointCrossSectionOnUnionEnergyGrid(
//       union_energy_grid,
//       cutoff_elastic_cross_section,
//       cutoff_cross_section,
//       threshold );
//   data_container.setAdjointCutoffElasticCrossSection( cutoff_cross_section );
//   data_container.setAdjointCutoffElasticCrossSectionThresholdEnergyIndex( threshold );
//   (*d_os_log) << "done." << std::endl;


//   (*d_os_log) << "   Setting the screened Rutherford elastic cross section...";
//   d_os_log->flush();
//   {
//   std::vector<double> raw_cross_section( total_cross_section.size() );
//   for ( int i = 0; i < total_cross_section.size(); ++i )
//   {
//       raw_cross_section.at(i) = total_cross_section.at(i) - cutoff_cross_section.at(i);

//       double relative_difference = raw_cross_section.at(i)/total_cross_section.at(i);

//       // Check for roundoff error and reduce to zero if needed
//       if ( relative_difference < 1.0e-6 )
//       {
//           raw_cross_section[i] = 0.0;

//           // Update threshold index
//           threshold = i+1;
//       }
//   }

//   std::vector<double>::iterator start = raw_cross_section.begin();
//   std::advance( start, threshold );

//   cross_section.assign( start, raw_cross_section.end() );

//   data_container.setAdjointScreenedRutherfordElasticCrossSection( cross_section );
//   data_container.setAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(
//   threshold );
//   }
//   (*d_os_log) << "done." << std::endl;

//   // Set the adjoint atomic excitation cross section data
//   (*d_os_log) << "   Setting the adjoint atomic excitation cross section...";
//   d_os_log->flush();
//   std::vector<double> excitation_cross_section;
//   this->createAdjointCrossSectionOnUnionEnergyGrid(
//       union_energy_grid,
//       atomic_excitation_cross_section,
//       excitation_cross_section,
//       threshold );

//   data_container.setAdjointAtomicExcitationCrossSection( excitation_cross_section );
//   data_container.setAdjointAtomicExcitationCrossSectionThresholdEnergyIndex( threshold );
//   (*d_os_log) << "done." << std::endl;

//   // Set the adjoint bremsstrahlung cross section data
//   (*d_os_log) << "   Setting the adjoint bremsstrahlung cross section...";
//   d_os_log->flush();
//   this->createAdjointCrossSectionOnUnionEnergyGrid(
//       union_energy_grid,
//       old_adjoint_bremsstrahlung_union_energy_grid,
//       old_adjoint_bremsstrahlung_cs,  
//       adjoint_bremsstrahlung_cs_evaluator,
//       cross_section,
//       threshold );

//   data_container.setAdjointBremsstrahlungCrossSection( cross_section );
//   data_container.setAdjointBremsstrahlungCrossSectionThresholdEnergyIndex( threshold );
//   (*d_os_log) << "done." << std::endl;


// //---------------------------------------------------------------------------//
// // Set Elastic Data
// //---------------------------------------------------------------------------//
//   (*d_os_log) << " Setting the adjoint elastic cutoff data...";
//   d_os_log->flush();

//   // Set elastic angular distribution
//   std::map<double,std::vector<double> > elastic_pdf, elastic_angle;

//   // Get energy bin below/equal to d_min_electron_energy
//   std::vector<double>::const_iterator start =
//     Utility::Search::binaryLowerBound(
//         d_forward_endl_data->getCutoffElasticAngularEnergyGrid().begin(),
//         d_forward_endl_data->getCutoffElasticAngularEnergyGrid().end(),
//         d_min_electron_energy );

//   // Get energy bin above/equal to d_max_electron_energy
//   std::vector<double>::const_iterator end =
//     Utility::Search::binaryUpperBound(
//         start,
//         d_forward_endl_data->getCutoffElasticAngularEnergyGrid().end(),
//         d_max_electron_energy );
//   ++end;

//   std::vector<double> angular_energy_grid( start, end );

//   /* ENDL gives the angular distribution in terms of the change in angle cosine
//    * (delta_angle_cosine = 1 - angle_cosine). For the native format it needs to
//    * be in terms of angle_cosine. This for loop flips the distribution and
//    * changes the variables to angle_cosine.
//    */
//   for ( start; start != end; ++start )
//   {
//     calculateElasticAngleCosine(
//         d_forward_endl_data->getCutoffElasticAnglesAtEnergy( *start ),
//         d_forward_endl_data->getCutoffElasticPDFAtEnergy( *start ),
//         elastic_angle[*start],
//         elastic_pdf[*start] );
//   }

//   // Evlauate the scattering distribution for the min energy (if necessary) 
//   if( angular_energy_grid.front() != d_min_electron_energy )
//   {
//     // Create the distribution above and below the min energy for interpolation
//     Utility::TabularDistribution<Utility::LinLin> lower_distribution(
//         elastic_angle[angular_energy_grid[0] ],
//         elastic_pdf[angular_energy_grid[0] ] );

//     Utility::TabularDistribution<Utility::LinLin> upper_distribution(
//         elastic_angle[angular_energy_grid[1] ],
//         elastic_pdf[angular_energy_grid[1] ] );

//     // Get the angular scattering grid for the min energy
//     std::vector<double> min_angles =
//       MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
//         d_forward_endl_data->getCutoffElasticAngles(),
//         d_min_electron_energy,
//         d_cutoff_angle_cosine );

//     // Get the pdf values for the min energy
//     std::vector<double> min_pdf( min_angles.size() );
//     for ( int i = 0; i < min_angles.size(); ++i )
//     {
//       min_pdf.at(i) = Utility::LinLog::interpolate(
//             angular_energy_grid[0],
//             angular_energy_grid[1],
//             d_min_electron_energy,
//             lower_distribution.evaluatePDF( min_angles.at(i) ),
//             upper_distribution.evaluatePDF( min_angles.at(i) ) );
//     }

//     // Set the distribution at the min energy
//     elastic_angle.emplace_hint(
//         elastic_angle.begin(),
//         d_min_electron_energy,
//         min_angles);

//     elastic_pdf.emplace_hint(
//         elastic_pdf.begin(),
//         d_min_electron_energy,
//         min_pdf);

//     // Erase the old front distribution
//     elastic_angle.erase( angular_energy_grid.front() );
//     elastic_pdf.erase( angular_energy_grid.front() );

//     angular_energy_grid.front() = d_min_electron_energy;
//   }

//   // Evlauate the scattering distribution for the max energy (if necessary) 
//   if( angular_energy_grid.back() != d_max_electron_energy )
//   {
//     // Create the distribution above and below the max energy for interpolation
//     Utility::TabularDistribution<Utility::LinLin> lower_distribution(
//         elastic_angle[angular_energy_grid[angular_energy_grid.size()-2] ],
//         elastic_pdf[angular_energy_grid[angular_energy_grid.size()-2] ] );

//     Utility::TabularDistribution<Utility::LinLin> upper_distribution(
//         elastic_angle[angular_energy_grid.back() ],
//         elastic_pdf[angular_energy_grid.back() ] );

//     // Get the angular scattering grid for the max energy
//     std::vector<double> max_angles =
//       MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
//         d_forward_endl_data->getCutoffElasticAngles(),
//         d_max_electron_energy,
//         d_cutoff_angle_cosine );

//     // Get the pdf values for the max energy
//     std::vector<double> max_pdf( max_angles.size() );
//     for ( int i = 0; i < max_angles.size(); ++i )
//     {
//       max_pdf.at(i) = Utility::LinLog::interpolate(
//             angular_energy_grid.at(angular_energy_grid.size()-2),
//             angular_energy_grid.back(),
//             d_max_electron_energy,
//             lower_distribution.evaluatePDF( max_angles.at(i) ),
//             upper_distribution.evaluatePDF( max_angles.at(i) ) );
//     }

//     // Set the distribution at the max energy
//     elastic_angle.emplace_hint(
//         elastic_angle.end(),
//         d_max_electron_energy,
//         max_angles);

//     elastic_pdf.emplace_hint(
//         elastic_pdf.end(),
//         d_max_electron_energy,
//         max_pdf);

//     // Erase the back distribution
//     elastic_angle.erase( angular_energy_grid.front() );
//     elastic_pdf.erase( angular_energy_grid.front() );

//     angular_energy_grid.back() = d_max_electron_energy;
//   }

//   data_container.setAdjointElasticAngularEnergyGrid( angular_energy_grid );
//   data_container.setAdjointCutoffElasticPDF( elastic_pdf );
//   data_container.setAdjointCutoffElasticAngles( elastic_angle );

//   (*d_os_log) << "done." << std::endl;

//   if ( d_cutoff_angle_cosine > 0.999999 )
//   {
//     (*d_os_log) << " Moment preserving data will not be generated because the"
//               << " cutoff angle cosine is greater than 0.999999." << std::endl
//               << " cutoff_angle_cosine = " << d_cutoff_angle_cosine << std::endl;
//   }
//   else if ( d_number_of_moment_preserving_angles < 1 )
//   {
//     (*d_os_log) << " Moment preserving data will not be generated because the"
//               << " number of moment preserving angles is less than 1." << std::endl
//               << " number_of_moment_preserving_angles = "
//               << d_number_of_moment_preserving_angles << std::endl;
//   }
//   else
//   {
//     (*d_os_log) << " Setting the adjoint elastic moment preserving data...";
//     d_os_log->flush();
//     // Set the moment preserving data
//     StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointMomentPreservingData(
//         angular_energy_grid,
//         data_container );
//     (*d_os_log) << "done." << std::endl;
//   }

// //---------------------------------------------------------------------------//
// // Set Bremsstrahlung Data
// //---------------------------------------------------------------------------//
//   (*d_os_log) << " Setting the bremsstrahlung data...";
//   d_os_log->flush();

//   std::vector<double> adjoint_bremsstrahlung_energy_grid =
//     data_container.getAdjointBremsstrahlungEnergyGrid();

//   Teuchos::ArrayRCP<double> adjoint_electron_energy_grid;
//   adjoint_electron_energy_grid.assign(
//     union_energy_grid.begin(),
//     union_energy_grid.end() );

//   Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
//       new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
//                 adjoint_electron_energy_grid,
//                 adjoint_electron_energy_grid[0],
//                 adjoint_electron_energy_grid[adjoint_electron_energy_grid.size()-1],
//                 adjoint_electron_energy_grid.size()/10 + 1 ) );

//   Teuchos::ArrayRCP<double> adjoint_bremsstrahlung_cross_section;
//   adjoint_bremsstrahlung_cross_section.assign(
//     data_container.getAdjointBremsstrahlungCrossSection().begin(),
//     data_container.getAdjointBremsstrahlungCrossSection().end() );

//   // Calculate the adjoint PDF at the different incoming adjoint energies and photon energies
//   std::map<double, std::vector<double> > adjoint_bremsstrahlung_pdf_map;

//   // Evaluate the PDF values for all but the max energy
//   for ( int i = 0; i < adjoint_bremsstrahlung_energy_grid.size()-1; i++ )
//   {
//     unsigned bin_index =
//       grid_searcher->findLowerBinIndex( adjoint_bremsstrahlung_energy_grid.at(i) );

//     std::vector<double> adjoint_bremsstrahlung_photon_energies;

//     if ( d_forward_endl_data->getBremsstrahlungPhotonEnergy().count(
//             adjoint_bremsstrahlung_energy_grid.at(i) ) )
//     {
//       adjoint_bremsstrahlung_photon_energies =
//         d_forward_endl_data->getBremsstrahlungPhotonEnergyAtEnergy(
//             adjoint_bremsstrahlung_energy_grid.at(i) );

//       data_container.setAdjointBremsstrahlungPhotonEnergyAtIncomingEnergy(
//         adjoint_bremsstrahlung_energy_grid.at(i),
//         adjoint_bremsstrahlung_photon_energies );
//     }
//     else if( adjoint_bremsstrahlung_energy_grid.at(i) == d_min_electron_energy )
//     {
//       adjoint_bremsstrahlung_photon_energies =
//         d_forward_endl_data->getBremsstrahlungPhotonEnergyAtEnergy(
//             adjoint_bremsstrahlung_energy_grid[i+1] );

//       data_container.setAdjointBremsstrahlungPhotonEnergyAtIncomingEnergy(
//         d_min_electron_energy,
//         adjoint_bremsstrahlung_photon_energies );
//     }

//     this->evaluateAdjointBremsstrahlungPhotonDistribution(
//         adjoint_bremsstrahlung_energy_grid.at(i),
//         bin_index,
//         data_container.getAdjointBremsstrahlungCrossSectionThresholdEnergyIndex(),
//         adjoint_bremsstrahlung_cross_section,
//         adjoint_electron_energy_grid,
//         adjoint_bremsstrahlung_cs_evaluator,
//         adjoint_bremsstrahlung_photon_energies,
//         adjoint_bremsstrahlung_pdf_map[adjoint_bremsstrahlung_energy_grid.at(i)] );
//   }

//   // The PDF for the max incoming energy is always zero
//   std::vector<double> photon_energy( 2 );
//   photon_energy[0] = 1.0e-7;
//   photon_energy[1] = d_max_electron_energy;

//   data_container.setAdjointBremsstrahlungPhotonEnergyAtIncomingEnergy(
//     d_max_electron_energy,
//     photon_energy );

//   std::vector<double> photon_pdf( 2 );
//   photon_energy[0] = 0.0;
//   photon_energy[1] = 0.0;
//   adjoint_bremsstrahlung_pdf_map[d_max_electron_energy] =
//     photon_pdf;

//   data_container.setAdjointBremsstrahlungPhotonPDF(
//     adjoint_bremsstrahlung_pdf_map );

//   (*d_os_log) << "done." << std::endl;

// //---------------------------------------------------------------------------//
// // Set Electroionization Data
// //---------------------------------------------------------------------------//
//   (*d_os_log) << " Setting the electroionization data...";
//   d_os_log->flush();

//   std::set<unsigned>::iterator shell = data_container.getSubshells().begin();

//   // Loop through electroionization data for every subshell
//   for ( shell; shell != data_container.getSubshells().end(); shell++ )
//   {/*
//     data_container.setAdjointElectroionizationEnergyGrid(
//         *shell,
//         d_forward_endl_data->getElectroionizationRecoilEnergyGrid( *shell ) );

//     data_container.setAdjointElectroionizationRecoilEnergy(
//         *shell,
//         d_forward_endl_data->getElectroionizationRecoilEnergy( *shell ) );

//     data_container.setAdjointElectroionizationRecoilPDF(
//         *shell,
//         d_forward_endl_data->getElectroionizationRecoilPDF( *shell ) );*/
//   }
//   (*d_os_log) << "done." << std::endl;
}

// Set the moment preserving data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointMomentPreservingData(
    std::vector<double>& angular_energy_grid,
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container )
{
  // // Test that the angular energy grid is valid
  // testPrecondition( angular_energy_grid.size() > 0 );

  // // Create the analog elastic distribution (combined Cutoff and Screened Rutherford)
  // std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution>
  //       analog_distribution;

  // MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
  //   analog_distribution,
  //   data_container.getAdjointCutoffElasticAngles(),
  //   data_container.getAdjointCutoffElasticPDF(),
  //   angular_energy_grid,
  //   data_container.getAtomicNumber() );

  // // Construct the hash-based grid searcher for this atom
  // Teuchos::ArrayRCP<double> energy_grid;
  // energy_grid.assign( data_container.getAdjointElectronEnergyGrid().begin(),
  //                     data_container.getAdjointElectronEnergyGrid().end() );

  // Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
  //     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
  //               energy_grid,
  //               energy_grid[0],
  //               energy_grid[energy_grid.size()-1],
  //               energy_grid.size()/10 + 1 ) );

  // // Construct the cutoff reaction
  // Teuchos::ArrayRCP<double> cutoff_cross_section;
  // cutoff_cross_section.assign(
  //   data_container.getAdjointCutoffElasticCrossSection().begin(),
  //   data_container.getAdjointCutoffElasticCrossSection().end() );

  // // Construct the screened Rutherford reaction
  // Teuchos::ArrayRCP<double> rutherford_cross_section;
  // rutherford_cross_section.assign(
  //   data_container.getAdjointScreenedRutherfordElasticCrossSection().begin(),
  //   data_container.getAdjointScreenedRutherfordElasticCrossSection().end() );

  // Teuchos::RCP<MonteCarlo::AnalogElasticElectroatomicReaction<Utility::LinLin>> 
  //   analog_reaction(
  //   	new MonteCarlo::AnalogElasticElectroatomicReaction<Utility::LinLin>(
  //           energy_grid,
  //           cutoff_cross_section,
  //           rutherford_cross_section,
  //           data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex(),
  //           data_container.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
  //           grid_searcher,
  //           analog_distribution ) );

  // // Create the moment evaluator of the elastic scattering distribution
  // std::shared_ptr<DataGen::ElasticElectronMomentsEvaluator> moments_evaluator;
  // moments_evaluator.reset(
  //   new DataGen::ElasticElectronMomentsEvaluator(
  //       data_container.getAdjointCutoffElasticAngles(),
  //       analog_distribution,
  //       analog_reaction,
  //       data_container.getCutoffAngleCosine() ) );

  // // Moment preserving discrete angles and weights
  // std::vector<double> discrete_angles, weights;

  // // weights for a discrete angle cosine = 1
  // std::vector<double> cross_section_reduction(
  //   angular_energy_grid.size() );

  // // iterate through all angular energy bins
  // for ( unsigned i = 0; i < angular_energy_grid.size(); i++ )
  // {
  //   StandardAdjointElectronPhotonRelaxationDataGenerator::evaluateDisceteAnglesAndWeights(
  //       moments_evaluator,
  //       angular_energy_grid.at(i),
  //       data_container.getNumberOfAdjointMomentPreservingAngles(),
  //       discrete_angles,
  //       weights,
  //       cross_section_reduction.at(i) );

  //   data_container.setAdjointMomentPreservingElasticDiscreteAngles(
  //       angular_energy_grid.at(i),
  //       discrete_angles );
  //   data_container.setAdjointMomentPreservingElasticWeights(
  //       angular_energy_grid.at(i),
  //       weights );
  // }

  // // Generate a cross section reduction distribution
  // std::shared_ptr<const Utility::OneDDistribution> reduction_distribution(
  //   new Utility::TabularDistribution<Utility::LinLin>(
  //       angular_energy_grid,
  //       cross_section_reduction ) );

  // // Calculate the moment preserving cross section
  // std::vector<double> moment_preserving_cross_section;
  // StandardAdjointElectronPhotonRelaxationDataGenerator::evaluateAdjointMomentPreservingCrossSection(
  //       energy_grid,
  //       analog_reaction,
  //       analog_distribution,
  //       reduction_distribution,
  //       data_container.getCutoffAngleCosine(),
  //       data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex(),
  //       moment_preserving_cross_section );

  // data_container.setAdjointMomentPreservingCrossSection(
  //   moment_preserving_cross_section );

  // data_container.setAdjointMomentPreservingCrossSectionThresholdEnergyIndex(
  //   data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex() );
}

// Merge a secondary energy grid with the electron union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::mergeAdjointElectronUnionEnergyGrid(
     const std::vector<double>& energy_grid,
     std::list<double>& union_energy_grid ) const
{
  // // Assign the new grid to the union grid
  // union_energy_grid.insert( union_energy_grid.begin(),
  //                           energy_grid.begin(),
  //                           energy_grid.end() );

  // // Sort the union energy grid
  // union_energy_grid.sort();

  // // Remove all energies less than the min
  // while ( *union_energy_grid.begin() < d_min_electron_energy )
  // {
  //     union_energy_grid.pop_front();
  // }

  // // Make sure the union energy grid values are unique
  // union_energy_grid.unique();
}

// Create the cross section on the union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::createAdjointCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const std::shared_ptr<const Utility::OneDDistribution>& original_cross_section,
   std::vector<double>& cross_section,
   unsigned& threshold_index ) const
{
  // std::vector<double> raw_cross_section( union_energy_grid.size() );

  // std::list<double>::const_iterator energy_grid_pt = union_energy_grid.begin();

  // unsigned index = 0u;

  // while( energy_grid_pt != union_energy_grid.end() )
  // {
  //   raw_cross_section[index] =
  //     original_cross_section->evaluate( *energy_grid_pt );

  //   ++energy_grid_pt;
  //   ++index;
  // }

  // std::vector<double>::iterator start =
  //   std::find_if( raw_cross_section.begin(),
  //       	  raw_cross_section.end(),
  //       	  notEqualZero );

  // cross_section.assign( start, raw_cross_section.end() );

  // threshold_index = std::distance( raw_cross_section.begin(), start );
}

// Create the cross section on the union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::createAdjointCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const std::shared_ptr<DataGen::AdjointBremsstrahlungCrossSectionEvaluator>
        adjoint_bremsstrahlung_cs_evaluator,
   std::vector<double>& cross_section,
   unsigned& threshold_index ) const
{
  // std::vector<double> raw_cross_section( union_energy_grid.size() );

  // std::list<double>::const_iterator energy_grid_pt = union_energy_grid.begin();

  // unsigned index = 0u;

  // while( energy_grid_pt != union_energy_grid.end() )
  // {
  //   raw_cross_section[index] =
  //     adjoint_bremsstrahlung_cs_evaluator->evaluateAdjointCrossSection(
  //       *energy_grid_pt,
  //       d_adjoint_bremsstrahlung_evaluation_tolerance );

  //   ++energy_grid_pt;
  //   ++index;
  // }

  // std::vector<double>::iterator start =
  //   std::find_if( raw_cross_section.begin(),
  //       	  raw_cross_section.end(),
  //       	  notEqualZero );

  // cross_section.assign( start, raw_cross_section.end() );

  // threshold_index = std::distance( raw_cross_section.begin(), start );
}

// Create the cross section on the union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::createAdjointCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const std::list<double>& old_union_energy_grid,
   const std::vector<double>& old_cross_section,
   const std::shared_ptr<DataGen::AdjointBremsstrahlungCrossSectionEvaluator>
        adjoint_bremsstrahlung_cs_evaluator,
   std::vector<double>& cross_section,
   unsigned& threshold_index ) const
{
  // std::vector<double> raw_cross_section( union_energy_grid.size() );

  // std::list<double>::const_iterator energy_grid_pt = union_energy_grid.begin();
  // std::list<double>::const_iterator old_energy_grid_pt =
  //   old_union_energy_grid.begin();

  // unsigned index = 0u;
  // unsigned old_index = 0u;

  // while( energy_grid_pt != union_energy_grid.end() )
  // {
  //   if ( *energy_grid_pt == *old_energy_grid_pt )
  //   {
  //     raw_cross_section[index] = old_cross_section[old_index];
   
  //     ++old_energy_grid_pt;
  //     ++old_index;
  //   }
  //   else
  //   {
  //     raw_cross_section[index] =
  //       adjoint_bremsstrahlung_cs_evaluator->evaluateAdjointCrossSection(
  //         *energy_grid_pt,
  //         d_adjoint_bremsstrahlung_evaluation_tolerance );
  //   }

  //   ++energy_grid_pt;
  //   ++index;
  // }

  // std::vector<double>::iterator start =
  //   std::find_if( raw_cross_section.begin(),
  //       	  raw_cross_section.end(),
  //       	  notEqualZero );

  // cross_section.assign( start, raw_cross_section.end() );

  // threshold_index = std::distance( raw_cross_section.begin(), start );
}

// Calculate the elastic anglular distribution for the angle cosine
void StandardAdjointElectronPhotonRelaxationDataGenerator::calculateElasticAngleCosine(
    const std::vector<double>& raw_elastic_angle,
    const std::vector<double>& raw_elastic_pdf,
    std::vector<double>& elastic_angle,
    std::vector<double>& elastic_pdf ) const
{
  // int size = raw_elastic_angle.size();
  // int r_bin = size - 1;

  // elastic_angle.resize( size );
  // elastic_pdf.resize( size );

  // for ( int bin = 0; bin < size; bin++ )
  // {
  //   elastic_pdf[r_bin] = raw_elastic_pdf[bin];
  //   long double angle_cosine = 1.0L - raw_elastic_angle[bin];
  //   elastic_angle[r_bin] = angle_cosine;
  //   r_bin--;
  // }
}

// Generate elastic moment preserving discrete angle cosines and weights
void StandardAdjointElectronPhotonRelaxationDataGenerator::evaluateDisceteAnglesAndWeights(
    const std::shared_ptr<DataGen::ElasticElectronMomentsEvaluator>& moments_evaluator,
    const double& energy,
    const int& number_of_moment_preserving_angles,
    std::vector<double>& discrete_angles,
    std::vector<double>& weights,
    double& cross_section_reduction )
{
  // std::vector<Utility::long_float> legendre_moments;
  // double precision = 1e-13;
  // int n = ( number_of_moment_preserving_angles+1 )*2 -2;

  // // Get the elastic moments
  // moments_evaluator->evaluateElasticMoment( legendre_moments,
  //                                           energy,
  //                                           n,
  //                                           precision );

  // // Use radau quadrature to find the discrete angles and weights from the moments
  // std::shared_ptr<Utility::SloanRadauQuadrature> radau_quadrature(
  //     new Utility::SloanRadauQuadrature( legendre_moments ) );

  // radau_quadrature->getRadauNodesAndWeights( discrete_angles,
  //                                            weights,
  //                                            number_of_moment_preserving_angles+1 );

  // // Eliminate the forward discrete angle (mu = 1)
  // discrete_angles.pop_back();
  // weights.pop_back();

  // // Renormalize weights and set the cross_section_reduction to the sum of the weights 
  // cross_section_reduction = 0.0;
  // for( int i = 0; i < weights.size(); i++ )
  // {
  //   cross_section_reduction += weights.at(i);
  // }

  // for( int i = 0; i < weights.size(); i++ )
  // {
  //   weights.at(i) /= cross_section_reduction;
  // }
}

// Generate elastic moment preserving cross section
void StandardAdjointElectronPhotonRelaxationDataGenerator::evaluateAdjointMomentPreservingCrossSection(
    const Teuchos::ArrayRCP<double>& electron_energy_grid,
    const Teuchos::RCP<MonteCarlo::AnalogElasticElectroatomicReaction<Utility::LinLin> >&
        analog_reaction,
    const std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution>&
        analog_distribution,
    const std::shared_ptr<const Utility::OneDDistribution>& reduction_distribution,
    const double cutoff_angle_cosine,
    const unsigned threshold_energy_index,
    std::vector<double>& moment_preserving_cross_section )
{
  // moment_preserving_cross_section.resize( electron_energy_grid.size() );

  // unsigned begin = threshold_energy_index;

  // for( unsigned i = begin; i < electron_energy_grid.size(); i++ )
  // {
  //   double cutoff_cdf = analog_distribution->evaluateCDF(
  //       electron_energy_grid[i],
  //       cutoff_angle_cosine );

  //   double cross_section_reduction =
  //       reduction_distribution->evaluate( electron_energy_grid[i] );

  //   double rutherford_cross_section =
  //       analog_reaction->getScreenedRutherfordCrossSection(
  //           electron_energy_grid[i] );

  //   double cutoff_cross_section =
  //       analog_reaction->getCutoffCrossSection( electron_energy_grid[i] );

  //   moment_preserving_cross_section.at(i) = cross_section_reduction*
  //       (rutherford_cross_section + (1.0 - cutoff_cdf)*cutoff_cross_section);
  // }
}

// Create the adjoint bremsstrahlung cross section evaluator
void StandardAdjointElectronPhotonRelaxationDataGenerator::createAdjointBremsstrahlungCrossSectionEvaluator(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    std::shared_ptr<DataGen::AdjointBremsstrahlungCrossSectionEvaluator>&
        adjoint_bremsstrahlung_cs_evaluator ) const
{
  // // Extract the forward electron energy grid
  // Teuchos::ArrayRCP<double> forward_brem_cs_energy_grid;
  // forward_brem_cs_energy_grid.assign(
  //   d_forward_endl_data->getBremsstrahlungCrossSectionEnergyGrid().begin(),
  //   d_forward_endl_data->getBremsstrahlungCrossSectionEnergyGrid().end() );

  // // Create the hash-based grid searcher
  // Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
  //   new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
  //   forward_brem_cs_energy_grid,
  //   forward_brem_cs_energy_grid[0],
  //   forward_brem_cs_energy_grid[forward_brem_cs_energy_grid.size()-1],
  //   forward_brem_cs_energy_grid.size()/10 + 1 ) );
 
  // // Extract the forward bremsstrahlung cross section
  // Teuchos::ArrayRCP<double> forward_bremsstrahlung_cross_section;
  // forward_bremsstrahlung_cross_section.assign(
  //   d_forward_endl_data->getBremsstrahlungCrossSection().begin(),
  //   d_forward_endl_data->getBremsstrahlungCrossSection().end() );

  // // Get the energy grid for the forward bremsstrahlung energy loss distributions
  // std::vector<double> forward_brem_energy_grid =
  //   d_forward_endl_data->getBremsstrahlungPhotonEnergyGrid();

  // // Get energy index below/equal to d_min_electron_energy
  // unsigned start_index =
  //   Utility::Search::binaryLowerBoundIndex(
  //             forward_brem_energy_grid.begin(),
  //             forward_brem_energy_grid.end(),
  //             d_min_electron_energy );

  // // Get energy index above/equal to d_max_electron_energy
  // unsigned end_index =
  //   Utility::Search::binaryUpperBoundIndex(
  //             forward_brem_energy_grid.begin(),
  //             forward_brem_energy_grid.end(),
  //             d_max_electron_energy );

  // end_index -= start_index;

  // // The adjoint bremsstrahlung energy grid for the energy gain function
  // std::vector<double> adjoint_bremsstrahlung_energy_grid( end_index+1 );

  // // Create the forward bremsstrahlung energy loss function
  // MonteCarlo::BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution
  //   energy_loss_function( end_index+1 );

  // unsigned n = 0;
  // // Insert bin below d_min_electron_energy (if necessary)
  // if( forward_brem_energy_grid[start_index] != d_min_electron_energy )
  // {
  //   energy_loss_function[n].first = forward_brem_energy_grid[start_index];
  //   adjoint_bremsstrahlung_energy_grid[n] = d_min_electron_energy;

  //   // Get the energy of the bremsstrahlung photon at the incoming energy
  //   std::vector<double> photon_energy(
  //       d_forward_endl_data->getBremsstrahlungPhotonEnergyAtEnergy(
  //         forward_brem_energy_grid[start_index] ) );

  //   // Get the bremsstrahlung photon pdf at the incoming energy
  //   std::vector<double> pdf(
  //       d_forward_endl_data->getBremsstrahlungPhotonPDFAtEnergy(
  //         forward_brem_energy_grid[start_index] ) );

  //   energy_loss_function[n].second.reset(
  //         new const Utility::TabularDistribution<Utility::LinLin>( photon_energy,
  //                                                              pdf ) );

  //   ++n;
  //   ++start_index;
  // }

  // std::map<double,std::vector<double> > photon_energy(
  //   d_forward_endl_data->getBremsstrahlungPhotonEnergy() );

  // std::map<double,std::vector<double> > pdf(
  //       d_forward_endl_data->getBremsstrahlungPhotonPDF() );

  // for( n; n < end_index; ++n )
  // {
  //   energy_loss_function[n].first = forward_brem_energy_grid[start_index];
  //   adjoint_bremsstrahlung_energy_grid[n] = forward_brem_energy_grid[start_index];

  //   energy_loss_function[n].second.reset(
  //           new const Utility::TabularDistribution<Utility::LinLin>(
  //       photon_energy[forward_brem_energy_grid[start_index] ],
  //       pdf[forward_brem_energy_grid[start_index] ] ) );

  //   ++start_index;
  // }

  // // Insert bin above d_max_electron_energy
  // {
  //   energy_loss_function[n].first = forward_brem_energy_grid[start_index];
  //   adjoint_bremsstrahlung_energy_grid[n] = d_max_electron_energy;

  //   energy_loss_function[n].second.reset(
  //           new const Utility::TabularDistribution<Utility::LinLin>(
  //       photon_energy[forward_brem_energy_grid[start_index] ],
  //       pdf[forward_brem_energy_grid[start_index] ] ) );
  // }

  // std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
  //   bremsstrahlung_distribution(
  //       new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
  //           energy_loss_function ) );

  // std::shared_ptr<MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> >
  //   bremsstrahlung_reaction(
  //       new MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin>(
  //           forward_brem_cs_energy_grid,
  //           forward_bremsstrahlung_cross_section,
  //           0,
  //           grid_searcher,
  //           bremsstrahlung_distribution ) );

  // adjoint_bremsstrahlung_cs_evaluator.reset(
  //   new DataGen::AdjointBremsstrahlungCrossSectionEvaluator(
  //       bremsstrahlung_reaction,
  //       adjoint_bremsstrahlung_energy_grid ) );

  //   // Add nudge value
  //   adjoint_bremsstrahlung_energy_grid.back() =
  //     d_max_electron_energy - s_threshold_energy_nudge_factor;
  //   adjoint_bremsstrahlung_energy_grid.push_back( d_max_electron_energy );

  // // Set the adjoint bremsstrahlung energy grid
  // data_container.setAdjointBremsstrahlungEnergyGrid(
  //   adjoint_bremsstrahlung_energy_grid );
}

// Generate adjoint bremsstrahlung photon energy distribution
void StandardAdjointElectronPhotonRelaxationDataGenerator::evaluateAdjointBremsstrahlungPhotonDistribution(
    const double incoming_adjoint_energy,
    const unsigned bin_index,
    const unsigned threshold_energy_index,
    const Teuchos::ArrayRCP<const double>& adjoint_cross_section,
    const Teuchos::ArrayRCP<const double>& adjoint_electron_energy_grid,
    const std::shared_ptr<DataGen::AdjointBremsstrahlungCrossSectionEvaluator>
        adjoint_bremsstrahlung_cs_evaluator,
    const std::vector<double>& adjoint_bremsstrahlung_photon_energy,
    std::vector<double>& adjoint_bremsstrahlung_pdf ) const
{
  // double adjoint_bremsstrahlung_cs =
  //   MonteCarlo::StandardElectroatomicReaction<Utility::LinLin, false>::getCrossSection(
  //       incoming_adjoint_energy,
  //       bin_index,
  //       adjoint_cross_section,
  //       adjoint_electron_energy_grid,
  //       threshold_energy_index );

  // adjoint_bremsstrahlung_pdf.resize(
  //   adjoint_bremsstrahlung_photon_energy.size() );

  // // Calculate the adjoint PDF values at the given incoming adjoint energy
  // for ( int j = 0; j < adjoint_bremsstrahlung_photon_energy.size(); ++j )
  // {
  //   double outgoing_adjoint_energy =
  //     incoming_adjoint_energy + adjoint_bremsstrahlung_photon_energy[j];

  //   if ( outgoing_adjoint_energy <= d_max_electron_energy )
  //   {
  //     adjoint_bremsstrahlung_pdf[j] =
  //         adjoint_bremsstrahlung_cs_evaluator->evaluateAdjointPDF(
  //           adjoint_bremsstrahlung_cs,
  //           incoming_adjoint_energy,
  //           outgoing_adjoint_energy,
  //           d_adjoint_bremsstrahlung_evaluation_tolerance );
  //   }
  //   else
  //     adjoint_bremsstrahlung_pdf[j] = 0.0;
  // }
}

// Create the adjoint electroionization subshell cross section evaluator
void StandardAdjointElectronPhotonRelaxationDataGenerator::createAdjointElectroionizationSubshellCrossSectionEvaluator(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    std::shared_ptr<DataGen::AdjointElectroionizationSubshellCrossSectionEvaluator>&
        adjoint_electroionization_cs_evaluator ) const
{

}

// Initialize the electron union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::initializeAdjointElectronUnionEnergyGrid(
     const Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
     std::list<double>& union_energy_grid ) const
{
  // // Add the min electron energy to the union energy grid
//   union_energy_grid.push_back( d_min_electron_energy );
// /*
//   const std::set<unsigned>& subshells = data_container.getSubshells();

//   std::set<unsigned>::const_iterator subshell = subshells.begin();

//   // Add the subshell binding energies
//   while( subshell != subshells.end() )
//   {
//     double binding_energy =
//       data_container.getSubshellBindingEnergy( *subshell );

//     if( binding_energy > d_min_electron_energy )
//     {
//       union_energy_grid.push_back( binding_energy );
//       union_energy_grid.push_back( binding_energy*
// 				   s_threshold_energy_nudge_factor );
//     }

//     ++subshell;
//   }
// */
//   // Add the max electron energy
//   union_energy_grid.push_back( d_max_electron_energy );

//   // Sort the union energy grid
//   union_energy_grid.sort();
}

// Initialize table generation data
// Note: We will initialize the table generation data in this method instead
//       of the initializer list of each constructor to avoid having to change
//       the default values in all initializer lists.
void StandardAdjointElectronPhotonRelaxationDataGenerator::initializeTableGenerationData()
{
  // Photon table generation default data
  d_adjoint_incoherent_max_energy_nudge_value = 0.2;
  d_adjoint_incoherent_energy_to_max_energy_nudge_value = 1e-6;
  d_adjoint_incoherent_evaluation_tol = 0.001;
  d_adjoint_incoherent_grid_convergence_tol = 0.001;
  d_adjoint_incoherent_absolute_diff_tol = 1e-20;
  d_adjoint_incoherent_distance_tol = 1e-14;

  // Electron table generation default data
  d_cutoff_angle_cosine = 1.0;
  d_number_of_moment_preserving_angles = 0;
  d_adjoint_bremsstrahlung_evaluation_tolerance = 0.001;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
