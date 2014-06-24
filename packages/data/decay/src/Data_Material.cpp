//---------------------------------------------------------------------------//
//!
//! \file   Data_Material.cpp
//! \author CJ Solomon
//! \brief  Material
//!
//---------------------------------------------------------------------------//

#include "Data_Material.hpp"

namespace data {

Material::Material() {
  m_mden = 0.0;
  m_aden = 0.0;
}

Material::Material(const AbundanceLib& al, const std::vector<unsigned int>& szas, const std::vector<double>& fracs, MatFType ftype, double den, MatFType dtype) {
  Make(al, szas, fracs, ftype, den, dtype);
}

void Material::Make(const AbundanceLib& al, const std::vector<unsigned int>& szas, const std::vector<double>& fracs, MatFType ftype, double den, MatFType dtype) {
  assert( szas.size() != 0 );
  assert( szas.size() == fracs.size() );
  
  // normalize the fractions
  double fsum = 0.0;
  std::vector<double> cfracs = fracs;
  for(unsigned int i=0; i<fracs.size(); i++) {
    fsum += fracs.at(i);
  }
  for(unsigned int i=0; i<fracs.size(); i++) {
    cfracs[i] /= fsum;
  }

  // populate the m_sza_data set and breakout natural zaids to isotopics
  if( ftype == Material::ATOM ) { // atom fractions provided
    
    // populate isotopic atom fractions and masses
    for(unsigned int i=0; i<szas.size(); i++) {
      unsigned int s, z, a;
      utils::getNumsFromSZA(szas.at(i), s, z, a);

      if( a == 0 ) {
        std::vector<unsigned int> iso_szas = al.GetIsosForZ(z);
        for(unsigned int j=0; j<iso_szas.size(); j++) {
          double abund = al.GetAbundance(iso_szas[j]);
          if( abund > 0.0 ) {
            m_sza_data[iso_szas[j]].m_afrac = cfracs[i]*al.GetAbundance(iso_szas[j]);
            m_sza_data[iso_szas[j]].m_mass = al.GetMass(iso_szas[j]);
          }
        }
      }
      else {
        m_sza_data[szas.at(i)].m_afrac = cfracs[i];
        m_sza_data[szas.at(i)].m_mass = al.GetMass(szas.at(i));
      }
    }

    // populate isotopic mass fractions
    double sum = 0.0;
    for(std::map<unsigned int,MatSZAData>::iterator it=m_sza_data.begin(); it!=m_sza_data.end(); it++) {
      it->second.m_mfrac = it->second.m_afrac * it->second.m_mass;
      sum += it->second.m_mfrac;
    }
    for(std::map<unsigned int,MatSZAData>::iterator it=m_sza_data.begin(); it!=m_sza_data.end(); it++) {
      it->second.m_mfrac /= sum;
    }

  }
  else { // mass fractions provided

    // populate atom fractions for provided isotopes
    double sum = 0.0;
    for(unsigned int i=0; i<szas.size(); i++) {
      m_sza_data[szas[i]].m_mass = al.GetMass(szas[i]);
      m_sza_data[szas[i]].m_afrac = cfracs[i] / m_sza_data[szas[i]].m_mass;
      sum += m_sza_data[szas[i]].m_afrac;
    }
    for(unsigned int i=0; i<szas.size(); i++) {
      m_sza_data[szas[i]].m_afrac /= sum;
    }

    // break out natural isotopes if any
    std::map<unsigned int,MatSZAData> new_sza_data;
    for(std::map<unsigned int,MatSZAData>::iterator it=m_sza_data.begin(); it!=m_sza_data.end(); it++) {
      unsigned int s, z, a;
      utils::getNumsFromSZA(it->first, s, z, a);

      if( a == 0 ) {
        std::vector<unsigned int> iso_szas = al.GetIsosForZ(z);
        for(unsigned int i=0; i<iso_szas.size(); i++) {
          double abund = al.GetAbundance(iso_szas[i]);
          if( abund > 0.0 ) {
            new_sza_data[iso_szas[i]].m_afrac = it->second.m_afrac * abund;
            new_sza_data[iso_szas[i]].m_mass = al.GetMass(iso_szas[i]);
          }
        }
      }
      else {
        new_sza_data[it->first].m_afrac = it->second.m_afrac;
        new_sza_data[it->first].m_mass = it->second.m_mass;
      }
    }
    m_sza_data = new_sza_data;

    // populate isotopic mass fractions
    sum = 0.0;
    for(std::map<unsigned int,MatSZAData>::iterator it=m_sza_data.begin(); it!=m_sza_data.end(); it++) {
      it->second.m_mfrac = it->second.m_afrac * it->second.m_mass;
      sum += it->second.m_mfrac;
    }
    for(std::map<unsigned int,MatSZAData>::iterator it=m_sza_data.begin(); it!=m_sza_data.end(); it++) {
      it->second.m_mfrac /= sum;
    }
  }

  // compute the densities
  if( dtype == Material::ATOM ) { // atom density provided
    m_aden = den;
    m_mden = 0.0;
    for(std::map<unsigned int,MatSZAData>::iterator it=m_sza_data.begin(); it!=m_sza_data.end(); it++) {
      m_mden += it->second.m_afrac * m_aden * 1e24 * it->second.m_mass / physcon::avagadro;
    }
  }
  else { // mass density provided
    m_mden = den;
    m_aden = 0.0;
    for(std::map<unsigned int,MatSZAData>::iterator it=m_sza_data.begin(); it!=m_sza_data.end(); it++) {
      m_aden += it->second.m_mfrac * m_mden * physcon::avagadro / it->second.m_mass / 1e24;
    }
  }
}

std::set<unsigned int> Material::GetSZAs() const {
  std::set<unsigned int> retval;
  for(std::map<unsigned int, MatSZAData>::const_iterator it=m_sza_data.begin(); it!=m_sza_data.end(); it++) {
    retval.insert( it->first );
  }
  return retval;
}

double Material::GetAtomFrac(const unsigned int& sza) const {
  double retval = 0.0;
  if(m_sza_data.find(sza) != m_sza_data.end() ) {
    retval = m_sza_data.at(sza).m_afrac;
  }

  return retval;
}

double Material::GetMassFrac(const unsigned int& sza) const {
  double retval = 0.0;
  if(m_sza_data.find(sza) != m_sza_data.end() ) {
    retval = m_sza_data.at(sza).m_mfrac;
  }

  return retval;
}

double Material::GetSZAMass(const unsigned int& sza) const {
  double retval = 0.0;
  if(m_sza_data.find(sza) != m_sza_data.end() ) {
    retval = m_sza_data.at(sza).m_mass;
  }

  return retval;
}

double Material::GetAtomDensity() const {
  return m_aden;
}

double Material::GetMassDensity() const {
  return m_mden;
}

void Material::Clear() {
  m_sza_data.clear();
  m_aden = 0.0;
  m_mden = 0.0;
}

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_Material.cpp
//---------------------------------------------------------------------------//
