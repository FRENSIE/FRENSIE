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
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Stream operator for printing directional coordinate system type enums
std::ostream& operator<<( std::ostream& os,
                          const DirectionalCoordinateSystemType coord_system )
{
  switch( coord_system )
  {
    case CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM:
    {
      os << "Cartesian Directional Coordinate System";
      break;
    }
    case SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM:
    {
      os << "Spherical Directional Coordinate System";
      break;
    }
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "directional coordinate system type "
                       << (unsigned)coord_system <<
                       " cannot be converted to a string!" );
    }
  }

  return os;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_DirectionalCoordinateSystemType.cpp
//---------------------------------------------------------------------------//
