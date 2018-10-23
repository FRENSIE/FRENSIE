//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellCollisionFluxEstimator.cpp
//! \author Alex Robinson
//! \brief  Cell collision flux estimator class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightMultipliedCellCollisionFluxEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightMultiplier> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightMultiplier> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightAndEnergyMultipliedCellCollisionFluxEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightAndChargeMultipliedCellCollisionFluxEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> );

//---------------------------------------------------------------------------//
// end MonteCarlo_CellCollisionFluxEstimator.cpp
//---------------------------------------------------------------------------//
