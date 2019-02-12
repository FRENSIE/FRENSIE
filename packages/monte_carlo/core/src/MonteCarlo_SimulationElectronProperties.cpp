//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationElectronProperties.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation electron properties class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// The absolute min electron energy
const double SimulationElectronProperties::s_absolute_min_electron_energy = 1.5e-5;

// The absolute max electron energy (MeV)
const double SimulationElectronProperties::s_absolute_max_electron_energy = 1.0e5;

// Constructor
SimulationElectronProperties::SimulationElectronProperties()
  : d_min_electron_energy( 1e-4 ),
    d_max_electron_energy( 20.0 ),
    d_evaluation_tol( 1e-7 ),
    d_electron_interpolation_type( LOGLOGLOG_INTERPOLATION ),
    d_electron_grid_type( UNIT_BASE_CORRELATED_GRID ),
    d_num_electron_hash_grid_bins( 1000 ),
    d_atomic_relaxation_mode_on( true ),
    d_elastic_mode_on( true ),
    d_elastic_interpolation_type( LOGLOGLOG_INTERPOLATION ),
    d_elastic_distribution_mode( COUPLED_DISTRIBUTION ),
    d_coupled_elastic_sampling_method( MODIFIED_TWO_D_UNION ),
    d_elastic_cutoff_angle_cosine( 1.0 ),
    d_bremsstrahlung_mode_on( true ),
    d_bremsstrahlung_interpolation_type( LOGLOGLOG_INTERPOLATION ),
    d_bremsstrahlung_angular_distribution_function( TWOBS_DISTRIBUTION ),
    d_electroionization_mode_on( true ),
    d_electroionization_interpolation_type( LOGLOGLOG_INTERPOLATION ),
    d_electroionization_sampling_mode( KNOCK_ON_SAMPLING ),
    d_atomic_excitation_mode_on( true ),
    d_threshold_weight( 0.0 ),
    d_survival_weight()
{ /* ... */ }

// Set the minimum electron energy (MeV)
void SimulationElectronProperties::setMinElectronEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition(energy >= s_absolute_min_electron_energy);
  testPrecondition( energy < d_max_electron_energy );

  d_min_electron_energy = energy;
}

// Return the minimum electron energy (MeV)
double SimulationElectronProperties::getMinElectronEnergy() const
{
  return d_min_electron_energy;
}

// Return the absolute minimum electron energy (MeV)
double SimulationElectronProperties::getAbsoluteMinElectronEnergy()
{
  return s_absolute_min_electron_energy;
}

// Set the maximum electron energy (MeV)
void SimulationElectronProperties::setMaxElectronEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( energy > d_min_electron_energy );
  testPrecondition(energy <= s_absolute_max_electron_energy);

  d_max_electron_energy = energy;
}

// Return the maximum electron energy (MeV) - cannot be set at runtime
double SimulationElectronProperties::getMaxElectronEnergy() const
{
  return d_max_electron_energy;
}

// Return the absolute maximum electron energy (MeV)
double SimulationElectronProperties::getAbsoluteMaxElectronEnergy()
{
  return s_absolute_max_electron_energy;
}

// Set the electron FullyTabularTwoDDistribution evaluation tolerance (default = 1e-7)
/*! \details The evaluation tolerance is used by the
 *  InterpolatedFullyTabularTwoDDistribution as the tolerance when performing
 *  evaluations.
 */
void SimulationElectronProperties::setElectronEvaluationTolerance(
    const double tol )
{
  d_evaluation_tol = tol;
}

// Return the electron FullyTabularTwoDDistribution evaluation tolerance (default = 1e-7)
/*! \details The evaluation tolerance is used by the
 *  InterpolatedFullyTabularTwoDDistribution as the tolerance when performing
 *  evaluations.
 */
double SimulationElectronProperties::getElectronEvaluationTolerance() const
{
  return d_evaluation_tol;
}

// Set the electron 2D interpolation policy (LogLogLog by default)
void SimulationElectronProperties::setElectronTwoDInterpPolicy(
    const TwoDInterpolationType interp_type )
{
  d_electron_interpolation_type = interp_type;
}

// Return the electron 2D interpolation policy
TwoDInterpolationType
SimulationElectronProperties::getElectronTwoDInterpPolicy() const
{
  return d_electron_interpolation_type;
}

// Set the electron bivariate grid policy (Unit-base Correlated by default)
void SimulationElectronProperties::setElectronTwoDGridPolicy(
    TwoDGridType grid_type )
{
  d_electron_grid_type = grid_type;
}

// Return the electron bivariate grid policy
TwoDGridType
SimulationElectronProperties::getElectronTwoDGridPolicy() const
{
  return d_electron_grid_type;
}

// Set the number of electron hash grid bins
void SimulationElectronProperties::setNumberOfElectronHashGridBins(
                                                          const unsigned bins )
{
  // Make sure the number of bins is valid
  testPrecondition( bins >= 1 );

  d_num_electron_hash_grid_bins = bins;
}

// Get the number of electron hash grid bins
unsigned SimulationElectronProperties::getNumberOfElectronHashGridBins() const
{
  return d_num_electron_hash_grid_bins;
}

// Set atomic relaxation mode to off (on by default)
void SimulationElectronProperties::setAtomicRelaxationModeOff()
{
  d_atomic_relaxation_mode_on = false;
}

// Set atomic relaxation mode to on (on by default)
void SimulationElectronProperties::setAtomicRelaxationModeOn()
{
  d_atomic_relaxation_mode_on = true;
}

// Return if atomic relaxation mode is on
bool SimulationElectronProperties::isAtomicRelaxationModeOn() const
{
  return d_atomic_relaxation_mode_on;
}

// Set elastic mode to off (on by default)
void SimulationElectronProperties::setElasticModeOff()
{
  d_elastic_mode_on = false;
}

// Set elastic mode to on (on by default)
void SimulationElectronProperties::setElasticModeOn()
{
  d_elastic_mode_on = true;
}

// Return if elastic mode is on
bool SimulationElectronProperties::isElasticModeOn() const
{
  return d_elastic_mode_on;
}

// Set the elastic distribution mode ( Decoupled by default )
void SimulationElectronProperties::setElasticElectronDistributionMode(
    const ElasticElectronDistributionType distribution_mode )
{
  d_elastic_distribution_mode = distribution_mode;
}

// Return the elastic distribution mode
ElasticElectronDistributionType
SimulationElectronProperties::getElasticElectronDistributionMode() const
{
  return d_elastic_distribution_mode;
}

// Set the coupled elastic sampling mode ( Two D Union by default )
void SimulationElectronProperties::setCoupledElasticSamplingMode(
    const CoupledElasticSamplingMethod sampling_method )
{
  d_coupled_elastic_sampling_method = sampling_method;
}

// Return the coupled elastic sampling mode
CoupledElasticSamplingMethod
SimulationElectronProperties::getCoupledElasticSamplingMode() const
{
  return d_coupled_elastic_sampling_method;
}

// Set the elastic cutoff angle cosine (mu = 1.0 by default)
void SimulationElectronProperties::setElasticCutoffAngleCosine(
                          const double cutoff_angle_cosine )
{
  d_elastic_cutoff_angle_cosine = cutoff_angle_cosine;
}

// Return the elastic cutoff angle cosine
double SimulationElectronProperties::getElasticCutoffAngleCosine() const
{
  return d_elastic_cutoff_angle_cosine;
}

// Set electroionization mode to off (on by default)
void SimulationElectronProperties::setElectroionizationModeOff()
{
  d_electroionization_mode_on = false;
}

// Set electroionization mode to on (on by default)
void SimulationElectronProperties::setElectroionizationModeOn()
{
  d_electroionization_mode_on = true;
}

// Return if electroionization mode is on
bool SimulationElectronProperties::isElectroionizationModeOn() const
{
  return d_electroionization_mode_on;
}

// Set the electroionization sampling mode (KNOCK_ON_SAMPLING by default)
void SimulationElectronProperties::setElectroionizationSamplingMode(
                        const ElectroionizationSamplingType sampling_mode )
{
  d_electroionization_sampling_mode = sampling_mode;
}

// Return the electroionization sampling mode
ElectroionizationSamplingType
SimulationElectronProperties::getElectroionizationSamplingMode() const
{
  return d_electroionization_sampling_mode;
}

// Set bremsstrahlung mode to off (on by default)
void SimulationElectronProperties::setBremsstrahlungModeOff()
{
  d_bremsstrahlung_mode_on = false;
}

// Set bremsstrahlung mode to on (on by default)
void SimulationElectronProperties::setBremsstrahlungModeOn()
{
  d_bremsstrahlung_mode_on = true;
}

// Return if bremsstrahlung mode is on
bool SimulationElectronProperties::isBremsstrahlungModeOn() const
{
  return d_bremsstrahlung_mode_on;
}

// Set the bremsstrahlung photon angular distribution function (2BS by default)
void SimulationElectronProperties::setBremsstrahlungAngularDistributionFunction(
                          const BremsstrahlungAngularDistributionType function )
{
  d_bremsstrahlung_angular_distribution_function = function;
}

// Return the bremsstrahlung photon angular distribution function (2BS by default)
BremsstrahlungAngularDistributionType
SimulationElectronProperties::getBremsstrahlungAngularDistributionFunction() const
{
  return d_bremsstrahlung_angular_distribution_function;
}

// Set atomic excitation mode to off (on by default)
void SimulationElectronProperties::setAtomicExcitationModeOff()
{
  d_atomic_excitation_mode_on = false;
}

// Set atomic excitation mode to on (on by default)
void SimulationElectronProperties::setAtomicExcitationModeOn()
{
  d_atomic_excitation_mode_on = true;
}

// Return if atomic excitation mode is on
bool SimulationElectronProperties::isAtomicExcitationModeOn() const
{
  return d_atomic_excitation_mode_on;
}

// Set the cutoff roulette threshold weight
void SimulationElectronProperties::setElectronRouletteThresholdWeight(
      const double threshold_weight )
{
  // Make sure the weights are valid
  testPrecondition( threshold_weight > 0.0 );

  d_threshold_weight = threshold_weight;
}

// Return the cutoff roulette threshold weight
double SimulationElectronProperties::getElectronRouletteThresholdWeight() const
{
  return d_threshold_weight;
}

// Set the cutoff roulette threshold weight
/*! \details The survival weight should be set after the threshold weight to
 * ensure the weight is valid.
 */
void SimulationElectronProperties::setElectronRouletteSurvivalWeight(
      const double survival_weight )
{
  // Make sure the weights are valid
  testPrecondition( survival_weight > d_threshold_weight );

  d_survival_weight = survival_weight;
}

// Return the cutoff roulette survival weight
double SimulationElectronProperties::getElectronRouletteSurvivalWeight() const
{
  return d_survival_weight;
}

EXPLICIT_CLASS_SERIALIZE_INST( SimulationElectronProperties );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SimulationElectronProperties );

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationElectronProperties.cpp
//---------------------------------------------------------------------------//
