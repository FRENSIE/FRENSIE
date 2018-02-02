//---------------------------------------------------------------------------//
//!
//! \file   tstVoidElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Void electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_VoidElectroatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::VoidElectroatomicReaction<Utility::LinLin> >
  void_reaction;

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
TEUCHOS_UNIT_TEST( VoidElectroatomicReaction, getReactionType )
{
  TEST_EQUALITY_CONST( void_reaction->getReactionType(),
		       MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( VoidElectroatomicReaction, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( void_reaction->getThresholdEnergy(),
                       1E-05 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( VoidElectroatomicReaction, getNumberOfEmittedElectrons )
{
  TEST_EQUALITY_CONST( void_reaction->getNumberOfEmittedElectrons(1e-5), 0u );
  TEST_EQUALITY_CONST( void_reaction->getNumberOfEmittedElectrons(20.0), 0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( VoidElectroatomicReaction, getNumberOfEmittedPhotons )
{
  TEST_EQUALITY_CONST( void_reaction->getNumberOfEmittedPhotons(1e-5), 0u );
  TEST_EQUALITY_CONST( void_reaction->getNumberOfEmittedPhotons(20.0), 0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( VoidElectroatomicReaction, getCrossSection )
{
  double cross_section =
    void_reaction->getCrossSection( 9E-05 );

  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838E+03, 1e-12 );

  cross_section =
    void_reaction->getCrossSection( 4E-04 );

  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439E+03, 1e-12 );

  cross_section =
    void_reaction->getCrossSection( 2E-03 );

  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255E+03, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the basic dipole bremsstrahlung reaction can be simulated
TEUCHOS_UNIT_TEST( VoidElectroatomicReaction, react )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 20 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  void_reaction->react( electron, bank, shell_of_interaction );

  TEST_ASSERT( electron.getEnergy() == 20.0 );
  TEST_EQUALITY_CONST( electron.getZDirection(), 1.0 );
  TEST_ASSERT( bank.isEmpty() );
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
  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
     new Data::ACEFileHandler( test_ace_file_name,
                               test_ace_table_name,
                               1u ) );
  Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
    new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                   ace_file_handler->getTableJXSArray(),
                                   ace_file_handler->getTableXSSArray() ) );

  // Extract the energy grid and cross section
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );

  Teuchos::ArrayView<const double> raw_bremsstrahlung_cross_section =
    xss_data_extractor->extractBremsstrahlungCrossSection();

  Teuchos::ArrayView<const double>::iterator start =
    std::find_if( raw_bremsstrahlung_cross_section.begin(),
                  raw_bremsstrahlung_cross_section.end(),
                  notEqualZero );

  Teuchos::ArrayRCP<double> bremsstrahlung_cross_section;
  bremsstrahlung_cross_section.assign( start, raw_bremsstrahlung_cross_section.end() );

  unsigned bremsstrahlung_threshold_index =
    energy_grid.size() - bremsstrahlung_cross_section.size();

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

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstVoidElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
