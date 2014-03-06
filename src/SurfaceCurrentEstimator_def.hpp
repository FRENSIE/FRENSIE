//---------------------------------------------------------------------------//
//!
//! \file   SurfaceCurrentEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Surface current estimator class definition
//!
//---------------------------------------------------------------------------//

#ifndef SURFACE_CURRENT_ESTIMATOR_DEF_HPP
#define SURFACE_CURRENT_ESTIMATOR_DEF_HPP

// FACEMC Includes
#include "ContractException.hpp"
#include "DirectionHelpers.hpp"

namespace FACEMC{

// Constructor
template<typename SurfaceId,typename ContributionMultiplierPolicy>
SurfaceCurrentEstimator<SurfaceId,
			ContributionMultiplierPolicy>::SurfaceCurrentEstimator(
						   const unsigned long long id,
						   const SurfaceId& surface_id,
						   const double norm_constant,
						   const double multiplier )
  : StandardEstimator<SurfaceId>( id, surface_id, norm_constant, multiplier )
{ /* ... */ }

// Calculate and add estimator contribution from a portion of the current hist.
/*! \details The contribution from this portion of the current history will
 * first be calculated. For a current estimator, this value is simply the
 * weight of the particle. For an energy current estimator, this value is
 * the weight of the particle multiplied by the particle energy. This function
 * will not multiply the contribution by the response function value. The 
 * reference direction will be used to calculate the cosine bin for the 
 * contribution. Once these two values have been calculated, the contribution
 * will be added to the other contributions from this history.
 */
template<typename SurfaceId,typename ContributionMultiplierPolicy>
void SurfaceCurrentEstimator<SurfaceId,
      ContributionMultiplierPolicy>::calculateAndAddPartialHistoryContribution(
					  const BasicParticleState& particle,
					  const double reference_direction[3] )
{
  // Make sure that the reference_direction is valid
  testPrecondition( validDirection( reference_direction ) );

  double angle_cosine = 
    calculateCosineOfAngleBetweenVectors( particle.getDirection(),
					  reference_direction );

  double contribution = ContributionMultiplierPolicy::multiplier( particle );

  // Add the contribution from this history
  StandardEstimator<SurfaceId>::addPartialHistoryContribution( particle, 
							       contribution, 
							       angle_cosine );
}

} // end FACEMC namespace

#endif // end SURFACE_CURRENT_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end SurfaceCurrentEstimator_def.hpp
//---------------------------------------------------------------------------//
