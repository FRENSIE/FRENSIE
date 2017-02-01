//---------------------------------------------------------------------------//
//!
//! \file   Utility_WarningType.hpp
//! \author Alex Robinson
//! \brief  Warning type enumeration and helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_WARNING_TYPE_HPP
#define UTILITY_WARNING_TYPE_HPP

// Std Lib Includes
#include <iostream>
#include <string>

// FRENSIE Includes
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

//! The warning type enum
enum UserWarningType
{
  CRITICAL_WARNING = 0,  // As close to an error as allowed
  HIGH_PRIORITY_WARNING,
  MEDIUM_PRIORITY_WARNING,
  LOW_PRIORITY_WARNING,
  PEDANTIC_WARNING
};

//! Convert the warning type enum to a string
inline std::string convertWarningTypeEnumToString(
                                               const WarningType warning_type )
{
  switch( warning_type )
  {
  case CRITICAL_WARNING:
    return "Critical Warning";
  case HIGH_PRIORITY_WARNING:
    return "High Priority Warning";
  case MEDIUM_PRIORITY_WARNING:
    return "Medium Priority Warning";
  case LOW_PRIORITY_WARNING:
    return "Medium Priority Warning";
  case PEDANTIC_WARNING:
    return "Pedantic Warning";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: warning type " << (unsigned)warning_type <<
                     " is unknown!" );
  }
}

//! Stream operator for printing warning type enums
inline std::ostream& operator<<( std::ostream& os,
                                 const WarningType& warning_type )
{
  os << convertWarningTypeEnumToString( warning_type );
  return os;
}
  
} // end Utility namespace

#endif // end UTILITY_WARNING_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_WarningType.hpp
//---------------------------------------------------------------------------//
