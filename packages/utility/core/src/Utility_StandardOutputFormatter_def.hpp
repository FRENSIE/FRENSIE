//---------------------------------------------------------------------------//
//!
//! \file   Utility_StandardOutputFormatter_def.hpp
//! \author Alex Robinson
//! \brief  The standard output formatter class template definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STANDARD_OUTPUT_FORMATTER_DEF_HPP
#define UTILITY_STANDARD_OUTPUT_FORMATTER_DEF_HPP

// Std Lib Includes
#include <sstream>

namespace Utility{

// General constructor
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy>
template<typename T>
StandardOutputFormatter<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>::StandardOutputFormatter(
                                                 const T& raw_string_contents )
{
  // Convert the input to a string
  std::ostringstream oss;
  oss << raw_string_contents;

  this->formatRawString( oss.str() );
}

// String constructor
template<typename TextFormatPolicy,
         typename TextColorPolicy, 
         typename TextBackgroundColorPolicy>
StandardOutputFormatter<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>::StandardOutputFormatter(
                                       const std::string& raw_string_contents )
{
  this->formatRawString( raw_string_contents );
}

// C-string constructor
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy>
StandardOutputFormatter<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>::StandardOutputFormatter( const char* raw_string_contents )
{
  this->formatRawString( raw_string_contents );
}

// Double constructor
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy>
StandardOutputFormatter<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>::StandardOutputFormatter(
                                             const double& raw_string_contents,
                                             const unsigned precision )
{
  // Convert the input to a string
  std::ostringstream oss;
  oss.precision( precision );
  oss << raw_string_contents;

  this->formatRawString( oss.str() );
}

// Get the text format
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy>
std::string StandardOutputFormatter<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>::getTextFormat() const
{
  return TextFormatPolicy::getTextFormat();
}

// Get the text color
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy>
std::string StandardOutputFormatter<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>::getTextColor() const
{
  return TextColorPolicy::getTextColor();
}

// Get the text background color
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy>
std::string StandardOutputFormatter<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>::getTextBackgroundColor() const
{
  return TextBackgroundColorPolicy::getTextBackgroundColor();
}

} // end Utility namespace

#endif // end UTILITY_STANDARD_OUTPUT_FORMATTER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_StandardOutputFormatter_def.hpp
//---------------------------------------------------------------------------//
