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

  //! Constructor
  SimulationNeutronProperties();

  //! Destructor
  virtual ~SimulationNeutronProperties()
  { /* ... */ }

  //! Set the free gas thermal treatment temperature threshold
  void setFreeGasThreshold( const double threshold );

  //! Return the free gas thermal treatment temperature threshold
  double getFreeGasThreshold() const;

  //! Set the minimum neutron energy (MeV)
  void setMinNeutronEnergy( const double energy );

  //! Return the minimum neutron energy (MeV)
  double getMinNeutronEnergy() const;

  //! Return the absolute minimum neutron energy (MeV)
  static double getAbsoluteMinNeutronEnergy();

  //! Set the max neutron energy (MeV)
  void setMaxNeutronEnergy( const double energy );

  //! Return the maximum neutron energy (MeV)
  double getMaxNeutronEnergy() const;

  //! Return the absolute maximum neutron
  static double getAbsoluteMaxNeutronEnergy();

private:

  // The absolute minimum neutron energy (MeV)
  static const double s_absolute_min_neutron_energy;

  // The absolute maximum neutron energy (MeV)
  static const double s_absolute_max_neutron_energy;

  // The free gas thermal treatment temperature threshold
  // Note: free gas thermal treatment used when energy<threshold*kT (and A > 1)
  double d_free_gas_threshold;

  // The minimum neutron energy (MeV)
  double d_min_neutron_energy;

  // The maximum neutron energy (MeV)
  double d_max_neutron_energy;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_NEUTRON_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationNeutronProperties.cpp
//---------------------------------------------------------------------------//
