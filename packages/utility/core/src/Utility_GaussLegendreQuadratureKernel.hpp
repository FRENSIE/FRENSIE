//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussLegendreQuadratureKernel.hpp
//! \author Luke Kersting
//! \brief Gauss - Legendre quadrature kernel declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_LEGENDRE_QUADRATURE_KERNEL_HPP
#define UTILITY_GAUSS_LEGENDRE_QUADRATURE_KERNEL_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

namespace Utility{

//! Return the Gauss moments of the legendre expansion of a function, f(x)
void getGaussMoments( const Teuchos::Array<double>& legendre_expansion_moments,
                      Teuchos::Array<double>& gauss_moments );

//! Return the coefficients of the legendre expansion of x^n
void getLegendrePowerExpansionCoefficients( Teuchos::Array<double>& coefficients,
                                            const int power = 0 );
} // end Utility namespace

#endif // end UTILITY_GAUSS_LEGENDRE_QUADRATURE_KERNEL_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussLegendreQuadratureKernel.hpp
//---------------------------------------------------------------------------//
