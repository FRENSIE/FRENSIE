//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussLegendreQuadratureSet.hpp
//! \author Luke Kersting
//! \brief Gauss - Legendre quadrature set declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_LEGENDRE_QUADRATURE_SET_HPP
#define UTILITY_GAUSS_LEGENDRE_QUADRATURE_SET_HPP

// Std Lib Includes
#include <vector>

// Boost Includes
#include <boost/multiprecision/cpp_dec_float.hpp>

namespace Utility{

typedef boost::multiprecision::cpp_dec_float_50 long_float;

//! Return the Gauss moments of the legendre expansion of a function, f(x)
void getGaussMoments( const std::vector<long_float>& legendre_expansion_moments,
                      std::vector<long_float>& gauss_moments );

//! Return the coefficients of the legendre expansion of x^n
void getLegendrePowerExpansionCoefficients(
                      std::vector<std::vector<long_float> >& coefficients,
                      const int power = 0 );
} // end Utility namespace

#endif // end UTILITY_GAUSS_LEGENDRE_QUADRATURE_SET_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussLegendreQuadratureSet.hpp
//---------------------------------------------------------------------------//
