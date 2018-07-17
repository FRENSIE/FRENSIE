//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussRadauQuadratureSet.cpp
//! \author Luke Kersting
//! \brief  Gauss-Radau quadrature set
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "Utility_GaussRadauQuadratureSet.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Constructor
GaussRadauQuadratureSet::GaussRadauQuadratureSet(
    boost::function<double (double, int)> polynomial_expansion_function,
    const double error_tol,
    const int polynomial_order )
  : d_polynomial_expansion_function( polynomial_expansion_function ),
    d_error_tol( error_tol ),
    d_polynomial_order( polynomial_order )
{
  // Make sure the error tolerances are valid
  testPrecondition( error_tol >= 0.0 );

  // Make sure the work space size is valid
  testPrecondition( polynomial_order > 0 );
}

// Calculate the nth order Jacobi Polynomial at x
/*! \details The Jacobi Polynomials can be calculated by the following recursion
 * relationship:
 * a1_n P_{n+1}^{\alpha,\beta}(x) = (a2_n + a3_n x)P_n^{\alpha,\beta}(x) - a4_n P_{n-1}^{\alpha,\beta}(x)
 * where:
 * a1_n = 2(n+1)(n+\alpha+\beta+1)(2n+\alpha+\beta)
 * a2_n = (2n+\alpha+\beta+1)(\alpha^2-\beta^2)
 * a3_n = (2n + \alpha + \beta)(2n + \alpha + \beta + 1)(2n + \alpha +\beta + 2)
 * a4_n = 2(n+\alpha)(n+\beta)(2n+\alpha+\beta+2)
 */
double GaussRadauQuadratureSet::getJacobiPolynomial(
    double x,
    int n,
    int alpha,
    int beta ) const
{
  // Calculate the first two polynomials
  double P_0 = 1.0;
  double P_1 = 0.5*( alpha - beta + ( alpha + beta + 2 )* x );

  if (n==0)
  {
    return P_0;
  }
  if (n==1)
  {
    return P_1;
  }
  else
  {
    int a_b = alpha + beta;
    int a_b_1 = a_b + 1;
    int a_b_2 = a_b + 2;

    double p_i_minus_2 = P_0;
    double p_i_minus_1 = P_1;
    double p_i;

    // Use recursion relation to calculate higher order Jacobi polynomials
    for (int i = 1; i < n; ++i)
    {
      int two_i = 2*i;

      // Calculate the Jacobi coefficients
      double a1_i = 2.0*( i + 1.0 )*( i + a_b_1 )*( two_i + a_b );
      double a2_i = ( two_i + a_b_1 )*( alpha*alpha - beta*beta );
      double a3_i = ( two_i + a_b )*( two_i + a_b_1 )*( two_i + a_b_2 );
      double a4_i = 2.0*( i + alpha )*( i + beta )*( two_i + a_b_2 );

      // Calculate new P_n value
      p_i = 1.0/a1_i*( ( a2_i + a3_i*x )*p_i_minus_1 - a4_i*p_i_minus_2 );

      // Update P_n_minus_1 and P_n_minus_2 for next value on n
      p_i_minus_2 = p_i_minus_1;
      p_i_minus_1 = p_i;
    }

  return p_i;
  }
}

double GaussRadauQuadratureSet::getLegendrePolynomial(
                                        double x,
                                        int n ) const
{
  return getJacobiPolynomial( x, n, 0, 0 );
}

// Calculate the derivative of the nth order Jacobi Polynomial at x
/* \details The Jacobi Polynomials can be calculated by the following recursion
 * relationship:
 * 1/2( n + \alpha + \beta + 1 )P_{n-1}^{\alpha + 1,\beta + 1}(x)
 */
double GaussRadauQuadratureSet::getJacobiPolynomialDerivative(
                              double x,
                              int n,
                              int alpha,
                              int beta ) const
{

  if (n==0)
  {
    return 0.0;
  }
  if (n==1)
  {
    return 0.5*( alpha + beta + 2.0 );
  }
  else
  {
    return 0.5 * (alpha + beta + n + 1.0) * getJacobiPolynomial( x,
                                                                 n-1,
                                                                 alpha + 1,
                                                                 beta + 1 );
  }
}

// Estimate the roots of the Jacobi Polynomial
/* \details The roots of the Jacobi Polynomials can be estimated by the roots of
 * the Chebyshev Polynomials which are given by the relationship:
 * x_k = cos( (2k - 1)\pi/2n ) , k = 1, ... , n
 */
void GaussRadauQuadratureSet::getJacobiPolynomialRoots(
                                 std::vector<double>& roots,
                                 const int n,
                                 int alpha,
                                 int beta ) const
{
  // Max number of allowed iterations
  int max_iterations = 200;

  int iteration;
  double root_k, s, jacobi, jacobi_derivative, delta_root;

  // Iterate through all n roots ( 0 < k < n )
  for (int k = 0; k < n; ++k)
  {
    // Make an initial guess that the roots are equal to the roots of the Chebyshev Polynomial
    root_k = -cos( ( 2.0*k + 1.0 )/( 2.0 * n )* PhysicalConstants::pi );

    // Actual root is known to be in between roots of Chebyshev Polynomial
    if (k > 0)
    {
      root_k = ( root_k + roots[k-1] )/2.0;
    }

    iteration = 0;

    // Iterate until you converge on root
    do
    {
      s = 0;

      for (int i = 0; i < k; ++i)
      {
        s += 1.0/( root_k - roots[i] );
      }

      // Get error
      jacobi = getJacobiPolynomial( root_k, n, alpha, beta );
      jacobi_derivative =
               getJacobiPolynomialDerivative( root_k, n, alpha, beta );\

      delta_root = -jacobi/( jacobi_derivative - jacobi*s );

      // Update root value
      root_k += delta_root;

      // Update iteration
      ++iteration;

      if ( iteration > max_iterations )
         break;
/*
      TEST_FOR_EXCEPTION( iteration > max_iterations,
		          RadauQuadratureError,
		          "Error: the root of the Jacobi Polynomial "
                          "did not converge" );
*/
    }
    while ( fabs(delta_root) > d_error_tol );

    roots[k] = root_k;
  }
}

// Find the Radau nodes and weights including at end point -1 or 1
void GaussRadauQuadratureSet::findNodesAndWeights(
                            double end_point,
                            std::vector<double>& nodes,
                            std::vector<double>& weights ) const
{
  // Make sure end_point is either -1 or 1
  testPrecondition( fabs(end_point) == 1.0 );

  int n = d_polynomial_order;
  int alpha = 0;
  int beta = 1;
  double jacobi_derivative;

  std::vector<double> roots( n );

  // Calculate the roots of the Jacobi Polynomial
  getJacobiPolynomialRoots( roots, n, alpha, beta );

  // Check to see if the end point is the first node
  if ( end_point < roots[0] )
  {
    nodes[0] = end_point;
    weights[0] = findWeightAtEndPoint( end_point, n );

    // Iterate through the all nodes and weights
    for ( int i = 0; i < n; ++i )
    {
      nodes[i+1] = roots[i];

      weights[i+1] = findWeightAtNode( roots[i], end_point, n );
    }
  }
  else
  {
    nodes[n] = end_point;
    weights[n] = findWeightAtEndPoint( end_point, n );

    // Iterate through all other nodes and weights
    for ( int i = 0; i < n; ++i )
    {
      nodes[i] = roots[i];

      weights[i] = findWeightAtNode( roots[i], end_point, n );
    }
  }
}

// Find the Radau nodes and weights including at end point -1 or 1
void GaussRadauQuadratureSet::findNodesAndPositiveWeights(
                            double end_point,
                            std::vector<double>& nodes,
                            std::vector<double>& weights ) const
{
  // Make sure end_point is either -1 or 1
  testPrecondition( fabs(end_point) == 1.0 );

  int n = d_polynomial_order;
  int alpha = 0;
  int beta = 1;
  double jacobi_derivative;

  std::vector<double> roots( n );

  // Calculate the roots of the Jacobi Polynomial
  getJacobiPolynomialRoots( roots, n, alpha, beta );

  // Check to see if the end point is the first node
  if ( end_point < roots[0] )
  {
    nodes[0] = end_point;
    weights[0] = findWeightAtEndPoint( end_point, n );

    // Iterate through the all nodes and weights
    for ( int i = 0; i < n; ++i )
    {
      nodes[i+1] = roots[i];

      jacobi_derivative =
              getJacobiPolynomialDerivative( nodes[i+1], n, alpha, beta );

      weights[i+1] = findWeightAtNode( roots[i], end_point, n );
    }
  }
  else
  {
    nodes[n] = end_point;
    weights[n] = findWeightAtEndPoint( -end_point, n );

    // Iterate through all other nodes and weights
    for ( int i = 0; i < n; ++i )
    {
      nodes[n-1-i] = -roots[i];

      // Get the derivative of the Jacobi Polynomial of order n
      jacobi_derivative =
              getJacobiPolynomialDerivative( roots[i],
                                             n,
                                             alpha, beta );

      weights[n-1-i] = findWeightAtNode( roots[i], -end_point, n );
    }
  }
}

// Create the integrand function for the weight at the end point -1 or 1
double GaussRadauQuadratureSet::getFixedWeightIntegrand(
                               double end_point,
                               int n ) const
{
  return d_polynomial_expansion_function( end_point, n )*getJacobiPolynomial( end_point, n );
}

// Create the integrand function for the weight at a given node with end point -1 or 1
double GaussRadauQuadratureSet::getWeightIntegrand(
                               double x,
                               double node,
                               double end_point,
                               int n ) const
{
  return getFixedWeightIntegrand( x, n )*( x - end_point )/( x - node );
}

// Find the Radau weight for the function at the end point -1 or 1
double GaussRadauQuadratureSet::findWeightAtEndPoint( double end_point,
                                                         int n ) const
{
  // Make sure end_point is either -1 or 1
  testPrecondition( fabs(end_point) == 1.0 );
  // Make sure n is positive
  testPrecondition( n > 0.0 );

  boost::function<double (double x)> weight_function =
    boost::bind<double>( &GaussRadauQuadratureSet::getFixedWeightIntegrand,
			 boost::cref( *this ),
			 _1,
			 n );

  double abs_error, result;
  double precision = 1e-12;

  Utility::GaussKronrodIntegrator<double> integrator( precision );

  integrator.integrateAdaptively<15>(
					weight_function,
					-1.0,
					1.0,
					result,
					abs_error );

  return result/getJacobiPolynomial( end_point, n );

}

// Find the Radau weight for the function at a given node
double GaussRadauQuadratureSet::findWeightAtNode( double node,
                                                     double end_point,
                                                     int n ) const
{
  // Make sure end_point is either -1 or 1
  testPrecondition( fabs(end_point) == 1.0 );
  // Make sure node is between -1 and 1
  testPrecondition( node < 1.0 );
  testPrecondition( node > -1.0 );
  // Make sure n is positive
  testPrecondition( n > 0.0 );

  boost::function<double (double x)> weight_function =
    boost::bind<double>( &GaussRadauQuadratureSet::getWeightIntegrand,
			 boost::cref( *this ),
			 _1,
                         node,
                         end_point,
			 n );

  double abs_error, result;
  double precision = 1e-12;

  Utility::GaussKronrodIntegrator<double> integrator( precision );

  integrator.integrateAdaptively<15>(
					weight_function,
					-1.0,
					1.0,
					result,
					abs_error );
  return result/
           ( getJacobiPolynomialDerivative( node, n ) * ( node - end_point) );

}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GaussRadauQuadratureSet.cpp
//---------------------------------------------------------------------------//
