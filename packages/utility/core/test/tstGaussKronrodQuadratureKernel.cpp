//---------------------------------------------------------------------------//
//!
//! \file   tstGaussKronrodQuadratureKernel.cpp
//! \author Alex Robinson
//! \brief  Gauss-Kronrod quadrature kernel unit tests.
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

double f_x( const double x )
{
  return x*x*x*x*x - x*x*x + 2*x;
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
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodQuadratureKernel,
				   integrate,
				   Functor )
{
  Utility::GaussKronrodQuadratureKernel kernel( 1e-12 );
  
  double result, absolute_error;
  size_t evals;

  Functor functor_instance;

  kernel.integrate( functor_instance, 0.0, 1.0, result, absolute_error, evals);

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

  Functor functor_instance;

  // Test the 15-point rule
  kernel.integrateAdaptively<15>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  double tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );

  // Test the 21-point rule
  kernel.integrateAdaptively<21>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );

  // Test the 31-point rule
  kernel.integrateAdaptively<31>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );

  // Test the 41-point rule
  kernel.integrateAdaptively<41>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );

  // Test the 51-point rule
  kernel.integrateAdaptively<51>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodQuadratureKernel, integrateAdaptively );

//---------------------------------------------------------------------------//
// Check that functions can be integrated over a semi-infinite interval
TEUCHOS_UNIT_TEST( GaussKronrodQuadratureKernel,
		   integrateSemiInfiniteIntervalUpper )
{
  boost::function<double (double x)> function_wrapper = exp_neg_x;
  
  Utility::GaussKronrodQuadratureKernel kernel( 1e-12 );

  double result, absolute_error;

  kernel.integrateSemiInfiniteIntervalUpper( function_wrapper,
					     0.0,
					     result,
					     absolute_error );

  double tol = absolute_error/result;
  
  TEST_FLOATING_EQUALITY( result, 1.0, tol );
}

//---------------------------------------------------------------------------//
// Check that functions can be integrated over a semi-infinite interval
TEUCHOS_UNIT_TEST( GaussKronrodQuadratureKernel,
		   integrateSemiInfiniteIntervalLower )
{
  boost::function<double (double x)> function_wrapper = exp;

  Utility::GaussKronrodQuadratureKernel kernel( 1e-12 );

  double result, absolute_error;

  kernel.integrateSemiInfiniteIntervalLower( function_wrapper,
					     0.0,
					     result,
					     absolute_error );

  double tol = absolute_error/result;
  
  TEST_FLOATING_EQUALITY( result, 1.0, tol );
}

//---------------------------------------------------------------------------//
// Check that functions can be integrated over an infinite interval
TEUCHOS_UNIT_TEST( GaussKronrodQuadratureKernel,
		   integrateInfiniteInterval )
{
  boost::function<double (double x)> function_wrapper = 
    boost::bind( exp_neg_abs_x, _1, 1.0 );

  Utility::GaussKronrodQuadratureKernel kernel( 1e-12 );

  double result, absolute_error;

  kernel.integrateInfiniteInterval( function_wrapper,
				    result,
				    absolute_error );

  double tol = absolute_error/result;
  
  TEST_FLOATING_EQUALITY( result, 2.0, tol );
}

//---------------------------------------------------------------------------//
// Check that a function with integrable singularities can be integrated
TEUCHOS_UNIT_TEST( GaussKronrodQuadratureKernel,
		   integrateAdaptivelyWynnEpsilon_basic )
{
  boost::function<double (double x)> function_wrapper = inv_sqrt_abs_x;

  Utility::GaussKronrodQuadratureKernel kernel( 1e-12, 0.0, 100000, 100000 );

  double result, absolute_error;

  kernel.integrateAdaptivelyWynnEpsilon( function_wrapper,
					 0.0,
					 1.0,
					 result,
					 absolute_error );

  double tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( result, 2.0, tol );

  kernel.integrateAdaptivelyWynnEpsilon( function_wrapper,
					 -1.0,
					 0.0,
					 result,
					 absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( result, 2.0, tol );
}

//---------------------------------------------------------------------------//
// Check that a function with integrable singularities can be integrated
TEUCHOS_UNIT_TEST( GaussKronrodQuadratureKernel,
		   integrateAdaptivelyWynnEpsilon_advanced )
{
  boost::function<double (double x)> function_wrapper = inv_sqrt_abs_x;

  Teuchos::Array<double> points_of_interest( 3 );
  points_of_interest[0] = -1.0;
  points_of_interest[1] = 0.0; // integrable singularity
  points_of_interest[2] = 1.0;

  Utility::GaussKronrodQuadratureKernel kernel( 1e-12, 0.0, 100000, 100000 );

  double result, absolute_error;

  kernel.integrateAdaptivelyWynnEpsilon( function_wrapper,
					 points_of_interest(),
					 result,
					 absolute_error );
  
  double tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( result, 4.0, tol );
}

//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1]
TEUCHOS_UNIT_TEST( GaussKronrodQuadratureKernel,
                   integrateGuassLegendre )
{
  boost::function<double (double x)> function_wrapper = f_x;

  Utility::GaussKronrodQuadratureKernel kernel( 1e-12, 0.0, 3, 3 );
  
  Teuchos::Array<double> points( 3 ), weights( 3 );

  double result;

  kernel.integrateGuassLegendre( function_wrapper, 1.0, 3.0, points, weights, result );


  TEST_FLOATING_EQUALITY( 1.2254, points[0], 1e-5 );
  TEST_FLOATING_EQUALITY( 2.0000, points[1], 1e-5 );
  TEST_FLOATING_EQUALITY( 2.7746, points[2], 1e-5 );
  TEST_FLOATING_EQUALITY( 0.555556, weights[0], 1e-5 );
  TEST_FLOATING_EQUALITY( 0.888889, weights[1], 1e-5 );
  TEST_FLOATING_EQUALITY( 0.555556, weights[2], 1e-5 );
}

//---------------------------------------------------------------------------//
// end tstGaussKronrodQuadratureKernel.cpp
//---------------------------------------------------------------------------//
