//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPhotoatomicReactionType.cpp
//! \author Alex Robinson
//! \brief  Adjoint photoatomic reaction type helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomicReactionType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an adjoint photoatomic reaction type can be converted to a
// string
FRENSIE_UNIT_TEST( AdjointPhotoatomicReactionType, toString )
{
  std::string reaction_name =
    Utility::toString( MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Total Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::TOTAL_ABSORPTION_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Total Absorption Adjoint Photoatomic Reaction" );

  reaction_name = 
    Utility::toString( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Total Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "K Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::L1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "L1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::L2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "L2 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::L3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "L3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M2 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M4 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M5 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N2 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N4 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N5 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N6 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N7 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O2 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O4 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O5 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O6 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O7 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O8 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O9 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P2 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P4 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P5 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P6 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P7 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P8 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P9 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P10_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P10 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P11_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P11 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::Q1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Q1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::Q2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Q2 Subshell Incoherent Adjoint Photoatomic Reaction" );
  
  reaction_name =
    Utility::toString( MonteCarlo::Q3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Q3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Coherent Adjoint Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Pair Production Photoatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Triplet Production Photoatomic Reaction" );
}

//---------------------------------------------------------------------------//
// Check that a subshell type can be converted to an incoherent adjoint
// photoatomic reaction type
FRENSIE_UNIT_TEST( AdjointPhotoatomicReactionType,
                   convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum )
{
  MonteCarlo::AdjointPhotoatomicReactionType reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum(
                                                            Data::K_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::L1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::L1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::L2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::L2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::L3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::L3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::M1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::M2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::M3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::M4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::M5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::N1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::N2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::N3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::N4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::N5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::N6_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::N7_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O6_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O7_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O8_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::O9_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P6_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P7_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P8_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P9_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P10_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P10_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::P11_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P11_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::Q1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::Q1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::Q2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::Q2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToIncoherentAdjointPhotoatomicReactionEnum( Data::Q3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::Q3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photoatomic reaction type can be placed in an
// output stream
FRENSIE_UNIT_TEST( AdjointPhotoatomicReactionType, ostream_operator )
{
  std::ostringstream oss;

  oss << MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Total Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TOTAL_ABSORPTION_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Total Absorption Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Total Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "K Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
 
  oss << MonteCarlo::L1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "L1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::L2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "L2 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::L3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "L3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M2 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M4 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::M5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M5 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N2 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N4 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N5 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N6 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N7 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O2 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O4 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O5 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O6 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O7 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O8 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::O9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O9 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P2 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P4 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P5 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P6 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P7 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P8 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P9 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P10_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P10 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::P11_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P11 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::Q1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Q1 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::Q2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Q2 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::Q3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Q3 Subshell Incoherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Coherent Adjoint Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Pair Production Photoatomic Reaction" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Triplet Production Photoatomic Reaction" );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photoatomic reaction type can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( AdjointPhotoatomicReactionType,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_adjoint_aphotoatomic_reaction_type" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::AdjointPhotoatomicReactionType type_1 = MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_2 = MonteCarlo::TOTAL_ABSORPTION_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_3 = MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_4 = MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_5 = MonteCarlo::L1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_6 = MonteCarlo::L2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_7 = MonteCarlo::L3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_8 = MonteCarlo::M1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_9 = MonteCarlo::M2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_10 = MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_11 = MonteCarlo::M4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_12 = MonteCarlo::M5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_13 = MonteCarlo::N1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_14 = MonteCarlo::N2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_15 = MonteCarlo::N3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_16 = MonteCarlo::N4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_17 = MonteCarlo::N5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_18 = MonteCarlo::N6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_19 = MonteCarlo::N7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_20 = MonteCarlo::O1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_21 = MonteCarlo::O2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_22 = MonteCarlo::O3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_23 = MonteCarlo::O4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_24 = MonteCarlo::O5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_25 = MonteCarlo::O6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_26 = MonteCarlo::O7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_27 = MonteCarlo::O8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_28 = MonteCarlo::O9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_29 = MonteCarlo::P1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_30 = MonteCarlo::P2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_31 = MonteCarlo::P3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_32 = MonteCarlo::P4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_33 = MonteCarlo::P5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_34 = MonteCarlo::P6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_35 = MonteCarlo::P7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_36 = MonteCarlo::P8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_37 = MonteCarlo::P9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_38 = MonteCarlo::P10_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_39 = MonteCarlo::P11_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_40 = MonteCarlo::Q1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_41 = MonteCarlo::Q2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_42 = MonteCarlo::Q3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_43 = MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_44 = MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION;
    MonteCarlo::AdjointPhotoatomicReactionType type_45 = MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION;

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
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::AdjointPhotoatomicReactionType type_1, type_2, type_3, type_4,
    type_5, type_6, type_7, type_8, type_9, type_10, type_11, type_12, type_13,
    type_14, type_15, type_16, type_17, type_18, type_19, type_20, type_21,
    type_22, type_23, type_24, type_25, type_26, type_27, type_28, type_29,
    type_30, type_31, type_32, type_33, type_34, type_35, type_36, type_37,
    type_38, type_39, type_40, type_41, type_42, type_43, type_44, type_45;

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

  iarchive.reset();
  
  FRENSIE_CHECK_EQUAL( type_1, MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_2, MonteCarlo::TOTAL_ABSORPTION_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_3, MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_4, MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_5, MonteCarlo::L1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_6, MonteCarlo::L2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_7, MonteCarlo::L3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_8, MonteCarlo::M1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_9, MonteCarlo::M2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_10, MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_11, MonteCarlo::M4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_12, MonteCarlo::M5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_13, MonteCarlo::N1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_14, MonteCarlo::N2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_15, MonteCarlo::N3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_16, MonteCarlo::N4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_17, MonteCarlo::N5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_18, MonteCarlo::N6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_19, MonteCarlo::N7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_20, MonteCarlo::O1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_21, MonteCarlo::O2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_22, MonteCarlo::O3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_23, MonteCarlo::O4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_24, MonteCarlo::O5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_25, MonteCarlo::O6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_26, MonteCarlo::O7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_27, MonteCarlo::O8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_28, MonteCarlo::O9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_29, MonteCarlo::P1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_30, MonteCarlo::P2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_31, MonteCarlo::P3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_32, MonteCarlo::P4_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_33, MonteCarlo::P5_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_34, MonteCarlo::P6_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_35, MonteCarlo::P7_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_36, MonteCarlo::P8_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_37, MonteCarlo::P9_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_38, MonteCarlo::P10_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_39, MonteCarlo::P11_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_40, MonteCarlo::Q1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_41, MonteCarlo::Q2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_42, MonteCarlo::Q3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_43, MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_44, MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_45, MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION );
}
  
//---------------------------------------------------------------------------//
// end tstAdjointPhotoatomicReactionType.cpp
//---------------------------------------------------------------------------//
