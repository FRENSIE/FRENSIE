//---------------------------------------------------------------------------//
//!
//! \file   Data_AbundanceFile.cpp
//! \author CJ Solomon
//! \brief  Reads the abundances from an XML file.
//!
//---------------------------------------------------------------------------//

#include "Data_AbundanceFile.hpp"

namespace data {

AbundanceFile::AbundanceFile() {}

AbundanceFile::AbundanceFile(const std::string& filename, const unsigned int type) {
  Load(filename, type);
}

void AbundanceFile::Insert(unsigned int sza, double mass, double abundance) {
  unsigned int s = sza / 1000000;
  unsigned int z = (sza - s*1000000) / 1000;
  unsigned int a = sza - s*1000000 - z*1000;
  m_abundances[z][a].m_mass = mass;
  m_abundances[z][a].m_abundance = abundance;
}

std::string AbundanceFile::PackString() const {
  std::stringstream ss;
  boost::archive::binary_oarchive ar(ss);

  ar & m_abundances;

  return ss.str();
}

void AbundanceFile::Save(const std::string& filename, const unsigned int type) const {
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
    ar << boost::serialization::make_nvp("abundance_file",*this);
  }
  else if( type == ISCDataFile::BIN ) {
    boost::archive::binary_oarchive ar(ofs);
    ar << *this;
  }
}

void AbundanceFile::Load(const std::string& filename, const unsigned int type) {
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
    ar >> boost::serialization::make_nvp("abundance_file",*this);
  }
  else if( type == ISCDataFile::BIN ) {
    boost::archive::binary_iarchive ar(ifs);
    ar >> *this;
  }
}

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_AbundanceFile.cpp
//---------------------------------------------------------------------------//
