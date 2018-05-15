//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution.cpp
//! \author Alex Robinson
//! \brief  Importance sampled independent phase space dimension distribution
//!         class template instantiations
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
#include "MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledIndependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledIndependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledIndependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledIndependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledIndependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledIndependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledIndependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledIndependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<TIME_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledIndependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledIndependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION> );

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//
