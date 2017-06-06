//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSource.cpp
//! \author Alex Robinson
//! \brief  Particle source definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>
#include <numeric>
#include <sstream>

// Boost Includes
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/set.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSource.hpp"
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Utility_CommHelpers.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
ParticleSource::ParticleSource()
  : d_model( new Geometry::InfiniteMediumModel( Geometry::ModuleTraits::invalid_internal_cell_handle ) ),
    d_navigator( d_model->createNavigatorAdvanced() ),
    d_start_cell_cache( 1 ),
    d_number_of_trials( 1, 0 ),
    d_number_of_samples( 1, 0 )
{ /* ... */ }

// Enable thread support
/*! \details Only the master thread should call this method.
 */
void ParticleSource::enableThreadSupport( const size_t threads )
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

  // Enable thread support in child class
  this->enableThreadSupportImpl( threads );
}

// Reset the source data
/*! \details Only the master thread should call this method. Since the 
 * envisioned use case for this method is to reset data on worker nodes
 * in parallel computations that will be used for statistical analyses, only
 * the trial and sample counters will be reset.
 */
void ParticleSource::resetData()
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  for( unsigned i = 0; i < d_number_of_trials.size(); ++i )
  {
    d_number_of_trials[i] = 0;
    d_number_of_samples[i] = 0;
  }

  // Reset the child class data
  this->resetDataImpl();
}

// Reduce the source data
/*! \details Only the master thread should call this method.
 */
void ParticleSource::reduceData(
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

    // Reduce data in child class
    this->reduceDataImpl( comm, root_process );
    
    // Reset the sampling data if not the root process
    if( comm->getRank() != root_process )
      this->resetData();
  }
}

// Merge the starting cells on the comm
void ParticleSource::mergeStartingCells(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process )
{
  std::set<Geometry::ModuleTraits::InternalCellHandle> starting_cells;

  this->mergeLocalStartCellCaches( starting_cells );

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
                               << status->getSourceRank() << "!" );

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
  unsigned long long packaged_data_size;
  
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
void ParticleSource::mergeStartingCellsWithPackagedData(
          std::set<Geometry::ModuleTraits::InternalCellHandle>& starting_cells,
          const std::string& packaged_data )
{
  std::set<Geometry::ModuleTraits::InternalCellHandle>
    unpacked_starting_cells = this->unpackStartingCellData( packaged_data );

  starting_cells.insert( unpacked_starting_cells.begin(),
                         unpacked_starting_cells.end() );
}

// Package the starting cell data
std::string ParticleSource::packageStartingCellData(
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
ParticleSource::unpackStartingCellData(
                                       const std::string& packaged_data ) const
{
  std::istringstream input_stream( packaged_data );
  boost::archive::binary_iarchive input_archive( input_stream );

  std::set<Geometry::ModuleTraits::InternalCellHandle> starting_cells;
  
  input_archive >> starting_cells;

  return starting_cells;
}

// Reduce the sample counters on the comm
void ParticleSource::reduceSampleCounters(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process )
{
  ParticleSource::reduceCounters( d_number_of_samples,
                                          comm,
                                          root_process );
                                         
}

// Reduce the trial counters on the comm
void ParticleSource::reduceTrialCounters(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process )
{
  ParticleSource::reduceCounters( d_number_of_trials,
                                          comm,
                                          root_process );
}

// Reduce the counters on the comm
void ParticleSource::reduceCounters(
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

// Export the source data
/*! \details Only the master thread should call this method.
 */
void ParticleSource::exportData(
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

  // Set the start cell cache
  std::set<Geometry::ModuleTraits::InternalCellHandle> starting_cells;

  this->getStartingCells( starting_cells );

  source_hdf5_file.setStartCellCache( this->getId(), starting_cells );

  // Export the child class data
  this->exportDataImpl( source_hdf5_file );
}

// Print a summary of the source data
/*! \details Only the master thread should call this method.
 */
void ParticleSource::printSummary( std::ostream& os ) const
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

  // Print the child class summary
  this->printSummaryImpl( os );
}

// Embed the source in the desired model
/*! \details The start cell cache and statistical data will be deleted. If any 
 * rejection cells have been set they will also be deleted.
 */
void ParticleSource::embedInModel(
                          const std::shared_ptr<const Geometry::Model>& model )
{
  // Make sure that the model is valid
  testPrecondition( model.get() );

  // Set the new model and navigator
  d_model = model;

  d_navigator.reset( model->createNavigatorAdvanced() );

  // Reset the start cell cache
  for( size_t i = 0; i < d_start_cell_cache.size(); ++i )
    d_start_cell_cache[i].clear();

  // Reset statistical data
  this->resetData();

  // Delete all rejection cells
  d_rejection_cells.clear();
}

// Set a rejection cell
/*! \details A rejection cell is used to determine if a sampled particle
 * position should be kept or rejected. If the sampled point is inside of
 * one of the rejection cells, it is kept. This function can be used to
 * set multiple rejection cells. Only the master thread should call this
 * method.
 */
void ParticleSource::setRejectionCell(
                        const Geometry::ModuleTraits::InternalCellHandle cell )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  // Make sure the cell is valid
  testPrecondition( d_model->doesCellExist( cell ) );

  d_rejection_cells.insert( cell );

  for( int i = 0; i < d_start_cell_cache.size(); ++i )
    d_start_cell_cache[i].insert( cell );
}

// Sample the particle state from the source
/*! \details If enableThreadSupport has been called, this method is
 * thread-safe.
 */
void ParticleSource::sampleParticleState(
                                             ParticleBank& bank,
					     const unsigned long long history )
{
  // Make sure thread support has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
                    d_number_of_samples.size() );

  // Cache some data for this thread in case they need to be
  // accessed multiple times
  ModuleTraits::InternalCounter& trial_counter =
    d_number_of_trials[Utility::GlobalOpenMPSession::getThreadId()];

  ModuleTraits::InternalCounter& sample_counter =
    d_number_of_samples[Utility::GlobalOpenMPSession::getThreadId()];

  std::set<Geometry::ModuleTraits::InternalCellHandle>& start_cell_cache =
    d_start_cell_cache[Utility::GlobalOpenMPSession::getThreadId()];

  // Determine the number of samples that must be made
  unsigned long long num_samples =
    this->getNumberOfParticleStateSamples( history );

  for( unsigned long long history_state_id = 0;
       history_state_id < num_samples;
       ++history_state_id )
  {
    // Initialize a particle state
    std::shared_ptr<ParticleState> particle =
      this->initializeParticleState( history, history_state_id );

    bool valid_sample = false;
    
    while( true )
    {
      // Increment the trial counter
      ++trial_counter;

      // Sample the particle state
      bool can_sample_again =
        this->sampleParticleStateImpl( particle, history_state_id );
      
      // Check if the particle position is inside of a rejection cell
      if( this->isSampledParticlePositionValid( *particle ) )
      {
        valid_sample = true;
        break;
      }
      else if( !can_sample_again )
      {
        valid_sample = false;
        break;
      }
    }

    // Set the particle source id
    particle->setSourceId( this->getId() );

    // Determine the cell that this particle has been born in
    if( valid_sample )
    {
      Geometry::ModuleTraits::InternalCellHandle start_cell;

      try{
        start_cell = d_navigator->findCellContainingRay(
                                                      particle->getPosition(),
                                                      particle->getDirection(),
                                                      start_cell_cache );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Unable to embed the sampled particle "
                               << particle->getHistoryNumber() << "in "
                               "the correct location of model "
                               << d_model->getName() << "!" );
      
      // Embed the particle in the model
      particle->embedInModel( d_model, start_cell );
      particle->setSourceCell( start_cell );
      
      // Add the particle to the bank
      bank.push( particle );
    }
    else
    {
      FRENSIE_LOG_WARNING( "Unable to sample a valid particle state for "
                           "history " << history << " (sub history "
                           << history_state_id << ")!" );
    }
      
    // Increment the samples counter (regardless of good or bad sample)
    ++sample_counter;
  }
}

// Return the number of sampling trials
/*! \details Only the master thread should call this method.
 */
auto ParticleSource::getNumberOfTrials() const
  -> ModuleTraits::InternalCounter
{
  // Make sure that only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  return this->reduceLocalTrialCounters();
}

// Return the number of samples
/*! \details Only the master thread should call this method.
 */
auto ParticleSource::getNumberOfSamples() const -> ModuleTraits::InternalCounter
{
  // Make sure that only the root process calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );

  return this->reduceLocalSampleCounters();
}

// Return the sampling efficiency from the source distribution
/*! \details Only the master thread should call this method.
 */
double ParticleSource::getSamplingEfficiency() const
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

// Check if the sampled particle position is valid
bool ParticleSource::isSampledParticlePositionValid(
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
        d_navigator->getPointLocation( particle.getPosition(),
                                       particle.getDirection(),
                                       *rejection_cell_it );

      if( location == Geometry::POINT_INSIDE_CELL )
      {
        valid_position = true;
        
        break;
      }

      ++rejection_cell_it;
    }
  }
  else
    valid_position = true;

  return valid_position;
}

// Return the starting cells that have been cached
void ParticleSource::getStartingCells( std::set<Geometry::ModuleTraits::InternalCellHandle>& starting_cells ) const
{
  this->mergeLocalStartCellCaches( starting_cells );
}

// Merge the local starting cells
void ParticleSource::mergeLocalStartCellCaches( std::set<Geometry::ModuleTraits::InternalCellHandle>& starting_cells ) const
{
  for( size_t i = 0; i < d_start_cell_cache.size(); ++i )
  {
    starting_cells.insert( d_start_cell_cache[i].begin(),
                           d_start_cell_cache[i].end() );
  }
}

// Reduce the local samples counters
auto ParticleSource::reduceLocalSampleCounters() const -> ModuleTraits::InternalCounter
{
  return std::accumulate( d_number_of_samples.begin(),
                          d_number_of_samples.end(),
                          0ull );
}

// Reduce the local trials counters
auto ParticleSource::reduceLocalTrialCounters() const -> ModuleTraits::InternalCounter
{
  return std::accumulate( d_number_of_trials.begin(),
                          d_number_of_trials.end(),
                          0ull );
}

// Initialze the start cell caches
void ParticleSource::initializeStartCellCaches()
{
  for( size_t i = 0; i < d_start_cell_cache.size(); ++i )
    d_start_cell_cache[i] = d_rejection_cells;
}

// Print a standard summary of the source data
void ParticleSource::printStandardSummary(
                                   const std::string& source_type,
                                   const ModuleTraits::InternalCounter trials,
                                   const ModuleTraits::InternalCounter samples,
                                   const double efficiency,
                                   std::ostream& os ) const
{
  os << "Source " << this->getId() << " Summary..." << "\n"
     << "\tType: " << source_type << "\n"
     << "\tNumber of (position) trials: " << trials << "\n"
     << "\tNumber of samples: " << samples << "\n"
     << "\tSampling efficiency: " << efficiency << std::endl;
}

// Print a standard summary of the source starting cells
void ParticleSource::printStandardStartingCellSummary(
           std::set<Geometry::ModuleTraits::InternalCellHandle> starting_cells,
           std::ostream& os ) const
{
  os << "\tSource " << this->getId() << " Starting Cells: ";

  std::set<Geometry::ModuleTraits::InternalCellHandle>::const_iterator cell_it,
    cell_end;
  cell_it = starting_cells.begin();
  cell_end = starting_cells.end();

  while( cell_it != cell_end )
  {
    os << *cell_it << " ";

    ++cell_it;
  }

  os << std::endl;
}

// Print a standard summary of the dimension data
void ParticleSource::printStandardDimensionSummary(
                                const std::string& dimension_distribution_type,
                                const PhaseSpaceDimension dimension,
                                const ModuleTraits::InternalCounter trials,
                                const ModuleTraits::InternalCounter samples,
                                const double efficiency,
                                std::ostream& os ) const
{
  os << "\t" << dimension << " Sampling Summary: \n"
     << "\t\tDistribution Type: " << dimension_distribution_type << "\n"
     << "\t\tNumber of trials: " << trials << "\n"
     << "\t\tNumber of samples: " << samples << "\n"
     << "\t\tSampling efficiency: " << efficiency << std::endl;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSource.cpp
//---------------------------------------------------------------------------//
