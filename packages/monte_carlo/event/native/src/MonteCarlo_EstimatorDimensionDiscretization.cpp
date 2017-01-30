//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorDimensionDiscretization.cpp
//! \author Alex Robinson
//! \brief  Estimator dimension discretization base class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_EstimatorDimensionDiscretization.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp"

namespace MonteCarlo{

// Constructor
EstimatorDimensionDiscretization::EstimatorDimensionDiscretization(
				  const ObserverPhaseSpaceDimension dimension )
  : d_dimension( dimension )
{ /* ... */ }

// Return the dimension that has been discretized
ObserverPhaseSpaceDimension
EstimatorDimensionDiscretization::getDimension() const
{
  return d_dimension;
}

// Calculate the indices of the bins that the value range falls in
/*! \details There are only a few dimensions where ranges of values are
 * acceptable (e.g. time and particle source id). For these dimensions
 * it is possible for the particle state to actually fall in multiple 
 * bins. The weight is used to report the fraction of the range that falls
 * with the bin (indicated by the first value of the pair).
 */
void EstimatorDimensionDiscretization::calculateBinIndicesOfRange(
                   const EstimatorParticleStateWrapper& particle_state_wrapper,
                   Teuchos::Array<Utility::Pair<unsigned,double> >&
                   bin_indices_and_weights ) const
{
  // Find the bins that the dimension value falls in
  Teuchos::Array<unsigned> bin_indices;

  this->calculateBinIndicesOfValue( bin_indices );
  
  bin_indices_and_weights.resize( bin_indices.size() );

  // Set all bin weights to 1.0
  for( size_t i = 0; i < bin_indices.size(); ++i )
  {
    bin_indices_and_weights[i].first = bin_indices[i];
    bin_indices_and_weights[i].second = 1.0;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
