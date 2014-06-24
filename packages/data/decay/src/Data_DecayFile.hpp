//---------------------------------------------------------------------------//
//!
//! \file   Data_DecayFile.hpp
//! \author CJ Solomon
//! \brief  Reads the decay data from an XML file.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_DECAY_FILE_HPP
#define DATA_DECAY_FILE_HPP

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>

#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "Data_DecayData.hpp"
#include "Data_ISCDataFile.hpp"

namespace data {

class DecayFile : public ISCDataFile {
public:
  DecayFile();
  DecayFile(const std::string& filename, const unsigned int type=ISCDataFile::XML);

  void SetDecayData(const unsigned int& zaid, const DecayData& dd);

  std::string PackString() const;

  void Save(const std::string& filename, const unsigned int type=ISCDataFile::XML) const;
  void Load(const std::string& filename, const unsigned int type=ISCDataFile::XML);

private:
  std::map<unsigned int, DecayData> m_decay_data;

  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    using namespace boost::serialization;
    ar & make_nvp("decay_data",m_decay_data);
  };
};

} // end namespace data

#endif // DATA_DECAY_FILE_HPP

//---------------------------------------------------------------------------//
// end Data_DecayFile.hpp
//---------------------------------------------------------------------------//
