//---------------------------------------------------------------------------//
//!
//! \file   tstPhotoatomicReactionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Photoatomic reaction factory using ACE data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReactionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor;
std::shared_ptr<std::vector<double> > energy_grid;
std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher;
std::shared_ptr<const MonteCarlo::PhotoatomicReaction> reaction;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an incoherent reaction without Doppler data can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionACEFactory,
		   createIncoherentReaction_no_doppler )
{
  MonteCarlo::PhotoatomicReactionACEFactory::createIncoherentReaction(
					      *xss_data_extractor,
					      energy_grid,
					      grid_searcher,
					      reaction,
					      MonteCarlo::WH_INCOHERENT_MODEL,
					      3.0 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
		       MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(),
		       exp( -1.381551055796E+01 ) );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection(exp( -1.381551055796E+01 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section = reaction->getCrossSection(exp( -1.364234411496E+01 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section = reaction->getCrossSection(exp( 1.151292546497E+01 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -6.573285045032E+00 ), 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an incoherent reaction with Doppler data can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionACEFactory,
		   createIncoherentReaction_doppler )
{
  MonteCarlo::PhotoatomicReactionACEFactory::createIncoherentReaction(
		 *xss_data_extractor,
		 energy_grid,
		 grid_searcher,
		 reaction,
		 MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
		 3.0 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
		       MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(),
		       exp( -1.381551055796E+01 ) );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection(exp( -1.381551055796E+01 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section = reaction->getCrossSection(exp( -1.364234411496E+01 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section = reaction->getCrossSection(exp( 1.151292546497E+01 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -6.573285045032E+00 ), 1e-12 );

  // Test that Doppler broadening is done
  Data::SubshellType shell_of_interaction;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  reaction->react( photon, bank, shell_of_interaction );

  FRENSIE_CHECK( shell_of_interaction != Data::UNKNOWN_SUBSHELL );
  FRENSIE_CHECK( shell_of_interaction != Data::INVALID_SUBSHELL );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a coherent reaction can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionACEFactory, createCoherentReaction )
{
  MonteCarlo::PhotoatomicReactionACEFactory::createCoherentReaction(
							   *xss_data_extractor,
							   energy_grid,
							   grid_searcher,
							   reaction );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
		       MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(),
		       exp( -1.381551055796E+01 ) );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( exp(-1.381551055796E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -5.071403810640E+00 ), 1e-12 );

  cross_section = reaction->getCrossSection( exp( -1.364234411496E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -4.284251858121E+00 ), 1e-12 );

  cross_section = reaction->getCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -2.309498238246E+01 ), 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a basic pair production reaction can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionACEFactory,
		   createPairProductionReaction_basic )
{
  MonteCarlo::PhotoatomicReactionACEFactory::createPairProductionReaction(
							   *xss_data_extractor,
							   energy_grid,
							   grid_searcher,
							   reaction,
							   false );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
		       MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(),
		       exp( 2.480967890857E-02 ) );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.431923975437E+01 ), 1e-12 );

  cross_section = reaction->getCrossSection( exp( 2.625237114407E-02 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.315996659940E+01 ), 1e-12 );

  cross_section = reaction->getCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 3.718032834377E+00 ), 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a detailed pair production reaction can be created
// FRENSIE_UNIT_TEST( PhotoatomicReactionACEFactory,
// 		   createPairProductionReaction_detailed )
// {

// }

//---------------------------------------------------------------------------//
// Check that the total photoelectric reaction can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionACEFactory,
		   createTotalPhotoelectricReaction )
{
  MonteCarlo::PhotoatomicReactionACEFactory::createTotalPhotoelectricReaction(
							   *xss_data_extractor,
							   energy_grid,
							   grid_searcher,
							   reaction );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
		       MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(),
		       exp( -1.214969212306E+01 ) );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section = reaction->getCrossSection( exp( -1.214969212306E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = reaction->getCrossSection( exp( -1.214720768866E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = reaction->getCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that the subshell photoelectric reactions can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionACEFactory,
		   createSubshellPhotoelectricReactions )
{
  std::vector<std::shared_ptr<const MonteCarlo::PhotoatomicReaction> > reactions;

  MonteCarlo::PhotoatomicReactionACEFactory::createSubshellPhotoelectricReactions(
							   *xss_data_extractor,
							   energy_grid,
							   grid_searcher,
							   reactions );

  FRENSIE_CHECK_EQUAL( reactions.size(), 24 );

  // Test the first shell's reaction properties
  FRENSIE_CHECK_EQUAL(
		   reactions.front()->getReactionType(),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions.front()->getThresholdEnergy(),
		       exp( -2.427128314806E+00 ) );

  // Test the first shell's stored cross section is correct
  double cross_section =
    reactions.front()->getCrossSection( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section =
    reactions.front()->getCrossSection( exp( -2.427128314806E+00 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 7.578565567350E+00 ), 1e-12 );

  cross_section =
    reactions.front()->getCrossSection( exp( -2.406201463890E+00 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 7.527375050980E+00 ), 1e-12 );

  cross_section =
    reactions.front()->getCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.135387253512E+01 ), 1e-12 );

  // Check the last shell's reaction properties
  FRENSIE_CHECK_EQUAL(
		  reactions.back()->getReactionType(),
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions.back()->getThresholdEnergy(),
		       exp( -1.214969212306E+01 ) );

  cross_section =
    reactions.back()->getCrossSection( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section =
    reactions.back()->getCrossSection( exp( -1.214969212306E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section =
    reactions.back()->getCrossSection( exp( -1.214665892126E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.718675283782E+01 ), 1e-12 );

  cross_section =
    reactions.back()->getCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -2.364731020721E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a heating reaction can be created
FRENSIE_UNIT_TEST( PhotoatomicReactionACEFactory, createHeatingReaction )
{
  MonteCarlo::PhotoatomicReactionACEFactory::createHeatingReaction(
							   *xss_data_extractor,
							   energy_grid,
							   grid_searcher,
							   reaction );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
		       MonteCarlo::HEATING_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(),
		       exp( -1.381551055796E+01 ) );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.916958825662E-07, 1e-12 );

  cross_section = reaction->getCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.999864243970E+04, 1e-12 );

  // Clear the reaction
  reaction.reset();
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
  {
    // Create a file handler and data extractor
    std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                        new Data::ACEFileHandler( test_ace_file_name,
                                                  "82000.12p",
						  test_ace_file_start_line ) );
    
    xss_data_extractor.reset( new Data::XSSEPRDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

    // Extract the common energy grid
    energy_grid.reset( new std::vector<double>( xss_data_extractor->extractPhotonEnergyGrid() ) );

    // Create the hash-based grid searcher
    grid_searcher.reset( new Utility::StandardHashBasedGridSearcher<std::vector<double>,true>(
					     energy_grid,
					     energy_grid->front(),
					     energy_grid->back(),
					     100 ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPhotoatomicReactionACEFactory.cpp
//---------------------------------------------------------------------------//
