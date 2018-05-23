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
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CellCollisionFluxEstimator<WeightMultiplier> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CellCollisionFluxEstimator<WeightAndEnergyMultiplier> );

// Constructor
template<typename ContributionMultiplierPolicy>
template<template<typename,typename...> class STLCompliantArrayA,
           template<typename,typename...> class STLCompliantArrayB>
CellCollisionFluxEstimator<ContributionMultiplierPolicy>::CellCollisionFluxEstimator(
                               const Estimator::idType id,
                               const double multiplier,
                               const STLCompliantArrayA<cellIdType>& cell_ids,
                               const STLCompliantArrayB<double>& cell_volumes )
  : StandardCellEstimator( id, multiplier, cell_ids, cell_volumes ),
    ParticleCollidingInCellEventObserver()
{ /* ... */ }

// Add estimator contribution from a portion of the current history
template<typename ContributionMultiplierPolicy>
void CellCollisionFluxEstimator<ContributionMultiplierPolicy>::updateFromParticleCollidingInCellEvent(
                                     const ParticleState& particle,
                                     const cellIdType cell_of_collision,
		                     const double inverse_total_cross_section )
{
  // Make sure the cell is assigned to this estimator
  testPrecondition( this->isEntityAssigned( cell_of_collision ) );

  if( this->isParticleTypeAssigned( particle.getParticleType() ) )
  {
    const double contribution = inverse_total_cross_section*
      ContributionMultiplierPolicy::multiplier( particle );

    EstimatorParticleStateWrapper particle_state_wrapper( particle );

    this->addPartialHistoryPointContribution( cell_of_collision,
                                              particle_state_wrapper,
                                              contribution );
  }
}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void CellCollisionFluxEstimator<ContributionMultiplierPolicy>::printSummary( std::ostream& os ) const
{
  os << "Cell Collision Estimator: " << getId() << std::endl;

  this->printImplementation( os, "Cell" );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_CELL_COLLISION_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellCollisionFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
