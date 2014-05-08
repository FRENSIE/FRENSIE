//---------------------------------------------------------------------------//
//!
//! \file   tstNuclearReactionFactory.cpp
//! \author Alex Robinson
//! \brief  Nuclear reaction factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "ACEFileHandler.hpp"
#include "XSSNeutronDataExtractor.hpp"
#include "NuclearReactionFactory.hpp"
#include "NuclearReaction.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_basic_ace_file_name;
std::string test_basic_ace_table_name;
// std::string test_fission_ace_file_name;
// std::string test_ptable_ace_file_name;
// std::string test_fission_ptable_ace_file_name;

Teuchos::RCP<FACEMC::ACEFileHandler> ace_file_handler;

Teuchos::RCP<FACEMC::XSSNeutronDataExtractor> xss_data_extractor;

Teuchos::RCP<FACEMC::NuclearReactionFactory> reaction_factory;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeReactionFactory( 
			Teuchos::RCP<FACEMC::NuclearReactionFactory>& factory )
{
  ace_file_handler.reset(new FACEMC::ACEFileHandler( test_basic_ace_file_name,
						     test_basic_ace_table_name,
						     1u ) );
  xss_data_extractor.reset(
   new FACEMC::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				        ace_file_handler->getTableJXSArray(),
				        ace_file_handler->getTableXSSArray()));

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractEnergyGrid() );

  factory.reset( new FACEMC::NuclearReactionFactory( 
			      test_basic_ace_table_name,
			      ace_file_handler->getTableAtomicWeightRatio(),
			      ace_file_handler->getTableTemperature(),
			      energy_grid,
			      xss_data_extractor->extractElasticCrossSection(),
			      xss_data_extractor->extractMTRBlock(),
			      xss_data_extractor->extractLQRBlock(),
			      xss_data_extractor->extractTYRBlock(),
			      xss_data_extractor->extractLSIGBlock(),
			      xss_data_extractor->extractSIGBlock(),
			      xss_data_extractor->extractLANDBlock(),
			      xss_data_extractor->extractANDBlock(),
			      xss_data_extractor->extractLDLWBlock(),
			      xss_data_extractor->extractDLWBlock() ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the elastic reaction can be created
TEUCHOS_UNIT_TEST( NuclearReactionFactory_hydrogen, createElasticReaction )
{
  initializeReactionFactory( reaction_factory );

  Teuchos::RCP<FACEMC::NuclearReaction> elastic_reaction;
  
  reaction_factory->createElasticReaction( elastic_reaction );

  TEST_EQUALITY_CONST( elastic_reaction->getReactionType(),
		       FACEMC::N__N_ELASTIC_REACTION );
  TEST_EQUALITY_CONST( elastic_reaction->getQValue(), 0.0 );
  TEST_EQUALITY_CONST( elastic_reaction->getNumberOfEmittedNeutrons( 0.0 ), 1);
  TEST_EQUALITY_CONST( elastic_reaction->getThresholdEnergy(), 1.0e-11 );
  TEST_EQUALITY_CONST( elastic_reaction->getCrossSection( 1.0e-11 ),
		       1.1605460e3 );
  TEST_EQUALITY_CONST( elastic_reaction->getCrossSection( 2.0e1 ),
		       4.827462e-1 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_basic_ace_file",
		 &test_basic_ace_file_name,
		 "Test basic ACE file name" );
  clp.setOption( "test_basic_ace_table",
		 &test_basic_ace_table_name,
		 "Test basic ACE table name in basic ACE file" );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstNuclearReactionFactory.cpp
//---------------------------------------------------------------------------//
