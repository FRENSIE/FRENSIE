//---------------------------------------------------------------------------//
//!
//! \file   Utility_QuantityTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Quantity traits declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_QUANTITY_TRAITS_DECL_HPP
#define UTILITY_QUANTITY_TRAITS_DECL_HPP

/*! \defgroup quantity_traits Quantity Traits
 * \ingroup traits
 */

namespace Utility{

/*! The default quantity traits implementation
 *
 * The default quantity traits implementation assumes that a 
 * boost::units::quantity is the template parameter. Specializations should be
 * made for other types.
 * \ingroup quantity_traits
 */
template<typename Quantity>
struct QuantityTraits
{
  //! The unit associated with this quantity
  typedef typename Quantity::unit_type Unit;

  //! The raw quantity type
  typedef typename Quantity::value_type RawType;

  //! Get the zero quantity
  static inline Quantity zero()
  { return Quantity::from_value( 0.0 ); }

  //! Get the one quantity
  static inline Quantity one()
  { return Quantity::from_value( 1.0 ); }

  //! Get the raw value of a quantity
  static inline const RawType& getRawQuantity( const Quantity& quantity )
  { return quantity.value(); }

  //! Set the value of a quantity
  static inline void setQuantity( Quantity& quantity,
				  const RawType& raw_quantity )
  { quantity = Quantity::from_value( raw_quantity ); }
};

//! This function allows access to the getRawQuantity QuantityTraits function
template<typename Quantity>
inline const typename QuantityTraits<Quantity>::RawType& getRawQuantity( const Quantity& quantity )
{ 
  return QuantityTraits<Quantity>::getRawQuantity( quantity ); 
}

//! This function allows access to the setQuantity QuantityTraits function
template<typename Quantity>
inline void setQuantity( Quantity& quantity,
			 const typename QuantityTraits<Quantity>::RawType& raw_quantity )
{ 
  QuantityTraits<Quantity>::setQuantity( quantity, raw_quantity );
}

} // end Utility namespace

#endif // end UTILITY_QUANTITY_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_QuantityTraitsDecl.hpp
//---------------------------------------------------------------------------//
