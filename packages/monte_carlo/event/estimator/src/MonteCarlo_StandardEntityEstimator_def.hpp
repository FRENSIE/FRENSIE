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
template<typename InputEntityId>
StandardEntityEstimator::StandardEntityEstimator(
                             const Id id,
                             const double multiplier,
                             const std::vector<InputEntityId>& entity_ids,
                             const std::vector<double>& entity_norm_constants )
  : EntityEstimator( id, multiplier, entity_ids, entity_norm_constants ),
    d_total_estimator_moments( 1 ),
    d_entity_total_estimator_moments_map(),
    d_total_estimator_moment_snapshots( 1 ),
    d_entity_total_estimator_moment_snapshots_map(),
    d_total_estimator_histograms( 1, Utility::SampleMomentHistogram<double>( this->getSampleMomentHistogramBins() ) ),
    d_entity_total_estimator_histograms_map(),
    d_update_tracker( 1 )
{
  this->initializeMomentsMaps( entity_ids );
}

// Constructor (for non-flux estimators)
template<typename InputEntityId>
StandardEntityEstimator::StandardEntityEstimator(
                                 const Id id,
                                 const double multiplier,
                                 const std::vector<InputEntityId>& entity_ids )
  : EntityEstimator( id, multiplier, entity_ids ),
    d_total_estimator_moments( 1 ),
    d_entity_total_estimator_moments_map(),
    d_total_estimator_moment_snapshots( 1 ),
    d_entity_total_estimator_moment_snapshots_map(),
    d_total_estimator_histograms( 1, Utility::SampleMomentHistogram<double>( this->getSampleMomentHistogramBins() ) ),
    d_entity_total_estimator_histograms_map(),
    d_update_tracker( 1 )
{
  this->initializeMomentsMaps( entity_ids );
}

// Initialize the moments maps
template<typename InputEntityId>
void StandardEntityEstimator::initializeMomentsMaps(
                                 const std::vector<InputEntityId>& entity_ids )
{
  // Set up the entity maps
  for( size_t i = 0; i < entity_ids.size(); ++i )
  {
    // Ignore duplicate entity ids
    if( d_entity_total_estimator_moments_map.find( entity_ids[i] ) ==
        d_entity_total_estimator_moments_map.end() )
    {
      d_entity_total_estimator_moments_map[entity_ids[i]].resize(
				        this->getNumberOfResponseFunctions() );

      d_entity_total_estimator_moment_snapshots_map[entity_ids[i]].resize(
                                        this->getNumberOfResponseFunctions() );

      Utility::SampleMomentHistogram<double>
        default_histogram( this->getSampleMomentHistogramBins() );

      d_entity_total_estimator_histograms_map[entity_ids[i]].resize(
                                          this->getNumberOfResponseFunctions(),
                                          default_histogram );
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
  ar & BOOST_SERIALIZATION_NVP( d_entity_total_estimator_moments_map );
  ar & BOOST_SERIALIZATION_NVP( d_total_estimator_moment_snapshots );
  ar & BOOST_SERIALIZATION_NVP( d_entity_total_estimator_moment_snapshots_map );
  ar & BOOST_SERIALIZATION_NVP( d_total_estimator_histograms );
  ar & BOOST_SERIALIZATION_NVP( d_entity_total_estimator_histograms_map );
}

// Load the data from an archive
template<typename Archive>
void StandardEntityEstimator::load( Archive& ar, const unsigned version )
{
  // Load the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( EntityEstimator );

  // Load the local data
  ar & BOOST_SERIALIZATION_NVP( d_total_estimator_moments );
  ar & BOOST_SERIALIZATION_NVP( d_entity_total_estimator_moments_map );
  ar & BOOST_SERIALIZATION_NVP( d_total_estimator_moment_snapshots );
  ar & BOOST_SERIALIZATION_NVP( d_entity_total_estimator_moment_snapshots_map );
  ar & BOOST_SERIALIZATION_NVP( d_total_estimator_histograms );
  ar & BOOST_SERIALIZATION_NVP( d_entity_total_estimator_histograms_map );

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
