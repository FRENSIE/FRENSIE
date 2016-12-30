//---------------------------------------------------------------------------//
//!
//! \file   Utility_DirectionalCoordinateSystemType.cpp
//! \author Alex Robinson
//! \brief  Directional coordinate system type helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_DirectionalCoordinateSystemType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Convert the directional coordinate system type enum to a string
std::string convertDirectionalCoordinateSystemTypeEnumToString(
                           const DirectionalCoordinateSystemType coord_system )
{
  switch( coord_system )
  {
  case CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM:
    return "Cartesian Directional Coordinate System";
  case SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM:
    return "Spherical Directional Coordinate System";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: Directional coordinate system type "
                     << (unsigned)coord_system <<
                     " cannot be converted to a string!" );
  }
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_DirectionalCoordinateSystemType.cpp
//---------------------------------------------------------------------------//
