//---------------------------------------------------------------------------//
//!
//! \file   Data_EmissionSpectra.cpp
//! \author CJ Solomon
//! \brief  Emission Spectra
//!
//---------------------------------------------------------------------------//

#include "Data_EmissionSpectra.hpp"

namespace data {

EmissionSpectra::EmissionSpectra() {}

EmissionSpectra::EmissionSpectra(const EmissionFile& ef) {
  FromEmissionFile(ef);
}

void EmissionSpectra::FromEmissionFile(const EmissionFile& ef) {
  // handle discrete emissions
  std::vector<int> endf_pts = ef.GetDiscreteTypes();
  for(unsigned int i=0; i<endf_pts.size(); i++) {
    EmissionSpectrum spc;
    for(unsigned int j=0; j<ef.GetDiscreteNumber(endf_pts[i]); j++) {
      DiscreteEmission de = ef.GetDiscrete(endf_pts[i],j);
      if( endf_pts[i] == endf::decay::BETAM || endf_pts[i] == endf::decay::BETAP ) {
        FermiBetaTheory fbt(ef.GetZ(), ef.GetA(), de.GetEnergy(), endf_pts[i] == endf::decay::BETAM ? false : true);
        Histogram h = DefaultContinua::GetDefaultContinuum(endf_pts[i]);
        fbt.Spectrum(h);
        spc.AddContinuum( h*de.GetIntensity() );
      }
      else {
        spc.AddDiscrete( de );
      }
    }

    m_spectra[ endf_pts[i] ] += spc;
  }

  // handle continuum emissions
  endf_pts = ef.GetContinuumTypes();
  for(unsigned int i=0; i<endf_pts.size(); i++) {
    EmissionSpectrum spc;
    for(unsigned int j=0; j<ef.GetContinuumNumber(endf_pts[i]); j++) {
      std::vector<double> energy = ef.GetContinuum(endf_pts[i],j).GetEnergy();
      std::vector<double> intensity = ef.GetContinuum(endf_pts[i],j).GetIntensity();
      if( energy.size() == intensity.size() ) {
        if( energy[0] != 0.0 ) {
          energy.insert(energy.begin(),0.0);
        }
        else {
          intensity.erase(intensity.begin());
        }
      }
      Histogram cont(energy, intensity);
      spc.AddContinuum( cont );
    }

    m_spectra[ endf_pts[i] ] += spc;
  }

  // handle watt spectra
  endf_pts = ef.GetWattSpectrumTypes();
  for(unsigned int i=0; i<endf_pts.size(); i++) {
    EmissionSpectrum spc;

    WattSpectrum ws = ef.GetWattSpectrum(endf_pts[i]);
    double wss = ef.GetWattScale(endf_pts[i]);

    Histogram cont = DefaultContinua::GetDefaultContinuum(endf_pts[i]);
    std::vector<double> cont_bins = cont.GetBins();
    for(unsigned int j=0; j<cont.Size(); j++) {
      double value = 0.0;
      if( j==0 ) {
        value = ws.cdf(cont_bins[j]) * wss;
      }
      else {
        value = (ws.cdf(cont_bins[j]) - ws.cdf(cont_bins[j-1])) * wss;
      }
      if( value < 0.0 )
        value = 0.0;
      cont.Set((int) j, value);
    }

    spc.AddContinuum( cont );

    m_spectra[ endf_pts[i] ] += spc;
  }
}

void EmissionSpectra::SetSpectrum(const int& pt, const EmissionSpectrum& spc) {
  m_spectra[pt] = spc;
}

void EmissionSpectra::AddSpectrum(const int& pt, const EmissionSpectrum& spc) {
  m_spectra[pt] += spc;
}

std::vector<int> EmissionSpectra::GetParticleTypes() const {
  std::vector<int> retval;
  
  for(std::map<int, EmissionSpectrum>::const_iterator it=m_spectra.begin(); it!=m_spectra.end(); it++) {
    retval.push_back(it->first);
  }

  return retval;
}

bool EmissionSpectra::HasSpectrum(const int& pt) const {
  bool retval = false;
  if( m_spectra.find(pt) != m_spectra.end() ) {
    retval = true;
  }
  return retval;
}

EmissionSpectrum EmissionSpectra::GetSpectrum(const int& pt) const {
  return m_spectra.at(pt);
}

void EmissionSpectra::EsToBrems(const double& z) {
  double c;
  if( z <= 4.0 ) {
    c = 2.96e-4;
  }
  else if( z > 4.0 && z <= 13.0 ) {
    c = 2.96e-4 + (z - 4.0) * 4.33e-6;
  }
  else if( z > 13.0 && z <= 29.0 ) {
    c = 3.35e-4 + (z - 13.0) * 4.02e-5;
  }
  else if( z > 29.0 && z <= 47.0 ) {
    c = 9.78e-4 + (z - 29.0) * 4.90e-5;
  }
  else if( z > 47.0 && z <= 79.0 ) {
    c = 1.86e-3 + (z - 47.0) * -1.09e-5;
  }
  else if( z > 79.0 && z <= 92.0 ) {
    c = 1.51e-3 + (z - 79.0) * -1.92e-5;
  }
  else if( z > 92.0 ) {
    c = 1.26e-3;
  }

  using namespace boost::assign;
  std::vector<int> brems_ptypes;
  brems_ptypes += endf::decay::BETAM, endf::decay::ELECTRON;

  for(std::vector<int>::iterator it=brems_ptypes.begin(); it!=brems_ptypes.end(); it++) {
    if( m_spectra.find(*it) == m_spectra.end() )
      continue;

    Histogram photon_brems = DefaultContinua::GetDefaultContinuum(endf::decay::BREMS);

    const EmissionSpectrum& es = m_spectra.at(*it);

    for(unsigned int i=0; i<es.GetDNumber(); i++) {
      double denergy = es.GetDEnergy(i);
      double dintensity = es.GetDIntensity(i);
      for(unsigned int j=0; j<photon_brems.Size() && photon_brems.Bin(j) < denergy; j++) {
        double b = photon_brems.Bin(j);
        double minb = (j == 0 ? photon_brems.MinBin() : photon_brems.Bin(j-1));
        double value = c * z * (denergy-b) / b * dintensity * (b - minb);
        photon_brems.Set((int) j, photon_brems.Get((int) j) + value);
      }
    }

    for(unsigned int i=0; i<es.GetCNumber(); i++) {
      double cenergy = es.GetCEnergy(i);
      double cintensity = es.GetCIntensity(i);
      for(unsigned int j=0; j<photon_brems.Size() && photon_brems.Bin(j) < cenergy; j++) {
        double b = photon_brems.Bin(j);
        double minb = (j == 0 ? photon_brems.MinBin() : photon_brems.Bin(j-1));
        double value = c * z * (cenergy-b) / b * cintensity * (b - minb);
        photon_brems.Set((int) j, photon_brems.Get((int) j) + value);
      }
    }

    EmissionSpectrum pbrems;
    pbrems.AddContinuum( photon_brems );

    m_spectra[endf::decay::BREMS] += pbrems;
    m_spectra.erase(*it);
  }
}

EmissionSpectra EmissionSpectra::ToMCNPTypes(bool add_brems_to_photon) const {
  EmissionSpectra retval;
  for(std::map<int, EmissionSpectrum>::const_iterator it=m_spectra.begin(); it!=m_spectra.end(); it++) {
    retval.m_spectra[ endfdecay2mcnp.at( (endf::decay::DecayTyp) it->first ) ] += it->second;
  }

  if( add_brems_to_photon && retval.m_spectra.find(mcnp::BREMS) != retval.m_spectra.end() ) {
    retval.m_spectra[mcnp::PHOTON] += retval.m_spectra.at(mcnp::BREMS);
    retval.m_spectra.erase(mcnp::BREMS);
  }

  return retval;
}
  

void EmissionSpectra::Clear() {
  m_spectra.clear();
}

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_EmissionSpectra.cpp
//---------------------------------------------------------------------------//
