//---------------------------------------------------------------------------//
//!
//! \file   tstStandardOutputFormatter.cpp
//! \author Alex Robinson
//! \brief  The standard output formatter unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_StandardOutputFormatter.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the desired output can be formatted
TEUCHOS_UNIT_TEST( StandardOutputFormatter, format )
{
  std::cout << Utility::Bold( "Testing" ) << "..." << std::endl;
  std::cout << Utility::Italicized( "Testing" ) << "..." << std::endl;
  std::cout << Utility::Underlined( "Testing" ) << "..." << std::endl;
  std::cout << Utility::Red( "Testing" ) << "..." << std::endl;
  std::cerr << Utility::Cyan( "Testing" ) << "..." << std::endl;
  std::cerr << Utility::Magenta( "Testing" ) << "..." << std::endl;
  std::cerr << Utility::BoldWhite( "Testing" ) << "..." << std::endl;
  std::cout << Utility::StandardOutputFormatter<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor>( "Testing" ) << "..." << std::endl;
}

//---------------------------------------------------------------------------//
// end tstStandardOutputFormatter.cpp
//---------------------------------------------------------------------------//
