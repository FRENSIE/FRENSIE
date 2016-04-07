//---------------------------------------------------------------------------//
//!
//! \file   tstResponseFunctionFactory.cpp
//! \author Alex Robinson
//! \brief  Response function factory unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_ResponseFunctionFactory.hpp"
#include "Utility_OneDDistributionEntryConverterDB.hpp"

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//

std::string test_resp_func_xml_file_name;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the response function id map can be constructed
TEUCHOS_UNIT_TEST( ResponseFunctionFactory, createResponseFunctions )
{
  Teuchos::RCP<Teuchos::ParameterList> response_reps = 
    Teuchos::getParametersFromXmlFile( test_resp_func_xml_file_name );

  boost::unordered_map<unsigned,std::shared_ptr<MonteCarlo::ResponseFunction> > 
    response_id_map;

  MonteCarlo::ResponseFunctionFactory::createResponseFunctions( *response_reps,
							    response_id_map );

  TEST_EQUALITY_CONST( response_id_map.size(), 2 );
  TEST_EQUALITY_CONST( response_id_map[0]->getName(), "Energy Response" );
  TEST_EQUALITY_CONST( response_id_map[0]->getId(), 0 );
  TEST_EQUALITY_CONST( response_id_map[1]->getName(), "Phase Space Response" );
  TEST_EQUALITY_CONST( response_id_map[1]->getId(), 1 );
}


//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_resp_func_xml_file",
		 &test_resp_func_xml_file_name,
		 "Test response function xml file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();
  
  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstResponseFunctionFactory.cpp
//---------------------------------------------------------------------------//
