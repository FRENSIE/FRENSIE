//---------------------------------------------------------------------------//
//!
//! \file   Data_EmissionFileIndex.cpp
//! \author CJ Solomon
//! \brief  Emission File Index
//!
//---------------------------------------------------------------------------//

#include "Data_EmissionFileIndex.hpp"

namespace data {

EmissionFileIndex::EmissionFileIndex() {}

EmissionFileIndex::EmissionFileIndex(const std::string& filename, const unsigned int type) {
  Load(filename, type);
}

void EmissionFileIndex::SetPath(const unsigned int& sza, const std::string& path) {
  m_index[sza] = path;
}

std::string EmissionFileIndex::GetPath(const unsigned int& sza) const {
  std::string retval;
  if( m_index.find(sza) != m_index.end() ) {
    retval = m_index.at(sza);
  }
  return retval;
}

bool EmissionFileIndex::HasPath(const unsigned int& sza) const {
  bool retval = false;
  if( m_index.find(sza) != m_index.end() ) {
    retval = true;
  }
  return retval;
}

std::set<unsigned int> EmissionFileIndex::GetSZAs() const {
  std::set<unsigned int> retval;
  for(std::map<unsigned int, std::string>::const_iterator it=m_index.begin(); it!=m_index.end(); it++) {
    retval.insert(it->first);
  }
  return retval;
}
  
void EmissionFileIndex::Save(const std::string& filename, const unsigned int type) const {
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
    ar << boost::serialization::make_nvp("emission_file_index",*this);
  }
  else if( type == ISCDataFile::BIN ) {
    boost::archive::binary_oarchive ar(ofs);
    ar << *this;
  }
}

void EmissionFileIndex::Load(const std::string& filename, const unsigned int type) {
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
    ar >> boost::serialization::make_nvp("emission_file_index",*this);
  }
  else if( type == ISCDataFile::BIN ) {
    boost::archive::binary_iarchive ar(ifs);
    ar >> *this;
  }
}

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_EmissionFileIndex.cpp
//---------------------------------------------------------------------------//
