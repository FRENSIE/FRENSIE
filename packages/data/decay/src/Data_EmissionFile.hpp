//---------------------------------------------------------------------------//
//!
//! \file   Data_EmissionFile.hpp
//! \author CJ Solomon
//! \brief  Reads emission data from an XML file.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_EMISSION_FILE_HPP
#define DATA_EMISSION_FILE_HPP

#include <map>
#include <vector>
#include <fstream>

#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "Data_ENDFConsts.hpp"
#include "Data_DiscreteEmission.hpp"
#include "Data_ContinuumEmission.hpp"
#include "Data_WattSpectrum.hpp"
#include "Data_ISCDataFile.hpp"

namespace data {

class EmissionFile : public ISCDataFile {
public:
  EmissionFile();
  EmissionFile(const std::string& filename, const unsigned int type=ISCDataFile::XML);
  EmissionFile(unsigned int z, unsigned int a, unsigned int s=0);

  void SetZ(unsigned int z);
  void SetA(unsigned int a);
  void SetS(unsigned int s);

  void AddDiscrete(int, const DiscreteEmission& de);
  void AddContinuum(int, const ContinuumEmission& ce );
  void AddWattSpectrum(int, const WattSpectrum&, const double& scale);

  unsigned int GetZ() const;
  unsigned int GetA() const;
  unsigned int GetS() const;

  std::vector<int> GetDiscreteTypes() const;
  std::vector<int> GetContinuumTypes() const;
  std::vector<int> GetWattSpectrumTypes() const;

  unsigned int GetDiscreteNumber(const int& pt) const;
  unsigned int GetContinuumNumber(const int& pt) const;

  DiscreteEmission GetDiscrete(const int& pt, const unsigned int& cnt) const;
  ContinuumEmission GetContinuum(const int& pt, const unsigned int& cnt) const;
  WattSpectrum GetWattSpectrum(const int& pt) const;

  double GetWattScale(const int& pt) const;

  void Save(const std::string& filename, const unsigned int type=ISCDataFile::XML) const;
  void Load(const std::string& filename, const unsigned int type=ISCDataFile::XML);

private:
  unsigned int m_s, m_z, m_a;
  std::map<int, std::vector<DiscreteEmission> > m_discretes;

  std::map<int, std::vector<ContinuumEmission> > m_continuum;

  std::map<int, WattSpectrum > m_watt;
  std::map<int, double > m_watt_scale;

  // boost serialization stuff
  friend class boost::serialization::access;
  template< class Archive >
  void serialize(Archive& ar, const unsigned int version) {
    using namespace boost::serialization;
    ar & make_nvp("z", m_z);
    ar & make_nvp("a", m_a);
    ar & make_nvp("s", m_s);

    ar & make_nvp("discretes",m_discretes);
    ar & make_nvp("continuum",m_continuum);

    ar & make_nvp("watt", m_watt);
    ar & make_nvp("watt_scale", m_watt_scale);
  };
};

} // end namespace data

#endif // DATA_EMISSION_FILE_HPP

//---------------------------------------------------------------------------//
// end Data_EmissionFile.hpp
//---------------------------------------------------------------------------//
