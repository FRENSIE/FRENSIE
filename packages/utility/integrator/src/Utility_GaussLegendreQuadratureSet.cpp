//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussLegendreQuadratureSet.hpp
//! \author Luke Kersting
//! \brief Gauss - Legendre quadrature set declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_GaussLegendreQuadratureSet.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{
void getLegendrePowerExpansionCoefficients(
                           std::vector<std::vector<long_float> >& coefficients,
                           const int power )
{
  testPrecondition( coefficients.size() == power+1 );

  // Set all the coefficients to 0
  for ( unsigned n = 0; n < coefficients.size(); ++n )
  {
    testPrecondition( coefficients[n].size() == power+1 );

    for ( unsigned i = 0; i < coefficients[n].size(); ++i )
    {
      coefficients[n][i] = 0.0;
    }
  }

  // Set the first coefficient to 1
  coefficients[0][0] = long_float(1);

  if ( power > 0 )
  {
    coefficients[1][0] = long_float(0);
    coefficients[1][1] = long_float(1);

    /* use recursion relationship to calculate the coefficients:
     * c_(n,l) = l/(2l-1) * c_(n-1,l-1) + (l+1)/(2l+3) * c_(n-1,l+1) */
    for ( int n = 2; n <= power; ++n )
    {
      // Set the 1st coefficient
      coefficients[n][0] = coefficients[n-1][1]/long_float(3);

      // Loop through the coefficients
      for ( int l = 1; l < n-1; ++l )
      {
        coefficients[n][l] =
            l/( long_float(2)*l - long_float(1) )*coefficients[n-1][l-1] +
            ( l + long_float(1) )/
            ( long_float(2)*l + long_float(3) )*coefficients[n-1][l+1];
      }

      // Set the last two coefficients
      for ( int l = n-1; l <= n; ++l )
      {
        coefficients[n][l] =
            l/( long_float(2)*l - long_float(1) )*coefficients[n-1][l-1];
      }
    }
  }
}

// Return the Gauss moments of the legendre expansion of a function, f(x)
/*! \details The Gauss moments, M_n, are found by summing the coefficients of a
 *! legendre expansion of x^n multipled by the legendre expansion of f(x).
 *! M_n = integral_(-1)^(1) x^n f(x) dx = sum_(l=0,..n) f_l c_(n,l).
 *! The zeroth moment should be included
 */
void getGaussMoments( const std::vector<long_float>& legendre_expansion_moments,
                      std::vector<long_float>& gauss_moments )
{
  // Make sure the arrays are the same size
  testPrecondition( gauss_moments.size() == legendre_expansion_moments.size() );
  testPrecondition( gauss_moments.size() > 1 );

  // Make sure the zeroth moment is included
  //testPrecondition( legendre_expansion_moments[0] == 1.0 );

  int number_of_moments = legendre_expansion_moments.size();
  long_float moment_n;
  std::vector<long_float> coef_n_minus_one( number_of_moments +1),
                          coef_n( number_of_moments +1);

  gauss_moments[0] = legendre_expansion_moments[0];
  gauss_moments[1] = legendre_expansion_moments[1];

  coef_n_minus_one[0] = long_float(0);
  coef_n_minus_one[1] = long_float(1);

  /* use recursion relationship to calculate the coefficients:
   * c_(n,l) = l/(2l-1) * c_(n-1,l-1) + (l+1)/(2l+3) * c_(n-1,l+1) */
  for ( int n = 2; n < number_of_moments; ++n )
  {
    // Set the 1st coefficient and its contribution to the gauss moment
    coef_n[0] = coef_n_minus_one[1]/long_float(3);
    moment_n = coef_n[0]*legendre_expansion_moments[0];

    // Loop through the rest of the coefficients and their contribution to the gauss moment
    for ( int l = 1; l <= n; ++l )
    {
      // Calculate coefficient n
      coef_n[l] = l/( long_float(2)*l - long_float(1) )*coef_n_minus_one[l-1] +
                  ( l + long_float(1) )/
                  ( long_float(2)*l + long_float(3) )*coef_n_minus_one[l+1];

      // Calculate moment n
      moment_n += coef_n[l]*legendre_expansion_moments[l];
    }
    gauss_moments[n] = moment_n;

    // Update coefficients
    coef_n_minus_one = coef_n;
  }
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GaussLegendreQuadratureSet.hpp
//---------------------------------------------------------------------------//
