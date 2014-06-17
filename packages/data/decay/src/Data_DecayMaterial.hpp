//---------------------------------------------------------------------------//
//!
//! \file   Data_DecayMaterial.hpp
//! \author CJ Solomon
//! \brief  Decay Material
//!
//---------------------------------------------------------------------------//

#ifndef DATA_DECAY_MATERIAL_HPP
#define DATA_DECAY_MATERIAL_HPP

#include <set>
#include <map>

#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>

#include "Data_Material.hpp"
#include "Data_AbundanceLib.hpp"
#include "Data_DecayLib.hpp"
#include "Data_EmissionLib.hpp"
#include "Data_EmissionSpectra.hpp"
#include "Data_ISCUtils.hpp"

namespace data {

class DecayMaterial : public Material {
public:
  DecayMaterial();
  DecayMaterial(const AbundanceLib& al, const std::vector<unsigned int>& szas, const std::vector<double>& fracs, MatFType ftype, double den=0.0, MatFType dtype=Material::MASS);

  void Age(const AbundanceLib& al, const DecayLib& dl, const double& t);

  void BuildSource(const DecayLib& dl, const EmissionLib& el, bool es_to_brems=false, double brems_z=0.0, double brems_mult=1.0);

  void Reset();

  std::set<unsigned int> GetSZAs() const;
  double GetAtomFrac(const unsigned int& sza) const;
  double GetMassFrac(const unsigned int& sza) const;
  double GetSZAMass(const unsigned int& sza) const;
  double GetAtomDensity() const;
  double GetMassDensity() const;

  EmissionSpectra GetSpectra(unsigned int sza=0) const;

//  std::set<unsigned int> GetDaughters(const DecayLib& dl) const;

private:
  std::map<unsigned int, MatSZAData> m_decay_sza_data;
  std::map<unsigned int, EmissionSpectra> m_iso_spectra;
  EmissionSpectra m_spectra;
  double m_decay_aden;
  double m_decay_mden;

  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    using namespace boost::serialization;
    ar & base_object<Material>(*this);
    ar & make_nvp("decay_sza_data", m_decay_sza_data);
    ar & make_nvp("decay_spectra", m_iso_spectra);
    ar & make_nvp("spectra", m_spectra);
    ar & make_nvp("decay_atom_density", m_decay_aden);
    ar & make_nvp("decay_mass_density", m_decay_mden);
  };
};

} // end namespace data
#endif // DATA_DECAY_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end Data_DecayMaterial.hpp
//---------------------------------------------------------------------------//
