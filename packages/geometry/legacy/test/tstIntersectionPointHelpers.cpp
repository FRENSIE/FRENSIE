//---------------------------------------------------------------------------//
//!
//! \file   tstIntersectionPointHelpers.cpp
//! \author Alex Robinson
//! \brief  IntersectionPoint helper function unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Geometry_IntersectionPointHelpers.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, short, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, short, double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, long, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, long, double )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an intersection point can be created from three intersecting
// planar surfaces.
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( IntersectionPointHelpers,
				   createIntersectionPoint,
				   OrdinalType,
				   ScalarType )
{
  typedef Geometry::Surface<OrdinalType,ScalarType> Surface;
  typedef Geometry::IntersectionPoint<OrdinalType,ScalarType> IntersectionPoint;

  // Create three intersecting surfaces
  // x = 2
  Surface primary_surface( 1,
			   1, 0, 0,
			   -2 );
  // y = 2
  Surface secondary_surface( 2,
			     0, 1, 0,
			     -2 );
  // z = 0
  Surface tertiary_surface( 3,
			    0, 0, 1,
			    0 );

  IntersectionPoint test_point =
    Geometry::createIntersectionPoint( primary_surface,
				     secondary_surface,
				     tertiary_surface );

  TEST_EQUALITY_CONST( test_point[0], 2.0 );
  TEST_EQUALITY_CONST( test_point[1], 2.0 );
  TEST_EQUALITY_CONST( test_point[2], 0.0 );
}

UNIT_TEST_INSTANTIATION( IntersectionPointHelpers, createIntersectionPoint );

//---------------------------------------------------------------------------//
// end tstIntersectionPointHelpers.cpp
//---------------------------------------------------------------------------//
