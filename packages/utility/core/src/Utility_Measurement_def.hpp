//---------------------------------------------------------------------------//
//!
//! \file   Utility_Measurement_def.hpp
//! \author Alex Robinson
//! \brief  The measurement class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MEASUREMENT_DEF_HPP
#define UTILITY_MEASUREMENT_DEF_HPP

// Std Lib Includes
#include <cmath>

// Boost Includes
#include <boost/io/ios_state.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
template<typename T>
Measurement<T>::Measurement( const Measurement<T>::ValueType& value, 
			     const Measurement<T>::ValueType& uncertainty )
  : PrintableObject( "", false ),
    d_value( value ),
    d_uncertainty( uncertainty )
{ 
  // Make sure the value is valid
  testPrecondition( !ST::isnaninf( value ) );
  // Make sure the uncertainty is valid
  testPrecondition( !ST::isnaninf( uncertainty ) );
  testPrecondition( uncertainty >= 0.0 );
}

// Copy constructor
template<typename T>
Measurement<T>::Measurement( const Measurement<T>& other_measurement )
  : PrintableObject( "", false ),
    d_value( other_measurement.d_value ),
    d_uncertainty( other_measurement.d_uncertainty )
{
  // Make sure the other measurement is valid
  testPrecondition( !ST::isnaninf( other_measurement.d_value ) );
  testPrecondition( !ST::isnaninf( other_measurement.d_uncertainty ) );
  testPrecondition( other_measurement.d_uncertainty >= 0.0 );
}

// Print method
template<typename T>
inline void Measurement<T>::print( std::ostream& os ) const
{
  boost::io::ios_precision_saver preision_saver(os);
  boost::io::ios_flags_saver flags_saver(os);

  os << d_value << "(+/-" << d_uncertainty << ")";
}

// Return the value of the measurement
template<typename T>
inline const typename Measurement<T>::ValueType& 
Measurement<T>::getValue() const
{
  return d_value;
}

// Return the uncertainty of the measurement
template<typename T>
inline const typename Measurement<T>::ValueType& 
Measurement<T>::getUncertainty() const
{
  return d_uncertainty;
}

// Return the relative uncertainty of the measurement
template<typename T>
inline const typename Measurement<T>::ValueType
Measurement<T>::getRelativeUncertainty() const
{
  if( d_value != 0.0 )
    return d_uncertainty/d_value;
  else
    return 0.0;
}

// Return the lower bound of the measurement
template<typename T>
inline const typename Measurement<T>::ValueType 
Measurement<T>::getLowerBound() const
{
  return d_value - d_uncertainty;
}

// Return the upper bound of the measurement
template<typename T>
inline const typename Measurement<T>::ValueType
Measurement<T>::getUpperBound() const
{
  return d_value + d_uncertainty;
}

// Value access operator
template<typename T>
inline Measurement<T>::operator Measurement<T>::ValueType() const
{
  return d_value;
}

// In-place addition operator
template<typename T>
inline Measurement<T>& Measurement<T>::operator+=( 
				       const Measurement<T>::ValueType& value )
{
  // Make sure the value is valid
  testPrecondition( !ST::isnaninf( value ) );
  
  d_value += value;

  return *this;
}

// In-place addition operator
template<typename T>
inline Measurement<T>& Measurement<T>::operator+=(
				      const Measurement<T>& other_measurement )
{
  // Make sure the other measurement is valid
  testPrecondition( !ST::isnaninf( other_measurement.d_value ) );
  testPrecondition( !ST::isnaninf( other_measurement.d_uncertainty ) );
  testPrecondition( other_measurement.d_uncertainty >= 0.0 );
  
  d_value += other_measurement.d_value;

  // Propagate the uncertainty of the measurements
  d_uncertainty = std::sqrt( d_uncertainty*d_uncertainty +
			     other_measurement.d_uncertainty*
			     other_measurement.d_uncertainty );

  return *this;
}

// In-place subtraction operator
template<typename T>
inline Measurement<T>& Measurement<T>::operator-=( 
				       const Measurement<T>::ValueType& value )
{
  // Make sure the value is valid
  testPrecondition( !ST::isnaninf( value ) );
  
  d_value -= value;

  return *this;
}

// In-place subtraction operator
template<typename T>
inline Measurement<T>& Measurement<T>::operator-=( 
				      const Measurement<T>& other_measurement )
{
  // Make sure the other measurement is valid
  testPrecondition( !ST::isnaninf( other_measurement.d_value ) );
  testPrecondition( !ST::isnaninf( other_measurement.d_uncertainty ) );
  testPrecondition( other_measurement.d_uncertainty >= 0.0 );
  
  d_value -= other_measurement.d_value;

  // Propagate the uncertainty of the measurements
  d_uncertainty = std::sqrt( d_uncertainty*d_uncertainty +
			     other_measurement.d_uncertainty*
			     other_measurement.d_uncertainty );

  return *this;
}

// In-place multiplication operator
template<typename T>
inline Measurement<T>& Measurement<T>::operator*=( 
				       const Measurement<T>::ValueType& value )
{
  // Make sure the value is valid
  testPrecondition( !ST::isnaninf( value ) );
  
  d_value *= value;

  return *this;
}

// In-place multiplication operator
template<typename T>
inline Measurement<T>& Measurement<T>::operator*=( 
				      const Measurement<T>& other_measurement )
{
  // Make sure the other measurement is valid
  testPrecondition( !ST::isnaninf( other_measurement.d_value ) );
  testPrecondition( !ST::isnaninf( other_measurement.d_uncertainty ) );
  testPrecondition( other_measurement.d_uncertainty >= 0.0 );
  
  d_value *= other_measurement.d_value;

  // Propagate the uncertainty of the measurements
  d_uncertainty = 
    std::sqrt( d_uncertainty*d_uncertainty*
	       other_measurement.d_value*other_measurement.d_value +
	       other_measurement.d_uncertainty*other_measurement.d_uncertainty*
	       d_value*d_value );

  return *this;
}

// In-place division operator
template<typename T>
inline Measurement<T>& Measurement<T>::operator/=( 
				       const Measurement<T>::ValueType& value )
{
  // Make sure the value is valid
  testPrecondition( !ST::isnaninf( value ) );
  testPrecondition( value > 0.0 );
  
  d_value /= value;

  return *this;
}

// In-place division operator
template<typename T>
inline Measurement<T>& Measurement<T>::operator/=( 
				      const Measurement<T>& other_measurement )
{
  // Make sure the other measurement is valid
  testPrecondition( !ST::isnaninf( other_measurement.d_value ) );
  testPrecondition( !ST::isnaninf( other_measurement.d_uncertainty ) );
  testPrecondition( other_measurement.d_value > 0.0 );
  testPrecondition( other_measurement.d_uncertainty >= 0.0 );
  
  d_value /= other_measurement.d_value;
  
  double other_value_sqr = other_measurement.d_value*other_measurement.d_value;

  double term_1 = d_uncertainty*d_uncertainty/other_value_sqr;
  
  double term_2 = 
    other_measurement.d_uncertainty*other_measurement.d_uncertainty*
    d_value*d_value/(other_value_sqr*other_value_sqr);
    

  // Propagate the uncertainty of the measurements
  d_uncertainty = std::sqrt( term_1 + term_2 );

  return *this;
}

} // end Utility namespace

#endif // end UTILITY_MEASUREMENT_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_Measurement_def.hpp
//---------------------------------------------------------------------------//
