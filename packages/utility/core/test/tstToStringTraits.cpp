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
// Check that an array can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, array_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( std::array<short,2>( {-1, 2} ) ),
                       "{-1, 2}" );
  TEST_EQUALITY_CONST( Utility::toString( std::array<unsigned short,3>( {0, 10, 100} ) ),
                       "{0, 10, 100}" );
  TEST_EQUALITY_CONST( Utility::toString( std::array<int,4>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  TEST_EQUALITY_CONST( Utility::toString( std::array<unsigned int, 5>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::array<long,4>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  TEST_EQUALITY_CONST( Utility::toString( std::array<unsigned long, 5>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::array<long long, 3>( {-10000000000, 0, 10000000000} ) ),
                       "{-10000000000, 0, 10000000000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::array<unsigned long long, 3>( {0, 1000000000, 1000000000000} ) ),
                       "{0, 1000000000, 1000000000000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::array<float, 3>( {-1.0f, 0.0f, 1.0f} ) ),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::array<double, 3>( {-1.0, 0.0, 1.0} ) ),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::array<char,11>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) ),
                       "{T, e, s, t,  , s, t, r, i, n, g}" );
  TEST_EQUALITY_CONST( Utility::toString( std::array<std::string, 2>( {"Test", "string"} ) ),
                       "{Test, string}" );
  TEST_EQUALITY_CONST( Utility::toString( std::array<std::pair<int, int>, 2>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) ),
                       "{{0, 1}, {-1, 2}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::array<std::tuple<unsigned, double, long>, 2>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) ),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that an array can be placed in a stream
TEUCHOS_UNIT_TEST( ToStringTraits, array_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::array<short,2>( {-1, 2} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<unsigned short,3>( {0, 10, 100} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<int,4>( {-11111, 0, 11111, 22222} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<unsigned int, 5>( {0, 10, 100, 1000, 10000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<long,4>( {-11111, 0, 11111, 22222} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<unsigned long, 5>( {0, 10, 100, 1000, 10000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<long long, 3>( {-10000000000, 0, 10000000000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<unsigned long long, 3>( {0, 1000000000, 1000000000000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<float, 3>( {-1.0f, 0.0f, 1.0f} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<double, 3>( {-1.0, 0.0, 1.0} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<char,11>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<std::string, 2>( {"Test", "string"} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<std::pair<int, int>, 2>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<std::tuple<unsigned, double, long>, 2>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a vector can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, vector_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( std::vector<short>( {-1, 2} ) ),
                       "{-1, 2}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<unsigned short>( {0, 10, 100} ) ),
                       "{0, 10, 100}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<int>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<unsigned int>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<long>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<unsigned long>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<long long>( {-10000000000, 0, 10000000000} ) ),
                       "{-10000000000, 0, 10000000000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<unsigned long long>( {0, 1000000000, 1000000000000} ) ),
                       "{0, 1000000000, 1000000000000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<float>( {-1.0f, 0.0f, 1.0f} ) ),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<double>( {-1.0, 0.0, 1.0} ) ),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) ),
                       "{T, e, s, t,  , s, t, r, i, n, g}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<std::string>( {"Test", "string"} ) ),
                       "{Test, string}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) ),
                       "{{0, 1}, {-1, 2}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::vector<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) ),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a vector can be placed in a stream
TEUCHOS_UNIT_TEST( ToStringTraits, vector_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::vector<short>( {-1, 2} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<unsigned short>( {0, 10, 100} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<int>( {-11111, 0, 11111, 22222} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<unsigned int>( {0, 10, 100, 1000, 10000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<long>( {-11111, 0, 11111, 22222} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<unsigned long>( {0, 10, 100, 1000, 10000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<long long>( {-10000000000, 0, 10000000000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<unsigned long long>( {0, 1000000000, 1000000000000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<float>( {-1.0f, 0.0f, 1.0f} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<double>( {-1.0, 0.0, 1.0} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<std::string>( {"Test", "string"} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<std::pair<int, int>>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<std::tuple<unsigned, double, long>>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a list can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, list_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( std::list<short>( {-1, 2} ) ),
                       "{-1, 2}" );
  TEST_EQUALITY_CONST( Utility::toString( std::list<unsigned short>( {0, 10, 100} ) ),
                       "{0, 10, 100}" );
  TEST_EQUALITY_CONST( Utility::toString( std::list<int>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  TEST_EQUALITY_CONST( Utility::toString( std::list<unsigned int>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::list<long>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  TEST_EQUALITY_CONST( Utility::toString( std::list<unsigned long>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::list<long long>( {-10000000000, 0, 10000000000} ) ),
                       "{-10000000000, 0, 10000000000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::list<unsigned long long>( {0, 1000000000, 1000000000000} ) ),
                       "{0, 1000000000, 1000000000000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::list<float>( {-1.0f, 0.0f, 1.0f} ) ),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::list<double>( {-1.0, 0.0, 1.0} ) ),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::list<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) ),
                       "{T, e, s, t,  , s, t, r, i, n, g}" );
  TEST_EQUALITY_CONST( Utility::toString( std::list<std::string>( {"Test", "string"} ) ),
                       "{Test, string}" );
  TEST_EQUALITY_CONST( Utility::toString( std::list<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) ),
                       "{{0, 1}, {-1, 2}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::list<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) ),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a list can be placed in a stream
TEUCHOS_UNIT_TEST( ToStringTraits, list_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::list<short>( {-1, 2} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<unsigned short>( {0, 10, 100} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<int>( {-11111, 0, 11111, 22222} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<unsigned int>( {0, 10, 100, 1000, 10000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<long>( {-11111, 0, 11111, 22222} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<unsigned long>( {0, 10, 100, 1000, 10000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<long long>( {-10000000000, 0, 10000000000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<unsigned long long>( {0, 1000000000, 1000000000000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<float>( {-1.0f, 0.0f, 1.0f} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<double>( {-1.0, 0.0, 1.0} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<std::string>( {"Test", "string"} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<std::pair<int, int>>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<std::tuple<unsigned, double, long>>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a forward_list can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, forward_list_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( std::forward_list<short>( {-1, 2} ) ),
                       "{-1, 2}" );
  TEST_EQUALITY_CONST( Utility::toString( std::forward_list<unsigned short>( {0, 10, 100} ) ),
                       "{0, 10, 100}" );
  TEST_EQUALITY_CONST( Utility::toString( std::forward_list<int>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  TEST_EQUALITY_CONST( Utility::toString( std::forward_list<unsigned int>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::forward_list<long>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  TEST_EQUALITY_CONST( Utility::toString( std::forward_list<unsigned long>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::forward_list<long long>( {-10000000000, 0, 10000000000} ) ),
                       "{-10000000000, 0, 10000000000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::forward_list<unsigned long long>( {0, 1000000000, 1000000000000} ) ),
                       "{0, 1000000000, 1000000000000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::forward_list<float>( {-1.0f, 0.0f, 1.0f} ) ),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::forward_list<double>( {-1.0, 0.0, 1.0} ) ),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::forward_list<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) ),
                       "{T, e, s, t,  , s, t, r, i, n, g}" );
  TEST_EQUALITY_CONST( Utility::toString( std::forward_list<std::string>( {"Test", "string"} ) ),
                       "{Test, string}" );
  TEST_EQUALITY_CONST( Utility::toString( std::forward_list<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) ),
                       "{{0, 1}, {-1, 2}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::forward_list<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) ),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a forward_list can be placed in a stream
TEUCHOS_UNIT_TEST( ToStringTraits, forward_list_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::forward_list<short>( {-1, 2} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<unsigned short>( {0, 10, 100} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<int>( {-11111, 0, 11111, 22222} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<unsigned int>( {0, 10, 100, 1000, 10000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<long>( {-11111, 0, 11111, 22222} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<unsigned long>( {0, 10, 100, 1000, 10000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<long long>( {-10000000000, 0, 10000000000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<unsigned long long>( {0, 1000000000, 1000000000000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<float>( {-1.0f, 0.0f, 1.0f} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<double>( {-1.0, 0.0, 1.0} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<std::string>( {"Test", "string"} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<std::pair<int, int>>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<std::tuple<unsigned, double, long>>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a deque can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, deque_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( std::deque<short>( {-1, 2} ) ),
                       "{-1, 2}" );
  TEST_EQUALITY_CONST( Utility::toString( std::deque<unsigned short>( {0, 10, 100} ) ),
                       "{0, 10, 100}" );
  TEST_EQUALITY_CONST( Utility::toString( std::deque<int>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  TEST_EQUALITY_CONST( Utility::toString( std::deque<unsigned int>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::deque<long>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  TEST_EQUALITY_CONST( Utility::toString( std::deque<unsigned long>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::deque<long long>( {-10000000000, 0, 10000000000} ) ),
                       "{-10000000000, 0, 10000000000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::deque<unsigned long long>( {0, 1000000000, 1000000000000} ) ),
                       "{0, 1000000000, 1000000000000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::deque<float>( {-1.0f, 0.0f, 1.0f} ) ),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::deque<double>( {-1.0, 0.0, 1.0} ) ),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::deque<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) ),
                       "{T, e, s, t,  , s, t, r, i, n, g}" );
  TEST_EQUALITY_CONST( Utility::toString( std::deque<std::string>( {"Test", "string"} ) ),
                       "{Test, string}" );
  TEST_EQUALITY_CONST( Utility::toString( std::deque<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) ),
                       "{{0, 1}, {-1, 2}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::deque<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) ),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a deque can be placed in a stream
TEUCHOS_UNIT_TEST( ToStringTraits, deque_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::deque<short>( {-1, 2} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<unsigned short>( {0, 10, 100} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<int>( {-11111, 0, 11111, 22222} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<unsigned int>( {0, 10, 100, 1000, 10000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<long>( {-11111, 0, 11111, 22222} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<unsigned long>( {0, 10, 100, 1000, 10000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<long long>( {-10000000000, 0, 10000000000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<unsigned long long>( {0, 1000000000, 1000000000000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<float>( {-1.0f, 0.0f, 1.0f} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<double>( {-1.0, 0.0, 1.0} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<std::string>( {"Test", "string"} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<std::pair<int, int>>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<std::tuple<unsigned, double, long>>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a set can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, set_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( std::set<short>( {-1, 2} ) ),
                       "{-1, 2}" );
  TEST_EQUALITY_CONST( Utility::toString( std::set<unsigned short>( {0, 10, 100} ) ),
                       "{0, 10, 100}" );
  TEST_EQUALITY_CONST( Utility::toString( std::set<int>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  TEST_EQUALITY_CONST( Utility::toString( std::set<unsigned int>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::set<long>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  TEST_EQUALITY_CONST( Utility::toString( std::set<unsigned long>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::set<long long>( {-10000000000, 0, 10000000000} ) ),
                       "{-10000000000, 0, 10000000000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::set<unsigned long long>( {0, 1000000000, 1000000000000} ) ),
                       "{0, 1000000000, 1000000000000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::set<float>( {-1.0f, 0.0f, 1.0f} ) ),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::set<double>( {-1.0, 0.0, 1.0} ) ),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::set<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) ),
                       "{ , T, e, g, i, n, r, s, t}" );
  TEST_EQUALITY_CONST( Utility::toString( std::set<std::string>( {"Test", "string"} ) ),
                       "{Test, string}" );
  TEST_EQUALITY_CONST( Utility::toString( std::set<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) ),
                       "{{-1, 2}, {0, 1}}" );
  TEST_EQUALITY_CONST( Utility::toString( std::set<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) ),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a set can be placed in a stream
TEUCHOS_UNIT_TEST( ToStringTraits, set_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::set<short>( {-1, 2} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<unsigned short>( {0, 10, 100} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<int>( {-11111, 0, 11111, 22222} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<unsigned int>( {0, 10, 100, 1000, 10000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<long>( {-11111, 0, 11111, 22222} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<unsigned long>( {0, 10, 100, 1000, 10000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<long long>( {-10000000000, 0, 10000000000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<unsigned long long>( {0, 1000000000, 1000000000000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<float>( {-1.0f, 0.0f, 1.0f} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<double>( {-1.0, 0.0, 1.0} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{ , T, e, g, i, n, r, s, t}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<std::string>( {"Test", "string"} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{{-1, 2}, {0, 1}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) );
  
  TEST_EQUALITY_CONST( oss.str(), 
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a unordered_set can be converted to a string
TEUCHOS_UNIT_TEST( ToStringTraits, unordered_set_toString )
{
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_set<short>( {-1, 2} ) ),
                       "{2, -1}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_set<unsigned short>( {0, 10, 100} ) ),
                       "{100, 0, 10}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_set<int>( {-11111, 0, 11111, 22222} ) ),
                       "{22222, 11111, 0, -11111}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_set<unsigned int>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10000, 100, 10, 1000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_set<long>( {-11111, 0, 11111, 22222} ) ),
                       "{22222, 11111, 0, -11111}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_set<unsigned long>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10000, 100, 10, 1000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_set<long long>( {-10000000000, 0, 10000000000} ) ),
                       "{10000000000, -10000000000, 0}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_set<unsigned long long>( {0, 1000000000, 1000000000000} ) ),
                       "{1000000000000, 0, 1000000000}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_set<float>( {-1.0f, 0.0f, 1.0f} ) ),
                       "{1.000000000e+00, -1.000000000e+00, 0.000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_set<double>( {-1.0, 0.0, 1.0} ) ),
                       "{1.000000000000000000e+00, -1.000000000000000000e+00, 0.000000000000000000e+00}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_set<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) ),
                       "{n, g, r,  , i, t, s, e, T}" );
  TEST_EQUALITY_CONST( Utility::toString( std::unordered_set<std::string>( {"Test", "string"} ) ),
                       "{string, Test}" );
}

//---------------------------------------------------------------------------//
// Check that a unordered_set can be placed in a stream
TEUCHOS_UNIT_TEST( ToStringTraits, unordered_set_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::unordered_set<short>( {-1, 2} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{2, -1}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<unsigned short>( {0, 10, 100} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{100, 0, 10}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<int>( {-11111, 0, 11111, 22222} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{22222, 11111, 0, -11111}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<unsigned int>( {0, 10, 100, 1000, 10000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10000, 100, 10, 1000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<long>( {-11111, 0, 11111, 22222} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{22222, 11111, 0, -11111}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<unsigned long>( {0, 10, 100, 1000, 10000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10000, 100, 10, 1000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<long long>( {-10000000000, 0, 10000000000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{10000000000, -10000000000, 0}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<unsigned long long>( {0, 1000000000, 1000000000000} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{1000000000000, 0, 1000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<float>( {-1.0f, 0.0f, 1.0f} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{1.000000000e+00, -1.000000000e+00, 0.000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<double>( {-1.0, 0.0, 1.0} ) );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{1.000000000000000000e+00, -1.000000000000000000e+00, 0.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{n, g, r,  , i, t, s, e, T}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<std::string>( {"Test", "string"} ) );
  
  TEST_EQUALITY_CONST( oss.str(), "{string, Test}" );
}

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
