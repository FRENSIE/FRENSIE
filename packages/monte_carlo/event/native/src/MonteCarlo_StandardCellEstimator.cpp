//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCellEstimator.cpp
//! \author Alex Robinson
//! \brief  Standard cell estimator class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_StandardCellEstimator.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"

namespace MonteCarlo{

// Constructor
StandardCellEstimator::StandardCellEstimator(
	     const Estimator::idType id,
	     const double multiplier,
	     const Teuchos::Array<StandardCellEstimator::cellIdType>& cell_ids,
	     const Teuchos::Array<double>& cell_volumes )
  : StandardEntityEstimator<cellIdType>(id, multiplier, cell_ids, cell_volumes)
{ /* ... */ }

// Set the particle types that can contribute to the estimator
/*! \details Photons, electrons and neutrons (or their adjoint
 * couterparts) can contribute to the estimator. Combinations are not 
 * allowed.
 */
void StandardCellEstimator::setParticleTypes(
			   const Teuchos::Array<ParticleType>& particle_types )
{
  if( particle_types.size() > 1 )
  {
    std::cerr << "Warning: Standard cell estimators can only have one "
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
void StandardCellEstimator::exportData( 
                    const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                    const bool process_data ) const
{
  // Export the lower level data first
  StandardEntityEstimator<Geometry::ModuleTraits::InternalCellHandle>::exportData( 
								hdf5_file,
								process_data );

  // Open the estimator hdf5 file
  EstimatorHDF5FileHandler estimator_hdf5_file( hdf5_file );

  // Set the estimator as a cell estimator
  estimator_hdf5_file.setCellEstimator( this->getId() );
}

// Assign bin boundaries to an estimator dimension
/*! \details The MonteCarlo::COSINE_DIMENSION cannot be discretized in standard
 * cell estimators.
 */
void StandardCellEstimator::assignBinBoundaries(
      const std::shared_ptr<EstimatorDimensionDiscretization>& bin_boundaries )
{
  if( bin_boundaries->getDimension() == COSINE_DIMENSION )
  {
    std::cerr << "Warning: " << bin_boundaries->getDimensionName()
	      << " bins cannot be set for standard cell estimators. The bins "
	      << "requested for standard cell estimator " << this->getId()
	      << " will be ignored."
	      << std::endl;
  }
  else
    StandardEntityEstimator<cellIdType>::assignBinBoundaries( bin_boundaries );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCellEstimator.cpp
//---------------------------------------------------------------------------//
