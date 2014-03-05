//---------------------------------------------------------------------------//
//!
//! \file   StandardEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Standard estimator class definition.
//!
//---------------------------------------------------------------------------//

#ifndef STANDARD_ESTIMATOR_DEF_HPP
#define STANDARD_ESTIMATOR_DEF_HPP

// FACEMC Includes
#include "ContractException.hpp"

namespace FACEMC{

// Default constructor
  template<typename EntityId>
StandardEstimator<EntityId>::StandardEstimator()
  : Estimator(),
    d_entity(),
    d_current_history_first_moments( 1 )
{ /* ... */ }

// Constructor
template<typename EntityId>
StandardEstimator<EntityId>::StandardEstimator( const unsigned long long id,
						const EntityId& entity_id,
						const double norm_constant,
						const double multiplier )
  : Estimator( id, norm_constant, multiplier ),
    d_entity_id( entity_id )
{
  d_current_history_first_moments.resize( getNumberOfBins() );
}

// Set the energy bin boundaries
template<typename EntityId>
void StandardEstimator<EntityId>::setEnergyBinBoundaries(
		          const Teuchos::Array<double>& energy_bin_boundaries )
{
  Esimator::setEnergyBinBoundaries( energy_bin_boundaries );
  
  d_current_history_first_moments.resize( getNumberOfBins() );
}

// Set the cosine bin boundaries
template<typename EntityId>
void StandardEstimator<EntityId>::setCosineBinBoundaries(
			  const Teuchos::Array<double>& cosine_bin_boundaries )
{
  Estimator::setCosineBinBoundaries( cosine_bin_boundaries );

  d_current_history_first_moments.resize( getNumberOfBins() );
}

// Set the time bin boundaries
template<typename EntityId>
void StandardEstimator<EntityId>::setTimeBinBoundaries(
			    const Teuchos::Array<double>& time_bin_boundaries )
{
  Estimator::setTimeBinBoundaries( time_bin_boundaries );

  d_current_history_first_moments.resize( getNumberOfBins() );
}

// Set the collision number bins
template<typename EntityId>
void StandardEstimator<EntityId>::setCollisionNumberBins(
			  const Teuchos::Array<double>& collision_number_bins )
{
  Estimator::setCollisionNumberBins( collision_number_bins );

  d_current_history_first_moments.resize( getNumberOfBins() );
}

// Set the response functions
template<typename EntityId>
void StandardEstimator<EntityId>::setResponseFunctions(
			 const Teuchos::Array<Teuchos::RCP<ResponseFunction> >&
			 response_functions )
{
  Estimator::setResponseFunctions( response_functions );

  d_current_history_first_moments.resize( getNumberOfBins() );
}

// Add estimator contribution from a portion of the current history
/*! \details The contribution is assumed to be processed (i.e. a raw
 * contribution multiplied by the particle weight and possibly the particle
 * energy). The contribution will be multiplied by each of the response 
 * function values (separately).
 */
template<typename EntityId>
void StandardEstimator<EntityId>::addPartialHistoryContribution(
				       const BasicParticleState& particle,
				       const double contribution,
				       const double angle_cosine )
{
  // Make sure that the contribution is valid
  testPrecondition( !ST::isnaninf( contribution ) );
  // Make sure that the angle cosine is valid
  testPrecondition( angle_cosine == angle_cosine );
  testPrecondition( angle_cosine >= -1.0 );
  testPrecondition( angle_cosine <= 1.0 );

  // Add the partial contribution to the appropriate bin
  if( isParticleInEstimatorPhaseSpace( particle, angle_cosine ) )
  {
    for( unsigned i = 0; i < getNumberOfResponseFunctions(); ++i )
    {
      double response_function_value = evaluateResponseFunction( particle, i );
      
      unsigned bin_offset = calculateBinIndex( particle, anle_cosine, i );

      d_current_history_first_moments[bin_offest] += 
	contribution*response_function_value;
    }
  }
}

// Commit the contribution from the current history to the estimator
/*! \details The contribution from the current history will be added to the
 * estimator. The constribution to the second, third and fourth moments of the 
 * estimator will also be calculated. This function must be called every time
 * a new history is started.
 */
template<typename EntityId>
void StandardEstimator<EntityId>::commitHistoryContribution()
{
  double total_first_moment_contribution;
  
  for( unsigned i = 0; i < getNumberOfResponseFunctions; ++i )
  {
    total_first_moment_contribution = 0.0;

    unsigned number_of_bins_for_response = getNumberOfBins()/
      getNumberOfResponseFunctions;

    for( unsigned j = 0; j < number_of_bins_for_response; ++j )
    {
      unsigned bin_index = j + number_of_bins*i;

      total_first_moment_contribution +=
	d_current_history_first_moments[bin_offset];

      commitHistoryContributionToBin( 
				 bin_index,
				 d_current_history_first_moments[bin_offset] );
    }

    commitHistoryContributionToTotal( i, total_first_moment_contribution );
  }
}

// Return the entity handle that this estimator is assigned to
template<typename EntityId>
const EntityId& StandardEstimator<EntityId>::getEntityId() const
{
  return d_entity_handle;
}
	 
} // end FACEMC namespace

#endif // end STANDARD_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end StandardEstimator_def.hpp
//---------------------------------------------------------------------------//
