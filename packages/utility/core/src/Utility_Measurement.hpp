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

// FRENSIE Includes
#include "Utility_QuantityTraits.hpp"
#include "Utility_OStreamableObject.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

/*! The measurement class
 *
 * This class wraps is meant to be used as any typical scalar type
 * (e.g. double). It is designed to keep track of and propagate the
 * uncertainty of a value (like one would with a measured quantity).
 */
template<typename T>
class Measurement : public OStreamableObject
{

private:

  // The quantity traits typedef
  typedef QuantityTraits<T> QT;

public:

  //! The typedef for this type
  typedef Measurement<T> ThisType;

  //! The typedef for the value type
  typedef T ValueType;

  //! Constructor
  Measurement( const ValueType& value = QT::zero(),
	       const ValueType& uncertainty = QT::zero() );

  //! Copy constructor
  Measurement( const ThisType& other_measurement );

  //! Destructor
  ~Measurement()
  { /* ... */ }

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

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
inline Measurement<decltype(Utility::sqrt(T()))> sqrt( const Measurement<T>& x )
{
  // Make sure the measurement is valid
  testPrecondition( x.getValue() >= 0.0 );

  const auto new_value = Utilty::sqrt( x.getValue() );

  const auto propagated_uncertainty = 0.5*new_value*
    (x.getUncertainty()/x.getValue());    

  // Make sure reasonable values have been calculated
  testPostcondition( !QuantityTraits<decltype(new_value)>::isnaninf( new_value ) );
  testPostcondition( !QuantityTraits<decltype(new_value)>::isnaninf(
						    propagated_uncertainty ) );

  return Measurement<decltype(new_value)>( new_value, propagated_uncertainty );
}

//! Overload of rpow for a measurement
template<boost::units::integer_type N,
	 boost::units::integer_type D,
	 typename Quantity>
inline typename Measurement<decltype(Utility::rpow<N,D>(Quantity()))>
rpow( const Measurement<Quantity>& x )
{
  const auto new_value = Utility::rpow<N,D>( x.getValue() );

  const auto propagated_uncertainty =
    Utility::abs((N/D)*new_value*(x.getUncertainty()/x.getValue()));

  return Measurement<decltype(new_value)>( new_value, propagated_uncertainty );
}

} // end Utility namespace

namespace std{

//! Overload of pow for a measurement
template<typename T, typename ExponentType>
inline typename std::enable_if<std::is_arithmetic<T>::value,Utility::Measurement<T> >::type
pow( const Utility::Measurement<T>& x,
     const ExponentType exponent )
{
  const T new_value = std::pow( x.getValue(), exponent );

  const T propagated_uncertainty = fabs(exponent*(new_value/x.getValue()))*
    x.getUncertainty();

  // Make sure reasonable values have been calculated
  testPostcondition( !Utility::QuantityTraits<T>::isnaninf( new_value ) );
  testPostcondition( !Utility::QuantityTraits<T>::isnaninf(
						    propagated_uncertainty ) );
  testPostcondition( propagated_uncertainty >= 0.0 );

  return Utility::Measurement<T>( new_value, propagated_uncertainty );
}

} // end std namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_Measurement_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_MEASUREMENT_HPP

//---------------------------------------------------------------------------//
// end Utility_Measurement.hpp
//---------------------------------------------------------------------------//
