//---------------------------------------------------------------------------//
//!
//! \file   Data_AbundanceLib.hpp
//! \author CJ Solomon
//! \brief  Abundance Library
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ABUNDANCE_LIB_HPP
#define DATA_ABUNDANCE_LIB_HPP

#include <string>
#include <sstream>
#include <vector>

#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/archive/binary_iarchive.hpp>

#include "Data_AbundanceFile.hpp"
#include "Data_AbundanceStruct.hpp"

namespace data {

class AbundanceLib {
public:
  AbundanceLib();
  AbundanceLib(const AbundanceFile& af);

  void UnpackString(std::string af_packed_string);

  double GetMass(const unsigned int& sza) const;
  double GetAbundance(const unsigned int& sza) const;

  std::vector<unsigned int> GetZs() const;
  std::vector<unsigned int> GetIsosForZ(const unsigned int& z) const;

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

#endif // DATA_ABUNDANCE_LIB_HPP

//---------------------------------------------------------------------------//
// end Data_AbundanceLib.hpp
//---------------------------------------------------------------------------//
