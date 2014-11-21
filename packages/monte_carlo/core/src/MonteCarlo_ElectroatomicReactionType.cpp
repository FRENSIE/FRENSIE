//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionType.cpp
//! \author Luke Kersting
//! \brief  Electroatomic reaction type helper function definitions.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Convert a ElectroatomicReactionType enum to a string
std::string convertElectroatomicReactionEnumToString( 
				       const ElectroatomicReactionType reaction )
{
  switch( reaction )
  {
  case TOTAL_ELECTROATOMIC_REACTION: 
    return "Total Electroatomic Reaction";
  case TOTAL_ABSORPTION_ELECTROATOMIC_REACTION:
    return "Total Absorption Electroatomic Reaction";
  case ATOMIC_EXCITATION_ELECTROATOMIC_REACTION: 
    return "Atomic Excitation Electroatomic Reaction";
  case HARD_ELASTIC_ELECTROATOMIC_REACTION:
    return "Hard Elastic Electroatomic Reaction";
  case BREMSSTRAHLUNG_ELECTROATOMIC_REACTION:
    return "Bremsstrahlung Electroatomic Reaction";
  case ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "Electroionization Electroatomic Reaction";
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Error: cannot convert the Electroatomic reaction type "
		     "to a string!" );
  }
}

// Convert a SubshellType enum to a ElectroatomicReactionType enum
ElectroatomicReactionType convertSubshellEnumToElectroatomicReactionEnum(
						  const unsigned subshell )
{
  switch( subshell )
  {
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Error: the invalid shell does not have a corresponding " 
		     "Electroionization Electroatomic reaction!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionType.cpp
//---------------------------------------------------------------------------//

