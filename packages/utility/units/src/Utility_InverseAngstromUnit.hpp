//---------------------------------------------------------------------------//
//!
//! \file   Utility_InverseAngstromUnit.hpp
//! \author Alex Robinson
//! \brief  The inverse Angstrom unit declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INVERSE_ANGSTROM_UNIT_HPP
#define UTILITY_INVERSE_ANGSTROM_UNIT_HPP

// FRENSIE Includes
#include "Utility_AngstromUnit.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

namespace Units{

//! The inverse Angstrom unit
typedef UnitTraits<Angstrom>::InverseUnit InverseAngstrom;

BOOST_UNITS_STATIC_CONSTANT( inverse_angstrom, InverseAngstrom );

} // end Units namespace

} // end Utility namespace

#endif // end UTILITY_INVERSE_ANGSTROM_UNIT_HPP

//---------------------------------------------------------------------------//
// end Utility_InverseAngstromUnit.hpp
//---------------------------------------------------------------------------//
