//---------------------------------------------------------------------------//
//!
//! \file   Facemc_CellTrackLengthFluxEstimator.hpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP
#define FACEMC_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

// FRENSIE Includes
#include "Facemc_StandardCellEstimator.hpp"
#include "Facemc_EstimatorContributionMultiplierPolicy.hpp"

namespace Facemc{

//! The cell track length flux estimator class
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class CellTrackLengthFluxEstimator : public StandardCellEstimator
{

public:
  
  //! Constructor
  CellTrackLengthFluxEstimator( 
	     const Estimator::idType id,
	     const double multiplier,
	     const Teuchos::Array<StandardCellEstimator::cellIdType>& cell_ids,
	     const Teuchos::Array<double>& cell_volumes );

  //! Destructor
  ~CellTrackLengthFluxEstimator()
  { /* ... */ }

  //! Set the response functions
  void setResponseFunctions(
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions );

  //! Add estimator contribution from a portion of the current history
  void addPartialHistoryContribution( 
			 const ParticleState& particle,
			 const StandardCellEstimator::cellIdType cell_of_track,
			 const double track_length,
			 const double angle_cosine = 0.0 );

  //! Print the estimator data
  void print( std::ostream& os ) const;
};

} // end Facemc namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Facemc_CellTrackLengthFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end Facemc_CellTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
