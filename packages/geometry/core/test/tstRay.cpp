//---------------------------------------------------------------------------//
//!
//! \file   tstRay.cpp
//! \author Alex Robinson
//! \brief  Ray unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Geometry_Ray.hpp"
#include "Utility_Array.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Get the position of a ray
FRENSIE_UNIT_TEST( Ray, getPosition )
{
  Geometry::Ray ray( 1.0, 1.0, -1.0, 0.0, 0.0, 1.0 );

  FRENSIE_CHECK_EQUAL( ray.getXPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( ray.getYPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( ray.getZPosition(), -1.0 );

  const double* head_position = ray.getPosition();

  FRENSIE_CHECK_EQUAL( head_position[0], 1.0 );
  FRENSIE_CHECK_EQUAL( head_position[1], 1.0 );
  FRENSIE_CHECK_EQUAL( head_position[2], -1.0 );
}

//---------------------------------------------------------------------------//
// Get the direction of a ray
FRENSIE_UNIT_TEST( Ray, getDirection )
{
  double head_position[3] = {1.0, 1.0, -1.0};
  double direction[3] = {0.0, 0.0, 1.0};

  Geometry::Ray ray( head_position, direction );

  FRENSIE_CHECK_EQUAL( ray.getXDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( ray.getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( ray.getZDirection(), 1.0 );

  const double* test_direction = ray.getDirection();

  FRENSIE_CHECK_EQUAL( test_direction[0], 0.0 );
  FRENSIE_CHECK_EQUAL( test_direction[1], 0.0 );
  FRENSIE_CHECK_EQUAL( test_direction[2], 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the direction can be changed
FRENSIE_UNIT_TEST( Ray, changeDirection )
{
  Geometry::Ray ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );

  ray.changeDirection( 1.0, 0.0, 0.0 );

  const double* ray_direction = ray.getDirection();

  FRENSIE_CHECK_EQUAL( ray_direction[0], 1.0 );
  FRENSIE_CHECK_EQUAL( ray_direction[1], 0.0 );
  FRENSIE_CHECK_EQUAL( ray_direction[2], 0.0 );

  const double new_direction[3] = {0.0, 1.0, 0.0};

  ray.changeDirection( new_direction );

  ray_direction = ray.getDirection();

  FRENSIE_CHECK_EQUAL( ray_direction[0], 0.0 );
  FRENSIE_CHECK_EQUAL( ray_direction[1], 1.0 );
  FRENSIE_CHECK_EQUAL( ray_direction[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Advance the ray head along its direction by a specified distance
FRENSIE_UNIT_TEST( Ray, advanceHead )
{
  const double position[3] = {1.0, 1.0, 1.0};
  const double direction[3] = {0.5773502691896258,
			       0.5773502691896258,
			       0.5773502691896258};

  Geometry::Ray ray( position, direction );

  ray.advanceHead( 1.7320508075688772 );

  FRENSIE_CHECK_FLOATING_EQUALITY( ray.getXPosition(), 2.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( ray.getYPosition(), 2.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( ray.getZPosition(), 2.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Create a non-owning ray
FRENSIE_UNIT_TEST( Ray, non_owning )
{
  double position[3] = {1.0, 1.0, 1.0};
  double direction[3] = {0.5773502691896258,
			 0.5773502691896258,
			 0.5773502691896258};

  Geometry::Ray ray( position, direction, false );

  FRENSIE_CHECK_EQUAL( ray.getXPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( ray.getYPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( ray.getZPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( ray.getXDirection(), 0.5773502691896258 );
  FRENSIE_CHECK_EQUAL( ray.getYDirection(), 0.5773502691896258 );
  FRENSIE_CHECK_EQUAL( ray.getZDirection(), 0.5773502691896258 );

  position[0] = 2.0;
  position[1] = 3.0;
  position[2] = 4.0;

  FRENSIE_CHECK_EQUAL( ray.getXPosition(), 2.0 );
  FRENSIE_CHECK_EQUAL( ray.getYPosition(), 3.0 );
  FRENSIE_CHECK_EQUAL( ray.getZPosition(), 4.0 );

  direction[0] = 1.0;
  direction[1] = 0.0;
  direction[2] = 0.0;

  FRENSIE_CHECK_EQUAL( ray.getXDirection(), 1.0 );
  FRENSIE_CHECK_EQUAL( ray.getYDirection(), 0.0 );
  FRENSIE_CHECK_EQUAL( ray.getZDirection(), 0.0 );

  ray.advanceHead( 1.0 );

  FRENSIE_CHECK_EQUAL( ray.getXPosition(), 3.0 );
  FRENSIE_CHECK_EQUAL( ray.getYPosition(), 3.0 );
  FRENSIE_CHECK_EQUAL( ray.getZPosition(), 4.0 );
  FRENSIE_CHECK_EQUAL( position[0], 3.0 );
  FRENSIE_CHECK_EQUAL( position[1], 3.0 );
  FRENSIE_CHECK_EQUAL( position[2], 4.0 );
}

//---------------------------------------------------------------------------//
// end tstRay.cpp
//---------------------------------------------------------------------------//

