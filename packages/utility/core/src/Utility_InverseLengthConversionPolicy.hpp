//---------------------------------------------------------------------------//
//!
//! \file   Utility_InverseLengthConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Policy structs that define inverse length conversions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INVERSE_LENGTH_CONVERSION_POLICY_HPP
#define UTILITY_INVERSE_LENGTH_CONVERSION_POLICY_HPP

// Boost Includes
#include <boost/units/systems/cgs.hpp>

namespace Utility{

//! The inverse length dimension tag
typedef boost::units::derived_dimension<boost::units::length_base_dimension,-1>::type InverseLengthDimension;

/*! \brief The base policy struct for converting an inverse length unit to
 * the native inverse length unit (1/cm).
 */
template<typename DerivedPolicy>
struct BaseInverseLengthConversionPolicy
{
  //! The dimension where the policy is applicable
  typedef InverseLengthDimension Dimension;

  //! Convert native units (1/cm) to the derived units
  template<typename T>
  static T convertFromNativeUnits( const T value_in_native_units );

  //! Convert from the derived units to native units (1/cm)
  template<typename T>
  static T convertToNativeUnits( const T value_in_derived_units );
};

/*! \brief Policy struct for converting between inverse Angstroms and the
 * native inverse length unit (1/cm)
 */
struct InverseAngstromConversionPolicy : public BaseInverseLengthConversionPolicy
{
  //! Inverse Angstrom per inverse centimeter
  inline double conversionFactor()
  { return 1e-8; }
};

/*! \brief Policy struct for converting between inverse cm and native
 * inverse length unit (1/cm)
 */
struct InverseCentimeterConversionPolicy : public BaseInverseLengthConversionPolicy
{
  //! Inverse centimeter per inverse centimeter
  inline double conversionFactor()
  { return 1.0; }
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_InverseLengthConversionPolicy_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_INVERSE_LENGTH_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_InverseLengthConversionPolicy.hpp
//---------------------------------------------------------------------------//
