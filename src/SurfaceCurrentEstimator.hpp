//---------------------------------------------------------------------------//
//!
//! \file   SurfaceCurrentEstimator.hpp
//! \author Alex Robinson
//! \brief  Surface current estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef SURFACE_CURRENT_ESTIMATOR_HPP
#define SURFACE_CURRENT_ESTIMATOR_HPP

// FACEMC Includes
#include "SurfaceEstimator.hpp"
#include "EstimatorContributionMultiplierPolicy.hpp"

namespace FACEMC{

//! The surface current estimator class
template<typename SurfaceId,
	 typename ContributionMultiplierPolicy = WeightMultiplier>
class SurfaceCurrentEstimator : public SurfaceEstimator<SurfaceId>
{

public:

  //! Constructor
  SurfaceCurrentEstimator( const unsigned long long id,
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

#include "SurfaceCurrentEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end SURFACE_CURRENT_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end SurfaceCurrentEstimator.hpp
//---------------------------------------------------------------------------//
