//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  Atomic Excitation electroatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ElectroatomicReaction> ace_excitation_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( AtomicExcitationElectroatomicReaction, getReactionType_ace )
{
  FRENSIE_CHECK_EQUAL( ace_excitation_reaction->getReactionType(),
		       MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( AtomicExcitationElectroatomicReaction, getThresholdEnergy_ace )
{
  FRENSIE_CHECK_EQUAL( ace_excitation_reaction->getThresholdEnergy(),
                       1.000000000000E-05 );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( AtomicExcitationElectroatomicReaction, getNumberOfEmittedElectrons_ace )
{
  FRENSIE_CHECK_EQUAL( ace_excitation_reaction->getNumberOfEmittedElectrons(1e-3),
		       1u );

  FRENSIE_CHECK_EQUAL( ace_excitation_reaction->getNumberOfEmittedElectrons(20.0),
		       1u );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( AtomicExcitationElectroatomicReaction, getNumberOfEmittedPhotons_ace )
{
  FRENSIE_CHECK_EQUAL( ace_excitation_reaction->getNumberOfEmittedPhotons(1e-3),
		       0u );

  FRENSIE_CHECK_EQUAL( ace_excitation_reaction->getNumberOfEmittedPhotons(20.0),
		       0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( AtomicExcitationElectroatomicReaction, getNumberOfEmittedPositrons_ace )
{
  FRENSIE_CHECK_EQUAL( ace_excitation_reaction->getNumberOfEmittedPositrons(1e-3),
		       0u );

  FRENSIE_CHECK_EQUAL( ace_excitation_reaction->getNumberOfEmittedPositrons(20.0),
		       0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( AtomicExcitationElectroatomicReaction, getCrossSection_ace )
{
  double cross_section =
    ace_excitation_reaction->getCrossSection( 9.000000000000E-05 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.160420000000E+09, 1e-12 );

  cross_section =
    ace_excitation_reaction->getCrossSection( 4.000000000000E-04 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.226820000000E+08, 1e-12 );

  cross_section =
    ace_excitation_reaction->getCrossSection( 2.000000000000E-03 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.965170000000E+08, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation reaction can be simulated
FRENSIE_UNIT_TEST( AtomicExcitationElectroatomicReaction, react_ace )
{
  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  double final_energy = electron.getEnergy() - 9.32298e-6;

  ace_excitation_reaction->react( electron, bank, shell_of_interaction );

  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), final_energy, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );
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

  Utility::ArrayView<const double> raw_excitation_cross_section =
    xss_data_extractor->extractExcitationCrossSection();

  Utility::ArrayView<const double>::iterator start =
    std::find_if( raw_excitation_cross_section.begin(),
                  raw_excitation_cross_section.end(),
                  []( const double element ){ return element != 0.0; } );

  std::shared_ptr<const std::vector<double> > excitation_cross_section(
        new std::vector<double>( start, raw_excitation_cross_section.end() ) );

  size_t excitation_threshold_index =
    energy_grid->size() - excitation_cross_section->size();

  // Extract the atomic excitation information data block (EXCIT)
  Utility::ArrayView<const double> excit_block(
                  xss_data_extractor->extractEXCITBlock() );

  // Extract the number of tabulated energies
  int size = excit_block.size()/2;

  // Extract the energy grid for atomic excitation energy loss
  std::vector<double> excitation_energy_grid(excit_block(0,size));

  // Extract the energy loss for atomic excitation
  std::vector<double> excitation_energy_loss(excit_block(size,size));

  // Create the energy loss distributions
  std::shared_ptr<Utility::UnivariateDistribution> energy_loss_function;

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
    new MonteCarlo::AtomicExcitationElectroatomicReaction<Utility::LinLin>(
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

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAtomicExcitationElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
