//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungAngularDistributionType.hpp
//! \author Luke Kersting
//! \brief  Bremsstrahlung angular distribution type enumeration and helper function decls.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_ANGULAR_DISTRIBUTION_TYPE_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_ANGULAR_DISTRIBUTION_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

namespace MonteCarlo{

//! The bremsstrahlung photon angular distribution type enum.
enum BremsstrahlungAngularDistributionType{
  DIPOLE_DISTRIBUTION = 1,
  TABULAR_DISTRIBUTION = 2,
  TWOBS_DISTRIBUTION = 3
};

//! Convert a BremsstrahlungAngularDistributionType enum to a string
std::string convertBremsstrahlungAngularDistributionEnumToString(
                      const BremsstrahlungAngularDistributionType reaction );

//! Stream operator for printing BremsstrahlungAngularDistributionType enums
inline std::ostream& operator<<( std::ostream& os,
                const BremsstrahlungAngularDistributionType reaction )
{
  os << convertBremsstrahlungAngularDistributionEnumToString( reaction );
  return os;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ANGULAR_DISTRIBUTION_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungAngularDistributionType.hpp
//---------------------------------------------------------------------------//

