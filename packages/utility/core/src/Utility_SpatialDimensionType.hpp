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

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"

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

/*! Specialization of FromStringTraits for Utility::SpatialDimensionType
 * \ingroup from_string_traits
 */
template<>
struct FromStringTraits<SpatialDimensionType> : public Details::FromStringTraitsEnumHelper<SpatialDimensionType>
{
  //! Convert the string to a Utility::SpatialDimensionType
  static ReturnType fromString( const std::string& obj_rep );

  //! Extract the object from a stream
  static void fromStream( std::istream& is,
                          SpatialDimensionType& obj,
                          const std::string& delim = std::string() );
};

//! Stream operator for printing spatial dimension type enums
std::ostream& operator<<( std::ostream& os,
                          const SpatialDimensionType dimension );

//! Stream operator for extracting spatial dimension type enums
std::istream& operator>>( std::istream& is, SpatialDimensionType& dimension );
  
} // end Utility namespace

#endif // end UTILITY_SPATIAL_DIMENSION_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_SpatialDimensionType.hpp
//---------------------------------------------------------------------------//

