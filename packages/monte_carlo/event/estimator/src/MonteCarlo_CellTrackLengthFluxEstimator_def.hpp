//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellTrackLengthFluxEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator class definition.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
template<typename ContributionMultiplierPolicy>
CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>::CellTrackLengthFluxEstimator()
{ /* ... */ }

// Constructor
template<typename ContributionMultiplierPolicy>
CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>::CellTrackLengthFluxEstimator(
                               const Id id,
                               const double multiplier,
                               const std::vector<CellIdType>& cell_ids,
	                       const std::vector<double>& cell_volumes )
  : StandardCellEstimator( id, multiplier, cell_ids, cell_volumes ),
    ParticleSubtrackEndingInCellEventObserver()
{ /* ... */ }

// Constructor (extract cell volumes from model)
template<typename ContributionMultiplierPolicy>
CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>::CellTrackLengthFluxEstimator(
                               const Id id,
                               const double multiplier,
                               const std::vector<CellIdType>& cell_ids,
	                       const Geometry::Model& model )
  : StandardCellEstimator( id, multiplier, cell_ids, model ),
    ParticleSubtrackEndingInCellEventObserver()
{ /* ... */ }

// Add estimator contribution from a portion of the current history
template<typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>::updateFromParticleSubtrackEndingInCellEvent(
                                             const ParticleState& particle,
                                             const CellIdType cell_of_subtrack,
                                             const double track_length )
{
  // Make sure that the particle type is assigned to this estimator
  testPrecondition( this->isParticleTypeAssigned( particle.getParticleType() ) );
  // Make sure the cell is assigned to this estimator
  testPrecondition( this->isEntityAssigned( cell_of_subtrack ) );

  const double contribution = track_length*
    ContributionMultiplierPolicy::multiplier( particle );

  ObserverParticleStateWrapper particle_state_wrapper( particle );
  particle_state_wrapper.calculateStateTimesUsingParticleTimeAsEndTime( track_length );

  this->addPartialHistoryRangeContribution( cell_of_subtrack,
                                            particle_state_wrapper,
                                            contribution );
}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>::printSummary( std::ostream& os ) const
{
  os << "Cell Track Length Flux Estimator: " << this->getId() << "\n";

  this->printImplementation( os, "Cell" );

  os << std::flush;
}

// Assign discretization to an estimator dimension
template<typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>::assignDiscretization(
  const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
  const bool )
{
  if( bins->getDimension() == OBSERVER_TIME_DIMENSION )
    StandardCellEstimator::assignDiscretization( bins, true );
  else
    StandardCellEstimator::assignDiscretization( bins, false );
}

// Assign the response functions
/*! \details This method does a very crude check that the response function
 * is spatially uniform (see the MonteCarlo::ParticleResponse::isSpatiallyUniform
 * details for the limitations of this method). If time bins have been set, the
 * response function must also be uniform over all of the specified time bins.
 */
template<typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>::assignResponseFunction(
             const std::shared_ptr<const ParticleResponse>& response_function )
{
  if( !response_function->isSpatiallyUniform() )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                                "only spatially uniform response functions "
                                "can be assigned to cell track-length "
                                "estimators. Estimator " << this->getId() <<
                                " will ignore response function "
                                << response_function->getName() << "!" );
  }
  else
    Estimator::assignResponseFunction( response_function );
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightMultipliedCellTrackLengthFluxEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, CellTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightAndEnergyMultipliedCellTrackLengthFluxEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, CellTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WeightAndChargeMultipliedCellTrackLengthFluxEstimator, MonteCarlo );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, CellTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> );

#endif // end MONTE_CARLO_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellTrackLengthFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
