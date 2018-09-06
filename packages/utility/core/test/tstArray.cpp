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

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/insert_range.hpp>

// FRENSIE Includes
#include "Utility_Array.hpp"
#include "Utility_Tuple.hpp"

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
// Check that an array can be converted to a string
BOOST_AUTO_TEST_CASE( array_toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( std::array<short,2>( {-1, 2} ) ),
                     "{-1, 2}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::array<unsigned short,3>( {0, 10, 100} ) ),
                     "{0, 10, 100}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::array<int,4>( {-11111, 0, 11111, 22222} ) ),
                     "{-11111, 0, 11111, 22222}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::array<unsigned int, 5>( {0, 10, 100, 1000, 10000} ) ),
                     "{0, 10, 100, 1000, 10000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::array<long,4>( {-11111, 0, 11111, 22222} ) ),
                     "{-11111, 0, 11111, 22222}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::array<unsigned long, 5>( {0, 10, 100, 1000, 10000} ) ),
                     "{0, 10, 100, 1000, 10000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::array<long long, 3>( {-10000000000, 0, 10000000000} ) ),
                     "{-10000000000, 0, 10000000000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::array<unsigned long long, 3>( {0, 1000000000, 1000000000000} ) ),
                     "{0, 1000000000, 1000000000000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::array<float, 3>( {-1.0f, 0.0f, 1.0f} ) ),
                     "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::array<double, 3>( {-1.0, 0.0, 1.0} ) ),
                     "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::array<char,11>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) ),
                     "{T, e, s, t,  , s, t, r, i, n, g}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::array<std::string, 2>( {"Test", "string"} ) ),
                     "{Test, string}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::array<std::pair<int, int>, 2>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) ),
                     "{{0, 1}, {-1, 2}}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::array<std::tuple<unsigned, double, long>, 2>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) ),
                     "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that an array can be placed in a stream
BOOST_AUTO_TEST_CASE( array_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::array<short,2>( {-1, 2} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<unsigned short,3>( {0, 10, 100} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<int,4>( {-11111, 0, 11111, 22222} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<unsigned int, 5>( {0, 10, 100, 1000, 10000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<long,4>( {-11111, 0, 11111, 22222} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<unsigned long, 5>( {0, 10, 100, 1000, 10000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<long long, 3>( {-10000000000, 0, 10000000000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<unsigned long long, 3>( {0, 1000000000, 1000000000000} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<float, 3>( {-1.0f, 0.0f, 1.0f} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<double, 3>( {-1.0, 0.0, 1.0} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<char,11>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<std::string, 2>( {"Test", "string"} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<std::pair<int, int>, 2>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::array<std::tuple<unsigned, double, long>, 2>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} ) );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that an array can be placed in a stream
BOOST_AUTO_TEST_CASE( array_ostream )
{
  std::ostringstream oss;

  oss << std::array<short,2>( {-1, 2} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-1, 2}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<unsigned short,3>( {0, 10, 100} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<int,4>( {-11111, 0, 11111, 22222} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<unsigned int, 5>( {0, 10, 100, 1000, 10000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<long,4>( {-11111, 0, 11111, 22222} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-11111, 0, 11111, 22222}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<unsigned long, 5>( {0, 10, 100, 1000, 10000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 10, 100, 1000, 10000}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<long long, 3>( {-10000000000, 0, 10000000000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-10000000000, 0, 10000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<unsigned long long, 3>( {0, 1000000000, 1000000000000} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0, 1000000000, 1000000000000}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<float, 3>( {-1.0f, 0.0f, 1.0f} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     "{-1.000000000e+00, 0.000000000e+00, 1.000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  oss << std::array<double, 3>( {-1.0, 0.0, 1.0} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     "{-1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<char,11>( {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' } );
  
  BOOST_CHECK_EQUAL( oss.str(), "{T, e, s, t,  , s, t, r, i, n, g}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<std::string, 2>( {"Test", "string"} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{Test, string}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<std::pair<int, int>, 2>( {std::pair<int, int>({0, 1}), std::pair<int,int>({-1, 2})} );
  
  BOOST_CHECK_EQUAL( oss.str(), "{{0, 1}, {-1, 2}}" );

  oss.str( "" );
  oss.clear();

  oss << std::array<std::tuple<unsigned, double, long>, 2>( {std::make_tuple( 0u, 1.0, -100000 ), std::make_tuple( 1u, -1.0, 100001 )} );
  
  BOOST_CHECK_EQUAL( oss.str(),
                     "{{0, 1.000000000000000000e+00, -100000}, {1, -1.000000000000000000e+00, 100001}}" );
}

//---------------------------------------------------------------------------//
// Check that a view of a array can be created
BOOST_AUTO_TEST_CASE_TEMPLATE( slice_operator, T, TestTypes )
{
  std::array<T,5> array({T(0), T(1), T(2), T(3), T(4)});

  Utility::ArrayView<T> view = array | Utility::Slice( 0, 1 );

  BOOST_CHECK_EQUAL( view.size(), 1 );
  BOOST_CHECK_EQUAL( view[0], array[0] );

  view = array | Utility::slice( 1, 2 );

  BOOST_CHECK_EQUAL( view.size(), 2 );
  BOOST_CHECK_EQUAL( view[0], array[1] );
  BOOST_CHECK_EQUAL( view[1], array[2] );

  view = array | std::make_pair( 1, 3 );

  BOOST_CHECK_EQUAL( view.size(), 3 );
  BOOST_CHECK_EQUAL( view[0], array[1] );
  BOOST_CHECK_EQUAL( view[1], array[2] );
  BOOST_CHECK_EQUAL( view[2], array[3] );

  view = array | std::make_pair( 2, 3 );

  BOOST_CHECK_EQUAL( view.size(), 3 );
  BOOST_CHECK_EQUAL( view[0], array[2] );
  BOOST_CHECK_EQUAL( view[1], array[3] );
  BOOST_CHECK_EQUAL( view[2], array[4] );

  Utility::ArrayView<const T> const_view =
    const_cast<const std::array<T,5>&>( array ) | Utility::slice( 1, 4 );

  BOOST_CHECK_EQUAL( const_view.size(), 4 );
  BOOST_CHECK_EQUAL( const_view[0], array[1] );
  BOOST_CHECK_EQUAL( const_view[1], array[2] );
  BOOST_CHECK_EQUAL( const_view[2], array[3] );
  BOOST_CHECK_EQUAL( const_view[3], array[4] );
}

//---------------------------------------------------------------------------//
// Check that the correct comparison policies are allowed for arrays
BOOST_AUTO_TEST_CASE_TEMPLATE( IsComparisonAllowed, T, TestTypes )
{
  typedef std::array<T,1> Array1;
  typedef std::array<T,2> Array2;

  BOOST_CHECK( Utility::ComparisonTraits<Array1>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<Array1>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Array1>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Array1>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Array1>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Array1>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<Array1>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<Array1>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<const Array1>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const Array1>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Array1>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Array1>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Array1>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Array1>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const Array1>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const Array1>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<Array2>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<Array2>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Array2>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Array2>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Array2>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<Array2>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<Array2>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<Array2>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );

  BOOST_CHECK( Utility::ComparisonTraits<const Array2>::template IsComparisonAllowed<Utility::EqualityComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const Array2>::template IsComparisonAllowed<Utility::InequalityComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Array2>::template IsComparisonAllowed<Utility::GreaterThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Array2>::template IsComparisonAllowed<Utility::GreaterThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Array2>::template IsComparisonAllowed<Utility::LessThanComparisonPolicy>::value );
  BOOST_CHECK( !Utility::ComparisonTraits<const Array2>::template IsComparisonAllowed<Utility::LessThanOrEqualToComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const Array2>::template IsComparisonAllowed<Utility::CloseComparisonPolicy>::value );
  BOOST_CHECK( Utility::ComparisonTraits<const Array2>::template IsComparisonAllowed<Utility::RelativeErrorComparisonPolicy>::value );
}

//---------------------------------------------------------------------------//
// Check that arrays can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, PolicyTypePair, TestPolicyTypes )
{
  typedef typename Utility::TupleElement<0,PolicyTypePair>::type Policy;
  typedef typename Utility::TupleElement<1,PolicyTypePair>::type T;

  std::array<T,3> left_array({T(0), T(1), T(2)});
  std::array<T,3> right_array({T(0), T(1), T(2)});

  std::ostringstream oss;

  // No details logging
  bool compare_result = Utility::compare<Policy,0>( left_array, "lhs",
                                                    right_array, "rhs",
                                                    oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( !compare_result );
  else
    BOOST_CHECK( compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {}, "lhs",
                                               right_array, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_array, "lhs",
                                               {}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( {T(1),T(1),T(1)}, "lhs",
                                               right_array, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_array, "lhs",
                                               {T(1),T(1),T(1)}, "rhs",
                                               oss );

  if( std::is_same<Policy,Utility::InequalityComparisonPolicy>::value )
    BOOST_CHECK( compare_result );
  else
    BOOST_CHECK( !compare_result );

  BOOST_CHECK_EQUAL( oss.str(), "" );

  // Details logging
  T tol( 1e-6 );

  compare_result = Utility::compare<Policy,0>( left_array, "lhs",
                                               right_array, "rhs",
                                               oss, tol, true );

  std::string expected_details =
    Utility::createComparisonHeader<Policy,0>( left_array, "lhs",
                                               right_array, "rhs",
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
                                               left_array.size(), "lhs", true,
                                               right_array.size(), "rhs", true,
                                               ".size()", local_oss, true );
    for( size_t i = 0; i < left_array.size(); ++i )
    {
      Utility::ComparisonTraits<T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                left_array[i], "lhs", true,
                right_array[i], "rhs", true,
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
                                               right_array, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( {T(1), T(1), T(1)}, "lhs",
                                               right_array, "rhs",
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
                                               right_array.size(), "rhs", true,
                                               ".size()", local_oss, true );
    for( size_t i = 0; i < right_array.size(); ++i )
    {
      Utility::ComparisonTraits<T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                T(1), "lhs", false,
                right_array[i], "rhs", true,
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

  compare_result = Utility::compare<Policy,0>( left_array, "lhs",
                                               {T(1), T(1), T(1)}, "rhs",
                                               oss, tol, true );

  expected_details =
    Utility::createComparisonHeader<Policy,0>( left_array, "lhs",
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
                                                left_array.size(), "lhs", true,
                                                3, "rhs", false,
                                                ".size()", local_oss, true );

    for( size_t i = 0; i < left_array.size(); ++i )
    {
      Utility::ComparisonTraits<T>::template compare<Policy,Utility::Details::incrementRightShift(0)>(
                left_array[i], "lhs", true,
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
// end tstArray.cpp
//---------------------------------------------------------------------------//
