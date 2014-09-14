//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellTrackLengthFluxEstimator.hpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP
#define FACEMC_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

// Boost Includes
#include <boost/mpl/vector.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardCellEstimator.hpp"
#include "MonteCarlo_ParticleSubtrackEndingInCellEventObserver.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"

namespace MonteCarlo{

//! The cell track length flux estimator class
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class CellTrackLengthFluxEstimator : public StandardCellEstimator,
				     public ParticleSubtrackEndingInCellEventObserver
{

public:

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleSubtrackEndingInCellEventObserver::EventTag>
  EventTags;
  
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

  //! Add current history estimator contribution
  void updateFromParticleSubtrackEndingInCellEvent(
		      const ParticleState& particle,
		      const StandardCellEstimator::cellIdType cell_of_subtrack,
		      const double track_length );

  //! Print the estimator data
  void print( std::ostream& os ) const;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CellTrackLengthFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
