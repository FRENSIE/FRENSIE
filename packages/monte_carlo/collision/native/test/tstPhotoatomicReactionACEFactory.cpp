//---------------------------------------------------------------------------//
//!
//! \file   tstPhotoatomicReactionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Photoatomic reaction factory using ACE data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReactionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor;
Teuchos::ArrayRCP<double> energy_grid;
Teuchos::RCP<MonteCarlo::PhotoatomicReaction> reaction;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an incoherent reaction without Doppler data can be created
TEUCHOS_UNIT_TEST( PhotoatomicReactionACEFactory, 
		   createIncoherentReaction_no_doppler )
{
  MonteCarlo::PhotoatomicReactionACEFactory::createIncoherentReaction(
						           *xss_data_extractor,
							   energy_grid,
							   reaction,
							   false );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::INCOHERENT_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(),
		       exp( -1.381551055796E+01 ) );
  
  // Test that the stored cross section is correct
  double cross_section = 
    reaction->getCrossSection(exp( -1.381551055796E+01 ));
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section = reaction->getCrossSection(exp( -1.364234411496E+01 ));

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section = reaction->getCrossSection(exp( 1.151292546497E+01 ));

  TEST_FLOATING_EQUALITY( cross_section, exp( -6.573285045032E+00 ), 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an incoherent reaction with Doppler data can be created
TEUCHOS_UNIT_TEST( PhotoatomicReactionACEFactory,
		   createIncoherentReaction_doppler )
{
  MonteCarlo::PhotoatomicReactionACEFactory::createIncoherentReaction(
						           *xss_data_extractor,
							   energy_grid,
							   reaction,
							   true );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::INCOHERENT_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(),
		       exp( -1.381551055796E+01 ) );
  
  // Test that the stored cross section is correct
  double cross_section = 
    reaction->getCrossSection(exp( -1.381551055796E+01 ));
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section = reaction->getCrossSection(exp( -1.364234411496E+01 ));

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section = reaction->getCrossSection(exp( 1.151292546497E+01 ));

  TEST_FLOATING_EQUALITY( cross_section, exp( -6.573285045032E+00 ), 1e-12 );

  // Test that Doppler broadening is done
  MonteCarlo::SubshellType shell_of_interaction;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::ParticleBank bank;
  
  reaction->react( photon, bank, shell_of_interaction );

  TEST_ASSERT( shell_of_interaction != MonteCarlo::UNKNOWN_SUBSHELL );
  TEST_ASSERT( shell_of_interaction != MonteCarlo::INVALID_SUBSHELL );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a coherent reaction can be created
TEUCHOS_UNIT_TEST( PhotoatomicReactionACEFactory, createCoherentReaction )
{
  MonteCarlo::PhotoatomicReactionACEFactory::createCoherentReaction(
							   *xss_data_extractor,
							   energy_grid,
							   reaction );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(),
		       exp( -1.381551055796E+01 ) );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( exp(-1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -5.071403810640E+00 ), 1e-12 );
  
  cross_section = reaction->getCrossSection( exp( -1.364234411496E+01 ) );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -4.284251858121E+00 ), 1e-12 );

  cross_section = reaction->getCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -2.309498238246E+01 ), 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a basic pair production reaction can be created
TEUCHOS_UNIT_TEST( PhotoatomicReactionACEFactory, 
		   createPairProductionReaction_basic )
{
  MonteCarlo::PhotoatomicReactionACEFactory::createPairProductionReaction(
							   *xss_data_extractor,
							   energy_grid,
							   reaction,
							   false );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 
		       exp( 2.480967890857E-02 ) );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( 1e-4 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = reaction->getCrossSection( reaction->getThresholdEnergy() );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.431923975437E+01 ), 1e-12 );

  cross_section = reaction->getCrossSection( exp( 2.625237114407E-02 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.315996659940E+01 ), 1e-12 );

  cross_section = reaction->getCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 3.718032834377E+00 ), 1e-12 );
  
  cross_section = reaction->getCrossSection( exp( 12.0 ) );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a detailed pair production reaction can be created
// TEUCHOS_UNIT_TEST( PhotoatomicReactionACEFactory,
// 		   createPairProductionReaction_detailed )
// {
  
// }

//---------------------------------------------------------------------------//
// Check that the total photoelectric reaction can be created
TEUCHOS_UNIT_TEST( PhotoatomicReactionACEFactory,
		   createTotalPhotoelectricReaction )
{
  MonteCarlo::PhotoatomicReactionACEFactory::createTotalPhotoelectricReaction(
							   *xss_data_extractor,
							   energy_grid,
							   reaction );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
		       MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(),
		       exp( -1.214969212306E+01 ) );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
    
  cross_section = reaction->getCrossSection( exp( -1.214969212306E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = reaction->getCrossSection( exp( -1.214720768866E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = reaction->getCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that the subshell photoelectric reactions can be created
TEUCHOS_UNIT_TEST( PhotoatomicReactionACEFactory,
		   createSubshellPhotoelectricReactions )
{
  Teuchos::Array<Teuchos::RCP<MonteCarlo::PhotoatomicReaction> > reactions;

  MonteCarlo::PhotoatomicReactionACEFactory::createSubshellPhotoelectricReactions(
							   *xss_data_extractor,
							   energy_grid,
							   reactions );

  TEST_EQUALITY_CONST( reactions.size(), 24 );

  // Test the first shell's reaction properties
  TEST_EQUALITY_CONST( 
		   reactions.front()->getReactionType(),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.front()->getThresholdEnergy(),
		       exp( -2.427128314806E+00 ) );

  // Test the first shell's stored cross section is correct
  double cross_section = 
    reactions.front()->getCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
  
  cross_section = 
    reactions.front()->getCrossSection( exp( -2.427128314806E+00 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 7.578565567350E+00 ), 1e-12 );

  cross_section = 
    reactions.front()->getCrossSection( exp( -2.406201463890E+00 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 7.527375050980E+00 ), 1e-12 );

  cross_section = 
    reactions.front()->getCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.135387253512E+01 ), 1e-12 );

  // Check the last shell's reaction properties
  TEST_EQUALITY_CONST(
		  reactions.back()->getReactionType(),
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.back()->getThresholdEnergy(),
		       exp( -1.214969212306E+01 ) );

  cross_section = 
    reactions.back()->getCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = 
    reactions.back()->getCrossSection( exp( -1.214969212306E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = 
    reactions.back()->getCrossSection( exp( -1.214665892126E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718675283782E+01 ), 1e-12 );

  cross_section = 
    reactions.back()->getCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -2.364731020721E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_ace_file_name, test_ace_table_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  {
    // Create a file handler and data extractor
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler( 
				 new Data::ACEFileHandler( test_ace_file_name,
							   test_ace_table_name,
							   1u ) );
    xss_data_extractor.reset( new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

    // Extract the common energy grid
    energy_grid.deepCopy( xss_data_extractor->extractPhotonEnergyGrid() );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstPhotoatomicReactionACEFactory.cpp
//---------------------------------------------------------------------------//
