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
    d_default_particle_state_sampling_function(),
    d_number_of_trials( 1, 0ull ),
    d_number_of_samples( 1, 0ull ),
    d_dimensions_with_distributions(),
    d_dimension_trial_counters( 1 ),
    d_dimension_sample_counters( 1 ),
    d_particle_state_critical_line_energy_sampling_functions(),
    d_cell_rejection_functions()
{ 
  // Make sure that the particle distribution is valid
  testPrecondition( particle_distribution.get() );

  // Create the default particle state sampling function
  d_default_particle_state_sampling_function =
    std::bind<void>( &ParticleDistribution::sampleAndRecordTrials,
                     std::cref( *d_particle_distribution ),
                     std::placeholders::_1,
                     std::placeholders::_2 );

  // Initialize the set of dimensions with distributions set
  particle_distribution->getDimensionsWithDistributionsDefined(
                                             d_dimensions_with_distributions );

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
void StandardParticleSource::enableThreadSupport( const size_t threads )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure a valid number of threads has been requested
  testPrecondition( threads > 0 );

  d_number_of_trials.resize( threads, 0ull );
  d_number_of_samples.resize( threads, 0ull );
  
  d_dimension_trial_counters.resize( threads );
  d_dimension_sample_counters.resize( threads );

  // Initialize the dimension counters
  this->initializeDimensionTrialCounters();
  this->initializeDimensionSampleCounters();
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
  }

  this->initializeDimensionSampleCounters();
  this->initializeDimensionTrialCounters();
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
    // Reduce the trial counters
    try{
      this->reduceTrialCounters( comm, root_process );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "unable to reduce the source trial "
                             "counters!" );

    // Reduce the sample counters
    try{
      this->reduceSampleCounters( comm, root_process );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "unable to reduce the source sample "
                             "counters!" );

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
    
    // Reset the sampling data if not the root process
    if( comm->getRank() != root_process )
      this->resetData();
  }
}

// Reduce the sample counters on the comm
void StandardParticleSource::reduceSampleCounters(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process )
{
  StandardParticleSource::reduceCounters( d_number_of_samples,
                                          comm,
                                          root_process );
                                         
}

// Reduce the trial counters on the comm
void StandardParticleSource::reduceTrialCounters(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process )
{
  StandardParticleSource::reduceCounters( d_number_of_trials,
                                          comm,
                                          root_process );
}

// Reduce the counters on the comm
void StandardParticleSource::reduceCounters(
            Teuchos::Array<ModuleTraits::InternalCounter>& counters,
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process )
{
  try{
    Teuchos::reduceAll<ModuleTraits::InternalCounter>(
                                      *comm,
                                      Teuchos::REDUCE_SUM,
                                      counters.size(),
                                      counters.getRawPtr(),
                                      counters.getRawPtr() );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "unable to reduce the counters!" );
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
  ModuleTraits::InternalCounter trials = this->getNumberOfTrials();

  source_hdf5_file.setNumberOfSourceSamplingTrials( this->getId(), trials );

  // Set the number of samples
  ModuleTraits::InternalCounter samples = this->getNumberOfSamples();

  source_hdf5_file.setNumberOfSourceSamples( this->getId(), samples );

  // Set the number of trials in each dimension
  DimensionCounterMap dimension_counters;

  this->reduceAllLocalDimensionTrialCounters( dimension_counters );

  DimensionCounterMap::const_iterator dimension_counter_it =
    dimension_counters.begin();

  while( dimension_counter_it != dimension_counters.end() )
  {
    source_hdf5_file.setNumberOfSourceDimensionSamplingTrials(
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
    source_hdf5_file.setNumberOfSourceDimensionSamples(
                                                this->getId(),
                                                dimension_counter_it->first,
                                                dimension_counter_it->second );
    
    ++dimension_counter_it;
  }
}

// Print a summary of the source data
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::printSummary( std::ostream& os ) const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  // Print the source sampling statistics
  this->printStandardSummary( "Standard Source",
                              this->getNumberOfTrials(),
                              this->getNumberOfSamples(),
                              this->getSamplingEfficiency(),
                              os );

  // Print the sampling statistics for each source dimension
  ParticleDistribution::DimensionSet::const_iterator dimension_it =
    d_dimensions_with_distributions.begin();
  
  while( dimension_it != d_dimensions_with_distributions.end() )
  {
    this->printStandardDimensionSummary(
      d_particle_distribution->getDimensionDistributionTypeName(*dimension_it),
      *dimension_it,
      this->getNumberOfDimensionTrials( *dimension_it ),
      this->getNumberOfDimensionSamples( *dimension_it ),
      this->getDimensionSamplingEfficiency( *dimension_it ),
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
  // Make sure that the energy dimension has a distribution assigned
  testPrecondition( d_dimensions_with_distributions.count(ENERGY_DIMENSION) );
  
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
  
  // Sample the particle state
  this->sampleParticleStateBasicImpl(
                       d_default_particle_state_sampling_function, *particle );

  // Add the particle to the bank
  bank.push( *particle );

  // Generate probe particles with the critical line energies
  this->generateProbeParticles( bank, history );
}

// Generate probe particles
/* Note: Probe particles are currently sampled completely independently from
 * the parent particle. It is quite possible that there is a more efficient
 * way to generate probe particles but given that a particle distribution
 * can be defined in a very general way it is not immediately obvious how to
 * do this. 
 */
void StandardParticleSource::generateProbeParticles(
                                             ParticleBank& bank,
                                             const unsigned long long history )
{
  for( size_t i = 0; i < d_particle_state_critical_line_energy_sampling_functions.size(); ++i )
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
                             << Utility::get<0>(d_particle_state_critical_line_energy_sampling_functions[i]) <<
                             ") could not be created!" );
    
    this->sampleParticleStateBasicImpl(
            Utility::get<1>(d_particle_state_critical_line_energy_sampling_functions[i]),
            *particle,
            true );

    // Add the particle to the bank
    bank.push( *particle );
  }  
}

// Sample a particle state
void StandardParticleSource::sampleParticleStateBasicImpl(
                              ParticleStateSamplingFunction& sampling_function,
                              ParticleState& particle,
                              const bool ignore_energy_dimension_counters )
{
  // Cache some of the counters for this thread in case they need to be
  // accessed multiple times
  ModuleTraits::InternalCounter& trial_counter =
    d_number_of_trials[Utility::GlobalOpenMPSession::getThreadId()];

  DimensionCounterMap& dimension_trial_counters =
    d_dimension_trial_counters[Utility::GlobalOpenMPSession::getThreadId()];

  DimensionCounterMap& dimension_sample_counters =
    d_dimension_sample_counters[Utility::GlobalOpenMPSession::getThreadId()];

  // Sample the particle state
  while( true )
  {
    // Increment the trials counter
    ++trial_counter;

    // Sample the particle state and record dimension sampling statistics
    sampling_function( particle, dimension_trial_counters );

    // Increment the dimension sample counters
    this->incrementDimensionCounters( dimension_sample_counters,
                                      ignore_energy_dimension_counters );

    // Check if the particle position satisfies a rejection cell.
    if( this->isSampledParticlePositionValid( particle ) )
      break;
  }

  // Increment the samples counter
  ++d_number_of_samples[Utility::GlobalOpenMPSession::getThreadId()];
}
  
// Return the number of sampling trials
/*! \details Only the master thread should call this method.
 */
auto StandardParticleSource::getNumberOfTrials() const
  -> ModuleTraits::InternalCounter
{
  // Make sure that only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  return this->reduceLocalTrialCounters();
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

  if( d_dimensions_with_distributions.count( dimension ) )
    return this->reduceLocalDimensionTrialCounters( dimension );
  else
    return 0;
}
                  
// Return the number of samples
/*! \details Only the master thread should call this method.
 */
auto StandardParticleSource::getNumberOfSamples() const -> ModuleTraits::InternalCounter
{
  // Make sure that only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  return this->reduceLocalSampleCounters();
}

// Return the number of dimension samples
/*! \details Only the master thread should call this method.
 */
auto StandardParticleSource::getNumberOfDimensionSamples(
           const PhaseSpaceDimension dimension ) const -> ModuleTraits::InternalCounter
{
  // Make sure that only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  if( d_dimensions_with_distributions.count( dimension ) )
    return this->reduceLocalDimensionSampleCounters( dimension );
  else
    return 0;
}

// Return the sampling efficiency from the source distribution
/*! \details Only the master thread should call this method.
 */
double StandardParticleSource::getSamplingEfficiency() const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  // Reduce the number of samples
  ModuleTraits::InternalCounter total_samples = this->reduceLocalSampleCounters();

  // Reduce the number of trials
  ModuleTraits::InternalCounter total_trials = this->reduceLocalTrialCounters();

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

// Reduce the local samples counters
auto StandardParticleSource::reduceLocalSampleCounters() const -> ModuleTraits::InternalCounter
{
  return std::accumulate( d_number_of_samples.begin(),
                          d_number_of_samples.end(),
                          0ull );
}

// Reduce the local trials counters
auto StandardParticleSource::reduceLocalTrialCounters() const -> ModuleTraits::InternalCounter
{
  return std::accumulate( d_number_of_trials.begin(),
                          d_number_of_trials.end(),
                          0ull );
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
                                               d_dimensions_with_distributions,
                                               d_dimension_sample_counters );
}

// Initialize the dimension trial counters
void StandardParticleSource::initializeDimensionTrialCounters()
{
  StandardParticleSource::initializeDimensionCounters(
                                               d_dimensions_with_distributions,
                                               d_dimension_trial_counters );
}

// Initialize the dimension counters
void StandardParticleSource::initializeDimensionCounters(
                      const ParticleDistribution::DimensionSet& dimensions,
                      Teuchos::Array<DimensionCounterMap>& dimension_counters )
{
  ParticleDistribution::DimensionSet::const_iterator dimension_it =
    dimensions.begin();

  while( dimension_it != dimensions.end() )
  {
    for( size_t i = 0; i < dimension_counters.size(); ++i )
      dimension_counters[i][*dimension_it] = 0;

    ++dimension_it;
  }
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
