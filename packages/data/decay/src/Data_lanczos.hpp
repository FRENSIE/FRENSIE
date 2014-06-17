//---------------------------------------------------------------------------//
//!
//! \file   Data_lanczos.hpp
//! \author CJ Solomon
//! \brief  lanczos
//!
//---------------------------------------------------------------------------//

#ifndef DATA_LANCZOS_HPP
#define DATA_LANCZOS_HPP

#include <cmath>
#include <complex>

#include "Data_PhysicalConstants.hpp"

namespace data {

namespace lanczos {

const static int g = 7;

const static double p[g+2] = 
  {  0.99999999999980993, 676.5203681218851,   -1259.1392167224028, 
   771.32342877765313,   -176.61502916214059,     12.507343278686905, 
    -0.13857109526572012,   9.9843695780195716e-6, 1.5056327351493116e-7};

std::complex<double> gamma(const std::complex<double>& z);

}

} // end namespace data
#endif // DATA_LANCZOS_HPP

//---------------------------------------------------------------------------//
// end Data_lanczos.hpp
//---------------------------------------------------------------------------//
