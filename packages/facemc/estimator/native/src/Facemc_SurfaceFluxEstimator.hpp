//---------------------------------------------------------------------------//
//!
//! \file   Facemc_SurfaceFluxEstimator.hpp
//! \author Alex Robinson
//! \brief  Surface flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_SURFACE_FLUX_ESTIMATOR_HPP
#define FACEMC_SURFACE_FLUX_ESTIMATOR_HPP

// FRENSIE Includes
#include "Facemc_StandardSurfaceEstimator.hpp"
#include "Facemc_EstimatorContributionMultiplierPolicy.hpp"

namespace Facemc{

//! The surface flux estimator class
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class SurfaceFluxEstimator : public StandardSurfaceEstimator
{

public:

  //! Typedef for event tags
  typedef StandardSurfaceEstimator::EventTags EventTags;

  //! Constructor
  SurfaceFluxEstimator( 
    const Estimator::idType id,
    const double multiplier,
    const Teuchos::Array<StandardSurfaceEstimator::surfaceIdType>& surface_ids,
    const Teuchos::Array<double>& surface_areas );

  //! Destructor
  ~SurfaceFluxEstimator()
  { /* ... */ }

  //! Add estimator contribution from a portion of the current history
  void updateFromParticleCrossingSurfaceEvent(
		const ParticleState& particle,
		const StandardSurfaceEstimator::surfaceIdType surface_crossing,
		const double angle_cosine );

  //! Print the estimator data
  void print( std::ostream& os ) const;
};

} // end Facemc namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Facemc_SurfaceFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_SURFACE_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end Facemc_SurfaceFluxEstimator.hpp
//---------------------------------------------------------------------------//
