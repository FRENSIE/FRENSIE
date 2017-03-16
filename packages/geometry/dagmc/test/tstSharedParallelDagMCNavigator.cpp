//---------------------------------------------------------------------------//
//!
//! \file   tstSharedParallelDagMC.cpp
//! \author Alex Robinson
//! \brief  DagMC wrapper class shared parallel unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Tuple.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Geometry_DagMCNavigator.hpp"
#include "Geometry_DagMCModel.hpp"
#include "Geometry_DagMCModelPropertiesFactory.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Geometry::DagMCModel> model;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a parallel internal ray trace can be done
TEUCHOS_UNIT_TEST( DagMC, parallel_ray_trace )
{
  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  Teuchos::Array<Utility::Quad<Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle> >
    surface_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  Teuchos::Array<Utility::Quad<double,double,double,double> >
    distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  #pragma omp parallel num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
  {
    // Create the thread navigators
    std::shared_ptr<Geometry::Navigator> navigator =
      model->createNavigator();
    
    // Initialize the ray
    if( Utility::GlobalOpenMPSession::getThreadId()%6 == 0 )
      navigator->setInternalRay( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 1 )
      navigator->setInternalRay( -41.0, -41.0, 59.0, 0.0, 0.0, 1.0 );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 2 )
      navigator->setInternalRay( -39.0, -39.0, 59.0, 0.0, 0.0, 1.0 );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 3 )
      navigator->setInternalRay( -38.0, -38.0, 59.0, 0.0, 0.0, 1.0 );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 4)
      navigator->setInternalRay( -37.0, -37.0, 59.0, 0.0, 0.0, 1.0 );
    else
      navigator->setInternalRay( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );

    // Find the cell that contains the ray
    Geometry::ModuleTraits::InternalCellHandle cell =
      navigator->getCellContainingInternalRay();

    Utility::get<0>(cell_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      cell;

    // Fire the ray
    Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;

    double distance_to_surface_hit =
      navigator->fireInternalRay( surface_hit );

    Utility::get<0>(surface_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      surface_hit;

    Utility::get<0>(distances[Utility::GlobalOpenMPSession::getThreadId()]) =
      distance_to_surface_hit;

    // Advance the ray to the boundary surface
    navigator->advanceInternalRayToCellBoundary();

    cell = navigator->getCellContainingInternalRay();

    Utility::get<1>(cell_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      cell;

    // Fire the ray
    distance_to_surface_hit = navigator->fireInternalRay( surface_hit );

    Utility::get<1>(surface_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      surface_hit;

    Utility::get<1>(distances[Utility::GlobalOpenMPSession::getThreadId()]) =
      distance_to_surface_hit;

    // Advance the ray to the boundary surface
    navigator->advanceInternalRayToCellBoundary();

    cell = navigator->getCellContainingInternalRay();

    Utility::get<2>(cell_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      cell;

    // Fire the ray
    distance_to_surface_hit = navigator->fireInternalRay( surface_hit );

    Utility::get<2>(surface_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      surface_hit;

    Utility::get<2>(distances[Utility::GlobalOpenMPSession::getThreadId()]) =
      distance_to_surface_hit;

    // Advance the ray a substep
    navigator->advanceInternalRayBySubstep( 0.5*distance_to_surface_hit);

    // Change the ray direction
    navigator->changeInternalRayDirection( 0.0, 0.0, -1.0 );

    // Fire the ray
    distance_to_surface_hit = navigator->fireInternalRay( surface_hit );

    Utility::get<3>(surface_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      surface_hit;

    Utility::get<3>(distances[Utility::GlobalOpenMPSession::getThreadId()]) =
      distance_to_surface_hit;
  }

  // Check that each of the rays traces were successful
  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    correct_cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_cell_ids[i] = std::make_tuple( 53, 54, 55 );

  UTILITY_TEST_COMPARE_ARRAYS( cell_ids, correct_cell_ids );

  Teuchos::Array<Utility::Quad<Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle> >
    correct_surface_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_surface_ids[i] = std::make_tuple( 242, 248, 254, 248 );

  UTILITY_TEST_COMPARE_ARRAYS( surface_ids, correct_surface_ids );

  Teuchos::Array<Utility::Quad<double,double,double,double> >
    correct_distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_distances.size(); ++i )
    correct_distances[i] = std::make_tuple( 1.959999084, 2.54, 2.54, 1.27 );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( distances, correct_distances, 1e-6 );
}

//---------------------------------------------------------------------------//
// Check that a parallel internal ray trace can be done
TEUCHOS_UNIT_TEST( DagMC, parallel_ray_trace_with_reflection )
{
  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle> >
    surface_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  Teuchos::Array<Utility::Trip<double,double,double> >
    distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  Teuchos::Array<Utility::Pair<int,int> >
    reflection( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  #pragma omp parallel num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
  {
    // Create the thread navigators
    std::shared_ptr<Geometry::Navigator> navigator =
      model->createNavigator();

    navigator->setInternalRay( -40.0, -40.0, 108.0, 0.0, 0.0, 1.0 );

    // Find the cell that contains the ray
    Geometry::ModuleTraits::InternalCellHandle cell =
      navigator->getCellContainingInternalRay();

    Utility::get<0>(cell_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      cell;

    // Fire the ray
    Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;

    double distance_to_surface_hit =
      navigator->fireInternalRay( surface_hit );

    Utility::get<0>(surface_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      surface_hit;

    Utility::get<0>(distances[Utility::GlobalOpenMPSession::getThreadId()]) =
      distance_to_surface_hit;

    // Advance the ray to the boundary surface
    Utility::get<0>(reflection[Utility::GlobalOpenMPSession::getThreadId()]) =
      navigator->advanceInternalRayToCellBoundary();

    cell = navigator->getCellContainingInternalRay();

    Utility::get<1>(cell_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      cell;

    distance_to_surface_hit = navigator->fireInternalRay( surface_hit );

    Utility::get<1>(surface_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      surface_hit;

    Utility::get<1>(distances[Utility::GlobalOpenMPSession::getThreadId()]) =
      distance_to_surface_hit;

    // Advance the ray to the boundary surface (reflecting)
    Utility::get<1>(reflection[Utility::GlobalOpenMPSession::getThreadId()]) =
      navigator->advanceInternalRayToCellBoundary();

    cell = navigator->getCellContainingInternalRay();

    Utility::get<2>(cell_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      cell;

    distance_to_surface_hit = navigator->fireInternalRay( surface_hit );

    Utility::get<2>(surface_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      surface_hit;

    Utility::get<2>(distances[Utility::GlobalOpenMPSession::getThreadId()]) =
      distance_to_surface_hit;
  }

  // Check that each of the rays traces were successful
  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    correct_cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_cell_ids[i] = std::make_tuple( 82, 83, 83 );

  UTILITY_TEST_COMPARE_ARRAYS( cell_ids, correct_cell_ids );

  Teuchos::Array<Utility::Trip<Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle> >
    correct_surface_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_surface_ids[i] = std::make_tuple( 394, 408, 394 );

  UTILITY_TEST_COMPARE_ARRAYS( surface_ids, correct_surface_ids );

  Teuchos::Array<Utility::Trip<double,double,double> >
    correct_distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_distances.size(); ++i )
    correct_distances[i] = std::make_tuple( 1.474, 17.526, 17.526 );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( distances, correct_distances, 1e-6 );

  Teuchos::Array<Utility::Pair<int,int> >
    correct_reflection( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_reflection.size(); ++i )
    correct_reflection[i] = std::make_tuple( false, true );

  UTILITY_TEST_COMPARE_ARRAYS( reflection, correct_reflection );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string xml_file_name;
int threads;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_xml_file",
                   &xml_file_name,
                   "Model properties xml file name" );

  clp().setOption( "threads",
                   &threads,
                   "Number of threads to use" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  Teuchos::RCP<const Teuchos::ParameterList> raw_model_properties =
    Teuchos::getParametersFromXmlFile( xml_file_name );

  std::shared_ptr<const Geometry::DagMCModelProperties> model_properties =
    Geometry::DagMCModelPropertiesFactory::createProperties(
                                                       *raw_model_properties );

  std::shared_ptr<Geometry::DagMCModel> tmp_model =
    Geometry::DagMCModel::getInstance();

  tmp_model->initialize( *model_properties );

  model = tmp_model;

  // Set the number of threads to use
  Utility::GlobalOpenMPSession::setNumberOfThreads( threads );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstSharedParallelDagMC.cpp
//---------------------------------------------------------------------------//
