//---------------------------------------------------------------------------//
//!
//! \file   Utility_DynamicOutputFormatter.cpp
//! \author Alex Robinson
//! \brief  Dynamic output formatter definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_DynamicOutputFormatter.hpp"
#include "Utility_LoggingStaticConstants.hpp"

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

// Make the keyword red in the output
/*! \details A regex pattern can be used as the keyword. Multiple calls
 * with the same keyword or multiple regex patterns that match the same
 * section of output will be ignored.
 */
void DynamicOutputFormatter::redKeyword( const std::string& keyword )
{
  this->formatKeyword<DefaultTextFormat,RedTextColor,DefaultTextBackgroundColor>( keyword );
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

// Make the keyword green in the output
/*! \details A regex pattern can be used as the keyword. Multiple calls
 * with the same keyword or multiple regex patterns that match the same
 * section of output will be ignored.
 */
void DynamicOutputFormatter::greenKeyword( const std::string& keyword )
{
  this->formatKeyword<DefaultTextFormat,GreenTextColor,DefaultTextBackgroundColor>( keyword );
}

// Make the keyword bold-green in the output
/*! \details A regex pattern can be used as the keyword. Multiple calls
 * with the same keyword or multiple regex patterns that match the same
 * section of output will be ignored.
 */
void DynamicOutputFormatter::boldGreenKeyword( const std::string& keyword )
{
  this->formatKeyword<BoldTextFormat,GreenTextColor,DefaultTextBackgroundColor>( keyword );
}

// Make the keyword yellow in the output
/*! \details A regex pattern can be used as the keyword. Multiple calls
 * with the same keyword or multiple regex patterns that match the same
 * section of output will be ignored.
 */
void DynamicOutputFormatter::yellowKeyword( const std::string& keyword )
{
  this->formatKeyword<DefaultTextFormat,YellowTextColor,DefaultTextBackgroundColor>( keyword );
}

// Make the keyword bold-yellow in the output
/*! \details A regex pattern can be used as the keyword. Multiple calls
 * with the same keyword or multiple regex patterns that match the same
 * section of output will be ignored.
 */
void DynamicOutputFormatter::boldYellowKeyword( const std::string& keyword )
{
  this->formatKeyword<BoldTextFormat,YellowTextColor,DefaultTextBackgroundColor>( keyword );
}

// Make the keyword cyan in the output
/*! \details A regex pattern can be used as the keyword. Multiple calls
 * with the same keyword or multiple regex patterns that match the same
 * section of output will be ignored.
 */
void DynamicOutputFormatter::cyanKeyword( const std::string& keyword )
{
  this->formatKeyword<DefaultTextFormat,CyanTextColor,DefaultTextBackgroundColor>( keyword );
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


// Make the keyword magenta in the output
/*! \details A regex pattern can be used as the keyword. Multiple calls
 * with the same keyword or multiple regex patterns that match the same
 * section of output will be ignored.
 */
void DynamicOutputFormatter::magentaKeyword( const std::string& keyword )
{
  this->formatKeyword<DefaultTextFormat,MagentaTextColor,DefaultTextBackgroundColor>( keyword );
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
/*! \details The standard error keyword FRENSIE_LOG_ERROR_MSG_REGEX. Any 
 * matches will be formatted in bold-red.
 */
void DynamicOutputFormatter::formatStandardErrorKeywords()
{
  this->boldRedKeyword( FRENSIE_LOG_ERROR_MSG_REGEX );
}

// Format the extended testing error keywords in the output
/*! \details The error keyword "(\\s*|\\s*\\S+)[E|e]rror:". Note that the 
 * "(\\s*|\\s*\\S+)" section allows matches such as "My Error",
 * "std::logic_error:", or "FatalError:" in addition to the standard "Error:"
 * and "error:". Any matches will be formatted in bold-red.
 */
void DynamicOutputFormatter::formatExtraErrorKeywords()
{
  this->boldRedKeyword( "(\\s*|\\s*\\S+)[E|e]rror:" );
}

// Format the standard warning message keywords in the output
/*! \details The standard warning keyword is FRENSIE_LOG_WARNING_MSG_REGEX. Any
 * matches will be formatted in bold-magenta.
 */
void DynamicOutputFormatter::formatStandardWarningKeywords()
{
  this->boldMagentaKeyword( FRENSIE_LOG_WARNING_MSG_REGEX );
}

// Format the standard note keywords in the output
/*! \details The standard note keyword is "\\s*[N|n]ote:". Any matches
 * will be formatted in bold-cyan.
 */
void DynamicOutputFormatter::formatStandardNoteKeywords()
{
  this->boldCyanKeyword( "\\s*[N|n]ote:" );
}

// Format the extra message keywords in the output
/*! \details The extra message keyword is ".*Msg:". Any matches will be
 * formatted in bold-cyan.
 */
void DynamicOutputFormatter::formatExtraMessageKeywords()
{
  this->boldCyanKeyword( "\\n[\\w ]*Msg:" );
}

// Format the standard location keywords in the output
/*! \details The standard location keyword is FRENSIE_LOG_LOCATION_MSG. Any 
 * matches will be formatted in bold-cyan.
 */
void DynamicOutputFormatter::formatStandardLocationKeywords()
{
  this->boldCyanKeyword( FRENSIE_LOG_LOCATION_MSG_REGEX );
}

// Format the standard stack keywords in the output
/*! \details The standard stack keyword is FRENSIE_LOG_STACK_MSG_REGEX. Any 
 * matches will be formatted in bold-cyan.
 */
void DynamicOutputFormatter::formatStandardStackKeywords()
{
  this->boldCyanKeyword( FRENSIE_LOG_STACK_MSG_REGEX );
}

// Format the standard stack depth deliminator keywords in the output
/*! \details The standard stack deliminator keyword is 
 * FRENSIE_LOG_STACK_DELIMINATOR_REGEX. Any matches will be formatted in 
 * bold-cyan.
 */
void DynamicOutputFormatter::formatStandardStackDeliminatorKeywords()
{
  this->boldCyanKeyword( FRENSIE_LOG_STACK_DELIMINATOR_REGEX );
}

// Format the standard arrow keywords in the output
/*! \details The standard arrow keyword is FRENSIE_LOG_ARROW_SEP_REGEX. Any 
 * matches will be formatted in bold-cyan.
 */
void DynamicOutputFormatter::formatStandardArrowKeywords()
{
  this->boldCyanKeyword( FRENSIE_LOG_ARROW_SEP_REGEX );
}

// Format the standard exception type keywords in the output
/*! \details The standard exception type keyword is 
 * FRENSIE_LOG_EXCEPTION_TYPE_MSG_REGEX. Any matches will be formatted in 
 * bold-cyan.
 */
void DynamicOutputFormatter::formatStandardExceptionTypeKeywords()
{
  this->boldCyanKeyword( FRENSIE_LOG_EXCEPTION_TYPE_MSG_REGEX );
}

// Format the standard throw test evaluation true keywords in the output
/*! \details The standard throw test evaluation true keyword is
 * FRENSIE_LOG_THROW_TEST_THAT_EVALUATED_TO_TRUE_MSG_REGEX. Any matches will be
 * formatted in bold-cyan.
 */ 
void DynamicOutputFormatter::formatStandardThrowTestEvaluatedTrueKeywords()
{
  this->boldCyanKeyword( FRENSIE_LOG_THROW_TEST_THAT_EVALUATED_TO_TRUE_MSG_REGEX );
}

// Format the standard beginning nested errors keywords in the output
/*! \details The standard beginning nested errors keyword is
 * FRENSIE_LOG_BEGINNING_NESTED_ERRORS_MSG_REGEX. Any matches will be formatted
 * in bold-cyan.
 */
void DynamicOutputFormatter::formatStandardBeginningNestedErrorsKeywords()
{
  this->underlinedKeyword( FRENSIE_LOG_BEGINNING_NESTED_ERRORS_MSG_REGEX );
}

// Format the standard filename keywords in the output
/*! \details The standard filename keyword 
 * "[\\s/|\\s\\w][\\w|/]*\\.[h|c]ppFRENSIE_LOG_FILE_LINE_SEP?\\d*:?". Any 
 * matches will be formatted in bold.
 */
void DynamicOutputFormatter::formatStandardFilenameKeywords()
{
  this->boldKeyword( "[\\s/|\\s\\w][\\w|/]*\\.[h|c]pp" FRENSIE_LOG_FILE_LINE_SEP "?\\d*:?" );
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

// Format the error log keywords
void DynamicOutputFormatter::formatErrorLogKeywords()
{
  this->formatStandardErrorKeywords();
  this->formatStandardLocationKeywords();
  this->formatStandardStackKeywords();
  this->formatStandardStackDeliminatorKeywords();
  this->formatStandardArrowKeywords();
  this->formatStandardExceptionTypeKeywords();
  this->formatStandardThrowTestEvaluatedTrueKeywords();
  this->formatStandardBeginningNestedErrorsKeywords();
  this->formatStandardFilenameKeywords();
  this->formatExtraMessageKeywords();
}

// Format the warning log keywords
void DynamicOutputFormatter::formatWarningLogKeywords()
{
  this->formatStandardWarningKeywords();
  this->formatStandardLocationKeywords();
  this->formatStandardFilenameKeywords();
}

// Format the Teuchos unit test keywords in the output
void DynamicOutputFormatter::formatTeuchosUnitTestKeywords()
{
  this->formatUnitTestKeywords();
}

// Format the Teuchos unit test keywords in the output
void DynamicOutputFormatter::formatUnitTestKeywords()
{
  this->formatStandardErrorKeywords();
  this->formatStandardWarningKeywords();
  this->formatStandardLocationKeywords();
  this->formatStandardStackKeywords();
  this->formatStandardStackDeliminatorKeywords();
  this->formatStandardArrowKeywords();
  this->formatStandardExceptionTypeKeywords();
  this->formatStandardThrowTestEvaluatedTrueKeywords();
  this->formatStandardBeginningNestedErrorsKeywords();
  this->formatStandardFilenameKeywords();
  this->formatExtraMessageKeywords();

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
