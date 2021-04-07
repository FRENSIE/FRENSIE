//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceSampledDependentPhaseSpaceDimensionDistribution.cpp
//! \author Alex Robinson
//! \brief  Importance sampled dependent phase space dimension distribution
//!         class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ImportanceSampledDependentPhaseSpaceDimensionDistribution.hpp"

//---------------------------------------------------------------------------//
// DependentPrimarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondarySpatialDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimaryDirectionalDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiaryDirectionalDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledEnergyDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTimeDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledWeightDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentSecondarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimarySpatialDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimaryDirectionalDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiaryDirectionalDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledEnergyDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTimeDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledWeightDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentTertiarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimarySpatialDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondarySpatialDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimaryDirectionalDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiaryDirectionalDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledEnergyDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTimeDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledWeightDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentPrimaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimarySpatialDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondarySpatialDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiaryDirectionalDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledEnergyDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTimeDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledWeightDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentSecondaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimarySpatialDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondarySpatialDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimaryDirectionalDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiaryDirectionalDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledEnergyDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTimeDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledWeightDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentTertiaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimarySpatialDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondarySpatialDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimaryDirectionalDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledEnergyDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTimeDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledWeightDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentEnergyDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimarySpatialDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondarySpatialDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimaryDirectionalDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiaryDirectionalDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTimeDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledWeightDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentTimeDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimarySpatialDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondarySpatialDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimaryDirectionalDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiaryDirectionalDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledEnergyDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledWeightDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TIME_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentWeightDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimarySpatialDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondarySpatialDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiarySpatialDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledPrimaryDirectionalDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledSecondaryDirectionalDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTertiaryDirectionalDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledEnergyDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ImportanceSampledTimeDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::ImportanceSampledDependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceSampledDependentPhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//
