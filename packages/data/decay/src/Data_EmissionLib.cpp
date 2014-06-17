//---------------------------------------------------------------------------//
//!
//! \file   Data_EmissionLib.cpp
//! \author CJ Solomon
//! \brief  Emission Library
//!
//---------------------------------------------------------------------------//

#include "Data_EmissionLib.hpp"

namespace data {

EmissionLib::EmissionLib() {};

void EmissionLib::SetFromEmissionFile(const EmissionFile& ef) {
  unsigned int sza = ef.GetS()*1000000 + ef.GetZ()*1000 + ef.GetA();

  SetSpectra(sza, EmissionSpectra(ef));
}

void EmissionLib::SetSpectra(const unsigned int& sza, const EmissionSpectra& es) {
  m_spectra[sza] = es;
}

std::set<unsigned int> EmissionLib::GetSZAs() const {
  std::set<unsigned int> retval;

  for(std::map<unsigned int, EmissionSpectra>::const_iterator it=m_spectra.begin(); it!=m_spectra.end(); it++) {
    retval.insert( it->first );
  }

  return retval;
}

EmissionSpectra EmissionLib::GetSpectra(const unsigned int& sza) const {
  EmissionSpectra retval;
  if( m_spectra.find(sza) != m_spectra.end() ) {
    retval = m_spectra.at(sza);
  }
  return retval;
}

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_EmissionLib.cpp
//---------------------------------------------------------------------------//
