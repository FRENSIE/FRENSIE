//---------------------------------------------------------------------------//
//!
//! \file   Utility_SloanRadauQuadrature.cpp
//! \author Luke Kersting
//! \brief  Sloan implementation of Gauss-Radau quadrature
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_SloanRadauQuadrature.hpp"
#include "Utility_GaussLegendreQuadratureKernel.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
SloanRadauQuadrature::SloanRadauQuadrature( 
            const Teuchos::Array<double>& legendre_expansion_moments,
            const int number_of_nodes )
  : d_legendre_expansion_moments( legendre_expansion_moments ),
    d_number_of_nodes( number_of_nodes )
{ 
  // Make sure there are enough moments to evaluate the number of nodes wanted
  testPrecondition( legendre_expansion_moments.size() >= 
                    2*number_of_nodes-1 );
}

// Find the Radau nodes including the end point mu = 1
void SloanRadauQuadrature::findNodesAndWeights( const Teuchos::Array<double>& radau_moments, 
                          Teuchos::Array<double>& nodes ) const
{
  
}

// Return the Radau moments of the legendre expansion of a function, f(x)
/*! \details The Radau moments can be calulated from the Gauss moments:
 *! radau_moment_n = gauss_moment_n - gauss_moment_n_plus_one
 *! Because the Radau Quadrature fixes a node at mu = 1, it will have one less
 *! degree of freedom and will preserve one less moment then the Gauss Quadrature
 *! see Sloan Eq. (B-79)
 */
void SloanRadauQuadrature::getRadauMoments(
            Teuchos::Array<double>& radau_moments ) const
{
  // Make sure the arrays are the right size
  testPrecondition( d_legendre_expansion_moments.size() == 
                    radau_moments.size() + 1 );

  // Get the Guass moments
  Teuchos::Array<double> gauss_moments( d_legendre_expansion_moments.size() );

  Utility::getGaussMoments( d_legendre_expansion_moments, gauss_moments );

  // Loop through array and calculate the radau moments
  for ( int n = 0; n < radau_moments.size(); n++ )
  {
    radau_moments[n] = gauss_moments[n] - gauss_moments[n+1];
  }
}

// Evaulate the normalization factors, N_i and L_i, for the orthogonal polynomial, Q and x*Q
/*! \details N is the normalization factor for the moment of Q and L is the 
 *! normalization factor for the moments of x*Q. They can be evaluated using 
 *! the Guass moments, M_i, and the orthogonal coefficients, a_(i,k):
 *! N_i = sum_( k=0,...,i ) a_(i,k)*M_(k+i) and L_(i+1) = sum_( k=0,...,i ) a_(i,k)*M_(k+i+1)
 *! see Sloan Eq. (B-100b) and (B-101b)
 */
void SloanRadauQuadrature::evaluateOrthogonalNormalizationFactor( 
        const Teuchos::TwoDArray<double>& orthogonal_coefficients,
        const Teuchos::Array<double>& gauss_moments,
        const int i,
        double& normalization_factor_N,
        double& normalization_factor_L ) const
{
  // Make sure i is valid
  testPrecondition( 2*i+1 <= gauss_moments.size() );

  for ( int k = 0; k < i; k++ )
  {
    normalization_factor_N += orthogonal_coefficients[i][k]*gauss_moments[k+i];
    normalization_factor_L += orthogonal_coefficients[i][k]*gauss_moments[k+i+1];
  }
}

// Evaulate the variance of the moments of the orthogonal polynomial, Q_i
/*! \details The variance can be found from the ratio of the orthogonal
 *! normalization factor to the i-1 factor: variance = N_i/N_(i-1)
 *! see Sloan Eq. (B-99)
 */
double SloanRadauQuadrature::evaluateVariance( 
        const Teuchos::Array<double>& normalization_factors_N,
        const int i ) const
{
  // Make sure i is valid
  testPrecondition( i <= normalization_factors_N.size() );

  return normalization_factors_N[i]/normalization_factors_N[i-1];
}

  // Evaulate the ith root of the orthogonal polynomial
/*! \details The ith root can be calculated from the Q and x*Q normalization factors: 
 *! root_i = L_i/N_(i-1) - L_(i-1)/N_(i-2)
 *! see Sloan Eq. (B-103b)  
 */
double SloanRadauQuadrature::evaluateRoot( 
        const Teuchos::Array<double>& normalization_factors_N,
        const Teuchos::Array<double>& normalization_factors_L,
        const int i ) const
{
  // Make sure i is valid
  testPrecondition( i <= normalization_factors_N.size() );
  testPrecondition( i <= normalization_factors_L.size() );

  return normalization_factors_L[i] / normalization_factors_N[i-1] -
         normalization_factors_L[i-1]/normalization_factors_N[i-2];
}

// Evaulate the (i+1,k)th coefficient of of the orthogonal polynomial Q
/*! \details The recursion relationship for the coefficients of the orthogonal
 *! polynomial are given by Sloan: Eq (B-106) 
 */
void SloanRadauQuadrature::evaluateOrthogonalCoefficient( 
        Teuchos::TwoDArray<double>& orthogonal_coefficients,
        const double& variance_i,
        const double& root_i_plus_one,
        const int i,
        const int k ) const
{
  orthogonal_coefficients[i+1][k] = orthogonal_coefficients[i][k-1] -
                    root_i_plus_one*orthogonal_coefficients[i][k-1] -
                         variance_i*orthogonal_coefficients[i-1][k]; 
}

// Evaulate the ith orthogonal polynomial, Q_i(x)
/*! \details The orthogonal polynomial can be evaulated at a value x using its 
 *! coefficients: Q_i(x) = sum_(k=0,...,i) c_(i,k)*x^k
 *! see Sloan Eq. (B-104) 
 */
double SloanRadauQuadrature::evaluateOrthogonalPolynomial( 
        Teuchos::TwoDArray<double>& orthogonal_coefficients,
        const double x,
        const int i ) const
{
  double result;

  for ( int k = 0; k < i; k++ )
  {
    result += orthogonal_coefficients[i][k]*pow(x,k);
  }
  
  return result;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_SloanRadauQuadrature.cpp
//---------------------------------------------------------------------------//
