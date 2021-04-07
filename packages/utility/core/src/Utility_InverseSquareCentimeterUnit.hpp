//---------------------------------------------------------------------------//
//!
//! \file   Utility_InverseSquareCentimeterUnit.hpp
//! \author Alex Robinson
//! \brief  The inverse square centimeter unit declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INVERSE_SQUARE_CENTIMETER_UNIT_HPP
#define UTILITY_INVERSE_SQUARE_CENTIMETER_UNIT_HPP

// FRENSIE Includes
#include "Utility_InverseCentimeterUnit.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

namespace Units{

//! The inverse square centimeter unit
typedef UnitTraits<InverseCentimeter>::template GetUnitToPowerType<2>::type InverseSquareCentimeter;

BOOST_UNITS_STATIC_CONSTANT( inverse_square_centimeter, InverseSquareCentimeter );

}  // end Units namespace

} // end Utility namespace

#endif // end UTILITY_INVERSE_SQUARE_CENTIMETER_UNIT_HPP

//---------------------------------------------------------------------------//
// end Utility_InverseSquareCentimeterUnit.hpp
//---------------------------------------------------------------------------//
