//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodQuadratureKernel.hpp
//! \author Alex Robinson
//! \brief  Gauss-Kronrod quadrature kernel
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_KRONROD_QUADRATURE_KERNEL
#define UTILITY_GAUSS_KRONROD_QUADRATURE_KERNEL

// GSL Includes
#include <gsl/gsl_integration.h>

namespace Utility{

//! The Gauss-Kronrod quadrature kernel
class GaussKronrodQuadratureKernel
{

public:
  
  //! Constructor
  GaussKronrodQuadratureKernel( const double relative_error_tol,
				const double absolute_error_tol = 0.0,
				const size_t subinterval_limit = 1000,
				const size_t work_space_size = 1000 );

  //! Destructor
  ~GaussKronrodQuadratureKernel();

  //! Integrate the function
  template<typename Functor>
  void integrate( Functor integrand, 
		  double lower_limit, 
		  double upper_limit,
		  double& result,
		  double& absolute_error,
		  size_t& number_of_function_evals ) const;

  //! Integrate the function adaptively
  template<int Points, typename Functor>
  void integrateAdaptively( Functor integrand,
			    double lower_limit,
			    double upper_limit,
			    double& result,
			    double& absolute_error ) const;

private:

  // AdaptiveQuadraturePointTraits declaration
  template<int Points>
  struct AdaptiveQuadraturePointTraits
  {
    //! Valid rule
    static const bool valid_rule = false;
    
    //! The Adaptive Guass-Kronrod rule GSL key
    static const int rule_key = 0;
  };

  // Function wrapper for evaluating the functor
  template<typename Functor>
  static double functorWrapper( const double x, void* indirected_functor );

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

#include "Utility_GaussKronrodQuadratureKernel_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_GUASS_KRONROD_QUADRATURE_KERNEL

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodQuadratureKernel.hpp
//---------------------------------------------------------------------------//
