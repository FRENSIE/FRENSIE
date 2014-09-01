//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodQuadratureKernel_def.hpp
//! \author Alex Robinson
//! \brief  Gauss-Kronrod quadrature kernel
//!
//---------------------------------------------------------------------------//

// GSL Includes
#include <gsl/gsl_errno.h>

// Boost Includes
#include <boost/mem_fn.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_GSLException.hpp"

namespace Utility{

// AdaptiveQuadraturePointTraits specialization for 15-point rule
template<>
struct GaussKronrodQuadratureKernel::AdaptiveQuadraturePointTraits<15>
{
  //! Valid rule
  static const bool valid_rule = true;
  
  //! The Gauss-Kronrod rule GSL key
  static const int rule_key = 1;
};
  
// AdaptiveQuadraturePointTraits specialization for 21-point rule
template<>
struct GaussKronrodQuadratureKernel::AdaptiveQuadraturePointTraits<21>
{
  //! Valid rule
  static const bool valid_rule = true;
  
  //! The Gauss-Kronrod rule GSL key
  static const int rule_key = 2;
};

// AdaptiveQuadraturePointTraits specialization for 31-point rule
template<>
struct GaussKronrodQuadratureKernel::AdaptiveQuadraturePointTraits<31>
{
  //! Valid rule
  static const bool valid_rule = true;
  
  //! The Gauss-Kronrod rule GSL key
  static const int rule_key = 3;
};

// AdaptiveQuadraturePointTraits specialization for 41-point rule
template<>
struct GaussKronrodQuadratureKernel::AdaptiveQuadraturePointTraits<41>
{
  //! Valid rule
  static const bool valid_rule = true;
  
  //! The Gauss-Kronrod rule GSL key
  static const int rule_key = 4;
};

// AdaptiveQuadraturePointTraits specialization for 51-point rule
template<>
struct GaussKronrodQuadratureKernel::AdaptiveQuadraturePointTraits<51>
{
  //! Valid rule
  static const bool valid_rule = true;
  
  //! The Gauss-Kronrod rule GSL key
  static const int rule_key = 5;
};

// AdaptiveQuadraturePointTraits specialization for 61-point rule 
template<>
struct GaussKronrodQuadratureKernel::AdaptiveQuadraturePointTraits<61>
{
  //! Valid rule
  static const bool valid_rule = true;
  
  //! The Gauss-Kronrod rule GSL key
  static const int rule_key = 6;
};

// Function wrapper for evaluating the functor
template<typename Functor>
double GaussKronrodQuadratureKernel::functorWrapper( const double x, 
						     void* indirected_functor )
{
  // Make sure the functor is valid
  testPrecondition( indirected_functor );

  Functor* functor = (Functor*)( indirected_functor );

  return (*functor)( x );
}

// Integrate the function
/*! \details Functor must have operator()( double ) defined
 */ 
template<typename Functor>
void GaussKronrodQuadratureKernel::integrate( 
				       Functor integrand, 
				       double lower_limit, 
				       double upper_limit,
				       double& result,
				       double& absolute_error,
				       size_t& number_of_function_evals ) const
{
  // Make sure the integration limits are valid
  testPrecondition( lower_limit < upper_limit );
  
  // Create the GSL function
  gsl_function gsl_function_wrapper;
  gsl_function_wrapper.function = 
    &GaussKronrodQuadratureKernel::functorWrapper<Functor>;
  gsl_function_wrapper.params = &integrand;

  // Integrate the function
  int status = gsl_integration_qng( &gsl_function_wrapper,
				    lower_limit,
				    upper_limit,
				    d_absolute_error_tol,
				    d_relative_error_tol,
				    &result,
				    &absolute_error,
				    &number_of_function_evals );

  // Verify success
  TEST_FOR_EXCEPTION( status != GSL_SUCCESS,
		      Utility::GSLException,
		      gsl_strerror( status ) );
}

// Integrate the function adaptively
/*! \details Functor must have operator()( double ) defined
 */ 
template<int Points, typename Functor>
void GaussKronrodQuadratureKernel::integrateAdaptively(
						 Functor integrand, 
						 double lower_limit, 
						 double upper_limit,
						 double& result,
						 double& absolute_error ) const
{
  // Make sure the rule requested is valid
  testStaticPrecondition( AdaptiveQuadraturePointTraits<Points>::valid_rule );
  // Make sure the integration limits are valid
  testPrecondition( lower_limit < upper_limit );

  // Just-in-time workspace allocation
  gsl_integration_workspace* workspace = 
    gsl_integration_workspace_alloc( d_workspace_size );
  
  // Create the GSL function
  gsl_function gsl_function_wrapper;
  gsl_function_wrapper.function = 
    &GaussKronrodQuadratureKernel::functorWrapper<Functor>;
  gsl_function_wrapper.params = &integrand;

  int status = gsl_integration_qag( 
			       &gsl_function_wrapper,
			       lower_limit,
			       upper_limit,
			       d_absolute_error_tol,
			       d_relative_error_tol,
			       d_subinterval_limit,
			       AdaptiveQuadraturePointTraits<Points>::rule_key,
			       workspace,
			       &result,
			       &absolute_error );

  // Verify success
  TEST_FOR_EXCEPTION( status != GSL_SUCCESS,
		      Utility::GSLException,
		      gsl_strerror( status ) );

  // Deallocate workspace
  gsl_integration_workspace_free( workspace );
}					

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodQuadratureKernel_def.hpp
//---------------------------------------------------------------------------//
