//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleTracker.cpp
//! \author Eli Moll
//! \brief  Particle tracking routine definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleTracker.hpp"
#include "MonteCarlo_ObserverParticleStateWrapper.hpp"
#include "MonteCarlo_ParticleType.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
ParticleTracker::ParticleTracker()
  : d_id( std::numeric_limits<Id>::max() )
{ /* ... */ }

// Constructor
ParticleTracker::ParticleTracker( const Id id,
                                  const uint64_t number_of_histories )
  : d_id( id ),
    d_histories_to_track(),
    d_partial_history_map( 1 ),
    d_history_number_map()
{
  // Make sure there are some particles being tracked
  testPrecondition( number_of_histories >= 0 );

  for( uint64_t i = 0; i < number_of_histories; ++i )
    d_histories_to_track.insert( i );
}

// Constructor
ParticleTracker::ParticleTracker( const Id id,
                                  const std::set<uint64_t>& history_numbers )
  : d_id( id ),
    d_histories_to_track( history_numbers ),
    d_partial_history_map( 1 ),
    d_history_number_map()
{
  // Make sure there are some particles being tracked
  testPrecondition( history_numbers.size() > 0 )
}

// Return the estimator id
auto ParticleTracker::getId() const -> Id
{
  return d_id;
}

// Return the histories that will be tracked
const std::set<uint64_t>& ParticleTracker::getTrackedHistories() const
{
  return d_histories_to_track;
}

// Add current history estimator contribution
void ParticleTracker::updateFromGlobalParticleSubtrackEndingEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] )
{
  // Check if we still need to be tracking particles
  if( d_histories_to_track.find( particle.getHistoryNumber() ) !=
      d_histories_to_track.end() )
  {
    unsigned thread_id = Utility::OpenMPProperties::getThreadId();

    PartialHistorySubmap& thread_partial_history_map =
      d_partial_history_map[thread_id];

    if( thread_partial_history_map.find( &particle ) ==
        thread_partial_history_map.end() )
    {
      ObserverParticleStateWrapper particle_wrapper( particle );

      const double track_length =
        std::sqrt( (end_point[0] - start_point[0])*(end_point[0] - start_point[0]) +
                   (end_point[1] - start_point[1])*(end_point[1] - start_point[1]) +
                   (end_point[2] - start_point[2])*(end_point[2] - start_point[2]) );

      particle_wrapper.calculateStateTimesUsingParticleTimeAsEndTime( track_length );
      
      thread_partial_history_map[&particle].push_back(
           std::make_tuple( std::array<double,3>( {start_point[0],
                                                   start_point[1],
                                                   start_point[2]} ),
                            std::array<double,3>( {particle.getXDirection(),
                                                   particle.getYDirection(),
                                                   particle.getZDirection()} ),
                            particle.getEnergy(),
                            particle_wrapper.getStartTime(),
                            particle.getWeight(),
                            particle.getCollisionNumber() ) );
    }
    
    thread_partial_history_map[&particle].push_back(
           std::make_tuple( std::array<double,3>( {end_point[0],
                                                   end_point[1],
                                                   end_point[2]} ),
                            std::array<double,3>( {particle.getXDirection(),
                                                   particle.getYDirection(),
                                                   particle.getZDirection()} ),
                            particle.getEnergy(),
                            particle.getTime(),
                            particle.getWeight(),
                            particle.getCollisionNumber() ) );
  }
}

// Update the observer
void ParticleTracker::updateFromGlobalParticleGoneEvent(
                                                const ParticleState& particle )
{
  unsigned thread_id = Utility::OpenMPProperties::getThreadId();

  if( d_partial_history_map[thread_id].find( &particle ) !=
      d_partial_history_map[thread_id].end() )
  {
    #pragma omp critical
    {
      IndividualParticleSubmap& particle_data = 
        d_history_number_map[particle.getHistoryNumber()][particle.getParticleType()][particle.getGenerationNumber()];

      // Get the unique id of this particle state
      unsigned i = 0u;

      while( particle_data.count( i ) )
        ++i;

      // Add the particle state data
      particle_data[i] = d_partial_history_map[thread_id][&particle];

      // Remove the particle state data from the partial data map
      d_partial_history_map[thread_id].erase( &particle );
    }
  }
}

// Take a snapshot
void ParticleTracker::takeSnapshot(
                              const uint64_t num_histories_since_last_snapshot,
                              const double time_since_last_snapshot )
{ /* ... */ }

// Reset data
void ParticleTracker::resetData()
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  for( size_t i = 0; i < d_partial_history_map.size(); ++i )
    d_partial_history_map[i].clear();

  // Clear the history number map
  d_history_number_map.clear();
}

// Enable support for multiple threads
void ParticleTracker::enableThreadSupport( const unsigned num_threads )
{
  testPrecondition( num_threads > 0 );
  
  d_partial_history_map.resize( num_threads );
}

// Has Uncommited History Contribution
bool ParticleTracker::hasUncommittedHistoryContribution() const
{
  return false;
}

// Commit History Contribution
void ParticleTracker::commitHistoryContribution()
{ /* ... */ }

// Reduce data
void ParticleTracker::reduceData( const Utility::Communicator& comm,
                                  const int root_process )
{
  // Make sure only the root process calls this function
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );
  // Make sure the root process is valid
  testPrecondition( root_process < comm.size() );

  // Only do the reduction if there is more than one process
  if( comm.size() > 1 )
  {
    // Handle the master
    if( comm.rank() == root_process )
    {
      std::vector<OverallHistoryMap> gathered_data( comm.size() );
      std::vector<Utility::Communicator::Request> gathered_requests;

      for( size_t i = 0; i < comm.size(); ++i )
      {
        if( i != root_process )
        {
          gathered_requests.push_back( Utility::ireceive( comm,
                                                          i,
                                                          0,
                                                          gathered_data[i] ) );
        }
      }

      std::vector<Utility::Communicator::Status>
        gathered_statuses( gathered_requests.size() );

      Utility::wait( gathered_requests, gathered_statuses );

      for( size_t i = 0; i < gathered_data.size(); ++i )
      {
        OverallHistoryMap::const_iterator gathered_data_it =
          gathered_data[i].begin();
        
        while( gathered_data_it != gathered_data[i].end() )
        {
          d_history_number_map[gathered_data_it->first] =
            gathered_data_it->second;

          ++gathered_data_it;
        }
      }
    }
    else
    {
      Utility::send( comm, root_process, 0, d_history_number_map );

      // Reset the non-root process data
      this->resetData();
    }
  }

  comm.barrier();
}

// Print a summary of the data
void ParticleTracker::printSummary( std::ostream& os ) const
{
  os << "Particle tracker " << this->getId() << ": ";

  std::vector<uint64_t> tracked_histories( d_histories_to_track.begin(),
                                           d_histories_to_track.end() );

  std::sort( tracked_histories.begin(), tracked_histories.end() );

  uint64_t range_start_history = tracked_histories.front();
  uint64_t range_end_history = range_start_history;
  
  for( size_t i = 1; i < tracked_histories.size(); ++i )
  {
    if( tracked_histories[i] == range_end_history + 1 )
      ++range_end_history;
    else
    {
      if( range_start_history == range_end_history )
        os << range_start_history;
      else
        os << range_start_history << "-" << range_end_history;
    }

    if( i < tracked_histories.size() - 1 )
      os << ", ";
  }
  
  os << std::endl;
}

// Get the data map
void ParticleTracker::getHistoryData( OverallHistoryMap& history_map ) const
{
  history_map = d_history_number_map;
}

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ParticleTracker );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ParticleTracker );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleTracker.cpp
//---------------------------------------------------------------------------//
