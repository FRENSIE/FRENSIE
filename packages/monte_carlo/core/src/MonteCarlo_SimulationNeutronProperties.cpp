//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationNeutronProperties.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation neutron properties class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must be included first
#include "MonteCarlo_SimulationNeutronProperties.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Initialize the static member data
const double SimulationNeutronProperties::s_absolute_min_neutron_energy = 1e-11;

// The absolute max neutron energy (MeV)
const double SimulationNeutronProperties::s_absolute_max_neutron_energy = 20.0;

// Constructor
SimulationNeutronProperties::SimulationNeutronProperties()
  : d_min_neutron_energy( s_absolute_min_neutron_energy ),
    d_max_neutron_energy( s_absolute_max_neutron_energy ),
    d_num_neutron_hash_grid_bins( 1000 ),
    d_free_gas_threshold( 400.0 ),
    d_unresolved_resonance_probability_table_mode_on( true ),
    d_threshold_weight( 0.0 ),
    d_survival_weight()
{ /* ... */ }

// Set the minimum neutron energy (MeV)
void SimulationNeutronProperties::setMinNeutronEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition(energy >= s_absolute_min_neutron_energy);
  testPrecondition( energy < d_max_neutron_energy );

  d_min_neutron_energy = energy;
}

// Return the minimum neutron energy (MeV)
double SimulationNeutronProperties::getMinNeutronEnergy() const
{
  return d_min_neutron_energy;
}

// Return the absolute min neutron energy (MeV)
double SimulationNeutronProperties::getAbsoluteMinNeutronEnergy()
{
  return s_absolute_min_neutron_energy;
}

// Set the max neutron energy (MeV)
void SimulationNeutronProperties::setMaxNeutronEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition(energy > d_min_neutron_energy );
  testPrecondition(energy <= s_absolute_max_neutron_energy);

  d_max_neutron_energy = energy;
}

// Return the maximum neutron energy (MeV) - cannot be set at runtime
double SimulationNeutronProperties::getMaxNeutronEnergy() const
{
  return d_max_neutron_energy;
}

// Return the absolute maximum neutron energy (MeV)
double SimulationNeutronProperties::getAbsoluteMaxNeutronEnergy()
{
  return s_absolute_max_neutron_energy;
}

// Set the number of neutron hash grid bins
void SimulationNeutronProperties::setNumberOfNeutronHashGridBins(
                                                          const unsigned bins )
{
  d_num_neutron_hash_grid_bins = bins;
}

// Get the number of neutron hash grid bins
unsigned SimulationNeutronProperties::getNumberOfNeutronHashGridBins() const
{
  return d_num_neutron_hash_grid_bins;
}

// Set the free gas thermal treatment temperature threshold
/*! \details The value given is the number of times above the material
 * temperature that the energy of a neutron can be before the free gas
 * thermal treatment is not used anymore.
 */
void SimulationNeutronProperties::setFreeGasThreshold( const double threshold )
{
  // Make sure the threshold is valid
  testPrecondition( threshold > 0.0 );

  d_free_gas_threshold = threshold;
}

// Return the free gas thermal treatment temperature threshold
double SimulationNeutronProperties::getFreeGasThreshold() const
{
  return d_free_gas_threshold;
}

// Set unresolved resonance probability table mode to on (on by default)
void SimulationNeutronProperties::setUnresolvedResonanceProbabilityTableModeOn()
{
  d_unresolved_resonance_probability_table_mode_on = true;
}

// Set unresolved resonance probability table mode to off (on by default)
void SimulationNeutronProperties::setUnresolvedResonanceProbabilityTableModeOff()
{
  d_unresolved_resonance_probability_table_mode_on = false;
}

// Return if unresolved resonance probability table mode is on
bool SimulationNeutronProperties::isUnresolvedResonanceProbabilityTableModeOn() const
{
  return d_unresolved_resonance_probability_table_mode_on;
}

// Set the cutoff roulette threshold weight
void SimulationNeutronProperties::setNeutronRouletteThresholdWeight(
      const double threshold_weight )
{
  // Make sure the weights are valid
  testPrecondition( threshold_weight > 0.0 );

  d_threshold_weight = threshold_weight;
}

// Return the cutoff roulette threshold weight
double SimulationNeutronProperties::getNeutronRouletteThresholdWeight() const
{
  return d_threshold_weight;
}

// Set the cutoff roulette threshold weight
/*! \details The survival weight should be set after the threshold weight to
 * ensure the weight is valid.
 */
void SimulationNeutronProperties::setNeutronRouletteSurvivalWeight(
      const double survival_weight )
{
  // Make sure the weights are valid
  testPrecondition( survival_weight > d_threshold_weight );

  d_survival_weight = survival_weight;
}

// Return the cutoff roulette survival weight
double SimulationNeutronProperties::getNeutronRouletteSurvivalWeight() const
{
  return d_survival_weight;
}

EXPLICIT_CLASS_SERIALIZE_INST( SimulationNeutronProperties );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SimulationNeutronProperties );

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationNeutronProperties.cpp
//---------------------------------------------------------------------------//
