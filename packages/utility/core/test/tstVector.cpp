//---------------------------------------------------------------------------//
//!
//! \file   tstVector.cpp
//! \author Alex Robinson
//! \brief  Vector helper function unit tests
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
#include "Utility_Vector.hpp"
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
    BOOST_REQUIRE_EQUAL( left_container.size(), right_container.size() ); \
                                                                        \
    for( size_t i = 0; i < left_container_ref.size(); ++i )             \
    {                                                                 \
      BOOST_CHECK_CLOSE_FRACTION( left_container[i], right_container[i], tol ); \
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
// Check that a vector can be converted to a string
BOOST_AUTO_TEST_CASE( toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<short>() ), "{}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<short>( {-1, 2} ) ),
                     "{-1, 2}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<unsigned short>( {0, 10, 100} ) ),
                     "{0, 10, 100}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<int>( {-11111, 0, 11111, 22222} ) ),
                     "{-11111, 0, 11111, 22222}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<unsigned int>( {0, 10, 100, 1000, 10000} ) ),
                     "{0, 10, 100, 1000, 10000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<long>( {-11111, 0, 11111, 22222} ) ),
                     "{-11111, 0, 11111, 22222}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<unsigned long>( {0, 10, 100, 1000, 10000} ) ),
                     "{0, 10, 100, 1000, 10000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<long long>( {-10000000000, 0, 10000000000} ) ),
                     "{-10000000000, 0, 10000000000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<unsigned long long>( {0, 1000000000, 1000000000000} ) ),
                     "{0, 1000000000, 1000000000000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<float>( {-1.0f, 0.0f, 1.0f} ) ),
                     "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<double>( {-1.0, 0.0, 1.0} ) ),
                     "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<char>() ), "{}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) ),
                     "{T, e, s, t,  , s, t, r, i, n, g}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<std::string>() ), "{}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<std::string>( {"Test", "string"} ) ),
                     "{Test, string}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) ),
                     "{{0, 1}, {-1, 2}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::vector<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) ),
                     "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a vector can be placed in a stream
BOOST_AUTO_TEST_CASE( toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::vector<short>( {-1, 2} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<unsigned short>( {0, 10, 100} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<int>( {-11111, 0, 11111, 22222} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<unsigned int>( {0, 10, 100, 1000, 10000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<long>( {-11111, 0, 11111, 22222} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<unsigned long>( {0, 10, 100, 1000, 10000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<long long>( {-10000000000, 0, 10000000000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<unsigned long long>( {0, 1000000000, 1000000000000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<float>( {-1.0f, 0.0f, 1.0f} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<double>( {-1.0, 0.0, 1.0} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<std::string>( {"Test", "string"} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<std::pair<int, int>>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::vector<std::tuple<unsigned, double, long>>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// CHeck that a vector iterator can be converted to a string
BOOST_AUTO_TEST_CASE( toString_iterator )
{
  std::vector<double> double_vector( {-1.0, 0.0, 1.0} );

  std::string iterator_string = Utility::toString(double_vector.begin());
  
  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString(double_vector.cbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString(double_vector.rbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString(double_vector.crbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  std::vector<int> int_vector( {-1, 0, 1} );

  iterator_string = Utility::toString(int_vector.begin());
  
  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString(int_vector.cbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString(int_vector.rbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );

  iterator_string = Utility::toString(int_vector.crbegin() );

  BOOST_CHECK( iterator_string.find( "x" ) < iterator_string.size() );
}

//---------------------------------------------------------------------------//
// CHeck that a vector iterator can be converted to a string
BOOST_AUTO_TEST_CASE( toStream_iterator )
{
  std::vector<double> double_vector( {-1.0, 0.0, 1.0} );

  std::ostringstream oss;

  Utility::toStream( oss, double_vector.begin() );
  
  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, double_vector.cbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, double_vector.rbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, double_vector.crbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  std::vector<int> int_vector( {-1, 0, 1} );

  Utility::toStream( oss, int_vector.begin());
  
  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, int_vector.cbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, int_vector.rbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, int_vector.crbegin() );

  BOOST_CHECK( oss.str().find( "x" ) < oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that a vector can be created from a string
BOOST_AUTO_TEST_CASE( fromString )
{
  // Extract vector of short
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<short> >( "{}" )),
                           std::vector<short>() );
  
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<short> >( "{-1, 2}" )),
                           std::vector<short>({-1, 2}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<short> >( "{-1r1, 2}" )),
                           std::vector<short>({-1, 2}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<short> >( "{-1r3, 2}" )),
                           std::vector<short>({-1, -1, -1, 2}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<short> >( "{-1, 2i, 2}" )),
                           std::vector<short>({-1, 0, 1, 2}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<short> >( "{-1r2, 2i, 2r2}" )),
                           std::vector<short>({-1, -1, 0, 1, 2, 2}) );

  // Extract vector of unsigned short
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned short> >( "{0, 10, 100}" )),
                           std::vector<unsigned short>({0, 10, 100}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned short> >( "{0, 3i, 100}" )),
                           std::vector<unsigned short>({0, 25, 50, 75, 100}) );

  // Extract vector of int
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<int> >( "{-11111, 0, 11111, 22222}" )),
                           std::vector<int>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<int> >( "{-11111, 2i, 22222}" )),
                           std::vector<int>({-11111, 0, 11111, 22222}) );

  // Extract vector of unsigned int
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned int> >( "{0, 10, 100, 1000, 10000}" )),
                           std::vector<unsigned int>({0, 10, 100, 1000, 10000}) );
  
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned int> >( "{0, 3i, 10000}" )),
                           std::vector<unsigned int>({0, 2500, 5000, 7500, 10000}) );

  // Extract vector of long
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<long> >( "{-11111, 0, 11111, 22222}" )),
                           std::vector<long>({-11111, 0, 11111, 22222}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<long> >( "{-11111, 2i, 22222}" )),
                           std::vector<long>({-11111, 0, 11111, 22222}) );

  // Extract vector of unsigned long
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned long> >( "{0, 10, 100, 1000, 10000}" )),
                           std::vector<unsigned long>({0, 10, 100, 1000, 10000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned long> >( "{0, 3i, 10000}" )),
                           std::vector<unsigned long>({0, 2500, 5000, 7500, 10000}) );

  // Extract vector of long long
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<long long> >( "{-1000000000, 0, 1000000000}" )),
                           std::vector<long long>({-1000000000, 0, 1000000000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<long long> >( "{-1000000000, 1i, 1000000000}" )),
                           std::vector<long long>({-1000000000, 0, 1000000000}) );

  // Extract vector of unsigned long long
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned long long> >( "{0, 1000000000, 10000000000}" )),
                           std::vector<unsigned long long>({0, 1000000000, 10000000000}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<unsigned long long> >( "{0, 1i, 10000000000}" )),
                           std::vector<unsigned long long>({0, 5000000000, 10000000000}) );

  // Extract vector of float
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{-1, 0.0, 1.000000000e+00}" )),
                           std::vector<float>({-1.0f, 0.0f, 1.0f}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{-1, 0.0r2, 1.0}" )),
                           std::vector<float>({-1.0f, 0.0f, 0.0f, 1.0f}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{-1, 3i, 1.000000000e+00}" )),
                           std::vector<float>({-1.0f, -0.5f, 0.0f, 0.5f, 1.0f}) );
  TEST_COMPARE_FLOATING_CONTAINERS( (Utility::fromString<std::vector<float> >( "{1e-3, 2l, 1.0}" )),
                                    std::vector<float>({1e-3f, 1e-2f, 1e-1f, 1.0f}),
                                    1e-7 );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{1.0, 1l, 100, 3i, 200}" )),
                           std::vector<float>({1.0f, 10.0f, 100.0f, 125.0f, 150.0f, 175.0f, 200.0f}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{1.0r2, 1l, 100r2, 3i, 200r2}" )),
                           std::vector<float>({1.0f, 1.0f, 10.0f, 100.0f, 100.0f, 125.0f, 150.0f, 175.0f, 200.0f, 200.0f}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" )),
                           std::vector<float>({0.0f, (float)Utility::PhysicalConstants::pi/2, 3*(float)Utility::PhysicalConstants::pi/4, (float)Utility::PhysicalConstants::pi, 2*(float)Utility::PhysicalConstants::pi}) );
  TEST_COMPARE_FLOATING_CONTAINERS( (Utility::fromString<std::vector<float> >( "{-pi, 3i, 0}" )),
                                    std::vector<float>({-(float)Utility::PhysicalConstants::pi, -3*(float)Utility::PhysicalConstants::pi/4, -(float)Utility::PhysicalConstants::pi/2, -(float)Utility::PhysicalConstants::pi/4, 0.0}),
                                    1e-7 );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{pi r3}" )),
                                    std::vector<float>({(float)Utility::PhysicalConstants::pi, (float)Utility::PhysicalConstants::pi, (float)Utility::PhysicalConstants::pi}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{-3*pi/4 r2}" )),
                           std::vector<float>({-3*(float)Utility::PhysicalConstants::pi/4, -3*(float)Utility::PhysicalConstants::pi/4}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{-inf, 0, Infinity}" )),
                           std::vector<float>({-std::numeric_limits<float>::infinity(), 0.0f, std::numeric_limits<float>::infinity()}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<float> >( "{-inf r2, 0r2, Infinity r 2}" )),
                           std::vector<float>({-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), 0.0f, 0.0f, std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()}) );
  
  
  // Extract vector of double
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<double> >( "{-1, 0.0, 1.000000000000000000e+00}" )),
                           std::vector<double>({-1.0, 0.0, 1.0}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<double> >( "{-1, 3i, 1.000000000e+00}" )),
                           std::vector<double>({-1.0, -0.5, 0.0, 0.5, 1.0}) );
  TEST_COMPARE_FLOATING_CONTAINERS( (Utility::fromString<std::vector<double> >( "{1e-3, 2l, 1.0}" )),
                                    std::vector<double>({1e-3, 1e-2, 1e-1, 1.0}),
                                    1e-9 );
  TEST_COMPARE_FLOATING_CONTAINERS( (Utility::fromString<std::vector<double> >( "{1.0, 1l, 100, 3i, 200}" )),
                                    std::vector<double>({1.0, 10.0, 100.0, 125.0, 150.0, 175.0, 200.0}),
                                    1e-9 );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<double> >( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" )),
                           std::vector<double>({0.0, Utility::PhysicalConstants::pi/2, 3*Utility::PhysicalConstants::pi/4, Utility::PhysicalConstants::pi, 2*Utility::PhysicalConstants::pi}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<double> >( "{-pi, 3i, 0}" )),
                           std::vector<double>({-Utility::PhysicalConstants::pi, -3*Utility::PhysicalConstants::pi/4, -Utility::PhysicalConstants::pi/2, -Utility::PhysicalConstants::pi/4, 0.0}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<double> >( "{-Infinity, 0, inf}" )),
                           std::vector<double>({-std::numeric_limits<double>::infinity(), 0, std::numeric_limits<double>::infinity()}) );

  // Extract vector of char
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<char> >( "{}" )),
                           std::vector<char>() );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<char> >( "{ }" )),
                           std::vector<char>({' '}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<char> >( "{   }" )),
                           std::vector<char>({' '}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<char> >( "{T, e, s, t,  , s, t, r, i, n, g}" )),
                           std::vector<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );

  // Extract vector of string
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<std::string> >( "{}" )),
                           std::vector<std::string>() );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<std::string> >( "{ }" )),
                           std::vector<std::string>({" "}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<std::string> >( "{   }" )),
                           std::vector<std::string>({"   "}) );
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<std::string> >( "{Test, string}" )),
                           std::vector<std::string>({"Test","string"}) );

  // Extract vector of pair
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<std::pair<int, int> > >( "{{0, 1}, {-1, 2}}" )),
                           (std::vector<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );

  // Extract vector of tuple
  TEST_COMPARE_CONTAINERS( (Utility::fromString<std::vector<std::tuple<unsigned, double, long> > >( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" )),
                           (std::vector<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );

  // Extract vector of vectors
  std::vector<std::vector<double> > test_vector =
    Utility::fromString<std::vector<std::vector<double> > >( "{{-1, 3i, 1}, {1e-3, 2l, 1.0}, {-Inf, Inf}, {-pi/2, 1i, pi/2}}" );

  BOOST_CHECK_EQUAL( test_vector.size(), 4 );
  TEST_COMPARE_CONTAINERS( test_vector[0],
                           (std::vector<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );
  TEST_COMPARE_FLOATING_CONTAINERS( test_vector[1],
                                    (std::vector<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                    1e-9 );
  TEST_COMPARE_CONTAINERS( test_vector[2],
                           (std::vector<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );
  TEST_COMPARE_CONTAINERS( test_vector[3],
                           (std::vector<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );
}

//---------------------------------------------------------------------------//
// Check that a vector can be extracted from a stream
BOOST_AUTO_TEST_CASE( fromStream )
{
  // Extract vector of short
  std::istringstream iss( "{-1, 2}" );

  {
    std::vector<short> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<short>({-1, 2}) );

    iss.str( "{-1, 2i, 2}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<short>({-1, 0, 1, 2}) );
  }

  // Extract vector of unsigned short
  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::vector<unsigned short> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned short>({0, 10, 100}) );

    iss.str( "{0, 3i, 100}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned short>({0, 25, 50, 75, 100}) );
  }

  // Extract vector of int
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::vector<int> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<int>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<int>({-11111, 0, 11111, 22222}) );
  }

  // Extract vector of unsigned int
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::vector<unsigned> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract vector of long
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::vector<long> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<long>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<long>({-11111, 0, 11111, 22222}) );
  }

  // Extract vector of unsigned long
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::vector<unsigned long> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned long>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned long>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract vector of long long
  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::vector<long long> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<long long>({-1000000000, 0, 1000000000}) );

    iss.str( "{-1000000000, 1i, 1000000000}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<long long>({-1000000000, 0, 1000000000}) );
  }

  // Extract vector of unsigned long long
  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::vector<unsigned long long> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned long long>({0, 1000000000, 10000000000}) );

    iss.str( "{0, 1i, 10000000000}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned long long>({0, 5000000000, 10000000000}) );
  }

  // Extract vector of float
  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::vector<float> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<float>({-1.0f, 0.0f, 1.0f}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<float>({-1.0f, -0.5f, 0.0f, 0.5f, 1.0f}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_FLOATING_CONTAINERS( test_vector,
                                      std::vector<float>({1e-3f, 1e-2f, 1e-1f, 1.0f}),
                                      1e-7 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<float>({1.0f, 10.0f, 100.0f, 125.0f, 150.0f, 175.0f, 200.0f}) );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<float>({0.0f, (float)Utility::PhysicalConstants::pi/2, 3*(float)Utility::PhysicalConstants::pi/4, (float)Utility::PhysicalConstants::pi, 2*(float)Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_vector,
                                      std::vector<float>({-(float)Utility::PhysicalConstants::pi, -3*(float)Utility::PhysicalConstants::pi/4, -(float)Utility::PhysicalConstants::pi/2, -(float)Utility::PhysicalConstants::pi/4, 0.0}),
                                      1e-7 );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<float>({-std::numeric_limits<float>::infinity(), 0.0f, std::numeric_limits<float>::infinity()}) );
  }

  // Extract vector of double
  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::vector<double> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<double>({-1.0, 0.0, 1.0}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<double>({-1.0, -0.5, 0.0, 0.5, 1.0}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_FLOATING_CONTAINERS( test_vector,
                                      std::vector<double>({1e-3, 1e-2, 1e-1, 1.0}),
                                      1e-9 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_vector,
                                      std::vector<double>({1.0, 10.0, 100.0, 125.0, 150.0, 175.0, 200.0}),
                                      1e-15 );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<double>({0.0, Utility::PhysicalConstants::pi/2, 3*Utility::PhysicalConstants::pi/4, Utility::PhysicalConstants::pi, 2*Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<double>({-Utility::PhysicalConstants::pi, -3*Utility::PhysicalConstants::pi/4, -Utility::PhysicalConstants::pi/2, -Utility::PhysicalConstants::pi/4, 0.0}) );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    Utility::fromStream( iss, test_vector );
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<double>({-std::numeric_limits<float>::infinity(), 0.0, std::numeric_limits<float>::infinity()}) );
  }

  // Extract vector of char
  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::vector<char> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  // Extract vector of string
  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::vector<std::string> test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<std::string>({"Test","string"}) );
  }

  // Extract vector of pair
  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::vector<std::pair<int,int> > test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  // Extract vector of tuple
  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::vector<std::tuple<unsigned,double,long> > test_vector;

    Utility::fromStream( iss, test_vector );

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  // Extract multiple vectors of pairs
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

  // Extract vector of vectors
  iss.str( "{{-1, 3i, 1}, {1e-3, 2l, 1.0}, {-Inf, Inf}, {-pi/2, 1i, pi/2}}" );
  iss.clear();

  {
    std::vector<std::vector<double> > test_vector;
    
    Utility::fromStream( iss, test_vector );
    
    BOOST_CHECK_EQUAL( test_vector.size(), 4 );
    TEST_COMPARE_CONTAINERS( test_vector[0],
                             (std::vector<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );
    TEST_COMPARE_FLOATING_CONTAINERS( test_vector[1],
                                      (std::vector<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );
    TEST_COMPARE_CONTAINERS( test_vector[2],
                             (std::vector<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );
    TEST_COMPARE_CONTAINERS( test_vector[3],
                             (std::vector<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );
  }
}

//---------------------------------------------------------------------------//
// Check that a vector can be placed in a stream
BOOST_AUTO_TEST_CASE( ostream )
{
  std::ostringstream oss;

  oss << std::vector<short>( {-1, 2} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<unsigned short>( {0, 10, 100} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<int>( {-11111, 0, 11111, 22222} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<unsigned int>( {0, 10, 100, 1000, 10000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<long>( {-11111, 0, 11111, 22222} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<unsigned long>( {0, 10, 100, 1000, 10000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<long long>( {-10000000000, 0, 10000000000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<unsigned long long>( {0, 1000000000, 1000000000000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<float>( {-1.0f, 0.0f, 1.0f} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  oss << std::vector<double>( {-1.0, 0.0, 1.0} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } );
  
  BOOST_CHECK_EQUAL( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<std::string>( {"Test", "string"} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<std::pair<int, int>>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  oss << std::vector<std::tuple<unsigned, double, long>>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                       "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a vector can be extracted from a stream
BOOST_AUTO_TEST_CASE( istream )
{
  // Extract vector of short
  std::istringstream iss( "{-1, 2}" );

  {
    std::vector<short> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<short>({-1, 2}) );

    iss.str( "{-1, 2i, 2}" );
    iss.clear();

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<short>({-1, 0, 1, 2}) );
  }

  // Extract vector of unsigned short
  iss.str( "{0, 10, 100}" );
  iss.clear();

  {
    std::vector<unsigned short> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned short>({0, 10, 100}) );

    iss.str( "{0, 3i, 100}" );
    iss.clear();

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned short>({0, 25, 50, 75, 100}) );
  }

  // Extract vector of int
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::vector<int> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<int>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<int>({-11111, 0, 11111, 22222}) );
  }

  // Extract vector of unsigned int
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::vector<unsigned> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract vector of long
  iss.str( "{-11111, 0, 11111, 22222}" );
  iss.clear();

  {
    std::vector<long> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<long>({-11111, 0, 11111, 22222}) );

    iss.str( "{-11111, 2i, 22222}" );
    iss.clear();

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<long>({-11111, 0, 11111, 22222}) );
  }

  // Extract vector of unsigned long
  iss.str( "{0, 10, 100, 1000, 10000}" );
  iss.clear();

  {
    std::vector<unsigned long> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned long>({0, 10, 100, 1000, 10000}) );

    iss.str( "{0, 3i, 10000}" );
    iss.clear();

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned long>({0, 2500, 5000, 7500, 10000}) );
  }

  // Extract vector of long long
  iss.str( "{-1000000000, 0, 1000000000}" );
  iss.clear();

  {
    std::vector<long long> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<long long>({-1000000000, 0, 1000000000}) );

    iss.str( "{-1000000000, 1i, 1000000000}" );
    iss.clear();

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<long long>({-1000000000, 0, 1000000000}) );
  }

  // Extract vector of unsigned long long
  iss.str( "{0, 1000000000, 10000000000}" );
  iss.clear();

  {
    std::vector<unsigned long long> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned long long>({0, 1000000000, 10000000000}) );

    iss.str( "{0, 1i, 10000000000}" );
    iss.clear();

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<unsigned long long>({0, 5000000000, 10000000000}) );
  }

  // Extract vector of float
  iss.str( "{-1, 0.0, 1.000000000e+00}" );
  iss.clear();

  {
    std::vector<float> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<float>({-1.0f, 0.0f, 1.0f}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<float>({-1.0f, -0.5f, 0.0f, 0.5f, 1.0f}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    iss >> test_vector;

    TEST_COMPARE_FLOATING_CONTAINERS( test_vector,
                                      std::vector<float>({1e-3f, 1e-2f, 1e-1f, 1.0f}),
                                      1e-7 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    iss >> test_vector;
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<float>({1.0f, 10.0f, 100.0f, 125.0f, 150.0f, 175.0f, 200.0f}) );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    iss >> test_vector;
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<float>({0.0f, (float)Utility::PhysicalConstants::pi/2, 3*(float)Utility::PhysicalConstants::pi/4, (float)Utility::PhysicalConstants::pi, 2*(float)Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    iss >> test_vector;
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_vector,
                                      std::vector<float>({-(float)Utility::PhysicalConstants::pi, -3*(float)Utility::PhysicalConstants::pi/4, -(float)Utility::PhysicalConstants::pi/2, -(float)Utility::PhysicalConstants::pi/4, 0.0}),
                                      1e-7 );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    iss >> test_vector;
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<float>({-std::numeric_limits<float>::infinity(), 0.0f, std::numeric_limits<float>::infinity()}) );
  }

  // Extract vector of double
  iss.str( "{-1, 0.0, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::vector<double> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<double>({-1.0, 0.0, 1.0}) );

    iss.str( "{-1, 3i, 1.000000000e+00}" );
    iss.clear();

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<double>({-1.0, -0.5, 0.0, 0.5, 1.0}) );

    iss.str( "{1e-3, 2l, 1.0}" );
    iss.clear();

    iss >> test_vector;

    TEST_COMPARE_FLOATING_CONTAINERS( test_vector,
                                      std::vector<double>({1e-3, 1e-2, 1e-1, 1.0}),
                                      1e-9 );

    iss.str( "{1.0, 1l, 100, 3i, 200}" );
    iss.clear();

    iss >> test_vector;
    
    TEST_COMPARE_FLOATING_CONTAINERS( test_vector,
                                      std::vector<double>({1.0, 10.0, 100.0, 125.0, 150.0, 175.0, 200.0}),
                                      1e-15 );

    iss.str( "{0.0, pi/2, 3Pi / 4, PI, 2*pi}" );
    iss.clear();

    iss >> test_vector;
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<double>({0.0, Utility::PhysicalConstants::pi/2, 3*Utility::PhysicalConstants::pi/4, Utility::PhysicalConstants::pi, 2*Utility::PhysicalConstants::pi}) );

    iss.str( "{-pi, 3i, 0}" );
    iss.clear();

    iss >> test_vector;
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<double>({-Utility::PhysicalConstants::pi, -3*Utility::PhysicalConstants::pi/4, -Utility::PhysicalConstants::pi/2, -Utility::PhysicalConstants::pi/4, 0.0}) );

    iss.str( "{-inf, 0, Infinity}" );
    iss.clear();

    iss >> test_vector;
    
    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<double>({-std::numeric_limits<float>::infinity(), 0.0, std::numeric_limits<float>::infinity()}) );
  }

  // Extract vector of char
  iss.str( "{T, e, s, t,  , s, t, r, i, n, g}" );
  iss.clear();

  {
    std::vector<char> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<char>({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'}) );
  }

  // Extract vector of string
  iss.str( "{Test, string}" );
  iss.clear();

  {
    std::vector<std::string> test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, std::vector<std::string>({"Test","string"}) );
  }

  // Extract vector of pair
  iss.str( "{{0, 1}, {-1, 2}}" );
  iss.clear();

  {
    std::vector<std::pair<int,int> > test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::pair<int,int> >({std::make_pair(0, 1), std::make_pair(-1, 2)})) );
  }

  // Extract vector of tuple
  iss.str( "{{0, 1.0, -100000}, {1, -1.00, 100001}}" );
  iss.clear();

  {
    std::vector<std::tuple<unsigned,double,long> > test_vector;

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::tuple<unsigned,double,long> >({std::make_tuple(0u, 1.0, -100000l), std::make_tuple(1u, -1.0, 100001l)})) );
  }

  // Extract multiple vectors of pairs
  iss.str( "{{0, 1}, {-1, 2}}, {{1, 0}, {2, -1}}" );
  iss.clear();

  {
    std::vector<std::pair<long,long> > test_vector;

    Utility::fromStream( iss, test_vector, "," );

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::pair<long,long> >({std::make_pair(0l, 1l), std::make_pair(-1l, 2l)})) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    iss >> test_vector;

    TEST_COMPARE_CONTAINERS( test_vector, (std::vector<std::pair<long,long> >({std::make_pair(1l, 0l), std::make_pair(2l, -1l)})) );
  }

  // Extract vector of vectors
  iss.str( "{{-1, 3i, 1}, {1e-3, 2l, 1.0}, {-Inf, Inf}, {-pi/2, 1i, pi/2}}" );
  iss.clear();

  {
    std::vector<std::vector<double> > test_vector;
    
    iss >> test_vector;
    
    BOOST_CHECK_EQUAL( test_vector.size(), 4 );
    TEST_COMPARE_CONTAINERS( test_vector[0],
                             (std::vector<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );
    TEST_COMPARE_FLOATING_CONTAINERS( test_vector[1],
                                      (std::vector<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );
    TEST_COMPARE_CONTAINERS( test_vector[2],
                             (std::vector<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );
    TEST_COMPARE_CONTAINERS( test_vector[3],
                             (std::vector<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );
  }
}

//---------------------------------------------------------------------------//
// Check that a vector can mimic stream behavior
BOOST_AUTO_TEST_CASE( stream_mimic )
{
  {
    std::vector<short> test_vector;

    test_vector << -1 << 0 << 1;

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<short>( {-1, 0, 1} ) );

    short element0, element1, element2;

    test_vector >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -1 );
    BOOST_CHECK_EQUAL( element1, 0 );
    BOOST_CHECK_EQUAL( element2, 1 );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );

    test_vector << "-1" << 0 << "1";

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<short>( {-1, 0, 1} ) );

    std::string element0_str, element1_str, element2_str;

    test_vector >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-1" );
    BOOST_CHECK_EQUAL( element1_str, "0" );
    BOOST_CHECK_EQUAL( element2_str, "1" );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );
  }

  {
    std::vector<unsigned short> test_vector;

    test_vector << 0 << 10 << 100;

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<unsigned short>( {0, 10, 100} ) );

    unsigned short element0, element1, element2;

    test_vector >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, 0 );
    BOOST_CHECK_EQUAL( element1, 10 );
    BOOST_CHECK_EQUAL( element2, 100 );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );

    test_vector << "0" << 10 << "100";

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<unsigned short>( {0, 10, 100} ) );

    std::string element0_str, element1_str, element2_str;

    test_vector >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "0" );
    BOOST_CHECK_EQUAL( element1_str, "10" );
    BOOST_CHECK_EQUAL( element2_str, "100" );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );
  }

  {
    std::vector<int> test_vector;

    test_vector << -11111 << 0 << 11111;

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<int>( {-11111, 0, 11111} ) );

    int element0, element1, element2;

    test_vector >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -11111 );
    BOOST_CHECK_EQUAL( element1, 0 );
    BOOST_CHECK_EQUAL( element2, 11111 );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );

    test_vector << "-11111" << 0 << "11111";

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<int>( {-11111, 0, 11111} ) );

    std::string element0_str, element1_str, element2_str;

    test_vector >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-11111" );
    BOOST_CHECK_EQUAL( element1_str, "0" );
    BOOST_CHECK_EQUAL( element2_str, "11111" );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );
  }

  {
    std::vector<unsigned int> test_vector;

    test_vector << 0 << 1000 << 1000000;

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<unsigned int>( {0, 1000, 1000000} ) );

    unsigned int element0, element1, element2;

    test_vector >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, 0 );
    BOOST_CHECK_EQUAL( element1, 1000 );
    BOOST_CHECK_EQUAL( element2, 1000000 );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );

    test_vector << "0" << 1000 << "1000000";

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<unsigned int>( {0, 1000, 1000000} ) );

    std::string element0_str, element1_str, element2_str;

    test_vector >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "0" );
    BOOST_CHECK_EQUAL( element1_str, "1000" );
    BOOST_CHECK_EQUAL( element2_str, "1000000" );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );
  }

  {
    std::vector<long> test_vector;

    test_vector << -11111l << 0l << 11111l;

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<long>( {-11111l, 0l, 11111l} ) );

    long element0, element1, element2;

    test_vector >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -11111l );
    BOOST_CHECK_EQUAL( element1, 0l );
    BOOST_CHECK_EQUAL( element2, 11111l );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );

    test_vector << "-11111" << 0 << "11111";

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<long>( {-11111l, 0l, 11111l} ) );

    std::string element0_str, element1_str, element2_str;

    test_vector >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-11111" );
    BOOST_CHECK_EQUAL( element1_str, "0" );
    BOOST_CHECK_EQUAL( element2_str, "11111" );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );
  }

  {
    std::vector<unsigned long> test_vector;

    test_vector << 0ul << 1000ul << 1000000ul;

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<unsigned long>( {0ul, 1000ul, 1000000ul} ) );

    unsigned long element0, element1, element2;

    test_vector >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, 0ul );
    BOOST_CHECK_EQUAL( element1, 1000ul );
    BOOST_CHECK_EQUAL( element2, 1000000ul );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );

    test_vector << "0" << 1000 << "1000000";

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<unsigned long>( {0ul, 1000ul, 1000000ul} ) );

    std::string element0_str, element1_str, element2_str;

    test_vector >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "0" );
    BOOST_CHECK_EQUAL( element1_str, "1000" );
    BOOST_CHECK_EQUAL( element2_str, "1000000" );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );
  }
  
  {
    std::vector<long long> test_vector;

    test_vector << -10000000000ll << 0ll << 10000000000ll;

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<long long>( {-10000000000ll, 0ll, 10000000000ll} ) );

    long long element0, element1, element2;

    test_vector >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -10000000000ll );
    BOOST_CHECK_EQUAL( element1, 0ll );
    BOOST_CHECK_EQUAL( element2, 10000000000ll );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );

    test_vector << "-10000000000" << 0 << "10000000000";

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<long long>( {-10000000000ll, 0ll, 10000000000ll} ) );

    std::string element0_str, element1_str, element2_str;

    test_vector >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-10000000000" );
    BOOST_CHECK_EQUAL( element1_str, "0" );
    BOOST_CHECK_EQUAL( element2_str, "10000000000" );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );
  }

  {
    std::vector<unsigned long long> test_vector;

    test_vector << 0ull << 10000000000ull << 100000000000ull;

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<unsigned long long>( {0ull, 10000000000ull, 100000000000ull} ) );

    unsigned long long element0, element1, element2;

    test_vector >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, 0ull );
    BOOST_CHECK_EQUAL( element1, 10000000000ull );
    BOOST_CHECK_EQUAL( element2, 100000000000ull );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );

    test_vector << "0" << 10000000000ull << "100000000000";

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<unsigned long long>( {0ull, 10000000000ull, 100000000000ull} ) );

    std::string element0_str, element1_str, element2_str;

    test_vector >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "0" );
    BOOST_CHECK_EQUAL( element1_str, "10000000000" );
    BOOST_CHECK_EQUAL( element2_str, "100000000000" );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );
  }

  {
    std::vector<float> test_vector;

    test_vector << -1.0f << 0.0f << 1.0f;

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<float>( {-1.0f, 0.0f, 1.0f} ) );

    float element0, element1, element2;

    test_vector >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -1.0f );
    BOOST_CHECK_EQUAL( element1, 0.0f );
    BOOST_CHECK_EQUAL( element2, 1.0f );

    test_vector << "-2pi/3" << "0" << "Inf";

    test_vector >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -2*(float)Utility::PhysicalConstants::pi/3 );
    BOOST_CHECK_EQUAL( element1, 0.0f );
    BOOST_CHECK_EQUAL( element2, std::numeric_limits<float>::infinity() );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );

    test_vector << -1.0f << 0.0f << 1.0f;

    std::string element0_str, element1_str, element2_str;

    test_vector >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-1.000000000e+00" );
    BOOST_CHECK_EQUAL( element1_str, "0.000000000e+00" );
    BOOST_CHECK_EQUAL( element2_str, "1.000000000e+00" );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );
  }

  {
    std::vector<double> test_vector;

    test_vector << -1.0 << 0.0 << 1.0;

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<double>( {-1.0, 0.0, 1.0} ) );

    double element0, element1, element2;

    test_vector >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -1.0 );
    BOOST_CHECK_EQUAL( element1, 0.0 );
    BOOST_CHECK_EQUAL( element2, 1.0 );

    test_vector << "-infty" << "0" << "pi/3";

    test_vector >> element2 >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, -std::numeric_limits<double>::infinity() );
    BOOST_CHECK_EQUAL( element1, 0.0 );
    BOOST_CHECK_EQUAL( element2, Utility::PhysicalConstants::pi/3 );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );

    test_vector << -1.0 << 0.0 << 1.0;

    std::string element0_str, element1_str, element2_str;

    test_vector >> element2_str >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "-1.000000000000000000e+00" );
    BOOST_CHECK_EQUAL( element1_str, "0.000000000000000000e+00" );
    BOOST_CHECK_EQUAL( element2_str, "1.000000000000000000e+00" );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );
  }

  {
    std::vector<char> test_vector;

    test_vector << 'T' << 'e' << 's' << 't' << ' '
                << 's' << 't' << 'r' << 'i' << 'n' << 'g';

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<char>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'} ) );

    std::string elements( "           " );

    test_vector >> elements[10] >> elements[9] >> elements[8] >> elements[7]
                >> elements[6] >> elements[5] >> elements[4] >> elements[3]
                >> elements[2] >> elements[1] >> elements[0];

    BOOST_CHECK_EQUAL( elements, "Test string" );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );
  }
  
  {
    std::vector<std::string> test_vector;

    test_vector << "Test" << "string";

    TEST_COMPARE_CONTAINERS( test_vector,
                             std::vector<std::string>( {"Test", "string"} ) );

    std::string element0, element1;

    test_vector >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, "Test" );
    BOOST_CHECK_EQUAL( element1, "string" );
  }

  {
    std::vector<std::pair<int, int> > test_vector;

    test_vector << std::make_pair( 0, 1 ) << std::make_pair( -1, 2 );

    TEST_COMPARE_CONTAINERS( test_vector,
                             (std::vector<std::pair<int, int> >( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} )) );

    std::pair<int,int> element0, element1;

    test_vector >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, std::make_pair( 0, 1 ) );
    BOOST_CHECK_EQUAL( element1, std::make_pair( -1, 2 ) );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );

    test_vector << "{0, 1}" << "{-1, 2}";

    test_vector >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, std::make_pair( 0, 1 ) );
    BOOST_CHECK_EQUAL( element1, std::make_pair( -1, 2 ) );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );

    test_vector << "{0, 1}" << std::make_pair( -1, 2 );

    std::string element0_str, element1_str;

    test_vector >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "{0, 1}" );
    BOOST_CHECK_EQUAL( element1_str, "{-1, 2}" );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );
  }

  {
    std::vector<std::tuple<unsigned, double, long> > test_vector;

    test_vector << std::make_tuple( 0u, 1.0, -100000l )
                << std::make_tuple( 1u, -1.0, 100001l );

    TEST_COMPARE_CONTAINERS( test_vector,
                             (std::vector<std::tuple<unsigned, double, long> >( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} )) );

    std::tuple<unsigned, double, long> element0, element1;

    test_vector >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, std::make_tuple( 0u, 1.0, -100000l ) );
    BOOST_CHECK_EQUAL( element1, std::make_tuple( 1u, -1.0, 100001l ) );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );

    test_vector << "{0, 1, -100000}" << "{1, -1, 100001}";

    test_vector >> element1 >> element0;

    BOOST_CHECK_EQUAL( element0, std::make_tuple( 0u, 1.0, -100000l ) );
    BOOST_CHECK_EQUAL( element1, std::make_tuple( 1u, -1.0, 100001l ) );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );

    test_vector << "{0, 1, -100000}" << std::make_tuple( 1u, -1.0, 100001l );

    std::string element0_str, element1_str;

    test_vector >> element1_str >> element0_str;

    BOOST_CHECK_EQUAL( element0_str, "{0, 1.000000000000000000e+00, -100000}" );
    BOOST_CHECK_EQUAL( element1_str, "{1, -1.000000000000000000e+00, 100001}" );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );
  }

  {
    std::vector<std::vector<double> > test_vector;

    test_vector << std::vector<double>( {-1, -0.5, 0.0, 0.5, 1.0} )
                << std::vector<double>( {1e-3, 1e-2, 1e-1, 1.0} )
                << std::vector<double>( {-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()} )
                << std::vector<double>( {-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2} );

    BOOST_CHECK_EQUAL( test_vector.size(), 4 );
    TEST_COMPARE_CONTAINERS( test_vector[0],
                             (std::vector<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );
    TEST_COMPARE_FLOATING_CONTAINERS( test_vector[1],
                                      (std::vector<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );
    TEST_COMPARE_CONTAINERS( test_vector[2],
                             (std::vector<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );
    TEST_COMPARE_CONTAINERS( test_vector[3],
                             (std::vector<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );

    std::vector<double> element0, element1, element2, element3;
    
    test_vector >> element3 >> element2 >> element1 >> element0;
    
    TEST_COMPARE_CONTAINERS( element0,
                             (std::vector<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );
    TEST_COMPARE_FLOATING_CONTAINERS( element1,
                                      (std::vector<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );
    TEST_COMPARE_CONTAINERS( element2,
                             (std::vector<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );
    TEST_COMPARE_CONTAINERS( element3,
                             (std::vector<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );

    test_vector << "{-1, 3i, 1}" << "{1e-3, 2l, 1.0}"
                << "{-Inf, Inf}" << "{-pi/2, 1i, pi/2}";

    BOOST_CHECK_EQUAL( test_vector.size(), 4 );
    TEST_COMPARE_CONTAINERS( test_vector[0],
                             (std::vector<double>({-1.0, -0.5, 0.0, 0.5, 1.0})) );
    TEST_COMPARE_FLOATING_CONTAINERS( test_vector[1],
                                      (std::vector<double>({1e-3, 1e-2, 1e-1, 1.0})),
                                      1e-9 );
    TEST_COMPARE_CONTAINERS( test_vector[2],
                             (std::vector<double>({-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()})) );
    TEST_COMPARE_CONTAINERS( test_vector[3],
                             (std::vector<double>({-Utility::PhysicalConstants::pi/2, 0.0, Utility::PhysicalConstants::pi/2})) );

    std::string element0_str, element1_str, element2_str, element3_str;

    test_vector >> element3_str >> element2_str
                >> element1_str >> element0_str;

    BOOST_CHECK( element0_str.size() > 0 );
    BOOST_CHECK( element1_str.size() > 0 );
    BOOST_CHECK( element2_str.size() > 0 );
    BOOST_CHECK( element3_str.size() > 0 );
    BOOST_CHECK_EQUAL( test_vector.size(), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that a view of a vector can be created
BOOST_AUTO_TEST_CASE_TEMPLATE( slice_operator, T, TestTypes )
{
  std::vector<T> vector({0, 1, 2, 3, 4});

  Utility::ArrayView<T> view = vector | Utility::Slice( 0, 1 );

  BOOST_CHECK_EQUAL( view.size(), 1 );
  BOOST_CHECK_EQUAL( view[0], vector[0] );

  view = vector | Utility::slice( 1, 2 );

  BOOST_CHECK_EQUAL( view.size(), 2 );
  BOOST_CHECK_EQUAL( view[0], vector[1] );
  BOOST_CHECK_EQUAL( view[1], vector[2] );

  view = vector | std::make_pair( 1, 3 );

  BOOST_CHECK_EQUAL( view.size(), 3 );
  BOOST_CHECK_EQUAL( view[0], vector[1] );
  BOOST_CHECK_EQUAL( view[1], vector[2] );
  BOOST_CHECK_EQUAL( view[2], vector[3] );

  view = vector | std::make_pair( 2, 3 );

  BOOST_CHECK_EQUAL( view.size(), 3 );
  BOOST_CHECK_EQUAL( view[0], vector[2] );
  BOOST_CHECK_EQUAL( view[1], vector[3] );
  BOOST_CHECK_EQUAL( view[2], vector[4] );

  Utility::ArrayView<const T> const_view =
    const_cast<const std::vector<T>&>( vector ) | Utility::slice( 1, 4 );

  BOOST_CHECK_EQUAL( const_view.size(), 4 );
  BOOST_CHECK_EQUAL( const_view[0], vector[1] );
  BOOST_CHECK_EQUAL( const_view[1], vector[2] );
  BOOST_CHECK_EQUAL( const_view[2], vector[3] );
  BOOST_CHECK_EQUAL( const_view[3], vector[4] );
}

//---------------------------------------------------------------------------//
// Check that the correct comparison policies are allowed for vectors
BOOST_AUTO_TEST_CASE_TEMPLATE( IsComparisonAllowed, T, TestTypes )
{
  typedef std::vector<T> Vector;

  BOOST_CHECK( Utility::ComparisonTraits<Vector>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<Vector>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Vector>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Vector>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Vector>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Vector>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<Vector>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<Vector>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<const Vector>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const Vector>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Vector>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Vector>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Vector>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Vector>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const Vector>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const Vector>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );
}

//---------------------------------------------------------------------------//
// Check that vectors can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, PolicyTypePair, TestPolicyTypes )
{
  typedef typename Utility::TupleElement<0,PolicyTypePair>::type Policy;
  typedef typename Utility::TupleElement<1,PolicyTypePair>::type T;

  std::vector<T> left_vector({T(0), T(1), T(2)});
  std::vector<T> right_vector({T(0), T(1), T(2)});

  std::ostringstream oss;

  // No details logging
  bool compare_result = Utility::compare<Policy,0>( left_vector, "lhs",
                                                    right_vector, "rhs",
                                                    oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( !compare_result );
  else
    BOOST_CHECK( compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_vector, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_vector, "lhs",
                                               {}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {T(1),T(1),T(1)}, "lhs",
                                               right_vector, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_vector, "lhs",
                                               {T(1),T(1),T(1)}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  // Details logging
  T tol( 1e-6 );

  compare_result = Utility::compare<Policy,0>( left_vector, "lhs",
                                               right_vector, "rhs",
                                               oss, tol, true );

  std::string expected_details =
    Utility::createComparisonHeader<Policy,0>( left_vector, "lhs",
                                               right_vector, "rhs",
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
                                              left_vector.size(), "lhs", true,
                                              right_vector.size(), "rhs", true,
                                              ".size()", local_oss, true );
    for( size_t i = 0; i < left_vector.size(); ++i )
    {
      Utility::ComparisonTraits<T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                left_vector[i], "lhs", true,
                right_vector[i], "rhs", true,
                std::string("[") + Utility::toString(i) + "]", local_oss, true,
                tol );
    }

    expected_details += "passed\n";
    expected_details += local_oss.str();

    BOOST_CHECK( compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( {T(1), T(1), T(1)}, "lhs",
                                               right_vector, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {T(1), T(1), T(1)}, "lhs",
                                               right_vector, "rhs",
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
                                              right_vector.size(), "rhs", true,
                                              ".size()", local_oss, true );
    for( size_t i = 0; i < right_vector.size(); ++i )
    {
      Utility::ComparisonTraits<T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                T(1), "lhs", false,
                right_vector[i], "rhs", true,
                std::string("[") + Utility::toString(i) + "]", local_oss, true,
                tol );
    }

    expected_details += "failed!\n";
    expected_details += local_oss.str();

    BOOST_CHECK( !compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_vector, "lhs",
                                               {T(1), T(1), T(1)}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_vector, "lhs",
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
                                               left_vector.size(), "lhs", true,
                                               3, "rhs", false,
                                               ".size()", local_oss, true );

    for( size_t i = 0; i < left_vector.size(); ++i )
    {
      Utility::ComparisonTraits<T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                left_vector[i], "lhs", true,
                T(1), "rhs", false,
                std::string("[") + Utility::toString(i) + "]", local_oss, true,
                tol );
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
// end tstVector.cpp
//---------------------------------------------------------------------------//
