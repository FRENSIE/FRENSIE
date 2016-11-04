//---------------------------------------------------------------------------//
//!
//! \file   Utility_InverseSquareAngstromUnit.hpp
//! \author Alex Robinson
//! \brief  The inverse square Angstrom unit declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INVERSE_SQUARE_ANGSTROM_UNIT_HPP
#define UTILITY_INVERSE_SQUARE_ANGSTROM_UNIT_HPP

// FRENSIE Includes
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

namespace Units{

//! The inverse square
typedef UnitTraits<InverseAngstrom>::template GetUnitToPowerType<2>::type InverseSquareAngstrom;

BOOST_UNITS_STATIC_CONSTANT( inverse_square_angstrom, InverseSquareAngstrom );

} // end Units namespace

} // end Utility namespace

#endif // end UTILITY_INVERSE_SQUARE_ANGSTROM_UNIT_HPP

//---------------------------------------------------------------------------//
// end Utility_InverseSquareAngstromUnit.hpp
//---------------------------------------------------------------------------//
