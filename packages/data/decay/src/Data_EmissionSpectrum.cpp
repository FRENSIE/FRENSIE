//---------------------------------------------------------------------------//
//!
//! \file   Data_EmissionSpectrum.cpp
//! \author CJ Solomon
//! \brief  Emission Spectrum
//!
//---------------------------------------------------------------------------//

#include "Data_EmissionSpectrum.hpp"

namespace data {

EmissionSpectrum::EmissionSpectrum() {
  m_dnorm = 0.0;
  m_cnorm = 0.0;
}

EmissionSpectrum& EmissionSpectrum::operator+=(const EmissionSpectrum& es) {
  // discrete piece
  for(unsigned int i=0; i<es.GetDNumber(); i++) {
    AddDiscrete( DiscreteEmission(es.GetDEnergy(i),
                                  es.GetDIntensity(i),
                                  es.GetDDecayType(i),
                                  es.GetDEnergyErr(i),
                                  es.GetDIntensityErr(i)) );
  }

  // continuum piece
  if(es.m_continuum.Size() > 0) {
    AddContinuum(es.m_continuum);
  }

  return *this;
}

EmissionSpectrum& EmissionSpectrum::operator*=(const double& d) {
  for(unsigned int i=0; i<GetDNumber(); i++) {
    m_discretes.at(i).SetIntensity( m_discretes.at(i).GetIntensity() * d, m_discretes.at(i).GetIntensityErr() * d );
  }
  m_dnorm *= d;

  if( m_continuum.Size() > 0 ) {
    m_continuum *= d;
    m_cnorm *= d;
  }

  return *this;
}

EmissionSpectrum& EmissionSpectrum::operator/=(const double& d) {
  for(unsigned int i=0; i<GetDNumber(); i++) {
    m_discretes.at(i).SetIntensity( m_discretes.at(i).GetIntensity() / d, m_discretes.at(i).GetIntensityErr() / d );
  }
  m_dnorm /= d;

  if( m_continuum.Size() > 0 ) {
    m_continuum /= d;
    m_cnorm /= d;
  }

  return *this;
}

void EmissionSpectrum::AddDiscrete(const DiscreteEmission& d) {
  m_discretes.push_back( d );
  m_dnorm += d.GetIntensity();
}

void EmissionSpectrum::SetContinuum(const Histogram& c) {
  m_continuum = c;

  m_cnorm = 0.0;
  int csize = c.Size();
  for(int i=0; i<csize; i++ ) {
    m_cnorm += c.Get(i);
  }
}

void EmissionSpectrum::AddContinuum(const Histogram& c) {
  double tsum = 0.0;
  if( m_continuum.Size() == 0 ) {
    m_continuum = c;

    double sum = 0.0;
    for(unsigned int i=0; i<m_continuum.Size(); i++) {
      sum += m_continuum.Get((int) i);
    }

    tsum = sum;
  }
  else {
    std::vector<double> bins = m_continuum.GetBins(true);
    std::vector<double> c_bins = c.GetBins(true);
    
    double sum = 0.0;
    for(unsigned int i=0; i<m_continuum.Size(); i++) {
      sum += m_continuum.Get((int) i);
    }

    double c_sum = 0.0;
    for(unsigned int i=0; i<c.Size(); i++) {
      c_sum += c.Get((int) i);
    }

    tsum = sum + c_sum;

    std::set<double> mset;
    mset.insert(bins.begin(),bins.end());
    mset.insert(c_bins.begin(),c_bins.end());

    bins.erase(bins.begin(),bins.end());
    bins.insert(bins.begin(),mset.begin(),mset.end());

    Histogram hist1(bins);
    Histogram hist2(bins);

    hist1.Convert(m_continuum);
    hist2.Convert(c);

    hist1 += hist2;

    m_continuum = hist1;
  }

  m_cnorm = 0.0;
  for(unsigned int i=0; i<m_continuum.Size(); i++ ) {
    m_cnorm += m_continuum.Get((int) i);
  }
}

unsigned int EmissionSpectrum::GetDNumber() const {
  return m_discretes.size();
}

double EmissionSpectrum::GetDEnergy(const unsigned int& i) const {
  return m_discretes.at(i).GetEnergy();
}

double EmissionSpectrum::GetDEnergyErr(const unsigned int& i) const {
  return m_discretes.at(i).GetEnergyErr();
}

double EmissionSpectrum::GetDIntensity(const unsigned int& i) const {
  return m_discretes.at(i).GetIntensity();
}

double EmissionSpectrum::GetDIntensityErr(const unsigned int& i) const {
  return m_discretes.at(i).GetIntensityErr();
}

unsigned int EmissionSpectrum::GetDDecayType(const unsigned int& i) const {
  return m_discretes.at(i).GetDecayType();
}

unsigned int EmissionSpectrum::GetCNumber() const {
  return m_continuum.Size();
}

double EmissionSpectrum::GetCEnergy(const unsigned int& i) const {
  return m_continuum.GetBins().at(i);
}

double EmissionSpectrum::GetCIntensity(const unsigned int& i) const {
  return m_continuum.Get((int) i);
}

double EmissionSpectrum::GetDNorm() const {
  return m_dnorm;
}

double EmissionSpectrum::GetCNorm() const {
  return m_cnorm;
}

const EmissionSpectrum operator+(const EmissionSpectrum& em1, const EmissionSpectrum& em2) {
  EmissionSpectrum retval(em1);
  retval += em2;
  return retval;
}

const EmissionSpectrum operator*(const double& d, const EmissionSpectrum& em) {
  EmissionSpectrum retval(em);
  retval *= d;
  return retval;
}

const EmissionSpectrum operator*(const EmissionSpectrum& em, const double& d) {
  EmissionSpectrum retval(em);
  retval *= d;
  return retval;
}

const EmissionSpectrum operator/(const EmissionSpectrum& em, const double& d) {
  EmissionSpectrum retval(em);
  retval /= d;
  return retval;
}

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_EmissionSpectrum.cpp
//---------------------------------------------------------------------------//
