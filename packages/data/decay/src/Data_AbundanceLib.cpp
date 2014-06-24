//---------------------------------------------------------------------------//
//!
//! \file   Data_AbundanceLib.cpp
//! \author CJ Solomon
//! \brief  Abundance Library
//!
//---------------------------------------------------------------------------//

#include "Data_AbundanceLib.hpp"

namespace data {

AbundanceLib::AbundanceLib() {}

AbundanceLib::AbundanceLib(const AbundanceFile& af) {
  UnpackString( af.PackString() );
}

void AbundanceLib::UnpackString(std::string af_packed_string) {
  std::stringstream ss;

  ss.str(af_packed_string);
  
  boost::archive::binary_iarchive ar(ss);

  ar & m_abundances;
};

double AbundanceLib::GetMass(const unsigned int& sza) const { 
  double retval = 0.0;

  unsigned int s = sza / 1000000;
  unsigned int z = (sza - s*1000000) / 1000;
  unsigned int a = sza - s*1000000 - z*1000;

  if( a == 0 ) {
    std::vector<unsigned int> iso_szas = GetIsosForZ(z);
    for(unsigned int i=0; i<iso_szas.size(); i++) {
      unsigned int is = iso_szas[i] / 1000000;
      unsigned int iz = (iso_szas[i] - is*1000000) / 1000;
      unsigned int ia = iso_szas[i] - is*1000000 - iz*1000;

      retval += m_abundances.at(iz).at(ia).m_mass * m_abundances.at(iz).at(ia).m_abundance;
    }
  }
  else {
    if( m_abundances.find(z) != m_abundances.end() ) {
      if( m_abundances.at(z).find(a) != m_abundances.at(z).end() ) {
        retval = m_abundances.at(z).at(a).m_mass;
      }
    }
  }

  return retval;
}

double AbundanceLib::GetAbundance(const unsigned int& sza) const { 
  double retval = 0.0;

  unsigned int s = sza / 1000000;
  unsigned int z = (sza - s*1000000) / 1000;
  unsigned int a = sza - s*1000000 - z*1000;

  if( m_abundances.find(z) != m_abundances.end() ) {
    if( m_abundances.at(z).find(a) != m_abundances.at(z).end() ) {
      retval = m_abundances.at(z).at(a).m_abundance;
    }
  }

  return retval;
}

std::vector<unsigned int> AbundanceLib::GetZs() const {
  std::vector<unsigned int> retval;

  for(std::map<unsigned int,std::map<unsigned int, AbundanceStruct> >::const_iterator it=m_abundances.begin(); it!=m_abundances.end(); it++) {
    retval.push_back( it->first );
  }

  return retval;
}

std::vector<unsigned int> AbundanceLib::GetIsosForZ(const unsigned int& z) const {
  std::vector<unsigned int> retval;

  for(std::map<unsigned int, AbundanceStruct>::const_iterator it=m_abundances.at(z).begin(); it!=m_abundances.at(z).end(); it++) {
    retval.push_back(z*1000 + it->first);
  }

  return retval;
}

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_AbundanceLib.cpp
//---------------------------------------------------------------------------//
