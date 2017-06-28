//---------------------------------------------------------------------------//
//!
//! \file   tstStreamHelpers.cpp
//! \author Alex Robinson
//! \brief  Stream helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_StreamHelpers.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a deque can be placed in a stream
TEUCHOS_UNIT_TEST( StreamHelpers, deque_ostream )
{
  std::ostringstream oss;

  oss << std::deque<short>( {-1, 2} );
  
  TEST_EQUALITY_CONST( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<unsigned short>( {0, 10, 100} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<int>( {-11111, 0, 11111, 22222} );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<unsigned int>( {0, 10, 100, 1000, 10000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<long>( {-11111, 0, 11111, 22222} );
  
  TEST_EQUALITY_CONST( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<unsigned long>( {0, 10, 100, 1000, 10000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<long long>( {-10000000000, 0, 10000000000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<unsigned long long>( {0, 1000000000, 1000000000000} );
  
  TEST_EQUALITY_CONST( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<float>( {-1.0f, 0.0f, 1.0f} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  oss << std::deque<double>( {-1.0, 0.0, 1.0} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } );
  
  TEST_EQUALITY_CONST( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<std::string>( {"Test", "string"} );
  
  TEST_EQUALITY_CONST( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<std::pair<int, int>>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<std::tuple<unsigned, double, long>>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a deque can be extracted from a stream
TEUCHOS_UNIT_TEST( StreamHelpers, deque_istream )
{
  std::istringstream iss( "{-1, 2}" );

  {
    std::deque<short> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<short>({-1, 2}) );
  }

  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::deque<unsigned short> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned short>({0, 10, 100}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::deque<int> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<int>({-11111, 0, 11111, 22222}) );
  }
                      
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::deque<unsigned> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::deque<long> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<long>({-11111, 0, 11111, 22222}) );
  }

  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::deque<unsigned long> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned long>({0, 10, 100, 1000, 10000}) );
  }

  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::deque<long long> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<long long>({-1000000000, 0, 1000000000}) );
  }

  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::deque<unsigned long long> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned long long>({0, 1000000000, 10000000000}) );
  }

  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::deque<float> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<float>({-1.0f, 0.0f, 1.0f}) );
  }

  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::deque<double> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<double>({-1.0, 0.0, 1.0}) );
  }

  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::deque<char> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::deque<std::string> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<std::string>({"Test","string"}) );
  }

  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::deque<std::pair<int,int> > test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, (std::deque<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::deque<std::tuple<unsigned,double,long> > test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, (std::deque<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  iss.str( "{{0, 1}, {-1, 2}}, {{1, 0}, {2, -1}}" );
  iss.clear();

  {
    std::deque<std::pair<long,long> > test_deque;

    Utility::fromStream( iss, test_deque, "," );

    TEST_COMPARE_CONTAINERS( test_deque, (std::deque<std::pair<long,long> >({std::make_pair(0l, 1l), std::make_pair(-1l, 2l)})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, (std::deque<std::pair<long,long> >({std::make_pair(1l, 0l), std::make_pair(2l, -1l)})) );
  }
}

//---------------------------------------------------------------------------//
// Check that a set can be placed in a stream
TEUCHOS_UNIT_TEST( StreamHelpers, set_ostream )
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
TEUCHOS_UNIT_TEST( StreamHelpers, set_istream )
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
TEUCHOS_UNIT_TEST( StreamHelpers, unordered_set_ostream )
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
TEUCHOS_UNIT_TEST( StreamHelpers, unordered_set_istream )
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
// Check that a map can be placed in a stream
TEUCHOS_UNIT_TEST( StreamHelpers, map_ostream )
{
  std::ostringstream oss;

  oss << std::map<short, short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{-1, 2}, {0, 1}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<unsigned short, unsigned short>( {std::pair<unsigned short, unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 1}, {2, 10}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{-10, 0}, {10, -20}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 2}, {10, 100}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<long, long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{-1000000000, 1}, {1000000000, 2}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<unsigned long, unsigned long>( {std::make_pair(0l, 1000000000l), std::make_pair(1000000000l, 2000000000l)} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 1000000000}, {1000000000, 2000000000}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{-10000000000, 1}, {10000000000, 2}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{0, 10000000000}, {10000000000, 20000000000}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{-1, -1.000000000e+00}, {1, 1.000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<unsigned, double>( {std::make_pair(0, 0.0), std::make_pair(1, 1.0)} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{0, 0.000000000000000000e+00}, {1, 1.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<char, char>( {std::make_pair( 'a', 'b'), std::make_pair( 'A', 'B' )} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{A, B}, {a, b}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<std::string, std::string>( {std::make_pair( "Test String A", "Hello A" ), std::make_pair( "Test String B", "Hello B" )} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{Test String A, Hello A}, {Test String B, Hello B}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<int,std::pair<double,unsigned> >( {std::make_pair( -1, std::make_pair( 1.0, 0u ) ), std::make_pair( 1, std::make_pair( 0.0, 10u ) )} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{-1, {1.000000000000000000e+00, 0}}, {1, {0.000000000000000000e+00, 10}}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<unsigned, std::tuple<int, float, unsigned long> >( {std::make_pair( 0u, std::make_tuple( 1, -1.0f, 10ul ) ), std::make_pair( 1u, std::make_tuple( -1, 0.0, 100ul ) )} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{0, {1, -1.000000000e+00, 10}}, {1, {-1, 0.000000000e+00, 100}}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<long, std::vector<float> >( {std::make_pair( -1000000000l, std::vector<float>( {-1.0, 0.0, 1.0} ) ), std::make_pair( 1000000000l, std::vector<float>( {0.0} ) )} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{-1000000000, {-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}}, {1000000000, {0.000000000e+00}}}" );
}

//---------------------------------------------------------------------------//
// Check that a map can be extracted from a stream
TEUCHOS_UNIT_TEST( StreamHelpers, map_istream )
{
  std::istringstream iss( "{{-1, 2}, {0, 1}}" );

  {
    std::map<short,short> test_map;

    iss >> test_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<short,short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} )) );
  }

  iss.str( "{{0, 1}, {2, 10}}" );
  iss.clear();

  {
    std::map<unsigned short, unsigned short> test_map;

    iss >> test_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<unsigned short, unsigned short>( {std::pair<unsigned short,unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} )) );
  }

  iss.str( "{{-10, 0}, {10, -20}}" );
  iss.clear();

  {
    std::map<int, int> test_map;

    iss >> test_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} )) );
  }

  iss.str( "{{0, 2}, {10, 100}}" );
  iss.clear();

  {
    std::map<unsigned, unsigned> test_map;

    iss >> test_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} )) );
  }

  iss.str( "{{-1000000000, 1}, {1000000000, 2}}" );
  iss.clear();

  {
    std::map<long, long> test_map;

    iss >> test_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<long,long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} )) );
  }

  iss.str( "{{0, 1000000000}, {1000000000, 2000000000}}" );
  iss.clear();

  {
    std::map<unsigned long, unsigned long> test_map;

    iss >> test_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<unsigned long, unsigned long>( {std::make_pair(0ul, 1000000000ul), std::make_pair(1000000000ul, 2000000000ul)} )) );
  }

  iss.str( "{{-10000000000, 1}, {10000000000, 2}}" );
  iss.clear();

  {
    std::map<long long, long long> test_map;

    iss >> test_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} )) );
  }

  iss.str( "{{0, 10000000000}, {10000000000, 20000000000}}" );
  iss.clear();

  {
    std::map<unsigned long long, unsigned long long> test_map;

    iss >> test_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} )) );
  }

  iss.str( "{{-1, -1.0000000000e+00}, {1, 1.000000000e+00}}" );
  iss.clear();

  {
    std::map<int, float> test_map;

    iss >> test_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} )) );
  }

  iss.str( "{{0, 0.000000000000000000e+00}, {1, 1.000000000000000000e+00}}" );
  iss.clear();

  {
    std::map<unsigned, double> test_map;

    iss >> test_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<unsigned, double>( {std::make_pair(0u, 0.0), std::make_pair(1u, 1.0)} )) );
  }

  iss.str( "{{A, B}, {a, b}}" );
  iss.clear();

  {
    std::map<char, char> test_map;

    iss >> test_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<char, char>( {std::make_pair('A', 'B'), std::make_pair('a', 'b')} )) );
  }

  iss.str( "{{Test String A, Hello A}, {Test String B, Hello B}}" );
  iss.clear();

  {
    std::map<std::string, std::string> test_map;

    iss >> test_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<std::string, std::string>( {std::make_pair("Test String A", "Hello A"), std::make_pair("Test String B", "Hello B")} )) );
  }

  iss.str( "{{-1, {1.0, 0}}, {1, {0.0, 10}}}" );
  iss.clear();

  {
    std::map<int,std::pair<double,unsigned> > test_map;

    iss >> test_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<int,std::pair<double,unsigned> >( {std::make_pair(-1, std::make_pair(1.0, 0u)), std::make_pair(1, std::make_pair(0.0, 10u))} )) );
  }

  iss.str( "{{0, {1, -1.0, 10}}, {1, {-1, 0.0, 100}}}" );
  iss.clear();

  {
    std::map<unsigned,std::tuple<int,float,unsigned long> > test_map;

    iss >> test_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<unsigned,std::tuple<int,float,unsigned long> >( {std::make_pair(0u, std::make_tuple(1, -1.0f, 10ul)), std::make_pair(1u, std::make_tuple(-1, 0.0f, 100ul))} )) );
  }

  iss.str( "{{-10, Test String A}, {201, Test String B}}, {{0, Test String C}, {333, Test String D}}" );
  iss.clear();

  {
    std::map<int, std::string> test_map;
    
    Utility::fromStream( iss, test_map, "," );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<int, std::string>({std::make_pair(-10, "Test String A"), std::make_pair(201, "Test String B")})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    iss >> test_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_map, (std::map<int, std::string>({std::make_pair(0, "Test String C"), std::make_pair(333, "Test String D")})) );
  }                                
}

//---------------------------------------------------------------------------//
// Check that an unordered_map can be placed in a stream
TEUCHOS_UNIT_TEST( StreamHelpers, unordered_map_ostream )
{
  std::ostringstream oss;

  oss << std::unordered_map<short, short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<unsigned short, unsigned short>( {std::pair<unsigned short, unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{2, 10}, {0, 1}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{10, -20}, {-10, 0}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{10, 100}, {0, 2}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<long, long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{1000000000, 2}, {-1000000000, 1}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<unsigned long, unsigned long>( {std::make_pair(0l, 1000000000l), std::make_pair(1000000000l, 2000000000l)} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{1000000000, 2000000000}, {0, 1000000000}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} );
  
  TEST_EQUALITY_CONST( oss.str(), "{{10000000000, 2}, {-10000000000, 1}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{10000000000, 20000000000}, {0, 10000000000}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{1, 1.000000000e+00}, {-1, -1.000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<unsigned, double>( {std::make_pair(0, 0.0), std::make_pair(1, 1.0)} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{1, 1.000000000000000000e+00}, {0, 0.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<char, char>( {std::make_pair( 'a', 'b'), std::make_pair( 'A', 'B' )} );

  TEST_EQUALITY_CONST( oss.str(), "{{A, B}, {a, b}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<std::string, std::string>( {std::make_pair( "Test String A", "Hello A" ), std::make_pair( "Test String B", "Hello B" )} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{Test String B, Hello B}, {Test String A, Hello A}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<int,std::pair<double,unsigned> >( {std::make_pair( -1, std::make_pair( 1.0, 0u ) ), std::make_pair( 1, std::make_pair( 0.0, 10u ) )} );
  
  TEST_EQUALITY_CONST( oss.str(), 
                       "{{1, {0.000000000000000000e+00, 10}}, {-1, {1.000000000000000000e+00, 0}}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<unsigned, std::tuple<int, float, unsigned long> >( {std::make_pair( 0u, std::make_tuple( 1, -1.0f, 10ul ) ), std::make_pair( 1u, std::make_tuple( -1, 0.0, 100ul ) )} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{1, {-1, 0.000000000e+00, 100}}, {0, {1, -1.000000000e+00, 10}}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<long, std::vector<float> >( {std::make_pair( -1000000000l, std::vector<float>( {-1.0, 0.0, 1.0} ) ), std::make_pair( 1000000000l, std::vector<float>( {0.0} ) )} );
  
  TEST_EQUALITY_CONST( oss.str(),
                       "{{1000000000, {0.000000000e+00}}, {-1000000000, {-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}}}" );
}

//---------------------------------------------------------------------------//
// Check that an unordered_map can be extracted from a stream
TEUCHOS_UNIT_TEST( StreamHelpers, unordered_map_istream )
{
  std::istringstream iss( "{{-1, 2}, {0, 1}}" );

  {
    std::unordered_map<short,short> test_unordered_map;

    iss >> test_unordered_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<short,short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} )) );
  }

  iss.str( "{{0, 1}, {2, 10}}" );
  iss.clear();

  {
    std::unordered_map<unsigned short, unsigned short> test_unordered_map;

    iss >> test_unordered_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<unsigned short, unsigned short>( {std::pair<unsigned short,unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} )) );
  }

  iss.str( "{{-10, 0}, {10, -20}}" );
  iss.clear();

  {
    std::unordered_map<int, int> test_unordered_map;

    iss >> test_unordered_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} )) );
  }

  iss.str( "{{0, 2}, {10, 100}}" );
  iss.clear();

  {
    std::unordered_map<unsigned, unsigned> test_unordered_map;

    iss >> test_unordered_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} )) );
  }

  iss.str( "{{-1000000000, 1}, {1000000000, 2}}" );
  iss.clear();

  {
    std::unordered_map<long, long> test_unordered_map;

    iss >> test_unordered_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<long,long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} )) );
  }

  iss.str( "{{0, 1000000000}, {1000000000, 2000000000}}" );
  iss.clear();

  {
    std::unordered_map<unsigned long, unsigned long> test_unordered_map;

    iss >> test_unordered_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<unsigned long, unsigned long>( {std::make_pair(0ul, 1000000000ul), std::make_pair(1000000000ul, 2000000000ul)} )) );
  }

  iss.str( "{{-10000000000, 1}, {10000000000, 2}}" );
  iss.clear();

  {
    std::unordered_map<long long, long long> test_unordered_map;

    iss >> test_unordered_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} )) );
  }

  iss.str( "{{0, 10000000000}, {10000000000, 20000000000}}" );
  iss.clear();

  {
    std::unordered_map<unsigned long long, unsigned long long> test_unordered_map;

    iss >> test_unordered_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} )) );
  }

  iss.str( "{{-1, -1.0000000000e+00}, {1, 1.000000000e+00}}" );
  iss.clear();

  {
    std::unordered_map<int, float> test_unordered_map;

    iss >> test_unordered_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} )) );
  }

  iss.str( "{{0, 0.000000000000000000e+00}, {1, 1.000000000000000000e+00}}" );
  iss.clear();

  {
    std::unordered_map<unsigned, double> test_unordered_map;

    iss >> test_unordered_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<unsigned, double>( {std::make_pair(0u, 0.0), std::make_pair(1u, 1.0)} )) );
  }

  iss.str( "{{A, B}, {a, b}}" );
  iss.clear();

  {
    std::unordered_map<char, char> test_unordered_map;

    iss >> test_unordered_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<char, char>( {std::make_pair('A', 'B'), std::make_pair('a', 'b')} )) );
  }

  iss.str( "{{Test String A, Hello A}, {Test String B, Hello B}}" );
  iss.clear();

  {
    std::unordered_map<std::string, std::string> test_unordered_map;

    iss >> test_unordered_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<std::string, std::string>( {std::make_pair("Test String A", "Hello A"), std::make_pair("Test String B", "Hello B")} )) );
  }

  iss.str( "{{-1, {1.0, 0}}, {1, {0.0, 10}}}" );
  iss.clear();

  {
    std::unordered_map<int,std::pair<double,unsigned> > test_unordered_map;

    iss >> test_unordered_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<int,std::pair<double,unsigned> >( {std::make_pair(-1, std::make_pair(1.0, 0u)), std::make_pair(1, std::make_pair(0.0, 10u))} )) );
  }

  iss.str( "{{0, {1, -1.0, 10}}, {1, {-1, 0.0, 100}}}" );
  iss.clear();

  {
    std::unordered_map<unsigned,std::tuple<int,float,unsigned long> > test_unordered_map;

    iss >> test_unordered_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<unsigned,std::tuple<int,float,unsigned long> >( {std::make_pair(0u, std::make_tuple(1, -1.0f, 10ul)), std::make_pair(1u, std::make_tuple(-1, 0.0f, 100ul))} )) );
  }

  iss.str( "{{-10, Test String A}, {201, Test String B}}, {{0, Test String C}, {333, Test String D}}" );
  iss.clear();

  {
    std::unordered_map<int, std::string> test_unordered_map;
    
    Utility::fromStream( iss, test_unordered_map, "," );

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<int, std::string>({std::make_pair(-10, "Test String A"), std::make_pair(201, "Test String B")})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    iss >> test_unordered_map;

    TEST_COMPARE_UNORDERED_CONTAINERS( test_unordered_map, (std::unordered_map<int, std::string>({std::make_pair(0, "Test String C"), std::make_pair(333, "Test String D")})) );
  }                             
}

//---------------------------------------------------------------------------//
// end tstStreamHelpers.cpp
//---------------------------------------------------------------------------//
