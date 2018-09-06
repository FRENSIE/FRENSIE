//---------------------------------------------------------------------------//
//!
//! \file   Utility_OutputFormatterFactory.hpp
//! \author Alex Robinson
//! \brief  The output formatter factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_OUTPUT_FORMATTER_FACTORY_HPP
#define UTILITY_OUTPUT_FORMATTER_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_OutputFormatter.hpp"

namespace Utility{

//! The output formatter factory class
class OutputFormatterFactory
{

public:

  //! Default constructor
  OutputFormatterFactory()
  { /* ... */ }

  //! Destructor
  virtual ~OutputFormatterFactory()
  { /* ... */ }

  //! Create an output formatter
  virtual std::shared_ptr<const OutputFormatter> createOutputFormatter(
                                     const std::string& raw_output ) const = 0;
};
  
} // end Utility namespace

#endif // end UTILITY_OUTPUT_FORMATTER_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Utility_OutputFormatterFactory.hpp
//---------------------------------------------------------------------------//
