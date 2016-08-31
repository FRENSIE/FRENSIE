//---------------------------------------------------------------------------//
//!
//! \file   Utility_TextBackgroundColorPolicy.hpp
//! \author Alex Robinson
//! \brief  The text background color policy class declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TEXT_BACKGROUND_COLOR_POLICY_HPP
#define UTILITY_TEXT_BACKGROUND_COLOR_POLICY_HPP

// Std Lib Includes
#include <string>

namespace Utility{

//! The default text background color policy
struct DefaultTextBackgroundColor
{
  static std::string getTextBackgroundColor();
};

//! The black text background color policy
struct BlackTextBackgroundColor
{
  static std::string getTextBackgroundColor();
};

//! The red text background color policy
struct RedTextBackgroundColor
{
  static std::string getTextBackgroundColor();
};

//! The green text background color policy
struct GreenTextBackgroundColor
{
  static std::string getTextBackgroundColor();
};

//! The yellow text background color policy
struct YellowTextBackgroundColor
{
  static std::string getTextBackgroundColor();
};

//! The blue text background color policy
struct BlueTextBackgroundColor
{
  static std::string getTextBackgroundColor();
};

//! The magenta text background color policy
struct MagentaTextBackgroundColor
{
  static std::string getTextBackgroundColor();
};

//! The cyan text background color policy
struct CyanTextBackgroundColor
{
  static std::string getTextBackgroundColor();
};

//! The white text background color policy
struct WhiteTextBackgroundColor
{
  static std::string getTextBackgroundColor();
};
  
} // end Utility namespace

#endif // end UTILITY_TEXT_BACKGROUND_COLOR_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_TextBackgroundColorPolicy.hpp
//---------------------------------------------------------------------------//
