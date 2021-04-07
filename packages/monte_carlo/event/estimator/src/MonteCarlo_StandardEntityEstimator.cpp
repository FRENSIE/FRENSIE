//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardEntityEstimator.cpp
//! \author Alex Robinson
//! \brief  The standard entity estimator class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_StandardEntityEstimator.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
StandardEntityEstimator::StandardEntityEstimator()
{ /* ... */ }

// Constructor with no entities (for mesh estimator)
StandardEntityEstimator::StandardEntityEstimator(
                                       const Id id,
                                       const double multiplier )
  : EntityEstimator( id, multiplier ),
    d_total_estimator_moments( 1 ),
    d_entity_total_estimator_moments_map(),
    d_total_estimator_moment_snapshots( 1 ),
    d_entity_total_estimator_moment_snapshots_map(),
    d_total_estimator_histograms( 1 ),
    d_entity_total_estimator_histograms_map(),
    d_update_tracker( 1 )
{ /* ... */ }

// Check if total data is available
bool StandardEntityEstimator::isTotalDataAvailable() const
{
  return true;
}

// Get the total data first moments
Utility::ArrayView<const double> StandardEntityEstimator::getTotalDataFirstMoments() const
{
  return Utility::ArrayView<const double>(
                     Utility::getCurrentScores<1>( d_total_estimator_moments ),
                     d_total_estimator_moments.size() );
}

// Get the total data second moments
Utility::ArrayView<const double> StandardEntityEstimator::getTotalDataSecondMoments() const
{
  return Utility::ArrayView<const double>(
                     Utility::getCurrentScores<2>( d_total_estimator_moments ),
                     d_total_estimator_moments.size() );
}

// Get the total data third moments
Utility::ArrayView<const double> StandardEntityEstimator::getTotalDataThirdMoments() const
{
  return Utility::ArrayView<const double>(
                     Utility::getCurrentScores<3>( d_total_estimator_moments ),
                     d_total_estimator_moments.size() );
}

// Get the total data fourth moments
Utility::ArrayView<const double> StandardEntityEstimator::getTotalDataFourthMoments() const
{
  return Utility::ArrayView<const double>(
                     Utility::getCurrentScores<4>( d_total_estimator_moments ),
                     d_total_estimator_moments.size() );
}

// Get the total data first moments for an entity
Utility::ArrayView<const double> StandardEntityEstimator::getEntityTotalDataFirstMoments( const size_t entity_id ) const
{
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );

  const Estimator::FourEstimatorMomentsCollection& entity_collection =
    d_entity_total_estimator_moments_map.find( entity_id )->second;

  return Utility::ArrayView<const double>(
                             Utility::getCurrentScores<1>( entity_collection ),
                             entity_collection.size() );
}

// Get the total data second moments for an entity
Utility::ArrayView<const double> StandardEntityEstimator::getEntityTotalDataSecondMoments( const size_t entity_id ) const
{
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );

  const Estimator::FourEstimatorMomentsCollection& entity_collection =
    d_entity_total_estimator_moments_map.find( entity_id )->second;

  return Utility::ArrayView<const double>(
                             Utility::getCurrentScores<2>( entity_collection ),
                             entity_collection.size() );
}

// Get the total data third moments for an entity
Utility::ArrayView<const double> StandardEntityEstimator::getEntityTotalDataThirdMoments( const size_t entity_id ) const
{
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );

  const Estimator::FourEstimatorMomentsCollection& entity_collection =
    d_entity_total_estimator_moments_map.find( entity_id )->second;

  return Utility::ArrayView<const double>(
                             Utility::getCurrentScores<3>( entity_collection ),
                             entity_collection.size() );
}

// Get the total data fourth moments for an entity
Utility::ArrayView<const double> StandardEntityEstimator::getEntityTotalDataFourthMoments( const size_t entity_id ) const
{
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );

  const Estimator::FourEstimatorMomentsCollection& entity_collection =
    d_entity_total_estimator_moments_map.find( entity_id )->second;

  return Utility::ArrayView<const double>(
                             Utility::getCurrentScores<4>( entity_collection ),
                             entity_collection.size() );
}

// Take a snapshot (of the moments)
void StandardEntityEstimator::takeSnapshot( const uint64_t num_histories_since_last_snapshot,
                                            const double time_since_last_snapshot )
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );
  
  d_total_estimator_moment_snapshots.takeSnapshot( num_histories_since_last_snapshot,
                                                   time_since_last_snapshot,
                                                   d_total_estimator_moments );

  for( auto&& entity_data : d_entity_total_estimator_moment_snapshots_map )
  {
    entity_data.second.takeSnapshot( num_histories_since_last_snapshot,
                                     time_since_last_snapshot,
                                     d_entity_total_estimator_moments_map[entity_data.first] );
  }

  EntityEstimator::takeSnapshot( num_histories_since_last_snapshot,
                                 time_since_last_snapshot );
}

// Get the entity total moment snapshot history values
void StandardEntityEstimator::getEntityTotalMomentSnapshotHistoryValues(
                                  const EntityId entity_id,
                                  std::vector<uint64_t>& history_values ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );

  const std::list<uint64_t>& raw_history_values =
    d_entity_total_estimator_moment_snapshots_map.find( entity_id )->second.getSnapshotIndices();

  history_values.assign( raw_history_values.begin(),
                         raw_history_values.end() );
}

//  Get the entity total moment snapshot sampling times
void StandardEntityEstimator::getEntityTotalMomentSnapshotSamplingTimes(
                                    const EntityId entity_id,
                                    std::vector<double>& sampling_times ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );

  const std::list<double>& raw_sampling_time_values =
    d_entity_total_estimator_moment_snapshots_map.find( entity_id )->second.getSnapshotSamplingTimes();

  sampling_times.assign( raw_sampling_time_values.begin(),
                         raw_sampling_time_values.end() );
}
  
// Get the total data first moment snapshots for an entity bin index
void StandardEntityEstimator::getEntityTotalFirstMomentSnapshots(
                                          const EntityId entity_id,
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );

  // Make sure that the response function index is valid
  TEST_FOR_EXCEPTION( response_function_index >= this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The response function index must be less than "
                      << this->getNumberOfResponseFunctions() << "!" );

  const std::list<double>& moment_snapshots =
    Utility::getScoreSnapshots<1>(
       d_entity_total_estimator_moment_snapshots_map.find( entity_id )->second,
       response_function_index );

  moments.assign( moment_snapshots.begin(), moment_snapshots.end() );
}

// Get the total data second moment snapshots for an entity bin index
void StandardEntityEstimator::getEntityTotalSecondMomentSnapshots(
                                          const EntityId entity_id,
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );

  // Make sure that the response function index is valid
  TEST_FOR_EXCEPTION( response_function_index >= this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The response function index must be less than "
                      << this->getNumberOfResponseFunctions() << "!" );

  const std::list<double>& moment_snapshots =
    Utility::getScoreSnapshots<2>(
       d_entity_total_estimator_moment_snapshots_map.find( entity_id )->second,
       response_function_index );

  moments.assign( moment_snapshots.begin(), moment_snapshots.end() );
}

// Get the total data third moment snapshots for an entity bin index
void StandardEntityEstimator::getEntityTotalThirdMomentSnapshots(
                                          const EntityId entity_id,
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );

  // Make sure that the response function index is valid
  TEST_FOR_EXCEPTION( response_function_index >= this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The response function index must be less than "
                      << this->getNumberOfResponseFunctions() << "!" );

  const std::list<double>& moment_snapshots =
    Utility::getScoreSnapshots<3>(
       d_entity_total_estimator_moment_snapshots_map.find( entity_id )->second,
       response_function_index );

  moments.assign( moment_snapshots.begin(), moment_snapshots.end() );
}

// Get the total data fourth moment snapshots for an entity bin index
void StandardEntityEstimator::getEntityTotalFourthMomentSnapshots(
                                          const EntityId entity_id,
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );

  // Make sure that the response function index is valid
  TEST_FOR_EXCEPTION( response_function_index >= this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The response function index must be less than "
                      << this->getNumberOfResponseFunctions() << "!" );

  const std::list<double>& moment_snapshots =
    Utility::getScoreSnapshots<4>(
       d_entity_total_estimator_moment_snapshots_map.find( entity_id )->second,
       response_function_index );

  moments.assign( moment_snapshots.begin(), moment_snapshots.end() );
}

// Get the total moment snapshot history values
void StandardEntityEstimator::getTotalMomentSnapshotHistoryValues(
                                  std::vector<uint64_t>& history_values ) const
{
  const std::list<uint64_t>& raw_history_values =
    d_total_estimator_moment_snapshots.getSnapshotIndices();

  history_values.assign( raw_history_values.begin(),
                         raw_history_values.end() );
}

// Get the total moment snapshot sampling times
void StandardEntityEstimator::getTotalMomentSnapshotSamplingTimes(
                                    std::vector<double>& sampling_times ) const
{
  const std::list<double>& raw_sampling_time_values =
    d_total_estimator_moment_snapshots.getSnapshotSamplingTimes();

  sampling_times.assign( raw_sampling_time_values.begin(),
                         raw_sampling_time_values.end() );
}

// Get the total data first moment snapshots for a total bin index
void StandardEntityEstimator::getTotalFirstMomentSnapshots(
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const
{
  // Make sure that the response function index is valid
  TEST_FOR_EXCEPTION( response_function_index >= this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The response function index must be less than "
                      << this->getNumberOfResponseFunctions() << "!" );

  const std::list<double>& moment_snapshots =
    Utility::getScoreSnapshots<1>( d_total_estimator_moment_snapshots,
                                   response_function_index );

  moments.assign( moment_snapshots.begin(), moment_snapshots.end() );
}

// Get the total data second moment snapshots for a total bin index
void StandardEntityEstimator::getTotalSecondMomentSnapshots(
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const
{
  // Make sure that the response function index is valid
  TEST_FOR_EXCEPTION( response_function_index >= this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The response function index must be less than "
                      << this->getNumberOfResponseFunctions() << "!" );

  const std::list<double>& moment_snapshots =
    Utility::getScoreSnapshots<2>( d_total_estimator_moment_snapshots,
                                   response_function_index );

  moments.assign( moment_snapshots.begin(), moment_snapshots.end() );
}

// Get the total data third moment snapshots for a total bin index
void StandardEntityEstimator::getTotalThirdMomentSnapshots(
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const
{
  // Make sure that the response function index is valid
  TEST_FOR_EXCEPTION( response_function_index >= this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The response function index must be less than "
                      << this->getNumberOfResponseFunctions() << "!" );

  const std::list<double>& moment_snapshots =
    Utility::getScoreSnapshots<3>( d_total_estimator_moment_snapshots,
                                   response_function_index );

  moments.assign( moment_snapshots.begin(), moment_snapshots.end() );
}

// Get the total data fourth moment snapshots for a total bin index
void StandardEntityEstimator::getTotalFourthMomentSnapshots(
                                          const size_t response_function_index,
                                          std::vector<double>& moments ) const
{
  // Make sure that the response function index is valid
  TEST_FOR_EXCEPTION( response_function_index >= this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The response function index must be less than "
                      << this->getNumberOfResponseFunctions() << "!" );

  const std::list<double>& moment_snapshots =
    Utility::getScoreSnapshots<4>( d_total_estimator_moment_snapshots,
                                   response_function_index );

  moments.assign( moment_snapshots.begin(), moment_snapshots.end() );
}

// Get the entity total sample moment histogram
void StandardEntityEstimator::getEntityTotalSampleMomentHistogram(
                      const EntityId entity_id,
                      const size_t response_function_index,
                      Utility::SampleMomentHistogram<double>& histogram ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );

  // Make sure that the response function index is valid
  TEST_FOR_EXCEPTION( response_function_index >= this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The response function index must be less than "
                      << this->getNumberOfResponseFunctions() << "!" );

  histogram = d_entity_total_estimator_histograms_map.find( entity_id )->second[response_function_index];
}

// Get the total sample moment histogram
void StandardEntityEstimator::getTotalSampleMomentHistogram(
                      const size_t response_function_index,
                      Utility::SampleMomentHistogram<double>& histogram ) const
{
  // Make sure that the response function index is valid
  TEST_FOR_EXCEPTION( response_function_index >= this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The response function index must be less than "
                      << this->getNumberOfResponseFunctions() << "!" );

  histogram = d_total_estimator_histograms[response_function_index];
}

// Commit the contribution from the current history to the estimator
/*! \details This function must only be called within an omp critical block
 * if multiple threads are being used. Failure to do this may result in
 * race conditions.
 */
void StandardEntityEstimator::commitHistoryContribution()
{
  // Thread id
  size_t thread_id = Utility::OpenMPProperties::getThreadId();

  // Number of bins per response function
  size_t num_bins = this->getNumberOfBins();

  // Number of response functions
  size_t num_response_funcs = this->getNumberOfResponseFunctions();

  // The entity totals
  std::vector<double> entity_totals( num_response_funcs, 0.0 );

  // The totals over all entities
  std::vector<double> totals( num_response_funcs, 0.0 );

  // The bin totals over all entities
  BinContributionMap bin_totals;

  // Get the entities with updated data
  typename SerialUpdateTracker::const_iterator entity, end_entity;

  this->getEntityIteratorFromUpdateTracker( thread_id, entity, end_entity );

  while( entity != end_entity )
  {
    // Process each updated bin
    BinContributionMap::const_iterator bin_data, end_bin_data;

    this->getBinIteratorFromUpdateTrackerIterator( thread_id,
                                                   entity,
                                                   bin_data,
                                                   end_bin_data );

    while( bin_data != end_bin_data )
    {
      size_t response_func_index =
	this->calculateResponseFunctionIndex( bin_data->first );

      const double bin_contribution = bin_data->second;

      entity_totals[response_func_index] += bin_contribution;

      totals[response_func_index] += bin_contribution;

      if( bin_totals.find( bin_data->first ) != bin_totals.end() )
	bin_totals[bin_data->first] += bin_contribution;
      else
	bin_totals[bin_data->first] = bin_contribution;

      this->commitHistoryContributionToBinOfEntity( entity->first,
						    bin_data->first,
						    bin_contribution );

      ++bin_data;
    }

    // Commit the entity totals
    for( size_t i = 0; i < num_response_funcs; ++i )
    {
      this->commitHistoryContributionToTotalOfEntity( entity->first,
                                                      i,
                                                      entity_totals[i] );

      // Reset the entity totals
      entity_totals[i] = 0.0;
    }

    ++entity;
  }

  // Commit the totals over all entities
  for( size_t i = 0; i < num_response_funcs; ++i )
    this->commitHistoryContributionToTotalOfEstimator( i, totals[i] );

  // Commit the bin totals over all entities
  BinContributionMap::const_iterator bin_data, end_bin_data;
  bin_data = bin_totals.begin();
  end_bin_data = bin_totals.end();

  while( bin_data != end_bin_data )
  {
    this->commitHistoryContributionToBinOfTotal( bin_data->first,
						 bin_data->second );
    ++bin_data;
  }

  // Reset the update tracker
  this->resetUpdateTracker( thread_id );

  // Unset the uncommitted history contribution flag
  this->unsetHasUncommittedHistoryContribution( thread_id );
}

// Enable support for multiple threads
void StandardEntityEstimator::enableThreadSupport( const unsigned num_threads )
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  EntityEstimator::enableThreadSupport( num_threads );

  // Add thread support to update tracker
  d_update_tracker.resize( num_threads );
}

// Reset the estimator data
void StandardEntityEstimator::resetData()
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  EntityEstimator::resetData();

  // Reset the total moments
  d_total_estimator_moments.reset();

  // Reset the entity total moments
  for( auto&& entity_data : d_entity_total_estimator_moments_map )
    entity_data.second.reset();

  // Reset the total moment snapshots
  d_total_estimator_moment_snapshots.reset();

  // Reset the entity total moment snapshots
  for( auto&& entity_data : d_entity_total_estimator_moment_snapshots_map )
    entity_data.second.reset();

  // Reset the total moment histograms
  for( auto&& histogram : d_total_estimator_histograms )
    histogram.reset();

  // Reset the entity total moment histograms
  for( auto&& entity_data : d_entity_total_estimator_histograms_map )
  {
    for( auto&& histogram : entity_data.second )
      histogram.reset();
  }

  // Reset the update tracker
  for( size_t i = 0; i < d_update_tracker.size(); ++i )
  {
    d_update_tracker[i].clear();

    this->unsetHasUncommittedHistoryContribution( i );
  }
}

// Reduce estimator data on all processes and collect on the root process
void StandardEntityEstimator::reduceData( const Utility::Communicator& comm,
                                          const int root_process )
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );
  // Make sure the root process is valid
  testPrecondition( root_process < comm.size() );

  // Only do the reduction if there is more than one process
  if( comm.size() > 1 )
  {
    // Reduce the entity data
    try{
      this->reduceEntityCollectionMaps( comm, root_process, d_entity_total_estimator_moments_map );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Unable to perform mpi reduction in "
                             "standard entity estimator " << this->getId() <<
                             " for entity total data!" );

    comm.barrier();

    // Reduce the total data
    try{
      this->reduceCollection( comm, root_process, d_total_estimator_moments );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Unable to perform mpi reduction in "
                             "standard entity estimator " << this->getId() <<
                             " for total data!" );

    // Reduce the entity snapshot data
    try{
      this->reduceEntitySnapshotMaps( comm, root_process, d_entity_total_estimator_moment_snapshots_map );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Unable to perform mpi reduction in "
                             "standard entity estimator " << this->getId() <<
                             " for entity total snapshot data!" );

    // Reduce the total snapshot data
    try{
      this->reduceSnapshots( comm, root_process, d_total_estimator_moment_snapshots );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Unable to perform mpi reduction in "
                             "standard entity estimator " << this->getId() <<
                             " for total snapshot data!" );

    // Reduce the entity histogram data
    try{
      this->reduceEntityHistogramMaps( comm, root_process, d_entity_total_estimator_histograms_map );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Unable to perform mpi reduction in "
                             "standard entity estimator " << this->getId() <<
                             " for entity total histograms!" );

    // Reduce the total histogram data
    try{
      this->reduceHistogramArrays( comm, root_process, d_total_estimator_histograms );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Unable to perform mpi reduction in "
                             "standard entity estimator " << this->getId() <<
                             " for total histograms!" );
  }

  // Reduce the bin data
  EntityEstimator::reduceData( comm, root_process );
}

// Assign entities
void StandardEntityEstimator::assignEntities(
                  const EntityEstimator::EntityNormConstMap& entity_norm_data )
{
  // Make sure there is at least one entity
  testPrecondition( entity_norm_data.size() > 0 );

  EntityEstimator::assignEntities( entity_norm_data );

  // Reset the estimator data
  d_total_estimator_moments.clear();
  d_entity_total_estimator_moments_map.clear();
  d_total_estimator_moment_snapshots.clear();
  d_entity_total_estimator_moment_snapshots_map.clear();
  d_total_estimator_histograms.clear();
  d_entity_total_estimator_histograms_map.clear();

  // Initialize the entity data
  for( auto&& entity_data : entity_norm_data )
  {
    d_entity_total_estimator_moments_map[entity_data.first];
    d_entity_total_estimator_moment_snapshots_map[entity_data.first];
    d_entity_total_estimator_histograms_map[entity_data.first];
  }      

  // Resize the entity total estimator momens map collections
  this->resizeEntityTotalEstimatorMomentsMapCollections();

  // Resize the total estimator moments array
  d_total_estimator_moments.resize( this->getNumberOfResponseFunctions() );
  d_total_estimator_moment_snapshots.resize( this->getNumberOfResponseFunctions() );

  {
    Utility::SampleMomentHistogram<double>
      default_histogram( this->getSampleMomentHistogramBins() );

    d_total_estimator_histograms.resize( this->getNumberOfResponseFunctions(),
                                         default_histogram );
  }
}

// Set the response functions
void StandardEntityEstimator::assignResponseFunction(
             const std::shared_ptr<const ParticleResponse>& response_function )
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  EntityEstimator::assignResponseFunction( response_function );

  // Resize the entity total estimator momens map collections
  this->resizeEntityTotalEstimatorMomentsMapCollections();

  // Resize the total estimator moments array
  d_total_estimator_moments.resize( this->getNumberOfResponseFunctions() );
  d_total_estimator_moment_snapshots.resize( this->getNumberOfResponseFunctions() );

  {
    Utility::SampleMomentHistogram<double>
      default_histogram( this->getSampleMomentHistogramBins() );
    
    d_total_estimator_histograms.resize( this->getNumberOfResponseFunctions(),
                                         default_histogram );
  }
}

// Assign the history score pdf bins
void StandardEntityEstimator::assignSampleMomentHistogramBins( const std::shared_ptr<const std::vector<double> >& bins )
{
  EntityEstimator::assignSampleMomentHistogramBins( bins );

  for( auto&& histogram : d_total_estimator_histograms )
    histogram.setBinBoundaries( bins );

  for( auto&& entity_data : d_entity_total_estimator_histograms_map )
  {
    for( auto&& histogram : entity_data.second )
      histogram.setBinBoundaries( bins );
  }
}

// Print the estimator data
void StandardEntityEstimator::printImplementation(
					 std::ostream& os,
					 const std::string& entity_type ) const
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  EntityEstimator::printImplementation( os, entity_type );

  // Print the entity total estimator data
  for( auto&& entity_id : d_entity_total_estimator_moments_map )
  {
    os << entity_type << " " << entity_id.first << " Total Data:\n";
    os << "--------\n";

    this->printEstimatorTotalData(
		              os,
                              entity_id.second,
		              this->getEntityNormConstant( entity_id.first ) );

    os << "\n";
  }

  // Print the total estimator data
  os << "All " << entity_type << "s Total Data:\n";
  os << "--------\n";

  this->printEstimatorTotalData( os,
				 d_total_estimator_moments,
				 this->getTotalNormConstant() );

  os << std::flush;
}

// Add estimator contribution from a point of the current history
/*! \details The contribution should incorporate the particle weight (and
 * possibly other multiplier(s) ) but not the response function values.
 */
void StandardEntityEstimator::addPartialHistoryPointContribution(
		   const EntityId entity_id,
		   const ObserverParticleStateWrapper& particle_state_wrapper,
                   const double contribution )
{
  // Make sure the thread id is valid
  testPrecondition( Utility::OpenMPProperties::getThreadId() <
		    d_update_tracker.size() );
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  // Make sure that the particle type is assigned
  testPrecondition( this->isParticleTypeAssigned( particle_state_wrapper.getParticleState().getParticleType() ) );

  const size_t thread_id = Utility::OpenMPProperties::getThreadId();

  // Only add the contribution if the particle state is in the phase space
  if( this->isPointInObserverPhaseSpace( particle_state_wrapper ) )
  {
    typename ObserverPhaseSpaceDimensionDiscretization::BinIndexArray
      bin_indices;

    for( size_t r = 0; r < this->getNumberOfResponseFunctions(); ++r )
    {
      this->calculateBinIndicesOfPoint( particle_state_wrapper,
                                        r,
                                        bin_indices );

      const double processed_contribution = contribution*
        this->evaluateResponseFunction(
                                particle_state_wrapper.getParticleState(), r );

      for( size_t i = 0; i < bin_indices.size(); ++i )
      {
        this->addInfoToUpdateTracker( thread_id,
                                      entity_id,
                                      bin_indices[i],
                                      processed_contribution );
      }

      bin_indices.clear();
    }
  }

  // Indicate that there is an uncommitted history contribution
  if( !this->hasUncommittedHistoryContribution( thread_id ) )
    this->setHasUncommittedHistoryContribution( thread_id );
}

// Add estimator contribution from a range of the current history
/*! \details The contribution should incorporate the particle weight (and
 * possibly other multiplier(s) ) but not the response function values.
 */
void StandardEntityEstimator::addPartialHistoryRangeContribution(
                   const EntityId entity_id,
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   const double contribution )
{
  // Make sure the thread id is valid
  testPrecondition( Utility::OpenMPProperties::getThreadId() <
		    d_update_tracker.size() );
  // Make sure the entity is assigned to the estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  // Make sure that the particle type is assigned
  testPrecondition( this->isParticleTypeAssigned( particle_state_wrapper.getParticleState().getParticleType() ) );

  const size_t thread_id = Utility::OpenMPProperties::getThreadId();

  // Only add the contribution if the particle state is in the phase space
  if( this->doesRangeIntersectObserverPhaseSpace( particle_state_wrapper ) )
  {
    typename ObserverPhaseSpaceDimensionDiscretization::BinIndexWeightPairArray
      bin_indices_and_weights;

    this->calculateBinIndicesAndWeightsOfRange( particle_state_wrapper,
                                                0,
                                                bin_indices_and_weights );

    for( size_t r = 0; r < this->getNumberOfResponseFunctions(); ++r )
    {
      const size_t bin_index_shift = r*this->getNumberOfBins();

      for( size_t i = 0; i < bin_indices_and_weights.size(); ++i )
      {
        const double processed_contribution = contribution*
          Utility::get<1>( bin_indices_and_weights[i] )*
          this->evaluateResponseFunction(
                                particle_state_wrapper.getParticleState(), r );

        const size_t complete_bin_index =
          Utility::get<0>( bin_indices_and_weights[i] ) + bin_index_shift;

        this->addInfoToUpdateTracker( thread_id,
                                      entity_id,
                                      complete_bin_index,
                                      processed_contribution );
      }
    }
  }

  // Indicate that there is an uncommitted history contribution
  if( !this->hasUncommittedHistoryContribution( thread_id ) )
    this->setHasUncommittedHistoryContribution( thread_id );
}

// Get the total estimator data
/*! \details This function breaks encapsulation and is therefore not ideal.
 * It is needed by mesh estimators for exporting data in .h5m and .vtk formats.
 */
const Estimator::FourEstimatorMomentsCollection&
StandardEntityEstimator::getTotalData() const
{
  return d_total_estimator_moments;
}

// Get the total data for an entity
/*! \details This function breaks encapsulation and is therefore not ideal.
 * It is needed by mesh estimators for exporting data in .h5m and .vtk formats.
 */
const Estimator::FourEstimatorMomentsCollection&
StandardEntityEstimator::getEntityTotalData( const EntityId entity_id ) const
{
  // Make sure the entity is valid
  testPrecondition( d_entity_total_estimator_moments_map.find( entity_id ) !=
		    d_entity_total_estimator_moments_map.end() );

  return d_entity_total_estimator_moments_map.find( entity_id )->second;
}

// Resize the entity total estimator moments map arrays
void StandardEntityEstimator::resizeEntityTotalEstimatorMomentsMapCollections()
{
  size_t size = this->getNumberOfResponseFunctions();
  
  for( auto&& entity_data : d_entity_total_estimator_moments_map )
    entity_data.second.resize( size );

  for( auto&& entity_data : d_entity_total_estimator_moment_snapshots_map )
    entity_data.second.resize( size );

  Utility::SampleMomentHistogram<double>
    default_histogram( this->getSampleMomentHistogramBins() );

  for( auto&& entity_data : d_entity_total_estimator_histograms_map )
    entity_data.second.resize( size, default_histogram );
}

// Commit hist. contr. to the total for a response function of an entity
void StandardEntityEstimator::commitHistoryContributionToTotalOfEntity(
					const EntityId entity_id,
					const size_t response_function_index,
					const double contribution )
{
  // Make sure the entity is assigned to this estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  // Make sure the response function index is valid
  testPrecondition( response_function_index <
		    this->getNumberOfResponseFunctions() );
  // Make sure the contribution is valid
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( contribution ) );

  Estimator::FourEstimatorMomentsCollection&
    entity_total_estimator_moments_collection =
    d_entity_total_estimator_moments_map.find( entity_id )->second;

  // Update the moments
  #pragma omp critical
  {
    entity_total_estimator_moments_collection.addRawScore( response_function_index, contribution );
  }

  this->addHistoryContributionToEntityBinHistogram( entity_id, response_function_index, contribution );
}

// Add contribution to entity bin histogram
void StandardEntityEstimator::addHistoryContributionToEntityBinHistogram(
                                          const EntityId entity_id,
                                          const size_t response_function_index,
                                          const double contribution )
{
  // Make sure the entity is assigned to this estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  // Make sure the response function index is valid
  testPrecondition( response_function_index <
		    this->getNumberOfResponseFunctions() );
  // Make sure the contribution is valid
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( contribution ) );

  Utility::SampleMomentHistogram<double>& histogram =
    d_entity_total_estimator_histograms_map.find( entity_id )->second[response_function_index];

  // Update the histogram
  #pragma omp critical
  {
    histogram.addRawScore( contribution );
  }
}  

// Commit history contr. to the total for a response function of an estimator
void StandardEntityEstimator::commitHistoryContributionToTotalOfEstimator(
					const size_t response_function_index,
					const double contribution )
{
  // Make sure the response function index is valid
  testPrecondition( response_function_index <
		    this->getNumberOfResponseFunctions() );
  // Make sure the contribution is valid
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( contribution ) );

  // Update the moments
  #pragma omp critical
  {
    d_total_estimator_moments.addRawScore( response_function_index, contribution );
  }

  this->addHistoryContributionToTotalBinHistogram( response_function_index,
                                                   contribution );
}

// Add contribution to total bin histogram
void StandardEntityEstimator::addHistoryContributionToTotalBinHistogram(
                                          const size_t response_function_index,
                                          const double contribution )
{
  // Make sure the response function index is valid
  testPrecondition( response_function_index <
		    this->getNumberOfResponseFunctions() );
  // Make sure the contribution is valid
  testPrecondition( !Utility::QuantityTraits<double>::isnaninf( contribution ) );

  Utility::SampleMomentHistogram<double>& histogram =
    d_total_estimator_histograms[response_function_index];
  
  // Update the histogram
  #pragma omp critical
  {
    histogram.addRawScore( contribution );
  }
}

// Add info to update tracker
void StandardEntityEstimator::addInfoToUpdateTracker(
						    const size_t thread_id,
						    const EntityId entity_id,
						    const size_t bin_index,
						    const double contribution )
{
  // Make sure the thread id is valid
  testPrecondition( thread_id < d_update_tracker.size() );

  BinContributionMap& thread_entity_bin_contribution_map =
    d_update_tracker[thread_id][entity_id];

  BinContributionMap::iterator entity_bin_data =
    thread_entity_bin_contribution_map.find( bin_index );

  if( entity_bin_data != thread_entity_bin_contribution_map.end() )
    entity_bin_data->second += contribution;
  else
    thread_entity_bin_contribution_map[bin_index] = contribution;
}

// Get the bin iterator from an update tracker iterator
void StandardEntityEstimator::getEntityIteratorFromUpdateTracker(
              const size_t thread_id,
	      typename SerialUpdateTracker::const_iterator& start_entity,
	      typename SerialUpdateTracker::const_iterator& end_entity ) const
{
  // Make sure the thread is is valid
  testPrecondition( thread_id < d_update_tracker.size() );

  start_entity = d_update_tracker[thread_id].begin();
  end_entity = d_update_tracker[thread_id].end();
}

// Get the bin iterator from an update tracker iterator
void StandardEntityEstimator::getBinIteratorFromUpdateTrackerIterator(
           const size_t thread_id,
	   const typename SerialUpdateTracker::const_iterator& entity_iterator,
	   BinContributionMap::const_iterator& start_bin,
	   BinContributionMap::const_iterator& end_bin ) const
{
  // Make sure the thread id is valid
  testPrecondition( thread_id < d_update_tracker.size() );
  // Make sure the entity iterator is valid
  testPrecondition( entity_iterator != d_update_tracker[thread_id].end() );

  start_bin = entity_iterator->second.begin();
  end_bin = entity_iterator->second.end();
}

// Reset the update tracker
void StandardEntityEstimator::resetUpdateTracker( const size_t thread_id )
{
  d_update_tracker[thread_id].clear();
}

EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::StandardEntityEstimator );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEntityEstimator.cpp
//---------------------------------------------------------------------------//
