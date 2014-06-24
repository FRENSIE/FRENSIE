//---------------------------------------------------------------------------//
//!
//! \file   Data_EmissionFile.cpp
//! \author CJ Solomon
//! \brief  Reads emission data from an XML file.
//!
//---------------------------------------------------------------------------//

#include "Data_EmissionFile.hpp"

namespace data {

EmissionFile::EmissionFile() {
  m_z = 0; m_a = 0; m_s = 0;
};

EmissionFile::EmissionFile(const std::string& filename, const unsigned int type) {
  Load(filename, type);
}

EmissionFile::EmissionFile(unsigned int z, unsigned int a, unsigned int s) {
  m_z = z; m_a = a; m_s = s;
};

void EmissionFile::SetZ(unsigned int z) {
  m_z = z;
}

void EmissionFile::SetA(unsigned int a) {
  m_a = a;
}

void EmissionFile::SetS(unsigned int s) {
  m_s = s;
}

void EmissionFile::AddDiscrete(int pt, const DiscreteEmission& de) {
  m_discretes[pt].push_back( de );
}

void EmissionFile::AddContinuum(int pt, const ContinuumEmission& ce) {
  m_continuum[pt].push_back( ce );
}

void EmissionFile::AddWattSpectrum(int pt, const WattSpectrum& ws, const double& scale) {
  if( m_watt.find(pt) != m_watt.end() ) {
    m_watt.erase(pt);
    m_watt_scale.erase(pt);
  }

  m_watt[pt] = ws;
  m_watt_scale[pt] = scale;
}

unsigned int EmissionFile::GetZ() const {
  return m_z;
}

unsigned int EmissionFile::GetA() const {
  return m_a;
}

unsigned int EmissionFile::GetS() const {
  return m_s;
}

std::vector<int> EmissionFile::GetDiscreteTypes() const {
  std::vector<int> retval;

  for(std::map<int, std::vector<DiscreteEmission> >::const_iterator it=m_discretes.begin(); it!=m_discretes.end(); it++) {
    retval.push_back(it->first);
  }

  return retval;
}

std::vector<int> EmissionFile::GetContinuumTypes() const {
  std::vector<int> retval;

  for(std::map<int, std::vector<ContinuumEmission> >::const_iterator it=m_continuum.begin(); it!=m_continuum.end(); it++) {
    retval.push_back(it->first);
  }

  return retval;
}

std::vector<int> EmissionFile::GetWattSpectrumTypes() const {
  std::vector<int> retval;

  for(std::map<int, WattSpectrum>::const_iterator it=m_watt.begin(); it!=m_watt.end(); it++) {
    retval.push_back(it->first);
  }

  return retval;
}

unsigned int EmissionFile::GetDiscreteNumber(const int& pt) const {
  return m_discretes.at(pt).size();
}

unsigned int EmissionFile::GetContinuumNumber(const int& pt) const {
  return m_continuum.at(pt).size();
}

DiscreteEmission EmissionFile::GetDiscrete(const int& pt, const unsigned int& cnt) const {
  return m_discretes.at(pt).at(cnt);
}

ContinuumEmission EmissionFile::GetContinuum(const int& pt, const unsigned int& cnt) const {
  return m_continuum.at(pt).at(cnt);
}

WattSpectrum EmissionFile::GetWattSpectrum(const int& pt) const {
  return m_watt.at(pt);
}

double EmissionFile::GetWattScale(const int& pt) const {
  return m_watt_scale.at(pt);
}

void EmissionFile::Save(const std::string& filename, const unsigned int type) const {
  // if( type != ISCDataFile::TXT && format != ISCDataFile::XML && format != ISCDataFile::BIN ) {
  //   need exception here
  // }

  std::ofstream ofs( filename.c_str() );

  if( type == ISCDataFile::TXT ) {
    boost::archive::text_oarchive ar(ofs);
    ar << *this;
  }
  else if( type == ISCDataFile::XML ) {
    boost::archive::xml_oarchive ar(ofs);
    ar << boost::serialization::make_nvp("emission_file",*this);
  }
  else if( type == ISCDataFile::BIN ) {
    boost::archive::binary_oarchive ar(ofs);
    ar << *this;
  }
}

void EmissionFile::Load(const std::string& filename, const unsigned int type) {
  // if( format != "txt" && format != "xml" && format != "bin" ) {
  //   need exception here
  // }

  std::ifstream ifs( filename.c_str() );

  if( type == ISCDataFile::TXT ) {
    boost::archive::text_iarchive ar(ifs);
    ar >> *this;
  }
  else if( type == ISCDataFile::XML ) {
    boost::archive::xml_iarchive ar(ifs);
    ar >> boost::serialization::make_nvp("emission_file",*this);
  }
  else if( type == ISCDataFile::BIN ) {
    boost::archive::binary_iarchive ar(ifs);
    ar >> *this;
  }
}

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_EmissionFile.cpp
//---------------------------------------------------------------------------//
