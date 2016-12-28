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

namespace Utility{

//! The spatial coordinate system type enum
enum SpatialCoordinateSystemType
{
  CARTESIAN_SPATIAL_COORDINATE_SYSTEM = 0,
  CYLINDRICAL_SPATIAL_COORDINATE_SYSTEM,
  SPHERICAL_SPATIAL_COORDINATE_SYSTEM,
};

//! Convert the spatial coordinate system type enum to a string
std::string convertSpatialCoordinateSystemTypeEnumToString(
                              const SpatialCoordinateSystemType coord_system );

//! Stream operator for printing spatial coordinate system type enums
inline std::ostream& operator<<(
                               std::ostream& os,
                               const SpatialCoordinateSystemType coord_system )
{
  os << convertSpatialCoordinateSystemTypeEnumToString( coord_system );
  return os;
}
  
} // end Utility namespace

#endif // end UTILITY_SPATIAL_COORDINATE_SYSTEM_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_SpatialCoordinateSystemType.hpp
//---------------------------------------------------------------------------//
