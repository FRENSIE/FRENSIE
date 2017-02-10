//---------------------------------------------------------------------------//
//!
//! \file   tstLogRecordType.cpp
//! \author Alex Robinson
//! \brief  Log record type enum unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_LogRecordType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if the log record type name is valid
TEUCHOS_UNIT_TEST( LogRecordType, isValidLogRecordTypeName )
{
  std::string log_record_name = "Error";

  TEST_ASSERT( Utility::isValidLogRecordTypeName( log_record_name ) );

  log_record_name = "Warning";

  TEST_ASSERT( Utility::isValidLogRecordTypeName( log_record_name ) );

  log_record_name = "Notification";

  TEST_ASSERT( Utility::isValidLogRecordTypeName( log_record_name ) );

  log_record_name = "Details";

  TEST_ASSERT( Utility::isValidLogRecordTypeName( log_record_name ) );

  log_record_name = "Pedantic Details";

  TEST_ASSERT( Utility::isValidLogRecordTypeName( log_record_name ) );

  log_record_name = "Dummy";

  TEST_ASSERT( !Utility::isValidLogRecordTypeName( log_record_name ) );
}

//---------------------------------------------------------------------------//
// Check that a log record type name can be converted to a log record type
TEUCHOS_UNIT_TEST( LogRecordType, convertLogRecordTypeNameToEnum )
{
  Utility::LogRecordType record_type =
    Utility::convertLogRecordTypeNameToEnum( "Error" );

  TEST_EQUALITY_CONST( record_type, Utility::ERROR_RECORD );

  record_type = Utility::convertLogRecordTypeNameToEnum( "Warning" );

  TEST_EQUALITY_CONST( record_type, Utility::WARNING_RECORD );

  record_type = Utility::convertLogRecordTypeNameToEnum( "Notification" );

  TEST_EQUALITY_CONST( record_type, Utility::NOTIFICATION_RECORD );

  record_type = Utility::convertLogRecordTypeNameToEnum( "Details" );

  TEST_EQUALITY_CONST( record_type, Utility::DETAILS_RECORD );

  record_type = Utility::convertLogRecordTypeNameToEnum( "Pedantic Details" );

  TEST_EQUALITY_CONST( record_type, Utility::PEDANTIC_DETAILS_RECORD );
}

//---------------------------------------------------------------------------//
// Check that a log record type enum can be converted to a name
TEUCHOS_UNIT_TEST( LogRecordType, convertLogRecordTypeEnumToString )
{
  std::string record_type_name =
    Utility::convertLogRecordTypeEnumToString( Utility::ERROR_RECORD );

  TEST_EQUALITY_CONST( record_type_name, "Error" );

  record_type_name =
    Utility::convertLogRecordTypeEnumToString( Utility::WARNING_RECORD );

  TEST_EQUALITY_CONST( record_type_name, "Warning" );

  record_type_name =
    Utility::convertLogRecordTypeEnumToString( Utility::NOTIFICATION_RECORD );

  TEST_EQUALITY_CONST( record_type_name, "Notification" );

  record_type_name =
    Utility::convertLogRecordTypeEnumToString( Utility::DETAILS_RECORD );

  TEST_EQUALITY_CONST( record_type_name, "Details" );

  record_type_name =
    Utility::convertLogRecordTypeEnumToString( Utility::PEDANTIC_DETAILS_RECORD );

  TEST_EQUALITY_CONST( record_type_name, "Pedantic Details" );
}

//---------------------------------------------------------------------------//
// Check that a log record type can be placed in a stream and formatted
TEUCHOS_UNIT_TEST( LogRecordType, stream_operator )
{
  std::ostringstream oss;

  oss << Utility::ERROR_RECORD;

  TEST_EQUALITY_CONST( oss.str(), "Error" );

  oss.str( "" );
  oss.clear();

  oss << Utility::WARNING_RECORD;

  TEST_EQUALITY_CONST( oss.str(), "Warning" );

  oss.str( "" );
  oss.clear();

  oss << Utility::NOTIFICATION_RECORD;

  TEST_EQUALITY_CONST( oss.str(), "Notification" );

  oss.str( "" );
  oss.clear();

  oss << Utility::DETAILS_RECORD;

  TEST_EQUALITY_CONST( oss.str(), "Details" );

  oss.str( "" );
  oss.clear();

  oss << Utility::PEDANTIC_DETAILS_RECORD;

  TEST_EQUALITY_CONST( oss.str(), "Pedantic Details" );
}

//---------------------------------------------------------------------------//
// end tstLogRecordType.cpp
//---------------------------------------------------------------------------//
