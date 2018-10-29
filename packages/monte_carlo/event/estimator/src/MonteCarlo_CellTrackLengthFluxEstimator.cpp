//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellTrackLengthFluxEstimator.cpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightAndEnergyMultipliedCellTrackLengthFluxEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightAndChargeMultipliedCellTrackLengthFluxEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> );

//---------------------------------------------------------------------------//
// end MonteCarlo_CellTrackLengthFluxEstimator.cpp
//---------------------------------------------------------------------------//
