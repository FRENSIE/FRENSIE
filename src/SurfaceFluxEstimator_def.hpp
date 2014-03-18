//---------------------------------------------------------------------------//
//!
//! \file   SurfaceFluxEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Surface flux estimator class definition
//!
//---------------------------------------------------------------------------//

#ifndef SURFACE_FLUX_ESTIMATOR_DEF_HPP
#define SURFACE_FLUX_ESTIMATOR_DEF_HPP

// FACEMC Includes
#include "ContractException.hpp"

namespace FACEMC{

// Initialize the static member data
double SurfaceFluxEstimator:angle_cosine_cutoff = 0.01;

// Set the angle cosine cutoff value
template<typename SurfaceId,typename ContributionMultiplierPolicy>
void SurfaceFluxEstimator<SurfaceId,
			  ContributionMultiplierPolicy>::setAngleCosineCutoff(
					     const double angle_cosine_cutoff )
{
  // Make sure the angle cosine cutoff is valid
  testPrecondition( angle_cosine_cutoff > 0.0 );
  testPrecondition( angle_cosine_cutoff < 1.0 );
  
  SurfaceFluxEstimator::angle_cosine_cutoff = angle_cosine_cutoff;
}

// Constructor
template<typename SurfaceId,typename ContributionMultiplierPolicy>
SurfaceFluxEstimator<SurfaceId,
		     ContributionMultiplierPolicy>::SurfaceFluxEstimator(
				  const unsigned long long id,
				  const double multiplier,
				  const Teuchos::Array<SurfaceId>& surface_ids,
				  const Teuchos::Array<double>& surface_areas )
  : StandardSurfaceEstimator( id, multiplier, surface_ids, surface_areas )
{ /* ... */ }

// Add estimator contribution from a portion of the current history
template<typename SurfaceId,typename ContributionMultiplierPolicy>
void SurfaceFluxEstimator<SurfaceId,
		  ContributionMultiplierPolicy>::addPartialHistoryContribution(
					    const BasicParticleState& particle,
					    const SurfaceId& surface_crossed,
					    const double angle_cosine )
{
  // Make sure the surface is assigned to this estimator
  testPrecondition( isEntityAssigned( surface_crossed ) );
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine <= 1.0 );
  testPrecondition( angle_cosine >= -1.0 );

  double contribution; 
  
  // If the angle cosine is very close to zero, set it to eps/2 to
  // prevent large contributions to the estimator
  if( ST::magnituce( angle_cosine ) >
      SurfaceFlusEstimator::angle_cosine_cutoff )
    contribution = 1.0/ST::magnitude( angle_cosine );
  else
    contribution = SurfaceFlusEstimator::angle_cosine_cutoff/2;
  
  contribution *= ContributionMultiplierPolicy::multiplier( particle );
  
  addPartialHistoryContribution( surface_crossed, 
				 particle, 
				 angle_cosine,
				 contribution );
}

// Print the estimator data
template<typename SurfaceId,typename ContributionMultiplierPolicy>
void SurfaceFluxEstimator<SurfaceId,
		 ContributionMultiplierPolicy>::print( std::ostream& os ) const
{
  os << "Surface Flux Estimator: " << getId() << std::endl;

  printImplementation( os, "Surface" );
}

} // end FACEMC namespace

#endif // end SURFACE_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end SurfaceFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
