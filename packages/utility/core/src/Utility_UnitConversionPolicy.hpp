//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Policy structs that define unit systems and conversions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_CONVERSION_POLICY_HPP
#define UTILITY_UNIT_CONVERSION_POLICY_HPP

// FRENSIE Includes
#include "Utility_LengthConversionPolicy.hpp"
#include "Utility_InverseLengthConversionPolicy.hpp"

namespace Utility{

//! The area dimension tag
typedef boost::units::area_dimension AreaDimension;

//! The inverse area dimension tag
typedef boost::units::derived_dimension<boost::units::length_base_dimension,-2>::type InverseAreaDimension;


} // end Utility namespace

#endif // end UTILITY_UNIT_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitConversionPolicy.hpp
//---------------------------------------------------------------------------//
