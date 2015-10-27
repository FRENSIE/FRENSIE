//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitConversionPolicyDecl.hpp
//! \author Alex Robinson
//! \brief  Unit conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_CONVERSION_POLICY_DECL_HPP
#define UTILITY_UNIT_CONVERSION_POLICY_DECL_HPP

namespace Utility{

//! \brief The base policy struct for converting to and from native units.
template<typename DerivedPolicy, typename BaseDimension>
struct BaseUnitConversionPolicy
{
  //! The dimension where the policy is applicable
  typedef BaseDimension Dimension;

  //! Convert native units to the derived units
  template<typename T>
  static inline void convertFromNativeUnits( T& value_in_native_units )
  {
    value_in_native_units *= DerivedPolicy::conversionFactor();
  }

  //! Convert from derived units to native units 
  template<typename T>
  static inline void convertToNativeUnits( T& value_in_derived_units )
  {
    value_in_derived_units /= DerivedPolicy::conversionFactor();
  }
};

} // end Utility namespace

#endif // end UTILITY_UNIT_CONVERSION_POLICY_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitConversionPolicyDecl.hpp
//---------------------------------------------------------------------------//
