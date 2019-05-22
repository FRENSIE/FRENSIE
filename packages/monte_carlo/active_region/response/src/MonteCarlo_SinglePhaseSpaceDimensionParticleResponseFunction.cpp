//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Single phase-space dimension particle response function class
//!         template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::XPositionParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::YPositionParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ZPositionParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::XDirectionParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::YDirectionParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ZDirectionParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::EnergyParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TimeParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TIME_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::WEIGHT_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SourceEnergyParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_ENERGY_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SourceTimeParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_TIME_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SourceWeightParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_WEIGHT_DIMENSION> );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SOURCE_WEIGHT_DIMENSION> );

//---------------------------------------------------------------------------//
// end MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.cpp
//---------------------------------------------------------------------------//
