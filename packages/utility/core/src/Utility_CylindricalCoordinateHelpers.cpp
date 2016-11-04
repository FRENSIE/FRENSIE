//---------------------------------------------------------------------------//
//!
//! \file   Utility_CylindricalCoordinateHelpers.cpp
//! \author Alex Robinson
//! \brief  Cylindrical coordinate helper function definitions.
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_CylindricalCoordinateHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Convert cylindrical coordinate (r,theta,axis) to cartesian (x,y,z)
/*! \details The origin is assumed to be at (x,y,z) = (0,0,0). If it is not,
 * the returned cartesian coordinate must be shifted.
 */
void convertCylindricalCoordsToCartesian( const double cylindrical_point[3],
					  double cartesian_point[3],
					  const Axis axis )
{
  // Make sure the cylindrical point is valid
  remember( typedef Teuchos::ScalarTraits<double> ST );
  testPrecondition( cylindrical_point[0] >= 0.0 );
  testPrecondition( cylindrical_point[1] >= 0.0 );
  testPrecondition( cylindrical_point[1] <= 2*PhysicalConstants::pi );
  testPrecondition( !ST::isnaninf( cylindrical_point[2] ) );

  double cos_theta = cos( cylindrical_point[1] );
  double sin_theta = sin( cylindrical_point[1] );

  switch( axis )
  {
  case Z_AXIS:
    cartesian_point[0] = cylindrical_point[0]*cos_theta;
    cartesian_point[1] = cylindrical_point[0]*sin_theta;
    cartesian_point[2] = cylindrical_point[2];
    break;

  case Y_AXIS:
    cartesian_point[0] = cylindrical_point[0]*sin_theta;
    cartesian_point[1] = cylindrical_point[2];
    cartesian_point[2] = cylindrical_point[0]*cos_theta;
    break;

  case X_AXIS:
    cartesian_point[0] = cylindrical_point[2];
    cartesian_point[1] = cylindrical_point[0]*cos_theta;
    cartesian_point[2] = cylindrical_point[0]*sin_theta;
    break;
  }

  // Make sure that the returned point is valid
  testPostcondition( !ST::isnaninf( cartesian_point[0] ) );
  testPostcondition( !ST::isnaninf( cartesian_point[1] ) );
  testPostcondition( !ST::isnaninf( cartesian_point[2] ) );
}

// Convert cartesian coordinate (x,y,z) to cylindrical (r,theta,axis)
/*! \details The origin of the cylindrical coordinate system w.r.t. the
 * cartesian coordinate system must be specified.
 */
void convertCartesianCoordsToCylindrical( const double cartesian_point[3],
					  const double origin[3],
					  double cylindrical_point[3],
					  const Axis axis )
{
  // Make sure that the cartesian point is valid
  remember( typedef Teuchos::ScalarTraits<double> ST );
  testPrecondition( !ST::isnaninf( cartesian_point[0] ) );
  testPrecondition( !ST::isnaninf( cartesian_point[1] ) );
  testPrecondition( !ST::isnaninf( cartesian_point[2] ) );
  // Make sure that the origin is valid
  testPrecondition( !ST::isnaninf( origin[0] ) );
  testPrecondition( !ST::isnaninf( origin[1] ) );
  testPrecondition( !ST::isnaninf( origin[2] ) );

  double x_distance = (cartesian_point[0] - origin[0]);
  double y_distance = (cartesian_point[1] - origin[1]);
  double z_distance = (cartesian_point[2] - origin[2]);

  switch( axis )
  {
  case Z_AXIS:
    // r = sqrt( x'^2 + y'^2 )
    cylindrical_point[0] = sqrt(x_distance*x_distance + y_distance*y_distance);
    // theta = atan( y'/x' )
    cylindrical_point[1] = atan2( y_distance, x_distance );
    // axis = z'
    cylindrical_point[2] = z_distance;
    break;
  case Y_AXIS:
    // r = sqrt( z'^2 + x'^2 )
    cylindrical_point[0] = sqrt(z_distance*z_distance + x_distance*x_distance);
    // theta = atan( x'/z' )
    cylindrical_point[1] = atan2( x_distance, z_distance );
    // axis = y'
    cylindrical_point[2] = y_distance;
    break;
  case X_AXIS:
    // r = sqrt( y'^2 + z'^2 )
    cylindrical_point[0] = sqrt(y_distance*y_distance + z_distance*z_distance);
    // theta = atan( z'/y' )
    cylindrical_point[1] = atan2( z_distance, y_distance );
    // axis = x'
    cylindrical_point[2] = x_distance;
    break;
  }

  // If the radius is zero, set the angle to zero as well
  if( cylindrical_point[0] == 0.0 )
    cylindrical_point[1] = 0.0;

  // Convert the theta value in [-pi,pi] to [0,2pi]
  if( cylindrical_point[1] < 0.0 )
    cylindrical_point[1] += 2*PhysicalConstants::pi;

  // Make sure that the point returned is valid
  testPostcondition( !ST::isnaninf( cylindrical_point[0] ) );
  testPostcondition( !ST::isnaninf( cylindrical_point[1] ) );
  testPostcondition( !ST::isnaninf( cylindrical_point[2] ) );
  testPostcondition( cylindrical_point[0] >= 0.0 );
  testPostcondition( cylindrical_point[1] >= 0.0 );
  testPostcondition( cylindrical_point[1] <= 2*PhysicalConstants::pi );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end CylindricalCoordinateHelpers.cpp
//---------------------------------------------------------------------------//
