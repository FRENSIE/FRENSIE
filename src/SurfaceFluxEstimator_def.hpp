//---------------------------------------------------------------------------//
//!
//! \file   SurfaceFluxEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Surface flux estimator class definition.
//!
//---------------------------------------------------------------------------//

#ifndef SURFACE_FLUX_ESTIMATOR_DEF_HPP
#define SURFACE_FLUX_ESTIMATOR_DEF_HPP

// FACEMC Includes
#include "ContractException.hpp"
#include "DirectionHelpers.hpp"

namespace FACEMC{

// Initialize the static member data
double SurfaceFluxEstimator::angle_cosine_cutoff = 0.01;


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
 * first be calculated. For a flux estimator, this value is simply the
 * weight of the particle divided by the absolute value of the cosine of the
 * angle between the particle direction and the reference direction (surface 
 * normal). For an energy flux estimator, this value is the weight of the 
 * particle multiplied by the particle energy and divided by the absolute 
 * value of the cosine of the angle between the particle direction and the 
 * reference direction (surface normal). This function will not multiply the 
 * contribution by the response function value. The reference direction will 
 * also be used to calculate the cosine bin for the contribution. Once these 
 * two values have been calculated, the contribution will be added to the 
 * other contributions from this history.
 */
template<typename SurfaceId,typename ContributionMultiplierPolicy>
void SurfaceFluxEstimator<SurfaceId,
      ContributionMultiplierPolicy>::calculateAndAddPartialHistoryContribution(
					  const BasicParticleState& particle,
					  const double reference_direction[3] )
{
  // Make sure that the reference direction is valid
  testPrecondition( validDirection( reference_direction ) );

  double angle_cosine = 
    calculateCosineOfAngleBetweenVectors( particle.getDirection(),
					  reference_direction );

  double contribution = ST::magnitude( angle_cosine );
  
  // If the angle cosine is very close to zero, set it to eps/2 to prevent
  // large contributions to the estimator
  if( contribution < SurfaceFlusEstimator::angle_cosine_cutoff )
    contribution = SurfaceFlusEstimator::angle_cosine_cutoff/2;
  
  contribution *= ContributionMultiplierPolicy::multiplier( particle );

  // Add the contribution from this history
  StandardEstimator<SurfaceId>::addPartialHistoryContribution( particle,
							       contribution,
							       angle_cosine );
}

// Set the angle cosine cutoff value
/*! This value will be used to prevent very large estimator contributions when
 * the angle cosine is very close to zero. The default value is 0.01. 
 */ 
template<typename SurfaceId,typename ContributionMultiplierPolicy>
void SurfaceFluxEstimator<SurfaceId,
			  ContributionMultiplierPolicy>::setAngleCosineCutoff( 
					     const double angle_cosine_cutoff )
{
  SurfaceFluxEstimator::angle_cosine_cutoff = angle_cosine_cutoff;
}

} // end FACEMC namespace

#endif // end SURFACE_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end SurfaceFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
