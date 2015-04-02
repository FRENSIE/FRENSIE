//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardSurfaceEstimator.cpp
//! \author Alex Robinson
//! \brief  Standard surface estimator class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_StandardSurfaceEstimator.hpp"

namespace MonteCarlo{

// Initialize the static member data
double StandardSurfaceEstimator::angle_cosine_cutoff = 0.001;

// Set the angle cosine cutoff value
void StandardSurfaceEstimator::setAngleCosineCutoff(
					     const double angle_cosine_cutoff )
{
  // Make sure the angle cosine cutoff is valid
  testPrecondition( angle_cosine_cutoff > 0.0 );
  testPrecondition( angle_cosine_cutoff < 1.0 );
  
  StandardSurfaceEstimator::angle_cosine_cutoff = angle_cosine_cutoff;
}

// Constructor (for flux estimators)
StandardSurfaceEstimator::StandardSurfaceEstimator(
    const Estimator::idType id,
    const double multiplier,
    const Teuchos::Array<StandardSurfaceEstimator::surfaceIdType>& surface_ids,
    const Teuchos::Array<double>& surface_areas )
  : StandardEntityEstimator<surfaceIdType>( id, 
					    multiplier, 
					    surface_ids, 
					    surface_areas ),
    ParticleCrossingSurfaceEventObserver()
{ /* ... */ }

// Constructor (for non-flux estimators)
StandardSurfaceEstimator::StandardSurfaceEstimator(
   const Estimator::idType id,
   const double multiplier,
   const Teuchos::Array<StandardSurfaceEstimator::surfaceIdType>& surface_ids )
  : StandardEntityEstimator<surfaceIdType>( id, multiplier, surface_ids ),
    ParticleCrossingSurfaceEventObserver()
{ /* ... */ }

// Set the particle types that can contribute to the estimator
/*! \details Photons, electrons and neutrons (or their adjoint
 * couterparts) can contribute to the estimator. Combinations are not 
 * allowed.
 */
void StandardSurfaceEstimator::setParticleTypes( 
			   const Teuchos::Array<ParticleType>& particle_types )
{
  if( particle_types.size() > 1 )
  {
    std::cerr << "Warning: Standard surface estimators can only have one "
	      << "particle type contribute. All but the first particle type "
	      << "requested in estimator " << this->getId() 
	      << " will be ignored."
	      << std::endl;
    
    Teuchos::Array<ParticleType> valid_particle_types( 1 );
    valid_particle_types[0] = particle_types.front();
    
    Estimator::setParticleTypes( valid_particle_types );
  }
  else
    Estimator::setParticleTypes( particle_types );
}

// Export the estimator data
void StandardSurfaceEstimator::exportData(
					  EstimatorHDF5FileHandler& hdf5_file,
					  const bool process_data ) const
{
  // Export the lower level data first
  StandardEntityEstimator<Geometry::ModuleTraits::InternalSurfaceHandle>::exportData( 
								hdf5_file,
								process_data );

  // Set the estimator as a surface estimator
  hdf5_file.setSurfaceEstimator( this->getId() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardSurfaceEstimator.cpp
//---------------------------------------------------------------------------//
