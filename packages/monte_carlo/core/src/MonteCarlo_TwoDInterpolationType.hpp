//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TwoDInterpolationType.hpp
//! \author Luke Kersting
//! \brief  TwoDInterpolation type enumeration and helper declarations
//!
//---------------------------------------------------------------------------//

#ifndef MONTECARLO_TWO_D_INTERPOLATION_TYPE_HPP
#define MONTECARLO_TWO_D_INTERPOLATION_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

namespace MonteCarlo{

//! The two d interpolation types
enum TwoDInterpolationType{
  LINLINLIN_INTERPOLATION = 1,
  LINLINLOG_INTERPOLATION = 2,
  LINLOGLIN_INTERPOLATION = 3,
  LOGLINLIN_INTERPOLATION = 4,
  LOGLOGLIN_INTERPOLATION = 5,
  LOGLINLOG_INTERPOLATION = 6,
  LINLOGLOG_INTERPOLATION = 7,
  LOGLOGLOG_INTERPOLATION = 8,
};

//! Convert the TwoDInterpolationType to a string
std::string convertTwoDInterpolationTypeToString( const TwoDInterpolationType type );

//! Convert string to TwoDInterpolationType
TwoDInterpolationType convertStringToTwoDInterpolationType( const std::string raw_policy );

//! Stream operator for printing TwoDInterpolationType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const TwoDInterpolationType type )
{
  os << convertTwoDInterpolationTypeToString( type );

  return os;
}
} // end MonteCarlo namespace

#endif // end MONTECARLO_TWO_D_INTERPOLATION_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDInterpolationType.hpp
//---------------------------------------------------------------------------//
