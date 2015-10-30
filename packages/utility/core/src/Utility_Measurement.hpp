//---------------------------------------------------------------------------//
//!
//! \file   Utility_Measurement.hpp
//! \author Alex Robinson
//! \brief  The measurement class declaration. This object is based of of the
//!         measurement class in the boost::units examples
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MEASUREMENT_HPP
#define UTILITY_MEASUREMENT_HPP

// Boost Includes
#include <boost/units/config.hpp>
#include <boost/units/operators.hpp>
#include <boost/typeof/typeof.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_PrintableObject.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

/*! The measurement class
 *
 * This class wraps is meant to be used as any typical scalar type
 * (e.g. double). It is designed to keep track of and propagate the
 * uncertainty of a value (like one would with a measured quantity).
 */
template<typename T>
class Measurement : public PrintableObject
{

private:

  // The scalar traits typedef
  typedef Teuchos::ScalarTraits<T> ST;
  
public:

  //! The typedef for this type
  typedef Measurement<T> ThisType;
  
  //! The typedef for the value type
  typedef T ValueType;

  //! Constructor
  Measurement( const ValueType& value = ValueType(),
	       const ValueType& uncertainty = ValueType() );

  //! Copy constructor
  Measurement( const ThisType& other_measurement );

  //! Destructor
  ~Measurement()
  { /* ... */ }

  //! Print method
  void print( std::ostream& os ) const;

  //! Return the value of the measurement
  const ValueType& getValue() const;

  //! Return the uncertainty of the measurement
  const ValueType& getUncertainty() const;

  //! Return the relative uncertainty of the measurement
  const ValueType getRelativeUncertainty() const;

  //! Return the lower bound of the measurement
  const ValueType getLowerBound() const;
  
  //! Return the upper bound of the measurement
  const ValueType getUpperBound() const;

  //! Implicit conversion to value type
  operator ValueType() const;

  //! In-place addition operator
  ThisType& operator+=( const ValueType& value );

  //! In-place addition operator
  ThisType& operator+=( const ThisType& other_measurement );

  //! In-place subtraction operator
  ThisType& operator-=( const ValueType& value );

  //! In-place subtraction operator
  ThisType& operator-=( const ThisType& other_measurement );

  //! In-place multiplication operator
  ThisType& operator*=( const ValueType& value );

  //! In-place multiplication operator
  ThisType& operator*=( const ThisType& other_measurement );

  //! In-place division operator
  ThisType& operator/=( const ValueType& value );

  //! In-place division operator
  ThisType& operator/=( const ThisType& other_measurement );

private:

  // The measurement value
  ValueType d_value;

  // The measurement uncertainty
  ValueType d_uncertainty;
};

//! Addition operator
template<typename T>
inline Measurement<T> operator+( T lhs, const Measurement<T>& rhs )
{
  // Make sure nested conditions are met
  testNestedConditionsBegin(1);
  
  return (Measurement<T>( lhs, T(0) ) += rhs);
  
  testNestedConditionsEnd(1);
}

//! Addition operator
template<typename T>
inline Measurement<T> operator+( const Measurement<T>& lhs, T rhs )
{
  // Make sure nested conditions are met
  testNestedConditionsBegin(1);
  
  return (Measurement<T>( lhs ) += Measurement<T>( rhs, T(0) ));

  testNestedConditionsEnd(1);
}

//! Addition operator
template<typename T>
inline Measurement<T> operator+( const Measurement<T>& lhs, 
				 const Measurement<T>& rhs )
{
  // Make sure nested conditions are met
  testNestedConditionsBegin(1);
  
  return (Measurement<T>( lhs ) += rhs );

  testNestedConditionsEnd(1);
}

//! Subtraction operator
template<typename T>
inline Measurement<T> operator-( T lhs, const Measurement<T>& rhs )
{
  // Make sure nested conditions are met
  testNestedConditionsBegin(1);
  
  return (Measurement<T>( lhs, T(0) ) -= rhs);

  testNestedConditionsEnd(1);
}

//! Subtraction operator
template<typename T>
inline Measurement<T> operator-( const Measurement<T>& lhs, T rhs )
{
  // Make sure nested conditions are met
  testNestedConditionsBegin(1);
  
  return (Measurement<T>( lhs ) -= Measurement<T>( rhs, T(0) ));

  testNestedConditionsEnd(1);
}

//! Subtraction operator
template<typename T>
inline Measurement<T> operator-( const Measurement<T>& lhs, 
				 const Measurement<T>& rhs )
{
  // Make sure nested conditions are met
  testNestedConditionsBegin(1);
  
  return (Measurement<T>( lhs ) -= rhs );

  testNestedConditionsEnd(1);
}

//! Multiplication operator
template<typename T>
inline Measurement<T> operator*( T lhs, const Measurement<T>& rhs )
{
  // Make sure nested conditions are met
  testNestedConditionsBegin(1);
  
  return (Measurement<T>( lhs, T(0) ) *= rhs);

  testNestedConditionsEnd(1);
}

//! Multiplication operator
template<typename T>
inline Measurement<T> operator*( const Measurement<T>& lhs, T rhs )
{
  // Make sure nested conditions are met
  testNestedConditionsBegin(1);
  
  return (Measurement<T>( lhs ) *= Measurement<T>( rhs, T(0) ));

  testNestedConditionsEnd(1);
}

//! Multiplication operator
template<typename T>
inline Measurement<T> operator*( const Measurement<T>& lhs, 
				 const Measurement<T>& rhs )
{
  // Make sure nested conditions are met
  testNestedConditionsBegin(1);
  
  return (Measurement<T>( lhs ) *= rhs );

  testNestedConditionsEnd(1);
}

//! Division operator
template<typename T>
inline Measurement<T> operator/( T lhs, const Measurement<T>& rhs )
{
  // Make sure nested conditions are met
  testNestedConditionsBegin(1);
  
  // Make sure nested conditions are met
  return (Measurement<T>( lhs, T(0) ) /= rhs);

  testNestedConditionsEnd(1);
}

//! Division operator
template<typename T>
inline Measurement<T> operator/( const Measurement<T>& lhs, T rhs )
{
  // Make sure nested conditions are met
  testNestedConditionsBegin(1);
  
  return (Measurement<T>( lhs ) /= Measurement<T>( rhs, T(0) ));
  
  testNestedConditionsEnd(1);
}

//! Division operator
template<typename T>
inline Measurement<T> operator/( const Measurement<T>& lhs, 
				 const Measurement<T>& rhs )
{
  // Make sure nested conditions are met
  testNestedConditionsBegin(1);
  
  return (Measurement<T>( lhs ) /= rhs );

  testNestedConditionsEnd(1);
}

//! Overload of sqrt for a measurement
template<typename T>
inline Measurement<T> sqrt( const Measurement<T>& x )
{
  // Make sure the measurement is valid
  testPrecondition( x.getValue() >= 0.0 );
  
  const T new_value = std::sqrt( x.getValue() );

  const T propagated_uncertainty = 0.5*(new_value/x.getValue())*
    x.getUncertainty();

  // Make sure reasonable values have been calculated
  testPostcondition( !Teuchos::ScalarTraits<T>::isnaninf( new_value ) );
  testPostcondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						    propagated_uncertainty ) );

  return Measurement<T>( new_value, propagated_uncertainty );
}

//! Overload of pow for a measurement
template<typename T, typename ExponentType>
inline Measurement<T> pow( const Measurement<T>& x, 
			   const ExponentType exponent )
{
  const T new_value = std::pow( x.getValue(), exponent );

  const T propagated_uncertainty = fabs(exponent*(new_value/x.getValue()))*
    x.getUncertainty();

  // Make sure reasonable values have been calculated
  testPostcondition( !Teuchos::ScalarTraits<T>::isnaninf( new_value ) );
  testPostcondition( !Teuchos::ScalarTraits<T>::isnaninf( 
						    propagated_uncertainty ) );
  testPostcondition( propagated_uncertainty >= 0.0 );

  return Measurement<T>( new_value, propagated_uncertainty );
}

} // end Utility namespace


namespace boost{

namespace units{

//! Specialization of the boost::units::power_typeof_helper
template<typename Y, long N, long D>
struct power_typeof_helper<Utility::Measurement<Y>,static_rational<N,D> >
{
  typedef Utility::Measurement<typename power_typeof_helper<Y,static_rational<N,D> >::type> type;
  
  static type value( const Utility::Measurement<Y>& x)
  {
    const static_rational<N,D> rational;

    const Y rational_power = Y(rational.numerator())/Y(rational.denominator());
    
    return Utility::pow( x, rational_power );
  }
};

//! Specialization of the boost::units::root_typeof_helper
template<typename Y, long N, long D>
struct root_typeof_helper<Utility::Measurement<Y>,static_rational<N,D> >
{
  typedef Utility::Measurement<typename root_typeof_helper<Y,static_rational<N,D> >::type> type;

  static type value( const Utility::Measurement<Y>& x )
  {
    const static_rational<N,D> rational;

    // Compute D/N instead of N/D since we're interested in the root
    const Y rational_power = Y(rational.denominator())/Y(rational.numerator());

    return Utility::pow( x, rational_power );
  }
};

} // end units namespace

} // end boost namespace

namespace Teuchos{

//! Partial specialization of Teuchos::ScalarTraits for the Measurement class
template<typename T>
struct ScalarTraits<Utility::Measurement<T> >
{
  typedef Utility::Measurement<T> Measurement;
  typedef T magnitudeType;
  typedef typename Teuchos::ScalarTraits<T>::halfPrecision halfPrecision;
  typedef typename Teuchos::ScalarTraits<T>::doublePrecision doublePrecision;
  
  static const bool isComplex = Teuchos::ScalarTraits<T>::isComplex;
  static const bool isOrdinal = Teuchos::ScalarTraits<T>::isOrdinal;
  static const bool isComparable = Teuchos::ScalarTraits<T>::isComparable;
  static const bool hasMachineParameters = Teuchos::ScalarTraits<T>::hasMachineParameters;

  static inline magnitudeType eps() { return ScalarTraits<magnitudeType>::eps(); }
  static inline magnitudeType sfmin() { return ScalarTraits<magnitudeType>::sfmin(); }
  static inline magnitudeType base() { return ScalarTraits<magnitudeType>::base(); }
  static inline magnitudeType prec() { return ScalarTraits<magnitudeType>::prec(); }
  static inline magnitudeType t() { return ScalarTraits<magnitudeType>::t(); }
  static inline magnitudeType rnd() { return ScalarTraits<magnitudeType>::rnd(); }
  static inline magnitudeType emin() { return ScalarTraits<magnitudeType>::emin(); }
  static inline magnitudeType rmin() { return ScalarTraits<magnitudeType>::rmin(); }
  static inline magnitudeType emax() { return ScalarTraits<magnitudeType>::emax(); }
  static inline magnitudeType rmax() { return ScalarTraits<magnitudeType>::rmax(); }
  static inline magnitudeType magnitude(Measurement a) { return ScalarTraits<magnitudeType>::magnitude( a.getValue() ); }
  static inline Measurement zero() { return Measurement( ScalarTraits<magnitudeType>::zero(), 0.0 ); }
  static inline Measurement one() { return Measurement( ScalarTraits<magnitudeType>::zero(), 1.0 ); }
  static inline Measurement conjugate(Measurement a){ return Measurement( ScalarTraits<magnitudeType>::conjugate(a.getValue()), ScalarTraits<magnitudeType>::conjugate(a.getUncertainty()) ); }
  static inline Measurement real(Measurement a){ return Measurement( ScalarTraits<magnitudeType>::real(a.getValue()), ScalarTraits<magnitudeType>::real(a.getUncertainty()) ); }
  static inline Measurement imag(Measurement a){ return Measurement( ScalarTraits<magnitudeType>::imag(a.getValue()), ScalarTraits<magnitudeType>::imag(a.getUncertainty()) ); }
  static inline Measurement nan() { return Measurement( ScalarTraits<magnitudeType>::nan(), ScalarTraits<magnitudeType>::nan() ); }
  static inline bool isnaninf(Measurement a){ return ScalarTraits<magnitudeType>::isnaninf(a.getValue()) || ScalarTraits<magnitudeType>::isnaninf(a.getUncertainty()); }
  static inline void seedrandom(unsigned int s) { ScalarTraits<magnitudeType>::seedrandom(s); }
  static inline Measurement random() { return Measurement( ScalarTraits<magnitudeType>::random(), 0.0 ); }
  static inline std::string name() { return std::string("Measurement<")+std::string(ScalarTraits<magnitudeType>::name())+std::string(">"); }
  static inline Measurement squareroot(Measurement a) { return Utility::sqrt(a); }
  static inline Measurement pow(Measurement a, Measurement b) { return Utility::pow( a, b.getValue() ); }

};

} // end Teuchos namespace

// Register the Measurement class with boost typeof for auto-like type
// deduction when used with the boost::units library
#if BOOST_UNITS_HAS_BOOST_TYPEOF

BOOST_TYPEOF_REGISTER_TEMPLATE(Utility::Measurement, 1)

#endif // end BOOST_UNITS_HAS_BOOST_TYPEOF

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_Measurement_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_MEASUREMENT_HPP

//---------------------------------------------------------------------------//
// end Utility_Measurement.hpp
//---------------------------------------------------------------------------//
