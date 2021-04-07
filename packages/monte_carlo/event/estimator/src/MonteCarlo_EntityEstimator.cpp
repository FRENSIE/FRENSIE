//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EntityEstimator.cpp
//! \author Alex Robinson
//! \brief  The Entity estimator class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_EntityEstimator.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
EntityEstimator::EntityEstimator()
{ /* ... */ }

// Constructor with no entities (for mesh estimators)
EntityEstimator::EntityEstimator( const Id id,
                                  const double multiplier )
  : Estimator( id, multiplier ),
    d_total_norm_constant( 1.0 ),
    d_supplied_norm_constants( false ),
    d_estimator_total_bin_data( 1 ),
    d_entity_estimator_moments_map(),
    d_entity_bin_snapshots_enabled( false ),
    d_estimator_total_bin_data_snapshots(),
    d_entity_estimator_moments_snapshots_map(),
    d_entity_bin_histograms_enabled( false ),
    d_estimator_total_bin_histograms(),
    d_entity_estimator_histograms_map(),
    d_entity_norm_constants_map()
{ /* ... */ }

// Return the entity ids associated with this estimator
void EntityEstimator::getEntityIds( std::set<EntityId>& entity_ids ) const
{
  for( auto&& entity_data : d_entity_norm_constants_map )
    entity_ids.insert( entity_data.first );
}
// Check if the entity is assigned to this estimator
bool EntityEstimator::isEntityAssigned( const EntityId entity_id ) const
{
  return d_entity_norm_constants_map.find( entity_id ) !=
    d_entity_norm_constants_map.end();
}

// Return the normalization constant for an entity
double EntityEstimator::getEntityNormConstant( const EntityId entity_id ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );

  return d_entity_norm_constants_map.find( entity_id )->second;
}

// Return the total normalization constant
double EntityEstimator::getTotalNormConstant() const
{
  return d_total_norm_constant;
}

// Get the total estimator bin data first moments
Utility::ArrayView<const double> EntityEstimator::getTotalBinDataFirstMoments() const
{
  return Utility::ArrayView<const double>(
                    Utility::getCurrentScores<1>( d_estimator_total_bin_data ),
                    d_estimator_total_bin_data.size() );
}

// Get the total estimator bin data second moments
Utility::ArrayView<const double> EntityEstimator::getTotalBinDataSecondMoments() const
{
  return Utility::ArrayView<const double>(
                    Utility::getCurrentScores<2>( d_estimator_total_bin_data ),
                    d_estimator_total_bin_data.size() );
}

// Get the total estimator bin data third moments
Utility::ArrayView<const double> EntityEstimator::getTotalBinDataThirdMoments() const
{
  return Utility::ArrayView<const double>(
                    Utility::getCurrentScores<3>( d_estimator_total_bin_data ),
                    d_estimator_total_bin_data.size() );
}

// Get the total estimator bin data fourth moments
Utility::ArrayView<const double> EntityEstimator::getTotalBinDataFourthMoments() const
{
  return Utility::ArrayView<const double>(
                    Utility::getCurrentScores<4>( d_estimator_total_bin_data ),
                    d_estimator_total_bin_data.size() );
}

// Get the bin data first moments for an entity
Utility::ArrayView<const double> EntityEstimator::getEntityBinDataFirstMoments( const EntityId entity_id ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );

  const FourEstimatorMomentsCollection& entity_collection =
    d_entity_estimator_moments_map.find( entity_id )->second;

  return Utility::ArrayView<const double>(
                             Utility::getCurrentScores<1>( entity_collection ),
                             entity_collection.size() );
}
  
// Get the bin data second moments for an entity
Utility::ArrayView<const double> EntityEstimator::getEntityBinDataSecondMoments( const EntityId entity_id ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );

  const FourEstimatorMomentsCollection& entity_collection =
    d_entity_estimator_moments_map.find( entity_id )->second;

  return Utility::ArrayView<const double>(
                             Utility::getCurrentScores<2>( entity_collection ),
                             entity_collection.size() );
}

// Get the bin data third moments for an entity
Utility::ArrayView<const double> EntityEstimator::getEntityBinDataThirdMoments( const EntityId entity_id ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );

  const FourEstimatorMomentsCollection& entity_collection =
    d_entity_estimator_moments_map.find( entity_id )->second;

  return Utility::ArrayView<const double>(
                             Utility::getCurrentScores<3>( entity_collection ),
                             entity_collection.size() );
}

// Get the bin data fourth moments for an entity
Utility::ArrayView<const double> EntityEstimator::getEntityBinDataFourthMoments( const EntityId entity_id ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );

  const FourEstimatorMomentsCollection& entity_collection =
    d_entity_estimator_moments_map.find( entity_id )->second;

  return Utility::ArrayView<const double>(
                             Utility::getCurrentScores<4>( entity_collection ),
                             entity_collection.size() );
}

// Enable snapshots on entity bins
void EntityEstimator::enableSnapshotsOnEntityBins()
{
  d_entity_bin_snapshots_enabled = true;

  this->initializeEntityEstimatorSnapshotsMap();
  this->resizeEstimatorTotalSnapshots();
}

// Check if snapshots have been enabled on entity bins
bool EntityEstimator::areSnapshotsOnEntityBinsEnabled() const
{
  return d_entity_bin_snapshots_enabled;
}

// Take a snapshot (of the moments)
void EntityEstimator::takeSnapshot( const uint64_t num_histories_since_last_snapshot,
                                    const double time_since_last_snapshot )
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );
  
  if( d_entity_bin_snapshots_enabled )
  {
    d_estimator_total_bin_data_snapshots.takeSnapshot( num_histories_since_last_snapshot,
                                                       time_since_last_snapshot,
                                                       d_estimator_total_bin_data );

    for( auto&& entity_data : d_entity_estimator_moments_snapshots_map )
    {
      entity_data.second.takeSnapshot( num_histories_since_last_snapshot,
                                       time_since_last_snapshot,
                                       d_entity_estimator_moments_map[entity_data.first] );
    }
  }
}

// Get the entity bin moment snapshot history values
void EntityEstimator::getEntityBinMomentSnapshotHistoryValues(
                                  const EntityId entity_id,
                                  std::vector<uint64_t>& history_values ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );
  
  if( d_entity_bin_snapshots_enabled )
  {
    const std::list<uint64_t>& raw_history_values = 
      d_entity_estimator_moments_snapshots_map.find( entity_id )->second.getSnapshotIndices();
    
    history_values.assign( raw_history_values.begin(),
                           raw_history_values.end() );
  }
}

// Get the entity bin moment snapshot sampling times
void EntityEstimator::getEntityBinMomentSnapshotSamplingTimes(
                                    const EntityId entity_id,
                                    std::vector<double>& sampling_times ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );
  
  if( d_entity_bin_snapshots_enabled )
  {
    const std::list<double>& raw_sampling_time_values = 
      d_entity_estimator_moments_snapshots_map.find( entity_id )->second.getSnapshotSamplingTimes();
    
    sampling_times.assign( raw_sampling_time_values.begin(),
                           raw_sampling_time_values.end() );
  }
}

// Get the bin data first moment snapshots for an entity bin index
void EntityEstimator::getEntityBinFirstMomentSnapshots(
                                           const EntityId entity_id,
                                           const size_t bin_index,
                                           std::vector<double>& moments ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );
  
  // Make sure that the bin index is valid
  TEST_FOR_EXCEPTION( bin_index >= this->getNumberOfBins()*this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The bin index must be less than "
                      << this->getNumberOfBins()*this->getNumberOfResponseFunctions() << "!" );

  if( d_entity_bin_snapshots_enabled )
  {
    const std::list<double>& moment_snapshots =
      Utility::getScoreSnapshots<1>(
            d_entity_estimator_moments_snapshots_map.find( entity_id )->second,
            bin_index );

    moments.assign( moment_snapshots.begin(), moment_snapshots.end() );
  }
}

// Get the bin data second moment snapshots for an entity bin index
void EntityEstimator::getEntityBinSecondMomentSnapshots(
                                           const EntityId entity_id,
                                           const size_t bin_index,
                                           std::vector<double>& moments ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );
  
  // Make sure that the bin index is valid
  TEST_FOR_EXCEPTION( bin_index >= this->getNumberOfBins()*this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The bin index must be less than "
                      << this->getNumberOfBins()*this->getNumberOfResponseFunctions() << "!" );

  if( d_entity_bin_snapshots_enabled )
  {
    const std::list<double>& moment_snapshots =
      Utility::getScoreSnapshots<2>(
           d_entity_estimator_moments_snapshots_map.find( entity_id )->second,
           bin_index );

    moments.assign( moment_snapshots.begin(), moment_snapshots.end() );
  }
}

// Get the bin data third moment snapshots for an entity bin index
void EntityEstimator::getEntityBinThirdMomentSnapshots(
                                           const EntityId entity_id,
                                           const size_t bin_index,
                                           std::vector<double>& moments ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );
  
  // Make sure that the bin index is valid
  TEST_FOR_EXCEPTION( bin_index >= this->getNumberOfBins()*this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The bin index must be less than "
                      << this->getNumberOfBins()*this->getNumberOfResponseFunctions() << "!" );

  if( d_entity_bin_snapshots_enabled )
  {
    const std::list<double>& moment_snapshots =
      Utility::getScoreSnapshots<3>(
           d_entity_estimator_moments_snapshots_map.find( entity_id )->second,
           bin_index );

    moments.assign( moment_snapshots.begin(), moment_snapshots.end() );
  }
}

// Get the bin data fourth moment snapshots for an entity bin index
void EntityEstimator::getEntityBinFourthMomentSnapshots(
                                           const EntityId entity_id,
                                           const size_t bin_index,
                                           std::vector<double>& moments ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );
  
  // Make sure that the bin index is valid
  TEST_FOR_EXCEPTION( bin_index >= this->getNumberOfBins()*this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The bin index must be less than "
                      << this->getNumberOfBins()*this->getNumberOfResponseFunctions() << "!" );

  if( d_entity_bin_snapshots_enabled )
  {
    const std::list<double>& moment_snapshots =
      Utility::getScoreSnapshots<4>(
           d_entity_estimator_moments_snapshots_map.find( entity_id )->second,
           bin_index );
    
    moments.assign( moment_snapshots.begin(), moment_snapshots.end() );
  }
}

// Get the moment snapshot history values
void EntityEstimator::getTotalBinMomentSnapshotHistoryValues(
                                  std::vector<uint64_t>& history_values ) const
{
  if( d_entity_bin_snapshots_enabled )
  {
    const std::list<uint64_t>& raw_history_values = 
      d_estimator_total_bin_data_snapshots.getSnapshotIndices();
    
    history_values.assign( raw_history_values.begin(),
                           raw_history_values.end() );
  }
}

// Get the moment snapshot sampling times for a total bin index
void EntityEstimator::getTotalBinMomentSnapshotSamplingTimes(
                                    std::vector<double>& sampling_times ) const
{
  if( d_entity_bin_snapshots_enabled )
  {
    const std::list<double>& raw_sampling_time_values = 
      d_estimator_total_bin_data_snapshots.getSnapshotSamplingTimes();
    
    sampling_times.assign( raw_sampling_time_values.begin(),
                           raw_sampling_time_values.end() );
  }
}

// Get the bin data first moment snapshots for an total bin index
void EntityEstimator::getTotalBinFirstMomentSnapshots(
                                           const size_t bin_index,
                                           std::vector<double>& moments ) const
{
  // Make sure that the bin index is valid
  TEST_FOR_EXCEPTION( bin_index >= this->getNumberOfBins()*this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The bin index must be less than "
                      << this->getNumberOfBins()*this->getNumberOfResponseFunctions() << "!" );

  if( d_entity_bin_snapshots_enabled )
  {
    const std::list<double>& moment_snapshots =
      Utility::getScoreSnapshots<1>( d_estimator_total_bin_data_snapshots,
                                     bin_index );
    
    moments.assign( moment_snapshots.begin(), moment_snapshots.end() );
  }
}

// Get the bin data second moment snapshots for an total bin index
void EntityEstimator::getTotalBinSecondMomentSnapshots(
                                           const size_t bin_index,
                                           std::vector<double>& moments ) const
{
  // Make sure that the bin index is valid
  TEST_FOR_EXCEPTION( bin_index >= this->getNumberOfBins()*this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The bin index must be less than "
                      << this->getNumberOfBins()*this->getNumberOfResponseFunctions() << "!" );

  if( d_entity_bin_snapshots_enabled )
  {
    const std::list<double>& moment_snapshots =
      Utility::getScoreSnapshots<2>( d_estimator_total_bin_data_snapshots,
                                     bin_index );
    
    moments.assign( moment_snapshots.begin(), moment_snapshots.end() );
  }
}

// Get the bin data third moment snapshots for an total bin index
void EntityEstimator::getTotalBinThirdMomentSnapshots(
                                           const size_t bin_index,
                                           std::vector<double>& moments ) const
{
  // Make sure that the bin index is valid
  TEST_FOR_EXCEPTION( bin_index >= this->getNumberOfBins()*this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The bin index must be less than "
                      << this->getNumberOfBins()*this->getNumberOfResponseFunctions() << "!" );

  if( d_entity_bin_snapshots_enabled )
  {
    const std::list<double>& moment_snapshots =
      Utility::getScoreSnapshots<3>( d_estimator_total_bin_data_snapshots,
                                     bin_index );
    
    moments.assign( moment_snapshots.begin(), moment_snapshots.end() );
  }
}

// Get the bin data fourth moment snapshots for an total bin index
void EntityEstimator::getTotalBinFourthMomentSnapshots(
                                           const size_t bin_index,
                                           std::vector<double>& moments ) const
{
  // Make sure that the bin index is valid
  TEST_FOR_EXCEPTION( bin_index >= this->getNumberOfBins()*this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The bin index must be less than "
                      << this->getNumberOfBins()*this->getNumberOfResponseFunctions() << "!" );

  if( d_entity_bin_snapshots_enabled )
  {
    const std::list<double>& moment_snapshots =
      Utility::getScoreSnapshots<4>( d_estimator_total_bin_data_snapshots,
                                     bin_index );

    moments.assign( moment_snapshots.begin(), moment_snapshots.end() );
  }
}

// Enable sample moment histograms on entity bins
void EntityEstimator::enableSampleMomentHistogramsOnEntityBins()
{
  d_entity_bin_histograms_enabled = true;

  this->initializeEntityEstimatorHistogramsMap();
  this->resizeEstimatorTotalHistograms();
}

// Check if sample moment histograms are enabled on on entity bins
bool EntityEstimator::areSampleMomentHistogramsOnEntityBinsEnabled() const
{
  return d_entity_bin_histograms_enabled;
}

// Get the entity bin sample moment histogram
void EntityEstimator::getEntityBinSampleMomentHistogram(
                      const EntityId entity_id,
                      const size_t bin_index,
                      Utility::SampleMomentHistogram<double>& histogram ) const
{
  // Make sure that the entity id is valid
  TEST_FOR_EXCEPTION( !this->isEntityAssigned( entity_id ),
                      std::runtime_error,
                      "Entity " << entity_id << " is not assigned to "
                      "estimator " << this->getId() << "!" );
  
  // Make sure that the bin index is valid
  TEST_FOR_EXCEPTION( bin_index >= this->getNumberOfBins()*this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The bin index must be less than "
                      << this->getNumberOfBins()*this->getNumberOfResponseFunctions() << "!" );

  if( d_entity_bin_histograms_enabled )
  {
    histogram = d_entity_estimator_histograms_map.find( entity_id )->second[bin_index];
  }
}

// Get the total bin sample moment histogram
void EntityEstimator::getTotalBinSampleMomentHistogram(
                      const size_t bin_index,
                      Utility::SampleMomentHistogram<double>& histogram ) const
{
  // Make sure that the bin index is valid
  TEST_FOR_EXCEPTION( bin_index >= this->getNumberOfBins()*this->getNumberOfResponseFunctions(),
                      std::runtime_error,
                      "The bin index must be less than "
                      << this->getNumberOfBins()*this->getNumberOfResponseFunctions() << "!" );

  if( d_entity_bin_histograms_enabled )
    histogram = d_estimator_total_bin_histograms[bin_index];
}

// Reset the estimator data
void EntityEstimator::resetData()
{
  // Reset the total bin data
  d_estimator_total_bin_data.reset();

  // Reset the entity bin data
  for( auto&& entity_data : d_entity_estimator_moments_map )
    entity_data.second.reset();

  if( d_entity_bin_snapshots_enabled )
  {
    // Reset the total snapshot data
    d_estimator_total_bin_data_snapshots.reset();

    // Reset the entity bin snapshot data
    for( auto&& entity_data : d_entity_estimator_moments_snapshots_map )
      entity_data.second.reset();
  }

  if( d_entity_bin_histograms_enabled )
  {
    // Reset the total histogram data
    for( auto&& histogram : d_estimator_total_bin_histograms )
      histogram.reset();

    // Reset the entity histogram data
    for( auto&& entity_data : d_entity_estimator_histograms_map )
    {
      for( auto&& histogram : entity_data.second )
        histogram.reset();
    }
  }
}

// Reduce estimator data on all processes and collect on the root process
void EntityEstimator::reduceData( const Utility::Communicator& comm,
                                  const int root_process )
{
  // Make sure the root process is valid
  testPrecondition( root_process < comm.size() );

  // Only do the reduction if there is more than one process
  if( comm.size() > 1 )
  {
    // Reduce the entity bin data
    try{
      this->reduceEntityCollectionMaps( comm, root_process, d_entity_estimator_moments_map );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Unable to perform mpi reduction in entity bin "
                             "estimator " << this->getId() << " for entity "
                             "bin data!" );

    comm.barrier();

    // Reduce bin data of total
    try{
      this->reduceCollection( comm, root_process, d_estimator_total_bin_data );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Unable to perform mpi reduction in entity "
                             "estimator " << this->getId() << " for total bin "
                             "data!" );

    if( d_entity_bin_snapshots_enabled )
    {
      // Reduce the entity bin snapshot data
      try{
        this->reduceEntitySnapshotMaps( comm, root_process, d_entity_estimator_moments_snapshots_map );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Unable to perform mpi reduction in entity "
                               "estimator " << this->getId() << " for entity "
                               "bin snapshot data!" );

      // Reduce the total bin snapshot data
      try{
        this->reduceSnapshots( comm, root_process, d_estimator_total_bin_data_snapshots );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Unable to perform mpi reduction in entity "
                               "estimator " << this->getId() << " for total "
                               "bin snapshot data!" );
    }

    if( d_entity_bin_histograms_enabled )
    {
      // Reduce the entity bin histogram data
      try{
        this->reduceEntityHistogramMaps( comm, root_process, d_entity_estimator_histograms_map );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Unable to perform mpi reduction in entity "
                               "estimator " << this->getId() << " for entity "
                               "bin histogram data!" );

      // Reduce the total bin histogram data
      try{
        this->reduceHistogramArrays( comm, root_process, d_estimator_total_bin_histograms );
      }
      EXCEPTION_CATCH_RETHROW( std::runtime_error,
                               "Unable to perform mpi reduction in entity "
                               "estimator " << this->getId() << " for total "
                               "bin histogram data!" );
    }
  }

  Estimator::reduceData( comm, root_process );
}

// Reduce the entity collection maps
void EntityEstimator::reduceEntityCollectionMaps(
                    const Utility::Communicator& comm,
                    const int root_process,
                    EntityEstimatorMomentsCollectionMap& collection_map ) const
{
  // Gather all of the entity data on the root process
  if( comm.rank() == root_process )
  {
    std::vector<EntityEstimatorMomentsCollectionMap>
      gathered_entity_data( comm.size() );

    std::vector<Utility::Communicator::Request> gathered_requests;

    for( size_t i = 0; i < comm.size(); ++i )
    {
      if( i != root_process )
      {
        gathered_requests.push_back(
                    Utility::ireceive( comm, i, 0, gathered_entity_data[i] ) );
      }
    }

    std::vector<Utility::Communicator::Status>
      gathered_statuses( gathered_requests.size() );
    
    Utility::wait( gathered_requests, gathered_statuses );
    
    this->reduceEntityCollections( gathered_entity_data,
                                   root_process,
                                   collection_map );
  }
  else
    Utility::send( comm, root_process, 0, collection_map );
}

// Reduce the entity moments
void EntityEstimator::reduceEntityCollections(
                    const std::vector<EntityEstimatorMomentsCollectionMap>&
                    other_entity_estimator_moments_maps,
                    const size_t root_index,
                    EntityEstimatorMomentsCollectionMap& collection_map ) const
{
  // Reduce the data that was on each process
  for( auto&& entity_data : collection_map )
  {
    // Don't double count data on this process (j starts from 1)
    for( size_t j = 0; j < other_entity_estimator_moments_maps.size(); ++j )
    {
      if( j != root_index )
      {
        const EntityEstimatorMomentsCollectionMap::value_type&
          other_entity_data = *other_entity_estimator_moments_maps[j].find( entity_data.first );

        for( size_t i = 0; i < entity_data.second.size(); ++i )
        {
          Utility::getCurrentScore<1>( entity_data.second, i ) +=
            Utility::getCurrentScore<1>( other_entity_data.second, i );

          Utility::getCurrentScore<2>( entity_data.second, i ) +=
            Utility::getCurrentScore<2>( other_entity_data.second, i );

          Utility::getCurrentScore<3>( entity_data.second, i ) +=
            Utility::getCurrentScore<3>( other_entity_data.second, i );

          Utility::getCurrentScore<4>( entity_data.second, i ) +=
            Utility::getCurrentScore<4>( other_entity_data.second, i );
        }
      }
    }
  }
}

// Reduce the entity snapshot maps
void EntityEstimator::reduceEntitySnapshotMaps(
            const Utility::Communicator& comm,
            const int root_process,
            EntityEstimatorMomentsCollectionSnapshotsMap& snapshots_map ) const
{
  // Gather all of the entity data on the root process
  if( comm.rank() == root_process )
  {
    std::vector<EntityEstimatorMomentsCollectionSnapshotsMap>
      gathered_entity_data( comm.size() );

    std::vector<Utility::Communicator::Request> gathered_requests;

    for( size_t i = 0; i < comm.size(); ++i )
    {
      if( i != root_process )
      {
        gathered_requests.push_back(
                    Utility::ireceive( comm, i, 0, gathered_entity_data[i] ) );
      }
    }

    std::vector<Utility::Communicator::Status>
      gathered_statuses( gathered_requests.size() );

    Utility::wait( gathered_requests, gathered_statuses );

    this->reduceEntitySnapshots( gathered_entity_data,
                                 root_process,
                                 snapshots_map );
  }
  else
    Utility::send( comm, root_process, 0, snapshots_map );
}

// Reduce the entity snapshots
void EntityEstimator::reduceEntitySnapshots(
            const std::vector<EntityEstimatorMomentsCollectionSnapshotsMap>&
            other_entity_estimator_snapshots_maps,
            const size_t root_index,
            EntityEstimatorMomentsCollectionSnapshotsMap& snapshots_map ) const
{
  // Reduce the data that was on each process
  for( auto&& entity_data : snapshots_map )
  {
    // Don't double count data on this process (j starts from 1)
    for( size_t j = 0; j < other_entity_estimator_snapshots_maps.size(); ++j )
    {
      if( j != root_index )
      {
        const EntityEstimatorMomentsCollectionSnapshotsMap::value_type&
          other_entity_data = *other_entity_estimator_snapshots_maps[j].find( entity_data.first );

        entity_data.second.mergeSnapshots( other_entity_data.second );
      }
    }
  }
}

// Reduce the entity histogram maps
void EntityEstimator::reduceEntityHistogramMaps(
            const Utility::Communicator& comm,
            const int root_process,
            EntityEstimatorSampleMomentHistogramArrayMap& histogram_map ) const
{
  // Gather all of the entity data on the root process
  if( comm.rank() == root_process )
  {
    std::vector<EntityEstimatorSampleMomentHistogramArrayMap>
      gathered_entity_data( comm.size() );

    std::vector<Utility::Communicator::Request> gathered_requests;

    for( size_t i = 0; i < comm.size(); ++i )
    {
      if( i != root_process )
      {
        gathered_requests.push_back(
                    Utility::ireceive( comm, i, 0, gathered_entity_data[i] ) );
      }
    }

    std::vector<Utility::Communicator::Status>
      gathered_statuses( gathered_requests.size() );

    Utility::wait( gathered_requests, gathered_statuses );

    this->reduceEntityHistograms( gathered_entity_data,
                                  root_process,
                                  histogram_map );
  }
  else
    Utility::send( comm, root_process, 0, histogram_map );
}

// Reduce the entity histograms
void EntityEstimator::reduceEntityHistograms(
            const std::vector<EntityEstimatorSampleMomentHistogramArrayMap>&
            gathered_entity_data,
            const size_t root_index,
            EntityEstimatorSampleMomentHistogramArrayMap& histogram_map ) const
{
  // Reduce the data that was on each process
  for( auto&& entity_data : histogram_map )
  {
    for( size_t i = 0; i < entity_data.second.size(); ++i )
    {
      Utility::SampleMomentHistogram<double>& histogram =
        entity_data.second[i];
      
      // Don't double count data on this process (j starts from 1)
      for( size_t j = 0; j < gathered_entity_data.size(); ++j )
      {
        if( j != root_index )
        {
          const Utility::SampleMomentHistogram<double>& other_histogram = 
            gathered_entity_data[j].find( entity_data.first )->second[i];

          histogram.mergeHistograms( other_histogram );
        }
      }
    }
  }
}

// Reduce the histogram arrays
void EntityEstimator::reduceHistogramArrays(
                            const Utility::Communicator& comm,
                            const int root_process,
                            SampleMomentHistogramArray& histogram_array ) const
{
  // Gather all of the entity data on the root process
  if( comm.rank() == root_process )
  {
    std::vector<SampleMomentHistogramArray>
      gathered_entity_data( comm.size() );

    std::vector<Utility::Communicator::Request> gathered_requests;

    for( size_t i = 0; i < comm.size(); ++i )
    {
      if( i != root_process )
      {
        gathered_requests.push_back(
                    Utility::ireceive( comm, i, 0, gathered_entity_data[i] ) );
      }
    }

    std::vector<Utility::Communicator::Status>
      gathered_statuses( gathered_requests.size() );

    Utility::wait( gathered_requests, gathered_statuses );

    this->reduceEntityHistograms( gathered_entity_data,
                                  root_process,
                                  histogram_array );
  }
  else
    Utility::send( comm, root_process, 0, histogram_array );
}

// Reduce the entity histograms
void EntityEstimator::reduceEntityHistograms(
                            const std::vector<SampleMomentHistogramArray>&
                            gathered_entity_data,
                            const size_t root_index,
                            SampleMomentHistogramArray& histogram_array ) const
{
  // Reduce the data that was on each process
  for( size_t i = 0; i < histogram_array.size(); ++i )
  {
    Utility::SampleMomentHistogram<double>& histogram =
      histogram_array[i];
      
    // Don't double count data on this process (j starts from 1)
    for( size_t j = 0; j < gathered_entity_data.size(); ++j )
    {
      if( j != root_index )
      {
        const Utility::SampleMomentHistogram<double>& other_histogram =
          gathered_entity_data[j][i];
        
        histogram.mergeHistograms( other_histogram );
      }
    }
  }
}

// Assign entities
void EntityEstimator::assignEntities(
                                   const EntityNormConstMap& entity_norm_data )
{
  // Make sure there is at least one entity
  testPrecondition( entity_norm_data.size() > 0 );

  // Reset the estimator data
  d_total_norm_constant = 1.0;
  d_supplied_norm_constants = true;
  d_estimator_total_bin_data.clear();
  d_entity_estimator_moments_map.clear();
  d_estimator_total_bin_data_snapshots.clear();
  d_entity_estimator_moments_snapshots_map.clear();
  d_estimator_total_bin_histograms.clear();
  d_entity_estimator_histograms_map.clear();
  d_entity_norm_constants_map = entity_norm_data;

  // Initialize the entity data
  for( auto&& entity_data : entity_norm_data )
  {
    d_entity_estimator_moments_map[entity_data.first];

    if( d_entity_bin_snapshots_enabled )
      d_entity_estimator_moments_snapshots_map[entity_data.first];

    if( d_entity_bin_histograms_enabled )
      d_entity_estimator_histograms_map[entity_data.first];
  }

  // Calculate the total normalization constant
  this->calculateTotalNormalizationConstant();

  // Resize the data
  this->resizeEntityEstimatorMapCollections();
  this->resizeEntityEstimatorMapSnapshots();
  this->resizeEntityEstimatorMapHistograms();

  // Resize the total data (it was likely not initialized in the constructor
  // if assignEntities was called)
  this->resizeEstimatorTotalCollection();
  this->resizeEstimatorTotalSnapshots();
  this->resizeEstimatorTotalHistograms();
}

// Assign discretization to an estimator dimension
void EntityEstimator::assignDiscretization(
  const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
  const bool range_dimension )
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::OpenMPProperties::getThreadId() == 0 );

  Estimator::assignDiscretization( bins, range_dimension );

  // Resize the entity estimator moments map collections
  this->resizeEntityEstimatorMapCollections();

  // Resize the total array
  this->resizeEstimatorTotalCollection();

  // Resize the entity estimator moments map snapshots
  this->resizeEntityEstimatorMapSnapshots();

  // Resize the estimator total snapshots
  this->resizeEstimatorTotalSnapshots();

  // Resize the entity estimator histograms
  this->resizeEntityEstimatorMapHistograms();

  // Resize the estimator total histograms
  this->resizeEstimatorTotalHistograms();
}

// Set the response functions
void EntityEstimator::assignResponseFunction(
             const std::shared_ptr<const ParticleResponse>& response_function )
{
  Estimator::assignResponseFunction( response_function );

  // Resize the entity estimator moment map collections
  this->resizeEntityEstimatorMapCollections();

  // Resize the total collection
  this->resizeEstimatorTotalCollection();

  // Resize the entity estimator moments map snapshots
  this->resizeEntityEstimatorMapSnapshots();

  // Resize the estimator total snapshots
  this->resizeEstimatorTotalSnapshots();

  // Resize the entity estimator histograms
  this->resizeEntityEstimatorMapHistograms();

  // Resize the estimator total histograms
  this->resizeEstimatorTotalHistograms();
}

// Assign the history score pdf bins
void EntityEstimator::assignSampleMomentHistogramBins( const std::shared_ptr<const std::vector<double> >& bins )
{
  Estimator::assignSampleMomentHistogramBins( bins );

  if( d_entity_bin_histograms_enabled );
  {
    for( auto&& histogram : d_estimator_total_bin_histograms )
      histogram.setBinBoundaries( bins );

    for( auto&& entity_data : d_entity_estimator_histograms_map )
    {
      for( auto&& histogram : entity_data.second )
        histogram.setBinBoundaries( bins );
    }
  }
}

// Commit history contribution to a bin of an entity
void EntityEstimator::commitHistoryContributionToBinOfEntity(
						    const EntityId entity_id,
						    const size_t bin_index,
						    const double contribution )
{
  // Make sure the entity is assigned to this estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  // Make sure the bin index is valid
  testPrecondition( bin_index <
		    this->getNumberOfBins()*
                    this->getNumberOfResponseFunctions() );

  FourEstimatorMomentsCollection& entity_estimator_moments =
    d_entity_estimator_moments_map.find( entity_id )->second;

  // Update the moments
  #pragma omp critical
  {
    entity_estimator_moments.addRawScore( bin_index, contribution );
  }

  this->addHistoryContributionToEntityBinHistogram( entity_id,
                                                    bin_index,
                                                    contribution );
}

// Add contribution to histogram
void EntityEstimator::addHistoryContributionToEntityBinHistogram(
                                                    const EntityId entity_id,
                                                    const size_t bin_index,
                                                    const double contribution )
{
  // Make sure the entity is assigned to this estimator
  testPrecondition( this->isEntityAssigned( entity_id ) );
  // Make sure the bin index is valid
  testPrecondition( bin_index <
		    this->getNumberOfBins()*
                    this->getNumberOfResponseFunctions() );

  if( d_entity_bin_histograms_enabled )
  {
    Utility::SampleMomentHistogram<double>& histogram =
      d_entity_estimator_histograms_map.find( entity_id )->second[bin_index];

    // Update the histogram
    #pragma omp critical
    {
      histogram.addRawScore( contribution );
    }
  }
}

// Commit history contribution to a bin of the total
void EntityEstimator::commitHistoryContributionToBinOfTotal(
						   const size_t bin_index,
						   const double contribution )
{
  // Make sure the bin index is valid
  testPrecondition( bin_index <
		    this->getNumberOfBins()*
                    this->getNumberOfResponseFunctions() );

  // Update the moments
  #pragma omp critical
  {
    d_estimator_total_bin_data.addRawScore( bin_index, contribution );
  }

  this->addHistoryContributionToTotalBinHistogram( bin_index, contribution );
}

// Add contribution to total bin histogram
void EntityEstimator::addHistoryContributionToTotalBinHistogram(
                                                    const size_t bin_index,
                                                    const double contribution )
{
  // Make sure the bin index is valid
  testPrecondition( bin_index <
		    this->getNumberOfBins()*
                    this->getNumberOfResponseFunctions() );

  if( d_entity_bin_histograms_enabled )
  {
    Utility::SampleMomentHistogram<double>& histogram =
      d_estimator_total_bin_histograms[bin_index];

    #pragma omp critical
    {
      histogram.addRawScore( contribution );
    }
  }
}

// Print the estimator data
void EntityEstimator::printImplementation(
					 std::ostream& os,
					 const std::string& entity_type ) const
{
  // Print the entity ids that are assigned to this estimator
  this->printEntityIds( os, entity_type );

  // Print the entity norm constants
  if( d_supplied_norm_constants )
    this->printEntityNormConstants( os, entity_type );

  // Print the response function names
  this->printEstimatorResponseFunctionNames( os );

  // Print the binning data
  this->printObserverDiscretization( os );

  os << "\n";

  // Print the estimator data for each entity
  // typename EntityEstimatorMomentsCollectionMap::const_iterator entity_data,
  //   end_entity_data;

  // entity_data = d_entity_estimator_moments_map.begin();
  // end_entity_data = d_entity_estimator_moments_map.end();

  // while( entity_data != end_entity_data )
  // {
  //   os << entity_type << " " << entity_data->first
  //      << " Bin Data: " << std::endl;
  //   os << "--------" << std::endl;

  //   printEstimatorBinData( os,
  //       		   entity_data->second,
  //       		   getEntityNormConstant( entity_data->first ) );
  //   os << std::endl;

  //   ++entity_data;
  // }

  // Print the estimator total bin data
  // os << " Total Bin Data: " << std::endl;
  // os << "--------" << std::endl;

  // printEstimatorBinData( os,
  //       		 d_estimator_total_bin_data,
  //       		 d_total_norm_constant );

  // os << std::endl;
}

// Print the entity ids assigned to the estimator
void EntityEstimator::printEntityIds( std::ostream& os,
                                      const std::string& entity_type) const
{
  os << entity_type << " Ids: ";

  for( auto&& entity_data : d_entity_norm_constants_map )
    os << entity_data.first << " ";

  os << "\n";
}

// Print the entity norm constants assigned to the estimator
void EntityEstimator::printEntityNormConstants(
					 std::ostream& os,
					 const std::string& entity_type ) const
{
  os << entity_type;

  if( entity_type == "Cell" )
    os << " Volumes: ";
  else if( entity_type == "Surface" )
    os << " Areas: ";

  for( auto&& entity_data : d_entity_norm_constants_map )
    os << Utility::toString(entity_data.second) << " ";

  os << "\n";
}

// Get the total estimator bin data
/*! \details This function breaks encapsulation and is therefore not ideal.
 * It is needed by mesh estimators for exporting data in .h5m and .vtk formats.
 */
const Estimator::FourEstimatorMomentsCollection&
EntityEstimator::getTotalBinData() const
{
  return d_estimator_total_bin_data;
}

// Get the bin data for an entity
/*! \details This function breaks encapsulation and is therefore not ideal.
 * It is needed by mesh estimators for exporting data in .h5m and .vtk formats.
 */
const Estimator::FourEstimatorMomentsCollection&
EntityEstimator::getEntityBinData( const EntityId entity_id ) const
{
  // Make sure the entity is valid
  testPrecondition( d_entity_estimator_moments_map.find( entity_id ) !=
		    d_entity_estimator_moments_map.end() );

  return d_entity_estimator_moments_map.find( entity_id )->second;
}

// Calculate the total normalization constant
void EntityEstimator::calculateTotalNormalizationConstant()
{
  d_total_norm_constant = 0.0;

  for( auto&& entity_data : d_entity_norm_constants_map )
    d_total_norm_constant += entity_data.second;
}

// Initialize entity estimator snapshots map
void EntityEstimator::initializeEntityEstimatorSnapshotsMap()
{
  if( d_entity_bin_snapshots_enabled )
  {
    if( d_entity_estimator_moments_snapshots_map.size() !=
        d_entity_norm_constants_map.size() )
    {
      size_t size = this->getNumberOfBins()*
        this->getNumberOfResponseFunctions();
      
      for( auto&& entity_data : d_entity_norm_constants_map )
      {
        d_entity_estimator_moments_snapshots_map[entity_data.first].resize( size );
      }
    }
  }
}

// Initialize entity entity estimator histograms map
void EntityEstimator::initializeEntityEstimatorHistogramsMap()
{
  if( d_entity_bin_histograms_enabled )
  {
    if( d_entity_estimator_histograms_map.size() !=
        d_entity_norm_constants_map.size() )
    {
      size_t size = this->getNumberOfBins()*
        this->getNumberOfResponseFunctions();
      
      Utility::SampleMomentHistogram<double>
        default_histogram( this->getSampleMomentHistogramBins() );

      for( auto&& entity_data : d_entity_norm_constants_map )
      {
        d_entity_estimator_histograms_map[entity_data.first].resize( size, default_histogram );
      }
    }
  }
}

// Resize the entity estimator moments map collections
void EntityEstimator::resizeEntityEstimatorMapCollections()
{
  size_t size = this->getNumberOfBins()*this->getNumberOfResponseFunctions();
  
  for( auto&& entity_data : d_entity_estimator_moments_map )
    entity_data.second.resize( size );
}

// Resize the estimator total collection
void EntityEstimator::resizeEstimatorTotalCollection()
{
  d_estimator_total_bin_data.resize(
                this->getNumberOfBins()*this->getNumberOfResponseFunctions() );
}

// Resize the entity estimator snapshots
void EntityEstimator::resizeEntityEstimatorMapSnapshots()
{
  if( d_entity_bin_snapshots_enabled )
  {
    size_t size = this->getNumberOfBins()*
      this->getNumberOfResponseFunctions();
    
    for( auto&& entity_data : d_entity_estimator_moments_snapshots_map )
      entity_data.second.resize( size );
  }
}

// Resize the entity total snapshots
void EntityEstimator::resizeEstimatorTotalSnapshots()
{
  if( d_entity_bin_snapshots_enabled )
  {
    d_estimator_total_bin_data_snapshots.resize(
                this->getNumberOfBins()*this->getNumberOfResponseFunctions() );
  }
}

// Resize the entity estimator histograms
void EntityEstimator::resizeEntityEstimatorMapHistograms()
{
  if( d_entity_bin_histograms_enabled )
  {
    size_t size = this->getNumberOfBins()*
      this->getNumberOfResponseFunctions();

    Utility::SampleMomentHistogram<double>
      default_histogram( this->getSampleMomentHistogramBins() );

    for( auto&& entity_data : d_entity_estimator_histograms_map )
      entity_data.second.resize( size, default_histogram );
  }
}

// Resize the estimator total histograms
void EntityEstimator::resizeEstimatorTotalHistograms()
{
  if( d_entity_bin_histograms_enabled )
  {
    Utility::SampleMomentHistogram<double>
      default_histogram( this->getSampleMomentHistogramBins() );
    
    d_estimator_total_bin_histograms.resize(
                  this->getNumberOfBins()*this->getNumberOfResponseFunctions(),
                  default_histogram );
  }
}

EXPLICIT_CLASS_SERIALIZE_INST( EntityEstimator );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EntityEstimator.cpp
//---------------------------------------------------------------------------//
