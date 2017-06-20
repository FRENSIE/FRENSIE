//---------------------------------------------------------------------------//
//!
//! \file   tstFromStringTraits.cpp
//! \author Alex Robinson
//! \brief  FromStringTraits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <type_traits>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_FromStringTraits.hpp"
#include "Utility_StreamHelpers.hpp"
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
// Check that a string can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, string_fromString )
{
  TEST_EQUALITY_CONST( Utility::fromString<std::string>( " " ), " " );
  TEST_EQUALITY_CONST( Utility::fromString<std::string>( "testing" ), "testing" );
}

//---------------------------------------------------------------------------//
// Check that a string can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, string_fromStream )
{
  std::istringstream iss;
  iss.str( " " );

  std::string string;
  
  Utility::fromStream( iss, string );

  TEST_EQUALITY_CONST( string, " " );

  iss.str( "testing" );
  iss.clear();

  Utility::fromStream( iss, string );

  TEST_EQUALITY_CONST( string, "testing" );

  string.clear();

  iss.str( "testing-1,testing-2" );
  iss.clear();

  Utility::fromStream( iss, string, "," );

  TEST_EQUALITY_CONST( string, "testing-1" );

  string.clear();

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, string );

  TEST_EQUALITY_CONST( string, "testing-2" );
}

//---------------------------------------------------------------------------//
// Check that a boolean can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, bool_fromString )
{
  TEST_EQUALITY_CONST( Utility::fromString<bool>( "0" ), false );
  TEST_EQUALITY_CONST( Utility::fromString<bool>( "false" ), false );

  TEST_EQUALITY_CONST( Utility::fromString<bool>( "1" ), true );
  TEST_EQUALITY_CONST( Utility::fromString<bool>( "true" ), true );
}

//---------------------------------------------------------------------------//
// Check that a boolean can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, bool_fromStream )
{
  std::istringstream iss( "0" );

  bool boolean;

  Utility::fromStream( iss, boolean );

  TEST_EQUALITY_CONST( boolean, false );

  iss.str( "false" );
  iss.clear();

  Utility::fromStream( iss, boolean );

  TEST_EQUALITY_CONST( boolean, false );

  iss.str( "1" );
  iss.clear();

  Utility::fromStream( iss, boolean );

  TEST_EQUALITY_CONST( boolean, true );

  iss.str( "true" );
  iss.clear();

  Utility::fromStream( iss, boolean );

  TEST_EQUALITY_CONST( boolean, true );

  iss.str( "0, true" );
  iss.clear();

  Utility::fromStream( iss, boolean, "," );

  TEST_EQUALITY_CONST( boolean, false );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, boolean );

  TEST_EQUALITY_CONST( boolean, true );
}

//---------------------------------------------------------------------------//
// Check that a float can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, float_fromString )
{
  TEST_EQUALITY_CONST( Utility::fromString<float>( "1" ), 1.0f );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "-1.0" ), -1.0f );
  TEST_EQUALITY_CONST( Utility::fromString<float>( "0.000000000e+00" ), 0.0f );
}

//---------------------------------------------------------------------------//
// Check that a float can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, float_fromStream )
{
  std::istringstream iss( "1" );

  float test_float;

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, 1.0f );

  iss.str( "-1.0" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, -1.0f );

  iss.str( "0.000000000e+00" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, 0.0f );

  iss.str( "-1, 1.000000000000000000e+00" );
  iss.clear();

  Utility::fromStream( iss, test_float, "," );

  TEST_EQUALITY_CONST( test_float, -1.0f );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, 1.0f );
}

//---------------------------------------------------------------------------//
// Check that a double can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, double_fromString )
{
  TEST_EQUALITY_CONST( Utility::fromString<double>( "1" ), 1.0 );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "-1.0" ), -1.0 );
  TEST_EQUALITY_CONST( Utility::fromString<double>( "0.000000000000000000e+00" ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a float can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, double_fromStream )
{
  std::istringstream iss( "1" );

  float test_float;

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, 1.0 );

  iss.str( "-1.0" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, -1.0 );

  iss.str( "0.000000000000000000e+00" );
  iss.clear();

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, 0.0 );

  iss.str( "-1, 1.000000000e+00" );
  iss.clear();

  Utility::fromStream( iss, test_float, "," );

  TEST_EQUALITY_CONST( test_float, -1.0 );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_float );

  TEST_EQUALITY_CONST( test_float, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that signed integer types can be created from a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( FromStringTraits, fromString, T )
{
  TEST_EQUALITY_CONST( Utility::fromString<T>( "-10" ), -10 );
  TEST_EQUALITY_CONST( Utility::fromString<T>( "0" ), 0 );
  TEST_EQUALITY_CONST( Utility::fromString<T>( "0.0" ), 0 );
  TEST_EQUALITY_CONST( Utility::fromString<T>( "0.000000000e+00" ), 0 );
  TEST_EQUALITY_CONST( Utility::fromString<T>( "10" ), 10 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( FromStringTraits, fromString );

//---------------------------------------------------------------------------//
// Check that signed integer types can be extracted from a stream
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( FromStringTraits, fromStream, T )
{
  std::istringstream iss( "-10" );

  T test_int;

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, -10 );

  iss.str( "0" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 0 );

  iss.str( "0.0" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 0 );

  iss.str( "0.000000000000000000e+00" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 0 );

  iss.str( "10" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 10 );

  iss.str( "-10, 1.000000000e+00" );
  iss.clear();
  
  Utility::fromStream( iss, test_int, "," );

  TEST_EQUALITY_CONST( test_int, -10 );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 1 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( FromStringTraits, fromStream );

//---------------------------------------------------------------------------//
// Check that unsigned integer types can be created from a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( FromStringTraits, unsigned_fromString, T )
{
  typedef typename std::make_unsigned<T>::type UnsignedT;
  
  TEST_EQUALITY_CONST( Utility::fromString<UnsignedT>( "0" ), 0 );
  TEST_EQUALITY_CONST( Utility::fromString<UnsignedT>( "0.0" ), 0 );
  TEST_EQUALITY_CONST( Utility::fromString<UnsignedT>( "0.000000000e+00" ), 0 );
  TEST_EQUALITY_CONST( Utility::fromString<UnsignedT>( "10" ), 10 );
  TEST_EQUALITY_CONST( Utility::fromString<UnsignedT>( "255" ), 255 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( FromStringTraits, unsigned_fromString );

//---------------------------------------------------------------------------//
// Check that unsigned integer types can be extracted from a stream
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( FromStringTraits, unsigned_fromStream, T )
{
  std::istringstream iss( "0" );

  T test_int;

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 0 );

  iss.str( "0.0" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 0 );

  iss.str( "0.000000000000000000e+00" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 0 );

  iss.str( "10" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 10 );

  iss.str( "255" );
  iss.clear();

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 255 );

  iss.str( "255, 1.000000000e+00" );
  iss.clear();
  
  Utility::fromStream( iss, test_int, "," );

  TEST_EQUALITY_CONST( test_int, 255 );

  Utility::moveInputStreamToNextElement( iss, ',', '}' );

  Utility::fromStream( iss, test_int );

  TEST_EQUALITY_CONST( test_int, 1 );
}

UNIT_TEST_TEMPLATE_1_INSTANT( FromStringTraits, unsigned_fromStream );

//---------------------------------------------------------------------------//
// Check that tuple types can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, tuple_fromString )
{
  TEST_EQUALITY_CONST( Utility::fromString<std::tuple<int> >( "{0}" ),
                       std::make_tuple( 0 ) );
  TEST_EQUALITY_CONST( Utility::fromString<std::tuple<float> >( "{0.0}" ),
                       std::make_tuple( 0.0f ) );
  TEST_EQUALITY_CONST( Utility::fromString<std::tuple<double> >( "{0.0}" ),
                       std::make_tuple( 0.0 ) );
  TEST_EQUALITY_CONST( Utility::fromString<std::tuple<std::string> >( "{test}" ),
                       std::make_tuple( std::string( "test" ) ) );
  TEST_EQUALITY_CONST( Utility::fromString<std::tuple<bool> >( "{0}" ),
                       std::make_tuple( false ) );
  TEST_EQUALITY_CONST( Utility::fromString<std::tuple<bool> >( "{false}" ),
                       std::make_tuple( false ) );
  TEST_EQUALITY_CONST( Utility::fromString<std::tuple<bool> >( "{1}" ),
                       std::make_tuple( true ) );
  TEST_EQUALITY_CONST( Utility::fromString<std::tuple<bool> >( "{true}" ),
                       std::make_tuple( true ) );

  TEST_EQUALITY_CONST( (Utility::fromString<std::tuple<int,double> >( "{-1, 1.000000000000000000e+00}" )),
                       std::make_tuple( -1, 1.0 ) );
  TEST_EQUALITY_CONST( (Utility::fromString<std::tuple<float,int> >( "{1.000000000e+00, -1000}" )),
                       std::make_tuple( 1.0f, -1000 ) );
  TEST_EQUALITY_CONST( (Utility::fromString<std::tuple<long,bool> >( "{10, true}" )),
                       std::make_tuple( 10l, true ) );
  TEST_EQUALITY_CONST( (Utility::fromString<std::tuple<bool,bool> >( "{1, false}" )),
                       std::make_tuple( true, false ) );
  TEST_EQUALITY_CONST( (Utility::fromString<std::tuple<std::string,bool> >( "{test, 0}" )),
                       std::make_tuple( std::string( "test" ), false ) );

  {
    std::string test_string;
    double test_double;

    auto tuple_proxy = std::tie( test_string, test_double );

    tuple_proxy = Utility::fromString<decltype(tuple_proxy)>( "{test, -1.0}" );

    TEST_EQUALITY_CONST( test_string, "test" );
    TEST_EQUALITY_CONST( test_double, -1.0 );
  }

  TEST_EQUALITY_CONST( (Utility::fromString<std::tuple<unsigned,int,bool> >( "{100, -1, false}" )),
                       std::make_tuple( 100u, -1, false ) );
  TEST_EQUALITY_CONST( (Utility::fromString<std::tuple<double,bool,std::string> >( "{1.0, 1, test}" )),
                       std::make_tuple( 1.0, true, std::string( "test" ) ) );

  {
    bool test_bool;
    unsigned long long test_ull;
    float test_float;

    auto tuple_proxy = std::tie( test_bool, test_ull, test_float );
    decltype(tuple_proxy)& tuple_proxy_reference = tuple_proxy;

    tuple_proxy = Utility::fromString<decltype(tuple_proxy_reference)>( "{true, 100000, -1.0}" );

    TEST_EQUALITY_CONST( test_bool, true );
    TEST_EQUALITY_CONST( test_ull, 100000 );
    TEST_EQUALITY_CONST( test_float, -1.0f );
  }

  TEST_EQUALITY_CONST( (Utility::fromString<std::tuple<bool,long long,std::string,std::tuple<float,double> > >( "{true, -100, test, {-1.0, 1.0}}" )),
                       std::make_tuple( true, -100ll, std::string( "test" ), std::make_tuple( -1.0f, 1.0 ) ) );
}

//---------------------------------------------------------------------------//
// Check that tuple types can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, tuple_fromStream )
{
  std::istringstream iss( "{0}" );

  {
    std::tuple<int> test_tuple;

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( 0 ) );
  }

  iss.str( "{0.0}" );
  iss.clear();

  {
    std::tuple<float> test_tuple;

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( 0.0f ) );
  }

  iss.str( "{0.0}" );
  iss.clear();

  {
    std::tuple<double> test_tuple;

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( 0.0 ) );
  }

  iss.str( "{test}" );
  iss.clear();

  {
    std::tuple<std::string> test_tuple;

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( std::string( "test" ) ) );
  }

  iss.str( "{0}" );
  iss.clear();

  {
    std::tuple<bool> test_tuple;

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( false ) );

    iss.str( "{false}" );
    iss.clear();

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( false ) );

    iss.str( "{1}" );
    iss.clear();

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( true ) );

    iss.str( "{true}" );
    iss.clear();

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( true ) );
  }

  iss.str( "{-1, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::tuple<int,double> test_tuple;

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( -1, 1.0 ) );
  }

  iss.str( "{1.000000000e+00, -1000}" );
  iss.clear();

  {
    std::tuple<float,int> test_tuple;

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( 1.0f, -1000 ) );
  }

  iss.str( "{10, true}" );
  iss.clear();

  {
    std::tuple<long,bool> test_tuple;

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( 10l, true ) );
  }

  iss.str( "{1, false}" );
  iss.clear();

  {
    std::tuple<bool,bool> test_tuple;

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( true, false ) );
  }

  iss.str( "{test, 0}" );
  iss.clear();

  {
    std::tuple<std::string,bool> test_tuple;

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( std::string( "test" ), false ) );
  }

  iss.str( "{test, -1.0}" );
  iss.clear();
  
  {
    std::string test_string;
    double test_double;

    auto tuple_proxy = std::tie( test_string, test_double );

    Utility::fromStream( iss, tuple_proxy );

    TEST_EQUALITY_CONST( test_string, "test" );
    TEST_EQUALITY_CONST( test_double, -1.0 );
  }

  iss.str( "{100, -1, false}" );
  iss.clear();

  {
    std::tuple<unsigned,int,bool> test_tuple;

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( 100u, -1, false ) );
  }

  iss.str( "{1.0, 1, test}" );
  iss.clear();

  {
    std::tuple<double,bool,std::string> test_tuple;

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( 1.0, true, std::string( "test" ) ) );
  }

  iss.str( "{true, 100000, -1.0}" );
  iss.clear();

  {
    bool test_bool;
    unsigned long long test_ull;
    float test_float;

    auto tuple_proxy = std::tie( test_bool, test_ull, test_float );
    decltype(tuple_proxy)& tuple_proxy_reference = tuple_proxy;

    Utility::fromStream( iss, tuple_proxy_reference );

    TEST_EQUALITY_CONST( test_bool, true );
    TEST_EQUALITY_CONST( test_ull, 100000 );
    TEST_EQUALITY_CONST( test_float, -1.0f );
  }

  iss.str( "{true, -100, test, {-1.0, 1.0}}" );
  iss.clear();

  {
    std::tuple<bool,long long,std::string,std::tuple<float,double> > test_tuple;

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( true, -100ll, std::string( "test" ), std::make_tuple( -1.0f, 1.0 ) ) );
  }

  iss.str( "{1, test 0}, {-1, test 1}" );
  iss.clear();

  {
    std::tuple<int,std::string> test_tuple;

    Utility::fromStream( iss, test_tuple, "," );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( 1, std::string( "test 0" ) ) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    Utility::fromStream( iss, test_tuple );

    TEST_EQUALITY_CONST( test_tuple, std::make_tuple( -1, std::string( "test 1" ) ) );
  }
}

//---------------------------------------------------------------------------//
// Check that pair types can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, pair_fromString )
{
  TEST_EQUALITY_CONST( (Utility::fromString<std::pair<int,double> >( "{-1, 1.000000000000000000e+00}" )),
                       std::make_pair( -1, 1.0 ) );
  TEST_EQUALITY_CONST( (Utility::fromString<std::pair<float,long> >( "{-1.0, 1}" )),
                       std::make_pair( -1.0f, 1l ) );
  TEST_EQUALITY_CONST( (Utility::fromString<std::pair<std::string,bool> >( "{test, true}" )),
                       std::make_pair( std::string( "test" ), true ) );
  TEST_EQUALITY_CONST( (Utility::fromString<std::pair<bool,std::string> >( "{0, test}" )),
                       std::make_pair( false, std::string( "test" ) ) );

  {
    long test_long;
    double test_double;

    std::pair<long&, double&> pair_proxy = std::make_pair( std::ref( test_long ), std::ref( test_double ) );

    pair_proxy = Utility::fromString<std::pair<long&, double&> >( "{-1000000, -1.0}" );

    TEST_EQUALITY_CONST( test_long, -1000000l );
    TEST_EQUALITY_CONST( test_double, -1.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that pair types can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, pair_fromStream )
{
  std::istringstream iss( "{-1, 1.000000000000000000e+00}" );

  {
    std::pair<int,double> test_pair;

    Utility::fromStream( iss, test_pair );

    TEST_EQUALITY_CONST( test_pair, std::make_pair( -1, 1.0 ) );
  }

  iss.str( "{-1.0, 1}" );
  iss.clear();

  {
    std::pair<float,long> test_pair;

    Utility::fromStream( iss, test_pair );
    
    TEST_EQUALITY_CONST( test_pair, std::make_pair( -1.0f, 1l ) );
  }

  iss.str( "{test, true}" );
  iss.clear();

  {
    std::pair<std::string,bool> test_pair;

    Utility::fromStream( iss, test_pair );

    TEST_EQUALITY_CONST( test_pair, std::make_pair( std::string( "test" ), true ) );
  }

  iss.str( "{0, test}" );
  iss.clear();

  {
    std::pair<bool,std::string> test_pair;

    Utility::fromStream( iss, test_pair );

    TEST_EQUALITY_CONST( test_pair, std::make_pair( false, std::string( "test" ) ) );
  }

  iss.str( "{-1000000, -1.0}" );
  iss.clear();
  
  {
    long test_long;
    double test_double;

    std::pair<long&, double&> pair_proxy =
      std::make_pair( std::ref( test_long ), std::ref( test_double ) );

    std::pair<long&, double&>& pair_proxy_reference = pair_proxy;

    Utility::fromStream( iss, pair_proxy_reference );

    TEST_EQUALITY_CONST( test_long, -1000000l );
    TEST_EQUALITY_CONST( test_double, -1.0 );
  }

  iss.str( "{1, test 0}, {-1, test 1}" );
  iss.clear();

  {
    std::pair<int,std::string> test_pair;

    Utility::fromStream( iss, test_pair, "," );

    TEST_EQUALITY_CONST( test_pair, std::make_pair( 1, std::string( "test 0" ) ) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    Utility::fromStream( iss, test_pair );

    TEST_EQUALITY_CONST( test_pair, std::make_pair( -1, std::string( "test 1" ) ) );
  }
}

//---------------------------------------------------------------------------//
// Check that a vector can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, vector_fromString )
{
  TEST_COMPARE_ARRAYS( (Utility::fromString<std::vector<short> >( "{-1, 2}" )),
                       std::vector<short>({-1, 2}) );
  TEST_COMPARE_ARRAYS( (Utility::fromString<std::vector<unsigned short> >( "{0, 10, 100}" )),
                       std::vector<unsigned short>({0, 10, 100}) );
  TEST_COMPARE_ARRAYS( (Utility::fromString<std::vector<int> >( "{-11111, 0, 11111, 22222}" )),
                       std::vector<int>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_ARRAYS( (Utility::fromString<std::vector<unsigned int> >( "{0, 10, 100, 1000, 10000}" )),
                       std::vector<unsigned int>({0, 10, 100, 1000, 10000}) );
  TEST_COMPARE_ARRAYS( (Utility::fromString<std::vector<long> >( "{-11111, 0, 11111, 22222}" )),
                       std::vector<long>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_ARRAYS( (Utility::fromString<std::vector<unsigned long> >( "{0, 10, 100, 1000, 10000}" )),
                       std::vector<unsigned long>({0, 10, 100, 1000, 10000}) );
  TEST_COMPARE_ARRAYS( (Utility::fromString<std::vector<long long> >( "{-1000000000, 0, 1000000000}" )),
                       std::vector<long long>({-1000000000, 0, 1000000000}) );
  TEST_COMPARE_ARRAYS( (Utility::fromString<std::vector<unsigned long long> >( "{0, 1000000000, 10000000000}" )),
                       std::vector<unsigned long long>({0, 1000000000, 10000000000}) );
  TEST_COMPARE_ARRAYS( (Utility::fromString<std::vector<float> >( "{-1, 0.0, 1.000000000e+00}" )),
                       std::vector<float>({-1.0f, 0.0f, 1.0f}) );
  TEST_COMPARE_ARRAYS( (Utility::fromString<std::vector<double> >( "{-1, 0.0, 1.000000000000000000e+00}" )),
                       std::vector<double>({-1.0, 0.0, 1.0}) );
  TEST_COMPARE_ARRAYS( (Utility::fromString<std::vector<char> >( "{T, e, s, t,  , s, t, r, i, n, g}" )),
                       std::vector<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  TEST_COMPARE_ARRAYS( (Utility::fromString<std::vector<std::string> >( "{Test, string}" )),
                       std::vector<std::string>({"Test","string"}) );
  TEST_COMPARE_ARRAYS( (Utility::fromString<std::vector<std::pair<int, int> > >( "{{0, 1}, {-1, 2}}" )),
                       (std::vector<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  TEST_COMPARE_ARRAYS( (Utility::fromString<std::vector<std::tuple<unsigned, double, long> > >( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" )),
                       (std::vector<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
}

//---------------------------------------------------------------------------//
// Check that a vector can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, vector_fromStream )
{
  std::istringstream iss( "{-1, 2}" );

  {
    std::vector<short> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_ARRAYS( test_vector, std::vector<short>({-1, 2}) );
  }

  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::vector<unsigned short> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_ARRAYS( test_vector, std::vector<unsigned short>({0, 10, 100}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::vector<int> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_ARRAYS( test_vector, std::vector<int>({-11111, 0, 11111, 22222}) );
  }
                      
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::vector<unsigned> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_ARRAYS( test_vector, std::vector<unsigned>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::vector<long> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_ARRAYS( test_vector, std::vector<long>({-11111, 0, 11111, 22222}) );
  }

  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::vector<unsigned long> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_ARRAYS( test_vector, std::vector<unsigned long>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::vector<long long> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_ARRAYS( test_vector, std::vector<long long>({-1000000000, 0, 1000000000}) );
  }

  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::vector<unsigned long long> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_ARRAYS( test_vector, std::vector<unsigned long long>({0, 1000000000, 10000000000}) );
  }

  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::vector<float> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_ARRAYS( test_vector, std::vector<float>({-1.0f, 0.0f, 1.0f}) );
  }

  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::vector<double> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_ARRAYS( test_vector, std::vector<double>({-1.0, 0.0, 1.0}) );
  }

  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::vector<char> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_ARRAYS( test_vector, std::vector<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::vector<std::string> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_ARRAYS( test_vector, std::vector<std::string>({"Test","string"}) );
  }

  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::vector<std::pair<int,int> > test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_ARRAYS( test_vector, (std::vector<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::vector<std::tuple<unsigned,double,long> > test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_ARRAYS( test_vector, (std::vector<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  iss.str( "{{0, 1}, {-1, 2}}, {{1, 0}, {2, -1}}" );
  iss.clear();

  {
    std::vector<std::pair<long,long> > test_vector;

    Utility::fromStream( iss, test_vector, "," );

    TEST_COMPARE_ARRAYS( test_vector, (std::vector<std::pair<long,long> >({std::make_pair(0l, 1l), std::make_pair(-1l, 2l)})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    Utility::fromStream( iss, test_vector );

    TEST_EQUALITY_CONST( test_vector, (std::vector<std::pair<long,long> >({std::make_pair(1l, 0l), std::make_pair(2l, -1l)})) );
  }
}

//---------------------------------------------------------------------------//
// end tstFromStringTraits.cpp
//---------------------------------------------------------------------------//
