//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussLegendreQuadratureKernel.hpp
//! \author Luke Kersting
//! \brief Gauss - Legendre quadrature kernel declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_GaussLegendreQuadratureKernel.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{
void getLegendrePowerExpansionCoefficients( 
                                  Teuchos::TwoDArray<long double>& coefficients,
                                  const int power )
{
  coefficients[0][0] = 1.0;

  if ( power > 0 )
  {
    coefficients[1][0] = 0.0;
    coefficients[1][1] = 1.0;

    /* use recusion relationship to calculate the coefficients:
     * c_(n,l) = l/(2l-1) * c_(n-1,l-1) + (l+1)/(2l+3) * c_(n-1,l+1) */
    for ( int n = 2; n <= power; n++ )
    {
      // Set the 1st coefficient
      coefficients[n][0] = coefficients[n-1][1]/3.0;

      // Loop through the rest of the coefficients
      for ( int l = 1; l <= n; l++ )
      {
        coefficients[n][l] =          l/( 2.0*l - 1.0 )*coefficients[n-1][l-1] + 
                            ( l + 1.0 )/( 2.0*l + 3.0 )*coefficients[n-1][l+1];
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
void getGaussMoments( const Teuchos::Array<double>& legendre_expansion_moments,
                      Teuchos::Array<double>& gauss_moments )
{
  // Make sure the arrays are the same size
  testPrecondition( gauss_moments.size() == legendre_expansion_moments.size() );
  testPrecondition( gauss_moments.size() > 1 );

  // Make sure the zeroth moment is included
  //testPrecondition( legendre_expansion_moments[0] == 1.0 );

  int number_of_moments = legendre_expansion_moments.size();
  long double moment_n;
  Teuchos::Array<long double> coef_n_minus_one( number_of_moments +1), 
                              coef_n( number_of_moments +1);

  gauss_moments[0] = legendre_expansion_moments[0];
  gauss_moments[1] = legendre_expansion_moments[1];

  coef_n_minus_one[0] = 0.0;
  coef_n_minus_one[1] = 1.0;

  /* use recusion relationship to calculate the coefficients:
   * c_(n,l) = l/(2l-1) * c_(n-1,l-1) + (l+1)/(2l+3) * c_(n-1,l+1) */
  for ( int n = 2; n < number_of_moments; n++ )
  {
    // Set the 1st coefficient and its contribution to the gauss moment
    coef_n[0] = coef_n_minus_one[1]/3.0;
    moment_n = coef_n[0]*legendre_expansion_moments[0];

    // Loop through the rest of the coefficients and their contribution to the gauss moment
    for ( int l = 1; l <= n; l++ )
    {
      // Calculate coefficient n
      coef_n[l] = l/( 2.0*l - 1.0 )*coef_n_minus_one[l-1] + 
                      ( l + 1.0 )/( 2.0*l + 3.0 )*coef_n_minus_one[l+1];

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
// end Utility_GaussLegendreQuadratureKernel.hpp
//---------------------------------------------------------------------------//
