//---------------------------------------------------------------------------//
//!
//! \file   Utility_DirectionalCoordinateSystemType.hpp
//! \author Alex Robinson
//! \brief  Directional coordinate system type enum and helper function decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DIRECTIONAL_COORDINATE_SYSTEM_TYPE_HPP
#define UTILITY_DIRECTIONAL_COORDINATE_SYSTEM_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

namespace Utility{

//! The directional coordinate system type enum
enum DirectionalCoordinateSystemType
{
  CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM = 0,
  SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM
};

//! Convert the directional coordinate system type enum to a string
std::string convertDirectionalCoordinateSystemTypeEnumToString(
                          const DirectionalCoordinateSystemType coord_system );

//! Stream operator for printing dirctional coordinate system type enums
inline std::ostream& operator<<(
                           std::ostream& os,
                           const DirectionalCoordinateSystemType coord_system )
{
  os << convertDirectionalCoordinateSystemTypeEnumToString( coord_system );
  return os;
}

}

#endif // end UTILITY_DIRCTIONAL_COORDINATE_SYSTEM_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_DirectionalCoordinateSystemType.hpp
//---------------------------------------------------------------------------//
