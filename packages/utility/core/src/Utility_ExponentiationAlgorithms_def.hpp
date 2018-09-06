//---------------------------------------------------------------------------//
//!
//! \file   Utility_ExponentiationAlgorithms_def.hpp
//! \author Alex Robinson
//! \brief  Function definitions for exponentiation algorithms.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EXPONENTIATION_ALGORITHMS_DEF_HPP
#define UTILITY_EXPONENTIATION_ALGORITHMS_DEF_HPP

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"

namespace Utility{

namespace Exponentiation{

// Recursive exponentiation algorithm
/*! \details Recursively evaluates the function x^y. This algorithm is a
 * modified version of the one found in "Algorithms" by Desgupta et al. Care
 * must be taken with integer types since overflow is possible with large
 * exponents and/or base values. In some cases the overflow is desired
 * (i.e. 2^64 or 2^32 modular exponentiation).
 */
template<typename BaseScalarType, typename ExponentOrdinalType>
typename std::enable_if<std::is_arithmetic<BaseScalarType>::value,BaseScalarType>::type
recursive( const BaseScalarType x, const ExponentOrdinalType y )
{
  testPrecondition( y >= 0 );

  // The output integer
  BaseScalarType z;

  if( y == 0 )
    z = 1;
  else
  {
    z = Exponentiation::recursive( x, y/2 );

    if( y%2 == 0 )
      z = z*z;
    else
      z = x*z*z;
  }

  // Return the new base
  return z;
}

// Recursive exponentiation algorithm (static)
/*! \details The value x^N will be computed in log(N) multiplications.
 */
template<size_t N, typename BaseScalarType>
typename QuantityTraits<BaseScalarType>::template GetQuantityToPowerType<N>::type
recursive( const BaseScalarType x )
{
  // Recursive exponentiation has been implemented by the rpow method for
  // the special case of positive integer powers
  return QuantityTraits<BaseScalarType>::template rpow<N,1>( x );
}

// Recursive modular exponentiation algorithm
/*! \details Recursively evaluates the function (x^y)mod(m). This algorithm is
 * based on the one found in "Algorithms" by Desgupta et al.
 */
template<typename OrdinalType>
typename std::enable_if<std::is_integral<OrdinalType>::value,OrdinalType>::type
recursiveMod( const OrdinalType x,
              const OrdinalType y,
              const OrdinalType m )
{
  // Make sure that the ExponentOrdinalType is not a scalar type
  testStaticPrecondition((boost::is_integral<OrdinalType>::value));
  // Make sure that the exponent is positive
  testPrecondition( y >= 0 );
  // Make sure that the modulus is positive
  testPrecondition( m >= 1 );

  // The output integer
  OrdinalType z;

  if( y == 0 )
    z = 1;
  else
  {
    z = Exponentiation::recursiveMod( x, y/2, m );

    if( y%2 == 0 )
      z = (z*z)%m;
    else
      z = (x*z*z)%m;
  }

  // Return the new base
  return z;
}

} // end Exponentiation namespace

} // end Utility namespace

#endif // end UTILITY_EXPONENTIATION_ALGORITHMS_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_ExponentiationAlgorithms_def.hpp
//---------------------------------------------------------------------------//
