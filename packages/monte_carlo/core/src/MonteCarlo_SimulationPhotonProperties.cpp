//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationPhotonProperties.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation photon properties class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// The absolute min photon energy (MeV)
const double SimulationPhotonProperties::s_absolute_min_photon_energy = 1e-3;

// The absolute max photon energy (MeV)
const double SimulationPhotonProperties::s_absolute_max_photon_energy = 20.0;

// The absolute min Kahn sampling cutoff energy
const double SimulationPhotonProperties::s_absolute_min_kahn_sampling_cutoff_energy =
  (1.0 + sqrt(3.0))*Utility::PhysicalConstants::electron_rest_mass_energy;

// Constructor
SimulationPhotonProperties::SimulationPhotonProperties()
  : d_min_photon_energy( s_absolute_min_photon_energy ),
    d_max_photon_energy( s_absolute_max_photon_energy ),
    d_kahn_sampling_cutoff_energy( 3.0 ),
    d_num_photon_hash_grid_bins( 1000 ),
    d_incoherent_model_type( COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL ),
    d_atomic_relaxation_mode_on( true ),
    d_detailed_pair_production_mode_on( false ),
    d_photonuclear_interaction_mode_on( false ),
    d_threshold_weight( 0.0 ),
    d_survival_weight()
{ /* ... */ }

// Set the minimum photon energy (MeV)
void SimulationPhotonProperties::setMinPhotonEnergy( const double energy )
{
  // Make sure the energy is valid
  TEST_FOR_EXCEPTION( energy < s_absolute_min_photon_energy,
                      std::runtime_error,
                      "The min photon energy must be greater than or equal to "
                      << Utility::toString(s_absolute_min_photon_energy) <<
                      "!" );
  TEST_FOR_EXCEPTION( energy >= d_max_photon_energy,
                      std::runtime_error,
                      "The min photon energy must be strictly less than the "
                      "max photon energy ("
                      << Utility::toString(d_max_photon_energy) << ")!" );

  d_min_photon_energy = energy;
}

// Return the minimum photon energy (MeV)
double SimulationPhotonProperties::getMinPhotonEnergy() const
{
  return d_min_photon_energy;
}

// Return the absolute minimum photon energy (MeV)
double SimulationPhotonProperties::getAbsoluteMinPhotonEnergy()
{
  return s_absolute_min_photon_energy;
}

// Set the max photon energy (MeV)
void SimulationPhotonProperties::setMaxPhotonEnergy( const double energy )
{
  // Make sure the energy is valid
  TEST_FOR_EXCEPTION( energy <= d_min_photon_energy,
                      std::runtime_error,
                      "The max photon energy must be strictly greater than "
                      "the min photon energy ("
                      << Utility::toString(d_min_photon_energy) << ")!" );
  TEST_FOR_EXCEPTION( energy > s_absolute_max_photon_energy,
                      std::runtime_error,
                      "The max photon energy must be less than or equal to "
                      << Utility::toString(s_absolute_max_photon_energy) <<
                      "!" );

  d_max_photon_energy = energy;
}

// Return the maximum photon energy (MeV) - cannot be set at runtime
double SimulationPhotonProperties::getMaxPhotonEnergy() const
{
  return d_max_photon_energy;
}

// Return the absolute maximum photon energy (MeV)
double SimulationPhotonProperties::getAbsoluteMaxPhotonEnergy()
{
  return s_absolute_max_photon_energy;
}

// Set the Kahn sampling cutoff energy (MeV)
void SimulationPhotonProperties::setKahnSamplingCutoffEnergy( const double energy )
{
  // Make sure the energy is valid
  TEST_FOR_EXCEPTION( energy < s_absolute_min_kahn_sampling_cutoff_energy,
                      std::runtime_error,
                      "The Kahn sampling cutoff energy must be greater than "
                      "or equal to the theoretical cutoff energy ("
                      << Utility::toString(s_absolute_min_kahn_sampling_cutoff_energy) <<
                      ")!" );

  d_kahn_sampling_cutoff_energy = energy;
}

// Return the Kahn sampling cutoff energy (MeV)
double SimulationPhotonProperties::getKahnSamplingCutoffEnergy() const
{
  return d_kahn_sampling_cutoff_energy;
}

// Return the absolute min Kahn sampling cutoff energy (MeV)
double SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy()
{
  return s_absolute_min_kahn_sampling_cutoff_energy;
}

// Set the number of photon hash grid bins
void SimulationPhotonProperties::setNumberOfPhotonHashGridBins(
                                                          const unsigned bins )
{
  // Make sure the number of bins is valid
  TEST_FOR_EXCEPTION( bins == 0,
                      std::runtime_error,
                      "At least one hash grid bin must be set!" );

  d_num_photon_hash_grid_bins = bins;
}

// Get the number of photon hash grid bins
unsigned SimulationPhotonProperties::getNumberOfPhotonHashGridBins() const
{
  return d_num_photon_hash_grid_bins;
}

// Set the incoherent model type
void SimulationPhotonProperties::setIncoherentModelType(
					      const IncoherentModelType model )
{
  d_incoherent_model_type = model;
}

// Return the incoherent model
IncoherentModelType SimulationPhotonProperties::getIncoherentModelType() const
{
  return d_incoherent_model_type;
}

// Set atomic relaxation mode to off (on by default)
void SimulationPhotonProperties::setAtomicRelaxationModeOff()
{
  d_atomic_relaxation_mode_on = false;
}

//! Set atomic relaxation mode to on (on by default)
void SimulationPhotonProperties::setAtomicRelaxationModeOn()
{
  d_atomic_relaxation_mode_on = true;
}

// Return if atomic relaxation mode is on
bool SimulationPhotonProperties::isAtomicRelaxationModeOn() const
{
  return d_atomic_relaxation_mode_on;
}

// Set detailed pair production mode to off (off by default)
void SimulationPhotonProperties::setDetailedPairProductionModeOff()
{
  d_detailed_pair_production_mode_on = false;
}

// Set detailed pair production mode to on (off by default)
void SimulationPhotonProperties::setDetailedPairProductionModeOn()
{
  d_detailed_pair_production_mode_on = true;
}

// Return if detailed pair production mode is on
bool SimulationPhotonProperties::isDetailedPairProductionModeOn() const
{
  return d_detailed_pair_production_mode_on;
}

// Set photonuclear interaction mode to off (off by default)
void SimulationPhotonProperties::setPhotonuclearInteractionModeOff()
{
  d_photonuclear_interaction_mode_on = false;
}

// Set photonuclear interaction mode to on (off by default)
void SimulationPhotonProperties::setPhotonuclearInteractionModeOn()
{
  d_photonuclear_interaction_mode_on = true;
}

// Return if photonuclear interaction mode is on
bool SimulationPhotonProperties::isPhotonuclearInteractionModeOn() const
{
  return d_photonuclear_interaction_mode_on;
}

// Set the cutoff roulette threshold weight
void SimulationPhotonProperties::setPhotonRouletteThresholdWeight(
      const double threshold_weight )
{
  // Make sure the weights are valid
  testPrecondition( threshold_weight > 0.0 );

  d_threshold_weight = threshold_weight;
}

// Return the cutoff roulette threshold weight
double SimulationPhotonProperties::getPhotonRouletteThresholdWeight() const
{
  return d_threshold_weight;
}

// Set the cutoff roulette threshold weight
/*! \details The survival weight should be set after the threshold weight to
 * ensure the weight is valid.
 */
void SimulationPhotonProperties::setPhotonRouletteSurvivalWeight(
      const double survival_weight )
{
  // Make sure the weights are valid
  testPrecondition( survival_weight > d_threshold_weight );

  d_survival_weight = survival_weight;
}

// Return the cutoff roulette survival weight
double SimulationPhotonProperties::getPhotonRouletteSurvivalWeight() const
{
  return d_survival_weight;
}

EXPLICIT_CLASS_SERIALIZE_INST( SimulationPhotonProperties );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SimulationPhotonProperties );

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationPhotonProperties.cpp
//---------------------------------------------------------------------------//
