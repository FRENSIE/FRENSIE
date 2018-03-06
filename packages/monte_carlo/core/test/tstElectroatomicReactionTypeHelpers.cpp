//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomicReactionTypeHelpers.cpp
//! \author Luke Kersting
//! \brief  Electro-atomic reaction type helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a electroatomic reaction type can be converted to a string
TEUCHOS_UNIT_TEST( ElectroatomicReactionType,
                   convertElectroatomicReactionEnumToString )
{
  std::string reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::TOTAL_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Total Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Total Absorption Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Coupled Elastic Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Hybrid Elastic Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Decoupled Elastic Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Cutoff Elastic Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Screened Rutherford Elastic Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Moment Preserving Elastic Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Bremsstrahlung Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::POSITRON_ANNIHILATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Positron Annihilation Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Atomic Excitation Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Total Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "K Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION  );

  TEST_EQUALITY_CONST( reaction_name, "L1 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::L2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "L2 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::L3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "L3 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::M1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M1 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::M2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M2 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::M3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M3 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::M4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M4 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::M5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M5 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::N1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N1 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::N2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N2 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::N3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N3 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::N4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION  );

  TEST_EQUALITY_CONST( reaction_name, "N4 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::N5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N5 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::N6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N6 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::N7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N7 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::O1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O1 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::O2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O2 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::O3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O3 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::O4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O4 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::O5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O5 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::O6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O6 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::O7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O7 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::O8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O8 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::O9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O9 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::P1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P1 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::P2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P2 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P3 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::P4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P4 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::P5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P5 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::P6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P6 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::P7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P7 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::P8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P8 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::P9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P9 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::P10_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P10 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::P11_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P11 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::Q1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Q1 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::Q2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Q2 Subshell Electro-ionization Electro-atomic Reaction" );

  reaction_name =
    MonteCarlo::convertElectroatomicReactionEnumToString( MonteCarlo::Q3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Q3 Subshell Electro-ionization Electro-atomic Reaction" );
}

//---------------------------------------------------------------------------//
// Check that a subshell type can be converted to an incoherent electroatomic
// reaction type enum
TEUCHOS_UNIT_TEST( ElectroatomicReactionType,
                   convertSubshellEnumToElectroionizationElectroatomicReactionEnum )
{
  MonteCarlo::ElectroatomicReactionType reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum(
                                                            Data::K_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::L1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::L2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::L2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::L3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::L3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::M1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::M2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::M3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::M4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::M5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::N1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::N2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::N3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::N4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::N5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::N6_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::N7_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::O1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::O2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::O3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::O4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::O5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::O6_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::O7_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::O8_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::O9_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::P1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::P2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::P3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::P4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::P5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::P6_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::P7_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::P8_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::P9_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::P10_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P10_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::P11_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P11_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::Q1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::Q1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::Q2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::Q2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationElectroatomicReactionEnum( Data::Q3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::Q3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that a electroatomic reaction type can be placed in an output stream
TEUCHOS_UNIT_TEST( ElectroatomicReactionType, ostream_operator )
{
  std::ostringstream oss;

  oss << MonteCarlo::TOTAL_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Total Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Total Absorption Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Coupled Elastic Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Hybrid Elastic Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Decoupled Elastic Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Cutoff Elastic Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Screened Rutherford Elastic Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Moment Preserving Elastic Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Bremsstrahlung Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::POSITRON_ANNIHILATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Positron Annihilation Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Atomic Excitation Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Total Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "K Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "L1 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::L2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "L2 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::L3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "L3 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::M1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M1 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::M2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M2 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::M3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M3 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::M4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M4 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::M5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M5 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N1 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N2 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N3 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N4 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N5 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N6 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N7 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O1 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O2 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O3 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O4 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O5 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O6 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O7 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O8 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O9 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P1 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P2 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P3 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P4_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P4 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P5_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P5 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P6_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P6 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P7_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P7 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P8_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P8 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P9_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P9 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P10_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P10 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P11_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P11 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::Q1_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Q1 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::Q2_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Q2 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::Q3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Q3 Subshell Electro-ionization Electro-atomic Reaction" );

  oss.str( "" );
  oss.clear();
}

//---------------------------------------------------------------------------//
// end tstElectroatomicReactionTypeHelpers.cpp
//---------------------------------------------------------------------------//
