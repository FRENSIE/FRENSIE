//---------------------------------------------------------------------------//
//!
//! \file   tstAbsorptionElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Absorption electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AbsorptionElectroatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ElectroatomicReaction> absorption_reaction;

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
TEUCHOS_UNIT_TEST( AbsorptionElectroatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( absorption_reaction->getReactionType(),
                       MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( AbsorptionElectroatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( absorption_reaction->getThresholdEnergy(),
                       1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( AbsorptionElectroatomicReaction,
                   getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST(
        absorption_reaction->getNumberOfEmittedElectrons( 1e-3 ),
        0u );

  TEST_EQUALITY_CONST(
        absorption_reaction->getNumberOfEmittedElectrons( 20.0 ),
        0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( AbsorptionElectroatomicReaction,
                   getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST(
        absorption_reaction->getNumberOfEmittedPhotons( 1e-3 ),
        0u );

  TEST_EQUALITY_CONST(
        absorption_reaction->getNumberOfEmittedPhotons( 20.0 ),
        0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( AbsorptionElectroatomicReaction, getCrossSection )
{
  double cross_section =
    absorption_reaction->getCrossSection( 4.000000000000E-04 );

  TEST_FLOATING_EQUALITY( cross_section, 1.278128947846E+09, 1e-12 );

  cross_section =
    absorption_reaction->getCrossSection( 9.000000000000E-05 );

  TEST_FLOATING_EQUALITY( cross_section, 2.411603154884E+09, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction can be simulated
TEUCHOS_UNIT_TEST( AbsorptionElectroatomicReaction, react )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  absorption_reaction->react( electron, bank, shell_of_interaction );

  TEST_ASSERT( electron.isGone() );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
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
  {
    // Create a file handler and data extractor
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
         new Data::ACEFileHandler( test_ace_file_name,
                                   test_ace_table_name,
                                   1u ) );
    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
        new Data::XSSEPRDataExtractor(
              ace_file_handler->getTableNXSArray(),
              ace_file_handler->getTableJXSArray(),
              ace_file_handler->getTableXSSArray() ) );

    // Extract the energy grid and cross section
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );

    Teuchos::ArrayView<const double> raw_total_cross_section =
      xss_data_extractor->extractElectronTotalCrossSection();

    Teuchos::ArrayView<const double>::iterator start =
      std::find_if( raw_total_cross_section.begin(),
                    raw_total_cross_section.end(),
                    notEqualZero );

    Teuchos::ArrayRCP<double> total_cross_section;
    total_cross_section.assign( start, raw_total_cross_section.end() );

    unsigned total_threshold_index =
      energy_grid.size() - total_cross_section.size();

    // Create the total reaction
    absorption_reaction.reset(
       new MonteCarlo::AbsorptionElectroatomicReaction<Utility::LinLin>(
              energy_grid,
              total_cross_section,
              total_threshold_index,
              MonteCarlo::TOTAL_ELECTROATOMIC_REACTION ) );
  }
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAbsorptionElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
