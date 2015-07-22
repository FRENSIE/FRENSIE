//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussLegendreQuadratureKernel.hpp
//! \author Luke Kersting
//! \brief Gauss - Legendre quadrature kernel declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_LEGENDRE_QUADRATURE_KERNEL_HPP
#define UTILITY_GAUSS_LEGENDRE_QUADRATURE_KERNEL_HPP

// Boost Includes
#include <boost/multiprecision/cpp_dec_float.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_TwoDArray.hpp>

namespace Utility{

typedef boost::multiprecision::cpp_dec_float_50 long_float;

//! Return the Gauss moments of the legendre expansion of a function, f(x)
void getGaussMoments( const Teuchos::Array<long_float>& legendre_expansion_moments,
                      Teuchos::Array<long_float>& gauss_moments );

//! Return the coefficients of the legendre expansion of x^n
void getLegendrePowerExpansionCoefficients( 
                      Teuchos::TwoDArray<long_float>& coefficients,
                      const int power = 0 );
} // end Utility namespace

#endif // end UTILITY_GAUSS_LEGENDRE_QUADRATURE_KERNEL_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussLegendreQuadratureKernel.hpp
//---------------------------------------------------------------------------//
