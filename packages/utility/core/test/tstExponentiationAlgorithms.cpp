//---------------------------------------------------------------------------//
//!
//! \file   tstExponentiationAlgorithms.cpp
//! \author Alex Robinson
//! \brief  Exponentiation algorithm unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs/length.hpp>
#include <boost/units/systems/si/length.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_ExponentiationAlgorithms.hpp"

typedef unsigned long uint32;
typedef unsigned long long uint64;
typedef boost::units::quantity<boost::units::cgs::length> q_cm_double;
typedef boost::units::quantity<boost::units::si::length> q_m_double;

//---------------------------------------------------------------------------//
// Instantiation macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION_2( type, name )			   \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, int );    \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, double, long );     \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, double, uint64 )

#define UNIT_TEST_INSTANTIATION( type, name )   \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double );           \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, q_cm_double );      \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, q_m_double )

#define UNIT_TEST_INTEGRAL_INSTANTIATION( type, name )                  \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unsigned );		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uint32 );		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uint64 )

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Test the recursive exponentiation algorithm
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Exponentiation,
				   recursive,
				   BaseScalarType,
				   ExponentOrdinalType )
{
  // Compute 2^30
  BaseScalarType value =
    Utility::Exponentiation::recursive<BaseScalarType,ExponentOrdinalType>(2,
									   30);
  TEST_EQUALITY_CONST( value, 1073741824 );
}

UNIT_TEST_INSTANTIATION_2( Exponentiation, recursive );

//---------------------------------------------------------------------------//
// Test the static recursive exponentiation algorithm
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Exponentiation,
                                   recursive_static,
                                   BaseScalarType )
{
  typedef typename Utility::QuantityTraits<BaseScalarType>::template GetQuantityToPowerType<30>::type ReturnType30;
  
  // Compute 2^30
  ReturnType30 value_30 = Utility::Exponentiation::recursive<30>( 2.*Utility::QuantityTraits<BaseScalarType>::one() );

  TEST_EQUALITY_CONST( value_30, Utility::QuantityTraits<ReturnType30>::one()*1073741824. );

  // Compute 2^29
  typedef typename Utility::QuantityTraits<BaseScalarType>::template GetQuantityToPowerType<29>::type ReturnType29;

  ReturnType29 value_29 = Utility::Exponentiation::recursive<29>( 2.*Utility::QuantityTraits<BaseScalarType>::one() );

  TEST_EQUALITY_CONST( value_29, Utility::QuantityTraits<ReturnType29>::one()*536870912. );
}

UNIT_TEST_INSTANTIATION( Exponentiation, recursive_static );

//---------------------------------------------------------------------------//
// Test the recursive modular exponentiation algorithm
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( Exponentiation,
				   recursiveMod,
				   OrdinalType )
{
  // Compute (2^30)mod(3)
  OrdinalType value =
    Utility::Exponentiation::recursiveMod<OrdinalType>(2,30,3);

  TEST_EQUALITY_CONST( value, 1 );

  OrdinalType value2 =
    Utility::Exponentiation::recursiveMod<OrdinalType>(2,15,3);
}

UNIT_TEST_INTEGRAL_INSTANTIATION( Exponentiation, recursiveMod );

//---------------------------------------------------------------------------//
// end tstExponentiationAlgorithms.cpp
//---------------------------------------------------------------------------//
