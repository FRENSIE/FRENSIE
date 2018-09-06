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

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/insert_range.hpp>

// FRENSIE Includes
#include "Utility_Set.hpp"
#include "Utility_Tuple.hpp"

//---------------------------------------------------------------------------//
// Testing Macros
//---------------------------------------------------------------------------//
#define TEST_COMPARE_UNORDERED_CONTAINERS( left_container, right_container )      \
  {                                                                     \
    const decltype(left_container)& left_container_ref = left_container; \
    const decltype(right_container)& right_container_ref = right_container; \
                                                                        \
    size_t left_container_size =                                        \
      std::distance( left_container_ref.begin(), left_container_ref.end() ); \
    size_t right_container_size =                                       \
      std::distance( right_container_ref.begin(), right_container_ref.end() );\
                                                                        \
    BOOST_REQUIRE_EQUAL( left_container_size, right_container_size );   \
                                                                        \
    auto left_container_it = left_container_ref.begin();                \
    auto left_container_end = left_container_ref.end();                 \
                                                                        \
    while( left_container_it != left_container_end )                   \
    {                                                                \
      BOOST_CHECK( std::find( right_container_ref.begin(),           \
                              right_container_ref.end(),             \
                              *left_container_it ) !=                \
                   right_container_ref.end() );                      \
      ++left_container_it;                                           \
    }                                                                \
  }

//---------------------------------------------------------------------------//
// Template Test Types
//---------------------------------------------------------------------------//

typedef boost::mpl::list<char,signed char,unsigned char,short,unsigned short,int,unsigned int,long,unsigned long,long long,unsigned long long,float,double> TestTypes;

template<typename Policy>
struct TypeList
{
  typedef boost::mpl::list<std::tuple<Policy,char>,std::tuple<Policy,signed char>,std::tuple<Policy,unsigned char>,std::tuple<Policy,short>,std::tuple<Policy,unsigned short>,std::tuple<Policy,int>,std::tuple<Policy,unsigned int>,std::tuple<Policy,long>,std::tuple<Policy,unsigned long>,std::tuple<Policy,long long>,std::tuple<Policy,unsigned long long>,std::tuple<Policy,float>,std::tuple<Policy,double> > type;
};

template<typename... TypeLists>
struct MergeTypeLists
{ /* ... */ };

template<typename FrontList, typename... TypeLists>
struct MergeTypeLists<FrontList,TypeLists...>
{
private:
  typedef typename MergeTypeLists<TypeLists...>::type BackMergedListType;

public:
  typedef typename boost::mpl::insert_range<FrontList,typename boost::mpl::end<FrontList>::type,BackMergedListType>::type type;
};

template<typename FrontList>
struct MergeTypeLists<FrontList>
{ 
  typedef FrontList type;
};

typedef typename MergeTypeLists<typename TypeList<Utility::EqualityComparisonPolicy>::type, typename TypeList<Utility::InequalityComparisonPolicy>::type>::type TestPolicyTypes;

//---------------------------------------------------------------------------//
// Set Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( Set )

//---------------------------------------------------------------------------//
// Check that a set can be converted to a string
BOOST_AUTO_TEST_CASE( toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( std::set<short>( {-1, 2} ) ),
                       "{-1, 2}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::set<unsigned short>( {0, 10, 100} ) ),
                       "{0, 10, 100}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::set<int>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::set<unsigned int>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::set<long>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::set<unsigned long>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::set<long long>( {-10000000000, 0, 10000000000} ) ),
                       "{-10000000000, 0, 10000000000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::set<unsigned long long>( {0, 1000000000, 1000000000000} ) ),
                       "{0, 1000000000, 1000000000000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::set<float>( {-1.0f, 0.0f, 1.0f} ) ),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::set<double>( {-1.0, 0.0, 1.0} ) ),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::set<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) ),
                       "{ , T, e, g, i, n, r, s, t}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::set<std::string>( {"Test", "string"} ) ),
                       "{Test, string}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::set<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) ),
                       "{{-1, 2}, {0, 1}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::set<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) ),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a set can be placed in a stream
BOOST_AUTO_TEST_CASE( toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::set<short>( {-1, 2} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<unsigned short>( {0, 10, 100} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<int>( {-11111, 0, 11111, 22222} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<unsigned int>( {0, 10, 100, 1000, 10000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<long>( {-11111, 0, 11111, 22222} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<unsigned long>( {0, 10, 100, 1000, 10000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<long long>( {-10000000000, 0, 10000000000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<unsigned long long>( {0, 1000000000, 1000000000000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<float>( {-1.0f, 0.0f, 1.0f} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<double>( {-1.0, 0.0, 1.0} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{ , T, e, g, i, n, r, s, t}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<std::string>( {"Test", "string"} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{-1, 2}, {0, 1}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::set<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), 
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a set iterator can be converted to a string
BOOST_AUTO_TEST_CASE( toString_iterator )
{
  std::set<int> int_set( {-1, 0, 1} );

  std::string iterator_string = Utility::toString( int_set.begin() );
  
  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( int_set.cbegin() );
  
  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( int_set.rbegin() );
  
  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( int_set.crbegin() );
  
  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  std::set<std::string> string_set( {"-1", "0", "1"} );

  iterator_string = Utility::toString( string_set.begin() );
  
  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( string_set.cbegin() );
  
  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( string_set.rbegin() );
  
  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( string_set.crbegin() );
  
  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );
}

//---------------------------------------------------------------------------//
// Check that a set iterator can be converted to a string
BOOST_AUTO_TEST_CASE( toStream_iterator )
{
  std::set<int> int_set( {-1, 0, 1} );

  std::ostringstream oss;

  Utility::toStream( oss, int_set.begin() );
  
  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  Utility::toStream( oss, int_set.cbegin() );
  
  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  Utility::toStream( oss, int_set.rbegin() );
  
  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  Utility::toStream( oss, int_set.crbegin() );
  
  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  std::set<std::string> string_set( {"-1", "0", "1"} );

  Utility::toStream( oss, string_set.begin() );
  
  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  Utility::toStream( oss, string_set.cbegin() );
  
  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  Utility::toStream( oss, string_set.rbegin() );
  
  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  Utility::toStream( oss, string_set.crbegin() );
  
  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that a set can be created from a string
BOOST_AUTO_TEST_CASE( fromString )
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
BOOST_AUTO_TEST_CASE( fromStream )
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
// Check that a set can be placed in a stream
BOOST_AUTO_TEST_CASE( ostream )
{
  std::ostringstream oss;

  oss << std::set<short>( {-1, 2} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<unsigned short>( {0, 10, 100} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<int>( {-11111, 0, 11111, 22222} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<unsigned int>( {0, 10, 100, 1000, 10000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<long>( {-11111, 0, 11111, 22222} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<unsigned long>( {0, 10, 100, 1000, 10000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<long long>( {-10000000000, 0, 10000000000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<unsigned long long>( {0, 1000000000, 1000000000000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<float>( {-1.0f, 0.0f, 1.0f} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<double>( {-1.0, 0.0, 1.0} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } );
  
  BOOST_CHECK_EQUAL( oss.str(), "{ , T, e, g, i, n, r, s, t}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<std::string>( {"Test", "string"} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{-1, 2}, {0, 1}}" );

  oss.str( "" );
  oss.clear();

  oss << std::set<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} );
  
  BOOST_CHECK_EQUAL( oss.str(), 
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a set can be extracted from a stream
BOOST_AUTO_TEST_CASE( istream )
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
// Check that the correct comparison policies are allowed for sets
BOOST_AUTO_TEST_CASE_TEMPLATE( IsComparisonAllowed, T, TestTypes )
{
  typedef std::set<T> Set;

  BOOST_CHECK( Utility::ComparisonTraits<Set>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<Set>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Set>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Set>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Set>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Set>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Set>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Set>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<const Set>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const Set>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Set>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Set>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Set>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Set>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Set>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Set>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );
}

//---------------------------------------------------------------------------//
// Check that sets can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, PolicyTypePair, TestPolicyTypes )
{
  typedef typename Utility::TupleElement<0,PolicyTypePair>::type Policy;
  typedef typename Utility::TupleElement<1,PolicyTypePair>::type T;

  std::set<T> left_set({T(0), T(1), T(2)});
  std::set<T> right_set({T(0), T(1), T(2)});

  std::ostringstream oss;

  // No details logging
  bool compare_result = Utility::compare<Policy,0>( left_set, "lhs",
                                                    right_set, "rhs",
                                                    oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( !compare_result );
  else
    BOOST_CHECK( compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_set, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_set, "lhs",
                                               {}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {T(1),T(10),T(100)}, "lhs",
                                               right_set, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_set, "lhs",
                                               {T(1),T(10),T(100)}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  // Details logging
  T tol( 1e-6 );

  compare_result = Utility::compare<Policy,0>( left_set, "lhs",
                                               right_set, "rhs",
                                               oss, tol, true );

  std::string expected_details =
    Utility::createComparisonHeader<Policy,0>( left_set, "lhs",
                                               right_set, "rhs",
                                               tol );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "failed!\n";

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                left_set.size(), "lhs", true,
                                                right_set.size(), "rhs", true,
                                                ".size()", local_oss, true );
    auto left_set_it = left_set.begin();
    auto left_set_end = left_set.end();

    while( left_set_it != left_set_end )
    {
      Utility::ComparisonTraits<bool>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                                                                         true, "lhs", true,
                                                                                                         true, "rhs", true,
                                                                                                         std::string(" contains ") + Utility::toString(*left_set_it),
                                                                                                         local_oss, true, tol );
      ++left_set_it;
    }

    expected_details += "passed\n";
    expected_details += local_oss.str();

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  
  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( {T(1), T(10), T(100)}, "lhs",
                                               right_set, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {T(1), T(10), T(100)}, "lhs",
                                               right_set, "rhs",
                                               tol );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "passed\n";

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                left_set.size(), "lhs", false,
                                                right_set.size(), "rhs", true,
                                                ".size()", local_oss, true );
    auto right_set_it = right_set.begin();
    auto right_set_end = right_set.end();

    while( right_set_it != right_set_end )
    {
      Utility::ComparisonTraits<bool>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
       *right_set_it==1|| *right_set_it==10|| *right_set_it==100, "lhs", true,
       true, "rhs", true,
       std::string(" contains ") + Utility::toString(*right_set_it),
       local_oss, true, tol );
      
      ++right_set_it;
    }

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  
  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_set, "lhs",
                                               {T(1), T(10), T(100)}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_set, "lhs",
                                               {T(1), T(10), T(100)}, "rhs",
                                               tol );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "passed\n";

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                left_set.size(), "lhs", true,
                                                right_set.size(), "rhs", false,
                                                ".size()", local_oss, true );
    auto left_set_it = left_set.begin();
    auto left_set_end = left_set.end();

    while( left_set_it != left_set_end )
    {
      Utility::ComparisonTraits<bool>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
       true, "lhs", true,
       *left_set_it==1|| *left_set_it==10|| *left_set_it==100, "rhs", true,
       std::string(" contains ") + Utility::toString(*left_set_it),
       local_oss, true, tol );
      
      ++left_set_it;
    }

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  
  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_set, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {}, "lhs",
                                               right_set, "rhs",
                                               tol );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "passed\n";

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                0, "lhs", false,
                                                right_set.size(), "rhs", true,
                                                ".size()", local_oss, true );

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  
  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_set, "lhs",
                                               {}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_set, "lhs",
                                               {}, "rhs",
                                               tol );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "passed\n";

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                left_set.size(), "lhs", true,
                                                0, "rhs", false,
                                                ".size()", local_oss, true );

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// Unordered Set Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( UnorderedSet)

//---------------------------------------------------------------------------//
// Check that a unordered_set can be converted to a string
BOOST_AUTO_TEST_CASE( toString )
{
  std::string set_string =
    Utility::toString( std::unordered_set<short>( {-1, 2} ) );
  BOOST_CHECK( set_string == "{-1, 2}" || set_string == "{2, -1}" );

  set_string = Utility::toString( std::unordered_set<unsigned short>( {0, 10, 100} ) );
  BOOST_CHECK( set_string == "{0, 10, 100}" ||
               set_string == "{100, 0, 10}" ||
               set_string == "{10, 100, 0}" ||
               set_string == "{0, 100, 10}" ||
               set_string == "{100, 10, 0}" ||
               set_string ==  "{10, 0, 100}" );

  set_string = Utility::toString( std::unordered_set<int>( {-11111, 0} ) );
  BOOST_CHECK( set_string == "{-11111, 0}" || set_string == "{0, -11111}" );

  set_string = Utility::toString( std::unordered_set<unsigned int>( {1000, 10000} ) );
  BOOST_CHECK( set_string == "{1000, 10000}" || "{10000, 1000}" );

  set_string = Utility::toString( std::unordered_set<long>( {11111, 22222} ) );
  BOOST_CHECK( set_string == "{11111, 22222}" ||
               set_string == "{22222, 11111}" );

  set_string = Utility::toString( std::unordered_set<unsigned long>( {10, 10000} ) );
  BOOST_CHECK( set_string == "{10, 10000}" || set_string == "{10000, 10}" );

  set_string = Utility::toString( std::unordered_set<long long>( {-10000000000, 10000000000} ) );
  BOOST_CHECK( set_string == "{-10000000000, 10000000000}" ||
               set_string == "{10000000000, -10000000000}" );

  set_string = Utility::toString( std::unordered_set<unsigned long long>( {100, 1000000000000} ) );
  BOOST_CHECK( set_string == "{100, 1000000000000}" ||
               set_string == "{1000000000000, 100}" );

  set_string = Utility::toString( std::unordered_set<float>( {-1.0f, 1.0f} ) );
  BOOST_CHECK( set_string == "{-1.000000000e+00, 1.000000000e+00}" ||
               set_string == "{1.000000000e+00, -1.000000000e+00}" );

  set_string = Utility::toString( std::unordered_set<double>( {-1.0, 1.0} ) );
  BOOST_CHECK( set_string == "{-1.000000000000000000e+00, 1.000000000000000000e+00}" ||
               set_string == "{1.000000000000000000e+00, -1.000000000000000000e+00}" );

  set_string = Utility::toString( std::unordered_set<char>( {'a', 'b'} ) );
  BOOST_CHECK( set_string == "{a, b}" || set_string == "{b, a}" );

  set_string = Utility::toString( std::unordered_set<std::string>( {"Test", "string"} ) );
  BOOST_CHECK( set_string == "{Test, string}" || set_string == "{string, Test}" );
}

//---------------------------------------------------------------------------//
// Check that a unordered_set can be placed in a stream
BOOST_AUTO_TEST_CASE( toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::unordered_set<short>( {-1, 2} ) );
  
  BOOST_CHECK( oss.str() == "{-1, 2}" || oss.str() == "{2, -1}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<unsigned short>( {0, 10, 100} ) );
  BOOST_CHECK( oss.str() == "{0, 10, 100}" ||
               oss.str() == "{100, 0, 10}" ||
               oss.str() == "{10, 100, 0}" ||
               oss.str() == "{0, 100, 10}" ||
               oss.str() == "{100, 10, 0}" ||
               oss.str() ==  "{10, 0, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<int>( {-11111, 0} ) );
  BOOST_CHECK( oss.str() == "{-11111, 0}" || oss.str() == "{0, -11111}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<unsigned int>( {1000, 10000} ) );
  BOOST_CHECK( oss.str() == "{1000, 10000}" || "{10000, 1000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<long>( {11111, 22222} ) );
  BOOST_CHECK( oss.str() == "{11111, 22222}" ||
               oss.str() == "{22222, 11111}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<unsigned long>( {10, 10000} ) );
  BOOST_CHECK( oss.str() == "{10, 10000}" || oss.str() == "{10000, 10}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<long long>( {-10000000000, 10000000000} ) );
  BOOST_CHECK( oss.str() == "{-10000000000, 10000000000}" ||
               oss.str() == "{10000000000, -10000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<unsigned long long>( {100, 1000000000000} ) );
  BOOST_CHECK( oss.str() == "{100, 1000000000000}" ||
               oss.str() == "{1000000000000, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<float>( {-1.0f, 1.0f} ) );
  BOOST_CHECK( oss.str() == "{-1.000000000e+00, 1.000000000e+00}" ||
               oss.str() == "{1.000000000e+00, -1.000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<double>( {-1.0, 1.0} ) );
  BOOST_CHECK( oss.str() == "{-1.000000000000000000e+00, 1.000000000000000000e+00}" ||
               oss.str() == "{1.000000000000000000e+00, -1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<char>( {'a', 'b'} ) );
  BOOST_CHECK( oss.str() == "{a, b}" || oss.str() == "{b, a}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_set<std::string>( {"Test", "string"} ) );
  BOOST_CHECK( oss.str() == "{Test, string}" || oss.str() == "{string, Test}" );
}

//---------------------------------------------------------------------------//
// Check that an unordered_set iterator can be converted to a string
BOOST_AUTO_TEST_CASE( toString_iterator )
{
  std::unordered_set<int> int_set( {-1, 0, 1} );

  std::string iterator_string = Utility::toString( int_set.begin() );
  
  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( int_set.cbegin() );
  
  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  std::unordered_set<std::string> string_set( {"-1", "0", "1"} );

  iterator_string = Utility::toString( string_set.begin() );
  
  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( string_set.cbegin() );
  
  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );
}

//---------------------------------------------------------------------------//
// Check that a unordered_set iterator can be converted to a string
BOOST_AUTO_TEST_CASE( toStream_iterator )
{
  std::unordered_set<int> int_set( {-1, 0, 1} );

  std::ostringstream oss;

  Utility::toStream( oss, int_set.begin() );
  
  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  Utility::toStream( oss, int_set.cbegin() );
  
  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  std::unordered_set<std::string> string_set( {"-1", "0", "1"} );

  Utility::toStream( oss, string_set.begin() );
  
  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  Utility::toStream( oss, string_set.cbegin() );
  
  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that an unordered_set can be created from a string
BOOST_AUTO_TEST_CASE( fromString )
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
BOOST_AUTO_TEST_CASE( fromStream )
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
// Check that an unordered_set can be placed in a stream
BOOST_AUTO_TEST_CASE( ostream )
{
  std::ostringstream oss;

  oss << std::unordered_set<short>( {-1, 2} );
  BOOST_CHECK( oss.str() == "{-1, 2}" || oss.str() == "{2, -1}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<unsigned short>( {0, 10, 100} );
  BOOST_CHECK( oss.str() == "{0, 10, 100}" ||
               oss.str() == "{100, 0, 10}" ||
               oss.str() == "{10, 100, 0}" ||
               oss.str() == "{0, 100, 10}" ||
               oss.str() == "{100, 10, 0}" ||
               oss.str() ==  "{10, 0, 100}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<int>( {-11111, 0} );
  BOOST_CHECK( oss.str() == "{-11111, 0}" || oss.str() == "{0, -11111}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<unsigned int>( {1000, 10000} );
  BOOST_CHECK( oss.str() == "{1000, 10000}" || "{10000, 1000}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<long>( {11111, 22222} );
  BOOST_CHECK( oss.str() == "{11111, 22222}" ||
               oss.str() == "{22222, 11111}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<unsigned long>( {10, 10000} );
  BOOST_CHECK( oss.str() == "{10, 10000}" || oss.str() == "{10000, 10}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<long long>( {-10000000000, 10000000000} );
  BOOST_CHECK( oss.str() == "{-10000000000, 10000000000}" ||
               oss.str() == "{10000000000, -10000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<unsigned long long>( {100, 1000000000000} );
  BOOST_CHECK( oss.str() == "{100, 1000000000000}" ||
               oss.str() == "{1000000000000, 100}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<float>( {-1.0f, 1.0f} );
  BOOST_CHECK( oss.str() == "{-1.000000000e+00, 1.000000000e+00}" ||
               oss.str() == "{1.000000000e+00, -1.000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<double>( {-1.0, 1.0} );
  BOOST_CHECK( oss.str() == "{-1.000000000000000000e+00, 1.000000000000000000e+00}" ||
               oss.str() == "{1.000000000000000000e+00, -1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<char>( {'a', 'b'} );
  BOOST_CHECK( oss.str() == "{a, b}" || oss.str() == "{b, a}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_set<std::string>( {"Test", "string"} );
  BOOST_CHECK( oss.str() == "{Test, string}" || oss.str() == "{string, Test}" );
}

//---------------------------------------------------------------------------//
// Check that an unordered_set can be extracted from a stream
BOOST_AUTO_TEST_CASE( istream )
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
// Check that the correct comparison policies are allowed for unordered sets
BOOST_AUTO_TEST_CASE_TEMPLATE( IsComparisonAllowed, T, TestTypes )
{
  typedef std::unordered_set<T> Set;

  BOOST_CHECK( Utility::ComparisonTraits<Set>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<Set>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Set>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Set>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Set>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Set>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Set>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Set>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<const Set>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const Set>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Set>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Set>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Set>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Set>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Set>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Set>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );
}

//---------------------------------------------------------------------------//
// Check that sets can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, PolicyTypePair, TestPolicyTypes )
{
  typedef typename Utility::TupleElement<0,PolicyTypePair>::type Policy;
  typedef typename Utility::TupleElement<1,PolicyTypePair>::type T;

  std::unordered_set<T> left_set({T(0), T(1), T(2)});
  std::unordered_set<T> right_set({T(0), T(1), T(2)});

  std::ostringstream oss;

  // No details logging
  bool compare_result = Utility::compare<Policy,0>( left_set, "lhs",
                                                    right_set, "rhs",
                                                    oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( !compare_result );
  else
    BOOST_CHECK( compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_set, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_set, "lhs",
                                               {}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {T(1),T(10),T(100)}, "lhs",
                                               right_set, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_set, "lhs",
                                               {T(1),T(10),T(100)}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  // Details logging
  T tol( 1e-6 );

  compare_result = Utility::compare<Policy,0>( left_set, "lhs",
                                               right_set, "rhs",
                                               oss, tol, true );

  std::string expected_details =
    Utility::createComparisonHeader<Policy,0>( left_set, "lhs",
                                               right_set, "rhs",
                                               tol );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "failed!\n";

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                left_set.size(), "lhs", true,
                                                right_set.size(), "rhs", true,
                                                ".size()", local_oss, true );
    auto left_set_it = left_set.begin();
    auto left_set_end = left_set.end();

    while( left_set_it != left_set_end )
    {
      Utility::ComparisonTraits<bool>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                                                                         true, "lhs", true,
                                                                                                         true, "rhs", true,
                                                                                                         std::string(" contains ") + Utility::toString(*left_set_it),
                                                                                                         local_oss, true, tol );
      ++left_set_it;
    }

    expected_details += "passed\n";
    expected_details += local_oss.str();

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  
  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( {T(1), T(10), T(100)}, "lhs",
                                               right_set, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {T(1), T(10), T(100)}, "lhs",
                                               right_set, "rhs",
                                               tol );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "passed\n";

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                left_set.size(), "lhs", false,
                                                right_set.size(), "rhs", true,
                                                ".size()", local_oss, true );
    auto right_set_it = right_set.begin();
    auto right_set_end = right_set.end();

    while( right_set_it != right_set_end )
    {
      Utility::ComparisonTraits<bool>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
       *right_set_it==1|| *right_set_it==10|| *right_set_it==100, "lhs", true,
       true, "rhs", true,
       std::string(" contains ") + Utility::toString(*right_set_it),
       local_oss, true, tol );
      
      ++right_set_it;
    }

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  
  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_set, "lhs",
                                               {T(1), T(10), T(100)}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_set, "lhs",
                                               {T(1), T(10), T(100)}, "rhs",
                                               tol );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "passed\n";

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                left_set.size(), "lhs", true,
                                                right_set.size(), "rhs", false,
                                                ".size()", local_oss, true );
    auto left_set_it = left_set.begin();
    auto left_set_end = left_set.end();

    while( left_set_it != left_set_end )
    {
      Utility::ComparisonTraits<bool>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
       true, "lhs", true,
       *left_set_it==1|| *left_set_it==10|| *left_set_it==100, "rhs", true,
       std::string(" contains ") + Utility::toString(*left_set_it),
       local_oss, true, tol );
      
      ++left_set_it;
    }

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  
  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_set, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {}, "lhs",
                                               right_set, "rhs",
                                               tol );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "passed\n";

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                0, "lhs", false,
                                                right_set.size(), "rhs", true,
                                                ".size()", local_oss, true );

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  
  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_set, "lhs",
                                               {}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_set, "lhs",
                                               {}, "rhs",
                                               tol );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
  {
    expected_details += "passed\n";

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  else
  {
    std::ostringstream local_oss;

    Utility::ComparisonTraits<size_t>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                left_set.size(), "lhs", true,
                                                0, "rhs", false,
                                                ".size()", local_oss, true );

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// end tstSet.cpp
//---------------------------------------------------------------------------//
