//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardEntityEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Standard entity estimator class definition.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ENTITY_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_STANDARD_ENTITY_ESTIMATOR_DEF_HPP

namespace MonteCarlo{

// Constructor (for flux estimators)
template<typename EntityId>
StandardEntityEstimator::StandardEntityEstimator(
                             const uint32_t id,
                             const double multiplier,
                             const std::vector<EntityId>& entity_ids,
                             const std::vector<double>& entity_norm_constants )
  : EntityEstimator( id, multiplier, entity_ids, entity_norm_constants ),
    d_total_estimator_moments( 1 ),
    d_update_tracker( 1 )
{
  this->initializeMomentsMaps( entity_ids );
}

// Constructor (for non-flux estimators)
template<typename EntityId>
StandardEntityEstimator::StandardEntityEstimator(
                                      const uint32_t id,
                                      const double multiplier,
			              const std::vector<EntityId>& entity_ids )
  : EntityEstimator( id, multiplier, entity_ids ),
    d_total_estimator_moments( 1 ),
    d_update_tracker( 1 )
{
  this->initializeMomentsMaps( entity_ids );
}

// Initialize the moments maps
template<typename EntityId>
void StandardEntityEstimator::initializeMomentsMaps(
                                      const std::vector<EntityId>& entity_ids )
{
  // Set up the entity maps
  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    // Ignore duplicate entity ids
    if( d_entity_total_estimator_moments_map.find( entity_ids[i] ) ==
        d_entity_total_estimator_moments_map.end() )
    {
      d_entity_total_estimator_moments_map[ entity_ids[i] ].resize(
				        this->getNumberOfResponseFunctions() );
    }
  }
}

// Save the data to an archive
template<typename Archive>
void StandardEntityEstimator::save( Archive& ar, const unsigned version ) const
{
  // Save the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( EntityEstimator );

  // Save the local data
  ar & BOOST_SERIALIZATION_NVP( d_total_estimator_moments );
  ar & BOOST_SERIALIZATION_NVP( d_total_estimator_moments );
}

// Load the data from an archive
template<typename Archive>
void StandardEntityEstimator::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( EntityEstimator );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_total_estimator_moments );
  ar & BOOST_SERIALIZATION_NVP( d_total_estimator_moments );

  // Initialize the thread data
  d_update_tracker.resize( 1 );
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( StandardEntityEstimator, MonteCarlo );

EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, StandardEntityEstimator );

#endif // end MONTE_CARLO_STANDARD_ENTITY_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEntityEstimator_def.hpp
//---------------------------------------------------------------------------//
