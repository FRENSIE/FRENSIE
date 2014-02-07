//---------------------------------------------------------------------------//
//!
//! \file   ExponentiationAlgorithms_def.hpp
//! \author Alex Robinson
//! \brief  Function definitions for exponentiation algorithms.
//!
//---------------------------------------------------------------------------//

#ifndef EXPONENTIATION_ALGORITHMS_DEF_HPP
#define EXPONENTIATION_ALGORITHMS_DEF_HPP

namespace FACEMC{

namespace Exponentiation{

// Recursive exponentiation algorithm
/*! \details Recursively evaluates the function x^y. This algorithm is a
 * modified version of the one found in "Algorithms" by Desgupta et al. Care
 * must be taken with integer types since overflow is large exponents and/or
 * base values. In some cases the overflow is desired (i.e. 2^64 or 2^32  
 * modular exponentiation).
 */
template<typename BaseScalarType, typename ExponentIntegralType>
BaseScalarType recursive( BaseScalarType x, ExponentIntegralType y )
{
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

} // end Exponentiation namespace

} // end FACEMC namespace

#endif // end EXPONENTIATION_ALGORITHMS_DEF_HPP

//---------------------------------------------------------------------------//
// end ExponentiationAlgorithms_def.hpp
//---------------------------------------------------------------------------//
