//---------------------------------------------------------------------------//
//!
//! \file   Utility_DirectionalDimensionType.cpp
//! \author Alex Robinson
//! \brief  Directional dimension type enum helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_DirectionalDimensionType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Test if the directional dimension name is valid
bool isValidDirectionalDimensionName( const std::string& dimension_name )
{
  if( dimension_name == "U Directional Dimension" ||
      dimension_name == "U Dimension" )
    return true;
  else if( dimension_name == "V Directional Dimension" ||
           dimension_name == "V Dimension" )
    return true;
  else if( dimension_name == "W Directional Dimension" ||
           dimension_name == "W Dimension" )
    return true;
  else if( dimension_name == "R Directional Dimension" )
    return true;
  else if( dimension_name == "Azimuthal Angle Directional Dimension" )
    return true;
  else if( dimension_name == "Polar Angle Cosine Directional Dimension" )
    return true;
  else
    return false;
}

// Convert the directional dimension name to a directional dimension type enum
DirectionalDimensionType convertDirectionalDimensionNameToEnum(
                                            const std::string& dimension_name )
{
  if( dimension_name == "U Directional Dimension" ||
      dimension_name == "U Dimension" )
    return U_DIRECTIONAL_DIMENSION;
  else if( dimension_name == "V Directional Dimension" ||
           dimension_name == "V Dimension" )
    return V_DIRECTIONAL_DIMENSION;
  else if( dimension_name == "W Directional Dimension" ||
           dimension_name == "W Dimension" )
    return W_DIRECTIONAL_DIMENSION;
  else if( dimension_name == "R Directional Dimension" )
    return R_DIRECTIONAL_DIMENSION;
  else if( dimension_name == "Azimuthal Angle Directional Dimension" )
    return AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION;
  else if( dimension_name == "Polar Angle Cosine Directional Dimension" )
    return POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: Directional dimension name " << dimension_name <<
                     " cannot be converted to an enum!" );
  }
}

// Convert the dimension type enum to a string
std::string convertDirectionalDimensionTypeEnumToString(
                                     const DirectionalDimensionType dimension )
{
  switch( dimension )
  {
  case U_DIRECTIONAL_DIMENSION:
    return "U Directional Dimension";
  case V_DIRECTIONAL_DIMENSION:
    return "V Directional Dimension";
  case W_DIRECTIONAL_DIMENSION:
    return "W Directional Dimension";
  case R_DIRECTIONAL_DIMENSION:
    return "R Directional Dimension";
  case AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION:
    return "Azimuthal Angle Directional Dimension";
  case POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION:
    return "Polar Angle Cosine Directional Dimension";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: An unknown DirectionalDimensionType was "
                     "encountered (" << (unsigned)dimension << ")!" );
  }
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_DirectionalDimensionType.cpp
//---------------------------------------------------------------------------//
