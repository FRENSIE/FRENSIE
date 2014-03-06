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
class CellTrackLengthFluxEstimator<CellId,
		   ContributionMultiplierPolicy>::CellTrackLengthFluxEstimator(
						   const unsigned long long id,
						   const CellId& cell_id,
						   const double norm_constant,
						   const double multiplier )
: CellEstimator<CellId>( id, cell_id, norm_constant, multiplier )
{ /* ... */ }

// Calculate and add estimator contribution from a portion of the cur. hist.
/*! \details The raw contribution is the track length of the portion of the 
 * current history that lies within the cell associated with this estimator. 
 */
template<typename CellId,typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<CellId,
      ContributionMultiplierPolicy>::calculateAndAddPartialHistoryContribution(
					    const BasicParticleState& particle,
					    const double raw_contribution )
{
  // Make sure the track length is valid
  testPrecondition( !ST::isnaninf( raw_contribution ) );
  testPrecondition( raw_contribution > 0.0 );
  
  double contribution = raw_contribution*
    ContributionMultiplierPolicy::multiplier( particle );

  // Assume a reference direction of (0,0,1) for calculating the angle cos bin
  StandardEstimator<CellId>::addPartialHistoryContribution( 
						    particle,
						    contribution,
						    particle.getZDirection() );
}

// Set the response function
/*! \details The response function must be uniform in space in order for the
 * track length estimator to be valid. 
 */
template<typename CellId,typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<CellId,
			   ContributionMultiplierPolicy>::setResponseFunctions(
    const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions )
{
  for( unsigned i = 0; i < response_functions.size(); ++i )
  {
    if( !response_functions[i]->isUniformInSpace() )
    {
      std::cerr << "Warning: CellTrackLengthFluxEstimator " 
		<< getId() << "has been assigned a response function that is "
		<< "not uniform in space. The estimated response will not be "
		<< "correct." << std::endl;
    }
  }

  StandardEstimator<CellId>::setResponseFunctions( response_functions );
}

} // end FACEMC namespace

#endif // end CELL_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end CellTrackLengthFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
