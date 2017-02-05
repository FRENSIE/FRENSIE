//---------------------------------------------------------------------------//
//!
//! \file   Utility_LogRecordType.cpp
//! \author Alex Robinson
//! \brief  Log record type helper function definitions
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "Utility_LogRecordType.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

namespace {

inline const char* const* getLogRecordTypeNames()
{
  static const char* const log_record_type_names[] =
  {
    "Pedantic Details",
    "Details",
    "Notification",
    "Warning",
    "Error"
  };

  return log_record_type_names;
}

inline const LogRecordType* const getLogRecordTypes()
{
  static const LogRecordType log_record_types[] =
  {
    PEDANTIC_DETAILS_RECORD,
    DETAILS_RECORD,
    NOTIFICATION_RECORD,
    WARNING_RECORD,
    ERROR_RECORD
  };

  return log_record_types;
}

} // end Anonymous namespace

// Test if the log record type name is valid
bool isValidLogRecordName( const std::string& log_record_type_name )
{
  const char* const* valid_names = getLogRecordTypeNames();
  
  for( size_t i = 0; i < sizeof(valid_names)/sizeof(*valid_names); ++i )
  {
    if( log_record_type_name == valid_names[i] )
      return true;
  }

  return false;
}

// Convert the log record type name to a log record type enum
LogRecordType convertLogRecordTypeNameToEnum(
                                      const std::string& log_record_type_name )
{
  const char* const* valid_names = getLogRecordTypeNames();
  const LogRecordType* const types = getLogRecordTypes();
  
  for( size_t i = 0; i < sizeof(valid_names)/sizeof(*valid_names); ++i )
  {
    if( log_record_type_name == valid_names[i] )
      return types[i];
  }

  THROW_EXCEPTION( std::runtime_error,
                   "Error: log record type " << log_record_type_name <<
                   " is unknown!" );
}

// Convert the log record type enum to a string
std::string convertLogRecordTypeEnumToString( const LogRecordType type )
{
  return getLogRecordTypeNames()[type];
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_LogRecordType.cpp
//---------------------------------------------------------------------------//
