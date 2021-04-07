//---------------------------------------------------------------------------//
//!
//! \file   tstRootNavigator.cpp
//! \author Alex Robinson
//! \brief  Root navigator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <fstream>
#include <memory>

// FRENSIE Includes
#include "Geometry_RootNavigator.hpp"
#include "Geometry_RootModel.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Geometry::RootModel> model;

bool cache_test_archive;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a point location w.r.t. a given cell can be determined
FRENSIE_UNIT_TEST( RootNavigator, getPointLocation )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  // Initialize the ray
  std::shared_ptr<Geometry::Navigator::Ray>
    ray( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0, 0.0, 1.0 ) );

  // Point inside of cell 2
  Geometry::PointLocation location =
    navigator->getPointLocation( *ray, 2 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_INSIDE_CELL );

  location = navigator->getPointLocation( *ray, 1 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( *ray, 3 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  // Point on boundary between cell 2 and cell 1
  ray.reset( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                           0.0*cgs::centimeter,
                                           2.5*cgs::centimeter,
                                           0.0, 0.0, 1.0 ) );

  location = navigator->getPointLocation( *ray, 2 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_INSIDE_CELL );

  location = navigator->getPointLocation( *ray, 1 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( *ray, 3 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  // Point in cell 1
  ray.reset( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                           0.0*cgs::centimeter,
                                           4.0*cgs::centimeter,
                                           0.0, 0.0, 1.0 ) );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          2 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          1 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_INSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          3 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  // Point on boundary between cell 1 and 3
  ray.reset( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                           0.0*cgs::centimeter,
                                           5.0*cgs::centimeter,
                                           0.0, 0.0, 1.0 ) );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          2 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          1 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_INSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          3 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  // Point in cell 3
  ray.reset( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                           0.0*cgs::centimeter,
                                           6.0*cgs::centimeter,
                                           0.0, 0.0, 1.0 ) );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          2 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          1 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );

  location = navigator->getPointLocation( ray->getPosition(),
                                          ray->getDirection(),
                                          3 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_INSIDE_CELL );
}

//---------------------------------------------------------------------------//
// Check that the surface normal can be returned
FRENSIE_UNIT_TEST( RootNavigator, getSurfaceNormal )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  std::shared_ptr<Geometry::Navigator::Ray>
    ray( new Geometry::Navigator::Ray( 2.5*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       1.0, 0.0, 0.0 ) );

  double normal[3];

  navigator->getSurfaceNormal( 0, *ray, normal );

  FRENSIE_CHECK_FLOATING_EQUALITY( normal[0], 1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( normal[1], 1e-15 );
  FRENSIE_CHECK_SMALL( normal[2], 1e-15 );

  ray.reset( new Geometry::Navigator::Ray( 2.5*cgs::centimeter,
                                           0.0*cgs::centimeter,
                                           0.0*cgs::centimeter,
                                           -1.0, 0.0, 0.0 ) );

  navigator->getSurfaceNormal( 0, *ray, normal );

  FRENSIE_CHECK_FLOATING_EQUALITY( normal[0], -1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( normal[1], 1e-15 );
  FRENSIE_CHECK_SMALL( normal[2], 1e-15 );

  ray.reset( new Geometry::Navigator::Ray( 2.5*cgs::centimeter,
                                           0.0*cgs::centimeter,
                                           0.0*cgs::centimeter,
                                           1/sqrt(3), 1/sqrt(3), 1/sqrt(3) ) );

  navigator->getSurfaceNormal( 0, *ray, normal );

  FRENSIE_CHECK_FLOATING_EQUALITY( normal[0], 1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( normal[1], 1e-15 );
  FRENSIE_CHECK_SMALL( normal[2], 1e-15 );

  ray.reset( new Geometry::Navigator::Ray( 2.5*cgs::centimeter,
                                           0.0*cgs::centimeter,
                                           0.0*cgs::centimeter,
                                           -1/sqrt(3), -1/sqrt(3), -1/sqrt(3) ) );

  navigator->getSurfaceNormal( 0, *ray, normal );

  FRENSIE_CHECK_FLOATING_EQUALITY( normal[0], -1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( normal[1], 1e-15 );
  FRENSIE_CHECK_SMALL( normal[2], 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cell containing the external ray can be found can cached
FRENSIE_UNIT_TEST( RootNavigator, findCellContainingRay_cache )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  // Initialize the found cell cache
  Geometry::Navigator::CellIdSet found_cell_cache;

  // Initialize the ray
  std::shared_ptr<Geometry::Navigator::Ray>
    ray( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0, 0.0, 1.0 ) );

  Geometry::Navigator::EntityId cell;

  cell = navigator->findCellContainingRay( *ray, found_cell_cache );

  FRENSIE_CHECK_EQUAL( cell, 2 );

  // Check that the direction is used to correctly determine the cell when
  // on a boundary
  ray.reset( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                           0.0*cgs::centimeter,
                                           2.5*cgs::centimeter,
                                           0.0, 0.0, 1.0 ) );

  cell = navigator->findCellContainingRay( *ray, found_cell_cache );

  FRENSIE_CHECK_EQUAL( cell, 1 );

  ray.reset( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                           0.0*cgs::centimeter,
                                           2.5*cgs::centimeter,
                                           0.0, 0.0, -1.0 ) );

  cell = navigator->findCellContainingRay( ray->getPosition(),
                                           ray->getDirection() );

  FRENSIE_CHECK_EQUAL( cell, 2 );

  // Check the found cell cache
  FRENSIE_CHECK_EQUAL( found_cell_cache.size(), 2 );
  FRENSIE_CHECK( found_cell_cache.count( 1 ) );
  FRENSIE_CHECK( found_cell_cache.count( 2 ) );
}

//---------------------------------------------------------------------------//
// Check that a cell containing an external ray can be determined
FRENSIE_UNIT_TEST( RootNavigator, findCellContainingRay )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  // Initialize the ray
  std::shared_ptr<Geometry::Navigator::Ray>
    ray( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0, 0.0, 1.0 ) );

  Geometry::Navigator::EntityId cell;

  cell = navigator->findCellContainingRay( *ray );

  FRENSIE_CHECK_EQUAL( cell, 2 );

  // Check that the direction is used to correctly determine the cell when
  // on a boundary
  ray.reset( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                           0.0*cgs::centimeter,
                                           2.5*cgs::centimeter,
                                           0.0, 0.0, 1.0 ) );

  cell = navigator->findCellContainingRay( *ray );

  FRENSIE_CHECK_EQUAL( cell, 1 );

  ray.reset( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                           0.0*cgs::centimeter,
                                           2.5*cgs::centimeter,
                                           0.0, 0.0, -1.0 ) );

  cell = navigator->findCellContainingRay( ray->getPosition(),
                                           ray->getDirection() );

  FRENSIE_CHECK_EQUAL( cell, 2 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be set
FRENSIE_UNIT_TEST( RootNavigator, setState )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  std::shared_ptr<Geometry::Navigator::Ray>
    ray( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0*cgs::centimeter,
                                       0.0, 0.0, 1.0 ) );

  FRENSIE_CHECK( !navigator->isStateSet() );

  navigator->setState( *ray );

  FRENSIE_CHECK( navigator->isStateSet() );

  FRENSIE_CHECK_EQUAL( navigator->getPosition()[0],
                       0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[1],
                       0.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[2],
                       0.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 1.0 );

  FRENSIE_CHECK_EQUAL( navigator->getCurrentCell(), 2 );

  ray.reset( new Geometry::Navigator::Ray( 1.0*cgs::centimeter,
                                           1.0*cgs::centimeter,
                                           1.0*cgs::centimeter,
                                           0.0, 1.0, 0.0 ) );

  navigator->setState( ray->getPosition(), ray->getDirection() );

  FRENSIE_CHECK_EQUAL( navigator->getPosition()[0],
                       1.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[1],
                       1.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[2],
                       1.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 0.0 );

  FRENSIE_CHECK_EQUAL( navigator->getCurrentCell(), 2 );

  navigator->setState( -1.0*cgs::centimeter,
                             -1.0*cgs::centimeter,
                             -1.0*cgs::centimeter,
                             1.0, 0.0, 0.0,
                             2 );

  // Check that the internal ray state does not change is a find call is made
  ray.reset( new Geometry::Navigator::Ray( 0.0*cgs::centimeter,
                                           0.0*cgs::centimeter,
                                           2.5*cgs::centimeter,
                                           0.0, 0.0, 1.0 ) );

  Geometry::Navigator::EntityId cell =
    navigator->findCellContainingRay( *ray );

  FRENSIE_CHECK_EQUAL( navigator->getPosition()[0],
                       -1.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[1],
                       -1.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[2],
                       -1.0*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 0.0 );

  FRENSIE_CHECK_EQUAL( cell, 1 );
  FRENSIE_CHECK_EQUAL( navigator->getCurrentCell(), 2 );
}

//---------------------------------------------------------------------------//
// Check that the distance to closest boundary
FRENSIE_UNIT_TEST( RootNavigator, getDistanceToClosestBoundary )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  // Initialize the ray
  navigator->setState( 0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  // Fire a ray through the geometry
  Geometry::Navigator::Length safety_distance =
    navigator->getDistanceToClosestBoundary();

  FRENSIE_CHECK_FLOATING_EQUALITY( safety_distance,
                                   2.5*cgs::centimeter,
                                   1e-9 );

  // Initialize the ray
  navigator->setState( 2.5*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  // Fire a ray through the geometry
  safety_distance = navigator->getDistanceToClosestBoundary();

  FRENSIE_CHECK_FLOATING_EQUALITY( safety_distance,
                                   0.0*cgs::centimeter,
                                   1e-9 );

  // Initialize the ray
  navigator->setState( 4.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  // Fire a ray through the geometry
  safety_distance = navigator->getDistanceToClosestBoundary();

  FRENSIE_CHECK_FLOATING_EQUALITY( safety_distance,
                                   1.0*cgs::centimeter,
                                   1e-9 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be fired
FRENSIE_UNIT_TEST( RootNavigator, fireRay )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  // Initialize the ray
  navigator->setState( 0.0*cgs::centimeter,
                             0.0*cgs::centimeter,
                             0.0*cgs::centimeter,
                             0.0, 0.0, 1.0 );

  // Fire a ray through the geometry
  Geometry::Navigator::Length distance_to_boundary =
    navigator->fireRay();

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_boundary,
                                   2.5*cgs::centimeter,
                                   1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray direction can be changed
FRENSIE_UNIT_TEST( RootNavigator, changeDirection )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  // Initialize the ray
  navigator->setState( 0.0*cgs::centimeter,
                             0.0*cgs::centimeter,
                             0.0*cgs::centimeter,
                             0.0, 0.0, 1.0 );

  navigator->changeDirection( 1.0, 0.0, 0.0 );

  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 0.0 );

  {
    const double direction[3] = {0.0, 1.0, 0.0};

    navigator->changeDirection( direction );
  }

  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a simple internal ray trace can be done
FRENSIE_UNIT_TEST( RootNavigator, ray_trace )
{
  std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

  // Initialize the ray
  navigator->setState( 0.0*cgs::centimeter,
                             0.0*cgs::centimeter,
                             0.0*cgs::centimeter,
                             0.0, 0.0, 1.0 );

  Geometry::Navigator::EntityId cell =
    navigator->getCurrentCell();

  FRENSIE_CHECK_EQUAL( cell, 2 );

  // Fire a ray through the geometry
  Geometry::Navigator::Length distance_to_boundary =
    navigator->fireRay();

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_boundary,
                                   2.5*cgs::centimeter,
                                   1e-9 );

  double surface_normal[3];

  // Advance the ray to the cell boundary
  navigator->advanceToCellBoundary( surface_normal );

  FRENSIE_CHECK_EQUAL( surface_normal[0], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[1], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[2], 1.0 );

  // Find the new cell
  cell = navigator->getCurrentCell();

  FRENSIE_CHECK_EQUAL( cell, 1 );

  // Fire a ray through the geometry
  distance_to_boundary = navigator->fireRay();

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_boundary,
                                   2.5*cgs::centimeter,
                                   1e-6 );

  // Advance the ray a substep
  navigator->advanceBySubstep( 0.5*distance_to_boundary );

  // Change the ray direction
  navigator->changeDirection( 0.0, 1.0, 0.0 );

  // Fire a ray through the geometry
  distance_to_boundary = navigator->fireRay();

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_boundary,
                                   5.0*cgs::centimeter,
                                   1e-9 );

  // Advance the ray to the cell boundary
  navigator->advanceToCellBoundary();

  // Find the new cell
  cell = navigator->getCurrentCell();

  FRENSIE_CHECK_EQUAL( cell, 3 );
}

//---------------------------------------------------------------------------//
// Check that a simple internal ray trace can be done
FRENSIE_UNIT_TEST( RootNavigator, advance_with_callback )
{
  Geometry::Navigator::Length distance_traveled = 0.0*cgs::centimeter;

  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator( [&distance_traveled](const Geometry::Navigator::Length distance){ distance_traveled += distance; } );

  // Initialize the ray
  navigator->setState( 0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  Geometry::Navigator::EntityId cell =
    navigator->getCurrentCell();

  FRENSIE_CHECK_EQUAL( cell, 2 );

  // Fire a ray through the geometry
  Geometry::Navigator::Length distance_to_boundary =
    navigator->fireRay();

  double surface_normal[3];

  // Advance the ray to the cell boundary
  navigator->advanceToCellBoundary( surface_normal );

  FRENSIE_CHECK_EQUAL( surface_normal[0], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[1], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[2], 1.0 );
  FRENSIE_CHECK_EQUAL( distance_traveled, 2.5*cgs::centimeter );

  // Fire a ray through the geometry
  distance_to_boundary = navigator->fireRay();

  // Advance the ray a substep
  navigator->advanceBySubstep( 0.5*distance_to_boundary );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_traveled,
                                   3.75*cgs::centimeter,
                                   1e-6 );

  // Change the ray direction
  navigator->changeDirection( 0.0, 1.0, 0.0 );

  // Fire a ray through the geometry
  distance_to_boundary = navigator->fireRay();

  // Advance the ray to the cell boundary
  navigator->advanceToCellBoundary();

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_traveled,
                                   8.75*cgs::centimeter,
                                   1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the ray can be cloned
FRENSIE_UNIT_TEST( RootNavigator, clone )
{
  size_t number_of_advances = 0;

  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator( [&number_of_advances](const Geometry::Navigator::Length){ ++number_of_advances; } );

  // Initialize the ray
  navigator->setState( 0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  Geometry::Navigator::Length distance_to_boundary = navigator->fireRay();

  navigator->advanceBySubstep( 0.1*distance_to_boundary );

  // Clone the ray
  std::shared_ptr<Geometry::Navigator> navigator_clone( navigator->clone() );

  FRENSIE_CHECK_EQUAL( navigator_clone->getPosition()[0],
                       navigator->getPosition()[0] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getPosition()[1],
                       navigator->getPosition()[1] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getPosition()[2],
                       navigator->getPosition()[2] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getDirection()[0],
                       navigator->getDirection()[0] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getDirection()[1],
                       navigator->getDirection()[1] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getDirection()[2],
                       navigator->getDirection()[2] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getCurrentCell(),
                       navigator->getCurrentCell() );

  distance_to_boundary = navigator_clone->fireRay();

  navigator_clone->advanceBySubstep( 0.1*distance_to_boundary );

  // The callback should've been copied during the clone
  FRENSIE_CHECK_EQUAL( number_of_advances, 2 );

  navigator_clone.reset( navigator->clone( [](const Geometry::Navigator::Length distance){ std::cout << "advanced " << distance << std::endl; } ) );

  FRENSIE_CHECK_EQUAL( navigator_clone->getPosition()[0],
                       navigator->getPosition()[0] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getPosition()[1],
                       navigator->getPosition()[1] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getPosition()[2],
                       navigator->getPosition()[2] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getDirection()[0],
                       navigator->getDirection()[0] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getDirection()[1],
                       navigator->getDirection()[1] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getDirection()[2],
                       navigator->getDirection()[2] );
  FRENSIE_CHECK_EQUAL( navigator_clone->getCurrentCell(),
                       navigator->getCurrentCell() );

  distance_to_boundary = navigator_clone->fireRay();

  navigator_clone->advanceBySubstep( 0.1*distance_to_boundary );

  // A new callback was set so the number of advances counter should be
  // unmodified
  FRENSIE_CHECK_EQUAL( number_of_advances, 2 );
}

// //---------------------------------------------------------------------------//
// // Check that a navigator can be archived
// FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( RootNavigator, archive, TestArchives )
// {
//   FETCH_TEMPLATE_PARAM( 0, RawOArchive );
//   FETCH_TEMPLATE_PARAM( 1, RawIArchive );

//   typedef typename std::remove_pointer<RawOArchive>::type OArchive;
//   typedef typename std::remove_pointer<RawIArchive>::type IArchive;

//   std::string archive_name( "test_root_navigator" );
//   std::ostringstream archive_ostream;

//   std::unique_ptr<OArchive> oarchive;

//   createOArchive( archive_name, archive_ostream, oarchive );

//   std::shared_ptr<Geometry::Navigator> navigator = model->createNavigator();

//   // Initialize the ray
//   navigator->setState( 0.0*cgs::centimeter,
//                        0.0*cgs::centimeter,
//                        0.0*cgs::centimeter,
//                        0.0, 0.0, 1.0 );

//   FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( navigator ) );

//   if( cache_test_archive && archive_name.find(".h5a") >= archive_name.size() )
//   {
//     std::unique_ptr<std::ofstream> ofstream;

//     if( archive_name.find( ".bin" ) < archive_name.size() )
//     {
//       ofstream.reset( new std::ofstream( archive_name, std::ofstream::binary ) );
//     }
//     else
//     {
//       ofstream.reset( new std::ofstream( archive_name ) );
//     }

//     (*ofstream) << archive_ostream.str();
//   }
// }

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_root_geom_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_root_file",
                                        test_root_geom_file_name, "",
                                        "Test ROOT file name" );
  // ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "cache_test_archive",
  //                                       cache_test_archive, false,
  //                                       "Cache the test archive" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  Geometry::RootModelProperties local_properties( test_root_geom_file_name );

  std::shared_ptr<Geometry::RootModel> tmp_model =
    Geometry::RootModel::getInstance();

  tmp_model->initialize( local_properties );

  model = tmp_model;
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstRootNavigator.cpp
//---------------------------------------------------------------------------//
