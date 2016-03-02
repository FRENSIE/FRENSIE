//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellTrackLengthFluxEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator class definition.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename ContributionMultiplierPolicy>
CellTrackLengthFluxEstimator<
		   ContributionMultiplierPolicy>::CellTrackLengthFluxEstimator(
	     const Estimator::idType id,
	     const double multiplier,
	     const Teuchos::Array<StandardCellEstimator::cellIdType>& cell_ids,
	     const Teuchos::Array<double>& cell_volumes )
  : StandardCellEstimator( id, multiplier, cell_ids, cell_volumes ),
    ParticleSubtrackEndingInCellEventObserver()
{ /* ... */ }

// Set the response functions
template<typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<
			   ContributionMultiplierPolicy>::setResponseFunctions(
                      const Teuchos::Array<std::shared_ptr<ResponseFunction> >&
                      response_functions )
{
  for( unsigned i = 0; i < response_functions.size(); ++i )
  {
    if( !response_functions[i]->isSpatiallyUniform() )
    {
      std::cerr << "Warning: cell track length estimators can only be used "
		<< "with spatially uniform response functions. Results from "
		<< "cell track length estimator " << getId()
		<< "will not be correct." << std::endl;
    }
  }
  
  Estimator::setResponseFunctions( response_functions );
}  

// Add estimator contribution from a portion of the current history
template<typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<
    ContributionMultiplierPolicy>::updateFromParticleSubtrackEndingInCellEvent(
		      const ParticleState& particle,
		      const StandardCellEstimator::cellIdType cell_of_subtrack,
		      const double track_length )
{
  // Make sure the cell is assigned to this estimator
  testPrecondition( isEntityAssigned( cell_of_subtrack ) );
  // Make sure the subtrack length is valid
  testPrecondition( !ST::isnaninf( track_length ) );
    
  if( isParticleTypeAssigned( particle.getParticleType() ) )
  {
    double contribution = track_length*
      ContributionMultiplierPolicy::multiplier( particle );

    EstimatorParticleStateWrapper particle_state_wrapper( particle );
  
    StandardEntityEstimator<
             StandardCellEstimator::cellIdType>::addPartialHistoryContribution(
                                                        cell_of_subtrack,
							particle_state_wrapper,
                                                        contribution);
  }
}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<
		 ContributionMultiplierPolicy>::printSummary( std::ostream& os ) const
{
  os << "Cell Track Length Flux Estimator: " << getId() << std::endl;

  printImplementation( os, "Cell" );
}

// Assign bin boundaries to an estimator dimension
template<typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<
                            ContributionMultiplierPolicy>::assignBinBoundaries(
      const std::shared_ptr<EstimatorDimensionDiscretization>& bin_boundaries )
{
  if( bin_boundaries->getDimension() == TIME_DIMENSION )
  {
    std::cerr << "Warning: " << bin_boundaries->getDimensionName()
	      << " bins cannot be set for cell track length flux estimators "
	      << "yet. The bins requested for cell track length flux "
	      << "estimator " << this->getId() << " will be ignored."
	      << std::endl;
  }
  else
    StandardCellEstimator::assignBinBoundaries( bin_boundaries );

}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellTrackLengthFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
