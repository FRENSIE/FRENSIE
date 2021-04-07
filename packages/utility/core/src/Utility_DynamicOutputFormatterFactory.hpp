//---------------------------------------------------------------------------//
//!
//! \file   Utility_DynamicOutputFormatterFactory.hpp
//! \author Alex Robinson
//! \brief  The dynamic output formatter factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DYNAMIC_OUTPUT_FORMATTER_FACTORY_HPP
#define UTILITY_DYNAMIC_OUTPUT_FORMATTER_FACTORY_HPP

// Std Lib Includes
#include <vector>
#include <functional>

// FRENSIE Includes
#include "Utility_OutputFormatterFactory.hpp"
#include "Utility_DynamicOutputFormatter.hpp"

namespace Utility{

//! The dynamic output formatter factory class
class DynamicOutputFormatterFactory : public OutputFormatterFactory
{

public:

  //! The formatting function type
  typedef std::function<void(DynamicOutputFormatter&)> FormattingFunction;

  //! The formatting function array
  typedef std::vector<FormattingFunction> FormattingFunctionArray;

  //! Constructor
  DynamicOutputFormatterFactory( FormattingFunctionArray& formatting_functions );

  //! Destructor
  ~DynamicOutputFormatterFactory()
  { /* ... */ }

  //! Create an output formatter
  std::shared_ptr<const OutputFormatter> createOutputFormatter(
                                const std::string& raw_output ) const override;

private:

  // The formatting functions
  FormattingFunctionArray d_formatting_functions;
};
  
} // end Utility namespace

#endif // end UTILITY_DYNAMIC_OUTPUT_FORMATTER_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Utility_DynamicOutputFormatterFactory.hpp
//---------------------------------------------------------------------------//
