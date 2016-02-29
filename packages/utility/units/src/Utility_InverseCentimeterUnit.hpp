//---------------------------------------------------------------------------//
//!
//! \file   Utility_InverseCentimeterUnit.hpp
//! \author Alex Robinson
//! \brief  The inverse centimeter unit declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INVERSE_CENTIMETER_UNIT_HPP
#define UTILITY_INVERSE_CENTIMETER_UNIT_HPP

// Boost Includes
#include <boost/units/systems/cgs/length.hpp>

// FRENSIE Includes
#include "Utility_InverseCentimeterUnit.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

namespace Units{

//! The inverse centimeter unit
typedef UnitTraits<boost::units::cgs::length>::InverseUnit InverseCentimeter;

BOOST_UNITS_STATIC_CONSTANT( inverse_centimeter, InverseCentimeter );

} // end Units namespace

} // end Utility namespace

#endif // end UTILITY_INVERSE_CENTIMETER_UNIT_HPP

//---------------------------------------------------------------------------//
// end Utility_InverseCentimeterUnit.hpp
//---------------------------------------------------------------------------//

