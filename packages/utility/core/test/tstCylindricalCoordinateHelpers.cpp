//---------------------------------------------------------------------------//
//!
//! \file   tstCylindricalCoordinateHelpers.cpp
//! \author Alex Robinson
//! \brief  Cylindrical coordinate helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_CylindricalCoordinateHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a cylindrical coordinate (with axis parallel to z-axis) can be
// converted to a cartesian coordinate
TEUCHOS_UNIT_TEST( CylindricalCoordinateHelpers,
		   convertCylindricalCoordinateToCartesian_zaxis )
{
  double cartesian_point[3];

  // (r=1.0,theta=0.0,axis=0.0) -> (x=1.0,y=0.0,z=0.0)
  double cylindrical_point[3] = {1.0, 0.0, 0.0};

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::Z_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], 1.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], 0.0 );

  // (r=1.0,theta=pi/2,axis=0.0) -> (x=0.0,y=1.0,z=0.0)
  cylindrical_point[1] = Utility::PhysicalConstants::pi/2;

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::Z_AXIS );

  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[0], 0.0, 1e-15 );
  TEST_EQUALITY_CONST( cartesian_point[1], 1.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], 0.0 );

  // (r=1.0,theta=pi,axis=0.0) -> (x=-1.0,y=0.0,z=0.0)
  cylindrical_point[1] = Utility::PhysicalConstants::pi;

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::Z_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], -1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[1], 0.0, 1e-15 );
  TEST_EQUALITY_CONST( cartesian_point[2], 0.0 );

  // (r=1.0,theta=3pi/2,axis=0.0) -> (x=0.0,y=-1.0,z=0.0)
  cylindrical_point[1] = 3*Utility::PhysicalConstants::pi/2;

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::Z_AXIS );

  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[0], 0.0, 1e-15 );
  TEST_EQUALITY_CONST( cartesian_point[1], -1.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], 0.0 );

  // (r=2.0,theta=pi/4,axis=2.0) -> (x=sqrt(2),y=sqrt(2),z=2.0)
  cylindrical_point[0] = 2.0;
  cylindrical_point[1] = Utility::PhysicalConstants::pi/4;
  cylindrical_point[2] = 2.0;

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::Z_AXIS );

  TEST_FLOATING_EQUALITY( cartesian_point[0], sqrt(2.0), 1e-15 );
  TEST_FLOATING_EQUALITY( cartesian_point[1], sqrt(2.0), 1e-15 );
  TEST_EQUALITY_CONST( cartesian_point[2], 2.0 );

  // (r=2.0,theta=5pi/4,axis=-2.0) -> (x=-sqrt(2),y=-sqrt(2),z=-2.0)
  cylindrical_point[0] = 2.0;
  cylindrical_point[1] = 5*Utility::PhysicalConstants::pi/4;
  cylindrical_point[2] = -2.0;

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::Z_AXIS );

  TEST_FLOATING_EQUALITY( cartesian_point[0], -sqrt(2.0), 1e-15 );
  TEST_FLOATING_EQUALITY( cartesian_point[1], -sqrt(2.0), 1e-15 );
  TEST_EQUALITY_CONST( cartesian_point[2], -2.0 );
}

//---------------------------------------------------------------------------//
// Check that a cylindrical coordinate (with axis parallel to y-axis) can be
// converted to a cartesian coordinate
TEUCHOS_UNIT_TEST( CylindricalCoordinateHelpers,
		   convertCylindricalCoordinateToCartesian_yaxis )
{
  double cartesian_point[3];

  // (r=1.0,theta=0.0,axis=0.0) -> (x=0.0,y=0.0,z=1.0)
  double cylindrical_point[3] = {1.0, 0.0, 0.0};

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::Y_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], 1.0 );

  // (r=1.0,theta=pi/2,axis=0.0) -> (x=1.0,y=0.0,z=0.0)
  cylindrical_point[1] = Utility::PhysicalConstants::pi/2;

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::Y_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], 1.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[2], 0.0, 1e-15 );

  // (r=1.0,theta=pi,axis=0.0) -> (x=0.0,y=0.0,z=-1.0)
  cylindrical_point[1] = Utility::PhysicalConstants::pi;

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::Y_AXIS );

  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[0], 0.0, 1e-15 );
  TEST_EQUALITY_CONST( cartesian_point[1], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], -1.0 );

  // (r=1.0,theta=3pi/2,axis=0.0) -> (x=-1.0,y=0.0,z=0.0)
  cylindrical_point[1] = 3*Utility::PhysicalConstants::pi/2;

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::Y_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], -1.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[2], 0.0, 1e-15 );

  // (r=2.0,theta=pi/4,axis=2.0) -> (x=sqrt(2),y=2.0,z=sqrt(2))
  cylindrical_point[0] = 2.0;
  cylindrical_point[1] = Utility::PhysicalConstants::pi/4;
  cylindrical_point[2] = 2.0;

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::Y_AXIS );

  TEST_FLOATING_EQUALITY( cartesian_point[0], sqrt(2.0), 1e-15 );
  TEST_EQUALITY_CONST( cartesian_point[1], 2.0 );
  TEST_FLOATING_EQUALITY( cartesian_point[2], sqrt(2.0), 1e-15 );

  // (r=2.0,theta=5pi/4,axis=-2.0) -> (x=-sqrt(2),y=-2.0,z=-sqrt(2))
  cylindrical_point[0] = 2.0;
  cylindrical_point[1] = 5*Utility::PhysicalConstants::pi/4;
  cylindrical_point[2] = -2.0;

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::Y_AXIS );

  TEST_FLOATING_EQUALITY( cartesian_point[0], -sqrt(2.0), 1e-15 );
  TEST_EQUALITY_CONST( cartesian_point[1], -2.0 );
  TEST_FLOATING_EQUALITY( cartesian_point[2], -sqrt(2.0), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a cylindrical coordinate (with axis parallel to x-axis) can be
// converted to a cartesian coordinate
TEUCHOS_UNIT_TEST( CylindricalCoordinateHelpers,
		   convertCylindricalCoordinateToCartesian_xaxis )
{
  double cartesian_point[3];

  // (r=1.0,theta=0.0,axis=0.0) -> (x=0.0,y=1.0,z=0.0)
  double cylindrical_point[3] = {1.0, 0.0, 0.0};

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::X_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], 1.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], 0.0 );

  // (r=1.0,theta=pi/2,axis=0.0) -> (x=0.0,y=0.0,z=1.0)
  cylindrical_point[1] = Utility::PhysicalConstants::pi/2;

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::X_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[1], 0.0, 1e-15 );
  TEST_EQUALITY_CONST( cartesian_point[2], 1.0 );

  // (r=1.0,theta=pi,axis=0.0) -> (x=0.0,y=-1.0,z=0.0)
  cylindrical_point[1] = Utility::PhysicalConstants::pi;

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::X_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], -1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[2], 0.0, 1e-15 );

  // (r=1.0,theta=3pi/2,axis=0.0) -> (x=0.0,y=0.0,z=-1.0)
  cylindrical_point[1] = 3*Utility::PhysicalConstants::pi/2;

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::X_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[1], 0.0, 1e-15 );
  TEST_EQUALITY_CONST( cartesian_point[2], -1.0 );

  // (r=2.0,theta=pi/4,axis=2.0) -> (x=2.0,y=sqrt(2),z=sqrt(2))
  cylindrical_point[0] = 2.0;
  cylindrical_point[1] = Utility::PhysicalConstants::pi/4;
  cylindrical_point[2] = 2.0;

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::X_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], 2.0 );
  TEST_FLOATING_EQUALITY( cartesian_point[1], sqrt(2.0), 1e-15 );
  TEST_FLOATING_EQUALITY( cartesian_point[2], sqrt(2.0), 1e-15 );

  // (r=2.0,theta=5pi/4,axis=-2.0) -> (x=-2.0,y=-sqrt(2),z=-sqrt(2))
  cylindrical_point[0] = 2.0;
  cylindrical_point[1] = 5*Utility::PhysicalConstants::pi/4;
  cylindrical_point[2] = -2.0;

  Utility::convertCylindricalCoordsToCartesian( cylindrical_point,
						cartesian_point,
						Utility::X_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], -2.0 );
  TEST_FLOATING_EQUALITY( cartesian_point[1], -sqrt(2.0), 1e-15 );
  TEST_FLOATING_EQUALITY( cartesian_point[2], -sqrt(2.0), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a cartesian coordinate can be converted to a cylindrical
// coordinate (with axis parallel to z-axis)
TEUCHOS_UNIT_TEST( CylindricalCoordinateHelpers,
		   convertCartesianCoordsToSpherical_zaxis )
{
  double cylindrical_point[3];

  const double origin[3] = {1.0, 1.0, 1.0};

  // (x'=1.0,y'=0.0,z'=0.0) -> (r=1.0,theta=0.0,axis=0.0)
  double cartesian_point[3] = {2.0, 1.0, 1.0};

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::Z_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], 1.0 );
  TEST_EQUALITY_CONST( cylindrical_point[1], 0.0 );
  TEST_EQUALITY_CONST( cylindrical_point[2], 0.0 );

  // (x'=0.0,y'=1.0,z'=0.0) -> (r=1.0,theta=pi/2,axis=0.0)
  cartesian_point[0] = 1.0;
  cartesian_point[1] = 2.0;

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::Z_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], 1.0 );
  TEST_EQUALITY_CONST( cylindrical_point[1],
		       Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( cylindrical_point[2], 0.0 );

  // (x'=-1.0,y'=0.0,z'=0.0) -> (r=1.0,theta=pi,axis=0.0)
  cartesian_point[0] = 0.0;
  cartesian_point[1] = 1.0;

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::Z_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], 1.0 );
  TEST_EQUALITY_CONST( cylindrical_point[1], Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( cylindrical_point[2], 0.0 );

  // (x'=0.0,y'=-1.0,z'=0.0) -> (r=1.0,theta=3pi/2,axis=0.0)
  cartesian_point[0] = 1.0;
  cartesian_point[1] = 0.0;

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::Z_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], 1.0 );
  TEST_EQUALITY_CONST( cylindrical_point[1],
		       3*Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( cylindrical_point[2], 0.0 );

  // (x'=1.0,y'=1.0,z'=1.0) -> (r=sqrt(2),theta=pi/4,axis=1.0)
  cartesian_point[0] = 2.0;
  cartesian_point[1] = 2.0;
  cartesian_point[2] = 2.0;

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::Z_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], sqrt(2) );
  TEST_EQUALITY_CONST( cylindrical_point[1],
		       Utility::PhysicalConstants::pi/4 );
  TEST_EQUALITY_CONST( cylindrical_point[2], 1.0 );

  // (x'=-1.0,y'=-1.0,z'=-1.0) -> (r=sqrt(2),theta=5pi/4,axis=-1.0)
  cartesian_point[0] = 0.0;
  cartesian_point[1] = 0.0;
  cartesian_point[2] = 0.0;

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::Z_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], sqrt(2) );
  TEST_EQUALITY_CONST( cylindrical_point[1],
		       5*Utility::PhysicalConstants::pi/4 );
  TEST_EQUALITY_CONST( cylindrical_point[2], -1.0 );
}

//---------------------------------------------------------------------------//
// Check that a cartesian coordinate can be converted to a cylindrical
// coordinate (with axis parallel to y-axis)
TEUCHOS_UNIT_TEST( CylindricalCoordinateHelpers,
		   convertCartesianCoordsToSpherical_yaxis )
{
  double cylindrical_point[3];

  const double origin[3] = {1.0, 1.0, 1.0};

  // (x'=0.0,y'=0.0,z'=1.0) -> (r=1.0,theta=0.0,axis=0.0)
  double cartesian_point[3] = {1.0, 1.0, 2.0};

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::Y_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], 1.0 );
  TEST_EQUALITY_CONST( cylindrical_point[1], 0.0 );
  TEST_EQUALITY_CONST( cylindrical_point[2], 0.0 );

  // (x'=1.0,y'=0.0,z'=0.0) -> (r=1.0,theta=pi/2,axis=0.0)
  cartesian_point[0] = 2.0;
  cartesian_point[2] = 1.0;

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::Y_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], 1.0 );
  TEST_EQUALITY_CONST( cylindrical_point[1],
		       Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( cylindrical_point[2], 0.0 );

  // (x'=0.0,y'=0.0,z'=-1.0) -> (r=1.0,theta=pi,axis=0.0)
  cartesian_point[0] = 1.0;
  cartesian_point[2] = 0.0;

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::Y_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], 1.0 );
  TEST_EQUALITY_CONST( cylindrical_point[1], Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( cylindrical_point[2], 0.0 );

  // (x'=-1.0,y'=0.0,z'=0.0) -> (r=1.0,theta=3pi/2,axis=0.0)
  cartesian_point[0] = 0.0;
  cartesian_point[2] = 1.0;

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::Y_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], 1.0 );
  TEST_EQUALITY_CONST( cylindrical_point[1],
		       3*Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( cylindrical_point[2], 0.0 );

  // (x'=1.0,y'=1.0,z'=1.0) -> (r=sqrt(2),theta=pi/4,axis=1.0)
  cartesian_point[0] = 2.0;
  cartesian_point[1] = 2.0;
  cartesian_point[2] = 2.0;

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::Y_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], sqrt(2) );
  TEST_EQUALITY_CONST( cylindrical_point[1],
		       Utility::PhysicalConstants::pi/4 );
  TEST_EQUALITY_CONST( cylindrical_point[2], 1.0 );

  // (x'=-1.0,y'=-1.0,z'=-1.0) -> (r=sqrt(2),theta=5pi/4,axis=-1.0)
  cartesian_point[0] = 0.0;
  cartesian_point[1] = 0.0;
  cartesian_point[2] = 0.0;

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::Y_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], sqrt(2) );
  TEST_EQUALITY_CONST( cylindrical_point[1],
		       5*Utility::PhysicalConstants::pi/4 );
  TEST_EQUALITY_CONST( cylindrical_point[2], -1.0 );
}

//---------------------------------------------------------------------------//
// Check that a cartesian coordinate can be converted to a cylindrical
// coordinate (with axis parallel to x-axis)
TEUCHOS_UNIT_TEST( CylindricalCoordinateHelpers,
		   convertCartesianCoordsToSpherical_xaxis )
{
  double cylindrical_point[3];

  const double origin[3] = {1.0, 1.0, 1.0};

  // (x'=0.0,y'=1.0,z'=0.0) -> (r=1.0,theta=0.0,axis=0.0)
  double cartesian_point[3] = {1.0, 2.0, 1.0};

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::X_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], 1.0 );
  TEST_EQUALITY_CONST( cylindrical_point[1], 0.0 );
  TEST_EQUALITY_CONST( cylindrical_point[2], 0.0 );

  // (x'=0.0,y'=0.0,z'=1.0) -> (r=1.0,theta=pi/2,axis=0.0)
  cartesian_point[1] = 1.0;
  cartesian_point[2] = 2.0;

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::X_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], 1.0 );
  TEST_EQUALITY_CONST( cylindrical_point[1],
		       Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( cylindrical_point[2], 0.0 );

  // (x'=0.0,y'=-1.0,z'=0.0) -> (r=1.0,theta=pi,axis=0.0)
  cartesian_point[1] = 0.0;
  cartesian_point[2] = 1.0;

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::X_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], 1.0 );
  TEST_EQUALITY_CONST( cylindrical_point[1], Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( cylindrical_point[2], 0.0 );

  // (x'=0.0,y'=0.0,z'=-1.0) -> (r=1.0,theta=3pi/2,axis=0.0)
  cartesian_point[1] = 1.0;
  cartesian_point[2] = 0.0;

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::X_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], 1.0 );
  TEST_EQUALITY_CONST( cylindrical_point[1],
		       3*Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( cylindrical_point[2], 0.0 );

  // (x'=1.0,y'=1.0,z'=1.0) -> (r=sqrt(2),theta=pi/4,axis=1.0)
  cartesian_point[0] = 2.0;
  cartesian_point[1] = 2.0;
  cartesian_point[2] = 2.0;

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::X_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], sqrt(2) );
  TEST_EQUALITY_CONST( cylindrical_point[1],
		       Utility::PhysicalConstants::pi/4 );
  TEST_EQUALITY_CONST( cylindrical_point[2], 1.0 );

  // (x'=-1.0,y'=-1.0,z'=-1.0) -> (r=sqrt(2),theta=5pi/4,axis=-1.0)
  cartesian_point[0] = 0.0;
  cartesian_point[1] = 0.0;
  cartesian_point[2] = 0.0;

  Utility::convertCartesianCoordsToCylindrical( cartesian_point,
						origin,
						cylindrical_point,
						Utility::X_AXIS );

  TEST_EQUALITY_CONST( cylindrical_point[0], sqrt(2) );
  TEST_EQUALITY_CONST( cylindrical_point[1],
		       5*Utility::PhysicalConstants::pi/4 );
  TEST_EQUALITY_CONST( cylindrical_point[2], -1.0 );
}

//---------------------------------------------------------------------------//
// end tstCylindricalCoordinateHelpers.cpp
//---------------------------------------------------------------------------//
