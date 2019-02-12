//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SurfaceCurrentEstimator.hpp
//! \author Alex Robinson
//! \brief  Surface current estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SURFACE_CURRENT_ESTIMATOR_HPP
#define MONTE_CARLO_SURFACE_CURRENT_ESTIMATOR_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardSurfaceEstimator.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"

namespace MonteCarlo{

/*! The surface current estimator class
 * \ingroup particle_crossing_surface_event
 */
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class SurfaceCurrentEstimator : public StandardSurfaceEstimator
{

public:

  //! Typedef for the surface id type
  typedef StandardSurfaceEstimator::SurfaceIdType SurfaceIdType;

  //! Typedef for event tags
  typedef StandardSurfaceEstimator::EventTags EventTags;

  //! Constructor
  SurfaceCurrentEstimator(
                    const Id id,
                    const double multiplier,
                    const std::vector<StandardSurfaceEstimator::SurfaceIdType>&
                    surface_ids );

  //! Destructor
  ~SurfaceCurrentEstimator()
  { /* ... */ }

  //! Add current history estimator contribution
  void updateFromParticleCrossingSurfaceEvent(
                 const ParticleState& particle,
                 const Geometry::Model::EntityId surface_crossing,
                 const double angle_cosine ) final override;

  //! Print the estimator data summary
  void printSummary( std::ostream& os ) const final override;

private:

  // Default constructor
  SurfaceCurrentEstimator();

  // Assign response function to the estimator
  void assignResponseFunction( const std::shared_ptr<const ParticleResponse>& response_function ) final override;

  // Serialize the entity estimator
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

// Serialize the entity estimator
template<typename ContributionMultiplierPolicy>
template<typename Archive>
void SurfaceCurrentEstimator<ContributionMultiplierPolicy>::serialize( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( StandardSurfaceEstimator );
}

//! The weight multiplied surface current estimator
typedef SurfaceCurrentEstimator<WeightMultiplier> WeightMultipliedSurfaceCurrentEstimator;

//! The weight and energy multiplied surface current estimator
typedef SurfaceCurrentEstimator<WeightAndEnergyMultiplier> WeightAndEnergyMultipliedSurfaceCurrentEstimator;

//! The weight and charge multiplied cell collision flux estimator
typedef SurfaceCurrentEstimator<WeightAndChargeMultiplier> WeightAndChargeMultipliedSurfaceCurrentEstimator;

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_SurfaceCurrentEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_SURFACE_CURRENT_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SurfaceCurrentEstimator.hpp
//---------------------------------------------------------------------------//
