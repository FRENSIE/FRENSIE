//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodIntegration.hpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod integration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_KRONROD_INTEGRATION_HPP
#define UTILITY_GAUSS_KRONROD_INTEGRATION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

namespace Utility{

//! The Gauss-Kronrod integration
class GaussKronrodIntegration
{

public:

  //! Constructor
  GaussKronrodIntegration( const double relative_error_tol,
                           const double absolute_error_tol = 0.0,
                           const size_t subinterval_limit = 1000,
                           const size_t work_space_size = 1000 );

  //! Destructor
  ~GaussKronrodIntegration();
/*
  //! Integrate the function
  template<typename Functor>
  void integrate( Functor& integrand, 
		  double lower_limit, 
		  double upper_limit,
		  double& result,
		  double& absolute_error,
		  size_t& number_of_function_evals ) const;
*/
  //! Integrate the function adaptively
  template<int Points, typename Functor>
  void integrateAdaptively( Functor& integrand,
			    double lower_limit,
			    double upper_limit,
			    double& result,
			    double& absolute_error ) const;

  //! Integrate the function with point rule
  template<int Points, typename Functor>
  void integrateWithPointRule( Functor& integrand,
			    double lower_limit,
			    double upper_limit,
			    double& result,
			    double& absolute_error,
                double& result_abs, 
                double& result_asc ) const;
/*
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
*/
private:

  // Gauss-Kronrod quadrature set for Points rule declaration 
  template<int Points>
  struct QuadratureSet
  {
    // Valid rule
    static const bool valid_rule = false;

    // Number of Kronrod weights and abscissae
    static const int kronrod_points = ( Points + 1 )/2;

    // Number of Gauss weights and abscissae
    static const int gauss_points = ( kronrod_points )/2;

    // Gauss quadrature weights 
    static const double gauss_weights[gauss_points];
    
    // Kronrad quadrature weights 
    static const double kronrod_weights[kronrod_points];

    // Kronrad quadrature abscissae
    static const double kronrod_abscissae[kronrod_points];
  };

  // Function wrapper for evaluating the functor
  template<typename Functor>
  static double functorWrapper( const double x, void* indirected_functor );

  // Calculate the quadrature upper and lower integrand values at an abscissa
  template<typename Functor>
  void calculateQuadratureIntegrandValuesAtAbscissa( 
    Functor& integrand, 
    double abscissa,
    double half_length,
    double midpoint,
    double& integrand_value_lower,
    double& integrand_value_upper ) const;

  // Rescale absolute error from integration
  void rescaleAbsoluteError( 
    double& absolute_error, 
    double result_abs, 
    double result_asc ) const;

  // Test if subinterval is too small
  template<int Points>
  inline bool subintervalTooSmall( double& lower_limit_1, 
                                   double& lower_limit_2, 
                                   double& upper_limit_2 ) const;

  // Update the integral results and errors
  inline void updateIntegral( Teuchos::Array<double>& bin_lower_limit, 
                              Teuchos::Array<double>& bin_upper_limit, 
                              Teuchos::Array<double>& bin_result, 
                              Teuchos::Array<double>& bin_error,
                              double& lower_limit_1, 
                              double& upper_limit_1,
                              double& area_1, 
                              double& error_1,
                              double& lower_limit_2,
                              double& upper_limit_2, 
                              double& area_2, 
                              double& error_2,
                              int& last,
                              int& bin_with_max_error ) const;

  // Sort the bin order from highest to lowest error 
  void sortErrorList( Teuchos::Array<double>& bin_error,
                      Teuchos::Array<double>& bin_order, 
                      double maximum_bin_error, 
                      int bin_with_larger_error,
                      int bin_with_smaller_error, 
                      int nr_max ) const;

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

#include "Utility_GaussKronrodIntegration_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_GUASS_KRONROD_INTEGRATION_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodIntegration.hpp
//---------------------------------------------------------------------------//
