//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardEntityEstimator.hpp
//! \author Alex Robinson
//! \brief  Standard entity estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_STANDARD_ENTITY_ESTIMATOR_HPP
#define FACEMC_STANDARD_ENTITY_ESTIMATOR_HPP

// Boost Includes
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_EntityEstimator.hpp"

namespace MonteCarlo{

//! The standard entity estimator class
template<typename EntityId>
class StandardEntityEstimator : public EntityEstimator<EntityId>
{

protected:

  // Typedef for Teuchos Scalar Traits
  typedef Teuchos::ScalarTraits<double> ST;

  // Typedef for the map of entity ids and estimator first moments
  typedef typename boost::unordered_map<EntityId,Teuchos::Array<double> > 
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
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions );

  //! Commit the contribution from the current history to the estimator
  void commitHistoryContribution();

  //! Export the estimator data
  virtual void exportData( EstimatorHDF5FileHandler& hdf5_file,
			   const bool process_data ) const;

protected:

  //! Assign bin boundaries to an estimator dimension
  virtual void assignBinBoundaries(
	const Teuchos::RCP<EstimatorDimensionDiscretization>& bin_boundaries );

  //! Add estimator contribution from a portion of the current history
  void addPartialHistoryContribution( const EntityId entity_id,
				      const ParticleState& particle,
				      const double angle_cosine,
				      const double contribution );

  //! Print the estimator data
  void printImplementation( std::ostream& os,
			    const std::string& entity_type ) const;

private:

  // Resize the entity estimator first moment map arrays
  void resizeEntityEstimatorFirstMomentsMapArrays();

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

  // The total estimator moments across all entities and response functions
  Estimator::FourEstimatorMomentsArray d_total_estimator_moments;

  // The total estimator moments for each entity and response functions
  EntityEstimatorMomentsArrayMap d_entity_total_estimator_moments_map;

  // The estimator first moment for each bin of the current history
  EntityEstimatorFirstMomentsArrayMap 
  d_entity_current_history_first_moments_map;

  // The generic particle state map (avoids having to make a new map for cont.)
  Estimator::DimensionValueMap d_dimension_values;
}; 

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardEntityEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_STANDARD_ENTITY_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEntityEstimator.hpp
//---------------------------------------------------------------------------//
