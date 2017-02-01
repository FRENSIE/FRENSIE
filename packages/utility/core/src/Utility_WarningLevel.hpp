//---------------------------------------------------------------------------//
//!
//! \file   Utility_WarningLevel.hpp
//! \author Alex Robinson
//! \brief  Warning level enumeration and helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_WARNING_LEVEL_HPP
#define UTILITY_WARNING_LEVEL_HPP

// Std Lib Includes
#include <iostream>
#include <string>

// FRENSIE Includes
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

//! The warning level enum
enum WarningLevel
{
  NO_WARNINGS = 0,
  CRITICAL_WARNINGS_ONLY,
  HIGH_PRIORITY_OR_HIGHER_WARNINGS,
  HIGH_PRIORITY_WARNINGS_ONLY,
  MEDIUM_PRIORITY_OR_HIGHER_WARNINGS,
  MEDIUM_PRIORITY_WARNINGS_ONLY,
  LOW_PRIORITY_OR_HIGHER_WARNINGS,
  LOW_PRIORITY_WARNINGS_ONLY,
  PEDANTIC_OR_HIGHER_WARNINGS,
  PEDANTIC_WARNINGS_ONLY,
  ALL_WARNINGS,
};

//! Convert the warning level name to a warning level
inline WarningLevel convertWarningLevelNameToWarningLevelEnum(
                                                const std::string& level_name )
{
  if( level_name == "No Warnings" )
    return NO_WARNINGS;
  else if( level_name == "Critical" )
    return CRITICAL_WARNINGS_ONLY;
  else if( level_name == "High Priority" )
    return HIGH_PRIORITY_WARNINGS_ONLY;
  else if( level_name == "High Priority+" )
    return HIGH_PRIORITY_OR_HIGHER_WARNINGS;
  else if( level_name == "Medium Priority" )
    return MEDIUM_PRIORITY_WARNINGS_ONLY;
  else if( level_name == "Medium Priority+" )
    return MEDIUM_PRIORITY_OR_HIGHER_WARNINGS;
  else if( level_name == "Low Priority" )
    return LOW_PRIORITY_WARNINGS_ONLY;
  else if( level_name == "Low Priority+" )
    return LOW_PRIORITY_OR_HIGHER_WARNINGS;
  else if( level_name == "Pedantic" )
    return PEDANTIC_WARNINGS_ONLY;
  else if( level_name == "Pedantic+" )
    return PEDANTIC_OR_HIGHER_WARNINGS;
  else if( level_name == "All Warnings" )
    return ALL_WARNINGS;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: warning level " << level_name << " is unknown!" );
  }
}
  
} // end Utility namespace

#endif // end UTILITY_WARNING_LEVEL_HPP

//---------------------------------------------------------------------------//
// end Utility_WarningLevel.hpp
//---------------------------------------------------------------------------//
