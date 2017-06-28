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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

typedef long long longlong;

//---------------------------------------------------------------------------//
// Instantiation Macros
//---------------------------------------------------------------------------//
#define UNIT_TEST_TEMPLATE_1_INSTANT( type, name )      \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, short ); \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, int );   \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, long );  \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, longlong )

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a string can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, string_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( std::string( " " ) ), " " );
  TEST_EQUALITY_CONST( Utility::toString( std::string( "testing" ) ), "testing" );
  TEST_EQUALITY_CONST( Utility::toString( "test c-string" ), "test c-string" );
}

//---------------------------------------------------------------------------//
// Check that a string can be placed in a stream
TEUCHOS_UNIT_TEST( ToStringTraits, string_toStream )
{
  std::ostringstream oss;
  Utility::toStream( oss, std::string( " " ) );
  
  TEST_EQUALITY_CONST( oss.str(), " " );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::string( "testing" ) );

  TEST_EQUALITY_CONST( oss.str(), "testing" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, "test c-string" );

  TEST_EQUALITY_CONST( oss.str(), "test c-string" );
}

//---------------------------------------------------------------------------//
// Check that a bool can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, bool_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( true ), "true" );
  TEST_EQUALITY_CONST( Utility::toString( false ), "false" );
}

//---------------------------------------------------------------------------//
// Check that a bool can be placed in a stream
TEUCHOS_UNIT_TEST( ToStringTraits, bool_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, true );
  
  TEST_EQUALITY_CONST( oss.str(), "true" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, false );

  TEST_EQUALITY_CONST( oss.str(), "false" );
}

//---------------------------------------------------------------------------//
// Check that a float can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, float_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( -1.0f ), "-1.000000000e+00" );
  TEST_EQUALITY_CONST( Utility::toString( 0.0f ), "0.000000000e+00" );
  TEST_EQUALITY_CONST( Utility::toString( 1.0f ), "1.000000000e+00" );
}

//---------------------------------------------------------------------------//
// Check that a float can be placed in a stream
TEUCHOS_UNIT_TEST( ToStringTraits, float_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, -1.0f );

  TEST_EQUALITY_CONST( oss.str(), "-1.000000000e+00" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, 0.0f );

  TEST_EQUALITY_CONST( oss.str(), "0.000000000e+00" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, 1.0f );

  TEST_EQUALITY_CONST( oss.str(), "1.000000000e+00" );
}

//---------------------------------------------------------------------------//
// Check that a double can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, double_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( -1.0 ), "-1.000000000000000000e+00" );
  TEST_EQUALITY_CONST( Utility::toString( 0.0 ), "0.000000000000000000e+00" );
  TEST_EQUALITY_CONST( Utility::toString( 1.0 ), "1.000000000000000000e+00" );
}

//---------------------------------------------------------------------------//
// Check that a double can be placed in a stream
TEUCHOS_UNIT_TEST( ToStringTraits, double_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, -1.0 );

  TEST_EQUALITY_CONST( oss.str(), "-1.000000000000000000e+00" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, 0.0 );

  TEST_EQUALITY_CONST( oss.str(), "0.000000000000000000e+00" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, 1.0 );

  TEST_EQUALITY_CONST( oss.str(), "1.000000000000000000e+00" );
}

//---------------------------------------------------------------------------//
// Check that signed integer types can be converted to a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ToStringTraits, toString, T )
{
  TEST_EQUALITY_CONST( Utility::toString( static_cast<T>( -10 ) ), "-10" );
  TEST_EQUALITY_CONST( Utility::toString( static_cast<T>( 0 ) ), "0" );
  TEST_EQUALITY_CONST( Utility::toString( static_cast<T>( 10 ) ), "10" );
}

UNIT_TEST_TEMPLATE_1_INSTANT( ToStringTraits, toString );

//---------------------------------------------------------------------------//
// Check that signed integer types can be placed in a stream
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ToStringTraits, toStream, T )
{
  std::ostringstream oss;

  Utility::toStream( oss, static_cast<T>( -10 ) );

  TEST_EQUALITY_CONST( oss.str(), "-10" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, static_cast<T>( 0 ) );
  
  TEST_EQUALITY_CONST( oss.str(), "0" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, static_cast<T>( 10 ) );
  
  TEST_EQUALITY_CONST( oss.str(), "10" );
}

UNIT_TEST_TEMPLATE_1_INSTANT( ToStringTraits, toStream );

//---------------------------------------------------------------------------//
// Check that unsigned integer types can be converted to a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ToStringTraits, unsigned_toString, T )
{
  typedef typename std::make_unsigned<T>::type UnsignedT;
  
  TEST_EQUALITY_CONST( Utility::toString( static_cast<UnsignedT>( 0 ) ), "0" );
  TEST_EQUALITY_CONST( Utility::toString( static_cast<UnsignedT>( 10 ) ), "10" );
  TEST_EQUALITY_CONST( Utility::toString( static_cast<UnsignedT>( 255 ) ), "255" );
}

UNIT_TEST_TEMPLATE_1_INSTANT( ToStringTraits, unsigned_toString );

//---------------------------------------------------------------------------//
// Check that unsigned integer types can be placed in a stream
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ToStringTraits, unsigned_toStream, T )
{
  typedef typename std::make_unsigned<T>::type UnsignedT;
  
  std::ostringstream oss;

  Utility::toStream( oss, static_cast<UnsignedT>( 0 ) );

  TEST_EQUALITY_CONST( oss.str(), "0" );
  
  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, static_cast<UnsignedT>( 10 ) );
  
  TEST_EQUALITY_CONST( oss.str(), "10" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, static_cast<UnsignedT>( 255 ) );
  
  TEST_EQUALITY_CONST( oss.str(), "255" );
}

UNIT_TEST_TEMPLATE_1_INSTANT( ToStringTraits, unsigned_toStream );

//---------------------------------------------------------------------------//
// end tstToStringTraits.cpp
//---------------------------------------------------------------------------//
