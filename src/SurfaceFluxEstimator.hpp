//---------------------------------------------------------------------------//
//!
//! \file   SurfaceFluxEstimator.hpp
//! \author Alex Robinson
//! \brief  Surface flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef SURFACE_FLUX_ESTIMATOR_HPP
#define SURFACE_FLUX_ESTIMATOR_HPP

// FACEMC Includes
#include "SurfaceEstimator.hpp"
#include "EstimatorContributionMultiplierPolicy.hpp"

namespace FACEMC{

template<typename SurfaceId,
	 typename ContributionMultiplierPolicy = WeightMultiplier>
class SurfaceFluxEstimator : public SurfaceEstimatorEstimator<SurfaceId>
{

public:

  //! Constructor
  SurfaceFluxEstimator( const unsigned long long id,
			const SurfaceId& surface_id,
			const double norm_constant,
			const double multiplier = 1.0 );

  //! Destructor
  ~SurfaceCurrentEstimator()
  { /* ... */ }

  //! Calculate and add estimator contribution from a portion of the cur. hist.
  void calculateAndAddPartialHistoryContribution(
					 const BasicParticleState& particle,
					 const double reference_direction[3] );
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "SurfaceFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end SURFACE_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end SurfaceFluxEstimator.hpp
//---------------------------------------------------------------------------//
