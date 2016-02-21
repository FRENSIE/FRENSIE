//---------------------------------------------------------------------------//
//!
//! \file   tstStandardEstimatorFactory_DagMC.cpp
//! \author Alex Robinson
//! \brief  Standard estimator factory specialization for DagMC unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// Moab Includes
#include <DagMC.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardEstimatorFactory_DagMC.hpp"
#include "MonteCarlo_ResponseFunctionFactory.hpp"
#include "MonteCarlo_EventHandler.hpp"
#include "Geometry_DagMCInstanceFactory.hpp"
#include "Geometry_ModuleInterface.hpp"
#include "Utility_OneDDistributionEntryConverterDB.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<Teuchos::ParameterList> observer_reps;

boost::unordered_map<unsigned,Teuchos::RCP<MonteCarlo::ResponseFunction> > 
  response_function_id_map;

std::shared_ptr<MonteCarlo::EventHandler> event_handler;

std::shared_ptr<MonteCarlo::EstimatorFactory> estimator_factory;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the factory can be constructed
TEUCHOS_UNIT_TEST( StandardEstimatorFactory_DagMC, constructor )
{
  TEST_NOTHROW( estimator_factory = 
                MonteCarlo::getEstimatorFactoryInstance<moab::DagMC>(
                                                  event_handler,
                                                  response_function_id_map ) );
  
}

//---------------------------------------------------------------------------//
// Check if the parameter list describes an estimator
TEUCHOS_UNIT_TEST( StandardEstimatorFactory_DagMC, isEstimatorRep )
{
  Teuchos::ParameterList dummy_rep;
  
  TEST_ASSERT( !estimator_factory->isEstimatorRep( dummy_rep ) );
  
  TEST_ASSERT( estimator_factory->isEstimatorRep( 
                               observer_reps->get<Teuchos::ParameterList>( 
                                      "Cell Track Length Flux Estimator" ) ) );

  TEST_ASSERT( estimator_factory->isEstimatorRep(
                               observer_reps->get<Teuchos::ParameterList>(
                                         "Cell Collision Flux Estimator" ) ) );

  TEST_ASSERT( estimator_factory->isEstimatorRep(
                               observer_reps->get<Teuchos::ParameterList>(
                                                "Pulse Height Estimator" ) ) );

  TEST_ASSERT( estimator_factory->isEstimatorRep(
                               observer_reps->get<Teuchos::ParameterList>(
                                                "Surface Flux Estimator" ) ) );

  TEST_ASSERT( estimator_factory->isEstimatorRep(
                               observer_reps->get<Teuchos::ParameterList>(
                                             "Surface Current Estimator" ) ) );

  TEST_ASSERT( estimator_factory->isEstimatorRep( 
                               observer_reps->get<Teuchos::ParameterList>(
                                  "Tet Mesh Track Length Flux Estimator" ) ) );
}

//---------------------------------------------------------------------------//
// Check if estimators can be created and registered with the event handler
TEUCHOS_UNIT_TEST( StandardEstimatorFactory_DagMC, createAndRegisterEstimator )
{
  Teuchos::ParameterList::ConstIterator observer_rep_it = 
    observer_reps->begin();

  while( observer_rep_it != observer_reps->end() )
  {
    const Teuchos::ParameterList& observer_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>(
                                            observer_rep_it->second.getAny() );

    estimator_factory->createAndRegisterEstimator( observer_rep );
  }
}

//---------------------------------------------------------------------------//
// Check that cached estimators can be created and registered
TEUCHOS_UNIT_TEST( StandardEstimatorFactory_DagMC, 
                   createAndRegisterCachedEstimators )
{
  TEST_NOTHROW( estimator_factory->createAndRegisterCachedEstimators() );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_geom_xml_file_name;
  std::string test_resp_func_xml_file_name;
  std::string test_observer_xml_file_name;
 
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_geom_xml_file",
		 &test_geom_xml_file_name,
		 "Test xml geometry file name" );

  clp.setOption( "test_resp_func_xml_file",
		 &test_resp_func_xml_file_name,
		 "Test response function xml file name" );

  clp.setOption( "test_observer_xml_file",
		 &test_observer_xml_file_name,
		 "Test estimator xml file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();
  
  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize DagMC
  Teuchos::RCP<Teuchos::ParameterList> geom_rep = 
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );

  Geometry::DagMCInstanceFactory::initializeDagMC( *geom_rep );

  Geometry::ModuleInterface<moab::DagMC>::initialize();

  // Load the observer parameter lists
  observer_reps = 
    Teuchos::getParametersFromXmlFile( test_observer_xml_file_name );

  // Load the response functions
  {
    Teuchos::RCP<Teuchos::ParameterList> response_reps = 
      Teuchos::getParametersFromXmlFile( test_resp_func_xml_file_name );

    MonteCarlo::ResponseFunctionFactory::createResponseFunctions(
                                                    *response_reps,
                                                    response_function_id_map );
  }

  // Initialize the event handler
  event_handler.reset( new MonteCarlo::EventHandler );

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
// end tstStandardEstimatorFactory_DagMC.cpp
//---------------------------------------------------------------------------//
