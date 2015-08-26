//---------------------------------------------------------------------------//
//!
//! \file   Utility_QuantityTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Quantity traits declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_QUANTITY_TRAITS_DECL_HPP
#define UTILITY_QUANTITY_TRAITS_DECL_HPP

// Boost Includes
#include <boost/units/cmath.hpp>
#include <boost/units/static_rational.hpp>
#include <boost/units/limits.hpp>
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

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
  //! The raw quantity type
  typedef typename Quantity::value_type RawType;

  //! The quantity raised to power N/D type
  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetQuantityToPowerType
  {
    typedef typename boost::units::power_typeof_helper<Quantity,boost::units::static_rational<N,D> >::type type;
  };

  //! Get the zero quantity
  static inline Quantity zero()
  { return Quantity::from_value( RawType(0) ); }

  //! Get the one quantity
  static inline Quantity one()
  { return Quantity::from_value( RawType(1) ); }

  //! Take the square root of a quantity (possible bug in boost::units::sqrt)
  static inline typename GetQuantityToPowerType<1,2>::type sqrt( const Quantity& quantity )
  { 
    return GetQuantityToPowerType<1,2>::type::from_value( std::sqrt( quantity.value() ) ); 
    // return boost::units::sqrt( quantity )
  }

  //! Take a quantity to the desired rational power
  template<boost::units::integer_type N, boost::units::integer_type D>
  static inline typename GetQuantityToPowerType<N,D>::type rpow( const Quantity& quantity )
  { return boost::units::pow<boost::units::static_rational<N,D> >( quantity ); }
  
  //! Initialize a quantity (potentially dangerous!)
  static inline Quantity initializeQuantity( const RawType& raw_quantity )
  { return Quantity::from_value( raw_quantity ); }

  //! Initialize a quantity (standard boost::units conversion - safe)
  template<typename InputQuantity>
  static inline Quantity initializeQuantity( const InputQuantity& input_quantity )
  { return Quantity( input_quantity ); }

  //! Get the raw value of a quantity
  static inline const RawType& getRawQuantity( const Quantity& quantity )
  { return quantity.value(); }

  //! Set the value of a quantity (potentially dangerous!)
  static inline void setQuantity( Quantity& quantity,
				  const RawType& raw_quantity )
  { quantity = Quantity::from_value( raw_quantity ); }
};

//! This function allows access to the sqrt QuantityTraits function
template<typename Quantity>
inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<1,2>::type 
sqrt( const Quantity& quantity )
{
  return QuantityTraits<Quantity>::sqrt( quantity );
}

//! This function allows access to the pow QuantityTraits function (rational pow)
template<boost::units::integer_type N,
	 boost::units::integer_type D,
	 typename Quantity>
inline typename QuantityTraits<Quantity>::template GetQuantityToPowerType<N,D>::type
rpow( const Quantity& quantity )
{
  return QuantityTraits<Quantity>::template rpow<N,D>( quantity );
}

//! This function allows access to the getRawQuantity QuantityTraits function
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
 */
template<typename Quantity>
inline void setQuantity( Quantity& quantity,
			 const typename QuantityTraits<Quantity>::RawType& raw_quantity )
{ 
  QuantityTraits<Quantity>::setQuantity( quantity, raw_quantity );
}

} // end Utility namespace

namespace Teuchos{

//! Partial specialization of Teuchos::ScalarTraits for boost::units::quantity
template<typename Unit, typename T>
struct ScalarTraits<boost::units::quantity<Unit,T> >
{
  typedef boost::units::quantity<Unit,T> QuantityT;
  typedef boost::units::quantity<Unit,T> magnitudeType;
  typedef boost::units::quantity<Unit,typename ScalarTraits<T>::halfPrecision> haflPrecision;
  typedef boost::units::quantity<Unit,typename ScalarTraits<T>::doublePrecision> doublePrecision;

  static const bool isComplex = ScalarTraits<T>::isComplex;
  static const bool isOrdinal = ScalarTraits<T>::isOrdinal;
  static const bool isComparable = ScalarTraits<T>::isComparable;
  static const bool hasMachineParameters = ScalarTraits<T>::hasMachineParameters;
  static inline magnitudeType eps() { return magnitudeType::from_value( ScalarTraits<T>::eps() ); }
  static inline magnitudeType sfmin() { return magnitudeType::from_value( ScalarTraits<T>::sfmin() ); }
  static inline magnitudeType base() { return magnitudeType::from_value( ScalarTraits<T>::base() ); }
  static inline magnitudeType prec() { return magnitudeType::from_value( ScalarTraits<T>::prec() ); }
  static inline magnitudeType t() { return magnitudeType::from_value( ScalarTraits<T>::t() ); }
  static inline magnitudeType rnd() { return magnitudeType::from_value( ScalarTraits<T>::rnd() ); }
  static inline magnitudeType emin() { return magnitudeType::from_value( ScalarTraits<T>::emin() ); }
  static inline magnitudeType rmin() { return magnitudeType::from_value( ScalarTraits<T>::rmin() ); }
  static inline magnitudeType emax() { return magnitudeType::from_value( ScalarTraits<T>::emax() ); }
  static inline magnitudeType rmax() { return magnitudeType::from_value( ScalarTraits<T>::rmax() ); }
  static magnitudeType magnitude(const QuantityT& a) { return boost::units::fabs(a); }
  static inline magnitudeType zero() { return Utility::QuantityTraits<magnitudeType>::zero(); }
  static inline magnitudeType one() { return Utility::QuantityTraits<magnitudeType>::one(); }
  static inline magnitudeType conjugate(magnitudeType a){ return magnitudeType::from_value( ScalarTraits<T>::conjugate( a.value() ) ); }
  static inline magnitudeType real(magnitudeType a){ return magnitudeType::from_value( ScalarTraits<T>::real( a.value() ) ); }
  static inline magnitudeType imag(magnitudeType a){ return magnitudeType::from_value( ScalarTraits<T>::imag( a.value() ) ); }
  static inline magnitudeType nan() { return magnitudeType::from_value( ScalarTraits<T>::nan() ); }
  static inline bool isnaninf(magnitudeType a) { return ScalarTraits<T>::isnaninf( a.value() ); }
  static inline void seedrandom(unsigned int s) { ScalarTraits<T>::seedrandom(s); }
  static inline magnitudeType random() { return magnitudeType::from_value( ScalarTraits<T>::random() ); }
  static inline std::string name() { return std::string("boost::units::quantity<")+boost::units::name_string(Unit())+std::string(",")+ScalarTraits<T>::name()+std::string(">"); }
  static inline typename Utility::QuantityTraits<magnitudeType>::template GetQuantityToPowerType<1,2>::type squareroot(magnitudeType a) { return Utility::sqrt(a); }
  //pow - incompatible
};

} // end Teuchos namespace

#endif // end UTILITY_QUANTITY_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_QuantityTraitsDecl.hpp
//---------------------------------------------------------------------------//
