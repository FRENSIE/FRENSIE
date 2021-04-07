//---------------------------------------------------------------------------//
//!
//! \file   Utility_TextFormatPolicy.cpp
//! \author Alex Robinson
//! \brief  The text format policy class definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_TextFormatPolicy.hpp"
#include "FRENSIE_tty_format_config.hpp"

namespace Utility{

// The default text format policy
std::string DefaultTextFormat::getTextFormat()
{
  return DEFAULT_FORMAT_KEY;
}

// The bold text format policy
std::string BoldTextFormat::getTextFormat()
{
  return BOLD_FORMAT_KEY;
}

// The faded text format policy
std::string FadedTextFormat::getTextFormat()
{
  return FADED_FORMAT_KEY;
}

// The italicized text format policy
std::string ItalicizedTextFormat::getTextFormat()
{
  return ITALICIZED_FORMAT_KEY;
}

// The underlined text format policy
std::string UnderlinedTextFormat::getTextFormat()
{
  return UNDERLINED_FORMAT_KEY;
}

} // end Utility namespace
  
//---------------------------------------------------------------------------//
// end Utility_TextFormatPolicy.cpp
//---------------------------------------------------------------------------//
