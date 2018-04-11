//---------------------------------------------------------------------------//
//!
//! \file   tstList.cpp
//! \author Alex Robinson
//! \brief  List helper function unit tests
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
#include "Utility_List.hpp"
#include "Utility_Tuple.hpp"

//---------------------------------------------------------------------------//
// Testing Macros
//---------------------------------------------------------------------------//
#define TEST_COMPARE_CONTAINERS( left_container, right_container )      \
  {                                                                     \
    const decltype(left_container)& left_container_ref = left_container; \
    const decltype(right_container)& right_container_ref = right_container; \
    BOOST_CHECK_EQUAL_COLLECTIONS( left_container_ref.begin(),          \
                                   left_container_ref.end(),            \
                                   right_container_ref.begin(),         \
                                   right_container_ref.end() );         \
  }

#define TEST_COMPARE_FLOATING_CONTAINERS( left_container, right_container, tol ) \
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
    auto right_container_it = right_container_ref.begin();                \
                                                                        \
    while( left_container_it != left_container_end )                   \
    {                                                                 \
      BOOST_CHECK_CLOSE_FRACTION( *left_container_it, *right_container_it, tol ); \
      ++left_container_it;                                              \
      ++right_container_it;                                             \
    }                                                                   \
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

typedef typename MergeTypeLists<typename TypeList<Utility::EqualityComparisonPolicy>::type, typename TypeList<Utility::CloseComparisonPolicy>::type, typename TypeList<Utility::RelativeErrorComparisonPolicy>::type, typename TypeList<Utility::InequalityComparisonPolicy>::type>::type TestPolicyTypes;

//---------------------------------------------------------------------------//
// List Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( List )

//---------------------------------------------------------------------------//
// Check that a list can be converted to a string
BOOST_AUTO_TEST_CASE( toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( std::list<short>( {-1, 2} ) ),
                       "{-1, 2}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::list<unsigned short>( {0, 10, 100} ) ),
                       "{0, 10, 100}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::list<int>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::list<unsigned int>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::list<long>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::list<unsigned long>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::list<long long>( {-10000000000, 0, 10000000000} ) ),
                       "{-10000000000, 0, 10000000000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::list<unsigned long long>( {0, 1000000000, 1000000000000} ) ),
                       "{0, 1000000000, 1000000000000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::list<float>( {-1.0f, 0.0f, 1.0f} ) ),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::list<double>( {-1.0, 0.0, 1.0} ) ),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::list<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) ),
                       "{T, e, s, t,  , s, t, r, i, n, g}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::list<std::string>( {"Test", "string"} ) ),
                       "{Test, string}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::list<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) ),
                       "{{0, 1}, {-1, 2}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::list<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) ),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a list can be placed in a stream
BOOST_AUTO_TEST_CASE( toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::list<short>( {-1, 2} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<unsigned short>( {0, 10, 100} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<int>( {-11111, 0, 11111, 22222} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<unsigned int>( {0, 10, 100, 1000, 10000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<long>( {-11111, 0, 11111, 22222} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<unsigned long>( {0, 10, 100, 1000, 10000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<long long>( {-10000000000, 0, 10000000000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<unsigned long long>( {0, 1000000000, 1000000000000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<float>( {-1.0f, 0.0f, 1.0f} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<double>( {-1.0, 0.0, 1.0} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<std::string>( {"Test", "string"} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<std::pair<int, int>>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::list<std::tuple<unsigned, double, long>>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a list iterator can be converted to a string
BOOST_AUTO_TEST_CASE( toString_iterator )
{
  std::list<int> int_list( {-1, 0, 1} );

  std::string iterator_string = Utility::toString( int_list.begin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( int_list.cbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( int_list.rbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( int_list.crbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  std::list<double> double_list( {-1, 0, 1} );

  iterator_string = Utility::toString( double_list.begin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( double_list.cbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( double_list.rbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( double_list.crbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );
}

//---------------------------------------------------------------------------//
// Check that a list iterator can be placed in a stream
BOOST_AUTO_TEST_CASE( toStream_iterator )
{
  std::list<int> int_list( {-1, 0, 1} );

  std::ostringstream oss;

  Utility::toStream( oss, int_list.begin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, int_list.cbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, int_list.rbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, int_list.crbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  std::list<double> double_list( {-1, 0, 1} );

  Utility::toStream( oss, double_list.begin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, double_list.cbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, double_list.rbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, double_list.crbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();
}

//---------------------------------------------------------------------------//
// Check that a list can be created from a string
BOOST_AUTO_TEST_CASE( fromString )
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
BOOST_AUTO_TEST_CASE( fromStream )
{
  // Extract list of short
  std::istringstream iss( "{-1, 2}" );

  {
    std::list<short> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<short>({-1, 2}) );

    iss.str( "{-1, 2i, 2}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<short>({-1, 0, 1, 2}) );
  }

  // Extract list of unsigned short
  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::list<unsigned short> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned short>({0, 10, 100}) );

    iss.str( "{0, 3i, 100}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned short>({0, 25, 50, 75, 100}) );
  }

  // Extract list of int
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::list<int> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<int>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<int>({-11111, 0, 11111, 22222}) );
  }

  // Extract list of unsigned int
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::list<unsigned> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract list of long
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::list<long> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<long>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<long>({-11111, 0, 11111, 22222}) );
  }

  // Extract list of unsigned long
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::list<unsigned long> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned long>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned long>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract list of long long
  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::list<long long> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<long long>({-1000000000, 0, 1000000000}) );

    iss.str( "{-1000000000, 1i, 1000000000}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<long long>({-1000000000, 0, 1000000000}) );
  }

  // Extract list of unsigned long long
  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::list<unsigned long long> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned long long>({0, 1000000000, 10000000000}) );

    iss.str( "{0, 1i, 10000000000}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned long long>({0, 5000000000, 10000000000}) );
  }

  // Extract list of float
  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::list<float> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<float>({-1.0f, 0.0f, 1.0f}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<float>({-1.0f, -0.5f, 0.0f, 0.5f, 1.0f}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_FLOATING_CONTAINERS( test_list,
                                      std::list<float>({1e-3f, 1e-2f, 1e-1f, 1.0f}),
                                      1e-7 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    Utility::fromStream( iss, test_list );
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<float>({1.0f, 10.0f, 100.0f, 125.0f, 150.0f, 175.0f, 200.0f}) );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    Utility::fromStream( iss, test_list );
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<float>({0.0f, (float)Utility::PhysicalConstants::pi/2, 3*(float)Utility::PhysicalConstants::pi/4, (float)Utility::PhysicalConstants::pi, 2*(float)Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    Utility::fromStream( iss, test_list );
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_list,
                                      std::list<float>({-(float)Utility::PhysicalConstants::pi, -3*(float)Utility::PhysicalConstants::pi/4, -(float)Utility::PhysicalConstants::pi/2, -(float)Utility::PhysicalConstants::pi/4, 0.0}),
                                      1e-7 );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    Utility::fromStream( iss, test_list );
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<float>({-std::numeric_limits<float>::infinity(), 0.0f, std::numeric_limits<float>::infinity()}) );
  }

  // Extract list of double
  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::list<double> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<double>({-1.0, 0.0, 1.0}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<double>({-1.0, -0.5, 0.0, 0.5, 1.0}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_FLOATING_CONTAINERS( test_list,
                                      std::list<double>({1e-3, 1e-2, 1e-1, 1.0}),
                                      1e-9 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    Utility::fromStream( iss, test_list );
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_list,
                                      std::list<double>({1.0, 10.0, 100.0, 125.0, 150.0, 175.0, 200.0}),
                                      1e-15 );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    Utility::fromStream( iss, test_list );
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<double>({0.0, Utility::PhysicalConstants::pi/2, 3*Utility::PhysicalConstants::pi/4, Utility::PhysicalConstants::pi, 2*Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    Utility::fromStream( iss, test_list );
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<double>({-Utility::PhysicalConstants::pi, -3*Utility::PhysicalConstants::pi/4, -Utility::PhysicalConstants::pi/2, -Utility::PhysicalConstants::pi/4, 0.0}) );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    Utility::fromStream( iss, test_list );
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<double>({-std::numeric_limits<float>::infinity(), 0.0, std::numeric_limits<float>::infinity()}) );
  }

  // Extract list of char
  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::list<char> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  // Extract list of string
  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::list<std::string> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::list<std::string>({"Test","string"}) );
  }

  // Extract list of pair
  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::list<std::pair<int,int> > test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, (std::list<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  // Extract list of tuple
  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::list<std::tuple<unsigned,double,long> > test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, (std::list<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  // Extract multiple lists of pairs
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

  // Extract list of lists
  iss.str( "{{-1, 3i, 1}, {1e-3, 2l, 1.0}, {-Inf, Inf}, {-pi/2, 1i, pi/2}}" );
  iss.clear();

  {
    std::list<std::list<double> > test_list;
    
    Utility::fromStream( iss, test_list );
    
    BOOST_CHECK_EQUAL( test_list.size(), 4 );

    std::list<std::list<double> >::const_iterator
      test_list_it = test_list.begin();
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::list<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );
    
    ++test_list_it;
    
    TEST_COMPARE_FLOATING_CONTAINERS( *test_list_it,
                                      (std::list<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );

    ++test_list_it;
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::list<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );

    ++test_list_it;
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::list<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );
  }
}

//---------------------------------------------------------------------------//
// Check that a list can be placed in a stream
BOOST_AUTO_TEST_CASE( ostream )
{
  std::ostringstream oss;

  oss << std::list<short>( {-1, 2} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  oss << std::list<unsigned short>( {0, 10, 100} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  oss << std::list<int>( {-11111, 0, 11111, 22222} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::list<unsigned int>( {0, 10, 100, 1000, 10000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::list<long>( {-11111, 0, 11111, 22222} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::list<unsigned long>( {0, 10, 100, 1000, 10000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::list<long long>( {-10000000000, 0, 10000000000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::list<unsigned long long>( {0, 1000000000, 1000000000000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::list<float>( {-1.0f, 0.0f, 1.0f} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  oss << std::list<double>( {-1.0, 0.0, 1.0} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::list<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } );
  
  BOOST_CHECK_EQUAL( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  oss << std::list<std::string>( {"Test", "string"} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  oss << std::list<std::pair<int, int>>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  oss << std::list<std::tuple<unsigned, double, long>>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a list can be extracted from a stream
BOOST_AUTO_TEST_CASE( istream )
{
  // Extract list of short
  std::istringstream iss( "{-1, 2}" );

  {
    std::list<short> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<short>({-1, 2}) );

    iss.str( "{-1, 2i, 2}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<short>({-1, 0, 1, 2}) );
  }

  // Extract list of unsigned short
  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::list<unsigned short> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned short>({0, 10, 100}) );

    iss.str( "{0, 3i, 100}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned short>({0, 25, 50, 75, 100}) );
  }

  // Extract list of int
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::list<int> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<int>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<int>({-11111, 0, 11111, 22222}) );
  }

  // Extract list of unsigned int
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::list<unsigned> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract list of long
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::list<long> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<long>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<long>({-11111, 0, 11111, 22222}) );
  }

  // Extract list of unsigned long
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::list<unsigned long> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned long>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned long>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract list of long long
  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::list<long long> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<long long>({-1000000000, 0, 1000000000}) );

    iss.str( "{-1000000000, 1i, 1000000000}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<long long>({-1000000000, 0, 1000000000}) );
  }

  // Extract list of unsigned long long
  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::list<unsigned long long> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned long long>({0, 1000000000, 10000000000}) );

    iss.str( "{0, 1i, 10000000000}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<unsigned long long>({0, 5000000000, 10000000000}) );
  }

  // Extract list of float
  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::list<float> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<float>({-1.0f, 0.0f, 1.0f}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<float>({-1.0f, -0.5f, 0.0f, 0.5f, 1.0f}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_FLOATING_CONTAINERS( test_list,
                                      std::list<float>({1e-3f, 1e-2f, 1e-1f, 1.0f}),
                                      1e-7);

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    iss >> test_list;
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<float>({1.0f, 10.0f, 100.0f, 125.0f, 150.0f, 175.0f, 200.0f}) );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    iss >> test_list;
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<float>({0.0f, (float)Utility::PhysicalConstants::pi/2, 3*(float)Utility::PhysicalConstants::pi/4, (float)Utility::PhysicalConstants::pi, 2*(float)Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    iss >> test_list;
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_list,
                                      std::list<float>({-(float)Utility::PhysicalConstants::pi, -3*(float)Utility::PhysicalConstants::pi/4, -(float)Utility::PhysicalConstants::pi/2, -(float)Utility::PhysicalConstants::pi/4, 0.0}),
                                      1e-7 );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    iss >> test_list;
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<float>({-std::numeric_limits<float>::infinity(), 0.0f, std::numeric_limits<float>::infinity()}) );
  }

  // Extract list of double
  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::list<double> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<double>({-1.0, 0.0, 1.0}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<double>({-1.0, -0.5, 0.0, 0.5, 1.0}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_FLOATING_CONTAINERS( test_list,
                                      std::list<double>({1e-3, 1e-2, 1e-1, 1.0}),
                                      1e-9 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    iss >> test_list;
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_list,
                                      std::list<double>({1.0, 10.0, 100.0, 125.0, 150.0, 175.0, 200.0}),
                                      1e-15 );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    iss >> test_list;
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<double>({0.0, Utility::PhysicalConstants::pi/2, 3*Utility::PhysicalConstants::pi/4, Utility::PhysicalConstants::pi, 2*Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    iss >> test_list;
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<double>({-Utility::PhysicalConstants::pi, -3*Utility::PhysicalConstants::pi/4, -Utility::PhysicalConstants::pi/2, -Utility::PhysicalConstants::pi/4, 0.0}) );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    iss >> test_list;
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<double>({-std::numeric_limits<float>::infinity(), 0.0, std::numeric_limits<float>::infinity()}) );
  }

  // Extract list of char
  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::list<char> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  // Extract list of string
  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::list<std::string> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::list<std::string>({"Test","string"}) );
  }

  // Extract list of pair
  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::list<std::pair<int,int> > test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, (std::list<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  // Extract list of tuple
  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::list<std::tuple<unsigned,double,long> > test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, (std::list<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  // Extract multiple lists of pairs
  iss.str( "{{0, 1}, {-1, 2}}, {{1, 0}, {2, -1}}" );
  iss.clear();

  {
    std::list<std::pair<long,long> > test_list;

    Utility::fromStream( iss, test_list, "," );

    TEST_COMPARE_CONTAINERS( test_list, (std::list<std::pair<long,long> >({std::make_pair(0l, 1l), std::make_pair(-1l, 2l)})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, (std::list<std::pair<long,long> >({std::make_pair(1l, 0l), std::make_pair(2l, -1l)})) );
  }

  // Extract list of lists
  iss.str( "{{-1, 3i, 1}, {1e-3, 2l, 1.0}, {-Inf, Inf}, {-pi/2, 1i, pi/2}}" );
  iss.clear();

  {
    std::list<std::list<double> > test_list;
    
    iss >> test_list;
    
    BOOST_CHECK_EQUAL( test_list.size(), 4 );

    std::list<std::list<double> >::const_iterator
      test_list_it = test_list.begin();
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::list<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );
    
    ++test_list_it;
    
    TEST_COMPARE_FLOATING_CONTAINERS( *test_list_it,
                                      (std::list<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );

    ++test_list_it;
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::list<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );

    ++test_list_it;
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::list<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );
  }
}

//---------------------------------------------------------------------------//
// Check that a list can mimic stream behavior
BOOST_AUTO_TEST_CASE( stream_mimic )
{
  {
    std::list<short> test_list;

    test_list << -1 << 0 << 1;

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<short>( {-1, 0, 1} ) );

    short element0, element1, element2;

    test_list >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -1 );
    BOOST_CHECK_EQUAL( element1, 0 );
    BOOST_CHECK_EQUAL( element2, 1 );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );

    test_list << "-1" << 0 << "1";

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<short>( {-1, 0, 1} ) );

    std::string element0_str, element1_str, element2_str;

    test_list >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-1" );
    BOOST_CHECK_EQUAL( element1_str, "0" );
    BOOST_CHECK_EQUAL( element2_str, "1" );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );
  }

  {
    std::list<unsigned short> test_list;

    test_list << 0 << 10 << 100;

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<unsigned short>( {0, 10, 100} ) );

    unsigned short element0, element1, element2;

    test_list >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, 0 );
    BOOST_CHECK_EQUAL( element1, 10 );
    BOOST_CHECK_EQUAL( element2, 100 );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );

    test_list << "0" << 10 << "100";

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<unsigned short>( {0, 10, 100} ) );

    std::string element0_str, element1_str, element2_str;

    test_list >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "0" );
    BOOST_CHECK_EQUAL( element1_str, "10" );
    BOOST_CHECK_EQUAL( element2_str, "100" );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );
  }

  {
    std::list<int> test_list;

    test_list << -11111 << 0 << 11111;

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<int>( {-11111, 0, 11111} ) );

    int element0, element1, element2;

    test_list >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -11111 );
    BOOST_CHECK_EQUAL( element1, 0 );
    BOOST_CHECK_EQUAL( element2, 11111 );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );

    test_list << "-11111" << 0 << "11111";

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<int>( {-11111, 0, 11111} ) );

    std::string element0_str, element1_str, element2_str;

    test_list >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-11111" );
    BOOST_CHECK_EQUAL( element1_str, "0" );
    BOOST_CHECK_EQUAL( element2_str, "11111" );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );
  }

  {
    std::list<unsigned int> test_list;

    test_list << 0 << 1000 << 1000000;

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<unsigned int>( {0, 1000, 1000000} ) );

    unsigned int element0, element1, element2;

    test_list >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, 0 );
    BOOST_CHECK_EQUAL( element1, 1000 );
    BOOST_CHECK_EQUAL( element2, 1000000 );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );

    test_list << "0" << 1000 << "1000000";

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<unsigned int>( {0, 1000, 1000000} ) );

    std::string element0_str, element1_str, element2_str;

    test_list >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "0" );
    BOOST_CHECK_EQUAL( element1_str, "1000" );
    BOOST_CHECK_EQUAL( element2_str, "1000000" );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );
  }

  {
    std::list<long> test_list;

    test_list << -11111l << 0l << 11111l;

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<long>( {-11111l, 0l, 11111l} ) );

    long element0, element1, element2;

    test_list >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -11111l );
    BOOST_CHECK_EQUAL( element1, 0l );
    BOOST_CHECK_EQUAL( element2, 11111l );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );

    test_list << "-11111" << 0 << "11111";

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<long>( {-11111l, 0l, 11111l} ) );

    std::string element0_str, element1_str, element2_str;

    test_list >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-11111" );
    BOOST_CHECK_EQUAL( element1_str, "0" );
    BOOST_CHECK_EQUAL( element2_str, "11111" );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );
  }

  {
    std::list<unsigned long> test_list;

    test_list << 0ul << 1000ul << 1000000ul;

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<unsigned long>( {0ul, 1000ul, 1000000ul} ) );

    unsigned long element0, element1, element2;

    test_list >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, 0ul );
    BOOST_CHECK_EQUAL( element1, 1000ul );
    BOOST_CHECK_EQUAL( element2, 1000000ul );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );

    test_list << "0" << 1000 << "1000000";

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<unsigned long>( {0ul, 1000ul, 1000000ul} ) );

    std::string element0_str, element1_str, element2_str;

    test_list >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "0" );
    BOOST_CHECK_EQUAL( element1_str, "1000" );
    BOOST_CHECK_EQUAL( element2_str, "1000000" );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );
  }
  
  {
    std::list<long long> test_list;

    test_list << -10000000000ll << 0ll << 10000000000ll;

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<long long>( {-10000000000ll, 0ll, 10000000000ll} ) );

    long long element0, element1, element2;

    test_list >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -10000000000ll );
    BOOST_CHECK_EQUAL( element1, 0ll );
    BOOST_CHECK_EQUAL( element2, 10000000000ll );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );

    test_list << "-10000000000" << 0 << "10000000000";

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<long long>( {-10000000000ll, 0ll, 10000000000ll} ) );

    std::string element0_str, element1_str, element2_str;

    test_list >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-10000000000" );
    BOOST_CHECK_EQUAL( element1_str, "0" );
    BOOST_CHECK_EQUAL( element2_str, "10000000000" );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );
  }

  {
    std::list<unsigned long long> test_list;

    test_list << 0ull << 10000000000ull << 100000000000ull;

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<unsigned long long>( {0ull, 10000000000ull, 100000000000ull} ) );

    unsigned long long element0, element1, element2;

    test_list >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, 0ull );
    BOOST_CHECK_EQUAL( element1, 10000000000ull );
    BOOST_CHECK_EQUAL( element2, 100000000000ull );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );

    test_list << "0" << 10000000000ull << "100000000000";

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<unsigned long long>( {0ull, 10000000000ull, 100000000000ull} ) );

    std::string element0_str, element1_str, element2_str;

    test_list >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "0" );
    BOOST_CHECK_EQUAL( element1_str, "10000000000" );
    BOOST_CHECK_EQUAL( element2_str, "100000000000" );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );
  }

  {
    std::list<float> test_list;

    test_list << -1.0f << 0.0f << 1.0f;

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<float>( {-1.0f, 0.0f, 1.0f} ) );

    float element0, element1, element2;

    test_list >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -1.0f );
    BOOST_CHECK_EQUAL( element1, 0.0f );
    BOOST_CHECK_EQUAL( element2, 1.0f );

    test_list << "-2pi/3" << "0" << "Inf";

    test_list >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -2*(float)Utility::PhysicalConstants::pi/3 );
    BOOST_CHECK_EQUAL( element1, 0.0f );
    BOOST_CHECK_EQUAL( element2, std::numeric_limits<float>::infinity() );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );

    test_list << -1.0f << 0.0f << 1.0f;

    std::string element0_str, element1_str, element2_str;

    test_list >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-1.000000000e+00" );
    BOOST_CHECK_EQUAL( element1_str, "0.000000000e+00" );
    BOOST_CHECK_EQUAL( element2_str, "1.000000000e+00" );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );
  }

  {
    std::list<double> test_list;

    test_list << -1.0 << 0.0 << 1.0;

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<double>( {-1.0, 0.0, 1.0} ) );

    double element0, element1, element2;

    test_list >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -1.0 );
    BOOST_CHECK_EQUAL( element1, 0.0 );
    BOOST_CHECK_EQUAL( element2, 1.0 );

    test_list << "-infty" << "0" << "pi/3";

    test_list >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -std::numeric_limits<double>::infinity() );
    BOOST_CHECK_EQUAL( element1, 0.0 );
    BOOST_CHECK_EQUAL( element2, Utility::PhysicalConstants::pi/3 );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );

    test_list << -1.0 << 0.0 << 1.0;

    std::string element0_str, element1_str, element2_str;

    test_list >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-1.000000000000000000e+00" );
    BOOST_CHECK_EQUAL( element1_str, "0.000000000000000000e+00" );
    BOOST_CHECK_EQUAL( element2_str, "1.000000000000000000e+00" );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );
  }

  {
    std::list<char> test_list;

    test_list << 'T' << 'e' << 's' << 't' << ' '
                << 's' << 't' << 'r' << 'i' << 'n' << 'g';

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'} ) );

    std::string elements( "           " );

    test_list >> elements[10] >> elements[9] >> elements[8] >> elements[7]
                >> elements[6] >> elements[5] >> elements[4] >> elements[3]
                >> elements[2] >> elements[1] >> elements[0];

    BOOST_CHECK_EQUAL( elements, "Test string" );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );
  }
  
  {
    std::list<std::string> test_list;

    test_list << "Test" << "string";

    TEST_COMPARE_CONTAINERS( test_list,
                             std::list<std::string>( {"Test", "string"} ) );

    std::string element0, element1;

    test_list >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, "Test" );
    BOOST_CHECK_EQUAL( element1, "string" );
  }

  {
    std::list<std::pair<int, int> > test_list;

    test_list << std::make_pair( 0, 1 ) << std::make_pair( -1, 2 );

    TEST_COMPARE_CONTAINERS( test_list,
                             (std::list<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} )) );

    std::pair<int,int> element0, element1;

    test_list >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, std::make_pair( 0, 1 ) );
    BOOST_CHECK_EQUAL( element1, std::make_pair( -1, 2 ) );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );

    test_list << "{0, 1}" << "{-1, 2}";

    test_list >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, std::make_pair( 0, 1 ) );
    BOOST_CHECK_EQUAL( element1, std::make_pair( -1, 2 ) );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );

    test_list << "{0, 1}" << std::make_pair( -1, 2 );

    std::string element0_str, element1_str;

    test_list >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "{0, 1}" );
    BOOST_CHECK_EQUAL( element1_str, "{-1, 2}" );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );
  }

  {
    std::list<std::tuple<unsigned, double, long> > test_list;

    test_list << std::make_tuple( 0u, 1.0, -100000l )
                << std::make_tuple( 1u, -1.0, 100001l );

    TEST_COMPARE_CONTAINERS( test_list,
                             (std::list<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} )) );

    std::tuple<unsigned, double, long> element0, element1;

    test_list >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, std::make_tuple( 0u, 1.0, -100000l ) );
    BOOST_CHECK_EQUAL( element1, std::make_tuple( 1u, -1.0, 100001l ) );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );

    test_list << "{0, 1, -100000}" << "{1, -1, 100001}";

    test_list >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, std::make_tuple( 0u, 1.0, -100000l ) );
    BOOST_CHECK_EQUAL( element1, std::make_tuple( 1u, -1.0, 100001l ) );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );

    test_list << "{0, 1, -100000}" << std::make_tuple( 1u, -1.0, 100001l );

    std::string element0_str, element1_str;

    test_list >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "{0, 1.000000000000000000e+00, -100000}" );
    BOOST_CHECK_EQUAL( element1_str, "{1, -1.000000000000000000e+00, 100001}" );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );
  }

  {
    std::list<std::list<double> > test_list;

    test_list << std::list<double>( {-1, -0.5, 0.0, 0.5, 1.0} )
              << std::list<double>( {1e-3, 1e-2, 1e-1, 1.0} )
              << std::list<double>( {-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()} )
              << std::list<double>( {-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2} );

    BOOST_CHECK_EQUAL( test_list.size(), 4 );

    std::list<std::list<double> >::const_iterator
      test_list_it = test_list.begin();
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::list<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );

    ++test_list_it;
    
    TEST_COMPARE_FLOATING_CONTAINERS( *test_list_it,
                                      (std::list<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );

    ++test_list_it;
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::list<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );

    ++test_list_it;
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::list<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );

    std::list<double> element0, element1, element2, element3;
    
    test_list >> element3 >> element2 >> element1 >> element0;
    
    TEST_COMPARE_CONTAINERS( element0,
                             (std::list<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );
    TEST_COMPARE_FLOATING_CONTAINERS( element1,
                                      (std::list<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );
    TEST_COMPARE_CONTAINERS( element2,
                             (std::list<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );
    TEST_COMPARE_CONTAINERS( element3,
                             (std::list<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );

    test_list << "{-1, 3i, 1}" << "{1e-3, 2l, 1.0}"
                << "{-Inf, Inf}" << "{-pi/2, 1i, pi/2}";

    BOOST_CHECK_EQUAL( test_list.size(), 4 );

    test_list_it = test_list.begin();
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::list<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );

    ++test_list_it;
    
    TEST_COMPARE_FLOATING_CONTAINERS( *test_list_it,
                                      (std::list<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );

    ++test_list_it;
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::list<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );

    ++test_list_it;
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::list<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );

    std::string element0_str, element1_str, element2_str, element3_str;

    test_list >> element3_str >> element2_str
                >> element1_str >> element0_str;

    BOOST_CHECK( element0_str.size() > 0 );
    BOOST_CHECK( element1_str.size() > 0 );
    BOOST_CHECK( element2_str.size() > 0 );
    BOOST_CHECK( element3_str.size() > 0 );
    BOOST_CHECK_EQUAL( test_list.size(), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the correct comparison policies are allowed for lists
BOOST_AUTO_TEST_CASE_TEMPLATE( IsComparisonAllowed, T, TestTypes )
{
  typedef std::list<T> List;

  BOOST_CHECK( Utility::ComparisonTraits<List>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<List>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<List>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<List>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<List>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<List>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<List>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<List>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<const List>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const List>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const List>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const List>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const List>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const List>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const List>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const List>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );
}

//---------------------------------------------------------------------------//
// Check that lists can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, PolicyTypePair, TestPolicyTypes )
{
  typedef typename Utility::TupleElement<0,PolicyTypePair>::type Policy;
  typedef typename Utility::TupleElement<1,PolicyTypePair>::type T;

  std::list<T> left_list({T(0), T(1), T(2)});
  std::list<T> right_list({T(0), T(1), T(2)});

  std::ostringstream oss;

  // No details logging
  bool compare_result = Utility::compare<Policy,0>( left_list, "lhs",
                                                    right_list, "rhs",
                                                    oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( !compare_result );
  else
    BOOST_CHECK( compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_list, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_list, "lhs",
                                               {}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {T(1),T(1),T(1)}, "lhs",
                                               right_list, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_list, "lhs",
                                               {T(1),T(1),T(1)}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  // Details logging
  T tol( 1e-6 );

  compare_result = Utility::compare<Policy,0>( left_list, "lhs",
                                               right_list, "rhs",
                                               oss, tol, true );

  std::string expected_details =
    Utility::createComparisonHeader<Policy,0>( left_list, "lhs",
                                               right_list, "rhs",
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
                                              left_list.size(), "lhs", true,
                                              right_list.size(), "rhs", true,
                                              ".size()", local_oss, true );

    auto left_list_it = left_list.begin();
    auto left_list_end = left_list.end();
    auto right_list_it = right_list.begin();
    
    while( left_list_it != left_list_end )
    {
      Utility::ComparisonTraits<T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                *left_list_it, "lhs", true,
                *right_list_it, "rhs", true,
                std::string("[") + Utility::toString(std::distance(left_list.begin(),left_list_it)) + "]", local_oss, true,
                tol );
      ++left_list_it;
      ++right_list_it;
    }

    expected_details += "passed\n";
    expected_details += local_oss.str();

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( {T(1), T(1), T(1)}, "lhs",
                                               right_list, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {T(1), T(1), T(1)}, "lhs",
                                               right_list, "rhs",
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
                                              3, "lhs", false,
                                              right_list.size(), "rhs", true,
                                              ".size()", local_oss, true );
    auto right_list_it = right_list.begin();
    auto right_list_end = right_list.end();
    
    while( right_list_it != right_list_end )
    {
      Utility::ComparisonTraits<T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                T(1), "lhs", false,
                *right_list_it, "rhs", true,
                std::string("[") + Utility::toString(std::distance(right_list.begin(),right_list_it)) + "]", local_oss, true,
                tol );
      ++right_list_it;
    }

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_list, "lhs",
                                               {T(1), T(1), T(1)}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_list, "lhs",
                                               {T(1), T(1), T(1)}, "rhs",
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
                                               left_list.size(), "lhs", true,
                                               3, "rhs", false,
                                               ".size()", local_oss, true );

    auto left_list_it = left_list.begin();
    auto left_list_end = left_list.end();
    
    while( left_list_it != left_list_end )
    {
      Utility::ComparisonTraits<T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                *left_list_it, "lhs", true,
                T(1), "rhs", false,
                std::string("[") + Utility::toString(std::distance(left_list.begin(),left_list_it)) + "]", local_oss, true,
                tol );
      ++left_list_it;
    }

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// Forward List Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( ForwardList )

//---------------------------------------------------------------------------//
// Check that a forward_list can be converted to a string
BOOST_AUTO_TEST_CASE( toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( std::forward_list<short>( {-1, 2} ) ),
                       "{-1, 2}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::forward_list<unsigned short>( {0, 10, 100} ) ),
                       "{0, 10, 100}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::forward_list<int>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::forward_list<unsigned int>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::forward_list<long>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::forward_list<unsigned long>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::forward_list<long long>( {-10000000000, 0, 10000000000} ) ),
                       "{-10000000000, 0, 10000000000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::forward_list<unsigned long long>( {0, 1000000000, 1000000000000} ) ),
                       "{0, 1000000000, 1000000000000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::forward_list<float>( {-1.0f, 0.0f, 1.0f} ) ),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::forward_list<double>( {-1.0, 0.0, 1.0} ) ),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::forward_list<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) ),
                       "{T, e, s, t,  , s, t, r, i, n, g}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::forward_list<std::string>( {"Test", "string"} ) ),
                       "{Test, string}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::forward_list<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) ),
                       "{{0, 1}, {-1, 2}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::forward_list<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) ),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a forward_list can be placed in a stream
BOOST_AUTO_TEST_CASE( toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::forward_list<short>( {-1, 2} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<unsigned short>( {0, 10, 100} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<int>( {-11111, 0, 11111, 22222} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<unsigned int>( {0, 10, 100, 1000, 10000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<long>( {-11111, 0, 11111, 22222} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<unsigned long>( {0, 10, 100, 1000, 10000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<long long>( {-10000000000, 0, 10000000000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<unsigned long long>( {0, 1000000000, 1000000000000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<float>( {-1.0f, 0.0f, 1.0f} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<double>( {-1.0, 0.0, 1.0} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<std::string>( {"Test", "string"} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<std::pair<int, int>>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::forward_list<std::tuple<unsigned, double, long>>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a list iterator can be converted to a string
BOOST_AUTO_TEST_CASE( toString_iterator )
{
  std::forward_list<int> int_list( {-1, 0, 1} );

  std::string iterator_string = Utility::toString( int_list.begin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( int_list.cbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  std::forward_list<double> double_list( {-1, 0, 1} );

  iterator_string = Utility::toString( double_list.begin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString( double_list.cbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );
}

//---------------------------------------------------------------------------//
// Check that a list iterator can be placed in a stream
BOOST_AUTO_TEST_CASE( toStream_iterator )
{
  std::forward_list<int> int_list( {-1, 0, 1} );

  std::ostringstream oss;

  Utility::toStream( oss, int_list.begin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, int_list.cbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  std::forward_list<double> double_list( {-1, 0, 1} );

  Utility::toStream( oss, double_list.begin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, double_list.cbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that a forward_list can be created from a string
BOOST_AUTO_TEST_CASE( fromString )
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
BOOST_AUTO_TEST_CASE( fromStream )
{
  // Extract forward_list of short
  std::istringstream iss( "{-1, 2}" );

  {
    std::forward_list<short> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<short>({-1, 2}) );

    iss.str( "{-1, 2i, 2}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<short>({-1, 0, 1, 2}) );
  }

  // Extract list of unsigned short
  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::forward_list<unsigned short> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<unsigned short>({0, 10, 100}) );

    iss.str( "{0, 3i, 100}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<unsigned short>({0, 25, 50, 75, 100}) );
  }

  // Extract list of int
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::forward_list<int> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<int>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<int>({-11111, 0, 11111, 22222}) );
  }

  // Extract list of unsigned int
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::forward_list<unsigned> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<unsigned>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<unsigned>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract list of long
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::forward_list<long> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<long>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<long>({-11111, 0, 11111, 22222}) );
  }

  // Extract list of unsigned long
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::forward_list<unsigned long> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<unsigned long>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<unsigned long>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract list of long long
  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::forward_list<long long> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<long long>({-1000000000, 0, 1000000000}) );

    iss.str( "{-1000000000, 1i, 1000000000}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<long long>({-1000000000, 0, 1000000000}) );
  }

  // Extract list of unsigned long long
  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::forward_list<unsigned long long> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<unsigned long long>({0, 1000000000, 10000000000}) );

    iss.str( "{0, 1i, 10000000000}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<unsigned long long>({0, 5000000000, 10000000000}) );
  }

  // Extract list of float
  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::forward_list<float> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<float>({-1.0f, 0.0f, 1.0f}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<float>({-1.0f, -0.5f, 0.0f, 0.5f, 1.0f}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_FLOATING_CONTAINERS( test_list,
                                      std::forward_list<float>({1e-3f, 1e-2f, 1e-1f, 1.0f}),
                                      1e-7 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    Utility::fromStream( iss, test_list );
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::forward_list<float>({1.0f, 10.0f, 100.0f, 125.0f, 150.0f, 175.0f, 200.0f}) );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    Utility::fromStream( iss, test_list );
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::forward_list<float>({0.0f, (float)Utility::PhysicalConstants::pi/2, 3*(float)Utility::PhysicalConstants::pi/4, (float)Utility::PhysicalConstants::pi, 2*(float)Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    Utility::fromStream( iss, test_list );
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_list,
                                      std::forward_list<float>({-(float)Utility::PhysicalConstants::pi, -3*(float)Utility::PhysicalConstants::pi/4, -(float)Utility::PhysicalConstants::pi/2, -(float)Utility::PhysicalConstants::pi/4, 0.0}),
                                      1e-7 );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    Utility::fromStream( iss, test_list );
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::forward_list<float>({-std::numeric_limits<float>::infinity(), 0.0f, std::numeric_limits<float>::infinity()}) );
  }

  // Extract list of double
  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::forward_list<double> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<double>({-1.0, 0.0, 1.0}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<double>({-1.0, -0.5, 0.0, 0.5, 1.0}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_FLOATING_CONTAINERS( test_list,
                                      std::forward_list<double>({1e-3, 1e-2, 1e-1, 1.0}),
                                      1e-9 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    Utility::fromStream( iss, test_list );
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_list,
                                      std::forward_list<double>({1.0, 10.0, 100.0, 125.0, 150.0, 175.0, 200.0}),
                                      1e-15 );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    Utility::fromStream( iss, test_list );
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::forward_list<double>({0.0, Utility::PhysicalConstants::pi/2, 3*Utility::PhysicalConstants::pi/4, Utility::PhysicalConstants::pi, 2*Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    Utility::fromStream( iss, test_list );
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::forward_list<double>({-Utility::PhysicalConstants::pi, -3*Utility::PhysicalConstants::pi/4, -Utility::PhysicalConstants::pi/2, -Utility::PhysicalConstants::pi/4, 0.0}) );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    Utility::fromStream( iss, test_list );
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::forward_list<double>({-std::numeric_limits<float>::infinity(), 0.0, std::numeric_limits<float>::infinity()}) );
  }

  // Extract list of char
  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::forward_list<char> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  // Extract list of string
  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::list<std::string> test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<std::string>({"Test","string"}) );
  }

  // Extract list of pair
  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::forward_list<std::pair<int,int> > test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, (std::forward_list<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  // Extract list of tuple
  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::forward_list<std::tuple<unsigned,double,long> > test_list;

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, (std::forward_list<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  // Extract multiple lists of pairs
  iss.str( "{{0, 1}, {-1, 2}}, {{1, 0}, {2, -1}}" );
  iss.clear();

  {
    std::forward_list<std::pair<long,long> > test_list;

    Utility::fromStream( iss, test_list, "," );

    TEST_COMPARE_CONTAINERS( test_list, (std::forward_list<std::pair<long,long> >({std::make_pair(0l, 1l), std::make_pair(-1l, 2l)})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    Utility::fromStream( iss, test_list );

    TEST_COMPARE_CONTAINERS( test_list, (std::forward_list<std::pair<long,long> >({std::make_pair(1l, 0l), std::make_pair(2l, -1l)})) );
  }

  // Extract list of lists
  iss.str( "{{-1, 3i, 1}, {1e-3, 2l, 1.0}, {-Inf, Inf}, {-pi/2, 1i, pi/2}}" );
  iss.clear();

  {
    std::forward_list<std::forward_list<double> > test_list;
    
    Utility::fromStream( iss, test_list );
    
    BOOST_CHECK_EQUAL( std::distance( test_list.begin(), test_list.end() ), 4 );

    std::forward_list<std::forward_list<double> >::const_iterator
      test_list_it = test_list.begin();
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::forward_list<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );
    
    ++test_list_it;
    
    TEST_COMPARE_FLOATING_CONTAINERS( *test_list_it,
                                      (std::forward_list<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );

    ++test_list_it;
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::forward_list<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );

    ++test_list_it;
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::forward_list<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );
  }
}

//---------------------------------------------------------------------------//
// Check that a forward_list can be placed in a stream
BOOST_AUTO_TEST_CASE( ostream )
{
  std::ostringstream oss;

  oss << std::forward_list<short>( {-1, 2} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  oss << std::forward_list<unsigned short>( {0, 10, 100} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  oss << std::forward_list<int>( {-11111, 0, 11111, 22222} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::forward_list<unsigned int>( {0, 10, 100, 1000, 10000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::forward_list<long>( {-11111, 0, 11111, 22222} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::forward_list<unsigned long>( {0, 10, 100, 1000, 10000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::forward_list<long long>( {-10000000000, 0, 10000000000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::forward_list<unsigned long long>( {0, 1000000000, 1000000000000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::forward_list<float>( {-1.0f, 0.0f, 1.0f} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  oss << std::forward_list<double>( {-1.0, 0.0, 1.0} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::forward_list<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } );
  
  BOOST_CHECK_EQUAL( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  oss << std::forward_list<std::string>( {"Test", "string"} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  oss << std::forward_list<std::pair<int, int>>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  oss << std::forward_list<std::tuple<unsigned, double, long>>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a forward_list can be extracted from a stream
BOOST_AUTO_TEST_CASE( istream )
{
  // Extract forward_list of short
  std::istringstream iss( "{-1, 2}" );

  {
    std::forward_list<short> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<short>({-1, 2}) );

    iss.str( "{-1, 2i, 2}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<short>({-1, 0, 1, 2}) );
  }

  // Extract list of unsigned short
  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::forward_list<unsigned short> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<unsigned short>({0, 10, 100}) );

    iss.str( "{0, 3i, 100}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<unsigned short>({0, 25, 50, 75, 100}) );
  }

  // Extract list of int
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::forward_list<int> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<int>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<int>({-11111, 0, 11111, 22222}) );
  }

  // Extract list of unsigned int
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::forward_list<unsigned> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<unsigned>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<unsigned>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract list of long
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::forward_list<long> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<long>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<long>({-11111, 0, 11111, 22222}) );
  }

  // Extract list of unsigned long
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::forward_list<unsigned long> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<unsigned long>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<unsigned long>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract list of long long
  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::forward_list<long long> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<long long>({-1000000000, 0, 1000000000}) );

    iss.str( "{-1000000000, 1i, 1000000000}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<long long>({-1000000000, 0, 1000000000}) );
  }

  // Extract list of unsigned long long
  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::forward_list<unsigned long long> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<unsigned long long>({0, 1000000000, 10000000000}) );

    iss.str( "{0, 1i, 10000000000}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<unsigned long long>({0, 5000000000, 10000000000}) );
  }

  // Extract list of float
  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::forward_list<float> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<float>({-1.0f, 0.0f, 1.0f}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<float>({-1.0f, -0.5f, 0.0f, 0.5f, 1.0f}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_FLOATING_CONTAINERS( test_list,
                                      std::forward_list<float>({1e-3f, 1e-2f, 1e-1f, 1.0f}),
                                      1e-7 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    iss >> test_list;
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::forward_list<float>({1.0f, 10.0f, 100.0f, 125.0f, 150.0f, 175.0f, 200.0f}) );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    iss >> test_list;
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::forward_list<float>({0.0f, (float)Utility::PhysicalConstants::pi/2, 3*(float)Utility::PhysicalConstants::pi/4, (float)Utility::PhysicalConstants::pi, 2*(float)Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    iss >> test_list;
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_list,
                                      std::forward_list<float>({-(float)Utility::PhysicalConstants::pi, -3*(float)Utility::PhysicalConstants::pi/4, -(float)Utility::PhysicalConstants::pi/2, -(float)Utility::PhysicalConstants::pi/4, 0.0}),
                                      1e-7 );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    iss >> test_list;
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::forward_list<float>({-std::numeric_limits<float>::infinity(), 0.0f, std::numeric_limits<float>::infinity()}) );
  }

  // Extract list of double
  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::forward_list<double> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<double>({-1.0, 0.0, 1.0}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<double>({-1.0, -0.5, 0.0, 0.5, 1.0}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    iss >> test_list;

    TEST_COMPARE_FLOATING_CONTAINERS( test_list,
                                      std::forward_list<double>({1e-3, 1e-2, 1e-1, 1.0}),
                                      1e-9 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    iss >> test_list;
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_list,
                                      std::forward_list<double>({1.0, 10.0, 100.0, 125.0, 150.0, 175.0, 200.0}),
                                      1e-15 );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    iss >> test_list;
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::forward_list<double>({0.0, Utility::PhysicalConstants::pi/2, 3*Utility::PhysicalConstants::pi/4, Utility::PhysicalConstants::pi, 2*Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    iss >> test_list;
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::forward_list<double>({-Utility::PhysicalConstants::pi, -3*Utility::PhysicalConstants::pi/4, -Utility::PhysicalConstants::pi/2, -Utility::PhysicalConstants::pi/4, 0.0}) );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    iss >> test_list;
    
    TEST_COMPARE_CONTAINERS( test_list,
                             std::forward_list<double>({-std::numeric_limits<float>::infinity(), 0.0, std::numeric_limits<float>::infinity()}) );
  }

  // Extract list of char
  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::forward_list<char> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  // Extract list of string
  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::list<std::string> test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, std::forward_list<std::string>({"Test","string"}) );
  }

  // Extract list of pair
  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::forward_list<std::pair<int,int> > test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, (std::forward_list<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  // Extract list of tuple
  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::forward_list<std::tuple<unsigned,double,long> > test_list;

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, (std::forward_list<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  // Extract multiple lists of pairs
  iss.str( "{{0, 1}, {-1, 2}}, {{1, 0}, {2, -1}}" );
  iss.clear();

  {
    std::forward_list<std::pair<long,long> > test_list;

    Utility::fromStream( iss, test_list, "," );

    TEST_COMPARE_CONTAINERS( test_list, (std::forward_list<std::pair<long,long> >({std::make_pair(0l, 1l), std::make_pair(-1l, 2l)})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    iss >> test_list;

    TEST_COMPARE_CONTAINERS( test_list, (std::forward_list<std::pair<long,long> >({std::make_pair(1l, 0l), std::make_pair(2l, -1l)})) );
  }

  // Extract list of lists
  iss.str( "{{-1, 3i, 1}, {1e-3, 2l, 1.0}, {-Inf, Inf}, {-pi/2, 1i, pi/2}}" );
  iss.clear();

  {
    std::forward_list<std::forward_list<double> > test_list;
    
    iss >> test_list;
    
    BOOST_CHECK_EQUAL( std::distance( test_list.begin(), test_list.end() ), 4 );

    std::forward_list<std::forward_list<double> >::const_iterator
      test_list_it = test_list.begin();
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::forward_list<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );
    
    ++test_list_it;
    
    TEST_COMPARE_FLOATING_CONTAINERS( *test_list_it,
                                      (std::forward_list<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );

    ++test_list_it;
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::forward_list<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );

    ++test_list_it;
    
    TEST_COMPARE_CONTAINERS( *test_list_it,
                             (std::forward_list<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );
  }
}


//---------------------------------------------------------------------------//
// Check that the correct comparison policies are allowed for forward lists
BOOST_AUTO_TEST_CASE_TEMPLATE( IsComparisonAllowed, T, TestTypes )
{
  typedef std::forward_list<T> List;

  BOOST_CHECK( Utility::ComparisonTraits<List>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<List>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<List>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<List>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<List>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<List>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<List>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<List>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<const List>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const List>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const List>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const List>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const List>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const List>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const List>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const List>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );
}

//---------------------------------------------------------------------------//
// Check that lists can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, PolicyTypePair, TestPolicyTypes )
{
  typedef typename Utility::TupleElement<0,PolicyTypePair>::type Policy;
  typedef typename Utility::TupleElement<1,PolicyTypePair>::type T;

  std::forward_list<T> left_list({T(0), T(1), T(2)});
  std::forward_list<T> right_list({T(0), T(1), T(2)});

  std::ostringstream oss;

  // No details logging
  bool compare_result = Utility::compare<Policy,0>( left_list, "lhs",
                                                    right_list, "rhs",
                                                    oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( !compare_result );
  else
    BOOST_CHECK( compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_list, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_list, "lhs",
                                               {}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {T(1),T(1),T(1)}, "lhs",
                                               right_list, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_list, "lhs",
                                               {T(1),T(1),T(1)}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  // Details logging
  T tol( 1e-6 );

  compare_result = Utility::compare<Policy,0>( left_list, "lhs",
                                               right_list, "rhs",
                                               oss, tol, true );

  std::string expected_details =
    Utility::createComparisonHeader<Policy,0>( left_list, "lhs",
                                               right_list, "rhs",
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
               std::distance(left_list.begin(),left_list.end()), "lhs", true,
               std::distance(right_list.begin(),right_list.end()), "rhs", true,
               ".size()", local_oss, true );

    auto left_list_it = left_list.begin();
    auto left_list_end = left_list.end();
    auto right_list_it = right_list.begin();
    
    while( left_list_it != left_list_end )
    {
      Utility::ComparisonTraits<T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                *left_list_it, "lhs", true,
                *right_list_it, "rhs", true,
                std::string("[") + Utility::toString(std::distance(left_list.begin(),left_list_it)) + "]", local_oss, true,
                tol );
      ++left_list_it;
      ++right_list_it;
    }

    expected_details += "passed\n";
    expected_details += local_oss.str();

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( {T(1), T(1), T(1)}, "lhs",
                                               right_list, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {T(1), T(1), T(1)}, "lhs",
                                               right_list, "rhs",
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
               3, "lhs", false,
               std::distance(right_list.begin(),right_list.end()), "rhs", true,
               ".size()", local_oss, true );
    auto right_list_it = right_list.begin();
    auto right_list_end = right_list.end();
    
    while( right_list_it != right_list_end )
    {
      Utility::ComparisonTraits<T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                T(1), "lhs", false,
                *right_list_it, "rhs", true,
                std::string("[") + Utility::toString(std::distance(right_list.begin(),right_list_it)) + "]", local_oss, true,
                tol );
      ++right_list_it;
    }

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_list, "lhs",
                                               {T(1), T(1), T(1)}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_list, "lhs",
                                               {T(1), T(1), T(1)}, "rhs",
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
                 std::distance(left_list.begin(),left_list.end()), "lhs", true,
                 3, "rhs", false,
                 ".size()", local_oss, true );

    auto left_list_it = left_list.begin();
    auto left_list_end = left_list.end();
    
    while( left_list_it != left_list_end )
    {
      Utility::ComparisonTraits<T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                *left_list_it, "lhs", true,
                T(1), "rhs", false,
                std::string("[") + Utility::toString(std::distance(left_list.begin(),left_list_it)) + "]", local_oss, true,
                tol );
      ++left_list_it;
    }

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// end tstList.cpp
//---------------------------------------------------------------------------//
