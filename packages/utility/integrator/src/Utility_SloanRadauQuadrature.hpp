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

// Std Lib Includes
#include <vector>

namespace Utility{

// use extended precision to make sure moments are preserved accurately
typedef boost::multiprecision::cpp_dec_float_50 long_float;

//! The Sloan implementation of Gauss-Radau quadrature
class SloanRadauQuadrature
{

public:

  //! Constructor
  SloanRadauQuadrature(
            const std::vector<long_float>& legendre_expansion_moments );

  //! Destructor
  ~SloanRadauQuadrature()
  { /* ... */ }

  //! Find the nodes for the Radau quadrature
  void getRadauNodesAndWeights( std::vector<long_float>& nodes,
                                std::vector<long_float>& weights,
                                const int number_of_angles_wanted = 1 ) const;

  //! Find the nodes for the Radau quadrature
  void getRadauNodesAndWeights( std::vector<long double>& nodes,
                                std::vector<long double>& weights,
                                const int number_of_angles_wanted = 1 ) const;

  //! Find the nodes for the Radau quadrature
  void getRadauNodesAndWeights( std::vector<double>& nodes,
                                std::vector<double>& weights,
                                const int number_of_angles_wanted = 1 ) const;

//protected:

  // Return the Radau moments of the legendre expansion of a function, f(x)
  void getRadauMoments( std::vector<long_float>& radau_moments ) const;

  // Return the Radau moments of the legendre expansion of a function, f(x)
  void getLongRadauMoments( std::vector<long_float>& radau_moments ) const;

  // Evaluate the normalization ratio for the orthogonal polynomials, Q and x*Q
  void evaluateOrthogonalNormalizationRatio(
        std::vector<long_float>& normalization_ratios,
        const std::vector<std::vector<long_float> >& orthogonal_coefficients,
        const std::vector<long_float>& normalization_factors_N,
        const std::vector<long_float>& radau_moments,
        const int i ) const;

  // Evaluate the ith mean coefficients for orthogonal polynomial recursion relation
  long_float evaluateMeanCoefficient(
                     const std::vector<long_float>& normalization_ratios,
                     const int i ) const;

  // Evaluate the ith row of coefficients of the orthogonal polynomial Q
  void evaluateOrthogonalCoefficients(
        std::vector<std::vector<long_float> >& orthogonal_coefficients,
        const std::vector<long_float>& variances,
        const std::vector<long_float>& mean_coefficients,
        const int i ) const;

  // Evaluate the normalization factors, N_i for the orthogonal polynomial, Q
  void evaluateOrthogonalNormalizationFactor(
        std::vector<long_float>& normalization_factors_N,
        const std::vector<std::vector<long_float> >& orthogonal_coefficients,
        const std::vector<long_float>& radau_moments,
        const int i ) const;

  // Evaluate the variance of the moments of the orthogonal polynomial, Q_i
  long_float evaluateVariance(
        const std::vector<long_float>& normalization_factors_N,
        const int i ) const;

  // Evaluate the nth orthogonal polynomial at x, Q_n(x)
  long_float evaluateOrthogonalPolynomial(
        const std::vector<long_float>& variances,
        const std::vector<long_float>& mean_coefficients,
        const long_float x,
        const int i ) const;

  // Evaluate the roots of the nth orthogonal polynomial using the roots of the (n-1)th
  bool evaluateOrthogonalRoots(
        std::vector<std::vector<long_float> >& roots,
        const std::vector<long_float>& variances,
        const std::vector<long_float>& mean_coefficients,
        const int i ) const;

  // Estimate an extra (i+1)th mean coefficient for the ith orthogonal polynomial
  void estimateExtraMeanCoefficient(
        std::vector<long_float>& mean_coefficients,
        const std::vector<long_float>& variances,
        const std::vector<long_float>& normalization_factors_N,
        const std::vector<long_float>& radau_moments,
        const int i ) const;

private:

  // Shape a two-d array
  static void shapeTwoDArray( std::vector<std::vector<long_float> >& two_d_array,
                              const size_t num_rows,
                              const size_t num_cols,
                              const long_float fill_value = 0.0 );

  // Moments of the Legendre expansion of weighting function f(x)
  std::vector<long_float> d_legendre_expansion_moments;

};

} // end Utility namespace

#endif // end UTILITY_GAUSS_RADAU_QUADRATURE_KERNEL_HPP

//---------------------------------------------------------------------------//
// end Utility_SloanRadauQuadrature.hpp
//---------------------------------------------------------------------------//
