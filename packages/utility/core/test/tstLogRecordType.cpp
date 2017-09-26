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

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// FRENSIE Includes
#include "Utility_LogRecordType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a log record type name can be converted to a log record type
BOOST_AUTO_TEST_CASE( istream_operator )
{
  Utility::LogRecordType record_type;
  std::istringstream iss( "Error" );
  
  iss >> record_type;

  BOOST_CHECK_EQUAL( record_type, Utility::ERROR_RECORD );

  iss.str( " Error " );
  iss.clear();

  iss >> record_type;

  BOOST_CHECK_EQUAL( record_type, Utility::ERROR_RECORD );

  iss.str( "error" );
  iss.clear();

  BOOST_CHECK_THROW( iss >> record_type, std::runtime_error );

  iss.str( "Warning" );
  iss.clear();

  iss >> record_type;

  BOOST_CHECK_EQUAL( record_type, Utility::WARNING_RECORD );

  iss.str( " Warning " );
  iss.clear();

  iss >> record_type;

  BOOST_CHECK_EQUAL( record_type, Utility::WARNING_RECORD );

  iss.str( "warning" );
  iss.clear();

  BOOST_CHECK_THROW( iss >> record_type, std::runtime_error );

  iss.str( "Notification" );
  iss.clear();

  iss >> record_type;

  BOOST_CHECK_EQUAL( record_type, Utility::NOTIFICATION_RECORD );

  iss.str( " Notification " );
  iss.clear();

  iss >> record_type;

  BOOST_CHECK_EQUAL( record_type, Utility::NOTIFICATION_RECORD );

  iss.str( "notification" );
  iss.clear();

  BOOST_CHECK_THROW( iss >> record_type, std::runtime_error );

  iss.str( "Details" );
  iss.clear();

  iss >> record_type;

  BOOST_CHECK_EQUAL( record_type, Utility::DETAILS_RECORD );

  iss.str( " Details " );
  iss.clear();

  iss >> record_type;

  BOOST_CHECK_EQUAL( record_type, Utility::DETAILS_RECORD );

  iss.str( "details" );
  iss.clear();

  BOOST_CHECK_THROW( iss >> record_type, std::runtime_error );

  iss.str( "Pedantic Details" );
  iss.clear();

  iss >> record_type;

  BOOST_CHECK_EQUAL( record_type, Utility::PEDANTIC_DETAILS_RECORD );

  iss.str( " Pedantic  Details " );
  iss.clear();

  iss >> record_type;

  BOOST_CHECK_EQUAL( record_type, Utility::PEDANTIC_DETAILS_RECORD );

  iss.str( "pedantic Details" );
  iss.clear();

  BOOST_CHECK_THROW( iss >> record_type, std::runtime_error );

  iss.str( "Pedantic details" );
  iss.clear();

  BOOST_CHECK_THROW( iss >> record_type, std::runtime_error );

  iss.str( "pedantic details" );
  iss.clear();

  BOOST_CHECK_THROW( iss >> record_type, std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check that a log record type can be placed in a stream and formatted
BOOST_AUTO_TEST_CASE( ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::ERROR_RECORD;

  BOOST_CHECK_EQUAL( oss.str(), "Error" );

  oss.str( "" );
  oss.clear();

  oss << Utility::WARNING_RECORD;

  BOOST_CHECK_EQUAL( oss.str(), "Warning" );

  oss.str( "" );
  oss.clear();

  oss << Utility::NOTIFICATION_RECORD;

  BOOST_CHECK_EQUAL( oss.str(), "Notification" );

  oss.str( "" );
  oss.clear();

  oss << Utility::DETAILS_RECORD;

  BOOST_CHECK_EQUAL( oss.str(), "Details" );

  oss.str( "" );
  oss.clear();

  oss << Utility::PEDANTIC_DETAILS_RECORD;

  BOOST_CHECK_EQUAL( oss.str(), "Pedantic Details" );
}

//---------------------------------------------------------------------------//
// end tstLogRecordType.cpp
//---------------------------------------------------------------------------//
