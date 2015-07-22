//---------------------------------------------------------------------------//
//!
//! \file   Utility_SloanRadauQuadrature.hpp
//! \author Luke Kersting
//! \brief  Sloan implementation of Gauss-Radau quadrature
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SLOAN_RADAU_QUADRATURE_HPP
#define UTILITY_SLOAN_RADAU_QUADRATURE_HPP

// Boost Includes
#include <boost/multiprecision/cpp_dec_float.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_TwoDArray.hpp>

namespace Utility{

// use extended precision to make sure moments are preserved accurately
typedef boost::multiprecision::cpp_dec_float_50 long_float;

//! The Sloan implementation of Gauss-Radau quadrature
class SloanRadauQuadrature
{

public:

  //! Constructor
  SloanRadauQuadrature( 
            const Teuchos::Array<long_float>& legendre_expansion_moments );

  //! Destructor
  ~SloanRadauQuadrature()
  { /* ... */ }

  //! Find the nodes for the Radau quadrature
  void getRadauNodesAndWeights( Teuchos::Array<long_float>& nodes,
                                Teuchos::Array<long_float>& weights,
                                const int number_of_angles_wanted = 1 ) const;

  //! Find the nodes for the Radau quadrature
  void getRadauNodesAndWeights( Teuchos::Array<long double>& nodes,
                                Teuchos::Array<long double>& weights,
                                const int number_of_angles_wanted = 1 ) const;

  //! Find the nodes for the Radau quadrature
  void getRadauNodesAndWeights( Teuchos::Array<double>& nodes,
                                Teuchos::Array<double>& weights,
                                const int number_of_angles_wanted = 1 ) const;

//protected:

  // Return the Radau moments of the legendre expansion of a function, f(x)
  void getRadauMoments( Teuchos::Array<long_float>& radau_moments ) const;

  // Return the Radau moments of the legendre expansion of a function, f(x)
  void getLongRadauMoments( Teuchos::Array<long_float>& radau_moments ) const;

  // Evaulate the normalization ratio for the orthogonal polynomials, Q and x*Q
  void evaluateOrthogonalNormalizationRatio( 
        Teuchos::Array<long_float>& normalization_ratios,
        const Teuchos::TwoDArray<long_float>& orthogonal_coefficients,
        const Teuchos::Array<long_float>& normalization_factors_N,
        const Teuchos::Array<long_float>& radau_moments,
        const int i ) const;

  // Evaulate the ith mean coefficients for orthogonal polynomial recursion relation
  long_float evaluateMeanCoefficient( 
                     const Teuchos::Array<long_float>& normalization_ratios,
                     const int i ) const;

  // Evaulate the ith row of coefficients of the orthogonal polynomial Q
  void evaluateOrthogonalCoefficients( 
        Teuchos::TwoDArray<long_float>& orthogonal_coefficients,
        const Teuchos::Array<long_float>& variances,
        const Teuchos::Array<long_float>& mean_coefficients,
        const int i ) const;

  // Evaulate the normalization factors, N_i for the orthogonal polynomial, Q
  void evaluateOrthogonalNormalizationFactor( 
        Teuchos::Array<long_float>& normalization_factors_N,
        const Teuchos::TwoDArray<long_float>& orthogonal_coefficients,
        const Teuchos::Array<long_float>& radau_moments,
        const int i ) const;

  // Evaulate the variance of the moments of the orthogonal polynomial, Q_i
  long_float evaluateVariance( 
        const Teuchos::Array<long_float>& normalization_factors_N,
        const int i ) const;

  // Evaulate the nth orthogonal polynomial at x, Q_n(x)
  long_float evaluateOrthogonalPolynomial( 
        const Teuchos::Array<long_float>& variances,
        const Teuchos::Array<long_float>& mean_coefficients,
        const long_float x,
        const int i ) const;

  // Evaulate the roots of the nth orthogonal polynomial using the roots of the (n-1)th
  bool evaluateOrthogonalRoots( 
        Teuchos::TwoDArray<long_float>& roots,
        const Teuchos::Array<long_float>& variances,
        const Teuchos::Array<long_float>& mean_coefficients,
        const int i ) const;

  // Estimate an extra (i+1)th mean coefficient for the ith orthogonal polynomial
  void estimateExtraMeanCoefficient(
        Teuchos::Array<long_float>& mean_coefficients, 
        const Teuchos::Array<long_float>& variances,
        const Teuchos::Array<long_float>& normalization_factors_N,
        const Teuchos::Array<long_float>& radau_moments,
        const int i ) const;  

private:

// Moments of the Legendre expansion of weighting function f(x)             
Teuchos::Array<long_float> d_legendre_expansion_moments;

};

} // end Utility namespace

#endif // end UTILITY_GUASS_RADAU_QUADRATURE_KERNEL_HPP

//---------------------------------------------------------------------------//
// end Utility_SloanRadauQuadrature.hpp
//---------------------------------------------------------------------------//
