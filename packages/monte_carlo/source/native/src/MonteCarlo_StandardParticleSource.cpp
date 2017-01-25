//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleSource.cpp
//! \author Alex Robinson
//! \brief  Distributed source class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>
#include <numeric>

// FRENSIE Includes
#include "MonteCarlo_StandardParticleSource.hpp"
#include "MonteCarlo_PhaseSpacePoint.hpp"
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "MonteCarlo_ParticleStateFactory.hpp"
#include "Utility_CommHelpers.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
StandardParticleSource::StandardParticleSource(
   const unsigned id,
   const std::shared_ptr<const ParticleDistribution>& particle_distribution )
  : ParticleSource( id ),
    d_particle_distribution( particle_distribution ),
    d_critical_line_energies(),
    d_cell_rejection_functions(),
    d_number_of_trials( 1, 0ull ),
    d_number_of_samples( 1, 0ull ),
    d_dimension_trial_counters( 1 )
{ 
  // Make sure that the particle distribution is valid
  testPrecondition( particle_distribution.get() );
}

// Enable thread support
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::enableThreadSupport( const unsigned threads )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure a valid number of threads has been requested
  testPrecondition( threads > 0 );

  d_number_of_trials.resize( threads, 0ull );
  d_number_of_samples.resize( threads, 0ull );
  
  d_dimension_trial_counters.resize( threads );
  d_dimension_sample_counters.resize( threads );
}

// Reset the source data
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::resetData()
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  for( unsigned i = 0; i < d_number_of_trials.size(); ++i )
  {
    d_number_of_trials[i] = 0;
    d_number_of_samples[i] = 0;

    // Reset the dimension trial counters
    DimensionTrailCounterMap::iterator dimension_counters_it,
      dimension_counters_end;

    dimension_counters_it = d_dimension_trial_counters[i].begin();
    dimension_counters_end = d_dimension_trial_counters[i].end();

    while( dimension_counters_it != dimension_counters_end )
    {
      dimension_counters_it->second = 0;
      
      ++dimension_counters_it;
    }

    // Reset the dimension sample counters
    dimension_counters_it = d_dimension_sample_counters[i].begin();
    dimension_counters_it = d_dimension_sample_counters[i].end();

    while( dimension_counters_it != dimension_counters_end )
    {
      dimension_counters_it->second = 0;

      ++dimension_counters_it;
    }
  }
}

// Reduce the source data
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::reduceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure the communicator is valid
  testPrecondition( !comm.is_null() );
  // Make sure the root process is valid
  testPrecondition( root_process < comm->getSize() );

  // Only do the reduction if there is more than one process
  if( comm->getSize() > 1 )
  {
    try{
      Teuchos::reduceAll<TrialCounter>( *comm,
                                        Teuchos::REDUCE_SUM,
                                        d_number_of_trials.size(),
                                        d_number_of_trials.getRawPtr(),
                                        d_number_of_trials.getRawPtr() );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Error: unable to reduce the source trials!" );

    try{
      Teuchos::reduceAll<TrialCounter>( *comm,
                                        Teuchos::REDUCE_SUM,
                                        d_number_of_samples.size(),
                                        d_number_of_samples.getRawPtr(),
                                        d_number_of_samples.getRawPtr());
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Error: unable to reduce the source samples!" );

    // Reduce the dimension trial counters
    for( size_t i = 0; i < d_dimension_trial_counters.size(); ++i )
    {
      DimensionTrialCounter::const_iterator local_dimension_trial_counters_it,
        local_dimension_trial_counters_end;

      local_dimension_trial_counters_it =
        d_dimension_trial_counters[i].begin();
      
      local_dimension_trial_counters_end =
        d_dimension_trial_counters[i].end();

      while( local_dimension_trial_counters_it !=
             local_dimension_trial_counters_end )
      {
        try{
          Teuchos::reduceAll<DimensionTrialCounter>(
                                  *comm,
                                  Teuchos::REDUCE_SUM,
                                  1,
                                  &local_dimension_trial_counters_it->second,
                                  &local_dimension_trial_counters_it->second );
        }
        EXCEPTION_CATCH_RETHROW( std::runtime_error,
                                 "Error: unable to reduce the source samples "
                                 "for dimension "
                                 << local_dimension_trial_counters_it->first
                                 << "!" );
      }
    }
    
    // Reset the sampling data if not the root process
    if( comm->getRank() != root_process )
      this->resetData();
  }
}

// Export the source data
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::exportData(
             const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure the hdf5 file is valid
  testPrecondition( hdf5_file.get() != NULL );

  // Open the source hdf5 file
  SourceHDF5FileHandler source_hdf5_file( hdf5_file );

  // Set the number of trials
  TrialCounter trials = this->getNumberOfTrials();

  source_hdf5_file.setNumberOfSourceSamplingTrials( this->getId(), trials );

  source_hdf5_file.setNumberOfDefaultSourceSamplingTrials( trials );


  // Set the number of samples
  TrialCounter  samples = this->getNumberOfSamples();

  source_hdf5_file.setNumberOfSourceSamples( this->getId(), samples );

  source_hdf5_file.setNumberOfDefaultSourceSamples( samples );
}

// Print a summary of the source data
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::printSummary( std::ostream& os ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  this->printStandardSummary( "Standard Source",
                              this->getNumberOfTrials(),
                              this->getNumberOfSamples(),
                              this->getSamplingEfficiency(),
                              os );
}

// Sample the particle state from the source
/*! \details If enableThreadSupport has been called, this method is
 * thread-safe. The cell that contains the sampled particle state will
 * not be set and must be determined by the geometry module.
 */
void StandardParticleSource::sampleParticleState(
                                             ParticleBank& bank,
					     const unsigned long long history )
{
  // Make sure thread support has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
                    d_number_of_samples.size() );

  // Initialize the particle
  std::shared_ptr<ParticleState> particle;
    
  ParticleStateFactory::createState( particle, d_particle_type, history );

  // Initialize a source phase space point
  ParticleSourcePhaseSpacePoint phase_space_sample(
                                       d_spatial_coord_conversion_policy,
                                       d_directional_coord_conversion_policy );
  
  // Sample the particle state
  while( true )
  {
    // Increment the trials counter
    ++d_number_of_trials[Utility::GlobalOpenMPSession::getThreadId()];

    std::set<ParticleSourceDimensionType>::const_iterator
      independent_dimension = d_independent_dimensions.begin();

    // Sample independent dimensions values first. This will also trigger
    // the sampling of the dimensions that are dependent on the
    // sampled independent dimension.
    while( independent_dimension != d_independent_dimensions.end() )
    {
      d_dimensions.find( *independent_dimension )->second->sample(
                                                          phase_space_sample );

      ++independent_dimension;
    }

    // Convert the sampled phase space point to a particle state. This will
    // use the spatial and directional conversion policies
    phase_space_sample.setParticleState( *particle );

    // Check if the particle position satisfies the rejection cells.
    if( this->isSampledParticlePositionValid( *particle ) )
      break;
  }

  // Generate probe particles with the critical line energies
  this->generateProbeParticles( phase_space_sample, bank, history );

  // Increment the samples counter
  ++d_number_of_samples[Utility::GlobalOpenMPSession::getThreadId()];

  // Add the particle to the bank
  bank.push( *particle );
}

// Return the number of sampling trials
/*! \details Only the master thread should call this method.
 */
auto StandardParticleSource::getNumberOfTrials() const -> TrialCounter
{
  // Make sure that only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  return this->reduceLocalTrialCounters();
}

// Return the number of trials in the phase space dimension
/*! \details Only the master thread should call this method.
 */
auto StandardParticleSource::getNumberOfTrials(
           const PhaseSpaceDimension dimension ) const -> DimensionTrialCounter
{
  // Make sure that only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  return this->reduceLocalDimensionTrialCounters( dimension );
}

// Return the number of samples
/*! \details Only the master thread should call this method.
 */
auto StandardParticleSource::getNumberOfSamples() const -> TrialCounter
{
  // Make sure that only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  return this->reduceLocalSampleCounters();
}

// Return the number of dimension samples
/*! \details Only the master thread should call this method.
 */
auto StandardParticleSource::getNumberOfDimensionSamples(
           const PhaseSpaceDimension dimension ) const -> DimensionTrialCounter
{
  // Make sure that only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  return this->reduceLocalDimensionSampleCounters( dimension );
}

// Return the sampling efficiency from the source distribution
/*! \details Only the master thread should call this method.
 */
double StandardParticleSource::getSamplingEfficiency() const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  // Reduce the number of samples
  TrialCounter total_samples = this->reduceLocalSampleCounters();

  // Reduce the number of trials
  TrialCounter total_trials = this->reduceLocalTrialCounters();

  if( total_trials > 0ull )
    return static_cast<double>( total_samples )/total_trials;
  else
    return 1.0;
}

// Return the sampling efficiency in the phase space dimension
/*! \details Only the master thread should call this method
 */
double StandardParticleSource::getDimensionSamplingEfficiency(
                                    const PhaseSpaceDimension dimension ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  // Reduce the number of samples for the dimension
  DimensionTrialCounter total_samples =
    this->reduceLocalDimensionSampleCounters( dimension );

  // Reduce the number of trials for the dimension
  DimensionTrialCounter total_trials =
    this->reduceLocalDimensionTrialCounters( dimension );

  if( total_trials > 0 )
    return static_cast<double>( total_samples )/total_trials;
  else
    return 1.0;
}

// Check if the sampled particle position is valid
bool StandardParticleSource::isSampledParticlePositionValid(
                                          const ParticleState& particle ) const
{
  bool valid_position = false;
  
  // Check if the position is acceptable
  if( d_cell_rejection_functions.size() > 0 )
  {
    for( unsigned i = 0; i < d_cell_rejection_functions.size(); ++i )
    {
      Geometry::PointLocation location =
        d_cell_rejection_functions[i]( particle.ray() );

      if( location == Geometry::POINT_INSIDE_CELL )
      {
        valid_position = true;
        
        break;
      }
    }
  }
  else
    valid_position = true;

  return valid_position;
}

// Generate probe particles
/* Note: If a spatial dimension is dependent on the energy dimension then
 * it is possible for the position of a generated probe particle to be 
 * outside of a rejection cell even if the original sampled particle state
 * was inside of a rejection cell. The position of the generated probe 
 * particles will always be checked against the rejection cells. Rejected 
 * probe particles will not affect the sampling efficiency of the source.
 */
void StandardParticleSource::generateProbeParticles(
                       ParticleSourcePhaseSpacePoint& phase_space_sample,
                       ParticleBank& bank,
                       const unsigned long long history ) const
{
  // Get the energy dimension
  const ParticleSourceDimension& energy_dimension =
    *d_dimensions.find( ENERGY_PS_DIMENSION )->second;
  
  for( size_t i = 0; i < d_critical_line_energies.size(); ++i )
  {
    // Initialize the particle (probe)
    std::shared_ptr<ParticleState> particle;

    try{
      ParticleStateFactory::createState(
                                    particle, d_particle_type, history, true );
    }
    EXCEPTION_CATCH_RETHROW( std::logic_error,
                             "Error: The probe particles with the desired "
                             "critical line energies could not be created!" );

    // If the position is dependent on the energy, the position of the probe
    // must be checked
    while( true )
    {
      // Set the phase space sample energy to the critical line energy
      energy_dimension.setDimensionValueAndSample(
                             phase_space_sample, d_critical_line_energies[i] );

      phase_space_sample.setParticleState( *particle );

      if( this->isSampledParticlePositionValid( *particle ) )
        break;
    }

    // Add the particle to the bank
    bank.push( *particle );
  }  
}

// Reduce the local samples counters
auto StandardParticleSource::reduceLocalSamplesCounters() const -> TrialCounter
{
  return std::accumulate( d_number_of_samples.begin(),
                          d_number_of_samples.end(),
                          0ull );
}

// Reduce the local trials counters
auto StandardParticleSource::reduceLocalTrialsCounters() const -> TrialCounter
{
  return std::accumulate( d_number_of_trials.begin(),
                          d_number_of_trials.end(),
                          0ull );
}

// Reduce all of the local dimension samples counters
void StandardParticleSource::reduceAllLocalDimensionSampleCounters(
                    DimensionTrialCounterMap& dimension_sample_counters ) const
{
  StandardParticleSource::reduceAllDimensionCounters(
                                                 dimension_trial_counters,
                                                 d_dimension_sample_counters );
}

// Reduce all of the local dimension trials counters
void StandardParticleSource::reduceAllLocalDimensionTrialsCounters(
                     DimensionTrialCounterMap& dimension_trial_counters ) const
{
  StandardParticleSource::reduceAllDimensionCounters(
                                                  dimension_trial_counters,
                                                  d_dimension_trial_counters );
}

// Reduce the dimension counters
void StandardParticleSource::reduceAllDimensionCounters(
       DimensionTrailCounterMap& dimension_counters,
       const Teuchos::Array<DimensionTrialCounterMap>& all_dimension_counters )
{
  for( size_t i = 0; i < all_dimension_counters.size(); ++i )
  {
    DimensionTrailCounterMap::const_iterator dimension_counter_it,
      dimension_counter_end;
    
    dimension_counter_it = all_dimension_counters[i].begin();
    dimension_counter_end = all_dimension_counters[i].end();

    while( dimension_counter_it != dimension_counter_end )
    {
      // Initialize the dimension counter
      if( dimension_counters.find(dimension_counter_it->first) ==
          dimension_counters.end() )
        dimension_counters[dimension_counter_it->first] = 0;

      dimension_counters.find(dimension_counter_it->first)->second +=
        dimension_counter_it->second;
      
      ++dimension_counter_it;
    }
  }
}

// Reduce the local dimension sample counters
auto StandardParticleSource::reduceLocalDimensionSampleCounters(
           const PhaseSpaceDimension dimension ) const -> DimensionTrailCounter
{
  return StandardParticleSource::reduceDimensionCounters(
                                      dimension, d_dimension_sample_counters );
}

// Reduce the local dimension trial counters
auto StandardParticleSource::reduceLocalDimensionTrialCounters(
           const PhaseSpaceDimension dimension ) const -> DimensionTrialCounter
{
  return StandardParticleSource::reduceDimensionCounters(
                                       dimension, d_dimension_trial_counters );
}

// Reduce the dimension counter
auto StandardParticleSource::reduceDimensionCounters(
           const PhaseSpaceDimension dimension,
           const Teuchos::Array<DimensionTrialCounterMap>& dimension_counters )
  -> DimensionTrialCounter
{
  DimensionTrialCounter counter = 0;

  for( size_t i = 0; i < d_dimension_counters.size(); ++i )
  {
    if( d_dimension_counters[i].find( dimension ) !=
        d_dimension_counters[i].end() )
      counter += d_dimension_counters[i].find( dimension )->second;
  }

  return counter;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSource.cpp
//---------------------------------------------------------------------------//
