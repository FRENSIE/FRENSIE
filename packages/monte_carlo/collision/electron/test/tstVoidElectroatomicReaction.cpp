//---------------------------------------------------------------------------//
//!
//! \file   tstVoidElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Void electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_VoidElectroatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::VoidElectroatomicReaction<Utility::LinLin> >
  void_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( VoidElectroatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( void_reaction->getReactionType(),
		       MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( VoidElectroatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( void_reaction->getThresholdEnergy(),
                       1E-05 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( VoidElectroatomicReaction, getNumberOfEmittedElectrons )
{
  FRENSIE_CHECK_EQUAL( void_reaction->getNumberOfEmittedElectrons(1e-5), 0u );
  FRENSIE_CHECK_EQUAL( void_reaction->getNumberOfEmittedElectrons(20.0), 0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( VoidElectroatomicReaction, getNumberOfEmittedPhotons )
{
  FRENSIE_CHECK_EQUAL( void_reaction->getNumberOfEmittedPhotons(1e-5), 0u );
  FRENSIE_CHECK_EQUAL( void_reaction->getNumberOfEmittedPhotons(20.0), 0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( VoidElectroatomicReaction, getCrossSection )
{
  double cross_section =
    void_reaction->getCrossSection( 9E-05 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.249970966838E+03, 1e-12 );

  cross_section =
    void_reaction->getCrossSection( 4E-04 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.914234996439E+03, 1e-12 );

  cross_section =
    void_reaction->getCrossSection( 2E-03 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.258661418255E+03, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the basic dipole bremsstrahlung reaction can be simulated
FRENSIE_UNIT_TEST( VoidElectroatomicReaction, react )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 20 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  void_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK( electron.getEnergy() == 20.0 );
  FRENSIE_CHECK_EQUAL( electron.getZDirection(), 1.0 );
  FRENSIE_CHECK( bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
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
  // Create a file handler and data extractor
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
     new Data::ACEFileHandler( test_ace_file_name,
                               "82000.12p",
                               test_ace_file_start_line ) );
  
  std::unique_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
    new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                   ace_file_handler->getTableJXSArray(),
                                   ace_file_handler->getTableXSSArray() ) );

  // Extract the energy grid and cross section
  std::shared_ptr<const std::vector<double> > energy_grid(
     new std::vector<double>( xss_data_extractor->extractElectronEnergyGrid() ) );

  Utility::ArrayView<const double> raw_bremsstrahlung_cross_section =
    xss_data_extractor->extractBremsstrahlungCrossSection();

  Utility::ArrayView<const double>::iterator start =
    std::find_if( raw_bremsstrahlung_cross_section.begin(),
                  raw_bremsstrahlung_cross_section.end(),
                  []( const double element ){ return element != 0.0; } );

  std::shared_ptr<const std::vector<double> > bremsstrahlung_cross_section(
    new std::vector<double>( start, raw_bremsstrahlung_cross_section.end() ) );

  size_t bremsstrahlung_threshold_index =
    energy_grid->size() - bremsstrahlung_cross_section->size();

  // Create the reactions
  void_reaction.reset(
    new MonteCarlo::VoidElectroatomicReaction<Utility::LinLin>(
          energy_grid,
          bremsstrahlung_cross_section,
          bremsstrahlung_threshold_index ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstVoidElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
