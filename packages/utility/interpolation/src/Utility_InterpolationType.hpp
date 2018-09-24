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

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"

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
  GAMOW_INTERPOLATION = 6,
  LOGLOGCOS_INTERPOLATION = 7,
  LOGCOSLOG_INTERPOLATION = 8,
  LINLOGCOS_INTERPOLATION = 9,
  LOGCOSLIN_INTERPOLATION = 10,
  LOGNUDGEDLOGCOS_INTERPOLATION = 11,
  NUDGEDLOGCOSLOG_INTERPOLATION = 12,
  LINNUDGEDLOGCOS_INTERPOLATION = 13,
  NUDGEDLOGCOSLIN_INTERPOLATION = 14
};

//! Convert an ENDF interpolation value to an InterpolationType
InterpolationType convertENDFInterpolationTypeToInterpolationType(
                                             const unsigned endf_interp_type );

/*! \brief Specialization of Utility::ToStringTraits for
 * Utility::InterpolationType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<InterpolationType>
{
  //! Convert a Utility::UnivariateDistributionType to a string
  static std::string toString( const InterpolationType obj );

  //! Place the Utility::UnivariateDistributionType in a stream
  static void toStream( std::ostream& os, const InterpolationType obj );
};

} // end Utility namespace

namespace std{

//! Stream operator for printing InterpolationType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const Utility::InterpolationType type )
{
  Utility::toStream( os, type );

  return os;
}

} // end std namespace

#endif // end UTILITY_INTERPOLATION_TYPE_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolationType.hpp
//---------------------------------------------------------------------------//
