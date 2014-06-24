//---------------------------------------------------------------------------//
//!
//! \file   Data_DecayMaterial.cpp
//! \author CJ Solomon
//! \brief  Decay Material
//!
//---------------------------------------------------------------------------//

#include "Data_DecayMaterial.hpp"

namespace data {

DecayMaterial::DecayMaterial() {}

DecayMaterial::DecayMaterial(const AbundanceLib& al, const std::vector<unsigned int>& szas, const std::vector<double>& fracs, MatFType ftype, double den, MatFType dtype) : 
  Material(al, szas, fracs, ftype, den, dtype) {
  m_decay_sza_data = m_sza_data;
  m_decay_aden = m_aden;
  m_decay_mden = m_mden;
};

void DecayMaterial::Age(const AbundanceLib& al, const DecayLib& dl, const double& t) {
  std::map<unsigned int, MatSZAData> new_decay_sza_data;

  // for each nuclide compute daughters at time t
  for(std::map<unsigned int, MatSZAData>::iterator it=m_decay_sza_data.begin(); it!=m_decay_sza_data.end(); it++) {
    std::map<unsigned int, double> unit_decay = dl.UnitDecay(it->first, t);
    for(std::map<unsigned int, double>::iterator ud=unit_decay.begin(); ud!=unit_decay.end(); ud++) {
      if( new_decay_sza_data.find(ud->first) == new_decay_sza_data.end() ) {
        new_decay_sza_data[ud->first].m_afrac = it->second.m_afrac * ud->second;
      }
      else {
        new_decay_sza_data[ud->first].m_afrac += it->second.m_afrac * ud->second;
      }
    }
  }

  // loop over resulting isotopes with atom fractions and compute the mass fractions and set the masses
  double sum = 0.0;
  for(std::map<unsigned int, MatSZAData>::iterator it=new_decay_sza_data.begin(); it!=new_decay_sza_data.end(); it++) {
    it->second.m_mass = al.GetMass(it->first);
    it->second.m_mfrac = it->second.m_afrac * it->second.m_mass;
    sum += it->second.m_mfrac;
  }
  for(std::map<unsigned int, MatSZAData>::iterator it=new_decay_sza_data.begin(); it!=new_decay_sza_data.end(); it++) {
    it->second.m_mfrac /= sum;
  }

  // compute mass density ASSUMING atom density is unchanged!
  m_decay_mden = 0.0;
  for(std::map<unsigned int, MatSZAData>::iterator it=new_decay_sza_data.begin(); it!=new_decay_sza_data.end(); it++) {
    m_decay_mden += it->second.m_afrac * m_decay_aden * 1e24 * it->second.m_mass / physcon::avagadro;
  }

  m_decay_sza_data = new_decay_sza_data;
}

void DecayMaterial::BuildSource(const DecayLib& dl, const EmissionLib& el, bool es_to_brems, double brems_z, double brems_mult) {
  for(std::map<unsigned int, MatSZAData>::iterator it=m_decay_sza_data.begin(); it!=m_decay_sza_data.end(); it++) {
    EmissionSpectra iso_spectra = el.GetSpectra(it->first);

    if( es_to_brems ) {
      if( brems_z == 0.0 ) {
        for(std::map<unsigned int, MatSZAData>::iterator it=m_decay_sza_data.begin(); it!=m_decay_sza_data.end(); it++) {
          unsigned int s, z, a;
          utils::getNumsFromSZA(it->first, s, z, a);
          brems_z += z * it->second.m_afrac;
        }
      }

      iso_spectra.EsToBrems(brems_z);
      if( iso_spectra.HasSpectrum(mcnp::BREMS) && brems_mult != 1.0 ) {
        EmissionSpectrum brems = m_spectra.GetSpectrum(mcnp::BREMS);
        brems *= brems_mult;
        m_spectra.SetSpectrum(mcnp::BREMS,brems);
      } 
    }

    // loop over particle types
    std::vector<int> ptypes = iso_spectra.GetParticleTypes();
    for(unsigned int i=0; i<ptypes.size(); i++) {
      EmissionSpectrum iso_spectrum = iso_spectra.GetSpectrum(ptypes[i]) * dl.GetDecayData(it->first).GetDecayConst() * it->second.m_afrac * m_decay_aden * 1e24;
      m_iso_spectra[it->first].SetSpectrum(ptypes[i],iso_spectrum);
      m_spectra.AddSpectrum(ptypes[i],iso_spectrum);
    }
  }
}

void DecayMaterial::Reset() {
  m_decay_sza_data = m_sza_data;
  m_decay_aden = m_aden;
  m_decay_mden = m_mden;

  m_iso_spectra.clear();
  m_spectra.Clear();
}

std::set<unsigned int> DecayMaterial::GetSZAs() const {
  std::set<unsigned int> retval;
  for(std::map<unsigned int, MatSZAData>::const_iterator it=m_decay_sza_data.begin(); it!=m_decay_sza_data.end(); it++) {
    retval.insert( it->first );
  }

  return retval;
}

double DecayMaterial::GetAtomFrac(const unsigned int& sza) const {
  double retval = 0.0;
  if(m_decay_sza_data.find(sza) != m_decay_sza_data.end() ) {
    retval = m_decay_sza_data.at(sza).m_afrac;
  }

  return retval;
}

double DecayMaterial::GetMassFrac(const unsigned int& sza) const {
  double retval = 0.0;
  if(m_decay_sza_data.find(sza) != m_decay_sza_data.end() ) {
    retval = m_decay_sza_data.at(sza).m_mfrac;
  }

  return retval;
}

double DecayMaterial::GetSZAMass(const unsigned int& sza) const {
  double retval = 0.0;
  if(m_decay_sza_data.find(sza) != m_decay_sza_data.end() ) {
    retval = m_decay_sza_data.at(sza).m_mass;
  }

  return retval;
}

double DecayMaterial::GetAtomDensity() const {
  return m_decay_aden;
}

double DecayMaterial::GetMassDensity() const {
  return m_decay_mden;
}

EmissionSpectra DecayMaterial::GetSpectra(unsigned int sza) const {
  EmissionSpectra retval;

  if( sza == 0 ) {
    retval = m_spectra;
  }
  else {
    if( m_iso_spectra.find(sza) != m_iso_spectra.end() ) {
      retval = m_iso_spectra.at(sza);
    }
  }

  return retval;
}

// std::set<unsigned int> DecayMaterial::GetDaughters(const DecayLib& dl) const {
//   std::set<unsigned int> retval;
//   for(std::map<unsigned int, MatSZAData>::const_iterator it=m_decay_sza_data.begin(); it!=m_decay_sza_data.end(); it++) {
//     std::set<unsigned int> daughters = dl.GetAllDaughters(it->first);
//     for(std::set<unsigned int>::iterator dit=daughters.begin(); dit!=daughters.end(); dit++) {
//       retval.insert(*dit);
//     }
//   }
//   return retval;
// }

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_DecayMaterial.cpp
//---------------------------------------------------------------------------//
