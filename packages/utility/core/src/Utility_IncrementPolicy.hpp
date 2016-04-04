//---------------------------------------------------------------------------//
//!
//! \file   Utility_IncrementPolicy.hpp
//! \author Alex Robinson
//! \brief  Increment policy struct declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INCREMENT_POLICY_HPP
#define UTILITY_INCREMENT_POLICY_HPP

namespace Utility{

/*! \brief Policy struct for incrementing values
 * \ingroup policies
 */
struct IncrementPolicy
{
  //! Increment the value
  template<typename T>
  static void increment( T& value );
};

/*! \brief Policy structor for ignoring the incrementing of values
 * \ingroup policies
 */
struct IgnoreIncrementPolicy
{
  //! Increment the value
  template<typename T>
  static void increment( T& value );
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_IncrementPolicy_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_INCREMENT_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_IncrementPolicy.hpp
//---------------------------------------------------------------------------//
