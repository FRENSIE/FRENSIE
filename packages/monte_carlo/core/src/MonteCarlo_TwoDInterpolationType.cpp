//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TwoDInterpolationType.cpp
//! \author Luke Kersting
//! \brief  TwoDInterpolation type helper definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_ExceptionTestMacros.hpp"
#include "MonteCarlo_TwoDInterpolationType.hpp"

namespace MonteCarlo{

// // Convert string to TwoDInterpolationType
// TwoDInterpolationType
// convertStringToTwoDInterpolationType( const std::string raw_policy )
// {
//   if( raw_policy == "LinLinLin" || raw_policy == "linlinlin" || raw_policy == "LINLINLIN" ||
//       raw_policy == "Lin-Lin-Lin" || raw_policy == "lin-lin-lin" || raw_policy == "LIN-LIN-LIN" )
//     return LINLINLIN_INTERPOLATION;
//   else if( raw_policy == "LinLinLog" || raw_policy == "linlinlog" || raw_policy == "LINLINLOG" ||
//            raw_policy == "Lin-Lin-Log" || raw_policy == "lin-lin-log" || raw_policy == "LIN-LIN-LOG" )
//     return LINLINLOG_INTERPOLATION;
//   else if( raw_policy == "LinLogLin" || raw_policy == "linloglin" || raw_policy == "LINLOGLIN" ||
//            raw_policy == "Lin-Log-Lin" || raw_policy == "lin-log-lin" || raw_policy == "LIN-LOG-LIN" )
//     return LINLOGLIN_INTERPOLATION;
//   else if( raw_policy == "LogLinLin" || raw_policy == "loglinlin" || raw_policy == "LOGLINLIN" ||
//            raw_policy == "Log-Lin-Lin" || raw_policy == "log-lin-lin" || raw_policy == "LOG-LIN-LIN" )
//     return LOGLINLIN_INTERPOLATION;
//   else if( raw_policy == "LinLogLog" || raw_policy == "linloglog" || raw_policy == "LINLOGLOG" ||
//            raw_policy == "Lin-Log-Log" || raw_policy == "lin-log-log" || raw_policy == "LIN-LOG-LOG" )
//     return LINLOGLOG_INTERPOLATION;
//   else if( raw_policy == "LogLinLog" || raw_policy == "loglinlog" || raw_policy == "LOGLINLOG" ||
//            raw_policy == "Log-Lin-Log" || raw_policy == "log-lin-log" || raw_policy == "LOG-LIN-LOG" )
//     return LOGLINLOG_INTERPOLATION;
//   else if( raw_policy == "LogLogLin" || raw_policy == "logloglin" || raw_policy == "LOGLOGLIN" ||
//            raw_policy == "Log-Log-Lin" || raw_policy == "log-log-lin" || raw_policy == "LOG-LOG-LIN" )
//     return LOGLOGLIN_INTERPOLATION;
//   else if( raw_policy == "LogLogLog" || raw_policy == "logloglog" || raw_policy == "LOGLOGLOG" ||
//            raw_policy == "Log-Log-Log" || raw_policy == "log-log-log" || raw_policy == "LOG-LOG-LOG" )
//     return LOGLOGLOG_INTERPOLATION;
//   else
//   {
//     THROW_EXCEPTION( std::runtime_error,
//                      "Error: the 2D interpolation type "
//                      << raw_policy <<
//                      " is not currently supported!" );
//   }
// }

} // end MonteCarlo namespace

namespace Utility{

// Convert a MonteCarlo::TwoDInterpolationType to a string
std::string ToStringTraits<MonteCarlo::TwoDInterpolationType>::toString( const MonteCarlo::TwoDInterpolationType type )
{
  switch( type )
  {
  case MonteCarlo::LINLINLIN_INTERPOLATION:
    return "Lin-Lin-Lin";
  case MonteCarlo::LINLINLOG_INTERPOLATION:
    return "Lin-Lin-Log";
  case MonteCarlo::LINLOGLIN_INTERPOLATION:
    return "Lin-Log-Lin";
  case MonteCarlo::LOGLINLIN_INTERPOLATION:
    return "Log-Lin-Lin";
  case MonteCarlo::LOGLOGLIN_INTERPOLATION:
    return "Log-Log-Lin";
  case MonteCarlo::LOGLINLOG_INTERPOLATION:
    return "Log-Lin-Log";
  case MonteCarlo::LINLOGLOG_INTERPOLATION:
    return "Lin-Log-Log";
  case MonteCarlo::LOGLOGLOG_INTERPOLATION:
    return "Log-Log-Log";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "TwoDInterpolationType " << (unsigned)type <<
                     " cannot be converted to a string!" );
  }
}

// Place the MonteCarlo::TwoDInterpolationType in a stream
void ToStringTraits<MonteCarlo::TwoDInterpolationType>::toStream( std::ostream& os, const MonteCarlo::TwoDInterpolationType type )
{
  os << ToStringTraits<MonteCarlo::TwoDInterpolationType>::toString( type );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDInterpolationType.cpp
//---------------------------------------------------------------------------//
