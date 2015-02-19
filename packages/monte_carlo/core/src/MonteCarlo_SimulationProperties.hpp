//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationProperties.hpp
//! \author Alex Robinson
//! \brief  Simulation properties class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_PROPERTIES_HPP
#define MONTE_CARLO_SIMULATION_PROPERTIES_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleModeType.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"

namespace MonteCarlo{

/*! The simulation properties class
 * \todo Modify XML parser to handle all options in this class. Use this class
 * in all parts of code that require runtime configuration.
 */
class SimulationProperties
{
  
public:

  //! Set the particle mode
  static void setParticleMode( const ParticleModeType particle_mode );

  //! Return the particle mode type
  static ParticleModeType getParticleMode();

  //! Set the number of histories to run
  static void setNumberOfHistories( const unsigned long long histories );

  //! Return the number of histories to run
  static unsigned long long getNumberOfHistories();

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
  
  //! Set the minimum photon energy (MeV)
  static void setMinPhotonEnergy( const double energy );

  //! Return the minimum photon energy (MeV)
  static double getMinPhotonEnergy();

  //! Return the absolute minimum photon energy (MeV)
  static double getAbsoluteMinPhotonEnergy();
  
  //! Set the maximum photon energy (MeV)
  static void setMaxPhotonEnergy( const double energy );

  //! Return the maximum photon energy (MeV)
  static double getMaxPhotonEnergy();

  //! Return the absolute maximum photon energy (MeV)
  static double getAbsoluteMaxPhotonEnergy();

  //! Set the minimum electron energy (MeV)
  static void setMinElectronEnergy( const double energy );

  //! Return the minimum electron energy (MeV)
  static double getMinElectronEnergy();

  //! Return the absolute minimum electron energy (MeV)
  static double getAbsoluteMinElectronEnergy();

  //! Set the maximum electron energy (MeV)
  static void setMaxElectronEnergy( const double energy );
  
  //! Return the maximum electron energy (MeV)
  static double getMaxElectronEnergy();

  //! Return the absolute maximum electron energy (MeV)
  static double getAbsoluteMaxElectronEnergy();

  //! Return the min particle energy
  template<typename ParticleType>
  static double getMinParticleEnergy();

  //! Return the max particle energy
  template<typename ParticleType>
  static double getMaxParticleEnergy();

  //! Set implicit capture mode to on (off by default)
  static void setImplicitCaptureModeOn();

  //! Return if implicit capture mode has been set
  static bool isImplicitCaptureModeOn();

  //! Set photon Doppler broadening mode to off (on by default)
  static void setPhotonDopplerBroadeningModeOff();

  //! Return if photon Doppler broadening mode is on
  static bool isPhotonDopplerBroadeningModeOn();

  //! Set atomic relaxation mode to off (on by default)
  static void setAtomicRelaxationModeOff();

  //! Return if atomic relaxation mode is on
  static bool isAtomicRelaxationModeOn();

  //! Set detailed pair production mode to on (off by default)
  static void setDetailedPairProductionModeOn();

  //! Return if detailed pair production mode is on
  static bool isDetailedPairProductionModeOn();

  //! Set photonuclear interaction mode to on (off by default)
  static void setPhotonuclearInteractionModeOn();

  //! Return if photonuclear interaction mode is on
  static bool isPhotonuclearInteractionModeOn();

  //! Set the bremsstrahlung photon angular distribution function (2BS by default)
  static void setBremsstrahlungAngularDistributionFunction( 
                         const BremsstrahlungAngularDistributionType function );

  //! Return the bremsstrahlung photon angular distribution function
  static BremsstrahlungAngularDistributionType 
          getBremsstrahlungAngularDistributionFunction();

private:

  // The particle mode
  static ParticleModeType particle_mode;

  // The number of histories to run
  static unsigned long long number_of_histories;

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

  // The minimum photon energy (MeV)
  static double min_photon_energy;

  // The maximum photon energy (MeV)
  static double max_photon_energy;

  // The absolute maximum photon energy
  static const double absolute_max_photon_energy;

  // The absolute minimum electron energy
  static const double absolute_min_electron_energy;

  // The minimum electron energy (MeV)
  static double min_electron_energy;

  // The maximum electron energy (MeV)
  static double max_electron_energy;

  // The absolute maximum electron energy (MeV)
  static const double absolute_max_electron_energy;

  // The capture mode (true = implicit, false = analogue - default)
  static bool implicit_capture_mode_on;

  // The photon Doppler broadening mode (true = on - default, false = off)
  static bool doppler_broadening_mode_on;

  // The atomic relaxation mode (true = on - default, false = off)
  static bool atomic_relaxation_mode_on;

  // The detailed pair production mode (true = on, false = off - default)
  static bool detailed_pair_production_mode_on;

  // The photonuclear interaction mode (true = on, false = off - default)
  static bool photonuclear_interaction_mode_on;

  // The bremsstrahlung photon angular distribution function (default is 2BS)
  static BremsstrahlungAngularDistributionType 
           bremsstrahlung_angular_distribution_function;
};

// Return the particle mode type
inline ParticleModeType SimulationProperties::getParticleMode()
{
  return SimulationProperties::particle_mode;
}

//! Return the number of histories to run
inline unsigned long long SimulationProperties::getNumberOfHistories()
{
  return SimulationProperties::number_of_histories;
}

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

// Return the absolute min neutron energy (MeV)
inline double SimulationProperties::getAbsoluteMinNeutronEnergy()
{
  return SimulationProperties::absolute_min_neutron_energy;
}

// Return the maximum neutron energy (MeV) - cannot be set at runtime
inline double SimulationProperties::getMaxNeutronEnergy()
{
  return SimulationProperties::max_neutron_energy;
}

// Return the absolute maximum neutron energy (MeV)
inline double SimulationProperties::getAbsoluteMaxNeutronEnergy()
{
  return SimulationProperties::absolute_max_neutron_energy;
}
  
// Return the minimum photon energy (MeV)
inline double SimulationProperties::getMinPhotonEnergy()
{
  return SimulationProperties::min_photon_energy;
}

// Return the absolute minimum photon energy (MeV)
inline double SimulationProperties::getAbsoluteMinPhotonEnergy()
{
  return SimulationProperties::absolute_min_photon_energy;
}
  
// Return the maximum photon energy (MeV) - cannot be set at runtime
inline double SimulationProperties::getMaxPhotonEnergy()
{
  return SimulationProperties::max_photon_energy;
}

// Return the absolute maximum photon energy (MeV)
inline double SimulationProperties::getAbsoluteMaxPhotonEnergy()
{
  return SimulationProperties::absolute_max_photon_energy;
}

// Return the minimum electron energy (MeV)
inline double SimulationProperties::getMinElectronEnergy()
{
  return SimulationProperties::min_electron_energy;
}

// Return the absolute minimum electron energy (MeV)
inline double SimulationProperties::getAbsoluteMinElectronEnergy()
{
  return SimulationProperties::absolute_min_electron_energy;
}
  
// Return the maximum electron energy (MeV) - cannot be set at runtime
inline double SimulationProperties::getMaxElectronEnergy()
{
  return SimulationProperties::max_electron_energy;
}

// Return the absolute maximum electron energy (MeV)
inline double SimulationProperties::getAbsoluteMaxElectronEnergy()
{
  return SimulationProperties::absolute_max_electron_energy;
}

// Return if implicit capture mode has been set
inline bool SimulationProperties::isImplicitCaptureModeOn()
{
  return SimulationProperties::implicit_capture_mode_on;
}

// Return if photon Doppler broadening mode is on
inline bool SimulationProperties::isPhotonDopplerBroadeningModeOn()
{
  return SimulationProperties::doppler_broadening_mode_on;
}

// Return if atomic relaxation mode is on
inline bool SimulationProperties::isAtomicRelaxationModeOn()
{
  return SimulationProperties::atomic_relaxation_mode_on;
}

// Return if detailed pair production mode is on
inline bool SimulationProperties::isDetailedPairProductionModeOn()
{
  return SimulationProperties::detailed_pair_production_mode_on;
}

// Return if photonuclear interaction mode is on
inline bool SimulationProperties::isPhotonuclearInteractionModeOn()
{
  return SimulationProperties::photonuclear_interaction_mode_on;
}

// Return if detailed bremsstrahlung mode is on
inline BremsstrahlungAngularDistributionType 
  SimulationProperties::getBremsstrahlungAngularDistributionFunction()
{
  return SimulationProperties::bremsstrahlung_angular_distribution_function;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_SimulationProperties_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_SIMULATION_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationProperties.cpp
//---------------------------------------------------------------------------//
