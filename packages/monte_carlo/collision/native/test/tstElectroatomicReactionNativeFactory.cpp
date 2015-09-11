//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomicReactionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  Electroatomic reaction factory using Native data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Data_EvaluatedElectronDataContainer.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

MonteCarlo::BremsstrahlungAngularDistributionType photon_distribution_function;
Teuchos::RCP<Data::EvaluatedElectronDataContainer> data_container;
Teuchos::ArrayRCP<double> energy_grid;
Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher;
Teuchos::RCP<MonteCarlo::ElectroatomicReaction> reaction;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an analog elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory, 
		           createAnalogElasticReaction )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createAnalogElasticReaction(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.00000e-5 );
  
  // Test that the stored cross section is correct
  double energy = 1.00000e-5;
  double cross_section = 
    reaction->getCrossSection( energy );
  
  TEST_FLOATING_EQUALITY( cross_section, 2.489240000000e+9, 1e-12 );

  energy = 4.00000e-4;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458e+8, 1e-12 );

  energy = 1.00000e+5;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 8.830510000000e-2, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a screened Rutherford elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory, 
		           createScreenedRutherfordElasticReaction )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createScreenedRutherfordElasticReaction(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 6.654785 );
  
  // Test that the stored cross section is correct
  double energy = 1.00000E+01;
  double cross_section = 
    reaction->getCrossSection( energy );
  
  TEST_FLOATING_EQUALITY( cross_section, 3.7220000000000E+05, 1e-12 );

  energy = 1.00000E+02;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 2.0561378000000E+06, 1e-12 );

  energy = 1.00000e+5;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 2.1116099116949E+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an atomic excitation reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
		   createAtomicExcitationReaction )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
					           *data_container,
							   energy_grid,
                               grid_searcher,
							   reaction);

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.00000e-5 );
  
  // Test that the stored cross section is correct
  double cross_section = 
    reaction->getCrossSection( 1.00000e-5 );
  
  TEST_FLOATING_EQUALITY( cross_section, 8.757550000000e+6, 1e-12 );

  cross_section = reaction->getCrossSection( 4.00000e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 6.226820000000e+8, 1e-12 );

  cross_section = reaction->getCrossSection( 1.00000e+5 );

  TEST_FLOATING_EQUALITY( cross_section, 1.578610000000e+6, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell reactions can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
		   createSubshellElectroelectricReactions )
{
  Teuchos::Array<Teuchos::RCP<MonteCarlo::ElectroatomicReaction> > reactions;

  MonteCarlo::ElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions(
							   *data_container,
							   energy_grid,
                               grid_searcher, 
							   reactions );

  TEST_EQUALITY_CONST( reactions.size(), 24 );

  // Test the first shell's reaction properties
  TEST_EQUALITY_CONST( 
		   reactions.front()->getReactionType(),
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.front()->getThresholdEnergy(), 8.97540e-2 );

  // Test the first shell's stored cross section is correct
  double cross_section = 
    reactions.front()->getCrossSection( 8.829000E-02 );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
  
  cross_section = 
    reactions.front()->getCrossSection( 1.00000e-1 );

  TEST_FLOATING_EQUALITY( cross_section, 9.283500e-1, 1e-12 );

  cross_section = 
    reactions.front()->getCrossSection( 1.58489e+2 );

  TEST_FLOATING_EQUALITY( cross_section, 2.788860E+01, 1e-12 );

  cross_section = 
    reactions.front()->getCrossSection( 1.00000e+5 );

  TEST_FLOATING_EQUALITY( cross_section, 3.649190e+1, 1e-12 );

  // Check the last shell's reaction properties
  TEST_EQUALITY_CONST(
		  reactions.back()->getReactionType(),
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.back()->getThresholdEnergy(), 1.00000e-5 );

  cross_section = 
    reactions.back()->getCrossSection( 1.00000e-5 );

  TEST_FLOATING_EQUALITY( cross_section, 1.065300e+8, 1e-12 );

  cross_section = 
    reactions.back()->getCrossSection( 1.00000e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 3.248850E+07, 1e-12 );

  cross_section = 
    reactions.back()->getCrossSection( 1.000000E+00 );

  TEST_FLOATING_EQUALITY( cross_section, 2.033500E+05, 1e-12 );

  cross_section = 
    reactions.back()->getCrossSection( 1.00000e+5 );

  TEST_FLOATING_EQUALITY( cross_section, 1.8223400e+5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a basic (dipole distribution) bremsstrahlung reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory, 
                   createBremsstrahlungReaction_dipole )
{
  photon_distribution_function = MonteCarlo::DIPOLE_DISTRIBUTION;

  MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
							   *data_container,
							   energy_grid,
                               grid_searcher,
							   reaction,
							   photon_distribution_function );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.00000e-5 );

  // Test that the stored cross section is correct
  double cross_section = 
    reaction->getCrossSection( reaction->getThresholdEnergy() );

  TEST_FLOATING_EQUALITY( cross_section, 4.869800000000e+3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.00000e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 9.528370E+03, 1e-12 );

  cross_section = reaction->getCrossSection( 4.000000E+01 );

  TEST_FLOATING_EQUALITY( cross_section, 1.405050E+03, 1e-12 );
  
  cross_section = reaction->getCrossSection( 1.00000e+5 );
  
  TEST_EQUALITY_CONST( cross_section, 1.9541700e+3 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
/* Check that a electroatom with detailed 2BS photon angular distribution 
 * data can be created
 */
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory, 
                   createBremsstrahlungReaction_2bs )
{
  photon_distribution_function = MonteCarlo::TWOBS_DISTRIBUTION;

  MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
							   *data_container,
							   energy_grid,
                               grid_searcher,
							   reaction,
							   photon_distribution_function );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.00000e-5 );

  // Test that the stored cross section is correct
  double cross_section = 
    reaction->getCrossSection( reaction->getThresholdEnergy() );

  TEST_FLOATING_EQUALITY( cross_section, 4.869800e+3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.00000e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 9.528370E+03, 1e-12 );

  cross_section = reaction->getCrossSection( 4.000000E+01 );

  TEST_FLOATING_EQUALITY( cross_section, 1.405050E+03, 1e-12 );
  
  cross_section = reaction->getCrossSection( 1.00000e+5 );
  
  TEST_EQUALITY_CONST( cross_section, 1.9541700e+3 );

  // Clear the reaction
  reaction.reset();
}



//---------------------------------------------------------------------------//
// Check that a void absorption reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory, 
                   createVoidAbsorptionReaction )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createVoidAbsorptionReaction(
                                                reaction );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.00000e-5 );

  // Test that the stored cross section is correct
  double cross_section = 
    reaction->getCrossSection( reaction->getThresholdEnergy() );

  TEST_EQUALITY_CONST( cross_section, 0.0);

  cross_section = reaction->getCrossSection( 1.00000e-4 );

  TEST_EQUALITY_CONST( cross_section, 0.0);

  cross_section = reaction->getCrossSection( 1.79008e-4 );

  TEST_EQUALITY_CONST( cross_section, 0.0);
  
  cross_section = reaction->getCrossSection( 1.00000e+5 );
  
  TEST_EQUALITY_CONST( cross_section, 0.0);

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_native_file_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_native_file",
		 &test_native_file_name,
		 "Test Native file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  {
    // Create the native data file container
    data_container.reset( new Data::EvaluatedElectronDataContainer( 
						     test_native_file_name ) );

    // Extract the common energy grid
    energy_grid.deepCopy( data_container->getElectronEnergyGrid() );

    // Create the hash-based grid searcher
    grid_searcher.reset( new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>( 
					     energy_grid,
					     energy_grid[0],
					     energy_grid[energy_grid.size()-1],
					     100 ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstElectroatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//

