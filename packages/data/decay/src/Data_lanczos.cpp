//---------------------------------------------------------------------------//
//!
//! \file   Data_lanczos.cpp
//! \author CJ Solomon
//! \brief  lanczos
//!
//---------------------------------------------------------------------------//

#include "Data_lanczos.hpp"

namespace data {

namespace lanczos {

std::complex<double> gamma(const std::complex<double>& z) {
  if( z.real() < 0.5 ) {
    return physcon::pi / sin(physcon::pi*z)*gamma(1.0-z);
  }
  else {
    std::complex<double> zp = z - 1.0;

    std::complex<double> x = p[0];
    for(int i=1; i < g+2; i++ ) {
      x += p[i]/(zp+std::complex<double>(i,0));
    }

    std::complex<double> t = zp + (double) g + 0.5;

    return sqrt(2.0*physcon::pi) * pow(t,zp+0.5) * exp(-t) * x;
  }
}

} // end namespace lanczos 

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_lanczos.cpp
//---------------------------------------------------------------------------//
