//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationGeneralProperties.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation general properties class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must be included first
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
SimulationGeneralProperties::SimulationGeneralProperties()
  : d_particle_mode( NEUTRON_MODE ),
    d_number_of_histories( 0 ),
    d_min_number_of_rendezvous( 1 ),
    d_max_rendezvous_batch_size( 1000000000 ),
    d_min_number_of_batches_per_rendezvous( 1 ),
    d_max_batch_size( d_max_rendezvous_batch_size ),
    d_number_of_batches_per_processor( 1 ),
    d_wall_time( Utility::QuantityTraits<double>::inf() ),
    d_surface_flux_estimator_angle_cosine_cutoff( 0.001 ),
    d_display_warnings( true ),
    d_implicit_capture_mode_on( false )
{ /* ... */ }
  
// Set the particle mode
void SimulationGeneralProperties::setParticleMode(
                                         const ParticleModeType particle_mode )
{
  d_particle_mode = particle_mode;
}

// Return the particle mode type
ParticleModeType SimulationGeneralProperties::getParticleMode() const
{
  return d_particle_mode;
}

// Set the number of histories to run
/*! \details Setting the number of histories to zero is acceptable if a wall
 * time is set and batch sizes are set.
 */
void SimulationGeneralProperties::setNumberOfHistories(
                                           const unsigned long long histories )
{
  d_number_of_histories = histories;
}

// Return the number of histories to run
unsigned long long SimulationGeneralProperties::getNumberOfHistories() const
{
  return d_number_of_histories;
}

// Set the minimum number of rendezvous per simulation
void SimulationGeneralProperties::setMinNumberOfRendezvous(
                                                   const uint64_t rendezvous )
{
  TEST_FOR_EXCEPTION( rendezvous == 0,
                      std::runtime_error,
                      "There must be at least on rendezvous!" );

  d_min_number_of_rendezvous = rendezvous;
}

// Return the mimimum number of rendezvous per simulation
uint64_t SimulationGeneralProperties::getMinNumberOfRendezvous() const
{
  return d_min_number_of_rendezvous;
}

// Set the maximum rendezvous batch size
void SimulationGeneralProperties::setMaxRendezvousBatchSize(
                                                const uint64_t max_batch_size )
{
  TEST_FOR_EXCEPTION( max_batch_size == 0,
                      std::runtime_error,
                      "The max rendezvous batch size must be greater "
                      "than 0!" );

  d_max_rendezvous_batch_size = max_batch_size;
}

// Get the maximum rendezvous batch size
uint64_t SimulationGeneralProperties::getMaxRendezvousBatchSize() const
{
  return d_max_rendezvous_batch_size;
}

// Set the minimum number of batches per rendezvous
void SimulationGeneralProperties::setMinNumberOfBatchesPerRendezvous(
                                                       const uint64_t batches )
{
  TEST_FOR_EXCEPTION( batches == 0,
                      std::runtime_error,
                      "The minimum number of batches per rendezvous must be "
                      "greater than 0!" );

  d_min_number_of_batches_per_rendezvous = batches;
}

// Get the minimum number of batches per rendezvous
uint64_t SimulationGeneralProperties::getMinNumberOfBatchesPerRendezvous() const
{
  return d_min_number_of_batches_per_rendezvous;
}

// Set the maximum batch size
void SimulationGeneralProperties::setMaxBatchSize( const uint64_t max_batch_size )
{
  TEST_FOR_EXCEPTION( max_batch_size == 0,
                      std::runtime_error,
                      "The max batch size must be greater than 0!" );

  d_max_batch_size = max_batch_size;
}

// Get the maximum batch size
uint64_t SimulationGeneralProperties::getMaxBatchSize() const
{
  return d_max_batch_size;
}

// Set the ideal number of batches per processor for an MPI configuration
/*! \details The rendezvous batch size will be used to determine the batch
 * size per processor.
 */
void SimulationGeneralProperties::setNumberOfBatchesPerProcessor(
                                                       const uint64_t batches )
{
  // There must be at least one batch
  TEST_FOR_EXCEPTION( batches == 0,
                      std::runtime_error,
                      "There must be at least one batch per processor!" );
  
  d_number_of_batches_per_processor = batches;
}

// Return the number of batches for an MPI configuration
uint64_t SimulationGeneralProperties::getNumberOfBatchesPerProcessor() const
{
  return d_number_of_batches_per_processor;
}

// Set the history simulation wall time
void SimulationGeneralProperties::setSimulationWallTime( const double wall_time )
{
  // Make sure that the wall time is valid
  TEST_FOR_EXCEPTION( wall_time <= 0.0,
                      std::runtime_error,
                      "The wall time must be greater that 0.0 seconds!" );
  
  d_wall_time = wall_time;
}

// Return the history simulation wall time
double SimulationGeneralProperties::getSimulationWallTime() const
{
  return d_wall_time;
}

// Set the angle cosine cutoff value for surface flux estimators
/*! \details When the angle cosine falls below the given cutoff an
 * approximation is used for the angle cosine to help bound the flux (avoids
 * a possible divide by zero).
 */
void SimulationGeneralProperties::setSurfaceFluxEstimatorAngleCosineCutoff(
                                                          const double cutoff )
{
  // Make sure the cutoff is valid
  TEST_FOR_EXCEPTION( cutoff <= 0.0,
                      std::runtime_error,
                      "The cutoff must be between 0.0 and 1.0!" );
  TEST_FOR_EXCEPTION( cutoff >= 1.0,
                      std::runtime_error,
                      "The cutoff must be between 0.0 and 1.0!" );

  d_surface_flux_estimator_angle_cosine_cutoff = cutoff;
}

// Return the angle cosine cutoff value for surface flux estimators
double SimulationGeneralProperties::getSurfaceFluxEstimatorAngleCosineCutoff() const
{
  return d_surface_flux_estimator_angle_cosine_cutoff;
}

// Turn on warnings (on by default)
void SimulationGeneralProperties::setWarningsOn()
{
  d_display_warnings = true;
}

// Turn off warnings (on by default)
void SimulationGeneralProperties::setWarningsOff()
{
  d_display_warnings = false;
}

// Return if warnings should be printed
bool SimulationGeneralProperties::displayWarnings() const
{
  return d_display_warnings;
}

// Set implicit capture mode to on (off by default)
void SimulationGeneralProperties::setImplicitCaptureModeOn()
{
  d_implicit_capture_mode_on = true;
}

// Set analogue capture mode to on (on by default)
void SimulationGeneralProperties::setAnalogueCaptureModeOn()
{
  d_implicit_capture_mode_on = false;
}

// Return if implicit capture mode has been set
bool SimulationGeneralProperties::isImplicitCaptureModeOn() const
{
  return d_implicit_capture_mode_on;
}

EXPLICIT_CLASS_SERIALIZE_INST( SimulationGeneralProperties );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SimulationGeneralProperties );

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationGeneralProperties.cpp
//---------------------------------------------------------------------------//
