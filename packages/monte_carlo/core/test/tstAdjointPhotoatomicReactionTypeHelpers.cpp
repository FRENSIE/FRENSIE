//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPhotoatomicReactionTypeHelpers.cpp
//! \author Alex Robinson
//! \brief  Adjoint photoatomic reaction type helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomicReactionType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an adjoint photoatomic reaction type can be converted to a
// string
TEUCHOS_UNIT_TEST( AdjointPhotoatomicReactionType,
                   convertAdjointPhotoatomicReactionEnumToString )
{
  std::string reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Total Adjoint Photoatomic Reaction" );

  reaction_name = 
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Total Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "K Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::L1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "L1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::L2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "L2 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::L3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "L3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::M1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::M2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M2 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::M4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M4 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::M5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "M5 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::N1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::N2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N2 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::N3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::N4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N4 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::N5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N5 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::N6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N6 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::N7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "N7 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::O1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::O2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O2 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::O3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::O4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O4 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::O5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O5 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::O6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O6 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::O7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O7 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::O8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O8 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::O9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "O9 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::P1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::P2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P2 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::P3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::P4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P4 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::P5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P5 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::P6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P6 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::P7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P7 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::P8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P8 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::P9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P9 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::P10_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P10 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::P11_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "P11 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::Q1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Q1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::Q2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Q2 Subshell Incoherent Adjoint Photoatomic Reaction" );
  
  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::Q3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Q3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Coherent Adjoint Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Pair Production Photoatomic Reaction" );

  reaction_name =
    MonteCarlo::convertAdjointPhotoatomicReactionEnumToString( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( reaction_name, "Triplet Production Photoatomic Reaction" );
}

//---------------------------------------------------------------------------//
// Check that a subshell type can be converted to an incoherent adjoint
// photoatomic reaction type
TEUCHOS_UNIT_TEST( AdjointPhotoatomicReactionType,
                   convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum )
{
  MonteCarlo::AdjointPhotoatomicReactionType reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum(
                                                            Data::K_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::L1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::L1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::L2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::L2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::L3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::L3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::M1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::M2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::M3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::M4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::M5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::M5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::N1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::N2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::N3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::N4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::N5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::N6_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::N7_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::N7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O6_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O7_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O8_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O9_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::O9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P4_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P5_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P6_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P7_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P8_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P9_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P10_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P10_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P11_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::P11_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::Q1_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::Q1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::Q2_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::Q2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::Q3_SUBSHELL );

  TEST_EQUALITY_CONST( reaction_type, MonteCarlo::Q3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// end tstAdjointPhotoatomicReactionTypeHelpers.cpp
//---------------------------------------------------------------------------//
