//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationNeutronProperties.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation neutron properties class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SimulationNeutronProperties.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize the static member data
double SimulationNeutronProperties::free_gas_threshold = 400.0;

// The absolute minimum neutron energy (MeV)
const double SimulationNeutronProperties::absolute_min_neutron_energy = 1e-11;

// The minimum neutron energy (MeV)
double SimulationNeutronProperties::min_neutron_energy =
  SimulationNeutronProperties::absolute_min_neutron_energy;

// The absolute max neutron energy (MeV)
const double SimulationNeutronProperties::absolute_max_neutron_energy = 20.0;

// The max neutron energy (MeV)
double SimulationNeutronProperties::max_neutron_energy =
  SimulationNeutronProperties::absolute_max_neutron_energy;

// Set the free gas thermal treatment temperature threshold
/*! \details The value given is the number of times above the material
 * temperature that the energy of a neutron can be before the free gas
 * thermal treatment is not used anymore.
 */
void SimulationNeutronProperties::setFreeGasThreshold( const double threshold )
{
  // Make sure the threshold is valid
  testPrecondition( threshold > 0.0 );

  SimulationNeutronProperties::free_gas_threshold = threshold;
}

// Set the minimum neutron energy (MeV)
void SimulationNeutronProperties::setMinNeutronEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition(energy >= SimulationNeutronProperties::absolute_min_neutron_energy);
  testPrecondition( energy < SimulationNeutronProperties::max_neutron_energy );

  SimulationNeutronProperties::min_neutron_energy = energy;
}

// Set the max neutron energy (MeV)
void SimulationNeutronProperties::setMaxNeutronEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition(energy > SimulationNeutronProperties::min_neutron_energy );
  testPrecondition(energy <= SimulationNeutronProperties::absolute_max_neutron_energy);

  SimulationNeutronProperties::max_neutron_energy = energy;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationNeutronProperties.cpp
//---------------------------------------------------------------------------//
