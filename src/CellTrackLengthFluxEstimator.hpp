//---------------------------------------------------------------------------//
//!
//! \file   CellTrackLengthFluxEstimator.hpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP
#define CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

// FACEMC Includes
#include "StandardEntityEstimator.hpp"
#include "EstimatorContributionMultiplierPolicy.hpp"

namespace FACEMC{

//! The cell track length flux estimator class
template<typename CellId,
	 typename ContributionMultiplierPolicy = WeightMultiplier>
class CellTrackLengthFluxEstimator : public StandardEntityEstimator<CellId>
{

public:
  
  //! Constructor
  CellTrackLengthFluxEstimator( const unsigned long long id,
				const double multiplier,
				const Teuchos::Array<CellId>& cell_ids,
				const Teuchos::Array<double>& cell_volumes )

  //! Destructor
  ~CellTrackLengthFluxEstimator()
  { /* ... */ }

  //! Set the cosine bin boundaries
  void setCosineBinBoundaries( 
			 const Teuchos::Array<double>& cosine_bin_boundaries );

  //! Set the response functions
  void setResponseFunctions(
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions );

  //! Set the particle types that can contribute to the estimator
  void setParticleTypes( const Teuchos::Array<ParticleType>& particle_types );

  //! Add estimator contribution from a portion of the current history
  void addPartialHistoryContribution( const BasicParticleState& particle,
				      const CellId& cell_of_track,
				      const double track_length );

  //! Print the estimator data
  void print( std::ostream& os ) const;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "CellTrackLengthFluxEstimator_def.hpp"

#endif // end CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end CellTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
