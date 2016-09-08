//---------------------------------------------------------------------------//
//!
//! \file   Utility_TextColorPolicy.cpp
//! \author Alex Robinson
//! \brief  The text color policy class definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_TextColorPolicy.hpp"
#include "FRENSIE_tty_format_config.hpp"

namespace Utility{

// The default text color policy
std::string DefaultTextColor::getTextColor()
{
  return DEFAULT_COLOR_TEXT_FORMAT_KEY;
}

// The black text color policy
std::string BlackTextColor::getTextColor()
{
  return BLACK_TEXT_FORMAT_KEY;
}

// The red text color policy
std::string RedTextColor::getTextColor()
{
  return RED_TEXT_FORMAT_KEY;
}

// The green text color policy
std::string GreenTextColor::getTextColor()
{
  return GREEN_TEXT_FORMAT_KEY;
}

// The yellow text color policy
std::string YellowTextColor::getTextColor()
{
  return YELLOW_TEXT_FORMAT_KEY;
}

// The blue text color policy
std::string BlueTextColor::getTextColor()
{
  return BLUE_TEXT_FORMAT_KEY;
}

// The magenta text color policy
std::string MagentaTextColor::getTextColor()
{
  return MAGENTA_TEXT_FORMAT_KEY;
}

// The cyan text color policy
std::string CyanTextColor::getTextColor()
{
  return CYAN_TEXT_FORMAT_KEY;
}

// The white text color policy
std::string WhiteTextColor::getTextColor()
{
  return WHITE_TEXT_FORMAT_KEY;
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_TextColorPolicy.cpp
//---------------------------------------------------------------------------//
