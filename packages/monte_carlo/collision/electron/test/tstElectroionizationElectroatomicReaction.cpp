//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Electroionization electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionACEFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::ElectroatomicReaction> ace_total_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( ElectroionizationElectroatomicReaction, getReactionType_ace )
{
  FRENSIE_CHECK_EQUAL( ace_total_reaction->getReactionType(),
                       MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( ElectroionizationElectroatomicReaction, getThresholdEnergy_ace )
{
  FRENSIE_CHECK_EQUAL( ace_total_reaction->getThresholdEnergy(), 1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( ElectroionizationElectroatomicReaction, getNumberOfEmittedElectrons_ace )
{
  FRENSIE_CHECK_EQUAL( ace_total_reaction->getNumberOfEmittedElectrons(1e-5),
                       2u );

  FRENSIE_CHECK_EQUAL( ace_total_reaction->getNumberOfEmittedElectrons(20.0),
                       2u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( ElectroionizationElectroatomicReaction, getNumberOfEmittedPhotons_ace )
{
  FRENSIE_CHECK_EQUAL( ace_total_reaction->getNumberOfEmittedPhotons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( ace_total_reaction->getNumberOfEmittedPhotons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( ElectroionizationElectroatomicReaction, getNumberOfEmittedPositrons_ace )
{
  FRENSIE_CHECK_EQUAL( ace_total_reaction->getNumberOfEmittedPositrons(1e-3),
                       0u );

  FRENSIE_CHECK_EQUAL( ace_total_reaction->getNumberOfEmittedPositrons(20.0),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( ElectroionizationElectroatomicReaction, getCrossSection_ace )
{
  // Test the total cross section is correct
  double cross_section = ace_total_reaction->getCrossSection( 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.310577E+08, 1e-12 );

  cross_section = ace_total_reaction->getCrossSection( 8.9754e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.59749583408E+06, 1e-12 );

  cross_section = ace_total_reaction->getCrossSection( 1e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.345696097519E+06, 1e-12 );

  cross_section = ace_total_reaction->getCrossSection( 1.58489e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.510192579238E+06, 1e-12 );

  cross_section = ace_total_reaction->getCrossSection( 1e+5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.2648388779E+06, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the reaction can be simulated
FRENSIE_UNIT_TEST( ElectroionizationElectroatomicReaction, react_ace )
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

  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 8.7092959303108897e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 9.6452810069913897e-01, 1e-12 );
  FRENSIE_CHECK( !bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::K_SUBSHELL );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 4.0780406968911040e-02, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 2.7854463307465377e-01, 1e-12 );
  FRENSIE_CHECK( bank.size() == 1 );

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

  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 9.9999014523848417e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 9.9999750949127741e-01, 1e-12 );
  FRENSIE_CHECK( !bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::P3_SUBSHELL );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 4.5647615157536130e-06, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 3.0052003679701955e-03, 1e-12 );
  FRENSIE_CHECK( bank.size() == 1 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Check that the hydrogen differential cross section can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationElectroatomicReaction,
                   getDifferentialCrossSection_ace )
{

  FRENSIE_CHECK_THROW( ace_total_reaction->getDifferentialCrossSection( 1.0, 0.5 ),
                       std::logic_error );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name;
unsigned test_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file_start_line",
                                        test_ace_file_start_line, 1,
                                        "Test ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create ACE distribution
  {
  // Create a file handler and data extractor
  std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                        new Data::ACEFileHandler( test_ace_file_name,
                                                  "82000.14p",
                                                  test_ace_file_start_line ) );
  
  std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
                                      ace_file_handler->getTableNXSArray(),
                                      ace_file_handler->getTableJXSArray(),
                                      ace_file_handler->getTableXSSArray() ) );

  // Extract the energy grid and cross section
  std::shared_ptr<const std::vector<double> > energy_grid(
     new std::vector<double>( xss_data_extractor->extractElectronEnergyGrid() ) );

  // Create the hash-based grid searcher
  std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher(
       new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                energy_grid,
                energy_grid->front(),
                energy_grid->back(),
                energy_grid->size()/10 + 1 ) );

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

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroionizationElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
