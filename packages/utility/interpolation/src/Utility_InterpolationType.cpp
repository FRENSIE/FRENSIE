//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolationType.cpp
//! \author Alex Robinson
//! \brief  Interpolation type helper definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_InterpolationPolicy.hpp"

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
  case 7u: return LOGLOGCOS_INTERPOLATION;
  case 8u: return LOGCOSLOG_INTERPOLATION;
  case 9u: return LINLOGCOS_INTERPOLATION;
  case 10u: return LOGCOSLIN_INTERPOLATION;
  case 11u: return LOGNUDGEDLOGCOS_INTERPOLATION;
  case 12u: return NUDGEDLOGCOSLOG_INTERPOLATION;
  case 13u: return LINNUDGEDLOGCOS_INTERPOLATION;
  case 14u: return NUDGEDLOGCOSLIN_INTERPOLATION;
  default:
    THROW_EXCEPTION( std::runtime_error,
                     "Error: ENDF interpolation type " << endf_interp_type <<
                     " is not supported." );
  }
}

// Convert a Utility::UnivariateDistributionType to a string
std::string ToStringTraits<InterpolationType>::toString(
                                                  const InterpolationType obj )
{
  switch( obj )
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
  case LOGLOGCOS_INTERPOLATION:
    return "Log-LogCos";
  case LOGCOSLOG_INTERPOLATION:
    return "LogCos-Log";
  case LINLOGCOS_INTERPOLATION:
    return "Lin-LogCos";
  case LOGCOSLIN_INTERPOLATION:
    return "LogCos-Lin";
  case LOGNUDGEDLOGCOS_INTERPOLATION:
    return "Log-NudgedLogCos";
  case NUDGEDLOGCOSLOG_INTERPOLATION:
    return "NudgedLogCos-Log";
  case LINNUDGEDLOGCOS_INTERPOLATION:
    return "Lin-NudgedLogCos";
  case NUDGEDLOGCOSLIN_INTERPOLATION:
    return "NudgedLogCos-Lin";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "InterpolationType " << (unsigned)obj <<
                     " cannot be converted to a string!" );
  }
}

// Place the Utility::UnivariateDistributionType in a stream
void ToStringTraits<InterpolationType>::toStream( std::ostream& os,
                                                  const InterpolationType obj )
{
  os << ToStringTraits<InterpolationType>::toString( obj );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_InterpolationType.cpp
//---------------------------------------------------------------------------//
