//---------------------------------------------------------------------------//
//!
//! \file   Data_EmissionSpectra.hpp
//! \author CJ Solomon
//! \brief  Emission Spectra
//!
//---------------------------------------------------------------------------//

#ifndef DATA_EMISSION_SPECTRA_HPP
#define DATA_EMISSION_SPECTRA_HPP

#include <map>
#include <vector>

#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/assign.hpp>

#include "Data_ENDFConsts.hpp"
#include "Data_MCNPConsts.hpp"
#include "Data_DefaultContinua.hpp"
#include "Data_EmissionSpectrum.hpp"
#include "Data_EmissionFile.hpp"
#include "Data_FermiBetaTheory.hpp"

namespace data{

class EmissionSpectra {
public:
  EmissionSpectra();
  EmissionSpectra(const EmissionFile& ef);

  void FromEmissionFile(const EmissionFile& ef);

  void SetSpectrum(const int& pt, const EmissionSpectrum& spc);
  void AddSpectrum(const int& pt, const EmissionSpectrum& spc);

  std::vector<int> GetParticleTypes() const;

  bool HasSpectrum(const int& pt) const;

  EmissionSpectrum GetSpectrum(const int& pt) const;

  void EsToBrems(const double& z);

  EmissionSpectra ToMCNPTypes(bool add_brems_to_photon=true) const;

  void Clear();

private:
  std::map<int, EmissionSpectrum> m_spectra;

  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    using namespace boost::serialization;
    ar & make_nvp("spectra", m_spectra);
  };
}; 

} // end namespace data

#endif // DATA_EMISSION_SPECTRA_HPP

//---------------------------------------------------------------------------//
// end Data_EmissionSpectra.hpp
//---------------------------------------------------------------------------//
