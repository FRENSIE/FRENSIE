//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SurfaceCurrentEstimator.cpp
//! \author Alex Robinson
//! \brief  Surface current estimator class template instantiations
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
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightMultipliedSurfaceCurrentEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier> );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightAndEnergyMultipliedSurfaceCurrentEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier> );

//---------------------------------------------------------------------------//
// end MonteCarlo_SurfaceCurrentEstimator.cpp
//---------------------------------------------------------------------------//
