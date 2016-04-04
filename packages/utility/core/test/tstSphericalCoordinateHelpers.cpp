//---------------------------------------------------------------------------//
//! 
//! \file   tstSphericalCoordinateHelpers.cpp
//! \author Alex Robinson
//! \brief  Spherical coordinate helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_SphericalCoordinateHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a spherical coordinate (with mu parallel to the z-axis) can be 
// converted to a cartesian coordinate
TEUCHOS_UNIT_TEST( SphericalCoordinateHelpers, 
		   convertSphericalCoordsToCartesian_zaxis )
{
  double cartesian_point[3];
  
  // (r=1.0,theta=0.0,mu=1.0) -> (x=0.0,y=0.0,z=1.0)
  double spherical_point[3] = {1.0, 0.0, 1.0};

  Utility::convertSphericalCoordsToCartesian( spherical_point, 
					      cartesian_point,
					      Utility::Z_AXIS );
  
  TEST_EQUALITY_CONST( cartesian_point[0], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], 1.0 );
  
  // (r=1.0,theta=0.0,mu=-1.0) -> (x=0.0,y=0.0,z=-1.0)
  spherical_point[2] = -1.0;

  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::Z_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], -1.0 );

  // (r=1.0,theta=0.0,mu=0.0) -> (x=1.0,y=0.0,z=0.0)
  spherical_point[2] = 0.0;
  
  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::Z_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], 1.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], 0.0 );

  // (r=1.0,theta=pi/2,mu=0.0) -> (x=0.0,y=1.0,z=0.0)
  spherical_point[1] = Utility::PhysicalConstants::pi/2;
  
  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::Z_AXIS );

  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[0], 0.0, 1e-15 );
  TEST_EQUALITY_CONST( cartesian_point[1], 1.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], 0.0 );

  // (r=1.0,theta=pi,mu=0.0) -> (x=-1.0,y=1.0,z=0.0)
  spherical_point[1] = Utility::PhysicalConstants::pi;

  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::Z_AXIS );
  
  TEST_EQUALITY_CONST( cartesian_point[0], -1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[1], 0.0, 1e-15 );
  TEST_EQUALITY_CONST( cartesian_point[2], 0.0 );

  // (r=1.0,theta=3pi/2,mu=0.0) -> (x=0.0,y=-1.0,z=0.0)
  spherical_point[1] = 3*Utility::PhysicalConstants::pi/2;
  
  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::Z_AXIS );

  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[0], 0.0, 1e-15 );
  TEST_EQUALITY_CONST( cartesian_point[1], -1.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], 0.0 );

  // (r=sqrt(3),theta=pi/4,mu=1/sqrt(3)) -> (x=1.0,y=1.0,z=1.0)
  spherical_point[0] = sqrt(3.0);
  spherical_point[1] = Utility::PhysicalConstants::pi/4;
  spherical_point[2] = 1.0/sqrt(3.0);

  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::Z_AXIS );

  TEST_FLOATING_EQUALITY( cartesian_point[0], 1.0, 1e-15 );
  TEST_FLOATING_EQUALITY( cartesian_point[1], 1.0, 1e-15 );
  TEST_FLOATING_EQUALITY( cartesian_point[2], 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a spherical coordinate (with mu parallel to the y-axis) can be 
// converted to a cartesian coordinate
TEUCHOS_UNIT_TEST( SphericalCoordinateHelpers, 
		   convertSphericalCoordsToCartesian_yaxis )
{
  double cartesian_point[3];
  
  // (r=1.0,theta=0.0,mu=1.0) -> (x=0.0,y=1.0,z=0.0)
  double spherical_point[3] = {1.0, 0.0, 1.0};

  Utility::convertSphericalCoordsToCartesian( spherical_point, 
					      cartesian_point,
					      Utility::Y_AXIS );
  
  TEST_EQUALITY_CONST( cartesian_point[0], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], 1.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], 0.0 );
  
  // (r=1.0,theta=0.0,mu=-1.0) -> (x=0.0,y=1.0,z=0.0)
  spherical_point[2] = -1.0;

  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::Y_AXIS );
  
  TEST_EQUALITY_CONST( cartesian_point[0], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], -1.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], 0.0 );

  // (r=1.0,theta=0.0,mu=0.0) -> (x=0.0,y=0.0,z=1.0)
  spherical_point[2] = 0.0;
  
  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::Y_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], 1.0 );

  // (r=1.0,theta=pi/2,mu=0.0) -> (x=1.0,y=0.0,z=0.0)
  spherical_point[1] = Utility::PhysicalConstants::pi/2;
  
  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::Y_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], 1.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[2], 0.0, 1e-15 );

  // (r=1.0,theta=pi,mu=0.0) -> (x=0.0,y=0.0,z=-1.0)
  spherical_point[1] = Utility::PhysicalConstants::pi;

  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::Y_AXIS );

  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[0], 0.0, 1e-15 );
  TEST_EQUALITY_CONST( cartesian_point[1], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], -1.0 );

  // (r=1.0,theta=3pi/2,mu=0.0) -> (x=-1.0,y=0.0,z=0.0)
  spherical_point[1] = 3*Utility::PhysicalConstants::pi/2;
  
  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::Y_AXIS );
  
  TEST_EQUALITY_CONST( cartesian_point[0], -1.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[2], 0.0, 1e-15 );

  // (r=sqrt(3),theta=pi/4,mu=1/sqrt(3)) -> (x=1.0,y=1.0,z=1.0)
  spherical_point[0] = sqrt(3.0);
  spherical_point[1] = Utility::PhysicalConstants::pi/4;
  spherical_point[2] = 1.0/sqrt(3.0);

  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::Y_AXIS );

  TEST_FLOATING_EQUALITY( cartesian_point[0], 1.0, 1e-15 );
  TEST_FLOATING_EQUALITY( cartesian_point[1], 1.0, 1e-15 );
  TEST_FLOATING_EQUALITY( cartesian_point[2], 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a spherical coordinate (with mu parallel to the x-axis) can be 
// converted to a cartesian coordinate
TEUCHOS_UNIT_TEST( SphericalCoordinateHelpers, 
		   convertSphericalCoordsToCartesian_xaxis )
{
  double cartesian_point[3];
  
  // (r=1.0,theta=0.0,mu=1.0) -> (x=1.0,y=0.0,z=0.0)
  double spherical_point[3] = {1.0, 0.0, 1.0};

  Utility::convertSphericalCoordsToCartesian( spherical_point, 
					      cartesian_point,
					      Utility::X_AXIS );
  
  TEST_EQUALITY_CONST( cartesian_point[0], 1.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], 0.0 );
  
  // (r=1.0,theta=0.0,mu=-1.0) -> (x=-1.0,y=0.0,z=0.0)
  spherical_point[2] = -1.0;

  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::X_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], -1.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], 0.0 );

  // (r=1.0,theta=0.0,mu=0.0) -> (x=0.0,y=1.0,z=0.0)
  spherical_point[2] = 0.0;
  
  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::X_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], 1.0 );
  TEST_EQUALITY_CONST( cartesian_point[2], 0.0 );

  // (r=1.0,theta=pi/2,mu=0.0) -> (x=0.0,y=0.0,z=1.0)
  spherical_point[1] = Utility::PhysicalConstants::pi/2;
  
  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::X_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[1], 0.0, 1e-15 );
  TEST_EQUALITY_CONST( cartesian_point[2], 1.0 );

  // (r=1.0,theta=pi,mu=0.0) -> (x=0.0,y=-1.0,z=0.0)
  spherical_point[1] = Utility::PhysicalConstants::pi;

  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::X_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], 0.0 );
  TEST_EQUALITY_CONST( cartesian_point[1], -1.0 );
  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[2], 0.0, 1e-15 );

  // (r=1.0,theta=3pi/2,mu=0.0) -> (x=0.0,y=0.0,z=-1.0)
  spherical_point[1] = 3*Utility::PhysicalConstants::pi/2;
  
  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::X_AXIS );

  TEST_EQUALITY_CONST( cartesian_point[0], 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( cartesian_point[1], 0.0, 1e-15 );
  TEST_EQUALITY_CONST( cartesian_point[2], -1.0 );

  // (r=sqrt(3),theta=pi/4,mu=1/sqrt(3)) -> (x=1.0,y=1.0,z=1.0)
  spherical_point[0] = sqrt(3.0);
  spherical_point[1] = Utility::PhysicalConstants::pi/4;
  spherical_point[2] = 1.0/sqrt(3.0);

  Utility::convertSphericalCoordsToCartesian( spherical_point,
					      cartesian_point,
					      Utility::X_AXIS );
  
  TEST_FLOATING_EQUALITY( cartesian_point[0], 1.0, 1e-15 );
  TEST_FLOATING_EQUALITY( cartesian_point[1], 1.0, 1e-15 );
  TEST_FLOATING_EQUALITY( cartesian_point[2], 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a cartesian coordinate can be converted to a cartesian 
// coordinate (with mu parallel to the z-axis)
TEUCHOS_UNIT_TEST( SphericalCoordinateHelpers, 
		   convertCartesianCoordsToSpherical_zaxis )
{
  double spherical_point[3];
  
  const double origin[3] = {1.0, 1.0, 1.0};

  // (x'=0.0,y'=0.0,z'=1.0) -> (r=1.0,theta=0.0,mu=1.0)
  double cartesian_point[3] = {1.0, 1.0, 2.0};
  
  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::Z_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], 0.0 );
  TEST_EQUALITY_CONST( spherical_point[2], 1.0 );
					     
  // (x'=0.0,y'=0.0,z'=-1.0) -> (r=1.0,theta=0.0,mu=-1.0)
  cartesian_point[2] = 0.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::Z_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], 0.0 );
  TEST_EQUALITY_CONST( spherical_point[2], -1.0 );

  // (x'=1.0,y'=0.0,z'=0.0) -> (r=1.0,theta=0.0,mu=0.0)
  cartesian_point[0] = 2.0;
  cartesian_point[2] = 1.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::Z_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], 0.0 );
  TEST_EQUALITY_CONST( spherical_point[2], 0.0 );

  // (x'=0.0,y'=1.0,z'=0.0) -> (r=1.0,theta=pi/2,mu=0.0)
  cartesian_point[0] = 1.0;
  cartesian_point[1] = 2.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::Z_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( spherical_point[2], 0.0 );
  
  // (x'=-1.0,y'=0.0,z'=0.0) -> (r=1.0,theta=pi,mu=0.0)
  cartesian_point[0] = 0.0;
  cartesian_point[1] = 1.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::Z_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( spherical_point[2], 0.0 );

  // (x'=0.0,y'=-1.0,z'=0.0) -> (r=1.0,theta=3pi/2,mu=0.0)
  cartesian_point[0] = 1.0;
  cartesian_point[1] = 0.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::Z_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], 
		       3*Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( spherical_point[2], 0.0 );

  // (x'=1.0,y'=1.0,z'=1.0) -> (r=sqrt(3),theta=pi/4,mu=1/sqrt(3))
  cartesian_point[0] = 2.0;
  cartesian_point[1] = 2.0;
  cartesian_point[2] = 2.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::Z_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], sqrt(3.0) );
  TEST_EQUALITY_CONST( spherical_point[1], Utility::PhysicalConstants::pi/4 );
  TEST_EQUALITY_CONST( spherical_point[2], 1.0/sqrt(3.0) );

  // (x'=-1.0,y'=-1.0,z'=-1.0) -> (r=sqrt(3),theta=5pi/4,mu=-1/sqrt(3))
  cartesian_point[0] = 0.0;
  cartesian_point[1] = 0.0;
  cartesian_point[2] = 0.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::Z_AXIS );
  
  TEST_EQUALITY_CONST( spherical_point[0], sqrt(3.0) );
  TEST_EQUALITY_CONST( spherical_point[1], 
		       5*Utility::PhysicalConstants::pi/4 );
  TEST_EQUALITY_CONST( spherical_point[2], -1.0/sqrt(3.0) );
}

//---------------------------------------------------------------------------//
// Check that a cartesian coordinate can be converted to a cartesian 
// coordinate (with mu parallel to the y-axis)
TEUCHOS_UNIT_TEST( SphericalCoordinateHelpers, 
		   convertCartesianCoordsToSpherical_yaxis )
{
  double spherical_point[3];
  
  const double origin[3] = {1.0, 1.0, 1.0};

  // (x'=0.0,y'=1.0,z'=0.0) -> (r=1.0,theta=0.0,mu=1.0)
  double cartesian_point[3] = {1.0, 2.0, 1.0};
  
  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::Y_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], 0.0 );
  TEST_EQUALITY_CONST( spherical_point[2], 1.0 );
					     
  // (x'=0.0,y'=-1.0,z'=0.0) -> (r=1.0,theta=0.0,mu=-1.0)
  cartesian_point[1] = 0.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::Y_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], 0.0 );
  TEST_EQUALITY_CONST( spherical_point[2], -1.0 );

  // (x'=0.0,y'=0.0,z'=1.0) -> (r=1.0,theta=0.0,mu=0.0)
  cartesian_point[1] = 1.0;
  cartesian_point[2] = 2.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::Y_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], 0.0 );
  TEST_EQUALITY_CONST( spherical_point[2], 0.0 );

  // (x'=1.0,y'=0.0,z'=0.0) -> (r=1.0,theta=pi/2,mu=0.0)
  cartesian_point[0] = 2.0;
  cartesian_point[2] = 1.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::Y_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( spherical_point[2], 0.0 );
  
  // (x'=0.0,y'=0.0,z'=-1.0) -> (r=1.0,theta=pi,mu=0.0)
  cartesian_point[0] = 1.0;
  cartesian_point[2] = 0.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::Y_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( spherical_point[2], 0.0 );

  // (x'=-1.0,y'=0.0,z'=0.0) -> (r=1.0,theta=3pi/2,mu=0.0)
  cartesian_point[0] = 0.0;
  cartesian_point[2] = 1.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::Y_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], 3*Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( spherical_point[2], 0.0 );

  // (x'=1.0,y'=1.0,z'=1.0) -> (r=sqrt(3),theta=pi/4,mu=1/sqrt(3))
  cartesian_point[0] = 2.0;
  cartesian_point[1] = 2.0;
  cartesian_point[2] = 2.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::Y_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], sqrt(3.0) );
  TEST_EQUALITY_CONST( spherical_point[1], Utility::PhysicalConstants::pi/4 );
  TEST_EQUALITY_CONST( spherical_point[2], 1.0/sqrt(3.0) );
}

//---------------------------------------------------------------------------//
// Check that a cartesian coordinate can be converted to a cartesian 
// coordinate (with mu parallel to the x-axis)
TEUCHOS_UNIT_TEST( SphericalCoordinateHelpers, 
		   convertCartesianCoordsToSpherical_xaxis )
{
  double spherical_point[3];
  
  const double origin[3] = {1.0, 1.0, 1.0};

  // (x'=1.0,y'=0.0,z'=0.0) -> (r=1.0,theta=0.0,mu=1.0)
  double cartesian_point[3] = {2.0, 1.0, 1.0};
  
  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::X_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], 0.0 );
  TEST_EQUALITY_CONST( spherical_point[2], 1.0 );
					     
  // (x'=-1.0,y'=0.0,z'=0.0) -> (r=1.0,theta=0.0,mu=-1.0)
  cartesian_point[0] = 0.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::X_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], 0.0 );
  TEST_EQUALITY_CONST( spherical_point[2], -1.0 );

  // (x'=0.0,y'=1.0,z'=0.0) -> (r=1.0,theta=0.0,mu=0.0)
  cartesian_point[0] = 1.0;
  cartesian_point[1] = 2.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::X_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], 0.0 );
  TEST_EQUALITY_CONST( spherical_point[2], 0.0 );

  // (x'=0.0,y'=0.0,z'=1.0) -> (r=1.0,theta=pi/2,mu=0.0)
  cartesian_point[1] = 1.0;
  cartesian_point[2] = 2.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::X_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( spherical_point[2], 0.0 );
  
  // (x'=0.0,y'=-1.0,z'=0.0) -> (r=1.0,theta=pi,mu=0.0)
  cartesian_point[1] = 0.0;
  cartesian_point[2] = 1.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::X_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], Utility::PhysicalConstants::pi );
  TEST_EQUALITY_CONST( spherical_point[2], 0.0 );

  // (x'=0.0,y'=0.0,z'=-1.0) -> (r=1.0,theta=3pi/2,mu=0.0)
  cartesian_point[1] = 1.0;
  cartesian_point[2] = 0.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::X_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], 1.0 );
  TEST_EQUALITY_CONST( spherical_point[1], 
		       3*Utility::PhysicalConstants::pi/2 );
  TEST_EQUALITY_CONST( spherical_point[2], 0.0 );

  // (x'=1.0,y'=1.0,z'=1.0) -> (r=sqrt(3),theta=pi/4,mu=1/sqrt(3))
  cartesian_point[0] = 2.0;
  cartesian_point[1] = 2.0;
  cartesian_point[2] = 2.0;

  Utility::convertCartesianCoordsToSpherical( cartesian_point,
					      origin,
					      spherical_point,
					      Utility::X_AXIS );

  TEST_EQUALITY_CONST( spherical_point[0], sqrt(3.0) );
  TEST_EQUALITY_CONST( spherical_point[1], Utility::PhysicalConstants::pi/4 );
  TEST_EQUALITY_CONST( spherical_point[2], 1.0/sqrt(3.0) );
}

//---------------------------------------------------------------------------//
// end tstSphericalCoordinateHelpers.cpp
//---------------------------------------------------------------------------//
