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

  //! Typedef for event tags
  typedef StandardSurfaceEstimator::EventTags EventTags;

  //! Constructor
  template<typename<typename,typename...> class STLCompliantArray>
  SurfaceCurrentEstimator(
              const Estimator::idType id,
              const double multiplier,
              const STLCompliantArray<StandardSurfaceEstimator::surfaceIdType>&
              surface_ids);

  //! Destructor
  ~SurfaceCurrentEstimator()
  { /* ... */ }

  //! Add current history estimator contribution
  void updateFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
	  const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double angle_cosine ) override;

  //! Print the estimator data summary
  void printSummary( std::ostream& os ) const override;

private:

  //! Assign the particle type to the estimator
  void assignParticleType( const ParticleType particle_type ) override;
};

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
