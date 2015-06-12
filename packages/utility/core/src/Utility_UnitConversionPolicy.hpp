//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Policy structs that define unit systems and conversions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_CONVERSION_POLICY_HPP
#define UTILITY_UNIT_CONVERSION_POLICY_HPP

// Boost Includes
#include <boost/units/systems/cgs.hpp>

namespace Utility{

//! The length dimension tag
typedef boost::units::length_base_dimension LengthDimension;

//! The inverse length dimension tag
typedef boost::units::derived_dimension<boost::units::length_base_dimension,-1>::type InverseLengthDimension;

//! The area dimension tag
typedef boost::units::area_dimension AreaDimension;

//! The inverse area dimension tag
typedef boost::units::derived_dimension<boost::units::length_base_dimension,-2>::type inverse_area_dimension;

/*! \brief The base policy struct for converting a length unit to the native
 * length unit (cm).
 */
  template<typename DerivedPolicy>
struct BaseLengthConversionPolicy
{
  //! The dimension where the policy is applicable
  typedef LengthDimension Dimension;
  
  //! Convert native units (cm) to Angstroms
  template<typename T>
  static T convertFromNativeUnits( const T value_in_native_units );

  //! Convert to native units (cm)
  template<typename T>
  static T convertToNativeUnits( const T value_in_angstroms );
}

/*! \brief Policy struct for converting between Angstroms and the native 
 * length unit (cm).
 */
struct AngstromConversionPolicy : public BaseLengthConversionPolicy<AngstromConversionPolicy>
{
  static const double length_units_per_cm;
};

/*! \brief Policy struct for converting between cm and the native length
 * unit (cm).
 */
struct CentimeterConversionPolicy : public BaseLengthConversionPolicy<CentimeterConversionPolicy>
{
  static const double length_units_per_cm;
};

/*! \brief Policy struct for converting between inverse Angstroms and the 
 * native inverse length unit (cm).
 */
struct InverseAngstromPolicy
{
  //! Convert native units (1/cm) to Angstroms
  template<typename T>
  static T convertFromNativeUnits( const T value_in_native_units );

  //! Convert to native units (cm)
  template<typename T>
  static T convertToNativeUnits( const T value_in_inverse_angstroms );
};

} // end Utility namespace

#endif // end UTILITY_UNIT_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitConversionPolicy.hpp
//---------------------------------------------------------------------------//
