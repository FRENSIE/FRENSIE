//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Electroionization electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionACEFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ElectroatomicReaction> ace_total_reaction;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
TEUCHOS_UNIT_TEST( ElectroionizationElectroatomicReaction, getReactionType_ace )
{
  TEST_EQUALITY_CONST( ace_total_reaction->getReactionType(),
                       MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( ElectroionizationElectroatomicReaction, getThresholdEnergy_ace )
{
  TEST_EQUALITY_CONST( ace_total_reaction->getThresholdEnergy(), 1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( ElectroionizationElectroatomicReaction, getNumberOfEmittedElectrons_ace )
{
  TEST_EQUALITY_CONST( ace_total_reaction->getNumberOfEmittedElectrons(1e-5),
                       1u );

  TEST_EQUALITY_CONST( ace_total_reaction->getNumberOfEmittedElectrons(20.0),
                       1u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( ElectroionizationElectroatomicReaction, getNumberOfEmittedPhotons_ace )
{
  TEST_EQUALITY_CONST( ace_total_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  TEST_EQUALITY_CONST( ace_total_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( ElectroionizationElectroatomicReaction, getCrossSection_ace )
{
  // Test the total cross section is correct
  double cross_section = ace_total_reaction->getCrossSection( 1e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.310577E+08, 1e-12 );

  cross_section = ace_total_reaction->getCrossSection( 8.9754e-2 );
  TEST_FLOATING_EQUALITY( cross_section, 3.59749583408E+06, 1e-12 );

  cross_section = ace_total_reaction->getCrossSection( 1e-1 );
  TEST_FLOATING_EQUALITY( cross_section, 3.345696097519E+06, 1e-12 );

  cross_section = ace_total_reaction->getCrossSection( 1.58489e-1 );
  TEST_FLOATING_EQUALITY( cross_section, 2.510192579238E+06, 1e-12 );

  cross_section = ace_total_reaction->getCrossSection( 1e+5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.2648388779E+06, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the reaction can be simulated
TEUCHOS_UNIT_TEST( ElectroionizationElectroatomicReaction, react_ace )
{
  {
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0; // select the first subshell
  fake_stream[1] = 0.5; // select the first subshell

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_total_reaction->react( electron, bank, shell_of_interaction );

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 8.7092959303108897e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.6452810069913897e-01, 1e-12 );
  TEST_ASSERT( !bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::K_SUBSHELL );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 4.0780406968911040e-02, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 2.7854463307465377e-01, 1e-12 );
  TEST_ASSERT( bank.size() == 1 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 1.0-1e-15; // select the last subshell
  fake_stream[1] = 0.5; // select the last subshell

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_total_reaction->react( electron, bank, shell_of_interaction );

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 9.9999014523848417e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 9.9999750949127741e-01, 1e-12 );
  TEST_ASSERT( !bank.isEmpty() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::P3_SUBSHELL );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 4.5647615157536130e-06, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 3.0052003679701955e-03, 1e-12 );
  TEST_ASSERT( bank.size() == 1 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Check that the hydrogen differential cross section can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationElectroatomicReaction,
                   getDifferentialCrossSection_ace )
{

  TEST_THROW( ace_total_reaction->getDifferentialCrossSection( 1.0, 0.5 ),
              std::logic_error );
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
  // Create ACE distribution
  {
  // Create a file handler and data extractor
  std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                                 new Data::ACEFileHandler( test_ace_file_name,
                                                           test_ace_table_name,
                                                           1u ) );
  std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
                                      ace_file_handler->getTableNXSArray(),
                                      ace_file_handler->getTableJXSArray(),
                                      ace_file_handler->getTableXSSArray() ) );

  // Extract the energy grid and cross section
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );

  // Create the hash-based grid searcher
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
      new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
                energy_grid,
                energy_grid[0],
                energy_grid[energy_grid.size()-1],
                energy_grid.size()/10 + 1 ) );

  MonteCarlo::ElectroatomicReactionACEFactory::createTotalElectroionizationReaction(
        *xss_data_extractor,
        energy_grid,
        grid_searcher,
        ace_total_reaction );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroionizationElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
