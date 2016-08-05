//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationNeutronProperties.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation neutron properties class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_NEUTRON_PROPERTIES_HPP
#define MONTE_CARLO_SIMULATION_NEUTRON_PROPERTIES_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleModeType.hpp"

namespace MonteCarlo{

/*! The simulation properties class
 * \todo Modify XML parser to handle all options in this class. Use this class
 * in all parts of code that require runtime configuration.
 */
class SimulationNeutronProperties
{

public:

  //! Set the free gas thermal treatment temperature threshold
  static void setFreeGasThreshold( const double threshold );

  //! Return the free gas thermal treatment temperature threshold
  static double getFreeGasThreshold();

  //! Set the minimum neutron energy (MeV)
  static void setMinNeutronEnergy( const double energy );

  //! Return the minimum neutron energy (MeV)
  static double getMinNeutronEnergy();

  //! Return the absolute minimum neutron energy (MeV)
  static double getAbsoluteMinNeutronEnergy();

  //! Set the max neutron energy (MeV)
  static void setMaxNeutronEnergy( const double energy );

  //! Return the maximum neutron energy (MeV)
  static double getMaxNeutronEnergy();

  //! Return the absolute maximum neutron
  static double getAbsoluteMaxNeutronEnergy();

private:

  // The free gas thermal treatment temperature threshold
  // Note: free gas thermal treatment used when energy<threshold*kT (and A > 1)
  static double free_gas_threshold;

  // The absolute minimum neutron energy (MeV)
  static const double absolute_min_neutron_energy;

  // The minimum neutron energy (MeV)
  static double min_neutron_energy;

  // The maximum neutron energy (MeV)
  static double max_neutron_energy;

  // The absolute maximum neutron energy (MeV)
  static const double absolute_max_neutron_energy;

  // The absolute minimum photon energy (MeV)
  static const double absolute_min_photon_energy;
};

// Return the free gas thermal treatment temperature threshold
inline double SimulationNeutronProperties::getFreeGasThreshold()
{
  return SimulationNeutronProperties::free_gas_threshold;
}

// Return the minimum neutron energy (MeV)
inline double SimulationNeutronProperties::getMinNeutronEnergy()
{
  return SimulationNeutronProperties::min_neutron_energy;
}

// Return the absolute min neutron energy (MeV)
inline double SimulationNeutronProperties::getAbsoluteMinNeutronEnergy()
{
  return SimulationNeutronProperties::absolute_min_neutron_energy;
}

// Return the maximum neutron energy (MeV) - cannot be set at runtime
inline double SimulationNeutronProperties::getMaxNeutronEnergy()
{
  return SimulationNeutronProperties::max_neutron_energy;
}

// Return the absolute maximum neutron energy (MeV)
inline double SimulationNeutronProperties::getAbsoluteMaxNeutronEnergy()
{
  return SimulationNeutronProperties::absolute_max_neutron_energy;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_NEUTRON_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationNeutronProperties.cpp
//---------------------------------------------------------------------------//
