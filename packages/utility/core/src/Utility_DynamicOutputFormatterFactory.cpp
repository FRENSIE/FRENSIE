//---------------------------------------------------------------------------//
//!
//! \file   Utility_DynamicOutputFormatterFactory.cpp
//! \author Alex Robinson
//! \brief  The dynamic output formatter factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_DynamicOutputFormatterFactory.hpp"

namespace Utility{

// Constructor
DynamicOutputFormatterFactory::DynamicOutputFormatterFactory(
                                FormattingFunctionArray& formatting_functions )
  : d_formatting_functions( formatting_functions )
{ /* ... */ }

// Create an output formatter
std::shared_ptr<const OutputFormatter>
DynamicOutputFormatterFactory::createOutputFormatter(
                                          const std::string& raw_output ) const
{
  // Create a new dynamic output formatter
  DynamicOutputFormatter* formatter = new DynamicOutputFormatter( raw_output );

  for( size_t i = 0; i < d_formatting_functions.size(); ++i )
    d_formatting_functions[i]( *formatter );

  return std::shared_ptr<const OutputFormatter>( formatter );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_DynamicOutputFormatterFactory.cpp
//---------------------------------------------------------------------------//
