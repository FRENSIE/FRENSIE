//---------------------------------------------------------------------------//
//!
//! \file   tstGaussKronrodQuadratureKernel.cpp
//! \author Alex Robinson
//! \brief  Gauss-Kronrod quadrature kernel unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_GaussKronrodQuadratureKernel.hpp"

//---------------------------------------------------------------------------//
// Testing Functors
//---------------------------------------------------------------------------//
struct X2Functor
{
  double operator()( const double x ) const
  {
    if( x >= 0.0 && x <= 1.0 )
      return x*x;
    else
      return 0.0;
  }
  
  static double getIntegratedValue()
  {
    return 1.0/3.0;
  }
};

struct X3Functor
{
  double operator()( const double x ) const
  {
    if( x >= 0.0 && x <= 1.0 )
      return x*x*x;
    else
      return 0.0;
  }

  static double getIntegratedValue()
  {
    return 0.25;
  }
};

//---------------------------------------------------------------------------//
// Instantiation macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, X2Functor ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, X3Functor )

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1]
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodQuadratureKernel,
				   integrate,
				   Functor )
{
  Utility::GaussKronrodQuadratureKernel kernel( 1e-12 );
  
  double result, absolute_error;
  size_t evals;

  kernel.integrate( Functor(), 0.0, 1.0, result, absolute_error, evals );

  double tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodQuadratureKernel, integrate );

//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1] adaptively
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodQuadratureKernel,
				   integrateAdaptively,
				   Functor )
{
  Utility::GaussKronrodQuadratureKernel kernel( 1e-12 );

  double result, absolute_error;

  // Test the 15-point rule
  kernel.integrateAdaptively<15>( Functor(), 0.0, 1.0, result, absolute_error);

  double tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );

  // Test the 21-point rule
  kernel.integrateAdaptively<21>( Functor(), 0.0, 1.0, result, absolute_error);

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );

  // Test the 31-point rule
  kernel.integrateAdaptively<31>( Functor(), 0.0, 1.0, result, absolute_error);

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );

  // Test the 41-point rule
  kernel.integrateAdaptively<41>( Functor(), 0.0, 1.0, result, absolute_error);

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );

  // Test the 51-point rule
  kernel.integrateAdaptively<51>( Functor(), 0.0, 1.0, result, absolute_error);

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodQuadratureKernel, integrateAdaptively );

//---------------------------------------------------------------------------//
// end tstGaussKronrodQuadratureKernel.cpp
//---------------------------------------------------------------------------//
