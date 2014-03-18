//---------------------------------------------------------------------------//
//!
//! \file   CellCollisionFluxEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Cell collision flux estimator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CELL_COLLISION_FLUX_ESTIMATOR_DEF_HPP
#define CELL_COLLISION_FLUX_ESTIMATOR_DEF_HPP

// Std Lib Includes
#include <iostream>

// FACEMC Includes
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
template<typename CellId,typename ContributionMultiplierPolicy>
CellCollisionFluxEstimator<CellId,
		     ContributionMultiplierPolicy>::CellCollisionFluxEstimator(
				   const unsigned long long id,
				   const double multiplier,
				   const Teuchos::Array<CellId>& cell_ids,
			           const Teuchos::Array<double>& cell_volumes )
  : StandardEntityEstimator<EntityId>( id,
				       multiplier,
				       cell_ids,
				       cell_volumes )
{ /* ... */ }

// Set the cosine bin boundaries
template<typename CellId,typename ContributionMultiplierPolicy>
void CellCollisionFluxEstimator<CellId,
			 ContributionMultiplierPolicy>::setCosineBinBoundaries(
			  const Teuchos::Array<double>& cosine_bin_boundaries )
{
  std::cerr << "Warning: Cosine bins cannot be set for cell collision flux "
	    << "estimators. The cosine bins requested for cell collision "
	    << "flux estimator " << getId() < " will be ignored."
	    << std::endl;
}

// Set the particle types that can contribute to the estimator
/*! \details Photons, electrons and neutrons (or their adjoint
 * couterparts) can contribute to the estimator. Combinations are not 
 * allowed.
 */
template<typename CellId,typename ContributionMultiplierPolicy>
void CellCollisionFluxEstimator<CellId,
			       ContributionMultiplierPolicy>::setParticleTypes(
			   const Teuchos::Array<ParticleType>& particle_types )
{
  // Make sure only one particle type has been specified
  testPrecondition( particle_types.size() == 1 );

  Estimator::setParticleTypes( particle_types );
}

// Add estimator contribution from a portion of the current history
template<typename CellId,typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<CellId,
		  ContributionMultiplierPolicy>::addPartialHistoryContribution(
				     const BasicParticleState& particle,
				     const CellId& cell_of_collision,
				     const double inverse_total_cross_section )
{
  // Make sure the cell is assigned to this estimator
  testPrecondition( isEntityAssigned( cell_of_collision ) );
  // Make sure the inverse total macroscopic cross section is valid
  testPrecondition( !ST::isnaninf( inverse_total_cross_section ) );
  
  double contribution = inverse_total_cross_section*
    ContributionMultiplierPolicy::multiplier( particle );

  addPartialHistoryContribution( cell_of_collision, 
				 particle, 
				 0, 
				 contribution );
}

// Print the estimator data
template<typename CellId,typename ContributionMultiplierPolicy>
void CellTrackCollisionEstimator<CellId,
		 ContributionMultiplierPolicy>::print( std::ostream& os ) const
{
  os << "Cell Collision Estimator: " << getId() << std::endl;

  printImplementation( os, "Cell" );
}

} // end FACEMC namespace

#endif // end CELL_COLLISION_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end CellCollisionFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
