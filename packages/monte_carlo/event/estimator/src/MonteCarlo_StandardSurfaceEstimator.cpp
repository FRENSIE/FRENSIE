//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardSurfaceEstimator.cpp
//! \author Alex Robinson
//! \brief  Standard surface estimator class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_StandardSurfaceEstimator.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "Utility_LoggingMacros.hpp"

namespace MonteCarlo{

// Export the estimator data
void StandardSurfaceEstimator::exportData(
                    const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                    const bool process_data ) const
{
  // Export the lower level data first
  BaseEstimatorType::exportData( hdf5_file, process_data );

  // Open the estimator hdf5 file
  EstimatorHDF5FileHandler estimator_hdf5_file( hdf5_file );

  // Set the estimator as a surface estimator
  estimator_hdf5_file.setSurfaceEstimator( this->getId() );
}

// Assign the particle type to the estimator
/*! \details Photons, electrons and neutrons (or their adjoint
 * couterparts) can contribute to the estimator. Combinations are not
 * allowed.
 */
void StandardSurfaceEstimator::assignParticleType(
                                            const ParticleType& particle_type )
{
  if( this->getNumberOfAssignedParticleTypes() != 0 )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                                "Standard surface estimators can "
                                "only have one particle type contribute. "
                                "Since estimator " << this->getId() <<
                                " already has a particle type assigned the "
                                "requested particle type of "
                                << particle_type << " will be ignored!" );
  }
  else
    Estimator::assignParticleType( particle_type );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardSurfaceEstimator.cpp
//---------------------------------------------------------------------------//
