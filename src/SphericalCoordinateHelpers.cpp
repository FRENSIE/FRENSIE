//---------------------------------------------------------------------------//
//!
//! \file   SphericalCoordinateHelpers.hpp
//! \author Alex Robinson
//! \brief  Spherical coordinate helper function definitions.
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "SphericalCoordinateHelpers.hpp"
#include "PhysicalConstants.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Convert spherical coordinate (r,theta,mu) to a cartesian coordinate (x,y,z)
/*! \details The origin is assumed to be at (x,y,z) = (0,0,0)
 */
void convertSphericalCoordsToCartesian( const double spherical_point[3],
					double cartesian_point[3],
					const Axis axis)
{
  // Make sure that the spherical point is valid
  testPrecondition( spherical_point[0] >= 0.0 );
  testPrecondition( spherical_point[1] >= 0.0 );
  testPrecondition( spherical_point[1] <= 2*PhysicalConstants::pi );
  testPrecondition( spherical_point[2] >= -1.0 );
  testPrecondition( spherical_point[2] <= 1.0 );
  
  double cos_theta = cos( spherical_point[1] );
  double sin_theta = sin( spherical_point[1] );
  double sin_phi = sqrt( 1.0 - spherical_point[2]*spherical_point[2] );
  
  switch( axis )
  {
  case Z_AXIS:
    cartesian_point[0] = sin_phi*cos_theta*spherical_point[0];
    cartesian_point[1] = sin_phi*sin_theta*spherical_point[0];
    cartesian_point[2] = spherical_point[2]*spherical_point[0];
    break;
  case Y_AXIS:
    cartesian_point[0] = sin_phi*sin_theta*spherical_point[0];
    cartesian_point[1] = spherical_point[2]*spherical_point[0];
    cartesian_point[2] = sin_phi*cos_theta*spherical_point[0];
    break;
  case X_AXIS:
    cartesian_point[0] = spherical_point[2]*spherical_point[0];
    cartesian_point[1] = sin_phi*cos_theta*spherical_point[0];
    cartesian_point[2] = sin_phi*sin_theta*spherical_point[0];
    break;
  }

  // Make sure that the returned point is valid
  remember( typedef Teuchos::ScalarTraits<double> ST );
  testPostcondition( !ST::isnaninf( cartesian_point[0] ) );
  testPostcondition( !ST::isnaninf( cartesian_point[1] ) );
  testPostcondition( !ST::isnaninf( cartesian_point[2] ) );
}

// Convert cartesian coordinate (x,y,z) to spherical (r,theta,mu)
/* \details The origin of the spherical coordinate system w.r.t. the
 * cartesian coordinate system must be specified.
 */
void convertCartesianCoordsToSpherical( const double cartesian_point[3],
					const double origin[3],
					double spherical_point[3],
					const Axis axis )
{
  double x_distance = (cartesian_point[0] - origin[0]);
  double y_distance = (cartesian_point[1] - origin[1]);
  double z_distance = (cartesian_point[2] - origin[2]);
  
  double radius = sqrt( x_distance*x_distance + y_distance*y_distance + 
			z_distance*z_distance );
  spherical_point[0] = radius;
  
  if( radius > 0.0 )
  {
    switch( axis )
    {
    case Z_AXIS:
      // theta = atan( y/x )
      spherical_point[1] = atan2( y_distance, x_distance );
      // mu = z/r
      spherical_point[2] = z_distance/radius;
      break;
    case Y_AXIS:
      // theta = atan( x/z )
      spherical_point[1] = atan2( x_distance, z_distance );
      // mu = y/r
      spherical_point[2] = y_distance/radius;
      break;
    case X_AXIS:
      // theta = atan( z/y )
      spherical_point[1] = atan2( z_distance, y_distance );
      // mu = x/r
      spherical_point[2] = x_distance/radius;
      break;
    }
  }
  else // radius == 0.0
  {
    spherical_point[1] = 0.0;
    spherical_point[2] = 0.0;
  }

  // Convert the theta value in [-pi,pi] to [0,2pi]
  if( spherical_point[1] < 0.0 )
    spherical_point[1] += 2*PhysicalConstants::pi;

  // Make sure that the point returned is valid
  remember( typedef Teuchos::ScalarTraits<double> ST );
  testPostcondition( !ST::isnaninf( spherical_point[0] ) );
  testPostcondition( !ST::isnaninf( spherical_point[1] ) );
  testPostcondition( !ST::isnaninf( spherical_point[2] ) );
  testPostcondition( spherical_point[0] >= 0.0 );
  testPostcondition( spherical_point[1] >= 0.0 );
  testPostcondition( spherical_point[1] <= 2*PhysicalConstants::pi );
  testPostcondition( spherical_point[2] >= -1.0 );
  testPostcondition( spherical_point[2] <= 1.0 );
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end SphericalCoordinateHelpers.cpp
//---------------------------------------------------------------------------//
