//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungAngularDistributionType.cpp
//! \author Luke Kersting
//! \brief  Electroatomic reaction type helper function definitions.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Convert a BremsstrahlungAngularDistributionType enum to a string
std::string convertBremsstrahlungAngularDistributionEnumToString(
				       const BremsstrahlungAngularDistributionType reaction )
{
  switch( reaction )
  {
  case DIPOLE_DISTRIBUTION:
    return "Dipole Distribution";
  case TABULAR_DISTRIBUTION:
    return "Tabular Distribution";
  case TWOBS_DISTRIBUTION:
    return "2BS Distribution";
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Error: cannot convert the Bremsstrahlung angular distribution "
		     "type to a string!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungAngularDistributionType.cpp
//---------------------------------------------------------------------------//

