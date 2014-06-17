//---------------------------------------------------------------------------//
//!
//! \file   Data_DiscreteEmission.cpp
//! \author CJ Solomon
//! \brief  Discrete Emission
//!
//---------------------------------------------------------------------------//

#ifndef DATA_DISCRETE_EMISSION_HPP
#define DATA_DISCRETE_EMISSION_HPP

#include <boost/serialization/nvp.hpp>

#include "Data_ENDFConsts.hpp"

namespace data {

class DiscreteEmission {
public:
  DiscreteEmission();
  DiscreteEmission(double energy, double intensity, int rtyp = endf::decay::UNKNOWN, double energy_err=0.0, double intensity_err=0.0);

  void SetDecayType(int rtyp);
  void SetEnergy(double energy, double energy_err=0.0);
  void SetIntensity(double intensity, double intensity_err=0.0);

  int GetDecayType() const;
  double GetEnergy() const;
  double GetEnergyErr() const;
  double GetIntensity() const;
  double GetIntensityErr() const;

private:
  int m_decay_type;
  double m_energy, m_energy_err;
  double m_intensity, m_intensity_err;

  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    using namespace boost::serialization;
    ar & make_nvp("energy", m_energy);
    ar & make_nvp("energy_err", m_energy_err);
    ar & make_nvp("intensity", m_intensity);
    ar & make_nvp("intensity_err", m_intensity_err);
    ar & make_nvp("decay_type", m_decay_type);
  };
};

} // end namespace data

#endif // DATA_DISCRETE_EMISSION_HPP

//---------------------------------------------------------------------------//
// end Data_DiscreteEmission.hpp
//---------------------------------------------------------------------------//
