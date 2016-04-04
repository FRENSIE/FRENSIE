//---------------------------------------------------------------------------//
//!
//! \file   tstDecoupledPhotonProductionReactionACEFactory.cpp
//! \author Eli Moll
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
#include "MonteCarlo_DecoupledPhotonProductionReactionACEFactory.hpp"
#include "MonteCarlo_DecoupledPhotonProductionReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_o16_ace_file_name;
std::string test_o16_ace_table_name;

Teuchos::RCP<MonteCarlo::DecoupledPhotonProductionReactionACEFactory> o16_reaction_factory;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void initializeReactionFactory( 
		  Teuchos::RCP<MonteCarlo::DecoupledPhotonProductionReactionACEFactory>& factory,
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

  factory.reset( new MonteCarlo::DecoupledPhotonProductionReactionACEFactory( 
			      ace_table_name,
			      ace_file_handler->getTableAtomicWeightRatio(),
			      ace_file_handler->getTableTemperature(),
			      energy_grid,
			      *xss_data_extractor ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the photon production reactions can be created
TEUCHOS_UNIT_TEST( NuclearReactionACEFactory_hydrogen, createScatteringReactions )
{
  boost::unordered_map<unsigned,
		   Teuchos::RCP<MonteCarlo::DecoupledPhotonProductionReaction> > reactions;
  
  o16_reaction_factory->createPhotonProductionReactions( reactions );

  TEST_EQUALITY_CONST( reactions.size(), 131 );

  // Test the yield based reaction (102001)
  Teuchos::RCP<MonteCarlo::DecoupledPhotonProductionReaction>& yield_based_reaction_102001 =
    reactions.find( 102001u )->second;
  
  TEST_EQUALITY_CONST( yield_based_reaction_102001->getBaseReactionType(),
		       MonteCarlo::N__GAMMA_REACTION );
	TEST_EQUALITY_CONST( yield_based_reaction_102001->getPhotonProductionReactionId(),
		       102001u );	       
  TEST_EQUALITY_CONST( yield_based_reaction_102001->getCrossSection( 1.0e-11 ),
		       0.146*9.55754000000E-03 );
		     
	// Test the XS based reaction (4001)  
	Teuchos::RCP<MonteCarlo::DecoupledPhotonProductionReaction>& xs_based_reaction_4001 =
    reactions.find( 4001u )->second;	
    
  TEST_EQUALITY_CONST( xs_based_reaction_4001->getBaseReactionType(),
		       MonteCarlo::N__N_INELASTIC_REACTION );
	TEST_EQUALITY_CONST( xs_based_reaction_4001->getPhotonProductionReactionId(),
		       4001u );	       
  TEST_EQUALITY_CONST( xs_based_reaction_4001->getCrossSection( 9.43140000000E+00 ),
		       1.85882800000E-12 );      
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

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
