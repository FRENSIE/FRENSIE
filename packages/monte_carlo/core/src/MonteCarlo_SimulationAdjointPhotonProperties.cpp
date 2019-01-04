//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationAdjointPhotonProperties.hpp
//! \author Alex Robinson
//! \brief  Simulation adjoint photon properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// The absolute mimimum adjoint photon energy (MeV)
const double SimulationAdjointPhotonProperties::s_absolute_min_adjoint_photon_energy = 1e-3;

// The absolute maximum adjoint photon energy (MeV)
const double SimulationAdjointPhotonProperties::s_absolute_max_adjoint_photon_energy = 20.0;

// Constructor
SimulationAdjointPhotonProperties::SimulationAdjointPhotonProperties()
  : d_min_adjoint_photon_energy( s_absolute_min_adjoint_photon_energy ),
    d_max_adjoint_photon_energy( s_absolute_max_adjoint_photon_energy ),
    d_num_adjoint_photon_hash_grid_bins( 500 ),
    d_incoherent_adjoint_model_type( DB_IMPULSE_INCOHERENT_ADJOINT_MODEL ),
    d_adjoint_kn_sampling_type( TWO_BRANCH_REJECTION_ADJOINT_KN_SAMPLING ),
    d_critical_line_energies(),
    d_threshold_weight( 0.0 ),
    d_survival_weight()
{ /* ... */ }

// Set the minimum adjoint photon energy (MeV)
void SimulationAdjointPhotonProperties::setMinAdjointPhotonEnergy( const double energy )
{
  // Make sure the energy is valid
  TEST_FOR_EXCEPTION( energy < s_absolute_min_adjoint_photon_energy,
                      std::runtime_error,
                      "The min adjoint photon energy must be greater than or "
                      "equal to "
                      << Utility::toString(s_absolute_min_adjoint_photon_energy) <<
                      "!" );
  TEST_FOR_EXCEPTION( energy >= d_max_adjoint_photon_energy,
                      std::runtime_error,
                      "The min adjoint photon energy must be strictly less "
                      "than the max adjoint photon energy ("
                      << Utility::toString(d_max_adjoint_photon_energy) <<
                      ")!" );

  d_min_adjoint_photon_energy = energy;
}

// Return the minimum adjoint photon energy (MeV)
double SimulationAdjointPhotonProperties::getMinAdjointPhotonEnergy() const
{
  return d_min_adjoint_photon_energy;
}

// Return the absolute minimum adjoint photon energy (MeV)
double SimulationAdjointPhotonProperties::getAbsoluteMinAdjointPhotonEnergy()
{
  return s_absolute_min_adjoint_photon_energy;
}

// Set the maximum adjoint photon energy (MeV)
void SimulationAdjointPhotonProperties::setMaxAdjointPhotonEnergy( const double energy )
{
  // Make sure the energy is valid
  TEST_FOR_EXCEPTION( energy <= d_min_adjoint_photon_energy,
                      std::runtime_error,
                      "The max adjoint photon energy must be strictly greater "
                      "than the min adjoint photon energy ("
                      << Utility::toString(d_min_adjoint_photon_energy) <<
                      ")!" );
  TEST_FOR_EXCEPTION( energy > s_absolute_max_adjoint_photon_energy,
                      std::runtime_error,
                      "The max adjoint photon energy must be less that or "
                      "equal to "
                      << Utility::toString(s_absolute_max_adjoint_photon_energy) <<
                      "!" );

  d_max_adjoint_photon_energy = energy;
}

// Return the maximum adjoint photon energy (MeV)
double SimulationAdjointPhotonProperties::getMaxAdjointPhotonEnergy() const
{
  return d_max_adjoint_photon_energy;
}

// Return the absolute maximum adjoint photon energy (MeV)
double SimulationAdjointPhotonProperties::getAbsoluteMaxAdjointPhotonEnergy()
{
  return s_absolute_max_adjoint_photon_energy;
}

// Set the number of adjoint photon hash grid bins
void SimulationAdjointPhotonProperties::setNumberOfAdjointPhotonHashGridBins(
                                                          const unsigned bins )
{
  // Make sure the number of bins is valid
  TEST_FOR_EXCEPTION( bins == 0,
                      std::runtime_error,
                      "At least on hash grid bin must be assigned!" );

  d_num_adjoint_photon_hash_grid_bins = bins;
}

// Get the number of adjoint photon hash grid bins
unsigned SimulationAdjointPhotonProperties::getNumberOfAdjointPhotonHashGridBins() const
{
  return d_num_adjoint_photon_hash_grid_bins;
}

// Set the incoherent adjoint model type
void SimulationAdjointPhotonProperties::setIncoherentAdjointModelType(
                                       const IncoherentAdjointModelType model )
{
  d_incoherent_adjoint_model_type = model;
}

// Return the incoherent adjoint model type
IncoherentAdjointModelType SimulationAdjointPhotonProperties::getIncoherentAdjointModelType() const
{
  return d_incoherent_adjoint_model_type;
}

// Set the adjoint Klein-Nishina sampling type
AdjointKleinNishinaSamplingType SimulationAdjointPhotonProperties::setAdjointKleinNishinaSamplingType(
                          const AdjointKleinNishinaSamplingType sampling_type )
{
  d_adjoint_kn_sampling_type = sampling_type;
}

// Return the adjoint Klein-Nishina sampling type
AdjointKleinNishinaSamplingType SimulationAdjointPhotonProperties::getAdjointKleinNishinaSamplingType() const
{
  return d_adjoint_kn_sampling_type;
}

// Set the critical line energies
/*! \details Do not change with min/max adjoint photon energy after setting
 * the critical line energies as the line energies may become invalid!
 */
void SimulationAdjointPhotonProperties::setCriticalAdjointPhotonLineEnergies(
                         const std::vector<double>& critical_line_energies )
{
  // Make sure there is at least one energy
  TEST_FOR_EXCEPTION( critical_line_energies.empty(),
                      std::runtime_error,
                      "There must be at least one critical line energy!" );
  // Make sure the critical line energies are sorted
  TEST_FOR_EXCEPTION( !Utility::Sort::isSortedAscending(
                                              critical_line_energies.begin(),
                                              critical_line_energies.end() ),
                      std::runtime_error,
                      "The critical line energies must be sorted!" );
  // Make sure the critical line energies are valid
  TEST_FOR_EXCEPTION( critical_line_energies.back() >
                      d_max_adjoint_photon_energy,
                      std::runtime_error,
                      "The max critical line energy must be less than or "
                      "or equal to the max adjoint photon energy!" );
  TEST_FOR_EXCEPTION( critical_line_energies.front() <
                      d_min_adjoint_photon_energy,
                      std::runtime_error,
                      "The min critical line energy must be greater than or "
                      "equal to the min adjoint photon energy!" );

  d_critical_line_energies = critical_line_energies;
}

// Get the critical line energies
const std::vector<double>&
SimulationAdjointPhotonProperties::getCriticalAdjointPhotonLineEnergies() const
{
  return d_critical_line_energies;
}

// Set the cutoff roulette threshold weight
void SimulationAdjointPhotonProperties::setAdjointPhotonRouletteThresholdWeight(
      const double threshold_weight )
{
  // Make sure the weights are valid
  testPrecondition( threshold_weight > 0.0 );

  d_threshold_weight = threshold_weight;
}

// Return the cutoff roulette threshold weight
double SimulationAdjointPhotonProperties::getAdjointPhotonRouletteThresholdWeight() const
{
  return d_threshold_weight;
}

// Set the cutoff roulette threshold weight
/*! \details The survival weight should be set after the threshold weight to
 * ensure the weight is valid.
 */
void SimulationAdjointPhotonProperties::setAdjointPhotonRouletteSurvivalWeight(
      const double survival_weight )
{
  // Make sure the weights are valid
  testPrecondition( survival_weight > d_threshold_weight );

  d_survival_weight = survival_weight;
}

// Return the cutoff roulette survival weight
double SimulationAdjointPhotonProperties::getAdjointPhotonRouletteSurvivalWeight() const
{
  return d_survival_weight;
}

EXPLICIT_CLASS_SERIALIZE_INST( SimulationAdjointPhotonProperties );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SimulationAdjointPhotonProperties );

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationAdjointPhotonProperties.cpp
//---------------------------------------------------------------------------//
