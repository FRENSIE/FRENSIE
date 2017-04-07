//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationProperties_def.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation properties class template definitions.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_PROPERTIES_DEF_HPP
#define MONTE_CARLO_SIMULATION_PROPERTIES_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_AdjointPhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Return the min particle energy
template<typename ParticleType>
double SimulationProperties::getMinParticleEnergy() const
{
  THROW_EXCEPTION( std::logic_error,
                   "Error: the particle type is not supported!" );
}

//! Return the min neutron energy
template<>
inline double SimulationProperties::getMinParticleEnergy<NeutronState>() const
{
  return this->getMinNeutronEnergy();
}

//! Return the min photon energy
template<>
inline double SimulationProperties::getMinParticleEnergy<PhotonState>() const
{
  return this->getMinPhotonEnergy();
}

//! Return the min adjoint photon energy
template<>
inline double SimulationProperties::getMinParticleEnergy<AdjointPhotonState>() const
{
  return this->getMinAdjointPhotonEnergy();
}

//! Return the min electron energy
template<>
inline double SimulationProperties::getMinParticleEnergy<ElectronState>() const
{
  return this->getMinElectronEnergy();
}

//! Return the min adjoint electron energy
template<>
inline double SimulationProperties::getMinParticleEnergy<AdjointElectronState>() const
{
  return this->getMinAdjointElectronEnergy();
}

// Return the max particle energy
template<typename ParticleType>
double SimulationProperties::getMaxParticleEnergy() const
{
  THROW_EXCEPTION( std::logic_error,
                   "Error: the particle type is not supported!" );
}

//! Return the max neutron energy
template<>
inline double SimulationProperties::getMaxParticleEnergy<NeutronState>() const
{
  return this->getMaxNeutronEnergy();
}

//! Return the max photon energy
template<>
inline double SimulationProperties::getMaxParticleEnergy<PhotonState>() const
{
  return this->getMaxPhotonEnergy();
}

//! Return the max adjoint photon energy
template<>
inline double SimulationProperties::getMaxParticleEnergy<AdjointPhotonState>() const
{
  return this->getMaxAdjointPhotonEnergy();
}

//! Return the max electron energy
template<>
inline double SimulationProperties::getMaxParticleEnergy<ElectronState>() const
{
  return this->getMaxElectronEnergy();
}

//! Return the max adjoint electron energy
template<>
inline double SimulationProperties::getMaxParticleEnergy<AdjointElectronState>() const
{
  return this->getMaxAdjointElectronEnergy();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_PROPERTIES_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationProperties_def.hpp
//---------------------------------------------------------------------------//
