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
  
  std::shared_ptr<EstimatorDimensionDiscretization> dimension_bin_boundaries(
    new GeneralEstimatorDimensionDiscretization<dimension>( bin_boundaries ) );
  
  assignBinBoundaries( dimension_bin_boundaries );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Estimator_def.hpp
//---------------------------------------------------------------------------//
