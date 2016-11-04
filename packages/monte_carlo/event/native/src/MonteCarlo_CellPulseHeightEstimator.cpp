//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellPulseHeightEstimator.cpp
//! \author Alex Robinson
//! \brief  Cell pulse height estimator class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CellPulseHeightEstimator.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( CellPulseHeightEstimator<WeightMultiplier> );
EXPLICIT_TEMPLATE_CLASS_INST( CellPulseHeightEstimator<WeightAndEnergyMultiplier> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CellPulseHeightEstimator.cpp
//---------------------------------------------------------------------------//
