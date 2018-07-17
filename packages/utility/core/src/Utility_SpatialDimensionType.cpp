//---------------------------------------------------------------------------//
//!
//! \file   Utility_SpatialDimensionType.cpp
//! \author Alex Robinson
//! \brief  Spatial dimension type enum helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_SpatialDimensionType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Convert the string to a Utility::SpatialDimensionType
auto FromStringTraits<SpatialDimensionType>::fromString(
                                     const std::string& obj_rep ) -> ReturnType
{
  if( obj_rep == "X" )
    return X_SPATIAL_DIMENSION;
  else if( obj_rep == "Y" )
    return Y_SPATIAL_DIMENSION;
  else if( obj_rep == "Z" )
    return Z_SPATIAL_DIMENSION;
  else if( obj_rep == "R" )
    return R_SPATIAL_DIMENSION;
  else if( obj_rep == "Theta" )
    return AZIMUTHAL_ANGLE_SPATIAL_DIMENSION;
  else if( obj_rep == "Mu" )
    return POLAR_ANGLE_COSINE_SPATIAL_DIMENSION;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "spatial dimension name " << obj_rep <<
                     " cannot be converted to an enum!" );
  }
}

// Extract the object from a stream
void FromStringTraits<SpatialDimensionType>::fromStream(
                                                     std::istream& is,
                                                     SpatialDimensionType& obj,
                                                     const std::string& delim )
{
  BaseType::fromStreamImpl( is, obj, delim, &FromStringTraits<SpatialDimensionType>::fromString );
}

// Stream operator for printing spatial dimension type enums
std::ostream& operator<<( std::ostream& os,
                          const SpatialDimensionType dimension )
{
  switch( dimension )
  {
    case X_SPATIAL_DIMENSION:
    {
      os << "X";
      break;
    }
    case Y_SPATIAL_DIMENSION:
    {
      os << "Y";
      break;
    }
    case Z_SPATIAL_DIMENSION:
    {
      os << "Z";
      break;
    }
    case R_SPATIAL_DIMENSION:
    {
      os << "R";
      break;
    }
    case AZIMUTHAL_ANGLE_SPATIAL_DIMENSION:
    {
      os << "Theta";
      break;
    }
    case POLAR_ANGLE_COSINE_SPATIAL_DIMENSION:
    {
      os << "Mu";
      break;
    }
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "an unknown SpatialDimensionType was "
                       "encountered (" << (unsigned)dimension << ")!" );
    }
  }

  return os;
}

// Stream operator for extracting spatial dimension type enums
std::istream& operator>>( std::istream& is, SpatialDimensionType& dimension )
{
  Utility::fromStream( is, dimension );

  return is;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_SpatialDimensionType.cpp
//---------------------------------------------------------------------------//
