//---------------------------------------------------------------------------//
//!
//! \file   Utility_TextBackgroundColorPolicy.hpp
//! \author Alex Robinson
//! \brief  The text background color policy class definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_TextBackgroundColorPolicy.hpp"
#include "FRENSIE_tty_format_config.hpp"

namespace Utility{

// The default text background color policy
std::string DefaultTextBackgroundColor::getTextBackgroundColor()
{
  return DEFAULT_BKGD_COLOR_FORMAT_KEY;
}

// The black text background color policy
std::string BlackTextBackgroundColor::getTextBackgroundColor()
{
  return BLACK_BKGD_FORMAT_KEY;
}

// The red text background color policy
std::string RedTextBackgroundColor::getTextBackgroundColor()
{
  return RED_BKGD_FORMAT_KEY;
}

// The green text background color policy
std::string GreenTextBackgroundColor::getTextBackgroundColor()
{
  return GREEN_BKGD_FORMAT_KEY;
}

// The yellow text background color policy
std::string YellowTextBackgroundColor::getTextBackgroundColor()
{
  return YELLOW_BKGD_FORMAT_KEY;
}

// The blue text background color policy
std::string BlueTextBackgroundColor::getTextBackgroundColor()
{
  return BLUE_BKGD_FORMAT_KEY;
}

// The magenta text background color policy
std::string MagentaTextBackgroundColor::getTextBackgroundColor()
{
  return MAGENTA_BKGD_FORMAT_KEY;
}

// The cyan text background color policy
std::string CyanTextBackgroundColor::getTextBackgroundColor()
{
  return CYAN_BKGD_FORMAT_KEY;
}

// The white text background color policy
std::string WhiteTextBackgroundColor::getTextBackgroundColor()
{
  return WHITE_BKGD_FORMAT_KEY;
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_TextBackgroundColorPolicy.cpp
//---------------------------------------------------------------------------//
