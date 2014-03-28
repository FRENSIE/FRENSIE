//---------------------------------------------------------------------------//
//!
//! \file   Estimator_def.hpp
//! \author Alex Robinson
//! \brief  Estimator base class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef ESTIMATOR_DEF_HPP
#define ESTIMATOR_DEF_HPP

// FACEMC Includes
#include "GeneralEstimatorDimensionDiscretization.hpp"

namespace FACEMC{

// Set the bin boundaries for a dimension of the sphase space
template<PhaseSpaceDimension dimension, typename DimensionType>
void Estimator::setBinBoundaries( 
			  const Teuchos::Array<DimensionType>& bin_boundaries )
{
  // Make sure the DimensionType matches the type associated with the dimension
  testStaticPrecondition((boost::is_same<typename Traits::PhaseSpaceDimensionTraits<dimension>::dimensionType,DimensionType>::value));
  
  Teuchos::RCP<EstimatorDimensionDiscretization> dimension_bin_boundaries(
    new GeneralEstimatorDimensionDiscretization<dimension>( bin_boundaries ) );
  
  assignBinBoundaries( dimension_bin_boundaries );
}

// Convert a portion of the particle state to a generic map
template<PhaseSpaceDimension dimension>
inline void Estimator::convertPartialParticleStateToGenericMap( 
			            const BasicParticleState& particle,
			            DimensionValueMap& dimension_values ) const
{
  dimension_values[dimension] = 
    Traits::PhaseSpaceDimensionTraits<dimension>::obfuscateValue( particle );

  // Recursive template instantiation
  convertPartialParticleStateToGenericMap<static_cast<PhaseSpaceDimension>(dimension+1)>( particle, dimension_values );
}

// This specialization allows recursion to end.
template<>
inline void Estimator::convertPartialParticleStateToGenericMap<DIMENSION_end>( 
	                            const BasicParticleState& particle,
	                            DimensionValueMap& dimension_values ) const
{ /* ... */ }

} // end FACEMC namespace

#endif // end ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Estimator_def.hpp
//---------------------------------------------------------------------------//
