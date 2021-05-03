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
#include <unordered_map>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardEstimatorFactory_DagMC.hpp"
#include "MonteCarlo_ResponseFunctionFactory.hpp"
#include "MonteCarlo_EventHandler.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "Geometry_DagMCInstanceFactory.hpp"
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
TEUCHOS_UNIT_TEST( StandardEstimatorFactory_DagMC, constructor )
{
  std::shared_ptr<MonteCarlo::SimulationGeneralProperties> properties(
                                 new MonteCarlo::SimulationGeneralProperties );
  
  TEST_NOTHROW( estimator_factory =
                MonteCarlo::getEstimatorFactoryInstance<Geometry::DagMC>(
                                                  event_handler,
                                                  response_function_id_map,
                                                  properties ) );

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

  TEST_ASSERT( estimator_factory->isEstimatorRep( 
                               observer_reps->get<Teuchos::ParameterList>(
                                  "Hex Mesh Track Length Flux Estimator" ) ) );
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

    ++observer_rep_it;
  }

  // Check that all of the estimators got created
  TEST_EQUALITY_CONST( event_handler->getNumberOfObservers(), 12 );

  std::string estimator_file_name( "estimator_factory_dagmc_partial.h5" );

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
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 1 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 2 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 4 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 9 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 10 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 11 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 12 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 13 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 14 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 15 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 16 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 17 ) );

  // Check that estimator 1 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isCellEstimator( 1 ) );

  double multiplier;
  hdf5_file_handler.getEstimatorMultiplier( 1, multiplier );

  TEST_EQUALITY_CONST( multiplier, 2.0 );

  Teuchos::Array<unsigned> response_function_ordering;

  hdf5_file_handler.getEstimatorResponseFunctionOrdering(
                                               1, response_function_ordering );

  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY_CONST( response_function_ordering[0], 0 );

  Teuchos::Array<MonteCarlo::PhaseSpaceDimension> dimension_ordering;

  hdf5_file_handler.getEstimatorDimensionOrdering( 1, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 1 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );

  Teuchos::Array<double> energy_bins;

  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
                                                              1, energy_bins );

  TEST_EQUALITY_CONST( energy_bins.size(), 14 );
  TEST_EQUALITY_CONST( energy_bins.front(), 1e-3 );
  TEST_EQUALITY_CONST( energy_bins.back(), 20.0 );

  std::unordered_map<Geometry::ModuleTraits::EntityId,double>
    cell_id_vols;

  hdf5_file_handler.getEstimatorEntities( 1, cell_id_vols );

  TEST_EQUALITY_CONST( cell_id_vols.size(), 55 );

  // Check that estimator 2 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isCellEstimator( 2 ) );

  hdf5_file_handler.getEstimatorMultiplier( 2, multiplier );

  TEST_EQUALITY_CONST( multiplier, 1.0 );

  hdf5_file_handler.getEstimatorResponseFunctionOrdering(
                                               2, response_function_ordering );

  TEST_EQUALITY_CONST( response_function_ordering.size(), 2 );
  TEST_EQUALITY_CONST( response_function_ordering[0], 0 );
  TEST_EQUALITY_CONST( response_function_ordering[1], 1 );

  hdf5_file_handler.getEstimatorDimensionOrdering( 2, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 2 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );
  TEST_EQUALITY_CONST( dimension_ordering[1],
                       MonteCarlo::COLLISION_NUMBER_DIMENSION );

  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
                                                              2, energy_bins );

  TEST_EQUALITY_CONST( energy_bins.size(), 14 );
  TEST_EQUALITY_CONST( energy_bins.front(), 1e-3 );
  TEST_EQUALITY_CONST( energy_bins.back(), 20.0 );

  Teuchos::Array<unsigned> collision_bins;

  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
                                                           2, collision_bins );

  TEST_EQUALITY_CONST( collision_bins.size(), 4 );
  TEST_EQUALITY_CONST( collision_bins.front(), 0 );
  TEST_EQUALITY_CONST( collision_bins.back(), 10 );

  cell_id_vols.clear();
  hdf5_file_handler.getEstimatorEntities( 2, cell_id_vols );
  
  TEST_EQUALITY_CONST( cell_id_vols.size(), 37 );

  // Check that estimator 4 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isCellEstimator( 4 ) );

  hdf5_file_handler.getEstimatorMultiplier( 4, multiplier );

  TEST_EQUALITY_CONST( multiplier, 1.0 );

  hdf5_file_handler.getEstimatorDimensionOrdering( 4, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 1 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );

  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
                                                              4, energy_bins );

  TEST_EQUALITY_CONST( energy_bins.size(), 14 );
  TEST_EQUALITY_CONST( energy_bins.front(), 1e-3 );
  TEST_EQUALITY_CONST( energy_bins.back(), 20.0 );

  cell_id_vols.clear();
  hdf5_file_handler.getEstimatorEntities( 4, cell_id_vols );
  
  TEST_EQUALITY_CONST( cell_id_vols.size(), 3 );

  // Check that estimator 9 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isSurfaceEstimator( 9 ) );

  hdf5_file_handler.getEstimatorMultiplier( 9, multiplier );

  TEST_EQUALITY_CONST( multiplier, 2.0 );

  hdf5_file_handler.getEstimatorDimensionOrdering( 9, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 2 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::COSINE_DIMENSION );
  TEST_EQUALITY_CONST( dimension_ordering[1], MonteCarlo::ENERGY_DIMENSION );

  Teuchos::Array<double> cosine_bins;

  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::COSINE_DIMENSION>(
                                                              9, cosine_bins );

  TEST_EQUALITY_CONST( cosine_bins.size(), 5 );
  TEST_EQUALITY_CONST( cosine_bins.front(), -1.0 );
  TEST_EQUALITY_CONST( cosine_bins.back(), 1.0 );

  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
                                                              9, energy_bins );

  TEST_EQUALITY_CONST( energy_bins.size(), 14 );
  TEST_EQUALITY_CONST( energy_bins.front(), 1e-3 );
  TEST_EQUALITY_CONST( energy_bins.back(), 20.0 );

  std::unordered_map<Geometry::ModuleTraits::EntityId,double>
    surface_id_areas;
  hdf5_file_handler.getEstimatorEntities( 9, surface_id_areas );

  TEST_EQUALITY_CONST( surface_id_areas.size(), 3 );

  // Check that estimator 10 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isSurfaceEstimator( 10 ) );

  hdf5_file_handler.getEstimatorMultiplier( 10, multiplier );

  TEST_EQUALITY_CONST( multiplier, 2.0 );

  hdf5_file_handler.getEstimatorDimensionOrdering( 10, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 2 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::COSINE_DIMENSION );
  TEST_EQUALITY_CONST( dimension_ordering[1],
                       MonteCarlo::COLLISION_NUMBER_DIMENSION );

  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::COSINE_DIMENSION>(
                                                             10, cosine_bins );

  TEST_EQUALITY_CONST( cosine_bins.size(), 5 );
  TEST_EQUALITY_CONST( cosine_bins.front(), -1.0 );
  TEST_EQUALITY_CONST( cosine_bins.back(), 1.0 );

  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
                                                          10, collision_bins );

  TEST_EQUALITY_CONST( collision_bins.size(), 4 );
  TEST_EQUALITY_CONST( collision_bins.front(), 0 );
  TEST_EQUALITY_CONST( collision_bins.back(), 10 );

  surface_id_areas.clear();
  hdf5_file_handler.getEstimatorEntities( 10, surface_id_areas );

  TEST_EQUALITY_CONST( surface_id_areas.size(), 3 );

  // Check that estimator 11 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isMeshEstimator( 11 ) );

  hdf5_file_handler.getEstimatorMultiplier( 11, multiplier );

  TEST_EQUALITY_CONST( multiplier, 2.0 );

  hdf5_file_handler.getEstimatorDimensionOrdering( 11, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 2 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );
  TEST_EQUALITY_CONST( dimension_ordering[1],
                       MonteCarlo::COLLISION_NUMBER_DIMENSION );

  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
                                                             11, energy_bins );

  TEST_EQUALITY_CONST( energy_bins.size(), 14 );
  TEST_EQUALITY_CONST( energy_bins.front(), 1e-3 );
  TEST_EQUALITY_CONST( energy_bins.back(), 20.0 );

  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
                                                          11, collision_bins );

  TEST_EQUALITY_CONST( collision_bins.size(), 4 );
  TEST_EQUALITY_CONST( collision_bins.front(), 0 );
  TEST_EQUALITY_CONST( collision_bins.back(), 10 );

  std::unordered_map<moab::EntityHandle,double>
    tet_id_vols;
  hdf5_file_handler.getEstimatorEntities( 11, tet_id_vols );

  TEST_EQUALITY_CONST( tet_id_vols.size(), 6 );

  // Check that estimator 12 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isCellEstimator( 12 ) );

  hdf5_file_handler.getEstimatorMultiplier( 12, multiplier );

  TEST_EQUALITY_CONST( multiplier, 2.0 );

  hdf5_file_handler.getEstimatorResponseFunctionOrdering(
                                              12, response_function_ordering );

  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY_CONST( response_function_ordering[0], 0 );

  dimension_ordering.clear();
  hdf5_file_handler.getEstimatorDimensionOrdering( 12, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 1 );
  TEST_EQUALITY_CONST( dimension_ordering[0],
                       MonteCarlo::SOURCE_ENERGY_DIMENSION );
  
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::SOURCE_ENERGY_DIMENSION>(
                                                             12, energy_bins );

  TEST_EQUALITY_CONST( energy_bins.size(), 14 );
  TEST_EQUALITY_CONST( energy_bins.front(), 1e-3 );
  TEST_EQUALITY_CONST( energy_bins.back(), 20.0 );
  
  cell_id_vols.clear();
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

  TEST_EQUALITY_CONST( dimension_ordering.size(), 1 );
  TEST_EQUALITY_CONST( dimension_ordering[0],
                       MonteCarlo::SOURCE_TIME_DIMENSION );

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
  
  // Check that estimator 15 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isSurfaceEstimator( 15 ) );

  hdf5_file_handler.getEstimatorMultiplier( 15, multiplier );

  TEST_EQUALITY_CONST( multiplier, 2.0 );

  response_function_ordering.clear();
  hdf5_file_handler.getEstimatorResponseFunctionOrdering(
                                              15, response_function_ordering );

  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY_CONST( response_function_ordering.front(), 4294967295 );

  dimension_ordering.clear();
  hdf5_file_handler.getEstimatorDimensionOrdering( 15, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 0 );

  surface_id_areas.clear();
  hdf5_file_handler.getEstimatorEntities( 15, surface_id_areas );

  TEST_EQUALITY_CONST( surface_id_areas.size(), 3 );
  TEST_ASSERT( surface_id_areas.count( 7 ) );
  TEST_ASSERT( surface_id_areas.count( 16 ) );
  TEST_ASSERT( surface_id_areas.count( 25 ) );

  // Check that estimator 16 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isSurfaceEstimator( 16 ) );

  hdf5_file_handler.getEstimatorMultiplier( 16, multiplier );

  TEST_EQUALITY_CONST( multiplier, 2.0 );

  response_function_ordering.clear();
  hdf5_file_handler.getEstimatorResponseFunctionOrdering(
                                              16, response_function_ordering );

  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY_CONST( response_function_ordering.front(), 4294967295 );

  dimension_ordering.clear();
  hdf5_file_handler.getEstimatorDimensionOrdering( 16, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 0 );

  surface_id_areas.clear();
  hdf5_file_handler.getEstimatorEntities( 16, surface_id_areas );

  TEST_EQUALITY_CONST( surface_id_areas.size(), 3 );
  TEST_ASSERT( surface_id_areas.count( 7 ) );
  TEST_ASSERT( surface_id_areas.count( 16 ) );
  TEST_ASSERT( surface_id_areas.count( 25 ) );

  // Check that estimator 17 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isMeshEstimator( 17 ) );
  
  hdf5_file_handler.getEstimatorMultiplier( 17, multiplier );
  
  TEST_EQUALITY_CONST( multiplier, 2.0 );

  hdf5_file_handler.getEstimatorDimensionOrdering( 17, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 1 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );

  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
                                                             17, energy_bins );

  TEST_EQUALITY_CONST( energy_bins.size(), 14 );
  TEST_EQUALITY_CONST( energy_bins.front(), 1e-3 );
  TEST_EQUALITY_CONST( energy_bins.back(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that cached estimators can be created and registered
TEUCHOS_UNIT_TEST( StandardEstimatorFactory_DagMC,
                   createAndRegisterCachedEstimators )
{
  TEST_NOTHROW( estimator_factory->createAndRegisterCachedEstimators() );

  // Check that all of the estimators got created
  TEST_EQUALITY_CONST( event_handler->getNumberOfObservers(), 18 );

  std::string estimator_file_name( "estimator_factory_dagmc_full.h5" );

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
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 0 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 1 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 2 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 3 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 4 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 5 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 6 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 7 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 8 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 9 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 10 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 11 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 12 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 13 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 14 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 15 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 16 ) );
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 17 ) );

  // Check that estimator 0 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isCellEstimator( 0 ) );

  double multiplier;
  hdf5_file_handler.getEstimatorMultiplier( 0, multiplier );

  TEST_EQUALITY_CONST( multiplier, 1.0 );

  Teuchos::Array<unsigned> response_function_ordering;
  hdf5_file_handler.getEstimatorResponseFunctionOrdering(
                                              0, response_function_ordering );

  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY_CONST( response_function_ordering.front(), 4294967295 );

  Teuchos::Array<MonteCarlo::PhaseSpaceDimension> dimension_ordering;
  hdf5_file_handler.getEstimatorDimensionOrdering( 0, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 0 );

  std::unordered_map<Geometry::ModuleTraits::EntityId,double>
    cell_id_vols;
  hdf5_file_handler.getEstimatorEntities( 0, cell_id_vols );

  TEST_EQUALITY_CONST( cell_id_vols.size(), 55 );

  // Check that estimator 3 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isCellEstimator( 3 ) );

  hdf5_file_handler.getEstimatorMultiplier( 3, multiplier );

  TEST_EQUALITY_CONST( multiplier, 1.0 );

  response_function_ordering.clear();
  hdf5_file_handler.getEstimatorResponseFunctionOrdering(
                                              3, response_function_ordering );

  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY_CONST( response_function_ordering.front(), 4294967295 );

  dimension_ordering.clear();
  hdf5_file_handler.getEstimatorDimensionOrdering( 3, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 0 );

  cell_id_vols.clear();
  hdf5_file_handler.getEstimatorEntities( 3, cell_id_vols );

  TEST_EQUALITY_CONST( cell_id_vols.size(), 36 );

  // Check that estimator 5 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isSurfaceEstimator( 5 ) );

  hdf5_file_handler.getEstimatorMultiplier( 5, multiplier );

  TEST_EQUALITY_CONST( multiplier, 1.0 );

  response_function_ordering.clear();
  hdf5_file_handler.getEstimatorResponseFunctionOrdering(
                                              5, response_function_ordering );

  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY_CONST( response_function_ordering.front(), 4294967295 );

  dimension_ordering.clear();
  hdf5_file_handler.getEstimatorDimensionOrdering( 5, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 0 );

  std::unordered_map<Geometry::ModuleTraits::EntityId,double>
    surface_id_areas;
  hdf5_file_handler.getEstimatorEntities( 5, surface_id_areas );

  TEST_EQUALITY_CONST( surface_id_areas.size(), 7 );

  // Check that estimator 6 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isSurfaceEstimator( 6 ) );

  hdf5_file_handler.getEstimatorMultiplier( 6, multiplier );

  TEST_EQUALITY_CONST( multiplier, 1.0 );

  response_function_ordering.clear();
  hdf5_file_handler.getEstimatorResponseFunctionOrdering(
                                              6, response_function_ordering );

  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY_CONST( response_function_ordering.front(), 4294967295 );

  dimension_ordering.clear();
  hdf5_file_handler.getEstimatorDimensionOrdering( 6, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 0 );

  surface_id_areas.clear();
  hdf5_file_handler.getEstimatorEntities( 6, surface_id_areas );

  TEST_EQUALITY_CONST( surface_id_areas.size(), 7 );

  // Check that estimator 7 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isSurfaceEstimator( 7 ) );

  hdf5_file_handler.getEstimatorMultiplier( 7, multiplier );

  TEST_EQUALITY_CONST( multiplier, 1.0 );

  response_function_ordering.clear();
  hdf5_file_handler.getEstimatorResponseFunctionOrdering(
                                              7, response_function_ordering );

  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY_CONST( response_function_ordering.front(), 4294967295 );

  dimension_ordering.clear();
  hdf5_file_handler.getEstimatorDimensionOrdering( 7, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 0 );

  surface_id_areas.clear();
  hdf5_file_handler.getEstimatorEntities( 7, surface_id_areas );

  TEST_EQUALITY_CONST( surface_id_areas.size(), 7 );

  // Check that estimator 8 has the correct properties
  TEST_ASSERT( hdf5_file_handler.isSurfaceEstimator( 8 ) );

  hdf5_file_handler.getEstimatorMultiplier( 8, multiplier );

  TEST_EQUALITY_CONST( multiplier, 1.0 );

  response_function_ordering.clear();
  hdf5_file_handler.getEstimatorResponseFunctionOrdering(
                                              8, response_function_ordering );

  TEST_EQUALITY_CONST( response_function_ordering.size(), 1 );
  TEST_EQUALITY_CONST( response_function_ordering.front(), 4294967295 );

  dimension_ordering.clear();
  hdf5_file_handler.getEstimatorDimensionOrdering( 8, dimension_ordering );

  TEST_EQUALITY_CONST( dimension_ordering.size(), 0 );

  surface_id_areas.clear();
  hdf5_file_handler.getEstimatorEntities( 8, surface_id_areas );

  TEST_EQUALITY_CONST( surface_id_areas.size(), 7 );
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
