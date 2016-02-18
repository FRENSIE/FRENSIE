//---------------------------------------------------------------------------//
//!
//! \file   tstGaussKronrodIntegrator.cpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod quadrature integrator unit tests.
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
#include "Utility_GaussKronrodIntegrator.hpp"

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

  static double getLowerIntegratedValue()
  {
    return 1.0/24.0;
  }

  static double getUpperIntegratedValue()
  {
    return 7.0/24.0;
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

  static double getLowerIntegratedValue()
  {
    return 1.0/64.0;
  }

  static double getUpperIntegratedValue()
  {
    return 15.0/64.0;
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
// Testing Structs.
//---------------------------------------------------------------------------//
class TestGaussKronrodIntegrator : public Utility::GaussKronrodIntegrator
{
public:
  TestGaussKronrodIntegrator( const double relative_error_tol )
    : Utility::GaussKronrodIntegrator( relative_error_tol )
  { /* ... */ }

  ~TestGaussKronrodIntegrator()
  { /* ... */ }

  // Allow public access to the GaussKronrodIntegrator protected member functions
  using Utility::GaussKronrodIntegrator::calculateQuadratureIntegrandValuesAtAbscissa;
  using Utility::GaussKronrodIntegrator::bisectAndIntegrateBinInterval;
  using Utility::GaussKronrodIntegrator::rescaleAbsoluteError;
  using Utility::GaussKronrodIntegrator::subintervalTooSmall;
  using Utility::GaussKronrodIntegrator::checkRoundoffError;
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
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegrator,
				                   integrateWithPointRule,
                                   Functor )
{
  Utility::GaussKronrodIntegrator gk_integrator( 1e-12 );
  
  double absolute_error, result_abs, result_asc, test_result, tol;
  long double result;

  Functor functor_instance;

  gk_integrator.integrateWithPointRule<15>( functor_instance, 
                                        0.0,  
                                        1.0,  
                                        result,  
                                        absolute_error,  
                                        result_abs, 
                                        result_asc );

  tol = absolute_error/result;
  test_result = result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), test_result, tol );

  gk_integrator.integrateWithPointRule<21>( functor_instance, 
                                        0.0,  
                                        1.0,  
                                        result,  
                                        absolute_error,  
                                        result_abs, 
                                        result_asc );

  tol = absolute_error/result;
  test_result = result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), test_result, tol );

  gk_integrator.integrateWithPointRule<31>( functor_instance, 
                                        0.0,  
                                        1.0,  
                                        result,  
                                        absolute_error,  
                                        result_abs, 
                                        result_asc );

  tol = absolute_error/result;
  test_result = result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), test_result, tol );

  gk_integrator.integrateWithPointRule<41>( functor_instance, 
                                        0.0,  
                                        1.0,  
                                        result,  
                                        absolute_error,  
                                        result_abs, 
                                        result_asc );

  tol = absolute_error/result;
  test_result = result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), test_result, tol );

  gk_integrator.integrateWithPointRule<51>( functor_instance, 
                                        0.0,  
                                        1.0,  
                                        result,  
                                        absolute_error,  
                                        result_abs, 
                                        result_asc );

  tol = absolute_error/result;
  test_result = result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), test_result, tol );

  gk_integrator.integrateWithPointRule<61>( functor_instance, 
                                        0.0,  
                                        1.0,  
                                        result,  
                                        absolute_error,  
                                        result_abs, 
                                        result_asc );

  tol = absolute_error/result;
  test_result = result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), test_result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodIntegrator, integrateWithPointRule );

//---------------------------------------------------------------------------//
// Check that quadrature integrand values can be evaulated at abscissa
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegrator,
				                   calculateQuadratureIntegrandValuesAtAbscissa,
                                   Functor )
{
  TestGaussKronrodIntegrator test_integrator( 1e-12 );
  
  double half_length = 0.5;
  double midpoint = 0.5;
  double abscissa = 0.5;

  double integrand_value_lower, integrand_value_upper ;

  Functor functor_instance;

  test_integrator.calculateQuadratureIntegrandValuesAtAbscissa( 
                functor_instance, 
                abscissa,
                half_length,
                midpoint,
                integrand_value_lower,
                integrand_value_upper );  


  double tol = 1e-12;

  TEST_FLOATING_EQUALITY( functor_instance( 0.25 ), integrand_value_lower, tol );
  TEST_FLOATING_EQUALITY( functor_instance( 0.75 ), integrand_value_upper, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodIntegrator, calculateQuadratureIntegrandValuesAtAbscissa );

//---------------------------------------------------------------------------//
// Check that quadrature integrand can be bisected and integrated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegrator,
				                   bisectAndIntegrateBinInterval,
                                   Functor )
{
  TestGaussKronrodIntegrator test_integrator( 1e-12 );
  
  Utility::BinTraits bin, bin_1, bin_2;

  double bin_1_asc, bin_2_asc, tol_1, tol_2;

  bin.lower_limit = 0.0;
  bin.upper_limit = 1.0;
  

  Functor functor_instance;

  test_integrator.bisectAndIntegrateBinInterval<15>( 
                functor_instance, 
                bin,
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc );  

  tol_1 = bin_1.error/bin_1.result;
  tol_2 = bin_2.error/bin_2.result;

  TEST_FLOATING_EQUALITY( Functor::getLowerIntegratedValue(), 
                          static_cast<double>( bin_1.result ), 
                          tol_1 );
  TEST_FLOATING_EQUALITY( Functor::getUpperIntegratedValue(),
                          static_cast<double>( bin_2.result ), 
                          tol_2 );

  TEST_EQUALITY( bin_1.lower_limit, bin.lower_limit );
  TEST_FLOATING_EQUALITY( bin_1.upper_limit, 0.5, 1e-15);
  TEST_FLOATING_EQUALITY( bin_2.lower_limit, 0.5, 1e-15 );
  TEST_EQUALITY( bin_2.upper_limit, bin.upper_limit );


  test_integrator.bisectAndIntegrateBinInterval<21>( 
                functor_instance, 
                bin,
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc );  

  tol_1 = bin_1.error/bin_1.result;
  tol_2 = bin_2.error/bin_2.result;

  TEST_FLOATING_EQUALITY( Functor::getLowerIntegratedValue(), 
                          static_cast<double>( bin_1.result ), 
                          tol_1 );
  TEST_FLOATING_EQUALITY( Functor::getUpperIntegratedValue(),
                          static_cast<double>( bin_2.result ), 
                          tol_2 );


  test_integrator.bisectAndIntegrateBinInterval<31>( 
                functor_instance, 
                bin,
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc );  

  tol_1 = bin_1.error/bin_1.result;
  tol_2 = bin_2.error/bin_2.result;

  TEST_FLOATING_EQUALITY( Functor::getLowerIntegratedValue(), 
                          static_cast<double>( bin_1.result ), 
                          tol_1 );
  TEST_FLOATING_EQUALITY( Functor::getUpperIntegratedValue(),
                          static_cast<double>( bin_2.result ), 
                          tol_2 );


  test_integrator.bisectAndIntegrateBinInterval<41>( 
                functor_instance, 
                bin,
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc );  

  tol_1 = bin_1.error/bin_1.result;
  tol_2 = bin_2.error/bin_2.result;

  TEST_FLOATING_EQUALITY( Functor::getLowerIntegratedValue(), 
                          static_cast<double>( bin_1.result ), 
                          tol_1 );
  TEST_FLOATING_EQUALITY( Functor::getUpperIntegratedValue(),
                          static_cast<double>( bin_2.result ), 
                          tol_2 );


  test_integrator.bisectAndIntegrateBinInterval<51>( 
                functor_instance, 
                bin,
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc );  

  tol_1 = bin_1.error/bin_1.result;
  tol_2 = bin_2.error/bin_2.result;

  TEST_FLOATING_EQUALITY( Functor::getLowerIntegratedValue(), 
                          static_cast<double>( bin_1.result ), 
                          tol_1 );
  TEST_FLOATING_EQUALITY( Functor::getUpperIntegratedValue(),
                          static_cast<double>( bin_2.result ), 
                          tol_2 );


  test_integrator.bisectAndIntegrateBinInterval<61>( 
                functor_instance, 
                bin,
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc );  

  tol_1 = bin_1.error/bin_1.result;
  tol_2 = bin_2.error/bin_2.result;

  TEST_FLOATING_EQUALITY( Functor::getLowerIntegratedValue(), 
                          static_cast<double>( bin_1.result ), 
                          tol_1 );
  TEST_FLOATING_EQUALITY( Functor::getUpperIntegratedValue(),
                          static_cast<double>( bin_2.result ), 
                          tol_2 );
}

UNIT_TEST_INSTANTIATION( GaussKronrodIntegrator, bisectAndIntegrateBinInterval );

//---------------------------------------------------------------------------//
// Check that the error can be rescaled
TEUCHOS_UNIT_TEST( GaussKronrodIntegrator, 
                   rescaleAbsoluteError )
{
  TestGaussKronrodIntegrator test_integrator( 1e-12 );
  
  double absolute_error = 0.0;
  double result_abs = 0.0;
  double result_asc = 0.0;
  double tol = 1e-12;
  double limit = std::numeric_limits<double>::min() / ( 50.0 *
                   std::numeric_limits<double>::epsilon() );

  absolute_error = limit/2.0;

  test_integrator.rescaleAbsoluteError( 
                absolute_error, 
                result_abs,
                result_asc );  

  TEST_FLOATING_EQUALITY( limit/2.0, absolute_error, tol );


  absolute_error = 1.0;
  result_asc = 2.0;

  test_integrator.rescaleAbsoluteError( 
                absolute_error, 
                result_abs,
                result_asc );  

  TEST_FLOATING_EQUALITY( 2.0, absolute_error, tol );


  absolute_error = 1.0;
  result_asc = 800.0;

  test_integrator.rescaleAbsoluteError( 
                absolute_error, 
                result_abs,
                result_asc );  

  TEST_FLOATING_EQUALITY( 100.0, absolute_error, tol );


  absolute_error = 50.0*std::numeric_limits<double>::epsilon();
  result_asc = 0.0;
  result_abs = 2.0;
  double min_error = 50.0*std::numeric_limits<double>::epsilon() * result_abs;

  test_integrator.rescaleAbsoluteError( 
                absolute_error, 
                result_abs,
                result_asc );  

  TEST_FLOATING_EQUALITY( min_error, absolute_error, tol );
}

//---------------------------------------------------------------------------//
// Check the roundoff error
TEUCHOS_UNIT_TEST( GaussKronrodIntegrator, 
                   checkRoundoffError )
{
  TestGaussKronrodIntegrator test_integrator( 1e-12 );
  
  Utility::BinTraits bin, bin_1, bin_2;
  int round_off_1 = 0;
  int round_off_2 = 0;
  int number_of_interactions = 0;
  double error_12 = 0.0, bin_1_asc = 0.0, bin_2_asc = 0.0;
  double tol = 1e-12;

  bin.result = 9.9999;
  bin_1.result = 5.0;
  bin_2.result = 5.0;

  bin.error = 0.1;
  bin_1.error = 0.5;
  bin_2.error = 0.49;

  bin_1_asc = bin_1.error;
  bin_2_asc = bin_2.error;


  test_integrator.checkRoundoffError( 
                bin, 
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc,
                round_off_1,
                round_off_2,
                number_of_interactions );  

  TEST_EQUALITY_CONST( 0, round_off_1 );
  TEST_EQUALITY_CONST( 0, round_off_2 );

  bin_1_asc = 0.0;
  bin_2_asc = 0.0;


  test_integrator.checkRoundoffError( 
                bin, 
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc,
                round_off_1,
                round_off_2,
                number_of_interactions );  

  TEST_EQUALITY_CONST( 1, round_off_1 );
  TEST_EQUALITY_CONST( 0, round_off_2 );


  bin_2.error = 0.501;
  number_of_interactions = 10;

  test_integrator.checkRoundoffError( 
                bin, 
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc,
                round_off_1,
                round_off_2,
                number_of_interactions );  

  TEST_EQUALITY_CONST( 2, round_off_1 );
  TEST_EQUALITY_CONST( 1, round_off_2 );


  bin.result = 9.9;

  test_integrator.checkRoundoffError( 
                bin, 
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc,
                round_off_1,
                round_off_2,
                number_of_interactions );  

  TEST_EQUALITY_CONST( 2, round_off_1 );
  TEST_EQUALITY_CONST( 2, round_off_2 );
}

//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1] adaptively
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegrator,
				   integrateAdaptively,
				   Functor )
{
  Utility::GaussKronrodIntegrator gk_integrator( 1e-12 );

  double result, absolute_error, tol;

  Functor functor_instance;

  // Test the 15-point rule
  gk_integrator.integrateAdaptively<15>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );


  // Test the 21-point rule
  gk_integrator.integrateAdaptively<21>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );


  // Test the 31-point rule
  gk_integrator.integrateAdaptively<31>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );


  // Test the 41-point rule
  gk_integrator.integrateAdaptively<41>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );


  // Test the 51-point rule
  gk_integrator.integrateAdaptively<51>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );


  // Test the 61-point rule
  gk_integrator.integrateAdaptively<61>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodIntegrator, integrateAdaptively );

//---------------------------------------------------------------------------//
// Check that a function with integrable singularities can be integrated
TEUCHOS_UNIT_TEST( GaussKronrodIntegrator,
		   integrateAdaptivelyWynnEpsilon_basic )
{
  boost::function<double (double x)> function_wrapper = inv_sqrt_abs_x;

  Utility::GaussKronrodIntegrator gkq_set( 1e-12, 0.0, 100000 );

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
/*
//---------------------------------------------------------------------------//
// Check that a function with integrable singularities can be integrated
TEUCHOS_UNIT_TEST( GaussKronrodIntegrator,
		   integrateAdaptivelyWynnEpsilon_advanced )
{
  boost::function<double (double x)> function_wrapper = inv_sqrt_abs_x;

  Teuchos::Array<double> points_of_interest( 3 );
  points_of_interest[0] = -1.0;
  points_of_interest[1] = 0.0; // integrable singularity
  points_of_interest[2] = 1.0;

  Utility::GaussKronrodIntegrator gkq_set( 1e-12, 0.0, 100000 );

  double result, absolute_error;

  gkq_set.integrateAdaptivelyWynnEpsilon( function_wrapper,
					 points_of_interest(),
					 result,
					 absolute_error );
  
  double tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( result, 4.0, tol );
}
*/
//---------------------------------------------------------------------------//
// end tstGaussKronrodIntegrator.cpp
//---------------------------------------------------------------------------//
