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

// FRENSIE Includes
#include "MonteCarlo_NuclearReaction.hpp"
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

Teuchos::RCP<MonteCarlo::NuclearReaction> nuclear_reaction;

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestNuclearReaction : public MonteCarlo::NuclearReaction
{
public:
  TestNuclearReaction( 
		   const MonteCarlo::NuclearReactionType reaction_type,
		   const double temperature,
		   const double q_value,
		   const unsigned threshold_energy_index,
	     const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section )
    : MonteCarlo::NuclearReaction( reaction_type,
			       temperature,
			       q_value,
			       threshold_energy_index,
			       incoming_energy_grid,
			       cross_section )
  { /* ... */ }

  ~TestNuclearReaction()
  { /* ... */ }
  
  unsigned getNumberOfEmittedNeutrons( const double energy ) const
  { return 0u; }

  void react( MonteCarlo::NeutronState& neutron, MonteCarlo::ParticleBank& bank ) const
  { /* ... */ }
};

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeElasticReaction(Teuchos::RCP<MonteCarlo::NuclearReaction>& reaction)
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

  Teuchos::ArrayRCP<double> cross_section;
  cross_section.deepCopy( xss_data_extractor->extractElasticCrossSection() );

  nuclear_reaction.reset( new TestNuclearReaction( 
			               MonteCarlo::N__N_ELASTIC_REACTION,
			               ace_file_handler->getTableTemperature(),
				       0.0,
				       0u,
				       energy_grid,
				       cross_section ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the reaction type of an elastic reaction can be returned
TEUCHOS_UNIT_TEST( NuclearReaction_elastic, getReactionType )
{
  initializeElasticReaction( nuclear_reaction );

  TEST_EQUALITY_CONST( nuclear_reaction->getReactionType(), 
		       MonteCarlo::N__N_ELASTIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the Q value can be returned
TEUCHOS_UNIT_TEST( NuclearReaction_elastic, getQValue )
{
  TEST_EQUALITY_CONST( nuclear_reaction->getQValue(), 0.0 );		       
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
TEUCHOS_UNIT_TEST( NuclearReaction_elastic, getCrossSection )
{
  double cross_section = 
    nuclear_reaction->getCrossSection( 1.00000000000e-11 );
  
  TEST_EQUALITY_CONST( cross_section, 1.16054600000e+03 );

  cross_section = nuclear_reaction->getCrossSection( 1.015625e-11 );
  
  TEST_EQUALITY_CONST( cross_section, 1.151689e3 );

  cross_section = nuclear_reaction->getCrossSection( 1.03125e-11 );
  
  TEST_EQUALITY_CONST( cross_section, 1.142832e3 );

  cross_section = nuclear_reaction->getCrossSection( 1.0625e-11 );
  
  TEST_EQUALITY_CONST( cross_section, 1.125904e3 );

  cross_section = nuclear_reaction->getCrossSection( 1.09375e-11 );

  TEST_EQUALITY_CONST( cross_section, 1.109708e3 );
    
  cross_section = nuclear_reaction->getCrossSection( 1.90e1 );
  
  TEST_EQUALITY_CONST( cross_section, 5.087783e-1 );
  
  cross_section = nuclear_reaction->getCrossSection( 1.95e1 );
  
  TEST_EQUALITY_CONST( cross_section, 4.95463e-1 );

  cross_section = nuclear_reaction->getCrossSection( 2.0e1 );
  
  TEST_EQUALITY_CONST( cross_section, 4.827462e-1 );
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
