//---------------------------------------------------------------------------//
//!
//! \file   Utility_IncrementPolicy_def.hpp
//! \author Alex Robinson
//! \brief  Increment policy struct definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INCREMENT_POLICY_DEF_HPP
#define UTILITY_INCREMENT_POLICY_DEF_HPP

namespace Utility{

// Increment the value
/*! \details The pre-increment operator will be called with the input value.
 */
template<typename T>
inline void IncrementPolicy::increment( T& value )
{
  ++value;
}

// Increment the value
/*! \details Nothing will be done to the input value.
 */
template<typename T>
inline void IgnoreIncrementPolicy::increment( T& value )
{ /* ... */ }


} // end Utility namespace

#endif // end UTILITY_INCREMENT_POLICY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_IncrementPolicy_def.hpp
//---------------------------------------------------------------------------//
