//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardSurfaceEstimator.cpp
//! \author Alex Robinson
//! \brief  Standard surface estimator class definition.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardSurfaceEstimator.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_LoggingMacros.hpp"

namespace MonteCarlo{

// Default constructor
StandardSurfaceEstimator::StandardSurfaceEstimator()
{ /* ... */ }

// Constructor (for flux estimators)
StandardSurfaceEstimator::StandardSurfaceEstimator(
                          const Estimator::idType id,
                          const double multiplier,
                          const std::vector<surfaceIdType>& surface_ids,
                          const std::vector<double>& surface_areas )
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
                          const std::vector<surfaceIdType>& surface_ids )
  : StandardEntityEstimator<surfaceIdType>( id, multiplier, surface_ids ),
    ParticleCrossingSurfaceEventObserver()
{ /* ... */ }

// Assign the particle type to the estimator
/*! \details All particle types can contribute to the estimator. Combinations
 are not allowed.
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

EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::StandardSurfaceEstimator );

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardSurfaceEstimator.cpp
//---------------------------------------------------------------------------//
