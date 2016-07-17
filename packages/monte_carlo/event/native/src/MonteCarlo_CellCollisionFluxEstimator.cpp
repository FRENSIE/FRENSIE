//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellCollisionFluxEstimator.cpp
//! \author Alex Robinson
//! \brief  Cell collision flux estimator class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( CellCollisionFluxEstimator<WeightMultiplier> );
EXPLICIT_TEMPLATE_CLASS_INST( CellCollisionFluxEstimator<WeightAndEnergyMultiplier> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CellCollisionFluxEstimator.cpp
//---------------------------------------------------------------------------//
