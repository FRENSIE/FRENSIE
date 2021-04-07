//---------------------------------------------------------------------------//
//!
//! \file   Utility_SpatialCoordinateSystemType.hpp
//! \author Alex Robinson
//! \brief  Spatial coordinate system type enum and helper function decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SPATIAL_COORDINATE_SYSTEM_TYPE_HPP
#define UTILITY_SPATIAL_COORDINATE_SYSTEM_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"

namespace Utility{

//! The spatial coordinate system type enum
enum SpatialCoordinateSystemType
{
  CARTESIAN_SPATIAL_COORDINATE_SYSTEM = 0,
  CYLINDRICAL_SPATIAL_COORDINATE_SYSTEM,
  SPHERICAL_SPATIAL_COORDINATE_SYSTEM,
};

//! Stream operator for printing spatial coordinate system type enums
std::ostream& operator<<( std::ostream& os,
                          const SpatialCoordinateSystemType coord_system );
  
} // end Utility namespace

#endif // end UTILITY_SPATIAL_COORDINATE_SYSTEM_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_SpatialCoordinateSystemType.hpp
//---------------------------------------------------------------------------//
