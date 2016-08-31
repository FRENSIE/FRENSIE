//---------------------------------------------------------------------------//
//!
//! \file   tstExponentiationAlgorithms.cpp
//! \author Alex Robinson
//! \brief  Exponentiation algorithm unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_ExponentiationAlgorithms.hpp"

//---------------------------------------------------------------------------//
// Instantiation macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION_2( type, name )			   \
  typedef unsigned long long  uint64;				   \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, int )  \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, double, long ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, double, uint64 )

#define UNIT_TEST_INSTANTIATION( type, name )				\
  typedef unsigned long long  uint64;					\
  typedef unsigned long  uint32;					\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unsigned )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, uint32 )		\
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

UNIT_TEST_INSTANTIATION( Exponentiation, recursiveMod );

//---------------------------------------------------------------------------//
// end tstExponentiationAlgorithms.cpp
//---------------------------------------------------------------------------//
