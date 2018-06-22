//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellPulseHeightEstimator.cpp
//! \author Alex Robinson
//! \brief  Cell pulse height estimator class template instantiations
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
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightMultipliedCellPulseHeightEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightAndEnergyMultipliedCellPulseHeightEstimator );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> );
  
//---------------------------------------------------------------------------//
// end MonteCarlo_CellPulseHeightEstimator.cpp
//---------------------------------------------------------------------------//
