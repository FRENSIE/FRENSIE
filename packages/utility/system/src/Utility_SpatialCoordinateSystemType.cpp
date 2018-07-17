//---------------------------------------------------------------------------//
//!
//! \file   Utility_SpatialCoordinateSystemType.cpp
//! \author Alex Robinson
//! \brief  Spatial coordinate system type helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_SpatialCoordinateSystemType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

//! Stream operator for printing spatial coordinate system type enums
std::ostream& operator<<( std::ostream& os,
                          const SpatialCoordinateSystemType coord_system )
{
  switch( coord_system )
  {
    case CARTESIAN_SPATIAL_COORDINATE_SYSTEM:
    {
      os << "Cartesian Spatial Coordinate System";
      break;
    }
    case CYLINDRICAL_SPATIAL_COORDINATE_SYSTEM:
    {
      os << "Cylindrical Spatial Coordinate System";
      break;
    }
    case SPHERICAL_SPATIAL_COORDINATE_SYSTEM:
    {
      os << "Spherical Spatial Coordinate System";
      break;
    }
  default:
    THROW_EXCEPTION( std::logic_error,
                     "spatial coordinate system type "
                     << (unsigned)coord_system <<
                     " cannot be converted to a string!" );
  }

  return os;
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_SpatialCoordinateSystemType.cpp
//---------------------------------------------------------------------------//
