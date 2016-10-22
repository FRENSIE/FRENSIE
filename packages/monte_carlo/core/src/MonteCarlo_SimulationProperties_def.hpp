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
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Return the min particle energy
template<typename ParticleType>
double SimulationProperties::getMinParticleEnergy()
{
  THROW_EXCEPTION( std::logic_error,
		   "Error: the particle type is not supported!" );
}

//! Return the min neutron energy
template<>
inline double SimulationProperties::getMinParticleEnergy<NeutronState>()
{
  return this->getMinNeutronEnergy();
}

//! Return the min photon energy
template<>
inline double SimulationProperties::getMinParticleEnergy<PhotonState>()
{
  return this->getMinPhotonEnergy();
}

//! Return the min adjoint photon energy
template<>
inline double SimulationProperties::getMinParticleEnergy<AdjointPhotonState>()
{
  return this->getMinAdjointPhotonEnergy();
}

//! Return the min electron energy
template<>
inline double SimulationProperties::getMinParticleEnergy<ElectronState>()
{
  return this->getMinElectronEnergy();
}

// Return the max particle energy
template<typename ParticleType>
double SimulationProperties::getMaxParticleEnergy()
{
  THROW_EXCEPTION( std::logic_error,
		   "Error: the particle type is not supported!" );
}

//! Return the max neutron energy
template<>
inline double SimulationProperties::getMaxParticleEnergy<NeutronState>()
{
  return this->getMaxNeutronEnergy();
}

//! Return the max photon energy
template<>
inline double SimulationProperties::getMaxParticleEnergy<PhotonState>()
{
  return this->getMaxPhotonEnergy();
}

//! Return the max adjoint photon energy
template<>
inline double SimulationProperties::getMaxParticleEnergy<AdjointPhotonState>()
{
  return this->getMaxAdjointPhotonEnergy();
}

//! Return the max photon energy
template<>
inline double SimulationProperties::getMaxParticleEnergy<ElectronState>()
{
  return this->getMaxElectronEnergy();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_PROPERTIES_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationProperties_def.hpp
//---------------------------------------------------------------------------//
