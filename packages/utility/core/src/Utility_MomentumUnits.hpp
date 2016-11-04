//---------------------------------------------------------------------------//
//!
//! \file   Utility_MomentumUnits.hpp
//! \author Alex Robinson
//! \brief  The momentum units
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MOMENTUM_UNITS_HPP
#define UTILITY_MOMENTUM_UNITS_HPP

// Boost Includes
#include <boost/units/systems/si/momentum.hpp>
#include <boost/units/conversion.hpp>

// FRENSIE Includes
#include "Utility_AtomicMomentumUnit.hpp"
#include "Utility_MeCMomentumUnit.hpp"
#include "Utility_RawPhysicalConstants.hpp"

BOOST_UNITS_DEFINE_CONVERSION_FACTOR( Utility::Units::AtomicMomentumBaseUnit, Utility::Units::MeCMomentumBaseUnit, double, Utility::RawPhysicalConstants::fine_structure_constant );

BOOST_UNITS_DEFINE_CONVERSION_FACTOR( Utility::Units::MeCMomentumBaseUnit, Utility::Units::AtomicMomentumBaseUnit, double, 1.0/Utility::RawPhysicalConstants::fine_structure_constant );

#endif // end UTILITY_MOMENTUM_UNITS_HPP

//---------------------------------------------------------------------------//
// end Utility_MomentumUnitS.hpp
//---------------------------------------------------------------------------//
