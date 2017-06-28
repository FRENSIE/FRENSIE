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
// Check that a map can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, map_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( std::map<short, short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} ) ),
                       "{{-1, 2}, {0, 1}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::map<unsigned short, unsigned short>( {std::pair<unsigned short, unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} ) ),
                       "{{0, 1}, {2, 10}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} ) ),
                       "{{-10, 0}, {10, -20}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} ) ),
                       "{{0, 2}, {10, 100}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::map<long, long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} ) ),
                       "{{-1000000000, 1}, {1000000000, 2}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::map<unsigned long, unsigned long>( {std::make_pair(0l, 1000000000l), std::make_pair(1000000000l, 2000000000l)} ) ),
                       "{{0, 1000000000}, {1000000000, 2000000000}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} ) ),
                       "{{-10000000000, 1}, {10000000000, 2}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} ) ),
                       "{{0, 10000000000}, {10000000000, 20000000000}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} ) ),
                       "{{-1, -1.000000000e+00}, {1, 1.000000000e+00}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::map<unsigned, double>( {std::make_pair(0, 0.0), std::make_pair(1, 1.0)} ) ),
                       "{{0, 0.000000000000000000e+00}, {1, 1.000000000000000000e+00}}" );

  TEST_EQUALITY_CONST( Utility::toString( std::map<char, char>( {std::make_pair( 'a', 'b'), std::make_pair( 'A', 'B' )} ) ),
                       "{{A, B}, {a, b}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::map<std::string, std::string>( {std::make_pair( "Test String A", "Hello A" ), std::make_pair( "Test String B", "Hello B" )} ) ),
                       "{{Test String A, Hello A}, {Test String B, Hello B}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::map<int,std::pair<double,unsigned> >( {std::make_pair( -1, std::make_pair( 1.0, 0u ) ), std::make_pair( 1, std::make_pair( 0.0, 10u ) )} ) ),
                       "{{-1, {1.000000000000000000e+00, 0}}, {1, {0.000000000000000000e+00, 10}}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::map<unsigned, std::tuple<int, float, unsigned long> >( {std::make_pair( 0u, std::make_tuple( 1, -1.0f, 10ul ) ), std::make_pair( 1u, std::make_tuple( -1, 0.0, 100ul ) )} ) ),
                       "{{0, {1, -1.000000000e+00, 10}}, {1, {-1, 0.000000000e+00, 100}}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::map<long, std::vector<float> >( {std::make_pair( -1000000000l, std::vector<float>( {-1.0, 0.0, 1.0} ) ), std::make_pair( 1000000000l, std::vector<float>( {0.0} ) )} ) ),
                       "{{-1000000000, {-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}}, {1000000000, {0.000000000e+00}}}" );
}

//---------------------------------------------------------------------------//
// Check that a map can be placed in a stream
TEUCHOS_UNIT_TEST( ToStringTraits, map_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::map<short, short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{-1, 2}, {0, 1}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<unsigned short, unsigned short>( {std::pair<unsigned short, unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 1}, {2, 10}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{-10, 0}, {10, -20}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 2}, {10, 100}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<long, long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{-1000000000, 1}, {1000000000, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<unsigned long, unsigned long>( {std::make_pair(0l, 1000000000l), std::make_pair(1000000000l, 2000000000l)} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 1000000000}, {1000000000, 2000000000}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{-10000000000, 1}, {10000000000, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{0, 10000000000}, {10000000000, 20000000000}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{-1, -1.000000000e+00}, {1, 1.000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<unsigned, double>( {std::make_pair(0, 0.0), std::make_pair(1, 1.0)} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{0, 0.000000000000000000e+00}, {1, 1.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<char, char>( {std::make_pair( 'a', 'b'), std::make_pair( 'A', 'B' )} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{A, B}, {a, b}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<std::string, std::string>( {std::make_pair( "Test String A", "Hello A" ), std::make_pair( "Test String B", "Hello B" )} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{Test String A, Hello A}, {Test String B, Hello B}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<int,std::pair<double,unsigned> >( {std::make_pair( -1, std::make_pair( 1.0, 0u ) ), std::make_pair( 1, std::make_pair( 0.0, 10u ) )} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{-1, {1.000000000000000000e+00, 0}}, {1, {0.000000000000000000e+00, 10}}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<unsigned, std::tuple<int, float, unsigned long> >( {std::make_pair( 0u, std::make_tuple( 1, -1.0f, 10ul ) ), std::make_pair( 1u, std::make_tuple( -1, 0.0, 100ul ) )} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{0, {1, -1.000000000e+00, 10}}, {1, {-1, 0.000000000e+00, 100}}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<long, std::vector<float> >( {std::make_pair( -1000000000l, std::vector<float>( {-1.0, 0.0, 1.0} ) ), std::make_pair( 1000000000l, std::vector<float>( {0.0} ) )} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{-1000000000, {-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}}, {1000000000, {0.000000000e+00}}}" );
}

//---------------------------------------------------------------------------//
// Check that a unordered_map can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, unordered_map_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_map<short, short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} ) ),
                       "{{0, 1}, {-1, 2}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_map<unsigned short, unsigned short>( {std::pair<unsigned short, unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} ) ),
                       "{{2, 10}, {0, 1}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} ) ),
                       "{{10, -20}, {-10, 0}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} ) ),
                       "{{10, 100}, {0, 2}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_map<long, long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} ) ),
                       "{{1000000000, 2}, {-1000000000, 1}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_map<unsigned long, unsigned long>( {std::make_pair(0l, 1000000000l), std::make_pair(1000000000l, 2000000000l)} ) ),
                       "{{1000000000, 2000000000}, {0, 1000000000}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} ) ),
                       "{{10000000000, 2}, {-10000000000, 1}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} ) ),
                       "{{10000000000, 20000000000}, {0, 10000000000}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} ) ),
                       "{{1, 1.000000000e+00}, {-1, -1.000000000e+00}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_map<unsigned, double>( {std::make_pair(0, 0.0), std::make_pair(1, 1.0)} ) ),
                       "{{1, 1.000000000000000000e+00}, {0, 0.000000000000000000e+00}}" );

  TEST_EQUALITY_CONST( Utility::toString( std::unordered_map<char, char>( {std::make_pair( 'a', 'b'), std::make_pair( 'A', 'B' )} ) ),
                       "{{A, B}, {a, b}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_map<std::string, std::string>( {std::make_pair( "Test String A", "Hello A" ), std::make_pair( "Test String B", "Hello B" )} ) ),
                       "{{Test String B, Hello B}, {Test String A, Hello A}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_map<int,std::pair<double,unsigned> >( {std::make_pair( -1, std::make_pair( 1.0, 0u ) ), std::make_pair( 1, std::make_pair( 0.0, 10u ) )} ) ),
                       "{{1, {0.000000000000000000e+00, 10}}, {-1, {1.000000000000000000e+00, 0}}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_map<unsigned, std::tuple<int, float, unsigned long> >( {std::make_pair( 0u, std::make_tuple( 1, -1.0f, 10ul ) ), std::make_pair( 1u, std::make_tuple( -1, 0.0, 100ul ) )} ) ),
                       "{{1, {-1, 0.000000000e+00, 100}}, {0, {1, -1.000000000e+00, 10}}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_map<long, std::vector<float> >( {std::make_pair( -1000000000l, std::vector<float>( {-1.0, 0.0, 1.0} ) ), std::make_pair( 1000000000l, std::vector<float>( {0.0} ) )} ) ),
                       "{{1000000000, {0.000000000e+00}}, {-1000000000, {-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}}}" );
}

//---------------------------------------------------------------------------//
// Check that a unordered_map can be placed in a stream
TEUCHOS_UNIT_TEST( ToStringTraits, unordered_map_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::unordered_map<short, short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<unsigned short, unsigned short>( {std::pair<unsigned short, unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{2, 10}, {0, 1}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{10, -20}, {-10, 0}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{10, 100}, {0, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<long, long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{1000000000, 2}, {-1000000000, 1}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<unsigned long, unsigned long>( {std::make_pair(0l, 1000000000l), std::make_pair(1000000000l, 2000000000l)} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{1000000000, 2000000000}, {0, 1000000000}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{10000000000, 2}, {-10000000000, 1}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{10000000000, 20000000000}, {0, 10000000000}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{1, 1.000000000e+00}, {-1, -1.000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<unsigned, double>( {std::make_pair(0, 0.0), std::make_pair(1, 1.0)} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{1, 1.000000000000000000e+00}, {0, 0.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<char, char>( {std::make_pair( 'a', 'b'), std::make_pair( 'A', 'B' )} ) );

  TEST_EQUALITY_CONST( oss.str(), "{{A, B}, {a, b}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<std::string, std::string>( {std::make_pair( "Test String A", "Hello A" ), std::make_pair( "Test String B", "Hello B" )} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{Test String B, Hello B}, {Test String A, Hello A}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<int,std::pair<double,unsigned> >( {std::make_pair( -1, std::make_pair( 1.0, 0u ) ), std::make_pair( 1, std::make_pair( 0.0, 10u ) )} ) );
  
  TEST_EQUALITY_CONST( oss.str(), 
                       "{{1, {0.000000000000000000e+00, 10}}, {-1, {1.000000000000000000e+00, 0}}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<unsigned, std::tuple<int, float, unsigned long> >( {std::make_pair( 0u, std::make_tuple( 1, -1.0f, 10ul ) ), std::make_pair( 1u, std::make_tuple( -1, 0.0, 100ul ) )} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{1, {-1, 0.000000000e+00, 100}}, {0, {1, -1.000000000e+00, 10}}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<long, std::vector<float> >( {std::make_pair( -1000000000l, std::vector<float>( {-1.0, 0.0, 1.0} ) ), std::make_pair( 1000000000l, std::vector<float>( {0.0} ) )} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{1000000000, {0.000000000e+00}}, {-1000000000, {-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}}}" );
}

//---------------------------------------------------------------------------//
// end tstToStringTraits.cpp
//---------------------------------------------------------------------------//
