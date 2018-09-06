//---------------------------------------------------------------------------//
//!
//! \file   Utility_ExponentiationAlgorithms.hpp
//! \author Alex Robinson
//! \brief  Function declarations for exponentiation algorithms.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EXPONENTIATION_ALGORITHMS_HPP
#define UTILITY_EXPONENTIATION_ALGORITHMS_HPP

// Std Lib Includes
#include <type_traits>

// FRENSIE Includes
#include "Utility_QuantityTraits.hpp"

namespace Utility{

namespace Exponentiation{

//! Recursive exponentiation algorithm
template<typename BaseScalarType, typename ExponentOrdinalType>
typename std::enable_if<std::is_arithmetic<BaseScalarType>::value,BaseScalarType>::type
recursive( const BaseScalarType x, const ExponentOrdinalType y );

//! Recursive exponentiation algorithm (compile-time)
template<size_t N, typename BaseScalarType>
typename QuantityTraits<BaseScalarType>::template GetQuantityToPowerType<N>::type
recursive( const BaseScalarType x );

//! Recursive modular exponentiation algorithm
template<typename OrdinalType>
typename std::enable_if<std::is_integral<OrdinalType>::value,OrdinalType>::type
recursiveMod( const OrdinalType x,
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
