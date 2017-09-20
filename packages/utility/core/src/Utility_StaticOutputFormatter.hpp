//---------------------------------------------------------------------------//
//!
//! \file   Utility_StaticOutputFormatter.hpp
//! \author Alex Robinson
//! \brief  The static output formatter class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STATIC_OUTPUT_FORMATTER_HPP
#define UTILITY_STATIC_OUTPUT_FORMATTER_HPP

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "Utility_OutputFormatter.hpp"
#include "Utility_TextFormatPolicy.hpp"
#include "Utility_TextColorPolicy.hpp"
#include "Utility_TextBackgroundColorPolicy.hpp"

namespace Utility{

//! The static output formatter class
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy=DefaultTextBackgroundColor>
class StaticOutputFormatter : public OutputFormatter
{
  
public:

  //! General constructor
  template<typename T>
  StaticOutputFormatter( const T& raw_string_contents );

  //! Destructor
  ~StaticOutputFormatter()
  { /* ... */ }
};

//! Default formatter
typedef StaticOutputFormatter<DefaultTextFormat,DefaultTextColor,DefaultTextBackgroundColor> Default;

//! Bold formatter
typedef StaticOutputFormatter<BoldTextFormat,DefaultTextColor,DefaultTextBackgroundColor> Bold;

//! Italicized formatter
typedef StaticOutputFormatter<ItalicizedTextFormat,DefaultTextColor,DefaultTextBackgroundColor> Italicized;

//! Underlined formatter
typedef StaticOutputFormatter<UnderlinedTextFormat,DefaultTextColor,DefaultTextBackgroundColor> Underlined;

//! Red formatter
typedef StaticOutputFormatter<DefaultTextFormat,RedTextColor,DefaultTextBackgroundColor> Red;

//! Bold-red formatter
typedef StaticOutputFormatter<BoldTextFormat,RedTextColor,DefaultTextBackgroundColor> BoldRed;

//! Green formatter
typedef StaticOutputFormatter<DefaultTextFormat,GreenTextColor,DefaultTextBackgroundColor> Green;

//! Bold-green formatter
typedef StaticOutputFormatter<BoldTextFormat,GreenTextColor,DefaultTextBackgroundColor> BoldGreen;

//! Yellow formatter
typedef StaticOutputFormatter<DefaultTextFormat,YellowTextColor,DefaultTextBackgroundColor> Yellow;

//! Bold-yellow formatter
typedef StaticOutputFormatter<BoldTextFormat,YellowTextColor,DefaultTextBackgroundColor> BoldYellow;

//! Cyan formatter
typedef StaticOutputFormatter<DefaultTextFormat,CyanTextColor,DefaultTextBackgroundColor> Cyan;  

//! Bold-cyan formatter
typedef StaticOutputFormatter<BoldTextFormat,CyanTextColor,DefaultTextBackgroundColor> BoldCyan;

//! Magenta formatter
typedef StaticOutputFormatter<DefaultTextFormat,MagentaTextColor,DefaultTextBackgroundColor> Magenta;

//! Bold-magenta formatter
typedef StaticOutputFormatter<BoldTextFormat,MagentaTextColor,DefaultTextBackgroundColor> BoldMagenta;

//! Bold-white formatter
typedef StaticOutputFormatter<BoldTextFormat,WhiteTextColor,DefaultTextBackgroundColor> BoldWhite;
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_StaticOutputFormatter_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_STATIC_OUTPUT_FORMATTER_HPP

//---------------------------------------------------------------------------//
// end Utility_StaticOutputFormatter.hpp
//---------------------------------------------------------------------------//
