//---------------------------------------------------------------------------//
//!
//! \file   SphericalCoordinateHelpers.hpp
//! \author Alex Robinson
//! \brief  Spherical coordinate helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef SPHERICAL_COORDINATE_HELPERS_HPP
#define SPHERICAL_COORDINATE_HELPERS_HPP

// FACEMC Includes
#include "Axis.hpp"

namespace FACEMC{

//! Convert spherical coordinate (r,theta,mu) to cartesian (x,y,z)
void convertSphericalCoordsToCartesian( const double spherical_point[3],
					double cartesian_point[3],
					const Axis axis = Z_AXIS );

//! Convert cartesian coordinate (x,y,z) to spherical (r,theta,mu)
void convertCartesianCoordsToSpherical( const double cartesian_point[3],
					const double origin[3],
					double spherical_point[3],
					const Axis axis = Z_AXIS );

} // end FACEMC namespace 

#endif // end SPHERICAL_COORDINATE_HELPERS_HPP

//---------------------------------------------------------------------------//
// end SphericalCoordinateHelpers.hpp
//---------------------------------------------------------------------------//
