//---------------------------------------------------------------------------//
//!
//! \file   Utility_StaticOutputFormatter_def.hpp
//! \author Alex Robinson
//! \brief  The static output formatter class template definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STATIC_OUTPUT_FORMATTER_DEF_HPP
#define UTILITY_STATIC_OUTPUT_FORMATTER_DEF_HPP

// Std Lib Includes
#include <sstream>

namespace Utility{

// General constructor
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy>
template<typename T>
StaticOutputFormatter<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>::StaticOutputFormatter(
                                                 const T& raw_string_contents )
{
  // Convert the input to a string
  std::ostringstream oss;
  oss << raw_string_contents;

  this->setRawStringAndFormat<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>( oss.str() );
}

// String constructor
template<typename TextFormatPolicy,
         typename TextColorPolicy, 
         typename TextBackgroundColorPolicy>
StaticOutputFormatter<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>::StaticOutputFormatter(
                                       const std::string& raw_string_contents )
{
  this->setRawStringAndFormat<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>( raw_string_contents );
}

// C-string constructor
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy>
StaticOutputFormatter<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>::StaticOutputFormatter( const char* raw_string_contents )
{
  this->setRawStringAndFormat<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>( raw_string_contents );
}

// Double constructor
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy>
StaticOutputFormatter<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>::StaticOutputFormatter(
                                             const double& raw_string_contents,
                                             const unsigned precision )
{
  // Convert the input to a string
  std::ostringstream oss;
  oss.precision( precision );
  oss << raw_string_contents;

  this->setRawStringAndFormat<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>( oss.str() );
}

} // end Utility namespace

#endif // end UTILITY_STATIC_OUTPUT_FORMATTER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_StaticOutputFormatter_def.hpp
//---------------------------------------------------------------------------//
