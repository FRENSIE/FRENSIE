//---------------------------------------------------------------------------//
//!
//! \file   tstPhotoelectricPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Photoelectric photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_PhotoelectricPhotoatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PhotoatomicReaction> ace_photoelectric_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( PhotoelectricPhotoatomicReaction, getReactionType_ace )
{
  FRENSIE_CHECK_EQUAL( ace_photoelectric_reaction->getReactionType(),
		       MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( PhotoelectricPhotoatomicReaction, getThresholdEnergy_ace )
{
  FRENSIE_CHECK_EQUAL( ace_photoelectric_reaction->getThresholdEnergy(),
		       exp( -1.214969212306E+01 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( PhotoelectricPhotoatomicReaction,
		   getNumberOfEmittedPhotons_ace )
{
  FRENSIE_CHECK_EQUAL(
		 ace_photoelectric_reaction->getNumberOfEmittedPhotons( 1e-3 ),
		 0u );

  FRENSIE_CHECK_EQUAL(
		 ace_photoelectric_reaction->getNumberOfEmittedPhotons( 20.0 ),
		 0u );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( PhotoelectricPhotoatomicReaction,
		   getNumberOfEmittedElectrons_ace )
{
  FRENSIE_CHECK_EQUAL(
	       ace_photoelectric_reaction->getNumberOfEmittedElectrons( 1e-3 ),
               0u );

  FRENSIE_CHECK_EQUAL(
	       ace_photoelectric_reaction->getNumberOfEmittedElectrons( 20.0 ),
               0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( PhotoelectricPhotoatomicReaction,
		   getNumberOfEmittedPositrons_ace )
{
  FRENSIE_CHECK_EQUAL(
	       ace_photoelectric_reaction->getNumberOfEmittedPositrons( 1e-3 ),
               0u );

  FRENSIE_CHECK_EQUAL(
	       ace_photoelectric_reaction->getNumberOfEmittedPositrons( 20.0 ),
               0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( PhotoelectricPhotoatomicReaction, getCrossSection_ace )
{
  double cross_section =
    ace_photoelectric_reaction->getCrossSection( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section =
    ace_photoelectric_reaction->getCrossSection( exp( -1.214969212306E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section =
    ace_photoelectric_reaction->getCrossSection( exp( -1.214720768866E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section =
    ace_photoelectric_reaction->getCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric effect can be simulated
FRENSIE_UNIT_TEST( PhotoelectricPhotoatomicReaction, react_ace )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  ace_photoelectric_reaction->react( photon,
				     bank,
				     shell_of_interaction );

  FRENSIE_CHECK( photon.isGone() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Custom Setup
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
  std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                        new Data::ACEFileHandler( test_ace_file_name,
                                                  "82000.12p",
						  test_ace_file_start_line ) );
  
  std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  // Extract the energy grid and cross section
  std::shared_ptr<std::vector<double> > energy_grid(
    new std::vector<double>( xss_data_extractor->extractPhotonEnergyGrid() ) );

  Utility::ArrayView<const double> raw_pe_cross_section =
    xss_data_extractor->extractPhotoelectricCrossSection();

  Utility::ArrayView<const double>::iterator start =
    std::find_if( raw_pe_cross_section.begin(),
		  raw_pe_cross_section.end(),
		  [](double cs){ return cs != 0.0; } );

  std::shared_ptr<std::vector<double> > pe_cross_section(
                new std::vector<double>( start, raw_pe_cross_section.end() ) );

  size_t pe_threshold_index =
    energy_grid->size() - pe_cross_section->size();

  // Create the photoelectric reaction
  ace_photoelectric_reaction.reset(
	     new MonteCarlo::PhotoelectricPhotoatomicReaction<Utility::LogLog>(
						        energy_grid,
							pe_cross_section,
							pe_threshold_index ) );

  // Clear the setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPhotoelectricPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//

