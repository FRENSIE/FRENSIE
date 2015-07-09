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
            const Teuchos::Array<double>& legendre_expansion_moments,
            const int number_of_nodes );

  //! Destructor
  ~SloanRadauQuadrature()
  { /* ... */ }
/*
  //! Find the Radau nodes and weights including the end point mu = 1
  void findNodesAndWeights( Teuchos::Array<double>& moments, 
                            Teuchos::Array<double>& nodes,
                            Teuchos::Array<double>& weights ) const;
*/

  //! Find the Radau nodes including the end point mu = 1
  void findNodesAndWeights( const Teuchos::Array<double>& radau_moments, 
                            Teuchos::Array<double>& nodes ) const;

//protected:

  // Return the Radau moments of the legendre expansion of a function, f(x)
  void getRadauMoments( 
                    const Teuchos::Array<double>& legendre_expansion_moments,
                    Teuchos::Array<double>& radau_moments ) const;

  // Evaulate the normalization factors, N_i and L_i, for the orthogonal polynomial, Q and x*Q
  void evaluateOrthogonalNormalizationFactor( 
        const Teuchos::TwoDArray<double>& orthogonal_coefficients,
        const Teuchos::Array<double>& gauss_moments,
        const int i,
        double& normalization_factor_N,
        double& normalization_factor_L ) const;

  // Evaulate the variance of the moments of the orthogonal polynomial, Q_i
  double evaluateVariance( 
        const Teuchos::Array<double>& normalization_factors_N,
        const int i ) const;

  // Evaulate the ith root of the orthogonal polynomial
  double evaluateRoot( 
        const Teuchos::Array<double>& normalization_factors_N,
        const Teuchos::Array<double>& normalization_factors_L,
        const int i ) const;

  // Evaulate the (i+1,k)th coefficient of of the orthogonal polynomial Q
  void evaluateOrthogonalCoefficient( 
        Teuchos::TwoDArray<double>& orthogonal_coefficients,
        const double& variance_i,
        const double& root_i_plus_one,
        const int i,
        const int k ) const;

  // Evaulate the (i+1)th orthogonal polynomial at x, Q_(i+1)(x)
  double evaluateOrthogonalPolynomial( 
        Teuchos::TwoDArray<double>& orthogonal_coefficients,
        const double x,
        const int i) const;

  // Evaulate the nth orthogonal polynomial at node_i of Q_(n-1)
  double evaluateOrthogonalPolynomialAtNode( 
        const Teuchos::Array<double>& variances,
        const Teuchos::Array<double>& roots,
        const double node_i,
        const int i ) const;

private:

// Moments of the Legendre expansion of function f(x)             
Teuchos::Array<double> d_legendre_expansion_moments;

// Number of nodes that the radau quadrature set is to be evaulated
int d_number_of_nodes;
};

} // end Utility namespace

#endif // end UTILITY_GUASS_RADAU_QUADRATURE_KERNEL_HPP

//---------------------------------------------------------------------------//
// end Utility_SloanRadauQuadrature.hpp
//---------------------------------------------------------------------------//
