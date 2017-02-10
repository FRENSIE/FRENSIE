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
#include "Utility_ContractException.hpp"

namespace Utility{

// Convert the spatial coordinate system type enum to a string
std::string convertSpatialCoordinateSystemTypeEnumToString(
                               const SpatialCoordinateSystemType coord_system )
{
  switch( coord_system )
  {
  case CARTESIAN_SPATIAL_COORDINATE_SYSTEM:
    return "Cartesian Spatial Coordinate System";
  case CYLINDRICAL_SPATIAL_COORDINATE_SYSTEM:
    return "Cylindrical Spatial Coordinate System";
  case SPHERICAL_SPATIAL_COORDINATE_SYSTEM:
    return "Spherical Spatial Coordinate System";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "spatial coordinate system type "
                     << (unsigned)coord_system <<
                     " cannot be converted to a string!" );
  }
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_SpatialCoordinateSystemType.cpp
//---------------------------------------------------------------------------//
