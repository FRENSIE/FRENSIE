//---------------------------------------------------------------------------//
//!
//! \file   tstPhotoatomicReactionType.cpp
//! \author Alex Robinson
//! \brief  Photoatomic reaction type helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReactionType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a photoatomic reaction type can be converted to a string
FRENSIE_UNIT_TEST( PhotoatomicReactionType, toString )
{
  std::string reaction_name =
    Utility::toString( MonteCarlo::TOTAL_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Total Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Total Absorption Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Total Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "K Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::L1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION  );

  FRENSIE_CHECK_EQUAL( reaction_name, "L1 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::L2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "L2 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::L3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "L3 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M1 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M2 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M3 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M4 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M5 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N1 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N2 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N3 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION  );

  FRENSIE_CHECK_EQUAL( reaction_name, "N4 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N5 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N6 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N7 Subshell Incoherent Photoatomic Reaction" );
  
  reaction_name =
    Utility::toString( MonteCarlo::O1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O1 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O2 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O3 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O4 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O5 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O6 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O7 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O8_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O8 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O9_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O9 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P1 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P2 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P3 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P4 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P5 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P6 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P7 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P8_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P8 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P9_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P9 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P10_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P10 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P11_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P11 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::Q1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Q1 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::Q2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Q2 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::Q3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Q3 Subshell Incoherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Coherent Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Pair Production Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Triplet Production Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Total Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "K Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::L1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "L1 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::L2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "L2 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::L3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "L3 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M1 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M2 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M3 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M4 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M5 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N1 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N2 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N3 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N4 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N5 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N6 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N7 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O1 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O2 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O3 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O4 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O5 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O6 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O7 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O8 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O9 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P1 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P2 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P3 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P4 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P5 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P6 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P7 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P8 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P9 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P10_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P10 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P11_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P11 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::Q1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Q1 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::Q2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Q2 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::Q3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Q3 Subshell Photoelectric Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::HEATING_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Heating Photoatomic Reaction" );
}

//---------------------------------------------------------------------------//
// Check that a subshell type can be converted to a photoelectric
// photoatomic reaction type enum
FRENSIE_UNIT_TEST( PhotoatomicReactionType,
                   convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum )
{
  MonteCarlo::PhotoatomicReactionType reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum(
                                                            Data::K_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::L1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::L1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::L2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::L2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::L3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::L3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::M1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::M2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::M3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::M4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::M5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::N1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::N2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::N3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::N4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::N5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::N6_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::N7_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O6_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O7_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O8_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::O9_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P6_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P7_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P8_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P9_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P10_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P10_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::P11_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P11_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::Q1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::Q1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::Q2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::Q2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToPhotoelectricPhotoatomicReactionEnum( Data::Q3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::Q3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that a subshell type can be converted to an incoherent photoatomic
// reaction type enum
FRENSIE_UNIT_TEST( PhotoatomicReactionType,
                   convertSubshellEnumToIncoherentPhotoatomicReactionEnum )
{
  MonteCarlo::PhotoatomicReactionType reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum(
                                                            Data::K_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::L1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::L1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::L2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::L2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::L3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::L3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::M1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::M2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::M3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::M4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::M5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::N1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::N2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::N3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::N4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::N5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::N6_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::N7_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O6_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O7_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O8_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O8_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::O9_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O9_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P6_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P7_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P8_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P8_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P9_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P9_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P10_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P10_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::P11_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P11_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::Q1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::Q1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::Q2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::Q2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentPhotoatomicReactionEnum( Data::Q3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::Q3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that a photoatomic reaction type can be placed in an output stream
FRENSIE_UNIT_TEST( PhotoatomicReactionType, ostream_operator )
{
  std::ostringstream oss;

  oss << MonteCarlo::TOTAL_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Total Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Total Absorption Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Total Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "K Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::L1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "L1 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::L2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "L2 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::L3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "L3 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M1 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M2 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M3 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M4 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M5 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N1 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N2 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N3 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N4 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N5 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N6 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N7 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O1 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O2 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O3 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O4 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O5 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O6 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O7 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O8_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O8 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O9_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O9 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P1 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P2 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P3 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P4 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P5 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P6 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P7 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P8_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P8 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P9_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P9 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P10_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P10 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P11_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P11 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::Q1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Q1 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::Q2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Q2 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::Q3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Q3 Subshell Incoherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::COHERENT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Coherent Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Pair Production Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Triplet Production Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Total Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "K Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::L1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "L1 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::L2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "L2 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::L3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "L3 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M1 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M2 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M3 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M4 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M5 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N1 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N2 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N3 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N4 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N5 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N6 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N7 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O1 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O2 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O3 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O4 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O5 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O6 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O7 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O8 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O9 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P1 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P2 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P3 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P4 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P5 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P6 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P7 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
      
  FRENSIE_CHECK_EQUAL( oss.str(), "P8 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P9 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P10_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P10 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P11_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P11 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::Q1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Q1 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::Q2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Q2 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::Q3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Q3 Subshell Photoelectric Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::HEATING_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Heating Photoatomic Reaction" );
}

//---------------------------------------------------------------------------//
// Check that a photoatomic reaction type can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( PhotoatomicReactionType,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_photoatomic_reaction_type" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    MonteCarlo::PhotoatomicReactionType type_1 = MonteCarlo::TOTAL_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_2 = MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_3 = MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_4 = MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_5 = MonteCarlo::L1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_6 = MonteCarlo::L2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_7 = MonteCarlo::L3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_8 = MonteCarlo::M1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_9 = MonteCarlo::M2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_10 = MonteCarlo::M3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_11 = MonteCarlo::M4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_12 = MonteCarlo::M5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_13 = MonteCarlo::N1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_14 = MonteCarlo::N2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_15 = MonteCarlo::N3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_16 = MonteCarlo::N4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_17 = MonteCarlo::N5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_18 = MonteCarlo::N6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_19 = MonteCarlo::N7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_20 = MonteCarlo::O1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_21 = MonteCarlo::O2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_22 = MonteCarlo::O3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_23 = MonteCarlo::O4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_24 = MonteCarlo::O5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_25 = MonteCarlo::O6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_26 = MonteCarlo::O7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_27 = MonteCarlo::O8_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_28 = MonteCarlo::O9_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_29 = MonteCarlo::P1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_30 = MonteCarlo::P2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_31 = MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_32 = MonteCarlo::P4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_33 = MonteCarlo::P5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_34 = MonteCarlo::P6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_35 = MonteCarlo::P7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_36 = MonteCarlo::P8_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_37 = MonteCarlo::P9_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_38 = MonteCarlo::P10_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_39 = MonteCarlo::P11_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_40 = MonteCarlo::Q1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_41 = MonteCarlo::Q2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_42 = MonteCarlo::Q3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_43 = MonteCarlo::COHERENT_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_44 = MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_45 = MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_46 = MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_47 = MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_48 = MonteCarlo::L1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_49 = MonteCarlo::L2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_50 = MonteCarlo::L3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_51 = MonteCarlo::M1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_52 = MonteCarlo::M2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_53 = MonteCarlo::M3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_54 = MonteCarlo::M4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_55 = MonteCarlo::M5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_56 = MonteCarlo::N1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_57 = MonteCarlo::N2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_58 = MonteCarlo::N3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_59 = MonteCarlo::N4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_60 = MonteCarlo::N5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_61 = MonteCarlo::N6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_62 = MonteCarlo::N7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_63 = MonteCarlo::O1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_64 = MonteCarlo::O2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_65 = MonteCarlo::O3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_66 = MonteCarlo::O4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_67 = MonteCarlo::O5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_68 = MonteCarlo::O6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_69 = MonteCarlo::O7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_70 = MonteCarlo::O8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_71 = MonteCarlo::O9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_72 = MonteCarlo::P1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_73 = MonteCarlo::P2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_74 = MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_75 = MonteCarlo::P4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_76 = MonteCarlo::P5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_77 = MonteCarlo::P6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_78 = MonteCarlo::P7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_79 = MonteCarlo::P8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_80 = MonteCarlo::P9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_81 = MonteCarlo::P10_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_82 = MonteCarlo::P11_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_83 = MonteCarlo::Q1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_84 = MonteCarlo::Q2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_85 = MonteCarlo::Q3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION;
    MonteCarlo::PhotoatomicReactionType type_86 = MonteCarlo::HEATING_PHOTOATOMIC_REACTION;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_1 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_2 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_3 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_4 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_5 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_6 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_7 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_8 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_9 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_10 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_11 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_12 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_13 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_14 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_15 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_16 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_17 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_18 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_19 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_20 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_21 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_22 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_23 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_24 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_25 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_26 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_27 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_28 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_29 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_30 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_31 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_32 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_33 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_34 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_35 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_36 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_37 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_38 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_39 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_40 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_41 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_42 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_43 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_44 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_45 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_46 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_47 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_48 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_49 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_50 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_51 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_52 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_53 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_54 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_55 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_56 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_57 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_58 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_59 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_60 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_61 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_62 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_63 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_64 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_65 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_66 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_67 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_68 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_69 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_70 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_71 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_72 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_73 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_74 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_75 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_76 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_77 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_78 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_79 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_80 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_81 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_82 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_83 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_84 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_85 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_86 ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::PhotoatomicReactionType type_1, type_2, type_3, type_4, type_5,
    type_6, type_7, type_8, type_9, type_10, type_11, type_12, type_13,
    type_14, type_15, type_16, type_17, type_18, type_19, type_20, type_21,
    type_22, type_23, type_24, type_25, type_26, type_27, type_28, type_29,
    type_30, type_31, type_32, type_33, type_34, type_35, type_36, type_37,
    type_38, type_39, type_40, type_41, type_42, type_43, type_44, type_45,
    type_46, type_47, type_48, type_49, type_50, type_51, type_52, type_53,
    type_54, type_55, type_56, type_57, type_58, type_59, type_60, type_61,
    type_62, type_63, type_64, type_65, type_66, type_67, type_68, type_69,
    type_70, type_71, type_72, type_73, type_74, type_75, type_76, type_77,
    type_78, type_79, type_80, type_81, type_82, type_83, type_84, type_85,
    type_86;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_1 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_2 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_3 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_4 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_5 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_6 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_7 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_8 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_9 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_10 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_11 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_12 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_13 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_14 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_15 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_16 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_17 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_18 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_19 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_20 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_21 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_22 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_23 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_24 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_25 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_26 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_27 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_28 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_29 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_30 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_31 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_32 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_33 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_34 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_35 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_36 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_37 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_38 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_39 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_40 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_41 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_42 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_43 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_44 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_45 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_46 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_47 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_48 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_49 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_50 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_51 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_52 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_53 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_54 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_55 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_56 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_57 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_58 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_59 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_60 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_61 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_62 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_63 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_64 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_65 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_66 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_67 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_68 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_69 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_70 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_71 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_72 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_73 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_74 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_75 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_76 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_77 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_78 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_79 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_80 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_81 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_82 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_83 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_84 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_85 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_86 ) );

  iarchive.reset();
  
  FRENSIE_CHECK_EQUAL( type_1, MonteCarlo::TOTAL_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_2, MonteCarlo::TOTAL_ABSORPTION_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_3, MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_4, MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_5, MonteCarlo::L1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_6, MonteCarlo::L2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_7, MonteCarlo::L3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_8, MonteCarlo::M1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_9, MonteCarlo::M2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_10, MonteCarlo::M3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_11, MonteCarlo::M4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_12, MonteCarlo::M5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_13, MonteCarlo::N1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_14, MonteCarlo::N2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_15, MonteCarlo::N3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_16, MonteCarlo::N4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_17, MonteCarlo::N5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_18, MonteCarlo::N6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_19, MonteCarlo::N7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_20, MonteCarlo::O1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_21, MonteCarlo::O2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_22, MonteCarlo::O3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_23, MonteCarlo::O4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_24, MonteCarlo::O5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_25, MonteCarlo::O6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_26, MonteCarlo::O7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_27, MonteCarlo::O8_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_28, MonteCarlo::O9_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_29, MonteCarlo::P1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_30, MonteCarlo::P2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_31, MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_32, MonteCarlo::P4_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_33, MonteCarlo::P5_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_34, MonteCarlo::P6_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_35, MonteCarlo::P7_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_36, MonteCarlo::P8_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_37, MonteCarlo::P9_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_38, MonteCarlo::P10_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_39, MonteCarlo::P11_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_40, MonteCarlo::Q1_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_41, MonteCarlo::Q2_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_42, MonteCarlo::Q3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_43, MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_44, MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_45, MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_46, MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_47, MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_48, MonteCarlo::L1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_49, MonteCarlo::L2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_50, MonteCarlo::L3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_51, MonteCarlo::M1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_52, MonteCarlo::M2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_53, MonteCarlo::M3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_54, MonteCarlo::M4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_55, MonteCarlo::M5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_56, MonteCarlo::N1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_57, MonteCarlo::N2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_58, MonteCarlo::N3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_59, MonteCarlo::N4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_60, MonteCarlo::N5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_61, MonteCarlo::N6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_62, MonteCarlo::N7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_63, MonteCarlo::O1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_64, MonteCarlo::O2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_65, MonteCarlo::O3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_66, MonteCarlo::O4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_67, MonteCarlo::O5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_68, MonteCarlo::O6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_69, MonteCarlo::O7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_70, MonteCarlo::O8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_71, MonteCarlo::O9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_72, MonteCarlo::P1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_73, MonteCarlo::P2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_74, MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_75, MonteCarlo::P4_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_76, MonteCarlo::P5_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_77, MonteCarlo::P6_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_78, MonteCarlo::P7_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_79, MonteCarlo::P8_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_80, MonteCarlo::P9_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_81, MonteCarlo::P10_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_82, MonteCarlo::P11_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_83, MonteCarlo::Q1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_84, MonteCarlo::Q2_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_85, MonteCarlo::Q3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_86, MonteCarlo::HEATING_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// end tstPhotoatomicReactionType.cpp
//---------------------------------------------------------------------------//
