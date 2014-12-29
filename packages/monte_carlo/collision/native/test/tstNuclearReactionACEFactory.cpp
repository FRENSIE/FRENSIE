//---------------------------------------------------------------------------//
//!
//! \file   tstNuclearReactionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Nuclear reaction factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearReactionACEFactory.hpp"
#include "MonteCarlo_NuclearReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_h1_ace_file_name;
std::string test_h1_ace_table_name;
std::string test_o16_ace_file_name;
std::string test_o16_ace_table_name;
// std::string test_fission_ace_file_name;
// std::string test_ptable_ace_file_name;
// std::string test_fission_ptable_ace_file_name;

Teuchos::RCP<MonteCarlo::NuclearReactionACEFactory> h1_reaction_factory;
Teuchos::RCP<MonteCarlo::NuclearReactionACEFactory> o16_reaction_factory;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeReactionFactory( 
		  Teuchos::RCP<MonteCarlo::NuclearReactionACEFactory>& factory,
		  const std::string& ace_file_name,
		  const std::string& ace_table_name )
{
  Teuchos::RCP<Data::ACEFileHandler>
    ace_file_handler( new Data::ACEFileHandler( ace_file_name,
						ace_table_name,
						1u ) );
  Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor(
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray()));

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractEnergyGrid() );

  factory.reset( new MonteCarlo::NuclearReactionACEFactory( 
			      ace_table_name,
			      ace_file_handler->getTableAtomicWeightRatio(),
			      ace_file_handler->getTableTemperature(),
			      energy_grid,
			      *xss_data_extractor ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the scattering reaction can be created
TEUCHOS_UNIT_TEST( NuclearReactionACEFactory_hydrogen, createScatteringReactions )
{
  boost::unordered_map<MonteCarlo::NuclearReactionType,
		       Teuchos::RCP<MonteCarlo::NuclearReaction> > reactions;
  
  h1_reaction_factory->createScatteringReactions( reactions );

  TEST_EQUALITY_CONST( reactions.size(), 1 );

  Teuchos::RCP<MonteCarlo::NuclearReaction>& elastic_reaction =
    reactions.find( MonteCarlo::N__N_ELASTIC_REACTION )->second;
  
  TEST_EQUALITY_CONST( elastic_reaction->getReactionType(),
		       MonteCarlo::N__N_ELASTIC_REACTION );
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
TEUCHOS_UNIT_TEST( NuclearReactionACEFactory_hydrogen, createAbsorptionReactions )
{
  boost::unordered_map<MonteCarlo::NuclearReactionType,
		       Teuchos::RCP<MonteCarlo::NuclearReaction> > reactions;
  
  h1_reaction_factory->createAbsorptionReactions( reactions );

  TEST_EQUALITY_CONST( reactions.size(), 3 );

  Teuchos::RCP<MonteCarlo::NuclearReaction>& n_gamma_reaction = 
    reactions.find( MonteCarlo::N__GAMMA_REACTION )->second;

  TEST_EQUALITY_CONST( n_gamma_reaction->getReactionType(),
		       MonteCarlo::N__GAMMA_REACTION );
  TEST_EQUALITY_CONST( n_gamma_reaction->getQValue(), 2.224631 );
  TEST_EQUALITY_CONST( n_gamma_reaction->getNumberOfEmittedNeutrons( 0.0 ), 0);
  TEST_EQUALITY_CONST( n_gamma_reaction->getThresholdEnergy(), 1.0e-11 );
  TEST_EQUALITY_CONST( n_gamma_reaction->getCrossSection( 1.0e-11 ),
		       1.670111e1 );
  TEST_EQUALITY_CONST( n_gamma_reaction->getCrossSection( 2.0e1 ),
		       2.722354e-5 );

  Teuchos::RCP<MonteCarlo::NuclearReaction>& d_production_reaction = 
    reactions.find( MonteCarlo::N__TOTAL_D_PRODUCTION )->second;

  TEST_EQUALITY_CONST( d_production_reaction->getReactionType(),
		       MonteCarlo::N__TOTAL_D_PRODUCTION );
  TEST_EQUALITY_CONST( d_production_reaction->getQValue(), 0.0 );
  TEST_EQUALITY_CONST( d_production_reaction->getNumberOfEmittedNeutrons(0.0),
		       0 );
  TEST_EQUALITY_CONST( d_production_reaction->getThresholdEnergy(), 1.0e-11 );
  TEST_EQUALITY_CONST( d_production_reaction->getCrossSection( 1.0e-11 ),
		       1.670111e1 );
  TEST_EQUALITY_CONST( d_production_reaction->getCrossSection( 2.0e1 ),
		       2.722354e-5 );

  Teuchos::RCP<MonteCarlo::NuclearReaction>& dpa_reaction = 
    reactions.find( MonteCarlo::N__DPA )->second;

  TEST_EQUALITY_CONST( dpa_reaction->getReactionType(),
		       MonteCarlo::N__DPA );
  TEST_EQUALITY_CONST( dpa_reaction->getQValue(), 0.0 );
  TEST_EQUALITY_CONST( dpa_reaction->getNumberOfEmittedNeutrons( 0.0 ), 0 );
  TEST_EQUALITY_CONST( dpa_reaction->getThresholdEnergy(), 2.375e-05);
  TEST_EQUALITY_CONST( dpa_reaction->getCrossSection( 2.375e-05 ), 0.0 );
  TEST_EQUALITY_CONST( dpa_reaction->getCrossSection( 2.0e1 ), 3.067696e-04 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction can be created
TEUCHOS_UNIT_TEST( NuclearReactionACEFactory_oxygen, createScatteringReactions )
{
  boost::unordered_map<MonteCarlo::NuclearReactionType,
		       Teuchos::RCP<MonteCarlo::NuclearReaction> > reactions;
  
  o16_reaction_factory->createScatteringReactions( reactions );

  typedef boost::unordered_map<MonteCarlo::NuclearReactionType,
    Teuchos::RCP<MonteCarlo::NuclearReaction> >::const_iterator Reaction;

  for( Reaction reaction = reactions.begin(); reaction != reactions.end(); ++reaction )
  {
    std::cout << reaction->first << " " << reaction->second->getThresholdEnergy() << std::endl;
  }

  TEST_EQUALITY_CONST( reactions.size(), 18 );

  Teuchos::RCP<MonteCarlo::NuclearReaction>& elastic_reaction =
    reactions.find( MonteCarlo::N__N_ELASTIC_REACTION )->second;
  
  TEST_EQUALITY_CONST( elastic_reaction->getReactionType(),
		       MonteCarlo::N__N_ELASTIC_REACTION );
  TEST_EQUALITY_CONST( elastic_reaction->getQValue(), 0.0 );
  TEST_EQUALITY_CONST( elastic_reaction->getNumberOfEmittedNeutrons( 0.0 ), 1);
  TEST_EQUALITY_CONST( elastic_reaction->getThresholdEnergy(), 1.0e-11 );
  TEST_EQUALITY_CONST( elastic_reaction->getCrossSection( 1.0e-11 ),
		       5.50078400000e+01 );
  TEST_EQUALITY_CONST( elastic_reaction->getCrossSection( 150.0 ),
		       1.48000000000e-01 );

  Teuchos::RCP<MonteCarlo::NuclearReaction>& inelastic_level_1_reaction = 
    reactions.find( MonteCarlo::N__N_EXCITED_STATE_1_REACTION )->second;
  TEST_EQUALITY_CONST( inelastic_level_1_reaction->getQValue(), 
		       -6.04940000000e+00 );
  TEST_EQUALITY_CONST( 
		 inelastic_level_1_reaction->getNumberOfEmittedNeutrons( 0.0 ),
		 1 );
  TEST_EQUALITY_CONST( inelastic_level_1_reaction->getThresholdEnergy(), 
		       6.43088600000e+00 );
  TEST_EQUALITY_CONST(
		      inelastic_level_1_reaction->getCrossSection( 1.0e-11 ),
		      0.0 );
  TEST_EQUALITY_CONST( inelastic_level_1_reaction->getCrossSection( 7.0 ),
		       1.022538000000e-03 );
  TEST_EQUALITY_CONST( inelastic_level_1_reaction->getCrossSection( 150.0 ),
		       0.0 );

  Teuchos::RCP<MonteCarlo::NuclearReaction>& inelastic_continuum_reaction = 
    reactions.find( MonteCarlo::N__N_CONTINUUM_REACTION )->second;
  TEST_EQUALITY_CONST( inelastic_continuum_reaction->getQValue(), 
		       -9.58500000000e+00 );
  TEST_EQUALITY_CONST( 
	       inelastic_continuum_reaction->getNumberOfEmittedNeutrons( 0.0 ),
	       1);
  TEST_EQUALITY_CONST( inelastic_continuum_reaction->getThresholdEnergy(), 
		       1.01894600000e+01 );
  TEST_EQUALITY_CONST(
	    inelastic_continuum_reaction->getCrossSection( 1.01894600000e+01 ),
	    0.0 );
  TEST_EQUALITY_CONST( inelastic_continuum_reaction->getCrossSection( 150.0 ),
		       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be created
TEUCHOS_UNIT_TEST( NuclearReactionACEFactory_oxygen, 
		   createAbsorptionReactions )
{
  boost::unordered_map<MonteCarlo::NuclearReactionType,
		       Teuchos::RCP<MonteCarlo::NuclearReaction> > reactions;

  o16_reaction_factory->createAbsorptionReactions( reactions );

  typedef boost::unordered_map<MonteCarlo::NuclearReactionType,
    Teuchos::RCP<MonteCarlo::NuclearReaction> >::const_iterator Reaction;

  for( Reaction reaction = reactions.begin(); reaction != reactions.end(); ++reaction )
  {
    if( reaction->first < 117 )
    {
      std::cout << reaction->first << " " << reaction->second->getThresholdEnergy() << std::endl;
    }
  }

  TEST_EQUALITY_CONST( reactions.size(), 51 );

  Teuchos::RCP<MonteCarlo::NuclearReaction>& n_gamma_reaction = 
    reactions.find( MonteCarlo::N__GAMMA_REACTION )->second;

  TEST_EQUALITY_CONST( n_gamma_reaction->getReactionType(),
		       MonteCarlo::N__GAMMA_REACTION );
  TEST_EQUALITY_CONST( n_gamma_reaction->getQValue(), 4.14342300000e+00 );
  TEST_EQUALITY_CONST( n_gamma_reaction->getNumberOfEmittedNeutrons( 0.0 ), 0);
  TEST_EQUALITY_CONST( n_gamma_reaction->getThresholdEnergy(), 1.0e-11 );
  TEST_EQUALITY_CONST( n_gamma_reaction->getCrossSection( 1.0e-11 ),
		       9.55754000000e-03 );
  TEST_EQUALITY_CONST( n_gamma_reaction->getCrossSection( 150.0 ), 0.0 );

 Teuchos::RCP<MonteCarlo::NuclearReaction>& n_alpha_ex_3_reaction = 
    reactions.find( MonteCarlo::N__ALPHA_EXCITED_STATE_3_REACTION )->second;

  TEST_EQUALITY_CONST( n_alpha_ex_3_reaction->getReactionType(),
		       MonteCarlo::N__ALPHA_EXCITED_STATE_3_REACTION );
  TEST_EQUALITY_CONST( n_alpha_ex_3_reaction->getQValue(), -6.06940000000e+00);
  TEST_EQUALITY_CONST(n_alpha_ex_3_reaction->getNumberOfEmittedNeutrons( 0.0 ),
		      0);
  TEST_EQUALITY_CONST( n_alpha_ex_3_reaction->getThresholdEnergy(), 
		       6.45214700000e+00 );
  TEST_EQUALITY_CONST( n_alpha_ex_3_reaction->getCrossSection( 1.0e-11 ),
		       0.0 );
  TEST_EQUALITY_CONST( n_alpha_ex_3_reaction->getCrossSection( 150.0 ),
		       0.0 ); 
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_h1_ace_file",
		 &test_h1_ace_file_name,
		 "Test h1 ACE file name" );
  clp.setOption( "test_h1_ace_table",
		 &test_h1_ace_table_name,
		 "Test ACE table name in h1 ACE file" );

  clp.setOption( "test_o16_ace_file",
		 &test_o16_ace_file_name,
		 "Test o16 ACE file name" );
  clp.setOption( "test_o16_ace_table",
		 &test_o16_ace_table_name,
		 "Test ACE table name in o16 ACE file" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Initialize nuclear reaction factories
  initializeReactionFactory( h1_reaction_factory,
			     test_h1_ace_file_name,
			     test_h1_ace_table_name );

  initializeReactionFactory( o16_reaction_factory,
			     test_o16_ace_file_name,
			     test_o16_ace_table_name );

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
// end tstNuclearReactionACEFactory.cpp
//---------------------------------------------------------------------------//
