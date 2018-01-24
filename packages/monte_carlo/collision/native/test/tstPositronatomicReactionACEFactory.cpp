//---------------------------------------------------------------------------//
//!
//! \file   tstPositronatomicReactionACEFactory.cpp
//! \author Luke Kersting
//! \brief  Positronatomic reaction factory using ACE data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReactionACEFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

MonteCarlo::BremsstrahlungAngularDistributionType photon_distribution_function;
Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor;
Teuchos::ArrayRCP<double> energy_grid;
Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher;
std::shared_ptr<MonteCarlo::PositronatomicReaction> reaction;
double min_electron_energy = 1e-5;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an elastic reaction can be created
TEUCHOS_UNIT_TEST( PositronatomicReactionACEFactory,
                   createCutoffElasticReaction )
{
  MonteCarlo::PositronatomicReactionACEFactory::createCutoffElasticReaction(
                *xss_data_extractor,
                energy_grid,
                grid_searcher,
                reaction );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section =
    reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 2.48924e+9, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458e+8, 1e-12 );

  energy = 1e+5;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 8.83051e-2, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an atomic excitation reaction can be created
TEUCHOS_UNIT_TEST( PositronatomicReactionACEFactory,
                   createAtomicExcitationReaction )
{
  MonteCarlo::PositronatomicReactionACEFactory::createAtomicExcitationReaction(
                *xss_data_extractor,
                energy_grid,
                grid_searcher,
                reaction,
                min_electron_energy );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( 1e-5 );

  TEST_FLOATING_EQUALITY( cross_section, 8.75755e+6, 1e-12 );

  cross_section = reaction->getCrossSection( 4e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 6.22682e+8, 1e-12 );

  cross_section = reaction->getCrossSection( 1e+5 );

  TEST_FLOATING_EQUALITY( cross_section, 1.57861e+6, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell reactions can be created
TEUCHOS_UNIT_TEST( PositronatomicReactionACEFactory,
                   createSubshellElectroionizationReactions )
{
  std::vector<std::shared_ptr<MonteCarlo::PositronatomicReaction> > reactions;

  MonteCarlo::PositronatomicReactionACEFactory::createSubshellPositronionizationReactions(
                *xss_data_extractor,
                energy_grid,
                grid_searcher,
                reactions,
                min_electron_energy );

  TEST_EQUALITY_CONST( reactions.size(), 24 );

  // Test the first shell's reaction properties
  TEST_EQUALITY_CONST(
            reactions.front()->getReactionType(),
            MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.front()->getThresholdEnergy(), 8.9754e-2 );

  // Test the first shell's stored cross section is correct
  double cross_section =
    reactions.front()->getCrossSection( 8.9754e-2 );

  TEST_FLOATING_EQUALITY( cross_section, 1.250673571307e-1, 1e-12 );

  cross_section =
    reactions.front()->getCrossSection( 1e-1 );

  TEST_FLOATING_EQUALITY( cross_section, 9.2835e-1, 1e-12 );

  cross_section =
    reactions.front()->getCrossSection( 1.58489e-1 );

  TEST_FLOATING_EQUALITY( cross_section, 3.51034535975, 1e-12 );

  cross_section =
    reactions.front()->getCrossSection( 1e+5 );

  TEST_FLOATING_EQUALITY( cross_section, 3.64919e+1, 1e-12 );

  // Check the last shell's reaction properties
  TEST_EQUALITY_CONST(
                  reactions.back()->getReactionType(),
                  MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.back()->getThresholdEnergy(), 1e-5 );

  cross_section =
    reactions.back()->getCrossSection( 1e-5 );

  TEST_FLOATING_EQUALITY( cross_section, 1.0653e+8, 1e-12 );

  cross_section =
    reactions.back()->getCrossSection( 2e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 1.123672769743e+8, 1e-12 );

  cross_section =
    reactions.back()->getCrossSection( 6.57156e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 4.612644761466e+7, 1e-12 );

  cross_section =
    reactions.back()->getCrossSection( 1e+5 );

  TEST_FLOATING_EQUALITY( cross_section, 1.82234e+5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a basic (dipole distribution) bremsstrahlung reaction can be created
TEUCHOS_UNIT_TEST( PositronatomicReactionACEFactory,
                   createBremsstrahlungReaction_dipole )
{
  photon_distribution_function = MonteCarlo::DIPOLE_DISTRIBUTION;

  MonteCarlo::PositronatomicReactionACEFactory::createBremsstrahlungReaction(
                *xss_data_extractor,
                energy_grid,
                grid_searcher,
                reaction,
                photon_distribution_function,
                min_electron_energy );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );

  TEST_FLOATING_EQUALITY( cross_section, 4.8698e+3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 7.363889022643e+3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.79008e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 8.026497035136e+3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e+5 );

  TEST_EQUALITY_CONST( cross_section, 1.95417e+3 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
/* Check that a electroatom with detailed 2BS photon angular distribution
 * data can be created
 */
TEUCHOS_UNIT_TEST( PositronatomicReactionACEFactory,
                   createBremsstrahlungReaction_2bs )
{
  photon_distribution_function = MonteCarlo::TWOBS_DISTRIBUTION;

  MonteCarlo::PositronatomicReactionACEFactory::createBremsstrahlungReaction(
                *xss_data_extractor,
                energy_grid,
                grid_searcher,
                reaction,
                photon_distribution_function,
                min_electron_energy );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );

  TEST_FLOATING_EQUALITY( cross_section, 4.8698e+3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 7.363889022643e+3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.79008e-4 );

  TEST_FLOATING_EQUALITY( cross_section, 8.026497035136e+3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e+5 );

  TEST_EQUALITY_CONST( cross_section, 1.95417e+3 );

  // Clear the reaction
  reaction.reset();
}



//---------------------------------------------------------------------------//
// Check that a void absorption reaction can be created
TEUCHOS_UNIT_TEST( PositronatomicReactionACEFactory,
                   createVoidAbsorptionReaction )
{
  MonteCarlo::PositronatomicReactionACEFactory::createVoidAbsorptionReaction(
                                                reaction );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );

  TEST_EQUALITY_CONST( cross_section, 0.0);

  cross_section = reaction->getCrossSection( 1e-4 );

  TEST_EQUALITY_CONST( cross_section, 0.0);

  cross_section = reaction->getCrossSection( 1.79008e-4 );

  TEST_EQUALITY_CONST( cross_section, 0.0);

  cross_section = reaction->getCrossSection( 1e+5 );

  TEST_EQUALITY_CONST( cross_section, 0.0);

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name, test_ace_table_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_ace_file",
                   &test_ace_file_name,
                   "Test ACE file name" );
  clp().setOption( "test_ace_table",
                   &test_ace_table_name,
                   "Test ACE table name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
        new Data::ACEFileHandler( test_ace_file_name,
                                  test_ace_table_name,
                                  1u ) );
  xss_data_extractor.reset(
        new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                       ace_file_handler->getTableJXSArray(),
                                       ace_file_handler->getTableXSSArray() ) );

  // Extract the common energy grid
  energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );

  // Create the hash-based grid searcher
  grid_searcher.reset( new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
                energy_grid,
                energy_grid[0],
                energy_grid[energy_grid.size()-1],
                100 ) );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPositronatomicReactionACEFactory.cpp
//---------------------------------------------------------------------------//