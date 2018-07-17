//---------------------------------------------------------------------------//
//!
//! \file   Utility_SloanRadauQuadrature.cpp
//! \author Luke Kersting
//! \brief  Sloan implementation of Gauss-Radau quadrature
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_SloanRadauQuadrature.hpp"
#include "Utility_GaussLegendreQuadratureSet.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Shape a two-d array
void SloanRadauQuadrature::shapeTwoDArray(
                            std::vector<std::vector<long_float> >& two_d_array,
                            const size_t num_rows,
                            const size_t num_cols,
                            const long_float fill_value )
{
  two_d_array.clear();
  two_d_array.resize( num_rows );

  for( size_t i = 0; i < num_rows; ++i )
    two_d_array[i].resize( num_cols, fill_value );
}

// Constructor
SloanRadauQuadrature::SloanRadauQuadrature(
            const std::vector<long_float>& legendre_expansion_moments )
  : d_legendre_expansion_moments( legendre_expansion_moments )
{
  // Make sure there are enough moments to evaluate the number of nodes wanted
  testPrecondition( legendre_expansion_moments.size() > 1 );

  // Make sure the zeroth legendre moment is included
 // testPrecondition( legendre_expansion_moments[0] == 1.0 );
}

// Find the Radau nodes including the end point mu = 1
void SloanRadauQuadrature::getRadauNodesAndWeights(
                                std::vector<long_float>& nodes,
                                std::vector<long_float>& weights,
                                const int number_of_angles_wanted ) const
{
  bool was_root_found;

  // Get the Radau moments
  std::vector<long_float>
                     radau_moments( d_legendre_expansion_moments.size() - 1 );

  getRadauMoments( radau_moments );

  // Calculate max number of roots from the number of radau moments
  int number_of_roots = ( radau_moments.size() - 1 )/2 + 1;

  // Calculate the number of coefficients of the orthogonal polynomials
  int number_of_coefficients = radau_moments.size() - number_of_roots + 1;
/*
std::cout << std::endl << "number_of_coefficients = " << number_of_coefficients  << std::endl;
std::cout << std::endl << "number_of_roots = " << number_of_roots  << std::endl;
*/
  // Initialize arrays for data needed to calculate the orthogonal polynomials
  std::vector<std::vector<long_float> > orthogonal_coefficients;
  this->shapeTwoDArray( orthogonal_coefficients,
                        number_of_coefficients,
                        number_of_coefficients,
                        long_float(0) );

  std::vector<std::vector<long_float> > roots;
  this->shapeTwoDArray( roots,
                        number_of_coefficients+1,
                        number_of_roots+1,
                        long_float(0) );

  std::vector<long_float> normalization_ratios( number_of_coefficients ),
                         normalization_factors_N( number_of_coefficients ),
                         variances( number_of_coefficients ),
                         mean_coefficients( number_of_coefficients + 1 );

  // Set the i = 0 case
  orthogonal_coefficients[0][0] = long_float(1);
  evaluateOrthogonalNormalizationFactor( normalization_factors_N,
                                         orthogonal_coefficients,
                                         radau_moments,
                                         0 );

  // Get the mean coefficients and variances for the orthogonal recursion relationship
  for ( int i = 1; i < number_of_roots; ++i )
  {
    // Get the normalization ratio to calculate the mean coefficient value
    evaluateOrthogonalNormalizationRatio( normalization_ratios,
                                          orthogonal_coefficients,
                                          normalization_factors_N,
                                          radau_moments,
                                          i );

    // Get the mean_coefficient value
    mean_coefficients[i] = evaluateMeanCoefficient( normalization_ratios, i );

    // Get the orthogonal coefficients for row i
    evaluateOrthogonalCoefficients( orthogonal_coefficients,
                                    variances,
                                    mean_coefficients,
                                    i);

    // Get the normalization factor
    evaluateOrthogonalNormalizationFactor( normalization_factors_N,
                                           orthogonal_coefficients,
                                           radau_moments,
                                           i );

    // Calculate the variance of the orthogonal coefficient
    variances[i] = evaluateVariance( normalization_factors_N, i );

    // If variance is negative it will cause a negative weight
    if ( variances[i] <= long_float(0) )
    {
      number_of_roots = i;
      number_of_coefficients = i + 1;

      std::cout << std::endl << "variance, " << i <<" is negative or zero." << std::endl;
    }
  }
  // Add last mean coefficient if needed
  if ( number_of_coefficients > number_of_roots )
  {
    // Get the normalization ratio to calculate the mean coefficient value
    evaluateOrthogonalNormalizationRatio( normalization_ratios,
                                          orthogonal_coefficients,
                                          normalization_factors_N,
                                          radau_moments,
                                          number_of_coefficients-1 );

    // Get the mean_coefficient value
    mean_coefficients[number_of_coefficients-1] =
      evaluateMeanCoefficient( normalization_ratios, number_of_coefficients-1 );
  }

  // check to see if first mean coefficient will give a negative weight
  if ( mean_coefficients[1] >= d_legendre_expansion_moments[1]/d_legendre_expansion_moments[0] )
  {
    // Only one node
    number_of_roots = 1;

    roots[1][0] = -normalization_factors_N[0]/
                    ( long_float(2) * d_legendre_expansion_moments[0] );
  }
  else
  {
    // Get the roots of the orthogonal polynomials
    // Set one root for i = 1
    roots[1][0] = mean_coefficients[1];

    // Loop through to get other roots
    for ( int i = 2; i < number_of_coefficients; ++i )
    {
      was_root_found = evaluateOrthogonalRoots( roots,
                                                variances,
                                                mean_coefficients,
                                                i );
      // If the i+1 roots cannot be found, use i roots
      if ( was_root_found == false)
      {
        number_of_coefficients = i;
        number_of_roots = i;
      }
    }

    /* For an odd legendre expansion it may be possible to approximate the n+1
     * expansion and increase the number of possible roots by 1. */
    if ( number_of_coefficients == number_of_roots )
    {
      // Estimate extra mean coefficient
      estimateExtraMeanCoefficient( mean_coefficients,
                                    variances,
                                    normalization_factors_N,
                                    radau_moments,
                                    number_of_roots );

      // evaluate the extra root
      was_root_found = evaluateOrthogonalRoots( roots,
                                                variances,
                                                mean_coefficients,
                                                number_of_roots );

      // If the extra root cannot be found, use number_of_roots -1 roots
      if ( was_root_found == false)
      {
        number_of_roots -= 1;
      }
    }
  }

  if ( number_of_angles_wanted > number_of_roots + 1)
  {
     std::cout << "WARNING: Could only get " << number_of_roots + 1 <<
     std::endl << "of the " << number_of_angles_wanted << " angles wanted." << std::endl;

     nodes.resize( number_of_roots + 1 );
     weights.resize( number_of_roots + 1 );

    for ( int k = 0; k < number_of_roots; ++k )
    {
      nodes[k] = roots[number_of_roots][k];
    }

    nodes[number_of_roots] = long_float(1);
  }
  else
  {
     nodes.resize( number_of_angles_wanted );
     weights.resize( number_of_angles_wanted );

    for ( int k = 0; k < number_of_angles_wanted-1; ++k )
    {
      nodes[k] = roots[number_of_angles_wanted-1][k];
    }

    nodes[number_of_angles_wanted-1] = long_float(1);
  }

  // Calculate the weights of the nodes
  long_float polynomial_at_node, variable;
  long_float sum_of_weights = long_float(0);

  for ( int i = 0; i < weights.size()-1; ++i )
  {
    variable = long_float(0);

    for ( int k = 0; k < weights.size()-1; ++k )
    {
      polynomial_at_node = evaluateOrthogonalPolynomial( variances,
                                                         mean_coefficients,
                                                         nodes[i],
                                                         k );
      variable += polynomial_at_node*polynomial_at_node/
                    normalization_factors_N[k];
    }

  weights[i] =  long_float(1)/( variable*( long_float(1) - nodes[i] ) )/
                d_legendre_expansion_moments[0];

  sum_of_weights += weights[i];
  }
  // Make sure weights are valid
  if ( sum_of_weights > long_float(1) )
    FRENSIE_LOG_WARNING( "non-physical weight!" );

  // Calculate the weight of the Mu = 1 node
  weights[weights.size()-1] = long_float(1) - sum_of_weights;
}

// Find the Radau nodes including the end point mu = 1
void SloanRadauQuadrature::getRadauNodesAndWeights(
                                std::vector<long double>& nodes,
                                std::vector<long double>& weights,
                                const int number_of_angles_wanted ) const
{
  std::vector<long_float> node, weight;
  getRadauNodesAndWeights( node, weight, number_of_angles_wanted );

  nodes.resize( node.size() );
  weights.resize( node.size() );

  for ( int i = 0; i < node.size(); ++i )
  {
    nodes[i] = node[i].convert_to<long double>();
    weights[i] = weight[i].convert_to<long double>();
  }

}

// Find the Radau nodes including the end point mu = 1
void SloanRadauQuadrature::getRadauNodesAndWeights(
                                std::vector<double>& nodes,
                                std::vector<double>& weights,
                                const int number_of_angles_wanted ) const
{
  std::vector<long_float> node, weight;
  getRadauNodesAndWeights( node, weight, number_of_angles_wanted );


  nodes.resize( node.size() );
  weights.resize( node.size() );

  for ( int i = 0; i < node.size(); ++i )
  {
    nodes[i] = node[i].convert_to<double>();
    weights[i] = weight[i].convert_to<long double>();
  }

}

// Return the Radau moments of the legendre expansion of a function, f(x)
/*! \details The Radau moments can be calculated from the Gauss moments:
 *! radau_moment_n = gauss_moment_n - gauss_moment_n_plus_one
 *! Because the Radau Quadrature fixes a node at mu = 1, it will have one less
 *! degree of freedom and will preserve one less moment then the Gauss Quadrature
 *! see Sloan Eq. (B-79)
 */
void SloanRadauQuadrature::getRadauMoments(
            std::vector<long_float>& radau_moments ) const
{

  // Make sure the arrays are the right size
  testPrecondition( d_legendre_expansion_moments.size() >=
                    radau_moments.size() + 1 );

  // Make sure the zeroth legendre moment is included
  //testPrecondition( d_legendre_expansion_moments[0] == 1.0 );

  // Get the Gauss moments
  std::vector<long_float> gauss_moments( d_legendre_expansion_moments.size() );

  Utility::getGaussMoments( d_legendre_expansion_moments, gauss_moments );

  for ( int n = 0; n < radau_moments.size(); ++n )
  {
    radau_moments[n] = gauss_moments[n] - gauss_moments[n+1];
  }
}

// Return the Radau moments of the legendre expansion of a function, f(x)
/*! \details The Radau moments can be calculated from the Gauss moments:
 *! radau_moment_n = gauss_moment_n - gauss_moment_n_plus_one
 *! Because the Radau Quadrature fixes a node at mu = 1, it will have one less
 *! degree of freedom and will preserve one less moment then the Gauss Quadrature
 *! see Sloan Eq. (B-79)
 */
void SloanRadauQuadrature::getLongRadauMoments(
            std::vector<long_float>& radau_moments ) const
{
  int number_of_moments = d_legendre_expansion_moments.size();

  // Make sure the arrays are the right size
  testPrecondition( number_of_moments >=
                    radau_moments.size() + 1 );
/*
  // Make sure the zeroth legendre moment is included
  testPrecondition( d_legendre_expansion_moments[0] == 1.0 );
*/
  // Get the coefficients of Gauss moments
  std::vector<std::vector<long_float> > coefficients;
  this->shapeTwoDArray( coefficients,
                        number_of_moments+1,
                        number_of_moments+1 );

  Utility::getLegendrePowerExpansionCoefficients( coefficients,
                                                  number_of_moments );

  long_float moment_n;
  for ( int n = 0; n < radau_moments.size(); ++n )
  {
    moment_n = 0;
    for ( int l = 0; l <= n; ++l )
    {
      // Calculate moment n
      moment_n += ( coefficients[n][l] - coefficients[n+1][l] )*
                  d_legendre_expansion_moments[l];
    }
  moment_n -= coefficients[n+1][n+1]*d_legendre_expansion_moments[n+1];
  radau_moments[n] = moment_n.convert_to<long_float>();
  }
}

// Evaluate the normalization ratio for the orthogonal polynomial, Q and x*Q
/*! \details The ratio of the normalization factor for the moments of Q, N, and
 *! for the moments of x*Q, L, is evaluated using the Gauss moments, M_i, and
 *! the orthogonal coefficients, a_(i,k). Sloan Eq. (B-101b) gives L as
 *! L_(i+1) = sum_( k=0,...,i ) a_(i,k)*M_(k+i+1). The ratio is defined as:
 *! normalization ratio = L_i/N_(i-1)
 */
void SloanRadauQuadrature::evaluateOrthogonalNormalizationRatio(
        std::vector<long_float>& normalization_ratios,
        const std::vector<std::vector<long_float> >& orthogonal_coefficients,
        const std::vector<long_float>& normalization_factors_N,
        const std::vector<long_float>& radau_moments,
        const int i ) const
{
  // Make sure i is valid
  testPrecondition( i > 0 );
  testPrecondition( 2*i - 1 <= radau_moments.size() );

  long_float normalization_factor_L = long_float(0);

  for ( int k = 0; k <= i-1; ++k )
  {
    normalization_factor_L += orthogonal_coefficients[i-1][k]*
                              radau_moments[k+i];
  }
  normalization_ratios[i] = normalization_factor_L.convert_to<long_float>()
                            /normalization_factors_N[i-1];
}

// Evaluate the ith mean coefficients for orthogonal polynomial recursion relation
/*! \details The ith mean coefficient can be calculated from the Q and x*Q normalization factors:
 *! mean_coefficient_i = L_i/N_(i-1) - L_(i-1)/N_(i-2)
 *! see Sloan Eq. (B-103b)
 */
long_float SloanRadauQuadrature::evaluateMeanCoefficient(
        const std::vector<long_float>& normalization_ratios,
        const int i ) const
{
  // Make sure i and arrays are valid
  testPrecondition( i > 0 );
  testPrecondition( i <= normalization_ratios.size() );

  if ( i == 1 )
  {
    return normalization_ratios[i];
  }
  else
  {
    return normalization_ratios[i] - normalization_ratios[i-1];
  }
}

// Evaluate the ith row of coefficients of of the orthogonal polynomial Q
/*! \details Given the coefficients for the rows before the ith row the ith
 *! row can be found using a recursion relationship for the coefficients of the
 *! orthogonal polynomial as given by Sloan: Eq (B-106).
 *! Note: The ith row should be initialized to zero when the function is called
 *! since all coefficients were k > i are zero.
 */
void SloanRadauQuadrature::evaluateOrthogonalCoefficients(
                std::vector<std::vector<long_float> >& orthogonal_coefficients,
                const std::vector<long_float>& variances,
                const std::vector<long_float>& mean_coefficients,
                const int i) const
{
  // Make sure i is valid
  testPrecondition( i >= 0 );

  // All terms for k > i are zero

  /* For k = i the 2nd and third term will go to zero. Therefore, all c_(i,i)
   * terms will be equal to the c_(0,0) term, which is set to unity.
   */
  orthogonal_coefficients[i][i] = long_float(1);

  if ( i == 1 )
  {
    // The 1st and 3rd term in the recursion relationship will go to zero for k = 0
    orthogonal_coefficients[i][0] =
                -mean_coefficients[i]*orthogonal_coefficients[i-1][0];
  }
  else if ( i > 1 )
  {
    // The 1st term in the recursion relationship will go to zero for k = 0
    orthogonal_coefficients[i][0] =
                         -mean_coefficients[i]*orthogonal_coefficients[i-1][0]
                         -variances[i-1]*orthogonal_coefficients[i-2][0];

    /* Use the recursion relationship for all other values of k < i.
     * When k > i all coeffcients reduce to zero.
     */
    for ( int k = 1; k < i; ++k )
    {
      orthogonal_coefficients[i][k] =
                        orthogonal_coefficients[i-1][k-1] -
                        mean_coefficients[i]*orthogonal_coefficients[i-1][k] -
                        variances[i-1]*orthogonal_coefficients[i-2][k];
    }
  }
}

// Evaluate the normalization factors, N_i for the orthogonal polynomial, Q
/*! \details N can be evaluated using the Gauss moments, M_i, and
 *! the orthogonal coefficients, a_(i,k) ( see Sloan Eq. (B-100b) ):
 *! N_i = sum_( k=0,...,i ) a_(i,k)*M_(k+i)
 */
void SloanRadauQuadrature::evaluateOrthogonalNormalizationFactor(
        std::vector<long_float>& normalization_factors_N,
        const std::vector<std::vector<long_float> >& orthogonal_coefficients,
        const std::vector<long_float>& radau_moments,
        const int i ) const
{
  // Make sure i is valid
  testPrecondition( 2*i < radau_moments.size() );

  long_float normalization_factor_N = long_float(0);

  for ( int k = 0; k <= i; ++k )
  {
    normalization_factor_N += orthogonal_coefficients[i][k]*
                              radau_moments[k+i];
  }

  normalization_factors_N[i] = normalization_factor_N.convert_to<long_float>();
}

// Evaluate the variance of the moments of the orthogonal polynomial, Q_i
/*! \details The variance can be found from the ratio of the orthogonal
 *! normalization factor to the i-1 factor: variance = N_i/N_(i-1)
 *! see Sloan Eq. (B-99)
 */
long_float SloanRadauQuadrature::evaluateVariance(
        const std::vector<long_float>& normalization_factors_N,
        const int i ) const
{
  // Make sure i is valid
  testPrecondition( i > 0 );
  testPrecondition( i <= normalization_factors_N.size() );

  return normalization_factors_N[i]/normalization_factors_N[i-1];
}

// Evaluate the nth orthogonal polynomial at x, Q_n(x)
/*! \details The orthogonal polynomial can be evaluated at a value x using the
 *! variance and the mean coefficients in the following recursion relationship:
 *! Q_n(x) = ( x - mean_coefficient_i )Q_(n-1)(x) - variance_(i-1)Q_(n-2)(x)
 *! see Sloan Eq. (B-97) */
long_float SloanRadauQuadrature::evaluateOrthogonalPolynomial(
        const std::vector<long_float>& variances,
        const std::vector<long_float>& mean_coefficients,
        const long_float x,
        const int i ) const
{
  // Make sure i is valid
  testPrecondition( i >= 0 )

  long_float q_n, q_n_minus_one, q_n_minus_two;

  if ( i == 0 )
  {
    return long_float(1);
  }
  else
  {
    // Set the i = 1 case ( q_n_minus_two term goes to zero )
    q_n = x - mean_coefficients[1];

    // Update for i > 1
    q_n_minus_two = long_float(1);
    q_n_minus_one = q_n;
    for ( int k = 2; k <= i; ++k )
    {
      // Use recursion relationship to calculate q_k(x)
      q_n = ( x - mean_coefficients[k] )*q_n_minus_one -
                          variances[k-1]*q_n_minus_two;

      // Update for next loop (k+1)
      q_n_minus_two = q_n_minus_one;
      q_n_minus_one = q_n;
    }
  }
  return q_n;
}

// Evaluate the roots of the nth orthogonal polynomial using the roots of the (n-1)th
/*! \details The roots of the nth orthogonal polynomial are found through a binary
 *! search using the (n-1)th roots as an upper and lower bound.
 *! The roots array should pass in the (n-1)th roots
 *! Returns true if usable root has been found, else returns false.
 */
bool SloanRadauQuadrature::evaluateOrthogonalRoots(
        std::vector<std::vector<long_float> >& roots,
        const std::vector<long_float>& variances,
        const std::vector<long_float>& mean_coefficients,
        const int i ) const
{
  // Make sure i is valid
  testPrecondition( i > 1 )

  bool root_found = false;
  std::vector<long_float> root_bounds( i+1 ), polynomial_at_bounds( i +1 );

  // Set the absolute lower and upper bound for cosine angle ( -1, +1 )
  root_bounds[0] = -long_float(1);
  root_bounds[i] = long_float(1);

  // Use the (n-1)th roots as bounds for the nth roots
  for ( int k = 1; k < i; ++k )
  {
    root_bounds[k] = roots[i-1][k-1];
  }

  // Check that the orthogonal polynomial has the correct signs at the end points ( -1, +1 )
  long_float polynomial_at_pos_one = evaluateOrthogonalPolynomial(
                                        variances,
                                        mean_coefficients,
                                        long_float(1),
                                        i );

  // The Legendre expansion should always be positive at 1.0
  if ( polynomial_at_pos_one <= long_float(0) )
  {
    // No root found
    return root_found;
  }

  long_float polynomial_at_neg_one = evaluateOrthogonalPolynomial(
                                            variances,
                                            mean_coefficients,
                                            -long_float(1),
                                            i );

  // The sign of the Legendre expansion at -1.0 will always be -1.0^i
  if ( polynomial_at_neg_one*pow( -long_float(1), i ) < long_float(0) )
  {
    // No roots found
    return root_found;
  }

  long_float remainder,  lower_bound,          upper_bound,
                          polynomial_at_lower,  polynomial_at_upper;

  for ( int k = 0; k < i; ++k )
  {
    // Set lower and upper bound for root[i][k]
    lower_bound = root_bounds[k];
    upper_bound = root_bounds[k+1];

    // Set the value of the orthogonal polynomial at lower bound
    polynomial_at_lower = evaluateOrthogonalPolynomial( variances,
                                                        mean_coefficients,
                                                        lower_bound,
                                                        i );

    // Set the value of the orthogonal polynomial at upper bound
    polynomial_at_upper = evaluateOrthogonalPolynomial( variances,
                                                        mean_coefficients,
                                                        upper_bound,
                                                        i );
    root_found = false;

    /* The orthogonal polynomial should be zero at the root, therefore one of
     * the bounds should be below zero and the other above zero. */
    if ( polynomial_at_upper*polynomial_at_lower > long_float(0) )
    {
      // no roots found
      return root_found;
    }

    // binary search until a root is found or there is no where left to search
    while ( !root_found )
    {
      // Try the midpoint between bounds as a possible root
      roots[i][k] = ( lower_bound + upper_bound )/long_float(2);

      // If root search range has vanished exit while loop
      if (roots[i][k] == lower_bound || roots[i][k] == upper_bound )
      {
        // the exact roots[k] could not be found
        root_found = true;
      }

      // If roots[k] is a true root the orthogonal polynomial should go to zero
      remainder = evaluateOrthogonalPolynomial( variances,
                                                mean_coefficients,
                                                roots[i][k],
                                                i );

      //std::cout << "remainder = " << remainder << std::endl;

      if ( remainder*polynomial_at_lower > long_float(0) )
      {
        // roots[k] is too low, try a higher value
        lower_bound = roots[i][k];
        polynomial_at_lower = remainder;
      }
      else if ( remainder*polynomial_at_lower < long_float(0) )
      {
        // roots[k] is too high, try a lower value
        upper_bound = roots[i][k];
      }
      else
      {
        // roots[k] has been found exactly
        root_found = true;
      }
    }
  }
  // All roots where found
  return 1;
}

// Estimate an extra (i+1)th mean coefficient for the ith orthogonal polynomial
/*! \details For an odd legendre expansion it may be possible to approximate the
 *! n+1expansion and increase the number of possible roots by 1.
 */
void SloanRadauQuadrature::estimateExtraMeanCoefficient(
        std::vector<long_float>& mean_coefficients,
        const std::vector<long_float>& variances,
        const std::vector<long_float>& normalization_factors_N,
        const std::vector<long_float>& radau_moments,
        const int number_of_roots ) const
{
  // Make sure number_of_roots is valid
  testPrecondition( number_of_roots > 1 )

  long_float extra_mean_coefficients;

  // evaluate the ratio of the nth and (n-1)th orthogonal polynomial at +1
  long_float ratio_at_pos_one =
      evaluateOrthogonalPolynomial( variances,
                                    mean_coefficients,
                                    long_float(1),
                                    number_of_roots - 2 )/
      evaluateOrthogonalPolynomial( variances,
                                    mean_coefficients,
                                    long_float(1),
                                    number_of_roots - 1 );

  // evaluate the ratio of the nth and (n-1)th orthogonal polynomial at -1
  long_float ratio_at_neg_one =
      evaluateOrthogonalPolynomial( variances,
                                    mean_coefficients,
                                    -long_float(1),
                                    number_of_roots - 2 )/
      evaluateOrthogonalPolynomial( variances,
                                    mean_coefficients,
                                    -long_float(1),
                                    number_of_roots - 1 );

  long_float poly_n_minus_one;
  long_float poly_n = evaluateOrthogonalPolynomial( variances,
                                                      mean_coefficients,
                                                      long_float(1),
                                                      1 );

  long_float parm = d_legendre_expansion_moments[0] -
                    normalization_factors_N[0]/poly_n;

  for ( int k = 2; k < number_of_roots; ++k )
  {
    poly_n_minus_one = poly_n;
    poly_n = evaluateOrthogonalPolynomial( variances,
                                           mean_coefficients,
                                           long_float(1),
                                           k );

     parm += -normalization_factors_N[k]/( poly_n_minus_one*poly_n );
  }

  extra_mean_coefficients =
         -variances[number_of_roots-1]/long_float(2)*
         ( ratio_at_pos_one + ratio_at_neg_one )
         -normalization_factors_N[number_of_roots-1]/
         ( long_float(2)*poly_n*poly_n*parm );

  mean_coefficients[number_of_roots] = extra_mean_coefficients;

//std::cout << "extra_mean_coefficients=\t "<< extra_mean_coefficients<<std::endl;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_SloanRadauQuadrature.cpp
//---------------------------------------------------------------------------//
