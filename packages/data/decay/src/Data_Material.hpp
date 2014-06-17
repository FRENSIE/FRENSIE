//---------------------------------------------------------------------------//
//!
//! \file   Data_Material.hpp
//! \author CJ Solomon
//! \brief  Material
//!
//---------------------------------------------------------------------------//

#ifndef DATA_MATERIAL_HPP
#define DATA_MATERIAL_HPP

#include <set>
#include <vector>
#include <map>
#include <cassert>

#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>

#include "Data_AbundanceLib.hpp"
#include "Data_PhysicalConstants.hpp"
#include "Data_ISCUtils.hpp"

namespace data {

class Material {
public:
  enum MatFType {
    ATOM = 0,
    MASS = 1
  };

  Material();
  Material(const AbundanceLib& al, const std::vector<unsigned int>& szas, const std::vector<double>& fracs, MatFType ftype, double den=0.0, MatFType dtype=Material::MASS);

  virtual void Make(const AbundanceLib& al, const std::vector<unsigned int>& szas, const std::vector<double>& fracs, MatFType ftype, double den=0.0, MatFType dtype=Material::MASS);

  virtual std::set<unsigned int> GetSZAs() const;
  virtual double GetAtomFrac(const unsigned int& sza) const;
  virtual double GetMassFrac(const unsigned int& sza) const;
  virtual double GetSZAMass(const unsigned int& sza) const;
  virtual double GetAtomDensity() const;
  virtual double GetMassDensity() const;

protected:
  struct MatSZAData {
    double m_afrac;
    double m_mfrac;
    double m_mass;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      using namespace boost::serialization;
      ar & make_nvp("atom_frac", m_afrac);
      ar & make_nvp("mass_frac", m_mfrac);
      ar & make_nvp("mass", m_mass);
    };
  };

  std::map<unsigned int, MatSZAData> m_sza_data;
  double m_aden;
  double m_mden;

  void Clear();

private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    using namespace boost::serialization;
    ar & make_nvp("sza_data", m_sza_data);
    ar & make_nvp("atom_density", m_aden);
    ar & make_nvp("mass_density", m_mden);
  };
};

} // end namespace data

#endif // DATA_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end Data_Material.hpp
//---------------------------------------------------------------------------//
