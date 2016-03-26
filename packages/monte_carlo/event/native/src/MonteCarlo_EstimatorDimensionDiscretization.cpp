//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorDimensionDiscretization.cpp
//! \author Alex Robinson
//! \brief  Estimator dimension discretization base class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_EstimatorDimensionDiscretization.hpp"
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"

namespace MonteCarlo{

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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorDimensionDiscretization.cpp
//---------------------------------------------------------------------------//
