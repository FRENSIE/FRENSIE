//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellCollisionFluxEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Cell collision flux estimator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_CELL_COLLISION_FLUX_ESTIMATOR_DEF_HPP
#define FACEMC_CELL_COLLISION_FLUX_ESTIMATOR_DEF_HPP

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename ContributionMultiplierPolicy>
CellCollisionFluxEstimator<
		     ContributionMultiplierPolicy>::CellCollisionFluxEstimator(
	     const Estimator::idType id,
	     const double multiplier,
	     const Teuchos::Array<StandardCellEstimator::cellIdType>& cell_ids,
	     const Teuchos::Array<double>& cell_volumes )
  : StandardCellEstimator( id, multiplier, cell_ids, cell_volumes ),
    ParticleCollidingInCellEventObserver()			 
{ /* ... */ }

// Add estimator contribution from a portion of the current history
template<typename ContributionMultiplierPolicy>
void CellCollisionFluxEstimator<
         ContributionMultiplierPolicy>::updateFromParticleCollidingInCellEvent(
		     const ParticleState& particle,
		     const StandardCellEstimator::cellIdType cell_of_collision,
		     const double inverse_total_cross_section )
{
  // Make sure the cell is assigned to this estimator
  testPrecondition( isEntityAssigned( cell_of_collision ) );
  // Make sure the inverse total macroscopic cross section is valid
  testPrecondition( !ST::isnaninf( inverse_total_cross_section ) );
  
  if( this->isParticleTypeAssigned( particle.getParticleType() ) )
  {
    double contribution = inverse_total_cross_section*
      ContributionMultiplierPolicy::multiplier( particle );

    StandardEntityEstimator<
             StandardCellEstimator::cellIdType>::addPartialHistoryContribution(
							     cell_of_collision,
							     particle, 
							     0.0, 
							     contribution );
  }
}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void CellCollisionFluxEstimator<
		 ContributionMultiplierPolicy>::print( std::ostream& os ) const
{
  os << "Cell Collision Estimator: " << getId() << std::endl;

  printImplementation( os, "Cell" );
}

} // end MonteCarlo namespace

#endif // end FACEMC_CELL_COLLISION_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellCollisionFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
