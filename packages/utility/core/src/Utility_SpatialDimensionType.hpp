//---------------------------------------------------------------------------//
//!
//! \file   Utility_SpatialDimensionType.hpp
//! \author Alex Robinson
//! \brief  Spatial dimension type enum and helper function decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SPATIAL_DIMENSION_TYPE_HPP
#define UTILITY_SPATIAL_DIMENSION_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

namespace Utility{

//! The spatial dimension type enum
enum SpatialDimensionType
{
  X_SPATIAL_DIMENSION = 0,
  Y_SPATIAL_DIMENSION,
  Z_SPATIAL_DIMENSION,
  R_SPATIAL_DIMENSION,
  AZIMUTHAL_ANGLE_SPATIAL_DIMENSION,
  POLAR_ANGLE_COSINE_SPATIAL_DIMENSION
};

//! Test if the spatial dimension name is valid
bool isValidSpatialDimensionName( const std::string& dimension_name );

//! Convert the spatial dimension name to a spatial dimension type enum
SpatialDimensionType convertSpatialDimensionNameToEnum(
                                           const std::string& dimension_name );

//! Convert the dimension type enum to a string
std::string convertSpatialDimensionTypeEnumToString(
                                        const SpatialDimensionType dimension );

//! Stream operator for printing spatial dimension type enums
inline std::ostream& operator<<( std::ostream& os,
                                 const SpatialDimensionType dimension )
{
  os << convertSpatialDimensionTypeEnumToString( dimension );
  return os;
}
  
} // end Utility namespace

#endif // end UTILITY_SPATIAL_DIMENSION_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_SpatialDimensionType.hpp
//---------------------------------------------------------------------------//

