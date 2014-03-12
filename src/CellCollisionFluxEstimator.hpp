//---------------------------------------------------------------------------//
//!
//! \file   CellCollisionFluxEstimator.hpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef CELL_COLLISION_FLUX_ESTIMATOR_HPP
#define CELL_COLLISION_FLUX_ESTIMATOR_HPP

// FACEMC Includes
#include "StandardEntityEstimator.hpp"
#include "EstimatorContributionMultiplierPolicy.hpp"

namespace FACEMC{

//! The cell collision flux estimator class
template<typename CellId,
	 typename ContributionMultiplierPolicy = WeightMultiplier>
class CellCollisionFluxEstimator : public StandardEntityEstimator<CellId>
{

public:

  //! Constructor
  CellCollisionFluxEstimator( const unsigned long long id,
			      const double multiplier,
			      const Teuchos::Array<CellId>& cell_ids,
			      const Teuchos::Array<double>& cell_volumes );

  //! Destructor
  ~CellCollisionFluxEstimator()
  { /* ... */ }

  //! Set the cosine bin boundaries
  void setCosineBinBoundaries( 
			 const Teuchos::Array<double>& cosine_bin_boundaries );

  //! Set the particle types that can contribute to the estimator
  void setParticleTypes( const Teuchos::Array<ParticleType>& particle_types );

  //! Add estimator contribution from a portion of the current history
  void addPartialHistoryContribution( 
				    const BasicParticleState& particle,
				    const CellId& cell_of_collision,
				    const double inverse_total_cross_section );

  //! Print the estimator data
  void print( std::ostream& os ) const;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "CellCollisionFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end CELL_COLLISION_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end CellCollisionFluxEstimator.hpp
//---------------------------------------------------------------------------//
