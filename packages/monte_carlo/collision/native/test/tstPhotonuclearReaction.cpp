//---------------------------------------------------------------------------//
//!
//! \file   tstPhotonuclearReaction.cpp
//! \author Ryan Pease
//! \brief  Photonuclear reaction unit tests.
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
#include "Data_XSSPhotonuclearDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_basic_h2_ace_file_name;
std::string test_basic_c12_ace_file_name;
std::string test_basic_h2_ace_table_name;
std::string test_basic_c12_ace_table_name;

Teuchos::RCP<Data::ACEFileHandler> h2_ace_file_handler;
Teuchos::RCP<Data::XSSNeutronDataExtractor> h2_xss_data_extractor;
Teuchos::RCP<MonteCarlo::PhotonuclearReaction> h2_photonuclear_reaction;

Teuchos::RCP<Data::ACEFileHandler> c12_ace_file_handler;
Teuchos::RCP<Data::XSSNeutronDataExtractor> c12_xss_data_extractor;
Teuchos::RCP<MonteCarlo::PhotonuclearReaction> c12_photonuclear_reaction;

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestPhotonuclearReaction : public MonteCarlo::PhotonuclearReaction
{
public:
  TestPhotonuclearReaction( 
		   const MonteCarlo::PhotonuclearReactionType reaction_type,
		   const double temperature,
		   const double q_value,
		   const unsigned threshold_energy_index,
	           const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section )
    : MonteCarlo::PhotonuclearReaction( reaction_type,
      			       q_value,
			       threshold_energy_index,
			       incoming_energy_grid,
			       cross_section )
  { /* ... */ }

  ~TestPhotonuclearReaction()
  { /* ... */ }
  
  unsigned getNumberOfEmittedPhotons( const double energy ) const
  { return 0u; }

  unsigned getNumberOfEmittedNeutrons( const double energy) const
  { return 0u; } 

  void react( MonteCarlo::PhotonState& photon, MonteCarlo::ParticleBank& bank ) const
  { /* ... */ }
};

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeOutGammaReaction(Teuchos::RCP<MonteCarlo::PhotonuclearReaction>& reaction)
{
  h2_ace_file_handler.reset(new Data::ACEFileHandler( test_basic_h2_ace_file_name,
						   test_basic_h2_ace_table_name,
						   1u ) );
  h2_xss_data_extractor.reset(
   new Data::XSSNeutronDataExtractor( h2_ace_file_handler->getTableNXSArray(),
				      h2_ace_file_handler->getTableJXSArray(),
				      h2_ace_file_handler->getTableXSSArray()));
   
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( h2_xss_data_extractor->extractEnergyGrid() );

  Teuchos::ArrayRCP<double> cross_section;
  cross_section.deepCopy( h2_xss_data_extractor->extractElasticCrossSection() );

  h2_photonuclear_reaction.reset( new TestPhotonuclearReaction( 
			               MonteCarlo::GAMMA__ANYTHING_REACTION,
				       0.0,
				       0u,
				       energy_grid,
				       cross_section ) );
}

void initializeOutNeutronReaction(Teuchos::RCP<MonteCarlo::PhotonuclearReaction>& reaction)
{
  c12_ace_file_handler.reset(new Data::ACEFileHandler( test_basic_c12_ace_file_name,
						   test_basic_c12_ace_table_name,
						   1u ) );
  c12_xss_data_extractor.reset(
   new Data::XSSNeutronDataExtractor( c12_ace_file_handler->getTableNXSArray(),
				      c12_ace_file_handler->getTableJXSArray(),
				      c12_ace_file_handler->getTableXSSArray()));
   
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( c12_xss_data_extractor->extractEnergyGrid() );

  Teuchos::ArrayRCP<double> cross_section;
  cross_section.deepCopy( c12_xss_data_extractor->extractElasticCrossSection() );

  c12_photonuclear_reaction.reset( new TestPhotonuclearReaction( 
			       MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION,
				       0.0,
				       0u,
				       energy_grid,
				       cross_section ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the reaction type of an elastic reaction can be returned
TEUCHOS_UNIT_TEST( PhotonuclearReaction_elastic, getReactionType )
{
  initializeOutGammaReaction( h2_photonuclear_reaction );
  initializeOutNeutronReaction( c12_photonuclear_reaction);

  TEST_EQUALITY_CONST( h2_photonuclear_reaction->getReactionType(), 
		       MonteCarlo::GAMMA__ANYTHING_REACTION );

  TEST_EQUALITY_CONST( c12_photonuclear_reaction->getReactionType(), 
		       MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the Q value can be returned
TEUCHOS_UNIT_TEST( PhotonuclearReaction_elastic, getQValue )
{
 // TEST_EQUALITY_CONST( photonuclear_reaction->getQValue(), 0.0 );		       
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
TEUCHOS_UNIT_TEST( PhotonuclearReaction_elastic, getThresholdEnergy )
{
 // TEST_EQUALITY_CONST( photonuclear_reaction->getThresholdEnergy(), 
//		       1.00000000000e-11 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
TEUCHOS_UNIT_TEST( PhotonuclearReaction_elastic, getCrossSection )
{
 
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_basic_h2_ace_file",
		 &test_basic_h2_ace_file_name,
		 "Test basic H2 ACE file name" );
  clp.setOption( "test_basic_h2_ace_table",
		 &test_basic_h2_ace_table_name,
		 "Test basic H2ACE table name in basic ACE file" );
  clp.setOption( "test_basic_c12_ace_file",
		 &test_basic_c12_ace_file_name,
		 "Test basic C12 ACE file name" );
  clp.setOption( "test_basic_c12_ace_table",
		 &test_basic_c12_ace_table_name,
		 "Test basic ACE table name in basic ACE file" );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstPhotonuclearReaction.cpp
//---------------------------------------------------------------------------//
