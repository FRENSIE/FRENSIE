//---------------------------------------------------------------------------//
//!
//! \file   tstDagMCRay.cpp
//! \author Alex Robinson
//! \brief  DagMCRay unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "Geometry_DagMCRay.hpp"
#include "Geometry_Ray.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if a ray is ready
FRENSIE_UNIT_TEST( DagMCRay, isReady )
{
  std::shared_ptr<Geometry::DagMCRay> ray( new Geometry::DagMCRay );

  FRENSIE_CHECK( !ray->isReady() );

  Geometry::Ray raw_ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 );

  ray.reset( new Geometry::DagMCRay( raw_ray, 1 ) );

  FRENSIE_CHECK( ray->isReady() );

  ray.reset( new Geometry::DagMCRay( raw_ray.getPosition(),
                                     raw_ray.getDirection(),
                                     1 ) );

  FRENSIE_CHECK( ray->isReady() );
}

//---------------------------------------------------------------------------//
// Check that the ray position can be returned
FRENSIE_UNIT_TEST( DagMCRay, getPosition )
{
  Geometry::Ray raw_ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 );

  Geometry::DagMCRay ray( raw_ray, 1 );

  const double* position = ray.getPosition();

  FRENSIE_CHECK_EQUAL( position[0], 1.0 );
  FRENSIE_CHECK_EQUAL( position[1], 1.0 );
  FRENSIE_CHECK_EQUAL( position[2], 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the ray direction can be returned
FRENSIE_UNIT_TEST( DagMCRay, getDirection )
{
  Geometry::Ray raw_ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 );

  Geometry::DagMCRay ray( raw_ray, 1 );

  const double* direction = ray.getDirection();

  FRENSIE_CHECK_EQUAL( direction[0], 0.0 );
  FRENSIE_CHECK_EQUAL( direction[1], 0.0 );
  FRENSIE_CHECK_EQUAL( direction[2], 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the cell handle can be returned
FRENSIE_UNIT_TEST( DagMCRay, getCurrentCell )
{
  Geometry::Ray raw_ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 );

  Geometry::DagMCRay ray( raw_ray, 1 );

  FRENSIE_CHECK_EQUAL( ray.getCurrentCell(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the ray can be reset
FRENSIE_UNIT_TEST( DagMCRay, set )
{
  std::shared_ptr<Geometry::Ray> raw_ray(
                           new Geometry::Ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 ) );

  Geometry::DagMCRay ray( *raw_ray, 1 );

  raw_ray.reset( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 ) );

  ray.set( *raw_ray, 2 );

  FRENSIE_CHECK_EQUAL( ray.getPosition()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( ray.getPosition()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( ray.getPosition()[2], 0.0 );
  FRENSIE_CHECK_EQUAL( ray.getDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( ray.getDirection()[1], 1.0 );
  FRENSIE_CHECK_EQUAL( ray.getDirection()[2], 0.0 );
  FRENSIE_CHECK_EQUAL( ray.getCurrentCell(), 2 );

  raw_ray.reset( new Geometry::Ray( -1.0, -1.0, -1.0, 1.0, 0.0, 0.0 ) );

  ray.set( raw_ray->getPosition(), raw_ray->getDirection(), 3 );

  FRENSIE_CHECK_EQUAL( ray.getPosition()[0], -1.0 );
  FRENSIE_CHECK_EQUAL( ray.getPosition()[1], -1.0 );
  FRENSIE_CHECK_EQUAL( ray.getPosition()[2], -1.0 );
  FRENSIE_CHECK_EQUAL( ray.getDirection()[0], 1.0 );
  FRENSIE_CHECK_EQUAL( ray.getDirection()[1], 0.0 );
  FRENSIE_CHECK_EQUAL( ray.getDirection()[2], 0.0 );
  FRENSIE_CHECK_EQUAL( ray.getCurrentCell(), 3 );
}

//---------------------------------------------------------------------------//
// Check that intersection data can be set
FRENSIE_UNIT_TEST( DagMCRay, setIntersetionSurfaceData )
{
  Geometry::Ray raw_ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 );

  Geometry::DagMCRay ray( raw_ray, 1 );

  FRENSIE_CHECK( !ray.knowsIntersectionSurface() );

  ray.setIntersectionSurfaceData( 10, 3.0 );

  FRENSIE_CHECK( ray.knowsIntersectionSurface() );
  FRENSIE_CHECK_EQUAL( ray.getIntersectionSurface(), 10 );
  FRENSIE_CHECK_EQUAL( ray.getDistanceToIntersectionSurface(), 3.0 );

  ray.resetIntersectionSurfaceData();

  FRENSIE_CHECK( !ray.knowsIntersectionSurface() );
}

//---------------------------------------------------------------------------//
// Check that the ray direction can be changed
FRENSIE_UNIT_TEST( DagMCRay, changeDirection )
{
  const double position[3] = {1.0, 1.0, 1.0};
  double direction[3] = {1.0, 0.0, 0.0};

  Geometry::DagMCRay ray( position, direction, 1 );
  ray.setIntersectionSurfaceData( 10, 3.0 );

  direction[0] = 0.0;
  direction[1] = 1.0;
  direction[2] = 0.0;

  ray.changeDirection( direction );

  FRENSIE_CHECK( !ray.knowsIntersectionSurface() );
  FRENSIE_CHECK_EQUAL( ray.getDirection()[0], 0.0 );
  FRENSIE_CHECK_EQUAL( ray.getDirection()[1], 1.0 );
  FRENSIE_CHECK_EQUAL( ray.getDirection()[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the ray history can be returned
FRENSIE_UNIT_TEST( DagMCRay, getHistory )
{
  Geometry::Ray raw_ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 );

  Geometry::DagMCRay ray( raw_ray, 1 );

  FRENSIE_CHECK_EQUAL( ray.getHistory().size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the ray can be advanced
FRENSIE_UNIT_TEST( DagMCRay, advanceToIntersectionSurface )
{
  Geometry::Ray raw_ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 );

  Geometry::DagMCRay ray( raw_ray, 1 );

  ray.setIntersectionSurfaceData( 10, 3.0 );

  ray.advanceToIntersectionSurface( 2 );

  FRENSIE_CHECK_EQUAL( ray.getPosition()[0], 1.0 );
  FRENSIE_CHECK_EQUAL( ray.getPosition()[1], 1.0 );
  FRENSIE_CHECK_EQUAL( ray.getPosition()[2], 4.0 );
  FRENSIE_CHECK_EQUAL( ray.getCurrentCell(), 2 );

  // Once the ray is advanced the intersection data will be reset
  FRENSIE_CHECK( !ray.knowsIntersectionSurface() );
}

//---------------------------------------------------------------------------//
// Check that the ray can be advanced a substep
FRENSIE_UNIT_TEST( DagMCRay, advanceSubstep )
{
  Geometry::Ray raw_ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 );

  Geometry::DagMCRay ray( raw_ray, 1 );

  ray.setIntersectionSurfaceData( 10, 3.0 );

  ray.advanceSubstep( 2.0 );

  FRENSIE_CHECK_EQUAL( ray.getPosition()[0], 1.0 );
  FRENSIE_CHECK_EQUAL( ray.getPosition()[1], 1.0 );
  FRENSIE_CHECK_EQUAL( ray.getPosition()[2], 3.0 );

  FRENSIE_CHECK( ray.knowsIntersectionSurface() );
  FRENSIE_CHECK_EQUAL( ray.getIntersectionSurface(), 10 );
  FRENSIE_CHECK_EQUAL( ray.getDistanceToIntersectionSurface(), 1.0 );
  FRENSIE_CHECK_EQUAL( ray.getCurrentCell(), 1 );
}

//---------------------------------------------------------------------------//
// end tstDagMCRay.cpp
//---------------------------------------------------------------------------//
