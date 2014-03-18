//---------------------------------------------------------------------------//
//!
//! \file   CellTrackLengthFluxEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator class definition.
//!
//---------------------------------------------------------------------------//

#ifndef CELL_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP
#define CELL_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP

// Std Lib Includes
#include <iostream>

// FACEMC Includes
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
template<typename CellId,typename ContributionMultiplierPolicy>
CellTrackLengthFluxEstimator<CellId,
		       ContributionMultiplierPolicy>::CellTrackLengthEstimator(
			           const unsigned long long id,
				   const double multiplier,
				   const Teuchos::Array<CellId>& cell_ids,
			           const Teuchos::Array<double>& cell_volumes )
  : StandardEntityEstimator<EntityId>( id,
				       multiplier,
				       cell_ids,
				       cell_volumes )
{ /* ... */ }

// Set the cosine bin boundaries
template<typename CellId,typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<CellId,
			 ContributionMultiplierPolicy>::setCosineBinBoundaries(
			  const Teuchos::Array<double>& cosine_bin_boundaries )
{
  std::cerr << "Warning: Cosine bins cannot be set for cell track length flux "
	    << "estimators. The cosine bins requested for cell track length "
	    << "flux estimator " << getId() < " will be ignored."
	    << std::endl;
}

// Set the response functions
template<typename CellId,typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<CellId,
			   ContributionMultiplierPolicy>::setResponseFunctions(
    const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions )
{
  for( unsigned i = 0; i < response_functions.size(); ++i )
  {
    if( !response_function[i]->isSpatiallyUniform() )
    {
      std::cerr << "Warning: cell track length estimators can only be used "
		<< "with spatially uniform response functions. Results from "
		<< "cell track length estimator " << getId()
		<< "will not be correct." << std::endl;
    }
  }
}  

// Set the particle types that can contribute to the estimator
/*! \details Photons, electrons and neutrons (or their adjoint
 * couterparts) can contribute to the estimator. Combinations are not 
 * allowed.
 */
template<typename CellId,typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<CellId,
			       ContributionMultiplierPolicy>::setParticleTypes(
			   const Teuchos::Array<ParticleType>& particle_types )
{
  // Make sure only one particle type has been specified
  testPrecondition( particle_types.size() == 1 );

  Estimator::setParticleTypes( particle_types );
}

// Add estimator contribution from a portion of the current history
template<typename CellId,typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<CellId,
		  ContributionMultiplierPolicy>::addPartialHistoryContribution(
					    const BasicParticleState& particle,
					    const CellId& cell_of_track,
					    const double track_length )
{
  // Make sure the cell is assigned to this estimator
  testPrecondition( isEntityAssigned( cell_of_track ) );
  // Make sure the track length is valid
  testPrecondition( !ST::isnaninf( track_length ) );
  
  double contribution = track_length*
    ContributionMultiplierPolicy::multiplier( particle );
  
  addPartialHistoryContribution( cell_of_track, particle, 0, contribution);
}

// Print the estimator data
template<typename CellId,typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<CellId,
		 ContributionMultiplierPolicy>::print( std::ostream& os ) const
{
  os << "Cell Track Length Flux Estimator: " << getId() << std::endl;

  printImplementation( os, "Cell" );
}

} // end FACEMC namespace

#endif // end CELL_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end CellTrackLengthFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
