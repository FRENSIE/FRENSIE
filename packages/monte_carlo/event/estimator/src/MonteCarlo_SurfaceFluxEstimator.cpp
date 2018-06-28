//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SurfaceFluxEstimator.cpp
//! \author Alex Robinson
//! \brief  Surface flux estimator class template instantiations
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "MonteCarlo_SurfaceFluxEstimator.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightMultipliedSurfaceFluxEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier> );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightAndEnergyMultipliedSurfaceFluxEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
  
//---------------------------------------------------------------------------//
// end MonteCarlo_SurfaceFluxEstimator.cpp
//---------------------------------------------------------------------------//
