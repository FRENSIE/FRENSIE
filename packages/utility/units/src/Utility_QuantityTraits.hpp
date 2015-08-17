//---------------------------------------------------------------------------//
//!
//! \file   Utility_QuantityTraits.hpp
//! \author Alex Robinson
//! \brief  Quantity traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_QUANTITY_TRAITS_HPP
#define UTILITY_QUANTITY_TRAITS_HPP

// FRENSIE Includes
#include "Utility_QuantityTraitsDecl.hpp"

namespace Utility{

/*! The specialization of QuantityTraits for double (no units).
 *
 * Note that having no units is different from a dimensionless unit.
 * \ingroup unit_traits
 */
template<>
struct QuantityTraits<double>
{
  typedef void Unit;
  typedef double RawType;

  static inline double zero()
  { return 0.0; }

  static inline double one()
  { return 1.0; }

  static inline const RawType& getRawQuantity( const double& quantity )
  { return quantity; }

  static inline void setQuantity( double& quantity,
				  const double& raw_quantity )
  { quantity = raw_quantity; }
};

} // end Utility namespace

#endif // end UTILITY_QUANTITY_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_QuantityTraits.hpp
//---------------------------------------------------------------------------//
