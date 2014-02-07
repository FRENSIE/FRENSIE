//---------------------------------------------------------------------------//
//!
//! \file   ExponentiationAlgorithms.hpp
//! \author Alex Robinson
//! \brief  Function declarations for exponentiation algorithms.
//!
//---------------------------------------------------------------------------//

#ifndef EXPONENTIATION_ALGORITHMS_HPP
#define EXPONENTIATION_ALGORITHMS_HPP

namespace FACEMC{

namespace Exponentiation{

//! Recursive exponentiation algorithm
template<typename BaseScalarType, typename ExponentIntegralType>
BaseScalarType recursive( BaseScalarType x, ExponentIntegralType y );

} // end Exponentiation namespace

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "ExponentiationAlgorithms_def.hpp"

//---------------------------------------------------------------------------//

#endif // end EXPONENTIATION_ALGORITHMS_HPP

//---------------------------------------------------------------------------//
// end ExponentiationAlgorithms.hpp
//---------------------------------------------------------------------------//
