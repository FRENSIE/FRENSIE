//---------------------------------------------------------------------------//
//!
//! \file   Utility_TextFormatPolicy.hpp
//! \author Alex Robinson
//! \brief  The text format policy class declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TEXT_FORMAT_POLICY_HPP
#define UTILITY_TEXT_FORMAT_POLICY_HPP

// Std Lib Includes
#include <string>

namespace Utility{

//! The default text format policy
struct DefaultTextFormat
{
  static std::string getTextFormat();
};

//! The bold text format policy
struct BoldTextFormat
{
  static std::string getTextFormat();
};

//! The faded text format policy
struct FadedTextFormat
{
  static std::string getTextFormat();
};

//! The italicized text format policy
struct ItalicizedTextFormat
{
  static std::string getTextFormat();
};

//! The underlined text format policy
struct UnderlinedTextFormat
{
  static std::string getTextFormat();
};
  
} // end Utility namespace

#endif // end UTILITY_TEXT_FORMAT_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_TextFormatPolicy.hpp
//---------------------------------------------------------------------------//
