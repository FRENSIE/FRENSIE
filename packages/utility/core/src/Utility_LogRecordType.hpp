//---------------------------------------------------------------------------//
//!
//! \file   Utility_LogRecordType.hpp
//! \author Alex Robinson
//! \brief  Log record type enum and helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_LOG_RECORD_TYPE_HPP
#define UTILITY_LOG_RECORD_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

namespace Utility{

//! The log record type enum
enum LogRecordType{
  PEDANTIC_DETAILS_RECORD,
  DETAILS_RECORD,
  NOTIFICATION_RECORD,
  WARNING_RECORD,
  ERROR_RECORD
};

//! Test if the log record type name is valid
bool isValidLogRecordTypeName( const std::string& log_record_type_name );

//! Convert the log record type name to a log record type enum
LogRecordType convertLogRecordTypeNameToEnum(
                                     const std::string& log_record_type_name );

//! Convert the log record type enum to a string
std::string convertLogRecordTypeEnumToString( const LogRecordType type );

//! Stream operator for printing log record type enums
template<typename CharT, typename TraitsT>
inline std::basic_ostream<CharT,TraitsT>& operator<<(
                    std::basic_ostream<CharT,TraitsT>& os, LogRecordType type )
{
  os << convertLogRecordTypeEnumToString( type );
  return os;
}
  
} // end Utility namespace

#endif // end UTILITY_LOG_RECORD_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_LogRecordType.hpp
//---------------------------------------------------------------------------//
