//---------------------------------------------------------------------------//
//!
//! \file   tstMap.cpp
//! \author Alex Robinson
//! \brief  Map helper function unit tests
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
#include "Utility_Map.hpp"
#include "Utility_Vector.hpp"
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
// Map Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( Map )

//---------------------------------------------------------------------------//
// Check that a map can be converted to a string
BOOST_AUTO_TEST_CASE( toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( std::map<short, short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} ) ),
                       "{{-1, 2}, {0, 1}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::map<unsigned short, unsigned short>( {std::pair<unsigned short, unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} ) ),
                       "{{0, 1}, {2, 10}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} ) ),
                       "{{-10, 0}, {10, -20}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} ) ),
                       "{{0, 2}, {10, 100}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::map<long, long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} ) ),
                       "{{-1000000000, 1}, {1000000000, 2}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::map<unsigned long, unsigned long>( {std::make_pair(0l, 1000000000l), std::make_pair(1000000000l, 2000000000l)} ) ),
                       "{{0, 1000000000}, {1000000000, 2000000000}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} ) ),
                       "{{-10000000000, 1}, {10000000000, 2}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} ) ),
                       "{{0, 10000000000}, {10000000000, 20000000000}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} ) ),
                       "{{-1, -1.000000000e+00}, {1, 1.000000000e+00}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::map<unsigned, double>( {std::make_pair(0, 0.0), std::make_pair(1, 1.0)} ) ),
                       "{{0, 0.000000000000000000e+00}, {1, 1.000000000000000000e+00}}" );

  BOOST_CHECK_EQUAL( Utility::toString( std::map<char, char>( {std::make_pair( 'a', 'b'), std::make_pair( 'A', 'B' )} ) ),
                       "{{A, B}, {a, b}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::map<std::string, std::string>( {std::make_pair( "Test String A", "Hello A" ), std::make_pair( "Test String B", "Hello B" )} ) ),
                       "{{Test String A, Hello A}, {Test String B, Hello B}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::map<int,std::pair<double,unsigned> >( {std::make_pair( -1, std::make_pair( 1.0, 0u ) ), std::make_pair( 1, std::make_pair( 0.0, 10u ) )} ) ),
                       "{{-1, {1.000000000000000000e+00, 0}}, {1, {0.000000000000000000e+00, 10}}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::map<unsigned, std::tuple<int, float, unsigned long> >( {std::make_pair( 0u, std::make_tuple( 1, -1.0f, 10ul ) ), std::make_pair( 1u, std::make_tuple( -1, 0.0, 100ul ) )} ) ),
                       "{{0, {1, -1.000000000e+00, 10}}, {1, {-1, 0.000000000e+00, 100}}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::map<long, std::vector<float> >( {std::make_pair( -1000000000l, std::vector<float>( {-1.0, 0.0, 1.0} ) ), std::make_pair( 1000000000l, std::vector<float>( {0.0} ) )} ) ),
                       "{{-1000000000, {-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}}, {1000000000, {0.000000000e+00}}}" );
}

//---------------------------------------------------------------------------//
// Check that a map can be placed in a stream
BOOST_AUTO_TEST_CASE( toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::map<short, short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{-1, 2}, {0, 1}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<unsigned short, unsigned short>( {std::pair<unsigned short, unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 1}, {2, 10}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{-10, 0}, {10, -20}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 2}, {10, 100}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<long, long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{-1000000000, 1}, {1000000000, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<unsigned long, unsigned long>( {std::make_pair(0l, 1000000000l), std::make_pair(1000000000l, 2000000000l)} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 1000000000}, {1000000000, 2000000000}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{-10000000000, 1}, {10000000000, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{0, 10000000000}, {10000000000, 20000000000}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{-1, -1.000000000e+00}, {1, 1.000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<unsigned, double>( {std::make_pair(0, 0.0), std::make_pair(1, 1.0)} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{0, 0.000000000000000000e+00}, {1, 1.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<char, char>( {std::make_pair( 'a', 'b'), std::make_pair( 'A', 'B' )} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{A, B}, {a, b}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<std::string, std::string>( {std::make_pair( "Test String A", "Hello A" ), std::make_pair( "Test String B", "Hello B" )} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{Test String A, Hello A}, {Test String B, Hello B}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<int,std::pair<double,unsigned> >( {std::make_pair( -1, std::make_pair( 1.0, 0u ) ), std::make_pair( 1, std::make_pair( 0.0, 10u ) )} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{-1, {1.000000000000000000e+00, 0}}, {1, {0.000000000000000000e+00, 10}}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<unsigned, std::tuple<int, float, unsigned long> >( {std::make_pair( 0u, std::make_tuple( 1, -1.0f, 10ul ) ), std::make_pair( 1u, std::make_tuple( -1, 0.0, 100ul ) )} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{0, {1, -1.000000000e+00, 10}}, {1, {-1, 0.000000000e+00, 100}}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::map<long, std::vector<float> >( {std::make_pair( -1000000000l, std::vector<float>( {-1.0, 0.0, 1.0} ) ), std::make_pair( 1000000000l, std::vector<float>( {0.0} ) )} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{-1000000000, {-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}}, {1000000000, {0.000000000e+00}}}" );
}

//---------------------------------------------------------------------------//
// Check that a map iterator can be converted to a string
BOOST_AUTO_TEST_CASE( toString_iterator )
{
  std::map<int, int> int_map( {std::pair<int,int>({-1,0}), std::pair<int,int>({1,2})} );

  std::string iterator_string = Utility::toString( int_map.begin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( int_map.cbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( int_map.rbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( int_map.crbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  std::map<std::string,double> string_double_map( {std::pair<std::string,double>({"-1",0.0}), std::pair<std::string,double>({"1", 2.0})} );

  iterator_string = Utility::toString( string_double_map.begin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( string_double_map.cbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( string_double_map.rbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( string_double_map.crbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );
}

//---------------------------------------------------------------------------//
// Check that a map iterator can be placed in a stream
BOOST_AUTO_TEST_CASE( toStream_iterator )
{
  std::map<int, int> int_map( {std::pair<int,int>({-1,0}), std::pair<int,int>({1,2})} );

  std::ostringstream oss;

  Utility::toStream( oss, int_map.begin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, int_map.cbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, int_map.rbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, int_map.crbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  std::map<std::string,double> string_double_map( {std::pair<std::string,double>({"-1",0.0}), std::pair<std::string,double>({"1", 2.0})} );

  Utility::toStream( oss, string_double_map.begin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, string_double_map.cbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, string_double_map.rbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, string_double_map.crbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that a map can be created from a string
BOOST_AUTO_TEST_CASE( fromString )
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
BOOST_AUTO_TEST_CASE( fromStream )
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
// Check that a map can be placed in a stream
BOOST_AUTO_TEST_CASE( ostream )
{
  std::ostringstream oss;

  oss << std::map<short, short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{-1, 2}, {0, 1}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<unsigned short, unsigned short>( {std::pair<unsigned short, unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 1}, {2, 10}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{-10, 0}, {10, -20}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 2}, {10, 100}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<long, long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{-1000000000, 1}, {1000000000, 2}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<unsigned long, unsigned long>( {std::make_pair(0l, 1000000000l), std::make_pair(1000000000l, 2000000000l)} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 1000000000}, {1000000000, 2000000000}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{-10000000000, 1}, {10000000000, 2}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{0, 10000000000}, {10000000000, 20000000000}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{-1, -1.000000000e+00}, {1, 1.000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<unsigned, double>( {std::make_pair(0, 0.0), std::make_pair(1, 1.0)} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{0, 0.000000000000000000e+00}, {1, 1.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<char, char>( {std::make_pair( 'a', 'b'), std::make_pair( 'A', 'B' )} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{A, B}, {a, b}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<std::string, std::string>( {std::make_pair( "Test String A", "Hello A" ), std::make_pair( "Test String B", "Hello B" )} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{Test String A, Hello A}, {Test String B, Hello B}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<int,std::pair<double,unsigned> >( {std::make_pair( -1, std::make_pair( 1.0, 0u ) ), std::make_pair( 1, std::make_pair( 0.0, 10u ) )} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{-1, {1.000000000000000000e+00, 0}}, {1, {0.000000000000000000e+00, 10}}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<unsigned, std::tuple<int, float, unsigned long> >( {std::make_pair( 0u, std::make_tuple( 1, -1.0f, 10ul ) ), std::make_pair( 1u, std::make_tuple( -1, 0.0, 100ul ) )} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{0, {1, -1.000000000e+00, 10}}, {1, {-1, 0.000000000e+00, 100}}}" );

  oss.str( "" );
  oss.clear();

  oss << std::map<long, std::vector<float> >( {std::make_pair( -1000000000l, std::vector<float>( {-1.0, 0.0, 1.0} ) ), std::make_pair( 1000000000l, std::vector<float>( {0.0} ) )} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{-1000000000, {-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}}, {1000000000, {0.000000000e+00}}}" );
}

//---------------------------------------------------------------------------//
// Check that a map can be extracted from a stream
BOOST_AUTO_TEST_CASE( istream )
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
// Check that the correct comparison policies are allowed for maps
BOOST_AUTO_TEST_CASE_TEMPLATE( IsComparisonAllowed, T, TestTypes )
{
  typedef std::map<T,T> Map;

  BOOST_CHECK( Utility::ComparisonTraits<Map>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<Map>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Map>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Map>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Map>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Map>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Map>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Map>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<const Map>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const Map>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Map>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Map>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Map>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Map>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Map>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Map>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );
}

//---------------------------------------------------------------------------//
// Check that maps can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, PolicyTypePair, TestPolicyTypes )
{
  typedef typename Utility::TupleElement<0,PolicyTypePair>::type Policy;
  typedef typename Utility::TupleElement<1,PolicyTypePair>::type T;

  std::map<T,T> left_map({std::make_pair(T(0),T(0)),
                          std::make_pair(T(1),T(1)),
                          std::make_pair(T(2),T(2))});
  
  std::map<T,T> right_map({std::make_pair(T(0),T(0)),
                           std::make_pair(T(1),T(1)),
                           std::make_pair(T(2),T(2))});

  std::ostringstream oss;

  // No details logging
  bool compare_result = Utility::compare<Policy,0>( left_map, "lhs",
                                                    right_map, "rhs",
                                                    oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( !compare_result );
  else
    BOOST_CHECK( compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_map, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_map, "lhs",
                                               {}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {std::make_pair(T(1),T(1)),
                                                std::make_pair(T(10),T(10)),
                                                std::make_pair(T(100),T(100))}, "lhs",
                                               right_map, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_map, "lhs",
                                               {std::make_pair(T(1),T(1)),
                                                std::make_pair(T(10),T(10)),
                                                std::make_pair(T(100),T(100))}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  // Details logging
  T tol( 1e-6 );

  compare_result = Utility::compare<Policy,0>( left_map, "lhs",
                                               right_map, "rhs",
                                               oss, tol, true );

  std::string expected_details =
    Utility::createComparisonHeader<Policy,0>( left_map, "lhs",
                                               right_map, "rhs",
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
                                                left_map.size(), "lhs", true,
                                                right_map.size(), "rhs", true,
                                                ".size()", local_oss, true );
    auto left_map_it = left_map.begin();
    auto left_map_end = left_map.end();

    while( left_map_it != left_map_end )
    {
      Utility::ComparisonTraits<bool>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                                                                         true, "lhs", true,
                                                                                                         true, "rhs", true,
                                                                                                         std::string(" contains ") + Utility::toString(*left_map_it),
                                                                                                         local_oss, true, tol );
      ++left_map_it;
    }

    expected_details += "passed\n";
    expected_details += local_oss.str();

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  
  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( {std::make_pair(T(1),T(1)),
                                                std::make_pair(T(10),T(10)),
                                                std::make_pair(T(100),T(100))}, "lhs",
                                               right_map, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {std::make_pair(T(1),T(1)),
                                                std::make_pair(T(10),T(10)),
                                                std::make_pair(T(100),T(100))}, "lhs",
                                               right_map, "rhs",
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
                                                left_map.size(), "lhs", false,
                                                right_map.size(), "rhs", true,
                                                ".size()", local_oss, true );
    auto right_map_it = right_map.begin();
    auto right_map_end = right_map.end();

    while( right_map_it != right_map_end )
    {
      Utility::ComparisonTraits<bool>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
       right_map_it->first==1|| right_map_it->first==10|| right_map_it->first==100, "lhs", true,
       true, "rhs", true,
       std::string(" contains ") + Utility::toString(*right_map_it),
       local_oss, true, tol );
      
      ++right_map_it;
    }

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  
  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_map, "lhs",
                                               {std::make_pair(T(1),T(1)),
                                                std::make_pair(T(10),T(10)),
                                                std::make_pair(T(100),T(100))}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_map, "lhs",
                                               {std::make_pair(T(1),T(1)),
                                                std::make_pair(T(10),T(10)),
                                                std::make_pair(T(100),T(100))}, "rhs",
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
                                                left_map.size(), "lhs", true,
                                                right_map.size(), "rhs", false,
                                                ".size()", local_oss, true );
    auto left_map_it = left_map.begin();
    auto left_map_end = left_map.end();

    while( left_map_it != left_map_end )
    {
      Utility::ComparisonTraits<bool>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
       true, "lhs", true,
       left_map_it->first==1|| left_map_it->first==10|| left_map_it->first==100, "rhs", true,
       std::string(" contains ") + Utility::toString(*left_map_it),
       local_oss, true, tol );
      
      ++left_map_it;
    }

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  
  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_map, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {}, "lhs",
                                               right_map, "rhs",
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
                                                right_map.size(), "rhs", true,
                                                ".size()", local_oss, true );

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  
  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_map, "lhs",
                                               {}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_map, "lhs",
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
                                                left_map.size(), "lhs", true,
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
// Unordered Map Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( UnorderedMap )

//---------------------------------------------------------------------------//
// Check that a unordered_map can be converted to a string
BOOST_AUTO_TEST_CASE( toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( std::unordered_map<short, short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} ) ),
                       "{{0, 1}, {-1, 2}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::unordered_map<unsigned short, unsigned short>( {std::pair<unsigned short, unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} ) ),
                       "{{2, 10}, {0, 1}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::unordered_map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} ) ),
                       "{{10, -20}, {-10, 0}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::unordered_map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} ) ),
                       "{{10, 100}, {0, 2}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::unordered_map<long, long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} ) ),
                       "{{1000000000, 2}, {-1000000000, 1}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::unordered_map<unsigned long, unsigned long>( {std::make_pair(0l, 1000000000l), std::make_pair(1000000000l, 2000000000l)} ) ),
                       "{{1000000000, 2000000000}, {0, 1000000000}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::unordered_map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} ) ),
                       "{{10000000000, 2}, {-10000000000, 1}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::unordered_map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} ) ),
                       "{{10000000000, 20000000000}, {0, 10000000000}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::unordered_map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} ) ),
                       "{{1, 1.000000000e+00}, {-1, -1.000000000e+00}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::unordered_map<unsigned, double>( {std::make_pair(0, 0.0), std::make_pair(1, 1.0)} ) ),
                       "{{1, 1.000000000000000000e+00}, {0, 0.000000000000000000e+00}}" );

  BOOST_CHECK_EQUAL( Utility::toString( std::unordered_map<char, char>( {std::make_pair( 'a', 'b'), std::make_pair( 'A', 'B' )} ) ),
                       "{{A, B}, {a, b}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::unordered_map<std::string, std::string>( {std::make_pair( "Test String A", "Hello A" ), std::make_pair( "Test String B", "Hello B" )} ) ),
                       "{{Test String B, Hello B}, {Test String A, Hello A}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::unordered_map<int,std::pair<double,unsigned> >( {std::make_pair( -1, std::make_pair( 1.0, 0u ) ), std::make_pair( 1, std::make_pair( 0.0, 10u ) )} ) ),
                       "{{1, {0.000000000000000000e+00, 10}}, {-1, {1.000000000000000000e+00, 0}}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::unordered_map<unsigned, std::tuple<int, float, unsigned long> >( {std::make_pair( 0u, std::make_tuple( 1, -1.0f, 10ul ) ), std::make_pair( 1u, std::make_tuple( -1, 0.0, 100ul ) )} ) ),
                       "{{1, {-1, 0.000000000e+00, 100}}, {0, {1, -1.000000000e+00, 10}}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::unordered_map<long, std::vector<float> >( {std::make_pair( -1000000000l, std::vector<float>( {-1.0, 0.0, 1.0} ) ), std::make_pair( 1000000000l, std::vector<float>( {0.0} ) )} ) ),
                       "{{1000000000, {0.000000000e+00}}, {-1000000000, {-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}}}" );
}

//---------------------------------------------------------------------------//
// Check that a unordered_map can be placed in a stream
BOOST_AUTO_TEST_CASE( toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::unordered_map<short, short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<unsigned short, unsigned short>( {std::pair<unsigned short, unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{2, 10}, {0, 1}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{10, -20}, {-10, 0}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{10, 100}, {0, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<long, long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{1000000000, 2}, {-1000000000, 1}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<unsigned long, unsigned long>( {std::make_pair(0l, 1000000000l), std::make_pair(1000000000l, 2000000000l)} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{1000000000, 2000000000}, {0, 1000000000}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{10000000000, 2}, {-10000000000, 1}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{10000000000, 20000000000}, {0, 10000000000}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{1, 1.000000000e+00}, {-1, -1.000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<unsigned, double>( {std::make_pair(0, 0.0), std::make_pair(1, 1.0)} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{1, 1.000000000000000000e+00}, {0, 0.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<char, char>( {std::make_pair( 'a', 'b'), std::make_pair( 'A', 'B' )} ) );

  BOOST_CHECK_EQUAL( oss.str(), "{{A, B}, {a, b}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<std::string, std::string>( {std::make_pair( "Test String A", "Hello A" ), std::make_pair( "Test String B", "Hello B" )} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{Test String B, Hello B}, {Test String A, Hello A}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<int,std::pair<double,unsigned> >( {std::make_pair( -1, std::make_pair( 1.0, 0u ) ), std::make_pair( 1, std::make_pair( 0.0, 10u ) )} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), 
                       "{{1, {0.000000000000000000e+00, 10}}, {-1, {1.000000000000000000e+00, 0}}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<unsigned, std::tuple<int, float, unsigned long> >( {std::make_pair( 0u, std::make_tuple( 1, -1.0f, 10ul ) ), std::make_pair( 1u, std::make_tuple( -1, 0.0, 100ul ) )} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{1, {-1, 0.000000000e+00, 100}}, {0, {1, -1.000000000e+00, 10}}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::unordered_map<long, std::vector<float> >( {std::make_pair( -1000000000l, std::vector<float>( {-1.0, 0.0, 1.0} ) ), std::make_pair( 1000000000l, std::vector<float>( {0.0} ) )} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{1000000000, {0.000000000e+00}}, {-1000000000, {-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}}}" );
}

//---------------------------------------------------------------------------//
// Check that an unordered_map iterator can be converted to a string
BOOST_AUTO_TEST_CASE( toString_iterator )
{
  std::unordered_map<int, int> int_map( {std::pair<int,int>({-1,0}), std::pair<int,int>({1,2})} );

  std::string iterator_string = Utility::toString( int_map.begin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( int_map.cbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  std::unordered_map<std::string,double> string_double_map( {std::pair<std::string,double>({"-1",0.0}), std::pair<std::string,double>({"1", 2.0})} );

  iterator_string = Utility::toString( string_double_map.begin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( string_double_map.cbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );
}

//---------------------------------------------------------------------------//
// Check that an unordered_map iterator can be placed in a stream
BOOST_AUTO_TEST_CASE( toStream_iterator )
{
  std::unordered_map<int, int> int_map( {std::pair<int,int>({-1,0}), std::pair<int,int>({1,2})} );

  std::ostringstream oss;

  Utility::toStream( oss, int_map.begin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, int_map.cbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  std::unordered_map<std::string,double> string_double_map( {std::pair<std::string,double>({"-1",0.0}), std::pair<std::string,double>({"1", 2.0})} );

  Utility::toStream( oss, string_double_map.begin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, string_double_map.cbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();
}

//---------------------------------------------------------------------------//
// Check that a unordered_map can be created from a string
BOOST_AUTO_TEST_CASE( fromString )
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
BOOST_AUTO_TEST_CASE( fromStream )
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
// Check that an unordered_map can be placed in a stream
BOOST_AUTO_TEST_CASE( ostream )
{
  std::ostringstream oss;

  oss << std::unordered_map<short, short>( {std::pair<short,short>({-1, 2}), std::pair<short,short>({0, 1})} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<unsigned short, unsigned short>( {std::pair<unsigned short, unsigned short>({0, 1}), std::pair<unsigned short, unsigned short>({2, 10})} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{2, 10}, {0, 1}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<int, int>( {std::make_pair(-10, 0), std::make_pair(10, -20)} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{10, -20}, {-10, 0}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<unsigned, unsigned>( {std::make_pair(0u, 2u), std::make_pair(10u, 100u)} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{10, 100}, {0, 2}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<long, long>( {std::make_pair(-1000000000l, 1l), std::make_pair(1000000000l, 2l)} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{1000000000, 2}, {-1000000000, 1}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<unsigned long, unsigned long>( {std::make_pair(0l, 1000000000l), std::make_pair(1000000000l, 2000000000l)} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{1000000000, 2000000000}, {0, 1000000000}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<long long, long long>( {std::make_pair(-10000000000ll, 1ll), std::make_pair(10000000000ll, 2ll)} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{10000000000, 2}, {-10000000000, 1}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<unsigned long long, unsigned long long>( {std::make_pair(0ull, 10000000000ull), std::make_pair(10000000000ull, 20000000000ull)} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{10000000000, 20000000000}, {0, 10000000000}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<int, float>( {std::make_pair(-1, -1.0f), std::make_pair(1, 1.0f)} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{1, 1.000000000e+00}, {-1, -1.000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<unsigned, double>( {std::make_pair(0, 0.0), std::make_pair(1, 1.0)} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{1, 1.000000000000000000e+00}, {0, 0.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<char, char>( {std::make_pair( 'a', 'b'), std::make_pair( 'A', 'B' )} );

  BOOST_CHECK_EQUAL( oss.str(), "{{A, B}, {a, b}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<std::string, std::string>( {std::make_pair( "Test String A", "Hello A" ), std::make_pair( "Test String B", "Hello B" )} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{Test String B, Hello B}, {Test String A, Hello A}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<int,std::pair<double,unsigned> >( {std::make_pair( -1, std::make_pair( 1.0, 0u ) ), std::make_pair( 1, std::make_pair( 0.0, 10u ) )} );
  
  BOOST_CHECK_EQUAL( oss.str(), 
                       "{{1, {0.000000000000000000e+00, 10}}, {-1, {1.000000000000000000e+00, 0}}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<unsigned, std::tuple<int, float, unsigned long> >( {std::make_pair( 0u, std::make_tuple( 1, -1.0f, 10ul ) ), std::make_pair( 1u, std::make_tuple( -1, 0.0, 100ul ) )} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{1, {-1, 0.000000000e+00, 100}}, {0, {1, -1.000000000e+00, 10}}}" );

  oss.str( "" );
  oss.clear();

  oss << std::unordered_map<long, std::vector<float> >( {std::make_pair( -1000000000l, std::vector<float>( {-1.0, 0.0, 1.0} ) ), std::make_pair( 1000000000l, std::vector<float>( {0.0} ) )} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{1000000000, {0.000000000e+00}}, {-1000000000, {-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}}}" );
}

//---------------------------------------------------------------------------//
// Check that an unordered_map can be extracted from a stream
BOOST_AUTO_TEST_CASE( istream )
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
// Check that the correct comparison policies are allowed for unordered maps
BOOST_AUTO_TEST_CASE_TEMPLATE( IsComparisonAllowed, T, TestTypes )
{
  typedef std::unordered_map<T,T> Map;

  BOOST_CHECK( Utility::ComparisonTraits<Map>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<Map>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Map>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Map>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Map>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Map>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Map>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Map>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<const Map>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const Map>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Map>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Map>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Map>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Map>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Map>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Map>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );
}

//---------------------------------------------------------------------------//
// Check that unordered maps can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, PolicyTypePair, TestPolicyTypes )
{
  typedef typename Utility::TupleElement<0,PolicyTypePair>::type Policy;
  typedef typename Utility::TupleElement<1,PolicyTypePair>::type T;

  std::unordered_map<T,T> left_map({std::make_pair(T(0),T(0)),
                                    std::make_pair(T(1),T(1)),
                                    std::make_pair(T(2),T(2))});
  
  std::unordered_map<T,T> right_map({std::make_pair(T(0),T(0)),
                                     std::make_pair(T(1),T(1)),
                                     std::make_pair(T(2),T(2))});

  std::ostringstream oss;

  // No details logging
  bool compare_result = Utility::compare<Policy,0>( left_map, "lhs",
                                                    right_map, "rhs",
                                                    oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( !compare_result );
  else
    BOOST_CHECK( compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_map, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_map, "lhs",
                                               {}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {std::make_pair(T(1),T(1)),
                                                std::make_pair(T(10),T(10)),
                                                std::make_pair(T(100),T(100))}, "lhs",
                                               right_map, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_map, "lhs",
                                               {std::make_pair(T(1),T(1)),
                                                std::make_pair(T(10),T(10)),
                                                std::make_pair(T(100),T(100))}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  // Details logging
  T tol( 1e-6 );

  compare_result = Utility::compare<Policy,0>( left_map, "lhs",
                                               right_map, "rhs",
                                               oss, tol, true );

  std::string expected_details =
    Utility::createComparisonHeader<Policy,0>( left_map, "lhs",
                                               right_map, "rhs",
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
                                                left_map.size(), "lhs", true,
                                                right_map.size(), "rhs", true,
                                                ".size()", local_oss, true );
    auto left_map_it = left_map.begin();
    auto left_map_end = left_map.end();

    while( left_map_it != left_map_end )
    {
      Utility::ComparisonTraits<bool>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                                                                                                         true, "lhs", true,
                                                                                                         true, "rhs", true,
                                                                                                         std::string(" contains ") + Utility::toString(*left_map_it),
                                                                                                         local_oss, true, tol );
      ++left_map_it;
    }

    expected_details += "passed\n";
    expected_details += local_oss.str();

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  
  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( {std::make_pair(T(1),T(1)),
                                                std::make_pair(T(10),T(10)),
                                                std::make_pair(T(100),T(100))}, "lhs",
                                               right_map, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {std::make_pair(T(1),T(1)),
                                                std::make_pair(T(10),T(10)),
                                                std::make_pair(T(100),T(100))}, "lhs",
                                               right_map, "rhs",
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
                                                left_map.size(), "lhs", false,
                                                right_map.size(), "rhs", true,
                                                ".size()", local_oss, true );
    auto right_map_it = right_map.begin();
    auto right_map_end = right_map.end();

    while( right_map_it != right_map_end )
    {
      Utility::ComparisonTraits<bool>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
       right_map_it->first==1|| right_map_it->first==10|| right_map_it->first==100, "lhs", true,
       true, "rhs", true,
       std::string(" contains ") + Utility::toString(*right_map_it),
       local_oss, true, tol );
      
      ++right_map_it;
    }

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  
  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_map, "lhs",
                                               {std::make_pair(T(1),T(1)),
                                                std::make_pair(T(10),T(10)),
                                                std::make_pair(T(100),T(100))}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_map, "lhs",
                                               {std::make_pair(T(1),T(1)),
                                                std::make_pair(T(10),T(10)),
                                                std::make_pair(T(100),T(100))}, "rhs",
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
                                                left_map.size(), "lhs", true,
                                                right_map.size(), "rhs", false,
                                                ".size()", local_oss, true );
    auto left_map_it = left_map.begin();
    auto left_map_end = left_map.end();

    while( left_map_it != left_map_end )
    {
      Utility::ComparisonTraits<bool>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
       true, "lhs", true,
       left_map_it->first==1|| left_map_it->first==10|| left_map_it->first==100, "rhs", true,
       std::string(" contains ") + Utility::toString(*left_map_it),
       local_oss, true, tol );
      
      ++left_map_it;
    }

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  
  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_map, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {}, "lhs",
                                               right_map, "rhs",
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
                                                right_map.size(), "rhs", true,
                                                ".size()", local_oss, true );

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
  
  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_map, "lhs",
                                               {}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_map, "lhs",
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
                                                left_map.size(), "lhs", true,
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
// end tstMap.cpp
//---------------------------------------------------------------------------//
