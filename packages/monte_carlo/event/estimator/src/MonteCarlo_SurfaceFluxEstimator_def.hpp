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
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
template<typename ContributionMultiplierPolicy>
SurfaceFluxEstimator<ContributionMultiplierPolicy>::SurfaceFluxEstimator()
{ /* ... */ }

// Constructor
template<typename ContributionMultiplierPolicy>
SurfaceFluxEstimator<ContributionMultiplierPolicy>::SurfaceFluxEstimator(
                              const Id id,
                              const double multiplier,
                              const std::vector<SurfaceIdType>& surface_ids,
                              const std::vector<double>& surface_areas )
  : StandardSurfaceEstimator( id, multiplier, surface_ids, surface_areas ),
    d_cosine_cutoff( this->getDefaultCosineCutoff() )
{ /* ... */ }

// Constructor (extract surface areas from model)
template<typename ContributionMultiplierPolicy>
SurfaceFluxEstimator<ContributionMultiplierPolicy>::SurfaceFluxEstimator(
                        const Id id,
                        const double multiplier,
                        const std::vector<SurfaceIdType>& surface_ids,
                        const Geometry::Model& model )
  : StandardSurfaceEstimator( id, multiplier, surface_ids, model ),
    d_cosine_cutoff( this->getDefaultCosineCutoff() )
{ /* ... */ }

// Set the cosine cutoff value
/*! \details The cosine cutoff must be between 0.0 and 1.0. The default value
 * is 0.001.
 */
template<typename ContributionMultiplierPolicy>
void SurfaceFluxEstimator<ContributionMultiplierPolicy>::setCosineCutoffValue( const double cosine_cutoff )
{
  TEST_FOR_EXCEPTION( cosine_cutoff <= 0.0,
                      std::runtime_error,
                      "The cosine cutoff must be between 0.0 and 1.0!" );

  TEST_FOR_EXCEPTION( cosine_cutoff >= 1.0,
                      std::runtime_error,
                      "The cosine cutoff must be between 0.0 and 1.0!" );

  d_cosine_cutoff = cosine_cutoff;
}

// Get the cosine cutoff value
template<typename ContributionMultiplierPolicy>
double SurfaceFluxEstimator<ContributionMultiplierPolicy>::getCosineCutoffValue() const
{
  return d_cosine_cutoff;
}

// Get the default cosine cutoff
template<typename ContributionMultiplierPolicy>
double SurfaceFluxEstimator<ContributionMultiplierPolicy>::getDefaultCosineCutoff()
{
  return 0.001;
}

// Add estimator contribution from a portion of the current history
/*! \details It is unsafe to call this function directly! This function will
 * be called by the appropriate dispatcher when an event of interest occurs.
 * If calling this function directly, make sure that the cell of surface of
 * interest is actually assigned to this estimator (otherwise seg. faults are
 * likely!).
 */
template<typename ContributionMultiplierPolicy>
void SurfaceFluxEstimator<ContributionMultiplierPolicy>::updateFromParticleCrossingSurfaceEvent(
                                          const ParticleState& particle,
                                          const SurfaceIdType surface_crossing,
                                          const double angle_cosine )
{
  // Make sure that the particle type is assigned to this estimator
  testPrecondition( this->isParticleTypeAssigned( particle.getParticleType() ) );
  // Make sure that the surface is assigned to this estimator
  testPrecondition( this->isEntityAssigned( surface_crossing ) );
  // Make sure that the angle cosine is valid
  testPrecondition( angle_cosine <= 1.0 );
  testPrecondition( angle_cosine >= -1.0 );

  double contribution;

  const double abs_angle_cosine = std::fabs( angle_cosine );

  // If the angle cosine is very close to zero, set it to eps/2 to
  // prevent large contributions to the estimator
  if( abs_angle_cosine > d_cosine_cutoff )
    contribution = 1.0/abs_angle_cosine;
  else
    contribution = 2.0/d_cosine_cutoff;

  contribution *= ContributionMultiplierPolicy::multiplier( particle );

  ObserverParticleStateWrapper particle_state_wrapper( particle );
  particle_state_wrapper.setAngleCosine( angle_cosine );

  this->addPartialHistoryPointContribution( surface_crossing,
                                            particle_state_wrapper,
                                            contribution );
}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void SurfaceFluxEstimator<ContributionMultiplierPolicy>::printSummary(
                                                       std::ostream& os ) const
{
  os << "Surface Flux Estimator: " << this->getId() << "\n";

  this->printImplementation( os, "Surface" );

  os << std::flush;
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightMultipliedSurfaceFluxEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SurfaceFluxEstimator<MonteCarlo::WeightMultiplier> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightAndEnergyMultipliedSurfaceFluxEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightAndChargeMultipliedSurfaceFluxEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SurfaceFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> );

#endif // end MONTE_CARLO_SURFACE_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SurfaceFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
