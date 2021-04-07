//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SurfaceFluxEstimator.hpp
//! \author Alex Robinson
//! \brief  Surface flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SURFACE_FLUX_ESTIMATOR_HPP
#define MONTE_CARLO_SURFACE_FLUX_ESTIMATOR_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardSurfaceEstimator.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"
#include "Geometry_Model.hpp"

namespace MonteCarlo{

/*! The surface flux estimator class
 * \ingroup particle_crossing_surface_event
 */
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class SurfaceFluxEstimator : public StandardSurfaceEstimator
{

public:

  //! Typedef for the surface id type
  typedef StandardSurfaceEstimator::SurfaceIdType SurfaceIdType;

  //! Typedef for event tags
  typedef StandardSurfaceEstimator::EventTags EventTags;

  //! Constructor
  SurfaceFluxEstimator( const Id id,
                        const double multiplier,
                        const std::vector<SurfaceIdType>& surface_ids,
                        const std::vector<double>& surface_areas );

  //! Constructor (extract surface areas from model)
  SurfaceFluxEstimator( const Id id,
                        const double multiplier,
                        const std::vector<SurfaceIdType>& surface_ids,
                        const Geometry::Model& model );

  //! Destructor
  ~SurfaceFluxEstimator()
  { /* ... */ }

  //! Set the cosine cutoff value
  void setCosineCutoffValue( const double cosine_cutoff ) final override;

  //! Get the cosine cutoff value
  double getCosineCutoffValue() const;

  //! Add estimator contribution from a portion of the current history
  void updateFromParticleCrossingSurfaceEvent(
                                    const ParticleState& particle,
                                    const SurfaceIdType surface_crossing,
                                    const double angle_cosine ) final override;

  //! Print the estimator data summary
  void printSummary( std::ostream& os ) const final override;

private:

  // Default constructor
  SurfaceFluxEstimator();

  // Get the default cosine cutoff
  static double getDefaultCosineCutoff();

  // Serialize the entity estimator
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The cosine cutoff
  double d_cosine_cutoff;
};

// Serialize the entity estimator
template<typename ContributionMultiplierPolicy>
template<typename Archive>
void SurfaceFluxEstimator<ContributionMultiplierPolicy>::serialize( Archive& ar, const unsigned version )
{
  // Serialize the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( StandardSurfaceEstimator );

  // Serialize the local data
  ar & BOOST_SERIALIZATION_NVP( d_cosine_cutoff );
}

//! The weight multiplied surface flux estimator
typedef SurfaceFluxEstimator<WeightMultiplier> WeightMultipliedSurfaceFluxEstimator;

//! The weight and energy multiplied surface flux estimator
typedef SurfaceFluxEstimator<WeightAndEnergyMultiplier> WeightAndEnergyMultipliedSurfaceFluxEstimator;

//! The weight and charge multiplied cell collision flux estimator
typedef SurfaceFluxEstimator<WeightAndChargeMultiplier> WeightAndChargeMultipliedSurfaceFluxEstimator;

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS1_VERSION( SurfaceFluxEstimator, MonteCarlo, 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_SurfaceFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_SURFACE_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SurfaceFluxEstimator.hpp
//---------------------------------------------------------------------------//
