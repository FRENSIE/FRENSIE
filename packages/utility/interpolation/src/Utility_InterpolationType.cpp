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

namespace Utility{

// Convert an unsigned int to an InterpolationType
InterpolationType convertENDFInterpolationTypeToInterpolationType(
                                              const unsigned endf_interp_type )
{
  switch( endf_interp_type )
  {
  case 1u: return HISTOGRAM_INTERPOLATION;
  case 2u: return LINLIN_INTERPOLATION;
  case 3u: return LINLOG_INTERPOLATION;
  case 4u: return LOGLIN_INTERPOLATION;
  case 5u: return LOGLOG_INTERPOLATION;
  case 6u: return GAMOW_INTERPOLATION;
  default:
    THROW_EXCEPTION( std::runtime_error,
                     "Error: ENDF interpolation type " << endf_interp_type <<
                     " is not supported." );
  }
}

// Convert the InterpolationType to a string
std::string convertInterpolationTypeToString( const InterpolationType type )
{
  switch( type )
  {
  case HISTOGRAM_INTERPOLATION:
    return "Histogram";
  case LINLIN_INTERPOLATION:
    return "Lin-Lin";
  case LINLOG_INTERPOLATION:
    return "Lin-Log";
  case LOGLIN_INTERPOLATION:
    return "Log-Lin";
  case LOGLOG_INTERPOLATION:
    return "Log-Log";
  case GAMOW_INTERPOLATION:
    return "Gamow";
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
