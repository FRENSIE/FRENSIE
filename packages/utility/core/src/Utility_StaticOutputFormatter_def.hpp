//---------------------------------------------------------------------------//
//!
//! \file   Utility_StaticOutputFormatter_def.hpp
//! \author Alex Robinson
//! \brief  The static output formatter class template definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STATIC_OUTPUT_FORMATTER_DEF_HPP
#define UTILITY_STATIC_OUTPUT_FORMATTER_DEF_HPP

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"

namespace Utility{

// General constructor
/*! \details This constructor can accept any type with a 
 * Utility::ToStringTraits specialization or Utility::toString overload.
 */
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy>
template<typename T>
StaticOutputFormatter<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>::StaticOutputFormatter(
                                                 const T& raw_string_contents )
{
  // Convert the input to a string
  this->setRawStringAndFormat<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>( Utility::toString( raw_string_contents ) );
}

} // end Utility namespace

#endif // end UTILITY_STATIC_OUTPUT_FORMATTER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_StaticOutputFormatter_def.hpp
//---------------------------------------------------------------------------//
