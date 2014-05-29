//---------------------------------------------------------------------------//
//!
//! \file   Facemc_CellTrackLengthFluxEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator class definition.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP
#define FACEMC_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
template<typename ContributionMultiplierPolicy>
CellTrackLengthFluxEstimator<
		   ContributionMultiplierPolicy>::CellTrackLengthFluxEstimator(
	     const Estimator::idType id,
	     const double multiplier,
	     const Teuchos::Array<StandardCellEstimator::cellIdType>& cell_ids,
	     const Teuchos::Array<double>& cell_volumes )
  : StandardCellEstimator( id, multiplier, cell_ids, cell_volumes )
{ /* ... */ }

// Set the response functions
template<typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<
			   ContributionMultiplierPolicy>::setResponseFunctions(
    const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions )
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
		  ContributionMultiplierPolicy>::addPartialHistoryContribution(
			 const ParticleState& particle,
			 const StandardCellEstimator::cellIdType cell_of_track,
			 const double track_length,
			 const double angle_cosine )
{
  // Make sure the cell is assigned to this estimator
  testPrecondition( isEntityAssigned( cell_of_track ) );
  // Make sure the particle type is assigned
  testPrecondition( isParticleTypeAssigned( particle.getParticleType() ) );
  // Make sure the track length is valid
  testPrecondition( !ST::isnaninf( track_length ) );
  // Make sure the angle cosine is valid
  testPrecondition( angle_cosine <= 1.0 );
  testPrecondition( angle_cosine >= -1.0 );
  
  double contribution = track_length*
    ContributionMultiplierPolicy::multiplier( particle );
  
  StandardEntityEstimator<
             StandardCellEstimator::cellIdType>::addPartialHistoryContribution(
								 cell_of_track,
								 particle, 
								 angle_cosine, 
								 contribution);
}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<
		 ContributionMultiplierPolicy>::print( std::ostream& os ) const
{
  os << "Cell Track Length Flux Estimator: " << getId() << std::endl;

  printImplementation( os, "Cell" );
}

} // end Facemc namespace

#endif // end FACEMC_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Facemc_CellTrackLengthFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
