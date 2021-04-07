//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungAngularDistributionType.cpp
//! \author Luke Kersting
//! \brief  Bremsstrahlung angular distribution type helper function definitions.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Convert a MonteCarlo::BremsstrahlungAngularDistributionType to a string
std::string ToStringTraits<MonteCarlo::BremsstrahlungAngularDistributionType>::toString(
             const MonteCarlo::BremsstrahlungAngularDistributionType reaction )
{
  switch( reaction )
  {
  case MonteCarlo::DIPOLE_DISTRIBUTION:
    return "Dipole Distribution";
  case MonteCarlo::TABULAR_DISTRIBUTION:
    return "Tabular Distribution";
  case MonteCarlo::TWOBS_DISTRIBUTION:
    return "2BS Distribution";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Cannot convert the Bremsstrahlung angular distribution "
                     "type to a string!" );
  }
}

// Place the MonteCarlo::BremsstrahlungAngularDistributionType in a stream
void ToStringTraits<MonteCarlo::BremsstrahlungAngularDistributionType>::toStream( std::ostream& os, const MonteCarlo::BremsstrahlungAngularDistributionType type )
{
  os << ToStringTraits<MonteCarlo::BremsstrahlungAngularDistributionType>::toString( type );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungAngularDistributionType.cpp
//---------------------------------------------------------------------------//

