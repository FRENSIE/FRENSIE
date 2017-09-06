//---------------------------------------------------------------------------//
//!
//! \file   tstDeque.cpp
//! \author Alex Robinson
//! \brief  Deque helper function unit tests
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
#include "Utility_Deque.hpp"
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
// Tests.
//---------------------------------------------------------------------------//
// Check that a deque can be converted to a string
BOOST_AUTO_TEST_CASE( toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( std::deque<short>( {-1, 2} ) ),
                       "{-1, 2}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::deque<unsigned short>( {0, 10, 100} ) ),
                       "{0, 10, 100}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::deque<int>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::deque<unsigned int>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::deque<long>( {-11111, 0, 11111, 22222} ) ),
                       "{-11111, 0, 11111, 22222}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::deque<unsigned long>( {0, 10, 100, 1000, 10000} ) ),
                       "{0, 10, 100, 1000, 10000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::deque<long long>( {-10000000000, 0, 10000000000} ) ),
                       "{-10000000000, 0, 10000000000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::deque<unsigned long long>( {0, 1000000000, 1000000000000} ) ),
                       "{0, 1000000000, 1000000000000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::deque<float>( {-1.0f, 0.0f, 1.0f} ) ),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::deque<double>( {-1.0, 0.0, 1.0} ) ),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::deque<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) ),
                       "{T, e, s, t,  , s, t, r, i, n, g}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::deque<std::string>( {"Test", "string"} ) ),
                       "{Test, string}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::deque<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) ),
                       "{{0, 1}, {-1, 2}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::deque<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) ),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a deque can be placed in a stream
BOOST_AUTO_TEST_CASE( toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::deque<short>( {-1, 2} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<unsigned short>( {0, 10, 100} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<int>( {-11111, 0, 11111, 22222} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<unsigned int>( {0, 10, 100, 1000, 10000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<long>( {-11111, 0, 11111, 22222} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<unsigned long>( {0, 10, 100, 1000, 10000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<long long>( {-10000000000, 0, 10000000000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<unsigned long long>( {0, 1000000000, 1000000000000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<float>( {-1.0f, 0.0f, 1.0f} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<double>( {-1.0, 0.0, 1.0} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<std::string>( {"Test", "string"} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<std::pair<int, int>>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::deque<std::tuple<unsigned, double, long>>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a deque can be created from a string
BOOST_AUTO_TEST_CASE( fromString )
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
BOOST_AUTO_TEST_CASE( fromStream )
{
  // Extract deque of short
  std::istringstream iss( "{-1, 2}" );

  {
    std::deque<short> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<short>({-1, 2}) );

    iss.str( "{-1, 2i, 2}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<short>({-1, 0, 1, 2}) );
  }

  // Extract deque of unsigned short
  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::deque<unsigned short> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned short>({0, 10, 100}) );

    iss.str( "{0, 3i, 100}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned short>({0, 25, 50, 75, 100}) );
  }

  // Extract deque of int
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::deque<int> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<int>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<int>({-11111, 0, 11111, 22222}) );
  }

  // Extract deque of unsigned int
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::deque<unsigned> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract deque of long
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::deque<long> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<long>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<long>({-11111, 0, 11111, 22222}) );
  }

  // Extract deque of unsigned long
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::deque<unsigned long> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned long>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned long>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract deque of long long
  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::deque<long long> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<long long>({-1000000000, 0, 1000000000}) );

    iss.str( "{-1000000000, 1i, 1000000000}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<long long>({-1000000000, 0, 1000000000}) );
  }

  // Extract deque of unsigned long long
  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::deque<unsigned long long> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned long long>({0, 1000000000, 10000000000}) );

    iss.str( "{0, 1i, 10000000000}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned long long>({0, 5000000000, 10000000000}) );
  }

  // Extract deque of float
  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::deque<float> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<float>({-1.0f, 0.0f, 1.0f}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<float>({-1.0f, -0.5f, 0.0f, 0.5f, 1.0f}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_FLOATING_CONTAINERS( test_deque,
                                      std::deque<float>({1e-3f, 1e-2f, 1e-1f, 1.0f}),
                                      1e-7 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );
    
    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<float>({1.0f, 10.0f, 100.0f, 125.0f, 150.0f, 175.0f, 200.0f}) );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );
    
    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<float>({0.0f, (float)Utility::PhysicalConstants::pi/2, 3*(float)Utility::PhysicalConstants::pi/4, (float)Utility::PhysicalConstants::pi, 2*(float)Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_deque,
                                      std::deque<float>({-(float)Utility::PhysicalConstants::pi, -3*(float)Utility::PhysicalConstants::pi/4, -(float)Utility::PhysicalConstants::pi/2, -(float)Utility::PhysicalConstants::pi/4, 0.0}),
                                      1e-7 );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );
    
    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<float>({-std::numeric_limits<float>::infinity(), 0.0f, std::numeric_limits<float>::infinity()}) );
  }

  // Extract deque of double
  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::deque<double> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<double>({-1.0, 0.0, 1.0}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<double>({-1.0, -0.5, 0.0, 0.5, 1.0}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_FLOATING_CONTAINERS( test_deque,
                                      std::deque<double>({1e-3, 1e-2, 1e-1, 1.0}),
                                      1e-9 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_deque,
                                      std::deque<double>({1.0, 10.0, 100.0, 125.0, 150.0, 175.0, 200.0}),
                                      1e-15 );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );
    
    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<double>({0.0, Utility::PhysicalConstants::pi/2, 3*Utility::PhysicalConstants::pi/4, Utility::PhysicalConstants::pi, 2*Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );
    
    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<double>({-Utility::PhysicalConstants::pi, -3*Utility::PhysicalConstants::pi/4, -Utility::PhysicalConstants::pi/2, -Utility::PhysicalConstants::pi/4, 0.0}) );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    Utility::fromStream( iss, test_deque );
    
    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<double>({-std::numeric_limits<float>::infinity(), 0.0, std::numeric_limits<float>::infinity()}) );
  }

  // Extract deque of char
  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::deque<char> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  // Extract deque of string
  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::deque<std::string> test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<std::string>({"Test","string"}) );
  }

  // Extract deque of pair
  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::deque<std::pair<int,int> > test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, (std::deque<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  // Extract deque of tuple
  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::deque<std::tuple<unsigned,double,long> > test_deque;

    Utility::fromStream( iss, test_deque );

    TEST_COMPARE_CONTAINERS( test_deque, (std::deque<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  // Extract multiple deques of pairs
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

  // Extract deque of deques
  iss.str( "{{-1, 3i, 1}, {1e-3, 2l, 1.0}, {-Inf, Inf}, {-pi/2, 1i, pi/2}}" );
  iss.clear();

  {
    std::deque<std::deque<double> > test_deque;
    
    Utility::fromStream( iss, test_deque );
    
    BOOST_CHECK_EQUAL( test_deque.size(), 4 );

    std::deque<std::deque<double> >::const_iterator
      test_deque_it = test_deque.begin();
      
    TEST_COMPARE_CONTAINERS( *test_deque_it,
                             (std::deque<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );

    ++test_deque_it;
    
    TEST_COMPARE_FLOATING_CONTAINERS( *test_deque_it,
                                      (std::deque<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );

    ++test_deque_it;
    
    TEST_COMPARE_CONTAINERS( *test_deque_it,
                             (std::deque<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );

    ++test_deque_it;
    
    TEST_COMPARE_CONTAINERS( *test_deque_it,
                             (std::deque<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );
  }
}

//---------------------------------------------------------------------------//
// Check that a deque can be placed in a stream
BOOST_AUTO_TEST_CASE( ostream )
{
  std::ostringstream oss;

  oss << std::deque<short>( {-1, 2} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<unsigned short>( {0, 10, 100} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<int>( {-11111, 0, 11111, 22222} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<unsigned int>( {0, 10, 100, 1000, 10000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<long>( {-11111, 0, 11111, 22222} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<unsigned long>( {0, 10, 100, 1000, 10000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<long long>( {-10000000000, 0, 10000000000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<unsigned long long>( {0, 1000000000, 1000000000000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<float>( {-1.0f, 0.0f, 1.0f} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  oss << std::deque<double>( {-1.0, 0.0, 1.0} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } );
  
  BOOST_CHECK_EQUAL( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<std::string>( {"Test", "string"} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<std::pair<int, int>>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  oss << std::deque<std::tuple<unsigned, double, long>>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a deque can be extracted from a stream
BOOST_AUTO_TEST_CASE( istream )
{
  // Extract deque of short
  std::istringstream iss( "{-1, 2}" );

  {
    std::deque<short> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<short>({-1, 2}) );

    iss.str( "{-1, 2i, 2}" );
    iss.clear();

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<short>({-1, 0, 1, 2}) );
  }

  // Extract deque of unsigned short
  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::deque<unsigned short> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned short>({0, 10, 100}) );

    iss.str( "{0, 3i, 100}" );
    iss.clear();

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned short>({0, 25, 50, 75, 100}) );
  }

  // Extract deque of int
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::deque<int> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<int>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<int>({-11111, 0, 11111, 22222}) );
  }

  // Extract deque of unsigned int
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::deque<unsigned> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract deque of long
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::deque<long> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<long>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<long>({-11111, 0, 11111, 22222}) );
  }

  // Extract deque of unsigned long
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::deque<unsigned long> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned long>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned long>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract deque of long long
  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::deque<long long> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<long long>({-1000000000, 0, 1000000000}) );

    iss.str( "{-1000000000, 1i, 1000000000}" );
    iss.clear();

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<long long>({-1000000000, 0, 1000000000}) );
  }

  // Extract deque of unsigned long long
  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::deque<unsigned long long> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned long long>({0, 1000000000, 10000000000}) );

    iss.str( "{0, 1i, 10000000000}" );
    iss.clear();

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<unsigned long long>({0, 5000000000, 10000000000}) );
  }

  // Extract deque of float
  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::deque<float> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<float>({-1.0f, 0.0f, 1.0f}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<float>({-1.0f, -0.5f, 0.0f, 0.5f, 1.0f}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    iss >> test_deque;

    TEST_COMPARE_FLOATING_CONTAINERS( test_deque,
                                      std::deque<float>({1e-3f, 1e-2f, 1e-1f, 1.0f}),
                                      1e-7 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    iss >> test_deque;
    
    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<float>({1.0f, 10.0f, 100.0f, 125.0f, 150.0f, 175.0f, 200.0f}) );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    iss >> test_deque;
    
    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<float>({0.0f, (float)Utility::PhysicalConstants::pi/2, 3*(float)Utility::PhysicalConstants::pi/4, (float)Utility::PhysicalConstants::pi, 2*(float)Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    iss >> test_deque;
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_deque,
                                      std::deque<float>({-(float)Utility::PhysicalConstants::pi, -3*(float)Utility::PhysicalConstants::pi/4, -(float)Utility::PhysicalConstants::pi/2, -(float)Utility::PhysicalConstants::pi/4, 0.0}),
                                      1e-7 );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    iss >> test_deque;
    
    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<float>({-std::numeric_limits<float>::infinity(), 0.0f, std::numeric_limits<float>::infinity()}) );
  }

  // Extract deque of double
  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::deque<double> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<double>({-1.0, 0.0, 1.0}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<double>({-1.0, -0.5, 0.0, 0.5, 1.0}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    iss >> test_deque;

    TEST_COMPARE_FLOATING_CONTAINERS( test_deque,
                                      std::deque<double>({1e-3, 1e-2, 1e-1, 1.0}),
                                      1e-9 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    iss >> test_deque;
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_deque,
                                      std::deque<double>({1.0, 10.0, 100.0, 125.0, 150.0, 175.0, 200.0}),
                                      1e-15 );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    iss >> test_deque;
    
    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<double>({0.0, Utility::PhysicalConstants::pi/2, 3*Utility::PhysicalConstants::pi/4, Utility::PhysicalConstants::pi, 2*Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    iss >> test_deque;
    
    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<double>({-Utility::PhysicalConstants::pi, -3*Utility::PhysicalConstants::pi/4, -Utility::PhysicalConstants::pi/2, -Utility::PhysicalConstants::pi/4, 0.0}) );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    iss >> test_deque;
    
    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<double>({-std::numeric_limits<float>::infinity(), 0.0, std::numeric_limits<float>::infinity()}) );
  }

  // Extract deque of char
  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::deque<char> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  // Extract deque of string
  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::deque<std::string> test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, std::deque<std::string>({"Test","string"}) );
  }

  // Extract deque of pair
  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::deque<std::pair<int,int> > test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, (std::deque<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  // Extract deque of tuple
  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::deque<std::tuple<unsigned,double,long> > test_deque;

    iss >> test_deque;

    TEST_COMPARE_CONTAINERS( test_deque, (std::deque<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  // Extract multiple deques of pairs
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

  // Extract deque of deques
  iss.str( "{{-1, 3i, 1}, {1e-3, 2l, 1.0}, {-Inf, Inf}, {-pi/2, 1i, pi/2}}" );
  iss.clear();

  {
    std::deque<std::deque<double> > test_deque;
    
    iss >> test_deque;
    
    BOOST_CHECK_EQUAL( test_deque.size(), 4 );

    std::deque<std::deque<double> >::const_iterator
      test_deque_it = test_deque.begin();
      
    TEST_COMPARE_CONTAINERS( *test_deque_it,
                             (std::deque<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );

    ++test_deque_it;
    
    TEST_COMPARE_FLOATING_CONTAINERS( *test_deque_it,
                                      (std::deque<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );

    ++test_deque_it;
    
    TEST_COMPARE_CONTAINERS( *test_deque_it,
                             (std::deque<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );

    ++test_deque_it;
    
    TEST_COMPARE_CONTAINERS( *test_deque_it,
                             (std::deque<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );
  }
}

//---------------------------------------------------------------------------//
// Check that a vector can mimic stream behavior
BOOST_AUTO_TEST_CASE( stream_mimic )
{
  {
    std::deque<short> test_deque;

    test_deque << -1 << 0 << 1;

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<short>( {-1, 0, 1} ) );

    short element0, element1, element2;

    test_deque >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -1 );
    BOOST_CHECK_EQUAL( element1, 0 );
    BOOST_CHECK_EQUAL( element2, 1 );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );

    test_deque << "-1" << 0 << "1";

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<short>( {-1, 0, 1} ) );

    std::string element0_str, element1_str, element2_str;

    test_deque >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-1" );
    BOOST_CHECK_EQUAL( element1_str, "0" );
    BOOST_CHECK_EQUAL( element2_str, "1" );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );
  }

  {
    std::deque<unsigned short> test_deque;

    test_deque << 0 << 10 << 100;

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<unsigned short>( {0, 10, 100} ) );

    unsigned short element0, element1, element2;

    test_deque >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, 0 );
    BOOST_CHECK_EQUAL( element1, 10 );
    BOOST_CHECK_EQUAL( element2, 100 );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );

    test_deque << "0" << 10 << "100";

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<unsigned short>( {0, 10, 100} ) );

    std::string element0_str, element1_str, element2_str;

    test_deque >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "0" );
    BOOST_CHECK_EQUAL( element1_str, "10" );
    BOOST_CHECK_EQUAL( element2_str, "100" );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );
  }

  {
    std::deque<int> test_deque;

    test_deque << -11111 << 0 << 11111;

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<int>( {-11111, 0, 11111} ) );

    int element0, element1, element2;

    test_deque >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -11111 );
    BOOST_CHECK_EQUAL( element1, 0 );
    BOOST_CHECK_EQUAL( element2, 11111 );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );

    test_deque << "-11111" << 0 << "11111";

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<int>( {-11111, 0, 11111} ) );

    std::string element0_str, element1_str, element2_str;

    test_deque >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-11111" );
    BOOST_CHECK_EQUAL( element1_str, "0" );
    BOOST_CHECK_EQUAL( element2_str, "11111" );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );
  }

  {
    std::deque<unsigned int> test_deque;

    test_deque << 0 << 1000 << 1000000;

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<unsigned int>( {0, 1000, 1000000} ) );

    unsigned int element0, element1, element2;

    test_deque >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, 0 );
    BOOST_CHECK_EQUAL( element1, 1000 );
    BOOST_CHECK_EQUAL( element2, 1000000 );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );

    test_deque << "0" << 1000 << "1000000";

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<unsigned int>( {0, 1000, 1000000} ) );

    std::string element0_str, element1_str, element2_str;

    test_deque >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "0" );
    BOOST_CHECK_EQUAL( element1_str, "1000" );
    BOOST_CHECK_EQUAL( element2_str, "1000000" );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );
  }

  {
    std::deque<long> test_deque;

    test_deque << -11111l << 0l << 11111l;

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<long>( {-11111l, 0l, 11111l} ) );

    long element0, element1, element2;

    test_deque >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -11111l );
    BOOST_CHECK_EQUAL( element1, 0l );
    BOOST_CHECK_EQUAL( element2, 11111l );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );

    test_deque << "-11111" << 0 << "11111";

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<long>( {-11111l, 0l, 11111l} ) );

    std::string element0_str, element1_str, element2_str;

    test_deque >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-11111" );
    BOOST_CHECK_EQUAL( element1_str, "0" );
    BOOST_CHECK_EQUAL( element2_str, "11111" );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );
  }

  {
    std::deque<unsigned long> test_deque;

    test_deque << 0ul << 1000ul << 1000000ul;

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<unsigned long>( {0ul, 1000ul, 1000000ul} ) );

    unsigned long element0, element1, element2;

    test_deque >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, 0ul );
    BOOST_CHECK_EQUAL( element1, 1000ul );
    BOOST_CHECK_EQUAL( element2, 1000000ul );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );

    test_deque << "0" << 1000 << "1000000";

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<unsigned long>( {0ul, 1000ul, 1000000ul} ) );

    std::string element0_str, element1_str, element2_str;

    test_deque >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "0" );
    BOOST_CHECK_EQUAL( element1_str, "1000" );
    BOOST_CHECK_EQUAL( element2_str, "1000000" );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );
  }
  
  {
    std::deque<long long> test_deque;

    test_deque << -10000000000ll << 0ll << 10000000000ll;

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<long long>( {-10000000000ll, 0ll, 10000000000ll} ) );

    long long element0, element1, element2;

    test_deque >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -10000000000ll );
    BOOST_CHECK_EQUAL( element1, 0ll );
    BOOST_CHECK_EQUAL( element2, 10000000000ll );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );

    test_deque << "-10000000000" << 0 << "10000000000";

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<long long>( {-10000000000ll, 0ll, 10000000000ll} ) );

    std::string element0_str, element1_str, element2_str;

    test_deque >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-10000000000" );
    BOOST_CHECK_EQUAL( element1_str, "0" );
    BOOST_CHECK_EQUAL( element2_str, "10000000000" );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );
  }

  {
    std::deque<unsigned long long> test_deque;

    test_deque << 0ull << 10000000000ull << 100000000000ull;

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<unsigned long long>( {0ull, 10000000000ull, 100000000000ull} ) );

    unsigned long long element0, element1, element2;

    test_deque >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, 0ull );
    BOOST_CHECK_EQUAL( element1, 10000000000ull );
    BOOST_CHECK_EQUAL( element2, 100000000000ull );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );

    test_deque << "0" << 10000000000ull << "100000000000";

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<unsigned long long>( {0ull, 10000000000ull, 100000000000ull} ) );

    std::string element0_str, element1_str, element2_str;

    test_deque >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "0" );
    BOOST_CHECK_EQUAL( element1_str, "10000000000" );
    BOOST_CHECK_EQUAL( element2_str, "100000000000" );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );
  }

  {
    std::deque<float> test_deque;

    test_deque << -1.0f << 0.0f << 1.0f;

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<float>( {-1.0f, 0.0f, 1.0f} ) );

    float element0, element1, element2;

    test_deque >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -1.0f );
    BOOST_CHECK_EQUAL( element1, 0.0f );
    BOOST_CHECK_EQUAL( element2, 1.0f );

    test_deque << "-2pi/3" << "0" << "Inf";

    test_deque >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -2*(float)Utility::PhysicalConstants::pi/3 );
    BOOST_CHECK_EQUAL( element1, 0.0f );
    BOOST_CHECK_EQUAL( element2, std::numeric_limits<float>::infinity() );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );

    test_deque << -1.0f << 0.0f << 1.0f;

    std::string element0_str, element1_str, element2_str;

    test_deque >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-1.000000000e+00" );
    BOOST_CHECK_EQUAL( element1_str, "0.000000000e+00" );
    BOOST_CHECK_EQUAL( element2_str, "1.000000000e+00" );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );
  }

  {
    std::deque<double> test_deque;

    test_deque << -1.0 << 0.0 << 1.0;

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<double>( {-1.0, 0.0, 1.0} ) );

    double element0, element1, element2;

    test_deque >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -1.0 );
    BOOST_CHECK_EQUAL( element1, 0.0 );
    BOOST_CHECK_EQUAL( element2, 1.0 );

    test_deque << "-infty" << "0" << "pi/3";

    test_deque >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -std::numeric_limits<double>::infinity() );
    BOOST_CHECK_EQUAL( element1, 0.0 );
    BOOST_CHECK_EQUAL( element2, Utility::PhysicalConstants::pi/3 );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );

    test_deque << -1.0 << 0.0 << 1.0;

    std::string element0_str, element1_str, element2_str;

    test_deque >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-1.000000000000000000e+00" );
    BOOST_CHECK_EQUAL( element1_str, "0.000000000000000000e+00" );
    BOOST_CHECK_EQUAL( element2_str, "1.000000000000000000e+00" );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );
  }

  {
    std::deque<char> test_deque;

    test_deque << 'T' << 'e' << 's' << 't' << ' '
                << 's' << 't' << 'r' << 'i' << 'n' << 'g';

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'} ) );

    std::string elements( "           " );

    test_deque >> elements[10] >> elements[9] >> elements[8] >> elements[7]
                >> elements[6] >> elements[5] >> elements[4] >> elements[3]
                >> elements[2] >> elements[1] >> elements[0];

    BOOST_CHECK_EQUAL( elements, "Test string" );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );
  }
  
  {
    std::deque<std::string> test_deque;

    test_deque << "Test" << "string";

    TEST_COMPARE_CONTAINERS( test_deque,
                             std::deque<std::string>( {"Test", "string"} ) );

    std::string element0, element1;

    test_deque >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, "Test" );
    BOOST_CHECK_EQUAL( element1, "string" );
  }

  {
    std::deque<std::pair<int, int> > test_deque;

    test_deque << std::make_pair( 0, 1 ) << std::make_pair( -1, 2 );

    TEST_COMPARE_CONTAINERS( test_deque,
                             (std::deque<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} )) );

    std::pair<int,int> element0, element1;

    test_deque >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, std::make_pair( 0, 1 ) );
    BOOST_CHECK_EQUAL( element1, std::make_pair( -1, 2 ) );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );

    test_deque << "{0, 1}" << "{-1, 2}";

    test_deque >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, std::make_pair( 0, 1 ) );
    BOOST_CHECK_EQUAL( element1, std::make_pair( -1, 2 ) );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );

    test_deque << "{0, 1}" << std::make_pair( -1, 2 );

    std::string element0_str, element1_str;

    test_deque >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "{0, 1}" );
    BOOST_CHECK_EQUAL( element1_str, "{-1, 2}" );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );
  }

  {
    std::deque<std::tuple<unsigned, double, long> > test_deque;

    test_deque << std::make_tuple( 0u, 1.0, -100000l )
                << std::make_tuple( 1u, -1.0, 100001l );

    TEST_COMPARE_CONTAINERS( test_deque,
                             (std::deque<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} )) );

    std::tuple<unsigned, double, long> element0, element1;

    test_deque >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, std::make_tuple( 0u, 1.0, -100000l ) );
    BOOST_CHECK_EQUAL( element1, std::make_tuple( 1u, -1.0, 100001l ) );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );

    test_deque << "{0, 1, -100000}" << "{1, -1, 100001}";

    test_deque >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, std::make_tuple( 0u, 1.0, -100000l ) );
    BOOST_CHECK_EQUAL( element1, std::make_tuple( 1u, -1.0, 100001l ) );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );

    test_deque << "{0, 1, -100000}" << std::make_tuple( 1u, -1.0, 100001l );

    std::string element0_str, element1_str;

    test_deque >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "{0, 1.000000000000000000e+00, -100000}" );
    BOOST_CHECK_EQUAL( element1_str, "{1, -1.000000000000000000e+00, 100001}" );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );
  }

  {
    std::deque<std::deque<double> > test_deque;

    test_deque << std::deque<double>( {-1, -0.5, 0.0, 0.5, 1.0} )
                << std::deque<double>( {1e-3, 1e-2, 1e-1, 1.0} )
                << std::deque<double>( {-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()} )
                << std::deque<double>( {-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2} );

    BOOST_CHECK_EQUAL( test_deque.size(), 4 );

    std::deque<std::deque<double> >::const_iterator
      test_deque_it = test_deque.begin();
    
    TEST_COMPARE_CONTAINERS( *test_deque_it,
                             (std::deque<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );

    ++test_deque_it;
    
    TEST_COMPARE_FLOATING_CONTAINERS( *test_deque_it,
                                      (std::deque<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );

    ++test_deque_it;
    
    TEST_COMPARE_CONTAINERS( *test_deque_it,
                             (std::deque<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );

    ++test_deque_it;
    
    TEST_COMPARE_CONTAINERS( *test_deque_it,
                             (std::deque<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );

    std::deque<double> element0, element1, element2, element3;
    
    test_deque >> element3 >> element2 >> element1 >> element0;
    
    TEST_COMPARE_CONTAINERS( element0,
                             (std::deque<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );
    TEST_COMPARE_FLOATING_CONTAINERS( element1,
                                      (std::deque<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );
    TEST_COMPARE_CONTAINERS( element2,
                             (std::deque<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );
    TEST_COMPARE_CONTAINERS( element3,
                             (std::deque<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );

    test_deque << "{-1, 3i, 1}" << "{1e-3, 2l, 1.0}"
                << "{-Inf, Inf}" << "{-pi/2, 1i, pi/2}";

    BOOST_CHECK_EQUAL( test_deque.size(), 4 );

    test_deque_it = test_deque.begin();
    
    TEST_COMPARE_CONTAINERS( *test_deque_it,
                             (std::deque<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );

    ++test_deque_it;
    
    TEST_COMPARE_FLOATING_CONTAINERS( *test_deque_it,
                                      (std::deque<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );

    ++test_deque_it;
    
    TEST_COMPARE_CONTAINERS( *test_deque_it,
                             (std::deque<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );

    ++test_deque_it;
    
    TEST_COMPARE_CONTAINERS( *test_deque_it,
                             (std::deque<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );

    std::string element0_str, element1_str, element2_str, element3_str;

    test_deque >> element3_str >> element2_str
                >> element1_str >> element0_str;

    BOOST_CHECK( element0_str.size() > 0 );
    BOOST_CHECK( element1_str.size() > 0 );
    BOOST_CHECK( element2_str.size() > 0 );
    BOOST_CHECK( element3_str.size() > 0 );
    BOOST_CHECK_EQUAL( test_deque.size(), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the correct comparison policies are allowed for deques
BOOST_AUTO_TEST_CASE_TEMPLATE( IsComparisonAllowed, T, TestTypes )
{
  typedef std::deque<T> Deque;

  BOOST_CHECK( Utility::ComparisonTraits<Deque>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<Deque>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Deque>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Deque>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Deque>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Deque>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<Deque>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<Deque>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<const Deque>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const Deque>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Deque>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Deque>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Deque>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Deque>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const Deque>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const Deque>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );
}

//---------------------------------------------------------------------------//
// Check that deques can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, PolicyTypePair, TestPolicyTypes )
{
  typedef typename Utility::TupleElement<0,PolicyTypePair>::type Policy;
  typedef typename Utility::TupleElement<1,PolicyTypePair>::type T;

  std::deque<T> left_deque({T(0), T(1), T(2)});
  std::deque<T> right_deque({T(0), T(1), T(2)});

  std::ostringstream oss;

  // No details logging
  bool compare_result = Utility::compare<Policy,0>( left_deque, "lhs",
                                                    right_deque, "rhs",
                                                    oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( !compare_result );
  else
    BOOST_CHECK( compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_deque, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_deque, "lhs",
                                               {}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {T(1),T(1),T(1)}, "lhs",
                                               right_deque, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_deque, "lhs",
                                               {T(1),T(1),T(1)}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  // Details logging
  T tol( 1e-6 );

  compare_result = Utility::compare<Policy,0>( left_deque, "lhs",
                                               right_deque, "rhs",
                                               oss, tol, true );

  std::string expected_details =
    Utility::createComparisonHeader<Policy,0>( left_deque, "lhs",
                                               right_deque, "rhs",
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
                                              left_deque.size(), "lhs", true,
                                              right_deque.size(), "rhs", true,
                                              ".size()", local_oss, true );

    auto left_deque_it = left_deque.begin();
    auto left_deque_end = left_deque.end();
    auto right_deque_it = right_deque.begin();
    
    while( left_deque_it != left_deque_end )
    {
      Utility::ComparisonTraits<T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                *left_deque_it, "lhs", true,
                *right_deque_it, "rhs", true,
                std::string("[") + Utility::toString(std::distance(left_deque.begin(),left_deque_it)) + "]", local_oss, true,
                tol );
      ++left_deque_it;
      ++right_deque_it;
    }

    expected_details += "passed\n";
    expected_details += local_oss.str();

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( {T(1), T(1), T(1)}, "lhs",
                                               right_deque, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {T(1), T(1), T(1)}, "lhs",
                                               right_deque, "rhs",
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
                                              right_deque.size(), "rhs", true,
                                              ".size()", local_oss, true );
    auto right_deque_it = right_deque.begin();
    auto right_deque_end = right_deque.end();
    
    while( right_deque_it != right_deque_end )
    {
      Utility::ComparisonTraits<T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                T(1), "lhs", false,
                *right_deque_it, "rhs", true,
                std::string("[") + Utility::toString(std::distance(right_deque.begin(),right_deque_it)) + "]", local_oss, true,
                tol );
      ++right_deque_it;
    }

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_deque, "lhs",
                                               {T(1), T(1), T(1)}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_deque, "lhs",
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
                                               left_deque.size(), "lhs", true,
                                               3, "rhs", false,
                                               ".size()", local_oss, true );

    auto left_deque_it = left_deque.begin();
    auto left_deque_end = left_deque.end();
    
    while( left_deque_it != left_deque_end )
    {
      Utility::ComparisonTraits<T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                *left_deque_it, "lhs", true,
                T(1), "rhs", false,
                std::string("[") + Utility::toString(std::distance(left_deque.begin(),left_deque_it)) + "]", local_oss, true,
                tol );
      ++left_deque_it;
    }

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();
}

//---------------------------------------------------------------------------//
// end tstDeque.cpp
//---------------------------------------------------------------------------//
