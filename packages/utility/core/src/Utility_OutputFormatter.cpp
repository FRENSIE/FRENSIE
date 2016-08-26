//---------------------------------------------------------------------------//
//!
//! \file   Utility_OutputFormatter.cpp
//! \author Alex Robinson
//! \brief  The output formatter class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Utility_OutputFormatter.hpp"
#include "FRENSIE_tty_format_config.hpp"

namespace Utility{

// Default constructor
OutputFormatter::OutputFormatter()
  : d_formatted_string()
{ /* ... */ }

// Place the formatted string in the output stream
/*! \details Even if your system/terminal supports TTY formatted outputs the
 * requested ostream object may not support it. This print method will check
 * the stream object for compatibility with TTY formatting and use either the
 * raw string or the formatted string depending on what it detects.
 */
void OutputFormatter::print( std::ostream& os ) const
{
  if( this->useFormattedString( os ) )
    this->print( os, true );
  else
    this->print( os, false );
}

// Place the string in the output stream
/*! \details This method should be rarely be used directly as it does not
 * check if the ostream object supports TTY formatted outputs.
 */
void OutputFormatter::print( std::ostream& os,
                             const bool use_formatted_output ) const
{
  if( use_formatted_output )
    os << d_formatted_string;
  else
    os << d_raw_string;
}

// Get the formatted string
const std::string& OutputFormatter::getFormattedOutput() const
{
  return d_formatted_string;
}

// Get the raw output
const std::string& OutputFormatter::getRawOutput() const
{
  return d_raw_string;
}

// Format the raw string
void OutputFormatter::formatRawString( const std::string& raw_string )
{
  // Cache the raw string
  d_raw_string = raw_string;

  // Format the raw string
  d_formatted_string = BEGIN_FORMAT_SPEC;
  d_formatted_string += this->getTextFormat();
  d_formatted_string += FORMAT_KEY_DELIMINATOR;
  d_formatted_string += this->getTextColor();
  d_formatted_string += FORMAT_KEY_DELIMINATOR;
  d_formatted_string += this->getTextBackgroundColor();
  d_formatted_string += END_FORMAT_SPEC;

  d_formatted_string += raw_string;

  d_formatted_string += RESET_FORMAT_SPEC;
}

// Check if the formatted string should be placed in the stream
bool OutputFormatter::useFormattedString( std::ostream& os ) const
{
#ifdef TTY_FORMATTING_SUPPORTED
  if( os.rdbuf() == std::cout.rdbuf() )
    return isatty(1);
  else if( os.rdbuf() == std::cerr.rdbuf() )
    return isatty(2);
  else
    return false;
#else
  return false;
#endif 
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_OutputFormatter.cpp
//---------------------------------------------------------------------------//
