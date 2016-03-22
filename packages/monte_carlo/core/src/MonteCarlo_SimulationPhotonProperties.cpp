//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationPhotonProperties.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation photon properties class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// The absolute min photon energy (MeV)
const double SimulationPhotonProperties::absolute_min_photon_energy = 1e-3;

// The min photon energy (MeV)
double SimulationPhotonProperties::min_photon_energy =
  SimulationPhotonProperties::absolute_min_photon_energy;

// The absolute max photon energy (MeV)
const double SimulationPhotonProperties::absolute_max_photon_energy = 20.0;

// The max photon energy (MeV)
double SimulationPhotonProperties::max_photon_energy = 
  SimulationPhotonProperties::absolute_max_photon_energy;

// The absolute min Kahn sampling cutoff energy
const double SimulationPhotonProperties::absolute_min_kahn_sampling_cutoff_energy =
  (1.0 + sqrt(3.0))*Utility::PhysicalConstants::electron_rest_mass_energy;

// The Kahn sampling cutoff energy (MeV)
double SimulationPhotonProperties::kahn_sampling_cutoff_energy = 3.0;

// The number of photon has grid bins
unsigned SimulationPhotonProperties::num_photon_hash_grid_bins = 1000;

// The incoherent model 
IncoherentModelType SimulationPhotonProperties::incoherent_model_type = 
  COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL;

// The atomic relaxation mode (true = on - default, false = off)
bool SimulationPhotonProperties::atomic_relaxation_mode_on = true;

// The detailed pair production mode (true = on, false = off - default)
bool SimulationPhotonProperties::detailed_pair_production_mode_on = false;

// The photonuclear interaction mode (true = on, false = off - default)
bool SimulationPhotonProperties::photonuclear_interaction_mode_on = false;

// Set the minimum photon energy (MeV)
void SimulationPhotonProperties::setMinPhotonEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition(energy >= SimulationPhotonProperties::absolute_min_photon_energy);
  testPrecondition( energy < SimulationPhotonProperties::max_photon_energy );
  
  SimulationPhotonProperties::min_photon_energy = energy;
}

// Set the max photon energy (MeV)
void SimulationPhotonProperties::setMaxPhotonEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition(energy > SimulationPhotonProperties::min_photon_energy );
  testPrecondition(energy <= SimulationPhotonProperties::absolute_max_photon_energy);

  SimulationPhotonProperties::max_photon_energy = energy;
}

// Set the Kahn sampling cutoff energy (MeV) 
void SimulationPhotonProperties::setKahnSamplingCutoffEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( energy >= SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy() );

  SimulationPhotonProperties::kahn_sampling_cutoff_energy = energy;
}

// Set the number of photon hash grid bins
void SimulationPhotonProperties::setNumberOfPhotonHashGridBins( const unsigned bins )
{
  // Make sure the number of bins is valid
  testPrecondition( bins >= 1 );

  SimulationPhotonProperties::num_photon_hash_grid_bins = bins;
}

// Set the incoherent model type
void SimulationPhotonProperties::setIncoherentModelType( 
					      const IncoherentModelType model )
{
  SimulationPhotonProperties::incoherent_model_type = model;
}

// Set atomic relaxation mode to off (on by default)
void SimulationPhotonProperties::setAtomicRelaxationModeOff()
{
  SimulationPhotonProperties::atomic_relaxation_mode_on = false;
}

// Set detailed pair production mode to on (off by default)
void SimulationPhotonProperties::setDetailedPairProductionModeOn()
{
  SimulationPhotonProperties::detailed_pair_production_mode_on = true;
}

// Set photonuclear interaction mode to on (off by default)
void SimulationPhotonProperties::setPhotonuclearInteractionModeOn()
{
  SimulationPhotonProperties::photonuclear_interaction_mode_on = true;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationPhotonProperties.cpp
//---------------------------------------------------------------------------//
