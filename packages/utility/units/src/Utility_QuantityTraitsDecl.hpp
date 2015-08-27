//---------------------------------------------------------------------------//
//!
//! \file   Utility_QuantityTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Quantity traits declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_QUANTITY_TRAITS_DECL_HPP
#define UTILITY_QUANTITY_TRAITS_DECL_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"

/*! \defgroup quantity_traits Quantity Traits
 * \ingroup traits
 */

namespace Utility{

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

  //! The quantity raised to power N/D type
  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetQuantityToPowerType
  { typedef QuantityType type; };

  //! Get the zero quantity
  static inline QuantityType zero()
  { return UndefinedTraits<T>::notDefined(); }

  //! Get the one quantity
  static inline QuantityType one()
  { return UndefinedTraits<T>::notDefined(); }

  //! Get the nan quantity
  static inline QuantityType nan()
  { return UndefinedTraits<T>::notDefined(); }

  //! Get the conjugate of a quantity
  static inline QuantityType conjugate( const QuantityType& a )
  { return UndefinedTraits<T>::notDefined(); }

  //! Get the real part of the quantity
  static inline QuantityType real( const QuantityType& a )
  { return UndefinedTraits<T>::notDefined(); }

  //! Get the imaginary part of the quantity
  static inline QuantityType imag( const QuantityType& a )
  { return UndefinedTraits<T>::notDefined(); }

  //! Test if the quantity is a nan or inf
  static inline bool isnaninf( const QuantityType& a )
  { return UndefinedTraits<T>::notDefined(); }

  //! Take the square root of a quantity (possible bug in boost::units::sqrt)
  static inline typename GetQuantityToPowerType<1,2>::type sqrt( const QuantityType& quantity )
  { return UndefinedTraits<T>::notDefined(); }

  //! Take a quantity to the desired rational power
  template<boost::units::integer_type N, boost::units::integer_type D>
  static inline typename GetQuantityToPowerType<N,D>::type rpow( const QuantityType& quantity )
  { return UndefinedTraits<T>::notDefined(); }
  
  //! Initialize a quantity (potentially dangerous!)
  static inline QuantityType initializeQuantity( const RawType& raw_quantity )
  { return UndefinedTraits<T>::notDefined(); }

  //! Get the raw value of a quantity
  static inline const RawType& getRawQuantity( const QuantityType& quantity )
  { return UndefinedTraits<T>::notDefined(); }

  //! Set the value of a quantity (potentially dangerous!)
  static inline void setQuantity( QuantityType& quantity,
				  const RawType& raw_quantity )
  { UndefinedTraits<T>::notDefined(); }
};

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
