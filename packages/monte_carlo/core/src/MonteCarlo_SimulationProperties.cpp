//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationProperties.hpp
//! \author Alex Robinson
//! \brief  Simulation properties class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// The particle mode 
ParticleModeType SimulationProperties::particle_mode = NEUTRON_MODE;

// The number of histories to run
unsigned long long SimulationProperties::number_of_histories = 0;

// Initialize the static member data
double SimulationProperties::free_gas_threshold = 400.0;

// The absolute minimum neutron energy (MeV)
const double SimulationProperties::absolute_min_neutron_energy = 1e-11;

// The minimum neutron energy (MeV)
double SimulationProperties::min_neutron_energy = 
  SimulationProperties::absolute_min_neutron_energy;

// The absolute max neutron energy (MeV)
const double SimulationProperties::absolute_max_neutron_energy = 20.0;

// The max neutron energy (MeV)
double SimulationProperties::max_neutron_energy = 
  SimulationProperties::absolute_max_neutron_energy;

// The absolute min photon energy (MeV)
const double SimulationProperties::absolute_min_photon_energy = 1e-3;

// The min photon energy (MeV)
double SimulationProperties::min_photon_energy =
  SimulationProperties::absolute_min_photon_energy;

// The absolute max photon energy (MeV)
const double SimulationProperties::absolute_max_photon_energy = 20.0;

// The max photon energy (MeV)
double SimulationProperties::max_photon_energy = 
  SimulationProperties::absolute_max_photon_energy;

// The absolute min electron energy
const double SimulationProperties::absolute_min_electron_energy = 1e-3;

// The minimum electron energy (MeV)
double SimulationProperties::min_electron_energy = 
  SimulationProperties::absolute_min_electron_energy;

// The absolute max electron energy (MeV)
const double SimulationProperties::absolute_max_electron_energy = 20.0;

// The max electron energy (MeV)
double SimulationProperties::max_electron_energy =
  SimulationProperties::absolute_max_electron_energy;

// The warning message flag
bool SimulationProperties::display_warnings = true;

// The capture mode (true = implicit, false = analogue - default)
bool SimulationProperties::implicit_capture_mode_on = false;

// The photon Doppler broadening mode (true = on - default, false = off)
bool SimulationProperties::doppler_broadening_mode_on = true;

// The atomic relaxation mode (true = on - default, false = off)
bool SimulationProperties::atomic_relaxation_mode_on = true;

// The detailed pair production mode (true = on, false = off - default)
bool SimulationProperties::detailed_pair_production_mode_on = false;

// The photonuclear interaction mode (true = on, false = off - default)
bool SimulationProperties::photonuclear_interaction_mode_on = false;

// Set the particle mode
void SimulationProperties::setParticleMode( 
					 const ParticleModeType particle_mode )
{
  SimulationProperties::particle_mode = particle_mode;
}

// Set the number of histories to run
void SimulationProperties::setNumberOfHistories( 
					   const unsigned long long histories )
{
  SimulationProperties::number_of_histories = histories;
}

// Set the free gas thermal treatment temperature threshold
/*! \details The value given is the number of times above the material 
 * temperature that the energy of a neutron can be before the free gas
 * thermal treatment is not used anymore.
 */
void SimulationProperties::setFreeGasThreshold( const double threshold )
{
  // Make sure the threshold is valid
  testPrecondition( threshold > 0.0 );
  
  SimulationProperties::free_gas_threshold = threshold;
}

// Set the minimum neutron energy (MeV)
void SimulationProperties::setMinNeutronEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition(energy >= SimulationProperties::absolute_min_neutron_energy);
  testPrecondition( energy < SimulationProperties::max_neutron_energy );
  
  SimulationProperties::min_neutron_energy = energy;
}

// Set the max neutron energy (MeV)
void SimulationProperties::setMaxNeutronEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition(energy > SimulationProperties::min_neutron_energy );
  testPrecondition(energy <= SimulationProperties::absolute_max_neutron_energy);

  SimulationProperties::max_neutron_energy = energy;
}

// Set the minimum photon energy (MeV)
void SimulationProperties::setMinPhotonEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition(energy >= SimulationProperties::absolute_min_photon_energy);
  testPrecondition( energy < SimulationProperties::max_photon_energy );
  
  SimulationProperties::min_photon_energy = energy;
}

// Set the max photon energy (MeV)
void SimulationProperties::setMaxPhotonEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition(energy > SimulationProperties::min_photon_energy );
  testPrecondition(energy <= SimulationProperties::absolute_max_photon_energy);

  SimulationProperties::max_photon_energy = energy;
}

// Set the minimum electron energy (MeV)
void SimulationProperties::setMinElectronEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition(energy >= SimulationProperties::absolute_min_electron_energy);
  testPrecondition( energy < SimulationProperties::max_electron_energy );
  
  SimulationProperties::min_electron_energy = energy;
}

// Set the maximum electron energy (MeV)
void SimulationProperties::setMaxElectronEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( energy > SimulationProperties::min_electron_energy );
  testPrecondition(energy <= SimulationProperties::absolute_max_electron_energy);

  SimulationProperties::max_electron_energy = energy;
}

// Turn off warnings
void SimulationProperties::setWarningsOff()
{
  SimulationProperties::display_warnings = false;
}

// Set implicit capture mode to on (off by default)
void SimulationProperties::setImplicitCaptureModeOn()
{
  SimulationProperties::implicit_capture_mode_on = true;
}

// Set photon Doppler broadening mode to off (on by default)
void SimulationProperties::setPhotonDopplerBroadeningModeOff()
{
  SimulationProperties::doppler_broadening_mode_on = false;
}

// Set atomic relaxation mode to off (on by default)
void SimulationProperties::setAtomicRelaxationModeOff()
{
  SimulationProperties::atomic_relaxation_mode_on = false;
}

// Set detailed pair production mode to on (off by default)
void SimulationProperties::setDetailedPairProductionModeOn()
{
  SimulationProperties::detailed_pair_production_mode_on = true;
}

// Set photonuclear interaction mode to on (off by default)
void SimulationProperties::setPhotonuclearInteractionModeOn()
{
  SimulationProperties::photonuclear_interaction_mode_on = true;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationProperties.cpp
//---------------------------------------------------------------------------//
