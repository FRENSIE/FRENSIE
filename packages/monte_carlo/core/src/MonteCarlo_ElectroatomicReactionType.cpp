//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionType.cpp
//! \author Luke Kersting
//! \brief  Electro-atomic reaction type helper function definitions.
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
    return "Total Electro-atomic Reaction";
  case TOTAL_ABSORPTION_ELECTROATOMIC_REACTION:
    return "Total Absorption Electro-atomic Reaction";
  case COUPLED_ELASTIC_ELECTROATOMIC_REACTION:
    return "Coupled Elastic Electro-atomic Reaction";
  case HYBRID_ELASTIC_ELECTROATOMIC_REACTION:
    return "Hybrid Elastic Electro-atomic Reaction";
  case DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION:
    return "Decoupled Elastic Electro-atomic Reaction";
  case CUTOFF_ELASTIC_ELECTROATOMIC_REACTION:
    return "Cutoff Elastic Electro-atomic Reaction";
  case SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION:
    return "Screened Rutherford Elastic Electro-atomic Reaction";
  case MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION:
    return "Moment Preserving Elastic Electro-atomic Reaction";
  case BREMSSTRAHLUNG_ELECTROATOMIC_REACTION:
    return "Bremsstrahlung Electro-atomic Reaction";
  case POSITRON_ANNIHILATION_ELECTROATOMIC_REACTION:
    return "Positron Annihilation Electro-atomic Reaction";
  case ATOMIC_EXCITATION_ELECTROATOMIC_REACTION:
    return "Atomic Excitation Electro-atomic Reaction";
  case TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "Total Electro-ionization Electro-atomic Reaction";
  case K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "K Subshell Electro-ionization Electro-atomic Reaction";
  case L1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "L1 Subshell Electro-ionization Electro-atomic Reaction";
  case L2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "L2 Subshell Electro-ionization Electro-atomic Reaction";
  case L3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "L3 Subshell Electro-ionization Electro-atomic Reaction";
  case M1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "M1 Subshell Electro-ionization Electro-atomic Reaction";
  case M2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "M2 Subshell Electro-ionization Electro-atomic Reaction";
  case M3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "M3 Subshell Electro-ionization Electro-atomic Reaction";
  case M4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "M4 Subshell Electro-ionization Electro-atomic Reaction";
  case M5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "M5 Subshell Electro-ionization Electro-atomic Reaction";
  case N1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "N1 Subshell Electro-ionization Electro-atomic Reaction";
  case N2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "N2 Subshell Electro-ionization Electro-atomic Reaction";
  case N3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "N3 Subshell Electro-ionization Electro-atomic Reaction";
  case N4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "N4 Subshell Electro-ionization Electro-atomic Reaction";
  case N5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "N5 Subshell Electro-ionization Electro-atomic Reaction";
  case N6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "N6 Subshell Electro-ionization Electro-atomic Reaction";
  case N7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "N7 Subshell Electro-ionization Electro-atomic Reaction";
  case O1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O1 Subshell Electro-ionization Electro-atomic Reaction";
  case O2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O2 Subshell Electro-ionization Electro-atomic Reaction";
  case O3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O3 Subshell Electro-ionization Electro-atomic Reaction";
  case O4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O4 Subshell Electro-ionization Electro-atomic Reaction";
  case O5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O5 Subshell Electro-ionization Electro-atomic Reaction";
  case O6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O6 Subshell Electro-ionization Electro-atomic Reaction";
  case O7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O7 Subshell Electro-ionization Electro-atomic Reaction";
  case O8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O8 Subshell Electro-ionization Electro-atomic Reaction";
  case O9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "O9 Subshell Electro-ionization Electro-atomic Reaction";
  case P1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P1 Subshell Electro-ionization Electro-atomic Reaction";
  case P2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P2 Subshell Electro-ionization Electro-atomic Reaction";
  case P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P3 Subshell Electro-ionization Electro-atomic Reaction";
  case P4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P4 Subshell Electro-ionization Electro-atomic Reaction";
  case P5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P5 Subshell Electro-ionization Electro-atomic Reaction";
  case P6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P6 Subshell Electro-ionization Electro-atomic Reaction";
  case P7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P7 Subshell Electro-ionization Electro-atomic Reaction";
  case P8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P8 Subshell Electro-ionization Electro-atomic Reaction";
  case P9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P9 Subshell Electro-ionization Electro-atomic Reaction";
  case P10_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P10 Subshell Electro-ionization Electro-atomic Reaction";
  case P11_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "P11 Subshell Electro-ionization Electro-atomic Reaction";
  case Q1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "Q1 Subshell Electro-ionization Electro-atomic Reaction";
  case Q2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "Q2 Subshell Electro-ionization Electro-atomic Reaction";
  case Q3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION:
    return "Q3 Subshell Electro-ionization Electro-atomic Reaction";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: cannot convert the Electro-atomic reaction type "
                     "to a string!" );
  }
}

// Convert a Data::SubshellType enum to a ElectroatomicReactionType enum
ElectroatomicReactionType convertSubshellEnumToElectroionizationElectroatomicReactionEnum(
                                            const Data::SubshellType subshell )
{
  switch( subshell )
  {
  case Data::K_SUBSHELL:  return K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::L1_SUBSHELL: return L1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::L2_SUBSHELL: return L2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::L3_SUBSHELL: return L3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::M1_SUBSHELL: return M1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::M2_SUBSHELL: return M2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::M3_SUBSHELL: return M3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::M4_SUBSHELL: return M4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::M5_SUBSHELL: return M5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::N1_SUBSHELL: return N1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::N2_SUBSHELL: return N2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::N3_SUBSHELL: return N3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::N4_SUBSHELL: return N4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::N5_SUBSHELL: return N5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::N6_SUBSHELL: return N6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::N7_SUBSHELL: return N7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::O1_SUBSHELL: return O1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::O2_SUBSHELL: return O2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::O3_SUBSHELL: return O3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::O4_SUBSHELL: return O4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::O5_SUBSHELL: return O5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::O6_SUBSHELL: return O6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::O7_SUBSHELL: return O7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::O8_SUBSHELL: return O8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::O9_SUBSHELL: return O9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::P1_SUBSHELL: return P1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::P2_SUBSHELL: return P2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::P3_SUBSHELL: return P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::P4_SUBSHELL: return P4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::P5_SUBSHELL: return P5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::P6_SUBSHELL: return P6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::P7_SUBSHELL: return P7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::P8_SUBSHELL: return P8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::P9_SUBSHELL: return P9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::P10_SUBSHELL: return P10_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::P11_SUBSHELL: return P11_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::Q1_SUBSHELL: return Q1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::Q2_SUBSHELL: return Q2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  case Data::Q3_SUBSHELL: return Q3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;
  default:
    THROW_EXCEPTION( std::logic_error,
             "Error: the invalid shell does not have a corresponding "
             "Electro-ionization Electro-atomic reaction!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionType.cpp
//---------------------------------------------------------------------------//

