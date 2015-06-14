//---------------------------------------------------------------------------//
//!
//! \file   Utility_LengthConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Policy structs that define length conversions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_LENGTH_CONVERSION_POLICY_HPP
#define UTILITY_LENGTH_CONVERSION_POLICY_HPP

// Boost Includes
#include <boost/units/systems/cgs.hpp>

namespace Utility{

//! The length dimension tag
typedef boost::units::length_base_dimension LengthDimension;

/*! \brief The base policy struct for converting a length unit to the native
 * length unit (cm).
 */
template<typename DerivedPolicy>
struct BaseLengthConversionPolicy
{
  //! The dimension where the policy is applicable
  typedef LengthDimension Dimension;
  
  //! Convert native units (cm) to the derived units
  template<typename T>
  static T convertFromNativeUnits( const T value_in_native_units );

  //! Convert from the derived units to native units (cm)
  template<typename T>
  static T convertToNativeUnits( const T value_in_derived_units );
}

/*! \brief Policy struct for converting between Angstroms and the native 
 * length unit (cm).
 */
struct AngstromConversionPolicy : public BaseLengthConversionPolicy<AngstromConversionPolicy>
{
  //! Angstroms per centimeter
  static inline double conversionFactor()
  { return 1e8; }
};

/*! \brief Policy struct for converting between cm and the native length
 * unit (cm).
 */
struct CentimeterConversionPolicy : public BaseLengthConversionPolicy<CentimeterConversionPolicy>
{
  //! Centimeters per centimeter
  static inline double conversionFactor()
  { return 1.0; }
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_LengthConversionPolicy_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_LENGTH_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_LengthConversionPolicy.hpp
//---------------------------------------------------------------------------//
