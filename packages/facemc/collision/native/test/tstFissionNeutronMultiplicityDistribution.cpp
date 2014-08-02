//---------------------------------------------------------------------------//
//!
//! \file   tstFissionNeutronMultiplicityDistribution.cpp
//! \author Alex Robinson
//! \brief  Fission neutron multiplicity distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Facemc_FissionNeutronMultiplicityDistributionFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<Facemc::FissionNeutronMultiplicityDistribution> multiplicity_dist;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the total nu-bar can be evaluated correctly
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistribution,
		   getAverageNumberOfEmittedNeutrons )
{
  TEST_EQUALITY_CONST(
	       multiplicity_dist->getAverageNumberOfEmittedNeutrons( 1.0e-11 ),
	       2.49208800000e+00 );
  TEST_EQUALITY_CONST(
		  multiplicity_dist->getAverageNumberOfEmittedNeutrons( 5.15 ),
		  3.12383700000e+00 );
  TEST_EQUALITY_CONST(
	       multiplicity_dist->getAverageNumberOfEmittedNeutrons( 30.0 ),
	       6.41410900000e+00 );
}

//---------------------------------------------------------------------------//
// Check that the prompt nu-bar can be evaluated correctly
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistribution,
		   getAverageNumberOfPromptNeutrons )
{
  TEST_EQUALITY_CONST(
	       multiplicity_dist->getAverageNumberOfPromptNeutrons( 1.0e-11 ),
	       2.44808800000e+00 );
  TEST_EQUALITY_CONST(
		  multiplicity_dist->getAverageNumberOfPromptNeutrons( 5.15 ),
		  3.08397700000e+00 );
  TEST_EQUALITY_CONST(
	       multiplicity_dist->getAverageNumberOfPromptNeutrons( 30.0 ),
	       6.38810900000e+00 );
}

//---------------------------------------------------------------------------//
// Check that the prompt nu-bar can be evaluated correctly
TEUCHOS_UNIT_TEST( FissionNeutronMultiplicityDistribution,
		   getAverageNumberOfDelayedNeutrons )
{
  TEST_EQUALITY_CONST(
	       multiplicity_dist->getAverageNumberOfDelayedNeutrons( 1.0e-11 ),
	       4.40000000000e-02 );
  TEST_EQUALITY_CONST(
		  multiplicity_dist->getAverageNumberOfDelayedNeutrons( 4.0 ),
		  4.40000000000e-02 );
  TEST_EQUALITY_CONST(
	       multiplicity_dist->getAverageNumberOfDelayedNeutrons( 30.0 ),
	       2.60000000000e-02 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  std::string test_u238_ace_file_name;
  std::string test_u238_ace_table_name;
  
  clp.setOption( "test_u238_ace_file",
		 &test_u238_ace_file_name,
		 "Test U238 ACE file name" );
  clp.setOption( "test_u238_ace_table",
		 &test_u238_ace_table_name,
		 "Test U238 ACE table name in basic ACE file" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize ace file handler, data extractor and multiplicity factory
  Teuchos::RCP<Data::ACEFileHandler>
  ace_file_handler( new Data::ACEFileHandler( test_u238_ace_file_name,
					      test_u238_ace_table_name,
					      1u ) );

  Teuchos::RCP<Data::XSSNeutronDataExtractor>
  xss_data_extractor( 
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  Teuchos::RCP<Facemc::FissionNeutronMultiplicityDistributionFactory>
  multiplicity_dist_factory(
		    new Facemc::FissionNeutronMultiplicityDistributionFactory( 
				     ace_file_handler->getTableName(),
				     xss_data_extractor->extractNUBlock(),
				     xss_data_extractor->extractDNUBlock() ) );

  multiplicity_dist_factory->createDistribution( multiplicity_dist );

  ace_file_handler.reset();
  xss_data_extractor.reset();
  multiplicity_dist_factory.reset();

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
// end tstFissionNeutronMultiplicityDistribution.cpp
//---------------------------------------------------------------------------//

