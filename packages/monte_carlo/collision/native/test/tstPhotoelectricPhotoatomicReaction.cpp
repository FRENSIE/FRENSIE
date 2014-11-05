//---------------------------------------------------------------------------//
//!
//! \file   tstPhotoelectricPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Photoelectric photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoelectricPhotoatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::PhotoatomicReaction> ace_photoelectric_reaction;

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
TEUCHOS_UNIT_TEST( PhotoelectricPhotoatomicReaction, getReactionType_ace )
{
  TEST_EQUALITY_CONST( ace_photoelectric_reaction->getReactionType(),
		       MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( PhotoelectricPhotoatomicReaction, getThresholdEnergy_ace )
{
  TEST_EQUALITY_CONST( ace_photoelectric_reaction->getThresholdEnergy(),
		       exp( -1.214969212306E+01 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
TEUCHOS_UNIT_TEST( PhotoelectricPhotoatomicReaction, 
		   getNumberOfEmittedPhotons_ace )
{
  TEST_EQUALITY_CONST( 
		 ace_photoelectric_reaction->getNumberOfEmittedPhotons( 1e-3 ),
		 0u );

  TEST_EQUALITY_CONST(
		 ace_photoelectric_reaction->getNumberOfEmittedPhotons( 20.0 ),
		 0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( PhotoelectricPhotoatomicReaction, getCrossSection_ace )
{
  double cross_section = 
    ace_photoelectric_reaction->getCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
    
  cross_section =
    ace_photoelectric_reaction->getCrossSection( exp( -1.214969212306E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = 
    ace_photoelectric_reaction->getCrossSection( exp( -1.214720768866E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = 
    ace_photoelectric_reaction->getCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric effect can be simulated
TEUCHOS_UNIT_TEST( PhotoelectricPhotoatomicReaction, react_ace )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::SubshellType shell_of_interaction;

  ace_photoelectric_reaction->react( photon, 
				     bank, 
				     shell_of_interaction );

  TEST_ASSERT( photon.isGone() );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::UNKNOWN_SUBSHELL );
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
  energy_grid.deepCopy( xss_data_extractor->extractPhotonEnergyGrid() );
  
  Teuchos::ArrayView<const double> raw_pe_cross_section = 
    xss_data_extractor->extractPhotoelectricCrossSection();

  Teuchos::ArrayView<const double>::iterator start = 
    std::find_if( raw_pe_cross_section.begin(),
		  raw_pe_cross_section.end(),
		  notEqualZero );

  Teuchos::ArrayRCP<double> pe_cross_section;
  pe_cross_section.assign( start, raw_pe_cross_section.end() );

  unsigned pe_threshold_index = 
    energy_grid.size() - pe_cross_section.size();

  // Create the photoelectric reaction
  ace_photoelectric_reaction.reset(
	     new MonteCarlo::PhotoelectricPhotoatomicReaction<Utility::LogLog>(
						        energy_grid,
							pe_cross_section,
							pe_threshold_index ) );

  // Clear the setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

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
// end tstPhotoelectricPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//

