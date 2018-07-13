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
class EntityEstimator : public Estimator
{

protected:

  // Typedef for the map of entity ids and esimator moments array
  typedef std::unordered_map<uint64_t,TwoEstimatorMomentsCollection>
  EntityEstimatorMomentsCollectionMap;

  // Typedef for the entity norm constants map
  typedef std::unordered_map<uint64_t,double> EntityNormConstMap;

public:

  //! Constructor (for flux estimators)
  template<typename EntityId>
  EntityEstimator( const uint32_t id,
		   const double multiplier,
		   const std::vector<EntityId>& entity_ids,
		   const std::vector<double>& entity_norm_constants );

  //! Constructor (for non-flux estimators)
  template<typename EntityId>
  EntityEstimator( const uint32_t id,
		   const double multiplier,
		   const std::vector<EntityId>& entity_ids );

  //! Destructor
  virtual ~EntityEstimator()
  { /* ... */ }

  //! Return the entity ids associated with this estimator
  void getEntityIds( std::set<uint64_t>& entity_ids ) const final override;

  //! Check if the entity is assigned to this estimator
  bool isEntityAssigned( const uint64_t entity_id ) const final override;

  //! Return the normalization constant for an entity
  double getEntityNormConstant( const uint64_t entity_id ) const final override;

  //! Return the total normalization constant
  double getTotalNormConstant() const override;

  //! Get the total estimator bin data first moments
  Utility::ArrayView<const double> getTotalBinDataFirstMoments() const final override;

  //! Get the total estimator bin data second moments
  Utility::ArrayView<const double> getTotalBinDataSecondMoments() const final override;

  //! Get the bin data first moments for an entity
  Utility::ArrayView<const double> getEntityBinDataFirstMoments( const uint64_t entity_id ) const final override;

  //! Get the bin data second moments for an entity
  Utility::ArrayView<const double> getEntityBinDataSecondMoments( const uint64_t entity_id ) const final override;

  //! Reset estimator data
  void resetData() override;

  //! Reduce estimator data on all processes and collect on the root process
  void reduceData( const Utility::Communicator& comm,
                   const int root_process ) override;

protected:

  //! Default constructor
  EntityEstimator();

  //! Constructor with no entities (for mesh estimators)
  EntityEstimator( const uint32_t id, const double multiplier );

  //! Assign entities
  virtual void assignEntities( const EntityNormConstMap& entity_norm_data );

  //! Assign discretization to an estimator dimension
  void assignDiscretization( const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
                             const bool range_dimension ) override;

  //! Assign response function to the estimator
  void assignResponseFunction( const std::shared_ptr<const ParticleResponse>& response_function ) override;

  //! Commit history contribution to a bin of an entity
  void commitHistoryContributionToBinOfEntity( const uint64_t entity_id,
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
  const Estimator::TwoEstimatorMomentsCollection& getEntityBinData( const uint64_t entity_id ) const;

private:

  // Initialize entity estimator moments map
  template<typename EntityId>
  void initializeEntityEstimatorMomentsMap(
                                     const std::vector<EntityId>& entity_ids );

  // Initialize entity norm constants map
  template<typename EntityId>
  void initializeEntityNormConstantsMap(
                                     const std::vector<EntityId>& entity_ids );

  // Initialize entity norm constants map
  template<typename EntityId>
  void initializeEntityNormConstantsMap(
                            const std::vector<EntityId>& entity_ids,
                            const std::vector<double>& entity_norm_constants );

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

  // Serialize the entity estimator
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

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
