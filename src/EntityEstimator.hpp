//---------------------------------------------------------------------------//
//!
//! \file   EntityEstimator.hpp
//! \author Alex Robinson
//! \brief  Entity estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef ENTITY_ESTIMATOR_HPP
#define ENTITY_ESTIMATOR_HPP

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// FACEMC Includes
#include "Estimator.hpp"
#include "Tuple.hpp"

namespace FACEMC{

//! The entity estimator class
template<typename EntityId>
class EntityEstimator : public Estimator
{

protected:

  // Typedef for the map of entity ids and esimator moments array
  typedef boost::unordered_map<EntityId,EstimatorMomentsArray> 
  EntityEstimatorMomentsArrayMap;

public:

  //! Typedef for entity id set
  typedef boost::unordered_set<EntityId> EntityIdSet;

  //! Constructor (for flux estimators)
  EntityEstimator( const unsigned long long id,
		   const double multiplier,
		   const Teuchos::Array<EntityId>& entity_ids,
		   const Teuchos::Array<double>& entity_norm_constants );

  //! Constructor (used by non-flux estimators)
  EntityEstimator( const unsigned long long id,
		   const double multiplier,
		   const Teuchos::Array<EntityId>& entity_ids );

  //! Destructor
  virtual ~EntityEstimator()
  { /* ... */ }

  //! Set the energy bin boundaries
  virtual void setEnergyBinBoundaries( 
			 const Teuchos::Array<double>& energy_bin_boundaries );

  //! Set the cosine bin boundaries
  virtual void setCosineBinBoundaries(
			 const Teuchos::Array<double>& cosine_bin_boundaries );

  //! Set the time bin boundaries
  virtual void setTimeBinBoundaries(
			   const Teuchos::Array<double>& time_bin_boundaries );

  //! Set the collision number bins
  virtual void setCollisionNumberBins( 
		       const Teuchos::Array<unsigned>& collision_number_bins );

  //! Set the response functions
  virtual void setResponseFunctions( 
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions );

  //! Return the entity ids associated with this estimator
  const EntityIdSet& getEntityIds() const;

  //! Check if the entity is assigned to this estimator
  bool isEntityAssigned( const EntityId& entity_id ) const;

protected:

  //! Return the normalization constant for an entity
  double getEntityNormConstant( const EntityId& entity_id ) const;

  //! Return the total normalization constant
  double getTotalNormConstant() const;

  //! Commit history contribution to a bin of an entity 
  void commitHistoryContributionToBinOfEntity( const EntityId& entity_id,
					       const unsigned bin_index,
					       const double contribution );

  //! Print the estimator data
  void printImplementation( std::ostream& os,
			    const std::string& entity_type ) const;
  
private:

  // Initialize entity ids and entity moment map
  void initializeEntityIds( const Teuchos::Array<EntityId>& entity_ids );

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

  // The total normalization constant (sum of all norm constants)
  double d_total_norm_constant;

  // The estimator moments (1st,2nd,3rd,4th) for each bin and each entity
  EntityEstimatorMomentsArrayMap d_entity_estimator_moments_map;
  
  // The entity normalization constants (surface areas or cell volumes)
  boost::unordered_map<EntityId,double> d_entity_norm_constants_map;
  
  // The set of all entity ids assigned to this estimator (used for quick ref.)
  boost::unordered_set<EntityId> d_entity_ids;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "EntityEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end ENTITY_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end EntityEstimator.hpp
//---------------------------------------------------------------------------//
