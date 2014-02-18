//---------------------------------------------------------------------------//
//!
//! \file   CylindricalCoordinateHelpers.hpp
//! \author Alex Robinson
//! \brief  Cylindrical coordindate helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef CYLINDRICAL_COORDINATE_HELPERS_HPP
#define CYLINDRICAL_COORDINATE_HELPERS_HPP

// FACEMC Includes
#include "Axis.hpp"

namespace FACEMC{

//! Convert cylindrical coordinate (r,theta,axis) to cartesian (x,y,z)
void convertCylindricalCoordsToCartesian( const double cylindrical_point[3],
					  double cartesian_point[3],
					  const Axis axis = Z_AXIS );

//! Convert cartesian coordinate (x,y,z) to cylindrical (r,theta,axis)
void convertCartesianCoordsToCylindrical( const double cartesian_point[3],
					  const double origin[3],
					  double cylindrical_point[3],
					  const Axis axis = Z_AXIS );
					  
} // end FACEMC namespace

#endif // end CYLINDRICAL_COORDINATE_HELPERS_HPP

//---------------------------------------------------------------------------//
// end CylindricalCoordinateHelpers.hpp
//---------------------------------------------------------------------------//
