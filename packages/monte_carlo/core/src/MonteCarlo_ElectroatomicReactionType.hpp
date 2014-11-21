//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionType.hpp
//! \author Luke Kersting
//! \brief  Electroatomic reaction type enumeration and helper function decls.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOMIC_REACTION_TYPE_HPP
#define MONTE_CARLO_ELECTROATOMIC_REACTION_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
//#include "MonteCarlo_SubshellType.hpp"

namespace MonteCarlo{
  
//! The photoatomic reaction type enum.
enum ElectroatomicReactionType{
  TOTAL_ELECTROATOMIC_REACTION = 1,
  TOTAL_ABSORPTION_ELECTROATOMIC_REACTION = 2,
  ATOMIC_EXCITATION_ELECTROATOMIC_REACTION = 3,
  HARD_ELASTIC_ELECTROATOMIC_REACTION = 4,
  BREMSSTRAHLUNG_ELECTROATOMIC_REACTION = 5,
  ELECTROIONIZATION_ELECTROATOMIC_REACTION = 6,
};

//! Convert a ElectroatomicReactionType enum to a string
std::string convertElectroatomicReactionEnumToString( 
				      const ElectroatomicReactionType reaction );

//! Convert a SubshellType enum to a ElectroatomicReactionType enum
ElectroatomicReactionType convertSubshellEnumToElectroatomicReactionEnum(
						 const unsigned subshell );

//! Stream operator for printing ElectroatomicReactionType enums
inline std::ostream& operator<<( std::ostream& os,
				 const ElectroatomicReactionType reaction )
{
  os << convertElectroatomicReactionEnumToString( reaction );
  return os;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROATOMIC_REACTION_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionType.hpp
//---------------------------------------------------------------------------//


