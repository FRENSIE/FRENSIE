//---------------------------------------------------------------------------//
//!
//! \file   tstTuple.cpp
//! \author Alex Robinson
//! \brief  Tuple unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

// FRENSIE Includes
#include "Utility_Tuple.hpp"

//---------------------------------------------------------------------------//
// Template Test Types
//---------------------------------------------------------------------------//
typedef boost::mpl::list<int,unsigned,long,float,double> TestTypes1;

typedef boost::mpl::list<std::tuple<int,int>, std::tuple<unsigned,unsigned>, std::tuple<long,long>, std::tuple<float,float>, std::tuple<double,double>, std::tuple<double,int>, std::tuple<int,double> > TestTypes2;

typedef boost::mpl::list<std::tuple<int,int,int>, std::tuple<unsigned,unsigned,unsigned>, std::tuple<long,long,long>, std::tuple<float,float,float>, std::tuple<double,double,double>, std::tuple<double,int,unsigned>, std::tuple<int, unsigned, double>, std::tuple<double,unsigned,int> > TestTypes3;

typedef boost::mpl::list<std::tuple<int,int,int,int>, std::tuple<unsigned,unsigned,unsigned,unsigned>, std::tuple<long,long,long,long>, std::tuple<float,float,float,float>, std::tuple<double,double,double,double>, std::tuple<float,double,int,unsigned>, std::tuple<unsigned,float,double,int>, std::tuple<int,unsigned,float,double>, std::tuple<double,int,unsigned,float>, std::tuple<float,int,double,unsigned>, std::tuple<double,int,float,unsigned>, std::tuple<float,unsigned,double,int>, std::tuple<double,unsigned,float,int> > TestTypes4;

typedef boost::mpl::list<Utility::EqualityComparisonPolicy,Utility::InequalityComparisonPolicy,Utility::GreaterThanComparisonPolicy,Utility::GreaterThanOrEqualToComparisonPolicy,Utility::LessThanComparisonPolicy,Utility::LessThanOrEqualToComparisonPolicy,Utility::CloseComparisonPolicy,Utility::RelativeErrorComparisonPolicy> ComparisonPolicies;

template<typename Policy>
struct TypeList
{
  typedef boost::mpl::list<std::tuple<Policy,int>,std::tuple<Policy,unsigned>,std::tuple<Policy,long>,std::tuple<Policy,float>,std::tuple<Policy,double> > type1;
  typedef boost::mpl::list<std::tuple<Policy,int,int>, std::tuple<Policy,unsigned,unsigned>, std::tuple<Policy,long,long>, std::tuple<Policy,float,float>, std::tuple<Policy,double,double>, std::tuple<Policy,double,int>, std::tuple<Policy,int,double> > type2;
  typedef boost::mpl::list<std::tuple<Policy,int,int,int,int>, std::tuple<Policy,unsigned,unsigned,unsigned,unsigned>, std::tuple<Policy,long,long,long,long>, std::tuple<Policy,float,float,float,float>, std::tuple<Policy,double,double,double,double>, std::tuple<Policy,float,double,int,unsigned>, std::tuple<Policy,unsigned,float,double,int>, std::tuple<Policy,int,unsigned,float,double>, std::tuple<Policy,double,int,unsigned,float>, std::tuple<Policy,float,int,double,unsigned>, std::tuple<Policy,double,int,float,unsigned>, std::tuple<Policy,float,unsigned,double,int>, std::tuple<Policy,double,unsigned,float,int> > type3;
  typedef boost::mpl::list<std::tuple<Policy,int,int,int,int>, std::tuple<Policy,unsigned,unsigned,unsigned,unsigned>, std::tuple<Policy,long,long,long,long>, std::tuple<Policy,float,float,float,float>, std::tuple<Policy,double,double,double,double>, std::tuple<Policy,float,double,int,unsigned>, std::tuple<Policy,unsigned,float,double,int>, std::tuple<Policy,int,unsigned,float,double>, std::tuple<Policy,double,int,unsigned,float>, std::tuple<Policy,float,int,double,unsigned>, std::tuple<Policy,double,int,float,unsigned>, std::tuple<Policy,float,unsigned,double,int>, std::tuple<Policy,double,unsigned,float,int> > type4;
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

typedef typename MergeTypeLists<typename TypeList<Utility::EqualityComparisonPolicy>::type1, typename TypeList<Utility::InequalityComparisonPolicy>::type1, typename TypeList<Utility::GreaterThanComparisonPolicy>::type1, typename TypeList<Utility::GreaterThanOrEqualToComparisonPolicy>::type1, typename TypeList<Utility::LessThanComparisonPolicy>::type1, typename TypeList<Utility::LessThanOrEqualToComparisonPolicy>::type1, typename TypeList<Utility::CloseComparisonPolicy>::type1, typename TypeList<Utility::RelativeErrorComparisonPolicy>::type1>::type PolicyTestTypes1;

typedef typename MergeTypeLists<typename TypeList<Utility::EqualityComparisonPolicy>::type2, typename TypeList<Utility::InequalityComparisonPolicy>::type2, typename TypeList<Utility::GreaterThanComparisonPolicy>::type2, typename TypeList<Utility::GreaterThanOrEqualToComparisonPolicy>::type2, typename TypeList<Utility::LessThanComparisonPolicy>::type2, typename TypeList<Utility::LessThanOrEqualToComparisonPolicy>::type2, typename TypeList<Utility::CloseComparisonPolicy>::type2, typename TypeList<Utility::RelativeErrorComparisonPolicy>::type2>::type PolicyTestTypes2;

typedef typename MergeTypeLists<typename TypeList<Utility::EqualityComparisonPolicy>::type3, typename TypeList<Utility::InequalityComparisonPolicy>::type3, typename TypeList<Utility::GreaterThanComparisonPolicy>::type3, typename TypeList<Utility::GreaterThanOrEqualToComparisonPolicy>::type3, typename TypeList<Utility::LessThanComparisonPolicy>::type3, typename TypeList<Utility::LessThanOrEqualToComparisonPolicy>::type3, typename TypeList<Utility::CloseComparisonPolicy>::type3, typename TypeList<Utility::RelativeErrorComparisonPolicy>::type3>::type PolicyTestTypes3;

typedef typename MergeTypeLists<typename TypeList<Utility::EqualityComparisonPolicy>::type4, typename TypeList<Utility::InequalityComparisonPolicy>::type4, typename TypeList<Utility::GreaterThanComparisonPolicy>::type4, typename TypeList<Utility::GreaterThanOrEqualToComparisonPolicy>::type4, typename TypeList<Utility::LessThanComparisonPolicy>::type4, typename TypeList<Utility::LessThanOrEqualToComparisonPolicy>::type4, typename TypeList<Utility::CloseComparisonPolicy>::type4, typename TypeList<Utility::RelativeErrorComparisonPolicy>::type4>::type PolicyTestTypes4;

//---------------------------------------------------------------------------//
// Basic Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( Basic )

//---------------------------------------------------------------------------//
// Check that the size of a tuple can be determined
BOOST_AUTO_TEST_CASE_TEMPLATE( TupleSize, T, TestTypes1 )
{
  BOOST_CHECK_EQUAL( Utility::TupleSize<T>::value, 1 );
}

//---------------------------------------------------------------------------//
// Check that basic types can be treated like tuples
BOOST_AUTO_TEST_CASE_TEMPLATE( get, T, TestTypes1 )
{
  T value( 1 );

  BOOST_CHECK_EQUAL( Utility::get<0>( value ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( value ), 1 );
}

//---------------------------------------------------------------------------//
// Check that basic types can be treated like tuples
BOOST_AUTO_TEST_CASE_TEMPLATE( get_reference, T, TestTypes1 )
{
  T value( 1 );

  Utility::get<0>( value ) = 2;
  BOOST_CHECK_EQUAL( Utility::get<0>( value ), 2 );

  Utility::get<Utility::FIRST>( value ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( value ), 3 );
}

//---------------------------------------------------------------------------//
// Check that a tuple element can be set
BOOST_AUTO_TEST_CASE_TEMPLATE( set, T, TestTypes1 )
{
  T tuple( 1 );
  
  typename Utility::TupleElement<0,T>::type value( 2 );

  Utility::set<0>( tuple, value );

  BOOST_CHECK_EQUAL( Utility::get<0>( tuple ), 2 );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// Empty Tuple Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( Tuple_0 )

//---------------------------------------------------------------------------//
// Check that the size of a tuple can be determined
BOOST_AUTO_TEST_CASE( TupleSize )
{
  BOOST_CHECK_EQUAL( Utility::TupleSize<std::tuple<> >::value, 0 );
  BOOST_CHECK_EQUAL( Utility::TupleSize<std::tuple<> >::value, 0 );

  BOOST_CHECK_EQUAL( std::tuple_size<std::tuple<> >::value, 0 );
  BOOST_CHECK_EQUAL( std::tuple_size<std::tuple<> >::value, 0 );
}

//---------------------------------------------------------------------------//
// Check that the tuple can be serialized
BOOST_AUTO_TEST_CASE( serialize )
{
  std::tuple<> empty_tuple;

  std::string archived_tuple;

  // Archive the tuple
  {
    std::ostringstream oss;

    boost::archive::binary_oarchive tuple_oarchive(oss);

    BOOST_CHECK_NO_THROW( tuple_oarchive << empty_tuple );

    archived_tuple = oss.str();
    
    BOOST_CHECK( archived_tuple.size() > 0 );
  }

  // Restore the tuple
  {
    std::istringstream iss(archived_tuple);
    
    boost::archive::binary_iarchive tuple_iarchive(iss);

    BOOST_CHECK_NO_THROW( tuple_iarchive >> empty_tuple );
  }
}

//---------------------------------------------------------------------------//
// Check that two tuples can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, Policy, ComparisonPolicies )
{
  std::ostringstream oss;

  bool compare_result =
    Utility::ComparisonTraits<std::tuple<> >::template compare<Policy,0>(
                                               std::tuple<>(), "lhs", false,
                                               std::tuple<>(), "rhs", false,
                                               "", oss );

  bool expected_compare_result =
    Policy::compare( std::tuple<>(), std::tuple<>() );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  compare_result =
    Utility::ComparisonTraits<std::tuple<> >::template compare<Policy,0>(
                                               std::tuple<>(), "lhs", false,
                                               std::tuple<>(), "rhs", false,
                                               "", oss, false,
                                               1e-6 );

  expected_compare_result = Policy::compare( std::tuple<>(), std::tuple<>() );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  compare_result =
    Utility::ComparisonTraits<std::tuple<> >::template compare<Policy,0>(
                                               std::tuple<>(), "lhs", false,
                                               std::tuple<>(), "rhs", false,
                                               "", oss, true );

  expected_compare_result = Policy::compare( std::tuple<>(), std::tuple<>() );

  std::string expected_details =
    Policy::createComparisonDetails( "lhs", false, std::tuple<>(),
                                     "rhs", false, std::tuple<>(),
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<> >::template compare<Policy,0>(
                                               std::tuple<>(), "lhs", true,
                                               std::tuple<>(), "rhs", false,
                                               "", oss, true );

  expected_compare_result = Policy::compare( std::tuple<>(), std::tuple<>() );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, std::tuple<>(),
                                     "rhs", false, std::tuple<>(),
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<> >::template compare<Policy,0>(
                                               std::tuple<>(), "lhs", false,
                                               std::tuple<>(), "rhs", true,
                                               "", oss, true );

  expected_compare_result = Policy::compare( std::tuple<>(), std::tuple<>() );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, std::tuple<>(),
                                     "rhs", true, std::tuple<>(),
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<> >::template compare<Policy,0>(
                                               std::tuple<>(), "lhs", true,
                                               std::tuple<>(), "rhs", true,
                                               "", oss, true );

  expected_compare_result = Policy::compare( std::tuple<>(), std::tuple<>() );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, std::tuple<>(),
                                     "rhs", true, std::tuple<>(),
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<> >::template compare<Policy,0>(
                                               std::tuple<>(), "lhs", true,
                                               std::tuple<>(), "rhs", true,
                                               "", oss, true,
                                               1e-6 );

  expected_compare_result = Policy::compare( std::tuple<>(), std::tuple<>() );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, std::tuple<>(),
                                     "rhs", true, std::tuple<>(),
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
}

//---------------------------------------------------------------------------//
// Check that two tuples can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare_helper, Policy, ComparisonPolicies )
{
  std::tuple<> left_value;
  const std::tuple<> const_left_value;

  std::tuple<> right_value;
  const std::tuple<> const_right_value;
  
  std::ostringstream oss;

  bool compare_result = Utility::compare<Policy,0>( left_value, "lhs",
                                                    right_value, "rhs",
                                                    oss );
  bool expected_compare_result = Policy::compare( left_value, right_value );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_value, "lhs",
                                               right_value, "rhs",
                                               oss, 1e-6, true );
  expected_compare_result = Policy::compare( left_value, right_value );

  std::string expected_details =
    Policy::createComparisonDetails( "lhs", true, left_value,
                                     "rhs", true, right_value,
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( const_left_value, "lhs",
                                               const_right_value, "rhs",
                                               oss, 1e-6, true );
  expected_compare_result = Policy::compare( left_value, right_value );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, const_left_value,
                                     "rhs", true, const_right_value,
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( std::tuple<>(), "lhs",
                                               right_value, "rhs",
                                               oss, 1e-6, true );
  expected_compare_result = Policy::compare( left_value, right_value );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, left_value,
                                     "rhs", true, right_value,
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( std::tuple<>(), "lhs",
                                               const_right_value, "rhs",
                                               oss, 1e-6, true );
  expected_compare_result = Policy::compare( left_value, right_value );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, const_left_value,
                                     "rhs", true, const_right_value,
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_value, "lhs",
                                               std::tuple<>(), "rhs",
                                               oss, 1e-6, true );
  expected_compare_result = Policy::compare( left_value, right_value );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, left_value,
                                     "rhs", false, right_value,
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( const_left_value, "lhs",
                                               std::tuple<>(), "rhs",
                                               oss, 1e-6, true );
  expected_compare_result = Policy::compare( left_value, right_value );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, const_left_value,
                                     "rhs", false, const_right_value,
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( std::tuple<>(), "lhs",
                                               std::tuple<>(), "rhs",
                                               oss, 1e-6, true );
  expected_compare_result = Policy::compare( left_value, right_value );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, left_value,
                                     "rhs", false, right_value,
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// Single Element Tuple Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( Tuple_1 )

//---------------------------------------------------------------------------//
// Check that the size of a tuple can be determined
BOOST_AUTO_TEST_CASE_TEMPLATE( TupleSize, T, TestTypes1 )
{
  BOOST_CHECK_EQUAL( Utility::TupleSize<std::tuple<T> >::value, 1 );
  BOOST_CHECK_EQUAL( Utility::TupleSize<std::tuple<T> >::value, 1 );

  BOOST_CHECK_EQUAL( std::tuple_size<std::tuple<T> >::value, 1 );
}

//---------------------------------------------------------------------------//
// Check that a 1-element tuple's elements can be retrieved
BOOST_AUTO_TEST_CASE_TEMPLATE( get, T, TestTypes1 )
{
  std::tuple<T> tuple_1( 1 );
  
  BOOST_CHECK_EQUAL( std::get<0>( tuple_1 ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<0>( tuple_1 ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( tuple_1 ), 1 );

  // Check that the std tuple will also work
  std::tuple<T> std_tuple_1( 1 );

  BOOST_CHECK_EQUAL( Utility::get<0>( std_tuple_1 ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( std_tuple_1 ), 1 );
}

//---------------------------------------------------------------------------//
// Check that a 1-element tuple's elements can be retrieved
BOOST_AUTO_TEST_CASE_TEMPLATE( get_reference, T, TestTypes1 )
{
  std::tuple<T> tuple_1( 1 );

  std::get<0>( tuple_1 ) = 2;
  BOOST_CHECK_EQUAL( std::get<0>( tuple_1 ), 2 );

  Utility::get<0>( tuple_1 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<0>( tuple_1 ), 3 );

  Utility::get<Utility::FIRST>( tuple_1 ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( tuple_1 ), 4 );

  // Check that the std tuple will also work
  std::tuple<T> std_tuple_1( 1 );

  Utility::get<0>( std_tuple_1 ) = 2;
  BOOST_CHECK_EQUAL( Utility::get<0>( std_tuple_1 ), 2 );

  Utility::get<Utility::FIRST>( std_tuple_1 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( std_tuple_1 ), 3 );
}

//---------------------------------------------------------------------------//
// Check that a tuple element can be set
BOOST_AUTO_TEST_CASE_TEMPLATE( set, T, TestTypes1 )
{
  std::tuple<T> tuple_1( 1 );

  typename Utility::TupleElement<0,decltype(tuple_1)>::type value_0( 2 );

  Utility::set<0>( tuple_1, value_0 );

  BOOST_CHECK_EQUAL( Utility::get<0>( tuple_1 ), 2 );

  // Check that std tuple will also work
  std::tuple<T> std_tuple_1( 1 );

  typename Utility::TupleElement<0,decltype(std_tuple_1)>::type std_value_0( 2 );

  Utility::set<0>( std_tuple_1, std_value_0 );
}

//---------------------------------------------------------------------------//
// Check that the tuple can be serialized
BOOST_AUTO_TEST_CASE_TEMPLATE( serialize, T, TestTypes1 )
{
  std::tuple<T> tuple( 1 );
  
  std::string archived_tuple;

  // Archive the tuple
  {
    std::ostringstream oss;

    boost::archive::binary_oarchive tuple_oarchive(oss);

    BOOST_CHECK_NO_THROW( tuple_oarchive << tuple );

    archived_tuple = oss.str();
    
    BOOST_CHECK( archived_tuple.size() > 0 );
  }

  std::tuple<T> restored_tuple;

  // Restore the tuple
  {
    std::istringstream iss(archived_tuple);
    
    boost::archive::binary_iarchive tuple_iarchive(iss);

    BOOST_CHECK_NO_THROW( tuple_iarchive >> restored_tuple );
  }

  BOOST_CHECK_EQUAL( Utility::get<0>( tuple ),
                     Utility::get<0>( restored_tuple ) );
}

//---------------------------------------------------------------------------//
// Check that two tuples can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, TypePair, PolicyTestTypes1 )
{
  typedef typename std::tuple_element<0,TypePair>::type Policy;
  typedef typename std::tuple_element<1,TypePair>::type T;

  std::tuple<T> left_value = std::make_tuple( T(0) );
  std::tuple<T> right_value = std::make_tuple( T(0) );
  std::ostringstream oss;

  // No details logging
  bool compare_result =
    Utility::ComparisonTraits<std::tuple<T> >::template compare<Policy,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss );

  bool expected_compare_result =
    Policy::compare( Utility::get<0>(left_value),
                     Utility::get<0>(right_value) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  compare_result =
    Utility::ComparisonTraits<std::tuple<T> >::template compare<Policy,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss, false,
                                                     1e-6 );

  expected_compare_result = Policy::compare( Utility::get<0>(left_value),
                                             Utility::get<0>(right_value),
                                             T(1e-6) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  // Details logging
  compare_result =
    Utility::ComparisonTraits<std::tuple<T> >::template compare<Policy,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss, true );
  expected_compare_result = Policy::compare( Utility::get<0>(left_value),
                                             Utility::get<0>(right_value) );

  std::string expected_details =
    Policy::createComparisonDetails("lhs", false, Utility::get<0>(left_value),
                                    "rhs", false, Utility::get<0>(right_value),
                                    "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<T> >::template compare<Policy,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss, true,
                                                     1e-6 );
  expected_compare_result = Policy::compare( Utility::get<0>(left_value),
                                             Utility::get<0>(right_value),
                                             T(1e-6) );

  expected_details =
    Policy::createComparisonDetails("lhs", false, Utility::get<0>(left_value),
                                    "rhs", false, Utility::get<0>(right_value),
                                    "", T(1e-6) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<T> >::template compare<Policy,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", false,
                                                     "", oss, true );
  expected_compare_result = Policy::compare( Utility::get<0>(left_value),
                                             Utility::get<0>(right_value) );

  expected_details =
    Policy::createComparisonDetails("lhs", true, Utility::get<0>(left_value),
                                    "rhs", false, Utility::get<0>(right_value),
                                    "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<T> >::template compare<Policy,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", false,
                                                     "", oss, true,
                                                     1e-6 );
  expected_compare_result = Policy::compare( Utility::get<0>(left_value),
                                             Utility::get<0>(right_value),
                                             T(1e-6) );

  expected_details =
    Policy::createComparisonDetails("lhs", true, Utility::get<0>(left_value),
                                    "rhs", false, Utility::get<0>(right_value),
                                    "", T(1e-6) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<T> >::template compare<Policy,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", true,
                                                     "", oss, true );
  expected_compare_result = Policy::compare( Utility::get<0>(left_value),
                                             Utility::get<0>(right_value) );

  expected_details =
    Policy::createComparisonDetails("lhs", false, Utility::get<0>(left_value),
                                    "rhs", true, Utility::get<0>(right_value),
                                    "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<T> >::template compare<Policy,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", true,
                                                     "", oss, true,
                                                     1e-6 );
  expected_compare_result = Policy::compare( Utility::get<0>(left_value),
                                             Utility::get<0>(right_value),
                                             T(1e-6) );

  expected_details =
    Policy::createComparisonDetails("lhs", false, Utility::get<0>(left_value),
                                    "rhs", true, Utility::get<0>(right_value),
                                    "", T(1e-6) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<T> >::template compare<Policy,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", true,
                                                     "", oss, true );
  expected_compare_result = Policy::compare( Utility::get<0>(left_value),
                                             Utility::get<0>(right_value) );

  expected_details =
    Policy::createComparisonDetails("lhs", true, Utility::get<0>(left_value),
                                    "rhs", true, Utility::get<0>(right_value),
                                    "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<T> >::template compare<Policy,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", true,
                                                     "", oss, true,
                                                     1e-6 );
  expected_compare_result = Policy::compare( Utility::get<0>(left_value),
                                             Utility::get<0>(right_value),
                                             T(1e-6) );

  expected_details =
    Policy::createComparisonDetails("lhs", true, Utility::get<0>(left_value),
                                    "rhs", true, Utility::get<0>(right_value),
                                    "", T(1e-6) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();
}

//---------------------------------------------------------------------------//
// Check that two tuples can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare_helper, TypePair, PolicyTestTypes1 )
{
  typedef typename std::tuple_element<0,TypePair>::type Policy;
  typedef typename std::tuple_element<1,TypePair>::type T;

  std::tuple<T> left_value = std::make_tuple( T(0) );
  const std::tuple<T> const_left_value = left_value;

  std::tuple<T> right_value = std::make_tuple( T(0) );
  const std::tuple<T> const_right_value = right_value;
  
  std::ostringstream oss;

  bool compare_result = Utility::compare<Policy,0>( left_value, "lhs",
                                                    right_value, "rhs",
                                                    oss );
                                                  
  bool expected_compare_result =
    Policy::compare( Utility::get<0>(left_value),
                     Utility::get<0>(right_value) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( const_left_value, "lhs",
                                               const_right_value, "rhs",
                                               oss, 1e-6, false );

  expected_compare_result = Policy::compare( Utility::get<0>(left_value),
                                             Utility::get<0>(right_value),
                                             T(1e-6) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_value, "lhs",
                                               right_value, "rhs",
                                               oss, 1e-6, true );

  expected_compare_result = Policy::compare( Utility::get<0>(left_value),
                                             Utility::get<0>(right_value),
                                             T(1e-6) );

  std::string expected_details =
    Policy::createComparisonDetails( "lhs", true, Utility::get<0>(left_value),
                                     "rhs", true, Utility::get<0>(right_value),
                                     "", T(1e-6) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( const_left_value, "lhs",
                                               const_right_value, "rhs",
                                               oss, 1e-6, true );

  expected_compare_result = Policy::compare( Utility::get<0>(left_value),
                                             Utility::get<0>(right_value),
                                             T(1e-6) );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, Utility::get<0>(left_value),
                                     "rhs", true, Utility::get<0>(right_value),
                                     "", T(1e-6) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( std::make_tuple( T(0) ), "lhs",
                                               right_value, "rhs",
                                               oss, 1e-6, true );

  expected_compare_result = Policy::compare( T(0),
                                             Utility::get<0>(right_value),
                                             T(1e-6) );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, T(0),
                                     "rhs", true, Utility::get<0>(right_value),
                                     "", T(1e-6) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( std::make_tuple( T(0) ), "lhs",
                                               const_right_value, "rhs",
                                               oss, 1e-6, true );

  expected_compare_result = Policy::compare( T(0),
                                             Utility::get<0>(right_value),
                                             T(1e-6) );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, T(0),
                                     "rhs", true, Utility::get<0>(right_value),
                                     "", T(1e-6) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_value, "lhs",
                                               std::make_tuple( T(0) ), "rhs",
                                               oss, 1e-6, true );

  expected_compare_result = Policy::compare( Utility::get<0>(left_value),
                                             T(0),
                                             T(1e-6) );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, Utility::get<0>(left_value),
                                     "rhs", false, T(0),
                                     "", T(1e-6) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( const_left_value, "lhs",
                                               std::make_tuple( T(0) ), "rhs",
                                               oss, 1e-6, true );

  expected_compare_result = Policy::compare( Utility::get<0>(left_value ),
                                             T(0),
                                             T(1e-6) );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, Utility::get<0>(left_value),
                                     "rhs", false, T(0),
                                     "", T(1e-6) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( std::make_tuple( T(0) ), "lhs",
                                               std::make_tuple( T(0) ), "rhs",
                                               oss, 1e-6, true );

  expected_compare_result = Policy::compare( T(0), T(0), T(1e-6) );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, T(0),
                                     "rhs", false, T(0),
                                     "", T(1e-6) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n" );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// Double Element Tuple Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( Tuple_2 )

//---------------------------------------------------------------------------//
// Check that the size of a tuple can be determined
BOOST_AUTO_TEST_CASE_TEMPLATE( TupleSize, TypePair, TestTypes2 )
{
  typedef typename std::tuple_element<0,TypePair>::type T1;
  typedef typename std::tuple_element<1,TypePair>::type T2;

  BOOST_CHECK_EQUAL( (Utility::TupleSize<std::tuple<T1,T2> >::value), 2 );
  BOOST_CHECK_EQUAL( (Utility::TupleSize<std::tuple<T1,T2> >::value), 2 );
  BOOST_CHECK_EQUAL( (Utility::TupleSize<std::tuple<T1,T2> >::value), 2 );

  BOOST_CHECK_EQUAL( (std::tuple_size<std::tuple<T1,T2> >::value), 2 );
  BOOST_CHECK_EQUAL( (std::tuple_size<std::tuple<T1,T2> >::value), 2 );
  BOOST_CHECK_EQUAL( (std::tuple_size<std::tuple<T1,T2> >::value), 2 );
}

//---------------------------------------------------------------------------//
// Check that a 2-element tuple's elements can be retrieved
BOOST_AUTO_TEST_CASE_TEMPLATE( get, TypePair, TestTypes2 )
{
  typedef typename std::tuple_element<0,TypePair>::type T1;
  typedef typename std::tuple_element<1,TypePair>::type T2;

  std::tuple<T1,T2> tuple_2( 2, 1 );
  
  BOOST_CHECK_EQUAL( std::get<0>( tuple_2 ), 2 );
  BOOST_CHECK_EQUAL( Utility::get<0>( tuple_2 ), 2 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( tuple_2 ), 2 );

  BOOST_CHECK_EQUAL( std::get<1>( tuple_2 ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<1>( tuple_2 ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( tuple_2 ), 1 );

  // Check that the pair alias will also work
  std::tuple<T1,T2> pair( 2, 1 );

  BOOST_CHECK_EQUAL( std::get<0>( pair ), 2 );
  BOOST_CHECK_EQUAL( Utility::get<0>( pair ), 2 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( pair ), 2 );

  BOOST_CHECK_EQUAL( std::get<1>( pair ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<1>( pair ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( pair ), 1 );

  // Check that the std tuple will also work
  std::tuple<T1,T2> std_tuple_2( 2, 1 );

  BOOST_CHECK_EQUAL( Utility::get<0>( std_tuple_2 ), 2 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( std_tuple_2 ), 2 );

  BOOST_CHECK_EQUAL( Utility::get<1>( std_tuple_2 ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( std_tuple_2 ), 1 );
}

//---------------------------------------------------------------------------//
// Check that a 2-element tuple's elements can be retrieved
BOOST_AUTO_TEST_CASE_TEMPLATE( get_reference, TypePair, TestTypes2 )
{
  typedef typename std::tuple_element<0,TypePair>::type T1;
  typedef typename std::tuple_element<1,TypePair>::type T2;

  std::tuple<T1,T2> tuple_2( 1, 1 );

  std::get<0>( tuple_2 ) = 2;
  BOOST_CHECK_EQUAL( std::get<0>( tuple_2 ), 2 );

  Utility::get<0>( tuple_2 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<0>( tuple_2 ), 3 );

  Utility::get<Utility::FIRST>( tuple_2 ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( tuple_2 ), 4 );

  std::get<1>( tuple_2 ) = 2;
  BOOST_CHECK_EQUAL( std::get<1>( tuple_2 ), 2 );

  Utility::get<1>( tuple_2 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<1>( tuple_2 ), 3 );

  Utility::get<Utility::SECOND>( tuple_2 ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( tuple_2 ), 4 );

  // Check that the pair alias will also work
  std::tuple<T1,T2> pair( 1, 1 );

  std::get<0>( pair ) = 2;
  BOOST_CHECK_EQUAL( std::get<0>( pair ), 2 );

  Utility::get<0>( pair ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<0>( pair ), 3 );

  Utility::get<Utility::FIRST>( pair ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( pair ), 4 );

  std::get<1>( pair ) = 2;
  BOOST_CHECK_EQUAL( std::get<1>( pair ), 2 );

  Utility::get<1>( pair ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<1>( pair ), 3 );

  Utility::get<Utility::SECOND>( pair ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( pair ), 4 );

  // Check that the std tuple will also work
  std::tuple<T1,T2> std_tuple_2( 1, 1 );

  Utility::get<0>( std_tuple_2 ) = 2;
  BOOST_CHECK_EQUAL( Utility::get<0>( std_tuple_2 ), 2 );

  Utility::get<Utility::FIRST>( std_tuple_2 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( std_tuple_2 ), 3 );

  Utility::get<1>( std_tuple_2 ) = 2;
  BOOST_CHECK_EQUAL( Utility::get<1>( std_tuple_2 ), 2 );

  Utility::get<Utility::SECOND>( std_tuple_2 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( std_tuple_2 ), 3 );
}

//---------------------------------------------------------------------------//
// Check that a tuple element can be set
BOOST_AUTO_TEST_CASE_TEMPLATE( set, TypePair, TestTypes2 )
{
  typedef typename std::tuple_element<0,TypePair>::type T1;
  typedef typename std::tuple_element<1,TypePair>::type T2;

  std::tuple<T1,T2> tuple_2( 1, 1 );

  typename Utility::TupleElement<0,decltype(tuple_2)>::type value_0( 2 );

  Utility::set<Utility::FIRST>( tuple_2, value_0 );

  BOOST_CHECK_EQUAL( Utility::get<0>( tuple_2 ), value_0 );

  typename Utility::TupleElement<1,decltype(tuple_2)>::type value_1( 2 );

  Utility::set<Utility::SECOND>( tuple_2, value_1 );

  BOOST_CHECK_EQUAL( Utility::get<1>( tuple_2 ), value_1 );

  // Check that std tuple will also work
  std::tuple<T1,T2> std_tuple_2( 1, 1 );

  typename Utility::TupleElement<0,decltype(std_tuple_2)>::type std_value_0( 2 );

  Utility::set<0>( std_tuple_2, std_value_0 );

  BOOST_CHECK_EQUAL( Utility::get<0>( std_tuple_2 ), std_value_0 );

  typename Utility::TupleElement<1,decltype(std_tuple_2)>::type std_value_1( 2 );

  Utility::set<1>( std_tuple_2, std_value_1 );

  BOOST_CHECK_EQUAL( Utility::get<1>( std_tuple_2 ), std_value_1 );
}

//---------------------------------------------------------------------------//
// Check that the tuple can be serialized
BOOST_AUTO_TEST_CASE_TEMPLATE( serialize, TypePair, TestTypes2 )
{
  typedef typename std::tuple_element<0,TypePair>::type T1;
  typedef typename std::tuple_element<1,TypePair>::type T2;

  std::tuple<T1,T2> tuple( 1, 1 );
  
  std::string archived_tuple;

  // Archive the tuple
  {
    std::ostringstream oss;

    boost::archive::binary_oarchive tuple_oarchive(oss);

    BOOST_CHECK_NO_THROW( tuple_oarchive << tuple );

    archived_tuple = oss.str();
    
    BOOST_CHECK( archived_tuple.size() > 0 );
  }

  std::tuple<T1,T2> restored_tuple;

  // Restore the tuple
  {
    std::istringstream iss(archived_tuple);
    
    boost::archive::binary_iarchive tuple_iarchive(iss);

    BOOST_CHECK_NO_THROW( tuple_iarchive >> restored_tuple );
  }

  BOOST_CHECK_EQUAL( Utility::get<0>( tuple ),
                     Utility::get<0>( restored_tuple ) );
  BOOST_CHECK_EQUAL( Utility::get<1>( tuple ),
                     Utility::get<1>( restored_tuple ) );
}

//---------------------------------------------------------------------------//
// Check that two tuples can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, TypeList, PolicyTestTypes2 )
{
  typedef typename std::tuple_element<0,TypeList>::type Policy;
  typedef typename std::tuple_element<1,TypeList>::type T1;
  typedef typename std::tuple_element<2,TypeList>::type T2;

  std::tuple<T1,T2> left_value = std::make_tuple( T1(0), T2(1) );
  std::tuple<T1,T2> right_value = std::make_tuple( T1(1), T2(0) );
  std::ostringstream oss;

  // No details logging
  bool compare_result =
    Utility::ComparisonTraits<std::tuple<T1,T2> >::template compare<Policy,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss );

  bool expected_compare_result;

  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    expected_compare_result =
      Policy::compare( Utility::get<0>(left_value),
                       Utility::get<0>(right_value) ) &&
      Policy::compare( Utility::get<1>(left_value),
                       Utility::get<1>(right_value) );
  }
  else
    expected_compare_result = Policy::compare( left_value, right_value );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result =
    Utility::ComparisonTraits<std::tuple<T1,T2> >::template compare<Policy,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss, false,
                                                     1e-6 );
  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    expected_compare_result =
      Policy::compare( Utility::get<0>(left_value),
                       Utility::get<0>(right_value),
                       T1(1e-6) ) &&
      Policy::compare( Utility::get<1>(left_value),
                       Utility::get<1>(right_value),
                       T2(1e-6) );
  }
  else
    expected_compare_result = Policy::compare( left_value, right_value );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  // Details logging
  compare_result =
    Utility::ComparisonTraits<std::tuple<T1,T2> >::template compare<Policy,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss, true );
  std::string expected_details;

  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    bool expected_compare_result_0 =
      Policy::compare( Utility::get<0>(left_value),
                       Utility::get<0>(right_value) );
    bool expected_compare_result_1 = 
      Policy::compare( Utility::get<1>(left_value),
                       Utility::get<1>(right_value) );
    
    expected_compare_result =
      expected_compare_result_0 && expected_compare_result_1;

    expected_details =
      Utility::ComparisonTraits<std::tuple<T1,T2> >::template createComparisonHeader<Policy,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "" ) +
      (expected_compare_result ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails("lhs", false, Utility::get<0>(left_value),
                                      "rhs", false, Utility::get<0>(right_value),
                                      "" ) + ": " +
      (expected_compare_result_0 ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails("lhs", false, Utility::get<1>(left_value),
                                      "rhs", false, Utility::get<1>(right_value),
                                      "" ) + ": " +
      (expected_compare_result_1 ? "passed\n" : "failed!\n" );
  }
  else
  {
    expected_compare_result = Policy::compare( left_value, right_value );

    expected_details =
      Policy::createComparisonDetails( "lhs", false, left_value,
                                       "rhs", false, right_value,
                                       "", std::tuple<T1,T2>() ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n" );
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<T1,T2> >::template compare<Policy,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss, true,
                                                     1e-6 );
  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    bool expected_compare_result_0 =
      Policy::compare( Utility::get<0>(left_value),
                       Utility::get<0>(right_value),
                       T1(1e-6) );
    bool expected_compare_result_1 = 
      Policy::compare( Utility::get<1>(left_value),
                       Utility::get<1>(right_value),
                       T2(1e-6) );
    
    expected_compare_result =
      expected_compare_result_0 && expected_compare_result_1;

    expected_details =
      Utility::ComparisonTraits<std::tuple<T1,T2> >::template createComparisonHeader<Policy,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", 1e-6 ) +
      (expected_compare_result ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails("lhs", false, Utility::get<0>(left_value),
                                      "rhs", false, Utility::get<0>(right_value),
                                      "", T1(1e-6) ) + ": " +
      (expected_compare_result_0 ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails("lhs", false, Utility::get<1>(left_value),
                                      "rhs", false, Utility::get<1>(right_value),
                                      "", T2(1e-6) ) + ": " +
      (expected_compare_result_1 ? "passed\n" : "failed!\n" );
  }
  else
  {
    expected_compare_result = Policy::compare( left_value, right_value );

    expected_details =
      Policy::createComparisonDetails( "lhs", false, left_value,
                                       "rhs", false, right_value,
                                       "", std::tuple<T1,T2>() ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n" );
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<T1,T2> >::template compare<Policy,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", false,
                                                     "", oss, true );
  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    bool expected_compare_result_0 =
      Policy::compare( Utility::get<0>(left_value),
                       Utility::get<0>(right_value) );
    bool expected_compare_result_1 = 
      Policy::compare( Utility::get<1>(left_value),
                       Utility::get<1>(right_value) );
    expected_compare_result =
      expected_compare_result_0 && expected_compare_result_1;

    expected_details =
      Utility::ComparisonTraits<std::tuple<T1,T2> >::template createComparisonHeader<Policy,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", false,
                                                     "" ) +
      (expected_compare_result ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails("Utility::get<0>(lhs)", true, Utility::get<0>(left_value),
                                      "rhs", false, Utility::get<0>(right_value),
                                      "" ) + ": " +
      (expected_compare_result_0 ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails("Utility::get<1>(lhs)", true, Utility::get<1>(left_value),
                                      "rhs", false, Utility::get<1>(right_value),
                                      "" ) + ": " +
      (expected_compare_result_1 ? "passed\n" : "failed!\n" );
  }
  else
  {
    expected_compare_result = Policy::compare( left_value, right_value );

    expected_details =
      Policy::createComparisonDetails( "lhs", true, left_value,
                                       "rhs", false, right_value,
                                       "", std::tuple<T1,T2>() ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n" );
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<T1,T2> >::template compare<Policy,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", false,
                                                     "", oss, true,
                                                     1e-6 );
  
  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    bool expected_compare_result_0 =
      Policy::compare( Utility::get<0>(left_value),
                       Utility::get<0>(right_value),
                       T1(1e-6) );
    bool expected_compare_result_1 = 
      Policy::compare( Utility::get<1>(left_value),
                       Utility::get<1>(right_value),
                       T2(1e-6) );
    
    expected_compare_result =
      expected_compare_result_0 && expected_compare_result_1;

    expected_details =
      Utility::ComparisonTraits<std::tuple<T1,T2> >::template createComparisonHeader<Policy,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", false,
                                                     "", 1e-6 ) +
      (expected_compare_result ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails("Utility::get<0>(lhs)", true, Utility::get<0>(left_value),
                                      "rhs", false, Utility::get<0>(right_value),
                                      "", T1(1e-6) ) + ": " +
      (expected_compare_result_0 ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails("Utility::get<1>(lhs)", true, Utility::get<1>(left_value),
                                      "rhs", false, Utility::get<1>(right_value),
                                      "", T2(1e-6) ) + ": " +
      (expected_compare_result_1 ? "passed\n" : "failed!\n" );
  }
  else
  {
    expected_compare_result = Policy::compare( left_value, right_value );

    expected_details =
      Policy::createComparisonDetails( "lhs", true, left_value,
                                       "rhs", false, right_value,
                                       "", std::tuple<T1,T2>() ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n" );
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<T1,T2> >::template compare<Policy,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", true,
                                                     "", oss, true );

  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    bool expected_compare_result_0 =
      Policy::compare( Utility::get<0>(left_value),
                       Utility::get<0>(right_value) );
    bool expected_compare_result_1 = 
      Policy::compare( Utility::get<1>(left_value),
                       Utility::get<1>(right_value) );
    
    expected_compare_result =
      expected_compare_result_0 && expected_compare_result_1;

    expected_details =
      Utility::ComparisonTraits<std::tuple<T1,T2> >::template createComparisonHeader<Policy,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", true,
                                                     "" ) +
      (expected_compare_result ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails("lhs", false, Utility::get<0>(left_value),
                                      "Utility::get<0>(rhs)", true, Utility::get<0>(right_value),
                                      "" ) + ": " +
      (expected_compare_result_0 ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails("lhs", false, Utility::get<1>(left_value),
                                      "Utility::get<1>(rhs)", true, Utility::get<1>(right_value),
                                      "" ) + ": " +
      (expected_compare_result_1 ? "passed\n" : "failed!\n" );
  }
  else
  {
    expected_compare_result = Policy::compare( left_value, right_value );

    expected_details =
      Policy::createComparisonDetails( "lhs", false, left_value,
                                       "rhs", true, right_value,
                                       "", std::tuple<T1,T2>() ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n" );
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<T1,T2> >::template compare<Policy,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", true,
                                                     "", oss, true,
                                                     1e-6 );

  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    bool expected_compare_result_0 =
      Policy::compare( Utility::get<0>(left_value),
                       Utility::get<0>(right_value),
                       T1(1e-6) );
    bool expected_compare_result_1 = 
      Policy::compare( Utility::get<1>(left_value),
                       Utility::get<1>(right_value),
                       T2(1e-6) );
    
    bool expected_compare_result =
      expected_compare_result_0 && expected_compare_result_1;

    expected_details =
      Utility::ComparisonTraits<std::tuple<T1,T2> >::template createComparisonHeader<Policy,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", true,
                                                     "", 1e-6 ) +
      (expected_compare_result ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails("lhs", false, Utility::get<0>(left_value),
                                      "Utility::get<0>(rhs)", true, Utility::get<0>(right_value),
                                      "", T1(1e-6) ) + ": " +
      (expected_compare_result_0 ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails("lhs", false, Utility::get<1>(left_value),
                                      "Utility::get<1>(rhs)", true, Utility::get<1>(right_value),
                                      "", T2(1e-6) ) + ": " +
      (expected_compare_result_1 ? "passed\n" : "failed!\n" );
  }
  else
  {
    expected_compare_result = Policy::compare( left_value, right_value );

    expected_details =
      Policy::createComparisonDetails( "lhs", false, left_value,
                                       "rhs", true, right_value,
                                       "", std::tuple<T1,T2>() ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n" );
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<T1,T2> >::template compare<Policy,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", true,
                                                     "", oss, true );

  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    bool expected_compare_result_0 =
      Policy::compare( Utility::get<0>(left_value),
                       Utility::get<0>(right_value) );
    bool expected_compare_result_1 = 
      Policy::compare( Utility::get<1>(left_value),
                       Utility::get<1>(right_value) );
    
    expected_compare_result =
      expected_compare_result_0 && expected_compare_result_1;

    expected_details =
      Utility::ComparisonTraits<std::tuple<T1,T2> >::template createComparisonHeader<Policy,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", true,
                                                     "" ) +
      (expected_compare_result ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails("Utility::get<0>(lhs)", true, Utility::get<0>(left_value),
                                      "Utility::get<0>(rhs)", true, Utility::get<0>(right_value),
                                      "" ) + ": " +
      (expected_compare_result_0 ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails("Utility::get<1>(lhs)", true, Utility::get<1>(left_value),
                                      "Utility::get<1>(rhs)", true, Utility::get<1>(right_value),
                                      "" ) + ": " +
      (expected_compare_result_1 ? "passed\n" : "failed!\n" );
  }
  else
  {
    expected_compare_result = Policy::compare( left_value, right_value );
     
    expected_details =
      Policy::createComparisonDetails( "lhs", true, left_value,
                                       "rhs", true, right_value,
                                       "", std::tuple<T1,T2>() ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n" );
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result =
    Utility::ComparisonTraits<std::tuple<T1,T2> >::template compare<Policy,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", true,
                                                     "", oss, true,
                                                     1e-6 );

  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    bool expected_compare_result_0 =
      Policy::compare( Utility::get<0>(left_value),
                       Utility::get<0>(right_value),
                       T1(1e-6) );
    bool expected_compare_result_1 = 
      Policy::compare( Utility::get<1>(left_value),
                       Utility::get<1>(right_value),
                       T2(1e-6) );
    expected_compare_result =
      expected_compare_result_0 && expected_compare_result_1;

    expected_details =
      Utility::ComparisonTraits<std::tuple<T1,T2> >::template createComparisonHeader<Policy,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", true,
                                                     "", 1e-6 ) +
      (expected_compare_result ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails("Utility::get<0>(lhs)", true, Utility::get<0>(left_value),
                                      "Utility::get<0>(rhs)", true, Utility::get<0>(right_value),
                                      "", T1(1e-6) ) + ": " +
      (expected_compare_result_0 ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails("Utility::get<1>(lhs)", true, Utility::get<1>(left_value),
                                      "Utility::get<1>(rhs)", true, Utility::get<1>(right_value),
                                      "", T2(1e-6) ) + ": " +
      (expected_compare_result_1 ? "passed\n" : "failed!\n" );
  }
  else
  {
    expected_compare_result = Policy::compare( left_value, right_value );

    expected_details =
      Policy::createComparisonDetails( "lhs", true, left_value,
                                       "rhs", true, right_value,
                                       "", std::tuple<T1,T2>() ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n" );
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
}

//---------------------------------------------------------------------------//
// Check that two tuples can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare_helper, TypeList, PolicyTestTypes2 )
{
  typedef typename std::tuple_element<0,TypeList>::type Policy;
  typedef typename std::tuple_element<1,TypeList>::type T1;
  typedef typename std::tuple_element<2,TypeList>::type T2;

  std::tuple<T1,T2> left_value = std::make_tuple( T1(0), T2(1) );
  const std::tuple<T1,T2> const_left_value = left_value;

  std::tuple<T1,T2> right_value = std::make_tuple( T1(1), T2(0) );
  const std::tuple<T1,T2> const_right_value = right_value;

  std::ostringstream oss;

  bool compare_result = Utility::compare<Policy,0>( left_value, "lhs",
                                                    right_value, "rhs",
                                                    oss );

  bool expected_compare_result;

  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    expected_compare_result = 
      Policy::compare( Utility::get<0>(left_value),
                       Utility::get<0>(right_value) ) &&
      Policy::compare( Utility::get<1>(left_value),
                       Utility::get<1>(right_value) );
  }
  else
    expected_compare_result = Policy::compare( left_value, right_value );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( const_left_value, "lhs",
                                               const_right_value, "rhs",
                                               oss, 1e-6, false );

  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    expected_compare_result =
      Policy::compare( Utility::get<0>(left_value),
                       Utility::get<0>(right_value),
                       T1(1e-6) ) &&
      Policy::compare( Utility::get<1>(left_value),
                       Utility::get<1>(right_value),
                       T2(1e-6) );
  }
  else
    expected_compare_result = Policy::compare( left_value, right_value );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), "" );

  compare_result = Utility::compare<Policy,0>( left_value, "lhs",
                                               right_value, "rhs",
                                               oss, 1e-6, true );
  std::string expected_details;

  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    bool expected_compare_result_0 =
      Policy::compare( Utility::get<0>(left_value),
                       Utility::get<0>(right_value),
                       T1(1e-6) );
    bool expected_compare_result_1 =
      Policy::compare( Utility::get<1>(left_value),
                       Utility::get<1>(right_value),
                       T2(1e-6) );
    expected_compare_result =
      expected_compare_result_0 && expected_compare_result_1;

    expected_details =
      Utility::createComparisonHeader<Policy,0>( left_value, "lhs",
                                                 right_value, "rhs",
                                                 1e-6, "" ) +
      (expected_compare_result ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails( "Utility::get<0>(lhs)", true, Utility::get<0>(left_value),
                                       "Utility::get<0>(rhs)", true, Utility::get<0>(right_value),
                                       "", T1(1e-6) ) + ": " +
      (expected_compare_result_0 ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails( "Utility::get<1>(lhs)", true, Utility::get<1>(left_value),
                                       "Utility::get<1>(rhs)", true, Utility::get<1>(right_value),
                                       "", T2(1e-6) ) + ": " +
      (expected_compare_result_1 ? "passed\n" : "failed!\n" );
  }
  else
  {
    expected_compare_result = Policy::compare( left_value, right_value );

    expected_details =
      Policy::createComparisonDetails( "lhs", true, left_value,
                                       "rhs", true, right_value,
                                       "", std::tuple<T1,T2>() ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n" );
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( const_left_value, "lhs",
                                               const_right_value, "rhs",
                                               oss, 1e-6, true );

  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    bool expected_compare_result_0 =
      Policy::compare( Utility::get<0>(const_left_value),
                       Utility::get<0>(const_right_value),
                       T1(1e-6) );
    bool expected_compare_result_1 =
      Policy::compare( Utility::get<1>(const_left_value),
                       Utility::get<1>(const_right_value),
                       T2(1e-6) );
    expected_compare_result =
      expected_compare_result_0 && expected_compare_result_1;

    expected_details =
      Utility::createComparisonHeader<Policy,0>( const_left_value, "lhs",
                                                 const_right_value, "rhs",
                                                 1e-6, "" ) +
      (expected_compare_result ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails( "Utility::get<0>(lhs)", true, Utility::get<0>(const_left_value),
                                       "Utility::get<0>(rhs)", true, Utility::get<0>(const_right_value),
                                       "", T1(1e-6) ) + ": " +
      (expected_compare_result_0 ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails( "Utility::get<1>(lhs)", true, Utility::get<1>(const_left_value),
                                       "Utility::get<1>(rhs)", true, Utility::get<1>(const_right_value),
                                       "", T2(1e-6) ) + ": " +
      (expected_compare_result_1 ? "passed\n" : "failed!\n" );
  }
  else
  {
    expected_compare_result =
      Policy::compare( const_left_value, const_right_value );

    expected_details =
      Policy::createComparisonDetails( "lhs", true, const_left_value,
                                       "rhs", true, const_right_value,
                                       "", std::tuple<T1,T2>() ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n" );
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( std::make_tuple(T1(0),T2(1)), "lhs",
                                               right_value, "rhs",
                                               oss, 1e-6, true );

  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    bool expected_compare_result_0 =
      Policy::compare( T1(0), Utility::get<0>(right_value), T1(1e-6) );
    bool expected_compare_result_1 =
      Policy::compare( T2(1), Utility::get<1>(right_value), T2(1e-6) );
    
    expected_compare_result =
      expected_compare_result_0 && expected_compare_result_1;

    expected_details =
      Utility::createComparisonHeader<Policy,0>( std::make_tuple(T1(0),T2(1)), "lhs",
                                                 right_value, "rhs",
                                                 1e-6, "" ) +
      (expected_compare_result ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails( "lhs", false, T1(0),
                                       "Utility::get<0>(rhs)", true, Utility::get<0>(right_value),
                                       "", T1(1e-6) ) + ": " +
      (expected_compare_result_0 ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails( "lhs", false, T2(1),
                                       "Utility::get<1>(rhs)", true, Utility::get<1>(right_value),
                                       "", T2(1e-6) ) + ": " +
      (expected_compare_result_1 ? "passed\n" : "failed!\n" );
  }
  else
  {
    expected_compare_result =
      Policy::compare( std::make_tuple(T1(0),T2(1)), right_value );

    expected_details =
      Policy::createComparisonDetails( "lhs", false, std::make_tuple(T1(0),T2(1)),
                                       "rhs", true, right_value,
                                       "", std::tuple<T1,T2>() ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n" );
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( std::make_tuple(T1(0),T2(1)), "lhs",
                                               const_right_value, "rhs",
                                               oss, 1e-6, true );

  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    bool expected_compare_result_0 =
      Policy::compare( T1(0), Utility::get<0>(const_right_value), T1(1e-6) );
    bool expected_compare_result_1 =
      Policy::compare( T2(1), Utility::get<1>(const_right_value), T2(1e-6) );
    
    expected_compare_result =
      expected_compare_result_0 && expected_compare_result_1;

    expected_details =
      Utility::createComparisonHeader<Policy,0>( std::make_tuple(T1(0),T2(1)), "lhs",
                                                 const_right_value, "rhs",
                                                 1e-6, "" ) +
      (expected_compare_result ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails( "lhs", false, T1(0),
                                       "Utility::get<0>(rhs)", true, Utility::get<0>(const_right_value),
                                       "", T1(1e-6) ) + ": " +
      (expected_compare_result_0 ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails( "lhs", false, T2(1),
                                       "Utility::get<1>(rhs)", true, Utility::get<1>(const_right_value),
                                       "", T2(1e-6) ) + ": " +
      (expected_compare_result_1 ? "passed\n" : "failed!\n" );
  }
  else
  {
    expected_compare_result =
      Policy::compare( std::make_tuple(T1(0),T2(1)), const_right_value );

    expected_details =
      Policy::createComparisonDetails( "lhs", false, std::make_tuple(T1(0),T2(1)),
                                       "rhs", true, const_right_value,
                                       "", std::tuple<T1,T2>() ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n" );
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( left_value, "lhs",
                                               std::make_tuple(T1(0),T2(1)), "rhs",
                                               oss, 1e-6, true );

  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    bool expected_compare_result_0 =
      Policy::compare( Utility::get<0>(left_value), T1(0), T1(1e-6) );
    bool expected_compare_result_1 =
      Policy::compare( Utility::get<1>(left_value), T2(1), T2(1e-6) );
    
    expected_compare_result =
      expected_compare_result_0 && expected_compare_result_1;

    expected_details =
      Utility::createComparisonHeader<Policy,0>( left_value, "lhs",
                                                 std::make_tuple(T1(0),T2(1)), "rhs",
                                                 1e-6, "" ) +
      (expected_compare_result ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails( "Utility::get<0>(lhs)", true, Utility::get<0>(left_value),
                                       "rhs", false, T1(0),
                                       "", T1(1e-6) ) + ": " +
      (expected_compare_result_0 ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails( "Utility::get<1>(lhs)", true, Utility::get<1>(left_value),
                                       "rhs", false, T2(1),
                                       "", T2(1e-6) ) + ": " +
      (expected_compare_result_1 ? "passed\n" : "failed!\n" );
  }
  else
  {
    expected_compare_result =
      Policy::compare( left_value, std::make_tuple(T1(0),T2(1)) );

    expected_details =
      Policy::createComparisonDetails( "lhs", true, left_value,
                                       "rhs", false, std::make_tuple(T1(0),T2(1)),
                                       "", std::tuple<T1,T2>() ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n" );
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( const_left_value, "lhs",
                                               std::make_tuple(T1(0),T2(1)), "rhs",
                                               oss, 1e-6, true );

  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    bool expected_compare_result_0 =
      Policy::compare( Utility::get<0>(const_left_value), T1(0), T1(1e-6) );
    bool expected_compare_result_1 =
      Policy::compare( Utility::get<1>(const_left_value), T2(1), T2(1e-6) );
    
    expected_compare_result =
      expected_compare_result_0 && expected_compare_result_1;

    expected_details =
      Utility::createComparisonHeader<Policy,0>( const_left_value, "lhs",
                                                 std::make_tuple(T1(0),T2(1)), "rhs",
                                                 1e-6, "" ) +
      (expected_compare_result ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails( "Utility::get<0>(lhs)", true, Utility::get<0>(const_left_value),
                                       "rhs", false, T1(0),
                                       "", T1(1e-6) ) + ": " +
      (expected_compare_result_0 ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails( "Utility::get<1>(lhs)", true, Utility::get<1>(const_left_value),
                                       "rhs", false, T2(1),
                                       "", T2(1e-6) ) + ": " +
      (expected_compare_result_1 ? "passed\n" : "failed!\n" );
  }
  else
  {
    expected_compare_result =
      Policy::compare( const_left_value, std::make_tuple(T1(0),T2(1)) );

    expected_details =
      Policy::createComparisonDetails( "lhs", true, const_left_value,
                                       "rhs", false, std::make_tuple(T1(0),T2(1)),
                                       "", std::tuple<T1,T2>() ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n" );
  }
    
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0>( std::make_tuple(T1(1),T2(1)), "lhs",
                                               std::make_tuple(T1(0),T2(1)), "rhs",
                                               oss, 1e-6, true );

  if( std::is_same<Policy,Utility::EqualityComparisonPolicy>::value ||
      std::is_same<Policy,Utility::CloseComparisonPolicy>::value ||
      std::is_same<Policy,Utility::RelativeErrorComparisonPolicy>::value  )
  {
    bool expected_compare_result_0 = Policy::compare( T1(1), T1(0), T1(1e-6) );
    bool expected_compare_result_1 = Policy::compare( T2(1), T2(1), T2(1e-6) );
    
    expected_compare_result =
      expected_compare_result_0 && expected_compare_result_1;

    expected_details =
      Utility::createComparisonHeader<Policy,0>(
                                           std::make_tuple(T1(1),T2(1)), "lhs",
                                           std::make_tuple(T1(0),T2(1)), "rhs",
                                           1e-6 ) +
      (expected_compare_result ? "passed\n" : "failed!\n") +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails( "lhs", false, T1(1),
                                       "rhs", false, T1(0),
                                       ".0", T1(1e-6) ) + ": " +
      (expected_compare_result_0 ? "passed\n" : "failed!\n" ) +
      std::string( Utility::Details::incrementRightShift(0), ' ' ) +
      Policy::createComparisonDetails( "lhs", false, T2(1),
                                       "rhs", false, T2(1),
                                       ".1", T2(1e-6) ) + ": " +
      (expected_compare_result_1 ? "passed\n" : "failed!\n" );
  }
  else
  {
    expected_compare_result =
      Policy::compare( std::make_tuple(T1(1),T2(1)),
                       std::make_tuple(T1(0),T2(1)) );

    expected_details =
      Policy::createComparisonDetails( "lhs", false, std::make_tuple(T1(1),T2(1)),
                                       "rhs", false, std::make_tuple(T1(0),T2(1)),
                                       "", std::tuple<T1,T2>() ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n" );
  }

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// Triple Element Tuple Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( Tuple_3 )

//---------------------------------------------------------------------------//
// Check that the size of a tuple can be determined
BOOST_AUTO_TEST_CASE_TEMPLATE( TupleSize, TypeTrip, TestTypes3 )
{
  typedef typename std::tuple_element<0,TypeTrip>::type T1;
  typedef typename std::tuple_element<1,TypeTrip>::type T2;
  typedef typename std::tuple_element<2,TypeTrip>::type T3;

  BOOST_CHECK_EQUAL( (Utility::TupleSize<std::tuple<T1,T2,T3> >::value), 3 );
  BOOST_CHECK_EQUAL( (Utility::TupleSize<std::tuple<T1,T2,T3> >::value), 3 );
  BOOST_CHECK_EQUAL( (Utility::TupleSize<std::tuple<T1,T2,T3> >::value), 3 );

  BOOST_CHECK_EQUAL( (std::tuple_size<std::tuple<T1,T2,T3> >::value), 3 );
  BOOST_CHECK_EQUAL( (std::tuple_size<std::tuple<T1,T2,T3> >::value), 3 );
}

//---------------------------------------------------------------------------//
// Check that a 3-element tuple's elements can be retrieved
BOOST_AUTO_TEST_CASE_TEMPLATE( get, TypeTrip, TestTypes3 )
{
  typedef typename std::tuple_element<0,TypeTrip>::type T1;
  typedef typename std::tuple_element<1,TypeTrip>::type T2;
  typedef typename std::tuple_element<2,TypeTrip>::type T3;

  std::tuple<T1,T2,T3> tuple_3( 3, 2, 1 );

  BOOST_CHECK_EQUAL( std::get<0>( tuple_3 ), 3 );
  BOOST_CHECK_EQUAL( Utility::get<0>( tuple_3 ), 3 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( tuple_3 ), 3 );

  BOOST_CHECK_EQUAL( std::get<1>( tuple_3 ), 2 );
  BOOST_CHECK_EQUAL( Utility::get<1>( tuple_3 ), 2 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( tuple_3 ), 2 );

  BOOST_CHECK_EQUAL( std::get<2>( tuple_3 ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<2>( tuple_3 ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::THIRD>( tuple_3 ), 1 );

  // Check that the trip alias will also work
  std::tuple<T1,T2,T3> trip( 3, 2, 1 );

  BOOST_CHECK_EQUAL( std::get<0>( trip ), 3 );
  BOOST_CHECK_EQUAL( Utility::get<0>( trip ), 3 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( trip ), 3 );

  BOOST_CHECK_EQUAL( std::get<1>( trip ), 2 );
  BOOST_CHECK_EQUAL( Utility::get<1>( trip ), 2 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( trip ), 2 );

  BOOST_CHECK_EQUAL( std::get<2>( trip ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<2>( trip ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::THIRD>( trip ), 1 );

  // Check that the std tuple will also work
  std::tuple<T1,T2,T3> std_tuple_3( 3, 2, 1 );

  BOOST_CHECK_EQUAL( Utility::get<0>( std_tuple_3 ), 3 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( std_tuple_3 ), 3 );

  BOOST_CHECK_EQUAL( Utility::get<1>( std_tuple_3 ), 2 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( std_tuple_3 ), 2 );

  BOOST_CHECK_EQUAL( Utility::get<2>( std_tuple_3 ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::THIRD>( std_tuple_3 ), 1 );
}

//---------------------------------------------------------------------------//
// Check that a 3-element tuple's elements can be retrieved
BOOST_AUTO_TEST_CASE_TEMPLATE( get_reference, TypeTrip, TestTypes3 )
{
  typedef typename std::tuple_element<0,TypeTrip>::type T1;
  typedef typename std::tuple_element<1,TypeTrip>::type T2;
  typedef typename std::tuple_element<2,TypeTrip>::type T3;

  std::tuple<T1,T2,T3> tuple_3( 1, 1, 1 );

  std::get<0>( tuple_3 ) = 2;
  BOOST_CHECK_EQUAL( std::get<0>( tuple_3 ), 2 );

  Utility::get<0>( tuple_3 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<0>( tuple_3 ), 3 );

  Utility::get<Utility::FIRST>( tuple_3 ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( tuple_3 ), 4 );

  std::get<1>( tuple_3 ) = 2;
  BOOST_CHECK_EQUAL( std::get<1>( tuple_3 ), 2 );

  Utility::get<1>( tuple_3 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<1>( tuple_3 ), 3 );

  Utility::get<Utility::SECOND>( tuple_3 ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( tuple_3 ), 4 );

  std::get<2>( tuple_3 ) = 2;
  BOOST_CHECK_EQUAL( std::get<2>( tuple_3 ), 2 );

  Utility::get<2>( tuple_3 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<2>( tuple_3 ), 3 );

  Utility::get<Utility::THIRD>( tuple_3 ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::THIRD>( tuple_3 ), 4 );

  // Check that the trip alias will also work
  std::tuple<T1,T2,T3> trip( 1, 1, 1 );
  
  std::get<0>( trip ) = 2;
  BOOST_CHECK_EQUAL( std::get<0>( trip ), 2 );

  Utility::get<0>( trip ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<0>( trip ), 3 );

  Utility::get<Utility::FIRST>( trip ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( trip ), 4 );

  std::get<1>( trip ) = 2;
  BOOST_CHECK_EQUAL( std::get<1>( trip ), 2 );

  Utility::get<1>( trip ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<1>( trip ), 3 );

  Utility::get<Utility::SECOND>( trip ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( trip ), 4 );

  std::get<2>( trip ) = 2;
  BOOST_CHECK_EQUAL( std::get<2>( trip ), 2 );

  Utility::get<2>( trip ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<2>( trip ), 3 );

  Utility::get<Utility::THIRD>( trip ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::THIRD>( trip ), 4 );

  // Check that the std tuple will also work
  std::tuple<T1,T2,T3> std_tuple_3( 1, 1, 1 );

  Utility::get<0>( std_tuple_3 ) = 2;
  BOOST_CHECK_EQUAL( Utility::get<0>( std_tuple_3 ), 2 );

  Utility::get<Utility::FIRST>( std_tuple_3 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( std_tuple_3 ), 3 );

  Utility::get<1>( std_tuple_3 ) = 2;
  BOOST_CHECK_EQUAL( Utility::get<1>( std_tuple_3 ), 2 );

  Utility::get<Utility::SECOND>( std_tuple_3 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( std_tuple_3 ), 3 );

  Utility::get<2>( std_tuple_3 ) = 2;
  BOOST_CHECK_EQUAL( Utility::get<2>( std_tuple_3 ), 2 );

  Utility::get<Utility::THIRD>( std_tuple_3 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<Utility::THIRD>( std_tuple_3 ), 3 );
}

//---------------------------------------------------------------------------//
// Check that a tuple element can be set
BOOST_AUTO_TEST_CASE_TEMPLATE( set, TypeTrip, TestTypes3 )
{
  typedef typename std::tuple_element<0,TypeTrip>::type T1;
  typedef typename std::tuple_element<1,TypeTrip>::type T2;
  typedef typename std::tuple_element<2,TypeTrip>::type T3;

  std::tuple<T1,T2,T3> tuple_3( 1, 1, 1 );

  typename Utility::TupleElement<0,decltype(tuple_3)>::type value_0( 2 );

  Utility::set<Utility::FIRST>( tuple_3, value_0 );

  BOOST_CHECK_EQUAL( Utility::get<0>( tuple_3 ), value_0 );

  typename Utility::TupleElement<1,decltype(tuple_3)>::type value_1( 2 );

  Utility::set<Utility::SECOND>( tuple_3, value_1 );

  BOOST_CHECK_EQUAL( Utility::get<1>( tuple_3 ), value_1 );

  typename Utility::TupleElement<2,decltype(tuple_3)>::type value_2( 2 );

  Utility::set<Utility::THIRD>( tuple_3, value_2 );

  BOOST_CHECK_EQUAL( Utility::get<2>( tuple_3 ), value_2 );

  // Check that std tuple will also work
  std::tuple<T1,T2,T3> std_tuple_3( 1, 1, 1 );

  typename Utility::TupleElement<0,decltype(std_tuple_3)>::type std_value_0( 2 );

  Utility::set<0>( std_tuple_3, std_value_0 );

  BOOST_CHECK_EQUAL( Utility::get<0>( std_tuple_3 ), std_value_0 );

  typename Utility::TupleElement<1,decltype(std_tuple_3)>::type std_value_1( 2 );

  Utility::set<1>( std_tuple_3, std_value_1 );

  BOOST_CHECK_EQUAL( Utility::get<1>( std_tuple_3 ), std_value_1 );

  typename Utility::TupleElement<2,decltype(std_tuple_3)>::type std_value_2( 2 );

  Utility::set<2>( std_tuple_3, std_value_2 );

  BOOST_CHECK_EQUAL( Utility::get<2>( std_tuple_3 ), std_value_2 );
}

//---------------------------------------------------------------------------//
// Check that the tuple can be serialized
BOOST_AUTO_TEST_CASE_TEMPLATE( serialize, TypeTrip, TestTypes3 )
{
  typedef typename std::tuple_element<0,TypeTrip>::type T1;
  typedef typename std::tuple_element<1,TypeTrip>::type T2;
  typedef typename std::tuple_element<2,TypeTrip>::type T3;

  std::tuple<T1,T2,T3> tuple( 1, 1, 1 );
  
  std::string archived_tuple;

  // Archive the tuple
  {
    std::ostringstream oss;

    boost::archive::binary_oarchive tuple_oarchive(oss);

    BOOST_CHECK_NO_THROW( tuple_oarchive << tuple );

    archived_tuple = oss.str();
    
    BOOST_CHECK( archived_tuple.size() > 0 );
  }

  std::tuple<T1,T2,T3> restored_tuple;

  // Restore the tuple
  {
    std::istringstream iss(archived_tuple);
    
    boost::archive::binary_iarchive tuple_iarchive(iss);

    BOOST_CHECK_NO_THROW( tuple_iarchive >> restored_tuple );
  }

  BOOST_CHECK_EQUAL( Utility::get<0>( tuple ),
                     Utility::get<0>( restored_tuple ) );
  BOOST_CHECK_EQUAL( Utility::get<1>( tuple ),
                     Utility::get<1>( restored_tuple ) );
  BOOST_CHECK_EQUAL( Utility::get<2>( tuple ),
                     Utility::get<2>( restored_tuple ) );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// Quadruple Element Tuple Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( Tuple_4 )

//---------------------------------------------------------------------------//
// Check that the size of a tuple can be determined
BOOST_AUTO_TEST_CASE_TEMPLATE( TupleSize, TypeQuad, TestTypes4 )
{
  typedef typename std::tuple_element<0,TypeQuad>::type T1;
  typedef typename std::tuple_element<1,TypeQuad>::type T2;
  typedef typename std::tuple_element<2,TypeQuad>::type T3;
  typedef typename std::tuple_element<3,TypeQuad>::type T4;

  BOOST_CHECK_EQUAL( (Utility::TupleSize<std::tuple<T1,T2,T3,T4> >::value), 4 );
  BOOST_CHECK_EQUAL( (Utility::TupleSize<std::tuple<T1,T2,T3,T4> >::value), 4 );
  BOOST_CHECK_EQUAL( (Utility::TupleSize<std::tuple<T1,T2,T3,T4> >::value), 4 );
  
  BOOST_CHECK_EQUAL( (std::tuple_size<std::tuple<T1,T2,T3,T4> >::value), 4 );
  BOOST_CHECK_EQUAL( (std::tuple_size<std::tuple<T1,T2,T3,T4> >::value ), 4 );
}

//---------------------------------------------------------------------------//
// Check that a 4-element tuple's elements can be retrieved
BOOST_AUTO_TEST_CASE_TEMPLATE( get, TypeQuad, TestTypes4 )
{
  typedef typename std::tuple_element<0,TypeQuad>::type T1;
  typedef typename std::tuple_element<1,TypeQuad>::type T2;
  typedef typename std::tuple_element<2,TypeQuad>::type T3;
  typedef typename std::tuple_element<3,TypeQuad>::type T4;

  std::tuple<T1,T2,T3,T4> tuple_4( 4, 3, 2, 1 );

  BOOST_CHECK_EQUAL( std::get<0>( tuple_4 ), 4 );
  BOOST_CHECK_EQUAL( Utility::get<0>( tuple_4 ), 4 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( tuple_4 ), 4 );

  BOOST_CHECK_EQUAL( std::get<1>( tuple_4 ), 3 );
  BOOST_CHECK_EQUAL( Utility::get<1>( tuple_4 ), 3 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( tuple_4 ), 3 );

  BOOST_CHECK_EQUAL( std::get<2>( tuple_4 ), 2 );
  BOOST_CHECK_EQUAL( Utility::get<2>( tuple_4 ), 2 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::THIRD>( tuple_4 ), 2 );

  BOOST_CHECK_EQUAL( std::get<3>( tuple_4 ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<3>( tuple_4 ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::FOURTH>( tuple_4 ), 1 );

  // Check that the quad alias will also work
  std::tuple<T1,T2,T3,T4> quad( 4, 3, 2, 1 );

  BOOST_CHECK_EQUAL( std::get<0>( quad ), 4 );
  BOOST_CHECK_EQUAL( Utility::get<0>( quad ), 4 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( quad ), 4 );

  BOOST_CHECK_EQUAL( std::get<1>( quad ), 3 );
  BOOST_CHECK_EQUAL( Utility::get<1>( quad ), 3 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( quad ), 3 );

  BOOST_CHECK_EQUAL( std::get<2>( quad ), 2 );
  BOOST_CHECK_EQUAL( Utility::get<2>( quad ), 2 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::THIRD>( quad ), 2 );

  BOOST_CHECK_EQUAL( std::get<3>( quad ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<3>( quad ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::FOURTH>( quad ), 1 );

  // Check that the std tuple will also work
  std::tuple<T1,T2,T3,T4> std_tuple_4( 4, 3, 2, 1 );

  BOOST_CHECK_EQUAL( Utility::get<0>( std_tuple_4 ), 4 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( std_tuple_4 ), 4 );

  BOOST_CHECK_EQUAL( Utility::get<1>( std_tuple_4 ), 3 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( std_tuple_4 ), 3 );

  BOOST_CHECK_EQUAL( Utility::get<2>( std_tuple_4 ), 2 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::THIRD>( std_tuple_4 ), 2 );

  BOOST_CHECK_EQUAL( Utility::get<3>( std_tuple_4 ), 1 );
  BOOST_CHECK_EQUAL( Utility::get<Utility::FOURTH>( std_tuple_4 ), 1 );
}

//---------------------------------------------------------------------------//
// Check that a 4-element tuple's elements can be retrieved
BOOST_AUTO_TEST_CASE_TEMPLATE( get_reference, TypeQuad, TestTypes4 )
{
  typedef typename std::tuple_element<0,TypeQuad>::type T1;
  typedef typename std::tuple_element<1,TypeQuad>::type T2;
  typedef typename std::tuple_element<2,TypeQuad>::type T3;
  typedef typename std::tuple_element<3,TypeQuad>::type T4;

  std::tuple<T1,T2,T3,T4> tuple_4( 1, 1, 1, 1 );

  std::get<0>( tuple_4 ) = 2;
  BOOST_CHECK_EQUAL( std::get<0>( tuple_4 ), 2 );

  Utility::get<0>( tuple_4 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<0>( tuple_4 ), 3 );

  Utility::get<Utility::FIRST>( tuple_4 ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( tuple_4 ), 4 );

  std::get<1>( tuple_4 ) = 2;
  BOOST_CHECK_EQUAL( std::get<1>( tuple_4 ), 2 );

  Utility::get<1>( tuple_4 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<1>( tuple_4 ), 3 );

  Utility::get<Utility::SECOND>( tuple_4 ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( tuple_4 ), 4 );

  std::get<2>( tuple_4 ) = 2;
  BOOST_CHECK_EQUAL( std::get<2>( tuple_4 ), 2 );

  Utility::get<2>( tuple_4 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<2>( tuple_4 ), 3 );

  Utility::get<Utility::THIRD>( tuple_4 ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::THIRD>( tuple_4 ), 4 );

  std::get<3>( tuple_4 ) = 2;
  BOOST_CHECK_EQUAL( std::get<3>( tuple_4 ), 2 );

  Utility::get<3>( tuple_4 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<3>( tuple_4 ), 3 );

  Utility::get<Utility::FOURTH>( tuple_4 ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::FOURTH>( tuple_4 ), 4 );

  // Check that the quad alias will also work
  std::tuple<T1,T2,T3,T4> quad( 1, 1, 1, 1 );

  std::get<0>( quad ) = 2;
  BOOST_CHECK_EQUAL( std::get<0>( quad ), 2 );

  Utility::get<0>( quad ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<0>( quad ), 3 );

  Utility::get<Utility::FIRST>( quad ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( quad ), 4 );

  std::get<1>( quad ) = 2;
  BOOST_CHECK_EQUAL( std::get<1>( quad ), 2 );

  Utility::get<1>( quad ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<1>( quad ), 3 );

  Utility::get<Utility::SECOND>( quad ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( quad ), 4 );

  std::get<2>( quad ) = 2;
  BOOST_CHECK_EQUAL( std::get<2>( quad ), 2 );

  Utility::get<2>( quad ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<2>( quad ), 3 );

  Utility::get<Utility::THIRD>( quad ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::THIRD>( quad ), 4 );

  std::get<3>( quad ) = 2;
  BOOST_CHECK_EQUAL( std::get<3>( quad ), 2 );

  Utility::get<3>( quad ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<3>( quad ), 3 );

  Utility::get<Utility::FOURTH>( quad ) = 4;
  BOOST_CHECK_EQUAL( Utility::get<Utility::FOURTH>( quad ), 4 );

  // Check that the std tuple will also work
  std::tuple<T1,T2,T3,T4> std_tuple_4( 1, 1, 1, 1 );

  Utility::get<0>( std_tuple_4 ) = 2;
  BOOST_CHECK_EQUAL( Utility::get<0>( std_tuple_4 ), 2 );

  Utility::get<Utility::FIRST>( std_tuple_4 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<Utility::FIRST>( std_tuple_4 ), 3 );

  Utility::get<1>( std_tuple_4 ) = 2;
  BOOST_CHECK_EQUAL( Utility::get<1>( std_tuple_4 ), 2 );

  Utility::get<Utility::SECOND>( std_tuple_4 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<Utility::SECOND>( std_tuple_4 ), 3 );

  Utility::get<2>( std_tuple_4 ) = 2;
  BOOST_CHECK_EQUAL( Utility::get<2>( std_tuple_4 ), 2 );

  Utility::get<Utility::THIRD>( std_tuple_4 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<Utility::THIRD>( std_tuple_4 ), 3 );

  Utility::get<3>( std_tuple_4 ) = 2;
  BOOST_CHECK_EQUAL( Utility::get<3>( std_tuple_4 ), 2 );

  Utility::get<Utility::FOURTH>( std_tuple_4 ) = 3;
  BOOST_CHECK_EQUAL( Utility::get<Utility::FOURTH>( std_tuple_4 ), 3 );
}

//---------------------------------------------------------------------------//
// Check that a tuple element can be set
BOOST_AUTO_TEST_CASE_TEMPLATE( set, TypeQuad, TestTypes4 )
{
  typedef typename std::tuple_element<0,TypeQuad>::type T1;
  typedef typename std::tuple_element<1,TypeQuad>::type T2;
  typedef typename std::tuple_element<2,TypeQuad>::type T3;
  typedef typename std::tuple_element<3,TypeQuad>::type T4;

  std::tuple<T1,T2,T3,T4> tuple_4( 1, 1, 1, 1 );

  Utility::set<0>( tuple_4, 0 );

  BOOST_CHECK_EQUAL( Utility::get<0>( tuple_4 ), 0 );

  Utility::set<1>( tuple_4, 1 );

  BOOST_CHECK_EQUAL( Utility::get<1>( tuple_4 ), 1 );

  Utility::set<2>( tuple_4, 2 );

  BOOST_CHECK_EQUAL( Utility::get<2>( tuple_4 ), 2 );

  Utility::set<3>( tuple_4, 3 );

  BOOST_CHECK_EQUAL( Utility::get<3>( tuple_4 ), 3 );

  // Check that std tuple will also work
  std::tuple<T1,T2,T3,T4> std_tuple_4( 1, 1, 1, 1 );

  Utility::set<0>( std_tuple_4, 0 );

  BOOST_CHECK_EQUAL( Utility::get<0>( std_tuple_4 ), 0 );

  Utility::set<1>( std_tuple_4, 1 );

  BOOST_CHECK_EQUAL( Utility::get<1>( std_tuple_4 ), 1 );

  Utility::set<2>( std_tuple_4, 2 );

  BOOST_CHECK_EQUAL( Utility::get<2>( std_tuple_4 ), 2 );

  Utility::set<3>( std_tuple_4, 3 );

  BOOST_CHECK_EQUAL( Utility::get<3>( std_tuple_4 ), 3 );
}

//---------------------------------------------------------------------------//
// Check that the tuple can be serialized
BOOST_AUTO_TEST_CASE_TEMPLATE( serialize, TypeQuad, TestTypes4 )
{
  typedef typename std::tuple_element<0,TypeQuad>::type T1;
  typedef typename std::tuple_element<1,TypeQuad>::type T2;
  typedef typename std::tuple_element<2,TypeQuad>::type T3;
  typedef typename std::tuple_element<3,TypeQuad>::type T4;

  std::tuple<T1,T2,T3,T4> tuple( 1, 1, 1, 1 );
  
  std::string archived_tuple;

  // Archive the tuple
  {
    std::ostringstream oss;

    boost::archive::binary_oarchive tuple_oarchive(oss);

    BOOST_CHECK_NO_THROW( tuple_oarchive << tuple );

    archived_tuple = oss.str();
    
    BOOST_CHECK( archived_tuple.size() > 0 );
  }

  std::tuple<T1,T2,T3,T4> restored_tuple;

  // Restore the tuple
  {
    std::istringstream iss(archived_tuple);
    
    boost::archive::binary_iarchive tuple_iarchive(iss);

    BOOST_CHECK_NO_THROW( tuple_iarchive >> restored_tuple );
  }

  BOOST_CHECK_EQUAL( Utility::get<0>( tuple ),
                     Utility::get<0>( restored_tuple ) );
  BOOST_CHECK_EQUAL( Utility::get<1>( tuple ),
                     Utility::get<1>( restored_tuple ) );
  BOOST_CHECK_EQUAL( Utility::get<2>( tuple ),
                     Utility::get<2>( restored_tuple ) );
  BOOST_CHECK_EQUAL( Utility::get<3>( tuple ),
                     Utility::get<3>( restored_tuple ) );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// General Tuple Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( GeneralTuple )

//---------------------------------------------------------------------------//
// Check that tuple types can be converted to a string
BOOST_AUTO_TEST_CASE( toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( std::make_tuple( 0 ) ), "{0}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::make_tuple( 0.0f ) ),
                       "{0.000000000e+00}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::make_tuple( 0.0 ) ),
                       "{0.000000000000000000e+00}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::make_tuple( "test" ) ),
                       "{test}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::make_tuple( true ) ),
                       "{true}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::make_tuple( false ) ),
                       "{false}" );
  
  BOOST_CHECK_EQUAL( Utility::toString( std::make_tuple( -1, 1.0 ) ),
                       "{-1, 1.000000000000000000e+00}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::make_tuple( 1.0f, -1000 ) ),
                       "{1.000000000e+00, -1000}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::make_tuple( 10l, true ) ),
                       "{10, true}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::make_tuple( true, false ) ),
                       "{true, false}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::make_tuple( std::string( "test" ), false ) ),
                       "{test, false}" );

  {
    std::string test_string( "test string" );
    double test_double = 1.0;

    BOOST_CHECK_EQUAL( Utility::toString( std::tie( test_string, test_double ) ),
                         "{test string, 1.000000000000000000e+00}" );
                                            
  }

  BOOST_CHECK_EQUAL( Utility::toString( std::make_tuple( 100u, -1, false ) ),
                       "{100, -1, false}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::make_tuple( 1.0, true, "test" ) ),
                       "{1.000000000000000000e+00, true, test}" );

  {
    const bool test_bool = true;
    const unsigned long long test_ull = 256ull;
    const float test_float = -1.0f;

    BOOST_CHECK_EQUAL( Utility::toString( std::tie( test_bool, test_ull, test_float ) ),
                         "{true, 256, -1.000000000e+00}" );
  }

  BOOST_CHECK_EQUAL( Utility::toString( std::make_tuple( true, -100ll, std::string( "test" ), std::make_tuple( -1.0f, 1.0f ) ) ),
                       "{true, -100, test, {-1.000000000e+00, 1.000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that tuple types can be placed in a stream
BOOST_AUTO_TEST_CASE( toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::make_tuple( 0 ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( 0.0f ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0.000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( 0.0 ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( "test" ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{test}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( true ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{true}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( false ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{false}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( -1, 1.0 ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-1, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( 1.0f, -1000 ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{1.000000000e+00, -1000}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( 10l, true ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{10, true}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( true, false ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{true, false}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( std::string( "test" ), false ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{test, false}" );

  oss.str( "" );
  oss.clear();

  {
    std::string test_string( "test string" );
    double test_double = 1.0;

    Utility::toStream( oss, std::tie( test_string, test_double ) );
    
    BOOST_CHECK_EQUAL( oss.str(),
                         "{test string, 1.000000000000000000e+00}" );

    oss.str( "" );
    oss.clear();                                            
  }

  Utility::toStream( oss, std::make_tuple( 100u, -1, false ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{100, -1, false}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_tuple( 1.0, true, "test" ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{1.000000000000000000e+00, true, test}" );

  oss.str( "" );
  oss.clear();

  {
    const bool test_bool = true;
    const unsigned long long test_ull = 256ull;
    const float test_float = -1.0f;

    Utility::toStream( oss, std::tie( test_bool, test_ull, test_float ) );

    BOOST_CHECK_EQUAL( oss.str(), "{true, 256, -1.000000000e+00}" );

    oss.str( "" );
    oss.clear();
  }

  Utility::toStream( oss, std::make_tuple( true, -100ll, std::string( "test" ), std::make_tuple( -1.0f, 1.0f ) ) );
  
  BOOST_CHECK_EQUAL( oss.str(), 
                       "{true, -100, test, {-1.000000000e+00, 1.000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that pair types can be converted to a string
BOOST_AUTO_TEST_CASE( pair_toString )
{
  BOOST_CHECK_EQUAL( Utility::toString( std::make_pair( -1, 1.0 ) ),
                       "{-1, 1.000000000000000000e+00}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::make_pair( -1.0f, 1l ) ),
                       "{-1.000000000e+00, 1}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::make_pair( "test", true ) ),
                       "{test, true}" );
  BOOST_CHECK_EQUAL( Utility::toString( std::make_pair( false, std::string( "test" ) ) ),
                       "{false, test}" );
}

//---------------------------------------------------------------------------//
// Check that pair types can be placed in a stream
BOOST_AUTO_TEST_CASE( pair_toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, std::make_pair( -1, 1.0 ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-1, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_pair( -1.0f, 1l ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-1.000000000e+00, 1}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_pair( "test", true ) );
 
  BOOST_CHECK_EQUAL( oss.str(), "{test, true}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, std::make_pair( false, std::string( "test" ) ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{false, test}" );
}

//---------------------------------------------------------------------------//
// Check that tuple types can be created from a string
BOOST_AUTO_TEST_CASE( fromString )
{
  BOOST_CHECK_EQUAL( Utility::fromString<std::tuple<int> >( "{0}" ),
                       std::make_tuple( 0 ) );
  BOOST_CHECK_EQUAL( Utility::fromString<std::tuple<float> >( "{0.0}" ),
                       std::make_tuple( 0.0f ) );
  BOOST_CHECK_EQUAL( Utility::fromString<std::tuple<double> >( "{0.0}" ),
                       std::make_tuple( 0.0 ) );
  BOOST_CHECK_EQUAL( Utility::fromString<std::tuple<std::string> >( "{test}" ),
                       std::make_tuple( std::string( "test" ) ) );
  BOOST_CHECK_EQUAL( Utility::fromString<std::tuple<bool> >( "{0}" ),
                       std::make_tuple( false ) );
  BOOST_CHECK_EQUAL( Utility::fromString<std::tuple<bool> >( "{false}" ),
                       std::make_tuple( false ) );
  BOOST_CHECK_EQUAL( Utility::fromString<std::tuple<bool> >( "{1}" ),
                       std::make_tuple( true ) );
  BOOST_CHECK_EQUAL( Utility::fromString<std::tuple<bool> >( "{true}" ),
                       std::make_tuple( true ) );

  BOOST_CHECK_EQUAL( (Utility::fromString<std::tuple<int,double> >( "{-1, 1.000000000000000000e+00}" )),
                       std::make_tuple( -1, 1.0 ) );
  BOOST_CHECK_EQUAL( (Utility::fromString<std::tuple<float,int> >( "{1.000000000e+00, -1000}" )),
                       std::make_tuple( 1.0f, -1000 ) );
  BOOST_CHECK_EQUAL( (Utility::fromString<std::tuple<long,bool> >( "{10, true}" )),
                       std::make_tuple( 10l, true ) );
  BOOST_CHECK_EQUAL( (Utility::fromString<std::tuple<bool,bool> >( "{1, false}" )),
                       std::make_tuple( true, false ) );
  BOOST_CHECK_EQUAL( (Utility::fromString<std::tuple<std::string,bool> >( "{test, 0}" )),
                       std::make_tuple( std::string( "test" ), false ) );

  {
    std::string test_string;
    double test_double;

    auto tuple_proxy = std::tie( test_string, test_double );

    tuple_proxy = Utility::fromString<decltype(tuple_proxy)>( "{test, -1.0}" );

    BOOST_CHECK_EQUAL( test_string, "test" );
    BOOST_CHECK_EQUAL( test_double, -1.0 );
  }

  BOOST_CHECK_EQUAL( (Utility::fromString<std::tuple<unsigned,int,bool> >( "{100, -1, false}" )),
                       std::make_tuple( 100u, -1, false ) );
  BOOST_CHECK_EQUAL( (Utility::fromString<std::tuple<double,bool,std::string> >( "{1.0, 1, test}" )),
                       std::make_tuple( 1.0, true, std::string( "test" ) ) );

  {
    bool test_bool;
    unsigned long long test_ull;
    float test_float;

    auto tuple_proxy = std::tie( test_bool, test_ull, test_float );
    decltype(tuple_proxy)& tuple_proxy_reference = tuple_proxy;

    tuple_proxy = Utility::fromString<decltype(tuple_proxy_reference)>( "{true, 100000, -1.0}" );

    BOOST_CHECK_EQUAL( test_bool, true );
    BOOST_CHECK_EQUAL( test_ull, 100000 );
    BOOST_CHECK_EQUAL( test_float, -1.0f );
  }

  BOOST_CHECK_EQUAL( (Utility::fromString<std::tuple<bool,long long,std::string,std::tuple<float,double> > >( "{true, -100, test, {-1.0, 1.0}}" )),
                       std::make_tuple( true, -100ll, std::string( "test" ), std::make_tuple( -1.0f, 1.0 ) ) );
}

//---------------------------------------------------------------------------//
// Check that tuple types can be extracted from a stream
BOOST_AUTO_TEST_CASE( fromStream )
{
  std::istringstream iss( "{0}" );

  {
    std::tuple<int> test_tuple;

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( 0 ) );
  }

  iss.str( "{0.0}" );
  iss.clear();

  {
    std::tuple<float> test_tuple;

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( 0.0f ) );
  }

  iss.str( "{0.0}" );
  iss.clear();

  {
    std::tuple<double> test_tuple;

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( 0.0 ) );
  }

  iss.str( "{test}" );
  iss.clear();

  {
    std::tuple<std::string> test_tuple;

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( std::string( "test" ) ) );
  }

  iss.str( "{0}" );
  iss.clear();

  {
    std::tuple<bool> test_tuple;

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( false ) );

    iss.str( "{false}" );
    iss.clear();

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( false ) );

    iss.str( "{1}" );
    iss.clear();

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( true ) );

    iss.str( "{true}" );
    iss.clear();

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( true ) );
  }

  iss.str( "{-1, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::tuple<int,double> test_tuple;

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( -1, 1.0 ) );
  }

  iss.str( "{1.000000000e+00, -1000}" );
  iss.clear();

  {
    std::tuple<float,int> test_tuple;

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( 1.0f, -1000 ) );
  }

  iss.str( "{10, true}" );
  iss.clear();

  {
    std::tuple<long,bool> test_tuple;

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( 10l, true ) );
  }

  iss.str( "{1, false}" );
  iss.clear();

  {
    std::tuple<bool,bool> test_tuple;

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( true, false ) );
  }

  iss.str( "{test, 0}" );
  iss.clear();

  {
    std::tuple<std::string,bool> test_tuple;

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( std::string( "test" ), false ) );
  }

  iss.str( "{test, -1.0}" );
  iss.clear();
  
  {
    std::string test_string;
    double test_double;

    auto tuple_proxy = std::tie( test_string, test_double );

    Utility::fromStream( iss, tuple_proxy );

    BOOST_CHECK_EQUAL( test_string, "test" );
    BOOST_CHECK_EQUAL( test_double, -1.0 );
  }

  iss.str( "{100, -1, false}" );
  iss.clear();

  {
    std::tuple<unsigned,int,bool> test_tuple;

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( 100u, -1, false ) );
  }

  iss.str( "{1.0, 1, test}" );
  iss.clear();

  {
    std::tuple<double,bool,std::string> test_tuple;

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( 1.0, true, std::string( "test" ) ) );
  }

  iss.str( "{true, 100000, -1.0}" );
  iss.clear();

  {
    bool test_bool;
    unsigned long long test_ull;
    float test_float;

    auto tuple_proxy = std::tie( test_bool, test_ull, test_float );
    decltype(tuple_proxy)& tuple_proxy_reference = tuple_proxy;

    Utility::fromStream( iss, tuple_proxy_reference );

    BOOST_CHECK_EQUAL( test_bool, true );
    BOOST_CHECK_EQUAL( test_ull, 100000 );
    BOOST_CHECK_EQUAL( test_float, -1.0f );
  }

  iss.str( "{true, -100, test, {-1.0, 1.0}}" );
  iss.clear();

  {
    std::tuple<bool,long long,std::string,std::tuple<float,double> > test_tuple;

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( true, -100ll, std::string( "test" ), std::make_tuple( -1.0f, 1.0 ) ) );
  }

  iss.str( "{1, test 0}, {-1, test 1}" );
  iss.clear();

  {
    std::tuple<int,std::string> test_tuple;

    Utility::fromStream( iss, test_tuple, "," );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( 1, std::string( "test 0" ) ) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    Utility::fromStream( iss, test_tuple );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( -1, std::string( "test 1" ) ) );
  }
}

//---------------------------------------------------------------------------//
// Check that pair types can be created from a string
BOOST_AUTO_TEST_CASE( pair_fromString )
{
  BOOST_CHECK_EQUAL( (Utility::fromString<std::pair<int,double> >( "{-1, 1.000000000000000000e+00}" )),
                       std::make_pair( -1, 1.0 ) );
  BOOST_CHECK_EQUAL( (Utility::fromString<std::pair<float,long> >( "{-1.0, 1}" )),
                       std::make_pair( -1.0f, 1l ) );
  BOOST_CHECK_EQUAL( (Utility::fromString<std::pair<std::string,bool> >( "{test, true}" )),
                       std::make_pair( std::string( "test" ), true ) );
  BOOST_CHECK_EQUAL( (Utility::fromString<std::pair<bool,std::string> >( "{0, test}" )),
                       std::make_pair( false, std::string( "test" ) ) );

  {
    long test_long;
    double test_double;

    std::pair<long&, double&> pair_proxy = std::make_pair( std::ref( test_long ), std::ref( test_double ) );

    pair_proxy = Utility::fromString<std::pair<long&, double&> >( "{-1000000, -1.0}" );

    BOOST_CHECK_EQUAL( test_long, -1000000l );
    BOOST_CHECK_EQUAL( test_double, -1.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that pair types can be extracted from a stream
BOOST_AUTO_TEST_CASE( pair_fromStream )
{
  std::istringstream iss( "{-1, 1.000000000000000000e+00}" );

  {
    std::pair<int,double> test_pair;

    Utility::fromStream( iss, test_pair );

    BOOST_CHECK_EQUAL( test_pair, std::make_pair( -1, 1.0 ) );
  }

  iss.str( "{-1.0, 1}" );
  iss.clear();

  {
    std::pair<float,long> test_pair;

    Utility::fromStream( iss, test_pair );
    
    BOOST_CHECK_EQUAL( test_pair, std::make_pair( -1.0f, 1l ) );
  }

  iss.str( "{test, true}" );
  iss.clear();

  {
    std::pair<std::string,bool> test_pair;

    Utility::fromStream( iss, test_pair );

    BOOST_CHECK_EQUAL( test_pair, std::make_pair( std::string( "test" ), true ) );
  }

  iss.str( "{0, test}" );
  iss.clear();

  {
    std::pair<bool,std::string> test_pair;

    Utility::fromStream( iss, test_pair );

    BOOST_CHECK_EQUAL( test_pair, std::make_pair( false, std::string( "test" ) ) );
  }

  iss.str( "{-1000000, -1.0}" );
  iss.clear();
  
  {
    long test_long;
    double test_double;

    std::pair<long&, double&> pair_proxy =
      std::make_pair( std::ref( test_long ), std::ref( test_double ) );

    std::pair<long&, double&>& pair_proxy_reference = pair_proxy;

    Utility::fromStream( iss, pair_proxy_reference );

    BOOST_CHECK_EQUAL( test_long, -1000000l );
    BOOST_CHECK_EQUAL( test_double, -1.0 );
  }

  iss.str( "{1, test 0}, {-1, test 1}" );
  iss.clear();

  {
    std::pair<int,std::string> test_pair;

    Utility::fromStream( iss, test_pair, "," );

    BOOST_CHECK_EQUAL( test_pair, std::make_pair( 1, std::string( "test 0" ) ) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    Utility::fromStream( iss, test_pair );

    BOOST_CHECK_EQUAL( test_pair, std::make_pair( -1, std::string( "test 1" ) ) );
  }
}

//---------------------------------------------------------------------------//
// Check that a pair can be placed in a stream
BOOST_AUTO_TEST_CASE( pair_ostream )
{
  std::ostringstream oss;
  oss << std::make_pair( -1, 1.0 );

  BOOST_CHECK_EQUAL( oss.str(), "{-1, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_pair( -1.0f, 1l );

  BOOST_CHECK_EQUAL( oss.str(), "{-1.000000000e+00, 1}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_pair( "test", true );
  
  BOOST_CHECK_EQUAL( oss.str(), "{test, true}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_pair( false, std::string( "test" ) );
  
  BOOST_CHECK_EQUAL( oss.str(), "{false, test}" );
}

//---------------------------------------------------------------------------//
// Check that a pair can be extracted from a stream
BOOST_AUTO_TEST_CASE( pair_istream )
{
  std::istringstream iss( "{-1, 1.000000000000000000e+00}" );

  {
    std::pair<int,double> test_pair;

    iss >> test_pair;

    BOOST_CHECK_EQUAL( test_pair, std::make_pair( -1, 1.0 ) );
  }

  iss.str( "{-1.0, 1}" );
  iss.clear();

  {
    std::pair<float,long> test_pair;

    iss >> test_pair;
    
    BOOST_CHECK_EQUAL( test_pair, std::make_pair( -1.0f, 1l ) );
  }

  iss.str( "{test, true}" );
  iss.clear();

  {
    std::pair<std::string,bool> test_pair;

    iss >> test_pair;

    BOOST_CHECK_EQUAL( test_pair, std::make_pair( std::string( "test" ), true ) );
  }

  iss.str( "{0, test}" );
  iss.clear();

  {
    std::pair<bool,std::string> test_pair;

    iss >> test_pair;

    BOOST_CHECK_EQUAL( test_pair, std::make_pair( false, std::string( "test" ) ) );
  }

  iss.str( "{-1000000, -1.0}" );
  iss.clear();
  
  {
    long test_long;
    double test_double;

    std::pair<long&, double&> pair_proxy =
      std::make_pair( std::ref( test_long ), std::ref( test_double ) );

    std::pair<long&, double&>& pair_proxy_reference = pair_proxy;

    Utility::fromStream( iss, pair_proxy_reference );

    BOOST_CHECK_EQUAL( test_long, -1000000l );
    BOOST_CHECK_EQUAL( test_double, -1.0 );
  }

  iss.str( "{1, test 0}, {-1, test 1}" );
  iss.clear();

  {
    std::pair<int,std::string> test_pair;

    Utility::fromStream( iss, test_pair, "," );

    BOOST_CHECK_EQUAL( test_pair, std::make_pair( 1, std::string( "test 0" ) ) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    iss >> test_pair;

    BOOST_CHECK_EQUAL( test_pair, std::make_pair( -1, std::string( "test 1" ) ) );
  }
}

//---------------------------------------------------------------------------//
// Check that a tuple can be placed in a stream
BOOST_AUTO_TEST_CASE( ostream )
{
  std::ostringstream oss;

  oss << std::make_tuple( 0 );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( 0.0f );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0.000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( 0.0 );
  
  BOOST_CHECK_EQUAL( oss.str(), "{0.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( "test" );
  
  BOOST_CHECK_EQUAL( oss.str(), "{test}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( true );
  
  BOOST_CHECK_EQUAL( oss.str(), "{true}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( false );
  
  BOOST_CHECK_EQUAL( oss.str(), "{false}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( -1, 1.0 );
  
  BOOST_CHECK_EQUAL( oss.str(), "{-1, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( 1.0f, -1000 );
  
  BOOST_CHECK_EQUAL( oss.str(), "{1.000000000e+00, -1000}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( 10l, true );
  
  BOOST_CHECK_EQUAL( oss.str(), "{10, true}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( true, false );
  
  BOOST_CHECK_EQUAL( oss.str(), "{true, false}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( std::string( "test" ), false );
  
  BOOST_CHECK_EQUAL( oss.str(), "{test, false}" );

  oss.str( "" );
  oss.clear();

  {
    std::string test_string( "test string" );
    double test_double = 1.0;

    oss << std::tie( test_string, test_double );
    
    BOOST_CHECK_EQUAL( oss.str(),
                         "{test string, 1.000000000000000000e+00}" );

    oss.str( "" );
    oss.clear();                                            
  }

  oss << std::make_tuple( 100u, -1, false );
  
  BOOST_CHECK_EQUAL( oss.str(), "{100, -1, false}" );

  oss.str( "" );
  oss.clear();

  oss << std::make_tuple( 1.0, true, "test" );
  
  BOOST_CHECK_EQUAL( oss.str(), "{1.000000000000000000e+00, true, test}" );

  oss.str( "" );
  oss.clear();

  {
    const bool test_bool = true;
    const unsigned long long test_ull = 256ull;
    const float test_float = -1.0f;

    oss << std::tie( test_bool, test_ull, test_float );

    BOOST_CHECK_EQUAL( oss.str(), "{true, 256, -1.000000000e+00}" );

    oss.str( "" );
    oss.clear();
  }

  oss << std::make_tuple( true, -100ll, std::string( "test" ), std::make_tuple( -1.0f, 1.0f ) );
  
  BOOST_CHECK_EQUAL( oss.str(), 
                       "{true, -100, test, {-1.000000000e+00, 1.000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that a tuple can be extracted from a stream
BOOST_AUTO_TEST_CASE( istream )
{
  std::istringstream iss( "{0}" );

  {
    std::tuple<int> test_tuple;

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( 0 ) );
  }

  iss.str( "{0.0}" );
  iss.clear();

  {
    std::tuple<float> test_tuple;

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( 0.0f ) );
  }

  iss.str( "{0.0}" );
  iss.clear();

  {
    std::tuple<double> test_tuple;

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( 0.0 ) );
  }

  iss.str( "{test}" );
  iss.clear();

  {
    std::tuple<std::string> test_tuple;

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( std::string( "test" ) ) );
  }

  iss.str( "{0}" );
  iss.clear();

  {
    std::tuple<bool> test_tuple;

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( false ) );

    iss.str( "{false}" );
    iss.clear();

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( false ) );

    iss.str( "{1}" );
    iss.clear();

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( true ) );

    iss.str( "{true}" );
    iss.clear();

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( true ) );
  }

  iss.str( "{-1, 1.000000000000000000e+00}" );
  iss.clear();

  {
    std::tuple<int,double> test_tuple;

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( -1, 1.0 ) );
  }

  iss.str( "{1.000000000e+00, -1000}" );
  iss.clear();

  {
    std::tuple<float,int> test_tuple;

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( 1.0f, -1000 ) );
  }

  iss.str( "{10, true}" );
  iss.clear();

  {
    std::tuple<long,bool> test_tuple;

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( 10l, true ) );
  }

  iss.str( "{1, false}" );
  iss.clear();

  {
    std::tuple<bool,bool> test_tuple;

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( true, false ) );
  }

  iss.str( "{test, 0}" );
  iss.clear();

  {
    std::tuple<std::string,bool> test_tuple;

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( std::string( "test" ), false ) );
  }

  iss.str( "{test, -1.0}" );
  iss.clear();
  
  {
    std::string test_string;
    double test_double;

    auto tuple_proxy = std::tie( test_string, test_double );

    Utility::fromStream( iss, tuple_proxy );

    BOOST_CHECK_EQUAL( test_string, "test" );
    BOOST_CHECK_EQUAL( test_double, -1.0 );
  }

  iss.str( "{100, -1, false}" );
  iss.clear();

  {
    std::tuple<unsigned,int,bool> test_tuple;

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( 100u, -1, false ) );
  }

  iss.str( "{1.0, 1, test}" );
  iss.clear();

  {
    std::tuple<double,bool,std::string> test_tuple;

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( 1.0, true, std::string( "test" ) ) );
  }

  iss.str( "{true, 100000, -1.0}" );
  iss.clear();

  {
    bool test_bool;
    unsigned long long test_ull;
    float test_float;

    auto tuple_proxy = std::tie( test_bool, test_ull, test_float );
    decltype(tuple_proxy)& tuple_proxy_reference = tuple_proxy;

    Utility::fromStream( iss, tuple_proxy_reference );

    BOOST_CHECK_EQUAL( test_bool, true );
    BOOST_CHECK_EQUAL( test_ull, 100000 );
    BOOST_CHECK_EQUAL( test_float, -1.0f );
  }

  iss.str( "{true, -100, test, {-1.0, 1.0}}" );
  iss.clear();

  {
    std::tuple<bool,long long,std::string,std::tuple<float,double> > test_tuple;

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( true, -100ll, std::string( "test" ), std::make_tuple( -1.0f, 1.0 ) ) );
  }

  iss.str( "{1, test 0}, {-1, test 1}" );
  iss.clear();

  {
    std::tuple<int,std::string> test_tuple;

    Utility::fromStream( iss, test_tuple, "," );

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( 1, std::string( "test 0" ) ) );

    Utility::moveInputStreamToNextElement( iss, ',', '}' );

    iss >> test_tuple;

    BOOST_CHECK_EQUAL( test_tuple, std::make_tuple( -1, std::string( "test 1" ) ) );
  }
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// end tstTuple.cpp
//---------------------------------------------------------------------------//
