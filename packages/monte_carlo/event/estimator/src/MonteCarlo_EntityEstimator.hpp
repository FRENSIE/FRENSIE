//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EntityEstimator.hpp
//! \author Alex Robinson
//! \brief  Entity estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ENTITY_ESTIMATOR_HPP
#define MONTE_CARLO_ENTITY_ESTIMATOR_HPP

// FRENSIE Includes
#include "MonteCarlo_Estimator.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"

namespace MonteCarlo{

//! The entity estimator class
class EntityEstimator : public Estimator
{

protected:

  //! Typedef for the map of entity ids and extended estimator moments array
  typedef std::unordered_map<EntityId,Estimator::FourEstimatorMomentsCollection>
  EntityEstimatorMomentsCollectionMap;

  //! Typedef for the map of entity ids and the estimator moments snapshots
  typedef std::unordered_map<EntityId,Estimator::FourEstimatorMomentsCollectionSnapshots>
  EntityEstimatorMomentsCollectionSnapshotsMap;

  //! Typedef for the sample moment histogram array
  typedef std::vector<Utility::SampleMomentHistogram<double> > SampleMomentHistogramArray;

  //! Typedef for the map of entity ids and the sample moment histogram array
  typedef std::unordered_map<EntityId,SampleMomentHistogramArray>
  EntityEstimatorSampleMomentHistogramArrayMap;

  //! Typedef for the entity norm constants map
  typedef std::unordered_map<EntityId,double> EntityNormConstMap;

public:

  //! Constructor (for flux estimators)
  template<typename InputEntityId>
  EntityEstimator( const Id id,
		   const double multiplier,
		   const std::vector<InputEntityId>& entity_ids,
		   const std::vector<double>& entity_norm_constants );

  //! Constructor (for non-flux estimators)
  template<typename InputEntityId>
  EntityEstimator( const Id id,
		   const double multiplier,
		   const std::vector<InputEntityId>& entity_ids );

  //! Destructor
  virtual ~EntityEstimator()
  { /* ... */ }

  //! Return the entity ids associated with this estimator
  void getEntityIds( std::set<EntityId>& entity_ids ) const final override;

  //! Check if the entity is assigned to this estimator
  bool isEntityAssigned( const EntityId entity_id ) const final override;

  //! Return the normalization constant for an entity
  double getEntityNormConstant( const EntityId entity_id ) const final override;

  //! Return the total normalization constant
  double getTotalNormConstant() const override;

  //! Get the total estimator bin data first moments
  Utility::ArrayView<const double> getTotalBinDataFirstMoments() const final override;

  //! Get the total estimator bin data second moments
  Utility::ArrayView<const double> getTotalBinDataSecondMoments() const final override;

  //! Get the total estimator bin data third moments
  Utility::ArrayView<const double> getTotalBinDataThirdMoments() const final override;

  //! Get the total estimator bin data fourth moments
  Utility::ArrayView<const double> getTotalBinDataFourthMoments() const final override;

  //! Get the bin data first moments for an entity
  Utility::ArrayView<const double> getEntityBinDataFirstMoments( const EntityId entity_id ) const final override;

  //! Get the bin data second moments for an entity
  Utility::ArrayView<const double> getEntityBinDataSecondMoments( const EntityId entity_id ) const final override;

  //! Get the bin data third moments for an entity
  Utility::ArrayView<const double> getEntityBinDataThirdMoments( const EntityId entity_id ) const final override;

  //! Get the bin data fourth moments for an entity
  Utility::ArrayView<const double> getEntityBinDataFourthMoments( const EntityId entity_id ) const final override;

  //! Enable snapshots on entity bins
  void enableSnapshotsOnEntityBins() final override;
  
  //! Check if snapshots have been enabled on entity bins
  bool areSnapshotsOnEntityBinsEnabled() const final override;

  //! Take a snapshot (of the moments)
  void takeSnapshot( const uint64_t num_histories_since_last_snapshot,
                     const double time_since_last_snapshot ) override;

  //! Get the entity bin moment snapshot history values
  void getEntityBinMomentSnapshotHistoryValues(
                  const EntityId entity_id,
                  std::vector<uint64_t>& history_values ) const final override;

  //! Get the entity bin moment snapshot sampling times
  void getEntityBinMomentSnapshotSamplingTimes(
                    const EntityId entity_id,
                    std::vector<double>& sampling_times ) const final override;
  
  //! Get the bin data first moment snapshots for an entity bin index
  void getEntityBinFirstMomentSnapshots(
                           const EntityId entity_id,
                           const size_t bin_index,
                           std::vector<double>& moments ) const final override;

  //! Get the bin data second moment snapshots for an entity bin index
  void getEntityBinSecondMomentSnapshots(
                           const EntityId entity_id,
                           const size_t bin_index,
                           std::vector<double>& moments ) const final override;

  //! Get the bin data third moment snapshots for an entity bin index
  void getEntityBinThirdMomentSnapshots(
                           const EntityId entity_id,
                           const size_t bin_index,
                           std::vector<double>& moments ) const final override;

  //! Get the bin data fourth moment snapshots for an entity bin index
  void getEntityBinFourthMomentSnapshots(
                           const EntityId entity_id,
                           const size_t bin_index,
                           std::vector<double>& moments ) const final override;

  //! Get the moment snapshot history values
  void getTotalBinMomentSnapshotHistoryValues(
                  std::vector<uint64_t>& history_values ) const final override;

  //! Get the moment snapshot sampling times for a total bin index
  void getTotalBinMomentSnapshotSamplingTimes(
                    std::vector<double>& sampling_times ) const final override;

  //! Get the bin data first moment snapshots for an total bin index
  void getTotalBinFirstMomentSnapshots(
                           const size_t bin_index,
                           std::vector<double>& moments ) const final override;

  //! Get the bin data second moment snapshots for an total bin index
  void getTotalBinSecondMomentSnapshots(
                           const size_t bin_index,
                           std::vector<double>& moments ) const final override;

  //! Get the bin data third moment snapshots for an total bin index
  void getTotalBinThirdMomentSnapshots(
                           const size_t bin_index,
                           std::vector<double>& moments ) const final override;

  //! Get the bin data fourth moment snapshots for an total bin index
  void getTotalBinFourthMomentSnapshots(
                           const size_t bin_index,
                           std::vector<double>& moments ) const final override;

  //! Enable sample moment histograms on entity bins
  void enableSampleMomentHistogramsOnEntityBins() final override;

  //! Check if sample moment histograms are enabled on on entity bins
  bool areSampleMomentHistogramsOnEntityBinsEnabled() const final override;

  //! Get the entity bin sample moment histogram
  void getEntityBinSampleMomentHistogram(
      const EntityId entity_id,
      const size_t bin_index,
      Utility::SampleMomentHistogram<double>& histogram ) const final override;

  //! Get the total bin sample moment histogram
  void getTotalBinSampleMomentHistogram(
      const size_t bin_index,
      Utility::SampleMomentHistogram<double>& histogram ) const final override;

  //! Reset estimator data
  void resetData() override;

  //! Reduce estimator data on all processes and collect on the root process
  void reduceData( const Utility::Communicator& comm,
                   const int root_process ) override;

protected:

  //! Default constructor
  EntityEstimator();

  //! Constructor with no entities (for mesh estimators)
  EntityEstimator( const Id id,
                   const double multiplier );

  //! Assign entities
  virtual void assignEntities( const EntityNormConstMap& entity_norm_data );

  //! Assign discretization to an estimator dimension
  void assignDiscretization( const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
                             const bool range_dimension ) override;

  //! Assign response function to the estimator
  void assignResponseFunction( const std::shared_ptr<const ParticleResponse>& response_function ) override;

  //! Assign the history score pdf bins
  void assignSampleMomentHistogramBins( const std::shared_ptr<const std::vector<double> >& bins ) override;

  //! Commit history contribution to a bin of an entity
  void commitHistoryContributionToBinOfEntity( const EntityId entity_id,
					       const size_t bin_index,
					       const double contribution );

  //! Commit history contribution to a bin of total
  void commitHistoryContributionToBinOfTotal( const size_t bin_index,
					      const double contribution );

  //! Print the estimator data
  virtual void printImplementation( std::ostream& os,
				    const std::string& entity_type ) const;

  //! Get the total estimator bin data
  const Estimator::FourEstimatorMomentsCollection& getTotalBinData() const;

  //! Get the bin data for an entity
  const Estimator::FourEstimatorMomentsCollection& getEntityBinData( const EntityId entity_id ) const;

  //! Reduce the entity collection maps
  void reduceEntityCollectionMaps(
                   const Utility::Communicator& comm,
                   const int root_process,
                   EntityEstimatorMomentsCollectionMap& collection_map ) const;

  //! Reduce the entity snapshot maps
  void reduceEntitySnapshotMaps(
            const Utility::Communicator& comm,
            const int root_process,
            EntityEstimatorMomentsCollectionSnapshotsMap& snapshot_map ) const;

  //! Reduce the entity histogram maps
  void reduceEntityHistogramMaps(
           const Utility::Communicator& comm,
           const int root_process,
           EntityEstimatorSampleMomentHistogramArrayMap& histogram_map ) const;

  //! Reduce the histogram arrays
  void reduceHistogramArrays(
                           const Utility::Communicator& comm,
                           const int root_process,
                           SampleMomentHistogramArray& histogram_array ) const;

private:

  // Initialize entity estimator moments map
  template<typename InputEntityId>
  void initializeEntityEstimatorMomentsMap(
                                  const std::vector<InputEntityId>& entity_ids,
                                  const bool warn_duplicate_ids );

  // Initialize entity estimator snapshots map
  void initializeEntityEstimatorSnapshotsMap();

  // Initialize entity entity estimator histograms map
  void initializeEntityEstimatorHistogramsMap();

  // Initialize entity norm constants map
  template<typename InputEntityId>
  void initializeEntityNormConstantsMap(
                                const std::vector<InputEntityId>& entity_ids );

  // Initialize entity norm constants map
  template<typename InputEntityId>
  void initializeEntityNormConstantsMap(
                            const std::vector<InputEntityId>& entity_ids,
                            const std::vector<double>& entity_norm_constants );

  // Calculate the total normalization constant
  void calculateTotalNormalizationConstant();

  // Resize the entity estimator moments map collections
  void resizeEntityEstimatorMapCollections();

  // Resize the estimator total collection
  void resizeEstimatorTotalCollection();

  // Resize the entity estimator snapshots
  void resizeEntityEstimatorMapSnapshots();

  // Resize the estimator total snapshots
  void resizeEstimatorTotalSnapshots();

  // Resize the entity estimator histograms
  void resizeEntityEstimatorMapHistograms();

  // Resize the estimator total histograms
  void resizeEstimatorTotalHistograms();

  // Add contribution to entity bin histogram
  void addHistoryContributionToEntityBinHistogram( const EntityId entity_id,
                                                   const size_t bin_index,
                                                   const double contribution );

  // Add contribution to total bin histogram
  void addHistoryContributionToTotalBinHistogram( const size_t bin_index,
                                                  const double contribution );

  // Reduce the entity collections
  void reduceEntityCollections(
                   const std::vector<EntityEstimatorMomentsCollectionMap>&
                   other_entity_estimator_moments_maps,
                   const size_t root_index,
                   EntityEstimatorMomentsCollectionMap& collection_map ) const;

  // Reduce the entity snapshots
  void reduceEntitySnapshots(
           const std::vector<EntityEstimatorMomentsCollectionSnapshotsMap>&
           gathered_entity_data,
           const size_t root_index,
           EntityEstimatorMomentsCollectionSnapshotsMap& snapshots_map ) const;

  // Reduce the entity histograms
  void reduceEntityHistograms(
           const std::vector<EntityEstimatorSampleMomentHistogramArrayMap>&
           gathered_entity_data,
           const size_t root_index,
           EntityEstimatorSampleMomentHistogramArrayMap& histogram_map ) const;

  // Reduce the entity histograms
  void reduceEntityHistograms(
                           const std::vector<SampleMomentHistogramArray>&
                           gathered_entity_data,
                           const size_t root_index,
                           SampleMomentHistogramArray& histogram_array ) const;

  // Print the entity ids assigned to the estimator
  void printEntityIds( std::ostream& os,
		       const std::string& entity_type ) const;

  // Print the entity norm constants
  void printEntityNormConstants( std::ostream& os,
				 const std::string& entity_type ) const;

  // Serialize the entity estimator
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The total normalization constant (sum of all norm constants)
  double d_total_norm_constant;

  // Bool that records if entity norm constants were supplied
  bool d_supplied_norm_constants;

  // The estimator moments (1st,2nd,3rd,4th) for each bin of the total
  FourEstimatorMomentsCollection d_estimator_total_bin_data;

  // The estimator moments (1st,2nd,3rd,4th) for each bin and each entity
  EntityEstimatorMomentsCollectionMap d_entity_estimator_moments_map;

  // Bool that record if entity bin moment snapshots have been enabled
  bool d_entity_bin_snapshots_enabled;

  // The estimator moments (1st,2nd,3rd,4th) snapshots for each bin of the
  // total
  FourEstimatorMomentsCollectionSnapshots d_estimator_total_bin_data_snapshots;

  // The estimator moments (1st,2nd,3rd,4th) snapshots for each bin and
  // each entity
  EntityEstimatorMomentsCollectionSnapshotsMap d_entity_estimator_moments_snapshots_map;

  // Bool that records if entity bin histograms have been enabled
  bool d_entity_bin_histograms_enabled;

  // The sample moment histograms for each bin of the total
  SampleMomentHistogramArray d_estimator_total_bin_histograms;

  // The estimator sample moment histograms for each bin and each
  // entity
  EntityEstimatorSampleMomentHistogramArrayMap d_entity_estimator_histograms_map;

  // The entity normalization constants (surface areas or cell volumes)
  EntityNormConstMap d_entity_norm_constants_map;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( EntityEstimator, MonteCarlo, 0 );

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_EntityEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end ENTITY_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end EntityEstimator.hpp
//---------------------------------------------------------------------------//
