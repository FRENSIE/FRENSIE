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

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"

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

/*! Specialization of FromStringTraits for Utility::DirectionalDimensionType
 * \ingroup from_string_traits
 */
template<>
struct FromStringTraits<DirectionalDimensionType> : public Details::FromStringTraitsEnumHelper<DirectionalDimensionType>
{
  //! Convert the string to a Utility::SpatialDimensionType
  static ReturnType fromString( const std::string& obj_rep );

  //! Extract the object from a stream
  static void fromStream( std::istream& is,
                          DirectionalDimensionType& obj,
                          const std::string& delim = std::string() );
};

//! Stream operator for printing directional dimension type enums
std::ostream& operator<<( std::ostream& os,
                          const DirectionalDimensionType dimension );

//! Stream operator for extracting directional dimension type enums
std::istream& operator>>( std::istream& is,
                          DirectionalDimensionType& dimension );
  
} // end Utility namespace

#endif // end UTILITY_DIRECTIONAL_DIMENSION_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_DirectionalDimensionType.hpp
//---------------------------------------------------------------------------//
