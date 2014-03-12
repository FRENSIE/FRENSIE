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
template<typename SurfaceId,
	 typename ContributionMultiplierPolicy = WeightMultiplier>
class SurfaceFluxEstimator : public StandardSurfaceEstimator<SurfaceId>
{

public:

  //! Set the angle cosine cutoff value
  static void setAngleCosineCutoff( const double angle_cosine_cutoff );
  
  //! Constructor
  SurfaceFluxEstimator( const unsigned long long id,
			const double multiplier,
			const Teuchos::Array<SurfaceId>& surface_ids,
			const Teuchos::Array<double>& surface_areas );

  //! Destructor
  ~SurfaceFluxEstimator()
  { /* ... */ }

  //! Add estimator contribution from a portion of the current history
  void addPartialHistoryContribution( const BasicParticleState& particle,
				      const SurfaceId& surface_crossed,
				      const double angle_cosine );

  //! Print the estimator data
  void print( std::ostream& os ) const;

private:

  // Angle cosine cutoff value (default = 0.01)
  static double angle_cosine_cutoff;
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
