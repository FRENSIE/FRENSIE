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
				const double absolute_error_tol = 0.0 );

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

  // Normalize absolute error from integration
  void normalizeAbsoluteError( 
    double& absolute_error, 
    double result_abs, 
    double result_asc ) const;

  // 7 point Gauss quadrature weights
  static const double gauss_weights_7[4];

  // 7 point Gauss quadrature abscissae
  static const double gauss_abscissae_7[4];

  // 15 point Gauss Kronrad quadrature weights 
  //static const Teuchos::Array<double> kronrod_weights_15;
  static const double kronrod_weights_15[8];

  // 15 point Gauss Kronrad quadrature abscissae
  //static Teuchos::Array<double> kronrod_abscissae_15;
  static const double kronrod_abscissae_15[8];

  // 21 point Gauss Kronrad quadrature weights 
  static Teuchos::Array<double> kronrod_weights_21;

  // 21 point Gauss Kronrad quadrature abscissae
  static Teuchos::Array<double> kronrod_abscissae_21;

  // 31 point Gauss Kronrad quadrature weights 
  static Teuchos::Array<double> kronrod_weights_31;

  // 31 point Gauss Kronrad quadrature abscissae
  static Teuchos::Array<double> kronrod_abscissae_31;

  // 41 point Gauss Kronrad quadrature weights 
  static Teuchos::Array<double> kronrod_weights_41;

  // 41 point Gauss Kronrad quadrature abscissae
  static Teuchos::Array<double> kronrod_abscissae_41;

  // 51 point Gauss Kronrad quadrature weights 
  static Teuchos::Array<double> kronrod_weights_51;

  // 51 point Gauss Kronrad quadrature abscissae
  static Teuchos::Array<double> kronrod_abscissae_51;

  // The relative error tolerance
  double d_relative_error_tol;

  // The absolute error tolerance
  double d_absolute_error_tol;
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
