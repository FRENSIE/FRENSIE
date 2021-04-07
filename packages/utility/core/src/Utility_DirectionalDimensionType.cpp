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
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Convert the string to a Utility::DirectionalDimensionType
auto FromStringTraits<DirectionalDimensionType>::fromString(
                                     const std::string& obj_rep ) -> ReturnType
{
  if( obj_rep == "U" )
    return U_DIRECTIONAL_DIMENSION;
  else if( obj_rep == "V" )
    return V_DIRECTIONAL_DIMENSION;
  else if( obj_rep == "W" )
    return W_DIRECTIONAL_DIMENSION;
  else if( obj_rep == "|R|" )
    return R_DIRECTIONAL_DIMENSION;
  else if( obj_rep == "Theta" )
    return AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION;
  else if( obj_rep == "Mu" )
    return POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "directional dimension name " << obj_rep <<
                     " cannot be converted to an enum!" );
  }
}

// Extract the object from a stream
void FromStringTraits<DirectionalDimensionType>::fromStream(
                                                 std::istream& is,
                                                 DirectionalDimensionType& obj,
                                                 const std::string& delim )
{
  BaseType::fromStreamImpl( is, obj, delim, &FromStringTraits<DirectionalDimensionType>::fromString );
}

// Stream operator for printing directional dimension type enums
std::ostream& operator<<( std::ostream& os,
                          const DirectionalDimensionType dimension )
{
  switch( dimension )
  {
    case U_DIRECTIONAL_DIMENSION:
    {
      os << "U";
      break;
    }
    case V_DIRECTIONAL_DIMENSION:
    {
      os << "V";
      break;
    }
    case W_DIRECTIONAL_DIMENSION:
    {
      os << "W";
      break;
    }
    case R_DIRECTIONAL_DIMENSION:
    {
      os << "|R|";
      break;
    }
    case AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION:
    {
      os << "Theta";
      break;
    }
    case POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION:
    {
      os << "Mu";
      break;
    }
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "an unknown DirectionalDimensionType was encountered ("
                       << (unsigned)dimension << ")!" );
    }
  }

  return os;
}

// Stream operator for extracting directional dimension type enums
std::istream& operator>>( std::istream& is,
                          DirectionalDimensionType& dimension )
{
  Utility::fromStream( is, dimension );

  return is;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_DirectionalDimensionType.cpp
//---------------------------------------------------------------------------//
