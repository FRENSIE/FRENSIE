//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellCollisionFluxEstimator.hpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CELL_COLLISION_FLUX_ESTIMATOR_HPP
#define MONTE_CARLO_CELL_COLLISION_FLUX_ESTIMATOR_HPP

// Boost Includes
#include <boost/mpl/vector.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardCellEstimator.hpp"
#include "MonteCarlo_ParticleCollidingInCellEventObserver.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"

namespace MonteCarlo{

/*! The cell collision flux estimator class
 * \ingroup particle_colliding_in_cell_event
 */
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class CellCollisionFluxEstimator : public StandardCellEstimator,
				   public ParticleCollidingInCellEventObserver
{

public:

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleCollidingInCellEventObserver::EventTag>
  EventTags;

  //! Constructor
  template<template<typename,typename...> class STLCompliantArrayA,
           template<typename,typename...> class STLCompliantArrayB>
  CellCollisionFluxEstimator( const Estimator::idType id,
                              const double multiplier,
                              const STLCompliantArrayA<cellIdType>& cell_ids,
                              const STLCompliantArrayB<double>& cell_volumes );

  //! Destructor
  ~CellCollisionFluxEstimator()
  { /* ... */ }

  //! Add current history estimator contribution
  void updateFromParticleCollidingInCellEvent(
                           const ParticleState& particle,
                           const cellIdType cell_of_collision,
                           const double inverse_total_cross_section ) override;

  //! Print the estimator data summary
  void printSummary( std::ostream& os ) const override;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CellCollisionFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_CELL_COLLISION_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellCollisionFluxEstimator.hpp
//---------------------------------------------------------------------------//
