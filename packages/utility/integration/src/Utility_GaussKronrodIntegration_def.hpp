//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodIntegration_def.hpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod integration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_KRONROD_INTEGRATION_DEF_HPP
#define UTILITY_GAUSS_KRONROD_INTEGRATION_DEF_HPP

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
#include "Utility_GSLException.hpp"
#include "Utility_SortAlgorithms.hpp"

namespace Utility{

// Function wrapper for evaluating the functor
template<typename Functor>
double GaussKronrodIntegration::functorWrapper( const double x, 
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
 * error estimate. See the QAG algorithm details in the GNU Scientific
 * Library documentation.
 */ 
template<int Points, typename Functor>
void GaussKronrodIntegration::integrateAdaptively(
						 Functor& integrand, 
						 double lower_limit, 
						 double upper_limit,
						 double& result,
						 double& absolute_error ) const
{
  // Make sure the rule requested is valid
  testPrecondition( Points == 15 );
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

    // Integrand at the midpoint
    double integrand_midpoint = integrand( midpoint );

    // Estimate result for 7 point Gauss
    double gauss_result = integrand_midpoint*gauss_weights_7[3];

    // Estimate result for 15 point Kronrod
    double kronrod_result = integrand_midpoint*kronrod_weights_15[7];
 
    // Absolute value of 15 point estimate
    double result_abs = fabs( kronrod_result );

    Teuchos::Array<double> integrand_values_lower( 7 );
    Teuchos::Array<double> integrand_values_upper( 7 );
    Teuchos::Array<double> integrand_values_sum( 7 );

    // Estimate Kronrod and absolute value integral
    for ( int j = 0; j < 7; j++ )
      {  
        calculateQuadratureIntegrandValuesAtAbscissa( 
            integrand, 
            kronrod_abscissae_15[j],
            half_length,
            midpoint,
            integrand_values_lower[j],
            integrand_values_upper[j] );

        kronrod_result += kronrod_weights_15[j]*integrand_values_sum[j];

        integrand_values_sum[j] = 
          integrand_values_lower[j] + integrand_values_upper[j];

        result_abs += kronrod_weights_15[j]*( 
          fabs( integrand_values_lower[j] ) + fabs( integrand_values_upper[j] ) );
      };

    double mean_kronrod_result = 0.5*kronrod_result;
    double result_asc = kronrod_weights_15[7]*
        fabs( integrand_midpoint - mean_kronrod_result );

    for ( int j = 0; j < 7; j++ )
      {  

        result_asc += kronrod_weights_15[j]*
          ( fabs( integrand_values_lower[j] - mean_kronrod_result ) +
            fabs( integrand_values_upper[j] - mean_kronrod_result ) );
      };

    // Estimate Gauss integral
    for ( int j = 0; j < 3; j++ )
      {
        int jj = j*2 + 1;
        gauss_result += gauss_weights_7[j]*integrand_values_sum[jj];
      };

  double abs_half_length = fabs( half_length );
  result = kronrod_result*half_length;
  result_abs *= abs_half_length;
  result_asc *= abs_half_length;
  absolute_error = fabs( ( kronrod_result - gauss_result ) * half_length );

  normalizeAbsoluteError( absolute_error, result_abs, result_asc );
         


  }
  else if( lower_limit == upper_limit )
  {
    result = 0.0;
    absolute_error = 0.0;
  }
  else // invalid limits
  {
    THROW_EXCEPTION( Utility::GSLException,
		     "Invalid integration limits: " << lower_limit << " !< "
		     << upper_limit << "." );
  }
}

// Calculate the quadrature upper and lower integrand values at an abscissa
template<typename Functor>
void GaussKronrodIntegration::calculateQuadratureIntegrandValuesAtAbscissa( 
    Functor& integrand, 
    double abscissa,
    double half_length,
    double midpoint,
    double& integrand_value_lower,
    double& integrand_value_upper ) const
{
  double weighted_abscissa = half_length*abscissa;

  integrand_value_lower = integrand( midpoint - abscissa );
  integrand_value_upper = integrand( midpoint + abscissa );
};  

} // end Utility namespace

#endif // end UTILITY_GAUSS_KRONROD_INTEGRATION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodIntegration_def.hpp
//---------------------------------------------------------------------------//
