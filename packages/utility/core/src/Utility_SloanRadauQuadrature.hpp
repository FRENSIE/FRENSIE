//---------------------------------------------------------------------------//
//!
//! \file   Utility_SloanRadauQuadrature.hpp
//! \author Luke Kersting
//! \brief  Sloan implementation of Gauss-Radau quadrature
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SLOAN_RADAU_QUADRATURE_HPP
#define UTILITY_SLOAN_RADAU_QUADRATURE_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_TwoDArray.hpp>

namespace Utility{

//! The Sloan implementation of Gauss-Radau quadrature
class SloanRadauQuadrature
{

public:

  //! Constructor
  SloanRadauQuadrature( 
            const Teuchos::Array<double>& legendre_expansion_moments );

  //! Destructor
  ~SloanRadauQuadrature()
  { /* ... */ }

  //! Find the nodes for the Radau quadrature
  void getRadauNodesAndWeights( Teuchos::Array<double>& nodes,
                                Teuchos::Array<double>& weights,
                                const int number_of_angles_wanted = 1 ) const;

//protected:

  // Return the Radau moments of the legendre expansion of a function, f(x)
  void getRadauMoments( Teuchos::Array<double>& radau_moments ) const;

  // Evaulate the normalization ratio for the orthogonal polynomials, Q and x*Q
  void evaluateOrthogonalNormalizationRatio( 
        Teuchos::Array<double>& normalization_ratios,
        const Teuchos::TwoDArray<double>& orthogonal_coefficients,
        const Teuchos::Array<double>& normalization_factors_N,
        const Teuchos::Array<double>& radau_moments,
        const int i ) const;

  // Evaulate the ith mean coefficients for orthogonal polynomial recursion relation
  double evaluateMeanCoefficient( 
                     const Teuchos::Array<double>& normalization_ratios,
                     const int i ) const;

  // Evaulate the ith row of coefficients of the orthogonal polynomial Q
  void evaluateOrthogonalCoefficients( 
        Teuchos::TwoDArray<double>& orthogonal_coefficients,
        const double& variance_i_minus_one,
        const double& mean_coefficient_i,
        const int i ) const;

  // Evaulate the normalization factors, N_i for the orthogonal polynomial, Q
  void evaluateOrthogonalNormalizationFactor( 
        Teuchos::Array<double>& normalization_factors_N,
        const Teuchos::TwoDArray<double>& orthogonal_coefficients,
        const Teuchos::Array<double>& radau_moments,
        const int i ) const;

  // Evaulate the variance of the moments of the orthogonal polynomial, Q_i
  double evaluateVariance( 
        const Teuchos::Array<double>& normalization_factors_N,
        const int i ) const;

  // Evaulate the nth orthogonal polynomial at x, Q_n(x)
  double evaluateOrthogonalPolynomial( 
        const Teuchos::Array<double>& variances,
        const Teuchos::Array<double>& mean_coefficients,
        const double x,
        const int i ) const;

  // Evaulate the roots of the nth orthogonal polynomial using the roots of the (n-1)th
  bool evaluateOrthogonalRoots( 
        Teuchos::TwoDArray<double>& roots,
        const Teuchos::Array<double>& variances,
        const Teuchos::Array<double>& mean_coefficients,
        const int i ) const;

  // Estimate an extra (i+1)th mean coefficient for the ith orthogonal polynomial
  void estimateExtraMeanCoefficient(
        Teuchos::Array<double>& mean_coefficients, 
        const Teuchos::Array<double>& variances,
        const Teuchos::Array<double>& normalization_factors_N,
        const Teuchos::Array<double>& radau_moments,
        const int i ) const;  

private:

// Moments of the Legendre expansion of weighting function f(x)             
Teuchos::Array<double> d_legendre_expansion_moments;

};

} // end Utility namespace

#endif // end UTILITY_GUASS_RADAU_QUADRATURE_KERNEL_HPP

//---------------------------------------------------------------------------//
// end Utility_SloanRadauQuadrature.hpp
//---------------------------------------------------------------------------//
