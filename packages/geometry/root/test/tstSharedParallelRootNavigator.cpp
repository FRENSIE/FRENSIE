//---------------------------------------------------------------------------//
//!
//! \file   tstSharedParallelRoot.cpp
//! \author Alex Robinson
//! \brief  Root wrapper class shared parallel unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "Geometry_RootNavigator.hpp"
#include "Geometry_RootModel.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Geometry::RootModel> model;

//---------------------------------------------------------------------------//
// Check that a parallel internal ray trace can be done
FRENSIE_UNIT_TEST( Root, parallel_ray_trace )
{
  std::vector<std::tuple<Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle,
                               Geometry::ModuleTraits::InternalCellHandle> >
    cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  std::vector<std::tuple<double,double,double> >
    distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  #pragma omp parallel num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
  {
    // Create the thread navigators
    std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();
    
    // Initialize the ray
    if( Utility::GlobalOpenMPSession::getThreadId()%6 == 0 )
      navigator->setInternalRay( 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 1 )
      navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 2 )
      navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 3 )
      navigator->setInternalRay( 0.0, 0.0, 0.0, -1.0, 0.0, 0.0 );
    else if( Utility::GlobalOpenMPSession::getThreadId()%6 == 4)
      navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, -1.0, 0.0 );
    else
      navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, -1.0 );

    Utility::get<0>(cell_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      navigator->getCellContainingInternalRay();

    // Fire a ray through the geometry
    Utility::get<0>(distances[Utility::GlobalOpenMPSession::getThreadId()]) =
      navigator->fireInternalRay();

    // Advance the ray to the cell boundary
    navigator->advanceInternalRayToCellBoundary();

    Utility::get<1>(cell_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      navigator->getCellContainingInternalRay();

    // Fire a ray through the geometry
    double distance_to_boundary = navigator->fireInternalRay();
    
    Utility::get<1>(distances[Utility::GlobalOpenMPSession::getThreadId()]) =
      distance_to_boundary;

    // Advance the ray a substep
    navigator->advanceInternalRayBySubstep( 0.5*distance_to_boundary );

    // Change the ray direction
    double new_direction[3];

    Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle(
                                     0.0,
                                     0.0,
                                     navigator->getInternalRayDirection(),
                                     new_direction );

    navigator->changeInternalRayDirection( new_direction );

    // Fire a ray through the geometry
    Utility::get<2>(distances[Utility::GlobalOpenMPSession::getThreadId()]) =
      navigator->fireInternalRay();

    // Advance the ray to the cell boundary
    navigator->advanceInternalRayToCellBoundary();

    // Find the new cell
    Utility::get<2>(cell_ids[Utility::GlobalOpenMPSession::getThreadId()]) =
      navigator->getCellContainingInternalRay();
  }

  // Check that each of the rays traces were successful
  std::vector<std::tuple<Geometry::ModuleTraits::InternalCellHandle,
                         Geometry::ModuleTraits::InternalCellHandle,
                         Geometry::ModuleTraits::InternalCellHandle> >
    correct_cell_ids( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  
  for( unsigned i = 0; i < correct_cell_ids.size(); ++i )
    correct_cell_ids[i] = std::make_tuple( 2, 1, 3 );

  FRENSIE_CHECK_EQUAL( cell_ids, correct_cell_ids );

  std::vector<std::tuple<double,double,double> >
    correct_distances( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  for( unsigned i = 0; i < correct_distances.size(); ++i )
    correct_distances[i] = std::make_tuple( 2.5, 2.5, 5.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( distances, correct_distances, 1e-6 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_root_geom_file_name;
int threads;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_root_file",
                                        test_root_geom_file_name, "",
                                        "Test ROOT file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "threads",
                                        threads, 1,
                                        "Number of threads to use" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  Geometry::RootModelProperties local_properties( test_root_geom_file_name );
  
  std::shared_ptr<Geometry::RootModel> tmp_model =
    Geometry::RootModel::getInstance();

  tmp_model->initialize( local_properties );

  model = tmp_model;

  // Set the number of threads to use
  Utility::GlobalOpenMPSession::setNumberOfThreads( threads );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstSharedParallelRoot.cpp
//---------------------------------------------------------------------------//
