//---------------------------------------------------------------------------//
//!
//! \file   Data_ISCUtils.cpp
//! \author CJ Solomon
//! \brief  ISC Utilities
//!
//---------------------------------------------------------------------------//

#include "Data_ISCUtils.hpp"

namespace data {

namespace utils {

void getNumsFromSZA(const unsigned int& sza, unsigned int& s, unsigned int& z, unsigned int& a) {
  s = sza/1000000;
  z = (sza - s*1000000) / 1000;
  a = sza - s*1000000 - z*1000;
}

std::string getStringFromSZA(const unsigned int& sza) {
  unsigned int s, z, a;
  getNumsFromSZA(sza, s, z, a);

  std::stringstream ss;

  ss << zsymbols.left.at(z) << "-";
  if( a > 0 ) {
    ss << a;

    if( s > 0 )
      ss << "m" << s;
  }
  else {
    ss << "Nat";
  }

  return ss.str();
}

void saveLibs(const AbundanceLib& al, const DecayLib& dl, const EmissionLib& el, std::string filename, const unsigned int format) {
  // if( format !=  && format != "xml" && format != "bin" ) {
  //   format = "bin";
  // }

  std::ofstream ofs( filename.c_str() );

  if( format == ISCDataFile::TXT ) {
    boost::archive::text_oarchive ar(ofs);
    ar << al;
    ar << dl;
    ar << el;
  }
  else if( format == ISCDataFile::XML ) {
    using namespace boost::serialization;
    boost::archive::xml_oarchive ar(ofs);
    ar << make_nvp("abundance_library", al);
    ar << make_nvp("decay_library", dl);
    ar << make_nvp("emission_library", el);
  }
  else if( format == ISCDataFile::BIN ) {
    boost::archive::binary_oarchive ar(ofs);
    ar << al;
    ar << dl;
    ar << el;
  }
}

void loadLibs(AbundanceLib& al, DecayLib& dl, EmissionLib& el, std::string filename, const unsigned int format) {
  // if( format != "txt" && format != "xml" && format != "bin" ) {
  //   format = "bin";
  // }

  std::ifstream ifs( filename.c_str() );

  if( format == ISCDataFile::TXT ) {
    boost::archive::text_iarchive ar(ifs);
    ar >> al;
    ar >> dl;
    ar >> el;
  }
  else if( format == ISCDataFile::XML ) {
    using namespace boost::serialization;
    boost::archive::xml_iarchive ar(ifs);
    ar >> make_nvp("abundance_library", al);
    ar >> make_nvp("decay_library", dl);
    ar >> make_nvp("emission_library", el);
  }
  else if( format == ISCDataFile::BIN ) {
    boost::archive::binary_iarchive ar(ifs);
    ar >> al;
    ar >> dl;
    ar >> el;
  }
}

} // end namespace utils

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_ISCUtils.cpp
//---------------------------------------------------------------------------//
