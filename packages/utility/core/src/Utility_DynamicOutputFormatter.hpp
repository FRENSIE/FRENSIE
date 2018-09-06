//---------------------------------------------------------------------------//
//!
//! \file   Utility_DynamicOutputFormatter.hpp
//! \author Alex Robinson
//! \brief  Dynamic output formatter declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DYNAMIC_OUTPUT_FORMATTER_HPP
#define UTILITY_DYNAMIC_OUTPUT_FORMATTER_HPP

// Std Lib Includes
#include <string>
#include <set>

// FRENSIE Includes
#include "Utility_OutputFormatter.hpp"
#include "Utility_TextFormatPolicy.hpp"
#include "Utility_TextColorPolicy.hpp"
#include "Utility_TextBackgroundColorPolicy.hpp"

namespace Utility{

//! The dynamic output formatter class
class DynamicOutputFormatter : public OutputFormatter
{

public:

  //! Constructor
  DynamicOutputFormatter( const std::string& raw_output );

  //! Destructor
  ~DynamicOutputFormatter()
  { /* ... */ }

  //! Format a keyword in the output
  template<typename TextFormatPolicy,
           typename TextColorPolicy,
           typename TextBackgroundColorPolicy>
  void formatKeyword( const std::string& keyword );

  //! Make the keyword bold in the output
  void boldKeyword( const std::string& keyword );

  //! Make the keyword italicized in the output
  void italicizedKeyword( const std::string& keyword );

  //! Make the keyword underlined in the output
  void underlinedKeyword( const std::string& keyword );

  //! Make the keyword red in the output
  void redKeyword( const std::string& keyword );
  
  //! Make the keyword bold-red in the output
  void boldRedKeyword( const std::string& keyword );

  //! Make the keyword green in the output
  void greenKeyword( const std::string& keyword );
  
  //! Make the keyword bold-green in the output
  void boldGreenKeyword( const std::string& keyword );

  //! Make the keyword yellow in the output
  void yellowKeyword( const std::string& keyword );
  
  //! Make the keyword bold-yellow in the output
  void boldYellowKeyword( const std::string& keyword );

  //! Make the keyword cyan in the output
  void cyanKeyword( const std::string& keyword );
  
  //! Make the keyword bold-cyan in the output
  void boldCyanKeyword( const std::string& keyword );

  //! Make the keyword magenta in the output
  void magentaKeyword( const std::string& keyword );
  
  //! Make the keyword bold-magenta in the output
  void boldMagentaKeyword( const std::string& keyword );

  //! Make the keyword bold-white in the output
  void boldWhiteKeyword( const std::string& keyword );

  //! Format the standard error message keywords in the output
  void formatStandardErrorKeywords();

  //! Format the extra error keywords in the output
  void formatExtraErrorKeywords();

  //! Format the standard warning message keywords in the output
  void formatStandardWarningKeywords();

  //! Format the standard note keywords in the output
  void formatStandardNoteKeywords();

  //! Format the extra message keywords in the output
  void formatExtraMessageKeywords();

  //! Format the standard location keywords in the output
  void formatStandardLocationKeywords();

  //! Format the standard stack keywords in the output
  void formatStandardStackKeywords();

  //! Format the standard stack depth deliminator keywords in the output
  void formatStandardStackDeliminatorKeywords();

  //! Format the standard arrow keywords in the output
  void formatStandardArrowKeywords();

  //! Format the standard exception type keywords in the output
  void formatStandardExceptionTypeKeywords();

  //! Format the standard throw test evaluation true keywords in the output
  void formatStandardThrowTestEvaluatedTrueKeywords();

  //! Format the standard beginning nested errors keywords in the output
  void formatStandardBeginningNestedErrorsKeywords();

  //! Format the standard filename keywords in the output
  void formatStandardFilenameKeywords();

  //! Format the standard pass keywords in the output
  void formatStandardPassKeywords();

  //! Format the standard fail keywords in the output
  void formatStandardFailKeywords();

  //! Format the error log keywords
  void formatErrorLogKeywords();

  //! Format the warning log keywords
  void formatWarningLogKeywords();

  //! Format the Teuchos unit test keywords in the output
  void formatTeuchosUnitTestKeywords();

  //! Format the unit test keywords in the output
  void formatUnitTestKeywords();
};

// Format a keyword in the output
/*! \details A regex pattern can be used as the keyword. Multiple calls
 * with the same keyword or multiple regex patterns that match the same
 * section of output will be ignored.
 */
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy>
inline void DynamicOutputFormatter::formatKeyword( const std::string& keyword )
{
  this->addFormatToRawStringKeyword<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>( keyword );
}
  
} // end Utility namespace

#endif // end UTILITY_DYNAMIC_OUTPUT_FORMATTER_HPP

//---------------------------------------------------------------------------//
// end Utility_DynamicOutputFormatter.hpp
//---------------------------------------------------------------------------//
