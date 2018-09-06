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

#ifdef TTY_FORMATTING_SUPPORTED
// We need to cache the cout and cerr stream buffers right away in case their
// buffers get redirected at some point
static const std::streambuf* cout_streambuf = std::cout.rdbuf();
static const std::streambuf* cerr_streambuf = std::cerr.rdbuf();
#endif // end TTY_FORMATTING_SUPPORTED

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
void OutputFormatter::toStream( std::ostream& os ) const
{
  if( this->useFormattedString( os ) )
    this->toStream( os, true );
  else
    this->toStream( os, false );
}

// Place the string in the output stream
/*! \details This method should be rarely be used directly as it does not
 * check if the ostream object supports TTY formatted outputs.
 */
void OutputFormatter::toStream( std::ostream& os,
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

// Set the raw string (no formatting)
void OutputFormatter::setRawString( const std::string& raw_string )
{
  d_formatted_string = raw_string;
  d_raw_string = raw_string;
}

// Compare two format locations
bool OutputFormatter::compareFormatLocations(
                                        const std::pair<size_t,size_t>& loc_a,
                                        const std::pair<size_t,size_t>& loc_b )
{
  return loc_a.first < loc_b.first;
}

// Check if a keyword location can be formatted
bool OutputFormatter::canKeywordLocationBeFormatted(
                                        const size_t keyword_front_index,
                                        const size_t keyword_back_index ) const
{
  std::list<std::pair<size_t,size_t> >::const_iterator format_loc_it =
    d_format_locations.begin();

  bool valid_format_location = true;
  
  while( format_loc_it != d_format_locations.end() )
  {
    if( format_loc_it->first <= keyword_front_index &&
        format_loc_it->second >= keyword_back_index )
    {
      valid_format_location = false;

      break;
    }
    else if( format_loc_it->first <= keyword_front_index &&
             format_loc_it->second >= keyword_front_index )
    {
      valid_format_location = false;
      
      break;
    }

    ++format_loc_it;
  }
  
  return valid_format_location;
}

// Add a format location
void OutputFormatter::addFormatLocation( const size_t keyword_front_index,
                                         const size_t keyword_back_index,
                                         const size_t shift )
{
  // Find where the new format location should be placed
  std::list<std::pair<size_t,size_t> >::iterator format_loc_it =
    d_format_locations.begin();

  while( format_loc_it != d_format_locations.end() )
  {
    if( format_loc_it->first > keyword_front_index )
      break;

    ++format_loc_it;
  }

  // Add the new format location to the list
  std::list<std::pair<size_t,size_t> >::iterator update_loc_it =
    format_loc_it = d_format_locations.insert(
                   format_loc_it,
                   std::make_pair( keyword_front_index, keyword_back_index ) );

  ++update_loc_it;

  // Shift all locations that occur after the new location
  while( update_loc_it != d_format_locations.end() )
  {
    update_loc_it->first += shift;
    update_loc_it->second += shift;

    ++update_loc_it;
  }
}

// Return the begin format spec string
std::string OutputFormatter::getBeginFormatSpecString() const
{
  return BEGIN_FORMAT_SPEC;
}

// Return the format key deliminator string
std::string OutputFormatter::getFormatKeyDeliminatorString() const
{
  return FORMAT_KEY_DELIMINATOR;
}

// Return the end format spec string
std::string OutputFormatter::getEndFormatSpecString() const
{
  return END_FORMAT_SPEC;
}

// Return the reset format spec string
std::string OutputFormatter::getResetFormatSpecString() const
{
  return RESET_FORMAT_SPEC;
}

// Check if the formatted string should be placed in the stream
bool OutputFormatter::useFormattedString( std::ostream& os ) const
{
#ifdef TTY_FORMATTING_SUPPORTED
  if( os.rdbuf() == cout_streambuf )
    return isatty(1);
  else if( os.rdbuf() == cerr_streambuf )
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
