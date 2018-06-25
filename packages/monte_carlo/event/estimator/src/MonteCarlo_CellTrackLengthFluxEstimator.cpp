//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellTrackLengthFluxEstimator.cpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( CellTrackLengthFluxEstimator<WeightMultiplier> );
EXPLICIT_TEMPLATE_CLASS_INST( CellTrackLengthFluxEstimator<WeightAndEnergyMultiplier> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CellTrackLengthFluxEstimator.cpp
//---------------------------------------------------------------------------//
