//---------------------------------------------------------------------------//
//!
//! \file   Data_ContinuumEmission.cpp
//! \author CJ Solomon
//! \brief  Continuum Emission
//!
//---------------------------------------------------------------------------//

#include "Data_ContinuumEmission.hpp"

namespace data {

ContinuumEmission::ContinuumEmission() {
  m_decay_type = endf::decay::UNKNOWN;
}

ContinuumEmission::ContinuumEmission(std::vector<double> energy, std::vector<double> intensity, int rtyp) {
  m_decay_type = rtyp;
  m_energy = energy;
  m_intensity = intensity;
  // m_interpolation = interp;
}

void ContinuumEmission::SetDecayType(int rtyp) {
  m_decay_type = rtyp;
}

void ContinuumEmission::SetEnergy(std::vector<double> energy) {
  m_energy = energy;
}

void ContinuumEmission::SetIntensity(std::vector<double> intensity) {
  m_intensity = intensity;
}

// void ContinuumEmission::SetInterpolation(std::vector<int> interp) {
//   m_interpolation = interp;
// }

int ContinuumEmission::GetDecayType() const {
  return m_decay_type;
}

std::vector<double> ContinuumEmission::GetEnergy() const {
  return m_energy;
}

std::vector<double> ContinuumEmission::GetIntensity() const {
  return m_intensity;
}

// std::vector<int> ContinuumEmission::GetInterpolation() const {
//   return m_interpolation;
// }

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_ContinuumEmission.cpp
//---------------------------------------------------------------------------//
