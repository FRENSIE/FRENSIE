//---------------------------------------------------------------------------//
//!
//! \file   tstGaussKronrodQuadratureSet.cpp
//! \author Alex Robinson
//! \brief  Gauss-Kronrod quadrature gkq_set unit tests.
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
#include "Utility_GaussKronrodQuadratureSet.hpp"

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

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1]
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodQuadratureSet,
				   integrate,
				   Functor )
{
  Utility::GaussKronrodQuadratureSet gkq_set( 1e-12 );
  
  double result, absolute_error;
  size_t evals;

  Functor functor_instance;

  gkq_set.integrate( functor_instance, 0.0, 1.0, result, absolute_error, evals);

  double tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodQuadratureSet, integrate );

//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1] adaptively
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodQuadratureSet,
				   integrateAdaptively,
				   Functor )
{
  Utility::GaussKronrodQuadratureSet gkq_set( 1e-12 );

  double result, absolute_error;

  Functor functor_instance;

  // Test the 15-point rule
  gkq_set.integrateAdaptively<15>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  double tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );

  // Test the 21-point rule
  gkq_set.integrateAdaptively<21>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );

  // Test the 31-point rule
  gkq_set.integrateAdaptively<31>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );

  // Test the 41-point rule
  gkq_set.integrateAdaptively<41>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );

  // Test the 51-point rule
  gkq_set.integrateAdaptively<51>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodQuadratureSet, integrateAdaptively );

//---------------------------------------------------------------------------//
// Check that functions can be integrated over a semi-infinite interval
TEUCHOS_UNIT_TEST( GaussKronrodQuadratureSet,
		   integrateSemiInfiniteIntervalUpper )
{
  boost::function<double (double x)> function_wrapper = exp_neg_x;
  
  Utility::GaussKronrodQuadratureSet gkq_set( 1e-12 );

  double result, absolute_error;

  gkq_set.integrateSemiInfiniteIntervalUpper( function_wrapper,
					     0.0,
					     result,
					     absolute_error );

  double tol = absolute_error/result;
  
  TEST_FLOATING_EQUALITY( result, 1.0, tol );
}

//---------------------------------------------------------------------------//
// Check that functions can be integrated over a semi-infinite interval
TEUCHOS_UNIT_TEST( GaussKronrodQuadratureSet,
		   integrateSemiInfiniteIntervalLower )
{
  boost::function<double (double x)> function_wrapper = exp;

  Utility::GaussKronrodQuadratureSet gkq_set( 1e-12 );

  double result, absolute_error;

  gkq_set.integrateSemiInfiniteIntervalLower( function_wrapper,
					     0.0,
					     result,
					     absolute_error );

  double tol = absolute_error/result;
  
  TEST_FLOATING_EQUALITY( result, 1.0, tol );
}

//---------------------------------------------------------------------------//
// Check that functions can be integrated over an infinite interval
TEUCHOS_UNIT_TEST( GaussKronrodQuadratureSet,
		   integrateInfiniteInterval )
{
  boost::function<double (double x)> function_wrapper = 
    boost::bind( exp_neg_abs_x, _1, 1.0 );

  Utility::GaussKronrodQuadratureSet gkq_set( 1e-12 );

  double result, absolute_error;

  gkq_set.integrateInfiniteInterval( function_wrapper,
				    result,
				    absolute_error );

  double tol = absolute_error/result;
  
  TEST_FLOATING_EQUALITY( result, 2.0, tol );
}

//---------------------------------------------------------------------------//
// Check that a function with integrable singularities can be integrated
TEUCHOS_UNIT_TEST( GaussKronrodQuadratureSet,
		   integrateAdaptivelyWynnEpsilon_basic )
{
  boost::function<double (double x)> function_wrapper = inv_sqrt_abs_x;

  Utility::GaussKronrodQuadratureSet gkq_set( 1e-12, 0.0, 100000, 100000 );

  double result, absolute_error;

  gkq_set.integrateAdaptivelyWynnEpsilon( function_wrapper,
					 0.0,
					 1.0,
					 result,
					 absolute_error );

  double tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( result, 2.0, tol );

  gkq_set.integrateAdaptivelyWynnEpsilon( function_wrapper,
					 -1.0,
					 0.0,
					 result,
					 absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( result, 2.0, tol );
}

//---------------------------------------------------------------------------//
// Check that a function with integrable singularities can be integrated
TEUCHOS_UNIT_TEST( GaussKronrodQuadratureSet,
		   integrateAdaptivelyWynnEpsilon_advanced )
{
  boost::function<double (double x)> function_wrapper = inv_sqrt_abs_x;

  Teuchos::Array<double> points_of_interest( 3 );
  points_of_interest[0] = -1.0;
  points_of_interest[1] = 0.0; // integrable singularity
  points_of_interest[2] = 1.0;

  Utility::GaussKronrodQuadratureSet gkq_set( 1e-12, 0.0, 100000, 100000 );

  double result, absolute_error;

  gkq_set.integrateAdaptivelyWynnEpsilon( function_wrapper,
					 points_of_interest(),
					 result,
					 absolute_error );
  
  double tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( result, 4.0, tol );
}

//---------------------------------------------------------------------------//
// end tstGaussKronrodQuadratureSet.cpp
//---------------------------------------------------------------------------//