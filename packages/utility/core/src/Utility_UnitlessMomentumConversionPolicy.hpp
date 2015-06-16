//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitlessMomentumConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Policy structs that define unitless momentum conversions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNITLESS_MOMENTUM_CONVERSION_POLICY_HPP
#define UTILITY_UNITLESS_MOMENTUM_CONVERSION_POLICY_HPP

// Boost Includes
#include <boost/units/base_dimension.hpp>

// FRENSIE Includes
#include "Utility_UnitConversionPolicyDecl.hpp"
#include "Utility_PhysicalConstants.hpp"

//! The dimensionless momentum dimension tag
struct DimensionlessMomentum : boost::units::base_dimension<DimensionlessMomentum,1>{};

namespace Utility{

/*! \brief Policy struct for converting between atomic dimensionless momentum
 * (p/(me*e^2/h_bar)) and the native dimensionless momentum (p/(me*c))
 */
struct AtomicDimensionlessMomentumConversionPolicy : public BaseUnitConversionPolicy<AtomicDimensionlessMomentumConversionPolicy, DimensionlessMomentum>
{
  //! Atomic dimensionless momentum per native dimensionless momentum
  static inline double conversionFactor()
  { return Utility::PhysicalConstants::inverse_fine_structure_constant; }
};

/*! \brief Policy struct for converting between native dimensionless
 * momentum (p/(me*c)) and native dimensionless momentum (p/(me*c))
 */
struct MeCDimensionlessMomentumConversionPolicy : public BaseUnitConversionPolicy<MeCDimensionlessMomentumConversionPolicy, DimensionlessMomentum>
{
  // Native dimensionless momentum per native dimensionless momentum
  static inline double conversionFactor()
  { return 1.0; }
};

} // end Utility namespace

#endif // end UTILITY_UNITLESS_MOMENTUM_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitlessMomentumConversionPolicy.hpp
//---------------------------------------------------------------------------//
