//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SurfaceCurrentEstimator.cpp
//! \author Alex Robinson
//! \brief  Surface current estimator class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"

namespace MonteCarlo{

// Explicit instantiation 
EXPLICIT_TEMPLATE_CLASS_INST( SurfaceCurrentEstimator<WeightMultiplier> );
EXPLICIT_TEMPLATE_CLASS_INST( SurfaceCurrentEstimator<WeightAndEnergyMultiplier> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SurfaceCurrentEstimator.cpp
//---------------------------------------------------------------------------//
