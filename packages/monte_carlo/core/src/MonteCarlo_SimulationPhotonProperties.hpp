//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationPhotonProperties.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation photon properties class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_PHOTON_PROPERTIES_HPP
#define MONTE_CARLO_SIMULATION_PHOTON_PROPERTIES_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleModeType.hpp"
#include "MonteCarlo_IncoherentModelType.hpp"

namespace MonteCarlo{

/*! The simulation properties class
 * \todo Modify XML parser to handle all options in this class. Use this class
 * in all parts of code that require runtime configuration.
 */
class SimulationPhotonProperties
{
  
public:
  
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

  //! Set the Kahn sampling cutoff energy (MeV) 
  static void setKahnSamplingCutoffEnergy( const double energy );

  //! Return the Kahn sampling cutoff energy (MeV)
  static double getKahnSamplingCutoffEnergy();

  //! Return the absolute min Kahn sampling cutoff energy (MeV)
  static double getAbsoluteMinKahnSamplingCutoffEnergy();

  //! Set the number of photon hash grid bins
  static void setNumberOfPhotonHashGridBins( const unsigned bins );

  //! Get the number of photon hash grid bins
  static unsigned getNumberOfPhotonHashGridBins();

  //! Set the incoherent model type
  static void setIncoherentModelType( const IncoherentModelType model );

  //! Return the incohernt model
  static IncoherentModelType getIncoherentModelType();

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

private:

  // The absolute minimum photon energy (MeV)
  static const double absolute_min_photon_energy;

  // The minimum photon energy (MeV)
  static double min_photon_energy;

  // The maximum photon energy (MeV)
  static double max_photon_energy;

  // The absolute maximum photon energy
  static const double absolute_max_photon_energy;

  // The Kahn sampling cutoff energy (MeV)
  static double kahn_sampling_cutoff_energy;

  // The absolute min Kahn sampling cutoff energy (MeV)
  static const double absolute_min_kahn_sampling_cutoff_energy;

  // The number of photon hash grid bins
  static unsigned num_photon_hash_grid_bins;

  // The incoherent model
  static IncoherentModelType incoherent_model_type;

  // The atomic relaxation mode (true = on - default, false = off)
  static bool atomic_relaxation_mode_on;

  // The detailed pair production mode (true = on, false = off - default)
  static bool detailed_pair_production_mode_on;

  // The photonuclear interaction mode (true = on, false = off - default)
  static bool photonuclear_interaction_mode_on;
};

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

// Return the Kahn sampling cutoff energy (MeV)
inline double SimulationProperties::getKahnSamplingCutoffEnergy()
{
  return SimulationProperties::kahn_sampling_cutoff_energy;
}

// Return the absolute min Kahn sampling cutoff energy (MeV)
inline double SimulationProperties::getAbsoluteMinKahnSamplingCutoffEnergy()
{
  return SimulationProperties::absolute_min_kahn_sampling_cutoff_energy;
}

// Get the number of photon hash grid bins
inline unsigned SimulationProperties::getNumberOfPhotonHashGridBins()
{
  return SimulationProperties::num_photon_hash_grid_bins;
}

// Return the incohernt model
inline IncoherentModelType SimulationProperties::getIncoherentModelType()
{
  return SimulationProperties::incoherent_model_type;
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

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_PHOTON_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationPhotonProperties.cpp
//---------------------------------------------------------------------------//
