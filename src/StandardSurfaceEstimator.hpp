//---------------------------------------------------------------------------//
//!
//! \file   StandardSurfaceEstimator.hpp
//! \author Alex Robinson
//! \brief  Standard surface estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef STANDARD_SURFACE_ESTIMATOR_HPP
#define STANDARD_SURFACE_ESTIMATOR_HPP

// FACEMC Includes
#include "StandardEntityEstimator.hpp"

namespace FACEMC{

//! The standard surface estimator base class
template<typename SurfaceId>
class StandardSurfaceEstimator : public StandardEntityEstimator<SurfaceId>
{

public:

  //! Constructor
  StandardSurfaceEstimator( const unsigned long long id,
			    const double multiplier,
			    const Teuchos::Array<SurfaceId>& surface_ids,
			    const Teuchos::Array<double>& surface_areas );

  //! Destructor
  ~StandardSurfaceEstimator()
  { /* ... */ }

  //! Set the particle types that can contribute to the estimator
  void setParticleTypes( const Teuchos::Array<ParticleType>& particle_types );

  //! Add estimator contribution from a portion of the current history
  virtual void addPartialHistoryContribution( 
				            const BasicParticleState& particle,
					    const SurfaceId& surface_crossed,
					    const double angle_cosine ) = 0;

};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "StandardSurfaceEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end STANDARD_SURFACE_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end StandardSurfaceEstimator.hpp
//---------------------------------------------------------------------------//
