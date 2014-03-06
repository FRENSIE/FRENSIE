//---------------------------------------------------------------------------//
//!
//! \file   CellCollisionFluxEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Cell collision flux estimator class definition.
//!
//---------------------------------------------------------------------------//

#ifndef CELL_COLLISION_FLUX_ESTIMATOR_DEF_HPP
#define CELL_COLLISION_FLUX_ESTIMATOR_DEF_HPP

// FACEMC Includes
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
template<typename CellID,typename ContributionMultiplierPolicy>
CellCollisionFluxEstimator<CellId,
		     ContributionMultiplierPolicy>::CellCollisionFluxEstimator(
						   const unsigned long long id,
						   const CellId& cell_id,
						   const double norm_constant,
						   const double multiplier )
  : CellEstimator( id, cell_id, norm_constant, multiplier )
{ /* ... */ }

// Calculate and add estimator contribution from a portion of the cur. hist.
/*! \details The raw contribution is 1 over the total macroscopic cross section
 * at the collision point inside of the cell associated with this estimator.
 */ 
template<typename CellID,typename ContributionMultiplierPolicy>
void CellCollisionFluxEstimator<CellId,
      ContributionMultiplierPolicy>::calculateAndAddPartialHistoryContribution(
					    const BasicParticleState& particle,
					    const double raw_contribution )
{
  // Make sure that the inverse macroscopic cross section value is valid
  testPrecondition( !ST::isnaninf( raw_contribution ) );
  testPrecondition( raw_contribution > 0.0 );

  double contribution = raw_contribution*
    ContributionMultiplierPolicy::multiplier( particle );

  // Assume a reference direction of (0,0,1) for calculating the angle cos bin
  StandardEstimator<CellId>::addPartialHistoryContribution( 
						    particle,
						    contribution,
						    particle.getZDirection() );
}

} // end FACEMC namespace

#endif // end CELL_COLLISION_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end CellCollisionFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
