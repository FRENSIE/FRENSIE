//---------------------------------------------------------------------------//
//!
//! \file   Utility_InverseLengthConversionPolicy_def.hpp
//! \author Alex Robinson
//! \brief  Inverse length conversion policy struct template defs.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INVERSE_LENGTH_CONVERSION_POLICY_DEF_HPP
#define UTILITY_INVERSE_LENGTH_CONVERSION_POLICY_DEF_HPP

namespace Utility{

// Convert native units (1/cm) to the derived units
template<typename DerivedPolicy>
template<typename T>
inline T convertFromNativeUnits( const T value_in_native_units )
{
  return value_in_native_units*DerivedPolicy::conversionFactor();
}

// Convert from the derived units to native units (1/cm)
template<typename DerivedPolicy>
template<typename T>
inline T convertToNativeUnits( const T value_in_derived_units )
{
  return value_in_derived_units/DerivedPolicy::conversionFactor();
}

} // end Utility namespace

#endif // end UTILITY_INVERSE_LENGTH_CONVERSION_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InverseLengthConversionPolicy_def.hpp
//---------------------------------------------------------------------------//
