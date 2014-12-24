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
  case ELASTIC_ELECTROATOMIC_REACTION:
    return "Elastic Electroatomic Reaction";
  case BREMSSTRAHLUNG_ELECTROATOMIC_REACTION:
    return "Bremsstrahlung Electroatomic Reaction";
  case POSITRON_ANNIHILATION_ELECTROATOMIC_REACTION:
    return "Positron Annihilation Electroatomic Reaction";
  case INELASTIC_ELECTROATOMIC_REACTION:
    return "Inelastic Electroatomic Reaction";
  case ATOMIC_EXCITATION_ELECTROATOMIC_REACTION: 
    return "Atomic Excitation Electroatomic Reaction";
  case HARD_ELASTIC_ELECTROATOMIC_REACTION:
    return "Hard Elastic Electroatomic Reaction";
  case BREMSSTRAHLUNG_ELECTROATOMIC_REACTION:
    return "Bremsstrahlung Electroatomic Reaction";
  case TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "Total Electroionization Electroatomic Reaction";
  case K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "K Subshell Electroionization Electroatomic Reaction";
  case L1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "L1 Subshell Electroionization Electroatomic Reaction";
  case L2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "L2 Subshell Electroionization Electroatomic Reaction";
  case L3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "L3 Subshell Electroionization Electroatomic Reaction";
  case M1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "M1 Subshell Electroionization Electroatomic Reaction";
  case M2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "M2 Subshell Electroionization Electroatomic Reaction";
  case M3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "M3 Subshell Electroionization Electroatomic Reaction";
  case M4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "M4 Subshell Electroionization Electroatomic Reaction";
  case M5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "M5 Subshell Electroionization Electroatomic Reaction";
  case N1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "N1 Subshell Electroionization Electroatomic Reaction";
  case N2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "N2 Subshell Electroionization Electroatomic Reaction";
  case N3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "N3 Subshell Electroionization Electroatomic Reaction";
  case N4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "N4 Subshell Electroionization Electroatomic Reaction";
  case N5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "N5 Subshell Electroionization Electroatomic Reaction";
  case N6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "N6 Subshell Electroionization Electroatomic Reaction";
  case N7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "N7 Subshell Electroionization Electroatomic Reaction";
  case O1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O1 Subshell Electroionization Electroatomic Reaction";
  case O2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O2 Subshell Electroionization Electroatomic Reaction";
  case O3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O3 Subshell Electroionization Electroatomic Reaction";
  case O4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O4 Subshell Electroionization Electroatomic Reaction";
  case O5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O5 Subshell Electroionization Electroatomic Reaction";
  case O6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O6 Subshell Electroionization Electroatomic Reaction";
  case O7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O7 Subshell Electroionization Electroatomic Reaction";
  case O8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O8 Subshell Electroionization Electroatomic Reaction";
  case O9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O9 Subshell Electroionization Electroatomic Reaction";
  case P1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P1 Subshell Electroionization Electroatomic Reaction";
  case P2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P2 Subshell Electroionization Electroatomic Reaction";
  case P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P3 Subshell Electroionization Electroatomic Reaction";
  case P4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P4 Subshell Electroionization Electroatomic Reaction";
  case P5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P5 Subshell Electroionization Electroatomic Reaction";
  case P6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P6 Subshell Electroionization Electroatomic Reaction";
  case P7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P7 Subshell Electroionization Electroatomic Reaction";
  case P8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P8 Subshell Electroionization Electroatomic Reaction";
  case P9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P9 Subshell Electroionization Electroatomic Reaction";
  case P10_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P10 Subshell Electroionization Electroatomic Reaction";
  case P11_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P11 Subshell Electroionization Electroatomic Reaction";
  case Q1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "Q1 Subshell Electroionization Electroatomic Reaction";
  case Q2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "Q2 Subshell Electroionization Electroatomic Reaction";
  case Q3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "Q3 Subshell Electroionization Electroatomic Reaction";
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Error: cannot convert the Electroatomic reaction type "
		     "to a string!" );
  }
}

// Convert a SubshellType enum to a ElectroatomicReactionType enum
ElectroatomicReactionType convertSubshellEnumToElectroatomicReactionEnum(
						  const SubshellType subshell )
{
  switch( subshell )
  {
  case K_SUBSHELL:  return K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case L1_SUBSHELL: return L1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case L2_SUBSHELL: return L2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case L3_SUBSHELL: return L3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case M1_SUBSHELL: return M1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case M2_SUBSHELL: return M2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case M3_SUBSHELL: return M3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case M4_SUBSHELL: return M4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case M5_SUBSHELL: return M5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case N1_SUBSHELL: return N1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case N2_SUBSHELL: return N2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case N3_SUBSHELL: return N3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case N4_SUBSHELL: return N4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case N5_SUBSHELL: return N5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case N6_SUBSHELL: return N6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case N7_SUBSHELL: return N7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case O1_SUBSHELL: return O1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case O2_SUBSHELL: return O2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case O3_SUBSHELL: return O3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case O4_SUBSHELL: return O4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case O5_SUBSHELL: return O5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case O6_SUBSHELL: return O6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case O7_SUBSHELL: return O7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case O8_SUBSHELL: return O8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case O9_SUBSHELL: return O9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case P1_SUBSHELL: return P1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case P2_SUBSHELL: return P2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case P3_SUBSHELL: return P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case P4_SUBSHELL: return P4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case P5_SUBSHELL: return P5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case P6_SUBSHELL: return P6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case P7_SUBSHELL: return P7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case P8_SUBSHELL: return P8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case P9_SUBSHELL: return P9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case P10_SUBSHELL: return P10_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case P11_SUBSHELL: return P11_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Q1_SUBSHELL: return Q1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Q2_SUBSHELL: return Q2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Q3_SUBSHELL: return Q3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
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

