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
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"

namespace Utility{

// Place a Utility::LogRecordType object in a stream
std::ostream& operator<<( std::ostream& os, const LogRecordType record_type )
{
  Utility::toStream( os, record_type );
}

// Extract a Utility::LogRecordType value from a stream
std::istream& operator>>( std::istream& is, LogRecordType& record_type )
{
  Utility::fromStream( is, record_type );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_LogRecordType.cpp
//---------------------------------------------------------------------------//
