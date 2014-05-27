//---------------------------------------------------------------------------//
//!
//! \file   Utility_CylindricalCoordinateHelpers.hpp
//! \author Alex Robinson
//! \brief  Cylindrical coordindate helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_CYLINDRICAL_COORDINATE_HELPERS_HPP
#define UTILITY_CYLINDRICAL_COORDINATE_HELPERS_HPP

// FRNECS Includes
#include "Utility_Axis.hpp"

namespace Utility{

//! Convert cylindrical coordinate (r,theta,axis) to cartesian (x,y,z)
void convertCylindricalCoordsToCartesian( const double cylindrical_point[3],
					  double cartesian_point[3],
					  const Axis axis = Z_AXIS );

//! Convert cartesian coordinate (x,y,z) to cylindrical (r,theta,axis)
void convertCartesianCoordsToCylindrical( const double cartesian_point[3],
					  const double origin[3],
					  double cylindrical_point[3],
					  const Axis axis = Z_AXIS );
					  
} // end Utility namespace

#endif // end UTILITY_CYLINDRICAL_COORDINATE_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_CylindricalCoordinateHelpers.hpp
//---------------------------------------------------------------------------//
