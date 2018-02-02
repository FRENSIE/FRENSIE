//---------------------------------------------------------------------------//
//!
//! \file   Utility_InverseAtomicMomentumUnit.hpp
//! \author Alex Robinson
//! \brief  The inverse atomic momentum unit declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INVERSE_ATOMIC_MOMENTUM_UNIT_HPP
#define UTILITY_INVERSE_ATOMIC_MOMENTUM_UNIT_HPP

// FRENSIE Includes
#include "Utility_AtomicMomentumUnit.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

namespace Units{

//! The inverse atomic momentum unit
typedef UnitTraits<AtomicMomentum>::InverseUnit InverseAtomicMomentum;

BOOST_UNITS_STATIC_CONSTANT( inverse_atomic_momentum, InverseAtomicMomentum );

} // end Units namespace

} // end Utility namespace

#endif // end UTILITY_INVERSE_ATOMIC_MOMENTUM_UNIT_HPP

//---------------------------------------------------------------------------//
// end Utility_InverseAtomicMomentumUnit.hpp
//---------------------------------------------------------------------------//
