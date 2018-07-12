//---------------------------------------------------------------------------//
//!
//! \file   EntityEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Entity estimator class definition.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ENTITY_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_ENTITY_ESTIMATOR_DEF_HPP

// Std Lib Includes
#include <sstream>
#include <vector>

namespace MonteCarlo{

// Constructor (for flux estimators)
/*! \details Flux estimators need to divide the first moment by the cell
 * volume or surface area.
 */
template<typename EntityId>
EntityEstimator::EntityEstimator(
                      const uint32_t id,
                      const double multiplier,
                      const std::vector<EntityId>& entity_ids,
		      const std::vector<double>& entity_norm_constants )
  : Estimator( id, multiplier ),
    d_total_norm_constant( 1.0 ),
    d_supplied_norm_constants( true ),
    d_estimator_total_bin_data( 1 )
{
  this->initializeEntityEstimatorMomentsMap( entity_ids );
  this->initializeEntityNormConstantsMap( entity_ids, entity_norm_constants );

  // Calculate the total normalization constant
  this->calculateTotalNormalizationConstant();

  // Initialize the total bin data
  this->resizeEstimatorTotalCollection();
}

// Constructor (for non-flux estimators)
/*! \details Non-flux estimators do not need to divide the first moment by the
 * cell volume or surface area.
 */
template<typename EntityId>
EntityEstimator::EntityEstimator( const uint32_t id,
                                  const double multiplier,
                                  const std::vector<EntityId>& entity_ids )
  : Estimator( id, multiplier ),
    d_total_norm_constant( 1.0 ),
    d_supplied_norm_constants( false ),
    d_estimator_total_bin_data( 1 )
{
  this->initializeEntityEstimatorMomentsMap( entity_ids );
  this->initializeEntityNormConstantsMap( entity_ids );

  // Initialize the total bin data
  this->resizeEstimatorTotalCollection();
}

// Initialize entity estimator moments map
template<typename EntityId>
void EntityEstimator::initializeEntityEstimatorMomentsMap(
                                      const std::vector<EntityId>& entity_ids )
{
  // Make sure there is at least one entity id
  testPrecondition( entity_ids.size() > 0 );

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    // Ignore duplicate entity ids
    if( d_entity_estimator_moments_map.count( entity_ids[i] ) == 0 )
    {
      d_entity_estimator_moments_map[entity_ids[i]].resize(
                                        this->getNumberOfBins()*
                                        this->getNumberOfResponseFunctions() );
    }
    else
    {
      FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                                  "entity id " << entity_ids[i] <<
                                  " has been specified more than once in "
                                  "estimator " << this->getId() <<
                                  ". All but the first occurrence will be "
                                  "ignored."
    }
  }
}

// Initialize the entity estimator moments map
template<typename EntityId>
void EntityEstimator::initializeEntityNormConstantsMap(
                                      const std::vector<EntityId>& entity_ids )
{
  // Make sure there is at least one entity id
  testPrecondition( entity_ids.size() > 0 );

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    // Ignore duplicate entity ids
    if( d_entity_norm_constants_map.count( entity_ids[i] ) == 0 )
      d_entity_norm_constants_map[ entity_ids[i] ] = 1.0;
  }
}

// Initialize the entity estimator moments map
template<typename EntityId>
void EntityEstimator::initializeEntityNormConstantsMap(
                             const std::vector<EntityId>& entity_ids,
                             const std::vector<double>& entity_norm_constants )
{
  // Make sure there is at least one entity id
  testPrecondition( entity_ids.size() > 0 );
  // Make sure every entity id has a normalization constant
  testPrecondition( entity_ids.size() == entity_norm_constants.size() );

  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    // Ignore duplicate entity ids
    if( d_entity_norm_constants_map.count( entity_ids[i] ) == 0 )
      d_entity_norm_constants_map[entity_ids[i]] = entity_norm_constants[i];
  }
}

// Serialize the entity estimator
template<typename Archive>
void EntityEstimator::serialize( Archive& ar, const unsigned version )
{
  // Serialize the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Estimator );

  // Serialize the local data
  ar & BOOST_SERIALIZATION_NVP( d_total_norm_constant );
  ar & BOOST_SERIALIZATION_NVP( d_supplied_norm_constants );
  ar & BOOST_SERIALIZATION_NVP( d_estimator_total_bin_data );
  ar & BOOST_SERIALIZATION_NVP( d_entity_estimator_moments_map );
  ar & BOOST_SERIALIZATION_NVP( d_entity_norm_constants_map );
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( EntityEstimator, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZATION_INST( MonteCarlo, EntityEstimator );

#endif // end MONTE_CARLO_ENTITY_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EntityEstimator_def.hpp
//---------------------------------------------------------------------------//
