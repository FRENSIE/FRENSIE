//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellCollisionFluxEstimator.hpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CELL_COLLISION_FLUX_ESTIMATOR_HPP
#define MONTE_CARLO_CELL_COLLISION_FLUX_ESTIMATOR_HPP

// Boost Includes
#include <boost/mpl/vector.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardCellEstimator.hpp"
#include "MonteCarlo_ParticleCollidingInCellEventObserver.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"

namespace MonteCarlo{

/*! The cell collision flux estimator class
 * \ingroup particle_colliding_in_cell_event
 */
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class CellCollisionFluxEstimator : public StandardCellEstimator,
				   public ParticleCollidingInCellEventObserver
{

public:

  //! Typedef for the cell id type
  typedef StandardCellEstimator::CellIdType CellIdType;

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleCollidingInCellEventObserver::EventTag>
  EventTags;

  //! Constructor
  CellCollisionFluxEstimator( const Id id,
                              const double multiplier,
                              const std::vector<CellIdType>& cell_ids,
                              const std::vector<double>& cell_volumes );

  //! Constructor (extract cell volumes from model)
  CellCollisionFluxEstimator( const Id id,
                              const double multiplier,
                              const std::vector<CellIdType>& cell_ids,
                              const Geometry::Model& model );

  //! Destructor
  ~CellCollisionFluxEstimator()
  { /* ... */ }

  //! Add current history estimator contribution
  void updateFromParticleCollidingInCellEvent(
                     const ParticleState& particle,
                     const CellIdType cell_of_collision,
                     const double inverse_total_cross_section ) final override;

  //! Print the estimator data summary
  void printSummary( std::ostream& os ) const final override;

private:

  // Default constructor
  CellCollisionFluxEstimator();

  // Serialize the estimator data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

// Serialize the estimator data
template<typename ContributionMultiplierPolicy>
template<typename Archive>
void CellCollisionFluxEstimator<ContributionMultiplierPolicy>::serialize( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( StandardCellEstimator );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleCollidingInCellEventObserver );
}

//! The weight multiplied cell collision flux estimator
typedef CellCollisionFluxEstimator<WeightMultiplier> WeightMultipliedCellCollisionFluxEstimator;

//! The weight and energy multiplied cell collision flux estimator
typedef CellCollisionFluxEstimator<WeightAndEnergyMultiplier> WeightAndEnergyMultipliedCellCollisionFluxEstimator;

//! The weight and charge multiplied cell collision flux estimator
typedef CellCollisionFluxEstimator<WeightAndChargeMultiplier> WeightAndChargeMultipliedCellCollisionFluxEstimator;

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS1_VERSION( CellCollisionFluxEstimator, MonteCarlo, 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CellCollisionFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_CELL_COLLISION_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellCollisionFluxEstimator.hpp
//---------------------------------------------------------------------------//
