//---------------------------------------------------------------------------//
//!
//! \file   Data_FermiBetaTheory.cpp
//! \author CJ Solomon
//! \brief  Fermi Beta Theory
//!
//---------------------------------------------------------------------------//

#include "Data_FermiBetaTheory.hpp"

namespace data {

FermiBetaTheory::FermiBetaTheory(const unsigned int& z, const unsigned int& a, const double& q, bool is_positron) {
  m_z = z;
  m_a = a;
  m_q = q;
  m_is_positron = is_positron;
}

void FermiBetaTheory::Spectrum(Histogram& h) {
  using namespace physcon;

  const double ep = m_q + mec2;

  std::vector<double> bincs = h.GetBinCenters();
  
  for(unsigned int i=0; i < bincs.size(); i++) {
    double e = bincs.at(i);
    if( e >= m_q ) {
      h.Set((int) i,0.0);
    }
    else {
      double val = g_fermi*g_fermi / (2.0*pow(physcon::pi,3)*pow(hbar,7)*pow(c_light,6)) *
        sqrt(pow(e+mec2,2.0) - mec2*mec2) * (e+mec2) * pow(ep-(e+mec2),2.0);

      h.Set((int) i, val*FermiFunction( (e+mec2)/mec2 ));
    }
  }

  h.Normalize();
}

double FermiBetaTheory::FermiFunction(const double& w){
  using namespace boost::math;
  using namespace physcon;

  const double eta = sqrt( w*w - 1.0 );
  const double s = sqrt(1.0 - pow( (double) m_z/137.0,2)) - 1.0;
  const double y = (m_is_positron ? - (double) m_z : (double) m_z) / 137.0 * w / eta;
  const double r = 1.12 * pow( (double) m_a,0.333333);  // approximation from cottingham & greenwood

  double p1 = 4.0 * (1.0 + s/2.0) / pow(gamma(3.0+2.0*s),2);
  double p2 = pow(2.0*r*mec2 / (hbar * c_light), 2.0*s);
  double p3 = pow(eta, 2.0*s) * exp(pi*y);
  double p4 = pow(abs(lanczos::gamma(1.0 + s + std::complex<double>(0,1)*y)), 2.0);

  return p1*p2*p3*p4;
}

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_FermiBetaTheory.cpp
//---------------------------------------------------------------------------//
