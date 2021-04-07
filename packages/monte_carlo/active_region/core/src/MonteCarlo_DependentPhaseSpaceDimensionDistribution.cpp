//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DependentPhaseSpaceDimensionDistribution.cpp
//! \author Alex Robinson
//! \brief  Dependent phase space dimension distribution class template
//!         instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp"

//---------------------------------------------------------------------------//
// DependentPrimarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SecondarySpatialDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TertiarySpatialDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PrimaryDirectionalDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SecondaryDirectionalDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TertiaryDirectionalDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::EnergyDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TimeDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightDependentPrimarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentSecondarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PrimarySpatialDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TertiarySpatialDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PrimaryDirectionalDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SecondaryDirectionalDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TertiaryDirectionalDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::EnergyDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TimeDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightDependentSecondarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentTertiarySpatialDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PrimarySpatialDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SecondarySpatialDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PrimaryDirectionalDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SecondaryDirectionalDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TertiaryDirectionalDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::EnergyDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TimeDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightDependentTertiarySpatialDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentPrimaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PrimarySpatialDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SecondarySpatialDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TertiarySpatialDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SecondaryDirectionalDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TertiaryDirectionalDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::EnergyDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TimeDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightDependentPrimaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentSecondaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PrimarySpatialDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SecondarySpatialDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TertiarySpatialDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PrimaryDirectionalDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TertiaryDirectionalDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::EnergyDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TimeDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightDependentSecondaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentTertiaryDirectionalDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PrimarySpatialDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SecondarySpatialDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TertiarySpatialDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PrimaryDirectionalDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SecondaryDirectionalDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::EnergyDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TimeDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightDependentTertiaryDirectionalDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentEnergyDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PrimarySpatialDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SecondarySpatialDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TertiarySpatialDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PrimaryDirectionalDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SecondaryDirectionalDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TertiaryDirectionalDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TimeDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightDependentEnergyDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::ENERGY_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentTimeDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PrimarySpatialDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SecondarySpatialDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TertiarySpatialDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PrimaryDirectionalDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SecondaryDirectionalDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TertiaryDirectionalDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::EnergyDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightDependentTimeDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION,MonteCarlo::TIME_DIMENSION> );

//---------------------------------------------------------------------------//
// DependentWeightDimensionDistributions
//---------------------------------------------------------------------------//

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PrimarySpatialDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SecondarySpatialDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TertiarySpatialDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PrimaryDirectionalDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SecondaryDirectionalDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TertiaryDirectionalDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::EnergyDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TimeDependentWeightDimensionDistribution );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::DependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION,MonteCarlo::WEIGHT_DIMENSION> );

//---------------------------------------------------------------------------//
// end MonteCarlo_DependentPhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//
