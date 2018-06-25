//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SurfaceFluxEstimator.hpp
//! \author Alex Robinson
//! \brief  Surface flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SURFACE_FLUX_ESTIMATOR_HPP
#define MONTE_CARLO_SURFACE_FLUX_ESTIMATOR_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardSurfaceEstimator.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"

namespace MonteCarlo{

/*! The surface flux estimator class
 * \ingroup particle_crossing_surface_event
 */
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class SurfaceFluxEstimator : public StandardSurfaceEstimator
{

public:

  //! Typedef for event tags
  typedef StandardSurfaceEstimator::EventTags EventTags;

  //! Constructor
  template<template<typename,typename...> class STLCompliantArrayA,
           template<typename,typename...> class STLCompliantArrayB>
  SurfaceFluxEstimator( const Estimator::idType id,
                        const double multiplier,
                        const STLCompliantArrayA<surfaceIdType>& surface_ids,
                        const STLCompliantArrayB<double>& surface_areas,
                        const double cosine_cutoff = 0.001 );

  //! Destructor
  ~SurfaceFluxEstimator()
  { /* ... */ }

  //! Add estimator contribution from a portion of the current history
  void updateFromParticleCrossingSurfaceEvent(
                                          const ParticleState& particle,
		                          const surfaceIdType surface_crossing,
                                          const double angle_cosine ) override;

  //! Print the estimator data summary
  void printSummary( std::ostream& os ) const override;

private:

  // The cosine cutoff
  double d_cosine_cutoff;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_SurfaceFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_SURFACE_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SurfaceFluxEstimator.hpp
//---------------------------------------------------------------------------//
