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
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

MonteCarlo::BremsstrahlungAngularDistributionType photon_distribution_function;
std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container;
Teuchos::ArrayRCP<double> energy_grid;
Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher;
std::shared_ptr<MonteCarlo::ElectroatomicReaction> reaction;

//---------------------------------------------------------------------------//
// LinLinLog Tests.
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
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section =
    reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 2.48924e9 + 0.0, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458e8 + 0.0, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 8.83051e-2 + 2.1116099116949e6, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an cutoff elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createCutoffElasticReaction )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createCutoffElasticReaction(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section =
    reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 2.48924e9, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 8.83051e-2, 1e-12 );

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
  double energy = 1e1;
  double cross_section =
    reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 3.722e5, 1e-12 );

  energy = 1e2;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 2.0561378e6, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 2.1116099116949e6, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an moment preserving elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createMomentPreservingElasticReaction )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section =
    reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 1.10632944155859e8, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 1.73737676297259e8, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 2.20377030499672E-03, 1e-12 );

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
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double cross_section = reaction->getCrossSection( 1.0e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 8.75755e6, 1e-12 );

  cross_section = reaction->getCrossSection( 4.0e-4 );
  TEST_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.57861e6, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell reactions can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createSubshellElectroelectricReactions )
{
  std::vector<std::shared_ptr<MonteCarlo::ElectroatomicReaction> > reactions;

  MonteCarlo::ElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reactions,
                               true );

  TEST_EQUALITY_CONST( reactions.size(), 24 );

  // Test the first shell's reaction properties
  TEST_EQUALITY_CONST(
              reactions.front()->getReactionType(),
              MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.front()->getThresholdEnergy(),
                       8.82899999999999935e-2 );

  // Test the first shell's stored cross section is correct
  double cross_section = reactions.front()->getCrossSection( 8.829e-2 );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.0e-1 );
  TEST_FLOATING_EQUALITY( cross_section, 9.2835e-1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.58489e2 );
  TEST_FLOATING_EQUALITY( cross_section, 2.788860e1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.0e5 );
  TEST_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );

  // Check the last shell's reaction properties
  TEST_EQUALITY_CONST(
          reactions.back()->getReactionType(),
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.back()->getThresholdEnergy(), 1.0e-5 );

  cross_section = reactions.back()->getCrossSection( 1.0e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0 );
  TEST_FLOATING_EQUALITY( cross_section, 2.0335e5, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0e5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
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
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );

  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4.0e1 );

  TEST_FLOATING_EQUALITY( cross_section, 1.405050e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e5 );

  TEST_EQUALITY_CONST( cross_section, 1.95417e3 );

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
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );

  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4.0e1 );

  TEST_FLOATING_EQUALITY( cross_section, 1.405050e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e5 );

  TEST_EQUALITY_CONST( cross_section, 1.95417e3 );

  // Clear the reaction
  reaction.reset();
}


//---------------------------------------------------------------------------//
// LinLinLog Tests.
//---------------------------------------------------------------------------//
// Check that an analog elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createAnalogElasticReaction_lin )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createAnalogElasticReaction(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                false );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section =
    reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 2.48924e9 + 0.0, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458e8 + 0.0, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 8.83051e-2 + 2.1116099116949e6, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an cutoff elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createCutoffElasticReaction_lin )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createCutoffElasticReaction<Utility::LinLinLin>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section =
    reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 2.48924e9, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 8.83051e-2, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an moment preserving elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createMomentPreservingElasticReaction_lin )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<Utility::LinLinLin>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.10632944155859e8, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.73737676297259e8, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.20377030499672E-03, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell reactions can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createSubshellElectroelectricReactions_lin )
{
  std::vector<std::shared_ptr<MonteCarlo::ElectroatomicReaction> > reactions;

  MonteCarlo::ElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<MonteCarlo::ElectroatomicReaction,Utility::LinLinLin>(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reactions,
                               false );

  TEST_EQUALITY_CONST( reactions.size(), 24 );

  // Test the first shell's reaction properties
  TEST_EQUALITY_CONST(
              reactions.front()->getReactionType(),
              MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.front()->getThresholdEnergy(),
                       8.82899999999999935e-2 );

  // Test the first shell's stored cross section is correct
  double cross_section = reactions.front()->getCrossSection( 8.829e-2 );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.0e-1 );
  TEST_FLOATING_EQUALITY( cross_section, 9.2835e-1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.58489e2 );
  TEST_FLOATING_EQUALITY( cross_section, 2.788860e1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.0e5 );
  TEST_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );

  // Check the last shell's reaction properties
  TEST_EQUALITY_CONST(
          reactions.back()->getReactionType(),
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.back()->getThresholdEnergy(), 1.0e-5 );

  cross_section = reactions.back()->getCrossSection( 1.0e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0 );
  TEST_FLOATING_EQUALITY( cross_section, 2.0335e5, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0e5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a basic (dipole distribution) bremsstrahlung reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createBremsstrahlungReaction_dipole_lin )
{
  photon_distribution_function = MonteCarlo::DIPOLE_DISTRIBUTION;

  MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction<MonteCarlo::ElectroatomicReaction,Utility::LinLinLin>(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reaction,
                               photon_distribution_function,
                               true );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4.0e1 );
  TEST_FLOATING_EQUALITY( cross_section, 1.405050e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e5 );
  TEST_EQUALITY_CONST( cross_section, 1.95417e3 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
/* Check that a electroatom with detailed 2BS photon angular distribution
 * data can be created
 */
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createBremsstrahlungReaction_2bs_lin )
{
  photon_distribution_function = MonteCarlo::TWOBS_DISTRIBUTION;

  MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction<MonteCarlo::ElectroatomicReaction,Utility::LinLinLin>(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reaction,
                               photon_distribution_function,
                               false );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4.0e1 );
  TEST_FLOATING_EQUALITY( cross_section, 1.40505e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e5 );
  TEST_EQUALITY_CONST( cross_section, 1.95417e3 );

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
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );
  TEST_EQUALITY_CONST( cross_section, 0.0);

  cross_section = reaction->getCrossSection( 1.0e-4 );
  TEST_EQUALITY_CONST( cross_section, 0.0);

  cross_section = reaction->getCrossSection( 1.79008e-4 );
  TEST_EQUALITY_CONST( cross_section, 0.0);

  cross_section = reaction->getCrossSection( 1.0e5 );
  TEST_EQUALITY_CONST( cross_section, 0.0);

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the native data file container
  data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
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

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//

