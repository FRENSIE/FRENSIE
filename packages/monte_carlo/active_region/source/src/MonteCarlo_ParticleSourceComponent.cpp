//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourceComponent.cpp
//! \author Alex Robinson
//! \brief  The particle source component class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>
#include <functional>
#include <numeric>
#include <limits>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleSourceComponent.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
ParticleSourceComponent::ParticleSourceComponent()
  : d_id( std::numeric_limits<Id>::max() )
{ /* ... */ }

// Constructor
ParticleSourceComponent::ParticleSourceComponent(
                          const Id id,
                          const double selection_weight,
                          const std::shared_ptr<const Geometry::Model>& model )
  : ParticleSourceComponent( id, selection_weight, CellIdSet(), model )
{ /* ... */ }

// Constructor (with rejection cells)
/*! The standard particle source class
 * \details It is sometimes necessary to limit where a particle's spatial
 * coordinates are sampled, this class allows the user to specify rejection
 * cells in the model of interest. Any sampled particle states with spatial
 * coordinates that do not fall within one of the rejection cells will be
 * discarded and a new state will be sampled. If no rejection cells are
 * specified all sampled particle states will be used.
 */
ParticleSourceComponent::ParticleSourceComponent(
                          const Id id,
                          const double selection_weight,
                          const CellIdSet& rejection_cells,
                          const std::shared_ptr<const Geometry::Model>& model )
  : d_id( id ),
    d_selection_weight( selection_weight ),
    d_rejection_cells( rejection_cells ),
    d_model( model ),
    d_navigator( 1, model->createNavigator() ),
    d_start_cell_cache( 1, rejection_cells ),
    d_number_of_trials( 1, 0 ),
    d_number_of_samples( 1, 0 )
{
  // Make sure that the model pointer is valid
  testPrecondition( model.get() );

  // Make sure that the selection weight is valid
  TEST_FOR_EXCEPTION( selection_weight <= 0.0,
                      std::runtime_error,
                      "The selection weight must be greater than 0.0!" );

  // Make sure that the rejection cells exist
  for( auto rejection_cell : rejection_cells )
  {
    TEST_FOR_EXCEPTION( !model->doesCellExist( rejection_cell ),
                        std::runtime_error,
                        "Rejection cell " << rejection_cell << " does "
                        "not exist!" );
  }
}

// Enable thread support
/*! \details Only the master thread should call this method.
 */
void ParticleSourceComponent::enableThreadSupport( const size_t threads )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );
  // Make sure a valid number of threads has been requested
  testPrecondition( threads > 0 );

  // The navigators will be initialize just-in-time
  d_navigator.resize( threads );

  d_start_cell_cache.resize( threads, d_rejection_cells );

  d_number_of_trials.resize( threads, 0 );
  d_number_of_samples.resize( threads, 0 );

  // Enable thread support in derived class
  this->enableThreadSupportImpl( threads );
}

// Reset the sampling statistics
/*! \details Only the master thread should call this method. Only
 * the trial and sample counters will be reset (the start cell caches will
 * remain)
 */
void ParticleSourceComponent::resetData()
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  for( size_t i = 0; i < d_number_of_trials.size(); ++i )
  {
    d_number_of_trials[i] = 0;
    d_number_of_samples[i] = 0;
  }

  // Reset the derived class data
  this->resetDataImpl();
}

// Reduce the sampling statistics on the root process
/*! \details Only the master thread should call this method. After the
 * reduction operation is complete the
 * MonteCarlo::ParticleSourceComponent::resetData will be called on all
 * processes except for the root process.
 */
void ParticleSourceComponent::reduceData( const Utility::Communicator& comm,
                                          const int root_process )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );
  // Make sure that the root process is valid
  testPrecondition( root_process < comm.size() );

  // Only do the reduction if there is more than one process
  if( comm.size() > 1 )
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

    comm.barrier();

    // Reduce data in derived class
    this->reduceDataImpl( comm, root_process );

    // Reset the sampling data if not the root process
    if( comm.rank() != root_process )
      this->resetData();
  }
}

// Sample a particle state
/*! \details If MonteCarlo::ParticleSourceComponent::enableThreadSupport has
 * been called, this method is thread-safe.
 */
void ParticleSourceComponent::sampleParticleState(
                                             ParticleBank& bank,
                                             const unsigned long long history )
{
  // Make sure thread support has been set up correctly
  testPrecondition( Utility::OpenMPProperties::getThreadId() <
                    d_number_of_samples.size() );

  // Just-in-time initialization of the navigator
  if( !d_navigator[Utility::OpenMPProperties::getThreadId()].get() )
  {
    d_navigator[Utility::OpenMPProperties::getThreadId()] =
      d_model->createNavigator();
  }

  // Cache some data for this thread in case they need to be
  // accessed multiple times
  const Geometry::Navigator& navigator =
    *d_navigator[Utility::OpenMPProperties::getThreadId()];

  Counter& trial_counter =
    d_number_of_trials[Utility::OpenMPProperties::getThreadId()];

  Counter& sample_counter =
    d_number_of_samples[Utility::OpenMPProperties::getThreadId()];

  CellIdSet& start_cell_cache =
    d_start_cell_cache[Utility::OpenMPProperties::getThreadId()];

  // Determine the number of samples that must be made
  unsigned long long number_of_samples =
    this->getNumberOfParticleStateSamples( history );

  for( unsigned long long history_state_id = 0;
       history_state_id < number_of_samples;
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
      if( this->isSampledParticlePositionValid( *particle, navigator ) )
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
    particle->setSourceId( d_id );

    // Determine the cell that this particle has been born in
    if( valid_sample )
    {
      Geometry::Model::EntityId start_cell_id;

      try{
        start_cell_id =
          navigator.findCellContainingRay( Utility::reinterpretAsQuantity<Geometry::Navigator::Length>( particle->getPosition() ),
                                           particle->getDirection(),
                                           start_cell_cache );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Unable to embed the sampled particle "
                               << particle->getHistoryNumber() << " in "
                               "the correct location of model "
                               << d_model->getName() << "!" );

      // Embed the particle in the model
      particle->embedInModel( d_model, start_cell_id );
      particle->setSourceCell( start_cell_id );

      // Add the particle to the bank
      bank.push( particle );
    }
    else
    {
      FRENSIE_LOG_TAGGED_WARNING( "ParticleSourceComponent",
                                  "Unable to sample a valid particle state "
                                  "for history " << history << " (sub history "
                                  << history_state_id << ")!" );
    }

    // Increment the samples counter (regardless of good or bad sample)
    ++sample_counter;
  }
}

// Return the starting cells that have been cached
/*! \details Only the master thread should call this method.
 */
void ParticleSourceComponent::getStartingCells(
                                              CellIdSet& starting_cells ) const
{
  // Make sure that only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  this->mergeLocalStartCellCaches( starting_cells );
}

// Get the selection weight of this component
double ParticleSourceComponent::getSelectionWeight() const
{
  return d_selection_weight;
}

// Get the id of this source
auto ParticleSourceComponent::getId() const -> Id
{
  return d_id;
}

// Return the number of sampling trials
/*! \details Only the master thread should call this method.
 */
auto ParticleSourceComponent::getNumberOfTrials() const -> Counter
{
  // Make sure that only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  return this->reduceLocalTrialCounters();
}

// Return the number of samples that have been generated
/*! \details Only the master thread should call this method.
 */
auto ParticleSourceComponent::getNumberOfSamples() const -> Counter
{
  // Make sure that only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  return this->reduceLocalSampleCounters();
}

// Return the sampling efficiency from the source
/*! \details Only the master thread should call this method.
 */
double ParticleSourceComponent::getSamplingEfficiency() const
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  // Reduce the number of samples
  Counter total_samples = this->reduceLocalSampleCounters();

  // Reduce the number of trials
  Counter total_trials = this->reduceLocalTrialCounters();

  if( total_trials > 0ull )
    return static_cast<double>( total_samples )/total_trials;
  else
    return 1.0;
}

// Log a summary of the sampling statistics
void ParticleSourceComponent::logSummary() const
{
  std::ostringstream oss;

  this->printSummary( oss );

  FRENSIE_LOG_NOTIFICATION( oss.str() );
}

// Print a standard summary of the source data
void ParticleSourceComponent::printStandardSummary(
                                    const std::string& source_component_type,
                                    const std::string& particle_type_generated,
                                    const Counter trials,
                                    const Counter samples,
                                    const double efficiency,
                                    std::ostream& os ) const
{
  os << "Source Component " << d_id << " Summary..." << "\n"
     << "  Type: " << source_component_type << "\n"
     << "  Particle type generated: " << particle_type_generated << "\n"
     << "  Selection weight: " << d_selection_weight << "\n"
     << "  Number of (position) trials: " << trials << "\n"
     << "  Number of samples: " << samples << "\n"
     << "  Sampling efficiency: " << efficiency << std::endl;
}

// Print a standard summary of the source starting cells
void ParticleSourceComponent::printStandardStartingCellSummary(
                                               const CellIdSet& starting_cells,
                                               std::ostream& os ) const
{
  os << "  Starting Cells: ";

  for( auto starting_cell : starting_cells )
    os << starting_cell << " ";

  os << std::endl;
}

// Print a standard summary of the dimension data
void ParticleSourceComponent::printStandardDimensionSummary(
                                const std::string& dimension_distribution_type,
                                const PhaseSpaceDimension dimension,
                                const Counter trials,
                                const Counter samples,
                                const double efficiency,
                                std::ostream& os ) const
{
  os << "  " << dimension << " Sampling Summary: \n"
     << "    Distribution Type: " << dimension_distribution_type << "\n"
     << "    Number of trials: " << trials << "\n"
     << "    Number of samples: " << samples << "\n"
     << "    Sampling efficiency: " << efficiency << std::endl;
}

// Merge the starting cells on the root process
void ParticleSourceComponent::mergeStartingCells(
                                             const Utility::Communicator& comm,
                                             const int root_process )
{
  CellIdSet start_cell_cache;
  this->mergeLocalStartCellCaches( start_cell_cache );

  std::vector<CellIdSet> gathered_start_cell_caches;

  try{
    Utility::allGather( comm,
                        start_cell_cache,
                        gathered_start_cell_caches );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "unable to merge the starting cell caches!" );

  // Merge the local cache with the gathered caches
  for( size_t i = 0; i < gathered_start_cell_caches.size(); ++i )
  {
    start_cell_cache.insert( gathered_start_cell_caches[i].begin(),
                             gathered_start_cell_caches[i].end() );
  }

  // Distribute the merged cache to all threads
  for( size_t i = 0; i < d_start_cell_cache.size(); ++i )
    d_start_cell_cache[i] = start_cell_cache;
}

// Merge the local starting cells
void ParticleSourceComponent::mergeLocalStartCellCaches(
                                              CellIdSet& starting_cells ) const
{
  for( size_t i = 0; i < d_start_cell_cache.size(); ++i )
  {
    starting_cells.insert( d_start_cell_cache[i].begin(),
                           d_start_cell_cache[i].end() );
  }
}

// Reduce the sample counters on the root process
void ParticleSourceComponent::reduceSampleCounters(
                                             const Utility::Communicator& comm,
                                             const int root_process )
{
  ParticleSourceComponent::reduceCounters( d_number_of_samples,
                                           comm,
                                           root_process );
}

// Reduce the trial counters on the root process
void ParticleSourceComponent::reduceTrialCounters(
                                             const Utility::Communicator& comm,
                                             const int root_process )
{
  ParticleSourceComponent::reduceCounters( d_number_of_trials,
                                           comm,
                                           root_process );
}

// Reduce the counters on the root process
void ParticleSourceComponent::reduceCounters( std::vector<Counter>& counters,
                                              const Utility::Communicator& comm,
                                              const int root_process )
{
  try{
    if( comm.rank() != root_process )
      Utility::reduce( comm, counters, std::plus<Counter>(), root_process );
    else
      Utility::reduce( comm, std::vector<Counter>(counters), counters, std::plus<Counter>(), root_process );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "unable to reduce the counters!" );
}

// Reduce the local samples counters
auto ParticleSourceComponent::reduceLocalSampleCounters() const -> Counter
{
  return std::accumulate( d_number_of_samples.begin(),
                          d_number_of_samples.end(),
                          0ull );
}

// Reduce the local trials counters
auto ParticleSourceComponent::reduceLocalTrialCounters() const -> Counter
{
  return std::accumulate( d_number_of_trials.begin(),
                          d_number_of_trials.end(),
                          0ull );
}

// Check if the sampled particle position is valid
bool ParticleSourceComponent::isSampledParticlePositionValid(
                                   const ParticleState& particle,
                                   const Geometry::Navigator& navigator ) const
{
  // Check if the position is acceptable
  if( d_rejection_cells.size() > 0 )
  {
    for( auto rejection_cell : d_rejection_cells )
    {
      Geometry::PointLocation location =
        navigator.getPointLocation( Utility::reinterpretAsQuantity<Geometry::Navigator::Length>( particle.getPosition() ),
                                    particle.getDirection(),
                                    rejection_cell );

      if( location == Geometry::POINT_INSIDE_CELL )
        return true;
    }

    return false;
  }
  else
    return true;
}

EXPLICIT_CLASS_SAVE_LOAD_INST( ParticleSourceComponent );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourceComponent.cpp
//---------------------------------------------------------------------------//
