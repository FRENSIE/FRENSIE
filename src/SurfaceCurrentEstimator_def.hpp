//---------------------------------------------------------------------------//
//!
//! \file   SurfaceCurrentEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Surface current estimator class definition
//!
//---------------------------------------------------------------------------//

#ifndef SURFACE_CURRENT_ESTIMATOR_DEF_HPP
#define SURFACE_CURRENT_ESTIMATOR_DEF_HPP

// Std Lib Includes
#include <iostream>

// FACEMC Includes
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
template<typename SurfaceId,typename ContributionMultiplierPolicy>
SurfaceCurrentEstimator<SurfaceId,
			ContributionMultiplierPolicy>::SurfaceCurrentEstimator(
				  const unsigned long long id,
				  const double multiplier,
				  const Teuchos::Array<SurfaceId>& surface_ids,
			          const Teuchos::Array<double>& surface_areas )
  : StandardEntityEstimator<SurfaceId>( id,
					multiplier,
					surface_ids,
					surface_areas )
{ /* ... */ }

// Set the response functions
template<typename SurfaceId,typename ContributionMultiplierPolicy>
void SurfaceCurrentEstimator<SurfaceId,
			   ContributionMultiplierPolicy>::setResponseFunctions(
    const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions )
{
  std::cerr << "Warning: Response functions cannot be set for surface current "
	    << "estimators. The response functions requested for surface "
	    << "current estimator " << getId() << " will be ignored."
	    << std::endl;
}

// Add estimator contribution from a portion of the current history
template<typename SurfaceId,typename ContributionMultiplierPolicy>
void SurfaceCurrentEstimator<SurfaceId,
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
  
  double contribution = 
    ContributionMultiplierPolicy::multiplier( particle );
  
  addPartialHistoryContribution( surface_crossed, 
				 particle, 
				 angle_cosine,
				 contribution );
}

// Print the estimator data
template<typename SurfaceId,typename ContributionMultiplierPolicy>
void SurfaceCurrentEstimator<SurfaceId,
		 ContributionMultiplierPolicy>::print( std::ostream& os ) const
{
  os << "Surface Current Estimator: " << getId() << std::endl;

  printImplementation( os, "Surface" );
}

} // end FACEMC namespace

#endif // end SURFACE_CURRENT_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// SurfaceCurrentEstimator_def.hpp
//---------------------------------------------------------------------------//
