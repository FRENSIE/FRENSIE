//---------------------------------------------------------------------------//
//!
//! \file   Utility_QuantityTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Quantity traits declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_QUANTITY_TRAITS_DECL_HPP
#define UTILITY_QUANTITY_TRAITS_DECL_HPP

// Std Lib Includes
#include <type_traits>
#include <limits>

/*! \defgroup quantity_traits Quantity Traits
 * \ingroup traits
 */

namespace Utility{

/*! A struct designed to give a compile time error for quantity traits
 * \ingroup quantity_traits
 */
template<typename T>
struct UndefinedQuantityTraits
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline T notDefined() { return T::this_type_is_missing_a_specialization(); }
};

/*! The default quantity traits implementation
 *
 * All traits defined in std::numeric_limits are also defined in this traits
 * class. Useful additions for boost::unit::quantity types are also defined
 * in this traits class. The default implementation will not compile. 
 * Specializations must be made for types of interest.
 * \ingroup quantity_traits
 */
template<typename T, typename Enabled = void>
struct QuantityTraits
{
  //! The unit type
  typedef void UnitType;

  //! The raw quantity type
  typedef T RawType;

  //! The quantity type
  typedef T QuantityType;

  //! Used to check if the traits class for quantity type is specialized
  typedef std::false_type is_specialized;

  //! The number of non-sign bits
  typedef std::integral_constant<int,0> digits;

  //! The number of digits (in decimal base) that can be represented
  typedef std::integral_constant<int,0> digits10;

  //! The number of digits (in decimal base) required to ensure that values that differ are always differentiated
  typedef std::integral_constant<int,0> max_digits10;

  //! Used to check if the quantity is signed
  typedef std::false_type is_signed;

  //! Used to check if the quantity is an integer type
  typedef std::false_type is_integer;

  //! Used to check if the quantity is complex
  typedef std::false_type is_complex;

  //! Used to check if the quantity uses exact representations
  typedef std::false_type is_exact;

  //! Base of the representation
  typedef std::integral_constant<int,0> radix;

  //! Min negative integer value such that radix raised to (this-1) generates a normalized floating-point quantity (only available for floating-point quantities)
  typedef std::integral_constant<int,0> min_exponent;

  //! Min negative integer value such that 10 raised to that power generates a normalized floating-point quantity (only available for floating-point quantities)
  typedef std::integral_constant<int,0> min_exponent10;

  //! Used to check if the quantity has a representation for positive infinity
  typedef std::false_type has_infinity;

  //! Used to check if the quantity has a representation for quiet nan
  typedef std::false_type has_quiet_nan;

  //! Used to check if the quantity has a representation for signaling nan
  typedef std::false_type has_signaling_nan;

  //! Used to check if the quantity allows denormalized values
  typedef std::false_type has_denorm;

  //! Used to check if a loss of accuracy is detected as a denormalization loss instead of an inexact result
  typedef std::false_type has_denorm_loss;

  //! Used to check if a quantity adheres to IEC-559/IEEE-754 standard
  typedef std::false_type is_iec559;

  //! Used to check if the set of values represented by the quantity is finite
  typedef std::false_type is_bounded;

  //! Used to check if the quantity is modulo
  typedef std::false_type is_modulo;

  //! Used to check if trapping is implemented for the quantity
  typedef std::false_type traps;

  //! Used to check if tinyness is implemented before rounding
  typedef std::false_type tinyness_before;

  //! Used to check the rounding style of floating-point quantities (only available for floating-point quantities)
  typedef std::integral_constant<std::float_round_style,std::round_indeterminate> round_style;

  //! The quantity raised to power N/D type
  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetQuantityToPowerType
  { typedef QuantityType type; };

  //! Get the zero quantity
  static inline QuantityType zero() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the one quantity
  static inline QuantityType one() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the min quantity
  static inline QuantityType min() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the min positive denormalized value
  static inline QuantityType denormMin() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the max quantity
  static inline QuantityType max() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the lowest quantity
  static inline QuantityType lowest() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the machine epsilon (only available for floating-point quantities)
  static inline QuantityType epsilon() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the maximum rounding error (only available for floating-point quantities)
  static inline QuantityType roundError() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the inf quantity (only available for floating-point quantities)
  static inline QuantityType inf() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the quiet nan quantity (only available for floating-point quantities)
  static inline QuantityType nan() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the signaling nan quantity (only available for floating-point quantities)
  static inline QuantityType signalingNan() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the absolute value of a quantity
  static inline QuantityType abs( const QuantityType& a ) noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the conjugate of a quantity
  static inline QuantityType conjugate( const QuantityType& a ) noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the real part of the quantity
  static inline QuantityType real( const QuantityType& a ) noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the imaginary part of the quantity
  static inline QuantityType imag( const QuantityType& a ) noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  /*! Test if the quantity is a nan or inf (only available for floating-point quantities)
   */
  static inline bool isnaninf( const QuantityType& a ) noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Take the square root of a quantity (possible bug in boost::units::sqrt)
  static inline typename GetQuantityToPowerType<1,2>::type sqrt( const QuantityType& quantity ) noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Take a quantity to the desired rational power
  template<boost::units::integer_type N, boost::units::integer_type D>
  static inline typename GetQuantityToPowerType<N,D>::type rpow( const QuantityType& quantity ) noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Initialize a quantity (potentially dangerous!)
  static inline QuantityType initializeQuantity( const RawType& raw_quantity ) noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the raw value of a quantity
  static inline const RawType& getRawQuantity( const QuantityType& quantity ) noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Set the value of a quantity (potentially dangerous!)
  static inline void setQuantity( QuantityType& quantity,
				  const RawType& raw_quantity ) noexcept
  { UndefinedQuantityTraits<T>::notDefined(); }
};

/*! This function is a shortcut to the abs QuantityTraits function
 * \ingroup quantity_traits
 */
template<typename Quantity>
inline Quantity abs( const Quantity& quantity )
{
  return QuantityTraits<Quantity>::abs( quantity );
}

/*! This function is a shortcut to the the sqrt QuantityTraits function
 * \ingroup quantity_traits
 */
template<typename Quantity>
inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<1,2>::type
sqrt( const Quantity& quantity )
{
  return QuantityTraits<Quantity>::sqrt( quantity );
}

/*! This function is a shortcut to the rpow QuantityTraits function (rational pow)
 * \ingroup quantity_traits
 */
template<boost::units::integer_type N,
	 boost::units::integer_type D,
	 typename Quantity>
inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<N,D>::type
rpow( const Quantity& quantity )
{
  return QuantityTraits<Quantity>::template rpow<N,D>( quantity );
}

/*! This function is a shortcut to the getRawQuantity QuantityTraits function
 * \ingroup quantity_traits
 */
template<typename Quantity>
inline const typename QuantityTraits<Quantity>::RawType& getRawQuantity( const Quantity& quantity )
{
  return QuantityTraits<Quantity>::getRawQuantity( quantity );
}

/*! This method is a shortcut to the setQuantity QuantityTraits method
 * \details This method should only be used in very rare cases such as when a 
 * class template parameter can be either a unit-aware type 
 * (e.g. boost::quantity<unit,double>) or a "raw" type (e.g. double). It
 * is dangerous because it avoids the type checking that is normally done
 * with unit-aware types.
 * \ingroup quantity_traits
 */
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
