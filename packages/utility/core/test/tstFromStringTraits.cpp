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
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<short> >( "{-1, 2}" )),
                           std::vector<short>({-1, 2}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned short> >( "{0, 10, 100}" )),
                           std::vector<unsigned short>({0, 10, 100}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<int> >( "{-11111, 0, 11111, 22222}" )),
                           std::vector<int>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned int> >( "{0, 10, 100, 1000, 10000}" )),
                           std::vector<unsigned int>({0, 10, 100, 1000, 10000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<long> >( "{-11111, 0, 11111, 22222}" )),
                           std::vector<long>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned long> >( "{0, 10, 100, 1000, 10000}" )),
                           std::vector<unsigned long>({0, 10, 100, 1000, 10000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<long long> >( "{-1000000000, 0, 1000000000}" )),
                           std::vector<long long>({-1000000000, 0, 1000000000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned long long> >( "{0, 1000000000, 10000000000}" )),
                           std::vector<unsigned long long>({0, 1000000000, 10000000000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{-1, 0.0, 1.000000000e+00}" )),
                           std::vector<float>({-1.0f, 0.0f, 1.0f}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<double> >( "{-1, 0.0, 1.000000000000000000e+00}" )),
                           std::vector<double>({-1.0, 0.0, 1.0}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<char> >( "{T, e, s, t,  , s, t, r, i, n, g}" )),
                           std::vector<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<std::string> >( "{Test, string}" )),
                           std::vector<std::string>({"Test","string"}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<std::pair<int, int> > >( "{{0, 1}, {-1, 2}}" )),
                           (std::vector<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<std::tuple<unsigned, double, long> > >( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" )),
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

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<short>({-1, 2}) );
  }

  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::vector<unsigned short> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned short>({0, 10, 100}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::vector<int> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<int>({-11111, 0, 11111, 22222}) );
  }
                      
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::vector<unsigned> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::vector<long> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<long>({-11111, 0, 11111, 22222}) );
  }

  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::vector<unsigned long> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned long>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::vector<long long> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<long long>({-1000000000, 0, 1000000000}) );
  }

  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::vector<unsigned long long> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned long long>({0, 1000000000, 10000000000}) );
  }

  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::vector<float> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<float>({-1.0f, 0.0f, 1.0f}) );
  }

  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::vector<double> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<double>({-1.0, 0.0, 1.0}) );
  }

  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::vector<char> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::vector<std::string> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<std::string>({"Test","string"}) );
  }

  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::vector<std::pair<int,int> > test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::vector<std::tuple<unsigned,double,long> > test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  iss.str( "{{0, 1}, {-1, 2}}, {{1, 0}, {2, -1}}" );
  iss.clear();

  {
    std::vector<std::pair<long,long> > test_vector;

    Utility::fromStream( iss, test_vector, "," );

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::pair<long,long> >({std::make_pair(0l, 1l), std::make_pair(-1l, 2l)})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::pair<long,long> >({std::make_pair(1l, 0l), std::make_pair(2l, -1l)})) );
  }
}

//---------------------------------------------------------------------------//
// Check that a list can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, list_fromString )
{
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::list<short> >( "{-1, 2}" )),
                           std::list<short>({-1, 2}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::list<unsigned short> >( "{0, 10, 100}" )),
                           std::list<unsigned short>({0, 10, 100}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::list<int> >( "{-11111, 0, 11111, 22222}" )),
                           std::list<int>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::list<unsigned int> >( "{0, 10, 100, 1000, 10000}" )),
                           std::list<unsigned int>({0, 10, 100, 1000, 10000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::list<long> >( "{-11111, 0, 11111, 22222}" )),
                           std::list<long>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::list<unsigned long> >( "{0, 10, 100, 1000, 10000}" )),
                           std::list<unsigned long>({0, 10, 100, 1000, 10000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::list<long long> >( "{-1000000000, 0, 1000000000}" )),
                           std::list<long long>({-1000000000, 0, 1000000000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::list<unsigned long long> >( "{0, 1000000000, 10000000000}" )),
                           std::list<unsigned long long>({0, 1000000000, 10000000000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::list<float> >( "{-1, 0.0, 1.000000000e+00}" )),
                           std::list<float>({-1.0f, 0.0f, 1.0f}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::list<double> >( "{-1, 0.0, 1.000000000000000000e+00}" )),
                           std::list<double>({-1.0, 0.0, 1.0}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::list<char> >( "{T, e, s, t,  , s, t, r, i, n, g}" )),
                           std::list<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::list<std::string> >( "{Test, string}" )),
                           std::list<std::string>({"Test","string"}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::list<std::pair<int, int> > >( "{{0, 1}, {-1, 2}}" )),
                           (std::list<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::list<std::tuple<unsigned, double, long> > >( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" )),
                           (std::list<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
}

//---------------------------------------------------------------------------//
// Check that a list can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, list_fromStream )
{
  std::istringstream iss( "{-1, 2}" );

  {
    std::list<short> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<short>({-1, 2}) );
  }

  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::list<unsigned short> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned short>({0, 10, 100}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::list<int> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<int>({-11111, 0, 11111, 22222}) );
  }
                      
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::list<unsigned> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::list<long> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<long>({-11111, 0, 11111, 22222}) );
  }

  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::list<unsigned long> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned long>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::list<long long> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<long long>({-1000000000, 0, 1000000000}) );
  }

  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::list<unsigned long long> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned long long>({0, 1000000000, 10000000000}) );
  }

  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::list<float> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<float>({-1.0f, 0.0f, 1.0f}) );
  }

  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::list<double> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<double>({-1.0, 0.0, 1.0}) );
  }

  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::list<char> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::list<std::string> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<std::string>({"Test","string"}) );
  }

  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::list<std::pair<int,int> > test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, (std::list<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::list<std::tuple<unsigned,double,long> > test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, (std::list<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  iss.str( "{{0, 1}, {-1, 2}}, {{1, 0}, {2, -1}}" );
  iss.clear();

  {
    std::list<std::pair<long,long> > test_list;

    Utility::fromStream( iss, test_list, "," );

    TEST_COMPARE_CONTAINERS( test_list, (std::list<std::pair<long,long> >({std::make_pair(0l, 1l), std::make_pair(-1l, 2l)})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, (std::list<std::pair<long,long> >({std::make_pair(1l, 0l), std::make_pair(2l, -1l)})) );
  }
}

//---------------------------------------------------------------------------//
// Check that a forward_list can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, forward_list_fromString )
{
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::forward_list<short> >( "{-1, 2}" )),
                           std::forward_list<short>({-1, 2}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::forward_list<unsigned short> >( "{0, 10, 100}" )),
                           std::forward_list<unsigned short>({0, 10, 100}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::forward_list<int> >( "{-11111, 0, 11111, 22222}" )),
                           std::forward_list<int>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::forward_list<unsigned int> >( "{0, 10, 100, 1000, 10000}" )),
                           std::forward_list<unsigned int>({0, 10, 100, 1000, 10000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::forward_list<long> >( "{-11111, 0, 11111, 22222}" )),
                           std::forward_list<long>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::forward_list<unsigned long> >( "{0, 10, 100, 1000, 10000}" )),
                           std::forward_list<unsigned long>({0, 10, 100, 1000, 10000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::forward_list<long long> >( "{-1000000000, 0, 1000000000}" )),
                           std::forward_list<long long>({-1000000000, 0, 1000000000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::forward_list<unsigned long long> >( "{0, 1000000000, 10000000000}" )),
                           std::forward_list<unsigned long long>({0, 1000000000, 10000000000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::forward_list<float> >( "{-1, 0.0, 1.000000000e+00}" )),
                           std::forward_list<float>({-1.0f, 0.0f, 1.0f}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::forward_list<double> >( "{-1, 0.0, 1.000000000000000000e+00}" )),
                           std::forward_list<double>({-1.0, 0.0, 1.0}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::forward_list<char> >( "{T, e, s, t,  , s, t, r, i, n, g}" )),
                           std::forward_list<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::forward_list<std::string> >( "{Test, string}" )),
                           std::forward_list<std::string>({"Test","string"}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::forward_list<std::pair<int, int> > >( "{{0, 1}, {-1, 2}}" )),
                           (std::forward_list<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::forward_list<std::tuple<unsigned, double, long> > >( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" )),
                           (std::forward_list<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
}

//---------------------------------------------------------------------------//
// Check that a forward_list can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, forward_list_fromStream )
{
  std::istringstream iss( "{-1, 2}" );

  {
    std::forward_list<short> test_forward_list;

    Utility::fromStream( iss, test_forward_list );

    TEST_COMPARE_CONTAINERS( test_forward_list, std::forward_list<short>({-1, 2}) );
  }

  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::forward_list<unsigned short> test_forward_list;

    Utility::fromStream( iss, test_forward_list );

    TEST_COMPARE_CONTAINERS( test_forward_list, std::forward_list<unsigned short>({0, 10, 100}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::forward_list<int> test_forward_list;

    Utility::fromStream( iss, test_forward_list );

    TEST_COMPARE_CONTAINERS( test_forward_list, std::forward_list<int>({-11111, 0, 11111, 22222}) );
  }
                      
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::forward_list<unsigned> test_forward_list;

    Utility::fromStream( iss, test_forward_list );

    TEST_COMPARE_CONTAINERS( test_forward_list, std::forward_list<unsigned>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::forward_list<long> test_forward_list;

    Utility::fromStream( iss, test_forward_list );

    TEST_COMPARE_CONTAINERS( test_forward_list, std::forward_list<long>({-11111, 0, 11111, 22222}) );
  }

  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::forward_list<unsigned long> test_forward_list;

    Utility::fromStream( iss, test_forward_list );

    TEST_COMPARE_CONTAINERS( test_forward_list, std::forward_list<unsigned long>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::forward_list<long long> test_forward_list;

    Utility::fromStream( iss, test_forward_list );

    TEST_COMPARE_CONTAINERS( test_forward_list, std::forward_list<long long>({-1000000000, 0, 1000000000}) );
  }

  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::forward_list<unsigned long long> test_forward_list;

    Utility::fromStream( iss, test_forward_list );

    TEST_COMPARE_CONTAINERS( test_forward_list, std::forward_list<unsigned long long>({0, 1000000000, 10000000000}) );
  }

  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::forward_list<float> test_forward_list;

    Utility::fromStream( iss, test_forward_list );

    TEST_COMPARE_CONTAINERS( test_forward_list, std::forward_list<float>({-1.0f, 0.0f, 1.0f}) );
  }

  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::forward_list<double> test_forward_list;

    Utility::fromStream( iss, test_forward_list );

    TEST_COMPARE_CONTAINERS( test_forward_list, std::forward_list<double>({-1.0, 0.0, 1.0}) );
  }

  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::forward_list<char> test_forward_list;

    Utility::fromStream( iss, test_forward_list );

    TEST_COMPARE_CONTAINERS( test_forward_list, std::forward_list<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::forward_list<std::string> test_forward_list;

    Utility::fromStream( iss, test_forward_list );

    TEST_COMPARE_CONTAINERS( test_forward_list, std::forward_list<std::string>({"Test","string"}) );
  }

  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::forward_list<std::pair<int,int> > test_forward_list;

    Utility::fromStream( iss, test_forward_list );

    TEST_COMPARE_CONTAINERS( test_forward_list, (std::forward_list<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::forward_list<std::tuple<unsigned,double,long> > test_forward_list;

    Utility::fromStream( iss, test_forward_list );

    TEST_COMPARE_CONTAINERS( test_forward_list, (std::forward_list<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  iss.str( "{{0, 1}, {-1, 2}}, {{1, 0}, {2, -1}}" );
  iss.clear();

  {
    std::forward_list<std::pair<long,long> > test_forward_list;

    Utility::fromStream( iss, test_forward_list, "," );

    TEST_COMPARE_CONTAINERS( test_forward_list, (std::forward_list<std::pair<long,long> >({std::make_pair(0l, 1l), std::make_pair(-1l, 2l)})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    Utility::fromStream( iss, test_forward_list );

    TEST_COMPARE_CONTAINERS( test_forward_list, (std::forward_list<std::pair<long,long> >({std::make_pair(1l, 0l), std::make_pair(2l, -1l)})) );
  }
}

//---------------------------------------------------------------------------//
// Check that a deque can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, deque_fromString )
{
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::deque<short> >( "{-1, 2}" )),
                           std::deque<short>({-1, 2}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::deque<unsigned short> >( "{0, 10, 100}" )),
                           std::deque<unsigned short>({0, 10, 100}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::deque<int> >( "{-11111, 0, 11111, 22222}" )),
                           std::deque<int>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::deque<unsigned int> >( "{0, 10, 100, 1000, 10000}" )),
                           std::deque<unsigned int>({0, 10, 100, 1000, 10000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::deque<long> >( "{-11111, 0, 11111, 22222}" )),
                           std::deque<long>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::deque<unsigned long> >( "{0, 10, 100, 1000, 10000}" )),
                           std::deque<unsigned long>({0, 10, 100, 1000, 10000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::deque<long long> >( "{-1000000000, 0, 1000000000}" )),
                           std::deque<long long>({-1000000000, 0, 1000000000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::deque<unsigned long long> >( "{0, 1000000000, 10000000000}" )),
                           std::deque<unsigned long long>({0, 1000000000, 10000000000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::deque<float> >( "{-1, 0.0, 1.000000000e+00}" )),
                           std::deque<float>({-1.0f, 0.0f, 1.0f}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::deque<double> >( "{-1, 0.0, 1.000000000000000000e+00}" )),
                           std::deque<double>({-1.0, 0.0, 1.0}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::deque<char> >( "{T, e, s, t,  , s, t, r, i, n, g}" )),
                           std::deque<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::deque<std::string> >( "{Test, string}" )),
                           std::deque<std::string>({"Test","string"}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::deque<std::pair<int, int> > >( "{{0, 1}, {-1, 2}}" )),
                           (std::deque<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::deque<std::tuple<unsigned, double, long> > >( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" )),
                           (std::deque<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
}

//---------------------------------------------------------------------------//
// Check that a deque can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, deque_fromStream )
{
  std::istringstream iss( "{-1, 2}" );

  {
    std::deque<short> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<short>({-1, 2}) );
  }

  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::deque<unsigned short> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned short>({0, 10, 100}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::deque<int> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<int>({-11111, 0, 11111, 22222}) );
  }
                      
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::deque<unsigned> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::deque<long> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<long>({-11111, 0, 11111, 22222}) );
  }

  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::deque<unsigned long> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned long>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::deque<long long> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<long long>({-1000000000, 0, 1000000000}) );
  }

  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::deque<unsigned long long> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned long long>({0, 1000000000, 10000000000}) );
  }

  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::deque<float> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<float>({-1.0f, 0.0f, 1.0f}) );
  }

  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::deque<double> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<double>({-1.0, 0.0, 1.0}) );
  }

  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::deque<char> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::deque<std::string> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<std::string>({"Test","string"}) );
  }

  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::deque<std::pair<int,int> > test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, (std::deque<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::deque<std::tuple<unsigned,double,long> > test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, (std::deque<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  iss.str( "{{0, 1}, {-1, 2}}, {{1, 0}, {2, -1}}" );
  iss.clear();

  {
    std::deque<std::pair<long,long> > test_deque;

    Utility::fromStream( iss, test_deque, "," );

    TEST_COMPARE_CONTAINERS( test_deque, (std::deque<std::pair<long,long> >({std::make_pair(0l, 1l), std::make_pair(-1l, 2l)})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, (std::deque<std::pair<long,long> >({std::make_pair(1l, 0l), std::make_pair(2l, -1l)})) );
  }
}

//---------------------------------------------------------------------------//
// Check that a set can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, set_fromString )
{
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::set<short> >( "{-1, 2}" )),
                                     std::set<short>({-1, 2}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::set<unsigned short> >( "{0, 10, 100}" )),
                                     std::set<unsigned short>({0, 10, 100}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::set<int> >( "{-11111, 0, 11111, 22222}" )),
                                     std::set<int>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::set<unsigned int> >( "{0, 10, 100, 1000, 10000}" )),
                                     std::set<unsigned int>({0, 10, 100, 1000, 10000}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::set<long> >( "{-11111, 0, 11111, 22222}" )),
                                     std::set<long>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::set<unsigned long> >( "{0, 10, 100, 1000, 10000}" )),
                                     std::set<unsigned long>({0, 10, 100, 1000, 10000}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::set<long long> >( "{-1000000000, 0, 1000000000}" )),
                                     std::set<long long>({-1000000000, 0, 1000000000}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::set<unsigned long long> >( "{0, 1000000000, 10000000000}" )),
                                     std::set<unsigned long long>({0, 1000000000, 10000000000}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::set<float> >( "{-1, 0.0, 1.000000000e+00}" )),
                                     std::set<float>({-1.0f, 0.0f, 1.0f}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::set<double> >( "{-1, 0.0, 1.000000000000000000e+00}" )),
                                     std::set<double>({-1.0, 0.0, 1.0}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::set<char> >( "{T, e, s, t,  , s, t, r, i, n, g}" )),
                                     std::set<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::set<std::string> >( "{Test, string}" )),
                                     std::set<std::string>({"Test","string"}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::set<std::pair<int, int> > >( "{{0, 1}, {-1, 2}}" )),
                                     (std::set<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::set<std::tuple<unsigned, double, long> > >( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" )),
                                     (std::set<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
}

//---------------------------------------------------------------------------//
// Check that a set can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, set_fromStream )
{
  std::istringstream iss( "{-1, 2}" );

  {
    std::set<short> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<short>({-1, 2}) );
  }

  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::set<unsigned short> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<unsigned short>({0, 10, 100}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::set<int> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<int>({-11111, 0, 11111, 22222}) );
  }
                      
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::set<unsigned> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<unsigned>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::set<long> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<long>({-11111, 0, 11111, 22222}) );
  }

  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::set<unsigned long> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<unsigned long>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::set<long long> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<long long>({-1000000000, 0, 1000000000}) );
  }

  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::set<unsigned long long> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<unsigned long long>({0, 1000000000, 10000000000}) );
  }

  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::set<float> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<float>({-1.0f, 0.0f, 1.0f}) );
  }

  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::set<double> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<double>({-1.0, 0.0, 1.0}) );
  }

  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::set<char> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::set<std::string> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<std::string>({"Test","string"}) );
  }

  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::set<std::pair<int,int> > test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, (std::set<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::set<std::tuple<unsigned,double,long> > test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, (std::set<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  iss.str( "{{0, 1}, {-1, 2}}, {{1, 0}, {2, -1}}" );
  iss.clear();

  {
    std::set<std::pair<long,long> > test_set;

    Utility::fromStream( iss, test_set, "," );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, (std::set<std::pair<long,long> >({std::make_pair(0l, 1l), std::make_pair(-1l, 2l)})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, (std::set<std::pair<long,long> >({std::make_pair(1l, 0l), std::make_pair(2l, -1l)})) );
  }
}

//---------------------------------------------------------------------------//
// Check that a unordered_set can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, unordered_set_fromString )
{
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_set<short> >( "{-1, 2}" )),
                                     std::unordered_set<short>({-1, 2}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_set<unsigned short> >( "{0, 10, 100}" )),
                                     std::unordered_set<unsigned short>({0, 10, 100}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_set<int> >( "{-11111, 0, 11111, 22222}" )),
                                     std::unordered_set<int>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_set<unsigned int> >( "{0, 10, 100, 1000, 10000}" )),
                                     std::unordered_set<unsigned int>({0, 10, 100, 1000, 10000}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_set<long> >( "{-11111, 0, 11111, 22222}" )),
                                     std::unordered_set<long>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_set<unsigned long> >( "{0, 10, 100, 1000, 10000}" )),
                                     std::unordered_set<unsigned long>({0, 10, 100, 1000, 10000}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_set<long long> >( "{-1000000000, 0, 1000000000}" )),
                                     std::unordered_set<long long>({-1000000000, 0, 1000000000}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_set<unsigned long long> >( "{0, 1000000000, 10000000000}" )),
                                     std::unordered_set<unsigned long long>({0, 1000000000, 10000000000}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_set<float> >( "{-1, 0.0, 1.000000000e+00}" )),
                                     std::unordered_set<float>({-1.0f, 0.0f, 1.0f}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_set<double> >( "{-1, 0.0, 1.000000000000000000e+00}" )),
                                     std::unordered_set<double>({-1.0, 0.0, 1.0}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_set<char> >( "{T, e, s, t,  , s, t, r, i, n, g}" )),
                                     std::unordered_set<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_set<std::string> >( "{Test, string}" )),
                                     std::unordered_set<std::string>({"Test","string"}) );
}

//---------------------------------------------------------------------------//
// Check that a unordered_set can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, unordered_set_fromStream )
{
  std::istringstream iss( "{-1, 2}" );

  {
    std::unordered_set<short> test_unordered_set;

    Utility::fromStream( iss, test_unordered_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<short>({-1, 2}) );
  }

  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::unordered_set<unsigned short> test_unordered_set;

    Utility::fromStream( iss, test_unordered_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<unsigned short>({0, 10, 100}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::unordered_set<int> test_unordered_set;

    Utility::fromStream( iss, test_unordered_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<int>({-11111, 0, 11111, 22222}) );
  }
                      
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::unordered_set<unsigned> test_unordered_set;

    Utility::fromStream( iss, test_unordered_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<unsigned>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::unordered_set<long> test_unordered_set;

    Utility::fromStream( iss, test_unordered_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<long>({-11111, 0, 11111, 22222}) );
  }

  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::unordered_set<unsigned long> test_unordered_set;

    Utility::fromStream( iss, test_unordered_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<unsigned long>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::unordered_set<long long> test_unordered_set;

    Utility::fromStream( iss, test_unordered_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<long long>({-1000000000, 0, 1000000000}) );
  }

  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::unordered_set<unsigned long long> test_unordered_set;

    Utility::fromStream( iss, test_unordered_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<unsigned long long>({0, 1000000000, 10000000000}) );
  }

  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::unordered_set<float> test_unordered_set;

    Utility::fromStream( iss, test_unordered_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<float>({-1.0f, 0.0f, 1.0f}) );
  }

  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::unordered_set<double> test_unordered_set;

    Utility::fromStream( iss, test_unordered_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<double>({-1.0, 0.0, 1.0}) );
  }

  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::unordered_set<char> test_unordered_set;

    Utility::fromStream( iss, test_unordered_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::unordered_set<std::string> test_unordered_set;

    Utility::fromStream( iss, test_unordered_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<std::string>({"Test","string"}) );
  }
}

//---------------------------------------------------------------------------//
// Check that a map can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, map_fromString )
{
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::map<short,short> >( "{{-1, 2}, {0, 1}}" )),
                                     (std::map<short,short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::map<unsigned short, unsigned short> >( "{{0, 1}, {2, 10}}" )),
                                     (std::map<unsigned short, unsigned short>( {std::pair<unsigned short,unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::map<int, int> >( "{{-10, 0}, {10, -20}}" )),
                                     (std::map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::map<unsigned, unsigned> >( "{{0, 2}, {10, 100}}" )),
                                     (std::map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::map<long, long> >( "{{-1000000000, 1}, {1000000000, 2}}" )),
                                     (std::map<long,long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::map<unsigned long, unsigned long> >( "{{0, 1000000000}, {1000000000, 2000000000}}" )),
                                     (std::map<unsigned long, unsigned long>( {std::make_pair(0ul, 1000000000ul), std::make_pair(1000000000ul, 2000000000ul)} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::map<long long, long long> >( "{{-10000000000, 1}, {10000000000, 2}}" )),
                                     (std::map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::map<unsigned long long, unsigned long long> >( "{{0, 10000000000}, {10000000000, 20000000000}}" )),
                                     (std::map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::map<int, float> >( "{{-1, -1.0000000000e+00}, {1, 1.000000000e+00}}" )),
                                     (std::map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::map<unsigned, double> >( "{{0, 0.000000000000000000e+00}, {1, 1.000000000000000000e+00}}" )),
                                     (std::map<unsigned, double>( {std::make_pair(0u, 0.0), std::make_pair(1u, 1.0)} )) );

  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::map<char, char> >( "{{A, B}, {a, b}}" )),
                                     (std::map<char, char>( {std::make_pair('A', 'B'), std::make_pair('a', 'b')} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::map<std::string, std::string> >( "{{Test String A, Hello A}, {Test String B, Hello B}}" )),
                                    (std::map<std::string, std::string>( {std::make_pair("Test String A", "Hello A"), std::make_pair("Test String B", "Hello B")} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::map<int,std::pair<double,unsigned> > >( "{{-1, {1.0, 0}}, {1, {0.0, 10}}}" )),
                                     (std::map<int,std::pair<double,unsigned> >( {std::make_pair(-1, std::make_pair(1.0, 0u)), std::make_pair(1, std::make_pair(0.0, 10u))} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::map<unsigned,std::tuple<int,float,unsigned long> > >( "{{0, {1, -1.0, 10}}, {1, {-1, 0.0, 100}}}" )),
                                     (std::map<unsigned,std::tuple<int,float,unsigned long> >( {std::make_pair(0u, std::make_tuple(1, -1.0f, 10ul)), std::make_pair(1u, std::make_tuple(-1, 0.0f, 100ul))} )) );
}

//---------------------------------------------------------------------------//
// Check that a map can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, map_fromStream )
{
  std::istringstream iss( "{{-1, 2}, {0, 1}}" );

  {
    std::map<short,short> test_map;

    Utility::fromStream( iss, test_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<short,short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} )) );
  }

  iss.str( "{{0, 1}, {2, 10}}" );
  iss.clear();

  {
    std::map<unsigned short, unsigned short> test_map;

    Utility::fromStream( iss, test_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<unsigned short, unsigned short>( {std::pair<unsigned short,unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} )) );
  }

  iss.str( "{{-10, 0}, {10, -20}}" );
  iss.clear();

  {
    std::map<int, int> test_map;

    Utility::fromStream( iss, test_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} )) );
  }

  iss.str( "{{0, 2}, {10, 100}}" );
  iss.clear();

  {
    std::map<unsigned, unsigned> test_map;

    Utility::fromStream( iss, test_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} )) );
  }

  iss.str( "{{-1000000000, 1}, {1000000000, 2}}" );
  iss.clear();

  {
    std::map<long, long> test_map;

    Utility::fromStream( iss, test_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<long,long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} )) );
  }

  iss.str( "{{0, 1000000000}, {1000000000, 2000000000}}" );
  iss.clear();

  {
    std::map<unsigned long, unsigned long> test_map;

    Utility::fromStream( iss, test_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<unsigned long, unsigned long>( {std::make_pair(0ul, 1000000000ul), std::make_pair(1000000000ul, 2000000000ul)} )) );
  }

  iss.str( "{{-10000000000, 1}, {10000000000, 2}}" );
  iss.clear();

  {
    std::map<long long, long long> test_map;

    Utility::fromStream( iss, test_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} )) );
  }

  iss.str( "{{0, 10000000000}, {10000000000, 20000000000}}" );
  iss.clear();

  {
    std::map<unsigned long long, unsigned long long> test_map;

    Utility::fromStream( iss, test_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} )) );
  }

  iss.str( "{{-1, -1.0000000000e+00}, {1, 1.000000000e+00}}" );
  iss.clear();

  {
    std::map<int, float> test_map;

    Utility::fromStream( iss, test_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} )) );
  }

  iss.str( "{{0, 0.000000000000000000e+00}, {1, 1.000000000000000000e+00}}" );
  iss.clear();

  {
    std::map<unsigned, double> test_map;

    Utility::fromStream( iss, test_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<unsigned, double>( {std::make_pair(0u, 0.0), std::make_pair(1u, 1.0)} )) );
  }

  iss.str( "{{A, B}, {a, b}}" );
  iss.clear();

  {
    std::map<char, char> test_map;

    Utility::fromStream( iss, test_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<char, char>( {std::make_pair('A', 'B'), std::make_pair('a', 'b')} )) );
  }

  iss.str( "{{Test String A, Hello A}, {Test String B, Hello B}}" );
  iss.clear();

  {
    std::map<std::string, std::string> test_map;

    Utility::fromStream( iss, test_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<std::string, std::string>( {std::make_pair("Test String A", "Hello A"), std::make_pair("Test String B", "Hello B")} )) );
  }

  iss.str( "{{-1, {1.0, 0}}, {1, {0.0, 10}}}" );
  iss.clear();

  {
    std::map<int,std::pair<double,unsigned> > test_map;

    Utility::fromStream( iss, test_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<int,std::pair<double,unsigned> >( {std::make_pair(-1, std::make_pair(1.0, 0u)), std::make_pair(1, std::make_pair(0.0, 10u))} )) );
  }

  iss.str( "{{0, {1, -1.0, 10}}, {1, {-1, 0.0, 100}}}" );
  iss.clear();

  {
    std::map<unsigned,std::tuple<int,float,unsigned long> > test_map;

    Utility::fromStream( iss, test_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<unsigned,std::tuple<int,float,unsigned long> >( {std::make_pair(0u, std::make_tuple(1, -1.0f, 10ul)), std::make_pair(1u, std::make_tuple(-1, 0.0f, 100ul))} )) );
  }

  iss.str( "{{-10, Test String A}, {201, Test String B}}, {{0, Test String C}, {333, Test String D}}" );
  iss.clear();

  {
    std::map<int, std::string> test_map;
    
    Utility::fromStream( iss, test_map, "," );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<int, std::string>({std::make_pair(-10, "Test String A"), std::make_pair(201, "Test String B")})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    Utility::fromStream( iss, test_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<int, std::string>({std::make_pair(0, "Test String C"), std::make_pair(333, "Test String D")})) );
  }                                
}

//---------------------------------------------------------------------------//
// Check that a unordered_map can be created from a string
TEUCHOS_UNIT_TEST( FromStringTraits, unordered_map_fromString )
{
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_map<short,short> >( "{{-1, 2}, {0, 1}}" )),
                                     (std::unordered_map<short,short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_map<unsigned short, unsigned short> >( "{{0, 1}, {2, 10}}" )),
                                     (std::unordered_map<unsigned short, unsigned short>( {std::pair<unsigned short,unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_map<int, int> >( "{{-10, 0}, {10, -20}}" )),
                                     (std::unordered_map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_map<unsigned, unsigned> >( "{{0, 2}, {10, 100}}" )),
                                     (std::unordered_map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_map<long, long> >( "{{-1000000000, 1}, {1000000000, 2}}" )),
                                     (std::unordered_map<long,long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_map<unsigned long, unsigned long> >( "{{0, 1000000000}, {1000000000, 2000000000}}" )),
                                     (std::unordered_map<unsigned long, unsigned long>( {std::make_pair(0ul, 1000000000ul), std::make_pair(1000000000ul, 2000000000ul)} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_map<long long, long long> >( "{{-10000000000, 1}, {10000000000, 2}}" )),
                                     (std::unordered_map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_map<unsigned long long, unsigned long long> >( "{{0, 10000000000}, {10000000000, 20000000000}}" )),
                                     (std::unordered_map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_map<int, float> >( "{{-1, -1.0000000000e+00}, {1, 1.000000000e+00}}" )),
                                     (std::unordered_map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_map<unsigned, double> >( "{{0, 0.000000000000000000e+00}, {1, 1.000000000000000000e+00}}" )),
                                     (std::unordered_map<unsigned, double>( {std::make_pair(0u, 0.0), std::make_pair(1u, 1.0)} )) );

  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_map<char, char> >( "{{A, B}, {a, b}}" )),
                                     (std::unordered_map<char, char>( {std::make_pair('A', 'B'), std::make_pair('a', 'b')} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_map<std::string, std::string> >( "{{Test String A, Hello A}, {Test String B, Hello B}}" )),
                                    (std::unordered_map<std::string, std::string>( {std::make_pair("Test String A", "Hello A"), std::make_pair("Test String B", "Hello B")} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_map<int,std::pair<double,unsigned> > >( "{{-1, {1.0, 0}}, {1, {0.0, 10}}}" )),
                                     (std::unordered_map<int,std::pair<double,unsigned> >( {std::make_pair(-1, std::make_pair(1.0, 0u)), std::make_pair(1, std::make_pair(0.0, 10u))} )) );
  TEST_COMPARE_UNORDERED_CONTAINERS( (Utility::fromString<std::unordered_map<unsigned,std::tuple<int,float,unsigned long> > >( "{{0, {1, -1.0, 10}}, {1, {-1, 0.0, 100}}}" )),
                                     (std::unordered_map<unsigned,std::tuple<int,float,unsigned long> >( {std::make_pair(0u, std::make_tuple(1, -1.0f, 10ul)), std::make_pair(1u, std::make_tuple(-1, 0.0f, 100ul))} )) );
}

//---------------------------------------------------------------------------//
// Check that a unordered_map can be extracted from a stream
TEUCHOS_UNIT_TEST( FromStringTraits, unordered_map_fromStream )
{
  std::istringstream iss( "{{-1, 2}, {0, 1}}" );

  {
    std::unordered_map<short,short> test_unordered_map;

    Utility::fromStream( iss, test_unordered_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<short,short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} )) );
  }

  iss.str( "{{0, 1}, {2, 10}}" );
  iss.clear();

  {
    std::unordered_map<unsigned short, unsigned short> test_unordered_map;

    Utility::fromStream( iss, test_unordered_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<unsigned short, unsigned short>( {std::pair<unsigned short,unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} )) );
  }

  iss.str( "{{-10, 0}, {10, -20}}" );
  iss.clear();

  {
    std::unordered_map<int, int> test_unordered_map;

    Utility::fromStream( iss, test_unordered_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} )) );
  }

  iss.str( "{{0, 2}, {10, 100}}" );
  iss.clear();

  {
    std::unordered_map<unsigned, unsigned> test_unordered_map;

    Utility::fromStream( iss, test_unordered_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} )) );
  }

  iss.str( "{{-1000000000, 1}, {1000000000, 2}}" );
  iss.clear();

  {
    std::unordered_map<long, long> test_unordered_map;

    Utility::fromStream( iss, test_unordered_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<long,long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} )) );
  }

  iss.str( "{{0, 1000000000}, {1000000000, 2000000000}}" );
  iss.clear();

  {
    std::unordered_map<unsigned long, unsigned long> test_unordered_map;

    Utility::fromStream( iss, test_unordered_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<unsigned long, unsigned long>( {std::make_pair(0ul, 1000000000ul), std::make_pair(1000000000ul, 2000000000ul)} )) );
  }

  iss.str( "{{-10000000000, 1}, {10000000000, 2}}" );
  iss.clear();

  {
    std::unordered_map<long long, long long> test_unordered_map;

    Utility::fromStream( iss, test_unordered_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} )) );
  }

  iss.str( "{{0, 10000000000}, {10000000000, 20000000000}}" );
  iss.clear();

  {
    std::unordered_map<unsigned long long, unsigned long long> test_unordered_map;

    Utility::fromStream( iss, test_unordered_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} )) );
  }

  iss.str( "{{-1, -1.0000000000e+00}, {1, 1.000000000e+00}}" );
  iss.clear();

  {
    std::unordered_map<int, float> test_unordered_map;

    Utility::fromStream( iss, test_unordered_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} )) );
  }

  iss.str( "{{0, 0.000000000000000000e+00}, {1, 1.000000000000000000e+00}}" );
  iss.clear();

  {
    std::unordered_map<unsigned, double> test_unordered_map;

    Utility::fromStream( iss, test_unordered_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<unsigned, double>( {std::make_pair(0u, 0.0), std::make_pair(1u, 1.0)} )) );
  }

  iss.str( "{{A, B}, {a, b}}" );
  iss.clear();

  {
    std::unordered_map<char, char> test_unordered_map;

    Utility::fromStream( iss, test_unordered_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<char, char>( {std::make_pair('A', 'B'), std::make_pair('a', 'b')} )) );
  }

  iss.str( "{{Test String A, Hello A}, {Test String B, Hello B}}" );
  iss.clear();

  {
    std::unordered_map<std::string, std::string> test_unordered_map;

    Utility::fromStream( iss, test_unordered_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<std::string, std::string>( {std::make_pair("Test String A", "Hello A"), std::make_pair("Test String B", "Hello B")} )) );
  }

  iss.str( "{{-1, {1.0, 0}}, {1, {0.0, 10}}}" );
  iss.clear();

  {
    std::unordered_map<int,std::pair<double,unsigned> > test_unordered_map;

    Utility::fromStream( iss, test_unordered_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<int,std::pair<double,unsigned> >( {std::make_pair(-1, std::make_pair(1.0, 0u)), std::make_pair(1, std::make_pair(0.0, 10u))} )) );
  }

  iss.str( "{{0, {1, -1.0, 10}}, {1, {-1, 0.0, 100}}}" );
  iss.clear();

  {
    std::unordered_map<unsigned,std::tuple<int,float,unsigned long> > test_unordered_map;

    Utility::fromStream( iss, test_unordered_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<unsigned,std::tuple<int,float,unsigned long> >( {std::make_pair(0u, std::make_tuple(1, -1.0f, 10ul)), std::make_pair(1u, std::make_tuple(-1, 0.0f, 100ul))} )) );
  }

  iss.str( "{{-10, Test String A}, {201, Test String B}}, {{0, Test String C}, {333, Test String D}}" );
  iss.clear();

  {
    std::unordered_map<int, std::string> test_unordered_map;
    
    Utility::fromStream( iss, test_unordered_map, "," );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<int, std::string>({std::make_pair(-10, "Test String A"), std::make_pair(201, "Test String B")})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    Utility::fromStream( iss, test_unordered_map );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<int, std::string>({std::make_pair(0, "Test String C"), std::make_pair(333, "Test String D")})) );
  }                                
}

//---------------------------------------------------------------------------//
// end tstFromStringTraits.cpp
//---------------------------------------------------------------------------//
