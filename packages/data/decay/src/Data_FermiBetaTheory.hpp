//---------------------------------------------------------------------------//
//!
//! \file   Data_FermiBetaTheory.hpp
//! \author CJ Solomon
//! \brief  FermiBetaTheory
//!
//---------------------------------------------------------------------------//

#ifndef DATA_FERMI_BETA_THEORY_HPP
#define DATA_FERMI_BETA_THEORY_HPP

#include <vector>
#include <cmath>
#include <complex>

#include <boost/math/special_functions/gamma.hpp>

#include "Data_Histogram.hpp"
#include "Data_PhysicalConstants.hpp"
#include "Data_lanczos.hpp"

namespace data {

class FermiBetaTheory {
public:
  FermiBetaTheory(const unsigned int& z, const unsigned int& a, const double& q, bool is_positron=false);

  void Spectrum(Histogram& h);

private:
  unsigned int m_z, m_a;
  double m_q;
  bool m_is_positron;

  double FermiFunction(const double& w);
};

} // end namespace data

#endif // DATA_FERMI_BETA_THEORY_HPP

//---------------------------------------------------------------------------//
// end Data_FermiBetaTheory.hpp
//---------------------------------------------------------------------------//
