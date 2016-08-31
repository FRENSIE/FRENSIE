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

  //! Make the keyword bold-red in the output
  void boldRedKeyword( const std::string& keyword );

  //! Make the keyword bold-cyan in the output
  void boldCyanKeyword( const std::string& keyword );

  //! Make the keyword bold-magenta in the output
  void boldMagentaKeyword( const std::string& keyword );

  //! Make the keyword bold-white in the output
  void boldWhiteKeyword( const std::string& keyword );

  //! Format the standard error message keywords in the output
  void formatStandardErrorKeywords();

  //! Format the standard warning message keywords in the output
  void formatStandardWarningKeywords();

  //! Format the standard filename keywords in the output
  void formatStandardFilenameKeywords();
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
