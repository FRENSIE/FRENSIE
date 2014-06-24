//---------------------------------------------------------------------------//
//!
//! \file   Data_DiscreteEmission.cpp
//! \author CJ Solomon
//! \brief  Discrete Emission
//!
//---------------------------------------------------------------------------//

#include "Data_DiscreteEmission.hpp"

namespace data {

DiscreteEmission::DiscreteEmission() {
  m_decay_type = endf::decay::UNKNOWN;
  m_energy = 0.0;
  m_energy_err = 0.0;
  m_intensity = 0.0;
  m_intensity_err = 0.0;
}

DiscreteEmission::DiscreteEmission(double energy, double intensity, int rtyp, double energy_err, double intensity_err) {
  m_decay_type = rtyp;
  m_energy = energy;
  m_intensity = intensity;
  m_energy_err = energy_err;
  m_intensity_err = intensity_err;
}

void DiscreteEmission::SetDecayType(int rtyp) {
  m_decay_type = rtyp;
}

void DiscreteEmission::SetEnergy(double energy, double energy_err) {
  m_energy = energy;
  m_energy_err = energy_err;
}

void DiscreteEmission::SetIntensity(double intensity, double intensity_err) {
  m_intensity = intensity;
  m_intensity_err = intensity_err;
}

int DiscreteEmission::GetDecayType() const {
  return m_decay_type;
}

double DiscreteEmission::GetEnergy() const {
  return m_energy;
}

double DiscreteEmission::GetEnergyErr() const {
  return m_energy_err;
}

double DiscreteEmission::GetIntensity() const {
  return m_intensity;
}

double DiscreteEmission::GetIntensityErr() const {
  return m_intensity_err;
}

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_DiscreteEmission.cpp
//---------------------------------------------------------------------------//
