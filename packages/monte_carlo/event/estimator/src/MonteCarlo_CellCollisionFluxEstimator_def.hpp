//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellCollisionFluxEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Cell collision flux estimator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CELL_COLLISION_FLUX_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_CELL_COLLISION_FLUX_ESTIMATOR_DEF_HPP

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
template<typename ContributionMultiplierPolicy>
CellCollisionFluxEstimator<ContributionMultiplierPolicy>::CellCollisionFluxEstimator()
{ /* ... */ }

// Constructor
template<typename ContributionMultiplierPolicy>
CellCollisionFluxEstimator<ContributionMultiplierPolicy>::CellCollisionFluxEstimator(
                                      const Id id,
                                      const double multiplier,
                                      const std::vector<CellIdType>& cell_ids,
                                      const std::vector<double>& cell_volumes )
  : StandardCellEstimator( id, multiplier, cell_ids, cell_volumes ),
    ParticleCollidingInCellEventObserver()
{ /* ... */ }

// Constructor (extract cell volumes from model)
template<typename ContributionMultiplierPolicy>
CellCollisionFluxEstimator<ContributionMultiplierPolicy>::CellCollisionFluxEstimator(
                                      const Id id,
                                      const double multiplier,
                                      const std::vector<CellIdType>& cell_ids,
                                      const Geometry::Model& model )
  : StandardCellEstimator( id, multiplier, cell_ids, model ),
    ParticleCollidingInCellEventObserver()
{ /* ... */ }

// Add estimator contribution from a portion of the current history
template<typename ContributionMultiplierPolicy>
void CellCollisionFluxEstimator<ContributionMultiplierPolicy>::updateFromParticleCollidingInCellEvent(
                                     const ParticleState& particle,
                                     const CellIdType cell_of_collision,
		                     const double inverse_total_cross_section )
{
  // Make sure that the particle type is assigned to this estimator
  testPrecondition( this->isParticleTypeAssigned( particle.getParticleType() ) )
  // Make sure that the cell is assigned to this estimator
  testPrecondition( this->isEntityAssigned( cell_of_collision ) );

  const double contribution = inverse_total_cross_section*
    ContributionMultiplierPolicy::multiplier( particle );

  ObserverParticleStateWrapper particle_state_wrapper( particle );

  this->addPartialHistoryPointContribution( cell_of_collision,
                                            particle_state_wrapper,
                                            contribution );
}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void CellCollisionFluxEstimator<ContributionMultiplierPolicy>::printSummary( std::ostream& os ) const
{
  os << "Cell Collision Estimator: " << this->getId() << "\n";

  this->printImplementation( os, "Cell" );

  os << std::flush;
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightMultipliedCellCollisionFluxEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightMultiplier> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, CellCollisionFluxEstimator<MonteCarlo::WeightMultiplier> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightAndEnergyMultipliedCellCollisionFluxEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, CellCollisionFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightAndChargeMultipliedCellCollisionFluxEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, CellCollisionFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> );

#endif // end MONTE_CARLO_CELL_COLLISION_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellCollisionFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
