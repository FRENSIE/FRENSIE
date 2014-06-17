//---------------------------------------------------------------------------//
//!
//! \file   Data_DecayFile.cpp
//! \author CJ Solomon
//! \brief  Reads the decay data from an XML file.
//!
//---------------------------------------------------------------------------//

#include "Data_DecayFile.hpp"

namespace data {

DecayFile::DecayFile() {};

DecayFile::DecayFile(const std::string& filename, const unsigned int type) {
  Load(filename, type);
}

void DecayFile::SetDecayData(const unsigned int& zaid, const DecayData& dd) {
  m_decay_data[zaid] = dd;
}

std::string DecayFile::PackString() const {
  std::stringstream ss;

  boost::archive::binary_oarchive ar(ss);

  ar & m_decay_data;

  return ss.str();
}

void DecayFile::Save(const std::string& filename, const unsigned int type) const {
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
    ar << boost::serialization::make_nvp("decay_file",*this);
  }
  else if( type == ISCDataFile::BIN ) {
    boost::archive::binary_oarchive ar(ofs);
    ar << *this;
  }
}

void DecayFile::Load(const std::string& filename, const unsigned int type) {
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
    ar >> boost::serialization::make_nvp("decay_file",*this);
  }
  else if( type == ISCDataFile::BIN ) {
    boost::archive::binary_iarchive ar(ifs);
    ar >> *this;
  }
}

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_DecayFile.cpp
//---------------------------------------------------------------------------//
