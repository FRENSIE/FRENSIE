//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolationType.hpp
//! \author Alex Robinson
//! \brief  Interpolation type enumeration and helper declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATION_TYPE_HPP
#define UTILITY_INTERPOLATION_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

namespace Utility{

/*! The interpolation types
 * \details The enumeration values correspond to the ENDF interpolation values
 */
enum InterpolationType{
  HISTOGRAM_INTERPOLATION = 1,
  LINLIN_INTERPOLATION = 2,
  LINLOG_INTERPOLATION = 3,
  LOGLIN_INTERPOLATION = 4,
  LOGLOG_INTERPOLATION = 5,
  GAMOW_INTERPOLATION = 6
};

//! Convert an ENDF interpolation value to an InterpolationType
InterpolationType convertENDFInterpolationTypeToInterpolationType(
                                             const unsigned endf_interp_type );

//! Convert the InterpolationType to a string
std::string convertInterpolationTypeToString( const InterpolationType type );

//! Stream operator for printing InterpolationType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const InterpolationType type )
{
  os << convertInterpolationTypeToString( type );

  return os;
}
  
  
} // end Utility namespace

#endif // end UTILITY_INTERPOLATION_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolationType.hpp
//---------------------------------------------------------------------------//
