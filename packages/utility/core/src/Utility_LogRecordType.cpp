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
#include "Utility_LoggingStaticConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

// Test if the log record type name is valid
bool isValidLogRecordTypeName( const std::string& log_record_type_name )
{
  if( log_record_type_name == FRENSIE_LOG_ERROR_MSG_BASIC )
    return true;
  else if( log_record_type_name == FRENSIE_LOG_WARNING_MSG_BASIC )
    return true;
  else if( log_record_type_name == FRENSIE_LOG_NOTIFICATION_MSG_BASIC )
    return true;
  else if( log_record_type_name == FRENSIE_LOG_DETAILS_MSG_BASIC )
    return true;
  else if( log_record_type_name == FRENSIE_LOG_PEDANTIC_DETAILS_MSG_BASIC )
    return true;
  else
    return false;
}

// Convert the log record type name to a log record type enum
LogRecordType convertLogRecordTypeNameToEnum(
                                      const std::string& log_record_type_name )
{
  if( log_record_type_name == FRENSIE_LOG_ERROR_MSG_BASIC )
    return ERROR_RECORD;
  else if( log_record_type_name == FRENSIE_LOG_WARNING_MSG_BASIC )
    return WARNING_RECORD;
  else if( log_record_type_name == FRENSIE_LOG_NOTIFICATION_MSG_BASIC )
    return NOTIFICATION_RECORD;
  else if( log_record_type_name == FRENSIE_LOG_DETAILS_MSG_BASIC )
    return DETAILS_RECORD;
  else if( log_record_type_name == FRENSIE_LOG_PEDANTIC_DETAILS_MSG_BASIC )
    return PEDANTIC_DETAILS_RECORD;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "unknown log record type name ("
                     << log_record_type_name << ")!" );
  }
}

// Convert the log record type enum to a string
std::string convertLogRecordTypeEnumToString( const LogRecordType type )
{
  switch( type )
  {
    case ERROR_RECORD:
      return FRENSIE_LOG_ERROR_MSG_BASIC;
    case WARNING_RECORD:
      return FRENSIE_LOG_WARNING_MSG_BASIC;
    case NOTIFICATION_RECORD:
      return FRENSIE_LOG_NOTIFICATION_MSG_BASIC;
    case DETAILS_RECORD:
      return FRENSIE_LOG_DETAILS_MSG_BASIC;
    case PEDANTIC_DETAILS_RECORD:
      return FRENSIE_LOG_PEDANTIC_DETAILS_MSG_BASIC;
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "unkown log record type (" << (unsigned)type << ")!" );
    }
  }
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_LogRecordType.cpp
//---------------------------------------------------------------------------//
