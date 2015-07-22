//---------------------------------------------------------------------------//
//!
//! \file   Utility_LegendrePolynomial.hpp
//! \author Luke Kersting
//! \brief Legendre Polynomials declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_LEGENDRE_POLYNOMIAL_HPP
#define UTILITY_LEGENDRE_POLYNOMIAL_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

namespace Utility{

//! Evaluate the Legendre Polynomial at the given value and order
double getLegendrePolynomial( const double value,
                              const int polynomial_order = 0 );

//! Evaluate the Legendre Polynomial at the given value and order
long double getLegendrePolynomial( const long double value,
                                   const int polynomial_order = 0 );

//! Evaluate the derivative of the Legendre Polynomial at the given value and order
double getLegendrePolynomialDerivative( const double value,
                                        const int polynomial_order = 0 );

} // end Utility namespace

#endif // end UTILITY_GUASS_KRONROD_QUADRATURE_KERNEL_HPP

//---------------------------------------------------------------------------//
// end Utility_LegendrePolynomial.hpp
//---------------------------------------------------------------------------//
