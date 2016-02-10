//---------------------------------------------------------------------------//
//!
//! \file   tstGaussKronrodIntegration.cpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod quadrature gk_integration unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_GaussKronrodIntegration.hpp"

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

double exp_neg_x( const double x )
{
  return exp( -x );
}

double exp_neg_abs_x( const double x, const double a )
{
  return exp( -a*fabs(x) );
}

double inv_sqrt_abs_x( const double x )
{
  return 1/sqrt(fabs(x));
}

//---------------------------------------------------------------------------//
// Instantiation macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, X2Functor ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, X3Functor )
/*
//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1]
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegration,
				   integrate,
				   Functor )
{
  Utility::GaussKronrodIntegration gk_integration( 1e-12 );
  
  double result, absolute_error;
  size_t evals;

  Functor functor_instance;

  gk_integration.integrate( functor_instance, 0.0, 1.0, result, absolute_error, evals);

  double tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodIntegration, integrate );
*/
//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1] adaptively
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegration,
				   integrateAdaptively_15,
				   Functor )
{
  Utility::GaussKronrodIntegration gk_integration( 1e-12 );

  double result, absolute_error, tol;

  Functor functor_instance;

  // Test the 15-point rule
  gk_integration.integrateAdaptively<15>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodIntegration, integrateAdaptively_15 );

//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1] adaptively
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegration,
				   integrateAdaptively_21,
				   Functor )
{
  Utility::GaussKronrodIntegration gk_integration( 1e-12 );

  double result, absolute_error, tol;

  Functor functor_instance;

  // Test the 21-point rule
  gk_integration.integrateAdaptively<21>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodIntegration, integrateAdaptively_21 );

//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1] adaptively
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegration,
				   integrateAdaptively_31,
				   Functor )
{
  Utility::GaussKronrodIntegration gk_integration( 1e-12 );

  double result, absolute_error, tol;

  Functor functor_instance;

  // Test the 31-point rule
  gk_integration.integrateAdaptively<31>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodIntegration, integrateAdaptively_31 );

//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1] adaptively
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegration,
				   integrateAdaptively_41,
				   Functor )
{
  Utility::GaussKronrodIntegration gk_integration( 1e-12 );

  double result, absolute_error, tol;

  Functor functor_instance;

  // Test the 41-point rule
  gk_integration.integrateAdaptively<41>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodIntegration, integrateAdaptively_41 );

//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1] adaptively
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegration,
				   integrateAdaptively_51,
				   Functor )
{
  Utility::GaussKronrodIntegration gk_integration( 1e-12 );

  double result, absolute_error, tol;

  Functor functor_instance;

  // Test the 51-point rule
  gk_integration.integrateAdaptively<51>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodIntegration, integrateAdaptively_51 );

//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1] adaptively
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegration,
				   integrateAdaptively_61,
				   Functor )
{
  Utility::GaussKronrodIntegration gk_integration( 1e-12 );

  double result, absolute_error, tol;

  Functor functor_instance;

  // Test the 61-point rule
  gk_integration.integrateAdaptively<61>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodIntegration, integrateAdaptively_61 );

//---------------------------------------------------------------------------//
// end tstGaussKronrodIntegration.cpp
//---------------------------------------------------------------------------//
