//---------------------------------------------------------------------------//
//!
//! \file   tstAbsorptionElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Absorption electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AbsorptionElectroatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ElectroatomicReaction> absorption_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( AbsorptionElectroatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( absorption_reaction->getReactionType(),
                       MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( AbsorptionElectroatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( absorption_reaction->getThresholdEnergy(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( AbsorptionElectroatomicReaction,
                   getNumberOfEmittedElectrons )
{
  FRENSIE_CHECK_EQUAL(
        absorption_reaction->getNumberOfEmittedElectrons( 1e-3 ),
        0u );

  FRENSIE_CHECK_EQUAL(
        absorption_reaction->getNumberOfEmittedElectrons( 20.0 ),
        0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( AbsorptionElectroatomicReaction,
                   getNumberOfEmittedPhotons )
{
  FRENSIE_CHECK_EQUAL(
        absorption_reaction->getNumberOfEmittedPhotons( 1e-3 ),
        0u );

  FRENSIE_CHECK_EQUAL(
        absorption_reaction->getNumberOfEmittedPhotons( 20.0 ),
        0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( AbsorptionElectroatomicReaction,
                   getNumberOfEmittedPositrons )
{
  FRENSIE_CHECK_EQUAL(
        absorption_reaction->getNumberOfEmittedPositrons( 1e-3 ),
        0u );

  FRENSIE_CHECK_EQUAL(
        absorption_reaction->getNumberOfEmittedPositrons( 20.0 ),
        0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( AbsorptionElectroatomicReaction, getCrossSection )
{
  double cross_section =
    absorption_reaction->getCrossSection( 4.000000000000E-04 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.278128947846E+09, 1e-12 );

  cross_section =
    absorption_reaction->getCrossSection( 9.000000000000E-05 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.411603154884E+09, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction can be simulated
FRENSIE_UNIT_TEST( AbsorptionElectroatomicReaction, react )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  absorption_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK( electron.isGone() );
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
  {
    // Create a file handler and data extractor
    std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
         new Data::ACEFileHandler( test_ace_file_name,
                                   "82000.12p",
                                   test_ace_file_start_line ) );
    
    std::unique_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
        new Data::XSSEPRDataExtractor(
              ace_file_handler->getTableNXSArray(),
              ace_file_handler->getTableJXSArray(),
              ace_file_handler->getTableXSSArray() ) );

    // Extract the energy grid and cross section
    std::shared_ptr<const std::vector<double> > energy_grid(
       new std::vector<double>( xss_data_extractor->extractElectronEnergyGrid() ) );

    Utility::ArrayView<const double> raw_total_cross_section =
      xss_data_extractor->extractElectronTotalCrossSection();

    Utility::ArrayView<const double>::iterator start =
      std::find_if( raw_total_cross_section.begin(),
                    raw_total_cross_section.end(),
                    []( const double element ){ return element != 0.0; } );

    std::shared_ptr<const std::vector<double> > total_cross_section(
             new std::vector<double>( start, raw_total_cross_section.end() ) );

    size_t total_threshold_index =
      energy_grid->size() - total_cross_section->size();

    // Create the total reaction
    absorption_reaction.reset(
       new MonteCarlo::AbsorptionElectroatomicReaction<Utility::LinLin>(
              energy_grid,
              total_cross_section,
              total_threshold_index,
              MonteCarlo::TOTAL_ELECTROATOMIC_REACTION ) );
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAbsorptionElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
