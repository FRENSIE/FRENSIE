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

//! Place a Utility::LogRecordType object in a stream
std::ostream& operator<<( std::ostream& os, const LogRecordType record_type );

//! Extract a Utility::LogRecordType value from a stream
std::istream& operator>>( std::istream& is, LogRecordType& record_type );
  
} // end Utility namespace

#endif // end UTILITY_LOG_RECORD_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_LogRecordType.hpp
//---------------------------------------------------------------------------//
