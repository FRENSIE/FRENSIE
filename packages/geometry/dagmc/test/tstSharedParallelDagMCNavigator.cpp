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

// FRENSIE Includes
#include "Geometry_DagMCNavigator.hpp"
#include "Geometry_DagMCModel.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Geometry::DagMCModel> model;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a parallel internal ray trace can be done
FRENSIE_UNIT_TEST( DagMC, parallel_ray_trace )
{
  std::vector<std::tuple<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  std::vector<std::tuple<Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle> >
    surface_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  std::vector<std::tuple<double,double,double,double> >
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
      navigator->fireInternalRay( &surface_hit );

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
    distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

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
    distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

    Utility::get<2>(surface_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      surface_hit;

    Utility::get<2>(distances[Utility::GlobalOpenMPSession::getThreadId()]) =
      distance_to_surface_hit;

    // Advance the ray a substep
    navigator->advanceInternalRayBySubstep( 0.5*distance_to_surface_hit);

    // Change the ray direction
    navigator->changeInternalRayDirection( 0.0, 0.0, -1.0 );

    // Fire the ray
    distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

    Utility::get<3>(surface_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      surface_hit;

    Utility::get<3>(distances[Utility::GlobalOpenMPSession::getThreadId()]) =
      distance_to_surface_hit;
  }

  // Check that each of the rays traces were successful
  std::vector<std::tuple<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    correct_cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_cell_ids[i] = std::make_tuple( 53, 54, 55 );

  FRENSIE_CHECK_EQUAL( cell_ids, correct_cell_ids );

  std::vector<std::tuple<Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle> >
    correct_surface_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_surface_ids[i] = std::make_tuple( 242, 248, 254, 248 );

  FRENSIE_CHECK_EQUAL( surface_ids, correct_surface_ids );

  std::vector<std::tuple<double,double,double,double> >
    correct_distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_distances.size(); ++i )
    correct_distances[i] = std::make_tuple( 1.959999084, 2.54, 2.54, 1.27 );

  FRENSIE_CHECK_FLOATING_EQUALITY( distances, correct_distances, 1e-6 );
}

//---------------------------------------------------------------------------//
// Check that a parallel internal ray trace can be done
FRENSIE_UNIT_TEST( DagMC, parallel_ray_trace_with_reflection )
{
  std::vector<std::tuple<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  std::vector<std::tuple<Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle> >
    surface_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  std::vector<std::tuple<double,double,double> >
    distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  std::vector<std::tuple<int,int> >
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
      navigator->fireInternalRay( &surface_hit );

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

    distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

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

    distance_to_surface_hit = navigator->fireInternalRay( &surface_hit );

    Utility::get<2>(surface_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      surface_hit;

    Utility::get<2>(distances[Utility::GlobalOpenMPSession::getThreadId()]) =
      distance_to_surface_hit;
  }

  // Check that each of the rays traces were successful
  std::vector<std::tuple<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    correct_cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_cell_ids[i] = std::make_tuple( 82, 83, 83 );

  FRENSIE_CHECK_EQUAL( cell_ids, correct_cell_ids );

  std::vector<std::tuple<Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle,
                               Geometry::ModuleTraits::InternalSurfaceHandle> >
    correct_surface_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_surface_ids[i] = std::make_tuple( 394, 408, 394 );

  FRENSIE_CHECK_EQUAL( surface_ids, correct_surface_ids );

  std::vector<std::tuple<double,double,double> >
    correct_distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_distances.size(); ++i )
    correct_distances[i] = std::make_tuple( 1.474, 17.526, 17.526 );

  FRENSIE_CHECK_FLOATING_EQUALITY( distances, correct_distances, 1e-6 );

  std::vector<std::tuple<int,int> >
    correct_reflection( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_reflection.size(); ++i )
    correct_reflection[i] = std::make_tuple( false, true );

  FRENSIE_CHECK_EQUAL( reflection, correct_reflection );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_dagmc_geom_file_name;
int threads;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_cad_file",
                                        test_dagmc_geom_file_name, "",
                                        "Test CAD file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "threads",
                                        threads, 1,
                                        "Number of threads to use" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  Geometry::DagMCModelProperties local_properties( test_dagmc_geom_file_name );
  
  local_properties.setFacetTolerance( 1e-3 );
  local_properties.setTerminationCellPropertyName( "graveyard" );
  local_properties.setMaterialPropertyName( "mat" );
  local_properties.setDensityPropertyName( "rho" );
  local_properties.setEstimatorPropertyName( "tally" );

  std::shared_ptr<Geometry::DagMCModel> tmp_model =
    Geometry::DagMCModel::getInstance();

  tmp_model->initialize( local_properties );

  model = tmp_model;

  // Set the number of threads to use
  Utility::GlobalOpenMPSession::setNumberOfThreads( threads );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstSharedParallelDagMC.cpp
//---------------------------------------------------------------------------//
