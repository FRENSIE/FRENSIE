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

// FRENSIE Includes
#include "Utility_PrintableObject.hpp"

namespace Utility{

//! The output formatter class
class OutputFormatter : public PrintableObject
{

public:

  //! Default constructor
  OutputFormatter();

  //! Destructor
  virtual ~OutputFormatter()
  { /* ... */ }

  //! Place the formatted string in the output stream
  void print( std::ostream& os ) const;

protected:

  //! Get the text format
  virtual std::string getTextFormat() const = 0;

  //! Get the text color
  virtual std::string getTextColor() const = 0;

  //! Get the text background color
  virtual std::string getTextBackgroundColor() const = 0;
  
  //! Format the raw string
  void formatRawString( const std::string& raw_string );
  
private:

  // Check if the formatted string should be placed in the stream
  bool useFormattedString( std::ostream& os ) const;

  // The raw string
  std::string d_raw_string;

  // The formatted string
  std::string d_formatted_string;
};

} // end Utility namespace

#endif // end UTILITY_OUTPUT_FORMATTER_HPP

//---------------------------------------------------------------------------//
// end Utility_OutputFormatter.hpp
//---------------------------------------------------------------------------//
