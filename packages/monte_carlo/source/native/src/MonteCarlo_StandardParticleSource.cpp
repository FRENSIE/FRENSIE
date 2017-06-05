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
      const std::shared_ptr<const ParticleDistribution>& particle_distribution,
      const ParticleType particle_type )
  : d_particle_distribution( particle_distribution ),
    d_particle_type( particle_type ),
    d_dimension_trial_counters( 1 ),
    d_dimension_sample_counters( 1 ),
    d_particle_state_critical_line_energy_sampling_functions()
{ 
  // Make sure that the particle distribution is valid
  testPrecondition( particle_distribution.get() );

  // Initialize the dimension trial counters
  this->initializeDimensionTrialCounters();

  // Initialize the dimension sample counters
  this->initializeDimensionSampleCounters();
}

// Get the source id
ModuleTraits::InternalROIHandle StandardParticleSource::getId() const
{
  return d_particle_distribution->getId();
}

// Get the particle type
ParticleType StandardParticleSource::getParticleType() const
{
  return d_particle_type;
}
  
// Enable thread support
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::enableThreadSupportImpl( const size_t threads )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure a valid number of threads has been requested
  testPrecondition( threads > 0 );

  d_dimension_trial_counters.resize( threads );
  d_dimension_sample_counters.resize( threads );

  // Initialize the dimension counters
  this->initializeDimensionTrialCounters();
  this->initializeDimensionSampleCounters();
}

// Reset the source data
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::resetDataImpl()
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  this->initializeDimensionSampleCounters();
  this->initializeDimensionTrialCounters();
}

// Reduce the source data
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::reduceDataImpl(
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
    // Reduce the dimension trial counters
    try{
      this->reduceDimensionTrialCounters( comm, root_process );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "unable to reduce the dimension trial "
                             "counters!" );

    // Reduce the dimension sample counters
    try{
      this->reduceDimensionTrialCounters( comm, root_process );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "unable to reduce the dimension sample "
                             "counters!" );
  }
}

// Reduce the dimension trial counters on the comm
void StandardParticleSource::reduceDimensionTrialCounters(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process )
{
  StandardParticleSource::reduceDimensionCounters( d_dimension_trial_counters,
                                                   comm,
                                                   root_process );
}

// Reduce the dimension sample counters on the comm
void StandardParticleSource::reduceDimensionSampleCounters(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process )
{
  StandardParticleSource::reduceDimensionCounters( d_dimension_sample_counters,
                                                   comm,
                                                   root_process );
}

// Reduce the dimension counters on the comm
void StandardParticleSource::reduceDimensionCounters(
            Teuchos::Array<DimensionCounterMap>& dimension_counters,
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process )
{
  for( size_t i = 0; i < dimension_counters.size(); ++i )
  {
    DimensionCounterMap::iterator local_dimension_counters_it,
      local_dimension_counters_end;

    local_dimension_counters_it = dimension_counters[i].begin();
    local_dimension_counters_end = dimension_counters[i].end();
    
    while( local_dimension_counters_it != local_dimension_counters_end )
    {
      try{
        Teuchos::reduceAll<ModuleTraits::InternalCounter>(
                                        *comm,
                                        Teuchos::REDUCE_SUM,
                                        1,
                                        &local_dimension_counters_it->second,
                                        &local_dimension_counters_it->second );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "unable to reduce the source counters "
                               "for dimension "
                               << local_dimension_counters_it->first
                               << "!" );
      comm->barrier();
    }
  }
}

// Export the source data
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::exportDataImpl(
                                       SourceHDF5FileHandler& hdf5_file ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  // Set the number of trials in each dimension
  DimensionCounterMap dimension_counters;

  this->reduceAllLocalDimensionTrialCounters( dimension_counters );

  DimensionCounterMap::const_iterator dimension_counter_it =
    dimension_counters.begin();

  while( dimension_counter_it != dimension_counters.end() )
  {
    hdf5_file.setNumberOfSourceDimensionSamplingTrials(
                                                this->getId(),
                                                dimension_counter_it->first,
                                                dimension_counter_it->second );
    
    ++dimension_counter_it;
  }

  // set the number of samples in each dimension
  dimension_counters.clear();

  this->reduceAllLocalDimensionSampleCounters( dimension_counters );

  dimension_counter_it = dimension_counters.begin();

  while( dimension_counter_it != dimension_counters.end() )
  {
    hdf5_file.setNumberOfSourceDimensionSamples(
                                                this->getId(),
                                                dimension_counter_it->first,
                                                dimension_counter_it->second );
    
    ++dimension_counter_it;
  }
}

// Print a summary of the source data
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::printSummaryImpl( std::ostream& os ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  // Print the sampling statistics for each source dimension
  DimensionCounterMap::const_iterator dimension_it, dimension_end;
  dimension_it = d_dimension_trial_counters.front().begin();
  dimension_end = d_dimension_trial_counters.front().end();
  
  while( dimension_it != dimension_end )
  {
    this->printStandardDimensionSummary(
      d_particle_distribution->getDimensionDistributionTypeName( dimension_it->first ),
      dimension_it->first,
      this->getNumberOfDimensionTrials( dimension_it->first ),
      this->getNumberOfDimensionSamples( dimension_it->first ),
      this->getDimensionSamplingEfficiency( dimension_it->first ),
      os );
    
    ++dimension_it;
  }
}

// Set the critical line energies
void StandardParticleSource::setCriticalLineEnergies(
                const Teuchos::ArrayRCP<const double>& critical_line_energies )
{
  // Make sure that at least one critical line energy has been specified
  testPrecondition( critical_line_energies.size() > 0 );
  
  // Resize the particle state critical line energy sampling functions array
  d_particle_state_critical_line_energy_sampling_functions.resize(
                                               critical_line_energies.size() );

  // Create the sampling function for each critical line energy
  for( size_t i = 0; i < critical_line_energies.size(); ++i )
  {
    Utility::get<0>(d_particle_state_critical_line_energy_sampling_functions[i]) =
      critical_line_energies[i];

    Utility::get<1>( d_particle_state_critical_line_energy_sampling_functions[i]) =
      std::bind<void>( &ParticleDistribution::sampleWithDimensionValueAndRecordTrials,
                       std::cref( *d_particle_distribution ),
                       std::placeholders::_1,
                       std::placeholders::_2,
                       ENERGY_DIMENSION,
                       critical_line_energies[i] );
  }
}

// Return the number of particle states that will be sampled for the 
// given history number
/*! \details The number of particle states that must be sampled for each
 * history is the the number of critical energies plus one (a probe particle
 * must be generated for each critical energy).
 */
unsigned long long StandardParticleSource::getNumberOfParticleStateSamples(
                                       const unsigned long long history ) const
{
  return d_particle_state_critical_line_energy_sampling_functions.size() + 1;
}

// Initialize a particle state
std::shared_ptr<ParticleState> StandardParticleSource::initializeParticleState(
                                    const unsigned long long history,
                                    const unsigned long long history_state_id )
{
  // Make sure that the history state id is valid
  testPrecondition( history_state_id <
                    this->getNumberOfParticleStateSamples( history ) );
  
  if( history_state_id == 0 )
  {
    // Initialize the particle
    std::shared_ptr<ParticleState> particle;
    
    ParticleStateFactory::createState( particle, d_particle_type, history );

    return particle;
  }
  else if( history_state_id > 0 )
  {
    // Initialize the particle (probe)
    std::shared_ptr<ParticleState> particle;

    try{
      ParticleStateFactory::createState(
                                    particle, d_particle_type, history, true );
    }
    EXCEPTION_CATCH_RETHROW( std::logic_error,
                             "A probe particle with the desired "
                             "critical line energy ("
                             << Utility::get<0>(d_particle_state_critical_line_energy_sampling_functions[history_state_id]) <<
                             ") could not be created!" );
  }
}

// Sample a particle state from the source
/*! \details Probe particles are currently sampled completely independently 
 * from the parent particle. It is quite possible that there is a more 
 * efficient way to generate probe particles but given that a particle 
 * distribution can be defined in a very general way it is not obvious how to 
 * do this. 
 */
bool StandardParticleSource::sampleParticleStateImpl(
                                const std::shared_ptr<ParticleState>& particle,
                                const unsigned long long history_state_id )
{
  // Make sure that the history state id is valid
  testPrecondition( history_state_id <
                    this->getNumberOfParticleStateSamples(history_state_id) );

  if( history_state_id > 0 )
  {
    // Sample a probe particle
    Utility::get<1>(d_particle_state_critical_line_energy_sampling_functions[history_state_id])( *particle, d_dimension_trial_counters[Utility::GlobalOpenMPSession::getThreadId()] );

    // Increment the dimension sample counters
    this->incrementDimensionCounters(
      d_dimension_sample_counters[Utility::GlobalOpenMPSession::getThreadId()],
      true );
  }
  else if( history_state_id == 0 )
  {
    // Sample a standard particle
    d_particle_distribution->sampleAndRecordTrials( *particle, d_dimension_trial_counters[Utility::GlobalOpenMPSession::getThreadId()] );

    // Increment the dimension sample counters
    this->incrementDimensionCounters(
      d_dimension_sample_counters[Utility::GlobalOpenMPSession::getThreadId()],
      false );
  }

  return true;
}
                  
// Return the number of trials in the phase space dimension
/*! \details Only the master thread should call this method.
 */
auto StandardParticleSource::getNumberOfDimensionTrials(
                                    const PhaseSpaceDimension dimension ) const
  -> ModuleTraits::InternalCounter
{
  // Make sure that only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  if( d_dimension_trial_counters.front().count( dimension ) )
    return this->reduceLocalDimensionTrialCounters( dimension );
  else
    return 0;
}

// Return the number of dimension samples
/*! \details Only the master thread should call this method.
 */
auto StandardParticleSource::getNumberOfDimensionSamples(
           const PhaseSpaceDimension dimension ) const -> ModuleTraits::InternalCounter
{
  // Make sure that only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  if( d_dimension_trial_counters.front().count( dimension ) )
    return this->reduceLocalDimensionSampleCounters( dimension );
  else
    return 0;
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
  ModuleTraits::InternalCounter total_samples =
    this->reduceLocalDimensionSampleCounters( dimension );

  // Reduce the number of trials for the dimension
  ModuleTraits::InternalCounter total_trials =
    this->reduceLocalDimensionTrialCounters( dimension );

  if( total_trials > 0 )
    return static_cast<double>( total_samples )/total_trials;
  else
    return 1.0;
}

// Reduce all of the local dimension samples counters
void StandardParticleSource::reduceAllLocalDimensionSampleCounters(
                         DimensionCounterMap& dimension_sample_counters ) const
{
  StandardParticleSource::reduceAllDimensionCounters(
                                                 dimension_sample_counters,
                                                 d_dimension_sample_counters );
}

// Reduce all of the local dimension trials counters
void StandardParticleSource::reduceAllLocalDimensionTrialCounters(
                          DimensionCounterMap& dimension_trial_counters ) const
{
  StandardParticleSource::reduceAllDimensionCounters(
                                                  dimension_trial_counters,
                                                  d_dimension_trial_counters );
}

// Reduce the dimension counters
void StandardParticleSource::reduceAllDimensionCounters(
       DimensionCounterMap& dimension_counters,
       const Teuchos::Array<DimensionCounterMap>& all_dimension_counters )
{
  for( size_t i = 0; i < all_dimension_counters.size(); ++i )
  {
    DimensionCounterMap::const_iterator dimension_counter_it,
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
                                    const PhaseSpaceDimension dimension ) const
  -> ModuleTraits::InternalCounter
{
  return StandardParticleSource::reduceDimensionCounters(
                                      dimension, d_dimension_sample_counters );
}

// Reduce the local dimension trial counters
auto StandardParticleSource::reduceLocalDimensionTrialCounters(
                                    const PhaseSpaceDimension dimension ) const
  -> ModuleTraits::InternalCounter
{
  return StandardParticleSource::reduceDimensionCounters(
                                       dimension, d_dimension_trial_counters );
}
                  
// Reduce the dimension counter
auto StandardParticleSource::reduceDimensionCounters(
           const PhaseSpaceDimension dimension,
           const Teuchos::Array<DimensionCounterMap>& dimension_counters )
  -> ModuleTraits::InternalCounter
{
  ModuleTraits::InternalCounter counter = 0;

  for( size_t i = 0; i < dimension_counters.size(); ++i )
  {
    if( dimension_counters[i].find( dimension ) !=
        dimension_counters[i].end() )
      counter += dimension_counters[i].find( dimension )->second;
  }

  return counter;
}

// Initialize the dimension sample counters
void StandardParticleSource::initializeDimensionSampleCounters()
{
  StandardParticleSource::initializeDimensionCounters(
                                                 d_dimension_sample_counters );
}

// Initialize the dimension trial counters
void StandardParticleSource::initializeDimensionTrialCounters()
{
  StandardParticleSource::initializeDimensionCounters(
                                                  d_dimension_trial_counters );
}

// Initialize the dimension counters
void StandardParticleSource::initializeDimensionCounters(
                      Teuchos::Array<DimensionCounterMap>& dimension_counters )
{
  for( size_t i = 0; i < dimension_counters.size(); ++i )
  d_particle_distribution->initializeDimensionCounters( dimension_counters[i] );
}

// Increment the dimension counters
void StandardParticleSource::incrementDimensionCounters(
                                       DimensionCounterMap& dimension_counters,
                                       const bool ignore_energy_dimension )
{
  DimensionCounterMap::iterator dimension_counter_it =
    dimension_counters.begin();

  while( dimension_counter_it != dimension_counters.end() )
  {
    // Always increment a dimension counter if it is not associated with the
    // energy dimension
    if( dimension_counter_it->first != ENERGY_DIMENSION )
      ++dimension_counter_it->second;
    
    // Only increment the energy dimension counter if requested
    else
    {
      if( !ignore_energy_dimension )
        ++dimension_counter_it->second;
    }
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSource.cpp
//---------------------------------------------------------------------------//
