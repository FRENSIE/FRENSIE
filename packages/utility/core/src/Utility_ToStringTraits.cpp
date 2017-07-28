//---------------------------------------------------------------------------//
//!
//! \file   Utility_ToStringTraits.cpp
//! \author Alex Robinson
//! \brief  ToStringTraits definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_LoggingStaticConstants.hpp"

namespace Utility{

// Container element deliminators
const char* container_element_delims = ",}";

// Container start character
const char container_start_char = '{';

// Next container element character
const char next_container_element_char = ',';

// Container end character
const char container_end_char = '}';

// Return the string
std::string ToStringTraits<LogRecordType>::toString( const LogRecordType obj )
{
  switch( obj )
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
      // We will not use the THROW_EXCEPTION macro since it depends on the
      // LogRecordType
      std::ostringstream oss;
      oss << "Error: unkown log record type (" << (int)obj << ")!";

      throw std::logic_error( oss.str() );

      return FRENSIE_LOG_ERROR_MSG_BASIC;
    }
  }
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_ToStringTraits.cpp
//---------------------------------------------------------------------------//
