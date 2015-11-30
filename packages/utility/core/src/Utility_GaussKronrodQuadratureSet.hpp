//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodQuadratureSet.hpp
//! \author Alex Robinson
//! \brief  Gauss-Kronrod quadrature gkq_set
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_KRONROD_QUADRATURE_KERNEL_HPP
#define UTILITY_GAUSS_KRONROD_QUADRATURE_KERNEL_HPP

// GSL Includes
#include <gsl/gsl_integration.h>
#include <gsl/gsl_errno.h>


// Trilinos Includes
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_Array.hpp>

namespace Utility{

//! The Gauss-Kronrod quadrature gkq_set
class GaussKronrodQuadratureSet
{

public:

  //! Allow the gkq_set to throw exceptions (default is no)
  static void throwExceptions( const bool allow_throw );
  
  
  //! Constructor
  GaussKronrodQuadratureSet( const double relative_error_tol,
				const double absolute_error_tol = 0.0,
				const size_t subinterval_limit = 1000,
				const size_t work_space_size = 1000 );

  //! Destructor
  ~GaussKronrodQuadratureSet();

  //! Integrate the function
  template<typename Functor>
  void integrate( Functor& integrand, 
		  double lower_limit, 
		  double upper_limit,
		  double& result,
		  double& absolute_error,
		  size_t& number_of_function_evals ) const;

  //! Integrate the function adaptively
  template<int Points, typename Functor>
  void integrateAdaptively( Functor& integrand,
			    double lower_limit,
			    double upper_limit,
			    double& result,
			    double& absolute_error ) const;

  //! Integrate the function over a semi-infinite interval (+infinity)
  template<typename Functor>
  void integrateSemiInfiniteIntervalUpper( Functor& integrand,
					   double lower_limit,
					   double& result,
					   double& absolute_error ) const;

  //! Integrate the function over a semi-infinite interval (-infinity)
  template<typename Functor>
  void integrateSemiInfiniteIntervalLower( Functor& integrand,
					   double upper_limit,
					   double& result,
					   double& absolute_error ) const;

  //! Integrate the function over an infinite interval (-infinity,+infinity)
  template<typename Functor>
  void integrateInfiniteInterval( Functor& integrand,
				  double& result,
				  double& absolute_error ) const;

  //! Integrate a function with integrable singularities adaptively
  template<typename Functor>
  void integrateAdaptivelyWynnEpsilon( Functor& integrand,
				       double lower_limit,
				       double upper_limit,
				       double& result,
				       double& absolute_error ) const;

  //! Integrate a function with known integrable singularities adaptively
  template<typename Functor>
  void integrateAdaptivelyWynnEpsilon( 
			  Functor& integrand,
			  const Teuchos::ArrayView<double>& points_of_interest,
			  double& result,
			  double& absolute_error ) const;

  //! Integrate a function with Gauss-Legendre integration
  template<typename Functor>
  void integrateGaussLegendre(
			  Functor& integrand, 
			  double lower_limit, 
			  double upper_limit,
			  Teuchos::Array<double>& points,
			  Teuchos::Array<double>& weights,
			  double& result ) const;

private:

  // AdaptiveQuadraturePointTraits declaration
  template<int Points>
  struct AdaptiveQuadraturePointTraits
  {
    //! Valid rule
    static const bool valid_rule = false;
    
    //! The Adaptive Gauss-Kronrod rule GSL key
    static const int rule_key = 0;
  };

  // Function wrapper for evaluating the functor
  template<typename Functor>
  static double functorWrapper( const double x, void* indirected_functor );

  // The default gsl error handler
  static gsl_error_handler_t* default_gsl_error_handler;

  // The relative error tolerance
  double d_relative_error_tol;

  // The absolute error tolerance
  double d_absolute_error_tol;

  // The subinterval limit
  size_t d_subinterval_limit;

  // The work array
  size_t d_workspace_size;
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_GaussKronrodQuadratureSet_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_GAUSS_KRONROD_QUADRATURE_KERNEL_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodQuadratureSet.hpp
//---------------------------------------------------------------------------//
