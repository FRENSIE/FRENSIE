//---------------------------------------------------------------------------//
//!
//! \file   Utility_StaticOutputFormatterFactory.hpp
//! \author Alex Robinson
//! \brief  The static output formatter factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STATIC_OUTPUT_FORMATTER_FACTORY_HPP
#define UTILITY_STATIC_OUTPUT_FORMATTER_FACTORY_HPP

// FRENSIE Includes
#include "Utility_OutputFormatterFactory.hpp"
#include "Utility_StaticOutputFormatter.hpp"

namespace Utility{

//! The static output formatter factory class
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy=DefaultTextBackgroundColor>
class StaticOutputFormatterFactory : public OutputFormatterFactory
{

public:

  //! Default constructor
  StaticOutputFormatterFactory()
  { /* ... */ }

  //! Destructor
  ~StaticOutputFormatterFactory()
  { /* ... */ }

  //! Create an output formatter
  std::shared_ptr<const OutputFormatter> createOutputFormatter(
                                const std::string& raw_output ) const override;
};

// Create an output formatter
template<typename TextFormatPolicy,
         typename TextColorPolicy,
         typename TextBackgroundColorPolicy>
inline std::shared_ptr<const OutputFormatter>
StaticOutputFormatterFactory<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>::createOutputFormatter(
                                          const std::string& raw_output ) const
{
  return std::shared_ptr<const OutputFormatter>( new StaticOutputFormatter<TextFormatPolicy,TextColorPolicy,TextBackgroundColorPolicy>( raw_output ) );
}
  
} // end Utility namespace

#endif // end UTILITY_STATIC_OUTPUT_FORMATTER_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Utility_StaticOutputFormatterFactory.hpp
//---------------------------------------------------------------------------//
