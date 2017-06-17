//---------------------------------------------------------------------------//
//!
//! \file   tstToStringTraits.cpp
//! \author Alex Robinson
//! \brief  ToStringTraits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
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
  std::string test_string( " " );

  TEST_EQUALITY_CONST( Utility::toString( test_string ), test_string );

  test_string = "testing";

  TEST_EQUALITY_CONST( Utility::toString( test_string ), test_string );

  TEST_EQUALITY_CONST( Utility::toString( "test c-string" ), "test c-string" );
}

//---------------------------------------------------------------------------//
// Check that a bool can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, bool_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( true ), "true" );
  TEST_EQUALITY_CONST( Utility::toString( false ), "false" );
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
// Check that a double can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, double_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( -1.0 ), "-1.000000000000000000e+00" );
  TEST_EQUALITY_CONST( Utility::toString( 0.0 ), "0.000000000000000000e+00" );
  TEST_EQUALITY_CONST( Utility::toString( 1.0 ), "1.000000000000000000e+00" );
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
// Check that tuple types can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, tuple_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( 0 ) ), "{0}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( 0.0f ) ),
                       "{0.000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( 0.0 ) ),
                       "{0.000000000000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( "test" ) ),
                       "{test}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( true ) ),
                       "{true}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( false ) ),
                       "{false}" );
  
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( -1, 1.0 ) ),
                       "{-1, 1.000000000000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( 1.0f, -1000 ) ),
                       "{1.000000000e+00, -1000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( 10l, true ) ),
                       "{10, true}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( true, false ) ),
                       "{true, false}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( std::string( "test" ), false ) ),
                       "{test, false}" );

  {
    std::string test_string( "test string" );
    double test_double = 1.0;

    TEST_EQUALITY_CONST( Utility::toString( std::tie( test_string, test_double ) ),
                         "{test string, 1.000000000000000000e+00}" );
                                            
  }

  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( 100u, -1, false ) ),
                       "{100, -1, false}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( 1.0, true, "test" ) ),
                       "{1.000000000000000000e+00, true, test}" );

  {
    const bool test_bool = true;
    const unsigned long long test_ull = 256ull;
    const float test_float = -1.0f;

    TEST_EQUALITY_CONST( Utility::toString( std::tie( test_bool, test_ull, test_float ) ),
                         "{true, 256, -1.000000000e+00}" );
  }

  TEST_EQUALITY_CONST( Utility::toString( std::make_tuple( true, -100ll, std::string( "test" ), std::make_tuple( -1.0f, 1.0f ) ) ),
                       "{true, -100, test, {-1.000000000e+00, 1.000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that pair types can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, pair_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( std::make_pair( -1, 1.0 ) ),
                       "{-1, 1.000000000000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_pair( -1.0f, 1l ) ),
                       "{-1.000000000e+00, 1}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_pair( "test", true ) ),
                       "{test, true}" );
  TEST_EQUALITY_CONST( Utility::toString( std::make_pair( false, std::string( "test" ) ) ),
                       "{false, test}" );
}

//---------------------------------------------------------------------------//
// end tstToStringTraits.cpp
//---------------------------------------------------------------------------//
