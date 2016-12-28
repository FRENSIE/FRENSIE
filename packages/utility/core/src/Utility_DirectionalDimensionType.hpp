//---------------------------------------------------------------------------//
//!
//! \file   Utility_DirectionalDimensionType.hpp
//! \author Alex Robinson
//! \brief  Directional dimension type enum and helper function decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DIRECTIONAL_DIMENSION_TYPE_HPP
#define UTILITY_DIRECTIONAL_DIMENSION_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

namespace Utility{

//! The directional dimension type enum
enum DirectionalDimensionType
{
  U_DIRECTIONAL_DIMENSION = 0,
  V_DIRECTIONAL_DIMENSION,
  W_DIRECTIONAL_DIMENSION,
  R_DIRECTIONAL_DIMENSION,
  AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION,
  POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION
};

//! Test if the directional dimension name is valid
bool isValidDirectionalDimensionName( const std::string& dimension_name );

//! Convert the directional dimension name to a directional dimension type enum
DirectionalDimensionType convertDirectionalDimensionNameToEnum(
                                           const std::string& dimension_name );

//! Convert the dimension type enum to a string
std::string convertDirectionalDimensionTypeEnumToString(
                                    const DirectionalDimensionType dimension );

//! Stream operator for printing directional dimension type enums
inline std::ostream& operator<<( std::ostream& os,
                                 const DirectionalDimensionType dimension )
{
  os << convertDirectionalDimensionTypeEnumToString( dimension );
  return os;
}
  
} // end Utility namespace

#endif // end UTILITY_DIRECTIONAL_DIMENSION_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_DirectionalDimensionType.hpp
//---------------------------------------------------------------------------//
