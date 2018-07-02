//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomicReactionType.cpp
//! \author Luke Kersting
//! \brief  Adjoint electroatomic reaction type helper function definitions.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReactionType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Convert a Data::SubshellType enum to an AdjointElectroatomicReactionType enum
AdjointElectroatomicReactionType
convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum(
                                            const Data::SubshellType subshell )
{
  switch( subshell )
  {
  case Data::K_SUBSHELL:  return K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::L1_SUBSHELL: return L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::L2_SUBSHELL: return L2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::L3_SUBSHELL: return L3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::M1_SUBSHELL: return M1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::M2_SUBSHELL: return M2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::M3_SUBSHELL: return M3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::M4_SUBSHELL: return M4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::M5_SUBSHELL: return M5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::N1_SUBSHELL: return N1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::N2_SUBSHELL: return N2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::N3_SUBSHELL: return N3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::N4_SUBSHELL: return N4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::N5_SUBSHELL: return N5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::N6_SUBSHELL: return N6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::N7_SUBSHELL: return N7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::O1_SUBSHELL: return O1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::O2_SUBSHELL: return O2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::O3_SUBSHELL: return O3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::O4_SUBSHELL: return O4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::O5_SUBSHELL: return O5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::O6_SUBSHELL: return O6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::O7_SUBSHELL: return O7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::O8_SUBSHELL: return O8_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::O9_SUBSHELL: return O9_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::P1_SUBSHELL: return P1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::P2_SUBSHELL: return P2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::P3_SUBSHELL: return P3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::P4_SUBSHELL: return P4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::P5_SUBSHELL: return P5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::P6_SUBSHELL: return P6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::P7_SUBSHELL: return P7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::P8_SUBSHELL: return P8_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::P9_SUBSHELL: return P9_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::P10_SUBSHELL: return P10_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::P11_SUBSHELL: return P11_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::Q1_SUBSHELL: return Q1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::Q2_SUBSHELL: return Q2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  case Data::Q3_SUBSHELL: return Q3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  default:
  {
    THROW_EXCEPTION( std::logic_error,
                     "The subshell does not have a corresponding "
                     "Electroionization Adjoint Electroatomic reaction!" );
  }
  }
}

} // end MonteCarlo namespace

namespace Utility{

// Convert a MonteCarlo::AdjointElectroatomicReactionType to a string
std::string ToStringTraits<MonteCarlo::AdjointElectroatomicReactionType>::toString(
                  const MonteCarlo::AdjointElectroatomicReactionType reaction )
{
  switch( reaction )
  {
  case MonteCarlo::TOTAL_ADJOINT_ELECTROATOMIC_REACTION:
    return "Total Adjoint Electroatomic Reaction";
  case MonteCarlo::TOTAL_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION:
    return "Total Absorption Adjoint Electroatomic Reaction";
  case MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION:
    return "Coupled Elastic Adjoint Electroatomic Reaction";
  case MonteCarlo::DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION:
    return "Decoupled Elastic Adjoint Electroatomic Reaction";
  case MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION:
    return "Hybrid Elastic Adjoint Electroatomic Reaction";
  case MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION:
    return "Cutoff Elastic Adjoint Electroatomic Reaction";
  case MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION:
    return "Screened Rutherford Elastic Adjoint Electroatomic Reaction";
  case MonteCarlo::MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION:
    return "Moment Preserving Elastic Adjoint Electroatomic Reaction";
  case MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION:
    return "Bremsstrahlung Adjoint Electroatomic Reaction";
  case MonteCarlo::POSITRON_ANNIHILATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "Positron Annihilation Adjoint Electroatomic Reaction";
  case MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "Atomic Excitation Adjoint Electroatomic Reaction";
  case MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "Total Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "K Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "L1 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::L2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "L2 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::L3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "L3 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::M1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "M1 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::M2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "M2 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::M3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "M3 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::M4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "M4 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::M5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "M5 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::N1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "N1 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::N2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "N2 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::N3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "N3 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::N4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "N4 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::N5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "N5 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::N6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "N6 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::N7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "N7 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::O1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "O1 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::O2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "O2 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::O3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "O3 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::O4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "O4 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::O5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "O5 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::O6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "O6 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::O7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "O7 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::O8_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "O8 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::O9_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "O9 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::P1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "P1 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::P2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "P2 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "P3 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::P4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "P4 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::P5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "P5 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::P6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "P6 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::P7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "P7 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::P8_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "P8 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::P9_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "P9 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::P10_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "P10 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::P11_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "P11 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::Q1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "Q1 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::Q2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "Q2 Subshell Electroionization Adjoint Electroatomic Reaction";
  case MonteCarlo::Q3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION:
    return "Q3 Subshell Electroionization Adjoint Electroatomic Reaction";
  default:
  {
    THROW_EXCEPTION( std::logic_error,
                     "Cannot convert the adjoint electroatomic reaction "
                     "type to a string!" );
  }
  }
}

// Place the MonteCarlo::AdjointElectroatomicReactionType in a stream
void ToStringTraits<MonteCarlo::AdjointElectroatomicReactionType>::toStream(
                      std::ostream& os,
                      const MonteCarlo::AdjointElectroatomicReactionType type )
{
  os << ToStringTraits<MonteCarlo::AdjointElectroatomicReactionType>::toString( type );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomicReactionType.cpp
//---------------------------------------------------------------------------//

