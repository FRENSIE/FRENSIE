//---------------------------------------------------------------------------//
//!
//! \file   ExponentiationAlgorithms_def.hpp
//! \author Alex Robinson
//! \brief  Function definitions for exponentiation algorithms.
//!
//---------------------------------------------------------------------------//

#ifndef EXPONENTIATION_ALGORITHMS_DEF_HPP
#define EXPONENTIATION_ALGORITHMS_DEF_HPP

// FACEMC Includes
#include "ContractException.hpp"

namespace FACEMC{

namespace Exponentiation{

// Recursive exponentiation algorithm
/*! \details Recursively evaluates the function x^y. This algorithm is a
 * modified version of the one found in "Algorithms" by Desgupta et al. Care
 * must be taken with integer types since overflow is large exponents and/or
 * base values. In some cases the overflow is desired (i.e. 2^64 or 2^32  
 * modular exponentiation).
 */
template<typename BaseScalarType, typename ExponentOrdinalType>
BaseScalarType recursive( const BaseScalarType x, 
			  const ExponentOrdinalType y )
{
  // Make sure that the ExponentOrdinalType is not a scalar type
  testStaticPrecondition((boost::is_integral<ExponentOrdinalType>::value));
  // Make sure thta the exponent is positive
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

// Recursive modular exponentiation algorithm
/*! \details Recursively evaluates the function (x^y)mod(m). This algorithm is 
 * based on the one found in "Algorithms" by Desgupta et al.
 */
template<typename OrdinalType>
OrdinalType recursiveMod( const OrdinalType x, 
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

} // end FACEMC namespace

#endif // end EXPONENTIATION_ALGORITHMS_DEF_HPP

//---------------------------------------------------------------------------//
// end ExponentiationAlgorithms_def.hpp
//---------------------------------------------------------------------------//
