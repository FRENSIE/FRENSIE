//---------------------------------------------------------------------------//
//!
//! \file   Utility_SpatialDimensionType.cpp
//! \author Alex Robinson
//! \brief  Spatial dimension type enum helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_SpatialDimensionType.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Test if the spatial dimension name is valid
bool isValidSpatialDimensionName( const std::string& dimension_name )
{
  if( dimension_name == "X Spatial Dimension" ||
      dimension_name == "X Dimension" )
    return true;
  else if( dimension_name == "Y Spatial Dimension" ||
           dimension_name == "Y Dimension" )
    return true;
  else if( dimension_name == "Z Spatial Dimension" ||
           dimension_name == "Z Dimension" )
    return true;
  else if( dimension_name == "R Spatial Dimension" ||
           dimension_name == "R Dimension")
    return true;
  else if( dimension_name == "Azimuthal Angle Spatial Dimension" )
    return true;
  else if( dimension_name == "Polar Angle Cosine Spatial Dimension" )
    return true;
  else
    return false;
}

// Convert the spatial dimension name to a spatial dimension type enum
SpatialDimensionType convertSpatialDimensionNameToEnum(
                                            const std::string& dimension_name )
{
  if( dimension_name == "X Spatial Dimension" ||
      dimension_name == "X Dimension" )
    return X_SPATIAL_DIMENSION;
  else if( dimension_name == "Y Spatial Dimension" ||
           dimension_name == "Y Dimension" )
    return Y_SPATIAL_DIMENSION;
  else if( dimension_name == "Z Spatial Dimension" ||
           dimension_name == "Z Dimension" )
    return Z_SPATIAL_DIMENSION;
  else if( dimension_name == "R Spatial Dimension" ||
           dimension_name == "R Dimension")
    return R_SPATIAL_DIMENSION;
  else if( dimension_name == "Azimuthal Angle Spatial Dimension" )
    return AZIMUTHAL_ANGLE_SPATIAL_DIMENSION;
  else if( dimension_name == "Polar Angle Cosine Spatial Dimension" )
    return POLAR_ANGLE_COSINE_SPATIAL_DIMENSION;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "spatial dimension name " << dimension_name <<
                     " cannot be converted to an enum!" );
  }
}

// Convert the dimension type enum to a string
std::string convertSpatialDimensionTypeEnumToString(
                                         const SpatialDimensionType dimension )
{
  switch( dimension )
  {
  case X_SPATIAL_DIMENSION:
    return "X Spatial Dimension";
  case Y_SPATIAL_DIMENSION:
    return "Y Spatial Dimension";
  case Z_SPATIAL_DIMENSION:
    return "Z Spatial Dimension";
  case R_SPATIAL_DIMENSION:
    return "R Spatial Dimension";
  case AZIMUTHAL_ANGLE_SPATIAL_DIMENSION:
    return "Azimuthal Angle Spatial Dimension";
  case POLAR_ANGLE_COSINE_SPATIAL_DIMENSION:
    return "Polar Angle Cosine Spatial Dimension";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "an unknown SpatialDimensionType was "
                     "encountered (" << (unsigned)dimension << ")!" );
  }
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_SpatialDimensionType.cpp
//---------------------------------------------------------------------------//
