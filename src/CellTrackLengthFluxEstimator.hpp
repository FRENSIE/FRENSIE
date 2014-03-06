//---------------------------------------------------------------------------//
//!
//! \file   CellTrackLengthFluxEstimator.hpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP
#define CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

// FACEMC Includes
#include "CellEstimator.hpp"
#include "EstimatorContributionMultiplierPolicy.hpp"

namespace FACEMC{

  //! The cell track length flux estimator
template<typename CellId,
	 typename ContributionMultiplierPolicy = WeightMultiplier>
class CellTrackLengthFluxEstimator : public CellEstimator<CellId>
{
  
public:

  //! Constructor
  CellTrackLengthFluxEstimator( const unsigned long long id,
				const CellId& cell_id,
				const double norm_constant,
				const double multiplier = 1.0 );

  //! Destructor
  ~CellTrackLengthFluxEstimator()
  { /* ... */ }
  
  //! Calculate and add estimator contribution from a portion of the cur. hist.
  void calculateAndAddPartialHistoryContribution( 
					   const BasicParticleState& particle,
					   const double raw_contribution );

  //! Set the response functions
  void setResponseFunctions( 
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions );
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "CellTrackLengthFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end CellTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
