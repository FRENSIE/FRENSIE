//---------------------------------------------------------------------------//
//!
//! \file   Data_DecayLib.hpp
//! \author CJ Solomon
//! \brief  Decay Library
//!
//---------------------------------------------------------------------------//

#ifndef DATA_DECAY_LIB_HPP
#define DATA_DECAY_LIB_HPP

#include <map>
#include <vector>
#include <set>
#include <string>
#include <sstream>

#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/archive/binary_iarchive.hpp>

#include "Data_DecayFile.hpp"
#include "Data_DecayData.hpp"

namespace data {

class DecayLib {
public:
  DecayLib();
  DecayLib(const DecayFile& df);

  void UnpackString(std::string df_packed_string);

  std::vector<unsigned int> GetSZAs() const;
  DecayData GetDecayData(const unsigned int& sza) const;

  std::set<unsigned int> GetAllDaughters(const unsigned int& sza) const;

  std::map<unsigned int,double> UnitDecay(const unsigned int& sza, const double& t, const std::vector<double> p_lambdas = std::vector<double>()) const;

private:
  std::map<unsigned int, DecayData> m_decay_data;

  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    using namespace boost::serialization;
    ar & make_nvp("decay_data", m_decay_data);
  };
};

} // end namespace data

#endif // DATA_DECAY_LIB_HPP

//---------------------------------------------------------------------------//
// end Data_DecayLib.hpp
//---------------------------------------------------------------------------//
