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
void StandardSurfaceEstimator::exportData( const std::string& hdf5_file_name,
                                           const bool process_data ) const
{
  // Export the lower level data first
  StandardEntityEstimator<Geometry::ModuleTraits::InternalSurfaceHandle>::exportData( 
								hdf5_file_name,
								process_data );

  // Open the hdf5 file
  EstimatorHDF5FileHandler hdf5_file( hdf5_file_name, 
                                      EstimatorHDF5FileHandler::APPEND_ESTIMATOR_HDF5_FILE );

  // Set the estimator as a surface estimator
  hdf5_file.setSurfaceEstimator( this->getId() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardSurfaceEstimator.cpp
//---------------------------------------------------------------------------//
