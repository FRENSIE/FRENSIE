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
 * The default implementation will not compile. Specializations should be
 * made for types of interest.
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

  //! Used to check if the quantity is a floating point quantity
  typedef boost::is_floating_point<T> is_floating_point;
  
  //! The quantity raised to power N/D type
  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetQuantityToPowerType
  { typedef QuantityType type; };

  //! Get the zero quantity
  static inline QuantityType zero()
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the one quantity
  static inline QuantityType one()
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the inf quantity (only available for floating point quantities)
  static inline QuantityType inf()
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the nan quantity (only available for floating point quantities)
  static inline QuantityType nan()
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the conjugate of a quantity
  static inline QuantityType conjugate( const QuantityType& a )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the real part of the quantity
  static inline QuantityType real( const QuantityType& a )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the imaginary part of the quantity
  static inline QuantityType imag( const QuantityType& a )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  /*! \brief Test if the quantity is a nan or inf (only available for floating point quantities)
   */
  static inline bool isnaninf( const QuantityType& a )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Take the square root of a quantity (possible bug in boost::units::sqrt)
  static inline typename GetQuantityToPowerType<1,2>::type sqrt( const QuantityType& quantity )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Take a quantity to the desired rational power
  template<boost::units::integer_type N, boost::units::integer_type D>
  static inline typename GetQuantityToPowerType<N,D>::type rpow( const QuantityType& quantity )
  { return UndefinedQuantityTraits<T>::notDefined(); }
  
  //! Initialize a quantity (potentially dangerous!)
  static inline QuantityType initializeQuantity( const RawType& raw_quantity )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Get the raw value of a quantity
  static inline const RawType& getRawQuantity( const QuantityType& quantity )
  { return UndefinedQuantityTraits<T>::notDefined(); }

  //! Set the value of a quantity (potentially dangerous!)
  static inline void setQuantity( QuantityType& quantity,
				  const RawType& raw_quantity )
  { UndefinedQuantityTraits<T>::notDefined(); }
};

/*! The QuantityTraitsHelper for all types.
 * \details Specialize this struct to add functions/typedefs when T has
 * certain properties (e.g. floating point).
 * \ingroup quantity_traits
 */
template<typename T, typename Enabled = void>
struct QuantityTraitsHelper
{ /* ... */ };

/*! This function allows access to the sqrt QuantityTraits function
 * \ingroup quantity_traits
 */
template<typename Quantity>
inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<1,2>::type 
sqrt( const Quantity& quantity )
{
  return QuantityTraits<Quantity>::sqrt( quantity );
}

/*! This function allows access to the pow QuantityTraits function (rational pow)
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

/*! This function allows access to the getRawQuantity QuantityTraits function
 * \ingroup quantity_traits
 */
template<typename Quantity>
inline const typename QuantityTraits<Quantity>::RawType& getRawQuantity( const Quantity& quantity )
{ 
  return QuantityTraits<Quantity>::getRawQuantity( quantity ); 
}

/*! This function allows access to the setQuantity QuantityTraits function
 * \details Avoid this function at all costs! It should only be used in very
 * rare cases where a class template parameter can be either a unit-aware
 * type (e.g. boost::quantity<unit,double>) or a "raw" type (e.g. double). It
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
