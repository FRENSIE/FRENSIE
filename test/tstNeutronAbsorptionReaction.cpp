//---------------------------------------------------------------------------//
//!
//! \file   tstNeutronAbsorptionReaction.cpp
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
#include "NeutronAbsorptionReaction.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_basic_ace_file_name;
std::string test_basic_ace_table_name;

Teuchos::RCP<FACEMC::ACEFileHandler> ace_file_handler;

Teuchos::RCP<FACEMC::XSSNeutronDataExtractor> xss_data_extractor;

Teuchos::RCP<FACEMC::NuclearReaction> nuclear_reaction;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeAbsorptionReaction(
			      Teuchos::RCP<FACEMC::NuclearReaction>& reaction )
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

  Teuchos::ArrayRCP<double> cross_section;
  cross_section.deepCopy( xss_data_extractor->extractElasticCrossSection() );

  nuclear_reaction.reset( new FACEMC::NeutronAbsorptionReaction( 
				       FACEMC::N__N_ELASTIC_REACTION,
			               ace_file_handler->getTableTemperature(),
				       0.0,
				       0u,
				       energy_grid,
				       cross_section ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of emitted neutrons can be returned
TEUCHOS_UNIT_TEST( NeutronAbsorptionReaction, 
		   getNumberOfEmittedNeutrons )
{
  initializeAbsorptionReaction( nuclear_reaction );
  
  TEST_EQUALITY_CONST( nuclear_reaction->getNumberOfEmittedNeutrons( 0.0 ), 0);
}

//---------------------------------------------------------------------------//
// Check that the reaction can be simulated
TEUCHOS_UNIT_TEST( NeutronAbsorptionReaction, 
		   react )
{
  Teuchos::RCP<FACEMC::NeutronState> neutron( new FACEMC::NeutronState(0ull) );
  
  neutron->setDirection( 0.0, 0.0, 1.0 );
  neutron->setEnergy( 1.0 );

  FACEMC::ParticleBank bank;

  bank.push( neutron );
  
  nuclear_reaction->react( *neutron, bank );

  TEST_ASSERT( neutron->isGone() );
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
// end tstNeutronAbsorptionReaction.cpp
//---------------------------------------------------------------------------//

