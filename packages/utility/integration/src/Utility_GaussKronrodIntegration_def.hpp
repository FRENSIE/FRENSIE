//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodIntegration_def.hpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod integration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_KRONROD_INTEGRATION_DEF_HPP
#define UTILITY_GAUSS_KRONROD_INTEGRATION_DEF_HPP

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

} // end Utility namespace

#endif // end UTILITY_GAUSS_KRONROD_INTEGRATION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodIntegration_def.hpp
//---------------------------------------------------------------------------//
