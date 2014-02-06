//---------------------------------------------------------------------------//
//!
//! \file   SphericalDistributionHelpers.hpp
//! \author Alex Robinson
//! \brief  Spherical distribution helper function definitions.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "SphericalDistributionHelpers.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Convert spherical coordinate (r,theta,mu) to a cartesian coordinate (x,y,z)
void convertSphericalCoordsToCartesian( const double spherical_point[3],
					double cartesian_point[3],
					const Axis axis)
{
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
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end SphericalDistributionHelpers.cpp
//---------------------------------------------------------------------------//
