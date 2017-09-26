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
#include "Utility_FromStringTraits.hpp"

namespace Utility{

// Place a Utility::LogRecordType object in a stream
std::ostream& operator<<( std::ostream& os, const LogRecordType record_type )
{
  switch( record_type )
  {
    case ERROR_RECORD:
    {
      os << FRENSIE_LOG_ERROR_MSG_BASIC;
      break;
    }
    case WARNING_RECORD:
    {
      os << FRENSIE_LOG_WARNING_MSG_BASIC;
      break;
    }
    case NOTIFICATION_RECORD:
    {
      os << FRENSIE_LOG_NOTIFICATION_MSG_BASIC;
      break;
    }
    case DETAILS_RECORD:
    {
      os << FRENSIE_LOG_DETAILS_MSG_BASIC;
      break;
    }
    case PEDANTIC_DETAILS_RECORD:
    {
      os << FRENSIE_LOG_PEDANTIC_DETAILS_MSG_BASIC;
      break;
    }
    default:
    {
      // We will not use the THROW_EXCEPTION macro since it depends on the
      // LogRecordType
      std::ostringstream oss;
      oss << "Error: unkown log record type (" << (int)record_type << ")!";

      throw std::logic_error( oss.str() );
    }
  }

  return os;
}

// Extract a Utility::LogRecordType value from a stream
std::istream& operator>>( std::istream& is, LogRecordType& record_type )
{
  Utility::fromStream( is, record_type );

  return is;
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_LogRecordType.cpp
//---------------------------------------------------------------------------//
