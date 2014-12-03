//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EntityEstimator.hpp
//! \author Alex Robinson
//! \brief  Entity estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ENTITY_ESTIMATOR_HPP
#define FACEMC_ENTITY_ESTIMATOR_HPP

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "MonteCarlo_Estimator.hpp"

namespace MonteCarlo{

//! The entity estimator class
template<typename EntityId>
class EntityEstimator : public Estimator
{

protected:

  // Typedef for the map of entity ids and esimator moments array
  typedef boost::unordered_map<EntityId,TwoEstimatorMomentsArray> 
  EntityEstimatorMomentsArrayMap;

  // Typedef for the entity norm constants map
  typedef boost::unordered_map<EntityId,double> EntityNormConstMap;

public:

  // Typedef for the set of entity ids
  typedef boost::unordered_set<EntityId> EntityIdSet;

  //! Constructor (for flux estimators)
  EntityEstimator( const Estimator::idType id,
		   const double multiplier,
		   const Teuchos::Array<EntityId>& entity_ids,
		   const Teuchos::Array<double>& entity_norm_constants );

  //! Constructor (for non-flux estimators)
  EntityEstimator( const Estimator::idType id,
		   const double multiplier,
		   const Teuchos::Array<EntityId>& entity_ids );

  //! Destructor
  virtual ~EntityEstimator()
  { /* ... */ }

  //! Set the response functions
  virtual void setResponseFunctions( 
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions );

  //! Return the entity ids associated with this estimator
  void getEntityIds( EntityIdSet& entity_ids ) const;

  //! Check if the entity is assigned to this estimator
  bool isEntityAssigned( const EntityId& entity_id ) const;

protected:

  //! Assign bin boundaries to an estimator dimension
  virtual void assignBinBoundaries(
	const Teuchos::RCP<EstimatorDimensionDiscretization>& bin_boundaries );

  //! Return the normalization constant for an entity
  double getEntityNormConstant( const EntityId& entity_id ) const;

  //! Return the total normalization constant
  double getTotalNormConstant() const;
  
  //! Commit history contribution to a bin of an entity 
  void commitHistoryContributionToBinOfEntity( const EntityId& entity_id,
					       const unsigned bin_index,
					       const double contribution );

  //! Print the estimator data
  virtual void printImplementation( std::ostream& os,
				    const std::string& entity_type ) const;

  //! Export the raw bin data
  void exportRawBinData(TwoEstimatorMomentsArray& raw_bin_data,
			Teuchos::Array<std::string>& response_function_names,
			Teuchos::Array<PhaseSpaceDimension> dimension_ordering,
			Teuchos::Array<unsigned> dimension_sizes,
			Teuchos::Array<std::string>& entity_names ) const;

  //! Import the raw bin data (this will overwrite the current data)
  void importRawBinData(
		  const TwoEstimatorMomentsArray& raw_bin_data,
		  const Teuchos::Array<std::string>& response_function_names,
		  const Teuchos::Array<PhaseSpaceDimension> dimension_ordering,
		  const Teuchos::Array<unsigned> dimension_sizes,
		  const Teuchos::Array<std::string>& entity_names,
		  const bool overwrite ) const;
  
private:

  // Initialize entity estimator moments map
  void initializeEntityEstimatorMomentsMap( 
				  const Teuchos::Array<EntityId>& entity_ids );

  // Initialize entity norm constants map
  void initializeEntityNormConstantsMap( 
			          const Teuchos::Array<EntityId>& entity_ids );

  // Initialize entity norm constants map
  void initializeEntityNormConstantsMap( 
			 const Teuchos::Array<EntityId>& entity_ids,
			 const Teuchos::Array<double>& entity_norm_constants );

  // Calculate the total normalization constant
  void calculateTotalNormalizationConstant();

  // Resize the entity estimator moments map arrays
  void resizeEntityEstimatorMapArrays();

  // Print the entity ids assigned to the estimator
  void printEntityIds( std::ostream& os,
		       const std::string& entity_type ) const;

  // Print the entity norm constants
  void printEntityNormConstants( std::ostream& os,
				 const std::string& entity_type ) const;

  // The total normalization constant (sum of all norm constants)
  double d_total_norm_constant;

  // Bool that records if entity norm constants were supplied
  bool d_supplied_norm_constants;

  // The estimator moments (1st,2nd) for each bin and each entity
  EntityEstimatorMomentsArrayMap d_entity_estimator_moments_map;
  
  // The entity normalization constants (surface areas or cell volumes)
  EntityNormConstMap d_entity_norm_constants_map;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_EntityEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end ENTITY_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end EntityEstimator.hpp
//---------------------------------------------------------------------------//
