//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Estimator_def.hpp
//! \author Alex Robinson
//! \brief  Estimator base class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_ESTIMATOR_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_GeneralEstimatorDimensionDiscretization.hpp"

namespace MonteCarlo{

// Set the bin boundaries for a dimension of the sphase space
template<PhaseSpaceDimension dimension, typename DimensionType>
void Estimator::setBinBoundaries( 
			  const Teuchos::Array<DimensionType>& bin_boundaries )
{
  // Make sure the DimensionType matches the type associated with the dimension
  testStaticPrecondition((boost::is_same<typename PhaseSpaceDimensionTraits<dimension>::dimensionType,DimensionType>::value));
  
  Teuchos::RCP<EstimatorDimensionDiscretization> dimension_bin_boundaries(
    new GeneralEstimatorDimensionDiscretization<dimension>( bin_boundaries ) );
  
  assignBinBoundaries( dimension_bin_boundaries );
}

// Convert a portion of the particle state to a generic map
template<PhaseSpaceDimension dimension>
inline void Estimator::convertPartialParticleStateToGenericMap( 
			            const ParticleState& particle,
			            DimensionValueMap& dimension_values ) const
{
  dimension_values[dimension] = 
    PhaseSpaceDimensionTraits<dimension>::obfuscateValue( particle );

  // Recursive template instantiation
  convertPartialParticleStateToGenericMap<static_cast<PhaseSpaceDimension>(dimension+1)>( particle, dimension_values );
}

// This specialization allows recursion to end.
template<>
inline void Estimator::convertPartialParticleStateToGenericMap<DIMENSION_end>( 
	                            const ParticleState& particle,
	                            DimensionValueMap& dimension_values ) const
{ /* ... */ }

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Estimator_def.hpp
//---------------------------------------------------------------------------//
