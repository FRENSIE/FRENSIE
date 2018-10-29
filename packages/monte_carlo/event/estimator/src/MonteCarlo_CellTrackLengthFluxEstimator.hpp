//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellTrackLengthFluxEstimator.hpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP
#define MONTE_CARLO_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

// Boost Includes
#include <boost/mpl/vector.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardCellEstimator.hpp"
#include "MonteCarlo_ParticleSubtrackEndingInCellEventObserver.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"

namespace MonteCarlo{

/*! The cell track length flux estimator class
 * \ingroup particle_subtrack_ending_in_cell_event
 */
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class CellTrackLengthFluxEstimator : public StandardCellEstimator,
				     public ParticleSubtrackEndingInCellEventObserver
{

public:

  //! Typedef for the cell id type
  typedef StandardCellEstimator::CellIdType CellIdType;

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleSubtrackEndingInCellEventObserver::EventTag>
  EventTags;

  //! Constructor
  CellTrackLengthFluxEstimator( const Id id,
                                const double multiplier,
                                const std::vector<CellIdType>& cell_ids,
                                const std::vector<double>& cell_volumes );

  //! Constructor (extract cell volumes from model)
  CellTrackLengthFluxEstimator( const Id id,
                                const double multiplier,
                                const std::vector<CellIdType>& cell_ids,
                                const Geometry::Model& model );

  //! Destructor
  ~CellTrackLengthFluxEstimator()
  { /* ... */ }

  //! Add current history estimator contribution
  void updateFromParticleSubtrackEndingInCellEvent(
                                    const ParticleState& particle,
                                    const CellIdType cell_of_subtrack,
                                    const double track_length ) final override;

  //! Print the estimator data summary
  void printSummary( std::ostream& os ) const final override;

private:

  // Default constructor
  CellTrackLengthFluxEstimator();

  // Assign discretization to an estimator dimension
  void assignDiscretization( const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
                             const bool range_dimension ) override;

  // Assign response function to the estimator
  void assignResponseFunction( const std::shared_ptr<const ParticleResponse>& response_function ) final override;

  // Serialize the estimator data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

// Serialize the estimator data
template<typename ContributionMultiplierPolicy>
template<typename Archive>
void CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>::serialize( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( StandardCellEstimator );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleSubtrackEndingInCellEventObserver );
}

//! The weight multiplied cell track length flux estimator
typedef CellTrackLengthFluxEstimator<WeightMultiplier> WeightMultipliedCellTrackLengthFluxEstimator;

//! The weight and energy multiplied cell track length flux estimator
typedef CellTrackLengthFluxEstimator<WeightAndEnergyMultiplier> WeightAndEnergyMultipliedCellTrackLengthFluxEstimator;

//! The weight and charge multiplied cell collision flux estimator
typedef CellTrackLengthFluxEstimator<WeightAndChargeMultiplier> WeightAndChargeMultipliedCellTrackLengthFluxEstimator;

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS1_VERSION( CellTrackLengthFluxEstimator, MonteCarlo, 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CellTrackLengthFluxEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
