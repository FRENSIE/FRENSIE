//---------------------------------------------------------------------------//
//!
//! \file   Utility_AtomicMomentumUnit.hpp
//! \author Alex Robinson
//! \brief  The atomic momentum unit declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ATOMIC_MOMENTUM_UNIT_HPP
#define UTILITY_ATOMIC_MOMENTUM_UNIT_HPP

// Boost Includes
#include <boost/units/systems/si/momentum.hpp>
#include <boost/units/physical_dimensions/length.hpp>
#include <boost/units/base_unit.hpp>
#include <boost/units/conversion.hpp>

// FRENSIE Includes
#include "Utility_RawPhysicalConstants.hpp"

namespace Utility{

namespace Units{

//! The atomic momentum base unit
struct AtomicMomentumBaseUnit : public boost::units::base_unit<AtomicMomentumBaseUnit, boost::units::momentum_dimension, 2>
{
  static const char* name() { return "Atomic Momentum"; }
  static const char* symbol() { return "a.mom."; }
};

//! The atomic momentum unit
typedef AtomicMomentumBaseUnit::unit_type AtomicMomentum;

BOOST_UNITS_STATIC_CONSTANT( atomic_momentum, AtomicMomentum );

} // end Units namespace

} // end Utility namespace

BOOST_UNITS_DEFINE_CONVERSION_FACTOR( Utility::Units::AtomicMomentumBaseUnit, boost::units::si::momentum, double, Utility::RawPhysicalConstants::atomic_momentum );

BOOST_UNITS_DEFINE_CONVERSION_FACTOR( boost::units::si::momentum, Utility::Units::AtomicMomentumBaseUnit, double, 1.0/Utility::RawPhysicalConstants::atomic_momentum );

BOOST_UNITS_DEFAULT_CONVERSION( Utility::Units::AtomicMomentumBaseUnit, boost::units::si::momentum );

#endif // end UTILITY_ATOMIC_MOMENTUM_UNIT_HPP

//---------------------------------------------------------------------------//
// end Utility_AtomicMomentumUnit.hpp
//---------------------------------------------------------------------------//
