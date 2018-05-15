//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceSampledDependentPhaseSpaceDimensionDistribution.cpp
//! \author Alex Robinson
//! \brief  Importance sampled dependent phase space dimension distribution
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
#include "MonteCarlo_ImportanceSampledDependentPhaseSpaceDimensionDistribution.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

//---------------------------------------------------------------------------//
// DependentPrimarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondarySpatialDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimaryDirectionalDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiaryDirectionalDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledEnergyDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTimeDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledWeightDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,PRIMARY_SPATIAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentSecondarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimarySpatialDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimaryDirectionalDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiaryDirectionalDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledEnergyDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTimeDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledWeightDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,SECONDARY_SPATIAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentTertiarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimarySpatialDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimaryDirectionalDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiaryDirectionalDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledEnergyDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTimeDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledWeightDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,TERTIARY_SPATIAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentPrimaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimarySpatialDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondarySpatialDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiaryDirectionalDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledEnergyDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTimeDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledWeightDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,PRIMARY_DIRECTIONAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentSecondaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimarySpatialDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondarySpatialDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiaryDirectionalDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledEnergyDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTimeDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledWeightDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,SECONDARY_DIRECTIONAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentTertiaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimarySpatialDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondarySpatialDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimaryDirectionalDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledEnergyDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTimeDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledWeightDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,TERTIARY_DIRECTIONAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentEnergyDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimarySpatialDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,ENERGY_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondarySpatialDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,ENERGY_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,ENERGY_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimaryDirectionalDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,ENERGY_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,ENERGY_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiaryDirectionalDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,ENERGY_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTimeDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,ENERGY_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledWeightDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,ENERGY_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,ENERGY_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentTimeDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimarySpatialDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,TIME_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondarySpatialDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,TIME_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,TIME_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimaryDirectionalDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,TIME_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,TIME_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiaryDirectionalDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,TIME_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledEnergyDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,TIME_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledWeightDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,TIME_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION,TIME_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentWeightDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimarySpatialDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,WEIGHT_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION,WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondarySpatialDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,WEIGHT_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION,WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,WEIGHT_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION,WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimaryDirectionalDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,WEIGHT_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION,WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,WEIGHT_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION,WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiaryDirectionalDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,WEIGHT_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION,WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledEnergyDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,WEIGHT_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION,WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTimeDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,WEIGHT_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<TIME_DIMENSION,WEIGHT_DIMENSION> );

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceSampledDependentPhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//
