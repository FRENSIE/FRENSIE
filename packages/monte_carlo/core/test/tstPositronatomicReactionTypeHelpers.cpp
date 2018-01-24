//---------------------------------------------------------------------------//
//!
//! \file   tstPositronatomicReactionTypeHelpers.cpp
//! \author Luke Kersting
//! \brief  Positron-atomic reaction type helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReactionType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a positronatomic reaction type can be converted to a string
TEUCHOS_UNIT_TEST( PositronatomicReactionType,
                   convertPositronatomicReactionEnumToString )
{
  std::string reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::TOTAL_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Total Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Total Absorption Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::COUPLED_ELASTIC_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Coupled Elastic Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::HYBRID_ELASTIC_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Hybrid Elastic Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Decoupled Elastic Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Cutoff Elastic Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Screened Rutherford Elastic Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::MOMENT_PRESERVING_ELASTIC_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Moment Preserving Elastic Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Bremsstrahlung Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::POSITRON_ANNIHILATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Positron Annihilation Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Atomic Excitation Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Total Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "K Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::L1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION  );

  TEST_EQUALITY_CONST( reaction_name, "L1 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::L2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "L2 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::L3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "L3 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::M1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M1 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::M2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M2 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::M3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M3 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::M4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M4 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::M5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M5 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::N1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N1 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::N2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N2 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::N3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N3 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::N4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION  );

  TEST_EQUALITY_CONST( reaction_name, "N4 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::N5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N5 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::N6_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N6 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::N7_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N7 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::O1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O1 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::O2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O2 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::O3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O3 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::O4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O4 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::O5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O5 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::O6_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O6 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::O7_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O7 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::O8_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O8 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::O9_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O9 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::P1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P1 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::P2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P2 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P3 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::P4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P4 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::P5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P5 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::P6_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P6 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::P7_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P7 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::P8_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P8 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::P9_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P9 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::P10_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P10 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::P11_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P11 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::Q1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Q1 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::Q2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Q2 Subshell Positron-ionization Positron-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertPositronatomicReactionEnumToString( MonteCarlo::Q3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Q3 Subshell Positron-ionization Positron-atomic Reaction" );
}

//---------------------------------------------------------------------------//
// Check that a subshell type can be converted to an incoherent positronatomic
// reaction type enum
TEUCHOS_UNIT_TEST( PositronatomicReactionType,
                   convertSubshellEnumToPositronionizationPositronatomicReactionEnum )
{
  MonteCarlo::PositronatomicReactionType reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum(
                                                            Data::K_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::L1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::L1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::L2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::L2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::L3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::L3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::M1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::M2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::M3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::M4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::M5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::N1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::N2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::N3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::N4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::N5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::N6_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N6_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::N7_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N7_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::O1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::O2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::O3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::O4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::O5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::O6_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O6_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::O7_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O7_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::O8_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O8_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::O9_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O9_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::P1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::P2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::P3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::P4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::P5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::P6_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P6_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::P7_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P7_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::P8_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P8_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::P9_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P9_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::P10_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P10_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::P11_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P11_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::Q1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::Q1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::Q2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::Q2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPositronionizationPositronatomicReactionEnum( Data::Q3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::Q3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that a positronatomic reaction type can be placed in an output stream
TEUCHOS_UNIT_TEST( PositronatomicReactionType, ostream_operator )
{
  std::ostringstream oss;

  oss << MonteCarlo::TOTAL_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Total Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TOTAL_ABSORPTION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Total Absorption Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::COUPLED_ELASTIC_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Coupled Elastic Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::HYBRID_ELASTIC_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Hybrid Elastic Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Decoupled Elastic Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Cutoff Elastic Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Screened Rutherford Elastic Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::MOMENT_PRESERVING_ELASTIC_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Moment Preserving Elastic Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Bremsstrahlung Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::POSITRON_ANNIHILATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Positron Annihilation Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Atomic Excitation Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Total Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "K Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::L1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "L1 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::L2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "L2 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::L3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "L3 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::M1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M1 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::M2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M2 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::M3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M3 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::M4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M4 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::M5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M5 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N1 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N2 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N3 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N4 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N5 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N6_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N6 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N7_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N7 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O1 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O2 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O3 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O4 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O5 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O6_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O6 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O7_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O7 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O8_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O8 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O9_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O9 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P1 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P2 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P3 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P4 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P5 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P6_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P6 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P7_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P7 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P8_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P8 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P9_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P9 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P10_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P10 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P11_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P11 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::Q1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Q1 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::Q2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Q2 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::Q3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Q3 Subshell Positron-ionization Positron-atomic Reaction" );

  oss.str( "" );
  oss.clear();
}

//---------------------------------------------------------------------------//
// end tstPositronatomicReactionTypeHelpers.cpp
//---------------------------------------------------------------------------//
