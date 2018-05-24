//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardEntityEstimator.hpp
//! \author Alex Robinson
//! \brief  Standard entity estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ENTITY_ESTIMATOR_HPP
#define MONTE_CARLO_STANDARD_ENTITY_ESTIMATOR_HPP

// Std Includes
#include <unordered_map>
#include <vector>

// FRENSIE Includes
#include "MonteCarlo_EntityEstimator.hpp"
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

private:

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
  template<template<typename,typename...> class STLCompliantArrayA,
           template<typename,typename...> class STLCompliantArrayB>
  StandardEntityEstimator(
                     const Estimator::idType id,
                     const double multiplier,
                     const STLCompliantArrayA<EntityId>& entity_ids,
		     const STLCompliantArrayB<double>& entity_norm_constants );

  //! Constructor (for non-flux estimators)
  template<typename<typename,typename...> class STLCompliantArray>
  StandardEntityEstimator( const Estimator::idType id,
			   const double multiplier,
			   const STLCompliantArray<EntityId>& entity_ids );

  //! Destructor
  virtual ~StandardEntityEstimator()
  { /* ... */ }

  //! Commit the contribution from the current history to the estimator
  void commitHistoryContribution() override;

  //! Enable support for multiple threads
  void enableThreadSupport( const unsigned num_threads ) override;

  //! Reset estimator data
  virtual void resetData() override;

  //! Reduce estimator data on all processes and collect on the root process
  void reduceData(
	    const std::shared_ptr<const Utility::Communicator<unsigned long long> >& comm,
	    const int root_process ) override;

protected:

  //! Constructor with no entities (for mesh estimators)
  StandardEntityEstimator( const Estimator::idType id,
                           const double multiplier );

  //! Assign entities
  void assignEntities(
                  const typename EntityEstimator<EntityId>::EntityNormConstMap&
                  entity_norm_data ) override;

  //! Assign response function to the estimator
  virtual void assignResponseFunction(
        const Estimator::ResponseFunctionPointer& response_function ) override;

  //! Print the estimator data
  void printImplementation( std::ostream& os,
			    const std::string& entity_type ) const override;


  //! Add estimator contribution from a point of the current history
  void addPartialHistoryPointContribution(
                   const EntityId entity_id,
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   const double contribution );

  //! Add estimator contribution from a range of the current history
  template<ObserverPhaseSpaceDimensions... RangeDimensions>
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
  template<template<typename,typename...> class STLCompliantArray>
  void initializeMomentsMaps( const STLCompliantArray<EntityId>& entity_ids );

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

  // The entities/bins that have been updated
  ParallelUpdateTracker d_update_tracker;

  // The total estimator moments across all entities and response functions
  Estimator::FourEstimatorMomentsCollection d_total_estimator_moments;

  // The total estimator moments for each entity and response functions
  EntityEstimatorMomentsCollectionMap d_entity_total_estimator_moments_map;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardEntityEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_ENTITY_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEntityEstimator.hpp
//---------------------------------------------------------------------------//
