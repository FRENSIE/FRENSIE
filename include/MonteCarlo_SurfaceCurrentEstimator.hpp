//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SurfaceCurrentEstimator.hpp
//! \author Alex Robinson
//! \brief  Surface current estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_SURFACE_CURRENT_ESTIMATOR_HPP
#define FACEMC_SURFACE_CURRENT_ESTIMATOR_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardSurfaceEstimator.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"

namespace MonteCarlo{

//! The surface current estimator class
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class SurfaceCurrentEstimator : public StandardSurfaceEstimator
{

public:

  //! Typedef for event tags
  typedef StandardSurfaceEstimator::EventTags EventTags;

  //! Constructor
  SurfaceCurrentEstimator( 
   const Estimator::idType id,
   const double multiplier,
   const Teuchos::Array<StandardSurfaceEstimator::surfaceIdType>& surface_ids);

  //! Destructor
  ~SurfaceCurrentEstimator()
  { /* ... */ }
  
  //! Set the response functions
  void setResponseFunctions( 
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions );

  //! Add current history estimator contribution
  void updateFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double angle_cosine );
  
  //! Print the estimator data
  void print( std::ostream& os ) const;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_SurfaceCurrentEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_SURFACE_CURRENT_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SurfaceCurrentEstimator.hpp
//---------------------------------------------------------------------------//
