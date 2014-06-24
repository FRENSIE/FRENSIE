//---------------------------------------------------------------------------//
//!
//! \file   Data_ISCUtils.hpp
//! \author CJ Solomon
//! \brief  ISC Utilities
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ISC_UTILS_HPP
#define DATA_ISC_UTILS_HPP

#include <string>
#include <sstream>
#include <fstream>

#include <boost/serialization/nvp.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "Data_AbundanceLib.hpp"
#include "Data_DecayLib.hpp"
#include "Data_EmissionLib.hpp"
#include "Data_ISCDataFile.hpp"
#include "Data_ZSymbolMap.hpp"

namespace data {

namespace utils {

void getNumsFromSZA(const unsigned int& sza, unsigned int& s, unsigned int& z, unsigned int& a);

std::string getStringFromSZA(const unsigned int& sza);

void saveLibs(const AbundanceLib& al, const DecayLib& dl, const EmissionLib& el, std::string filename, const unsigned int=ISCDataFile::BIN);
void loadLibs(AbundanceLib& al, DecayLib& dl, EmissionLib& el, std::string filename, const unsigned int=ISCDataFile::BIN);

} // end namespace utils

} // end namespace data

#endif // DATA_ISC_UTILS_HPP

//---------------------------------------------------------------------------//
// end Data_ISCUtils.hpp
//---------------------------------------------------------------------------//
