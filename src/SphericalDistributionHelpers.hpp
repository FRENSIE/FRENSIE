//---------------------------------------------------------------------------//
//!
//! \file   SphericalDistributionHelpers.hpp
//! \author Alex Robinson
//! \brief  Spherical distribution helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef SPHERICAL_DISTRIBUTION_HELPERS_HPP
#define SPHERICAL_DISTRIBUTION_HELPERS_HPP

// FACEMC Includes
#include "Axis.hpp"

namespace FACEMC{

//! Convert spherical coordinate (r,theta,mu) to cartesian (x,y,z)
void convertSphericalCoordsToCartesian( const double spherical_point[3],
					double cartesian_point[3],
					const Axis axis = Z_AXIS );

} // end FACEMC namespace 

#endif // end SPHERICAL_DISTRIBUTION_HELPERS_HPP

//---------------------------------------------------------------------------//
// end SphericalDistributionHelpers.hpp
//---------------------------------------------------------------------------//
