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

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"

namespace Utility{

//! The directional coordinate system type enum
enum DirectionalCoordinateSystemType
{
  CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM = 0,
  SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM
};

//! Stream operator for printing directional coordinate system type enums
std::ostream& operator<<( std::ostream& os,
                          const DirectionalCoordinateSystemType coord_system );

} // end Utility namespace

#endif // end UTILITY_DIRECTIONAL_COORDINATE_SYSTEM_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_DirectionalCoordinateSystemType.hpp
//---------------------------------------------------------------------------//
