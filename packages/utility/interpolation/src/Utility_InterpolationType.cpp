//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolationType.cpp
//! \author Alex Robinson
//! \brief  Interpolation type helper definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ExceptionTestMacros.hpp"

#define INTERPOLATION_STRING( type ) #type

namespace Utility{

// Convert an unsigned int to an InterpolationType
InterpolationType convertUnsignedToInterpolationType(
                                                   const unsigned interp_type )
{
  switch( interp_type )
  {
  case 1u: return HISTOGRAM_INTERPOLATION;
  case 2u: return LINLIN_INTERPOLATION;
  case 3u: return LINLOG_INTERPOLATION;
  case 4u: return LOGLIN_INTERPOLATION;
  case 5u: return LOGLOG_INTERPOLATION;
  case 6u: return GAMOW_INTERPOLATION;
  default:
    THROW_EXCEPTION( std::runtime_error,
                     "Error: ENDF interpolation type " << interp_type <<
                     " is not supported." );
  }
}

// Convert the InterpolationType to a string
std::string convertInterpolationTypeToString( const InterpolationType type )
{
  switch( type )
  {
  case HISTOGRAM_INTERPOLATION:
    return INTERPOLATION_STRING( HISTOGRAM_INTERPOLATION );
  case LINLIN_INTERPOLATION:
    return INTERPOLATION_STRING( LINLIN_INTERPOLATION );
  case LINLOG_INTERPOLATION:
    return INTERPOLATION_STRING( LINLOG_INTERPOLATION );
  case LOGLIN_INTERPOLATION:
    return INTERPOLATION_STRING( LOGLIN_INTERPOLATION );
  case LOGLOG_INTERPOLATION:
    return INTERPOLATION_STRING( LOGLOG_INTERPOLATION );
  case GAMOW_INTERPOLATION:
    return INTERPOLATION_STRING( GAMOW_INTERPOLATION );
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: InterpolationType " << (unsigned)type <<
                     " cannot be converted to a string!" );
  }
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_InterpolationType.cpp
//---------------------------------------------------------------------------//
