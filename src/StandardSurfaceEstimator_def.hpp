//---------------------------------------------------------------------------//
//!
//! \file   StandardSurfaceEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Standard surface estimator class definition.
//!
//---------------------------------------------------------------------------//

#ifndef STANDARD_SURFACE_ESTIMATOR_DEF_HPP
#define STANDARD_SURFACE_ESTIMATOR_DEF_HPP

namespace FACEMC{

// Constructor
template<typename SurfaceId>
StandardSurfaceEstimator<SurfaceId>::StandardSurfaceEstimator(
				  const unsigned long long id,
				  const double multiplier,
			          const Teuchos::Array<SurfaceId>& surface_ids,
				  const Teuchos::Array<double>& surface_areas )
  : StandardEntityEstimator( id, mulitiplier, surface_ids, surface_areas )
{ /* ... */ }

// Set the particle types that can contribute to the estimator
/*! \details Photons, electrons and neutrons (or their adjoint
 * couterparts) can contribute to the estimator. Combinations are not 
 * allowed.
 */
template<typename SurfaceId>
void StandardSurfaceEstimator<SurfaceId>::setParticleTypes( 
			   const Teuchos::Array<ParticleType>& particle_types )
{
  // Make sure only one particle type has been specified
  testPrecondition( particle_types.size() == 1 );

  Estimator::setParticleTypes( particle_types );
}

} // end FACEMC namespace

#endif // end STANDARD_SURFACE_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end StandardSurfaceEstimator_def.hpp
//---------------------------------------------------------------------------//
