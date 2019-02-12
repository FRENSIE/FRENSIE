//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardSurfaceEstimator.cpp
//! \author Alex Robinson
//! \brief  Standard surface estimator class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_StandardSurfaceEstimator.hpp"
#include "Geometry_AdvancedModel.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Default constructor
StandardSurfaceEstimator::StandardSurfaceEstimator()
{ /* ... */ }

// Constructor (for flux estimators)
StandardSurfaceEstimator::StandardSurfaceEstimator(
                          const Id id,
                          const double multiplier,
                          const std::vector<SurfaceIdType>& surface_ids,
                          const std::vector<double>& surface_areas )
  : StandardEntityEstimator( id, multiplier, surface_ids, surface_areas ),
    ParticleCrossingSurfaceEventObserver()
{ /* ... */ }

// Constructor (for flux estimators)
StandardSurfaceEstimator::StandardSurfaceEstimator(
                                 const Id id,
                                 const double multiplier,
                                 const std::vector<SurfaceIdType>& surface_ids,
                                 const Geometry::Model& model )
  : StandardEntityEstimator( id, multiplier ),
    ParticleCrossingSurfaceEventObserver()
{
  // Extract the surface areas
  TEST_FOR_EXCEPTION( !model.isAdvanced(),
                      std::runtime_error,
                      "An advanced model (a model with surface info) must be "
                      "used with surface estimators!" );

  const Geometry::AdvancedModel& advanced_model =
    dynamic_cast<const Geometry::AdvancedModel&>( model );

  EntityEstimator::EntityNormConstMap surface_id_area_map;

  for( size_t i = 0; i < surface_ids.size(); ++i )
  {
    TEST_FOR_EXCEPTION( !advanced_model.doesSurfaceExist( surface_ids[i] ),
                        std::runtime_error,
                        "A requested surface (" << surface_ids[i] << ") for "
                        "estimator " << id << " does not exist!" );

    if( surface_id_area_map.find( surface_ids[i] ) !=
        surface_id_area_map.end() )
    {
      FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                                  "A surface (" << surface_ids[i] << ") was "
                                  "requested multiple times for estimator "
                                  << id << "!" );
    }
    
    surface_id_area_map[surface_ids[i]] =
      advanced_model.getSurfaceArea( surface_ids[i] ).value();
  }

  this->assignEntities( surface_id_area_map );
}

// Constructor (for non-flux estimators)
StandardSurfaceEstimator::StandardSurfaceEstimator(
                          const Id id,
                          const double multiplier,
                          const std::vector<SurfaceIdType>& surface_ids )
  : StandardEntityEstimator( id, multiplier, surface_ids ),
    ParticleCrossingSurfaceEventObserver()
{ /* ... */ }

// Check if the estimator is a cell estimator
bool StandardSurfaceEstimator::isCellEstimator() const
{
  return false;
}

// Check if the estimator is a surface estimator
bool StandardSurfaceEstimator::isSurfaceEstimator() const
{
  return true;
}

// Check if the estimator is a mesh estimator
bool StandardSurfaceEstimator::isMeshEstimator() const
{
  return false;
}

// Assign the particle type to the estimator
/*! \details All particle types can contribute to the estimator. Combinations
 are not allowed.
 */
void StandardSurfaceEstimator::assignParticleType(
                                             const ParticleType particle_type )
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

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::StandardSurfaceEstimator );

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardSurfaceEstimator.cpp
//---------------------------------------------------------------------------//
