//---------------------------------------------------------------------------//
//!
//! \file   Data_WattSpectrum.cpp
//! \author CJ Solomon
//! \brief  Watt Spectrum
//!
//---------------------------------------------------------------------------//

#include <cmath>

#include "Data_WattSpectrum.hpp"
#include "Data_PhysicalConstants.hpp"

namespace data {

WattSpectrum::WattSpectrum(double a, double b) {
  m_a = a;
  m_b = b;

  m_norm = sqrt(4.0/(physcon::pi*pow(m_a,3)*m_b))*exp(-m_a*m_b/4.0);
}

double WattSpectrum::pdf(double x) {
  return m_norm * exp(-x/m_a) * sinh(sqrt(m_b*x));
}

double WattSpectrum::cdf(double x) {
  return 0.5*(erf(sqrt(x/m_a)-sqrt(m_a*m_b)/2.0) + erf(sqrt(x/m_a)+sqrt(m_a*m_b)/2.0))
         - 2.0*m_a/sqrt(physcon::pi*pow(m_a,3)*m_b) * exp(-m_a*m_b/4.0) * exp(-x/m_a) * sinh(sqrt(m_b*x));
}

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_WattSpectrum.cpp
//---------------------------------------------------------------------------//
