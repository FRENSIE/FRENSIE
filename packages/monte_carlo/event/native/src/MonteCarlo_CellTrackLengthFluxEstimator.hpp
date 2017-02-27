//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellTrackLengthFluxEstimator.hpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP
#define MONTE_CARLO_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

// Boost Includes
#include <boost/mpl/vector.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardCellEstimator.hpp"
#include "MonteCarlo_ParticleSubtrackEndingInCellEventObserver.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"

namespace MonteCarlo{

/*! The cell track length flux estimator class
 * \ingroup particle_subtrack_ending_in_cell_event
 */
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class CellTrackLengthFluxEstimator : public StandardCellEstimator,
				     public ParticleSubtrackEndingInCellEventObserver
{

public:

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleSubtrackEndingInCellEventObserver::EventTag>
  EventTags;

  //! Constructor
  template<template<typename,typename...> class STLCompliantArrayA,
           template<typename,typename...> class STLCompliantArrayB>
  CellTrackLengthFluxEstimator(
                              const Estimator::idType id,
                              const double multiplier,
                              const STLCompliantArrayA<cellIdType>& cell_ids,
	                      const STLCompliantArrayB<double>& cell_volumes );

  //! Destructor
  ~CellTrackLengthFluxEstimator()
  { /* ... */ }

  //! Add current history estimator contribution
  void updateFromParticleSubtrackEndingInCellEvent(
                                             const ParticleState& particle,
		                             const cellIdType cell_of_subtrack,
                                             const double track_length );

  //! Print the estimator data summary
  void printSummary( std::ostream& os ) const;

private:

  //! Assign response function to the estimator
  void assignResponseFunction(
        const Estimator::ResponseFunctionPointer& response_function ) override;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CellTrackLengthFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
