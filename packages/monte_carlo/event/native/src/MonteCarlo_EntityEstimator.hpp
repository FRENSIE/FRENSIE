//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EntityEstimator.hpp
//! \author Alex Robinson
//! \brief  Entity estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ENTITY_ESTIMATOR_HPP
#define MONTE_CARLO_ENTITY_ESTIMATOR_HPP

// Std Lib Includes
#include <unordered_map>
#include <unordered_set>

// FRENSIE Includes
#include "MonteCarlo_Estimator.hpp"

namespace MonteCarlo{

//! The entity estimator class
template<typename EntityId>
class EntityEstimator : public Estimator
{

protected:

  // Typedef for the map of entity ids and esimator moments array
  typedef std::unordered_map<EntityId,TwoEstimatorMomentsCollection>
  EntityEstimatorMomentsCollectionMap;

  // Typedef for the entity norm constants map
  typedef std::unordered_map<EntityId,double> EntityNormConstMap;

public:

  //! Constructor (for flux estimators)
  template<template<typename,typename...> class STLCompliantArrayA,
           template<typename,typename...> class STLCompliantArrayB>
  EntityEstimator( const Estimator::idType id,
		   const double multiplier,
		   const STLCompliantArrayA<EntityId>& entity_ids,
		   const STLCompliantArrayB<double>& entity_norm_constants );

  //! Constructor (for non-flux estimators)
  template<typename<typename,typename...> class STLCompliantArray>
  EntityEstimator( const Estimator::idType id,
		   const double multiplier,
		   const STLCompliantArray<EntityId>& entity_ids );

  //! Destructor
  virtual ~EntityEstimator()
  { /* ... */ }

  //! Return the entity ids associated with this estimator
  template<template<typename,typename...> class STLCompliantSet>
  void getEntityIds( STLCompliantSet<EntityId>& entity_ids ) const;

  //! Check if the entity is assigned to this estimator
  bool isEntityAssigned( const EntityId& entity_id ) const;

  //! Return the normalization constant for an entity
  double getEntityNormConstant( const EntityId& entity_id ) const;

  //! Return the total normalization constant
  double getTotalNormConstant() const;

  //! Reset estimator data
  virtual void resetData() override;

  //! Reduce estimator data on all processes and collect on the root process
  virtual void reduceData(
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process ) override;

  //! Export the estimator data
  virtual void exportData(
                    const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                    const bool process_data ) const override;

protected:

  //! Constructor with no entities (for mesh estimators)
  EntityEstimator( const Estimator::idType id, const double multiplier );

  //! Assign entities
  virtual void assignEntities( const EntityNormConstMap& entity_norm_data );

  //! Assign discretization to an estimator dimension
  virtual void assignDiscretization(
    const Estimator::DimensionDiscretizationPointer& bin_boundaries ) override;

  //! Assign response function to the estimator
  virtual void assignResponseFunction(
        const Estimator::ResponseFunctionPointer& response_function ) override;

  //! Commit history contribution to a bin of an entity
  void commitHistoryContributionToBinOfEntity( const EntityId& entity_id,
					       const size_t bin_index,
					       const double contribution );

  //! Commit history contribution to a bin of total
  void commitHistoryContributionToBinOfTotal( const size_t bin_index,
					      const double contribution );

  //! Print the estimator data
  virtual void printImplementation( std::ostream& os,
				    const std::string& entity_type ) const;

  //! Get the total estimator bin data
  const Estimator::TwoEstimatorMomentsCollection& getTotalBinData() const;

  //! Get the bin data for an entity
  const Estimator::TwoEstimatorMomentsCollection& getEntityBinData(
					      const EntityId entity_id ) const;

private:

  // Initialize entity estimator moments map
  template<template<typename,typename...> class STLCompliantArray>
  void initializeEntityEstimatorMomentsMap(
                               const STLCompliantArray<EntityId>& entity_ids );

  // Initialize entity norm constants map
  template<template<typename,typename...> class STLCompliantArray>
  void initializeEntityNormConstantsMap(
                               const STLCompliantArray<EntityId>& entity_ids );

  // Initialize entity norm constants map
  template<template<typename,typename...> class STLCompliantArrayA,
           template<typename,typename...> class STLCompliantArrayB>
  void initializeEntityNormConstantsMap(
                     const STLCompliantArrayA<EntityId>& entity_ids,
                     const STLCompliantArrayB<double>& entity_norm_constants );

  // Calculate the total normalization constant
  void calculateTotalNormalizationConstant();

  // Resize the entity estimator moments map collections
  void resizeEntityEstimatorMapCollections();

  // Resize the estimator total collection
  void resizeEstimatorTotalCollection();

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

  // The estimator moments (1st,2nd) for each bin of the total
  TwoEstimatorMomentsCollection d_estimator_total_bin_data;

  // The estimator moments (1st,2nd) for each bin and each entity
  EntityEstimatorMomentsCollectionMap d_entity_estimator_moments_map;

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
