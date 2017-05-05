//---------------------------------------------------------------------------//
//!
//! \file   tstInfiniteMediumNavigator.cpp
//! \author Alex Robinson
//! \brief  Infinite medium navigator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>
#include <vector>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Geometry_InfiniteMediumNavigator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the location of a point w.r.t. a cell can be returned
TEUCHOS_UNIT_TEST( InfiniteMediumNavigator, getPointLocation )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  std::unique_ptr<Geometry::Ray>
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );
  
  Geometry::PointLocation location = navigator->getPointLocation( *ray, 1 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  location = navigator->getPointLocation( *ray, 2 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );

  ray.reset( new Geometry::Ray( std::numeric_limits<double>::infinity(),
                                std::numeric_limits<double>::infinity(),
                                std::numeric_limits<double>::infinity(),
                                1.0,
                                0.0,
                                0.0 ) );

  location = navigator->getPointLocation( *ray, 1 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  location = navigator->getPointLocation( *ray, 2 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );
}

//---------------------------------------------------------------------------//
// Check that the surface normal at a point on the surface can be returned
TEUCHOS_UNIT_TEST( InfiniteMediumNavigator, getSurfaceNormal )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  std::unique_ptr<Geometry::Ray>
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  std::vector<double> normal( 3 );

  navigator->getSurfaceNormal( 0, *ray, normal.data() );

  TEST_EQUALITY_CONST( normal[0], 0.0 );
  TEST_EQUALITY_CONST( normal[1], 0.0 );
  TEST_EQUALITY_CONST( normal[2], 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the cell containing a ray can be found
TEUCHOS_UNIT_TEST( InfiniteMediumNavigator, findCellContainingRay_cache )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  std::unique_ptr<Geometry::Ray>
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  Geometry::Navigator::CellIdSet cell_cache;
  
  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->findCellContainingRay( *ray, cell_cache );

  TEST_EQUALITY_CONST( cell, 1 );
  TEST_EQUALITY_CONST( cell_cache.size(), 1 );
  TEST_ASSERT( cell_cache.count( 1 ) );

  ray.reset( new Geometry::Ray( std::numeric_limits<double>::infinity(),
                                std::numeric_limits<double>::infinity(),
                                std::numeric_limits<double>::infinity(),
                                1.0,
                                0.0,
                                0.0 ) );

  cell = navigator->findCellContainingRay( *ray, cell_cache );

  TEST_EQUALITY_CONST( cell, 1 );
  TEST_EQUALITY_CONST( cell_cache.size(), 1 );
  TEST_ASSERT( cell_cache.count( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that the cell containing a ray can be found
TEUCHOS_UNIT_TEST( InfiniteMediumNavigator, findCellContainingRay )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  std::unique_ptr<Geometry::Ray>
    ray( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 ) );

  Geometry::ModuleTraits::InternalCellHandle cell =
    navigator->findCellContainingRay( *ray );

  TEST_EQUALITY_CONST( cell, 1 );
  
  ray.reset( new Geometry::Ray( std::numeric_limits<double>::infinity(),
                                std::numeric_limits<double>::infinity(),
                                std::numeric_limits<double>::infinity(),
                                1.0,
                                0.0,
                                0.0 ) );

  cell = navigator->findCellContainingRay( *ray );

  TEST_EQUALITY_CONST( cell, 1 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be set
TEUCHOS_UNIT_TEST( InfiniteMediumNavigator, setInternalRay )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  TEST_ASSERT( navigator->isInternalRaySet() );

  navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  TEST_ASSERT( navigator->isInternalRaySet() );

  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[0], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[2], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2], 1.0 );
  TEST_EQUALITY_CONST( navigator->getCellContainingInternalRay(), 1 );

  navigator->setInternalRay( std::numeric_limits<double>::infinity(),
                             std::numeric_limits<double>::infinity(),
                             std::numeric_limits<double>::infinity(),
                             1.0,
                             0.0,
                             0.0 );

  TEST_ASSERT( navigator->isInternalRaySet() );

  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[0],
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[1],
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[2],
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0], 1.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2], 0.0 );
  TEST_EQUALITY_CONST( navigator->getCellContainingInternalRay(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be fired through the geometry
TEUCHOS_UNIT_TEST( InfiniteMediumNavigator, fireInternalRay )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  double distance_to_boundary = navigator->fireInternalRay();

  TEST_EQUALITY_CONST( distance_to_boundary,
                       std::numeric_limits<double>::infinity() );

  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;

  navigator->setInternalRay( 1.0, -1.0, 1.0, 1.0, 0.0, 0.0 );
  
  distance_to_boundary = navigator->fireInternalRay( &surface_hit );

  TEST_EQUALITY_CONST( distance_to_boundary,
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( surface_hit,
                       Geometry::ModuleTraits::invalid_internal_surface_handle );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be advanced to the cell boundary
TEUCHOS_UNIT_TEST( InfiniteMediumNavigator, advanceInternalRayToCellBoundary )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  bool reflected = navigator->advanceInternalRayToCellBoundary();

  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[0],
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[1],
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[2],
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2], 1.0 );
  TEST_EQUALITY_CONST( navigator->getCellContainingInternalRay(), 1 );
  TEST_ASSERT( !reflected );

  navigator->setInternalRay( 1.0, -1.0, 1.0, 1.0/sqrt(3), 1.0/sqrt(3), 1.0/sqrt(3) );

  std::vector<double> surface_normal( 3 );

  reflected =
    navigator->advanceInternalRayToCellBoundary( surface_normal.data() );

  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[0],
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[1],
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[2],
                       std::numeric_limits<double>::infinity() );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0],
                       1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1],
                       1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2],
                       1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( navigator->getCellContainingInternalRay(), 1 );
  TEST_ASSERT( !reflected );
  TEST_EQUALITY_CONST( surface_normal[0], 1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( surface_normal[1], 1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( surface_normal[2], 1.0/sqrt(3.0) );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be advanced by a substep
TEUCHOS_UNIT_TEST( InfiniteMediumNavigator, advanceInternalRayBySubstep )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  navigator->advanceInternalRayBySubstep( 1.0 );

  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[0], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[2], 1.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2], 1.0 );

  navigator->setInternalRay( 1.0, -1.0, 1.0, 1.0/sqrt(3), 1.0/sqrt(3), -1.0/sqrt(3) );

  navigator->advanceInternalRayBySubstep( 2.0 );

  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[0],
                       1.0+2.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[1],
                       -1.0+2.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[2],
                       1.0-2.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0],
                       1.0/sqrt(3) );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1],
                       1.0/sqrt(3) );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2],
                       -1.0/sqrt(3) );
}

//---------------------------------------------------------------------------//
// Check that the internal ray direction can be changed
TEUCHOS_UNIT_TEST( InfiniteMediumNavigator, changeInternalRayDirection )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  navigator->changeInternalRayDirection( 1.0, 0.0, 0.0 );

  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[0], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayPosition()[2], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[0], 1.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( navigator->getInternalRayDirection()[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the navigator can be cloned
TEUCHOS_UNIT_TEST( InfiniteMediumNavigator, clone )
{
  std::unique_ptr<Geometry::Navigator>
    navigator( new Geometry::InfiniteMediumNavigator( 1 ) );

  navigator->setInternalRay( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  std::unique_ptr<Geometry::Navigator> navigator_clone( navigator->clone() );

  TEST_EQUALITY_CONST( navigator_clone->getInternalRayPosition()[0],
                       navigator->getInternalRayPosition()[0] );
  TEST_EQUALITY_CONST( navigator_clone->getInternalRayPosition()[1],
                       navigator->getInternalRayPosition()[1] );
  TEST_EQUALITY_CONST( navigator_clone->getInternalRayPosition()[2],
                       navigator->getInternalRayPosition()[2] );
  TEST_EQUALITY_CONST( navigator_clone->getInternalRayDirection()[0],
                       navigator->getInternalRayDirection()[0] );
  TEST_EQUALITY_CONST( navigator_clone->getInternalRayDirection()[1],
                       navigator->getInternalRayDirection()[1] );
  TEST_EQUALITY_CONST( navigator_clone->getInternalRayDirection()[2],
                       navigator->getInternalRayDirection()[2] );
  TEST_EQUALITY_CONST( navigator_clone->getCellContainingInternalRay(),
                       navigator->getCellContainingInternalRay() );
}

//---------------------------------------------------------------------------//
// end tstInfiniteMediumNavigator.cpp
//---------------------------------------------------------------------------//

