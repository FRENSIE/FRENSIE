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

// Return the cutoff roulette threshold weight
template<typename ParticleType>
double SimulationProperties::getRouletteThresholdWeight() const
{
  THROW_EXCEPTION( std::logic_error,
                   "Error: the particle type is not supported!" );
}

// Return the cutoff roulette threshold weight
template<>
inline double SimulationProperties::getRouletteThresholdWeight<NeutronState>() const
{
  return this->getNeutronRouletteThresholdWeight();
}

// Return the cutoff roulette threshold weight
template<>
inline double SimulationProperties::getRouletteThresholdWeight<PhotonState>() const
{
  return this->getPhotonRouletteThresholdWeight();
}

// Return the cutoff roulette threshold weight
template<>
inline double SimulationProperties::getRouletteThresholdWeight<AdjointPhotonState>() const
{
  return this->getAdjointPhotonRouletteThresholdWeight();
}

// Return the cutoff roulette threshold weight
template<>
inline double SimulationProperties::getRouletteThresholdWeight<ElectronState>() const
{
  return this->getElectronRouletteThresholdWeight();
}

// Return the cutoff roulette threshold weight
template<>
inline double SimulationProperties::getRouletteThresholdWeight<AdjointElectronState>() const
{
  return this->getAdjointElectronRouletteThresholdWeight();
}

// Return the cutoff roulette survival weight
template<typename ParticleType>
double SimulationProperties::getRouletteSurvivalWeight() const
{
  THROW_EXCEPTION( std::logic_error,
                   "Error: the particle type is not supported!" );
}

// Return the cutoff roulette survival weight
template<>
inline double SimulationProperties::getRouletteSurvivalWeight<NeutronState>() const
{
  return this->getNeutronRouletteSurvivalWeight();
}

// Return the cutoff roulette threshold weight
template<>
inline double SimulationProperties::getRouletteSurvivalWeight<PhotonState>() const
{
  return this->getPhotonRouletteSurvivalWeight();
}

// Return the cutoff roulette threshold weight
template<>
inline double SimulationProperties::getRouletteSurvivalWeight<AdjointPhotonState>() const
{
  return this->getAdjointPhotonRouletteSurvivalWeight();
}

// Return the cutoff roulette threshold weight
template<>
inline double SimulationProperties::getRouletteSurvivalWeight<ElectronState>() const
{
  return this->getElectronRouletteSurvivalWeight();
}

// Return the cutoff roulette threshold weight
template<>
inline double SimulationProperties::getRouletteSurvivalWeight<AdjointElectronState>() const
{
  return this->getAdjointElectronRouletteSurvivalWeight();
}

// Save/load the state to an archive
template<typename Archive>
void SimulationProperties::serialize( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( SimulationGeneralProperties );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( SimulationNeutronProperties );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( SimulationPhotonProperties );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( SimulationAdjointPhotonProperties );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( SimulationElectronProperties );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( SimulationAdjointElectronProperties );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_PROPERTIES_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationProperties_def.hpp
//---------------------------------------------------------------------------//
