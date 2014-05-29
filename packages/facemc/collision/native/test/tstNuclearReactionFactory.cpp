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

// FRENSIE Includes
#include "Facemc_NuclearReactionFactory.hpp"
#include "Facemc_NuclearReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_basic_ace_file_name;
std::string test_basic_ace_table_name;
// std::string test_fission_ace_file_name;
// std::string test_ptable_ace_file_name;
// std::string test_fission_ptable_ace_file_name;

Teuchos::RCP<Data::ACEFileHandler> ace_file_handler;

Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor;

Teuchos::RCP<Facemc::NuclearReactionFactory> reaction_factory;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeReactionFactory( 
			Teuchos::RCP<Facemc::NuclearReactionFactory>& factory )
{
  ace_file_handler.reset(new Data::ACEFileHandler( test_basic_ace_file_name,
						     test_basic_ace_table_name,
						     1u ) );
  xss_data_extractor.reset(
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				        ace_file_handler->getTableJXSArray(),
				        ace_file_handler->getTableXSSArray()));

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractEnergyGrid() );

  factory.reset( new Facemc::NuclearReactionFactory( 
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
// Check that the scattering reaction can be created
TEUCHOS_UNIT_TEST( NuclearReactionFactory_hydrogen, createScatteringReactions )
{
  initializeReactionFactory( reaction_factory );

  boost::unordered_map<Facemc::NuclearReactionType,
		       Teuchos::RCP<Facemc::NuclearReaction> > reactions;
  
  reaction_factory->createScatteringReactions( reactions );

  TEST_EQUALITY_CONST( reactions.size(), 1 );

  Teuchos::RCP<Facemc::NuclearReaction>& elastic_reaction =
    reactions.find( Facemc::N__N_ELASTIC_REACTION )->second;
  
  TEST_EQUALITY_CONST( elastic_reaction->getReactionType(),
		       Facemc::N__N_ELASTIC_REACTION );
  TEST_EQUALITY_CONST( elastic_reaction->getQValue(), 0.0 );
  TEST_EQUALITY_CONST( elastic_reaction->getNumberOfEmittedNeutrons( 0.0 ), 1);
  TEST_EQUALITY_CONST( elastic_reaction->getThresholdEnergy(), 1.0e-11 );
  TEST_EQUALITY_CONST( elastic_reaction->getCrossSection( 1.0e-11 ),
		       1.1605460e3 );
  TEST_EQUALITY_CONST( elastic_reaction->getCrossSection( 2.0e1 ),
		       4.827462e-1 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be created
TEUCHOS_UNIT_TEST( NuclearReactionFactory_hydrogen, createAbsorptionReactions )
{
  boost::unordered_map<Facemc::NuclearReactionType,
		       Teuchos::RCP<Facemc::NuclearReaction> > reactions;
  
  reaction_factory->createAbsorptionReactions( reactions );

  TEST_EQUALITY_CONST( reactions.size(), 3 );

  Teuchos::RCP<Facemc::NuclearReaction>& n_gamma_reaction = 
    reactions.find( Facemc::N__GAMMA_REACTION )->second;

  TEST_EQUALITY_CONST( n_gamma_reaction->getReactionType(),
		       Facemc::N__GAMMA_REACTION );
  TEST_EQUALITY_CONST( n_gamma_reaction->getQValue(), 2.224631 );
  TEST_EQUALITY_CONST( n_gamma_reaction->getNumberOfEmittedNeutrons( 0.0 ), 0);
  TEST_EQUALITY_CONST( n_gamma_reaction->getThresholdEnergy(), 1.0e-11 );
  TEST_EQUALITY_CONST( n_gamma_reaction->getCrossSection( 1.0e-11 ),
		       1.670111e1 );
  TEST_EQUALITY_CONST( n_gamma_reaction->getCrossSection( 2.0e1 ),
		       2.722354e-5 );

  Teuchos::RCP<Facemc::NuclearReaction>& d_production_reaction = 
    reactions.find( Facemc::N__TOTAL_D_PRODUCTION )->second;

  TEST_EQUALITY_CONST( d_production_reaction->getReactionType(),
		       Facemc::N__TOTAL_D_PRODUCTION );
  TEST_EQUALITY_CONST( d_production_reaction->getQValue(), 0.0 );
  TEST_EQUALITY_CONST( d_production_reaction->getNumberOfEmittedNeutrons(0.0),
		       0 );
  TEST_EQUALITY_CONST( d_production_reaction->getThresholdEnergy(), 1.0e-11 );
  TEST_EQUALITY_CONST( d_production_reaction->getCrossSection( 1.0e-11 ),
		       1.670111e1 );
  TEST_EQUALITY_CONST( d_production_reaction->getCrossSection( 2.0e1 ),
		       2.722354e-5 );

  Teuchos::RCP<Facemc::NuclearReaction>& dpa_reaction = 
    reactions.find( Facemc::N__DPA )->second;

  TEST_EQUALITY_CONST( dpa_reaction->getReactionType(),
		       Facemc::N__DPA );
  TEST_EQUALITY_CONST( dpa_reaction->getQValue(), 0.0 );
  TEST_EQUALITY_CONST( dpa_reaction->getNumberOfEmittedNeutrons( 0.0 ), 0 );
  TEST_EQUALITY_CONST( dpa_reaction->getThresholdEnergy(), 2.375e-05);
  TEST_EQUALITY_CONST( dpa_reaction->getCrossSection( 2.375e-05 ), 0.0 );
  TEST_EQUALITY_CONST( dpa_reaction->getCrossSection( 2.0e1 ), 3.067696e-04 );

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
