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

// FRENSIE Includes
#include "Utility_UnitConversionPolicyDecl.hpp"

namespace Utility{

//! The inverse length dimension tag
typedef boost::units::derived_dimension<boost::units::length_base_dimension,-1>::type InverseLengthDimension;

/*! \brief Policy struct for converting between inverse Angstroms and the
 * native inverse length unit (1/cm)
 */
struct InverseAngstromConversionPolicy : public BaseUnitConversionPolicy<InverseAngstromConversionPolicy,InverseLengthDimension>
{
  //! Inverse Angstrom per inverse centimeter
  static inline double conversionFactor()
  { return 1e-8; }
};

/*! \brief Policy struct for converting between inverse cm and native
 * inverse length unit (1/cm)
 */
struct InverseCentimeterConversionPolicy : public BaseUnitConversionPolicy<InverseCentimeterConversionPolicy,InverseLengthDimension>
{
  //! Inverse centimeter per inverse centimeter
  static inline double conversionFactor()
  { return 1.0; }
};

} // end Utility namespace

#endif // end UTILITY_INVERSE_LENGTH_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_InverseLengthConversionPolicy.hpp
//---------------------------------------------------------------------------//
