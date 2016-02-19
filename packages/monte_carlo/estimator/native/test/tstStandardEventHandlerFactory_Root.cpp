//---------------------------------------------------------------------------//
//!
//! \file   tstStandardEventHandlerFactory_Root.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Event handler factory unit tests
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
#include "MonteCarlo_StandardEventHandlerFactory_Root.hpp"
#include "Geometry_Root.hpp"
#include "Geometry_RootInstanceFactory.hpp"
#include "Geometry_ModuleInterface_Root.hpp"
#include "Utility_OneDDistributionEntryConverterDB.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string test_geom_xml_file_name;
std::string test_resp_func_xml_file_name;
std::string test_estimator_xml_file_name;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the estimator handler can be initialized
TEUCHOS_UNIT_TEST( EventHandlerFactoryRoot, initializeHandlerUsingRoot )
{
  Teuchos::RCP<Teuchos::ParameterList> response_reps = 
    Teuchos::getParametersFromXmlFile( test_resp_func_xml_file_name );

  Teuchos::RCP<Teuchos::ParameterList> estimator_reps =
    Teuchos::getParametersFromXmlFile( test_estimator_xml_file_name );

  MonteCarlo::EventHandlerFactory<Geometry::Root>::initializeHandler( 
							     *response_reps,
							     *estimator_reps );

  TEST_EQUALITY_CONST( MonteCarlo::EventHandler::getNumberOfEstimators(), 3 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_geom_xml_file",
		 &test_geom_xml_file_name,
		 "Test xml geometry file name" );

  clp.setOption( "test_resp_func_xml_file",
		 &test_resp_func_xml_file_name,
		 "Test response function xml file name" );

  clp.setOption( "test_estimator_xml_file",
		 &test_estimator_xml_file_name,
		 "Test estimator xml file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();
  
  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize Root
  Teuchos::RCP<Teuchos::ParameterList> geom_rep = 
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );

  Geometry::RootInstanceFactory::initializeRoot( *geom_rep );

  Geometry::ModuleInterface<Geometry::Root>::initialize();
  
  // Run the unit tests
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
// end tstStandardEventHandlerFactory_Root.cpp
//---------------------------------------------------------------------------//
