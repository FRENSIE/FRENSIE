//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardEntityEstimator.hpp
//! \author Alex Robinson
//! \brief  Standard entity estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ENTITY_ESTIMATOR_HPP
#define MONTE_CARLO_STANDARD_ENTITY_ESTIMATOR_HPP

// Boost Includes
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_TwoDArray.hpp>

// FRENSIE Includes
#include "MonteCarlo_EntityEstimator.hpp"

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
  typedef boost::unordered_map<unsigned,double> BinContributionMap;

  // Typedef for serial update tracker
  typedef typename boost::unordered_map<EntityId,BinContributionMap>
  SerialUpdateTracker;

  // Typedef for parallel update tracker 
  typedef typename Teuchos::Array<SerialUpdateTracker>
  ParallelUpdateTracker;

protected:

  // Typedef for Teuchos Scalar Traits
  typedef Teuchos::ScalarTraits<double> ST;

  // Typedef for the map of entity ids and estimator first moments
  typedef typename boost::unordered_map<EntityId,Teuchos::TwoDArray<double> > 
  EntityEstimatorFirstMomentsArrayMap;

  // Typedef for the map of entity ids and estimator moments array
  typedef typename boost::unordered_map<EntityId,
					Estimator::FourEstimatorMomentsArray>
  EntityEstimatorMomentsArrayMap;

public:

  //! Constructor (for flux estimators)
  StandardEntityEstimator( 
			 const Estimator::idType id,
			 const double multiplier,
			 const Teuchos::Array<EntityId>& entity_ids,
			 const Teuchos::Array<double>& entity_norm_constants );

  //! Constructor (for non-flux estimators)
  StandardEntityEstimator( const Estimator::idType id,
			   const double multiplier,
			   const Teuchos::Array<EntityId>& entity_ids );

  //! Destructor
  virtual ~StandardEntityEstimator()
  { /* ... */ }

  //! Set the response functions
  virtual void setResponseFunctions( 
                      const Teuchos::Array<std::shared_ptr<ResponseFunction> >&
                      response_functions );

  //! Commit the contribution from the current history to the estimator
  void commitHistoryContribution();

  //! Enable support for multiple threads
  void enableThreadSupport( const unsigned num_threads );

  //! Reset estimator data
  virtual void resetData();

  //! Reduce estimator data on all processes and collect on the root process
  void reduceData(
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process );

  //! Export the estimator data
  virtual void exportData( 
                    const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                    const bool process_data ) const;
  
protected:

  //! Constructor with no entities (for mesh estimators)
  StandardEntityEstimator( const Estimator::idType id,
			   const double multiplier );

  //! Assign entities
  void assignEntities( 
	       const boost::unordered_map<EntityId,double>& entity_norm_data );
  

  //! Add estimator contribution from a portion of the current history
  void addPartialHistoryContribution( 
                   const EntityId entity_id,
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   const double contribution );

  //! Print the estimator data
  void printImplementation( std::ostream& os,
			    const std::string& entity_type ) const;

  //! Get the total estimator data
  const Estimator::FourEstimatorMomentsArray& getTotalData() const;

  //! Get the total data for an entity
  const Estimator::FourEstimatorMomentsArray& 
  getEntityTotalData( const EntityId entity_id ) const;

private:

  // Resize the entity total estimator moments map arrays
  void resizeEntityTotalEstimatorMomentsMapArrays();

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
  void initializeMomentsMaps( const Teuchos::Array<EntityId>& entity_ids );

  // Add info to update tracker
  void addInfoToUpdateTracker( const unsigned thread_id,
			       const EntityId entity_id,
			       const unsigned bin_index,
			       const double contribution );

  // Get entity iterators from update tracker
  void getEntityIteratorFromUpdateTracker( 
	      const unsigned thread_id,
	      typename SerialUpdateTracker::const_iterator& start_entity,
	      typename SerialUpdateTracker::const_iterator& end_entity ) const;

  // Get the bin iterator from an update tracker iterator
  void getBinIteratorFromUpdateTrackerIterator(
	   const unsigned thread_id,
	   const typename SerialUpdateTracker::const_iterator& entity_iterator,
	   BinContributionMap::const_iterator& start_bin,
	   BinContributionMap::const_iterator& end_bin ) const;
	
  // Reset the update tracker
  void resetUpdateTracker( const unsigned thread_id );

  // The entities/bins that have been updated
  ParallelUpdateTracker d_update_tracker;

  // The total estimator moments across all entities and response functions
  Estimator::FourEstimatorMomentsArray d_total_estimator_moments;

  // The total estimator moments for each entity and response functions
  EntityEstimatorMomentsArrayMap d_entity_total_estimator_moments_map;
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
