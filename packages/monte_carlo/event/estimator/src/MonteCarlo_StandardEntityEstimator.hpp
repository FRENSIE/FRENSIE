//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardEntityEstimator.hpp
//! \author Alex Robinson
//! \brief  Standard entity estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ENTITY_ESTIMATOR_HPP
#define MONTE_CARLO_STANDARD_ENTITY_ESTIMATOR_HPP

// FRENSIE Includes
#include "MonteCarlo_EntityEstimator.hpp"
#include "Utility_Map.hpp"
#include "Utility_Vector.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

/*! The standard entity estimator class
 * \details This class has been set up to get correct results with multiple
 * threads. However, the commitHistoryContribution member function call should
 * only appear within an omp critical block. Use the enable thread support
 * member function to set up an instance of this class for the requested number
 * of threads. The classes default initialization is for a single thread.
 */
class StandardEntityEstimator : public EntityEstimator
{
  // Typedef for bin contribution map
  typedef std::unordered_map<size_t,double> BinContributionMap;

  // Typedef for serial update tracker
  typedef std::unordered_map<EntityId,BinContributionMap> SerialUpdateTracker;

  // Typedef for parallel update tracker
  typedef std::vector<SerialUpdateTracker> ParallelUpdateTracker;

protected:

  //! Typedef for the map of entity ids and estimator moments array
  typedef EntityEstimator::EntityEstimatorMomentsCollectionMap 
  EntityEstimatorMomentsCollectionMap;

  //! Typedef for the map of entity ids and the estimator moments snapshots
  typedef EntityEstimator::EntityEstimatorMomentsCollectionSnapshotsMap
  EntityEstimatorMomentsCollectionSnapshotsMap;

  //! Typedef for the sample moment histogram array
  typedef EntityEstimator::SampleMomentHistogramArray
  SampleMomentHistogramArray;
  
  //! Typedef for the map of entity ids and the sample moment histogram array
  typedef EntityEstimator::EntityEstimatorSampleMomentHistogramArrayMap
  EntityEstimatorSampleMomentHistogramArrayMap;

public:

  //! Constructor (for flux estimators)
  template<typename InputEntityId>
  StandardEntityEstimator( const Id id,
                           const double multiplier,
                           const std::vector<InputEntityId>& entity_ids,
                           const std::vector<double>& entity_norm_constants );

  //! Constructor (for non-flux estimators)
  template<typename InputEntityId>
  StandardEntityEstimator( const Id id,
			   const double multiplier,
			   const std::vector<InputEntityId>& entity_ids );

  //! Destructor
  virtual ~StandardEntityEstimator()
  { /* ... */ }

  //! Check if total data is available
  bool isTotalDataAvailable() const final override;

  //! Get the total data first moments
  Utility::ArrayView<const double> getTotalDataFirstMoments() const final override;

  //! Get the total data second moments
  Utility::ArrayView<const double> getTotalDataSecondMoments() const final override;

  //! Get the total data third moments
  Utility::ArrayView<const double> getTotalDataThirdMoments() const final override;

  //! Get the total data fourth moments
  Utility::ArrayView<const double> getTotalDataFourthMoments() const final override;

  //! Get the total data first moments for an entity
  Utility::ArrayView<const double> getEntityTotalDataFirstMoments( const EntityId entity_id ) const final override;

  //! Get the total data second moments for an entity
  Utility::ArrayView<const double> getEntityTotalDataSecondMoments( const EntityId entity_id ) const final override;

  //! Get the total data third moments for an entity
  Utility::ArrayView<const double> getEntityTotalDataThirdMoments( const EntityId entity_id ) const final override;

  //! Get the total data fourth moments for an entity
  Utility::ArrayView<const double> getEntityTotalDataFourthMoments( const EntityId entity_id ) const final override;

  //! Take a snapshot (of the moments)
  void takeSnapshot( const uint64_t num_histories_since_last_snapshot,
                     const double time_since_last_snapshot ) final override;

  //! Get the entity total moment snapshot history values
  void getEntityTotalMomentSnapshotHistoryValues(
                  const EntityId entity_id,
                  std::vector<uint64_t>& history_values ) const final override;

  //! Get the entity total moment snapshot sampling times
  void getEntityTotalMomentSnapshotSamplingTimes(
                    const EntityId entity_id,
                    std::vector<double>& sampling_times ) const final override;

  //! Get the total data first moment snapshots for an entity bin index
  void getEntityTotalFirstMomentSnapshots(
                           const EntityId entity_id,
                           const size_t response_function_index,
                           std::vector<double>& moments ) const final override;

  //! Get the total data second moment snapshots for an entity bin index
  void getEntityTotalSecondMomentSnapshots(
                           const EntityId entity_id,
                           const size_t response_function_index,
                           std::vector<double>& moments ) const final override;

  //! Get the total data third moment snapshots for an entity bin index
  void getEntityTotalThirdMomentSnapshots(
                           const EntityId entity_id,
                           const size_t response_function_index,
                           std::vector<double>& moments ) const final override;

  //! Get the total data fourth moment snapshots for an entity bin index
  void getEntityTotalFourthMomentSnapshots(
                           const EntityId entity_id,
                           const size_t response_function_index,
                           std::vector<double>& moments ) const final override;

  //! Get the total moment snapshot history values
  void getTotalMomentSnapshotHistoryValues(
                  std::vector<uint64_t>& history_values ) const final override;

  //! Get the total moment snapshot sampling times
  void getTotalMomentSnapshotSamplingTimes(
                    std::vector<double>& sampling_times ) const final override;
  
  //! Get the total data first moment snapshots for a total bin index
  void getTotalFirstMomentSnapshots(
                           const size_t response_function_index,
                           std::vector<double>& moments ) const final override;

  //! Get the total data second moment snapshots for a total bin index
  void getTotalSecondMomentSnapshots(
                           const size_t response_function_index,
                           std::vector<double>& moments ) const final override;

  //! Get the total data third moment snapshots for a total bin index
  void getTotalThirdMomentSnapshots(
                           const size_t response_function_index,
                           std::vector<double>& moments ) const final override;

  //! Get the total data fourth moment snapshots for a total bin index
  void getTotalFourthMomentSnapshots(
                           const size_t response_function_index,
                           std::vector<double>& moments ) const final override;

  //! Get the entity total sample moment histogram
  void getEntityTotalSampleMomentHistogram(
      const EntityId entity_id,
      const size_t response_function_index,
      Utility::SampleMomentHistogram<double>& histogram ) const final override;

  //! Get the total sample moment histogram
  void getTotalSampleMomentHistogram(
      const size_t response_function_index,
      Utility::SampleMomentHistogram<double>& histogram ) const final override;

  //! Commit the contribution from the current history to the estimator
  void commitHistoryContribution() final override;

  //! Enable support for multiple threads
  void enableThreadSupport( const unsigned num_threads ) final override;

  //! Reset estimator data
  void resetData() final override;

  //! Reduce estimator data on all processes and collect on the root process
  void reduceData( const Utility::Communicator& comm,
                   const int root_process ) final override;

protected:

  //! Default constructor
  StandardEntityEstimator();

  //! Constructor with no entities (for mesh estimators)
  StandardEntityEstimator( const Id id, const double multiplier );

  //! Assign entities
  void assignEntities( const EntityEstimator::EntityNormConstMap& entity_norm_data ) override;

  //! Assign response function to the estimator
  void assignResponseFunction( const std::shared_ptr<const ParticleResponse>& response_function ) override;

  //! Assign the history score pdf bins
  void assignSampleMomentHistogramBins( const std::shared_ptr<const std::vector<double> >& bins ) final override;

  //! Print the estimator data
  void printImplementation( std::ostream& os,
			    const std::string& entity_type ) const final override;

  //! Add estimator contribution from a point of the current history
  void addPartialHistoryPointContribution(
                   const EntityId entity_id,
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   const double contribution );

  //! Add estimator contribution from a range of the current history
  void addPartialHistoryRangeContribution(
                   const EntityId entity_id,
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   const double contribution );

  //! Get the total estimator data
  const Estimator::FourEstimatorMomentsCollection& getTotalData() const;

  //! Get the total data for an entity
  const Estimator::FourEstimatorMomentsCollection&
  getEntityTotalData( const EntityId entity_id ) const;

private:

  // Resize the entity total estimator moments map collections
  void resizeEntityTotalEstimatorMomentsMapCollections();

  // Commit history contr. to the total for a response function of an entity
  void commitHistoryContributionToTotalOfEntity(
					const EntityId entity_id,
					const size_t response_function_index,
					const double contribution );

  // Commit hist. contr. to the total for a response function of the estimator
  void commitHistoryContributionToTotalOfEstimator(
					const size_t response_function_index,
					const double contribution );

  // Add contribution to entity bin histogram
  void addHistoryContributionToEntityBinHistogram(
                                          const EntityId entity_id,
                                          const size_t response_function_index,
                                          const double contribution );

  // Add contribution to total bin histogram
  void addHistoryContributionToTotalBinHistogram(
                                          const size_t response_function_index,
                                          const double contribution );

  // Initialize the moments maps
  template<typename InputEntityId>
  void initializeMomentsMaps( const std::vector<InputEntityId>& entity_ids );

  // Add info to update tracker
  void addInfoToUpdateTracker( const size_t thread_id,
                               const EntityId entity_id,
                               const size_t bin_index,
                               const double contribution );

  // Get entity iterators from update tracker
  void getEntityIteratorFromUpdateTracker(
	      const size_t thread_id,
	      typename SerialUpdateTracker::const_iterator& start_entity,
	      typename SerialUpdateTracker::const_iterator& end_entity ) const;

  // Get the bin iterator from an update tracker iterator
  void getBinIteratorFromUpdateTrackerIterator(
	   const size_t thread_id,
	   const typename SerialUpdateTracker::const_iterator& entity_iterator,
	   BinContributionMap::const_iterator& start_bin,
	   BinContributionMap::const_iterator& end_bin ) const;

  // Reset the update tracker
  void resetUpdateTracker( const size_t thread_id );

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The total estimator moments across all entities and response functions
  Estimator::FourEstimatorMomentsCollection d_total_estimator_moments;

  // The total estimator moments for each entity and response functions
  EntityEstimatorMomentsCollectionMap d_entity_total_estimator_moments_map;

  // The total estimator moment snapshots across all entities and resp. funcs.
  Estimator::FourEstimatorMomentsCollectionSnapshots d_total_estimator_moment_snapshots;

  // The total estimator moment snapshots for each entity and response func.
  EntityEstimatorMomentsCollectionSnapshotsMap d_entity_total_estimator_moment_snapshots_map;

  // The sample moment histograms across all entities and response functions
  SampleMomentHistogramArray d_total_estimator_histograms;

  // The total estimator moment histograms for each entity and response func.
  EntityEstimatorSampleMomentHistogramArrayMap d_entity_total_estimator_histograms_map;

  // The entities/bins that have been updated
  ParallelUpdateTracker d_update_tracker;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( StandardEntityEstimator, MonteCarlo, 0 );

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardEntityEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_ENTITY_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEntityEstimator.hpp
//---------------------------------------------------------------------------//
