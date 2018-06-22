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
template<typename EntityId>
class StandardEntityEstimator : public EntityEstimator<EntityId>
{
  // Typedef for the base type
  typedef EntityEstimator<EntityId> BaseEstimatorType;
  
  // Typedef for bin contribution map
  typedef std::unordered_map<unsigned,double> BinContributionMap;

  // Typedef for serial update tracker
  typedef std::unordered_map<EntityId,BinContributionMap> SerialUpdateTracker;

  // Typedef for parallel update tracker
  typedef std::vector<SerialUpdateTracker> ParallelUpdateTracker;

protected:

  //! Typedef for the map of entity ids and estimator moments array
  typedef std::unordered_map<EntityId,Estimator::FourEstimatorMomentsCollection>
  EntityEstimatorMomentsCollectionMap;

public:

  //! Constructor (for flux estimators)
  StandardEntityEstimator(
                     const Estimator::idType id,
                     const double multiplier,
                     const std::vector<EntityId>& entity_ids,
		     const std::vector<double>& entity_norm_constants );

  //! Constructor (for non-flux estimators)
  StandardEntityEstimator( const Estimator::idType id,
			   const double multiplier,
			   const std::vector<EntityId>& entity_ids );

  //! Destructor
  virtual ~StandardEntityEstimator()
  { /* ... */ }

  //! Commit the contribution from the current history to the estimator
  void commitHistoryContribution() final override;

  //! Enable support for multiple threads
  void enableThreadSupport( const unsigned num_threads ) final override;

  //! Reset estimator data
  void resetData() final override;

  //! Reduce estimator data on all processes and collect on the root process
  void reduceData( Utility::Communicator& comm,
                   const int root_process ) final override;

protected:

  //! Default constructor
  StandardEntityEstimator();

  //! Constructor with no entities (for mesh estimators)
  StandardEntityEstimator( const Estimator::idType id,
                           const double multiplier );

  //! Assign entities
  void assignEntities( const typename BaseEstimatorType::EntityNormConstMap&
                       entity_norm_data ) override;

  //! Assign response function to the estimator
  virtual void assignResponseFunction( const std::shared_ptr<const Response>& response_function );

  //! Print the estimator data
  void printImplementation( std::ostream& os,
			    const std::string& entity_type ) const final override;


  //! Add estimator contribution from a point of the current history
  void addPartialHistoryPointContribution(
                   const EntityId entity_id,
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   const double contribution );

  //! Add estimator contribution from a range of the current history
  void addParticleHistoryRangeContribution(
                   const EntityId entity_id,
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
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
					const EntityId& entity_id,
					const unsigned response_function_index,
					const double contribution );

  // Commit hist. contr. to the total for a response function of the estimator
  void commitHistoryContributionToTotalOfEstimator(
					const unsigned response_function_index,
					const double contribution );

  // Initialize the moments maps
  void initializeMomentsMaps( const std::vector<EntityId>& entity_ids );

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

  // The entities/bins that have been updated
  ParallelUpdateTracker d_update_tracker;

  // The total estimator moments across all entities and response functions
  Estimator::FourEstimatorMomentsCollection d_total_estimator_moments;

  // The total estimator moments for each entity and response functions
  EntityEstimatorMomentsCollectionMap d_entity_total_estimator_moments_map;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS1_VERSION( EntityEstimator, MonteCarlo, 0 );

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardEntityEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_ENTITY_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEntityEstimator.hpp
//---------------------------------------------------------------------------//
