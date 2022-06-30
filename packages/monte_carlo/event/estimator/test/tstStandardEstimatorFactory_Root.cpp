//---------------------------------------------------------------------------//
//!
//! \file   tstStandardEstimatorFactory_Root.cpp
//! \author Alex Robinson
//! \brief  Standard estimator factory specialization for Root unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>
#include <unordered_map>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardEstimatorFactory_Root.hpp"
#include "MonteCarlo_ResponseFunctionFactory.hpp"
#include "MonteCarlo_EventHandler.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "Geometry_Root.hpp"
#include "Geometry_RootInstanceFactory.hpp"
#include "Geometry_ModuleInterface_Root.hpp"
#include "Utility_OneDDistributionEntryConverterDB.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<Teuchos::ParameterList> observer_reps;

std::unordered_map<unsigned,std::shared_ptr<MonteCarlo::ResponseFunction> >
  response_function_id_map;

std::shared_ptr<MonteCarlo::EventHandler> event_handler;

std::shared_ptr<MonteCarlo::EstimatorFactory> estimator_factory;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the factory can be constructed
TEUCHOS_UNIT_TEST( StandardEstimatorFactory_Root, constructor )
{
  std::shared_ptr<MonteCarlo::SimulationGeneralProperties> properties(
                                 new MonteCarlo::SimulationGeneralProperties );
  
  TEST_NOTHROW( estimator_factory =
                MonteCarlo::getEstimatorFactoryInstance<Geometry::Root>(
                                                  event_handler,
                                                  response_function_id_map,
                                                  properties ) );
}

//---------------------------------------------------------------------------//
// Check if the parameter list describes an estimator
TEUCHOS_UNIT_TEST( StandardEstimatorFactory_Root, isEstimatorRep )
{
  Teuchos::ParameterList dummy_rep;

  TEST_ASSERT( !estimator_factory->isEstimatorRep( dummy_rep ) );

  TEST_ASSERT( estimator_factory->isEstimatorRep(
                                observer_reps->get<Teuchos::ParameterList>(
                                    "Cell Track Length Flux Estimator 2" ) ) );

  TEST_ASSERT( estimator_factory->isEstimatorRep(
                                observer_reps->get<Teuchos::ParameterList>(
                                       "Cell Collision Flux Estimator 2" ) ) );

  TEST_ASSERT( estimator_factory->isEstimatorRep(
                                observer_reps->get<Teuchos::ParameterList>(
                                              "Pulse Height Estimator 2" ) ) );

  TEST_ASSERT( estimator_factory->isEstimatorRep(
                                observer_reps->get<Teuchos::ParameterList>(
                                              "Surface Flux Estimator 2" ) ) );

  TEST_ASSERT( estimator_factory->isEstimatorRep(
                                observer_reps->get<Teuchos::ParameterList>(
                                           "Surface Current Estimator 2" ) ) );
}

//---------------------------------------------------------------------------//
// Check if estimators can be created and registered with the event handler
TEUCHOS_UNIT_TEST( StandardEstimatorFactory_Root, createAndRegisterEstimator )
{
  Teuchos::ParameterList::ConstIterator observer_rep_it =
    observer_reps->begin();

  while( observer_rep_it != observer_reps->end() )
  {
    const Teuchos::ParameterList& observer_rep =
      Teuchos::any_cast<Teuchos::ParameterList>(
                                            observer_rep_it->second.getAny() );

    estimator_factory->createAndRegisterEstimator( observer_rep );

    ++observer_rep_it;
  }

  // Check that all of the estimators got created
  TEST_EQUALITY_CONST( event_handler->getNumberOfObservers(), 8 );

  std::string estimator_file_name( "estimator_factory_root.h5" );

  {
    std::shared_ptr<Utility::HDF5FileHandler>
        hdf5_file( new Utility::HDF5FileHandler );
    hdf5_file->openHDF5FileAndOverwrite( estimator_file_name );

    event_handler->exportObserverData( hdf5_file,
                                       1,
                                       1,
                                       0.0,
                                       1.0,
                                       false );
  }

  // Initialize the hdf5 file
  std::shared_ptr<Utility::HDF5FileHandler>
    hdf5_file( new Utility::HDF5FileHandler );
  hdf5_file->openHDF5FileAndReadOnly( estimator_file_name );

  // Create an estimator hdf5 file handler
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

  // Check that the correct estimators exist
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 12 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 13 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 14 ) );

  // Check that estimator 12 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isCellEstimator( 12 ) );

  double multiplier;
  hdf5_file_handler.getEstimatorMultiplier( 12, multiplier );

  TEST_EQUALITY_CONST( multiplier, 2.0 );

  Teuchos::Array<unsigned> response_function_ordering;
  hdf5_file_handler.getEstimatorResponseFunctionOrdering(
                                              12, response_function_ordering );

  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY_CONST( response_function_ordering[0], 0 );

  Teuchos::Array<MonteCarlo::PhaseSpaceDimension> dimension_ordering;
  hdf5_file_handler.getEstimatorDimensionOrdering( 12, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 1 );
  TEST_EQUALITY_CONST( dimension_ordering[0],
                       MonteCarlo::SOURCE_ENERGY_DIMENSION );

  Teuchos::Array<double> energy_bins;
  
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::SOURCE_ENERGY_DIMENSION>(
                                                             12, energy_bins );

  TEST_EQUALITY_CONST( energy_bins.size(), 14 );
  TEST_EQUALITY_CONST( energy_bins.front(), 1e-3 );
  TEST_EQUALITY_CONST( energy_bins.back(), 20.0 );

  std::unordered_map<Geometry::ModuleTraits::EntityId,double>
    cell_id_vols;
  hdf5_file_handler.getEstimatorEntities( 12, cell_id_vols );
  
  TEST_EQUALITY_CONST( cell_id_vols.size(), 1 );

  TEST_ASSERT( cell_id_vols.count( 1 ) );
  
  // Check that estimator 13 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isCellEstimator( 13 ) );

  hdf5_file_handler.getEstimatorMultiplier( 13, multiplier );

  TEST_EQUALITY_CONST( multiplier, 2.0 );

  hdf5_file_handler.getEstimatorResponseFunctionOrdering(
                                              13, response_function_ordering );

  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY_CONST( response_function_ordering[0], 0 );

  dimension_ordering.clear();
  hdf5_file_handler.getEstimatorDimensionOrdering( 13, dimension_ordering );

  Teuchos::Array<double> time_bins;

  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::SOURCE_TIME_DIMENSION>(
                                                               13, time_bins );

  TEST_EQUALITY_CONST( time_bins.size(), 5 );
  TEST_EQUALITY_CONST( time_bins.front(), 0.0 );
  TEST_EQUALITY_CONST( time_bins.back(), 1.0 );

  cell_id_vols.clear();
  hdf5_file_handler.getEstimatorEntities( 13, cell_id_vols );
  
  TEST_EQUALITY_CONST( cell_id_vols.size(), 1 );

  TEST_ASSERT( cell_id_vols.count( 1 ) );

  // Check that estimator 14 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isCellEstimator( 14 ) );

  hdf5_file_handler.getEstimatorMultiplier( 14, multiplier );

  TEST_EQUALITY_CONST( multiplier, 1.0 );

  response_function_ordering.clear();
  hdf5_file_handler.getEstimatorResponseFunctionOrdering(
                                              14, response_function_ordering );

  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY_CONST( response_function_ordering.front(), 4294967295 );

  dimension_ordering.clear();
  hdf5_file_handler.getEstimatorDimensionOrdering( 14, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 0 );

  cell_id_vols.clear();
  hdf5_file_handler.getEstimatorEntities( 14, cell_id_vols );
  
  TEST_EQUALITY_CONST( cell_id_vols.size(), 1 );

  TEST_ASSERT( cell_id_vols.count( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that cached estimators can be created and registered
TEUCHOS_UNIT_TEST( StandardEstimatorFactory_Root,
                   createAndRegisterCachedEstimators )
{
  TEST_NOTHROW( estimator_factory->createAndRegisterCachedEstimators() );

  // Check that all of the estimators got created
  TEST_EQUALITY_CONST( event_handler->getNumberOfObservers(), 8 );
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

  // Initialize Root
  Teuchos::RCP<Teuchos::ParameterList> geom_rep =
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );

  Geometry::RootInstanceFactory::initializeRoot( *geom_rep );

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
// end tstStandardEstimatorFactory_Root.cpp
//---------------------------------------------------------------------------//
