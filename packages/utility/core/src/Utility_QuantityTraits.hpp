//---------------------------------------------------------------------------//
//!
//! \file   Utility_QuantityTraits.hpp
//! \author Alex Robinson
//! \brief  Quantity traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_QUANTITY_TRAITS_HPP
#define UTILITY_QUANTITY_TRAITS_HPP

// Std Lib Includes
#include <type_traits>
#include <cmath>
#include <complex>

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/cmath.hpp>
#include <boost/units/static_rational.hpp>
#include <boost/units/limits.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_QuantityTraitsDecl.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

namespace Details{

/*! The raw rational power helper
 * \ingroup quantity_traits
 */
template<boost::units::integer_type N,
         boost::units::integer_type D,
         typename T,
         typename Enabled = void>
struct RawRationalPowerHelper
{
  //! Calculate the value raised to the rational power N/D
  static inline T calculateRationalPower( const T& value )
  { return std::pow( value, static_cast<double>( N )/D ); }
};

/*! The partial specialization of the RawRationalPowerHelper for D==0
 *
 * The denominator of the rational power cannot be zero. Therefore, this
 * specialization is not defined to prevent compilation.
 * \ingroup quantity_traits
 */
template<boost::units::integer_type N, typename T>
struct RawRationalPowerHelper<N,0,T>;

/*! The partial specialization of the RawRationalPowerHelper for N==0, D!=0
 * \ingroup quantity_traits
 */
template<boost::units::integer_type D, typename T>
struct RawRationalPowerHelper<0,D,T, typename std::enable_if<D!=0>::type>
{
  //! Calculate the value raised to 0
  static inline T calculateRationalPower( const T& value )
  { return T(1); }
};

/*! The partial specialization of RawRationalPowerHelper for N==D, N!=0, D!=0
 * \ingroup quantity_traits
 */
template<boost::units::integer_type I, typename T>
struct RawRationalPowerHelper<I, I, T, typename std::enable_if<I!=0>::type>
{
  //! Calculate the value raised to the rational power N/D
  static inline T calculateRationalPower( const T& value )
  { return value; }
};

/*! The partial specialization of RawRationalPowerHelper for N>1, N%2==0, D==1
 *
 * When the rational power is a positive integer value we can use an efficient
 * recusive exponentiation algorithm which calculates the value raised to N in 
 * log(N) multiplications.
 * \ingroup quantity_traits
 */
template<boost::units::integer_type N, typename T>
struct RawRationalPowerHelper<N, 1, T, typename std::enable_if<(N>1 && N%2==0)>::type>
{
  //! Calculate the value raised to the integer power N
  static inline T calculateRationalPower( const T& value )
  {
    T tmp_value = RawRationalPowerHelper<N/2,1,T>::calculateRationalPower( value );
    return tmp_value*tmp_value;
  }
};

/*! The partial specialization of RawRationalPowerHelper for N>1, N%2==1, D==1
 *
 * When the rational power is a positive integer value we can use an efficient
 * recusive exponentiation algorithm which calculates the value raised to N in 
 * log(N) multiplications.
 * \ingroup quantity_traits
 */
template<boost::units::integer_type N, typename T>
struct RawRationalPowerHelper<N, 1, T, typename std::enable_if<(N>1 && N%2==1)>::type>
{
  //! Calculate the value raised to the integer power N
  static inline T calculateRationalPower( const T& value )
  {
    T tmp_value = RawRationalPowerHelper<N/2,1,T>::calculateRationalPower( value );
    return tmp_value*tmp_value*value;
  }
};

/*! The partial specialization of RawRationalPowerHelper for N>1,D>1,N>D,N%D==0
 * If N is an integer multiple of D, we will set N to N/D and D to 1 to 
 * take advantage of other partial specializations for D==1.
 * \ingroup quantity_traits
 */
template<boost::units::integer_type N,
         boost::units::integer_type D,
         typename T>
struct RawRationalPowerHelper<N, D, T, typename std::enable_if<(N>1 && D>1 && N>D && N%D==0)>::type> : public RawRationalPowerHelper<N/D,1,T>
{ /* ... */ };         

/*! The partial specialization of RawRationalPowerHelper for N==1, D==2
 *
 * The std::sqrt method will be used instead of std::pow.
 * \ingroup quantity_traits
 */
template<typename T>
struct RawRationalPowerHelper<1,2,T>
{
  //! Calculate the square root of the value
  static inline T calculateRationalPower( const T& value )
  { return std::sqrt( value ); }
};

/*! The partial specialization of RawRationalPowerHelper for N==1, D==3
 *
 * The std::cbrt method will be used instead of std::pow.
 * \ingroup quantity_traits
 */
template<typename T>
struct RawRationalPowerHelper<1,3,T>
{
  //! Calculate the cubed root of the value
  static inline T calculateRationalPower( const T& value )
  { return std::cbrt( value ); }
};

/*! The partial specialization of RawRationalPowerHelper for N>1,D>1,N<D,N%D==0
 * If D is an integer multiple of N, we will set N to 1 and D to D/N to 
 * take advantage of other partial specializations for N==1.
 * \ingroup quantity_traits
 */
template<boost::units::integer_type N,
         boost::units::integer_type D,
         typename T>
struct RawRationalPowerHelper<N, D, T, typename std::enable_if<(N>1 && D>1 && N<D && D%N==0)>::type> : public RawRationalPowerHelper<1,D/N,T>
{ /* ... */ };         

/*! The partial specialization of RawRationalPowerHelper for N<0, D>0
 *
 * Instead of using the std::pow method, 1 over the value calculated from
 * RawRationalPowerHelper for N>0, D>0 will be returned (any specializations
 * for abs(N), D can be taken advantage of this way).
 * \ingroup quantity_traits
 */
template<boost::units::integer_type N,
         boost::units::integer_type D,
         typename T>
struct RawRationalPowerHelper<N,D,T,typename std::enable_if<(N<0 && D>0)>::type>
{
  //! Calculate the value raised to the rational power -(N/D)
  static inline T calculateRationalPower( const T& value )
  { return 1/RawRationalPowerHelper<-N,D,T>::calculateRationalPower( value ); }
};

/*! The partial specialization of RawRationalPowerHelper for N>0, D<0
 *
 * Instead of using the std::pow method, 1 over the value calculated from
 * RawRationalPowerHelper for N>0, D>0 will be returned (any specializations
 * for N, abs(D) can be taken advantage of this way).
 * \ingroup quantity_traits
 */
template<boost::units::integer_type N,
         boost::units::integer_type D,
         typename T>
struct RawRationalPowerHelper<N,D,T,typename std::enable_if<(N>0 && D<0)>::type>
{
  //! Calculate the value raised to the rational power -(N/D)
  static inline T calculateRationalPower( const T& value )
  { return 1/RawRationalPowerHelper<N,-D,T>::calculateRationalPower( value ); }
};

/*! The partial specialization of RawRationalPowerHelper for N<0, D<0
 *
 * The partial specialization of RawRationalPowerHelper for N>0, D>0 will be
 * used.
 * \ingroup quantity_traits
 */
template<boost::units::integer_type N,
         boost::units::integer_type D,
         typename T>
struct RawRationalPowerHelper<N,D,T,typename std::enable_if<N<0 && D<0 && N!=D>::type> : public RawRationalPowerHelper<-N,-D,T>
{ /* ... */ };

/*! The true or false type
 * \ingroup quantity_traits
 */
template<bool is_true>
struct TrueOrFalseType : public std::conditional<is_true,std::true_type,std::false_type>::type
{ /* ... */ };

/*! The QuantityTraitsGeneralHelperBase
 * 
 * Only use this struct with arithmetic types
 * \ingroup quantity_traits
 */
template<typename T>
struct QuantityTraitsGeneralHelperBase
{
  //! The traits class for this quantity is specialized
  typedef TrueOrFalseType<std::numeric_limits<T>::is_specialized> is_specialized;

  //! Used to check if the quantity is signed
  typedef std::is_signed<T> is_signed;

  //! Used to check if the quantity is an integer type
  typedef std::is_integral<T> is_integer;

  //! Used to check if the quantity is a complex type
  typedef std::false_type is_complex;

  //! Used to check if the quantity uses exact representations
  typedef TrueOrFalseType<std::numeric_limits<T>::is_exact> is_exact;

  //! Used to check if a quantity adheres to IEC-559/IEEE-754 standard
  typedef TrueOrFalseType<std::numeric_limits<T>::is_iec559> is_iec559;

  //! Used to check if the set of values represented by the quantity is finite
  typedef TrueOrFalseType<std::numeric_limits<T>::is_bounded> is_bounded;

  //! Used to check if the quantity is modulo
  typedef TrueOrFalseType<std::numeric_limits<T>::is_modulo> is_modulo;

  //! Used to check if the quantity has a representation for positive infinity
  typedef TrueOrFalseType<std::numeric_limits<T>::has_infinity> has_infinity;

  //! Used to check if the quantity has a representation for quiet nan
  typedef TrueOrFalseType<std::numeric_limits<T>::has_quiet_NaN> has_quiet_nan;

  //! Used to check if the quantity has a representation for signaling nan
  typedef TrueOrFalseType<std::numeric_limits<T>::has_signaling_NaN> has_signaling_nan;
  
  //! Used to check if the quantity allows denormalized values
  typedef TrueOrFalseType<std::numeric_limits<T>::has_denorm> has_denorm;

  //! Used to check if a loss of accuracy is detected as a denormalization loss instead of an inexact result
  typedef TrueOrFalseType<std::numeric_limits<T>::has_denorm_loss> has_denorm_loss;

  //! Used to check if trapping is implemented for the quantity
  typedef TrueOrFalseType<std::numeric_limits<T>::traps> traps;

  //! Used to check if tinyness is checked before rounding
  typedef TrueOrFalseType<std::numeric_limits<T>::tinyness_before> tinyness_before;

  //! Used to check the rounding style of floating-point quantities (only available for floating-point quantities)
  typedef std::integral_constant<std::float_round_style,std::numeric_limits<T>::round_style> round_style;

  //! The number of non-sign bits
  typedef std::integral_constant<int,std::numeric_limits<T>::digits> digits;

  //! The number of digits (in decimal base) that can be represented
  typedef std::integral_constant<int,std::numeric_limits<T>::digits10> digits10;

  //! The number of digits (in decimal base) required to ensure that values that differ are always differentiated
  typedef std::integral_constant<int,std::numeric_limits<T>::max_digits10> max_digits10;

  //! Base of the representation
  typedef std::integral_constant<int,std::numeric_limits<T>::radix> radix;

  //! Min negative integer value such that radix raised to (this-1) generates a normalized floating-point quantity
  typedef std::integral_constant<int,std::numeric_limits<T>::min_exponent> min_exponent;

  //! Min negative integer value such that 10 raised to that power generates a normalized floating-point quantity
  typedef std::integral_constant<int,std::numeric_limits<T>::min_exponent10> min_exponent10;

  //! One more than the largest integer power of the radix that is a valid finite floating-point value
  typedef std::integral_constant<int,std::numeric_limits<T>::max_exponent> max_exponent;

  //! Max integer power of 10 that is a valid finite floating-point value
  typedef std::integral_constant<int,std::numeric_limits<T>::max_exponent10> max_exponent10;

private:

  // Typedef for this type
  typedef QuantityTraitsGeneralHelperBase<T> ThisType;
  
protected:

  //! Get the raw zero value
  static inline T rawZero() noexcept
  { return T(0); }

  //! Get the raw one value
  static inline T rawOne() noexcept
  { return T(1); }

  //! Get the min value
  static inline T rawMin() noexcept
  { return std::numeric_limits<T>::min(); }

  //! Get the min positive denormalized value
  static inline T rawDenormMin() noexcept
  { return std::numeric_limits<T>::denorm_min(); }

  //! Get the max value
  static inline T rawMax() noexcept
  { return std::numeric_limits<T>::max(); }

  //! Get the lowest value
  static inline T rawLowest() noexcept
  { return std::numeric_limits<T>::lowest(); }

  //! Get the machine epsilon 
  static inline T rawEpsilon() noexcept
  { return std::numeric_limits<T>::epsilon(); }

  //! Get the maximum rounding error
  static inline T rawRoundError() noexcept
  { return std::numeric_limits<T>::round_error(); }

  //! Get the quiet nan quantity 
  static inline T rawNan() noexcept
  { return std::numeric_limits<T>::quiet_NaN(); }

  //! Get the signaling nan quantity (only available for floating-point quantities)
  static inline T rawSignalingNan() noexcept
  { return std::numeric_limits<T>::signaling_NaN(); }

  //! Get the conjugate of a value
  static inline T rawConj( const T a ) noexcept
  { return a; }

  //! Get the real part of the value
  static inline T rawReal( const T a ) noexcept
  { return a; }

  //! Get the imaginary part of the value
  static inline T rawImag( const T a ) noexcept
  { return ThisType::zero(); }

  //! Take the square root of a value 
  static inline T rawSqrt( const T a )
  { return std::sqrt( a ); }

  //! Take the cube root of a value
  static inline T rawCbrt( const T a )
  { return std::cbrt( a ); }

  //! Take a value to the desired rational power
  template<boost::units::integer_type N, boost::units::integer_type D>
  static inline T rawRpow( const T a )
  { return RawRationalPowerHelper<N,D,T>::calculateRationalPower( a ); }
};

/*! The QuantityTraitsGeneralHelperBase partial specialization for std::complex
 * \ingroup quantity_traits
 */
template<typename T>
struct QuantityTraitsGeneralHelperBase<std::complex<T> > : public QuantityTraitsGeneralHelperBase<T>
{
  //! Used to check if the quantity is a complex type
  typedef std::true_type is_complex;
  
private:

  // Typedef for the base type
  typedef QuantityTraitsGeneralHelperBase<T> BaseType;
  
protected:

  //! Get the raw zero value
  static inline std::complex<T> rawZero() noexcept
  { return std::complex<T>(BaseType::rawZero(), BaseType::rawZero()); }

  //! Get the raw one value
  static inline std::complex<T> rawOne() noexcept
  { return std::complex<T>(BaseType::rawOne(), BaseType::rawZero()); }

  //! Get the min quantity
  static inline std::complex<T> rawMin() noexcept
  { return std::complex<T>(BaseType::rawMin(), BaseType::rawZero()); }

  //! Get the min positive denormalized value
  static inline std::complex<T> rawDenormMin() noexcept
  { return std::complex<T>(BaseType::rawDenormMin(), BaseType::rawZero()); }

  //! Get the max quantity
  static inline std::complex<T> rawMax() noexcept
  { return std::complex<T>(BaseType::rawMax(), BaseType::rawZero()); }

  //! Get the lowest quantity
  static inline std::complex<T> rawLowest() noexcept
  { return std::complex<T>(BaseType::rawLowest(), BaseType::rawZero()); }

  //! Get the machine epsilon 
  static inline std::complex<T> rawEpsilon() noexcept
  { return std::complex<T>(BaseType::rawEpsilon(), BaseType::rawZero()); }

  //! Get the maximum rounding error
  static inline std::complex<T> rawRoundError() noexcept
  { return std::complex<T>(BaseType::rawRoundError(), BaseType::rawZero()); }

  //! Get the quiet nan quantity 
  static inline std::complex<T> rawNan() noexcept
  { return std::complex<T>(BaseType::rawNan(), BaseType::rawZero()); }

  //! Get the signaling nan quantity (only available for floating-point quantities)
  static inline std::complex<T> rawSignalingNan() noexcept
  { return std::complex<T>(BaseType::rawSignalingNan(), BaseType::rawZero()); }

  //! Get the conjugate of a quantity
  static inline std::complex<T> rawConj( const std::complex<T>& a )
  { return std::conj( a ); }

  //! Get the real part of the quantity
  static inline std::complex<T> rawReal( const std::complex<T>& a )
  { return std::complex<T>(std::real( a ), BaseType::rawZero()); }

  //! Get the imaginary part of the quantity
  static inline std::complex<T> rawImag( const std::complex<T>& a )
  { return std::complex<T>(BaseType::rawZero(), std::imag( a )); }

  //! Take the square root of a value 
  static inline std::complex<T> rawSqrt( const std::complex<T>& a )
  { return std::sqrt( a ); }

  //! Take the cube root of a value
  static inline std::complex<T> rawCbrt( const std::complex<T>& a )
  { return std::cbrt( a ); }

  //! Take a value to the desired rational power
  template<boost::units::integer_type N, boost::units::integer_type D>
  static inline std::complex<T> rawRpow( const std::complex<T>& a )
  { return RawRationalPowerHelper<N,D,std::complex<T> >::calculateRationalPower( a ); }
};

/*! The QuantityTraitsHelperBase
 * \details Only use this struct with arithmetic and complex types
 * \ingroup quantity_traits
 */
template<typename T, typename Enabled = void>
struct QuantityTraitsHelperBase;

/*! \brief The QuantityTraitsHelperBase partial specialization for 
 * floating-point types
 * \ingroup quantity_traits
 */
template<typename T>
struct QuantityTraitsHelperBase<T,typename std::enable_if<std::is_floating_point<T>::value>::type> : public QuantityTraitsGeneralHelperBase<T>
{
private:

  // Typedef for this type
  typedef QuantityTraitsHelperBase<T,typename std::enable_if<std::is_floating_point<T>::value>::type> ThisType;

protected:

  //! Get the inf value
  static inline T rawInf() noexcept
  { return std::numeric_limits<T>::infinity(); }

  //! Get the absolute value of the given value
  static inline T rawAbs( const T value )
  { return fabs( value ); }

  /*! Test if the value is a nan or inf (only available for floating-point quantities)
   */
  static inline bool rawIsnaninf( const T a )
  {
    // Check for nan
    if( a != a )
      return true;

    // Check for inf
    if( ThisType::rawAbs( a ) == ThisType::rawInf() )
      return true;

    // Neither nan nor inf
    return false;
  }
};

/*! \brief The QuantityTraitsHelperBase partial specialization for 
 * integral types
 * \ingroup quantity_traits
 */
template<typename T>
struct QuantityTraitsHelperBase<T,typename std::enable_if<std::is_integral<T>::value>::type> : public QuantityTraitsGeneralHelperBase<T>
{
private:

  // Typedef for this type
  typedef QuantityTraitsHelperBase<T,typename std::enable_if<std::is_integral<T>::value>::type> ThisType;
  
protected:

  //! Get the inf value (simply the max value for integral types)
  static inline T rawInf() noexcept
  { return std::numeric_limits<T>::max(); }
  
  //! Get the absolute value of the given value
  static inline T rawAbs( const T value )
  { return std::abs( value ); }

  //! Test if the quantity is a nan or inf
  static inline bool rawIsnaninf( const T a )
  {
    // Check for nan
    if( ThisType::has_quiet_nan::value )
    {
      if( a != a )
        return true;
    }

    // Check for inf
    if( ThisType::has_infinity::value )
    {
      if( ThisType::rawAbs( a ) == ThisType::rawInf() )
        return true;
    }

    // Neither nan nor inf
    return false;
  }
};

/*! \brief The QuantityTraitsHelperBase partial specialization for std::complex
 * types
 * \ingroup quantity_traits
 */
template<typename T>
struct QuantityTraitsHelperBase<std::complex<T> > : public QuantityTraitsGeneralHelperBase<std::complex<T> >
{
private:

  // Typedef for base type of T (parallel base type
  typedef QuantityTraitsHelperBase<T> ParallelBaseType;
  
protected:

  //! Get the inf quantity
  static inline std::complex<T> rawInf() noexcept
  { return std::complex<T>(ParallelBaseType::rawInf(), ParallelBaseType::rawZero()); }

  //! Get the absolute value (magnitude) of the given complex value
  static inline std::complex<T> rawAbs( const std::complex<T>& a ) noexcept
  { return std::complex<T>( std::abs( a ), ParallelBaseType::rawZero() ); }

  //! Test if the either the real or complex component of the value is a nan or inf 
  static inline bool rawIsnaninf( const std::complex<T>& a )
  {
    return ParallelBaseType::rawIsnaninf( std::real( a ) ) ||
      ParallelBaseType::rawIsNaninf( std::imag( a ) );
  }
};

/*! The QuantityTraitsRawTypeHelperBase
 * \details Only use this struct with raw (unitless) types
 * \ingroup quantity_traits
 */
template<typename T, typename Enabled = void>
struct QuantityTraitsRawTypeHelper : public QuantityTraitsHelperBase<T>
{
private:

  // Typedef for the base type
  typedef QuantityTraitsHelperBase<T> BaseType;

public:

  //! The unit type
  typedef void UnitType;

  //! The raw quantity type (no units)
  typedef T RawType;

  //! The quantity type
  typedef T QuantityType;

  //! The quantity raised to rational power N/D type
  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetQuantityToPowerType
  { typedef T type; };

  //! Get the zero quantity
  static inline QuantityType zero() noexcept
  { return BaseType::rawZero(); }

  //! Get the one quantity
  static inline QuantityType one() noexcept
  { return BaseType::rawOne(); }

  //! Get the min quantity
  static inline QuantityType min() noexcept
  { return BaseType::rawMin(); }

  //! Get the min positive denormalized value
  static inline QuantityType denormMin() noexcept
  { return BaseType::rawDenormMin(); }

  //! Get the max quantity
  static inline QuantityType max() noexcept
  { return BaseType::rawMax(); }

  //! Get the lowest quantity
  static inline QuantityType lowest() noexcept
  { return BaseType::rawLowest(); }

  //! Get the machine epsilon 
  static inline QuantityType epsilon() noexcept
  { return BaseType::rawEpsilon(); }

  //! Get the maximum rounding error
  static inline QuantityType roundError() noexcept
  { return BaseType::rawRoundError(); }

  //! Get the inf quantity 
  static inline QuantityType inf() noexcept
  { return BaseType::rawInf(); }

  //! Get the quiet nan quantity 
  static inline QuantityType nan() noexcept
  { return BaseType::rawNan(); }

  //! Get the signaling nan quantity (only available for floating-point quantities)
  static inline QuantityType signalingNan() noexcept
  { return BaseType::rawSignalingNan(); }

  //! Get the absolute value of a quantity
  static inline QuantityType abs( const QuantityType& a )
  { return BaseType::rawAbs( a.value() ); }

  //! Get the complex conjugate of the quantity
  static inline QuantityType conj( const QuantityType& a )
  { return BaseType::rawConj( a.value() ); }

  //! Get the real component of the quantity
  static inline QuantityType real( const QuantityType& a )
  { return BaseType::rawReal( a.value() ); }

  //! Get the imaginary component of the quantity
  static inline QuantityType imag( const QuantityType& a )
  { return BaseType::rawImag( a.value() ); }

  //! Test if the quantity is a nan or inf 
  static inline bool isnaninf( const QuantityType& a )
  { return BaseType::rawIsnaninf( a ); }

  //! Get the square root of the quantity
  static inline QuantityType sqrt( const QuantityType& a )
  { return BaseType::rawSqrt( a ); }

  //! Get the cube root of the quantity
  static inline QuantityType cbrt( const QuantityType& a )
  { return BaseType::rawCbrt( a ); }

  template<boost::units::integer_type N, boost::units::integer_type D>
  static inline QuantityType rpow( const QuantityType& a ) noexcept
  { return BaseType::rawRpow( a ); }
  
  //! Potentially dangerous to initialize quantities in this way!
  static inline QuantityType initializeQuantity( const RawType& raw_quantity ) noexcept
  { return raw_quantity; }

  //! Get the raw value of a quantity
  static inline const RawType& getRawQuantity( const QuantityType& quantity ) noexcept
  { return quantity; }

  //! Set the value of a quantity (potentially dangerous!)
  static inline void setQuantity( QuantityType& quantity,
				  const RawType& raw_quantity )
  { quantity = raw_quantity; }
};

/*! The QuantityToPowerTypeHelper (default not defined)
 * \ingroup quantity_traits
 */
template<boost::units::integer_type N, boost::units::integer_type D, typename QuantityType, typename Enabled = void>
struct QuantityToPowerTypeHelper;

/*! Partial specialization of QuantityToPowerTypeHelper for N!=D, N!=0
 * \ingroup quantity_traits
 */
template<boost::units::integer_type N, boost::units::integer_type D, typename Unit, typename T>
struct QuantityToPowerTypeHelper<N,D,boost::units::quantity<Unit,T>, typename std::enable_if<N!=D && N!=0>::type>
{
  //! The quantity to the rational power N/D type
  typedef boost::units::quantity<typename Utility::UnitTraits<Unit>::template GetUnitToPowerType<N,D>::type,T> QuantityToRpowType;

  //! Compute the quantity raised to the rational power N/D
  static inline QuantityToRpowType rpow( const boost::units::quantity<Unit,T>& a )
  {
    return QuantityToRpowType::from_value( QuantityTraitsHelperBase<T>::rawRpow( a.value() ) );
  }
};

/*! Partial specialization of QuantityToPowerTypeHelper for N!=D, N==0
 * \ingroup quantity_traits
 */
template<boost::units::integer_type D, typename Unit, typename T>
struct QuantityToPowerTypeHelper<0,D,boost::units::quantity<Unit,T>, typename std::enable_if<D!=0>::type>
{
  //! The quantity to the 0th power type
  typedef T QuantityToRpowType;

  //! Compute the quantity raised to the rational power N/D
  static inline QuantityToRpowType rpow( const boost::units::quantity<Unit,T>& a )
  {
    return QuantityTraitsHelperBase<T>::rawRpow<0,D>( a.value() );
  }
}; 

/*! Partial specialization of QuantityToPowerTypeHelper for N==D, N!=0
 * \ingroup quantity_traits
 */
template<boost::units::integer_type I, typename QuantityType>
struct QuantityToPowerTypeHelper<I, I, QuantityType, typename std::enable_if<I!=0>::type>
{
  //! The quantity to the rational power 1 type
  typedef QuantityType QuantityToRpowType;

  //! Compute the quantity raised to the rational power 1
  static inline QuantityToRpowType rpow( const QuantityType& a )
  { return a; }
};

/*! The QuantityTraitsQuantityTypeHelperBase
 * \details Only use this struct with quantity types
 * \ingroup quantity_traits
 */
template<typename T, typename Enabled = void>
struct QuantityTraitsQuantityTypeHelper;

/*! \brief The QuantityTraitsQuantityTypeHelperBase partial specialization for 
 * all boost::units::quantity types
 * \ingroup quantity_traits
 */
template<typename Unit, typename T>
struct QuantityTraitsQuantityTypeHelper<boost::units::quantity<Unit,T> > : public QuantityTraitsHelperBase<T>
{
private:
  
  // Typedef for the base type
  typedef QuantityTraitsHelperBase<T> BaseType;

public:
  
  //! The unit type
  typedef Unit UnitType;

  //! The raw quantity type (no units)
  typedef T RawType;

  //! The quantity type
  typedef boost::units::quantity<Unit,T> QuantityType;

  //! The quantity raised to rational power N/D type
  template<boost::units::integer_type N, boost::units::integer_type D = 1>
  struct GetQuantityToPowerType
  {
    //typedef typename std::conditional<N==D,QuantityType,typename boost::units::power_typeof_helper<QuantityType,boost::units::static_rational<N,D> >::type>::type type;
    typedef typename QuantityToPowerTypeHelper<N,D,QuantityType>::QuantityToRpowType type;
  };

  //! Get the zero quantity
  static inline QuantityType zero() noexcept
  { return QuantityType::from_value( BaseType::rawZero() ); }

  //! Get the one quantity
  static inline QuantityType one() noexcept
  { return QuantityType::from_value( BaseType::rawOne() ); }

  //! Get the min quantity
  static inline QuantityType min() noexcept
  { return QuantityType::from_value( BaseType::rawMin() ); }

  //! Get the min positive denormalized value
  static inline QuantityType denormMin() noexcept
  { return QuantityType::from_value( BaseType::rawDenormMin() ); }

  //! Get the max quantity
  static inline QuantityType max() noexcept
  { return QuantityType::from_value( BaseType::rawMax() ); }

  //! Get the lowest quantity
  static inline QuantityType lowest() noexcept
  { return QuantityType::from_value( BaseType::rawLowest() ); }

  //! Get the machine epsilon 
  static inline QuantityType epsilon() noexcept
  { return QuantityType::from_value( BaseType::rawEpsilon() ); }

  //! Get the maximum rounding error
  static inline QuantityType roundError() noexcept
  { return QuantityType::from_value( BaseType::rawRoundError() ); }

  //! Get the inf quantity 
  static inline QuantityType inf() noexcept
  { return QuantityType::from_value( BaseType::rawInf() ); }

  //! Get the quiet nan quantity 
  static inline QuantityType nan() noexcept
  { return QuantityType::from_value( BaseType::rawNan() ); }

  //! Get the signaling nan quantity (only available for floating-point quantities)
  static inline QuantityType signalingNan() noexcept
  { return QuantityType::from_value( BaseType::rawSignalingNan() ); }

  //! Get the absolute value of a quantity
  static inline QuantityType abs( const QuantityType& a )
  { return QuantityType::from_value( BaseType::rawAbs( a.value() ) ); }

  //! Get the complex conjugate of the quantity
  static inline QuantityType conj( const QuantityType& a )
  { return QuantityType::from_value( BaseType::rawConj( a.value() ) ); }

  //! Get the real component of the quantity
  static inline QuantityType real( const QuantityType& a )
  { return QuantityType::from_value( BaseType::rawReal( a.value() ) ); }

  //! Get the imaginary component of the quantity
  static inline QuantityType imag( const QuantityType& a )
  { return QuantityType::from_value( BaseType::rawImag( a.value() ) ); }

  //! Test if the quantity is a nan or inf 
  static inline bool isnaninf( const QuantityType& a )
  { return BaseType::rawIsnaninf( a.value() ); }

  /*! Get the square root of the quantity
   * \details There appears to be a bug in boost::units::sqrt so it is not used
   * in the implementation of this method
   */
  static inline typename GetQuantityToPowerType<1,2>::type sqrt( const QuantityType& quantity )
  {
    return GetQuantityToPowerType<1,2>::type::from_value( BaseType::rawSqrt( quantity.value() ) );
  }

  //! Get the cube root of the quantity
  static inline typename GetQuantityToPowerType<1,3>::type cbrt( const QuantityType& quantity )
  {
    return GetQuantityToPowerType<1,3>::type::from_value( BaseType::rawCbrt( quantity.value() ) );
  }

  //! Take the quantity to the desired rational power
  template<boost::units::integer_type N, boost::units::integer_type D>
  static inline typename GetQuantityToPowerType<N,D>::type rpow( const QuantityType& quantity )
  { return QuantityToPowerTypeHelper<N,D,QuantityType>::rpow( quantity ); }
  
  //! Potentially dangerous to initialize quantities in this way!
  static inline QuantityType initializeQuantity( const RawType& raw_quantity ) noexcept
  { return QuantityType::from_value( raw_quantity ); }

  //! Get the raw value of a quantity
  static inline const RawType& getRawQuantity( const QuantityType& quantity ) noexcept
  { return quantity.value(); }

  //! Set the value of a quantity (potentially dangerous!)
  static inline void setQuantity( QuantityType& quantity,
				  const RawType& raw_quantity )
  { quantity = QuantityType::from_value( raw_quantity ); }
};

} // end Details namespace

/*! \brief The partial specialization of QuantityTraits for all arithmetic 
 * types (no units).
 *
 * Note: having no units is different than a dimensionless unit, which is a
 * defined unit type in the boost::units package.
 * \ingroup quantity_traits
 */
template<typename T>
struct QuantityTraits<T,typename std::enable_if<std::is_arithmetic<T>::value>::type> : public Details::QuantityTraitsRawTypeHelper<T>
{ /* ... */ };

/*! The partial specialization of QuantityTraits for all std::complex types 
 * (no units).
 *
 * Note: having no units is different than a dimensionless unit, which is a
 * defined unit type in the boost::units package.
 * \ingroup quantity_traits
 */
template<typename T>
struct QuantityTraits<std::complex<T>,typename std::enable_if<std::is_arithmetic<T>::value>::type> : public Details::QuantityTraitsRawTypeHelper<std::complex<T> >
{ /* ... */ };

/*! \brief The partial specialization of QuantityTraits for all
 * boost::units::quantity types
 * \ingroup quantity_traits
 */
template<typename Unit, typename T>
struct QuantityTraits<boost::units::quantity<Unit,T> > : public Details::QuantityTraitsQuantityTypeHelper<boost::units::quantity<Unit,T> >
{ /* ... */ };

} // end Utility namespace

#endif // end UTILITY_QUANTITY_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_QuantityTraits.hpp
//---------------------------------------------------------------------------//
