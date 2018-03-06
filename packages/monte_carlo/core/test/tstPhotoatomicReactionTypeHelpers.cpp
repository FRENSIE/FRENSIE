//---------------------------------------------------------------------------//
//!
//! \file   tstPhotoatomicReactionTypeHelpers.cpp
//! \author Alex Robinson
//! \brief  Photoatomic reaction type helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReactionType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a photoatomic reaction type can be converted to a string
TEUCHOS_UNIT_TEST( PhotoatomicReactionType,
                   convertPhotoatomicReactionEnumToString )
{
  std::string reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::TOTAL_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Total Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Total Absorption Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Total Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "K Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::L1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION  );

  TEST_EQUALITY_CONST( reaction_name, "L1 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::L2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "L2 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::L3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "L3 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::M1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M1 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::M2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M2 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::M3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M3 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::M4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M4 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::M5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M5 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::N1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N1 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::N2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N2 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::N3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N3 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::N4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION  );

  TEST_EQUALITY_CONST( reaction_name, "N4 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::N5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N5 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::N6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N6 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::N7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N7 Subshell Incoherent Photoatomic Reaction" );
  
  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O1 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O2 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O3 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O4 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O5 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O6 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O7 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O8_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O8 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O9_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O9 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P1 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P2 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P3 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P4 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P5 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P6 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P7 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P8_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P8 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P9_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P9 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P10_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P10 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P11_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P11 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::Q1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Q1 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::Q2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Q2 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::Q3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Q3 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Coherent Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Pair Production Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Triplet Production Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Total Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "K Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::L1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "L1 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::L2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "L2 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::L3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "L3 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::M1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M1 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::M2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M2 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::M3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M3 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::M4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M4 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::M5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M5 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::N1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N1 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::N2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N2 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::N3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N3 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::N4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N4 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::N5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N5 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::N6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N6 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::N7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N7 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O1 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O2 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O3 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O4 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O5 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O6 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O7 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O8 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::O9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O9 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P1 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P2 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P3 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P4 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P5 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P6 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P7 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P8 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P9 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P10_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P10 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::P11_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P11 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::Q1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Q1 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::Q2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Q2 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::Q3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Q3 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertPhotoatomicReactionEnumToString( MonteCarlo::HEATING_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Heating Photoatomic Reaction" );
}

//---------------------------------------------------------------------------//
// Check that a subshell type can be converted to a photoelectric
// photoatomic reaction type enum
TEUCHOS_UNIT_TEST( PhotoatomicReactionType,
                   convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum )
{
  MonteCarlo::PhotoatomicReactionType reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum(
                                                            Data::K_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::L1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::L1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::L2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::L2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::L3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::L3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::M1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::M2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::M3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::M4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::M5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::N1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::N2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::N3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::N4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::N5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::N6_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::N7_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O6_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O7_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O8_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O9_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P6_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P7_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P8_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P9_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P10_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P10_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P11_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P11_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::Q1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::Q1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::Q2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::Q2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::Q3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::Q3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that a subshell type can be converted to an incoherent photoatomic
// reaction type enum
TEUCHOS_UNIT_TEST( PhotoatomicReactionType,
                   convertSubshellEnumToIncoherentPhotoatomicReactionEnum )
{
  MonteCarlo::PhotoatomicReactionType reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum(
                                                            Data::K_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::L1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::L1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::L2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::L2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::L3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::L3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::M1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::M2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::M3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::M4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::M5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::N1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::N2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::N3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::N4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::N5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::N6_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::N7_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O6_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O7_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O8_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O8_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O9_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O9_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P6_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P7_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P8_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P8_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P9_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P9_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P10_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P10_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P11_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P11_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::Q1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::Q1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::Q2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::Q2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::Q3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::Q3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that a photoatomic reaction type can be placed in an output stream
TEUCHOS_UNIT_TEST( PhotoatomicReactionType, ostream_operator )
{
  std::ostringstream oss;

  oss << MonteCarlo::TOTAL_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Total Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Total Absorption Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Total Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "K Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::L1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "L1 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::L2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "L2 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::L3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "L3 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M1 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M2 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M3 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M4 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M5 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N1 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N2 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N3 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N4 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N5 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N6 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N7 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O1 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O2 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O3 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O4 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O5 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O6 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O7 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O8_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O8 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O9_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O9 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P1 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P2 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P3 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P4 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P5 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P6 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P7 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P8_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P8 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P9_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P9 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P10_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P10 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P11_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P11 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::Q1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Q1 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::Q2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Q2 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::Q3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Q3 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::COHERENT_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Coherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Pair Production Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Triplet Production Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Total Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "K Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::L1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "L1 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::L2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "L2 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::L3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "L3 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M1 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M2 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M3 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M4 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "M5 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N1 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N2 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N3 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N4 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N5 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N6 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "N7 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O1 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O2 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O3 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O4 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O5 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O6 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O7 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O8 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "O9 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P1 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P2 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P3 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P4 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P5 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P6 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P7 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
      
  TEST_EQUALITY_CONST( oss.str(), "P8 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P9 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P10_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P10 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P11_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "P11 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::Q1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Q1 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::Q2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Q2 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::Q3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Q3 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::HEATING_PHOTOATOMIC_REACTION;

  TEST_EQUALITY_CONST( oss.str(), "Heating Photoatomic Reaction" );
}                   

//---------------------------------------------------------------------------//
// end tstPhotoatomicReactionTypeHelpers.cpp
//---------------------------------------------------------------------------//
