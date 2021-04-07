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
#include "Utility_TypeTraits.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

/*! The measurement class
 *
 * The default template is not defined.
 */
template<typename T, typename Enabled = void>
class Measurement;

/*! The measurement class (for all floating-point types)
 *
 * This class wraps is meant to be used as any typical scalar type
 * (e.g. double). It is designed to keep track of and propagate the
 * uncertainty of a value (like one would with a measured quantity).
 */
template<typename T>
class Measurement<T,typename std::enable_if<std::is_floating_point<T>::value>::type> : public OStreamableObject
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
  explicit Measurement( const ValueType& value = QT::zero(),
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
  ValueType getRelativeUncertainty() const;

  //! Return the lower bound of the measurement
  ValueType getLowerBound() const;

  //! Return the upper bound of the measurement
  ValueType getUpperBound() const;

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

/*! Partial specialization of Utility::QuantityTraits for Utility::Measurement
 * \ingroup quantity_traits
 */
template<typename T>
struct QuantityTraits<Measurement<T>,typename std::enable_if<std::is_floating_point<T>::value>::type>;

/*! \brief Partial specialization of Utility::QuantityTraits for 
 * boost::units::quantity<Unit,Utility::Measurement> types
 * \ingroup quantity_traits
 */
template<typename Unit, typename T>
struct QuantityTraits<boost::units::quantity<Unit,Measurement<T> >,typename std::enable_if<std::is_floating_point<T>::value>::type>;

} // end Utility namespace

namespace std{

//! Overload of sqrt for a measurement
template<typename T>
Utility::Measurement<T> sqrt( const Utility::Measurement<T>& x );

//! Overload of cbrt for a measurement
template<typename T>
Utility::Measurement<T> cbrt( const Utility::Measurement<T>& x );

//! Overload of pow for a measurement
template<typename T, typename ExponentType>
Utility::Measurement<T> pow( const Utility::Measurement<T>& x,
                             const ExponentType exponent );

} // end std namespace

// Allow the above overloads to be accessed in the global namespace
using std::sqrt;
using std::cbrt;
using std::pow;

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_Measurement_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_MEASUREMENT_HPP

//---------------------------------------------------------------------------//
// end Utility_Measurement.hpp
//---------------------------------------------------------------------------//
