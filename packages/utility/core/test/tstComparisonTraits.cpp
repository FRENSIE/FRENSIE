//---------------------------------------------------------------------------//
//!
//! \file   tstComparisonTraits.cpp
//! \author Alex Robinson
//! \brief  Comparison traits unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/energy.hpp>
#include <boost/units/systems/si/energy.hpp>

// FRENSIE Includes
#include "Utility_ComparisonTraits.hpp"
#include "Utility_QuantityTraits.hpp"

//---------------------------------------------------------------------------//
// Template Test Types
//---------------------------------------------------------------------------//
template<typename Policy>
struct TypeList
{
  typedef boost::mpl::list<std::tuple<Policy,bool>,
                           std::tuple<Policy,char>,
                           std::tuple<Policy,signed char>,
                           std::tuple<Policy,unsigned char>,
                           std::tuple<Policy,short>,
                           std::tuple<Policy,unsigned short>,
                           std::tuple<Policy,int>,
                           std::tuple<Policy,long>,
                           std::tuple<Policy,unsigned>,
                           std::tuple<Policy,unsigned long>,
                           std::tuple<Policy,long long>,
                           std::tuple<Policy,unsigned long long>,
                           std::tuple<Policy,float>,
                           std::tuple<Policy,double>,
                           std::tuple<Policy,boost::units::quantity<boost::units::si::energy> >,
                           std::tuple<Policy,std::string> > type;

  typedef boost::mpl::list<std::tuple<Policy,short>,
                           std::tuple<Policy,unsigned short>,
                           std::tuple<Policy,int>,
                           std::tuple<Policy,long>,
                           std::tuple<Policy,unsigned>,
                           std::tuple<Policy,unsigned long>,
                           std::tuple<Policy,long long>,
                           std::tuple<Policy,unsigned long long>,
                           std::tuple<Policy,float>,
                           std::tuple<Policy,double>,
                           std::tuple<Policy,boost::units::quantity<boost::units::si::energy> >,
                           std::tuple<Policy,std::string> > LongTypes;
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

typedef typename MergeTypeLists<typename TypeList<Utility::EqualityComparisonPolicy>::type, typename TypeList<Utility::InequalityComparisonPolicy>::type, typename TypeList<Utility::GreaterThanComparisonPolicy>::type, typename TypeList<Utility::GreaterThanOrEqualToComparisonPolicy>::type, typename TypeList<Utility::LessThanComparisonPolicy>::type, typename TypeList<Utility::LessThanOrEqualToComparisonPolicy>::type, typename TypeList<Utility::CloseComparisonPolicy>::type, typename TypeList<Utility::RelativeErrorComparisonPolicy>::type>::type TestTypes;

typedef typename MergeTypeLists<typename TypeList<Utility::EqualityComparisonPolicy>::LongTypes, typename TypeList<Utility::InequalityComparisonPolicy>::LongTypes>::type EqualityTestTypes;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
template<typename T>
T zero( const T = T() )
{ return Utility::QuantityTraits<T>::zero(); }

std::string zero( const std::string& = std::string() )
{ return "0"; }

template<typename T>
T one( const T = T() )
{ return Utility::QuantityTraits<T>::one(); }

std::string one( const std::string& = std::string() )
{ return "1"; }

template<typename T>
typename std::enable_if<std::is_integral<T>::value || std::is_same<T,std::string>::value,T>::type
small( const T dummy = T() )
{ return zero( dummy ); }

float small( const float = 0.0f )
{ return 1e-6f; }

double small( const double = 0.0 )
{ return 1e-12; }

template<typename Unit>
double small( const boost::units::quantity<Unit,double> = Utility::QuantityTraits<boost::units::quantity<Unit,double> >::zero() )
{ return small( double() ); }

template<typename T>
T smallQuantity( const T dummy = T() )
{ return small( dummy ); }

template<typename Unit>
boost::units::quantity<Unit,double> smallQuantity( const boost::units::quantity<Unit,double> dummy = Utility::QuantityTraits<boost::units::quantity<Unit,double> >::zero() )
{ return Utility::QuantityTraits<boost::units::quantity<Unit,double> >::initializeQuantity( small( dummy ) ); }

template<typename T>
typename std::enable_if<std::is_integral<T>::value || std::is_same<T,std::string>::value,T>::type smallByTwo( const T dummy = T() )
{ return small( dummy ); }

float smallByTwo( const float dummy = 0.0f )
{ return 2*small( dummy ); }

double smallByTwo( const double dummy = 0.0 )
{ return 2*small( dummy ); }

template<typename Unit>
boost::units::quantity<Unit,double> smallByTwo( const boost::units::quantity<Unit,double> = Utility::QuantityTraits<boost::units::quantity<Unit,double> >::zero() )
{
  return Utility::QuantityTraits<boost::units::quantity<Unit,double> >::initializeQuantity( smallByTwo( double() ) );
}

template<typename T>
typename std::enable_if<std::is_integral<T>::value || std::is_same<T,std::string>::value,T>::type smallOverTwo( const T dummy = T() )
{ return small( dummy ); }

float smallOverTwo( const float dummy = 0.0f )
{ return small( dummy )/2; }

double smallOverTwo( const double dummy = 0.0 )
{ return small( dummy )/2; }

template<typename Unit>
boost::units::quantity<Unit,double> smallOverTwo( const boost::units::quantity<Unit,double> = Utility::QuantityTraits<boost::units::quantity<Unit,double> >::zero() )
{
  return Utility::QuantityTraits<boost::units::quantity<Unit,double> >::initializeQuantity( smallOverTwo( double() ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the comparison header can be created
BOOST_AUTO_TEST_CASE_TEMPLATE( createComparisonHeader, TypePair, TestTypes )
{
  typedef typename std::tuple_element<0,TypePair>::type Policy;
  typedef typename std::tuple_element<1,TypePair>::type T;
  
  std::string header =
    Utility::ComparisonTraits<T>::template createComparisonHeader<Policy>(
                                                    zero( T() ), "lhs", false,
                                                    zero( T() ), "rhs", false,
                                                    "" );

  std::string expected_header =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", false, zero( T() ),
                                     "" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T>::template createComparisonHeader<Policy>(
                                                    zero( T() ), "lhs", false,
                                                    zero( T() ), "rhs", false,
                                                    "", small( T() ) );

  expected_header =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", false, zero( T() ),
                                     "", small( T() ) ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T>::template createComparisonHeader<Policy>(
                                                    zero( T() ), "lhs", true,
                                                    zero( T() ), "rhs", false,
                                                    "" );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T>::template createComparisonHeader<Policy>(
                                                    zero( T() ), "lhs", true,
                                                    zero( T() ), "rhs", false,
                                                    "", small( T() ) );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "", small( T() ) ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T>::template createComparisonHeader<Policy>(
                                                    zero( T() ), "lhs", true,
                                                    zero( T() ), "rhs", false,
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "[0].first" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T>::template createComparisonHeader<Policy>(
                                                    zero( T() ), "lhs", true,
                                                    zero( T() ), "rhs", false,
                                                    "[0].first", small(T()) );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "[0].first", small(T()) )
    + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T>::template createComparisonHeader<Policy>(
                                                    zero( T() ), "lhs", false,
                                                    zero( T() ), "rhs", true,
                                                    "" );

  expected_header = Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T>::template createComparisonHeader<Policy>(
                                                    zero( T() ), "lhs", false,
                                                    zero( T() ), "rhs", true,
                                                    "", small( T() ) );

  expected_header = Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "", small( T() ) ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T>::template createComparisonHeader<Policy>(
                                                    zero( T() ), "lhs", false,
                                                    zero( T() ), "rhs", true,
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T>::template createComparisonHeader<Policy>(
                                                    zero( T() ), "lhs", false,
                                                    zero( T() ), "rhs", true,
                                                    "[0].first", small(T()) );

  expected_header = Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first", small(T()) )
    + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T>::template createComparisonHeader<Policy>(
                                                    zero( T() ), "lhs", true,
                                                    zero( T() ), "rhs", true,
                                                    "" );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T>::template createComparisonHeader<Policy>(
                                                    zero( T() ), "lhs", true,
                                                    zero( T() ), "rhs", true,
                                                    "", small(T()) );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "", small(T()) ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T>::template createComparisonHeader<Policy>(
                                                    zero( T() ), "lhs", true,
                                                    zero( T() ), "rhs", true,
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T>::template createComparisonHeader<Policy>(
                                                    zero( T() ), "lhs", true,
                                                    zero( T() ), "rhs", true,
                                                    "[0].first", small(T()) );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first", small(T()) )
    + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );
}

//---------------------------------------------------------------------------//
// Check that the comparison header can be created
BOOST_AUTO_TEST_CASE_TEMPLATE( createComparisonHeader_pointer,
                               TypePair,
                               EqualityTestTypes )
{
  typedef typename std::tuple_element<0,TypePair>::type Policy;
  typedef typename std::tuple_element<1,TypePair>::type T;
  
  std::string header =
    Utility::ComparisonTraits<T*>::template createComparisonHeader<Policy>(
                                                    (T*)NULL, "lhs", false,
                                                    (T*)NULL, "rhs", false,
                                                    "" );

  std::string expected_header =
    Policy::createComparisonDetails( "lhs", false, (T*)NULL,
                                     "rhs", false, (T*)NULL,
                                     "" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  T value = zero( T() );

  header =
    Utility::ComparisonTraits<T*>::template createComparisonHeader<Policy>(
                                                    &value, "lhs", true,
                                                    &value, "rhs", false,
                                                    "" );

  expected_header = Policy::createComparisonDetails( "lhs", true, &value,
                                                     "rhs", false, &value,
                                                     "" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T*>::template createComparisonHeader<Policy>(
                                                    &value, "lhs", true,
                                                    &value, "rhs", false,
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", true, &value,
                                                     "rhs", false, &value,
                                                     "[0].first" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T*>::template createComparisonHeader<Policy>(
                                                    &value, "lhs", false,
                                                    &value, "rhs", true,
                                                    "" );

  expected_header = Policy::createComparisonDetails( "lhs", false, &value,
                                                     "rhs", true, &value,
                                                     "" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T*>::template createComparisonHeader<Policy>(
                                                    &value, "lhs", false,
                                                    &value, "rhs", true,
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", false, &value,
                                                     "rhs", true, &value,
                                                     "[0].first" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T*>::template createComparisonHeader<Policy>(
                                                    &value, "lhs", true,
                                                    &value, "rhs", true,
                                                    "" );

  expected_header = Policy::createComparisonDetails( "lhs", true, &value,
                                                     "rhs", true, &value,
                                                     "" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::ComparisonTraits<T*>::template createComparisonHeader<Policy>(
                                                    &value, "lhs", true,
                                                    &value, "rhs", true,
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", true, &value,
                                                     "rhs", true, &value,
                                                     "[0].first" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );
}

//---------------------------------------------------------------------------//
// Check that the comparison header can be created (two lvalues)
BOOST_AUTO_TEST_CASE_TEMPLATE( createComparisonHeader_lvalues_helper,
                               TypePair,
                               TestTypes )
{
  typedef typename std::tuple_element<0,TypePair>::type Policy;
  typedef typename std::tuple_element<1,TypePair>::type T;
  
  T left_value = zero( T() );
  T right_value = zero( T() );

  std::string header = Utility::createComparisonHeader<Policy,0>(
                                                          left_value, "lhs",
                                                          right_value, "rhs" );

  std::string expected_header =
    Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                     "rhs", true, zero( T() ),
                                     "" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( left_value, "lhs",
                                                    right_value, "rhs",
                                                    small( T() ) );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "", small( T() ) ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( left_value, "lhs",
                                                    right_value, "rhs",
                                                    typename Utility::ComparisonTraits<T>::ExtraDataType(),
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( left_value, "lhs",
                                                    right_value, "rhs",
                                                    small( T() ),
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first", small(T()) )
    + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  // Check that const values have the same details created
  const T const_left_value = left_value;
  const T const_right_value = right_value;

  header = Utility::createComparisonHeader<Policy,0>( const_left_value, "lhs",
                                                    const_right_value, "rhs" );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( const_left_value, "lhs",
                                                    const_right_value, "rhs",
                                                    small( T() ) );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "", small( T() ) ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( const_left_value, "lhs",
                                                    const_right_value, "rhs",
                                                    typename Utility::ComparisonTraits<T>::ExtraDataType(),
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( const_left_value, "lhs",
                                                    const_right_value, "rhs",
                                                    small( T() ),
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first", small(T()) )
    + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );
}

//---------------------------------------------------------------------------//
// Check that the comparison header can be created (lvalue and rvalue)
BOOST_AUTO_TEST_CASE_TEMPLATE( createComparisonHeader_lvalue_rvalue_helper,
                               TypePair,
                               TestTypes )
{
  typedef typename std::tuple_element<0,TypePair>::type Policy;
  typedef typename std::tuple_element<1,TypePair>::type T;
  
  T left_value = zero( T() );
  T right_value = zero( T() );

  // LHS = lvalue reference, RHS = rvalue reference
  std::string header = Utility::createComparisonHeader<Policy,0>(
                                                          left_value, "lhs",
                                                          zero( T() ), "rhs" );

  std::string expected_header =
    Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                     "rhs", false, zero( T() ),
                                     "" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( left_value, "lhs",
                                                    zero( T() ), "rhs",
                                                    small( T() ) );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "", small( T() ) ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( left_value, "lhs",
                                                    zero( T() ), "rhs",
                                                    typename Utility::ComparisonTraits<T>::ExtraDataType(),
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "[0].first" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( left_value, "lhs",
                                                    zero( T() ), "rhs",
                                                    small( T() ),
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "[0].first", small(T()) )
    + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  // LHS = rvalue reference, RHS = lvalue reference
  header = Utility::createComparisonHeader<Policy,0>( zero( T() ), "lhs",
                                                    right_value, "rhs" );

  expected_header =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", true, zero( T() ),
                                     "" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( zero( T() ), "lhs",
                                                    right_value, "rhs",
                                                    small( T() ) );

  expected_header = Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "", small( T() ) ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( zero( T() ), "lhs",
                                                    right_value, "rhs",
                                                    typename Utility::ComparisonTraits<T>::ExtraDataType(),
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( zero( T() ), "lhs",
                                                    right_value, "rhs",
                                                    small( T() ),
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first", small(T()) )
    + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  const T const_left_value = left_value;
  const T const_right_value = right_value;

  // LHS = const lvalue reference, RHS = rvalue reference
  header = Utility::createComparisonHeader<Policy,0>( const_left_value, "lhs",
                                                    zero( T() ), "rhs" );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( const_left_value, "lhs",
                                                    zero( T() ), "rhs",
                                                    small( T() ) );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "", small( T() ) ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( const_left_value, "lhs",
                                                    zero( T() ), "rhs",
                                                    typename Utility::ComparisonTraits<T>::ExtraDataType(),
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "[0].first" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( const_left_value, "lhs",
                                                    zero( T() ), "rhs",
                                                    small( T() ),
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "[0].first", small(T()) )
    + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  // LHS = rvalue reference, RHS = const lvalue reference
  header = Utility::createComparisonHeader<Policy,0>( zero( T() ), "lhs",
                                                    const_right_value, "rhs" );

  expected_header =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", true, zero( T() ),
                                     "" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( zero( T() ), "lhs",
                                                    const_right_value, "rhs",
                                                    small( T() ) );

  expected_header = Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "", small( T() ) ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( zero( T() ), "lhs",
                                                    const_right_value, "rhs",
                                                    typename Utility::ComparisonTraits<T>::ExtraDataType(),
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( zero( T() ), "lhs",
                                                    const_right_value, "rhs",
                                                    small( T() ),
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first", small(T()) )
    + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );
}

//---------------------------------------------------------------------------//
// Check that the comparison header can be created (two rvalues)
BOOST_AUTO_TEST_CASE_TEMPLATE( createComparisonHeader_rvalues_helper,
                               TypePair,
                               TestTypes )
{
  typedef typename std::tuple_element<0,TypePair>::type Policy;
  typedef typename std::tuple_element<1,TypePair>::type T;

  std::string header = Utility::createComparisonHeader<Policy,0>(
                                                          zero( T() ), "lhs",
                                                          zero( T() ), "rhs" );

  std::string expected_header =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", false, zero( T() ),
                                     "" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( zero( T() ), "lhs",
                                                    zero( T() ), "rhs",
                                                    small( T() ) );

  expected_header = Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "", small( T() ) ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( zero( T() ), "lhs",
                                                    zero( T() ), "rhs",
                                                    typename Utility::ComparisonTraits<T>::ExtraDataType(),
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "[0].first" ) + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );

  header = Utility::createComparisonHeader<Policy,0>( zero( T() ), "lhs",
                                                    zero( T() ), "rhs",
                                                    small( T() ),
                                                    "[0].first" );

  expected_header = Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "[0].first", small(T()) )
    + ": ";

  BOOST_CHECK_EQUAL( header, expected_header );
}

//---------------------------------------------------------------------------//
// Check that the comparison header can be created (two string literals)
BOOST_AUTO_TEST_CASE( createComparisonHeader_string_literals_helper )
{
  // Two string literals (same size)
  std::string header =
    Utility::createComparisonHeader<Utility::EqualityComparisonPolicy,0>(
                                                    "test string", "\"lhs\"",
                                                    "test string", "\"rhs\"" );

  std::string expected_header =
    Utility::EqualityComparisonPolicy::createComparisonDetails(
                     std::string("\"lhs\""), false, std::string("test string"),
                     std::string("\"rhs\""), false, std::string("test string"),
                     "" ) + ": ";
  
  BOOST_CHECK_EQUAL( header, expected_header );

  // Two string literals (different size)
  header =
    Utility::createComparisonHeader<Utility::EqualityComparisonPolicy,0>(
                                            "test string", "\"lhs\"",
                                            "another test string", "\"rhs\"" );

  expected_header =
    Utility::EqualityComparisonPolicy::createComparisonDetails(
             std::string("\"lhs\""), false, std::string("test string"),
             std::string("\"rhs\""), false, std::string("another test string"),
             "" ) + ": ";
  
  BOOST_CHECK_EQUAL( header, expected_header );

  // One string literal and one string rvalue
  header =
    Utility::createComparisonHeader<Utility::EqualityComparisonPolicy,0>(
                                       "test string", "\"lhs\"",
                                       std::string("test string"), "rhs" );

  expected_header =
    Utility::EqualityComparisonPolicy::createComparisonDetails(
                     std::string("\"lhs\""), false, std::string("test string"),
                     std::string("rhs"), false, std::string("test string"),
                     "" ) + ": ";
  
  BOOST_CHECK_EQUAL( header, expected_header );

  header =
    Utility::createComparisonHeader<Utility::EqualityComparisonPolicy,0>(
                                             std::string("test string"), "lhs",
                                             "test string", "\"rhs\"" );

  expected_header =
    Utility::EqualityComparisonPolicy::createComparisonDetails(
                     std::string("lhs"), false, std::string("test string"),
                     std::string("\"rhs\""), false, std::string("test string"),
                     "" ) + ": ";
  
  BOOST_CHECK_EQUAL( header, expected_header );

  // One string literal and one string lvalue
  {
    std::string test_string( "test string" );

    header =
      Utility::createComparisonHeader<Utility::EqualityComparisonPolicy,0>(
                                                      "test string", "\"lhs\"",
                                                      test_string, "rhs" );

    expected_header =
      Utility::EqualityComparisonPolicy::createComparisonDetails(
                     std::string("\"lhs\""), false, std::string("test string"),
                     std::string("rhs"), true, test_string,
                     "" ) + ": ";
  
    BOOST_CHECK_EQUAL( header, expected_header );
    
    header =
      Utility::createComparisonHeader<Utility::EqualityComparisonPolicy,0>(
                                                    test_string, "lhs",
                                                    "test string", "\"rhs\"" );

    expected_header =
      Utility::EqualityComparisonPolicy::createComparisonDetails(
                     std::string("lhs"), true, test_string,
                     std::string("\"rhs\""), false, std::string("test string"),
                     "" ) + ": ";
  
    BOOST_CHECK_EQUAL( header, expected_header );
  }
}

//---------------------------------------------------------------------------//
// Check that two values of a type can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, TypePair, TestTypes )
{
  typedef typename std::tuple_element<0,TypePair>::type Policy;
  typedef typename std::tuple_element<1,TypePair>::type T;

  // No detail logging
  T left_value = zero( T() );
  T right_value = zero( T() );
  std::ostringstream oss;

  bool compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss );

  bool expected_compare_result = Policy::compare( left_value, right_value );
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  left_value = zero( T() );
  right_value = one( T() );

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss );

  expected_compare_result = Policy::compare( left_value, right_value );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  left_value = one( T() );
  right_value = zero( T() );

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss );

  expected_compare_result = Policy::compare( left_value, right_value );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  left_value = one( T() );
  right_value = one( T() );

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss );

  expected_compare_result = Policy::compare( left_value, right_value );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  left_value = zero(T());
  right_value = smallOverTwo(T());

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss, false,
                                                     small(T()) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  left_value = smallOverTwo(T());
  right_value = zero(T());

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss, false,
                                                     small(T()) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  left_value = zero(T());
  right_value = smallByTwo(T());

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss, false,
                                                     small(T()) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  left_value = smallByTwo(T());
  right_value = zero(T());

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss, false,
                                                     small(T()) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  left_value = one(T());
  right_value = one(T())+smallOverTwo(T());

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss, false,
                                                     small(T()) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  left_value = one(T())+smallOverTwo(T());
  right_value = one(T());

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss, false,
                                                     small(T()) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  left_value = one(T());
  right_value = one(T())+smallByTwo(T());

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss, false,
                                                     small(T()) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  left_value = one(T())+smallByTwo(T());
  right_value = one(T());

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss, false,
                                                     small(T()) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  // Detail logging
  left_value = zero( T() );
  right_value = zero( T() );
  
  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", true,
                                                     "", oss, true );

  expected_compare_result = Policy::compare( left_value, right_value );

  std::string expected_details =
    Policy::createComparisonDetails( "lhs", true, left_value,
                                     "rhs", true, right_value,
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  left_value = zero( T() );
  right_value = one( T() );

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", false,
                                                     "", oss, true );

  expected_compare_result = Policy::compare( left_value, right_value );

  expected_details = Policy::createComparisonDetails( "lhs", true, left_value,
                                                      "rhs", false, right_value,
                                                      "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  left_value = one( T() );
  right_value = zero( T() );

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", true,
                                                     "", oss, true );

  expected_compare_result = Policy::compare( left_value, right_value );

  expected_details = Policy::createComparisonDetails( "lhs", false, left_value,
                                                      "rhs", true, right_value,
                                                      "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  left_value = one( T() );
  right_value = one( T() );

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", false,
                                                     right_value, "rhs", false,
                                                     "", oss, true );

  expected_compare_result = Policy::compare( left_value, right_value );

  expected_details = Policy::createComparisonDetails( "lhs", false, left_value,
                                                      "rhs", false, right_value,
                                                      "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  left_value = zero(T());
  right_value = smallOverTwo(T());

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", true,
                                                     "", oss, true,
                                                     small(T()) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  expected_details = Policy::createComparisonDetails( "lhs", true, left_value,
                                                      "rhs", true, right_value,
                                                      "", small(T()) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  left_value = smallOverTwo(T());
  right_value = zero(T());

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", true,
                                                     "", oss, true,
                                                     small(T()) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  expected_details = Policy::createComparisonDetails( "lhs", true, left_value,
                                                      "rhs", true, right_value,
                                                      "", small(T()) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  left_value = zero(T());
  right_value = smallByTwo(T());

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", true,
                                                     "", oss, true,
                                                     small(T()) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  expected_details = Policy::createComparisonDetails( "lhs", true, left_value,
                                                      "rhs", true, right_value,
                                                      "", small(T()) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  left_value = smallByTwo(T());
  right_value = zero(T());

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", true,
                                                     "", oss, true,
                                                     small(T()) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  expected_details = Policy::createComparisonDetails( "lhs", true, left_value,
                                                      "rhs", true, right_value,
                                                      "", small(T()) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  left_value = one(T());
  right_value = one(T())+smallOverTwo(T());

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", true,
                                                     "", oss, true,
                                                     small(T()) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  expected_details = Policy::createComparisonDetails( "lhs", true, left_value,
                                                      "rhs", true, right_value,
                                                      "", small(T()) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  left_value = one(T())+smallOverTwo(T());
  right_value = one(T());

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", true,
                                                     "", oss, true,
                                                     small(T()) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  expected_details = Policy::createComparisonDetails( "lhs", true, left_value,
                                                      "rhs", true, right_value,
                                                      "", small(T()) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  left_value = one(T());
  right_value = one(T())+smallByTwo(T());

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", true,
                                                     "", oss, true,
                                                     small(T()) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  expected_details = Policy::createComparisonDetails( "lhs", true, left_value,
                                                      "rhs", true, right_value,
                                                      "", small(T()) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  left_value = one(T())+smallByTwo(T());
  right_value = one(T());

  compare_result = Utility::ComparisonTraits<T>::template compare<Policy,0,0>(
                                                     left_value, "lhs", true,
                                                     right_value, "rhs", true,
                                                     "", oss, true,
                                                     small(T()) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  expected_details = Policy::createComparisonDetails( "lhs", true, left_value,
                                                      "rhs", true, right_value,
                                                      "", small(T()) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
}

//---------------------------------------------------------------------------//
// Check that two values of a type can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare_pointer, TypePair, EqualityTestTypes )
{
  typedef typename std::tuple_element<0,TypePair>::type Policy;
  typedef typename std::tuple_element<1,TypePair>::type T;

  // No detail logging
  T left_value = zero( T() );
  T right_value = zero( T() );
  std::ostringstream oss;

  bool compare_result = Utility::ComparisonTraits<T*>::template compare<Policy,0,0>(
                                                     &left_value, "lhs", false,
                                                     &right_value, "rhs", false,
                                                     "", oss );

  bool expected_compare_result = Policy::compare( &left_value, &right_value );
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  left_value = zero( T() );
  right_value = one( T() );

  compare_result = Utility::ComparisonTraits<T*>::template compare<Policy,0,0>(
                                                     &left_value, "lhs", false,
                                                     &right_value, "rhs", false,
                                                     "", oss );

  expected_compare_result = Policy::compare( &left_value, &right_value );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  left_value = one( T() );
  right_value = zero( T() );

  compare_result = Utility::ComparisonTraits<T*>::template compare<Policy,0,0>(
                                                     &left_value, "lhs", false,
                                                     &right_value, "rhs", false,
                                                     "", oss );

  expected_compare_result = Policy::compare( &left_value, &right_value );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  left_value = one( T() );
  right_value = one( T() );

  compare_result = Utility::ComparisonTraits<T*>::template compare<Policy,0,0>(
                                                     &left_value, "lhs", false,
                                                     &right_value, "rhs", false,
                                                     "", oss );

  expected_compare_result = Policy::compare( &left_value, &right_value );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  // Detail logging
  left_value = zero( T() );
  right_value = zero( T() );
  
  compare_result = Utility::ComparisonTraits<T*>::template compare<Policy,0,0>(
                                                     &left_value, "lhs", true,
                                                     &right_value, "rhs", true,
                                                     "", oss, true );

  expected_compare_result = Policy::compare( &left_value, &right_value );

  std::string expected_details =
    Policy::createComparisonDetails( "lhs", true, &left_value,
                                     "rhs", true, &right_value,
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  left_value = zero( T() );
  right_value = one( T() );

  compare_result = Utility::ComparisonTraits<T*>::template compare<Policy,0,0>(
                                                     &left_value, "lhs", true,
                                                     &right_value, "rhs", false,
                                                     "", oss, true );

  expected_compare_result = Policy::compare( &left_value, &right_value );

  expected_details = Policy::createComparisonDetails( "lhs", true, &left_value,
                                                      "rhs", false, &right_value,
                                                      "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  left_value = one( T() );
  right_value = zero( T() );

  compare_result = Utility::ComparisonTraits<T*>::template compare<Policy,0,0>(
                                                     &left_value, "lhs", false,
                                                     &right_value, "rhs", true,
                                                     "", oss, true );

  expected_compare_result = Policy::compare( &left_value, &right_value );

  expected_details = Policy::createComparisonDetails( "lhs", false, &left_value,
                                                      "rhs", true, &right_value,
                                                      "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  left_value = one( T() );
  right_value = one( T() );

  compare_result = Utility::ComparisonTraits<T*>::template compare<Policy,0,0>(
                                                     &left_value, "lhs", false,
                                                     &left_value, "rhs", false,
                                                     "", oss, true );

  expected_compare_result = Policy::compare( &left_value, &left_value );

  expected_details = Policy::createComparisonDetails( "lhs", false, &left_value,
                                                      "rhs", false, &left_value,
                                                      "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
}

//---------------------------------------------------------------------------//
// Check that two lvalues of a type can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare_lvalues_helper, TypePair, TestTypes )
{
  typedef typename std::tuple_element<0,TypePair>::type Policy;
  typedef typename std::tuple_element<1,TypePair>::type T;

  // No details logging
  T left_value = zero( T() );
  T right_value = zero( T() );
  std::ostringstream oss;

  bool compare_result = Utility::compare<Policy,0,0>( left_value, "lhs",
                                                  right_value, "rhs",
                                                  oss );

  bool expected_compare_result = Policy::compare( left_value, right_value );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  compare_result = Utility::compare<Policy,0,0>( left_value, "lhs",
                                             right_value, "rhs",
                                             oss, small( T() ) );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  const T const_left_value = left_value;
  const T const_right_value = right_value;

  compare_result = Utility::compare<Policy,0,0>( const_left_value, "lhs",
                                             const_right_value, "rhs",
                                             oss, small( T() ) );

  expected_compare_result =
    Policy::compare( const_left_value, const_right_value, small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  compare_result = Utility::compare<Policy,0,0>( const_left_value, "lhs",
                                             const_right_value, "rhs",
                                             oss, small( T() ) );

  expected_compare_result =
    Policy::compare( const_left_value, const_right_value, small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  // Details logging
  const typename Utility::ComparisonTraits<T>::ExtraDataType extra_data =
    typename Utility::ComparisonTraits<T>::ExtraDataType();
  
  compare_result = Utility::compare<Policy,0,0>( left_value, "lhs",
                                             right_value, "rhs",
                                             oss, extra_data, true );

  expected_compare_result = Policy::compare( left_value, right_value );

  std::string expected_details =
    Policy::createComparisonDetails( "lhs", true, left_value,
                                     "rhs", true, right_value,
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( left_value, "lhs",
                                             right_value, "rhs",
                                             oss, extra_data, true,
                                             "[0].first" );

  expected_compare_result = Policy::compare( left_value, right_value );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, left_value,
                                     "rhs", true, right_value,
                                     "[0].first" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( left_value, "lhs",
                                             right_value, "rhs",
                                             oss, small( T() ), true );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, left_value,
                                     "rhs", true, right_value,
                                     "", small( T() ) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( left_value, "lhs",
                                             right_value, "rhs",
                                             oss, small( T() ), true,
                                             "[0].first" );

  expected_compare_result =
    Policy::compare( left_value, right_value, small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, left_value,
                                     "rhs", true, right_value,
                                     "[0].first", small( T() ) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( const_left_value, "lhs",
                                             const_right_value, "rhs",
                                             oss, small( T() ), true );

  expected_compare_result =
    Policy::compare( const_left_value, const_right_value, small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, const_left_value,
                                     "rhs", true, const_right_value,
                                     "", small(T()) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( const_left_value, "lhs",
                                             const_right_value, "rhs",
                                             oss, small( T() ), true,
                                             "[0].first" );

  expected_compare_result =
    Policy::compare( const_left_value, const_right_value, small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, const_left_value,
                                     "rhs", true, const_right_value,
                                     "[0].first", small(T()) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( const_left_value, "lhs",
                                             const_right_value, "rhs",
                                             oss, small( T() ), true );

  expected_compare_result =
    Policy::compare( const_left_value, const_right_value, small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, const_left_value,
                                     "rhs", true, const_right_value,
                                     "", small( T() ) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( const_left_value, "lhs",
                                             const_right_value, "rhs",
                                             oss, small( T() ), true,
                                             "[0].first" );

  expected_compare_result =
    Policy::compare( const_left_value, const_right_value, small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, const_left_value,
                                     "rhs", true, const_right_value,
                                     "[0].first", small( T() ) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
}

//---------------------------------------------------------------------------//
// Check that an lvalue and rvalue of a type can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare_lvalue_rvalue_helper,
                               TypePair,
                               TestTypes )
{
  typedef typename std::tuple_element<0,TypePair>::type Policy;
  typedef typename std::tuple_element<1,TypePair>::type T;

  // No details logging, LHS = lvalue reference, RHS = rvalue reference
  T left_value = zero( T() );
  T right_value = zero( T() );
  std::ostringstream oss;

  bool compare_result = Utility::compare<Policy,0,0>( left_value, "lhs",
                                                  zero( T() ), "rhs",
                                                  oss );

  bool expected_compare_result = Policy::compare( left_value, zero( T() ) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  compare_result = Utility::compare<Policy,0,0>( left_value, "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ) );

  expected_compare_result =
    Policy::compare( left_value, zero( T() ), small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  const T const_left_value = left_value;
  const T const_right_value = right_value;

  compare_result = Utility::compare<Policy,0,0>( const_left_value, "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ) );

  expected_compare_result =
    Policy::compare( const_left_value, zero( T() ), small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  compare_result = Utility::compare<Policy,0,0>( const_left_value, "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ) );

  expected_compare_result =
    Policy::compare( const_left_value, zero( T() ), small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  // No details logging, LHS = rvalue reference, RHS = lvalue reference
  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             right_value, "rhs",
                                             oss );

  expected_compare_result = Policy::compare( zero( T() ), right_value );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             right_value, "rhs",
                                             oss, small( T() ) );

  expected_compare_result =
    Policy::compare( zero( T() ), right_value, small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             const_right_value, "rhs",
                                             oss, small( T() ) );

  expected_compare_result =
    Policy::compare( zero( T() ), const_right_value, small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             const_right_value, "rhs",
                                             oss, small( T() ) );

  expected_compare_result =
    Policy::compare( zero( T() ), const_right_value, small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  // Details logging, LHS = lvalue reference, RHS = rvalue reference
  const typename Utility::ComparisonTraits<T>::ExtraDataType extra_data =
    typename Utility::ComparisonTraits<T>::ExtraDataType();
  
  compare_result = Utility::compare<Policy,0,0>( left_value, "lhs",
                                             zero( T() ), "rhs",
                                             oss, extra_data, true );

  expected_compare_result = Policy::compare( left_value, zero( T() ) );

  std::string expected_details =
    Policy::createComparisonDetails( "lhs", true, left_value,
                                     "rhs", false, zero( T() ),
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( left_value, "lhs",
                                             zero( T() ), "rhs",
                                             oss, extra_data, true,
                                             "[0].first" );

  expected_compare_result = Policy::compare( left_value, zero( T() ) );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, left_value,
                                     "rhs", false, zero( T() ),
                                     "[0].first" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( left_value, "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ), true );

  expected_compare_result =
    Policy::compare( left_value, zero( T() ), small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, left_value,
                                     "rhs", false, zero( T() ),
                                     "", small( T() ) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( left_value, "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ), true,
                                             "[0].first" );

  expected_compare_result =
    Policy::compare( left_value, zero( T() ), small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, left_value,
                                     "rhs", false, zero( T() ),
                                     "[0].first", small( T() ) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( const_left_value, "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ), true );

  expected_compare_result =
    Policy::compare( const_left_value, zero( T() ), small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, const_left_value,
                                     "rhs", false, zero( T() ),
                                     "", small(T()) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( const_left_value, "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ), true,
                                             "[0].first" );

  expected_compare_result =
    Policy::compare( const_left_value, zero( T() ), small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, const_left_value,
                                     "rhs", false, zero( T() ),
                                     "[0].first", small(T()) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( const_left_value, "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ), true );

  expected_compare_result =
    Policy::compare( const_left_value, zero( T() ), small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, const_left_value,
                                     "rhs", false, zero( T() ),
                                     "", small( T() ) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( const_left_value, "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ), true,
                                             "[0].first" );

  expected_compare_result =
    Policy::compare( const_left_value, zero( T() ), small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", true, const_left_value,
                                     "rhs", false, zero( T() ),
                                     "[0].first", small( T() ) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  // Details logging, LHS = rvalue reference, RHS = lvalue reference
  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             right_value, "rhs",
                                             oss, extra_data, true );

  expected_compare_result = Policy::compare( zero( T() ), right_value );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", true, right_value,
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             right_value, "rhs",
                                             oss, extra_data, true,
                                             "[0].first" );

  expected_compare_result = Policy::compare( zero( T() ), right_value );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", true, right_value,
                                     "[0].first" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             right_value, "rhs",
                                             oss, small( T() ), true );

  expected_compare_result =
    Policy::compare( zero( T() ), right_value, small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", true, right_value,
                                     "", small( T() ) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             right_value, "rhs",
                                             oss, small( T() ), true,
                                             "[0].first" );

  expected_compare_result =
    Policy::compare( zero( T() ), right_value, small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", true, right_value,
                                     "[0].first", small( T() ) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             const_right_value, "rhs",
                                             oss, small( T() ), true );

  expected_compare_result =
    Policy::compare( zero( T() ), const_right_value, small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", true, const_right_value,
                                     "", small(T()) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             const_right_value, "rhs",
                                             oss, small( T() ), true,
                                             "[0].first" );

  expected_compare_result =
    Policy::compare( zero( T() ), const_right_value, small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", true, const_right_value,
                                     "[0].first", small(T()) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             const_right_value, "rhs",
                                             oss, small( T() ), true );

  expected_compare_result =
    Policy::compare( zero( T() ), const_right_value, small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", true, const_right_value,
                                     "", small( T() ) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             const_right_value, "rhs",
                                             oss, small( T() ), true,
                                             "[0].first" );

  expected_compare_result =
    Policy::compare( zero( T() ), const_right_value, small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", true, const_right_value,
                                     "[0].first", small( T() ) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
}

//---------------------------------------------------------------------------//
// Check that two rvalues of a type can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare_rvalues_helper, TypePair, TestTypes )
{
  typedef typename std::tuple_element<0,TypePair>::type Policy;
  typedef typename std::tuple_element<1,TypePair>::type T;

  //// No details logging
  std::ostringstream oss;

  bool compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                                  zero( T() ), "rhs",
                                                  oss );

  bool expected_compare_result = Policy::compare( zero( T() ), zero( T() ) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ) );

  expected_compare_result =
    Policy::compare( zero( T() ), zero( T() ), small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ) );

  expected_compare_result =
    Policy::compare( zero( T() ), zero( T() ), small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ) );

  expected_compare_result =
    Policy::compare( zero( T() ), zero( T() ), small(T()) );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  // Details logging
  const typename Utility::ComparisonTraits<T>::ExtraDataType extra_data =
    typename Utility::ComparisonTraits<T>::ExtraDataType();
  
  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             zero( T() ), "rhs",
                                             oss, extra_data, true );

  expected_compare_result = Policy::compare( zero( T() ), zero( T() ) );

  std::string expected_details =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", false, zero( T() ),
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             zero( T() ), "rhs",
                                             oss, extra_data, true,
                                             "[0].first" );

  expected_compare_result = Policy::compare( zero( T() ), zero( T() ) );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", false, zero( T() ),
                                     "[0].first" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ), true );

  expected_compare_result =
    Policy::compare( zero( T() ), zero( T() ), small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", false, zero( T() ),
                                     "", small( T() ) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ), true,
                                             "[0].first" );

  expected_compare_result =
    Policy::compare( zero( T() ), zero( T() ), small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", false, zero( T() ),
                                     "[0].first", small( T() ) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ), true );

  expected_compare_result =
    Policy::compare( zero( T() ), zero( T() ), small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", false, zero( T() ),
                                     "", small(T()) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ), true,
                                             "[0].first" );

  expected_compare_result =
    Policy::compare( zero( T() ), zero( T() ), small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", false, zero( T() ),
                                     "[0].first", small(T()) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ), true );

  expected_compare_result =
    Policy::compare( zero( T() ), zero( T() ), small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", false, zero( T() ),
                                     "", small( T() ) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( zero( T() ), "lhs",
                                             zero( T() ), "rhs",
                                             oss, small( T() ), true,
                                             "[0].first" );

  expected_compare_result =
    Policy::compare( zero( T() ), zero( T() ), small(T()) );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, zero( T() ),
                                     "rhs", false, zero( T() ),
                                     "[0].first", small( T() ) ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );
}

typedef boost::mpl::list<Utility::EqualityComparisonPolicy,Utility::InequalityComparisonPolicy> LocalPolicyTypes;

//---------------------------------------------------------------------------//
// Check that two rvalues of a type can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare_string_literals_helper,
                               Policy,
                               LocalPolicyTypes )
{
  // No details logging
  std::ostringstream oss;

  bool compare_result = Utility::compare<Policy,0,0>( "test string", "\"lhs\"",
                                                      "test string", "\"rhs\"",
                                                      oss );

  bool expected_compare_result = Policy::compare( std::string("test string"),
                                                  std::string("test string") );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  compare_result = Utility::compare<Policy,0,0>( "test string", "\"lhs\"",
                                                 std::string("test string"), "rhs",
                                                 oss );

  expected_compare_result = Policy::compare( std::string("test string"),
                                             std::string("test string") );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  compare_result = Utility::compare<Policy,0,0>( std::string("test string"), "lhs",
                                                 "test string", "\"rhs\"",
                                                 oss );

  expected_compare_result = Policy::compare( std::string("test string"),
                                             std::string("test string") );

  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );

  {
    std::string test_string( "test string" );

    compare_result = Utility::compare<Policy,0,0>( "test string", "\"lhs\"",
                                                   test_string, "rhs",
                                                   oss );

    expected_compare_result = Policy::compare( std::string("test string"),
                                               test_string );

    BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
    
    compare_result = Utility::compare<Policy,0,0>( test_string, "lhs",
                                                   "test string", "\"rhs\"",
                                                   oss );
    
    expected_compare_result = Policy::compare( test_string,
                                               std::string("test string") );
    
    BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  }
  

  // Details logging
  std::string extra_data;
  
  compare_result = Utility::compare<Policy,0,0>( "test string", "\"lhs\"",
                                                 "test string", "\"rhs\"",
                                                 oss, extra_data, true );

  expected_compare_result = Policy::compare( std::string("test string"),
                                             std::string("test string") );

  std::string expected_details =
    Policy::createComparisonDetails( "\"lhs\"", false, std::string("test string"),
                                     "\"rhs\"", false, std::string("test string"),
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( "test string", "\"lhs\"",
                                                 std::string("test string"), "rhs",
                                                 oss, extra_data, true );

  expected_compare_result = Policy::compare( std::string("test string"),
                                             std::string("test string") );

  expected_details =
    Policy::createComparisonDetails( "\"lhs\"", false, std::string("test string"),
                                     "rhs", false, std::string("test string"),
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  compare_result = Utility::compare<Policy,0,0>( std::string("test string"), "lhs",
                                                 "test string", "\"rhs\"",
                                                 oss, extra_data, true );

  expected_compare_result = Policy::compare( std::string("test string"),
                                             std::string("test string") );

  expected_details =
    Policy::createComparisonDetails( "lhs", false, std::string("test string"),
                                     "\"rhs\"", false, std::string("test string"),
                                     "" ) + ": " +
    (expected_compare_result ? "passed\n" : "failed!\n");
  
  BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
  BOOST_CHECK_EQUAL( oss.str(), expected_details );

  oss.str( "" );
  oss.clear();

  {
    std::string test_string( "test string" );

    compare_result = Utility::compare<Policy,0,0>( "test string", "\"lhs\"",
                                                   test_string, "rhs",
                                                   oss, extra_data, true );

    expected_compare_result = Policy::compare( std::string("test string"),
                                               test_string );
    
    expected_details =
      Policy::createComparisonDetails( "\"lhs\"", false, std::string("test string"),
                                       "rhs", true, test_string,
                                       "" ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n");
  
    BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );

    oss.str( "" );
    oss.clear();

    compare_result = Utility::compare<Policy,0,0>( test_string, "lhs",
                                                   "test string", "\"rhs\"",
                                                   oss, extra_data, true );

    expected_compare_result = Policy::compare( test_string,
                                               std::string("test string") );

    expected_details =
      Policy::createComparisonDetails( "lhs", true, test_string,
                                       "\"rhs\"", false, std::string("test string"),
                                       "" ) + ": " +
      (expected_compare_result ? "passed\n" : "failed!\n");
  
    BOOST_CHECK_EQUAL( compare_result, expected_compare_result );
    BOOST_CHECK_EQUAL( oss.str(), expected_details );
  }
}

//---------------------------------------------------------------------------//
// end tstComparisonTraits.cpp
//---------------------------------------------------------------------------//
