//---------------------------------------------------------------------------//
//!
//! \file   StandardEntityEstimator.hpp
//! \author Alex Robinson
//! \brief  Standard entity estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef STANDARD_ENTITY_ESTIMATOR_HPP
#define STANDARD_ENTITY_ESTIMATOR_HPP

// FACEMC Includes
#include "EntityEstimator.hpp"

namespace FACEMC{

//! The standard entity estimator class
template<typename EntityId>
class StandardEntityEstimator : public EntityEstimator<EntityId>
{

protected:

  // Typedef for the map of entity ids and estimator first moments
  typedef boost::unordered_map<EntityId,Teuchos::Array<double> > 
  EntityEstimatorFirstMomentsArrayMap;

public:

  //! Constructor
  StandardEntityEstimator( 
			 const unsigned long long id,
			 const double multiplier,
			 const Teuchos::Array<EntityId>& entity_ids,
			 const Teuchos::Array<double>& entity_norm_constants );

  //! Destructor
  virtual ~StandardEntityEstimator()
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

  //! Commit the contribution from the current history to the estimator
  void commitHistoryContribution();

protected:

  //! Add estimator contribution from a portion of the current history
  void addPartialHistoryContribution( const EntityId& entity_id,
				      const BasicParticleState& particle,
				      const double angle_cosine,
				      const double contribution );

  //! Print the estimator data
  void printImplementation( std::ostream& os,
			    const std::string& entity_type ) const;

private:

  // Resize the entity estimator first moment map arrays
  void resizeEntityEstimatorFirstMomentMapArrays();

  // Resize the entity total estimator moments map arrays
  void resizeEntityTotalEstimatorMapArrays();

  // Commit history contr. to the total for a response function of an entity
  void commitHistoryContributionToTotalOfEntity( 
					const EntityId& entity_id,
					const unsigned response_function_index,
					const double contribution );

  // Commit hist. contr. to the total for a response function of the estimator
  void commitHistoryContributionToTotalOfEstimator( 
					const unsigned response_function_index,
					const double contribution );

  // The total estimator moments across all entities and response functions
  EstimatorMomentsArray d_total_estimator_moments;

  // The total estimator moments for each entity and response functions
  EntityEstimatorMomentsArrayMap d_entity_total_estimator_moments_map;

  // The estimator first moment for each bin of the current history
  EntityEstimatorFirstMomentArrayMap 
  d_entity_current_history_first_moments_map;
}; 

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "StandardEntityEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end STANDARD_ENTITY_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end StandardEntityEstimator.hpp
//---------------------------------------------------------------------------//
