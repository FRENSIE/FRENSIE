//---------------------------------------------------------------------------//
//!
//! \file   Utility_StandardOutputFormatter.hpp
//! \author Alex Robinson
//! \brief  The standard output formatter class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STANDARD_OUTPUT_FORMATTER_HPP
#define UTILITY_STANDARD_OUTPUT_FORMATTER_HPP

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "Utility_OutputFormatter.hpp"
#include "Utility_TextFormatPolicy.hpp"
#include "Utility_TextColorPolicy.hpp"
#include "Utility_TextBackgroundColorPolicy.hpp"

namespace Utility{

//! The standard output formatter class
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy=DefaultTextBackgroundColor>
class StandardOutputFormatter : public OutputFormatter
{
  
public:

  //! General constructor
  template<typename T>
  StandardOutputFormatter( const T& raw_string_contents );

  //! String constructor
  StandardOutputFormatter( const std::string& raw_string_contents );

  //! C-string constructor
  StandardOutputFormatter( const char* raw_string_contents );

  //! Double constructor
  StandardOutputFormatter( const double& raw_string_contents,
                           const unsigned precision = 18u );

  //! Destructor
  ~StandardOutputFormatter()
  { /* ... */ }

protected:

  // Get the text format
  std::string getTextFormat() const;

  // Get the text color
  std::string getTextColor() const;

  // Get the text background color
  std::string getTextBackgroundColor() const;
};

//! Bold formatter
typedef StandardOutputFormatter<BoldTextFormat,DefaultTextColor,DefaultTextBackgroundColor> Bold;

//! Italicized formatter
typedef StandardOutputFormatter<ItalicizedTextFormat,DefaultTextColor,DefaultTextBackgroundColor> Italicized;

//! Underlined formatter
typedef StandardOutputFormatter<UnderlinedTextFormat,DefaultTextColor,DefaultTextBackgroundColor> Underlined;

//! Red formatter
typedef StandardOutputFormatter<DefaultTextFormat,RedTextColor,DefaultTextBackgroundColor> Red;

//! Cyan formatter
typedef StandardOutputFormatter<DefaultTextFormat,CyanTextColor,DefaultTextBackgroundColor> Cyan;

//! Magenta formatter
typedef StandardOutputFormatter<DefaultTextFormat,MagentaTextColor,DefaultTextBackgroundColor> Magenta;

//! Bold-white formatter
typedef StandardOutputFormatter<BoldTextFormat,WhiteTextColor,DefaultTextBackgroundColor> BoldWhite;
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_StandardOutputFormatter_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_STANDARD_OUTPUT_FORMATTER_HPP

//---------------------------------------------------------------------------//
// end Utility_StandardOutputFormatter.hpp
//---------------------------------------------------------------------------//
