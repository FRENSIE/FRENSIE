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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Geometry_DagMCRay.hpp"
#include "Geometry_Ray.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if a ray is ready
TEUCHOS_UNIT_TEST( DagMCRay, isReady )
{
  std::shared_ptr<Geometry::DagMCRay> ray( new Geometry::DagMCRay );

  TEST_ASSERT( !ray->isReady() );

  Geometry::Ray raw_ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 );

  ray.reset( new Geometry::DagMCRay( raw_ray, 1 ) );

  TEST_ASSERT( ray->isReady() );

  ray.reset( new Geometry::DagMCRay( raw_ray.getPosition(),
                                     raw_ray.getDirection(),
                                     1 ) );

  TEST_ASSERT( ray->isReady() );
}

//---------------------------------------------------------------------------//
// Check that the ray position can be returned
TEUCHOS_UNIT_TEST( DagMCRay, getPosition )
{
  Geometry::Ray raw_ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 );
  
  Geometry::DagMCRay ray( raw_ray, 1 );

  const double* position = ray.getPosition();

  TEST_EQUALITY_CONST( position[0], 1.0 );
  TEST_EQUALITY_CONST( position[1], 1.0 );
  TEST_EQUALITY_CONST( position[2], 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the ray direction can be returned
TEUCHOS_UNIT_TEST( DagMCRay, getDirection )
{
  Geometry::Ray raw_ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 );
  
  Geometry::DagMCRay ray( raw_ray, 1 );

  const double* direction = ray.getDirection();

  TEST_EQUALITY_CONST( direction[0], 0.0 );
  TEST_EQUALITY_CONST( direction[1], 0.0 );
  TEST_EQUALITY_CONST( direction[2], 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the cell handle can be returned
TEUCHOS_UNIT_TEST( DagMCRay, getCurrentCell )
{
  Geometry::Ray raw_ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 );
  
  Geometry::DagMCRay ray( raw_ray, 1 );

  TEST_EQUALITY_CONST( ray.getCurrentCell(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the ray can be reset
TEUCHOS_UNIT_TEST( DagMCRay, set )
{
  std::shared_ptr<Geometry::Ray> raw_ray( 
                           new Geometry::Ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 ) );

  Geometry::DagMCRay ray( *raw_ray, 1 );

  raw_ray.reset( new Geometry::Ray( 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 ) );

  ray.set( *raw_ray, 2 );

  TEST_EQUALITY_CONST( ray.getPosition()[0], 0.0 );
  TEST_EQUALITY_CONST( ray.getPosition()[1], 0.0 );
  TEST_EQUALITY_CONST( ray.getPosition()[2], 0.0 );
  TEST_EQUALITY_CONST( ray.getDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( ray.getDirection()[1], 1.0 );
  TEST_EQUALITY_CONST( ray.getDirection()[2], 0.0 );
  TEST_EQUALITY_CONST( ray.getCurrentCell(), 2 );

  raw_ray.reset( new Geometry::Ray( -1.0, -1.0, -1.0, 1.0, 0.0, 0.0 ) );

  ray.set( raw_ray->getPosition(), raw_ray->getDirection(), 3 );
           
  TEST_EQUALITY_CONST( ray.getPosition()[0], -1.0 );
  TEST_EQUALITY_CONST( ray.getPosition()[1], -1.0 );
  TEST_EQUALITY_CONST( ray.getPosition()[2], -1.0 );
  TEST_EQUALITY_CONST( ray.getDirection()[0], 1.0 );
  TEST_EQUALITY_CONST( ray.getDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( ray.getDirection()[2], 0.0 );
  TEST_EQUALITY_CONST( ray.getCurrentCell(), 3 );
}

//---------------------------------------------------------------------------//
// Check that intersection data can be set
TEUCHOS_UNIT_TEST( DagMCRay, setIntersetionSurfaceData )
{
  Geometry::Ray raw_ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 );
  
  Geometry::DagMCRay ray( raw_ray, 1 );

  TEST_ASSERT( !ray.knowsIntersectionSurface() );

  ray.setIntersectionSurfaceData( 10, 3.0 );

  TEST_ASSERT( ray.knowsIntersectionSurface() );
  TEST_EQUALITY_CONST( ray.getIntersectionSurface(), 10 );
  TEST_EQUALITY_CONST( ray.getDistanceToIntersectionSurface(), 3.0 );

  ray.resetIntersectionSurfaceData();
  
  TEST_ASSERT( !ray.knowsIntersectionSurface() );
}

//---------------------------------------------------------------------------//
// Check that the ray direction can be changed
TEUCHOS_UNIT_TEST( DagMCRay, changeDirection )
{
  const double position[3] = {1.0, 1.0, 1.0};
  double direction[3] = {1.0, 0.0, 0.0};

  Geometry::DagMCRay ray( position, direction, 1 );
  ray.setIntersectionSurfaceData( 10, 3.0 );
  
  direction[0] = 0.0;
  direction[1] = 1.0;
  direction[2] = 0.0;

  ray.changeDirection( direction );

  TEST_ASSERT( !ray.knowsIntersectionSurface() );
  TEST_EQUALITY_CONST( ray.getDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( ray.getDirection()[1], 1.0 );
  TEST_EQUALITY_CONST( ray.getDirection()[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the ray history can be returned
TEUCHOS_UNIT_TEST( DagMCRay, getHistory )
{
  Geometry::Ray raw_ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 );
  
  Geometry::DagMCRay ray( raw_ray, 1 );

  TEST_EQUALITY_CONST( ray.getHistory().size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the ray can be advanced
TEUCHOS_UNIT_TEST( DagMCRay, advanceToIntersectionSurface )
{
  Geometry::Ray raw_ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 );
  
  Geometry::DagMCRay ray( raw_ray, 1 );

  ray.setIntersectionSurfaceData( 10, 3.0 );

  ray.advanceToIntersectionSurface( 2 );

  TEST_EQUALITY_CONST( ray.getPosition()[0], 1.0 );
  TEST_EQUALITY_CONST( ray.getPosition()[1], 1.0 );
  TEST_EQUALITY_CONST( ray.getPosition()[2], 4.0 );
  TEST_EQUALITY_CONST( ray.getCurrentCell(), 2 );
  
  // Once the ray is advanced the intersection data will be reset
  TEST_ASSERT( !ray.knowsIntersectionSurface() );
}

//---------------------------------------------------------------------------//
// Check that the ray can be advanced a substep
TEUCHOS_UNIT_TEST( DagMCRay, advanceSubstep )
{
  Geometry::Ray raw_ray( 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 );
  
  Geometry::DagMCRay ray( raw_ray, 1 );

  ray.setIntersectionSurfaceData( 10, 3.0 );

  ray.advanceSubstep( 2.0 );

  TEST_EQUALITY_CONST( ray.getPosition()[0], 1.0 );
  TEST_EQUALITY_CONST( ray.getPosition()[1], 1.0 );
  TEST_EQUALITY_CONST( ray.getPosition()[2], 3.0 );
  
  TEST_ASSERT( ray.knowsIntersectionSurface() );
  TEST_EQUALITY_CONST( ray.getIntersectionSurface(), 10 );
  TEST_EQUALITY_CONST( ray.getDistanceToIntersectionSurface(), 1.0 );
  TEST_EQUALITY_CONST( ray.getCurrentCell(), 1 );
}

//---------------------------------------------------------------------------//
// end tstDagMCRay.cpp
//---------------------------------------------------------------------------//
