//---------------------------------------------------------------------------//
//!
//! \file   Utility_MeCMomentumUnit.hpp
//! \author Alex Robinson
//! \brief  The me*c momentum unit
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MEC_MOMENTUM_UNIT_HPP
#define UTILITY_MEC_MOMENTUM_UNIT_HPP

// Boost Includes
#include <boost/units/systems/si/momentum.hpp>
#include <boost/units/physical_dimensions/length.hpp>
#include <boost/units/base_unit.hpp>
#include <boost/units/conversion.hpp>

// FRENSIE Includes
#include "Utility_RawPhysicalConstants.hpp"

namespace Utility{

namespace Units{

//! The me*c momentum base unit
struct MeCMomentumBaseUnit : public boost::units::base_unit<MeCMomentumBaseUnit, boost::units::momentum_dimension, 3>
{
  static const char* name() { return "MeC Momentum"; }
  static const char* symbol() { return "me*c"; }
};

//! The me*c momentum base unit
typedef MeCMomentumBaseUnit::unit_type MeCMomentum;

BOOST_UNITS_STATIC_CONSTANT( mec_momentum, MeCMomentum );
BOOST_UNITS_STATIC_CONSTANT( mec, MeCMomentum );

} // end Units namespace

} // end Utility namespace

BOOST_UNITS_DEFINE_CONVERSION_FACTOR( Utility::Units::MeCMomentumBaseUnit, boost::units::si::momentum, double, Utility::RawPhysicalConstants::atomic_momentum/Utility::RawPhysicalConstants::fine_structure_constant );

BOOST_UNITS_DEFINE_CONVERSION_FACTOR( boost::units::si::momentum, Utility::Units::MeCMomentumBaseUnit, double, Utility::RawPhysicalConstants::fine_structure_constant/Utility::RawPhysicalConstants::atomic_momentum );

BOOST_UNITS_DEFAULT_CONVERSION( Utility::Units::MeCMomentumBaseUnit, boost::units::si::momentum );

#endif // end UTILITY_MEC_MOMENTUM_UNIT_HPP

//---------------------------------------------------------------------------//
// end Utility_MeCMomentumUnit.hpp
//---------------------------------------------------------------------------//
