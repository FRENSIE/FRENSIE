//---------------------------------------------------------------------------//
//!
//! \file   Data_AbundanceFile.hpp
//! \author CJ Solomon
//! \brief  Reads the abundances from an XML file.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ABUNDANCE_FILE_HPP
#define DATA_ABUNDANCE_FILE_HPP

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

#include "Data_ISCDataFile.hpp"
#include "Data_AbundanceStruct.hpp"

namespace data {

class AbundanceFile : public ISCDataFile {
public:
  AbundanceFile();
  AbundanceFile(const std::string& filename, const unsigned int type=ISCDataFile::XML);

  void Insert(unsigned int sza, double mass, double abundance=0.0);

  std::string PackString() const;

  void Save(const std::string& filename, const unsigned int type=ISCDataFile::XML) const;
  void Load(const std::string& filename, const unsigned int type=ISCDataFile::XML);

private:
  std::map<unsigned int, std::map<unsigned int, AbundanceStruct> > m_abundances;

  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    using namespace boost::serialization;
    ar & make_nvp("abundances", m_abundances);
  };
};

} // end namespace data
#endif // DATA_ABUNDANCE_FILE_HPP

//---------------------------------------------------------------------------//
// end Data_AbundanceFile.hpp
//---------------------------------------------------------------------------//
