//---------------------------------------------------------------------------//
//!
//! \file   tstComparisonPolicy.cpp
//! \author Alex Robinson
//! \brief  Comparison policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/energy.hpp>
#include <boost/units/systems/si/energy.hpp>

// FRENSIE Includes
#include "Utility_ComparisonPolicy.hpp"
#include "Utility_QuantityTraits.hpp"

//---------------------------------------------------------------------------//
// Template Test Types
//---------------------------------------------------------------------------//
typedef boost::mpl::list<bool, char, signed char, unsigned char, short, unsigned short, int, long, unsigned, unsigned long, long long, unsigned long long, float, double, boost::units::quantity<boost::units::si::energy>, std::string> TestTypes;

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
// EqualityComparisonPolicy Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( EqualityComparisonPolicy )

//---------------------------------------------------------------------------//
// Check that the operator name can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( getOperatorName, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::EqualityComparisonPolicy::getOperatorName<T>(), "==" );
}

//---------------------------------------------------------------------------//
// Check that the comparison details can be created
BOOST_AUTO_TEST_CASE_TEMPLATE( createComparisonDetails, T, TestTypes )
{
  std::string comparison_details =
    Utility::EqualityComparisonPolicy::createComparisonDetails(
                                               "lhs", false, zero( T() ),
                                               "rhs", false, zero( T() ),
                                               "" );

  BOOST_CHECK_EQUAL( comparison_details,
                     Utility::toString(zero( T() )) + " " +
                     Utility::EqualityComparisonPolicy::getOperatorName<T>() +
                     " " + Utility::toString(zero( T() )) );

  comparison_details =
    Utility::EqualityComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::EqualityComparisonPolicy::getOperatorName<T>() +
                      " " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::EqualityComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs[0].first = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::EqualityComparisonPolicy::getOperatorName<T>() +
                      " " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::EqualityComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      Utility::toString(zero( T() )) + " " +
                      Utility::EqualityComparisonPolicy::getOperatorName<T>() +
                      " rhs = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::EqualityComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      Utility::toString(zero( T() )) + " " +
                      Utility::EqualityComparisonPolicy::getOperatorName<T>() +
                      " rhs[0].first = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::EqualityComparisonPolicy::createComparisonDetails(
                                                      "lhs", true, zero( T() ),
                                                      "rhs", true, zero( T() ),
                                                      "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::EqualityComparisonPolicy::getOperatorName<T>() +
                      " rhs = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::EqualityComparisonPolicy::createComparisonDetails(
                                                      "lhs", true, zero( T() ),
                                                      "rhs", true, zero( T() ),
                                                      "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs[0].first = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::EqualityComparisonPolicy::getOperatorName<T>() +
                      " rhs[0].first = " + Utility::toString(zero( T() )) );
}

//---------------------------------------------------------------------------//
// Check that two values can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, T, TestTypes )
{
  BOOST_CHECK( (Utility::EqualityComparisonPolicy::compare( zero(T()), zero(T()) )) );
  BOOST_CHECK( !(Utility::EqualityComparisonPolicy::compare( zero(T()), one(T()) )) );
  BOOST_CHECK( !(Utility::EqualityComparisonPolicy::compare( one(T()), zero(T()) )) );
  BOOST_CHECK( (Utility::EqualityComparisonPolicy::compare( one(T()), one(T()) )) );

  Utility::EqualityComparisonPolicy policy;

  BOOST_CHECK( (policy( zero(T()), zero(T()) )) );
  BOOST_CHECK( !(policy( zero(T()), one(T()) )) );
  BOOST_CHECK( !(policy( one(T()), zero(T()) )) );
  BOOST_CHECK( (policy( one(T()), one(T()) )) );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// InequalityComparisonPolicy Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( InequalityComparisonPolicy )

//---------------------------------------------------------------------------//
// Check that the operator name can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( getOperatorName, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::InequalityComparisonPolicy::getOperatorName<T>(), "!=" );
}

//---------------------------------------------------------------------------//
// Check that the comparison details can be created
BOOST_AUTO_TEST_CASE_TEMPLATE( createComparisonDetails, T, TestTypes )
{
  std::string comparison_details =
    Utility::InequalityComparisonPolicy::createComparisonDetails(
                                               "lhs", false, zero( T() ),
                                               "rhs", false, zero( T() ),
                                               "" );

  BOOST_CHECK_EQUAL( comparison_details,
                     Utility::toString(zero( T() )) + " " +
                     Utility::InequalityComparisonPolicy::getOperatorName<T>() +
                     " " + Utility::toString(zero( T() )) );

  comparison_details =
    Utility::InequalityComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::InequalityComparisonPolicy::getOperatorName<T>() +
                      " " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::InequalityComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs[0].first = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::InequalityComparisonPolicy::getOperatorName<T>() +
                      " " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::InequalityComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      Utility::toString(zero( T() )) + " " +
                      Utility::InequalityComparisonPolicy::getOperatorName<T>() +
                      " rhs = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::InequalityComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      Utility::toString(zero( T() )) + " " +
                      Utility::InequalityComparisonPolicy::getOperatorName<T>() +
                      " rhs[0].first = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::InequalityComparisonPolicy::createComparisonDetails(
                                                      "lhs", true, zero( T() ),
                                                      "rhs", true, zero( T() ),
                                                      "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::InequalityComparisonPolicy::getOperatorName<T>() +
                      " rhs = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::InequalityComparisonPolicy::createComparisonDetails(
                                                      "lhs", true, zero( T() ),
                                                      "rhs", true, zero( T() ),
                                                      "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs[0].first = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::InequalityComparisonPolicy::getOperatorName<T>() +
                      " rhs[0].first = " + Utility::toString(zero( T() )) );
}

//---------------------------------------------------------------------------//
// Check that two values can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, T, TestTypes )
{
  BOOST_CHECK( !(Utility::InequalityComparisonPolicy::compare( zero(T()), zero(T()) )) );
  BOOST_CHECK( (Utility::InequalityComparisonPolicy::compare( zero(T()), one(T()) )) );
  BOOST_CHECK( (Utility::InequalityComparisonPolicy::compare( one(T()), zero(T()) )) );
  BOOST_CHECK( !(Utility::InequalityComparisonPolicy::compare( one(T()), one(T()) )) );

  Utility::InequalityComparisonPolicy policy;

  BOOST_CHECK( !(policy( zero(T()), zero(T()) )) );
  BOOST_CHECK( (policy( zero(T()), one(T()) )) );
  BOOST_CHECK( (policy( one(T()), zero(T()) )) );
  BOOST_CHECK( !(policy( one(T()), one(T()) )) );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// GreaterThanComparisonPolicy Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( GreaterThanComparisonPolicy )

//---------------------------------------------------------------------------//
// Check that the operator name can be returned
  BOOST_AUTO_TEST_CASE_TEMPLATE( getOperatorName, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::GreaterThanComparisonPolicy::getOperatorName<T>(), ">" );
}

//---------------------------------------------------------------------------//
// Check that the comparison details can be created
BOOST_AUTO_TEST_CASE_TEMPLATE( createComparisonDetails, T, TestTypes )
{
  std::string comparison_details =
    Utility::GreaterThanComparisonPolicy::createComparisonDetails(
                                               "lhs", false, zero( T() ),
                                               "rhs", false, zero( T() ),
                                               "" );

  BOOST_CHECK_EQUAL( comparison_details,
                     Utility::toString(zero( T() )) + " " +
                     Utility::GreaterThanComparisonPolicy::getOperatorName<T>() +
                     " " + Utility::toString(zero( T() )) );

  comparison_details =
    Utility::GreaterThanComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::GreaterThanComparisonPolicy::getOperatorName<T>() +
                      " " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::GreaterThanComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs[0].first = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::GreaterThanComparisonPolicy::getOperatorName<T>() +
                      " " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::GreaterThanComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      Utility::toString(zero( T() )) + " " +
                      Utility::GreaterThanComparisonPolicy::getOperatorName<T>() +
                      " rhs = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::GreaterThanComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      Utility::toString(zero( T() )) + " " +
                      Utility::GreaterThanComparisonPolicy::getOperatorName<T>() +
                      " rhs[0].first = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::GreaterThanComparisonPolicy::createComparisonDetails(
                                                      "lhs", true, zero( T() ),
                                                      "rhs", true, zero( T() ),
                                                      "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::GreaterThanComparisonPolicy::getOperatorName<T>() +
                      " rhs = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::GreaterThanComparisonPolicy::createComparisonDetails(
                                                      "lhs", true, zero( T() ),
                                                      "rhs", true, zero( T() ),
                                                      "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs[0].first = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::GreaterThanComparisonPolicy::getOperatorName<T>() +
                      " rhs[0].first = " + Utility::toString(zero( T() )) );
}

//---------------------------------------------------------------------------//
// Check that two values can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, T, TestTypes )
{
  BOOST_CHECK( !(Utility::GreaterThanComparisonPolicy::compare( zero(T()), zero(T()) )) );
  BOOST_CHECK( !(Utility::GreaterThanComparisonPolicy::compare( zero(T()), one(T()) )) );
  BOOST_CHECK( (Utility::GreaterThanComparisonPolicy::compare( one(T()), zero(T()) )) );
  BOOST_CHECK( !(Utility::GreaterThanComparisonPolicy::compare( one(T()), one(T()) )) );

  Utility::GreaterThanComparisonPolicy policy;

  BOOST_CHECK( !(policy( zero(T()), zero(T()) )) );
  BOOST_CHECK( !(policy( zero(T()), one(T()) )) );
  BOOST_CHECK( (policy( one(T()), zero(T()) )) );
  BOOST_CHECK( !(policy( one(T()), one(T()) )) );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// GreaterThanOrEqualToComparisonPolicy Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( GreaterThanOrEqualToComparisonPolicy )

//---------------------------------------------------------------------------//
// Check that the operator name can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( getOperatorName, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::GreaterThanOrEqualToComparisonPolicy::getOperatorName<T>(), ">=" );
}

//---------------------------------------------------------------------------//
// Check that the comparison details can be created
BOOST_AUTO_TEST_CASE_TEMPLATE( createComparisonDetails, T, TestTypes )
{
  std::string comparison_details =
    Utility::GreaterThanOrEqualToComparisonPolicy::createComparisonDetails(
                                               "lhs", false, zero( T() ),
                                               "rhs", false, zero( T() ),
                                               "" );

  BOOST_CHECK_EQUAL( comparison_details,
                     Utility::toString(zero( T() )) + " " +
                     Utility::GreaterThanOrEqualToComparisonPolicy::getOperatorName<T>() +
                     " " + Utility::toString(zero( T() )) );

  comparison_details =
    Utility::GreaterThanOrEqualToComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::GreaterThanOrEqualToComparisonPolicy::getOperatorName<T>() +
                      " " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::GreaterThanOrEqualToComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs[0].first = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::GreaterThanOrEqualToComparisonPolicy::getOperatorName<T>() +
                      " " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::GreaterThanOrEqualToComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      Utility::toString(zero( T() )) + " " +
                      Utility::GreaterThanOrEqualToComparisonPolicy::getOperatorName<T>() +
                      " rhs = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::GreaterThanOrEqualToComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      Utility::toString(zero( T() )) + " " +
                      Utility::GreaterThanOrEqualToComparisonPolicy::getOperatorName<T>() +
                      " rhs[0].first = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::GreaterThanOrEqualToComparisonPolicy::createComparisonDetails(
                                                      "lhs", true, zero( T() ),
                                                      "rhs", true, zero( T() ),
                                                      "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::GreaterThanOrEqualToComparisonPolicy::getOperatorName<T>() +
                      " rhs = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::GreaterThanOrEqualToComparisonPolicy::createComparisonDetails(
                                                      "lhs", true, zero( T() ),
                                                      "rhs", true, zero( T() ),
                                                      "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs[0].first = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::GreaterThanOrEqualToComparisonPolicy::getOperatorName<T>() +
                      " rhs[0].first = " + Utility::toString(zero( T() )) );
}

//---------------------------------------------------------------------------//
// Check that two values can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, T, TestTypes )
{
  BOOST_CHECK( (Utility::GreaterThanOrEqualToComparisonPolicy::compare( zero(T()), zero(T()) )) );
  BOOST_CHECK( !(Utility::GreaterThanOrEqualToComparisonPolicy::compare( zero(T()), one(T()) )) );
  BOOST_CHECK( (Utility::GreaterThanOrEqualToComparisonPolicy::compare( one(T()), zero(T()) )) );
  BOOST_CHECK( (Utility::GreaterThanOrEqualToComparisonPolicy::compare( one(T()), one(T()) )) );

  Utility::GreaterThanOrEqualToComparisonPolicy policy;

  BOOST_CHECK( (policy( zero(T()), zero(T()) )) );
  BOOST_CHECK( !(policy( zero(T()), one(T()) )) );
  BOOST_CHECK( (policy( one(T()), zero(T()) )) );
  BOOST_CHECK( (policy( one(T()), one(T()) )) );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// LessThanComparisonPolicy Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( LessThanComparisonPolicy )

//---------------------------------------------------------------------------//
// Check that the operator name can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( getOperatorName, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::LessThanComparisonPolicy::getOperatorName<T>(), "<" );
}

//---------------------------------------------------------------------------//
// Check that the comparison details can be created
BOOST_AUTO_TEST_CASE_TEMPLATE( createComparisonDetails, T, TestTypes )
{
  std::string comparison_details =
    Utility::LessThanComparisonPolicy::createComparisonDetails(
                                               "lhs", false, zero( T() ),
                                               "rhs", false, zero( T() ),
                                               "" );

  BOOST_CHECK_EQUAL( comparison_details,
                     Utility::toString(zero( T() )) + " " +
                     Utility::LessThanComparisonPolicy::getOperatorName<T>() +
                     " " + Utility::toString(zero( T() )) );

  comparison_details =
    Utility::LessThanComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::LessThanComparisonPolicy::getOperatorName<T>() +
                      " " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::LessThanComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs[0].first = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::LessThanComparisonPolicy::getOperatorName<T>() +
                      " " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::LessThanComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      Utility::toString(zero( T() )) + " " +
                      Utility::LessThanComparisonPolicy::getOperatorName<T>() +
                      " rhs = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::LessThanComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      Utility::toString(zero( T() )) + " " +
                      Utility::LessThanComparisonPolicy::getOperatorName<T>() +
                      " rhs[0].first = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::LessThanComparisonPolicy::createComparisonDetails(
                                                      "lhs", true, zero( T() ),
                                                      "rhs", true, zero( T() ),
                                                      "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::LessThanComparisonPolicy::getOperatorName<T>() +
                      " rhs = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::LessThanComparisonPolicy::createComparisonDetails(
                                                      "lhs", true, zero( T() ),
                                                      "rhs", true, zero( T() ),
                                                      "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs[0].first = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::LessThanComparisonPolicy::getOperatorName<T>() +
                      " rhs[0].first = " + Utility::toString(zero( T() )) );
}

//---------------------------------------------------------------------------//
// Check that two values can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, T, TestTypes )
{
  BOOST_CHECK( !(Utility::LessThanComparisonPolicy::compare( zero(T()), zero(T()) )) );
  BOOST_CHECK( (Utility::LessThanComparisonPolicy::compare( zero(T()), one(T()) )) );
  BOOST_CHECK( !(Utility::LessThanComparisonPolicy::compare( one(T()), zero(T()) )) );
  BOOST_CHECK( !(Utility::LessThanComparisonPolicy::compare( one(T()), one(T()) )) );

  Utility::LessThanComparisonPolicy policy;

  BOOST_CHECK( !(policy( zero(T()), zero(T()) )) );
  BOOST_CHECK( (policy( zero(T()), one(T()) )) );
  BOOST_CHECK( !(policy( one(T()), zero(T()) )) );
  BOOST_CHECK( !(policy( one(T()), one(T()) )) );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// LessThanOrEqualToComparisonPolicy Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( LessThanOrEqualToComparisonPolicy )

//---------------------------------------------------------------------------//
// Check that the operator name can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( getOperatorName, T, TestTypes )
{
  BOOST_CHECK_EQUAL( Utility::LessThanOrEqualToComparisonPolicy::getOperatorName<T>(), "<=" );
}

//---------------------------------------------------------------------------//
// Check that the comparison details can be created
BOOST_AUTO_TEST_CASE_TEMPLATE( createComparisonDetails, T, TestTypes )
{
  std::string comparison_details =
    Utility::LessThanOrEqualToComparisonPolicy::createComparisonDetails(
                                               "lhs", false, zero( T() ),
                                               "rhs", false, zero( T() ),
                                               "" );

  BOOST_CHECK_EQUAL( comparison_details,
                     Utility::toString(zero( T() )) + " " +
                     Utility::LessThanOrEqualToComparisonPolicy::getOperatorName<T>() +
                     " " + Utility::toString(zero( T() )) );

  comparison_details =
    Utility::LessThanOrEqualToComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::LessThanOrEqualToComparisonPolicy::getOperatorName<T>() +
                      " " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::LessThanOrEqualToComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs[0].first = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::LessThanOrEqualToComparisonPolicy::getOperatorName<T>() +
                      " " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::LessThanOrEqualToComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      Utility::toString(zero( T() )) + " " +
                      Utility::LessThanOrEqualToComparisonPolicy::getOperatorName<T>() +
                      " rhs = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::LessThanOrEqualToComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      Utility::toString(zero( T() )) + " " +
                      Utility::LessThanOrEqualToComparisonPolicy::getOperatorName<T>() +
                      " rhs[0].first = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::LessThanOrEqualToComparisonPolicy::createComparisonDetails(
                                                      "lhs", true, zero( T() ),
                                                      "rhs", true, zero( T() ),
                                                      "" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::LessThanOrEqualToComparisonPolicy::getOperatorName<T>() +
                      " rhs = " + Utility::toString(zero( T() )) );

   comparison_details =
     Utility::LessThanOrEqualToComparisonPolicy::createComparisonDetails(
                                                      "lhs", true, zero( T() ),
                                                      "rhs", true, zero( T() ),
                                                      "[0].first" );

   BOOST_CHECK_EQUAL( comparison_details,
                      std::string( "lhs[0].first = " ) +
                      Utility::toString(zero( T() )) + " " +
                      Utility::LessThanOrEqualToComparisonPolicy::getOperatorName<T>() +
                      " rhs[0].first = " + Utility::toString(zero( T() )) );
}

//---------------------------------------------------------------------------//
// Check that two values can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, T, TestTypes )
{
  BOOST_CHECK( (Utility::LessThanOrEqualToComparisonPolicy::compare( zero(T()), zero(T()) )) );
  BOOST_CHECK( (Utility::LessThanOrEqualToComparisonPolicy::compare( zero(T()), one(T()) )) );
  BOOST_CHECK( !(Utility::LessThanOrEqualToComparisonPolicy::compare( one(T()), zero(T()) )) );
  BOOST_CHECK( (Utility::LessThanOrEqualToComparisonPolicy::compare( one(T()), one(T()) )) );

  Utility::LessThanOrEqualToComparisonPolicy policy;

  BOOST_CHECK( (policy( zero(T()), zero(T()) )) );
  BOOST_CHECK( (policy( zero(T()), one(T()) )) );
  BOOST_CHECK( !(policy( one(T()), zero(T()) )) );
  BOOST_CHECK( (policy( one(T()), one(T()) )) );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// CloseComparisonPolicy Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( CloseComparisonPolicy )

//---------------------------------------------------------------------------//
// Check that the operator name can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( getOperatorName, T, TestTypes )
{
  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( Utility::CloseComparisonPolicy::getOperatorName<T>(), "~" );
  }
  else
  {
    BOOST_CHECK_EQUAL( Utility::CloseComparisonPolicy::getOperatorName<T>(), "==" );
  }
}

//---------------------------------------------------------------------------//
// Check that the comparison details can be created
BOOST_AUTO_TEST_CASE_TEMPLATE( createComparisonDetails, T, TestTypes )
{
  std::string comparison_details =
    Utility::CloseComparisonPolicy::createComparisonDetails(
                                               "lhs", false, zero( T() ),
                                               "rhs", false, zero( T() ),
                                               "" );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("distance(") +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( T() )) + " <= " +
                       Utility::toString(zero( T() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       Utility::toString(zero( T() )) + " " +
                       Utility::CloseComparisonPolicy::getOperatorName<T>() +
                       " " + Utility::toString(zero( T() )) );
  }

  comparison_details = Utility::CloseComparisonPolicy::createComparisonDetails(
                                               "lhs", false, zero( T() ),
                                               "rhs", false, zero( T() ),
                                               "", small( T() ) );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("distance(") +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( T() )) + " <= " +
                       Utility::toString(smallQuantity( T() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       Utility::toString(zero( T() )) + " " +
                       Utility::CloseComparisonPolicy::getOperatorName<T>() +
                       " " + Utility::toString(zero( T() )) );
  }

  comparison_details =
    Utility::CloseComparisonPolicy::createComparisonDetails(
                                                    "lhs", true, zero( T() ),
                                                    "rhs", false, zero( T() ),
                                                    "" );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("distance(lhs,") +
                       Utility::toString(zero( T() )) + ") = distance(" +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( T() )) + " <= " +
                       Utility::toString(zero( T() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string( "lhs = " ) +
                       Utility::toString(zero( T() )) + " " +
                       Utility::CloseComparisonPolicy::getOperatorName<T>() +
                       " " + Utility::toString(zero( T() )) );
  }

  comparison_details =
    Utility::CloseComparisonPolicy::createComparisonDetails(
                                                    "lhs", true, zero( T() ),
                                                    "rhs", false, zero( T() ),
                                                    "", small( T() ) );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("distance(lhs,") +
                       Utility::toString(zero( T() )) + ") = distance(" +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( T() )) + " <= " +
                       Utility::toString(smallQuantity( T() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string( "lhs = " ) +
                       Utility::toString(zero( T() )) + " " +
                       Utility::CloseComparisonPolicy::getOperatorName<T>() +
                       " " + Utility::toString(zero( T() )) );
  }

  comparison_details =
    Utility::CloseComparisonPolicy::createComparisonDetails(
                                                    "lhs", true, zero( T() ),
                                                    "rhs", false, zero( T() ),
                                                    "[0].first" );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("distance(lhs[0].first,") +
                       Utility::toString(zero( T() )) + ") = distance(" +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( T() )) + " <= " +
                       Utility::toString(zero( T() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string( "lhs[0].first = " ) +
                       Utility::toString(zero( T() )) + " " +
                       Utility::CloseComparisonPolicy::getOperatorName<T>() +
                       " " + Utility::toString(zero( T() )) );
  }

  comparison_details =
    Utility::CloseComparisonPolicy::createComparisonDetails(
                                                    "lhs", true, zero( T() ),
                                                    "rhs", false, zero( T() ),
                                                    "[0].first", small(T()) );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("distance(lhs[0].first,") +
                       Utility::toString(zero( T() )) + ") = distance(" +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( T() )) + " <= " +
                       Utility::toString(smallQuantity( T() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string( "lhs[0].first = " ) +
                       Utility::toString(zero( T() )) + " " +
                       Utility::CloseComparisonPolicy::getOperatorName<T>() +
                       " " + Utility::toString(zero( T() )) );
  }

   comparison_details =
     Utility::CloseComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "" );

   if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
   {
     BOOST_CHECK_EQUAL( comparison_details,
                        std::string("distance(") +
                        Utility::toString(zero( T() )) + ",rhs) = distance(" +
                        Utility::toString(zero( T() )) + "," +
                        Utility::toString(zero( T() )) + ") = " +
                        Utility::toString(zero( T() )) + " <= " +
                        Utility::toString(zero( T() )) );
   }
   else
   {
     BOOST_CHECK_EQUAL( comparison_details,
                        Utility::toString(zero( T() )) + " " +
                        Utility::CloseComparisonPolicy::getOperatorName<T>() +
                        " rhs = " + Utility::toString(zero( T() )) );
   }

   comparison_details =
     Utility::CloseComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "", small( T() ) );

   if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
   {
     BOOST_CHECK_EQUAL( comparison_details,
                        std::string("distance(") +
                        Utility::toString(zero( T() )) + ",rhs) = distance(" +
                        Utility::toString(zero( T() )) + "," +
                        Utility::toString(zero( T() )) + ") = " +
                        Utility::toString(zero( T() )) + " <= " +
                        Utility::toString(smallQuantity( T() )) );
   }
   else
   {
     BOOST_CHECK_EQUAL( comparison_details,
                        Utility::toString(zero( T() )) + " " +
                        Utility::CloseComparisonPolicy::getOperatorName<T>() +
                        " rhs = " + Utility::toString(zero( T() )) );
   }

   comparison_details =
     Utility::CloseComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first" );

   if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
   {
     BOOST_CHECK_EQUAL( comparison_details,
                        std::string("distance(") +
                        Utility::toString(zero( T() )) + ",rhs[0].first) = distance(" +
                        Utility::toString(zero( T() )) + "," +
                        Utility::toString(zero( T() )) + ") = " +
                        Utility::toString(zero( T() )) + " <= " +
                        Utility::toString(zero( T() )) );
   }
   else
   {
     BOOST_CHECK_EQUAL( comparison_details,
                        Utility::toString(zero( T() )) + " " +
                        Utility::CloseComparisonPolicy::getOperatorName<T>() +
                        " rhs[0].first = " + Utility::toString(zero( T() )) );
   }

    comparison_details =
     Utility::CloseComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first", small(T()) );

   if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
   {
     BOOST_CHECK_EQUAL( comparison_details,
                        std::string("distance(") +
                        Utility::toString(zero( T() )) + ",rhs[0].first) = distance(" +
                        Utility::toString(zero( T() )) + "," +
                        Utility::toString(zero( T() )) + ") = " +
                        Utility::toString(zero( T() )) + " <= " +
                        Utility::toString(smallQuantity( T() )) );
   }
   else
   {
     BOOST_CHECK_EQUAL( comparison_details,
                        Utility::toString(zero( T() )) + " " +
                        Utility::CloseComparisonPolicy::getOperatorName<T>() +
                        " rhs[0].first = " + Utility::toString(zero( T() )) );
   }

   comparison_details =
     Utility::CloseComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "" );

   if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
   {
     BOOST_CHECK_EQUAL( comparison_details,
                        std::string("distance(lhs,rhs) = distance(") +
                        Utility::toString(zero( T() )) + "," +
                        Utility::toString(zero( T() )) + ") = " +
                        Utility::toString(zero( T() )) + " <= " +
                        Utility::toString(zero( T() )) );
   }
   else
   {
     BOOST_CHECK_EQUAL( comparison_details,
                        std::string( "lhs = " ) +
                        Utility::toString(zero( T() )) + " " +
                        Utility::CloseComparisonPolicy::getOperatorName<T>() +
                        " rhs = " + Utility::toString(zero( T() )) );
   }

   comparison_details =
     Utility::CloseComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "", small( T() ) );

   if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
   {
     BOOST_CHECK_EQUAL( comparison_details,
                        std::string("distance(lhs,rhs) = distance(") +
                        Utility::toString(zero( T() )) + "," +
                        Utility::toString(zero( T() )) + ") = " +
                        Utility::toString(zero( T() )) + " <= " +
                        Utility::toString(smallQuantity( T() )) );
   }
   else
   {
     BOOST_CHECK_EQUAL( comparison_details,
                        std::string( "lhs = " ) +
                        Utility::toString(zero( T() )) + " " +
                        Utility::CloseComparisonPolicy::getOperatorName<T>() +
                        " rhs = " + Utility::toString(zero( T() )) );
   }

   comparison_details =
     Utility::CloseComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first" );

   if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
   {
     BOOST_CHECK_EQUAL( comparison_details,
                        std::string("distance(lhs[0].first,rhs[0].first) = distance(") +
                        Utility::toString(zero( T() )) + "," +
                        Utility::toString(zero( T() )) + ") = " +
                        Utility::toString(zero( T() )) + " <= " +
                        Utility::toString(zero( T() )) );
   }
   else
   {
     BOOST_CHECK_EQUAL( comparison_details,
                        std::string( "lhs[0].first = " ) +
                        Utility::toString(zero( T() )) + " " +
                        Utility::CloseComparisonPolicy::getOperatorName<T>() +
                        " rhs[0].first = " + Utility::toString(zero( T() )) );
   }

   comparison_details =
     Utility::CloseComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first", small(T()) );

   if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
   {
     BOOST_CHECK_EQUAL( comparison_details,
                        std::string("distance(lhs[0].first,rhs[0].first) = distance(") +
                        Utility::toString(zero( T() )) + "," +
                        Utility::toString(zero( T() )) + ") = " +
                        Utility::toString(zero( T() )) + " <= " +
                        Utility::toString(smallQuantity( T() )) );
   }
   else
   {
     BOOST_CHECK_EQUAL( comparison_details,
                        std::string( "lhs[0].first = " ) +
                        Utility::toString(zero( T() )) + " " +
                        Utility::CloseComparisonPolicy::getOperatorName<T>() +
                        " rhs[0].first = " + Utility::toString(zero( T() )) );
   }
}

//---------------------------------------------------------------------------//
// Check that two values can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, T, TestTypes )
{
  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK( (Utility::CloseComparisonPolicy::compare( zero(T()), zero(T()) )) );
    BOOST_CHECK( !(Utility::CloseComparisonPolicy::compare( zero(T()), one(T()) )) );
    BOOST_CHECK( !(Utility::CloseComparisonPolicy::compare( one(T()), zero(T()) )) );
    BOOST_CHECK( (Utility::CloseComparisonPolicy::compare( one(T()), one(T()) )) );

    BOOST_CHECK( (Utility::CloseComparisonPolicy::compare( zero(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( !(Utility::CloseComparisonPolicy::compare( zero(T()), one(T()), small(T()) )) );
    BOOST_CHECK( !(Utility::CloseComparisonPolicy::compare( one(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( (Utility::CloseComparisonPolicy::compare( one(T()), one(T()), small(T()) )) );

    BOOST_CHECK( (Utility::CloseComparisonPolicy::compare( zero(T()), smallOverTwo(T()), small(T()) )) );
    BOOST_CHECK( (Utility::CloseComparisonPolicy::compare( smallOverTwo(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( !(Utility::CloseComparisonPolicy::compare( zero(T()), smallByTwo(T()), small(T()) )) );
    BOOST_CHECK( !(Utility::CloseComparisonPolicy::compare( smallByTwo(T()), zero(T()), small(T()) )) );

    BOOST_CHECK( (Utility::CloseComparisonPolicy::compare( one(T()), (T)(one(T())+smallOverTwo(T())), small(T()) )) );
    BOOST_CHECK( (Utility::CloseComparisonPolicy::compare( (T)(one(T())+smallOverTwo(T())), one(T()), small(T()) )) );
    BOOST_CHECK( !(Utility::CloseComparisonPolicy::compare( one(T()), (T)(one(T())+smallByTwo(T())), small(T()) )) );
    BOOST_CHECK( !(Utility::CloseComparisonPolicy::compare( (T)(one(T())+smallByTwo(T())), one(T()), small(T()) )) );
  }
  else
  {
    BOOST_CHECK( (Utility::CloseComparisonPolicy::compare( zero(T()), zero(T()) )) );
    BOOST_CHECK( !(Utility::CloseComparisonPolicy::compare( zero(T()), one(T()) )) );
    BOOST_CHECK( !(Utility::CloseComparisonPolicy::compare( one(T()), zero(T()) )) );
    BOOST_CHECK( (Utility::CloseComparisonPolicy::compare( one(T()), one(T()) )) );

    BOOST_CHECK( (Utility::CloseComparisonPolicy::compare( zero(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( !(Utility::CloseComparisonPolicy::compare( zero(T()), one(T()), small(T()) )) );
    BOOST_CHECK( !(Utility::CloseComparisonPolicy::compare( one(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( (Utility::CloseComparisonPolicy::compare( one(T()), one(T()), small(T()) )) );
  }

  Utility::CloseComparisonPolicy policy;

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK( (policy( zero(T()), zero(T()) )) );
    BOOST_CHECK( !(policy( zero(T()), one(T()) )) );
    BOOST_CHECK( !(policy( one(T()), zero(T()) )) );
    BOOST_CHECK( (policy( one(T()), one(T()) )) );

    BOOST_CHECK( (policy( zero(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( !(policy( zero(T()), one(T()), small(T()) )) );
    BOOST_CHECK( !(policy( one(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( (policy( one(T()), one(T()), small(T()) )) );

    BOOST_CHECK( (policy( zero(T()), smallOverTwo(T()), small(T()) )) );
    BOOST_CHECK( (policy( smallOverTwo(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( !(policy( zero(T()), smallByTwo(T()), small(T()) )) );
    BOOST_CHECK( !(policy( smallByTwo(T()), zero(T()), small(T()) )) );

    BOOST_CHECK( (policy( one(T()), (T)(one(T())+smallOverTwo(T())), small(T()) )) );
    BOOST_CHECK( (policy( (T)(one(T())+smallOverTwo(T())), one(T()), small(T()) )) );
    BOOST_CHECK( !(policy( one(T()), (T)(one(T())+smallByTwo(T())), small(T()) )) );
    BOOST_CHECK( !(policy( (T)(one(T())+smallByTwo(T())), one(T()), small(T()) )) );
  }
  else
  {
    BOOST_CHECK( (policy( zero(T()), zero(T()) )) );
    BOOST_CHECK( !(policy( zero(T()), one(T()) )) );
    BOOST_CHECK( !(policy( one(T()), zero(T()) )) );
    BOOST_CHECK( (policy( one(T()), one(T()) )) );

    BOOST_CHECK( (policy( zero(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( !(policy( zero(T()), one(T()), small(T()) )) );
    BOOST_CHECK( !(policy( one(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( (policy( one(T()), one(T()), small(T()) )) );
  }
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// RelativeErrorComparisonPolicy Test Suite
//---------------------------------------------------------------------------//
BOOST_AUTO_TEST_SUITE( RelativeErrorComparisonPolicy )

//---------------------------------------------------------------------------//
// Check that the operator name can be returned
BOOST_AUTO_TEST_CASE_TEMPLATE( getOperatorName, T, TestTypes )
{
  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( Utility::RelativeErrorComparisonPolicy::getOperatorName<T>(), "~=" );
  }
  else
  {
    BOOST_CHECK_EQUAL( Utility::RelativeErrorComparisonPolicy::getOperatorName<T>(), "==" );
  }
}

//---------------------------------------------------------------------------//
// Check that the comparison details can be created
BOOST_AUTO_TEST_CASE_TEMPLATE( createComparisonDetails, T, TestTypes )
{
  std::string comparison_details =
    Utility::RelativeErrorComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "" );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("relErr(") +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) + " <= " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       Utility::toString(zero( T() )) + " " +
                       Utility::RelativeErrorComparisonPolicy::getOperatorName<T>() +
                       " " + Utility::toString(zero( T() )) );
  }

  comparison_details = Utility::RelativeErrorComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "", small( T() ) );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("relErr(") +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) + " <= " +
                       Utility::toString(small( T() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       Utility::toString(zero( T() )) + " " +
                       Utility::RelativeErrorComparisonPolicy::getOperatorName<T>() +
                       " " + Utility::toString(zero( T() )) );
  }

  comparison_details = Utility::RelativeErrorComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "" );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("relErr(lhs,") +
                       Utility::toString(zero( T() )) + ") = relErr(" +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) + " <= " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string( "lhs = " ) +
                       Utility::toString(zero( T() )) + " " +
                       Utility::RelativeErrorComparisonPolicy::getOperatorName<T>() +
                       " " + Utility::toString(zero( T() )) );
  }

  comparison_details = Utility::RelativeErrorComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "", small( T() ) );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("relErr(lhs,") +
                       Utility::toString(zero( T() )) + ") = relErr(" +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) + " <= " +
                       Utility::toString(small( T() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string( "lhs = " ) +
                       Utility::toString(zero( T() )) + " " +
                       Utility::RelativeErrorComparisonPolicy::getOperatorName<T>() +
                       " " + Utility::toString(zero( T() )) );
  }

  comparison_details = Utility::RelativeErrorComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "[0].first" );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("relErr(lhs[0].first,") +
                       Utility::toString(zero( T() )) + ") = relErr(" +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) + " <= " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string( "lhs[0].first = " ) +
                       Utility::toString(zero( T() )) + " " +
                       Utility::RelativeErrorComparisonPolicy::getOperatorName<T>() +
                       " " + Utility::toString(zero( T() )) );
  }

  comparison_details = Utility::RelativeErrorComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", false, zero( T() ),
                                                     "[0].first", small(T()) );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("relErr(lhs[0].first,") +
                       Utility::toString(zero( T() )) + ") = relErr(" +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) + " <= " +
                       Utility::toString(small( T() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string( "lhs[0].first = " ) +
                       Utility::toString(zero( T() )) + " " +
                       Utility::RelativeErrorComparisonPolicy::getOperatorName<T>() +
                       " " + Utility::toString(zero( T() )) );
  }

  comparison_details = Utility::RelativeErrorComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "" );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("relErr(") +
                       Utility::toString(zero( T() )) + ",rhs) = relErr(" +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) + " <= " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                        Utility::toString(zero( T() )) + " " +
                        Utility::RelativeErrorComparisonPolicy::getOperatorName<T>() +
                        " rhs = " + Utility::toString(zero( T() )) );
  }

  comparison_details = Utility::RelativeErrorComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "", small( T() ) );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("relErr(") +
                       Utility::toString(zero( T() )) + ",rhs) = relErr(" +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) + " <= " +
                       Utility::toString(small( T() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                        Utility::toString(zero( T() )) + " " +
                        Utility::RelativeErrorComparisonPolicy::getOperatorName<T>() +
                        " rhs = " + Utility::toString(zero( T() )) );
  }

  comparison_details = Utility::RelativeErrorComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first" );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("relErr(") +
                       Utility::toString(zero( T() )) + ",rhs[0].first) = relErr(" +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) + " <= " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                        Utility::toString(zero( T() )) + " " +
                        Utility::RelativeErrorComparisonPolicy::getOperatorName<T>() +
                        " rhs[0].first = " + Utility::toString(zero( T() )) );
  }

  comparison_details = Utility::RelativeErrorComparisonPolicy::createComparisonDetails(
                                                     "lhs", false, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first", small(T()) );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("relErr(") +
                       Utility::toString(zero( T() )) + ",rhs[0].first) = relErr(" +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) + " <= " +
                       Utility::toString(small( T() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                        Utility::toString(zero( T() )) + " " +
                        Utility::RelativeErrorComparisonPolicy::getOperatorName<T>() +
                        " rhs[0].first = " + Utility::toString(zero( T() )) );
  }

  comparison_details = Utility::RelativeErrorComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "" );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("relErr(lhs,rhs) = relErr(") +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) + " <= " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                        std::string( "lhs = " ) +
                        Utility::toString(zero( T() )) + " " +
                        Utility::CloseComparisonPolicy::getOperatorName<T>() +
                        " rhs = " + Utility::toString(zero( T() )) );
  }

  comparison_details = Utility::RelativeErrorComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "", small( T() ) );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("relErr(lhs,rhs) = relErr(") +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) + " <= " +
                       Utility::toString(small( T() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                        std::string( "lhs = " ) +
                        Utility::toString(zero( T() )) + " " +
                        Utility::CloseComparisonPolicy::getOperatorName<T>() +
                        " rhs = " + Utility::toString(zero( T() )) );
  }

  comparison_details = Utility::RelativeErrorComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first" );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("relErr(lhs[0].first,rhs[0].first) = relErr(") +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) + " <= " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                        std::string( "lhs[0].first = " ) +
                        Utility::toString(zero( T() )) + " " +
                        Utility::CloseComparisonPolicy::getOperatorName<T>() +
                        " rhs[0].first = " + Utility::toString(zero( T() )) );
  }

  comparison_details = Utility::RelativeErrorComparisonPolicy::createComparisonDetails(
                                                     "lhs", true, zero( T() ),
                                                     "rhs", true, zero( T() ),
                                                     "[0].first", small(T()) );

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK_EQUAL( comparison_details,
                       std::string("relErr(lhs[0].first,rhs[0].first) = relErr(") +
                       Utility::toString(zero( T() )) + "," +
                       Utility::toString(zero( T() )) + ") = " +
                       Utility::toString(zero( typename Utility::QuantityTraits<T>::RawType() )) + " <= " +
                       Utility::toString(small( T() )) );
  }
  else
  {
    BOOST_CHECK_EQUAL( comparison_details,
                        std::string( "lhs[0].first = " ) +
                        Utility::toString(zero( T() )) + " " +
                        Utility::CloseComparisonPolicy::getOperatorName<T>() +
                        " rhs[0].first = " + Utility::toString(zero( T() )) );
  }
}

//---------------------------------------------------------------------------//
// Check that two values can be compared
BOOST_AUTO_TEST_CASE_TEMPLATE( compare, T, TestTypes )
{
  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK( (Utility::RelativeErrorComparisonPolicy::compare( zero(T()), zero(T()) )) );
    BOOST_CHECK( !(Utility::RelativeErrorComparisonPolicy::compare( zero(T()), one(T()) )) );
    BOOST_CHECK( !(Utility::RelativeErrorComparisonPolicy::compare( one(T()), zero(T()) )) );
    BOOST_CHECK( (Utility::RelativeErrorComparisonPolicy::compare( one(T()), one(T()) )) );

    BOOST_CHECK( (Utility::RelativeErrorComparisonPolicy::compare( zero(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( !(Utility::RelativeErrorComparisonPolicy::compare( zero(T()), one(T()), small(T()) )) );
    BOOST_CHECK( !(Utility::RelativeErrorComparisonPolicy::compare( one(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( (Utility::RelativeErrorComparisonPolicy::compare( one(T()), one(T()), small(T()) )) );

    BOOST_CHECK( !(Utility::RelativeErrorComparisonPolicy::compare( zero(T()), smallOverTwo(T()), small(T()) )) );
    BOOST_CHECK( !(Utility::RelativeErrorComparisonPolicy::compare( smallOverTwo(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( !(Utility::RelativeErrorComparisonPolicy::compare( zero(T()), smallByTwo(T()), small(T()) )) );
    BOOST_CHECK( !(Utility::RelativeErrorComparisonPolicy::compare( smallByTwo(T()), zero(T()), small(T()) )) );

    BOOST_CHECK( (Utility::RelativeErrorComparisonPolicy::compare( one(T()), (T)(one(T())+smallOverTwo(T())), small(T()) )) );
    BOOST_CHECK( (Utility::RelativeErrorComparisonPolicy::compare( (T)(one(T())+smallOverTwo(T())), one(T()), small(T()) )) );
    BOOST_CHECK( !(Utility::RelativeErrorComparisonPolicy::compare( one(T()), (T)(one(T())+smallByTwo(T())), small(T()) )) );
    BOOST_CHECK( !(Utility::RelativeErrorComparisonPolicy::compare( (T)(one(T())+smallByTwo(T())), one(T()), small(T()) )) );
  }
  else
  {
    BOOST_CHECK( (Utility::RelativeErrorComparisonPolicy::compare( zero(T()), zero(T()) )) );
    BOOST_CHECK( !(Utility::RelativeErrorComparisonPolicy::compare( zero(T()), one(T()) )) );
    BOOST_CHECK( !(Utility::RelativeErrorComparisonPolicy::compare( one(T()), zero(T()) )) );
    BOOST_CHECK( (Utility::RelativeErrorComparisonPolicy::compare( one(T()), one(T()) )) );

    BOOST_CHECK( (Utility::RelativeErrorComparisonPolicy::compare( zero(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( !(Utility::RelativeErrorComparisonPolicy::compare( zero(T()), one(T()), small(T()) )) );
    BOOST_CHECK( !(Utility::RelativeErrorComparisonPolicy::compare( one(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( (Utility::RelativeErrorComparisonPolicy::compare( one(T()), one(T()), small(T()) )) );
  }

  Utility::RelativeErrorComparisonPolicy policy;

  if( std::is_floating_point<typename Utility::QuantityTraits<T>::RawType>::value )
  {
    BOOST_CHECK( (policy( zero(T()), zero(T()) )) );
    BOOST_CHECK( !(policy( zero(T()), one(T()) )) );
    BOOST_CHECK( !(policy( one(T()), zero(T()) )) );
    BOOST_CHECK( (policy( one(T()), one(T()) )) );

    BOOST_CHECK( (policy( zero(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( !(policy( zero(T()), one(T()), small(T()) )) );
    BOOST_CHECK( !(policy( one(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( (policy( one(T()), one(T()), small(T()) )) );

    BOOST_CHECK( !(policy( zero(T()), smallOverTwo(T()), small(T()) )) );
    BOOST_CHECK( !(policy( smallOverTwo(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( !(policy( zero(T()), smallByTwo(T()), small(T()) )) );
    BOOST_CHECK( !(policy( smallByTwo(T()), zero(T()), small(T()) )) );

    BOOST_CHECK( (policy( one(T()), (T)(one(T())+smallOverTwo(T())), small(T()) )) );
    BOOST_CHECK( (policy( (T)(one(T())+smallOverTwo(T())), one(T()), small(T()) )) );
    BOOST_CHECK( !(policy( one(T()), (T)(one(T())+smallByTwo(T())), small(T()) )) );
    BOOST_CHECK( !(policy( (T)(one(T())+smallByTwo(T())), one(T()), small(T()) )) );
  }
  else
  {
    BOOST_CHECK( (policy( zero(T()), zero(T()) )) );
    BOOST_CHECK( !(policy( zero(T()), one(T()) )) );
    BOOST_CHECK( !(policy( one(T()), zero(T()) )) );
    BOOST_CHECK( (policy( one(T()), one(T()) )) );

    BOOST_CHECK( (policy( zero(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( !(policy( zero(T()), one(T()), small(T()) )) );
    BOOST_CHECK( !(policy( one(T()), zero(T()), small(T()) )) );
    BOOST_CHECK( (policy( one(T()), one(T()), small(T()) )) );
  }
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// end tstComparisonPolicy.cpp
//---------------------------------------------------------------------------//
