//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationGeneralProperties_def.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation general properties class template definitions.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_GENERAL_PROPERTIES_DEF_HPP
#define MONTE_CARLO_SIMULATION_GENERAL_PROPERTIES_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_SimulationNeutronProperties.hpp"
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Return the min particle energy
template<typename ParticleType>
double SimulationGeneralProperties::getMinParticleEnergy()
{
  THROW_EXCEPTION( std::logic_error,
		   "Error: the particle type is not supported!" );
}

//! Return the min neutron energy
template<>
inline double SimulationGeneralProperties::getMinParticleEnergy<NeutronState>()
{
  return SimulationNeutronProperties::getMinNeutronEnergy();
}

//! Return the min photon energy
template<>
inline double SimulationGeneralProperties::getMinParticleEnergy<PhotonState>()
{
  return SimulationPhotonProperties::getMinPhotonEnergy();
}

//! Return the min electron energy
template<>
inline double SimulationGeneralProperties::getMinParticleEnergy<ElectronState>()
{
  return SimulationElectronProperties::getMinElectronEnergy();
}

// Return the max particle energy
template<typename ParticleType>
double SimulationGeneralProperties::getMaxParticleEnergy()
{
  THROW_EXCEPTION( std::logic_error,
		   "Error: the particle type is not supported!" );
}

//! Return the max neutron energy
template<>
inline double SimulationGeneralProperties::getMaxParticleEnergy<NeutronState>()
{
  return SimulationNeutronProperties::getMaxNeutronEnergy();
}

//! Return the max photon energy
template<>
inline double SimulationGeneralProperties::getMaxParticleEnergy<PhotonState>()
{
  return SimulationPhotonProperties::getMaxPhotonEnergy();
}

//! Return the max photon energy
template<>
inline double SimulationGeneralProperties::getMaxParticleEnergy<ElectronState>()
{
  return SimulationElectronProperties::getMaxElectronEnergy();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_GENERAL_PROPERTIES_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationGeneralProperties_def.hpp
//---------------------------------------------------------------------------//
