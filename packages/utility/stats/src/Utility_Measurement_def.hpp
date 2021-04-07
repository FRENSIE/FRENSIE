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
#include <functional>

// Boost Includes
#include <boost/io/ios_state.hpp>

namespace Utility{

// Constructor
template<typename T>
Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type>::Measurement(
                                                 const ValueType& value,
                                                 const ValueType& uncertainty )
  : d_value( value ),
    d_uncertainty( uncertainty )
{
  // Make sure the value is valid
  testPrecondition( !Utility::isnaninf( value ) );
  // Make sure the uncertainty is valid
  testPrecondition( !Utility::isnaninf( uncertainty ) );
  testPrecondition( uncertainty >= 0.0 );
}

// Copy constructor
template<typename T>
Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type>::Measurement( const Measurement<T>& other_measurement )
  : d_value( other_measurement.d_value ),
    d_uncertainty( other_measurement.d_uncertainty )
{
  // Make sure the other measurement is valid
  testPrecondition( !Utility::isnaninf( other_measurement.d_value ) );
  testPrecondition( !Utility::isnaninf( other_measurement.d_uncertainty ) );
  testPrecondition( other_measurement.d_uncertainty >= 0.0 );
}

// Method for placing the object in an output stream
template<typename T>
inline void Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type>::toStream( std::ostream& os ) const
{
  os << Utility::toString( d_value ) << " +/- "
     << Utility::toString( d_uncertainty );
}

// Return the value of the measurement
template<typename T>
inline auto Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type>::getValue() const -> const ValueType&
{
  return d_value;
}

// Return the uncertainty of the measurement
template<typename T>
inline auto Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type>::getUncertainty() const -> const ValueType&
{
  return d_uncertainty;
}

// Return the relative uncertainty of the measurement
template<typename T>
inline auto Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type>::getRelativeUncertainty() const -> ValueType
{
  if( d_value != 0.0 )
    return d_uncertainty/fabs(d_value);
  else
    return 0.0;
}

// Return the lower bound of the measurement
template<typename T>
inline auto Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type>::getLowerBound() const -> ValueType
{
  return d_value - d_uncertainty;
}

// Return the upper bound of the measurement
template<typename T>
inline auto Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type>::getUpperBound() const -> ValueType
{
  return d_value + d_uncertainty;
}

// In-place addition operator
template<typename T>
inline Measurement<T>& Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type>::operator+=( const ValueType& value )
{
  // Make sure the value is valid
  testPrecondition( !Utility::isnaninf( value ) );

  d_value += value;

  return *this;
}

// In-place addition operator
template<typename T>
inline Measurement<T>& Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type>::operator+=( const Measurement<T>& other_measurement )
{
  // Make sure the other measurement is valid
  testPrecondition( !Utility::isnaninf( other_measurement.d_value ) );
  testPrecondition( !Utility::isnaninf( other_measurement.d_uncertainty ) );
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
inline Measurement<T>& Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type>::operator-=( const ValueType& value )
{
  // Make sure the value is valid
  testPrecondition( !Utility::isnaninf( value ) );

  d_value -= value;

  return *this;
}

// In-place subtraction operator
template<typename T>
inline Measurement<T>& Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type>::operator-=( const Measurement<T>& other_measurement )
{
  // Make sure the other measurement is valid
  testPrecondition( !Utility::isnaninf( other_measurement.d_value ) );
  testPrecondition( !Utility::isnaninf( other_measurement.d_uncertainty ) );
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
inline Measurement<T>& Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type>::operator*=( const ValueType& value )
{
  // Make sure the value is valid
  testPrecondition( !Utility::isnaninf( value ) );

  d_value *= value;

  d_uncertainty *= fabs( value );

  return *this;
}

// In-place multiplication operator
template<typename T>
inline Measurement<T>& Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type>::operator*=( const Measurement<T>& other_measurement )
{
  // Make sure the other measurement is valid
  testPrecondition( !Utility::isnaninf( other_measurement.d_value ) );
  testPrecondition( !Utility::isnaninf( other_measurement.d_uncertainty ) );

  // Propagate the uncertainty of the measurements
  d_uncertainty = std::sqrt( d_uncertainty*d_uncertainty*
	       other_measurement.d_value*other_measurement.d_value +
	       other_measurement.d_uncertainty*other_measurement.d_uncertainty*
	       d_value*d_value );

  d_value *= other_measurement.d_value;

  return *this;
}

// In-place division operator
template<typename T>
inline Measurement<T>& Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type>::operator/=( const ValueType& value )
{
  // Make sure the value is valid
  testPrecondition( !Utility::isnaninf( value ) );
  testPrecondition( value != 0.0 );

  d_value /= value;

  d_uncertainty /= fabs( value );

  return *this;
}

// In-place division operator
template<typename T>
inline Measurement<T>& Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type>::operator/=( const Measurement<T>& other_measurement )
{
  // Make sure the other measurement is valid
  testPrecondition( !Utility::isnaninf( other_measurement.d_value ) );
  testPrecondition( !Utility::isnaninf( other_measurement.d_uncertainty ) );
  testPrecondition( other_measurement.d_value != 0.0 );
  testPrecondition( other_measurement.d_uncertainty >= 0.0 );

  double other_value_sqr = other_measurement.d_value*other_measurement.d_value;

  double term_1 = d_uncertainty*d_uncertainty/other_value_sqr;

  double term_2 =
    other_measurement.d_uncertainty*other_measurement.d_uncertainty*
    d_value*d_value/(other_value_sqr*other_value_sqr);


  // Propagate the uncertainty of the measurements
  d_uncertainty = std::sqrt( term_1 + term_2 );

  d_value /= other_measurement.d_value;

  return *this;
}

namespace Details{

//! Calculate the propagated uncertainty of a measurement to a real power
template<typename T1, typename T2>
inline T1 calculatePropagatedUncertaintyFromRealPowerOp(
                                                const T1 value,
                                                const T1 value_to_exponent,
                                                const T1 uncertainty,
                                                const T2 exponent )
{ return std::fabs(exponent*value_to_exponent*(uncertainty/value)); }

//! The pow method implementation
template<typename T, typename ExponentType, typename BasePowMethod>
inline Utility::Measurement<T> powImpl( const Utility::Measurement<T>& x,
                                       const ExponentType exponent,
                                       BasePowMethod basePow )
{
  if( x.getValue() != Utility::QuantityTraits<T>::zero() )
  {
    const T new_value = basePow( x.getValue() );

    const T propagated_uncertainty =
      Utility::Details::calculatePropagatedUncertaintyFromRealPowerOp(
                                                            x.getValue(),
                                                            new_value,
                                                            x.getUncertainty(),
                                                            exponent );
    
    return Utility::Measurement<T>( new_value, propagated_uncertainty );
  }
  else if( x.getValue() == Utility::QuantityTraits<T>::zero() &&
           x.getUncertainty() > Utility::QuantityTraits<T>::zero() )
  {
    return Utility::Measurement<T>( Utility::QuantityTraits<T>::zero(),
                                    Utility::QuantityTraits<T>::inf() );
  }
  // quantity.getValue() == 0, quantity.getUncertainty() == 0
  else
  {
    return Utility::Measurement<T>( Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::zero() );
  }
}
  
} // end Details namespace

} // end Utility namespace

namespace std{

// Overload of sqrt for a measurement
template<typename T>
inline Utility::Measurement<T> sqrt( const Utility::Measurement<T>& x )
{
  if( x.getValue() > Utility::QuantityTraits<T>::zero() )
  {
    const T new_value = std::sqrt( x.getValue() );

    const T propagated_uncertainty =
      Utility::Details::calculatePropagatedUncertaintyFromRealPowerOp(
                                                            x.getValue(),
                                                            new_value,
                                                            x.getUncertainty(),
                                                            0.5 );
    return Utility::Measurement<T>( new_value, propagated_uncertainty );
  }
  else if( x.getValue() == Utility::QuantityTraits<T>::zero() &&
           x.getUncertainty() > Utility::QuantityTraits<T>::zero() )
  {
    return Utility::Measurement<T>( Utility::QuantityTraits<T>::zero(),
                                    Utility::QuantityTraits<T>::inf() );
  }
  else if( x.getValue() == Utility::QuantityTraits<T>::zero() &&
           x.getUncertainty() == Utility::QuantityTraits<T>::zero() )
  {
    return Utility::Measurement<T>( Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::zero() );
  }
  else
  {
    return Utility::Measurement<T>( Utility::QuantityTraits<T>::nan(), Utility::QuantityTraits<T>::nan() );
  }
}

// Overload of cbrt for a measurement
template<typename T>
inline Utility::Measurement<T> cbrt( const Utility::Measurement<T>& x )
{
  if( x.getValue() != Utility::QuantityTraits<T>::zero() )
  {
    const T new_value = std::cbrt( x.getValue() );

    const T propagated_uncertainty =
      Utility::Details::calculatePropagatedUncertaintyFromRealPowerOp(
                                                            x.getValue(),
                                                            new_value,
                                                            x.getUncertainty(),
                                                            1.0/3 );
    return Utility::Measurement<T>( new_value, propagated_uncertainty );
  }
  else if( x.getValue() == Utility::QuantityTraits<T>::zero() &&
           x.getUncertainty() > Utility::QuantityTraits<T>::zero() )
  {
    return Utility::Measurement<T>( Utility::QuantityTraits<T>::zero(),
                                    Utility::QuantityTraits<T>::inf() );
  }
  // quantity.getValue() == 0, quantity.getUncertainty() == 0
  else
  {
    return Utility::Measurement<T>( Utility::QuantityTraits<T>::zero(), Utility::QuantityTraits<T>::zero() );
  }
}

// Overload of pow for a measurement
template<typename T, typename ExponentType>
inline Utility::Measurement<T> pow( const Utility::Measurement<T>& x,
                                    const ExponentType exponent )
{
  return Utility::Details::powImpl( x, exponent, std::bind<T>( static_cast<T (*)(T,T)>(&std::pow<T>), std::placeholders::_1, static_cast<T>(exponent) ) );
}

} // end std namespace

namespace Utility{

// Partial specialization of Utility::QuantityTraits for Utility::Measurement
template<typename T>
struct QuantityTraits<Measurement<T>,typename std::enable_if<std::is_floating_point<T>::value>::type>
{
private:

  // The quantity traits for the raw type
  typedef QuantityTraits<T> RawQuantityTraits;

  // These quantity traits
  typedef QuantityTraits<Measurement<T>,typename std::enable_if<std::is_floating_point<T>::value>::type> ThisType;

public:
  
  //! The unit type
  typedef void UnitType;

  //! The raw quantity type
  typedef Measurement<T> RawType;

  //! The raw floating-point quantity type
  typedef Measurement<T> RawFloatingPointType;

  //! The real raw floating-point quantity type
  typedef Measurement<T> RealRawFloatingPointType;

  //! The quantity type
  typedef Measurement<T> QuantityType;

  //! The floating-point quantity type
  typedef Measurement<T> FloatingPointQuantityType;

  //! The real floating-point quantity type
  typedef Measurement<T> RealFloatingPointQuantityType;

  //! The quantity raised to power N/D type
  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetQuantityToPowerType
  {
    typedef QuantityType type;
    typedef FloatingPointQuantityType AsFloatingPointType;
  };

  //! Used to check if the traits class for quantity type is specialized
  typedef typename RawQuantityTraits::is_specialized is_specialized;

  //! Used to check if the quantity is signed
  typedef typename RawQuantityTraits::is_signed is_signed;

  //! Used to check if the quantity is an integer type
  typedef typename RawQuantityTraits::is_integer is_integer;

  //! Used to check if the quantity is complex
  typedef typename RawQuantityTraits::is_complex is_complex;

  //! Used to check if the quantity uses exact representations
  typedef typename RawQuantityTraits::is_exact is_exact;

  //! Used to check if a quantity adheres to IEC-559/IEEE-754 standard
  typedef typename RawQuantityTraits::is_iec559 is_iec559;

  //! Used to check if the set of values represented by the quantity is finite
  typedef typename RawQuantityTraits::is_bounded is_bounded;

  //! Used to check if the quantity is modulo
  typedef typename RawQuantityTraits::is_modulo is_modulo;

  //! Used to check if the quantity has a representation for positive infinity
  typedef typename RawQuantityTraits::has_infinity has_infinity;

  //! Used to check if the quantity has a representation for quiet nan
  typedef typename RawQuantityTraits::has_quiet_nan has_quiet_nan;

  //! Used to check if the quantity has a representation for signaling nan
  typedef typename RawQuantityTraits::has_signaling_nan has_signaling_nan;

  //! Used to check if the quantity allows denormalized values
  typedef typename RawQuantityTraits::has_denorm has_denorm;

  //! Used to check if a loss of accuracy is detected as a denormalization loss instead of an inexact result
  typedef typename RawQuantityTraits::has_denorm_loss has_denorm_loss;

  //! Used to check if trapping is implemented for the quantity
  typedef typename RawQuantityTraits::traps traps;

  //! Used to check if tinyness is implemented before rounding
  typedef typename RawQuantityTraits::tinyness_before tinyness_before;

  //! Used to check the rounding style of floating-point quantities 
  typedef typename RawQuantityTraits::round_style round_style;

    //! The number of non-sign bits
  typedef typename RawQuantityTraits::digits digits;

  //! The number of digits (in decimal base) that can be represented
  typedef typename RawQuantityTraits::digits10 digits10;

  //! The number of digits (in decimal base) required to ensure that values that differ are always differentiated
  typedef typename RawQuantityTraits::max_digits10 max_digits10;

  //! Base of the representation
  typedef typename RawQuantityTraits::radix radix;

  //! Min negative integer value such that radix raised to (this-1) generates a normalized floating-point quantity 
  typedef typename RawQuantityTraits::min_exponent min_exponent;

  //! Min negative integer value such that 10 raised to that power generates a normalized floating-point quantity 
  typedef typename RawQuantityTraits::min_exponent10 min_exponent10;

  //! One more than the largest integer power of the radix that is a valid finite floating-point value
  typedef typename RawQuantityTraits::max_exponent max_exponent;

  //! Max integer power of 10 that is a valid finite floating-point value
  typedef typename RawQuantityTraits::max_exponent10 max_exponent10;

  //! Get the zero quantity
  static inline QuantityType zero() noexcept
  { return QuantityType(RawQuantityTraits::zero(), RawQuantityTraits::zero()); }

  //! Get the one quantity
  static inline QuantityType one() noexcept
  { return QuantityType(RawQuantityTraits::one(), RawQuantityTraits::zero()); }

  //! Get the min quantity
  static inline QuantityType min() noexcept
  { return QuantityType(RawQuantityTraits::min(), RawQuantityTraits::zero()); }

  //! Get the min positive denormalized value
  static inline QuantityType denormMin() noexcept
  { return QuantityType(RawQuantityTraits::denormMin(), RawQuantityTraits::zero()); }

  //! Get the max quantity
  static inline QuantityType max() noexcept
  { return QuantityType(RawQuantityTraits::max(), RawQuantityTraits::zero()); }

  //! Get the lowest quantity
  static inline QuantityType lowest() noexcept
  { return QuantityType(RawQuantityTraits::lowest(), RawQuantityTraits::zero()); }

  //! Get the machine epsilon (only defined for floating-point types)
  static inline QuantityType epsilon() noexcept
  { return QuantityType(RawQuantityTraits::epsilon(), RawQuantityTraits::zero()); }

  //! Get the maximum rounding error (only defined for floating-point types)
  static inline QuantityType roundError() noexcept
  { return QuantityType(RawQuantityTraits::roundError(), RawQuantityTraits::zero()); }

  //! Get the inf quantity (only defined for floating-point types)
  static inline QuantityType inf() noexcept
  { return QuantityType(RawQuantityTraits::inf(), RawQuantityTraits::zero()); }

  //! Get the quiet nan quantity (only defined for floating-point types)
  static inline QuantityType nan() noexcept
  { return QuantityType(RawQuantityTraits::nan(), RawQuantityTraits::zero()); }

  //! Get the signaling nan quantity (only defined for floating-point types)
  static inline QuantityType signalingNan() noexcept
  { return QuantityType(RawQuantityTraits::signalingNan(), RawQuantityTraits::zero()); }

  //! Get the absolute value of a quantity
  static inline RealFloatingPointQuantityType abs( const QuantityType& a )
  { return RealFloatingPointQuantityType(RawQuantityTraits::abs(a.getValue()), a.getUncertainty()); }

  //! Get the conjugate of a quantity
  static inline FloatingPointQuantityType conj( const QuantityType& a )
  { return a; }

  //! Get the real part of the quantity
  static inline RealFloatingPointQuantityType real( const QuantityType& a )
  { return a; }

  //! Get the imaginary part of the quantity
  static inline RealFloatingPointQuantityType imag( const QuantityType& a )
  { return RealFloatingPointQuantityType(RawQuantityTraits::zero(),RawQuantityTraits::zero()); }

  //! Test if the quantity is a nan or inf 
  static inline bool isnaninf( const QuantityType& a )
  {
    if( RawQuantityTraits::isnaninf( a.getValue() ) ||
        RawQuantityTraits::isnaninf( a.getUncertainty() ) )
      return true;

    return false;
  }

  //! Take the square root of a quantity (only one root will be calculated)
  static inline typename GetQuantityToPowerType<1,2>::AsFloatingPointType sqrt( const QuantityType& quantity )
  { return std::sqrt( quantity ); }

  //! Take the cube root of a quantity (only one root will be calculated)
  static inline typename GetQuantityToPowerType<1,3>::AsFloatingPointType cbrt( const QuantityType& quantity )
  { return std::cbrt( quantity ); }

  //! Take a quantity to the desired rational power
  template<boost::units::integer_type N, boost::units::integer_type D>
  static typename GetQuantityToPowerType<N,D>::AsFloatingPointType rpow( const QuantityType& quantity )
  {
    return Details::powImpl( quantity, static_cast<double>(N)/D, &RawQuantityTraits::template rpow<N,D> );
  }

  //! Initialize a quantity (potentially dangerous!)
  static inline QuantityType initializeQuantity( const RawType& raw_quantity ) noexcept
  { return raw_quantity; }

  //! Get the raw value of a quantity
  static inline const RawType& getRawQuantity( const QuantityType& quantity ) noexcept
  { return quantity; }

  //! Set the value of a quantity (potentially dangerous!)
  static inline void setQuantity( QuantityType& quantity,
				  const RawType& raw_quantity ) noexcept
  { quantity = raw_quantity; }
};

// Partial specialization of Utility::QuantityTraits for
// boost::units::quantity<Unit,Utility::Measurement> types
template<typename Unit, typename T>
struct QuantityTraits<boost::units::quantity<Unit,Measurement<T> >,typename std::enable_if<std::is_floating_point<T>::value>::type>
{
  // The quantity traits for the raw type
  typedef QuantityTraits<Measurement<T> > RawQuantityTraits;

  // These quantity traits
  typedef QuantityTraits<boost::units::quantity<Unit,Measurement<T> >,typename std::enable_if<std::is_floating_point<T>::value>::type> ThisType;

public:
  
  //! The unit type
  typedef Unit UnitType;

  //! The raw quantity type
  typedef Measurement<T> RawType;

  //! The raw floating-point quantity type
  typedef Measurement<T> RawFloatingPointType;

  //! The real raw floating-point quantity type
  typedef Measurement<T> RealRawFloatingPointType;

  //! The quantity type
  typedef boost::units::quantity<Unit,Measurement<T> > QuantityType;

  //! The floating-point quantity type
  typedef boost::units::quantity<Unit,Measurement<T> > FloatingPointQuantityType;

  //! The real floating-point quantity type
  typedef boost::units::quantity<Unit,Measurement<T> > RealFloatingPointQuantityType;

  //! The quantity raised to power N/D type
  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetQuantityToPowerType
  {
    typedef typename Details::QuantityToPowerTypeHelper<N,D,QuantityType>::QuantityToRpowType type;
    typedef typename Details::QuantityToPowerTypeHelper<N,D,FloatingPointQuantityType>::QuantityToRpowType AsFloatingPointType;
  };

  //! Used to check if the traits class for quantity type is specialized
  typedef typename RawQuantityTraits::is_specialized is_specialized;

  //! Used to check if the quantity is signed
  typedef typename RawQuantityTraits::is_signed is_signed;

  //! Used to check if the quantity is an integer type
  typedef typename RawQuantityTraits::is_integer is_integer;

  //! Used to check if the quantity is complex
  typedef typename RawQuantityTraits::is_complex is_complex;

  //! Used to check if the quantity uses exact representations
  typedef typename RawQuantityTraits::is_exact is_exact;

  //! Used to check if a quantity adheres to IEC-559/IEEE-754 standard
  typedef typename RawQuantityTraits::is_iec559 is_iec559;

  //! Used to check if the set of values represented by the quantity is finite
  typedef typename RawQuantityTraits::is_bounded is_bounded;

  //! Used to check if the quantity is modulo
  typedef typename RawQuantityTraits::is_modulo is_modulo;

  //! Used to check if the quantity has a representation for positive infinity
  typedef typename RawQuantityTraits::has_infinity has_infinity;

  //! Used to check if the quantity has a representation for quiet nan
  typedef typename RawQuantityTraits::has_quiet_nan has_quiet_nan;

  //! Used to check if the quantity has a representation for signaling nan
  typedef typename RawQuantityTraits::has_signaling_nan has_signaling_nan;

  //! Used to check if the quantity allows denormalized values
  typedef typename RawQuantityTraits::has_denorm has_denorm;

  //! Used to check if a loss of accuracy is detected as a denormalization loss instead of an inexact result
  typedef typename RawQuantityTraits::has_denorm_loss has_denorm_loss;

  //! Used to check if trapping is implemented for the quantity
  typedef typename RawQuantityTraits::traps traps;

  //! Used to check if tinyness is implemented before rounding
  typedef typename RawQuantityTraits::tinyness_before tinyness_before;

  //! Used to check the rounding style of floating-point quantities 
  typedef typename RawQuantityTraits::round_style round_style;

    //! The number of non-sign bits
  typedef typename RawQuantityTraits::digits digits;

  //! The number of digits (in decimal base) that can be represented
  typedef typename RawQuantityTraits::digits10 digits10;

  //! The number of digits (in decimal base) required to ensure that values that differ are always differentiated
  typedef typename RawQuantityTraits::max_digits10 max_digits10;

  //! Base of the representation
  typedef typename RawQuantityTraits::radix radix;

  //! Min negative integer value such that radix raised to (this-1) generates a normalized floating-point quantity 
  typedef typename RawQuantityTraits::min_exponent min_exponent;

  //! Min negative integer value such that 10 raised to that power generates a normalized floating-point quantity 
  typedef typename RawQuantityTraits::min_exponent10 min_exponent10;

  //! One more than the largest integer power of the radix that is a valid finite floating-point value
  typedef typename RawQuantityTraits::max_exponent max_exponent;

  //! Max integer power of 10 that is a valid finite floating-point value
  typedef typename RawQuantityTraits::max_exponent10 max_exponent10;

  //! Get the zero quantity
  static inline QuantityType zero() noexcept
  { return QuantityType::from_value( RawQuantityTraits::zero() ); }

  //! Get the one quantity
  static inline QuantityType one() noexcept
  { return QuantityType::from_value( RawQuantityTraits::one() ); }

  //! Get the min quantity
  static inline QuantityType min() noexcept
  { return QuantityType::from_value( RawQuantityTraits::min() ); }

  //! Get the min positive denormalized value
  static inline QuantityType denormMin() noexcept
  { return QuantityType::from_value( RawQuantityTraits::denormMin() ); }

  //! Get the max quantity
  static inline QuantityType max() noexcept
  { return QuantityType::from_value( RawQuantityTraits::max() ); }

  //! Get the lowest quantity
  static inline QuantityType lowest() noexcept
  { return QuantityType::from_value( RawQuantityTraits::lowest() ); }

  //! Get the machine epsilon (only defined for floating-point types)
  static inline QuantityType epsilon() noexcept
  { return QuantityType::from_value( RawQuantityTraits::epsilon() ); }

  //! Get the maximum rounding error (only defined for floating-point types)
  static inline QuantityType roundError() noexcept
  { return QuantityType::from_value( RawQuantityTraits::roundError() ); }

  //! Get the inf quantity (only defined for floating-point types)
  static inline QuantityType inf() noexcept
  { return QuantityType::from_value( RawQuantityTraits::inf() ); }

  //! Get the quiet nan quantity (only defined for floating-point types)
  static inline QuantityType nan() noexcept
  { return QuantityType::from_value( RawQuantityTraits::nan() ); }

  //! Get the signaling nan quantity (only defined for floating-point types)
  static inline QuantityType signalingNan() noexcept
  { return QuantityType::from_value( RawQuantityTraits::signalingNan() ); }

  //! Get the absolute value of a quantity
  static inline RealFloatingPointQuantityType abs( const QuantityType& a )
  { return RealFloatingPointQuantityType::from_value( RawQuantityTraits::abs(a.value()) ); }

  //! Get the conjugate of a quantity
  static inline FloatingPointQuantityType conj( const QuantityType& a )
  { return FloatingPointQuantityType::from_value( RawQuantityTraits::conj(a.value()) ); }

  //! Get the real part of the quantity
  static inline RealFloatingPointQuantityType real( const QuantityType& a )
  { return RealFloatingPointQuantityType::from_value( RawQuantityTraits::real(a.value()) ); }

  //! Get the imaginary part of the quantity
  static inline RealFloatingPointQuantityType imag( const QuantityType& a )
  { return RealFloatingPointQuantityType::from_value( RawQuantityTraits::imag(a.value()) ); }

  //! Test if the quantity is a nan or inf 
  static inline bool isnaninf( const QuantityType& a )
  { return RawQuantityTraits::isnaninf(a.value()); }

  //! Take the square root of a quantity (only one root will be calculated)
  static inline typename GetQuantityToPowerType<1,2>::AsFloatingPointType sqrt( const QuantityType& quantity )
  { return GetQuantityToPowerType<1,2>::AsFloatingPointType::from_value( RawQuantityTraits::sqrt( quantity.value() ) ); }

  //! Take the cube root of a quantity (only one root will be calculated)
  static inline typename GetQuantityToPowerType<1,3>::AsFloatingPointType cbrt( const QuantityType& quantity )
  { return GetQuantityToPowerType<1,3>::AsFloatingPointType::from_value( RawQuantityTraits::cbrt( quantity.value() ) ); }

  //! Take a quantity to the desired rational power
  template<boost::units::integer_type N, boost::units::integer_type D>
  static typename GetQuantityToPowerType<N,D>::AsFloatingPointType rpow( const QuantityType& quantity )
  { return GetQuantityToPowerType<N,D>::AsFloatingPointType::from_value( RawQuantityTraits::template rpow<N,D>( quantity.value() ) ); }

  //! Initialize a quantity (potentially dangerous!)
  static inline QuantityType initializeQuantity( const RawType& raw_quantity ) noexcept
  { return QuantityType::from_value( raw_quantity ); }

  //! Get the raw value of a quantity
  static inline const RawType& getRawQuantity( const QuantityType& quantity ) noexcept
  { return quantity.value(); }

  //! Set the value of a quantity (potentially dangerous!)
  static inline void setQuantity( QuantityType& quantity,
				  const RawType& raw_quantity ) noexcept
  { quantity = QuantityType::from_value( raw_quantity ); }
};

} // end Utility namespace

#endif // end UTILITY_MEASUREMENT_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_Measurement_def.hpp
//---------------------------------------------------------------------------//
