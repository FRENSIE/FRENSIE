//---------------------------------------------------------------------------//
//!
//! \file   Utility_OutputFormatter_def.hpp
//! \author Alex Robinson
//! \brief  The output formatter class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_OUTPUT_FORMATTER_DEF_HPP
#define UTILITY_OUTPUT_FORMATTER_DEF_HPP

// Std Lib Includes
#include <regex>
#include <iostream>

namespace Utility{

// Set the raw string (with formatting)
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy>
void OutputFormatter::setRawStringAndFormat( const std::string& raw_string )
{
  // Cache the raw string
  d_raw_string = raw_string;

  // Format the raw string
  d_formatted_string = this->formatString<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>( raw_string );
}

// Add format to raw string keyword
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy>
void OutputFormatter::addFormatToRawStringKeyword( const std::string& keyword )
{
  // Initialize the regex pattern
  std::regex regex_pattern( keyword );
  std::smatch match;

  std::string::const_iterator search_string_start_it =
    d_formatted_string.begin();
  
  std::string::const_iterator search_string_end_it =
    d_formatted_string.end();

  size_t true_start_loc = 0;

 try{
   while( std::regex_search( search_string_start_it,
                             search_string_end_it,
                             match,
                             regex_pattern ) )
    {
      // Get the formatted keyword
      std::string formatted_keyword = this->formatString<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>( match[0].str() );

      // Get the keyword location
      size_t keyword_front_loc = match.position( 0 )+true_start_loc;
      size_t keyword_back_loc = keyword_front_loc + match[0].str().size() - 1;
      size_t formatted_keyword_back_loc =
        keyword_front_loc + formatted_keyword.size() - 1;

      // Check if the keyword location can be formatted
      if( this->canKeywordLocationBeFormatted( keyword_front_loc,
                                               keyword_back_loc ) )
      {
        size_t match_string_size = match[0].str().size();
        
        d_formatted_string.replace( keyword_front_loc,
                                    match_string_size,
                                    formatted_keyword );

        this->addFormatLocation( keyword_front_loc,
                                 formatted_keyword_back_loc,
                                 formatted_keyword.size()-match_string_size );

        true_start_loc = formatted_keyword_back_loc + 1;
        
        search_string_start_it = d_formatted_string.begin() +
          true_start_loc;
      }
      else
      {
        true_start_loc = keyword_back_loc + 1;
        
        search_string_start_it += true_start_loc;
      }
      
      search_string_end_it = d_formatted_string.end();
    }
  }
  // If the pattern was bad we will ignore it
  catch( std::regex_error& error )
  { /* ... */ }
}

// Format the string
template<typename TextFormatPolicy,
           typename TextColorPolicy,
           typename TextBackgroundColorPolicy>
inline std::string
OutputFormatter::formatString( const std::string& string ) const
{
  std::string formatted_string = this->getBeginFormatSpecString();
  formatted_string += TextFormatPolicy::getTextFormat();
  formatted_string += this->getFormatKeyDeliminatorString();
  formatted_string += TextColorPolicy::getTextColor();
  formatted_string += this->getFormatKeyDeliminatorString();
  formatted_string += TextBackgroundColorPolicy::getTextBackgroundColor();
  formatted_string += this->getEndFormatSpecString();

  formatted_string += string;

  formatted_string += this->getResetFormatSpecString();

  return formatted_string;
}
  
} // end Utility namespace

#endif // end UTILITY_OUTPUT_FORMATTER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_OutputFormatter_def.hpp
//---------------------------------------------------------------------------//
