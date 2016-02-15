//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodIntegrator_def.hpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod integrator
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_KRONROD_INTEGRATOR_DEF_HPP
#define UTILITY_GAUSS_KRONROD_INTEGRATOR_DEF_HPP

// Std Includes
#include <limits>

// GSL Includes
#include <gsl/gsl_errno.h>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_ConstTypeTraits.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_IntegratorException.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_GaussKronrodQuadratureSetTraits.hpp"

namespace Utility{

// Function wrapper for evaluating the functor
template<typename Functor>
double GaussKronrodIntegrator::functorWrapper( const double x, 
						     void* indirected_functor )
{
  // Make sure the functor is valid
  testPrecondition( indirected_functor );

  Functor* functor = (Functor*)( indirected_functor );

  return (*functor)( x );
}

// Integrate the function adaptively
/*! \details Functor must have operator()( double ) defined. This function
 * applies the specified integration rule (Points) adaptively until an 
 * estimate of the integral of the integrand over [lower_limit,upper_limit] is
 * achieved within the desired tolerances. Valid Gauss-Kronrod rules are
 * 15, 21, 31, 41, 51 and 61. Higher-order rules give better accuracy for
 * smooth functions, while lower-order rules save time when the function
 * contains local difficulties, such as discontinuities. On each iteration
 * the adaptive integration strategy bisects the interval with the largest
 * error estimate. See the qag function details in the quadpack documentation.
 */ 
template<int Points, typename Functor>
void GaussKronrodIntegrator::integrateAdaptively(
						 Functor& integrand, 
						 double lower_limit, 
						 double upper_limit,
						 double& result,
						 double& absolute_error ) const
{
  Teuchos::Array<double> bin_result( d_subinterval_limit ); 
  Teuchos::Array<double> bin_error( d_subinterval_limit );
  Teuchos::Array<double> bin_lower_limit( d_subinterval_limit );
  Teuchos::Array<double> bin_upper_limit( d_subinterval_limit );
  Teuchos::Array<double> bin_order( d_subinterval_limit );

  result = 0.0;
  bin_lower_limit[0] = lower_limit;
  bin_upper_limit[0] = upper_limit;  

  TEST_FOR_EXCEPTION( 
    d_absolute_error_tol <= 0 && 
    (d_relative_error_tol < 50 * std::numeric_limits<double>::epsilon() ||
    d_relative_error_tol < 0.5e-28),
    Utility::IntegratorException,
    "tolerance cannot be acheived with given relative_error_tol and absolute_error_tol" );

  /* perform the first integration */

  double result_abs = 0.0;
  double result_asc = 0.0;

  integrateWithPointRule<Points>(
    integrand, 
    lower_limit, 
    upper_limit, 
    bin_result[0], 
    bin_error[0], 
    result_abs, 
    result_asc );

  /* Test on accuracy */

  double tolerance =
    std::max(d_absolute_error_tol, d_relative_error_tol * fabs (bin_result[0]));

  /* need IEEE rounding here to match original quadpack behavior */
  volatile double volatile_round_off; 
  volatile_round_off = 50.0*std::numeric_limits<double>::epsilon()*result_abs;
  double round_off = volatile_round_off;

  TEST_FOR_EXCEPTION( bin_error[0] <= round_off && bin_error[0] > tolerance, 
                      Utility::IntegratorException,
                      "cannot reach tolerance because of roundoff error "
                      "on first attempt" );

  if ( ( bin_error[0] <= tolerance && bin_error[0] != result_asc ) || 
            bin_error[0] == 0.0)
    {
      result = bin_result[0];
      absolute_error = bin_error[0];    

      return;
    }


  TEST_FOR_EXCEPTION( d_subinterval_limit == 1, 
                      Utility::IntegratorException,
                      "a maximum of one iteration was insufficient" );

  double maximum_bin_error = bin_error[0];
  int bin_with_max_error = 0;
  double area = bin_result[0];
  double total_error = bin_error[0];
  int round_off_1 = 0.0;
  int round_off_2 = 0.0;
  int nr_max = 0;

  int last;
  for ( last = 1; last < d_subinterval_limit; last++ )
    {
      double lower_limit_1, upper_limit_1, lower_limit_2, upper_limit_2;
      double area_1 = 0.0, area_2 = 0.0, area_12 = 0.0;
      double error_1 = 0.0, error_2 = 0.0, error_12 = 0.0;
      double result_asc_1 = 0.0, result_asc_2 = 0.0;
      double result_abs_1 = 0.0, result_abs_2 = 0.0;

      /* Bisect the subinterval with the largest error estimate 
         into interval 1 and 2 */

      lower_limit_1 = bin_lower_limit[bin_with_max_error]; 
      upper_limit_1 = 0.5 * ( bin_lower_limit[bin_with_max_error] + 
                              bin_upper_limit[bin_with_max_error] );
      lower_limit_2 = upper_limit_1;
      upper_limit_2 = bin_upper_limit[bin_with_max_error];

      integrateWithPointRule<Points>(
        integrand, 
        lower_limit_1, 
        upper_limit_1, 
        area_1, 
        error_1, 
        result_abs_1, 
        result_asc_1 );

      integrateWithPointRule<Points>(
        integrand, 
        lower_limit_2, 
        upper_limit_2, 
        area_2, 
        error_2, 
        result_abs_2, 
        result_asc_2 );

      /* Improve previous approximations to integral and error and 
         test for accuracy. */

      area_12 = area_1 + area_2;
      error_12 = error_1 + error_2;

      total_error += error_12 - maximum_bin_error;
      area += area_12 - bin_result[bin_with_max_error];

      if (result_asc_1 != error_1 && result_asc_2 != error_2)
        {
          double delta = bin_result[bin_with_max_error] - area_12;

          if ( fabs (delta) <= 1.0e-5 * fabs (area_12) && 
               error_12 >= 0.99 * maximum_bin_error )
            {
              round_off_1++;
            }
          if ( last >= 9 && error_12 > maximum_bin_error )
            {
              round_off_2++;
            }
        }
//std::cout << " my a2 = " << lower_limit_2 << std::endl;
//std::cout << " my b2 = " << upper_limit_2 << std::endl;
//std::cout << " my result1 = " << area_1 << std::endl;
//std::cout << " my result2 = " << area_2 << std::endl;

      updateIntegral( bin_lower_limit, bin_upper_limit, bin_result, bin_error,
                      lower_limit_1, upper_limit_1, area_1, error_1, 
                      lower_limit_2, upper_limit_2, area_2, error_2,
                      last, bin_with_max_error );

      tolerance = std::max( d_absolute_error_tol, d_relative_error_tol * fabs (area));

      if ( total_error <= tolerance )
        break;

      TEST_FOR_EXCEPTION( round_off_1 >= 6 || round_off_2 >= 20, 
                          Utility::IntegratorException,
                          "Roundoff error prevented tolerance from being achieved" );

      TEST_FOR_EXCEPTION( last+1 == d_subinterval_limit, 
                          Utility::IntegratorException,
                          "Maximum number of subdivisions reached" );

      TEST_FOR_EXCEPTION( subintervalTooSmall<Points>( lower_limit_1, 
                                                       lower_limit_2, 
                                                       upper_limit_2 ), 
                          Utility::IntegratorException,
                          "Maximum number of subdivisions reached" );

      sortErrorList( bin_error, bin_order, maximum_bin_error,
                     bin_with_max_error, last, nr_max );

    }
  for ( int i = last; i >= 0; i-- )
    {
      result += bin_result[i];
    }

  absolute_error = total_error;
}

// Integrate the function adaptively with BinQueue
/*! \details Functor must have operator()( double ) defined. This function
 * applies the specified integration rule (Points) adaptively until an 
 * estimate of the integral of the integrand over [lower_limit,upper_limit] is
 * achieved within the desired tolerances. Valid Gauss-Kronrod rules are
 * 15, 21, 31, 41, 51 and 61. Higher-order rules give better accuracy for
 * smooth functions, while lower-order rules save time when the function
 * contains local difficulties, such as discontinuities. On each iteration
 * the adaptive integration strategy bisects the interval with the largest
 * error estimate. See the qag function details in the quadpack documentation.
 */ 
template<int Points, typename Functor>
void GaussKronrodIntegrator::integrateAdaptivelyWithBinQueue(
						 Functor& integrand, 
						 double lower_limit, 
						 double upper_limit,
						 double& result,
						 double& absolute_error ) const
{
  Teuchos::Array<double> bin_result( d_subinterval_limit ); 
  Teuchos::Array<double> bin_error( d_subinterval_limit );
  Teuchos::Array<double> bin_lower_limit( d_subinterval_limit );
  Teuchos::Array<double> bin_upper_limit( d_subinterval_limit );
  Teuchos::Array<double> bin_order( d_subinterval_limit );

  BinTraits bin;
  BinQueue bin_queue;

  result = 0.0;
  bin.lower_limit = lower_limit;
  bin.upper_limit = upper_limit;  

  TEST_FOR_EXCEPTION( 
    d_absolute_error_tol <= 0 && 
    (d_relative_error_tol < 50 * std::numeric_limits<double>::epsilon() ||
    d_relative_error_tol < 0.5e-28),
    Utility::IntegratorException,
    "tolerance cannot be acheived with given relative_error_tol and absolute_error_tol" );

  /* perform the first integration */

  double result_abs = 0.0;
  double result_asc = 0.0;

  integrateWithPointRule<Points>(
    integrand, 
    bin.lower_limit, 
    bin.upper_limit, 
    bin.result, 
    bin.error, 
    result_abs, 
    result_asc );

  bin_queue.push(bin);

  /* Test on accuracy */

  double tolerance =
    std::max(d_absolute_error_tol, d_relative_error_tol * fabs (bin.result));

  /* need IEEE rounding here to match original quadpack behavior */
  volatile double volatile_round_off; 
  volatile_round_off = 50.0*std::numeric_limits<double>::epsilon()*result_abs;
  double round_off = volatile_round_off;

  TEST_FOR_EXCEPTION( bin.error <= round_off && bin.error > tolerance, 
                      Utility::IntegratorException,
                      "cannot reach tolerance because of roundoff error "
                      "on first attempt" );

  if ( ( bin.error <= tolerance && bin.error != result_asc ) || 
            bin.error == 0.0)
    {
      result = bin.result;
      absolute_error = bin.error;    

      return;
    }


  TEST_FOR_EXCEPTION( d_subinterval_limit == 1, 
                      Utility::IntegratorException,
                      "a maximum of one iteration was insufficient" );

  double maximum_bin_error = bin.error;
  int bin_with_max_error = 0;
  double area = bin.result;
  double total_error = bin.error;
  int round_off_1 = 0.0;
  int round_off_2 = 0.0;
  int nr_max = 0;

  int last;
  for ( last = 1; last < d_subinterval_limit; last++ )
    {
      double area_12 = 0.0;
      double error_12 = 0.0;
      double result_asc_1 = 0.0, result_asc_2 = 0.0;
      double result_abs_1 = 0.0, result_abs_2 = 0.0;

      // Pop bin with highest error from queue
      bin = bin_queue.pop();

      // Bisect the bin with the largest error estimate into bin 1 and bin 2 
      BinTraits bin_1, bin_2;

      // Set bin_1
      bin_1.lower_limit = bin.lower_limit;
      bin_1.upper_limit = 0.5 * ( bin.lower_limit + bin.upper_limit );

      // Set bin 2
      bin_2.lower_limit = bin_1.upper_limit;
      bin_2.upper_limit = bin.upper_limit;

      integrateWithPointRule<Points>(
        integrand, 
        bin_1.lower_limit, 
        bin_1.upper_limit, 
        bin_1.result, 
        bin_1.error, 
        result_abs_1, 
        result_asc_1 );

      integrateWithPointRule<Points>(
        integrand, 
        bin_2.lower_limit, 
        bin_2.upper_limit, 
        bin_2.result, 
        bin_2.error, 
        result_abs_2, 
        result_asc_2 );

      /* Improve previous approximations to integral and error and 
         test for accuracy. */

      area_12 = bin_1.result + bin_2.result;
      error_12 = bin_1.error + bin_2.error;

      total_error += error_12 - bin.error;
      area += area_12 - bin.result;

      if (result_asc_1 != bin_1.error && result_asc_2 != bin_2.error)
        {
          double delta = bin.result - area_12;

          if ( fabs (delta) <= 1.0e-5 * fabs (area_12) && 
               error_12 >= 0.99 * bin.error )
            {
              round_off_1++;
            }
          if ( last >= 9 && error_12 > bin.error )
            {
              round_off_2++;
            }
        }

      bin_queue.push(bin_1);
      bin_queue.push(bin_2);

      tolerance = std::max( d_absolute_error_tol, d_relative_error_tol * fabs (area));

      if ( total_error <= tolerance )
        break;

      TEST_FOR_EXCEPTION( round_off_1 >= 6 || round_off_2 >= 20, 
                          Utility::IntegratorException,
                          "Roundoff error prevented tolerance from being achieved" );

      TEST_FOR_EXCEPTION( last+1 == d_subinterval_limit, 
                          Utility::IntegratorException,
                          "Maximum number of subdivisions reached" );

      TEST_FOR_EXCEPTION( subintervalTooSmall<Points>( bin_1.lower_limit, 
                                                       bin_2.lower_limit, 
                                                       bin_2.upper_limit ), 
                          Utility::IntegratorException,
                          "Maximum number of subdivisions reached" );

    }
  while ( !bin_queue.empty() )
    {
      bin = bin_queue.pop();
      result += bin.result;
    }

  absolute_error = total_error;
}


// Integrate a function with integrable singularities adaptively
/*! \details Functor must have operator()( double ) defined. This function
 * applies the Gauss-Kronrod 21-point integration rule adaptively until an
 * estimate of the integral of the integrand over [lower_limit,upper_limit]
 * is achieved within the desired tolerances. The results are extrapolated 
 * using the Wynn epsilon-algorithm, which accelerates the convergence of the 
 * integral in the presence of discontinuities and integrable singularities. 
 * See QAGS algorithm details in the GNU Scientific Library documentation.
 */ 
template<typename Functor>
void GaussKronrodIntegrator::integrateAdaptivelyWynnEpsilon( 
    Functor& integrand,
    double lower_limit,
    double upper_limit,
    double& result,
    double& absolute_error ) const
{/*
  Teuchos::Array<double> bin_result( d_subinterval_limit ); 
  Teuchos::Array<double> bin_error( d_subinterval_limit );
  Teuchos::Array<double> bin_lower_limit( d_subinterval_limit );
  Teuchos::Array<double> bin_upper_limit( d_subinterval_limit );
  Teuchos::Array<double> bin_order( d_subinterval_limit );
  Teuchos::Array<double> bin_extrapolated_result( 52 ); 

  int error_type;

  result = 0.0;
  bin_lower_limit[0] = lower_limit;
  bin_upper_limit[0] = upper_limit;  

  TEST_FOR_EXCEPTION( 
    d_absolute_error_tol <= 0 && 
    (d_relative_error_tol < 50 * std::numeric_limits<double>::epsilon() ||
    d_relative_error_tol < 0.5e-28),
    Utility::IntegratorException,
    "tolerance cannot be acheived with given relative_error_tol and absolute_error_tol" );

  // perform the first integration 

  double result_abs = 0.0;
  double result_asc = 0.0;

  integrateWithPointRule<21>(
    integrand, 
    lower_limit, 
    upper_limit, 
    bin_result[0], 
    bin_error[0], 
    result_abs, 
    result_asc );

  // Test on accuracy

  double fabs_result = fabs (bin_result[0]);
  double tolerance =
    std::max(d_absolute_error_tol, d_relative_error_tol * fabs_result);


  double round_off = std::numeric_limits<double>::epsilon()*result_abs;

  TEST_FOR_EXCEPTION( bin_error[0] <= 100.0*round_off && bin_error[0] > tolerance, 
                      Utility::IntegratorException,
                      "cannot reach tolerance because of roundoff error "
                      "on first attempt" );

  if ( ( bin_error[0] <= tolerance && bin_error[0] != result_asc ) || 
            bin_error[0] == 0.0)
    {
      result = bin_result[0];
      absolute_error = bin_error[0];    

      return;
    }


  TEST_FOR_EXCEPTION( d_subinterval_limit == 1, 
                      Utility::IntegratorException,
                      "a maximum of one iteration was insufficient" );

  double maximum_bin_error = bin_error[0];
  int bin_with_max_error = 0;
  double area = bin_result[0];
  double total_error = bin_error[0];
  double round_off_1 = 0.0;
  double round_off_2 = 0.0;
  double round_off_3 = 0.0;
  int nr_max = 0;

  int number_of_extrapolations = 0;
  int number_of_extrapolated_bins = 2;
  double ktmin = 0;
  bool extrapolate = false;
  bool no_extrapolation_allowed = false;
  int iroff1 = 0;
  int iroff2 = 0;
  int iroff3 = 0;

  int ksgn;
  if ( fabs_result >= 1.0 - 50.0*round_off )
  {
    ksgn = 1;
  }
  else
  {
    ksgn = -1;
  }

  int last;
  for ( last = 1; last < d_subinterval_limit; last++ )
    {
*/


}


// Integrate the function with given Gauss-Kronrod point rule
/*! \details Functor must have operator()( double ) defined. This function
 * applies the specified integration rule (Points) to estimate 
 * the integral of the integrand over [lower_limit,upper_limit]. 
 * Valid Gauss-Kronrod rules are 15, 21, 31, 41, 51 and 61. 
 * Higher-order rules give better accuracy for smooth functions, 
 * while lower-order rules save time when the function contains local 
 * difficulties, such as discontinuities. On each iteration
 * the adaptive integration strategy bisects the interval with the largest
 * error estimate. See the qag function details in the quadpack documentation.
 */ 
template<int Points, typename Functor>
void GaussKronrodIntegrator::integrateWithPointRule(
            Functor& integrand, 
            double lower_limit, 
            double upper_limit,
            double& result,
            double& absolute_error,
            double& result_abs, 
            double& result_asc ) const
{
  // Make sure the point rule is valid_rule
  testStaticPrecondition( GaussKronrodQuadratureSetTraits<Points>::valid_rule );
  // Make sure the integration limits are valid
  testPrecondition( lower_limit <= upper_limit );
  // Make sure the integration limits are bounded
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( lower_limit ) );
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( upper_limit ) );

  if( lower_limit < upper_limit )
  {
    // midpoint between upper and lower integration limits
    double midpoint = 0.5*( upper_limit + lower_limit );

    // half the length between the upper and lower integration limits
    double half_length = 0.5*(upper_limit - lower_limit );
    double abs_half_length = fabs( half_length );

    // Get number of Kronrod weights
    int number_of_weights =
        GaussKronrodQuadratureSetTraits<Points>::kronrod_weights.size();

    Teuchos::Array<double> integrand_values_lower( number_of_weights );
    Teuchos::Array<double> integrand_values_upper( number_of_weights );
    Teuchos::Array<double> integrand_values_sum( number_of_weights );
    Teuchos::Array<double> kronrod_values( number_of_weights );

    // Estimate Kronrod and absolute value integral for all but last weight
    double kronrod_result = 0.0;
    result_abs = kronrod_result;
    for ( int j = 0; j < number_of_weights-1; j++ )
      {  
        calculateQuadratureIntegrandValuesAtAbscissa( 
            integrand, 
            GaussKronrodQuadratureSetTraits<Points>::kronrod_abscissae[j],
            half_length,
            midpoint,
            integrand_values_lower[j],
            integrand_values_upper[j] );

        integrand_values_sum[j] = 
          integrand_values_lower[j] + integrand_values_upper[j];

        kronrod_result += 
            GaussKronrodQuadratureSetTraits<Points>::kronrod_weights[j]*integrand_values_sum[j];

        result_abs += GaussKronrodQuadratureSetTraits<Points>::kronrod_weights[j]*( 
          fabs( integrand_values_lower[j] ) + fabs( integrand_values_upper[j] ) );
      };

    // Integrand at the midpoint
    double integrand_midpoint = integrand( midpoint );

    // Estimate Kronrod integral for the last weight
    double kronrod_result_last_weight = integrand_midpoint*
        GaussKronrodQuadratureSetTraits<Points>::kronrod_weights[number_of_weights-1];

    // Update Kronrod estimate and absolute value with last weight
    kronrod_result += kronrod_result_last_weight;
    result_abs += fabs( kronrod_result_last_weight );

    // Calculate final integral result and absolute value
    result = kronrod_result*half_length;
    result_abs *= abs_half_length;

    // Calculate the mean kronrod result
    double mean_kronrod_result = 0.5*kronrod_result;

    // Estimate the result asc for all but the last weight
    result_asc = 0.0;
    for ( int j = 0; j < number_of_weights - 1; j++ )
      {  
        result_asc += GaussKronrodQuadratureSetTraits<Points>::kronrod_weights[j]*
          ( fabs( integrand_values_lower[j] - mean_kronrod_result ) +
            fabs( integrand_values_upper[j] - mean_kronrod_result ) );
      };

    // Estimate the result asc for the last weight
    result_asc += GaussKronrodQuadratureSetTraits<Points>::kronrod_weights[number_of_weights-1]*
        fabs( integrand_midpoint - mean_kronrod_result );

    // Calculate final result acx
    result_asc *= abs_half_length;

    // Estimate Gauss integral
    double gauss_result = 0.0;

    for ( int j = 0; j < (number_of_weights-1)/2; j++ )
      {
        int jj = j*2 + 1;
        gauss_result += integrand_values_sum[jj]*
            GaussKronrodQuadratureSetTraits<Points>::gauss_weights[j];
      };

    // Update Gauss estimate with last weight if needed
    if ( number_of_weights % 2 == 0 )
    {
      gauss_result += integrand_midpoint*
        GaussKronrodQuadratureSetTraits<Points>::gauss_weights[number_of_weights/2 - 1];
    }

    // Estimate error in integral 
    absolute_error = fabs( ( kronrod_result - gauss_result ) * half_length );
    rescaleAbsoluteError( absolute_error, result_abs, result_asc);

  }
  else if( lower_limit == upper_limit )
  {
    result = 0.0;
    absolute_error = 0.0;
  }
  else // invalid limits
  {
    THROW_EXCEPTION( Utility::IntegratorException,
		     "Invalid integration limits: " << lower_limit << " !< "
		     << upper_limit << "." );
  }
}

// Test if subinterval is too small
template<int Points>
inline bool GaussKronrodIntegrator::subintervalTooSmall( 
        double& lower_limit_1, 
        double& lower_limit_2, 
        double& upper_limit_2 ) const
{
  int c = Points/10;
  double max = std::max( fabs ( lower_limit_1 ), fabs ( upper_limit_2 ) );
  double epsilon = 1000.0*c*std::numeric_limits<double>::epsilon();
  double min = 10000.0*std::numeric_limits<double>::min();

  if ( max <= ( 1.0 + epsilon ) * ( fabs( lower_limit_2 ) + min ) )
    return true;
  else
    return false;
};

// Calculate the quadrature upper and lower integrand values at an abscissa
template<typename Functor>
void GaussKronrodIntegrator::calculateQuadratureIntegrandValuesAtAbscissa( 
    Functor& integrand, 
    double abscissa,
    double half_length,
    double midpoint,
    double& integrand_value_lower,
    double& integrand_value_upper ) const
{
  double weighted_abscissa = half_length*abscissa;

  integrand_value_lower = integrand( midpoint - weighted_abscissa );
  integrand_value_upper = integrand( midpoint + weighted_abscissa );
};  

} // end Utility namespace

#endif // end UTILITY_GAUSS_KRONROD_INTEGRATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodIntegrator_def.hpp
//---------------------------------------------------------------------------//
