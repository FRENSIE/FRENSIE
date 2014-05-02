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
#include "StandardSurfaceEstimator.hpp"
#include "EstimatorContributionMultiplierPolicy.hpp"

namespace FACEMC{

//! The surface flux estimator class
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class SurfaceFluxEstimator : public StandardSurfaceEstimator
{

public:

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
  void addPartialHistoryContribution( 
		 const ParticleState& particle,
		 const StandardSurfaceEstimator::surfaceIdType surface_crossed,
		 const double angle_cosine );

  //! Print the estimator data
  void print( std::ostream& os ) const;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "SurfaceFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end SURFACE_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end SurfaceFluxEstimator.hpp
//---------------------------------------------------------------------------//
