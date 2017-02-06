//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronSecondaryInterpolationType.hpp
//! \author Luke Kersting
//! \brief  The electron secondary distribution interpolation type enumeration and helper function definitions.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRON_SECONDARY_INTERPOLATION_TYPE_HPP
#define MONTE_CARLO_ELECTRON_SECONDARY_INTERPOLATION_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

namespace MonteCarlo{

//! The two dimensional interpolation type enum.
enum ElectronSecondaryInterpolationType{
  LIN_LIN_LIN = 1,
  LIN_LIN_LOG = 2
};

//! Convert a TwoDInterpolationType enum to a string
std::string convertElectronSecondaryInterpolationEnumToString(
                      const ElectronSecondaryInterpolationType interpolation_type );

//! Stream operator for printing ElectronSecondaryInterpolationType enums
inline std::ostream& operator<<( std::ostream& os,
                const ElectronSecondaryInterpolationType interpolation_type )
{
  os << convertElectronSecondaryInterpolationEnumToString( interpolation_type );
  return os;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTRON_SECONDARY_INTERPOLATION_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronSecondaryInterpolationType.hpp
//---------------------------------------------------------------------------//

