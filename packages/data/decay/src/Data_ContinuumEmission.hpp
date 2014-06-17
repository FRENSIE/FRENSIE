//---------------------------------------------------------------------------//
//!
//! \file   Data_ContinuumEmission.hpp
//! \author CJ Solomon
//! \brief  Continuum Emission
//!
//---------------------------------------------------------------------------//

#ifndef DATA_CONTINUUM_EMISSION_HPP
#define DATA_CONTINUUM_EMISSION_HPP

#include <vector>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>

#include "Data_ENDFConsts.hpp"

namespace data {

class ContinuumEmission {
public:
  ContinuumEmission();
  ContinuumEmission(std::vector<double> energy, std::vector<double> intensity, int rtyp=endf::decay::UNKNOWN);
  // ContinuumEmission(std::vector<double> energy, std::vector<double> intensity, std::vector<int> interp, unsigned int rtyp=endf::decay::UNKNOWN);

  void SetDecayType(int rtyp);
  void SetEnergy(std::vector<double> energy);
  void SetIntensity(std::vector<double> intensity);
  // void SetInterpolation(std::vector<int> interp);

  int GetDecayType() const;
  std::vector<double> GetEnergy() const;
  std::vector<double> GetIntensity() const;
  // std::vector<int> GetInterpolation() const;

private:
  int m_decay_type;
  std::vector<double> m_energy;
  std::vector<double> m_intensity;
  // std::vector<int> m_interpolation;

  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    using namespace boost::serialization;
    ar & make_nvp("decay_type", m_decay_type);
    ar & make_nvp("energy", m_energy);
    ar & make_nvp("intensity", m_intensity);
    // ar & make_nvp("interpolation", m_interpolation);
  };
};

} // end namespace data

#endif  // DATA_CONTINUUM_EMISSION_HPP

//---------------------------------------------------------------------------//
// end Data_ContinuumEmission.hpp
//---------------------------------------------------------------------------//
