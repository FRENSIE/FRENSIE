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
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CellTrackLengthFluxEstimator<WeightMultiplier> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( CellTrackLengthFluxEstimator<WeightAndEnergyMultiplier> );

// Constructor
template<typename ContributionMultiplierPolicy>
CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>::CellTrackLengthFluxEstimator(
                               const Estimator::idType id,
                               const double multiplier,
                               const STLCompliantArrayA<cellIdType>& cell_ids,
	                       const STLCompliantArrayB<double>& cell_volumes )
  : StandardCellEstimator( id, multiplier, cell_ids, cell_volumes ),
    ParticleSubtrackEndingInCellEventObserver()
{ /* ... */ }

// Add estimator contribution from a portion of the current history
template<typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>::updateFromParticleSubtrackEndingInCellEvent(
                                             const ParticleState& particle,
                                             const cellIdType cell_of_subtrack,
                                             const double track_length )
{
  // Make sure the cell is assigned to this estimator
  testPrecondition( this->isEntityAssigned( cell_of_subtrack ) );
  
  if( this->isParticleTypeAssigned( particle.getParticleType() ) )
  {
    const double contribution = track_length*
      ContributionMultiplierPolicy::multiplier( particle );

    EstimatorParticleStateWrapper particle_state_wrapper( particle );
    particle_state_wrapper.calculateStateTimesUsingParticleTimeAsEndTime( track_length );

    this->addPartialHistoryRangeContribution<OBSERVER_TIME_DIMENSION>(
                                                        cell_of_subtrack,
							particle_state_wrapper,
                                                        contribution);
  }
}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>::printSummary( std::ostream& os ) const
{
  os << "Cell Track Length Flux Estimator: " << this->getId() << std::endl;

  this->printImplementation( os, "Cell" );
}

// Set the response functions
template<typename ContributionMultiplierPolicy>
void CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>::setResponseFunctions(
                  const Estimator::ResponseFunctionPointer& response_function )
{
  if( !response_function->isSpatiallyUniform() )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                                "only spatially uniform response functions "
                                "can be assigned to cell track length "
                                "estimators. Estimator " << this->getId() <<
                                " will ignore response function "
                                << response_function->getName() << "!" );
  }
  else
    Estimator::setResponseFunctions( response_functions );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_CELL_TRACK_LENGTH_FLUX_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellTrackLengthFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
