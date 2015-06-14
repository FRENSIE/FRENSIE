//---------------------------------------------------------------------------//
//!
//! \file   Utility_LengthConversionPolicy_def.hpp
//! \author Alex Robinson
//! \brief  Length conversion policy struct template defs.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_LENGTH_CONVERSION_POLICY_DEF_HPP
#define UTILITY_LENGTH_CONVERSION_POLICY_DEF_HPP

namespace Utility{

// Convert native units (cm) to derived units
template<typename DerivedPolicy>
template<typename T>
inline T BaseLengthConversionPolicy<DerivedPolicy>::convertFromNativeUnits( 
                                                const T value_in_native_units )
{
  return value_in_native_units*DerivedPolicy::conversionFactor();
}

// Convert from the derived units to native units (cm)
template<typename DerivedPolicy>
template<typename T>
inline T BaseLengthConversionPolicy<DerivedPolicy>::convertToNativeUnits( 
                                               const T value_in_derived_units )
{
  return value_in_derived_units/DerivedPolicy::conversionFactor();
}

} // end Utility namespace

#endif // end UTILITY_LENGTH_CONVERSION_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_LengthConversionPolicy_def.hpp
//---------------------------------------------------------------------------//
