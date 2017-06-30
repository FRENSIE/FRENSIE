//---------------------------------------------------------------------------//
//!
//! \file   tstArray.cpp
//! \author Alex Robinson
//! \brief  Array helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_Array.hpp"
#include "Utility_Tuple.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an array can be converted to a string
TEUCHOS_UNIT_TEST( Array, array_toString )
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
TEUCHOS_UNIT_TEST( Array, array_toStream )
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
// Check that an array can be placed in a stream
TEUCHOS_UNIT_TEST( Array, array_ostream )
{
  std::ostringstream oss;

  oss << std::array<short,2>( {-1, 2} );
  
  TEST_EQUALITY_CONST( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<unsigned short,3>( {0, 10, 100} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<int,4>( {-11111, 0, 11111, 22222} );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<unsigned int, 5>( {0, 10, 100, 1000, 10000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<long,4>( {-11111, 0, 11111, 22222} );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<unsigned long, 5>( {0, 10, 100, 1000, 10000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<long long, 3>( {-10000000000, 0, 10000000000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<unsigned long long, 3>( {0, 1000000000, 1000000000000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<float, 3>( {-1.0f, 0.0f, 1.0f} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  oss << std::array<double, 3>( {-1.0, 0.0, 1.0} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<char,11>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } );
  
  TEST_EQUALITY_CONST( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<std::string, 2>( {"Test", "string"} );
  
  TEST_EQUALITY_CONST( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<std::pair<int, int>, 2>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<std::tuple<unsigned, double, long>, 2>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a view of a array can be created
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Array, slice_operator, T )
{
  std::array<T,5> array({0, 1, 2, 3, 4});

  Utility::ArrayView<T> view = array | Utility::Slice( 0, 1 );

  TEST_EQUALITY_CONST( view.size(), 1 );
  TEST_EQUALITY_CONST( view[0], array[0] );

  view = array | Utility::slice( 1, 2 );

  TEST_EQUALITY_CONST( view.size(), 2 );
  TEST_EQUALITY_CONST( view[0], array[1] );
  TEST_EQUALITY_CONST( view[1], array[2] );

  view = array | std::make_pair( 1, 3 );

  TEST_EQUALITY_CONST( view.size(), 3 );
  TEST_EQUALITY_CONST( view[0], array[1] );
  TEST_EQUALITY_CONST( view[1], array[2] );
  TEST_EQUALITY_CONST( view[2], array[3] );

  view = array | std::make_pair( 2, 3 );

  TEST_EQUALITY_CONST( view.size(), 3 );
  TEST_EQUALITY_CONST( view[0], array[2] );
  TEST_EQUALITY_CONST( view[1], array[3] );
  TEST_EQUALITY_CONST( view[2], array[4] );

  Utility::ArrayView<const T> const_view =
    const_cast<const std::array<T,5>&>( array ) | Utility::slice( 1, 4 );

  TEST_EQUALITY_CONST( const_view.size(), 4 );
  TEST_EQUALITY_CONST( const_view[0], array[1] );
  TEST_EQUALITY_CONST( const_view[1], array[2] );
  TEST_EQUALITY_CONST( const_view[2], array[3] );
  TEST_EQUALITY_CONST( const_view[3], array[4] );
}

typedef unsigned short ushort;
typedef unsigned int uint;
typedef long long longlong;
typedef unsigned long long ulonglong;

TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( Array, slice_operator, short );
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( Array, slice_operator, ushort );
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( Array, slice_operator, int );
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( Array, slice_operator, uint );
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( Array, slice_operator, long );
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( Array, slice_operator, ulong );
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( Array, slice_operator, longlong );
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( Array, slice_operator, ulonglong );
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( Array, slice_operator, float );
TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( Array, slice_operator, double );

//---------------------------------------------------------------------------//
// end tstArray.cpp
//---------------------------------------------------------------------------//
