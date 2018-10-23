//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SurfaceCurrentEstimator.cpp
//! \author Alex Robinson
//! \brief  Surface current estimator class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightMultipliedSurfaceCurrentEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightAndEnergyMultipliedSurfaceCurrentEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightAndChargeMultipliedSurfaceCurrentEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndChargeMultiplier> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndChargeMultiplier> );

//---------------------------------------------------------------------------//
// end MonteCarlo_SurfaceCurrentEstimator.cpp
//---------------------------------------------------------------------------//
