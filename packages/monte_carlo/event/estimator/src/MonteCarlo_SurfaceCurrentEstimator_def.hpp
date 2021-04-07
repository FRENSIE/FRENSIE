//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SurfaceCurrentEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Surface current estimator class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SURFACE_CURRENT_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_SURFACE_CURRENT_ESTIMATOR_DEF_HPP

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
template<typename ContributionMultiplierPolicy>
SurfaceCurrentEstimator<ContributionMultiplierPolicy>::SurfaceCurrentEstimator()
{ /* ... */ }

// Constructor
template<typename ContributionMultiplierPolicy>
SurfaceCurrentEstimator<ContributionMultiplierPolicy>::SurfaceCurrentEstimator(
                    const Id id,
                    const double multiplier,
                    const std::vector<StandardSurfaceEstimator::SurfaceIdType>&
                    surface_ids )
  : StandardSurfaceEstimator( id, multiplier, surface_ids )
{ /* ... */ }

// Add current history estimator contribution
/*! \details It is unsafe to call this function directly! This function will
 * be called by the appropriate dispatcher whan an event of interest occurs.
 * If calling this function directly, make sure that the cell of surface of
 * interest is actually assigned to this estimator (otherwise seg. faults are
 * likely!).
 */
template<typename ContributionMultiplierPolicy>
void SurfaceCurrentEstimator<ContributionMultiplierPolicy>::updateFromParticleCrossingSurfaceEvent(
		const ParticleState& particle,
		const StandardSurfaceEstimator::SurfaceIdType surface_crossing,
		const double angle_cosine )
{
  // Make sure that the particle type is assigned to this estimator
  testPrecondition( this->isParticleTypeAssigned( particle.getParticleType() ) );
  // Make sure that the surface is assigned to this estimator
  testPrecondition( this->isEntityAssigned( surface_crossing ) );
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine <= 1.0 );
  testPrecondition( angle_cosine >= -1.0 );

  const double contribution =
    ContributionMultiplierPolicy::multiplier( particle );

  ObserverParticleStateWrapper particle_state_wrapper( particle );
  particle_state_wrapper.setAngleCosine( angle_cosine );

  this->addPartialHistoryPointContribution( surface_crossing,
                                            particle_state_wrapper,
                                            contribution );
}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void SurfaceCurrentEstimator<ContributionMultiplierPolicy>::printSummary(
                                                       std::ostream& os ) const
{
  os << "Surface Current Estimator: " << getId() << "\n";

  this->printImplementation( os, "Surface" );

  os << std::flush;
}



// Set the response functions
template<typename ContributionMultiplierPolicy>
void SurfaceCurrentEstimator<ContributionMultiplierPolicy>::assignResponseFunction( const std::shared_ptr<const ParticleResponse>& response_function )
{
  FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                              "Response functions cannot be set for surface "
                              "current estimators. The response function "
                              "requested for surface current estimator "
                              << this->getId() << " will be ignored." );
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightMultipliedSurfaceCurrentEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightAndEnergyMultipliedSurfaceCurrentEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightAndChargeMultipliedSurfaceCurrentEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndChargeMultiplier> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SurfaceCurrentEstimator<MonteCarlo::WeightAndChargeMultiplier> );

#endif // end MONTE_CARLO_SURFACE_CURRENT_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SurfaceCurrentEstimator_def.hpp
//---------------------------------------------------------------------------//
