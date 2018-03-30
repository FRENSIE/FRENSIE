//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationPositronatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Atomic Excitation positron-atomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationPositronatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PositronatomicReaction> ace_excitation_reaction;

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
TEUCHOS_UNIT_TEST( AtomicExcitationPositronatomicReaction, getReactionType_ace )
{
  TEST_EQUALITY_CONST( ace_excitation_reaction->getReactionType(),
		       MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( AtomicExcitationPositronatomicReaction, getThresholdEnergy_ace )
{
  TEST_EQUALITY_CONST( ace_excitation_reaction->getThresholdEnergy(),
                       1e-05 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( AtomicExcitationPositronatomicReaction, getNumberOfEmittedElectrons_ace )
{
  TEST_EQUALITY_CONST( ace_excitation_reaction->getNumberOfEmittedElectrons(1e-3),
		       0u );

  TEST_EQUALITY_CONST( ace_excitation_reaction->getNumberOfEmittedElectrons(20.0),
		       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( AtomicExcitationPositronatomicReaction, getNumberOfEmittedPhotons_ace )
{
  TEST_EQUALITY_CONST( ace_excitation_reaction->getNumberOfEmittedPhotons(1e-3),
		       0u );

  TEST_EQUALITY_CONST( ace_excitation_reaction->getNumberOfEmittedPhotons(20.0),
		       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( AtomicExcitationPositronatomicReaction, getCrossSection_ace )
{
  double cross_section =
    ace_excitation_reaction->getCrossSection( 9e-05 );

  TEST_FLOATING_EQUALITY( cross_section, 1.16042e+09, 1e-12 );

  cross_section =
    ace_excitation_reaction->getCrossSection( 4e-04 );

  TEST_FLOATING_EQUALITY( cross_section, 6.22682e+08, 1e-12 );

  cross_section =
    ace_excitation_reaction->getCrossSection( 2e-03 );

  TEST_FLOATING_EQUALITY( cross_section, 1.96517e+08, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation reaction can be simulated
TEUCHOS_UNIT_TEST( AtomicExcitationPositronatomicReaction, react_ace )
{
  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 1e-3 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  double final_energy = positron.getEnergy() - 9.32298e-6;

  ace_excitation_reaction->react( positron, bank, shell_of_interaction );

  TEST_FLOATING_EQUALITY( positron.getEnergy(), final_energy, 1e-12 );
  TEST_FLOATING_EQUALITY( positron.getZDirection(), 1.0, 1e-12 );
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

  Teuchos::ArrayView<const double> raw_excitation_cross_section =
    xss_data_extractor->extractExcitationCrossSection();

  Teuchos::ArrayView<const double>::iterator start =
    std::find_if( raw_excitation_cross_section.begin(),
                  raw_excitation_cross_section.end(),
                  notEqualZero );

  Teuchos::ArrayRCP<double> excitation_cross_section;
  excitation_cross_section.assign( start, raw_excitation_cross_section.end() );

  unsigned excitation_threshold_index =
    energy_grid.size() - excitation_cross_section.size();

  // Extract the atomic excitation information data block (EXCIT)
  Teuchos::ArrayView<const double> excit_block(
                  xss_data_extractor->extractEXCITBlock() );

  // Extract the number of tabulated energies
  int size = excit_block.size()/2;

  // Extract the energy grid for atomic excitation energy loss
  Teuchos::Array<double> excitation_energy_grid(excit_block(0,size));

  // Extract the energy loss for atomic excitation
  Teuchos::Array<double> excitation_energy_loss(excit_block(size,size));

  // Create the energy loss distributions
  std::shared_ptr<Utility::OneDDistribution> energy_loss_function;

  energy_loss_function.reset(
  new Utility::TabularDistribution<Utility::LinLin>( excitation_energy_grid,
                                                     excitation_energy_loss ) );

  std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution>
                      excitation_energy_loss_distribution;

  excitation_energy_loss_distribution.reset(
    new MonteCarlo::AtomicExcitationElectronScatteringDistribution(
                      energy_loss_function ) );

  // Create the reaction
  ace_excitation_reaction.reset(
    new MonteCarlo::AtomicExcitationPositronatomicReaction<Utility::LinLin>(
          energy_grid,
          excitation_cross_section,
          excitation_threshold_index,
          excitation_energy_loss_distribution ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAtomicExcitationPositronatomicReaction.cpp
//---------------------------------------------------------------------------//