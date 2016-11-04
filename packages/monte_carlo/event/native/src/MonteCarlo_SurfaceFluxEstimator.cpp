//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SurfaceFluxEstimator.cpp
//! \author Alex Robinson
//! \brief  Surface flux estimator class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SurfaceFluxEstimator.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( SurfaceFluxEstimator<WeightMultiplier> );
EXPLICIT_TEMPLATE_CLASS_INST( SurfaceFluxEstimator<WeightAndEnergyMultiplier> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SurfaceFluxEstimator.cpp
//---------------------------------------------------------------------------//
