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
void GaussKronrodIntegrator::integrateAdaptively(
						 Functor& integrand, 
						 double lower_limit, 
						 double upper_limit,
						 double& result,
						 double& absolute_error ) const
{
  BinTraits bin;
  BinQueue bin_queue;

  result = 0.0;
  bin.lower_limit = lower_limit;
  bin.upper_limit = upper_limit;  

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

  long double area = bin.result;
  absolute_error = bin.error;
  int round_off_1 = 0.0;
  int round_off_2 = 0.0;

  int last;
  for ( last = 1; last < d_subinterval_limit; last++ )
  {
    long double area_12 = 0.0;
    double error_12 = 0.0;
    double result_asc_1 = 0.0, result_asc_2 = 0.0;
    BinTraits bin_1, bin_2;

    // Pop bin with highest error from queue
    bin = bin_queue.top();
    bin_queue.pop();

    bisectAndIntegrateBinInterval<Points>( 
      integrand, 
      bin,
      bin_1,
      bin_2,
      result_asc_1,
      result_asc_2 );

    bin_queue.push(bin_1);
    bin_queue.push(bin_2);

    // Improve previous approximations to integral and error and test for accuracy
    absolute_error += bin_1.error + bin_2.error - bin.error;
    area += bin_1.result + bin_2.result - bin.result;

    // Check that the roundoff error is not too high
    checkRoundoffError( bin, 
                        bin_1, 
                        bin_2,    
                        result_asc_1,
                        result_asc_2,
                        round_off_1,
                        round_off_2,
                        last+1 );

    tolerance = 
      std::max( d_absolute_error_tol, d_relative_error_tol * fabs (area));

    if ( absolute_error <= tolerance )
      break;

    TEST_FOR_EXCEPTION( last+1 == d_subinterval_limit, 
                        Utility::IntegratorException,
                        "Maximum number of subdivisions reached" );

    TEST_FOR_EXCEPTION( subintervalTooSmall<Points>( bin_1.lower_limit, 
                                                     bin_2.lower_limit, 
                                                     bin_2.upper_limit ), 
                        Utility::IntegratorException,
                        "Maximum number of subdivisions reached" );

  }

  result = area;
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
    const Teuchos::ArrayView<double>& points_of_interest,
    double& result,
    double& absolute_error ) const
{
  // Check that the points of interest are in ascending order
  testPrecondition( Sort::isSortedAscending( points_of_interest.begin(),
                                             points_of_interest.end(),
                                             true ) );
  // check that the number of points don't excees the subinterval limit
  testPrecondition( points_of_interest.size() < d_subinterval_limit );
  // check that there are at least two points
  testPrecondition( points_of_interest.size() > 1 );

  ExtrpolatedBinTraits bin;
  BinArray bin_array( d_subinterval_limit );
  
  Teuchos::Array<double> bin_extrapolated_result( 52 ); 
  Teuchos::Array<double> last_three_results( 3 ); 
  long double total_area = 0.0L;
  double total_error = 0.0, total_area_abs = 0.0;  

  int number_of_intervals = points_of_interest.size() - 1;
  Teuchos::Array<bool> rescale_bin_error( number_of_intervals );

  absolute_error = 0.0;
  // Compute the integration between the points of interest
  for ( int i = 0; i < number_of_intervals; i++ )
  {
    bin.lower_limit = points_of_interest[i];
    bin.upper_limit = points_of_interest[i+1];  

    double result_abs = 0.0;
    double result_asc = 0.0;

    integrateWithPointRule<21>(
        integrand, 
        bin.lower_limit, 
        bin.upper_limit, 
        bin.result, 
        bin.error, 
        result_abs, 
        result_asc );

    bin.level = 0;
    bin_array[i] = bin;
    total_area += bin.result;
    absolute_error += bin.error;
    total_area_abs += result_abs;

    if ( bin.error == result_asc && bin.error != 0.0 )
    {
      rescale_bin_error[i] = true;
    }
    else
    {
      rescale_bin_error[i] = false;
    }
  }
  // initialize bin_order array
  Teuchos::Array<int> bin_order( number_of_intervals );

  // Compute error approximations for integrals between the points of interest
  for ( int i = 0; i < number_of_intervals; i++ )
  {
    if ( rescale_bin_error[i] ) 
      bin_array[i].error = absolute_error;

    total_error += bin_array[i].error;

    bin_order[i] = i;
  }

  // Test on accuracy

  double fabs_total_area = fabs (total_area);
  double tolerance =
    std::max(d_absolute_error_tol, d_relative_error_tol * fabs_total_area);


  double round_off = std::numeric_limits<double>::epsilon()*total_area_abs;

  TEST_FOR_EXCEPTION( absolute_error <= 100.0*round_off && absolute_error > tolerance, 
                      Utility::IntegratorException,
                      "cannot reach tolerance because of roundoff error "
                      "on first attempt" );

  if ( absolute_error <= tolerance )
    {
      result = total_area;

      return;
    }

  // sort bins from greatest to lowest error
  std::sort( bin_array.rend()-number_of_intervals, bin_array.rend() );

  TEST_FOR_EXCEPTION( d_subinterval_limit == 1, 
                      Utility::IntegratorException,
                      "a maximum of one iteration was insufficient" );

  // initialize
  bin_extrapolated_result[0] = total_area;
  absolute_error = std::numeric_limits<double>::max();
  int nr_max = 0;
  int number_of_extrapolated_calls = 0;
  int number_of_extrapolated_intervals = 0;
  int ktmin = 0;
  bool extrapolate = false;
  bool no_extrapolation_allowed = false;
  bool bad_integration_behavior = false;
  double error_over_large_bins = total_error;
  double extrapolated_tolerance = tolerance;
  int max_level = 1;
  int round_off_1 = 0;
  int round_off_2 = 0;
  int round_off_3 = 0;
  int ierro = 0;
 

  double error_correction = 0.0;

  int ksgn;
  if ( fabs_total_area >= 1.0 - 50.0*round_off )
  {
    ksgn = 1;
  }
  else
  {
    ksgn = -1;
  }

  //number_of_intervals++;
  for ( number_of_intervals; number_of_intervals < d_subinterval_limit; number_of_intervals++ )
  {
    double area_12 = 0.0, error_12 = 0.0;
    double result_asc_1 = 0.0, result_asc_2 = 0.0;
    double smallest_bin_size = 0.0; // 1.5*smallest bin size 

    ExtrpolatedBinTraits bin_1, bin_2;

    // Set bin to interval with largest error
    bin = bin_array[bin_order[nr_max]];

    bisectAndIntegrateBinInterval<21>( 
      integrand, 
      bin,
      bin_1,
      bin_2,
      result_asc_1,
      result_asc_2 );

    bin_1.level = bin.level + 1;
    bin_2.level = bin.level + 1;

    // Improve previous approximations to integral and error and test for accuracy
    total_error += bin_1.error + bin_2.error - bin.error;
    total_area += bin_1.result + bin_2.result - bin.result;

    // Check that the roundoff error is not too high
    checkRoundoffError( bin, 
                        bin_1, 
                        bin_2,    
                        result_asc_1,
                        result_asc_2,
                        round_off_1,
                        round_off_2,
                        round_off_3,
                        extrapolate,
                        number_of_intervals );

    // Update and sort bin order
    sortBins( bin_order, 
              bin_array,
              bin_1,
              bin_2,
              number_of_intervals,
              nr_max );

    tolerance = 
      std::max( d_absolute_error_tol, d_relative_error_tol * fabs (total_area));

    if ( total_error <= tolerance )
      break;

    TEST_FOR_EXCEPTION( number_of_intervals+1 == d_subinterval_limit, 
                        Utility::IntegratorException,
                        "Maximum number of subdivisions reached" );

    TEST_FOR_EXCEPTION( subintervalTooSmall<21>( bin_1.lower_limit, 
                                                 bin_2.lower_limit, 
                                                 bin_2.upper_limit ), 
                        Utility::IntegratorException,
                        "Maximum number of subdivisions reached" );

    if ( round_off_2 >= 5 )
    {
      bad_integration_behavior = true;
    }

    if ( no_extrapolation_allowed )
      continue; // go to next for loop iteration without extrapolating

    error_over_large_bins -= bin.error;

    if ( bin_1.level + 1 <= max_level )
    {
      error_over_large_bins += error_12;
    }

    bin = bin_array[bin_order[nr_max]];
    // Test whether the interval to be bisected next is the smallest interval
    if ( !extrapolate )
    {
      if ( bin.level + 1 <= max_level )
        continue; // go to next for loop iteration without extrapolating

      extrapolate = true;
      nr_max = 1; 
    }

    if ( bad_integration_behavior != true && 
         error_over_large_bins > extrapolated_tolerance )
    {
      int id = nr_max;
      int size = number_of_intervals;

      if ( number_of_intervals >  2 + d_subinterval_limit/2 )
        size = d_subinterval_limit + 3 - number_of_intervals;

      bool still_have_large_bins = false;
      for ( int k = id; k < size; k++ )
      {
        bin = bin_array[bin_order[nr_max]];
        if ( bin.level + 1 <= max_level )
        {
          still_have_large_bins = true;
          continue;
        }   
        nr_max++;    
      }
    
      if ( still_have_large_bins )
        continue;
    }

    // Perform extrapolation
    double extrapolated_result = 0.0;
    double extrapolated_error = 0.0;
    

    number_of_extrapolated_intervals++;
    bin_extrapolated_result[number_of_extrapolated_intervals] = total_area;

    if ( number_of_extrapolated_intervals < 2 )
    {
      nr_max = 0;
      extrapolate = false;
      max_level++;
      error_over_large_bins = total_error;
      continue;
    }

    getWynnEpsilonAlgorithmExtrapolation( 
        bin_extrapolated_result,
        last_three_results,
        extrapolated_result, 
        extrapolated_error,  
        number_of_extrapolated_intervals,
        number_of_extrapolated_calls );

    ktmin++;

    TEST_FOR_EXCEPTION( ktmin > 5 && absolute_error < 1.0E-03 * total_error, 
                        Utility::IntegratorException,
                        "The integral is probably divergent, or slowly convergent." );

    if ( extrapolated_error < absolute_error )
    {
      ktmin = 0;
      absolute_error = extrapolated_error;
      result = extrapolated_result;
      error_correction = error_over_large_bins;
      extrapolated_tolerance = 
        std::max( d_absolute_error_tol, 
                  d_relative_error_tol*fabs( extrapolated_result ) ); 

      if ( absolute_error <= extrapolated_tolerance )
        break;
    }

    // Prepare bisection of the smallest interval.
    if ( number_of_extrapolated_intervals == 0 )
      no_extrapolation_allowed = true;

    nr_max = 0;
    extrapolate = false;
    max_level++;
    error_over_large_bins = total_error;
  } // end main for loop

  //  Set final result and error estimate.

  if ( absolute_error == std::numeric_limits<double>::max() )
  {
    //  Compute global integral sum.
   
    long double long_result = 0.0L;
    Teuchos::Array<int>::reverse_iterator j =  bin_order.rbegin();
    // Sum result over all bins
    for ( j; j != bin_order.rend(); j++ )
    {
      bin = bin_array[*j];
      long_result += bin.result;
    }
    result = long_result;
    absolute_error = total_error;

    
    return;
  }

  if ( bad_integration_behavior ) 
  {
    absolute_error += error_correction;

    TEST_FOR_EXCEPTION( bad_integration_behavior, 
                        Utility::IntegratorException,
                        "extremely bad integrand behavior occurs at some "
                        "points of the integration interval." );

  }



  // Test on divergence.
  if ( ksgn == (-1) && 
       std::max( fabs(result), fabs(total_area) ) <= total_area_abs*1.0E-02 )
  {
    return;
  }

  TEST_FOR_EXCEPTION( 1.0E-02 > result/total_area ||
                      result/total_area > 1.0E+02 ||
                      total_error > fabs( total_area ), 
                      Utility::IntegratorException,
                      "the input is invalid, because d_absolute_error_tol < 0 "
                      "and d_relative_error_tol < 0, result, absolute_error "
                      "are set to zero." );

  return;
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
            long double& result,
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
    long double half_length = 0.5*(upper_limit - lower_limit );
    double abs_half_length = fabs( half_length );

    // Get number of Kronrod weights
    int number_of_weights =
        GaussKronrodQuadratureSetTraits<Points>::kronrod_weights.size();

    Teuchos::Array<double> integrand_values_lower( number_of_weights );
    Teuchos::Array<double> integrand_values_upper( number_of_weights );
    Teuchos::Array<double> integrand_values_sum( number_of_weights );
    Teuchos::Array<double> kronrod_values( number_of_weights );

    // Estimate Kronrod and absolute value integral for all but last weight
    long double kronrod_result = 0.0L;
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
    long double kronrod_result_last_weight = integrand_midpoint*
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
    long double gauss_result = 0.0L;

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


// Bisect and integrate the given bin interval
template<int Points, typename Functor, typename Bin>
void GaussKronrodIntegrator::bisectAndIntegrateBinInterval( 
    Functor& integrand, 
    const Bin& bin,
    Bin& bin_1,
    Bin& bin_2,
    double& bin_1_asc,
    double& bin_2_asc ) const
{
    // Bisect the bin with the largest error estimate into bin 1 and bin 2 

    // Set bin_1
    bin_1.lower_limit = bin.lower_limit;
    bin_1.upper_limit = 0.5 * ( bin.lower_limit + bin.upper_limit );

    // Set bin 2
    bin_2.lower_limit = bin_1.upper_limit;
    bin_2.upper_limit = bin.upper_limit;

    double bin_1_abs, bin_2_abs;
    // Integrate over bin 1
    integrateWithPointRule<Points>(
      integrand, 
      bin_1.lower_limit, 
      bin_1.upper_limit, 
      bin_1.result, 
      bin_1.error, 
      bin_1_abs, 
      bin_1_asc );

    // Integrate over bin 2
    integrateWithPointRule<Points>(
      integrand, 
      bin_2.lower_limit, 
      bin_2.upper_limit, 
      bin_2.result, 
      bin_2.error, 
      bin_2_abs, 
      bin_2_asc );
};

} // end Utility namespace

#endif // end UTILITY_GAUSS_KRONROD_INTEGRATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodIntegrator_def.hpp
//---------------------------------------------------------------------------//
