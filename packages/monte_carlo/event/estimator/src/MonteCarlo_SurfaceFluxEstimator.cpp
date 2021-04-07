//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SurfaceFluxEstimator.cpp
//! \author Alex Robinson
//! \brief  Surface flux estimator class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_SurfaceFluxEstimator.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightMultipliedSurfaceFluxEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightAndEnergyMultipliedSurfaceFluxEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightAndChargeMultipliedSurfaceFluxEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> );

//---------------------------------------------------------------------------//
// end MonteCarlo_SurfaceFluxEstimator.cpp
//---------------------------------------------------------------------------//
