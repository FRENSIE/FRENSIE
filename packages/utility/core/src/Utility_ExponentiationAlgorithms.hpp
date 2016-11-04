//---------------------------------------------------------------------------//
//!
//! \file   Utility_ExponentiationAlgorithms.hpp
//! \author Alex Robinson
//! \brief  Function declarations for exponentiation algorithms.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EXPONENTIATION_ALGORITHMS_HPP
#define UTILITY_EXPONENTIATION_ALGORITHMS_HPP

namespace Utility{

namespace Exponentiation{

//! Recursive exponentiation algorithm
template<typename BaseScalarType, typename ExponentOrdinalType>
BaseScalarType recursive( const BaseScalarType x,
			  const ExponentOrdinalType y );

//! Recursive modular exponentiation algorithm
template<typename OrdinalType>
OrdinalType recursiveMod( const OrdinalType x,
			  const OrdinalType y,
			  const OrdinalType m );

} // end Exponentiation namespace

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Utility_ExponentiationAlgorithms_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_EXPONENTIATION_ALGORITHMS_HPP

//---------------------------------------------------------------------------//
// end Utility_ExponentiationAlgorithms.hpp
//---------------------------------------------------------------------------//
