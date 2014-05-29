//---------------------------------------------------------------------------//
//!
//! \file   Facemc_EstimatorDimensionDiscretization.cpp
//! \author Alex Robinson
//! \brief  Estimator dimension discretization base class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_EstimatorDimensionDiscretization.hpp"

namespace Facemc{

// Constructor
EstimatorDimensionDiscretization::EstimatorDimensionDiscretization( 
				          const PhaseSpaceDimension dimension )
  : d_dimension( dimension )
{ /* ... */ }

// Return the dimension that has been discretized
PhaseSpaceDimension EstimatorDimensionDiscretization::getDimension() const
{
  return d_dimension;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_EstimatorDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
