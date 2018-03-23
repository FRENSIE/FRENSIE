//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectroatomicReactionTypeHelpers.cpp
//! \author Luke Kersting
//! \brief  Adjoint Electroatomic reaction tyhpe helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReactionType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a electroatomic reaction type can be converted to a string
FRENSIE_UNIT_TEST( AdjointAdjointElectroatomicReactionType, toString )
{
  std::string reaction_name =
    Utility::toString( MonteCarlo::TOTAL_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Total Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Coupled Elastic Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Hybrid Elastic Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Cutoff Elastic Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Screened Rutherford Elastic Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Moment Preserving Elastic Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Bremsstrahlung Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::POSITRON_ANNIHILATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Positron Annihilation Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Atomic Excitation Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Total Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "K Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION  );

  FRENSIE_CHECK_EQUAL( reaction_name, "L1 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::L2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "L2 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::L3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "L3 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M1 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M2 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M3 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M4 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::M5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "M5 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N1 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N2 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N3 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION  );

  FRENSIE_CHECK_EQUAL( reaction_name, "N4 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N5 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N6 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::N7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "N7 Subshell Electroionization Adjoint Electroatomic Reaction" );
  
  reaction_name =
    Utility::toString( MonteCarlo::O1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O1 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O2 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O3 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O4 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O5 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O6 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O7 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O8_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O8 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::O9_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "O9 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P1 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P2 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P3 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P4 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P5 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P6 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P7 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P8_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P8 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P9_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P9 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P10_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P10 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::P11_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "P11 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::Q1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Q1 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::Q2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Q2 Subshell Electroionization Adjoint Electroatomic Reaction" );

  reaction_name =
    Utility::toString( MonteCarlo::Q3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( reaction_name, "Q3 Subshell Electroionization Adjoint Electroatomic Reaction" );
}

//---------------------------------------------------------------------------//
// Check that a subshell type can be converted to an incoherent electroatomic
// reaction type enum
FRENSIE_UNIT_TEST( AdjointElectroatomicReactionType,
                   convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum )
{
  MonteCarlo::AdjointElectroatomicReactionType reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum(
                                                            Data::K_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::L1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::L2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::L2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::L3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::L3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::M1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::M2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::M3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::M4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::M5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::M5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::N1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::N2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::N3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::N4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::N5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::N6_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::N7_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::N7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::O1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::O2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::O3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::O4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::O5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::O6_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::O7_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::O8_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O8_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::O9_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::O9_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::P1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::P2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::P3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::P4_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::P5_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::P6_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::P7_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::P8_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P8_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::P9_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P9_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::P10_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P10_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::P11_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::P11_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::Q1_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::Q1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::Q2_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::Q2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  reaction_type =
    MonteCarlo::convertSubshellEnumToElectroionizationAdjointElectroatomicReactionEnum( Data::Q3_SUBSHELL );

  FRENSIE_CHECK_EQUAL( reaction_type, MonteCarlo::Q3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that a electroatomic reaction type can be placed in an output stream
FRENSIE_UNIT_TEST( AdjointElectroatomicReactionType, ostream_operator )
{
  std::ostringstream oss;

  oss << MonteCarlo::TOTAL_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Total Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Coupled Elastic Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Hybrid Elastic Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Cutoff Elastic Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Screened Rutherford Elastic Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Moment Preserving Elastic Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::POSITRON_ANNIHILATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Positron Annihilation Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Bremsstrahlung Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Atomic Excitation Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Total Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "K Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "L1 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::L2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "L2 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::L3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "L3 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::M1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M1 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::M2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M2 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::M3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M3 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::M4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M4 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::M5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "M5 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N1 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N2 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N3 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N4 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N5 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N6 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "N7 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O1 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O2 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O3 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O4 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O5 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O6 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O7 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O8_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O8 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::O9_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "O9 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P1 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P2 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P3 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P4 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P5 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P6 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P7 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P8_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P8 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P9_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P9 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P10_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P10 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::P11_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "P11 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::Q1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Q1 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::Q2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Q2 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::Q3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Q3 Subshell Electroionization Adjoint Electroatomic Reaction" );

  oss.str( "" );
  oss.clear();
}

//---------------------------------------------------------------------------//
// end tstAdjointElectroatomicReactionTypeHelpers.cpp
//---------------------------------------------------------------------------//
