//---------------------------------------------------------------------------//
//!
//! \file   EstimatorDimensionDiscretization.cpp
//! \author Alex Robinson
//! \brief  Estimator dimension discretization base class definition.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "EstimatorDimensionDiscretization.hpp"

namespace FACEMC{

// Constructor
EstimatorDimensionDiscretization::EstimatorDimensionDiscretization( 
				 const EstimatorPhaseSpaceDimension dimension )
  : d_dimension( dimension )
{ /* ... */ }

// Return the dimension that has been discretized
EstimatorPhaseSpaceDimension 
EstimatorDimensionDiscretization::getDimension() const
{
  return d_dimension;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end EstimatorDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
