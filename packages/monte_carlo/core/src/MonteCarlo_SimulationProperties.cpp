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

// The angle cosine cutoff value for surface flux estimators
double SimulationProperties::surface_flux_estimator_angle_cosine_cutoff =0.001;

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

// The absolute min Kahn sampling cutoff energy
const double SimulationProperties::absolute_min_kahn_sampling_cutoff_energy =
  (1.0 + sqrt(3.0))*Utility::PhysicalConstants::electron_rest_mass_energy;

// The Kahn sampling cutoff energy (MeV)
double SimulationProperties::kahn_sampling_cutoff_energy = 3.0;

// The number of photon has grid bins
unsigned SimulationProperties::num_photon_hash_grid_bins = 1000;

// The absolute min electron energy
const double SimulationProperties::absolute_min_electron_energy = 1.5e-5;

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

// The incoherent model 
IncoherentModelType SimulationProperties::incoherent_model_type = 
  COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL;

// The atomic relaxation mode (true = on - default, false = off)
bool SimulationProperties::atomic_relaxation_mode_on = true;

// The detailed pair production mode (true = on, false = off - default)
bool SimulationProperties::detailed_pair_production_mode_on = false;

// The photonuclear interaction mode (true = on, false = off - default)
bool SimulationProperties::photonuclear_interaction_mode_on = false;

// The bremsstrahlung photon angular distribution function (2BS by default)
BremsstrahlungAngularDistributionType 
  SimulationProperties::bremsstrahlung_angular_distribution_function = 
                             TWOBS_DISTRIBUTION;

// The elastic cutoff angle cosine (default 1.0)
double SimulationProperties::elastic_cutoff_angle_cosine = 1.0;

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

// Set the angle cosine cutoff value for surface flux estimators
/*! \details When the angle cosine falls below the given cutoff an
 * approximation is used for the angle cosine to help bound the flux (avoids
 * a possible divide by zero).
 */
void SimulationProperties::setSurfaceFluxEstimatorAngleCosineCutoff( 
							  const double cutoff )
{
  // Make sure the cutoff is valid
  testPrecondition( cutoff > 0.0 );
  testPrecondition( cutoff < 1.0 );

  SimulationProperties::surface_flux_estimator_angle_cosine_cutoff = cutoff;
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

// Set the Kahn sampling cutoff energy (MeV) 
void SimulationProperties::setKahnSamplingCutoffEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( energy >= SimulationProperties::getAbsoluteMinKahnSamplingCutoffEnergy() );

  SimulationProperties::kahn_sampling_cutoff_energy = energy;
}

// Set the number of photon hash grid bins
void SimulationProperties::setNumberOfPhotonHashGridBins( const unsigned bins )
{
  // Make sure the number of bins is valid
  testPrecondition( bins >= 1 );

  SimulationProperties::num_photon_hash_grid_bins = bins;
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

// Set the incoherent model type
void SimulationProperties::setIncoherentModelType( 
					      const IncoherentModelType model )
{
  SimulationProperties::incoherent_model_type = model;
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

// Set the bremsstrahlung photon angular distribution function (2BS by default)
void SimulationProperties::setBremsstrahlungAngularDistributionFunction( 
                          const BremsstrahlungAngularDistributionType function )
{
  SimulationProperties::bremsstrahlung_angular_distribution_function = function;
}

// Set the elastic cutoff angle cosine (mu = 1.0 by default)
void SimulationProperties::setElasticCutoffAngleCosine( 
                          const double cutoff_angle_cosine )
{
  SimulationProperties::elastic_cutoff_angle_cosine = cutoff_angle_cosine;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationProperties.cpp
//---------------------------------------------------------------------------//
