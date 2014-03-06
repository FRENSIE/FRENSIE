//---------------------------------------------------------------------------//
//!
//! \file   CellCollisionFluxEstimator.hpp
//! \author Alex Robinson
//! \brief  Cell collision flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef CELL_COLLISION_FLUX_ESTIMATOR_HPP
#define CELL_COLLISION_FLUX_ESTIMATOR_HPP

// FACEMC Includes
#include "CellEstimator.hpp"
#include "EstimatorContributionMultiplierPolicy.hpp"

namespace FACEMC{

template<typename CellId,
	 typename ContributionMultiplierPolicy = WeightMultiplier>
class CellCollisionFluxEstimator : public CellEstimator<CellId>
{

public:

  //! Constructor
  CellCollisionFluxEstimator( const unsigned long long id,
			      const CellId& cell_id,
			      const double norm_constant,
			      const double multiplier = 1.0 );

  //! Destructor
  ~CellCollisionFluxEstimator()
  { /* ... */ }

  //! Calculate and add estimator contribution from a portion of the cur. hist.
  void calculateAndAddPartialHistoryContribution( 
					   const BasicParticleState& particle,
					   const double raw_contribution );
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "CellCollisionFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end CELL_COLLISION_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end CellCollisionFluxEstimator.hpp
//---------------------------------------------------------------------------//
