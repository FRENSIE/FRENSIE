//---------------------------------------------------------------------------//
//!
//! \file   tstSet.cpp
//! \author Alex Robinson
//! \brief  Set helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_Set.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a set can be converted to a string
TEUCHOS_UNIT_TEST( Set, toString )
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
TEUCHOS_UNIT_TEST( Set, toStream )
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
TEUCHOS_UNIT_TEST( UnorderedSet, toString )
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
TEUCHOS_UNIT_TEST( UnorderedSet, toStream )
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
// Check that a set can be created from a string
TEUCHOS_UNIT_TEST( Set, fromString )
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
TEUCHOS_UNIT_TEST( Set, fromStream )
{
  // Extract set of short
  std::istringstream iss( "{-1, 2}" );

  {
    std::set<short> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<short>({-1, 2}) );

    iss.str( "{-1, 2i, 2}" );
    iss.clear();

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<short>({-1, 0, 1, 2}) );
  }

  // Extract set of unsigned short
  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::set<unsigned short> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<unsigned short>({0, 10, 100}) );

    iss.str( "{0, 3i, 100}" );
    iss.clear();

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<unsigned short>({0, 25, 50, 75, 100}) );
  }

  // Extract set of int
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::set<int> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<int>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<int>({-11111, 0, 11111, 22222}) );
  }

  // Extract set of unsigned int
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::set<unsigned> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<unsigned>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<unsigned>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract set of long
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::set<long> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<long>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<long>({-11111, 0, 11111, 22222}) );
  }

  // Extract set of unsigned long
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::set<unsigned long> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<unsigned long>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<unsigned long>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract set of long long
  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::set<long long> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<long long>({-1000000000, 0, 1000000000}) );

    iss.str( "{-1000000000, 1i, 1000000000}" );
    iss.clear();

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<long long>({-1000000000, 0, 1000000000}) );
  }

  // Extract set of unsigned long long
  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::set<unsigned long long> test_set;

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<unsigned long long>({0, 1000000000, 10000000000}) );

    iss.str( "{0, 1i, 10000000000}" );
    iss.clear();

    Utility::fromStream( iss, test_set );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<unsigned long long>({0, 5000000000, 10000000000}) );
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
TEUCHOS_UNIT_TEST( UnorderedSet, fromString )
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
TEUCHOS_UNIT_TEST( UnorderedSet, fromStream )
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
// Check that a set can be placed in a stream
TEUCHOS_UNIT_TEST( Set, ostream )
{
  std::ostringstream oss;

  oss << std::set<short>( {-1, 2} );
  
  TEST_EQUALITY_CONST( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<unsigned short>( {0, 10, 100} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<int>( {-11111, 0, 11111, 22222} );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<unsigned int>( {0, 10, 100, 1000, 10000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<long>( {-11111, 0, 11111, 22222} );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<unsigned long>( {0, 10, 100, 1000, 10000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<long long>( {-10000000000, 0, 10000000000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<unsigned long long>( {0, 1000000000, 1000000000000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<float>( {-1.0f, 0.0f, 1.0f} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<double>( {-1.0, 0.0, 1.0} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } );
  
  TEST_EQUALITY_CONST( oss.str(), "{ , T, e, g, i, n, r, s, t}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<std::string>( {"Test", "string"} );
  
  TEST_EQUALITY_CONST( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{-1, 2}, {0, 1}}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} );
  
  TEST_EQUALITY_CONST( oss.str(), 
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a set can be extracted from a stream
TEUCHOS_UNIT_TEST( Set, istream )
{
  std::istringstream iss( "{-1, 2}" );

  {
    std::set<short> test_set;

    iss >> test_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<short>({-1, 2}) );
  }

  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::set<unsigned short> test_set;

    iss >> test_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<unsigned short>({0, 10, 100}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::set<int> test_set;

    iss >> test_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<int>({-11111, 0, 11111, 22222}) );
  }
                      
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::set<unsigned> test_set;

    iss >> test_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<unsigned>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::set<long> test_set;

    iss >> test_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<long>({-11111, 0, 11111, 22222}) );
  }

  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::set<unsigned long> test_set;

    iss >> test_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<unsigned long>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::set<long long> test_set;

    iss >> test_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<long long>({-1000000000, 0, 1000000000}) );
  }

  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::set<unsigned long long> test_set;

    iss >> test_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<unsigned long long>({0, 1000000000, 10000000000}) );
  }

  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::set<float> test_set;

    iss >> test_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<float>({-1.0f, 0.0f, 1.0f}) );
  }

  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::set<double> test_set;

    iss >> test_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<double>({-1.0, 0.0, 1.0}) );
  }

  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::set<char> test_set;

    iss >> test_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::set<std::string> test_set;

    iss >> test_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, std::set<std::string>({"Test","string"}) );
  }

  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::set<std::pair<int,int> > test_set;

    iss >> test_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, (std::set<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::set<std::tuple<unsigned,double,long> > test_set;

    iss >> test_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, (std::set<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  iss.str( "{{0, 1}, {-1, 2}}, {{1, 0}, {2, -1}}" );
  iss.clear();

  {
    std::set<std::pair<long,long> > test_set;

    Utility::fromStream( iss, test_set, "," );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, (std::set<std::pair<long,long> >({std::make_pair(0l, 1l), std::make_pair(-1l, 2l)})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    iss >> test_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_set, (std::set<std::pair<long,long> >({std::make_pair(1l, 0l), std::make_pair(2l, -1l)})) );
  }
}

//---------------------------------------------------------------------------//
// Check that an unordered_set can be placed in a stream
TEUCHOS_UNIT_TEST( UnorderedSet, ostream )
{
  std::ostringstream oss;

  oss << std::unordered_set<short>( {-1, 2} );
  
  TEST_EQUALITY_CONST( oss.str(), "{2, -1}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<unsigned short>( {0, 10, 100} );
  
  TEST_EQUALITY_CONST( oss.str(), "{100, 0, 10}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<int>( {-11111, 0, 11111, 22222} );
  
  TEST_EQUALITY_CONST( oss.str(), "{22222, 11111, 0, -11111}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<unsigned int>( {0, 10, 100, 1000, 10000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10000, 100, 10, 1000}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<long>( {-11111, 0, 11111, 22222} );
  
  TEST_EQUALITY_CONST( oss.str(), "{22222, 11111, 0, -11111}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<unsigned long>( {0, 10, 100, 1000, 10000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10000, 100, 10, 1000}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<long long>( {-10000000000, 0, 10000000000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{10000000000, -10000000000, 0}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<unsigned long long>( {0, 1000000000, 1000000000000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{1000000000000, 0, 1000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<float>( {-1.0f, 0.0f, 1.0f} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{1.000000000e+00, -1.000000000e+00, 0.000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<double>( {-1.0, 0.0, 1.0} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{1.000000000000000000e+00, -1.000000000000000000e+00, 0.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } );
  
  TEST_EQUALITY_CONST( oss.str(), "{n, g, r,  , i, t, s, e, T}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<std::string>( {"Test", "string"} );
  
  TEST_EQUALITY_CONST( oss.str(), "{string, Test}" );
}

//---------------------------------------------------------------------------//
// Check that an unordered_set can be extracted from a stream
TEUCHOS_UNIT_TEST( UnorderedSet, istream )
{
  std::istringstream iss( "{-1, 2}" );

  {
    std::unordered_set<short> test_unordered_set;

    iss >> test_unordered_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<short>({-1, 2}) );
  }

  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::unordered_set<unsigned short> test_unordered_set;

    iss >> test_unordered_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<unsigned short>({0, 10, 100}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::unordered_set<int> test_unordered_set;

    iss >> test_unordered_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<int>({-11111, 0, 11111, 22222}) );
  }
                      
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::unordered_set<unsigned> test_unordered_set;

    iss >> test_unordered_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<unsigned>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::unordered_set<long> test_unordered_set;

    iss >> test_unordered_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<long>({-11111, 0, 11111, 22222}) );
  }

  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::unordered_set<unsigned long> test_unordered_set;

    iss >> test_unordered_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<unsigned long>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::unordered_set<long long> test_unordered_set;

    iss >> test_unordered_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<long long>({-1000000000, 0, 1000000000}) );
  }

  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::unordered_set<unsigned long long> test_unordered_set;

    iss >> test_unordered_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<unsigned long long>({0, 1000000000, 10000000000}) );
  }

  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::unordered_set<float> test_unordered_set;

    iss >> test_unordered_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<float>({-1.0f, 0.0f, 1.0f}) );
  }

  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::unordered_set<double> test_unordered_set;

    iss >> test_unordered_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<double>({-1.0, 0.0, 1.0}) );
  }

  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::unordered_set<char> test_unordered_set;

    iss >> test_unordered_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::unordered_set<std::string> test_unordered_set;

    iss >> test_unordered_set;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_set, std::unordered_set<std::string>({"Test","string"}) );
  }
}

//---------------------------------------------------------------------------//
// end tstSet.cpp
//---------------------------------------------------------------------------//
