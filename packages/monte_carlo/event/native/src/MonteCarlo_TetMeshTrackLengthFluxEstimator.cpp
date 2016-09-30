//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TetMeshTrackLengthFluxEstimator.cpp
//! \author Alex Robinson
//! \brief  Tet mesh track length flux estimator class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp"

namespace MonteCarlo{

// Explicit instantiation 
EXPLICIT_TEMPLATE_CLASS_INST( TetMeshTrackLengthFluxEstimator<WeightMultiplier> );
EXPLICIT_TEMPLATE_CLASS_INST( TetMeshTrackLengthFluxEstimator<WeightAndEnergyMultiplier> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_TetMeshTrackLengthFluxEstimator.cpp
//---------------------------------------------------------------------------//
