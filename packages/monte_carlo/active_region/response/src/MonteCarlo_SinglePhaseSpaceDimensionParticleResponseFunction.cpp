//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Single phase-space dimension particle response function class
//!         template instantiations
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
#include "MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::XDimensionParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::YDimensionParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ZDimensionParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_SPATIAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::UDimensionParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::VDimensionParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WDimensionParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::EnergyDimensionParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::ENERGY_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::ENERGY_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::TimeDimensionParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TIME_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::TIME_DIMENSION> );

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightDimensionParticleResponseFunction );
EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::WEIGHT_DIMENSION> );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::SinglePhaseSpaceDimensionParticleResponseFunction<MonteCarlo::WEIGHT_DIMENSION> );

//---------------------------------------------------------------------------//
// end MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.cpp
//---------------------------------------------------------------------------//
