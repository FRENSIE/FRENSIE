//---------------------------------------------------------------------------//
//!
//! \file   tstToStringTraits.cpp
//! \author Alex Robinson
//! \brief  ToStringTraits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <type_traits>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"

//---------------------------------------------------------------------------//
// Template Test Types
//---------------------------------------------------------------------------//
typedef boost::mpl::list<int8_t, short, int16_t, int, long, int32_t, long long, int64_t> TestTypes;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a string can be converted to a string
BOOST_AUTO_TEST_CASE( string_toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( std::string( " " ) ), " " );
  BOOST_CHECK_EQUAL( Utility::toString( std::string( "testing" ) ), "testing" );
  BOOST_CHECK_EQUAL( Utility::toString( "test c-string" ), "test c-string" );
}

//---------------------------------------------------------------------------//
// Check that a string can be placed in a stream
BOOST_AUTO_TEST_CASE( string_toStream )
{
  std::ostringstream oss;
  Utility::toStream( oss, std::string( " " ) );
  
  BOOST_CHECK_EQUAL( oss.str(), " " );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::string( "testing" ) );

  BOOST_CHECK_EQUAL( oss.str(), "testing" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, "test c-string" );

  BOOST_CHECK_EQUAL( oss.str(), "test c-string" );
}

//---------------------------------------------------------------------------//
// Check that a bool can be converted to a string
BOOST_AUTO_TEST_CASE( bool_toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( true ), "true" );
  BOOST_CHECK_EQUAL( Utility::toString( false ), "false" );
}

//---------------------------------------------------------------------------//
// Check that a bool can be placed in a stream
BOOST_AUTO_TEST_CASE( bool_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, true );
  
  BOOST_CHECK_EQUAL( oss.str(), "true" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, false );

  BOOST_CHECK_EQUAL( oss.str(), "false" );
}

//---------------------------------------------------------------------------//
// Check that a float can be converted to a string
BOOST_AUTO_TEST_CASE( float_toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( -1.0f ), "-1.000000000e+00" );
  BOOST_CHECK_EQUAL( Utility::toString( 0.0f ), "0.000000000e+00" );
  BOOST_CHECK_EQUAL( Utility::toString( 1.0f ), "1.000000000e+00" );
}

//---------------------------------------------------------------------------//
// Check that a float can be placed in a stream
BOOST_AUTO_TEST_CASE( float_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, -1.0f );

  BOOST_CHECK_EQUAL( oss.str(), "-1.000000000e+00" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, 0.0f );

  BOOST_CHECK_EQUAL( oss.str(), "0.000000000e+00" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, 1.0f );

  BOOST_CHECK_EQUAL( oss.str(), "1.000000000e+00" );
}

//---------------------------------------------------------------------------//
// Check that a double can be converted to a string
BOOST_AUTO_TEST_CASE( double_toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( -1.0 ), "-1.000000000000000000e+00" );
  BOOST_CHECK_EQUAL( Utility::toString( 0.0 ), "0.000000000000000000e+00" );
  BOOST_CHECK_EQUAL( Utility::toString( 1.0 ), "1.000000000000000000e+00" );
}

//---------------------------------------------------------------------------//
// Check that a double can be placed in a stream
BOOST_AUTO_TEST_CASE( double_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, -1.0 );

  BOOST_CHECK_EQUAL( oss.str(), "-1.000000000000000000e+00" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, 0.0 );

  BOOST_CHECK_EQUAL( oss.str(), "0.000000000000000000e+00" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, 1.0 );

  BOOST_CHECK_EQUAL( oss.str(), "1.000000000000000000e+00" );
}

//---------------------------------------------------------------------------//
// Check that signed integer types can be converted to a string
BOOST_AUTO_TEST_CASE_TEMPLATE( toString, T, TestTypes )
{
  if( sizeof(T) > 1 )
  {
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<T>( -10 ) ), "-10" );
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<T>( 0 ) ), "0" );
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<T>( 10 ) ), "10" );
  }
  else
  {
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<T>( -10 ) ),
                       std::string( 1, -10 ) );
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<T>( 0 ) ),
                       std::string( 1, 0 ) );
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<T>( 10 ) ),
                       std::string( 1, 10 ) );
  }
}

//---------------------------------------------------------------------------//
// Check that signed integer types can be placed in a stream
BOOST_AUTO_TEST_CASE_TEMPLATE( toStream, T, TestTypes )
{
  std::ostringstream oss;

  Utility::toStream( oss, static_cast<T>( -10 ) );

  if( sizeof(T) > 1 )
    BOOST_CHECK_EQUAL( oss.str(), "-10" );
  else
    BOOST_CHECK_EQUAL( oss.str(), std::string( 1, -10 ) );      

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, static_cast<T>( 0 ) );

  if( sizeof(T) > 1 )
    BOOST_CHECK_EQUAL( oss.str(), "0" );
  else
    BOOST_CHECK_EQUAL( oss.str(), std::string( 1, 0 ) );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, static_cast<T>( 10 ) );

  if( sizeof(T) > 1 )
    BOOST_CHECK_EQUAL( oss.str(), "10" );
  else
    BOOST_CHECK_EQUAL( oss.str(), std::string( 1, 10 ) );
}

//---------------------------------------------------------------------------//
// Check that unsigned integer types can be converted to a string
BOOST_AUTO_TEST_CASE_TEMPLATE( unsigned_toString, T, TestTypes )
{
  typedef typename std::make_unsigned<T>::type UnsignedT;

  if( sizeof(T) > 1 )
  {
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<UnsignedT>( 0 ) ), "0" );
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<UnsignedT>( 10 ) ), "10" );
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<UnsignedT>( 255 ) ), "255" );
  }
  else
  {
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<UnsignedT>( 0 ) ),
                       std::string( 1, (char)0 ) );
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<UnsignedT>( 10 ) ),
                       std::string( 1, (char)10 ) );
    BOOST_CHECK_EQUAL( Utility::toString( static_cast<UnsignedT>( 255 ) ),
                       std::string( 1, (char)255 ) );
  }
}

//---------------------------------------------------------------------------//
// Check that unsigned integer types can be placed in a stream
BOOST_AUTO_TEST_CASE_TEMPLATE( unsigned_toStream, T, TestTypes )
{
  typedef typename std::make_unsigned<T>::type UnsignedT;
  
  std::ostringstream oss;

  Utility::toStream( oss, static_cast<UnsignedT>( 0 ) );

  if( sizeof(T) > 1 )
    BOOST_CHECK_EQUAL( oss.str(), "0" );
  else
    BOOST_CHECK_EQUAL( oss.str(), std::string( 1, (char)0 ) );
  
  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, static_cast<UnsignedT>( 10 ) );

  if( sizeof(T) > 1 )
    BOOST_CHECK_EQUAL( oss.str(), "10" );
  else
    BOOST_CHECK_EQUAL( oss.str(), std::string( 1, (char)10 ) );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, static_cast<UnsignedT>( 255 ) );

  if( sizeof(T) > 1 )
    BOOST_CHECK_EQUAL( oss.str(), "255" );
  else
    BOOST_CHECK_EQUAL( oss.str(), std::string( 1, (char)255 ) );
}

//---------------------------------------------------------------------------//
// end tstToStringTraits.cpp
//---------------------------------------------------------------------------//
