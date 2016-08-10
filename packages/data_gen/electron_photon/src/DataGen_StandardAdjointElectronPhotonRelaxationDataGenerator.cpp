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
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_VoidStandardElectroatomicReaction.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_GridGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SloanRadauQuadrature.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"

namespace DataGen{

// Initialize the static member data

const double StandardAdjointElectronPhotonRelaxationDataGenerator::s_threshold_energy_nudge_factor = 1.0001;
const double StandardAdjointElectronPhotonRelaxationDataGenerator::s_min_tabulated_energy_loss = 1.0e-7;

// Advanced Constructor
StandardAdjointElectronPhotonRelaxationDataGenerator::StandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data,
      const double min_photon_energy,
      const double max_photon_energy,
      const double min_electron_energy,
      const double max_electron_energy,
      const double cutoff_angle_cosine,
      const unsigned number_of_moment_preserving_angles,
      const double adjoint_bremsstrahlung_evaluation_tolerance,
      const double adjoint_electroionization_evaluation_tolerance,
      const double grid_convergence_tol,
      const double grid_absolute_diff_tol,
      const double grid_distance_tol )
  : AdjointElectronPhotonRelaxationDataGenerator( forward_epr_data->getAtomicNumber() ),
    d_forward_epr_data( forward_epr_data ),
    d_min_photon_energy( min_photon_energy ),
    d_max_photon_energy( max_photon_energy ),
    d_min_electron_energy( min_electron_energy ),
    d_max_electron_energy( max_electron_energy ),
    d_cutoff_angle_cosine( cutoff_angle_cosine ),
    d_number_of_moment_preserving_angles( number_of_moment_preserving_angles ),
    d_adjoint_bremsstrahlung_evaluation_tolerance( adjoint_bremsstrahlung_evaluation_tolerance ),
    d_adjoint_electroionization_evaluation_tolerance( adjoint_electroionization_evaluation_tolerance ),
    d_grid_convergence_tol( grid_convergence_tol ),
    d_grid_absolute_diff_tol( grid_absolute_diff_tol ),
    d_grid_distance_tol( grid_distance_tol )
{
  // Make sure the forward epr data is valid
  testPrecondition( forward_epr_data.get() );
  // Make sure the photon energy limits are valid
  testPrecondition( min_photon_energy > 0.0 );
  testPrecondition( min_photon_energy < max_photon_energy );
  // Make sure the electron energy limits are valid
  testPrecondition( min_electron_energy > 0.0 );
  testPrecondition( min_electron_energy < max_electron_energy );
  // Make sure the cutoff angle is valid
  testPrecondition( cutoff_angle_cosine <= 1.0 );
  testPrecondition( cutoff_angle_cosine > -1.0 );
  // Make sure the number of moment preserving angles is valid
  testPrecondition( number_of_moment_preserving_angles >= 0 );

  // Check if the min photon energy is below the forward table min energy
  if( d_min_photon_energy < forward_epr_data->getMinPhotonEnergy() )
  {
    d_min_photon_energy = forward_epr_data->getMinPhotonEnergy();

    std::cerr << "Warning: the min photon energy requested is below the "
              << "requested forward table min photon energy! The table's min "
              << "photon energy will be used instead."
              << std::endl;
  }

  // Check if the max photon energy is above the forward table max energy
  if( d_max_photon_energy > forward_epr_data->getMaxPhotonEnergy() )
  {
    d_max_photon_energy = forward_epr_data->getMaxPhotonEnergy();

    std::cerr << "Warning: the max photon energy requested is above the "
              << "requested forward table max photon energy! The table's max "
              << "photon energy will be used instead."
              << std::endl;
  }

  // Check if the min electron energy is below the forward table min energy
  if( d_min_electron_energy < forward_epr_data->getMinElectronEnergy() )
  {
    d_min_electron_energy = forward_epr_data->getMinElectronEnergy();

    std::cerr << "Warning: the min electron energy requested is above the "
              << "requested forward table min electron energy! The table's "
              << "min electron energy will be used instead."
              << std::endl;
  }

  // Check if the max electron energy is above the forward table max energy
  if( d_max_electron_energy > forward_epr_data->getMaxElectronEnergy() )
  {
    d_max_electron_energy = forward_epr_data->getMaxElectronEnergy();

    std::cerr << "Warning: the max electron energy requested is above the "
              << "requested forward table max electron energy! The table's "
              << "max electron energy will be used instead."
              << std::endl;
  }
}

// Basic Constructor
StandardAdjointElectronPhotonRelaxationDataGenerator::StandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data,
      const double cutoff_angle_cosine,
      const unsigned number_of_moment_preserving_angles,
      const double adjoint_bremsstrahlung_evaluation_tolerance,
      const double adjoint_electroionization_evaluation_tolerance,
      const double grid_convergence_tol,
      const double grid_absolute_diff_tol,
      const double grid_distance_tol )
  : StandardAdjointElectronPhotonRelaxationDataGenerator(
      forward_epr_data,
      forward_epr_data->getMinPhotonEnergy(),
      forward_epr_data->getMaxPhotonEnergy(),
      forward_epr_data->getMinElectronEnergy(),
      forward_epr_data->getMaxElectronEnergy(),
      cutoff_angle_cosine,
      number_of_moment_preserving_angles,
      adjoint_bremsstrahlung_evaluation_tolerance,
      adjoint_electroionization_evaluation_tolerance,
      grid_convergence_tol,
      grid_absolute_diff_tol,
      grid_distance_tol )
{ /* ... */ }

// Populate the adjoint electron-photon-relaxation data container
void StandardAdjointElectronPhotonRelaxationDataGenerator::populateEPRDataContainer(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // Set the table data
  this->setAtomicNumber( data_container );
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
  std::cout << std::endl << "Setting the adjoint relaxation data...";
  std::cout.flush();
  this->setAdjointRelaxationData( data_container );
  std::cout << "done." << std::endl;

  // Set the photon data
  std::cout << "Setting the adjoint photon data... " << std::endl;
  std::cout.flush();
  this->setAdjointPhotonData( data_container );
  std::cout << "done." << std::endl;

  // Set the electron data
  std::cout << "Setting the adjoint electron data: " << std::endl;
  this->setAdjointElectronData( data_container );
  std::cout << "done." << std::endl;
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

  std::cout << std::endl << "Setting the adjoint moment preserving electron data...";
  std::cout.flush();
  StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointMomentPreservingData( 
    adjoint_angular_energy_grid, 
    data_container );
  std::cout << "done." << std::endl;
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

// Set the photon data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointPhotonData(
			   Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const
{
  std::cout << " Adjoint photon data generation has not been implmented yet!" << std::endl;
}


void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointElectronData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
//---------------------------------------------------------------------------//
// Set Electron Cross Section Data Data
//---------------------------------------------------------------------------//
/*! \details The cross section data is needed for caluculating the 
 *  moment preserving data and must be set first.
 */
  std::cout << " Setting the adjoint electron cross section data:" << std::endl;
  std::cout.flush();

  // Extract the common electron energy grid
  Teuchos::ArrayRCP<double> forward_electron_energy_grid;
  forward_electron_energy_grid.assign(
    d_forward_epr_data->getElectronEnergyGrid().begin(),
    d_forward_epr_data->getElectronEnergyGrid().end() );

  Teuchos::RCP<Utility::HashBasedGridSearcher> forward_grid_searcher(
      new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
                forward_electron_energy_grid,
                forward_electron_energy_grid[0],
                forward_electron_energy_grid[forward_electron_energy_grid.size()-1],
                forward_electron_energy_grid.size()/10 + 1 ) );

  //---------------------------------------------------------------------------//
  // Extract The Elastic Cross Section Data
  //---------------------------------------------------------------------------//
  // Extract the cutoff elastic cross section data
  Teuchos::ArrayRCP<double> forward_cutoff_cross_section;
  forward_cutoff_cross_section.assign(
    d_forward_epr_data->getCutoffElasticCrossSection().begin(),
    d_forward_epr_data->getCutoffElasticCrossSection().end() );

  std::shared_ptr<const MonteCarlo::ElectroatomicReaction> cutoff_elastic_reaction(
    new MonteCarlo::VoidStandardElectroatomicReaction<Utility::LinLin>(
        forward_electron_energy_grid,
        forward_cutoff_cross_section,
        d_forward_epr_data->getCutoffElasticCrossSectionThresholdEnergyIndex(),
        forward_grid_searcher ) );

  // Extract the total elastic cross section data
  Teuchos::ArrayRCP<double> forward_total_cross_section;
  forward_total_cross_section.assign(
    d_forward_epr_data->getTotalElasticCrossSection().begin(),
    d_forward_epr_data->getTotalElasticCrossSection().end() );

  std::shared_ptr<const MonteCarlo::ElectroatomicReaction> total_elastic_reaction(
    new MonteCarlo::VoidStandardElectroatomicReaction<Utility::LinLin>(
        forward_electron_energy_grid,
        forward_total_cross_section,
        d_forward_epr_data->getTotalElasticCrossSectionThresholdEnergyIndex(),
        forward_grid_searcher ) );

  //---------------------------------------------------------------------------//
  // Extract The Adjoint Atomic Excitation Cross Section Data
  //---------------------------------------------------------------------------//

  // Extract the atomic excitation cross section data
  std::shared_ptr<MonteCarlo::ElectroatomicReaction> atomic_excitation_reaction;
  MonteCarlo::ElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
    *d_forward_epr_data,
    forward_electron_energy_grid,
    forward_grid_searcher,
    atomic_excitation_reaction );


/*
  std::vector<double>::const_iterator energy_gain_start =
    d_forward_epr_data->getAtomicExcitationEnergyLoss().begin();

  std::vector<double>::const_iterator energy_grid_start =
    d_forward_epr_data->getElectronEnergyGrid().begin();

  // Make sure the first energy grid point is not zero
  if ( d_forward_epr_data->getAtomicExcitationEnergyLoss().front() ==
       d_forward_epr_data->getAtomicExcitationEnergyGrid().front() )
  {
    ++energy_gain_start;
    ++energy_grid_start;
    ++cross_section_start;
  }

  // Find the index of the energy grid for the max electron energy
  unsigned end_excitation_index =
    Utility::Search::binaryLowerBoundIndex(
              energy_grid_start,
              d_forward_epr_data->getAtomicExcitationEnergyGrid().end(),
              d_max_electron_energy );

  std::vector<double> adjoint_excitation_energy_gain( energy_gain_start,
    d_forward_epr_data->getAtomicExcitationEnergyLoss().end() );

  std::vector<double> adjoint_excitation_energy_grid( energy_grid_start,
    d_forward_epr_data->getAtomicExcitationEnergyGrid().end() );

  // Calcualte the adjoint icoming energy grid from the forward incoming energy grid and energy loss
  for ( int i = 0; i < adjoint_excitation_energy_grid.size(); i++ )
  {
    adjoint_excitation_energy_grid[i] -= adjoint_excitation_energy_gain[i];
  }

  // Set atomic excitation energy gain (adjoint energy gain = forward energy loss)
  data_container.setAdjointAtomicExcitationEnergyGrid(
    adjoint_excitation_energy_grid );
  data_container.setAdjointAtomicExcitationEnergyGain(
    adjoint_excitation_energy_gain );

  std::shared_ptr<const Utility::OneDDistribution> atomic_excitation_cross_section(
    new Utility::TabularDistribution<Utility::LinLin>(
      adjoint_excitation_energy_grid,
      adjoint_excitation_cross_section ) );
*/
  //---------------------------------------------------------------------------//
  // Create The Adjoint Bremsstrahlung Cross Section Evaluator
  //---------------------------------------------------------------------------//
  // The adjoint bremsstrahlung cross section evaluator
  std::shared_ptr<DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction> >
    adjoint_bremsstrahlung_cs_evaluator;

  this->createAdjointBremsstrahlungCrossSectionEvaluator(
          forward_electron_energy_grid,
          forward_grid_searcher,
          adjoint_bremsstrahlung_cs_evaluator );

//  //---------------------------------------------------------------------------//
//  // Create The Adjoint Electroionization Subshell Cross Section Evaluator
//  //---------------------------------------------------------------------------//
//  // The adjoint electroionization subshell cross section evaluator
//  std::map<unsigned,std::shared_ptr<DataGen::AdjointElectronCrossSectionEvaluator<ElectroionizationReaction> > >
//    adjoint_electroionization_cs_evaluators;

//  this->createAdjointElectroionizationSubshellCrossSectionEvaluator(
//          data_container,
//          adjoint_electroionization_cs_evaluators );

//  //---------------------------------------------------------------------------//
//  // Create union energy grid and calculate cross sections
//  //---------------------------------------------------------------------------//

//  // Create the union energy grid
//  std::cout << "   Creating union energy grid";
//  std::cout.flush();
//  std::list<double> union_energy_grid;

//  this->initializeAdjointElectronUnionEnergyGrid(
//          data_container,
//          union_energy_grid );

//  Utility::GridGenerator<Utility::LinLin>
//  union_energy_grid_generator( d_grid_convergence_tol,
//                               d_grid_absolute_diff_tol,
//                               d_grid_distance_tol );

//  // Calculate the union energy grid
//  boost::function<double (double pz)> grid_function =
//    boost::bind( &Utility::OneDDistribution::evaluate,
//                 boost::cref( *cutoff_elastic_cross_section ),
//                 _1 );

//  union_energy_grid_generator.generateInPlace( union_energy_grid,
//                                               grid_function );

//  std::cout << ".";
//  std::cout.flush();

//  grid_function = 
//    boost::bind( &Utility::OneDDistribution::evaluate,
//                 boost::cref( *total_elastic_cross_section ),
//                 _1 );

//  union_energy_grid_generator.generateInPlace( union_energy_grid,
//                                               grid_function );

//  std::cout << ".";
//  std::cout.flush();

//  grid_function = boost::bind( &Utility::OneDDistribution::evaluate,
//  		                   boost::cref( *atomic_excitation_cross_section ),
//  		                   _1 );

//  std::list<double>::iterator it =
//    Utility::Search::binaryLowerBound(
//        union_energy_grid.begin(),
//        union_energy_grid.end(),
//        adjoint_excitation_energy_grid[end_excitation_index] );

//  std::list<double> temp_union_energy_grid;
//  temp_union_energy_grid.splice(
//    temp_union_energy_grid.begin(), union_energy_grid, union_energy_grid.begin(), it );

//  union_energy_grid_generator.generateInPlace( temp_union_energy_grid,
//                                               grid_function );

//  union_energy_grid.merge( temp_union_energy_grid );

//  std::cout << ".";
//  std::cout.flush();


//  grid_function = 
//    boost::bind(
//        &DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction>::evaluateAdjointCrossSection,
//        boost::cref( *adjoint_bremsstrahlung_cs_evaluator ),
//        _1,
//        d_adjoint_bremsstrahlung_evaluation_tolerance );

//  std::vector<double> old_adjoint_bremsstrahlung_cs;

//  union_energy_grid_generator.generateAndEvaluateInPlace(
//    union_energy_grid,
//    old_adjoint_bremsstrahlung_cs,
//    grid_function );

//  std::list<double> old_adjoint_bremsstrahlung_union_energy_grid(
//    union_energy_grid );

//  std::cout << ".";
//  std::cout.flush();


//  std::map<unsigned,std::list<double> >
//    old_adjoint_electroionization_union_energy_grid;

//  std::map<unsigned,std::vector<double> > old_adjoint_electroionization_cs;

//  std::set<unsigned>::iterator shell = data_container.getSubshells().begin();

//  // Loop through electroionization evaluator for every subshell
//  for ( shell; shell != data_container.getSubshells().end(); shell++ )
//  {
//    grid_function =
//      boost::bind(
//    	   &DataGen::AdjointElectronCrossSectionEvaluator<ElectroionizationReaction>::evaluateAdjointCrossSection,
//    	   boost::cref( *adjoint_electroionization_cs_evaluators.find( *shell )->second ),
//    	   _1,
//         d_adjoint_electroionization_evaluation_tolerance );

//    double binding_energy = data_container.getSubshellBindingEnergy( *shell );

//    it =  Utility::Search::binaryLowerBound(
//        union_energy_grid.begin(),
//        union_energy_grid.end(),
//        d_max_electron_energy - binding_energy - 1.0e-7 );

//std::cout << std::endl << "*shell = " << *shell << std::endl;
//std::cout << "union_energy_grid.size() = " << union_energy_grid.size() << std::endl;
//  temp_union_energy_grid.splice(
//    temp_union_energy_grid.begin(), union_energy_grid, union_energy_grid.begin(), it );

//std::cout << "temp_union_energy_grid.size() = " << temp_union_energy_grid.size() << std::endl;
//std::cout << "spliced union_energy_grid.size() = " << union_energy_grid.size() << std::endl;

//    union_energy_grid_generator.generateAndEvaluateInPlace(
//      temp_union_energy_grid,
//      old_adjoint_electroionization_cs[*shell],
//      grid_function );

//    old_adjoint_electroionization_union_energy_grid[*shell] =
//      temp_union_energy_grid;

//std::cout << "new temp_union_energy_grid.size() = " << temp_union_energy_grid.size() << std::endl;

//    // If needed add the max electron energy
//    if ( old_adjoint_electroionization_union_energy_grid[*shell].back() < d_max_electron_energy )
//    {
//      old_adjoint_electroionization_union_energy_grid[*shell].push_back(
//        d_max_electron_energy );
//      old_adjoint_electroionization_cs[*shell].push_back( 0.0 );
//    }

//    union_energy_grid.merge( temp_union_energy_grid );

//std::cout << "new union_energy_grid.size() = " << union_energy_grid.size() << std::endl;

//    std::cout << ".";
//    std::cout.flush();
//  }

//  std::cout << "done." << std::endl;

//  // Set the union energy grid
//  std::vector<double> energy_grid(
//        union_energy_grid.begin(),
//        union_energy_grid.end() );

//std::cout << "union_energy_grid.size() = " << union_energy_grid.size() << std::endl;
//std::cout << "energy_grid.size() = " << energy_grid.size() << std::endl;


//  data_container.setAdjointElectronEnergyGrid( energy_grid );

//  // Create and set the cross sections
//  std::vector<double> cross_section;
//  unsigned threshold;

//  // Set the adjoint elastic cross section data
//  std::cout << "   Setting the adjoint total elastic cross section...";
//  std::cout.flush();
//  std::vector<double> total_cross_section;
//  this->createAdjointCrossSectionOnUnionEnergyGrid(
//      union_energy_grid,
//      total_elastic_cross_section,
//      total_cross_section,
//      threshold );
//  data_container.setAdjointTotalElasticCrossSection( total_cross_section );
//  data_container.setAdjointTotalElasticCrossSectionThresholdEnergyIndex( threshold );
//  std::cout << "done." << std::endl;

//  std::cout << "   Setting the adjoint cutoff elastic cross section...";
//  std::cout.flush();
//  std::vector<double> cutoff_cross_section;
//  this->createAdjointCrossSectionOnUnionEnergyGrid(
//      union_energy_grid,
//      cutoff_elastic_cross_section,
//      cutoff_cross_section,
//      threshold );
//  data_container.setAdjointCutoffElasticCrossSection( cutoff_cross_section );
//  data_container.setAdjointCutoffElasticCrossSectionThresholdEnergyIndex( threshold );
//  std::cout << "done." << std::endl;


//  std::cout << "   Setting the screened Rutherford elastic cross section...";
//  std::cout.flush();
//  {
//  std::vector<double> raw_cross_section( total_cross_section.size() );
//  for ( int i = 0; i < total_cross_section.size(); ++i )
//  {
//      raw_cross_section.at(i) = total_cross_section.at(i) - cutoff_cross_section.at(i);

//      double relative_difference = raw_cross_section.at(i)/total_cross_section.at(i);

//      // Check for roundoff error and reduce to zero if needed
//      if ( relative_difference < 1.0e-6 )
//      {
//          raw_cross_section[i] = 0.0;

//          // Update threshold index
//          threshold = i+1;
//      }
//  }

//  std::vector<double>::iterator start = raw_cross_section.begin();
//  std::advance( start, threshold );

//  cross_section.assign( start, raw_cross_section.end() );

//  data_container.setAdjointScreenedRutherfordElasticCrossSection( cross_section );
//  data_container.setAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(
//  threshold );
//  }
//  std::cout << "done." << std::endl;

//  // Set the adjoint atomic excitation cross section data
//  std::cout << "   Setting the adjoint atomic excitation cross section...";
//  std::cout.flush();
//  std::vector<double> excitation_cross_section;
//  this->createAdjointCrossSectionOnUnionEnergyGrid(
//      union_energy_grid,
//      atomic_excitation_cross_section,
//      excitation_cross_section,
//      threshold );

//  data_container.setAdjointAtomicExcitationCrossSection( excitation_cross_section );
//  data_container.setAdjointAtomicExcitationCrossSectionThresholdEnergyIndex( threshold );
//  std::cout << "done." << std::endl;

//  // Set the adjoint bremsstrahlung cross section data
//  std::cout << "   Setting the adjoint bremsstrahlung cross section...";
//  std::cout.flush();
//  this->createAdjointCrossSectionOnUnionEnergyGrid(
//      union_energy_grid,
//      old_adjoint_bremsstrahlung_union_energy_grid,
//      old_adjoint_bremsstrahlung_cs,  
//      adjoint_bremsstrahlung_cs_evaluator,
//      d_adjoint_bremsstrahlung_evaluation_tolerance,
//      cross_section,
//      threshold );

//  data_container.setAdjointBremsstrahlungCrossSection( cross_section );
//  data_container.setAdjointBremsstrahlungCrossSectionThresholdEnergyIndex( threshold );
//  std::cout << "done." << std::endl;

//  // Set the adjoint electroionization subshell cross section data
//  std::cout << "   Setting the adjoint electroionization subshell cross section...";
//  std::cout.flush();

//  // Loop through the electroionization subshells
//  shell = data_container.getSubshells().begin();
//  for ( shell; shell != data_container.getSubshells().end(); shell++ )
//  {
//    this->createAdjointCrossSectionOnUnionEnergyGrid(
//        union_energy_grid,
//        old_adjoint_electroionization_union_energy_grid[*shell],
//        old_adjoint_electroionization_cs[*shell],  
//        adjoint_electroionization_cs_evaluators[*shell],
//        d_adjoint_electroionization_evaluation_tolerance,
//        cross_section,
//        threshold );

//    data_container.setAdjointElectroionizationCrossSection(
//      *shell,
//      cross_section );

//    data_container.setAdjointElectroionizationCrossSectionThresholdEnergyIndex(
//      *shell,
//      threshold );
//  }
//  std::cout << "done." << std::endl;

////---------------------------------------------------------------------------//
//// Set Elastic Data
////---------------------------------------------------------------------------//
//  std::cout << " Setting the adjoint elastic cutoff data...";
//  std::cout.flush();

//  // Set elastic angular distribution
//  std::map<double,std::vector<double> > elastic_pdf, elastic_angle;

//  // Get energy bin below/equal to d_min_electron_energy
//  std::vector<double>::const_iterator start =
//    Utility::Search::binaryLowerBound(
//        d_forward_epr_data->getCutoffElasticAngularEnergyGrid().begin(),
//        d_forward_epr_data->getCutoffElasticAngularEnergyGrid().end(),
//        d_min_electron_energy );

//  // Get energy bin above/equal to d_max_electron_energy
//  std::vector<double>::const_iterator end =
//    Utility::Search::binaryUpperBound(
//        start,
//        d_forward_epr_data->getCutoffElasticAngularEnergyGrid().end(),
//        d_max_electron_energy );
//  ++end;

//  std::vector<double> angular_energy_grid( start, end );

//  /* ENDL gives the angular distribution in terms of the change in angle cosine
//   * (delta_angle_cosine = 1 - angle_cosine). For the native format it needs to
//   * be in terms of angle_cosine. This for loop flips the distribution and
//   * changes the variables to angle_cosine.
//   */
//  for ( start; start != end; ++start )
//  {
//    calculateElasticAngleCosine(
//        d_forward_epr_data->getCutoffElasticAnglesAtEnergy( *start ),
//        d_forward_epr_data->getCutoffElasticPDFAtEnergy( *start ),
//        elastic_angle[*start],
//        elastic_pdf[*start] );
//  }

//  // Evlauate the scattering distribution for the min energy (if necessary) 
//  if( angular_energy_grid.front() != d_min_electron_energy )
//  {
//    // Create the distribution above and below the min energy for interpolation
//    Utility::TabularDistribution<Utility::LinLin> lower_distribution(
//        elastic_angle[angular_energy_grid[0] ],
//        elastic_pdf[angular_energy_grid[0] ] );

//    Utility::TabularDistribution<Utility::LinLin> upper_distribution(
//        elastic_angle[angular_energy_grid[1] ],
//        elastic_pdf[angular_energy_grid[1] ] );

//    // Get the angular scattering grid for the min energy
//    std::vector<double> min_angles =
//      MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
//        elastic_angle,
//        d_min_electron_energy,
//        d_cutoff_angle_cosine );

//    // Get the pdf values for the min energy
//    std::vector<double> min_pdf( min_angles.size() );
//    for ( int i = 0; i < min_angles.size(); ++i )
//    {
//      min_pdf.at(i) = Utility::LinLog::interpolate(
//            angular_energy_grid[0],
//            angular_energy_grid[1],
//            d_min_electron_energy,
//            lower_distribution.evaluatePDF( min_angles.at(i) ),
//            upper_distribution.evaluatePDF( min_angles.at(i) ) );
//    }

//    // Set the distribution at the min energy
//    elastic_angle.emplace_hint(
//        elastic_angle.begin(),
//        d_min_electron_energy,
//        min_angles);

//    elastic_pdf.emplace_hint(
//        elastic_pdf.begin(),
//        d_min_electron_energy,
//        min_pdf);

//    // Erase the old front distribution
//    elastic_angle.erase( angular_energy_grid.front() );
//    elastic_pdf.erase( angular_energy_grid.front() );

//    angular_energy_grid.front() = d_min_electron_energy;
//  }

//  // Evlauate the scattering distribution for the max energy (if necessary) 
//  if( angular_energy_grid.back() != d_max_electron_energy )
//  {
//    // Create the distribution above and below the max energy for interpolation
//    Utility::TabularDistribution<Utility::LinLin> lower_distribution(
//        elastic_angle[angular_energy_grid[angular_energy_grid.size()-2] ],
//        elastic_pdf[angular_energy_grid[angular_energy_grid.size()-2] ] );

//    Utility::TabularDistribution<Utility::LinLin> upper_distribution(
//        elastic_angle[angular_energy_grid.back() ],
//        elastic_pdf[angular_energy_grid.back() ] );

//    // Get the angular scattering grid for the max energy
//    std::vector<double> max_angles =
//      MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
//        d_forward_epr_data->getCutoffElasticAngles(),
//        d_max_electron_energy,
//        d_cutoff_angle_cosine );

//    // Get the pdf values for the max energy
//    std::vector<double> max_pdf( max_angles.size() );
//    for ( int i = 0; i < max_angles.size(); ++i )
//    {
//      max_pdf.at(i) = Utility::LinLog::interpolate(
//            angular_energy_grid.at(angular_energy_grid.size()-2),
//            angular_energy_grid.back(),
//            d_max_electron_energy,
//            lower_distribution.evaluatePDF( max_angles.at(i) ),
//            upper_distribution.evaluatePDF( max_angles.at(i) ) );
//    }

//    // Set the distribution at the max energy
//    elastic_angle.emplace_hint(
//        elastic_angle.end(),
//        d_max_electron_energy,
//        max_angles);

//    elastic_pdf.emplace_hint(
//        elastic_pdf.end(),
//        d_max_electron_energy,
//        max_pdf);

//    // Erase the back distribution
//    elastic_angle.erase( angular_energy_grid.front() );
//    elastic_pdf.erase( angular_energy_grid.front() );

//    angular_energy_grid.back() = d_max_electron_energy;
//  }

//  data_container.setAdjointElasticAngularEnergyGrid( angular_energy_grid );
//  data_container.setAdjointCutoffElasticPDF( elastic_pdf );
//  data_container.setAdjointCutoffElasticAngles( elastic_angle );

//  std::cout << "done." << std::endl;

//  if ( d_cutoff_angle_cosine > 0.999999 )
//  {
//    std::cout << " Moment preserving data will not be generated because the"
//              << " cutoff angle cosine is greater than 0.999999." << std::endl
//              << " cutoff_angle_cosine = " << d_cutoff_angle_cosine << std::endl;
//  }
//  else if ( d_number_of_moment_preserving_angles < 1 )
//  {
//    std::cout << " Moment preserving data will not be generated because the"
//              << " number of moment preserving angles is less than 1." << std::endl
//              << " number_of_moment_preserving_angles = "
//              << d_number_of_moment_preserving_angles << std::endl;
//  }
//  else
//  {
//    std::cout << " Setting the adjoint elastic moment preserving data...";
//    std::cout.flush();
//    // Set the moment preserving data
//    StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointMomentPreservingData(
//        angular_energy_grid,
//        data_container );
//    std::cout << "done." << std::endl;
//  }

////---------------------------------------------------------------------------//
//// Set Bremsstrahlung Data
////---------------------------------------------------------------------------//
//  std::cout << " Setting the bremsstrahlung data...";
//  std::cout.flush();

//  std::vector<double> adjoint_bremsstrahlung_energy_grid =
//    data_container.getAdjointBremsstrahlungEnergyGrid();

//  Teuchos::ArrayRCP<double> adjoint_electron_energy_grid;
//  adjoint_electron_energy_grid.assign(
//    union_energy_grid.begin(),
//    union_energy_grid.end() );

//  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
//      new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
//                adjoint_electron_energy_grid,
//                adjoint_electron_energy_grid[0],
//                adjoint_electron_energy_grid[adjoint_electron_energy_grid.size()-1],
//                adjoint_electron_energy_grid.size()/10 + 1 ) );

//  Teuchos::ArrayRCP<double> adjoint_bremsstrahlung_cross_section;
//  adjoint_bremsstrahlung_cross_section.assign(
//    data_container.getAdjointBremsstrahlungCrossSection().begin(),
//    data_container.getAdjointBremsstrahlungCrossSection().end() );

//  // Calculate the adjoint PDF at the different incoming adjoint energies and photon energies
//  std::map<double, std::vector<double> > adjoint_bremsstrahlung_pdf_map;

//  // Evaluate the PDF values for all but the max energy
//  for ( int i = 0; i < adjoint_bremsstrahlung_energy_grid.size()-1; i++ )
//  {
//    unsigned bin_index =
//      grid_searcher->findLowerBinIndex( adjoint_bremsstrahlung_energy_grid.at(i) );

//    std::vector<double> adjoint_bremsstrahlung_photon_energies;

//    // When possible use the same photon energies as the forward data
//    if ( d_forward_epr_data->getBremsstrahlungPhotonEnergy().count(
//            adjoint_bremsstrahlung_energy_grid.at(i) ) )
//    {
//      adjoint_bremsstrahlung_photon_energies =
//        d_forward_epr_data->getBremsstrahlungPhotonEnergyAtEnergy(
//            adjoint_bremsstrahlung_energy_grid.at(i) );

//      data_container.setAdjointBremsstrahlungPhotonEnergyAtIncomingEnergy(
//        adjoint_bremsstrahlung_energy_grid.at(i),
//        adjoint_bremsstrahlung_photon_energies );
//    }
//    else
//    {
//      /* If the min_electron_energy falls between two energies on the forward
//          bremsstrahlung energy grid a new set of photon energies must be chosen.
//          This is done by taking the set of photon energies for the forward
//          energy grid point above the min energy and substracting the photon
//          energies above the min electron energy.
//          For the nudge energy (right below the max energy) the photon energies
//          for the max_electron_energy are used with the max_electron_energy
//          replaced with the nudge energy.
//       */
//      adjoint_bremsstrahlung_photon_energies =
//        d_forward_epr_data->getBremsstrahlungPhotonEnergyAtEnergy(
//            adjoint_bremsstrahlung_energy_grid.at(i+1) );
//   
//      // Eliminate photon energies above the current electron energy
//      while ( adjoint_bremsstrahlung_photon_energies.back() >=
//              adjoint_bremsstrahlung_energy_grid.at(i) )
//      {
//        adjoint_bremsstrahlung_photon_energies.pop_back();
//      }

//      // Add the current energy as the max photon energy
//      adjoint_bremsstrahlung_photon_energies.push_back(
//        adjoint_bremsstrahlung_energy_grid.at(i) );

//      data_container.setAdjointBremsstrahlungPhotonEnergyAtIncomingEnergy(
//        adjoint_bremsstrahlung_energy_grid.at(i),
//        adjoint_bremsstrahlung_photon_energies );
//    }

//    this->evaluateAdjointBremsstrahlungPhotonDistribution(
//        adjoint_bremsstrahlung_energy_grid.at(i),
//        bin_index,
//        data_container.getAdjointBremsstrahlungCrossSectionThresholdEnergyIndex(),
//        adjoint_bremsstrahlung_cross_section,
//        adjoint_electron_energy_grid,
//        adjoint_bremsstrahlung_cs_evaluator,
//        adjoint_bremsstrahlung_photon_energies,
//        adjoint_bremsstrahlung_pdf_map[adjoint_bremsstrahlung_energy_grid.at(i)] );
//  }

//  // The PDF for the max incoming energy is always zero
//  std::vector<double> photon_energy( 2 );
//  photon_energy[0] = 1e-7;
//  photon_energy[1] = d_max_electron_energy;

//  data_container.setAdjointBremsstrahlungPhotonEnergyAtIncomingEnergy(
//    d_max_electron_energy,
//    photon_energy );

//  std::vector<double> photon_pdf( 2 );
//  photon_energy[0] = 0.0;
//  photon_energy[1] = 0.0;
//  adjoint_bremsstrahlung_pdf_map[d_max_electron_energy] =
//    photon_pdf;

//  data_container.setAdjointBremsstrahlungPhotonPDF(
//    adjoint_bremsstrahlung_pdf_map );

//  std::cout << "done." << std::endl;

////---------------------------------------------------------------------------//
//// Set Electroionization Data
////---------------------------------------------------------------------------//
//  std::cout << " Setting the electroionization data...";
//  std::cout.flush();

//  shell = data_container.getSubshells().begin();

//  // Loop through electroionization data for every subshell
//  for ( shell; shell != data_container.getSubshells().end(); shell++ )
//  {/*
//    data_container.setAdjointElectroionizationEnergyGrid(
//        *shell,
//        d_forward_epr_data->getElectroionizationEnergyGrid( *shell ) );

//    data_container.setAdjointElectroionizationRecoilEnergy(
//        *shell,
//        d_forward_epr_data->getElectroionizationEnergy( *shell ) );

//    data_container.setAdjointElectroionizationRecoilPDF(
//        *shell,
//        d_forward_epr_data->getElectroionizationRecoilPDF( *shell ) );*/
//  }
//  std::cout << "done." << std::endl;
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

  // std::shared_ptr<MonteCarlo::AnalogElasticElectroatomicReaction<Utility::LinLin>> 
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
    const std::shared_ptr<MonteCarlo::AnalogElasticElectroatomicReaction<Utility::LinLin> >&
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
    const Teuchos::ArrayRCP<const double>& forward_electron_energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& forward_grid_searcher,
    std::shared_ptr<DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction> >&
        adjoint_bremsstrahlung_cs_evaluator ) const
{
  std::shared_ptr<BremsstrahlungReaction> bremsstrahlung_reaction;

  MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
    *d_forward_epr_data,
    forward_electron_energy_grid,
    forward_grid_searcher,
    bremsstrahlung_reaction,
    MonteCarlo::DIPOLE_DISTRIBUTION );

  std::vector<double>::const_iterator start, end;

  this->findLowerAndUpperBinBoundary(
          d_min_electron_energy,
          d_max_electron_energy,
          d_forward_epr_data->getBremsstrahlungEnergyGrid(),
          start,
          end );
  ++end;

  // The bremsstrahlung integration points
  /*! \details The forward bremsstrahlung energy grid is used as a basis for
   *  the cross section evaluator integration points
   */
  std::vector<double> bremsstrahlung_integration_points( start, end );

  // Replace the lower and upper bins with the min and max electron energies
  bremsstrahlung_integration_points.front() = d_min_electron_energy;
  bremsstrahlung_integration_points.back() = d_max_electron_energy;

//  adjoint_bremsstrahlung_cs_evaluator.reset(
//    new DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction>(
//        bremsstrahlung_reaction,
//        bremsstrahlung_integration_points ) );

/*
  MonteCarlo::ElectroatomicReactionENDLFactory::createBremsstrahlungReaction(
    *d_forward_epr_data,
    adjoint_bremsstrahlung_energy_grid,
    bremsstrahlung_reaction,
	  MonteCarlo::DIPOLE_DISTRIBUTION );

  // Set the min and max adjoint energies
  adjoint_bremsstrahlung_energy_grid.front() = d_min_electron_energy;
  adjoint_bremsstrahlung_energy_grid.back() = d_max_electron_energy;

  adjoint_bremsstrahlung_cs_evaluator.reset(
    new DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction>(
        bremsstrahlung_reaction,
        adjoint_bremsstrahlung_energy_grid ) );

  // Add nudge value
  adjoint_bremsstrahlung_energy_grid.back() =
     d_max_electron_energy - s_min_tabulated_energy_loss;
   adjoint_bremsstrahlung_energy_grid.push_back( d_max_electron_energy );

  // Set the adjoint bremsstrahlung energy grid
  data_container.setAdjointBremsstrahlungEnergyGrid(
    adjoint_bremsstrahlung_energy_grid );*/
}

// Generate adjoint bremsstrahlung photon energy distribution
void StandardAdjointElectronPhotonRelaxationDataGenerator::evaluateAdjointBremsstrahlungPhotonDistribution(
    const double incoming_adjoint_energy,
    const unsigned bin_index,
    const unsigned threshold_energy_index,
    const Teuchos::ArrayRCP<const double>& adjoint_cross_section,
    const Teuchos::ArrayRCP<const double>& adjoint_electron_energy_grid,
    const std::shared_ptr<DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction> >
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
    std::map<unsigned,std::shared_ptr<DataGen::AdjointElectronCrossSectionEvaluator<ElectroionizationReaction> > >&
        adjoint_electroionization_cs_evaluators ) const
{
  // Extract the subshell information
  std::set<unsigned>::const_iterator shell =
    d_forward_epr_data->getSubshells().begin();

  // Get the energy grid for the forward electroionization subshell reactions
  std::vector<double>::const_iterator start, end;

  double threshold_energy =
    *d_forward_epr_data->getElectroionizationEnergyGrid(*shell).begin();

  for ( shell; shell != d_forward_epr_data->getSubshells().end(); ++shell )
  {
    if ( threshold_energy >= d_min_electron_energy )
    {
      start =
        d_forward_epr_data->getElectroionizationEnergyGrid(*shell).begin();
    }
    else
    {
      // Get energy iterator below/equal to d_min_electron_energy
      start = Utility::Search::binaryLowerBound(
          d_forward_epr_data->getElectroionizationEnergyGrid(*shell).begin(),
          d_forward_epr_data->getElectroionizationEnergyGrid(*shell).end(),
          d_min_electron_energy );
    }

    // Get energy iterator above/equal to d_max_electron_energy
    end = Utility::Search::binaryUpperBound(
        start,
        d_forward_epr_data->getElectroionizationEnergyGrid(*shell).end(),
        d_max_electron_energy );
    ++end;

    // Set the recoil energy grid for the given min and max electron energy
    std::vector<double> ionization_energy_grid( start, end );

    // Create the subshell reaction
    std::shared_ptr<ElectroionizationReaction>
      electroionization_subshell_reaction;
/*
    MonteCarlo::ElectroatomicReactionENDLFactory::createSubshellElectroionizationReaction(
      *d_forward_epr_data,
      ionization_energy_grid,
      *shell,
      electroionization_subshell_reaction );

    // Set the min and max adjoint energies
    if ( threshold_energy < d_min_electron_energy )
    {
      ionization_energy_grid.front() = d_min_electron_energy;
    }
    ionization_energy_grid.back() = d_max_electron_energy;

    adjoint_electroionization_cs_evaluators[*shell].reset(
      new DataGen::AdjointElectronCrossSectionEvaluator<ElectroionizationReaction>(
          electroionization_subshell_reaction,
          ionization_energy_grid ) );

    // Add nudge value
    ionization_energy_grid.back() =
        d_max_electron_energy - s_min_tabulated_energy_loss;
      ionization_energy_grid.push_back( d_max_electron_energy );

    // Set the adjoint electroionization energy grid
    data_container.setAdjointElectroionizationEnergyGrid(
      *shell,
      ionization_energy_grid );*/
  }
}

// Initialize the electron union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::initializeAdjointElectronUnionEnergyGrid(
     const Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
     std::list<double>& union_energy_grid ) const
{
  // Add the min electron energy to the union energy grid
  union_energy_grid.push_back( d_min_electron_energy );

  const std::set<unsigned>& subshells = data_container.getSubshells();

  std::set<unsigned>::const_iterator subshell = subshells.begin();

  // Add the subshell binding energies
  while( subshell != subshells.end() )
  {
    double binding_energy =
      data_container.getSubshellBindingEnergy( *subshell );

      union_energy_grid.push_back(
        d_max_electron_energy - binding_energy - s_min_tabulated_energy_loss );
      union_energy_grid.push_back(
        d_max_electron_energy - binding_energy - s_min_tabulated_energy_loss*s_threshold_energy_nudge_factor );

    ++subshell;
  }

  // Add a max allowed adjoint energy bin
  union_energy_grid.push_back(
    d_max_electron_energy - s_min_tabulated_energy_loss );

  // Add the max electron energy
  union_energy_grid.push_back( d_max_electron_energy );

  // Sort the union energy grid
  union_energy_grid.sort();
}

// Find the lower and upper bin boundary for a min and max energy
void StandardAdjointElectronPhotonRelaxationDataGenerator::findLowerAndUpperBinBoundary(
    const double min_energy,
    const double max_energy,
    const std::vector<double>& energy_distribution,
    std::vector<double>::const_iterator& lower_energy_boundary,
    std::vector<double>::const_iterator& upper_energy_boundary ) const
{
  // Get energy iterator below/equal to min_energy
  lower_energy_boundary = Utility::Search::binaryLowerBound(
              energy_distribution.begin(),
              energy_distribution.end(),
              min_energy );

  // Get energy iterator above/equal to d_max_electron_energy
  upper_energy_boundary = Utility::Search::binaryUpperBound(
              lower_energy_boundary,
              energy_distribution.end(),
              max_energy );
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
