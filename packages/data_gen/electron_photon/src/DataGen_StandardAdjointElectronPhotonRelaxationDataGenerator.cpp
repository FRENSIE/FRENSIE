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

const double StandardAdjointElectronPhotonRelaxationDataGenerator::s_threshold_energy_nudge_factor = 1.0e-4;
const double StandardAdjointElectronPhotonRelaxationDataGenerator::s_min_tabulated_energy_loss = 1.0e-7;

// Advanced Constructor
StandardAdjointElectronPhotonRelaxationDataGenerator::StandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data,
      const double min_photon_energy,
      const double max_photon_energy,
      const double min_electron_energy,
      const double max_electron_energy,
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
    d_cutoff_angle_cosine( forward_epr_data->getCutoffAngleCosine() ),
    d_number_of_moment_preserving_angles( forward_epr_data->getNumberOfMomentPreservingAngles() ),
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
  Teuchos::ArrayRCP<double> forward_cutoff_elastic_cs;
  forward_cutoff_elastic_cs.assign(
    d_forward_epr_data->getCutoffElasticCrossSection().begin(),
    d_forward_epr_data->getCutoffElasticCrossSection().end() );

  std::shared_ptr<MonteCarlo::ElectroatomicReaction> cutoff_elastic_reaction(
    new MonteCarlo::VoidStandardElectroatomicReaction<Utility::LinLin>(
        forward_electron_energy_grid,
        forward_cutoff_elastic_cs,
        d_forward_epr_data->getCutoffElasticCrossSectionThresholdEnergyIndex(),
        forward_grid_searcher ) );

  // Extract the total elastic cross section data
  Teuchos::ArrayRCP<double> forward_total_elastic_cs;
  forward_total_elastic_cs.assign(
    d_forward_epr_data->getTotalElasticCrossSection().begin(),
    d_forward_epr_data->getTotalElasticCrossSection().end() );

  std::shared_ptr<MonteCarlo::ElectroatomicReaction> total_elastic_reaction(
    new MonteCarlo::VoidStandardElectroatomicReaction<Utility::LinLin>(
        forward_electron_energy_grid,
        forward_total_elastic_cs,
        d_forward_epr_data->getTotalElasticCrossSectionThresholdEnergyIndex(),
        forward_grid_searcher ) );

  //---------------------------------------------------------------------------//
  // Extract The Adjoint Atomic Excitation Cross Section Data
  //---------------------------------------------------------------------------//

  std::shared_ptr<const Utility::OneDDistribution> adjoint_excitation_cross_section;

  this->createAdjointAtomicExcitationCrossSectionDistribution(
          data_container,
          forward_electron_energy_grid,
          forward_grid_searcher,
          adjoint_excitation_cross_section );


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

  //---------------------------------------------------------------------------//
  // Create The Adjoint Electroionization Subshell Cross Section Evaluator
  //---------------------------------------------------------------------------//
  // The adjoint electroionization subshell cross section evaluator
  std::map<unsigned,std::shared_ptr<DataGen::AdjointElectronCrossSectionEvaluator<ElectroionizationReaction> > >
    adjoint_electroionization_cs_evaluators;

  this->createAdjointElectroionizationSubshellCrossSectionEvaluator(
          forward_electron_energy_grid,
          forward_grid_searcher,
          adjoint_electroionization_cs_evaluators );

  //---------------------------------------------------------------------------//
  // Create union energy grid and calculate cross sections
  //---------------------------------------------------------------------------//

  // Create the union energy grid
  std::cout << "   Creating union energy grid";
  std::cout.flush();
  std::list<double> union_energy_grid;

  this->initializeAdjointElectronUnionEnergyGrid(
          data_container,
          union_energy_grid );

  Utility::GridGenerator<Utility::LinLin>
  union_energy_grid_generator( d_grid_convergence_tol,
                               d_grid_absolute_diff_tol,
                               d_grid_distance_tol );

  // Calculate the union energy grid
  boost::function<double (double pz)> cutoff_elastic_grid_function =
    boost::bind( &MonteCarlo::ElectroatomicReaction::getCrossSection,
                 boost::cref( *cutoff_elastic_reaction ),
                 _1 );

  union_energy_grid_generator.generateInPlace( union_energy_grid,
                                               cutoff_elastic_grid_function );

  std::cout << ".";
  std::cout.flush();

  boost::function<double (double pz)> total_elastic_grid_function =
    boost::bind( &MonteCarlo::ElectroatomicReaction::getCrossSection,
                 boost::cref( *total_elastic_reaction ),
                 _1 );

  union_energy_grid_generator.generateInPlace( union_energy_grid,
                                               total_elastic_grid_function );

  std::cout << ".";
  std::cout.flush();

  boost::function<double (double pz)> atomic_excitation_grid_function =
    boost::bind( &Utility::OneDDistribution::evaluate,
  		                   boost::cref( *adjoint_excitation_cross_section ),
  		                   _1 );

  union_energy_grid_generator.refineInPlace( 
    union_energy_grid,
    atomic_excitation_grid_function,
    d_min_electron_energy,
    data_container.getAdjointAtomicExcitationEnergyGrid().back() );

  std::cout << ".";
  std::cout.flush();


  boost::function<double (double pz)> bremsstrahlung_grid_function =
    boost::bind(
        &DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction>::evaluateAdjointCrossSection,
        boost::cref( *adjoint_bremsstrahlung_cs_evaluator ),
        _1,
        d_adjoint_bremsstrahlung_evaluation_tolerance );

  std::vector<double> old_adjoint_bremsstrahlung_cs;

  union_energy_grid_generator.refineAndEvaluateInPlace(
    union_energy_grid,
    old_adjoint_bremsstrahlung_cs,
    bremsstrahlung_grid_function,
    d_min_electron_energy,
    d_max_electron_energy*(1.0 - s_threshold_energy_nudge_factor) );

  std::list<double> old_adjoint_bremsstrahlung_union_energy_grid(
    union_energy_grid );

  std::cout << ".";
  std::cout.flush();


  std::map<unsigned,std::list<double> >
    old_adjoint_electroionization_union_energy_grid;

  std::map<unsigned,std::vector<double> > old_adjoint_electroionization_cs;
  std::map<unsigned,boost::function<double (double pz)> >
    ionization_grid_functions;

  std::set<unsigned>::iterator shell = data_container.getSubshells().begin();

  // Loop through electroionization evaluator for every subshell
  for ( shell; shell != data_container.getSubshells().end(); shell++ )
  {
    ionization_grid_functions[*shell] =
      boost::bind(
    	   &DataGen::AdjointElectronCrossSectionEvaluator<ElectroionizationReaction>::evaluateAdjointCrossSection,
    	   boost::cref( *adjoint_electroionization_cs_evaluators.find( *shell )->second ),
    	   _1,
         d_adjoint_electroionization_evaluation_tolerance );

    double binding_energy = data_container.getSubshellBindingEnergy( *shell );

    union_energy_grid_generator.refineAndEvaluateInPlace(
      union_energy_grid,
      old_adjoint_electroionization_cs[*shell],
      ionization_grid_functions[*shell],
      d_min_electron_energy,
      d_max_electron_energy - binding_energy - 2.0*s_min_tabulated_energy_loss );

    old_adjoint_electroionization_union_energy_grid[*shell] =
      union_energy_grid;

    std::cout << ".";
    std::cout.flush();
  }

  std::cout << "done." << std::endl;

  // Set the union energy grid
  std::vector<double> energy_grid(
        union_energy_grid.begin(),
        union_energy_grid.end() );

  data_container.setAdjointElectronEnergyGrid( energy_grid );

  // Create and set the cross sections
  std::vector<double> cross_section;
  unsigned threshold;

  // Set the adjoint elastic cross section data
  std::cout << "   Setting the adjoint total elastic cross section...";
  std::cout.flush();
  std::vector<double> total_cross_section;
  this->createAdjointCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      total_elastic_grid_function,
      total_cross_section,
      threshold );
  data_container.setAdjointTotalElasticCrossSection( total_cross_section );
  data_container.setAdjointTotalElasticCrossSectionThresholdEnergyIndex( threshold );
  std::cout << "done." << std::endl;

  std::cout << "   Setting the adjoint cutoff elastic cross section...";
  std::cout.flush();
  std::vector<double> cutoff_cross_section;
  this->createAdjointCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      cutoff_elastic_grid_function,
      cutoff_cross_section,
      threshold );
  data_container.setAdjointCutoffElasticCrossSection( cutoff_cross_section );
  data_container.setAdjointCutoffElasticCrossSectionThresholdEnergyIndex( threshold );
  std::cout << "done." << std::endl;


  std::cout << "   Setting the screened Rutherford elastic cross section...";
  std::cout.flush();
  {
  std::vector<double> raw_cross_section( total_cross_section.size() );
  for ( int i = 0; i < total_cross_section.size(); ++i )
  {
      raw_cross_section.at(i) = total_cross_section.at(i) - cutoff_cross_section.at(i);

      double relative_difference = raw_cross_section.at(i)/total_cross_section.at(i);

      // Check for roundoff error and reduce to zero if needed
      if ( relative_difference < 1.0e-6 )
      {
          raw_cross_section[i] = 0.0;

          // Update threshold index
          threshold = i+1;
      }
  }

  std::vector<double>::iterator start = raw_cross_section.begin();
  std::advance( start, threshold );

  cross_section.assign( start, raw_cross_section.end() );

  data_container.setAdjointScreenedRutherfordElasticCrossSection( cross_section );
  data_container.setAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(
  threshold );
  }
  std::cout << "done." << std::endl;

  if( d_forward_epr_data->hasMomentPreservingData() )
  {
    std::cout << "   Setting the adjoint moment preserving elastic cross section...";
    std::cout.flush();

    // Extract the moment preserving elastic cross section data
    Teuchos::ArrayRCP<double> forward_moment_preserving_elastic_cs;
    forward_moment_preserving_elastic_cs.assign(
      d_forward_epr_data->getMomentPreservingCrossSection().begin(),
      d_forward_epr_data->getMomentPreservingCrossSection().end() );

    std::shared_ptr<MonteCarlo::ElectroatomicReaction> moment_preserving_elastic_reaction(
      new MonteCarlo::VoidStandardElectroatomicReaction<Utility::LinLin>(
          forward_electron_energy_grid,
          forward_moment_preserving_elastic_cs,
          d_forward_epr_data->getMomentPreservingCrossSectionThresholdEnergyIndex(),
          forward_grid_searcher ) );

    boost::function<double (double pz)> moment_preserving_elastic_grid_function =
      boost::bind( &MonteCarlo::ElectroatomicReaction::getCrossSection,
                   boost::cref( *moment_preserving_elastic_reaction ),
                   _1 );

    std::vector<double> moment_preserving_cross_section;
    this->createAdjointCrossSectionOnUnionEnergyGrid(
        union_energy_grid,
        moment_preserving_elastic_grid_function,
        moment_preserving_cross_section,
        threshold );
    data_container.setAdjointMomentPreservingCrossSection( moment_preserving_cross_section );
    data_container.setAdjointMomentPreservingCrossSectionThresholdEnergyIndex( threshold );
    std::cout << "done." << std::endl;
  }

  // Set the adjoint atomic excitation cross section data
  std::cout << "   Setting the adjoint atomic excitation cross section...";
  std::cout.flush();
  std::vector<double> excitation_cross_section;
  this->createAdjointCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      atomic_excitation_grid_function,
      excitation_cross_section,
      threshold );

  data_container.setAdjointAtomicExcitationCrossSection( excitation_cross_section );
  data_container.setAdjointAtomicExcitationCrossSectionThresholdEnergyIndex( threshold );
  std::cout << "done." << std::endl;

  // Set the adjoint bremsstrahlung cross section data
  std::cout << "   Setting the adjoint bremsstrahlung cross section...";
  std::cout.flush();
  this->createAdjointCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      old_adjoint_bremsstrahlung_union_energy_grid,
      old_adjoint_bremsstrahlung_cs,  
      adjoint_bremsstrahlung_cs_evaluator,
      d_adjoint_bremsstrahlung_evaluation_tolerance,
      cross_section,
      threshold );

  data_container.setAdjointBremsstrahlungCrossSection( cross_section );
  data_container.setAdjointBremsstrahlungCrossSectionThresholdEnergyIndex( threshold );
  std::cout << "done." << std::endl;

  // Set the adjoint electroionization subshell cross section data
  std::cout << "   Setting the adjoint electroionization subshell cross section...";
  std::cout.flush();

  // Loop through the electroionization subshells
  shell = data_container.getSubshells().begin();
  for ( shell; shell != data_container.getSubshells().end(); shell++ )
  {
    this->createAdjointCrossSectionOnUnionEnergyGrid(
        union_energy_grid,
        old_adjoint_electroionization_union_energy_grid[*shell],
        old_adjoint_electroionization_cs[*shell],  
        adjoint_electroionization_cs_evaluators[*shell],
        d_adjoint_electroionization_evaluation_tolerance,
        cross_section,
        threshold );

    data_container.setAdjointElectroionizationCrossSection(
      *shell,
      cross_section );

    data_container.setAdjointElectroionizationCrossSectionThresholdEnergyIndex(
      *shell,
      threshold );
  }
  std::cout << "done." << std::endl;

//---------------------------------------------------------------------------//
// Set Elastic Data
//---------------------------------------------------------------------------//
  std::cout << " Setting the adjoint elastic cutoff data...";
  std::cout.flush();

  // Set elastic angular distribution
  data_container.setAdjointElasticAngularEnergyGrid(
        d_forward_epr_data->getElasticAngularEnergyGrid() );

  data_container.setAdjointCutoffElasticAngles(
        d_forward_epr_data->getCutoffElasticAngles() );

  data_container.setAdjointCutoffElasticPDF(
        d_forward_epr_data->getCutoffElasticPDF() );

  std::cout << "done." << std::endl;

  std::cout << " Setting the adjoint elastic moment preserving data...";
  std::cout.flush();

  data_container.setAdjointMomentPreservingElasticDiscreteAngles(
        d_forward_epr_data->getMomentPreservingElasticDiscreteAngles() );

  data_container.setAdjointMomentPreservingElasticWeights(
        d_forward_epr_data->getMomentPreservingElasticWeights() );

  std::cout << "done." << std::endl;

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

// Create the adjoint atomic excitation cross section reaction
void StandardAdjointElectronPhotonRelaxationDataGenerator::createAdjointAtomicExcitationCrossSectionDistribution(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    const Teuchos::ArrayRCP<const double>& forward_electron_energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& forward_grid_searcher,
    std::shared_ptr<const Utility::OneDDistribution>&
      adjoint_excitation_cross_section_distribution ) const
{
  // Extract the total elastic cross section data
  Teuchos::ArrayRCP<double> atomic_excitation_cross_section;
  atomic_excitation_cross_section.assign(
    d_forward_epr_data->getAtomicExcitationCrossSection().begin(),
    d_forward_epr_data->getAtomicExcitationCrossSection().end() );

  std::shared_ptr<MonteCarlo::ElectroatomicReaction> atomic_excitation_reaction(
    new MonteCarlo::VoidStandardElectroatomicReaction<Utility::LinLin>(
        forward_electron_energy_grid,
        atomic_excitation_cross_section,
        d_forward_epr_data->getAtomicExcitationCrossSectionThresholdEnergyIndex(),
        forward_grid_searcher ) );

  // Find the upper and lower boundary bins for the min and max energy
  std::vector<double>::const_iterator energy_grid_start, energy_grid_end;
  this->findLowerAndUpperBinBoundary(
          d_min_electron_energy,
          d_max_electron_energy,
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
  while ( *energy_grid_start - *energy_gain_start < d_min_electron_energy  )
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

  // Calcualte the adjoint icoming energy grid from the forward incoming energy grid and energy loss
  for ( int i = 0; i < adjoint_excitation_energy_grid.size(); i++ )
  {
    // Evaluate the cross section at the forward energy
    adjoint_excitation_cross_section[i] =
      atomic_excitation_reaction->getCrossSection( adjoint_excitation_energy_grid[i] );

    // Calculate the adjoint energy grid point at the forward energy
    adjoint_excitation_energy_grid[i] -= adjoint_excitation_energy_gain[i];
  }

  // Set atomic excitation energy grid (adjoint energy grid = forward energy grid - forward energy loss)
  data_container.setAdjointAtomicExcitationEnergyGrid(
    adjoint_excitation_energy_grid );

  // Set atomic excitation energy gain (adjoint energy gain = forward energy loss)
  data_container.setAdjointAtomicExcitationEnergyGain(
    adjoint_excitation_energy_gain );

  adjoint_excitation_cross_section_distribution.reset(
    new Utility::TabularDistribution<Utility::LinLin>(
      adjoint_excitation_energy_grid,
      adjoint_excitation_cross_section ) );
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

  adjoint_bremsstrahlung_cs_evaluator.reset(
    new DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction>(
        bremsstrahlung_reaction,
        bremsstrahlung_integration_points ) );

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
    const Teuchos::ArrayRCP<const double>& forward_electron_energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& forward_grid_searcher,
    std::map<unsigned,std::shared_ptr<DataGen::AdjointElectronCrossSectionEvaluator<ElectroionizationReaction> > >&
        adjoint_electroionization_cs_evaluators ) const
{
  // Extract the subshell information
  std::set<unsigned>::const_iterator shell =
    d_forward_epr_data->getSubshells().begin();

  // Get the energy grid for the forward electroionization subshell reactions
  std::vector<double>::const_iterator start, end;

  for ( shell; shell != d_forward_epr_data->getSubshells().end(); ++shell )
  {

    // Create the subshell reaction
    std::shared_ptr<ElectroionizationReaction>
      electroionization_subshell_reaction;

    MonteCarlo::ElectroatomicReactionNativeFactory::createSubshellElectroionizationReaction(
      *d_forward_epr_data,
      forward_electron_energy_grid,
      forward_grid_searcher,
      *shell,
      electroionization_subshell_reaction );

    // Get the threshold energy for the reaction
    double threshold_energy = d_forward_epr_data->getSubshellBindingEnergy( *shell );

    // Get the minimum allowable energy for the sunshell (either threshold_energy or d_min_electron_energy)
    double min_ionization_subshell_energy;
    if ( threshold_energy > d_min_electron_energy )
      min_ionization_subshell_energy = threshold_energy;
    else
      min_ionization_subshell_energy = d_min_electron_energy;

    // Find the upper and lower boundary bins for the min and max energy
    this->findLowerAndUpperBinBoundary(
          min_ionization_subshell_energy,
          d_max_electron_energy,
          d_forward_epr_data->getElectroionizationEnergyGrid(*shell),
          start,
          end );
    ++end;

    // Set the recoil energy grid for the given min and max electron energy
    std::vector<double> ionization_energy_grid( start, end );

    // Set the min and max adjoint energies
    ionization_energy_grid.front() = min_ionization_subshell_energy;
    ionization_energy_grid.back() = d_max_electron_energy;

    adjoint_electroionization_cs_evaluators[*shell].reset(
      new DataGen::AdjointElectronCrossSectionEvaluator<ElectroionizationReaction>(
          electroionization_subshell_reaction,
          ionization_energy_grid ) );

  
/*
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
