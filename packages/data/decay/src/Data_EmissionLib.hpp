//---------------------------------------------------------------------------//
//!
//! \file   Data_EmissionLib.hpp
//! \author CJ Solomon
//! \brief  Emission Library
//!
//---------------------------------------------------------------------------//

#ifndef DATA_EMISSION_LIB_HPP
#define DATA_EMISSION_LIB_HPP

#include <set>
#include <map>

#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>

#include "Data_EmissionSpectra.hpp"
#include "Data_EmissionFile.hpp"

namespace data {

class EmissionLib {
public:
  EmissionLib();

  void SetFromEmissionFile(const EmissionFile& ef);

  void SetSpectra(const unsigned int& sza, const EmissionSpectra& es);

  std::set<unsigned int> GetSZAs() const;

  EmissionSpectra GetSpectra(const unsigned int& sza) const;

private:
  std::map<unsigned int, EmissionSpectra> m_spectra;

  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive& ar, const unsigned int& version) {
    using namespace boost::serialization;
    ar & make_nvp("spectra", m_spectra);
  };
};

} // end namespace data

#endif // DATA_EMISSION_LIB_HPP

//---------------------------------------------------------------------------//
// end Data_EmissionLib.hpp
//---------------------------------------------------------------------------//
