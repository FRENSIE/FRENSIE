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
/*! \details A regex pattern can be used as the keyword. Multiple calls
 * with the same keyword or multiple regex patterns that match the same
 * section of output will be ignored.
 */
void DynamicOutputFormatter::boldKeyword( const std::string& keyword )
{
  this->formatKeyword<BoldTextFormat,DefaultTextColor,DefaultTextBackgroundColor>( keyword );
}

// Make the keyword italicized in the output
/*! \details A regex pattern can be used as the keyword. Multiple calls
 * with the same keyword or multiple regex patterns that match the same
 * section of output will be ignored.
 */
void DynamicOutputFormatter::italicizedKeyword( const std::string& keyword )
{
  this->formatKeyword<ItalicizedTextFormat,DefaultTextColor,DefaultTextBackgroundColor>( keyword );
}

// Make the keyword underlined in the output
/*! \details A regex pattern can be used as the keyword. Multiple calls
 * with the same keyword or multiple regex patterns that match the same
 * section of output will be ignored.
 */
void DynamicOutputFormatter::underlinedKeyword( const std::string& keyword )
{
  this->formatKeyword<UnderlinedTextFormat,DefaultTextColor,DefaultTextBackgroundColor>( keyword );
}

// Make the keyword bold-red in the output
/*! \details A regex pattern can be used as the keyword. Multiple calls
 * with the same keyword or multiple regex patterns that match the same
 * section of output will be ignored.
 */
void DynamicOutputFormatter::boldRedKeyword( const std::string& keyword )
{
  this->formatKeyword<BoldTextFormat,RedTextColor,DefaultTextBackgroundColor>( keyword );
}

// Make the keyword bold-cyan in the output
/*! \details A regex pattern can be used as the keyword. Multiple calls
 * with the same keyword or multiple regex patterns that match the same
 * section of output will be ignored.
 */
void DynamicOutputFormatter::boldCyanKeyword( const std::string& keyword )
{
  this->formatKeyword<BoldTextFormat,CyanTextColor,DefaultTextBackgroundColor>( keyword );
}

// Make the keyword bold-magenta in the output
/*! \details A regex pattern can be used as the keyword. Multiple calls
 * with the same keyword or multiple regex patterns that match the same
 * section of output will be ignored.
 */
void DynamicOutputFormatter::boldMagentaKeyword( const std::string& keyword )
{
  this->formatKeyword<BoldTextFormat,MagentaTextColor,DefaultTextBackgroundColor>( keyword );
}

// Make the keyword bold-white in the output
/*! \details A regex pattern can be used as the keyword. Multiple calls
 * with the same keyword or multiple regex patterns that match the same
 * section of output will be ignored.
 */
void DynamicOutputFormatter::boldWhiteKeyword( const std::string& keyword )
{
  this->formatKeyword<BoldTextFormat,WhiteTextColor,DefaultTextBackgroundColor>( keyword );
}

// Format the standard error message keywords in the output
/*! \details The standard error keyword "\\s*[E|e]rror:". Any matches will 
 * be formatted in bold-red.
 */
void DynamicOutputFormatter::formatStandardErrorKeywords()
{
  this->boldRedKeyword( "\\s*[E|e]rror:" );
}

// Format the standard warning message keywords in the output
/*! \details The standard warning keyword is "\\s*[W|w]arning:". Any matches
 * will be formatted in bold-magenta.
 */
void DynamicOutputFormatter::formatStandardWarningKeywords()
{
  this->boldMagentaKeyword( "\\s*[W|w]arning:" );
}

// Format the standard note keywords in the output
/*! \details The standard note keyword is "\\s*[N|n]ote:". Any matches
 * will be formatted in bold-cyan.
 */
void DynamicOutputFormatter::formatStandardNoteKeywords()
{
  this->boldCyanKeyword( "\\s*[N|n]ote:" );
}

// Format the standard filename keywords in the output
/*! \details The standard filename keyword 
 * "[\\s/|\\s\\w][\\w|/]*\\.[h|c]pp:?\\d*:?". Any matches will be formatted in
 * bold.
 */
void DynamicOutputFormatter::formatStandardFilenameKeywords()
{
  this->boldKeyword( "[\\s/|\\s\\w][\\w|/]*\\.[h|c]pp:?\\d*:?" );
}

// Format the standard pass keywords in the output
/*! \details The standard pass keyword is "[P|p]ass(ed)?". Any matches
 * will be formatted in green.
 */
void DynamicOutputFormatter::formatStandardPassKeywords()
{
  this->formatKeyword<Utility::DefaultTextFormat,Utility::GreenTextColor,Utility::DefaultTextBackgroundColor>( "[P|p]ass(ed)?" );
}

// Format the standard fail keywords in the output
/*! \details The standard fail keyword is "[F|f]ail(ed)?". Any matches
 * will be formatted in red.
 */
void DynamicOutputFormatter::formatStandardFailKeywords()
{
  this->formatKeyword<Utility::DefaultTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor>( "[F|f]ail(ed)?" );
}

// Format the Teuchos unit test keywords in the output
void DynamicOutputFormatter::formatTeuchosUnitTestKeywords()
{
  this->formatStandardErrorKeywords();
  this->formatStandardWarningKeywords();
  this->formatStandardFilenameKeywords();
  this->formatStandardNoteKeywords();
  this->formatStandardPassKeywords();
  this->formatStandardFailKeywords();
  this->formatKeyword<Utility::DefaultTextFormat,Utility::GreenTextColor,Utility::DefaultTextBackgroundColor>( "(TEST\\s)?PASSED" );
  this->formatKeyword<Utility::DefaultTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor>( "(TEST\\s)?FAILED" );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_DynamicOutputFormatter.cpp
//---------------------------------------------------------------------------//
