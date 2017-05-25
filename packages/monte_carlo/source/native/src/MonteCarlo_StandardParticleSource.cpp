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
#include <sstream>

// Boost Includes
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

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
    d_start_cell_cache( 1 ),
    d_number_of_trials( 1, 0ull ),
    d_number_of_samples( 1, 0ull ),
    d_dimension_trial_counters( 1 ),
    d_dimension_sample_counters( 1 ),
    d_particle_state_critical_line_energy_sampling_functions(),
    d_rejection_cells()
{ 
  // Make sure that the particle distribution is valid
  testPrecondition( particle_distribution.get() );

  // Create the default particle state sampling function
  d_default_particle_state_sampling_function =
    std::bind<void>( &ParticleDistribution::sampleAndRecordTrials,
                     std::cref( *d_particle_distribution ),
                     std::placeholders::_1,
                     std::placeholders::_2 );

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

  d_start_cell_cache.resize( threads );

  // Initialize the start cell caches
  this->initializeStartCellCaches();

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
    // Reduce the starting cell sets
    try{
      this->mergeStartingCells( comm, root_process );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "unable to merge starting cell caches!" );
    
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

// Merge the starting cells on the comm
void StandardParticleSource::mergeStartingCells(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process )
{
  std::set<Geometry::ModuleTraits::InternalCellHandle> starting_cells;

  this->mergeLocalStartingCellCaches( starting_cells );

  // Handle the root process
  if( comm->getRank() == root_process )
  {
    // Start at one since the root process does not need to report
    int nodes_reporting = 1;
    
    while( nodes_reporting < comm->getSize() )
    {
      Teuchos::RCP<Teuchos::CommStatus<unsigned long long> > status;

      // Probe for incoming sends to determine message size
      try{
        Utility::probe( *comm, status );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Root process (" << root_process <<
                               ") was unable to probe for starting cell data "
                               "sent by non-root processes!" );

      // Get the size of the incoming message
      std::string packaged_data;

      try{
        int message_size = Utility::getMessageSize<char>( *status );

        packaged_data.resize( message_size );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Root proces (" << root_process <<
                               ") was unable to determine the size of the "
                               "starting cell data sent from process "
                               << status->getSourceRank() << "!" );

      // Get the message
      try{
        Teuchos::receive( *comm,
                          status->getSourceRank(),
                          (unsigned long long)packaged_data.size(),
                          &packaged_data[0] );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Root process (" << root_process <<
                               ") was unable to receive starting cell data "
                               "from process "
                               << static->getSourceRank() << "!" );

      this->mergeStartingCellsWithPackagedData( starting_cells,
                                                packaged_data );

      ++nodes_reporting;
    }
  }
  // Handle non-root nodes
  else
  {
    std::string packaged_data =
      this->packageStartingCellData( starting_cells );

    try{
      Teuchos::send( *comm,
                     (unsigned long long)packaged_data.size(),
                     &packaged_data[0],
                     root_process );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Process " << comm->getRank() <<
                             " was unable to send starting cell data "
                             "to the root process ("
                             << root_process << ")!" );
  }

  // Wait for the root node to finish merging starting cell sets
  comm->barrier();

  // Broadcast the merged starting cell set to every node
  std::string packaged_data;
  size_t packaged_data_size;
  
  if( comm->getRank() == root_process )
  {
    packaged_data = this->packageStartingCellData( starting_cells );
    packaged_data_size = packaged_data.size();
  }

  Teuchos::broadcast( *comm, root_process, &packaged_data_size );

  if( comm->getRank() != root_process )
    packaged_data.resize( packaged_data_size );

  Teuchos::broadcast( *comm,
                      root_process,
                      packaged_data_size,
                      &packaged_data[0] );

  if( comm->getRank() != root_process )
    starting_cells = this->unpackStartingCellData( packaged_data );

  // Distribute the starting cells set to all threads
  for( size_t i = 0; i < d_start_cell_cache.size(); ++i )
    d_start_cell_cache[i] = starting_cells;
}

// Merge the starting cells with the packaged data
void StandardParticleSource::mergeStaringCellsWithPackagedData(
          std::set<Geometry::ModuleTraits::InternalCellHandle>& starting_cells,
          const std::string& packaged_data )
{
  std::set<Geometry::ModuleTraits::InternalCellHandle>
    unpacked_starting_cells = this->unpackStartingCellData( packaged_data );

  starting_cells.insert( unpacked_starting_cells.begin(),
                         unpacked_starting_cells.end() );
}

// Package the starting cell data
std::string StandardParticleSource::packageStartingCellData(
                    const std::set<Geometry::ModuleTraits::InternalCellHandle>&
                    starting_cells ) const
{
  std::ostringstream starting_cells_stream;
  
  boost::archive::binary_oarchive
    starting_cells_archive( starting_cells_stream );

  starting_cells_archive << starting_cells;

  return starting_cells_stream.str();
}

// Unpack the starting cell data
std::set<Geometry::ModuleTraits::InternalCellHandle>
StandardParticleSource::unpackStartingCellData(
                                       const std::string& packaged_data ) const
{
  std::istringstream input_stream( packaged_data );
  boost::archive::binary_iarchive input_archive( input_stream );

  std::set<Geometry::ModuleTraits::InternalCellHandle> starting_cells;
  
  input_archive >> starting_cells;

  return starting_cells;
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

  // Print the starting cell summary
  std::set<Geometry::ModuleTraits::InternalCellHandle> starting_cells;
  this->getStartingCells( starting_cells );
  
  this->printStandardStartingCellSummary( starting_cells, os );

  // Print the sampling statistics for each source dimension
  ParticleDistribution::DimensionSet::const_iterator dimension_it,
    dimension_end;
  dimension_it = d_dimension_trial_counters.front().begin();
  dimension_end = d_dimension_trial_counters.front().end();
  
  while( dimension_it != dimension_end )
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

  // Determine the cell that this particle has been born in
  Geometry::ModuleTraits::InternalCellHandle start_cell;

  try{
    start_cell = this->getGeometryNavigator().findCellContainingRay(
             particle.getPosition(),
             particle.getDirection(),
             d_start_cell_cache[Utility::GlobalOpenMPSession::getThreadId()] );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Unable to embed the sampled particle "
                           << particle.getHistoryNumber() << "in "
                           "the correct location of model "
                           << this->getModel().getName() << "!" );

  this->embedParticleInModel( particle, start_cell );

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

  if( d_dimension_trial_counters.front().count( dimension ) )
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

  if( d_dimension_trial_counters.front().count( dimension ) )
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
  if( d_rejection_cells.size() > 0 )
  {
    std::set<Geometry::ModuleTraits::InternalCellHandle>::const_iterator
      rejection_cell_it, rejection_cell_end;
    rejection_cell_it = d_rejection_cells.begin();
    rejection_cell_end = d_rejection_cells.end();

    while( rejection_cell_it != rejection_cell_end )
    {
      Geometry::PointLocation location =
        this->getGeometryNavigator().getPointLocation( particle.getPosition(),
                                                       particle.getDirection(),
                                                       *rejection_cell_it );

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

// Return the starting cells that have been cached
void StandardParticleSource::getStaringCells( std::set<Geometry::ModuleTraits::InternalCellHandle>& starting_cells ) const
{
  this->mergeLocalStartCellCaches( starting_cells );
}

// Merge the local starting cells
void StandardParticleSource::mergeLocalStartCellCaches( std::set<Geometry::ModuleTraits::InternalCellHandle>& starting_cells ) const
{
  for( size_t i = 0; i < d_start_cell_cache.size(); ++i )
  {
    starting_cells.insert( d_start_cell_cache[i].begin(),
                           d_start_cell_cache[i].end() );
  }
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

// Initialze the start cell caches
void StandardParticleSource::initializeStartCellCaches()
{
  for( size_t i = 0; i < d_start_cell_cache.size(); ++i )
    d_start_cell_cache[i] = d_rejection_cells;
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
