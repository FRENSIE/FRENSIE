//---------------------------------------------------------------------------//
//!
//! \file   tstRay.cpp
//! \author Alex Robinson
//! \brief  Ray unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Geometry_Ray.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Get the position of a ray
TEUCHOS_UNIT_TEST( Ray, getPosition )
{
  Geometry::Ray ray( 1.0, 1.0, -1.0, 0.0, 0.0, 1.0 );

  TEST_EQUALITY_CONST( ray.getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( ray.getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( ray.getZPosition(), -1.0 );

  const double* head_position = ray.getPosition();

  TEST_EQUALITY_CONST( head_position[0], 1.0 );
  TEST_EQUALITY_CONST( head_position[1], 1.0 );
  TEST_EQUALITY_CONST( head_position[2], -1.0 );
}

//---------------------------------------------------------------------------//
// Get the direction of a ray
TEUCHOS_UNIT_TEST( Ray, getDirection )
{
  double head_position[3] = {1.0, 1.0, -1.0};
  double direction[3] = {0.0, 0.0, 1.0};
  
  Geometry::Ray ray( head_position, direction );

  TEST_EQUALITY_CONST( ray.getXDirection(), 0.0 );
  TEST_EQUALITY_CONST( ray.getYDirection(), 0.0 );
  TEST_EQUALITY_CONST( ray.getZDirection(), 1.0 );

  const double* test_direction = ray.getDirection();

  TEST_EQUALITY_CONST( test_direction[0], 0.0 );
  TEST_EQUALITY_CONST( test_direction[1], 0.0 );
  TEST_EQUALITY_CONST( test_direction[2], 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the direction can be changed
TEUCHOS_UNIT_TEST( Ray, changeDirection )
{
  Geometry::Ray ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  ray.changeDirection( 1.0, 0.0, 0.0 );

  const double* ray_direction = ray.getDirection();

  TEST_EQUALITY_CONST( ray_direction[0], 1.0 );
  TEST_EQUALITY_CONST( ray_direction[1], 0.0 );
  TEST_EQUALITY_CONST( ray_direction[2], 0.0 );

  const double new_direction[3] = {0.0, 1.0, 0.0};

  ray.changeDirection( new_direction );
  
  ray_direction = ray.getDirection();

  TEST_EQUALITY_CONST( ray_direction[0], 0.0 );
  TEST_EQUALITY_CONST( ray_direction[1], 1.0 );
  TEST_EQUALITY_CONST( ray_direction[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Advance the ray head along its direction by a specified distance
TEUCHOS_UNIT_TEST( Ray, advanceHead )
{
  const double position[3] = {1.0, 1.0, 1.0};
  const double direction[3] = {0.5773502691896258, 
			       0.5773502691896258,
			       0.5773502691896258};
  
  Geometry::Ray ray( position, direction );

  ray.advanceHead( 1.7320508075688772 );

  TEST_FLOATING_EQUALITY( ray.getXPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( ray.getYPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( ray.getZPosition(), 2.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Create a non-owning ray
TEUCHOS_UNIT_TEST( Ray, non_owning )
{
  double position[3] = {1.0, 1.0, 1.0};
  double direction[3] = {0.5773502691896258, 
			 0.5773502691896258,
			 0.5773502691896258};

  Geometry::Ray ray( position, direction, false );

  TEST_EQUALITY_CONST( ray.getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( ray.getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( ray.getZPosition(), 1.0 );
  TEST_EQUALITY_CONST( ray.getXDirection(), 0.5773502691896258 );
  TEST_EQUALITY_CONST( ray.getYDirection(), 0.5773502691896258 );
  TEST_EQUALITY_CONST( ray.getZDirection(), 0.5773502691896258 );

  position[0] = 2.0;
  position[1] = 3.0;
  position[2] = 4.0;

  TEST_EQUALITY_CONST( ray.getXPosition(), 2.0 );
  TEST_EQUALITY_CONST( ray.getYPosition(), 3.0 );
  TEST_EQUALITY_CONST( ray.getZPosition(), 4.0 );

  direction[0] = 1.0;
  direction[1] = 0.0;
  direction[2] = 0.0;

  TEST_EQUALITY_CONST( ray.getXDirection(), 1.0 );
  TEST_EQUALITY_CONST( ray.getYDirection(), 0.0 );
  TEST_EQUALITY_CONST( ray.getZDirection(), 0.0 );

  ray.advanceHead( 1.0 );

  TEST_EQUALITY_CONST( ray.getXPosition(), 3.0 );
  TEST_EQUALITY_CONST( ray.getYPosition(), 3.0 );
  TEST_EQUALITY_CONST( ray.getZPosition(), 4.0 );
  TEST_EQUALITY_CONST( position[0], 3.0 );
  TEST_EQUALITY_CONST( position[1], 3.0 );
  TEST_EQUALITY_CONST( position[2], 4.0 ); 
}

//---------------------------------------------------------------------------//
// end tstRay.cpp
//---------------------------------------------------------------------------//

