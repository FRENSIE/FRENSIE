//---------------------------------------------------------------------------//
//!
//! \file   Utility_QuantityTraits.hpp
//! \author Alex Robinson
//! \brief  Quantity traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_QUANTITY_TRAITS_HPP
#define UTILITY_QUANTITY_TRAITS_HPP

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/cmath.hpp>
#include <boost/units/static_rational.hpp>
#include <boost/units/limits.hpp>
#include <boost/units/io.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/type_traits/is_floating_point.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_QuantityTraitsDecl.hpp"

namespace Utility{

/*! \brief The QuantityTraitsHelper partial specialization for floating point
 * boost::units::quantity
 * \ingroup quantity_traits
 */
template<typename Unit, typename T>
struct QuantityTraitsHelper<boost::units::quantity<Unit,T>,typename boost::enable_if<boost::is_floating_point<T> >::type>
{
private:
  typedef boost::units::quantity<Unit,T> QuantityType;
  typedef T RawType;

public:
  static inline QuantityType inf()
  { return QuantityType::from_value( std::numeric_limits<RawType>::infinity() ); }

  static inline QuantityType nan()
  { return QuantityType::from_value( Teuchos::ScalarTraits<RawType>::nan() ); }

  static inline bool isnaninf( const QuantityType& a )
  { return Teuchos::ScalarTraits<RawType>::isnaninf( a.value() ); }
};

/*! \brief The partial specialization of QuantityTraits for arithmetic
 * boost::units::quantity
 * \ingroup quantity_traits
 */
template<typename Unit, typename T>
struct QuantityTraits<boost::units::quantity<Unit,T>, typename boost::enable_if<boost::is_arithmetic<T> >::type> : public QuantityTraitsHelper<boost::units::quantity<Unit,T> >
{
  typedef Unit UnitType;
  typedef T RawType;
  typedef boost::units::quantity<Unit,T> QuantityType;
  typedef boost::is_floating_point<T> is_floating_point;

  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetQuantityToPowerType
  {
    typedef typename boost::units::power_typeof_helper<QuantityType,boost::units::static_rational<N,D> >::type type;
  };

  static inline QuantityType zero()
  { return QuantityType::from_value( RawType(0) ); }

  static inline QuantityType one()
  { return QuantityType::from_value( RawType(1) ); }

  static inline QuantityType conjugate( const QuantityType& a )
  { return QuantityType::from_value( Teuchos::ScalarTraits<RawType>::conjugate( a.value() ) ); }

  static inline QuantityType real( const QuantityType& a )
  { return QuantityType::from_value( Teuchos::ScalarTraits<RawType>::real( a.value() ) ); }

  static inline QuantityType imag( const QuantityType& a )
  { return QuantityType::from_value( Teuchos::ScalarTraits<RawType>::imag( a.value() ) ); }

  //! Possible bug in boost::units::sqrt
  static inline typename GetQuantityToPowerType<1,2>::type sqrt( const QuantityType& quantity )
  {
    return GetQuantityToPowerType<1,2>::type::from_value( std::sqrt( quantity.value() ) );
    // return boost::units::sqrt( quantity )
  }

  template<boost::units::integer_type N, boost::units::integer_type D>
  static inline typename GetQuantityToPowerType<N,D>::type rpow( const QuantityType& quantity )
  { return boost::units::pow<boost::units::static_rational<N,D> >( quantity ); }
  //! Potentially dangerous to initialize quantities in this way!
  static inline QuantityType initializeQuantity( const RawType& raw_quantity )
  { return QuantityType::from_value( raw_quantity ); }

  //! Get the raw value of a quantity
  static inline const RawType& getRawQuantity( const QuantityType& quantity )
  { return quantity.value(); }

  //! Set the value of a quantity (potentially dangerous!)
  static inline void setQuantity( QuantityType& quantity,
				  const RawType& raw_quantity )
  { quantity = QuantityType::from_value( raw_quantity ); }
};

/*! \brief The QuantityTraitsHelper partial specialization for floating point
  types (no units).
 * \ingroup quantity_traits
 */
template<typename T>
struct QuantityTraitsHelper<T,typename boost::enable_if<boost::is_floating_point<T> >::type>
{
private:
  typedef T QuantityType;

public:

  static inline QuantityType inf()
  { return std::numeric_limits<QuantityType>::infinity(); }

  static inline QuantityType nan()
  { return Teuchos::ScalarTraits<QuantityType>::nan(); }

  static inline bool isnaninf( const QuantityType& a )
  { return Teuchos::ScalarTraits<QuantityType>::isnaninf(a); }
};

/*! The specialization of QuantityTraits for all arithmetic types (no units).
 *
 * Note that having no units is different from a dimensionless unit.
 * \ingroup quantity_traits
 */
template<typename T>
struct QuantityTraits<T,typename boost::enable_if<boost::is_arithmetic<T> >::type> : public QuantityTraitsHelper<T>
{
  typedef void Unit;
  typedef T RawType;
  typedef T QuantityType;
  typedef boost::is_floating_point<T> is_floating_point;

  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetQuantityToPowerType
  { typedef QuantityType type; };

  static inline QuantityType zero()
  { return RawType(0); }

  static inline QuantityType one()
  { return RawType(1); }

  static inline QuantityType conjugate( const QuantityType& a )
  { return Teuchos::ScalarTraits<QuantityType>::conjugate(a); }

  static inline QuantityType real( const QuantityType& a )
  { return Teuchos::ScalarTraits<QuantityType>::real(a); }

  static inline QuantityType imag( const QuantityType& a )
  { return Teuchos::ScalarTraits<QuantityType>::imag(a); }

  static inline QuantityType sqrt( const QuantityType quantity )
  { return std::sqrt( quantity ); }

  template<boost::units::integer_type N, boost::units::integer_type D>
  static inline QuantityType rpow( const QuantityType quantity )
  { return boost::units::pow<boost::units::static_rational<N,D> >( quantity ); }

  static inline QuantityType initializeQuantity( const RawType& raw_quantity )
  { return raw_quantity; }

  static inline const RawType& getRawQuantity( const QuantityType& quantity )
  { return quantity; }

  static inline void setQuantity( QuantityType& quantity,
				  const RawType& raw_quantity )
  { quantity = raw_quantity; }
};

} // end Utility namespace

#endif // end UTILITY_QUANTITY_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_QuantityTraits.hpp
//---------------------------------------------------------------------------//
