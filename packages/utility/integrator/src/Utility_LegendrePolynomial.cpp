//---------------------------------------------------------------------------//
//!
//! \file   Utility_LegendrePolynomial.cpp
//! \author Luke Kersting
//! \brief Legendre Polynomials definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_LegendrePolynomial.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Evaluate the Legendre Polynomial at the given value and order
double getLegendrePolynomial( const double value,
                              const int polynomial_order )
{
  // The first two legendre polynomials
  double P0 = 1.0;
  double P1 = value;

  if ( polynomial_order == 0 )
  {
    return P0;
  }
  else if ( polynomial_order == 1 )
  {
    return P1;
  }
  else
  {
    double p_n_minus_2 = P0;
    double p_n_minus_1 = P1;
    double p_n;

    for ( int i = 2; i <= polynomial_order; ++i)
    {
      p_n = ( ( 2.0*i - 1.0 )*value*p_n_minus_1 - ( i - 1.0 )*p_n_minus_2 )/i;

      p_n_minus_2 = p_n_minus_1;
      p_n_minus_1 = p_n;
    }

    return p_n;
  }
}

// Evaluate the Legendre Polynomial at the given value and order
long double getLegendrePolynomial( const long double value,
                                   const int polynomial_order )
{
  // The first two legendre polynomials
  long double P0 = 1.0L;
  long double P1 = value;

  if ( polynomial_order == 0 )
  {
    return P0;
  }
  else if ( polynomial_order == 1 )
  {
    return P1;
  }
  else
  {
    long double p_n_minus_2 = P0;
    long double p_n_minus_1 = P1;
    long double p_n;

    for ( int i = 2; i <= polynomial_order; ++i)
    {
      p_n = ( ( 2.0L*i - 1.0L )*value*p_n_minus_1 - ( i - 1.0L )*p_n_minus_2 )/i;

      p_n_minus_2 = p_n_minus_1;
      p_n_minus_1 = p_n;
    }

    return p_n;
  }
}

// Evaluate the derivative of the Legendre Polynomial at the given value and order
double getLegendrePolynomialDerivative( const double value,
                                        const int polynomial_order )
{
  if ( polynomial_order == 0 )
  {
    return 0.0;
  }
  else if ( polynomial_order == 1 )
  {
    return 1.0;
  }
  else
  {
    double p_n_minus_1 = getLegendrePolynomial( value, polynomial_order -1 );
    double p_n = getLegendrePolynomial( value, polynomial_order );

    return ( value*p_n - p_n_minus_1 )*polynomial_order/( value*value -1.0 );
  }
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_LegendrePolynomial.cpp
//---------------------------------------------------------------------------//
