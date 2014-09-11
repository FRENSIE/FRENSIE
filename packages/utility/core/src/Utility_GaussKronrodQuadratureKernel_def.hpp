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

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_ConstTypeTraits.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_GSLException.hpp"
#include "Utility_SortAlgorithms.hpp"

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
/*! \details Functor must have operator()( double ) defined. This function
 * applies the Gauss-Kronrod 10-point, 21-point, 43-points and 87-point
 * integration rules in succession until an estimate of the integrand over
 * [lower_limit,upper_limit] is achieved within the desired tolerances. See
 * the QNG algorithm details in the GNU Scientific Library documentation.
 */ 
template<typename Functor>
void GaussKronrodQuadratureKernel::integrate( 
				       Functor& integrand, 
				       double lower_limit, 
				       double upper_limit,
				       double& result,
				       double& absolute_error,
				       size_t& number_of_function_evals ) const
{
  // Make sure the integration limits are valid
  testPrecondition( lower_limit < upper_limit );
  // Make sure the integration limits are bounded
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( lower_limit ) );
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( upper_limit ) );
  
  // Create the GSL function
  gsl_function gsl_function_wrapper;
  gsl_function_wrapper.function = 
    &GaussKronrodQuadratureKernel::functorWrapper<Functor>;
  gsl_function_wrapper.params = const_cast<typename Teuchos::ConstTypeTraits<Functor>::NonConstType*>(&integrand);

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
void GaussKronrodQuadratureKernel::integrateAdaptively(
						 Functor& integrand, 
						 double lower_limit, 
						 double upper_limit,
						 double& result,
						 double& absolute_error ) const
{
  // Make sure the rule requested is valid
  testStaticPrecondition( AdaptiveQuadraturePointTraits<Points>::valid_rule );
  // Make sure the integration limits are valid
  testPrecondition( lower_limit <= upper_limit );
  // Make sure the integration limits are bounded
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( lower_limit ) );
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( upper_limit ) );

  if( lower_limit < upper_limit )
  {
    // Just-in-time workspace allocation
    gsl_integration_workspace* workspace = 
      gsl_integration_workspace_alloc( d_workspace_size );
    
    // Create the GSL function
    gsl_function gsl_function_wrapper;
    gsl_function_wrapper.function = 
      &GaussKronrodQuadratureKernel::functorWrapper<Functor>;
    gsl_function_wrapper.params = const_cast<typename Teuchos::ConstTypeTraits<Functor>::NonConstType*>(&integrand);
    
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

// Integrate the function over a semi-infinite interval (+infinity)
/*! \details Functor must have operator()( double ) defined. This function
 * computes the integral of the integrand over the semi-infinite interval
 * [lower_limit,+infinity). The integral is mapped onto the semi-open interval
 * (0,1] using the transformation x = a + (1-t)/t. Due to the possible
 * creation of an integrable singularity at the origin, the Wynn-epsilon
 * acceleration scheme is used. See the QAGI algorithm details in the GNU 
 * Scientific Library documentation.
 */ 
template<typename Functor>
void GaussKronrodQuadratureKernel::integrateSemiInfiniteIntervalUpper( 
				                 Functor& integrand, 
						 double lower_limit, 
						 double& result,
				                 double& absolute_error ) const
{
  // Make sure the lower integration limit is bounded
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( lower_limit ) );
  
  // Create the GSL function
  gsl_function gsl_function_wrapper;
  gsl_function_wrapper.function = 
    &GaussKronrodQuadratureKernel::functorWrapper<Functor>;
  gsl_function_wrapper.params = const_cast<typename Teuchos::ConstTypeTraits<Functor>::NonConstType*>(&integrand);

  // Just-in-time workspace allocation
  gsl_integration_workspace* workspace = 
    gsl_integration_workspace_alloc( d_workspace_size );

  // Integrate the function
  int status = gsl_integration_qagiu( &gsl_function_wrapper,
				      lower_limit,
				      d_absolute_error_tol,
				      d_relative_error_tol,
				      d_subinterval_limit,
				      workspace,
				      &result,
				      &absolute_error );

  // Deallocate workspace
  gsl_integration_workspace_free( workspace );

  // Verify success
  TEST_FOR_EXCEPTION( status != GSL_SUCCESS,
		      Utility::GSLException,
		      gsl_strerror( status ) );
}

// Integrate the function over a semi-infinite interval (-infinity)
/*! \details Functor must have operator()( double ) defined. This function
 * computes the integral of the integrand over the semi-infinite interval
 * (-infinity,upper_limit]. The integral is mapped onto the semi-open interval
 * (0,1] using the transformation x = b - (1-t)/t. Due to the possible
 * creation of an integrable singularity at the origin, the Wynn-epsilon
 * acceleration scheme is used. See the QAGI algorithm details in the GNU 
 * Scientific Library documentation.
 */ 
template<typename Functor>
void GaussKronrodQuadratureKernel::integrateSemiInfiniteIntervalLower( 
				                 Functor& integrand, 
						 double upper_limit, 
						 double& result,
				                 double& absolute_error ) const
{
  // Make sure the lower integration limit is bounded
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( upper_limit ) );
  
  // Create the GSL function
  gsl_function gsl_function_wrapper;
  gsl_function_wrapper.function = 
    &GaussKronrodQuadratureKernel::functorWrapper<Functor>;
  gsl_function_wrapper.params = const_cast<typename Teuchos::ConstTypeTraits<Functor>::NonConstType*>(&integrand);

  // Just-in-time workspace allocation
  gsl_integration_workspace* workspace = 
    gsl_integration_workspace_alloc( d_workspace_size );

  // Integrate the function
  int status = gsl_integration_qagil( &gsl_function_wrapper,
				      upper_limit,
				      d_absolute_error_tol,
				      d_relative_error_tol,
				      d_subinterval_limit,
				      workspace,
				      &result,
				      &absolute_error );

  // Deallocate workspace
  gsl_integration_workspace_free( workspace );

  // Verify success
  TEST_FOR_EXCEPTION( status != GSL_SUCCESS,
		      Utility::GSLException,
		      gsl_strerror( status ) );
}

// Integrate the function over an infinite interval (-infinity,+infinity)
/*! \details Functor must have operator()( double ) defined. This function
 * computes the integral of the integrand over the infinite interval
 * (-infinity,+infinity). The integral is mapped onto the semi-open interval
 * (0,1] using the transformation x = (1-t)/t. Due to the possible
 * creation of an integrable singularity at the origin, the Wynn-epsilon
 * acceleration scheme is used with a 15-point Gauss-Kronrod rule. See the
 * QAGI algorithm details in the GNU Scientific Library documentation.
 */ 
template<typename Functor>
void GaussKronrodQuadratureKernel::integrateInfiniteInterval( 
				                 Functor& integrand, 
						 double& result,
				                 double& absolute_error ) const
{
  // Create the GSL function
  gsl_function gsl_function_wrapper;
  gsl_function_wrapper.function = 
    &GaussKronrodQuadratureKernel::functorWrapper<Functor>;
  gsl_function_wrapper.params = const_cast<typename Teuchos::ConstTypeTraits<Functor>::NonConstType*>(&integrand);

  // Just-in-time workspace allocation
  gsl_integration_workspace* workspace = 
    gsl_integration_workspace_alloc( d_workspace_size );

  // Integrate the function
  int status = gsl_integration_qagi( &gsl_function_wrapper,
				     d_absolute_error_tol,
				     d_relative_error_tol,
				     d_subinterval_limit,
				     workspace,
				     &result,
				     &absolute_error );

  // Deallocate workspace
  gsl_integration_workspace_free( workspace );

  // Verify success
  TEST_FOR_EXCEPTION( status != GSL_SUCCESS,
		      Utility::GSLException,
		      gsl_strerror( status ) );
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
void GaussKronrodQuadratureKernel::integrateAdaptivelyWynnEpsilon(
						 Functor& integrand, 
						 double lower_limit, 
						 double upper_limit,
						 double& result,
						 double& absolute_error ) const
{
  // Make sure the integration limits are valid
  testPrecondition( lower_limit <= upper_limit );
  // Make sure the integration limits are bounded
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( lower_limit ) );
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( upper_limit ) );

  if( lower_limit < upper_limit )
  {
    // Just-in-time workspace allocation
    gsl_integration_workspace* workspace = 
      gsl_integration_workspace_alloc( d_workspace_size );
    
    // Create the GSL function
    gsl_function gsl_function_wrapper;
    gsl_function_wrapper.function = 
      &GaussKronrodQuadratureKernel::functorWrapper<Functor>;
    gsl_function_wrapper.params = const_cast<typename Teuchos::ConstTypeTraits<Functor>::NonConstType*>(&integrand);
    
    int status = gsl_integration_qags( &gsl_function_wrapper,
				       lower_limit,
				       upper_limit,
				       d_absolute_error_tol,
				       d_relative_error_tol,
				       d_subinterval_limit,
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

// Integrate a funtion with known integrable singularities adaptively
/*! \details Functor must have operator()( double ) defined. The 
 * points-of-interest array must have the in integration limits (first and
 * last array elements), and each singular point. The array must also be 
 * sorted (ascending order). This function applies the Gauss-Kronrod 21-point 
 * integration rule adaptively until an estimate of the integral of the
 * integrand over [lower_limit,upper_limit] is achieved within the desired 
 * tolerances. The results are extrapolated using the Wynn epsilon-algorithm, 
 * which accelerates the convergence of the integral in the presence of 
 * discontinuities and integrable singularities. This algorithm is also 
 * accelerated by using the user supplied singular points. See QAGP algorithm 
 * details in GNU Scientific Library documentation.
 */ 
template<typename Functor>
void GaussKronrodQuadratureKernel::integrateAdaptivelyWynnEpsilon(
			  Functor& integrand, 
			  const Teuchos::ArrayView<double>& points_of_interest,
			  double& result,
			  double& absolute_error ) const
{
  // Make sure the points-of-interest array is valid
  testPrecondition( Sort::isSortedAscending( points_of_interest.begin(),
					     points_of_interest.end() ) );
  testPrecondition( points_of_interest.size() >= 2 );
  // Make sure the integration limits are bounded
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( 
						points_of_interest.front() ) );
  testPrecondition( !Teuchos::ScalarTraits<double>::isnaninf( 
						 points_of_interest.back() ) );

  if( points_of_interest.front() < points_of_interest.back() )
  {
    // Just-in-time workspace allocation
    gsl_integration_workspace* workspace = 
      gsl_integration_workspace_alloc( d_workspace_size );
    
    // Create the GSL function
    gsl_function gsl_function_wrapper;
    gsl_function_wrapper.function = 
      &GaussKronrodQuadratureKernel::functorWrapper<Functor>;
    gsl_function_wrapper.params = const_cast<typename Teuchos::ConstTypeTraits<Functor>::NonConstType*>(&integrand);
    
    int status = gsl_integration_qagp( &gsl_function_wrapper,
				       points_of_interest.getRawPtr(),
				       points_of_interest.size(),
				       d_absolute_error_tol,
				       d_relative_error_tol,
				       d_subinterval_limit,
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
  else if( points_of_interest.front() == points_of_interest.back() )
  {
    result = 0.0;
    absolute_error = 0.0;
  }
  else // invalid limits
  {
    THROW_EXCEPTION( Utility::GSLException,
		     "Invalid integration limits: " 
		     << points_of_interest.front() << " !< "
		     << points_of_interest.back() << "." );
  }
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodQuadratureKernel_def.hpp
//---------------------------------------------------------------------------//
