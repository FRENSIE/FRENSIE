//---------------------------------------------------------------------------//
//!
//! \file   Utility_InverseAreaConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Policy structs that define inverse area conversions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INVERSE_AREA_CONVERSION_POLICY_HPP
#define UTILITY_INVERSE_AREA_CONVERSION_POLICY_HPP

// Boost Includes
#include <boost/units/systems/cgs.hpp>

// FRENSIE Includes
#include "Utility_UnitConversionPolicyDecl.hpp"

namespace Utility{

//! The inverse area dimension tag
typedef boost::units::derived_dimension<boost::units::length_base_dimension,-2>::type InverseAreaDimension;

/*! \brief Policy struct for converting between inverse square Angstroms and
 * the native inverse area unit (1/cm^2)
 */
struct InverseSquareAngstromConversionPolicy : public BaseUnitConversionPolicy<InverseSquareAngstromConversionPolicy,InverseAreaDimension>
{
  //! Inverse square Angstrom per inverse square centimeter
  static inline double conversionFactor()
  { return 1e-16; }
};

/*! \brief Policy struct for converting between inverse square cm and 
 * native inverse area unit (1/cm^2)
 */
struct InverseSquareCentimeterConversionPolicy : public BaseUnitConversionPolicy<InverseSquareCentimeterConversionPolicy, InverseAreaDimension>
{
  //! Inverse square centimeter per inverse square centimeter
  static inline double conversionFactor()
  { return 1.0; }
};

} // end Utility namespace

#endif // end UTILITY_INVERSE_AREA_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_InverseAreaConversionPolicy.hpp
//---------------------------------------------------------------------------//
