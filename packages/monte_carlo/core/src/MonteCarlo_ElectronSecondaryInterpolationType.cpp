//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronSecondaryInterpolationType.cpp
//! \author Luke Kersting
//! \brief  The electron secondary distribution interpolation type helper function definitions.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_ElectronSecondaryInterpolationType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Convert a ElectronSecondaryInterpolationType enum to a string
std::string convertElectronSecondaryInterpolationEnumToString(
                      const ElectronSecondaryInterpolationType interpolation_type )

{
  switch( interpolation_type )
  {
  case LIN_LIN_LIN:
    return "Lin-Lin-Lin";
  case LIN_LIN_LOG:
    return "Lin-Lin-Log";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: cannot convert the electron secondary "
                     "interpolation type to a string!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronSecondaryInterpolationType.cpp
//---------------------------------------------------------------------------//

