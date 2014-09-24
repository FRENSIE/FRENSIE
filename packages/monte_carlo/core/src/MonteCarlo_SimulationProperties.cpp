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

// Initialize the static member data
double SimulationProperties::free_gas_threshold = 400.0;

// The minimum neutron energy (MeV)
double SimulationProperties::min_neutron_energy = 1e-11;

// The max neutron energy (MeV)
double SimulationProperties::max_neutron_energy = 20.0;

// The min photon energy (MeV)
double SimulationProperties::min_photon_energy = 1e-3;

// The max photon energy (MeV)
double SimulationProperties::max_photon_energy = 20.0;

// The minimum electron energy (MeV)
double SimulationProperties::min_electron_energy = 1e-3;

// The max neutron energy (MeV)
double SimulationProperties::max_electron_energy = 20.0;

// The capture mode (true = implicit capture mode on, false = analogue)
bool SimulationProperties::implicit_capture_mode_on = false;

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
  testPrecondition( energy > 0.0 );
  testPrecondition( energy < SimulationProperties::max_neutron_energy );
  
  SimulationProperties::min_neutron_energy = energy;
}

// Set the minimum photon energy (MeV)
void SimulationProperties::setMinPhotonEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );
  testPrecondition( energy < SimulationProperties::max_photon_energy );
  
  SimulationProperties::min_photon_energy = energy;
}

// Set the minimum electron energy (MeV)
void SimulationProperties::setMinElectronEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );
  testPrecondition( energy < SimulationProperties::max_electron_energy );
  
  SimulationProperties::min_electron_energy = energy;
}

// Set implicit capture mode to on 
void SimulationProperties::setImplicitCaptureModeOn()
{
  SimulationProperties::implicit_capture_mode_on = true;
}

// Set implicit capture mode to off
void SimulationProperties::setImplicitCaptureModeOff()
{
  SimulationProperties::implicit_capture_mode_on = false;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationProperties.cpp
//---------------------------------------------------------------------------//
