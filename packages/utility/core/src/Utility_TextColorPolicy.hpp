//---------------------------------------------------------------------------//
//!
//! \file   Utility_TextColorPolicy.hpp
//! \author Alex Robinson
//! \brief  The text color policy class declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TEXT_COLOR_POLICY_HPP
#define UTILITY_TEXT_COLOR_POLICY_HPP

// Std Lib Includes
#include <string>

namespace Utility{

//! The default text color policy
struct DefaultTextColor
{
  static std::string getTextColor();
};

//! The black text color policy
struct BlackTextColor
{
  static std::string getTextColor();
};

//! The red text color policy
struct RedTextColor
{
  static std::string getTextColor();
};

//! The green text color policy
struct GreenTextColor
{
  static std::string getTextColor();
};

//! The yellow text color policy
struct YellowTextColor
{
  static std::string getTextColor();
};

//! The blue text color policy
struct BlueTextColor
{
  static std::string getTextColor();
};

//! The magenta text color policy
struct MagentaTextColor
{
  static std::string getTextColor();
};

//! The cyan text color policy
struct CyanTextColor
{
  static std::string getTextColor();
};

//! The white text color policy
struct WhiteTextColor
{
  static std::string getTextColor();
};
  
} // end Utility namespace

#endif // end UTILITY_TEXT_COLOR_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_TextColorPolicy.hpp
//---------------------------------------------------------------------------//
