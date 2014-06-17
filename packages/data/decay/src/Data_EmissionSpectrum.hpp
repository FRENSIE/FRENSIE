//---------------------------------------------------------------------------//
//!
//! \file   Data_EmissionSpectrum.hpp
//! \author CJ Solomon
//! \brief  Emission Spectrum
//!
//---------------------------------------------------------------------------//

#ifndef DATA_EMISSION_SPECTRUM_HPP
#define DATA_EMISSION_SPECTRUM_HPP

#include <set>
#include <vector>

#include "Data_DiscreteEmission.hpp"
#include "Data_Histogram.hpp"

#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>

namespace data {

class EmissionSpectrum {
public:
  EmissionSpectrum();

  EmissionSpectrum& operator+=(const EmissionSpectrum& es);
  EmissionSpectrum& operator*=(const double& d);
  EmissionSpectrum& operator/=(const double& d);

  void AddDiscrete(const DiscreteEmission& d);
  void SetContinuum(const Histogram& c);
  void AddContinuum(const Histogram& c);

  unsigned int GetDNumber() const;
  double GetDEnergy(const unsigned int& i) const;
  double GetDEnergyErr(const unsigned int& i) const;
  double GetDIntensity(const unsigned int& i) const;
  double GetDIntensityErr(const unsigned int& i) const;
  unsigned int GetDDecayType(const unsigned int& i) const;

  unsigned int GetCNumber() const;
  double GetCEnergy(const unsigned int& i) const;
  double GetCIntensity(const unsigned int& i) const;

  double GetDNorm() const;
  double GetCNorm() const;

private:
  double m_dnorm;
  double m_cnorm;
  std::vector<DiscreteEmission> m_discretes;
  Histogram m_continuum;

  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    using namespace boost::serialization;
    ar & make_nvp("dnorm", m_dnorm);
    ar & make_nvp("cnorm", m_cnorm);
    ar & make_nvp("discretes", m_discretes);
    ar & make_nvp("continuum", m_continuum);
  };
};

const EmissionSpectrum operator+(const EmissionSpectrum& em1, const EmissionSpectrum& em2);
const EmissionSpectrum operator*(const double& d, const EmissionSpectrum& em);
const EmissionSpectrum operator*(const EmissionSpectrum& em, const double& d);
const EmissionSpectrum operator/(const EmissionSpectrum& em, const double& d);

} // end namespace data

#endif // DATA_EMISSION_SPECTRUM_HPP

//---------------------------------------------------------------------------//
// end Data_EmissionSpectrum.hpp
//---------------------------------------------------------------------------//
