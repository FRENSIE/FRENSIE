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

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"

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

  /*! The raw floating-point quantity type
   * 
   * This is the raw floating-point type that corresponds to the
   * RawType. If RawType is a floating-point type or a complex floating-point
   * type then this type is identical to the RawType.
   * Examples: 
   * <ul>
   *  <li> RawType==int -> RawFloatingPointType==double </li>
   *  <li> RawType==float -> RawFloatingPointType==float </li>
   *  <li> RawType==double -> RawFloatingPointType==double </li>
   *  <li> RawType==std::complex<int> -> RawFloatingPointType==std::complex<double> </li>
   *  <li> RawType==std::complex<float> -> RawFloatingPointType==std::complex<float> </li>
   *  <li> RawType==std::complex<double> -> RawFloatingPointType==std::complex<double> </li>
   * </ul>
   *
   */
  typedef T RawFloatingPointType;

  /*! The real raw floating-point quantity type
   *
   * This is the real raw floating-point type that corresponds to
   * the RawFloatingPointType. If RawFloatingPointType is not a complex
   * floating-point type then this type is identical to the 
   * RawFloatingPointType.
   * Examples:
   * <ul>
   *  <li> RawFloatingPointType==float -> RealRawFloatingPointType==float </li>
   *  <li> RawFloatingPointType==double -> RealRawFloatingPointType==double </li>
   *  <li> RawFloatingPointType==std::complex<float> -> RealRawFloatingPointType==float </li>
   *  <li> RawFloatingPointType==std::complex<double> -> RealRawFloatingPointType==double </li>
   * </ul>
   */
  typedef T RealRawFloatingPointType;

  /*! The quantity type
   *
   * If the UnitType is not void, this type will be 
   * boost::units::quantity<Unit,RawType>. Otherwise, this type will be 
   * the same as the RawType.
   */
  typedef T QuantityType;

  /*! The floating-point quantity type
   *
   * If the UnitType is not void, this type will be 
   * boost::units::quantity<Unit,RawFloatingPointType>. Otherwise, this type
   * will be the same as the RawFloatingPointType.
   */
  typedef T FloatingPointQuantityType;

  /*! The real floating-point quantity type
   *
   * If the UnitType is not void, this type will be
   * boost::units::quantity<Unit,RealRawFloatingPointType>. Otherwise, this
   * type will be the same as the RealRawFloatingPointType.
   */
  typedef T RealFloatingPointQuantityType;

  //! The quantity raised to power N/D type
  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetQuantityToPowerType
  {
    typedef QuantityType type;
    typedef FloatingPointQuantityType AsFloatingPointType;
  };

  //! Used to check if the traits class for quantity type is specialized
  typedef std::false_type is_specialized;

  //! Used to check if the quantity is signed
  typedef std::false_type is_signed;

  //! Used to check if the quantity is an integer type
  typedef std::false_type is_integer;

  //! Used to check if the quantity is complex
  typedef std::false_type is_complex;

  //! Used to check if the quantity uses exact representations
  typedef std::false_type is_exact;

  //! Used to check if a quantity adheres to IEC-559/IEEE-754 standard
  typedef std::false_type is_iec559;

  //! Used to check if the set of values represented by the quantity is finite
  typedef std::false_type is_bounded;

  //! Used to check if the quantity is modulo
  typedef std::false_type is_modulo;

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

  //! Used to check if trapping is implemented for the quantity
  typedef std::false_type traps;

  //! Used to check if tinyness is implemented before rounding
  typedef std::false_type tinyness_before;

  //! Used to check the rounding style of floating-point quantities 
  typedef std::integral_constant<std::float_round_style,std::round_indeterminate> round_style;

    //! The number of non-sign bits
  typedef std::integral_constant<int,0> digits;

  //! The number of digits (in decimal base) that can be represented
  typedef std::integral_constant<int,0> digits10;

  //! The number of digits (in decimal base) required to ensure that values that differ are always differentiated
  typedef std::integral_constant<int,0> max_digits10;

  //! Base of the representation
  typedef std::integral_constant<int,0> radix;

  //! Min negative integer value such that radix raised to (this-1) generates a normalized floating-point quantity 
  typedef std::integral_constant<int,0> min_exponent;

  //! Min negative integer value such that 10 raised to that power generates a normalized floating-point quantity 
  typedef std::integral_constant<int,0> min_exponent10;

  //! One more than the largest integer power of the radix that is a valid finite floating-point value
  typedef std::integral_constant<int,0> max_exponent;

  //! Max integer power of 10 that is a valid finite floating-point value
  typedef std::integral_constant<int,0> max_exponent10;

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

  //! Get the machine epsilon (only defined for floating-point types)
  static inline QuantityType epsilon() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

    //! Get comparison tolerance (only defined for floating-point types)
  static inline QuantityType comparisonTolerance() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the maximum rounding error (only defined for floating-point types)
  static inline QuantityType roundError() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the inf quantity (only defined for floating-point types)
  static inline QuantityType inf() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the quiet nan quantity (only defined for floating-point types)
  static inline QuantityType nan() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the signaling nan quantity (only defined for floating-point types)
  static inline QuantityType signalingNan() noexcept
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the absolute value of a quantity
  static inline RealFloatingPointQuantityType abs( const QuantityType& a )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the conjugate of a quantity
  static inline FloatingPointQuantityType conj( const QuantityType& a )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the real part of the quantity
  static inline RealFloatingPointQuantityType real( const QuantityType& a )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the imaginary part of the quantity
  static inline RealFloatingPointQuantityType imag( const QuantityType& a )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Test if the quantity is a nan or inf 
  static inline bool isnaninf( const QuantityType& a )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Take the square root of a quantity (only one root will be calculated)
  static inline typename GetQuantityToPowerType<1,2>::AsFloatingPointType sqrt( const QuantityType& quantity )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Take the cube root of a quantity (only one root will be calculated)
  static inline typename GetQuantityToPowerType<1,3>::AsFloatingPointType cbrt( const QuantityType& quantity )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Take a quantity to the desired rational power
  template<boost::units::integer_type N, boost::units::integer_type D>
  static inline typename GetQuantityToPowerType<N,D>::AsFloatingPointType rpow( const QuantityType& quantity )
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

  //! Reinterpret quantity type memory as raw type memory 
  static inline RawType* reinterpretAsRaw( QuantityType* quantity )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Reinterpret const quantity type memory as raw type memory
  static inline const RawType* reinterpretAsRaw( const QuantityType* quantity )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Reinterpret raw type memory as quantity type memory
  static inline QuantityType* reinterpretAsQuantity( RawType* raw_quantity )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Reinterpret const raw type memory as quantity type memory
  static inline const QuantityType* reinterpretAsQuantity( const RawType* raw_quantity )
  { return UndefinedQuantityTraits<T>::notDefined(); }
};

/*! This function is a shortcut to the abs QuantityTraits function
 * \ingroup quantity_traits
 */
template<typename Quantity>
inline typename QuantityTraits<Quantity>::RealFloatingPointQuantityType
abs( const Quantity& quantity )
{
  return QuantityTraits<Quantity>::abs( quantity );
}

/*! This function is a shortcut to the conj QuantityTraits function
 * \ingroup quantity_traits
 */
template<typename Quantity>
inline typename QuantityTraits<Quantity>::FloatingPointQuantityType
conj( const Quantity& a )
{ 
  return QuantityTraits<Quantity>::conj( a );
}

/*! This function is a shortcut to the real QuantityTraits function
 * \ingroup quantity_traits
 */
template<typename Quantity>
inline typename QuantityTraits<Quantity>::RealFloatingPointQuantityType
real( const Quantity& a )
{
  return QuantityTraits<Quantity>::real( a );
}

/*! This function is a shortcut to the imag QuantityTraits function
 * \ingroup quantity_traits
 */
template<typename Quantity>
inline typename QuantityTraits<Quantity>::RealFloatingPointQuantityType
imag( const Quantity& a )
{
  return QuantityTraits<Quantity>::imag( a );
}

/*! This function is a shortcut to the isnaninf QuantityTraits function
 * \ingroup quantity_traits
 */
template<typename Quantity>
inline bool isnaninf( const Quantity& a )
{
  return QuantityTraits<Quantity>::isnaninf( a );
}

/*! This function is a shortcut to the sqrt QuantityTraits function
 * \ingroup quantity_traits
 */
template<typename Quantity>
inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<1,2>::AsFloatingPointType
sqrt( const Quantity& quantity )
{
  return QuantityTraits<Quantity>::sqrt( quantity );
}

/*! This function is a shortcut to the cbrt QuantityTraits function
 * \ingroup quantity_traits
 */
template<typename Quantity>
inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<1,3>::AsFloatingPointType
cbrt( const Quantity& quantity )
{
  return QuantityTraits<Quantity>::cbrt( quantity );
}  

/*! This function is a shortcut to the rpow QuantityTraits function (rational pow)
 * \ingroup quantity_traits
 */
template<boost::units::integer_type N,
	 boost::units::integer_type D,
	 typename Quantity>
inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<N,D>::AsFloatingPointType
rpow( const Quantity& quantity )
{
  return QuantityTraits<Quantity>::template rpow<N,D>( quantity );
}

/*! This function is a shortcut to the rpow QuantityTraits function (rational pow)
 * \ingroup quantity_traits
 */
template<boost::units::integer_type N,
	 typename Quantity>
inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<N,1>::AsFloatingPointType
rpow( const Quantity& quantity )
{
  return QuantityTraits<Quantity>::template rpow<N,1>( quantity );
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

/*! This method is a shortcut to the reinterpretAsRaw QuantityTraits method
 * \details This method should only be used in very rare cases when an array
 * of quantities needs to be passed through an interface that only excepts
 * arrays of the raw type
 * \ingroup quantity_traits
 */
template<typename Quantity>
inline typename std::conditional<std::is_const<Quantity>::value,
                                 const typename QuantityTraits<typename std::remove_const<Quantity>::type>::RawType,
                                       typename QuantityTraits<typename std::remove_const<Quantity>::type>::RawType>::type*
reinterpretAsRaw( Quantity* quantity )
{
  return QuantityTraits<typename std::remove_const<Quantity>::type>::reinterpretAsRaw( quantity );
}

/*! \brief This method is a shortcut to the reinterpretAsQuantity 
 * QuantityTraits method.
 *
 * This method should only be used in very rare cases when an array of 
 * raw types needs to be passed through an interface that only excepts
 * arrays of the quantities
 * \ingroup quantity_traits
 */
template<typename Quantity, typename RawType>
inline typename std::conditional<std::is_const<RawType>::value,
                                 const typename std::remove_const<Quantity>::type,
                                       typename std::remove_const<Quantity>::type>::type*
reinterpretAsQuantity( RawType* raw_quantity )
{
  // The raw types must match
  testStaticPrecondition( (std::is_same<typename std::remove_const<RawType>::type,typename QuantityTraits<typename std::remove_const<Quantity>::type>::RawType>::value) );
  
  return QuantityTraits<typename std::remove_const<Quantity>::type>::reinterpretAsQuantity( raw_quantity );
}

} // end Utility namespace

#endif // end UTILITY_QUANTITY_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_QuantityTraitsDecl.hpp
//---------------------------------------------------------------------------//
