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
#include "StandardSurfaceEstimator.hpp"
#include "EstimatorContributionMultiplierPolicy.hpp"

namespace FACEMC{

//! The surface current estimator class
template<typename SurfaceId,
	 typename ContributionMultiplierPolicy = WeightMultiplier>
class SurfaceCurrentEstimator : public StandardSurfaceEstimator<SurfaceId>
{

public:

  //! Constructor
  SurfaceCurrentEstimator( const unsigned long long id,
			   const double multiplier,
			   const Teuchos::Array<SurfaceId>& surface_ids,
			   const Teuchos::Array<double>& surface_areas );   

  //! Destructor
  ~SurfaceCurrentEstimator()
  { /* ... */ }
  
  //! Set the response functions
  void setResponseFunctions( 
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions );

  //! Add estimator contribution from a portion of the current history
  void addPartialHistoryContribution( const BasicParticleState& particle,
				      const SurfaceId& surface_crossed,
				      const double angle_cosine );
  
  //! Print the estimator data
  void print( std::ostream& os ) const;
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
