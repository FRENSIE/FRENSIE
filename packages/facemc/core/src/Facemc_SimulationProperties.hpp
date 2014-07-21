//---------------------------------------------------------------------------//
//!
//! \file   Facemc_SimulationProperties.hpp
//! \author Alex Robinson
//! \brief  Simulation properties class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_SIMULATION_PROPERTIES_HPP
#define FACEMC_SIMULATION_PROPERTIES_HPP

namespace Facemc{

//! The simulation properties class
class SimulationProperties
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

  //! Return the maximum neutron energy (MeV) - cannot be set at runtime
  static double getMaxNeutronEnergy();
  
  //! Set the minimum photon energy (MeV)
  static void setMinPhotonEnergy( const double energy );

  //! Return the minimum photon energy (MeV)
  static double getMinPhotonEnergy();
  
  //! Return the maximum photon energy (MeV) - cannot be set at runtime
  static double getMaxPhotonEnergy();

  //! Set implicit capture mode to on 
  static void setImplicitCaptureModeOn();

  //! Set implicit capture mode to off
  static void setImplicitCaptureModeOff();

  //! Return if implicit capture mode has been set
  static bool isImplicitCaptureModeOn();

private:

  // The free gas thermal treatment temperature threshold
  // Note: free gas thermal treatment used when energy<threshold*kT (and A > 1)
  static double free_gas_threshold;

  // The minimum neutron energy (MeV)
  static double min_neutron_energy;

  // The max neutron energy (MeV)
  static double max_neutron_energy;

  // The min photon energy (MeV)
  static double min_photon_energy;

  // The max photon energy (MeV)
  static double max_photon_energy;

  // The capture mode (true = implicit capture mode on, false = analogue)
  static bool implicit_capture_mode_on;
};

// Return the free gas thermal treatment temperature threshold
inline double SimulationProperties::getFreeGasThreshold()
{
  return SimulationProperties::free_gas_threshold;
}

// Return the minimum neutron energy (MeV)
inline double SimulationProperties::getMinNeutronEnergy()
{
  return SimulationProperties::min_neutron_energy;
}

// Return the maximum neutron energy (MeV) - cannot be set at runtime
inline double SimulationProperties::getMaxNeutronEnergy()
{
  return SimulationProperties::max_neutron_energy;
}
  
// Return the minimum photon energy (MeV)
inline double SimulationProperties::getMinPhotonEnergy()
{
  return SimulationProperties::min_photon_energy;
}
  
// Return the maximum photon energy (MeV) - cannot be set at runtime
inline double SimulationProperties::getMaxPhotonEnergy()
{
  return SimulationProperties::max_photon_energy;
}

// Return if implicit capture mode has been set
inline bool SimulationProperties::isImplicitCaptureModeOn()
{
  return SimulationProperties::implicit_capture_mode_on;
}

} // end Facemc namespace

#endif // end FACEMC_SIMULATION_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Facemc_SimulationProperties.cpp
//---------------------------------------------------------------------------//
