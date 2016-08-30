//---------------------------------------------------------------------------//
//!
//! \file   Utility_DynamicOutputFormatter.cpp
//! \author Alex Robinson
//! \brief  Dynamic output formatter definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_DynamicOutputFormatter.hpp"

namespace Utility{

// Constructor
DynamicOutputFormatter::DynamicOutputFormatter( const std::string& raw_output )
  : OutputFormatter()
{
  this->setRawString( raw_output );
}

// Make the keyword bold in the output
void DynamicOutputFormatter::boldKeyword( const std::string& keyword )
{
  this->formatKeyword<BoldTextFormat,DefaultTextColor,DefaultTextBackgroundColor>( keyword );
}

// Make the keyword italicized in the output
void DynamicOutputFormatter::italicizedKeyword( const std::string& keyword )
{
  this->formatKeyword<ItalicizedTextFormat,DefaultTextColor,DefaultTextBackgroundColor>( keyword );
}

// Make the keyword underlined in the output
void DynamicOutputFormatter::underlinedKeyword( const std::string& keyword )
{
  this->formatKeyword<UnderlinedTextFormat,DefaultTextColor,DefaultTextBackgroundColor>( keyword );
}

// Make the keyword bold-red in the output
void DynamicOutputFormatter::boldRedKeyword( const std::string& keyword )
{
  this->formatKeyword<BoldTextFormat,RedTextColor,DefaultTextBackgroundColor>( keyword );
}

// Make the keyword bold-cyan in the output
void DynamicOutputFormatter::boldCyanKeyword( const std::string& keyword )
{
  this->formatKeyword<BoldTextFormat,CyanTextColor,DefaultTextBackgroundColor>( keyword );
}

// Make the keyword bold-magenta in the output
void DynamicOutputFormatter::boldMagentaKeyword( const std::string& keyword )
{
  this->formatKeyword<BoldTextFormat,MagentaTextColor,DefaultTextBackgroundColor>( keyword );
}

// Make the keyword bold-white in the output
void DynamicOutputFormatter::boldWhiteKeyword( const std::string& keyword )
{
  this->formatKeyword<BoldTextFormat,WhiteTextColor,DefaultTextBackgroundColor>( keyword );
}

// Format the standard error message keywords in the output
/*! \details The standard error keywords are "error*" and "Error*". They will 
 * be formatted in bold-red.
 */
void DynamicOutputFormatter::formatStandardErrorKeywords()
{
  this->boldRedKeyword( "[E|e]rror:?" );
}

// Format the standard warning message keywords in the output
/*! \details The standard warning keywords are "warning*" and  "Warning*". They
 * will be formatted in bold-magenta.
 */
void DynamicOutputFormatter::formatStandardWarningKeywords()
{
  this->boldMagentaKeyword( "[W|w]arning:?" );
}

// Format the standard filename keywords in the output
/*! \details The standard filename keywords are "*.cpp" and "*.hpp". They
 * will be formatted in bold.
 */
void DynamicOutputFormatter::formatStandardFilenameKeywords()
{
  this->boldKeyword( "\\w+.[h|c]pp\\b" );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_DynamicOutputFormatter.cpp
//---------------------------------------------------------------------------//
