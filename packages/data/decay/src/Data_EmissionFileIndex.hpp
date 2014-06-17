//---------------------------------------------------------------------------//
//!
//! \file   Data_EmissionFileIndex.hpp
//! \author CJ Solomon
//! \brief  Emission File Index
//!
//---------------------------------------------------------------------------//

#ifndef DATA_EMISSION_FILE_INDEX_HPP
#define DATA_EMISSION_FILE_INDEX_HPP

#include <map>
#include <set>
#include <string>
#include <fstream>

#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "Data_ISCDataFile.hpp"

namespace data {

class EmissionFileIndex : public ISCDataFile {
public:
  EmissionFileIndex();
  EmissionFileIndex(const std::string& filename, const unsigned int type=ISCDataFile::XML);
  
  void SetPath(const unsigned int& sza, const std::string& path);

  std::string GetPath(const unsigned int& sza) const;

  bool HasPath(const unsigned int& sza) const;

  std::set<unsigned int> GetSZAs() const;

  void Save(const std::string& filename, const unsigned int type=ISCDataFile::XML) const;
  void Load(const std::string& filename, const unsigned int type=ISCDataFile::XML);

private:
  std::map<unsigned int, std::string> m_index;

  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    using namespace boost::serialization;
    ar & make_nvp("index", m_index);
  };
};

} // end namespace data

#endif // DATA_EMISSION_FILE_INDEX_HPP

//---------------------------------------------------------------------------//
// end Data_EmissionFileIndex.hpp
//---------------------------------------------------------------------------//
