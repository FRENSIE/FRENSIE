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
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( SurfaceFluxEstimator<WeightMultiplier> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( SurfaceFluxEstimator<WeightAndEnergyMultiplier> );

// Constructor
template<typename ContributionMultiplierPolicy>
SurfaceFluxEstimator<ContributionMultiplierPolicy>::SurfaceFluxEstimator(
                              const Estimator::idType id,
                              const double multiplier,
                              const std::vector<surfaceIdType>& surface_ids,
                              const std::vector<double>& surface_areas,
                              const double cosine_cutoff )
  : StandardSurfaceEstimator( id, multiplier, surface_ids, surface_areas ),
    d_cosine_cutoff( cosine_cutoff )
{ /* ... */ }

// Add estimator contribution from a portion of the current history
/*! \details It is unsafe to call this function directly! This function will
 * be called by the appropriate dispatcher whan an event of interest occurs.
 * If calling this function directly, make sure that the cell of surface of
 * interest is actually assigned to this estimator (otherwise seg. faults are
 * likely!).
 */
template<typename ContributionMultiplierPolicy>
void SurfaceFluxEstimator<ContributionMultiplierPolicy>::updateFromParticleCrossingSurfaceEvent(
                                          const ParticleState& particle,
                                          const surfaceIdType surface_crossing,
                                          const double angle_cosine )
{
  // Make sure the surface is assigned to this estimator
  testPrecondition( this->isEntityAssigned( surface_crossing ) );
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine <= 1.0 );
  testPrecondition( angle_cosine >= -1.0 );

  if( this->isParticleTypeAssigned( particle.getParticleType() ) )
  {
    double contribution;

    double abs_angle_cosine = std::fabs( angle_cosine );

    // If the angle cosine is very close to zero, set it to eps/2 to
    // prevent large contributions to the estimator
    if( abs_angle_cosine > d_cosine_cutoff )
      contribution = 1.0/abs_angle_cosine;
    else
      contribution = 2.0/d_cosine_cutoff;

    contribution *= ContributionMultiplierPolicy::multiplier( particle );

    EstimatorParticleStateWrapper particle_state_wrapper( particle );
    particle_state_wrapper.setAngleCosine( angle_cosine );

    this->addPartialHistoryPointContribution( surface_crossing,
                                              particle_state_wrapper,
                                              contribution );
  }
}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void SurfaceFluxEstimator<ContributionMultiplierPolicy>::printSummary(
                                                       std::ostream& os ) const
{
  os << "Surface Flux Estimator: " << this->getId() << std::endl;

  this->printImplementation( os, "Surface" );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SURFACE_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SurfaceFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
