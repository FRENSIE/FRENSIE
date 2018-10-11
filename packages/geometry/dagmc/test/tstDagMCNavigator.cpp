//---------------------------------------------------------------------------//
//!
//! \file tstDagMCNavigator.cpp
//! \author Alex Robinson
//! \brief  DagMC navigator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <fstream>
#include <memory>

// FRENSIE Includes
#include "Geometry_DagMCNavigator.hpp"
#include "Geometry_DagMCModel.hpp"
#include "Utility_Array.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const Geometry::DagMCModel> model;

bool cache_test_archive;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the point location w.r.t. a given cell can be returned
FRENSIE_UNIT_TEST( DagMCNavigator, getPointLocation )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

  // Initialize the ray
  std::shared_ptr<Geometry::Navigator::Ray> ray( new Geometry::Navigator::Ray(
                                                         -40.0*cgs::centimeter,
                                                         -40.0*cgs::centimeter,
                                                         59.0*cgs::centimeter,
                                                         0.0, 0.0, 1.0 ) );

  Geometry::PointLocation location =
    navigator->getPointLocation( *ray, 53 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_INSIDE_CELL );

  ray.reset( new Geometry::Navigator::Ray( -42.647999*cgs::centimeter,
                                           -40.0*cgs::centimeter,
                                           59.0*cgs::centimeter,
                                           -1.0, 0.0, 0.0 ) );

  location = navigator->getPointLocation( *ray, 53 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_INSIDE_CELL );

  ray.reset( new Geometry::Navigator::Ray( -42.648001*cgs::centimeter,
                                           -40.0*cgs::centimeter,
                                           59.0*cgs::centimeter,
                                           -1.0, 0.0, 0.0 ) );

  location = navigator->getPointLocation( *ray, 53 );

  FRENSIE_CHECK_EQUAL( location, Geometry::POINT_OUTSIDE_CELL );
}

//---------------------------------------------------------------------------//
// Check that the surface normal can be found
FRENSIE_UNIT_TEST( DagMCNavigator, getSurfaceNormal )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

  // Initialize the ray (on cell 53)
  Geometry::Navigator::Ray ray( -40.0*cgs::centimeter,
                                -40.0*cgs::centimeter,
                                60.959999084*cgs::centimeter,
                                0.0, 0.0, 1.0 );

  // Get the surface normal
  std::array<double,3> normal;

  navigator->getSurfaceNormal( 242,
                               ray.getPosition(),
                               ray.getDirection(),
                               normal.data() );

  std::array<double,3> ref_normal( {0.0, 0.0, 1.0} );

  FRENSIE_CHECK_EQUAL( normal, ref_normal );

  // Reversing the ray direction should not change the returned normal
  ray.changeDirection( 0.0, 0.0, -1.0 );

  navigator->getSurfaceNormal( 242,
                               ray.getPosition(),
                               ray.getDirection(),
                               normal.data() );

  FRENSIE_CHECK_EQUAL( normal, ref_normal );
}

//---------------------------------------------------------------------------//
// Check that the boundary cell can be found
FRENSIE_UNIT_TEST( DagMCNavigator, getBoundaryCell )
{
  std::shared_ptr<Geometry::DagMCNavigator>
    navigator( model->createNavigatorAdvanced() );

  FRENSIE_CHECK_EQUAL( navigator->getBoundaryCell( 53, 242 ), 54 );
  FRENSIE_CHECK_EQUAL( navigator->getBoundaryCell( 54, 248 ), 55 );
}

//---------------------------------------------------------------------------//
// Check that the cell containing the external ray can be found and cached
FRENSIE_UNIT_TEST( DagMCNavigator, findCellContainingRay_cache )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

  // Initialize the start cell cache
  Geometry::Navigator::CellIdSet found_cell_cache;

  // Initialize the ray
  std::shared_ptr<Geometry::Navigator::Ray> ray(
                           new Geometry::Navigator::Ray( -40.0*cgs::centimeter,
                                                         -40.0*cgs::centimeter,
                                                         59.0*cgs::centimeter,
                                                         0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  Geometry::Navigator::EntityId cell =
    navigator->findCellContainingRay( *ray, found_cell_cache );

  FRENSIE_CHECK_EQUAL( cell, 53 );

  // Initialize a new ray
  ray.reset( new Geometry::Navigator::Ray( -39.0*cgs::centimeter,
                                           -39.0*cgs::centimeter,
                                           59.0*cgs::centimeter,
                                           1.0, 0.0, 0.0 ) );

  // Find the cell that contains the point
  cell = navigator->findCellContainingRay( *ray, found_cell_cache );

  FRENSIE_CHECK_EQUAL( cell, 53 );

  // Initialize a new ray
  ray.reset( new Geometry::Navigator::Ray( -40.0*cgs::centimeter,
                                           -40.0*cgs::centimeter,
                                           61.0*cgs::centimeter,
                                           0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = navigator->findCellContainingRay( *ray, found_cell_cache );

  FRENSIE_CHECK_EQUAL( cell, 54 );

  // Initialize the new ray
  ray.reset( new Geometry::Navigator::Ray( -40.0*cgs::centimeter,
                                           -40.0*cgs::centimeter,
                                           64.0*cgs::centimeter,
                                           0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = navigator->findCellContainingRay( *ray, found_cell_cache );

  FRENSIE_CHECK_EQUAL( cell, 55 );

  // Check the found cell cache
  FRENSIE_CHECK_EQUAL( found_cell_cache.size(), 3 );
  FRENSIE_CHECK( found_cell_cache.count( 53 ) );
  FRENSIE_CHECK( found_cell_cache.count( 54 ) );
  FRENSIE_CHECK( found_cell_cache.count( 55 ) );
}

//---------------------------------------------------------------------------//
// Check that the cell containing the external ray can be found
FRENSIE_UNIT_TEST( DagMCNavigator, findCellContainingRay )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

  // Initialize the ray
  std::shared_ptr<Geometry::Navigator::Ray> ray(
                           new Geometry::Navigator::Ray( -40.0*cgs::centimeter,
                                                         -40.0*cgs::centimeter,
                                                         59.0*cgs::centimeter,
                                                         0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  Geometry::Navigator::EntityId cell =
    navigator->findCellContainingRay( *ray );

  FRENSIE_CHECK_EQUAL( cell, 53 );

  // Initialize a new ray
  ray.reset( new Geometry::Navigator::Ray( -40.0*cgs::centimeter,
                                           -40.0*cgs::centimeter,
                                           61.0*cgs::centimeter,
                                           0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = navigator->findCellContainingRay( *ray );

  FRENSIE_CHECK_EQUAL( cell, 54 );

  // Initialize the new ray
  ray.reset( new Geometry::Navigator::Ray( -40.0*cgs::centimeter,
                                           -40.0*cgs::centimeter,
                                           64.0*cgs::centimeter,
                                           0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = navigator->findCellContainingRay( *ray );

  FRENSIE_CHECK_EQUAL( cell, 55 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be set
FRENSIE_UNIT_TEST( DagMCNavigator, setState_unknown_cell )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

  FRENSIE_CHECK( !navigator->isStateSet() );

  std::shared_ptr<Geometry::Navigator::Ray> ray(
                           new Geometry::Navigator::Ray( -40.0*cgs::centimeter,
                                                         -40.0*cgs::centimeter,
                                                         59.0*cgs::centimeter,
                                                         0.0, 0.0, 1.0 ) );

  navigator->setState( ray->getPosition(), ray->getDirection() );

  FRENSIE_CHECK( navigator->isStateSet() );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[0], -40.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[1], -40.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[2], 59.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getCurrentCell(), 53 );

  ray.reset( new Geometry::Navigator::Ray( -40.0*cgs::centimeter,
                                           -40.0*cgs::centimeter,
                                           61.0*cgs::centimeter,
                                           0.0, 0.0, 1.0 ) );

  navigator->setState( ray->getPosition(), ray->getDirection() );

  FRENSIE_CHECK( navigator->isStateSet() );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[0], -40.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[1], -40.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[2], 61.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getCurrentCell(), 54 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be set
FRENSIE_UNIT_TEST( DagMCNavigator, setState_known_cell )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

  // Set the internal ray but do not cache its starting cell
  std::shared_ptr<Geometry::Navigator::Ray> ray(
                           new Geometry::Navigator::Ray( -40.0*cgs::centimeter,
                                                         -40.0*cgs::centimeter,
                                                         59.0*cgs::centimeter,
                                                         0.0, 0.0, 1.0 ) );

  FRENSIE_CHECK( !navigator->isStateSet() );

  navigator->setState( ray->getPosition(),
                             ray->getDirection(),
                             53 );

  FRENSIE_CHECK( navigator->isStateSet() );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[0], -40.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[1], -40.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[2], 59.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getCurrentCell(), 53 );

  ray.reset( new Geometry::Navigator::Ray( -40.0*cgs::centimeter,
                                           -40.0*cgs::centimeter,
                                           61.0*cgs::centimeter,
                                           0.0, 0.0, 1.0 ) );

  navigator->setState( ray->getPosition(), ray->getDirection(), 54 );

  FRENSIE_CHECK( navigator->isStateSet() );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[0], -40.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[1], -40.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getPosition()[2], 61.0*cgs::centimeter );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getCurrentCell(), 54 );
}

//---------------------------------------------------------------------------//
// Check that the distance to closest boundary
FRENSIE_UNIT_TEST( DagMCNavigator, getDistanceToClosestBoundary )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

  // Initialize the ray
  std::shared_ptr<Geometry::Navigator::Ray> ray(
                           new Geometry::Navigator::Ray( -39.6*cgs::centimeter,
                                                         -39.6*cgs::centimeter,
                                                         59.69*cgs::centimeter,
                                                         0.0, 1.0, 0.0 ) );

  navigator->setState( ray->getPosition(), ray->getDirection(), 53 );

  // Get safety distance
  Geometry::Navigator::Length safety_distance =
    navigator->getDistanceToClosestBoundary();

  FRENSIE_CHECK_FLOATING_EQUALITY( safety_distance,
                                   1.27*cgs::centimeter,
                                   1e-9 );

  // Reset the ray
  ray.reset( new Geometry::Navigator::Ray( -39.6*cgs::centimeter,
                                           -39.6*cgs::centimeter,
                                           60.69*cgs::centimeter,
                                           0.0, 1.0, 0.0 ) );

  navigator->setState( ray->getPosition(), ray->getDirection(), 53 );

  // Get safety distance
  safety_distance = navigator->getDistanceToClosestBoundary();

  FRENSIE_CHECK_FLOATING_EQUALITY( safety_distance,
                                   0.27*cgs::centimeter,
                                   1e-9 );

  // Reset the ray
  ray.reset( new Geometry::Navigator::Ray( -39.6*cgs::centimeter,
                                           -39.6*cgs::centimeter,
                                           60.96*cgs::centimeter,
                                           1.0, 0.0, 0.0 ) );

  navigator->setState( ray->getPosition(), ray->getDirection(), 53 );

  // Get safety distance
  safety_distance = navigator->getDistanceToClosestBoundary();

  FRENSIE_CHECK_FLOATING_EQUALITY( safety_distance,
                                   0.0*cgs::centimeter,
                                   1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be fired
FRENSIE_UNIT_TEST( DagMCNavigator, fireRay )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

  // Initialize the ray
  Geometry::Navigator::Ray ray( -40.0*cgs::centimeter,
                                -40.0*cgs::centimeter,
                                59.0*cgs::centimeter,
                                0.0, 0.0, 1.0 );

  navigator->setState( ray.getPosition(), ray.getDirection(), 53 );

  // Fire an external ray through the geometry
  Geometry::Navigator::EntityId surface_hit;

  Geometry::Navigator::Length distance_to_surface_hit =
    navigator->fireRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit,
                                   1.96*cgs::centimeter,
                                   1e-9 );
  FRENSIE_CHECK_EQUAL( surface_hit, 242 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be advanced by a substep
FRENSIE_UNIT_TEST( DagMCNavigator, advanceBySubstep )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

  // Initialize the ray
  navigator->setState( -40.0*cgs::centimeter,
                       -40.0*cgs::centimeter,
                       59.0*cgs::centimeter,
                       0.0, 0.0, 1.0,
                       53 );

  navigator->advanceBySubstep( 0.96*cgs::centimeter );

  // Find the cell that contains the ray
  Geometry::Navigator::EntityId cell = navigator->getCurrentCell();

  FRENSIE_CHECK_EQUAL( cell, 53 );

  // Fire the ray
  Geometry::Navigator::EntityId surface_hit;

  Geometry::Navigator::Length distance_to_surface_hit =
    navigator->fireRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit,
                                   1.0*cgs::centimeter,
                                   1e-9 );
  FRENSIE_CHECK_EQUAL( surface_hit, 242 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be advanced
FRENSIE_UNIT_TEST( DagMCNavigator, advanceToCellBoundary_basic )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

  // Initialize the ray
  navigator->setState( -40.0*cgs::centimeter,
                       -40.0*cgs::centimeter,
                       59.0*cgs::centimeter,
                       0.0, 0.0, 1.0,
                       53 );

  // Find the cell that contains the ray
  Geometry::Navigator::EntityId cell =
    navigator->getCurrentCell();

  FRENSIE_CHECK_EQUAL( cell, 53 );

  // Advance the ray to the boundary surface
  navigator->advanceToCellBoundary();

  cell = navigator->getCurrentCell();

  FRENSIE_CHECK_EQUAL( cell, 54 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be advanced
FRENSIE_UNIT_TEST( DagMCNavigator, advanceToCellBoundary_advanced )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

  // Initialize the ray
  navigator->setState( -40.0*cgs::centimeter,
                       -40.0*cgs::centimeter,
                       59.0*cgs::centimeter,
                       0.0, 0.0, 1.0,
                       53 );

  // Find the cell that contains the ray
  Geometry::Navigator::EntityId cell = navigator->getCurrentCell();

  FRENSIE_CHECK_EQUAL( cell, 53 );

  // Advance the ray to the boundary surface
  double surface_normal[3];

  bool reflection =
    navigator->advanceToCellBoundary( surface_normal );

  FRENSIE_CHECK( !reflection );
  FRENSIE_CHECK_EQUAL( surface_normal[0], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[1], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[2], 1.0 );

  cell = navigator->getCurrentCell();

  FRENSIE_CHECK_EQUAL( cell, 54 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be advanced by a substep
FRENSIE_UNIT_TEST( DagMCNavigator, advance_with_callback )
{
  Geometry::Navigator::Length distance_traveled = 0.0*cgs::centimeter;

  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator( [&distance_traveled](const Geometry::Navigator::Length distance){ distance_traveled += distance; } );

  // Initialize the ray
  navigator->setState( -40.0*cgs::centimeter,
                       -40.0*cgs::centimeter,
                       59.0*cgs::centimeter,
                       0.0, 0.0, 1.0,
                       53 );

  navigator->advanceBySubstep( 0.959999084*cgs::centimeter );

  FRENSIE_CHECK_EQUAL( distance_traveled, 0.959999084*cgs::centimeter );

  navigator->advanceToCellBoundary();

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_traveled,
                                   1.96*cgs::centimeter,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray direction can be changed
FRENSIE_UNIT_TEST( DagMCNavigator, changeDirection )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

  std::shared_ptr<Geometry::Navigator::Ray> ray(
                           new Geometry::Navigator::Ray( -40.0*cgs::centimeter,
                                                         -40.0*cgs::centimeter,
                                                         59.0*cgs::centimeter,
                                                         0.0, 0.0, 1.0 ) );

  navigator->setState( ray->getPosition(),
                       ray->getDirection(),
                       53 );

  ray.reset( new Geometry::Navigator::Ray( -40.0*cgs::centimeter,
                                           -40.0*cgs::centimeter,
                                           59.0*cgs::centimeter,
                                           1.0, 0.0, 0.0 ) );

  navigator->changeDirection( ray->getDirection() );

  FRENSIE_CHECK_EQUAL( navigator->getDirection()[0], 1.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( navigator->getDirection()[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray trace can be done
FRENSIE_UNIT_TEST( DagMCNavigator, ray_trace )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

  // Initialize the ray
  navigator->setState( -40.0*cgs::centimeter,
                       -40.0*cgs::centimeter,
                       59.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  // Find the cell that contains the ray
  Geometry::Navigator::EntityId cell = navigator->getCurrentCell();

  FRENSIE_CHECK_EQUAL( cell, 53 );

  // Fire the ray
  Geometry::Navigator::EntityId surface_hit;

  Geometry::Navigator::Length distance_to_surface_hit =
    navigator->fireRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit,
                                   1.96*cgs::centimeter,
                                   1e-9 );
  FRENSIE_CHECK_EQUAL( surface_hit, 242 );

  // Advance the ray to the boundary surface
  navigator->advanceToCellBoundary();

  cell = navigator->getCurrentCell();

  FRENSIE_CHECK_EQUAL( cell, 54 );

  // Fire the ray
  distance_to_surface_hit = navigator->fireRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit,
                                   2.54*cgs::centimeter,
                                   1e-6 );
  FRENSIE_CHECK_EQUAL( surface_hit, 248 );

  // Advance the ray to the boundary surface
  navigator->advanceToCellBoundary();

  cell = navigator->getCurrentCell();

  FRENSIE_CHECK_EQUAL( cell, 55 );

  // Fire the ray
  distance_to_surface_hit = navigator->fireRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit,
                                   2.54*cgs::centimeter,
                                   1e-6 );
  FRENSIE_CHECK_EQUAL( surface_hit, 254 );

  // Advance the ray a substep
  navigator->advanceBySubstep( 0.5*distance_to_surface_hit );

  // Change the ray direction
  navigator->changeDirection( 0.0, 0.0, -1.0 );

  // Fire the ray
  distance_to_surface_hit = navigator->fireRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit,
                                   1.27*cgs::centimeter,
                                   1e-6 );
  FRENSIE_CHECK_EQUAL( surface_hit, 248 );

  // Special case: change ray direction - ray intersects same surface
  navigator->changeDirection( -2.571015391079360581e-04,
                              -1.645567034813260362e-04,
                              -9.999999534099438536e-01 );

  // Fire the ray
  distance_to_surface_hit = navigator->fireRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit,
                                   1.27*cgs::centimeter,
                                   1e-6 );
  FRENSIE_CHECK_EQUAL( surface_hit, 248 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray trace can be done
FRENSIE_UNIT_TEST( DagMCNavigator, ray_trace_with_reflection )
{
  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator();

  // Initialize the ray
  navigator->setState( -40.0*cgs::centimeter,
                       -40.0*cgs::centimeter,
                       108.0*cgs::centimeter,
                       0.0, 0.0, 1.0 );

  // Find the cell that contains the ray
  Geometry::Navigator::EntityId cell = navigator->getCurrentCell();

  FRENSIE_CHECK_EQUAL( cell, 82 );

  // Fire the ray
  Geometry::Navigator::EntityId surface_hit;

  Geometry::Navigator::Length distance_to_surface_hit =
    navigator->fireRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit,
                                   1.474*cgs::centimeter,
                                   1e-6 );
  FRENSIE_CHECK_EQUAL( surface_hit, 394 );

  // Advance the ray to the boundary surface
  bool reflection = navigator->advanceToCellBoundary();

  FRENSIE_CHECK( !reflection );

  cell = navigator->getCurrentCell();

  FRENSIE_CHECK_EQUAL( cell, 83 );

  distance_to_surface_hit = navigator->fireRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit,
                                   17.526*cgs::centimeter,
                                   1e-6 );
  FRENSIE_CHECK_EQUAL( surface_hit, 408 );

  // Advance the ray to the boundary surface (reflecting)
  double surface_normal[3];

  reflection = navigator->advanceToCellBoundary( surface_normal );

  FRENSIE_CHECK( reflection );
  FRENSIE_CHECK_EQUAL( surface_normal[0], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[1], 0.0 );
  FRENSIE_CHECK_EQUAL( surface_normal[2], 1.0 );

  cell = navigator->getCurrentCell();

  FRENSIE_CHECK_EQUAL( cell, 83 );

  distance_to_surface_hit = navigator->fireRay( &surface_hit );

  FRENSIE_CHECK_FLOATING_EQUALITY( distance_to_surface_hit,
                                   17.526*cgs::centimeter,
                                   1e-6 );
  FRENSIE_CHECK_EQUAL( surface_hit, 394 );
}

//---------------------------------------------------------------------------//
// Check that the ray can be cloned
FRENSIE_UNIT_TEST( DagMCNavigator, clone )
{
  size_t number_of_advances = 0;

  std::shared_ptr<Geometry::Navigator> navigator =
    model->createNavigator( [&number_of_advances](const Geometry::Navigator::Length){ ++number_of_advances; } );

  // Initialize the ray
  navigator->setState( -40.0*cgs::centimeter,
                       -40.0*cgs::centimeter,
                       108.0*cgs::centimeter,
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

  navigator_clone->advanceBySubstep( 0.1*distance_to_boundary );

  // A new callback was set so the number of advances counter should be
  // unmodified
  FRENSIE_CHECK_EQUAL( number_of_advances, 2 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_dagmc_geom_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_cad_file",
                                        test_dagmc_geom_file_name, "",
                                        "Test CAD file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  Geometry::DagMCModelProperties local_properties( test_dagmc_geom_file_name );

  local_properties.setTerminationCellPropertyName( "graveyard" );
  local_properties.setMaterialPropertyName( "mat" );
  local_properties.setDensityPropertyName( "rho" );
  local_properties.setEstimatorPropertyName( "tally" );

  model.reset( new Geometry::DagMCModel( local_properties ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDagMCNavigator.cpp
//---------------------------------------------------------------------------//
