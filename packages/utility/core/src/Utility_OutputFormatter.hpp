//---------------------------------------------------------------------------//
//!
//! \file   Utility_OutputFormatter.hpp
//! \author Alex Robinson
//! \brief  The output formatter class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_OUTPUT_FORMATTER_HPP
#define UTILITY_OUTPUT_FORMATTER_HPP

// Std Lib Includes
#include <string>
#include <utility>
#include <list>

// FRENSIE Includes
#include "Utility_OStreamableObject.hpp"

namespace Utility{

//! The output formatter class
class OutputFormatter : public OStreamableObject
{

public:

  //! Default constructor
  OutputFormatter();

  //! Destructor
  virtual ~OutputFormatter()
  { /* ... */ }

  //! Place the formatted string in the output stream
  void toStream( std::ostream& os ) const;

  //! Place the string in the output stream
  void toStream( std::ostream& os, const bool use_formatted_output ) const;

  //! Get the formatted string
  const std::string& getFormattedOutput() const;

  //! Get the raw output
  const std::string& getRawOutput() const;

protected:

  //! Set the raw string (no formatting)
  void setRawString( const std::string& raw_string );

  //! Set the raw string (with formatting)
  template<typename TextFormatPolicy,
           typename TextColorPolicy,
           typename TextBackgroundColorPolicy>
  void setRawStringAndFormat( const std::string& raw_string );

  //! Add format to raw string keyword
  template<typename TextFormatPolicy,
           typename TextColorPolicy,
           typename TextBackgroundColorPolicy>
  void addFormatToRawStringKeyword( const std::string& keyword );
  
private:

  // Compare two format locations
  static bool compareFormatLocations( const std::pair<size_t,size_t>& loc_a,
                                      const std::pair<size_t,size_t>& loc_b );

  // Check if a keyword location can be formatted
  bool canKeywordLocationBeFormatted( const size_t keyword_front_index,
                                      const size_t keyword_back_index ) const;

  // Add a format location
  void addFormatLocation( const size_t keyword_front_index,
                          const size_t keyword_back_index,
                          const size_t shift );
  
  // Format the string
  template<typename TextFormatPolicy,
           typename TextColorPolicy,
           typename TextBackgroundColorPolicy>
  std::string formatString( const std::string& string ) const;

  // Return the begin format spec string
  std::string getBeginFormatSpecString() const;

  // Return the format key deliminator string
  std::string getFormatKeyDeliminatorString() const;

  // Return the end format spec string
  std::string getEndFormatSpecString() const;

  // Return the reset format spec string
  std::string getResetFormatSpecString() const;

  // Check if the formatted string should be placed in the stream
  bool useFormattedString( std::ostream& os ) const;

  // The raw string
  std::string d_raw_string;

  // The formatted string
  std::string d_formatted_string;

  // The format locations
  std::list<std::pair<size_t,size_t> > d_format_locations;
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_OutputFormatter_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_OUTPUT_FORMATTER_HPP

//---------------------------------------------------------------------------//
// end Utility_OutputFormatter.hpp
//---------------------------------------------------------------------------//
