//---------------------------------------------------------------------------//
//!
//! \file   tstNuclearReaction.cpp
//! \author Alex Robinson
//! \brief  Nuclear reaction unit tests.
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
#include "NeutronNeutronScatteringDistributionFactory.hpp"
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

Teuchos::RCP<FACEMC::NuclearReaction> nuclear_reaction;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeElasticReaction(Teuchos::RCP<FACEMC::NuclearReaction>& reaction)
{
  ace_file_handler.reset(new FACEMC::ACEFileHandler( test_basic_ace_file_name,
						     test_basic_ace_table_name,
						     1u ) );
  xss_data_extractor.reset(
   new FACEMC::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				        ace_file_handler->getTableJXSArray(),
				        ace_file_handler->getTableXSSArray()));
   
  FACEMC::NeutronNeutronScatteringDistributionFactory 
    factory( test_basic_ace_table_name,
	     ace_file_handler->getTableAtomicWeightRatio(),
	     xss_data_extractor->extractMTRBlock(),
	     xss_data_extractor->extractTYRBlock(),
	     xss_data_extractor->extractLANDBlock(),
	     xss_data_extractor->extractANDBlock(),
	     xss_data_extractor->extractLDLWBlock(),
	     xss_data_extractor->extractDLWBlock() );

  Teuchos::RCP<FACEMC::NeutronNeutronScatteringDistribution> scattering_dist;
  
  factory.createElasticScatteringDist( scattering_dist );

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractEnergyGrid() );

  nuclear_reaction.reset( new FACEMC::NuclearReaction( 
			      FACEMC::N__N_ELASTIC_REACTION,
			      ace_file_handler->getTableTemperature(),
			      0.0,
			      1u,
			      0u,
			      energy_grid,
			      xss_data_extractor->extractElasticCrossSection(),
			      scattering_dist ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the reaction type of an elastic reaction can be returned
TEUCHOS_UNIT_TEST( NuclearReaction_elastic, getReactionType )
{
  initializeElasticReaction( nuclear_reaction );

  TEST_EQUALITY_CONST( nuclear_reaction->getReactionType(), 
		       FACEMC::N__N_ELASTIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the Q value can be returned
TEUCHOS_UNIT_TEST( NuclearReaction_elastic, getQValue )
{
  TEST_EQUALITY_CONST( nuclear_reaction->getQValue(), 0.0 );		       
}

//---------------------------------------------------------------------------//
// Check that the number of emitted neutrons can be returned
TEUCHOS_UNIT_TEST( NuclearReaction_elastic, getNumberOfEmittedNeutrons )
{
  TEST_EQUALITY_CONST( nuclear_reaction->getNumberOfEmittedNeutrons( 0.0 ), 1);
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( NuclearReaction_elastic, getThresholdEnergy )
{
  TEST_EQUALITY_CONST( nuclear_reaction->getThresholdEnergy(), 
		       1.00000000000e-11 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( NuclearReaction_elastic, getCrossSectionValue )
{
  double cross_section = 
    nuclear_reaction->getCrossSectionValue( 1.00000000000e-11 );
  
  TEST_EQUALITY_CONST( cross_section, 1.16054600000e+03 );

  cross_section = nuclear_reaction->getCrossSectionValue( 1.015625e-11 );
  
  TEST_EQUALITY_CONST( cross_section, 1.151689e3 );

  cross_section = nuclear_reaction->getCrossSectionValue( 1.03125e-11 );
  
  TEST_EQUALITY_CONST( cross_section, 1.142832e3 );

  cross_section = nuclear_reaction->getCrossSectionValue( 1.0625e-11 );
  
  TEST_EQUALITY_CONST( cross_section, 1.125904e3 );

  cross_section = nuclear_reaction->getCrossSectionValue( 1.09375e-11 );

  TEST_EQUALITY_CONST( cross_section, 1.109708e3 );
    
  cross_section = nuclear_reaction->getCrossSectionValue( 1.90e1 );
  
  TEST_EQUALITY_CONST( cross_section, 5.087783e-1 );
  
  cross_section = nuclear_reaction->getCrossSectionValue( 1.95e1 );
  
  TEST_EQUALITY_CONST( cross_section, 4.95463e-1 );

  cross_section = nuclear_reaction->getCrossSectionValue( 2.0e1 );
  
  TEST_EQUALITY_CONST( cross_section, 4.827462e-1 );
}

//---------------------------------------------------------------------------//
// Check that the reaction can be simulated
TEUCHOS_UNIT_TEST( NuclearReaction_elastic, react )
{
  Teuchos::RCP<FACEMC::NeutronState> neutron( new FACEMC::NeutronState(0ull) );
  
  neutron->setDirection( 0.0, 0.0, 1.0 );
  neutron->setEnergy( 1.0 );

  FACEMC::ParticleBank bank;

  bank.push( neutron );
  
  nuclear_reaction->react( *neutron, bank );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  std::cout << std::endl << std::endl << *neutron << std::endl;
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
// end tstNuclearReaction.cpp
//---------------------------------------------------------------------------//
