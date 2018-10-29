//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MeshTrackLengthFluxEstimator.cpp
//! \author Alex Robinson
//! \brief  The mesh track-length flux estimator instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_MeshTrackLengthFluxEstimator.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightMultipliedMeshTrackLengthFluxEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightAndEnergyMultipliedMeshTrackLengthFluxEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightAndChargeMultipliedMeshTrackLengthFluxEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> );

//---------------------------------------------------------------------------//
// end MonteCarlo_MeshTrackLengthFluxEstimator.cpp
//---------------------------------------------------------------------------//
