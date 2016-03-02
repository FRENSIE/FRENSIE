//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SurfaceFluxEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Surface flux estimator class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SURFACE_FLUX_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_SURFACE_FLUX_ESTIMATOR_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename ContributionMultiplierPolicy>
SurfaceFluxEstimator<ContributionMultiplierPolicy>::SurfaceFluxEstimator(
    const Estimator::idType id,
    const double multiplier,
    const Teuchos::Array<StandardSurfaceEstimator::surfaceIdType>& surface_ids,
    const Teuchos::Array<double>& surface_areas )
  : StandardSurfaceEstimator( id, multiplier, surface_ids, surface_areas )
{ /* ... */ }

// Add estimator contribution from a portion of the current history
/*! \details It is unsafe to call this function directly! This function will
 * be called by the appropriate dispatcher whan an event of interest occurs.
 * If calling this function directly, make sure that the cell of surface of
 * interest is actually assigned to this estimator (otherwise seg. faults are
 * likely!).
 */
template<typename ContributionMultiplierPolicy>
void SurfaceFluxEstimator<
         ContributionMultiplierPolicy>::updateFromParticleCrossingSurfaceEvent(
		const ParticleState& particle,
		const StandardSurfaceEstimator::surfaceIdType surface_crossing,
		const double angle_cosine )
{
  // Make sure the surface is assigned to this estimator
  testPrecondition( isEntityAssigned( surface_crossing ) );
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine <= 1.0 );
  testPrecondition( angle_cosine >= -1.0 );

  if( this->isParticleTypeAssigned( particle.getParticleType() ) )
  {
    double contribution; 
    
    // If the angle cosine is very close to zero, set it to eps/2 to
    // prevent large contributions to the estimator
    if( ST::magnitude( angle_cosine ) > 
        SimulationGeneralProperties::getSurfaceFluxEstimatorAngleCosineCutoff() )
      contribution = 1.0/ST::magnitude( angle_cosine );
    else
    {
      contribution = 
	2.0/SimulationGeneralProperties::getSurfaceFluxEstimatorAngleCosineCutoff();
    }

    contribution *= ContributionMultiplierPolicy::multiplier( particle );
  
    EstimatorParticleStateWrapper particle_state_wrapper( particle );
    particle_state_wrapper.setAngleCosine( angle_cosine );

    StandardEntityEstimator<
       StandardSurfaceEstimator::surfaceIdType>::addPartialHistoryContribution(
                                                        surface_crossing,
							particle_state_wrapper,
                                                        contribution );
  }
}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void SurfaceFluxEstimator<
		 ContributionMultiplierPolicy>::printSummary( 
                                                       std::ostream& os ) const
{
  os << "Surface Flux Estimator: " << getId() << std::endl;

  printImplementation( os, "Surface" );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SURFACE_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SurfaceFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
