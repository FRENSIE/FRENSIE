//---------------------------------------------------------------------------//
//!
//! \file   Facemc_CellCollisionFluxEstimator_def.hpp
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

namespace Facemc{

// Constructor
template<typename ContributionMultiplierPolicy>
CellCollisionFluxEstimator<
		     ContributionMultiplierPolicy>::CellCollisionFluxEstimator(
	     const Estimator::idType id,
	     const double multiplier,
	     const Teuchos::Array<StandardCellEstimator::cellIdType>& cell_ids,
	     const Teuchos::Array<double>& cell_volumes )
  : StandardCellEstimator( id, multiplier, cell_ids, cell_volumes )
{ /* ... */ }

// Add estimator contribution from a portion of the current history
template<typename ContributionMultiplierPolicy>
void CellCollisionFluxEstimator<
		  ContributionMultiplierPolicy>::addPartialHistoryContribution(
		     const ParticleState& particle,
		     const StandardCellEstimator::cellIdType cell_of_collision,
		     const double inverse_total_cross_section,
		     const double angle_cosine )
{
  // Make sure the cell is assigned to this estimator
  testPrecondition( isEntityAssigned( cell_of_collision ) );
  // Make sure the particle type is assigned
  testPrecondition( isParticleTypeAssigned( particle.getParticleType() ) );
  // Make sure the inverse total macroscopic cross section is valid
  testPrecondition( !ST::isnaninf( inverse_total_cross_section ) );
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine <= 1.0 );
  testPrecondition( angle_cosine >= -1.0 );
  
  double contribution = inverse_total_cross_section*
    ContributionMultiplierPolicy::multiplier( particle );

  StandardEntityEstimator<
             StandardCellEstimator::cellIdType>::addPartialHistoryContribution(
							     cell_of_collision,
							     particle, 
							     angle_cosine, 
							     contribution );
}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void CellCollisionFluxEstimator<
		 ContributionMultiplierPolicy>::print( std::ostream& os ) const
{
  os << "Cell Collision Estimator: " << getId() << std::endl;

  printImplementation( os, "Cell" );
}

} // end Facemc namespace

#endif // end FACEMC_CELL_COLLISION_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Facemc_CellCollisionFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
