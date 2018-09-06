//---------------------------------------------------------------------------//
//!
//! \file   tstNuclearReactionType.cpp
//! \author Alex Robinson
//! \brief  Nuclear reaction type helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <fstream>

// FRENSIE Includes
#include "MonteCarlo_NuclearReactionType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a raw mt number can be converted to a nuclear reaction
FRENSIE_UNIT_TEST( NuclearReactionType,
                   convertMTNumberToNuclearReactionType )
{
  MonteCarlo::NuclearReactionType type =
    MonteCarlo::convertMTNumberToNuclearReactionType( 1 );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__TOTAL_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 2 );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_ELASTIC_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 3 );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_NON_ELASTIC_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 4 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_INELASTIC_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 5 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ANYTHING_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 11 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_D_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 16 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 17 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__3N_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 18 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__TOTAL_FISSION_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 19 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__FISSION_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 20 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_FISSION_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 21 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_FISSION_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 22 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_ALPHA_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 24 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_ALPHA_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 25 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__3N_ALPHA_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 27 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__TOTAL_ABSORPTION_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 28 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_P_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 29 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 30 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 32 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_D_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 33 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 34 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 35 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_D_2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 36 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_T_2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 37 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__4N_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 38 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__3N_FISSION_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 41 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_P_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 42 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__3N_P_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 44 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_2P_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 45 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_P_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 51 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_1_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 52 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_2_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 53 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 54 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_4_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 55 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_5_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 56 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_6_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 57 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_7_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 58 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_8_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 59 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_9_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 60 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_10_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 61 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_11_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 62 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_12_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 63 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_13_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 64 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_14_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 65 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_15_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 66 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_16_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 67 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_17_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 68 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_18_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 69 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_19_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 70 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_20_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 71 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_21_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 72 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_22_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 73 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_23_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 74 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_24_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 75 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_25_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 76 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_26_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 77 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_27_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 78 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_28_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 79 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_29_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 80 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_30_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 81 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_31_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 82 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_32_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 83 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_33_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 84 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_34_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 85 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_35_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 86 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_36_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 87 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_37_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 88 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_38_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 89 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_39_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 90 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_EXCITED_STATE_40_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 91 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_CONTINUUM_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 101 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__CAPTURE_REACTION );

  type = MonteCarlo::convertMTNumberToNuclearReactionType( 102 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__GAMMA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 103 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 104 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 105 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 106 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 107 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 108 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 109 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__3ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 111 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2P_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 112 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 113 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 114 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 115 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_D_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 116 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 117 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 152 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__5N_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 153 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__6N_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 154 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 155 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 156 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__4N_P_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 157 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__3N_D_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 158 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_D_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 159 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_P_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 160 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__7N_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 161 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__8N_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 162 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__5N_P_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 163 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__6N_P_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 164 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__7N_P_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 165 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__4N_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 166 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__5N_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 167 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__6N_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 168 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__7N_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 169 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__4N_D_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 170 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__5N_D_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 171 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__6N_D_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 172 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__3N_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 173 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__4N_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 174 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__5N_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 175 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__6N_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 176 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 177 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__3N_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 178 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__4N_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 179 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__3N_2P_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 180 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__3N_2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 181 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__3N_P_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 182 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 183 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_P_D_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 184 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_P_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 185 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_D_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 186 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_P_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 187 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_D_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 188 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_T_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 189 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_T_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 190 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_2P_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 191 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 192 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 193 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 194 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__4N_2P_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 195 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__4N_2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 196 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__4N_P_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 197 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__3P_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 198 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__N_3P_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 199 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__3N_2P_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 200 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__5N_2P_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 201 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__TOTAL_N_PRODUCTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 202 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__TOTAL_GAMMA_PRODUCTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 203 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__TOTAL_P_PRODUCTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 204 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__TOTAL_D_PRODUCTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 205 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__TOTAL_T_PRODUCTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 206 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__TOTAL_HE3_PRODUCTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 207 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__TOTAL_ALPHA_PRODUCTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 301 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__AVERAGE_HEATING );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 444 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__DAMAGE );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 600 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_0_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 601 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_1_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 602 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_2_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 603 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 604 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_4_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 605 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_5_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 606 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_6_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 607 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_7_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 608 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_8_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 609 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_9_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 610 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_10_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 611 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_11_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 612 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_12_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 613 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_13_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 614 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_14_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 615 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_15_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 616 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_16_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 617 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_17_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 618 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_18_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 619 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_19_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 620 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_20_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 621 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_21_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 622 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_22_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 623 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_23_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 624 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_24_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 625 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_25_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 626 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_26_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 627 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_27_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 628 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_28_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 629 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_29_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 630 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_30_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 631 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_31_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 632 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_32_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 633 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_33_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 634 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_34_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 635 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_35_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 636 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_36_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 637 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_37_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 638 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_38_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 639 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_39_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 640 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_40_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 641 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_41_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 642 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_42_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 643 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_43_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 644 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_44_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 645 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_45_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 646 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_46_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 647 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_47_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 648 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_EXCITED_STATE_48_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 649 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__P_CONTINUUM_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 650 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_0_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 651 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_1_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 652 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_2_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 653 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 654 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_4_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 655 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_5_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 656 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_6_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 657 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_7_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 658 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_8_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 659 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_9_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 660 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_10_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 661 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_11_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 662 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_12_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 663 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_13_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 664 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_14_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 665 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_15_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 666 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_16_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 667 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_17_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 668 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_18_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 669 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_19_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 670 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_20_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 671 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_21_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 672 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_22_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 673 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_23_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 674 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_24_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 675 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_25_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 676 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_26_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 677 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_27_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 678 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_28_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 679 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_29_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 680 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_30_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 681 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_31_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 682 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_32_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 683 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_33_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 684 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_34_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 685 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_35_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 686 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_36_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 687 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_37_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 688 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_38_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 689 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_39_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 690 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_40_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 691 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_41_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 692 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_42_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 693 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_43_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 694 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_44_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 695 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_45_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 696 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_46_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 697 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_47_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 698 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_EXCITED_STATE_48_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 699 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__D_CONTINUUM_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 700 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_0_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 701 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_1_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 702 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_2_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 703 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 704 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_4_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 705 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_5_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 706 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_6_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 707 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_7_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 708 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_8_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 709 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_9_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 710 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_10_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 711 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_11_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 712 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_12_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 713 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_13_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 714 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_14_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 715 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_15_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 716 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_16_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 717 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_17_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 718 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_18_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 719 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_19_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 720 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_20_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 721 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_21_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 722 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_22_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 723 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_23_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 724 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_24_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 725 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_25_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 726 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_26_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 727 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_27_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 728 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_28_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 729 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_29_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 730 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_30_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 731 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_31_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 732 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_32_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 733 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_33_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 734 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_34_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 735 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_35_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 736 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_36_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 737 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_37_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 738 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_38_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 739 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_39_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 740 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_40_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 741 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_41_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 742 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_42_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 743 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_43_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 744 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_44_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 745 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_45_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 746 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_46_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 747 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_47_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 748 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_EXCITED_STATE_48_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 749 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__T_CONTINUUM_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 750 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_0_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 751 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_1_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 752 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_2_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 753 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 754 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_4_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 755 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_5_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 756 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_6_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 757 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_7_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 758 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_8_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 759 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_9_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 760 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_10_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 761 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_11_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 762 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_12_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 763 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_13_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 764 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_14_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 765 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_15_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 766 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_16_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 767 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_17_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 768 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_18_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 769 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_19_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 770 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_20_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 771 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_21_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 772 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_22_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 773 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_23_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 774 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_24_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 775 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_25_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 776 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_26_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 777 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_27_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 778 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_28_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 779 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_29_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 780 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_30_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 781 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_31_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 782 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_32_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 783 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_33_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 784 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_34_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 785 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_35_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 786 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_36_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 787 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_37_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 788 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_38_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 789 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_39_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 790 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_40_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 791 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_41_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 792 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_42_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 793 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_43_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 794 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_44_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 795 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_45_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 796 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_46_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 797 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_47_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 798 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_EXCITED_STATE_48_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 799 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__HE3_CONTINUUM_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 800 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_0_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 801 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_1_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 802 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_2_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 803 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 804 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_4_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 805 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_5_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 806 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_6_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 807 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_7_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 808 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_8_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 809 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_9_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 810 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_10_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 811 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_11_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 812 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_12_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 813 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_13_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 814 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_14_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 815 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_15_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 816 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_16_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 817 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_17_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 818 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_18_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 819 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_19_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 820 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_20_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 821 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_21_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 822 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_22_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 823 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_23_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 824 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_24_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 825 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_25_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 826 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_26_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 827 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_27_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 828 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_28_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 829 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_29_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 830 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_30_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 831 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_31_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 832 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_32_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 833 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_33_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 834 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_34_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 835 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_35_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 836 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_36_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 837 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_37_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 838 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_38_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 839 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_39_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 840 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_40_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 841 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_41_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 842 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_42_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 843 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_43_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 844 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_44_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 845 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_45_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 846 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_46_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 847 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_47_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 848 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_EXCITED_STATE_48_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 849 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__ALPHA_CONTINUUM_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 875 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_EXCITED_STATE_0_REACTION ); 
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 876 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_EXCITED_STATE_1_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 877 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_EXCITED_STATE_2_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 878 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_EXCITED_STATE_3_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 879 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_EXCITED_STATE_4_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 880 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_EXCITED_STATE_5_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 881 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_EXCITED_STATE_6_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 882 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_EXCITED_STATE_7_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 883 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_EXCITED_STATE_8_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 884 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_EXCITED_STATE_9_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 885 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_EXCITED_STATE_10_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 886 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_EXCITED_STATE_11_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 887 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_EXCITED_STATE_12_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 888 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_EXCITED_STATE_13_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 889 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_EXCITED_STATE_14_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 890 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_EXCITED_STATE_15_REACTION );
  
  type = MonteCarlo::convertMTNumberToNuclearReactionType( 891 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::N__2N_CONTINUUM_REACTION );
}

//---------------------------------------------------------------------------//
// Check that a nuclear reaction type can be converted to a string
FRENSIE_UNIT_TEST( NuclearReactionType, toString )
{
  std::string type_string =
    Utility::toString( MonteCarlo::N__TOTAL_REACTION );
  
  FRENSIE_CHECK_EQUAL( type_string, "(n,total)" );

  type_string = Utility::toString( MonteCarlo::N__N_ELASTIC_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,elastic)" );

  type_string = Utility::toString( MonteCarlo::N__N_NON_ELASTIC_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,non-elastic)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_INELASTIC_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n)" );
  
  type_string = Utility::toString( MonteCarlo::N__ANYTHING_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,anything)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n-d)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n)" );
  
  type_string = Utility::toString( MonteCarlo::N__3N_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,3n)" );
  
  type_string = Utility::toString( MonteCarlo::N__TOTAL_FISSION_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,total_fission)" );

  type_string = Utility::toString( MonteCarlo::N__FISSION_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,fission)" );

  type_string = Utility::toString( MonteCarlo::N__N_FISSION_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-fission)" );

  type_string = Utility::toString( MonteCarlo::N__2N_FISSION_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n-fission)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__3N_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,3n-alpha)" );

  type_string = Utility::toString( MonteCarlo::N__TOTAL_ABSORPTION_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,total_absorption)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-p)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n-2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-d)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-t)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-he3)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_D_2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-d-2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_T_2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-t-2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__4N_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,4n)" );

  type_string = Utility::toString( MonteCarlo::N__3N_FISSION_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,3n-fission)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n-p)" );
  
  type_string = Utility::toString( MonteCarlo::N__3N_P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,3n-p)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_2P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-2p)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_P_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-p-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_1_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_1)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_2_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_2)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_3)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_4_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_4)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_5_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_5)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_6_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_6)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_7_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_7)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_8_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_8)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_9_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_9)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_10_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_10)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_11_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_11)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_12_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_12)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_13_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_13)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_14_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_14)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_15_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_15)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_16_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_16)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_17_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_17)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_18_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_18)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_19_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_19)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_20_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_20)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_21_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_21)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_22_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_22)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_23_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_23)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_24_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_24)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_25_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_25)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_26_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_26)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_27_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_27)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_28_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_28)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_29_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_29)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_30_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_30)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_31_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_31)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_32_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_32)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_33_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_33)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_34_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_34)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_35_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_35)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_36_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_36)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_37_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_37)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_38_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_38)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_39_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_39)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_EXCITED_STATE_40_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_40)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_CONTINUUM_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_continuum)" );
  
  type_string = Utility::toString( MonteCarlo::N__CAPTURE_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,capture)" );

  type_string = Utility::toString( MonteCarlo::N__GAMMA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,gamma)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__3ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,3alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__2P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2p)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t-2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d-2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p-d)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p-t)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__5N_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,5n)" );
  
  type_string = Utility::toString( MonteCarlo::N__6N_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,6n)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n-t)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__4N_P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,4n-p)" );
  
  type_string = Utility::toString( MonteCarlo::N__3N_D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,3n-d)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_D_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-d-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_P_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n-p-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__7N_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,7n)" );
  
  type_string = Utility::toString( MonteCarlo::N__8N_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,8n)" );
  
  type_string = Utility::toString( MonteCarlo::N__5N_P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,5n-p)" );
  
  type_string = Utility::toString( MonteCarlo::N__6N_P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,6n-p)" );
  
  type_string = Utility::toString( MonteCarlo::N__7N_P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,7n-p)" );
  
  type_string = Utility::toString( MonteCarlo::N__4N_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,4n-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__5N_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,5n-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__6N_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,6n-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__7N_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,7n-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__4N_D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,4n-d)" );
  
  type_string = Utility::toString( MonteCarlo::N__5N_D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,5n-d)" );
  
  type_string = Utility::toString( MonteCarlo::N__6N_D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,6n-d)" );
  
  type_string = Utility::toString( MonteCarlo::N__3N_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,3n-t)" );
  
  type_string = Utility::toString( MonteCarlo::N__4N_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,4n-t)" );
  
  type_string = Utility::toString( MonteCarlo::N__5N_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,5n-t)" );
  
  type_string = Utility::toString( MonteCarlo::N__6N_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,6n-t)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n-he3)" );
  
  type_string = Utility::toString( MonteCarlo::N__3N_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,3n-he3)" );
  
  type_string = Utility::toString( MonteCarlo::N__4N_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,4n-he3)" );
  
  type_string = Utility::toString( MonteCarlo::N__3N_2P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,3n-2p)" );
  
  type_string = Utility::toString( MonteCarlo::N__3N_2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,3n-2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__3N_P_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,3n-p-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d-t)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_P_D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-p-d)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_P_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-p-t)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_D_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-d-t)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_P_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-p-he3)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_D_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-d-he3)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_T_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-t-he3)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_T_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-t-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_2P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n-2p)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p-he3)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d-he3)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__4N_2P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,4n-2p)" );
  
  type_string = Utility::toString( MonteCarlo::N__4N_2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,4n-2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__4N_P_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,4n-p-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__3P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,3p)" );
  
  type_string = Utility::toString( MonteCarlo::N__N_3P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n-3p)" );
  
  type_string = Utility::toString( MonteCarlo::N__3N_2P_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,3n-2p-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::N__5N_2P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,5n-2p)" );
  
  type_string = Utility::toString( MonteCarlo::N__TOTAL_N_PRODUCTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,n_production)" );
  
  type_string = Utility::toString( MonteCarlo::N__TOTAL_GAMMA_PRODUCTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,gamma_production)" );
  
  type_string = Utility::toString( MonteCarlo::N__TOTAL_P_PRODUCTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_production)" );
  
  type_string = Utility::toString( MonteCarlo::N__TOTAL_D_PRODUCTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_production)" );
  
  type_string = Utility::toString( MonteCarlo::N__TOTAL_T_PRODUCTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_production)" );
  
  type_string = Utility::toString( MonteCarlo::N__TOTAL_HE3_PRODUCTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_production)" );
  
  type_string = Utility::toString( MonteCarlo::N__TOTAL_ALPHA_PRODUCTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_production)" );
  
  type_string = Utility::toString( MonteCarlo::N__AVERAGE_HEATING );

  FRENSIE_CHECK_EQUAL( type_string, "(n,heating)" );
  
  type_string = Utility::toString( MonteCarlo::N__DAMAGE );

  FRENSIE_CHECK_EQUAL( type_string, "(n,damage)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_0_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_0)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_1_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_1)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_2_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_2)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_3)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_4_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_4)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_5_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_5)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_6_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_6)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_7_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_7)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_8_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_8)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_9_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_9)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_10_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_10)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_11_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_11)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_12_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_12)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_13_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_13)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_14_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_14)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_15_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_15)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_16_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_16)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_17_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_17)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_18_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_18)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_19_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_19)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_20_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_20)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_21_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_21)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_22_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_22)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_23_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_23)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_24_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_24)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_25_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_25)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_26_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_26)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_27_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_27)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_28_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_28)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_29_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_29)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_30_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_30)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_31_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_31)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_32_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_32)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_33_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_33)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_34_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_34)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_35_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_35)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_36_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_36)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_37_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_37)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_38_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_38)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_39_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_39)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_40_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_40)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_41_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_41)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_42_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_42)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_43_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_43)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_44_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_44)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_45_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_45)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_46_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_46)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_47_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_47)" );
  
  type_string = Utility::toString( MonteCarlo::N__P_EXCITED_STATE_48_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_48)" );

  type_string = Utility::toString( MonteCarlo::N__P_CONTINUUM_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,p_continuum)" );

  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_0_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_0)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_1_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_1)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_2_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_2)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_3)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_4_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_4)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_5_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_5)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_6_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_6)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_7_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_7)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_8_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_8)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_9_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_9)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_10_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_10)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_11_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_11)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_12_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_12)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_13_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_13)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_14_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_14)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_15_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_15)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_16_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_16)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_17_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_17)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_18_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_18)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_19_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_19)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_20_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_20)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_21_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_21)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_22_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_22)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_23_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_23)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_24_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_24)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_25_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_25)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_26_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_26)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_27_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_27)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_28_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_28)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_29_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_29)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_30_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_30)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_31_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_31)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_32_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_32)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_33_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_33)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_34_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_34)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_35_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_35)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_36_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_36)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_37_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_37)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_38_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_38)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_39_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_39)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_40_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_40)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_41_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_41)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_42_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_42)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_43_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_43)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_44_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_44)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_45_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_45)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_46_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_46)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_47_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_47)" );
  
  type_string = Utility::toString( MonteCarlo::N__D_EXCITED_STATE_48_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_48)" );

  type_string = Utility::toString( MonteCarlo::N__D_CONTINUUM_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,d_continuum)" );

  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_0_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_0)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_1_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_1)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_2_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_2)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_3)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_4_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_4)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_5_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_5)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_6_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_6)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_7_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_7)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_8_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_8)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_9_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_9)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_10_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_10)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_11_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_11)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_12_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_12)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_13_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_13)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_14_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_14)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_15_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_15)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_16_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_16)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_17_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_17)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_18_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_18)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_19_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_19)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_20_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_20)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_21_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_21)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_22_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_22)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_23_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_23)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_24_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_24)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_25_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_25)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_26_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_26)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_27_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_27)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_28_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_28)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_29_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_29)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_30_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_30)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_31_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_31)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_32_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_32)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_33_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_33)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_34_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_34)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_35_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_35)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_36_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_36)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_37_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_37)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_38_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_38)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_39_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_39)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_40_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_40)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_41_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_41)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_42_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_42)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_43_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_43)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_44_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_44)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_45_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_45)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_46_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_46)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_47_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_47)" );
  
  type_string = Utility::toString( MonteCarlo::N__T_EXCITED_STATE_48_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_48)" );

  type_string = Utility::toString( MonteCarlo::N__T_CONTINUUM_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,t_continuum)" );

  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_0_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_0)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_1_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_1)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_2_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_2)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_3)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_4_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_4)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_5_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_5)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_6_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_6)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_7_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_7)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_8_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_8)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_9_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_9)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_10_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_10)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_11_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_11)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_12_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_12)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_13_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_13)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_14_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_14)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_15_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_15)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_16_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_16)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_17_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_17)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_18_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_18)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_19_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_19)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_20_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_20)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_21_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_21)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_22_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_22)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_23_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_23)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_24_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_24)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_25_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_25)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_26_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_26)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_27_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_27)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_28_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_28)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_29_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_29)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_30_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_30)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_31_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_31)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_32_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_32)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_33_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_33)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_34_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_34)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_35_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_35)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_36_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_36)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_37_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_37)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_38_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_38)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_39_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_39)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_40_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_40)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_41_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_41)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_42_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_42)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_43_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_43)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_44_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_44)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_45_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_45)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_46_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_46)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_47_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_47)" );
  
  type_string = Utility::toString( MonteCarlo::N__HE3_EXCITED_STATE_48_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_48)" );

  type_string = Utility::toString( MonteCarlo::N__HE3_CONTINUUM_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,he3_continuum)" );

  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_0_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_0)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_1_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_1)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_2_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_2)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_3)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_4_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_4)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_5_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_5)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_6_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_6)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_7_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_7)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_8_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_8)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_9_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_9)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_10_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_10)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_11_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_11)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_12_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_12)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_13_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_13)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_14_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_14)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_15_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_15)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_16_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_16)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_17_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_17)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_18_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_18)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_19_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_19)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_20_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_20)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_21_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_21)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_22_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_22)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_23_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_23)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_24_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_24)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_25_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_25)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_26_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_26)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_27_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_27)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_28_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_28)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_29_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_29)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_30_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_30)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_31_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_31)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_32_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_32)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_33_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_33)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_34_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_34)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_35_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_35)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_36_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_36)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_37_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_37)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_38_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_38)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_39_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_39)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_40_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_40)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_41_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_41)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_42_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_42)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_43_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_43)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_44_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_44)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_45_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_45)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_46_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_46)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_47_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_47)" );
  
  type_string = Utility::toString( MonteCarlo::N__ALPHA_EXCITED_STATE_48_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_48)" );

  type_string = Utility::toString( MonteCarlo::N__ALPHA_CONTINUUM_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,alpha_continuum)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_EXCITED_STATE_0_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_0)" ); 
  
  type_string = Utility::toString( MonteCarlo::N__2N_EXCITED_STATE_1_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_1)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_EXCITED_STATE_2_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_2)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_EXCITED_STATE_3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_3)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_EXCITED_STATE_4_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_4)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_EXCITED_STATE_5_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_5)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_EXCITED_STATE_6_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_6)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_EXCITED_STATE_7_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_7)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_EXCITED_STATE_8_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_8)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_EXCITED_STATE_9_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_9)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_EXCITED_STATE_10_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_10)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_EXCITED_STATE_11_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_11)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_EXCITED_STATE_12_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_12)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_EXCITED_STATE_13_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_13)" );

  type_string = Utility::toString( MonteCarlo::N__2N_EXCITED_STATE_14_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_14)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_EXCITED_STATE_15_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_15)" );
  
  type_string = Utility::toString( MonteCarlo::N__2N_CONTINUUM_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(n,2n_continuum)" );
}

//---------------------------------------------------------------------------//
// Check that a nuclear reaction type can be placed in a stream
FRENSIE_UNIT_TEST( NuclearReactionType, ostream_operator )
{
  std::ostringstream oss;
  oss << MonteCarlo::N__TOTAL_REACTION;
  
  FRENSIE_CHECK_EQUAL( oss.str(), "(n,total)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__N_ELASTIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,elastic)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__N_NON_ELASTIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,non-elastic)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_INELASTIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ANYTHING_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,anything)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n-d)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__3N_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,3n)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__TOTAL_FISSION_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,total_fission)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__FISSION_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,fission)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__N_FISSION_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-fission)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__2N_FISSION_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n-fission)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__3N_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,3n-alpha)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__TOTAL_ABSORPTION_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,total_absorption)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-p)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-2alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n-2alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-d)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-t)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-he3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_D_2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-d-2alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_T_2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-t-2alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__4N_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,4n)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__3N_FISSION_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,3n-fission)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n-p)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__3N_P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,3n-p)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_2P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-2p)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_P_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-p-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_1_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_1)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_2_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_2)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_4_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_4)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_5_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_5)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_6_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_6)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_7_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_7)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_8_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_8)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_9_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_9)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_10_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_10)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_11_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_11)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_12_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_12)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_13_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_13)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_14_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_14)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_15_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_15)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_16_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_16)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_17_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_17)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_18_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_18)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_19_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_19)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_20_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_20)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_21_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_21)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_22_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_22)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_23_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_23)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_24_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_24)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_25_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_25)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_26_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_26)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_27_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_27)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_28_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_28)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_29_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_29)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_30_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_30)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_31_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_31)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_32_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_32)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_33_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_33)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_34_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_34)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_35_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_35)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_36_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_36)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_37_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_37)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_38_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_38)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_39_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_39)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_EXCITED_STATE_40_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_40)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_CONTINUUM_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_continuum)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__CAPTURE_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,capture)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__GAMMA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,gamma)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__3ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,3alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2p)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t-2alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d-2alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p-d)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p-t)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__5N_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,5n)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__6N_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,6n)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n-t)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__4N_P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,4n-p)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__3N_D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,3n-d)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_D_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-d-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_P_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n-p-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__7N_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,7n)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__8N_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,8n)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__5N_P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,5n-p)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__6N_P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,6n-p)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__7N_P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,7n-p)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__4N_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,4n-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__5N_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,5n-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__6N_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,6n-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__7N_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,7n-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__4N_D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,4n-d)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__5N_D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,5n-d)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__6N_D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,6n-d)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__3N_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,3n-t)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__4N_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,4n-t)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__5N_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,5n-t)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__6N_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,6n-t)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n-he3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__3N_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,3n-he3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__4N_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,4n-he3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__3N_2P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,3n-2p)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__3N_2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,3n-2alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__3N_P_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,3n-p-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d-t)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_P_D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-p-d)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_P_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-p-t)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_D_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-d-t)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_P_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-p-he3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_D_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-d-he3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_T_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-t-he3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_T_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-t-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_2P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n-2p)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p-he3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d-he3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__4N_2P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,4n-2p)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__4N_2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,4n-2alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__4N_P_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,4n-p-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__3P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,3p)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__N_3P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n-3p)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__3N_2P_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,3n-2p-alpha)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__5N_2P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,5n-2p)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__TOTAL_N_PRODUCTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,n_production)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__TOTAL_GAMMA_PRODUCTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,gamma_production)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__TOTAL_P_PRODUCTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_production)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__TOTAL_D_PRODUCTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_production)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__TOTAL_T_PRODUCTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_production)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__TOTAL_HE3_PRODUCTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_production)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__TOTAL_ALPHA_PRODUCTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_production)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__AVERAGE_HEATING;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,heating)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__DAMAGE;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,damage)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_0_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_0)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_1_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_1)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_2_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_2)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_4_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_4)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_5_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_5)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_6_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_6)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_7_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_7)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_8_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_8)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_9_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_9)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_10_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_10)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_11_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_11)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_12_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_12)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_13_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_13)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_14_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_14)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_15_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_15)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_16_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_16)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_17_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_17)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_18_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_18)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_19_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_19)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_20_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_20)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_21_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_21)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_22_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_22)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_23_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_23)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_24_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_24)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_25_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_25)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_26_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_26)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_27_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_27)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_28_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_28)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_29_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_29)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_30_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_30)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_31_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_31)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_32_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_32)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_33_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_33)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_34_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_34)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_35_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_35)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_36_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_36)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_37_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_37)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_38_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_38)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_39_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_39)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_40_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_40)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_41_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_41)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_42_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_42)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_43_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_43)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_44_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_44)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_45_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_45)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_46_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_46)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_47_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_47)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__P_EXCITED_STATE_48_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_48)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__P_CONTINUUM_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,p_continuum)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__D_EXCITED_STATE_0_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_0)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_1_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_1)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_2_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_2)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_4_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_4)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_5_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_5)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_6_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_6)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_7_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_7)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_8_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_8)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_9_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_9)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_10_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_10)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_11_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_11)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_12_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_12)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_13_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_13)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_14_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_14)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_15_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_15)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_16_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_16)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_17_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_17)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_18_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_18)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_19_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_19)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_20_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_20)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_21_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_21)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_22_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_22)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_23_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_23)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_24_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_24)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_25_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_25)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_26_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_26)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_27_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_27)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_28_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_28)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_29_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_29)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_30_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_30)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_31_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_31)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_32_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_32)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_33_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_33)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_34_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_34)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_35_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_35)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_36_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_36)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_37_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_37)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_38_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_38)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_39_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_39)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_40_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_40)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_41_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_41)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_42_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_42)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_43_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_43)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_44_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_44)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_45_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_45)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_46_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_46)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_47_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_47)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__D_EXCITED_STATE_48_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_48)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__D_CONTINUUM_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,d_continuum)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__T_EXCITED_STATE_0_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_0)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_1_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_1)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_2_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_2)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_4_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_4)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_5_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_5)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_6_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_6)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_7_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_7)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_8_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_8)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_9_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_9)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_10_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_10)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_11_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_11)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_12_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_12)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_13_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_13)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_14_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_14)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_15_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_15)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_16_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_16)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_17_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_17)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_18_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_18)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_19_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_19)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_20_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_20)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_21_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_21)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_22_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_22)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_23_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_23)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_24_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_24)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_25_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_25)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_26_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_26)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_27_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_27)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_28_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_28)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_29_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_29)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_30_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_30)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_31_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_31)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_32_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_32)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_33_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_33)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_34_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_34)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_35_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_35)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_36_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_36)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_37_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_37)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_38_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_38)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_39_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_39)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_40_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_40)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_41_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_41)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_42_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_42)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_43_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_43)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_44_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_44)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_45_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_45)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_46_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_46)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_47_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_47)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__T_EXCITED_STATE_48_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_48)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__T_CONTINUUM_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,t_continuum)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__HE3_EXCITED_STATE_0_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_0)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_1_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_1)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_2_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_2)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_4_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_4)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_5_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_5)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_6_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_6)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_7_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_7)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_8_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_8)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_9_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_9)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_10_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_10)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_11_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_11)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_12_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_12)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_13_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_13)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_14_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_14)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_15_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_15)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_16_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_16)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_17_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_17)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_18_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_18)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_19_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_19)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_20_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_20)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_21_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_21)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_22_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_22)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_23_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_23)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_24_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_24)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_25_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_25)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_26_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_26)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_27_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_27)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_28_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_28)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_29_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_29)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_30_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_30)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_31_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_31)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_32_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_32)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_33_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_33)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_34_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_34)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_35_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_35)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_36_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_36)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_37_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_37)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_38_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_38)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_39_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_39)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_40_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_40)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_41_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_41)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_42_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_42)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_43_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_43)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_44_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_44)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_45_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_45)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_46_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_46)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_47_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_47)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__HE3_EXCITED_STATE_48_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_48)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__HE3_CONTINUUM_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,he3_continuum)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_0_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_0)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_1_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_1)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_2_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_2)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_4_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_4)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_5_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_5)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_6_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_6)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_7_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_7)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_8_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_8)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_9_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_9)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_10_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_10)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_11_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_11)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_12_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_12)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_13_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_13)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_14_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_14)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_15_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_15)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_16_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_16)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_17_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_17)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_18_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_18)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_19_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_19)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_20_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_20)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_21_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_21)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_22_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_22)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_23_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_23)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_24_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_24)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_25_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_25)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_26_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_26)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_27_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_27)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_28_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_28)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_29_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_29)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_30_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_30)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_31_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_31)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_32_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_32)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_33_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_33)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_34_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_34)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_35_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_35)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_36_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_36)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_37_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_37)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_38_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_38)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_39_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_39)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_40_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_40)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_41_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_41)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_42_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_42)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_43_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_43)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_44_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_44)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_45_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_45)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_46_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_46)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_47_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_47)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__ALPHA_EXCITED_STATE_48_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_48)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__ALPHA_CONTINUUM_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,alpha_continuum)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_EXCITED_STATE_0_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_0)" );

  oss.str( "" );
  oss.clear(); 
  
  oss << MonteCarlo::N__2N_EXCITED_STATE_1_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_1)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_EXCITED_STATE_2_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_2)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_EXCITED_STATE_3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_3)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_EXCITED_STATE_4_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_4)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_EXCITED_STATE_5_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_5)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_EXCITED_STATE_6_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_6)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_EXCITED_STATE_7_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_7)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_EXCITED_STATE_8_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_8)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_EXCITED_STATE_9_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_9)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_EXCITED_STATE_10_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_10)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_EXCITED_STATE_11_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_11)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_EXCITED_STATE_12_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_12)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_EXCITED_STATE_13_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_13)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::N__2N_EXCITED_STATE_14_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_14)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_EXCITED_STATE_15_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_15)" );

  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::N__2N_CONTINUUM_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(n,2n_continuum)" );
}

//---------------------------------------------------------------------------//
// Check that a nuclear reaction type can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( NuclearReactionType,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_nuclear_reaction_type" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::NuclearReactionType type_1 = MonteCarlo::N__TOTAL_REACTION;
    MonteCarlo::NuclearReactionType type_2 = MonteCarlo::N__N_ELASTIC_REACTION;
    MonteCarlo::NuclearReactionType type_3 = MonteCarlo::N__N_NON_ELASTIC_REACTION;
    MonteCarlo::NuclearReactionType type_4 = MonteCarlo::N__N_INELASTIC_REACTION;
    MonteCarlo::NuclearReactionType type_5 = MonteCarlo::N__ANYTHING_REACTION;
    MonteCarlo::NuclearReactionType type_6 = MonteCarlo::N__2N_D_REACTION;
    MonteCarlo::NuclearReactionType type_7 = MonteCarlo::N__2N_REACTION;
    MonteCarlo::NuclearReactionType type_8 = MonteCarlo::N__3N_REACTION;
    MonteCarlo::NuclearReactionType type_9 = MonteCarlo::N__TOTAL_FISSION_REACTION;
    MonteCarlo::NuclearReactionType type_9a = MonteCarlo::N__FISSION_REACTION;
    MonteCarlo::NuclearReactionType type_9b = MonteCarlo::N__N_FISSION_REACTION;
    MonteCarlo::NuclearReactionType type_9c = MonteCarlo::N__2N_FISSION_REACTION;
    MonteCarlo::NuclearReactionType type_10 = MonteCarlo::N__N_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_11 = MonteCarlo::N__2N_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_12 = MonteCarlo::N__3N_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_12a = MonteCarlo::N__TOTAL_ABSORPTION_REACTION;
    MonteCarlo::NuclearReactionType type_13 = MonteCarlo::N__N_P_REACTION;
    MonteCarlo::NuclearReactionType type_14 = MonteCarlo::N__N_2ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_15 = MonteCarlo::N__2N_2ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_16 = MonteCarlo::N__N_D_REACTION;
    MonteCarlo::NuclearReactionType type_17 = MonteCarlo::N__N_T_REACTION;
    MonteCarlo::NuclearReactionType type_18 = MonteCarlo::N__N_HE3_REACTION;
    MonteCarlo::NuclearReactionType type_19 = MonteCarlo::N__N_D_2ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_20 = MonteCarlo::N__N_T_2ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_21 = MonteCarlo::N__4N_REACTION;
    MonteCarlo::NuclearReactionType type_21a = MonteCarlo::N__3N_FISSION_REACTION;
    MonteCarlo::NuclearReactionType type_22 = MonteCarlo::N__2N_P_REACTION;
    MonteCarlo::NuclearReactionType type_23 = MonteCarlo::N__3N_P_REACTION;
    MonteCarlo::NuclearReactionType type_24 = MonteCarlo::N__N_2P_REACTION;
    MonteCarlo::NuclearReactionType type_25 = MonteCarlo::N__N_P_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_27 = MonteCarlo::N__N_EXCITED_STATE_1_REACTION;
    MonteCarlo::NuclearReactionType type_28 = MonteCarlo::N__N_EXCITED_STATE_2_REACTION;
    MonteCarlo::NuclearReactionType type_29 = MonteCarlo::N__N_EXCITED_STATE_3_REACTION;
    MonteCarlo::NuclearReactionType type_30 = MonteCarlo::N__N_EXCITED_STATE_4_REACTION;
    MonteCarlo::NuclearReactionType type_31 = MonteCarlo::N__N_EXCITED_STATE_5_REACTION;
    MonteCarlo::NuclearReactionType type_32 = MonteCarlo::N__N_EXCITED_STATE_6_REACTION;
    MonteCarlo::NuclearReactionType type_33 = MonteCarlo::N__N_EXCITED_STATE_7_REACTION;
    MonteCarlo::NuclearReactionType type_34 = MonteCarlo::N__N_EXCITED_STATE_8_REACTION;
    MonteCarlo::NuclearReactionType type_35 = MonteCarlo::N__N_EXCITED_STATE_9_REACTION;
    MonteCarlo::NuclearReactionType type_36 = MonteCarlo::N__N_EXCITED_STATE_10_REACTION;
    MonteCarlo::NuclearReactionType type_37 = MonteCarlo::N__N_EXCITED_STATE_11_REACTION;
    MonteCarlo::NuclearReactionType type_38 = MonteCarlo::N__N_EXCITED_STATE_12_REACTION;
    MonteCarlo::NuclearReactionType type_39 = MonteCarlo::N__N_EXCITED_STATE_13_REACTION;
    MonteCarlo::NuclearReactionType type_40 = MonteCarlo::N__N_EXCITED_STATE_14_REACTION;
    MonteCarlo::NuclearReactionType type_41 = MonteCarlo::N__N_EXCITED_STATE_15_REACTION;
    MonteCarlo::NuclearReactionType type_42 = MonteCarlo::N__N_EXCITED_STATE_16_REACTION;
    MonteCarlo::NuclearReactionType type_43 = MonteCarlo::N__N_EXCITED_STATE_17_REACTION;
    MonteCarlo::NuclearReactionType type_44 = MonteCarlo::N__N_EXCITED_STATE_18_REACTION;
    MonteCarlo::NuclearReactionType type_45 = MonteCarlo::N__N_EXCITED_STATE_19_REACTION;
    MonteCarlo::NuclearReactionType type_46 = MonteCarlo::N__N_EXCITED_STATE_20_REACTION;
    MonteCarlo::NuclearReactionType type_47 = MonteCarlo::N__N_EXCITED_STATE_21_REACTION;
    MonteCarlo::NuclearReactionType type_48 = MonteCarlo::N__N_EXCITED_STATE_22_REACTION;
    MonteCarlo::NuclearReactionType type_49 = MonteCarlo::N__N_EXCITED_STATE_23_REACTION;
    MonteCarlo::NuclearReactionType type_50 = MonteCarlo::N__N_EXCITED_STATE_24_REACTION;
    MonteCarlo::NuclearReactionType type_51 = MonteCarlo::N__N_EXCITED_STATE_25_REACTION;
    MonteCarlo::NuclearReactionType type_52 = MonteCarlo::N__N_EXCITED_STATE_26_REACTION;
    MonteCarlo::NuclearReactionType type_53 = MonteCarlo::N__N_EXCITED_STATE_27_REACTION;
    MonteCarlo::NuclearReactionType type_54 = MonteCarlo::N__N_EXCITED_STATE_28_REACTION;
    MonteCarlo::NuclearReactionType type_55 = MonteCarlo::N__N_EXCITED_STATE_29_REACTION;
    MonteCarlo::NuclearReactionType type_56 = MonteCarlo::N__N_EXCITED_STATE_30_REACTION;
    MonteCarlo::NuclearReactionType type_57 = MonteCarlo::N__N_EXCITED_STATE_31_REACTION;
    MonteCarlo::NuclearReactionType type_58 = MonteCarlo::N__N_EXCITED_STATE_32_REACTION;
    MonteCarlo::NuclearReactionType type_59 = MonteCarlo::N__N_EXCITED_STATE_33_REACTION;
    MonteCarlo::NuclearReactionType type_60 = MonteCarlo::N__N_EXCITED_STATE_34_REACTION;
    MonteCarlo::NuclearReactionType type_61 = MonteCarlo::N__N_EXCITED_STATE_35_REACTION;
    MonteCarlo::NuclearReactionType type_62 = MonteCarlo::N__N_EXCITED_STATE_36_REACTION;
    MonteCarlo::NuclearReactionType type_63 = MonteCarlo::N__N_EXCITED_STATE_37_REACTION;
    MonteCarlo::NuclearReactionType type_64 = MonteCarlo::N__N_EXCITED_STATE_38_REACTION;
    MonteCarlo::NuclearReactionType type_65 = MonteCarlo::N__N_EXCITED_STATE_39_REACTION;
    MonteCarlo::NuclearReactionType type_66 = MonteCarlo::N__N_EXCITED_STATE_40_REACTION;
    MonteCarlo::NuclearReactionType type_67 = MonteCarlo::N__N_CONTINUUM_REACTION;
    MonteCarlo::NuclearReactionType type_68 = MonteCarlo::N__CAPTURE_REACTION;
    MonteCarlo::NuclearReactionType type_68a = MonteCarlo::N__GAMMA_REACTION;
    MonteCarlo::NuclearReactionType type_69 = MonteCarlo::N__P_REACTION;
    MonteCarlo::NuclearReactionType type_70 = MonteCarlo::N__D_REACTION;
    MonteCarlo::NuclearReactionType type_71 = MonteCarlo::N__T_REACTION;
    MonteCarlo::NuclearReactionType type_72 = MonteCarlo::N__HE3_REACTION;
    MonteCarlo::NuclearReactionType type_73 = MonteCarlo::N__ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_74 = MonteCarlo::N__2ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_75 = MonteCarlo::N__3ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_76 = MonteCarlo::N__2P_REACTION;
    MonteCarlo::NuclearReactionType type_77 = MonteCarlo::N__P_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_78 = MonteCarlo::N__T_2ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_79 = MonteCarlo::N__D_2ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_80 = MonteCarlo::N__P_D_REACTION;
    MonteCarlo::NuclearReactionType type_81 = MonteCarlo::N__P_T_REACTION;
    MonteCarlo::NuclearReactionType type_82 = MonteCarlo::N__D_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_83 = MonteCarlo::N__5N_REACTION;
    MonteCarlo::NuclearReactionType type_84 = MonteCarlo::N__6N_REACTION;
    MonteCarlo::NuclearReactionType type_85 = MonteCarlo::N__2N_T_REACTION;
    MonteCarlo::NuclearReactionType type_86 = MonteCarlo::N__T_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_87 = MonteCarlo::N__4N_P_REACTION;
    MonteCarlo::NuclearReactionType type_88 = MonteCarlo::N__3N_D_REACTION;
    MonteCarlo::NuclearReactionType type_89 = MonteCarlo::N__N_D_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_90 = MonteCarlo::N__2N_P_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_91 = MonteCarlo::N__7N_REACTION;
    MonteCarlo::NuclearReactionType type_92 = MonteCarlo::N__8N_REACTION;
    MonteCarlo::NuclearReactionType type_93 = MonteCarlo::N__5N_P_REACTION;
    MonteCarlo::NuclearReactionType type_94 = MonteCarlo::N__6N_P_REACTION;
    MonteCarlo::NuclearReactionType type_95 = MonteCarlo::N__7N_P_REACTION;
    MonteCarlo::NuclearReactionType type_96 = MonteCarlo::N__4N_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_97 = MonteCarlo::N__5N_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_98 = MonteCarlo::N__6N_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_99 = MonteCarlo::N__7N_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_100 = MonteCarlo::N__4N_D_REACTION;
    MonteCarlo::NuclearReactionType type_101 = MonteCarlo::N__5N_D_REACTION;
    MonteCarlo::NuclearReactionType type_102 = MonteCarlo::N__6N_D_REACTION;
    MonteCarlo::NuclearReactionType type_103 = MonteCarlo::N__3N_T_REACTION;
    MonteCarlo::NuclearReactionType type_104 = MonteCarlo::N__4N_T_REACTION;
    MonteCarlo::NuclearReactionType type_105 = MonteCarlo::N__5N_T_REACTION;
    MonteCarlo::NuclearReactionType type_106 = MonteCarlo::N__6N_T_REACTION;
    MonteCarlo::NuclearReactionType type_107 = MonteCarlo::N__2N_HE3_REACTION;
    MonteCarlo::NuclearReactionType type_108 = MonteCarlo::N__3N_HE3_REACTION;
    MonteCarlo::NuclearReactionType type_109 = MonteCarlo::N__4N_HE3_REACTION;
    MonteCarlo::NuclearReactionType type_110 = MonteCarlo::N__3N_2P_REACTION;
    MonteCarlo::NuclearReactionType type_111 = MonteCarlo::N__3N_2ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_112 = MonteCarlo::N__3N_P_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_113 = MonteCarlo::N__D_T_REACTION;
    MonteCarlo::NuclearReactionType type_114 = MonteCarlo::N__N_P_D_REACTION;
    MonteCarlo::NuclearReactionType type_115 = MonteCarlo::N__N_P_T_REACTION;
    MonteCarlo::NuclearReactionType type_116 = MonteCarlo::N__N_D_T_REACTION;
    MonteCarlo::NuclearReactionType type_117 = MonteCarlo::N__N_P_HE3_REACTION;
    MonteCarlo::NuclearReactionType type_118 = MonteCarlo::N__N_D_HE3_REACTION;
    MonteCarlo::NuclearReactionType type_119 = MonteCarlo::N__N_T_HE3_REACTION;
    MonteCarlo::NuclearReactionType type_120 = MonteCarlo::N__N_T_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_121 = MonteCarlo::N__2N_2P_REACTION;
    MonteCarlo::NuclearReactionType type_122 = MonteCarlo::N__P_HE3_REACTION;
    MonteCarlo::NuclearReactionType type_123 = MonteCarlo::N__D_HE3_REACTION;
    MonteCarlo::NuclearReactionType type_124 = MonteCarlo::N__HE3_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_125 = MonteCarlo::N__4N_2P_REACTION;
    MonteCarlo::NuclearReactionType type_126 = MonteCarlo::N__4N_2ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_127 = MonteCarlo::N__4N_P_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_128 = MonteCarlo::N__3P_REACTION;
    MonteCarlo::NuclearReactionType type_129 = MonteCarlo::N__N_3P_REACTION;
    MonteCarlo::NuclearReactionType type_130 = MonteCarlo::N__3N_2P_ALPHA_REACTION;
    MonteCarlo::NuclearReactionType type_131 = MonteCarlo::N__5N_2P_REACTION;
    MonteCarlo::NuclearReactionType type_132 = MonteCarlo::N__TOTAL_N_PRODUCTION;
    MonteCarlo::NuclearReactionType type_133 = MonteCarlo::N__TOTAL_GAMMA_PRODUCTION;
    MonteCarlo::NuclearReactionType type_134 = MonteCarlo::N__TOTAL_P_PRODUCTION;
    MonteCarlo::NuclearReactionType type_135 = MonteCarlo::N__TOTAL_D_PRODUCTION;
    MonteCarlo::NuclearReactionType type_136 = MonteCarlo::N__TOTAL_T_PRODUCTION;
    MonteCarlo::NuclearReactionType type_137 = MonteCarlo::N__TOTAL_HE3_PRODUCTION;
    MonteCarlo::NuclearReactionType type_138 = MonteCarlo::N__TOTAL_ALPHA_PRODUCTION;
    MonteCarlo::NuclearReactionType type_139 = MonteCarlo::N__AVERAGE_HEATING;
    MonteCarlo::NuclearReactionType type_140 = MonteCarlo::N__DAMAGE;
    MonteCarlo::NuclearReactionType type_141 = MonteCarlo::N__P_EXCITED_STATE_0_REACTION;
    MonteCarlo::NuclearReactionType type_142 = MonteCarlo::N__P_EXCITED_STATE_1_REACTION;
    MonteCarlo::NuclearReactionType type_143 = MonteCarlo::N__P_EXCITED_STATE_2_REACTION;
    MonteCarlo::NuclearReactionType type_144 = MonteCarlo::N__P_EXCITED_STATE_3_REACTION;
    MonteCarlo::NuclearReactionType type_145 = MonteCarlo::N__P_EXCITED_STATE_4_REACTION;
    MonteCarlo::NuclearReactionType type_146 = MonteCarlo::N__P_EXCITED_STATE_5_REACTION;
    MonteCarlo::NuclearReactionType type_147 = MonteCarlo::N__P_EXCITED_STATE_6_REACTION;
    MonteCarlo::NuclearReactionType type_148 = MonteCarlo::N__P_EXCITED_STATE_7_REACTION;
    MonteCarlo::NuclearReactionType type_149 = MonteCarlo::N__P_EXCITED_STATE_8_REACTION;
    MonteCarlo::NuclearReactionType type_150 = MonteCarlo::N__P_EXCITED_STATE_9_REACTION;
    MonteCarlo::NuclearReactionType type_151 = MonteCarlo::N__P_EXCITED_STATE_10_REACTION;
    MonteCarlo::NuclearReactionType type_152 = MonteCarlo::N__P_EXCITED_STATE_11_REACTION;
    MonteCarlo::NuclearReactionType type_153 = MonteCarlo::N__P_EXCITED_STATE_12_REACTION;
    MonteCarlo::NuclearReactionType type_154 = MonteCarlo::N__P_EXCITED_STATE_13_REACTION;
    MonteCarlo::NuclearReactionType type_155 = MonteCarlo::N__P_EXCITED_STATE_14_REACTION;
    MonteCarlo::NuclearReactionType type_156 = MonteCarlo::N__P_EXCITED_STATE_15_REACTION;
    MonteCarlo::NuclearReactionType type_157 = MonteCarlo::N__P_EXCITED_STATE_16_REACTION;
    MonteCarlo::NuclearReactionType type_158 = MonteCarlo::N__P_EXCITED_STATE_17_REACTION;
    MonteCarlo::NuclearReactionType type_159 = MonteCarlo::N__P_EXCITED_STATE_18_REACTION;
    MonteCarlo::NuclearReactionType type_160 = MonteCarlo::N__P_EXCITED_STATE_19_REACTION;
    MonteCarlo::NuclearReactionType type_161 = MonteCarlo::N__P_EXCITED_STATE_20_REACTION;
    MonteCarlo::NuclearReactionType type_162 = MonteCarlo::N__P_EXCITED_STATE_21_REACTION;
    MonteCarlo::NuclearReactionType type_163 = MonteCarlo::N__P_EXCITED_STATE_22_REACTION;
    MonteCarlo::NuclearReactionType type_164 = MonteCarlo::N__P_EXCITED_STATE_23_REACTION;
    MonteCarlo::NuclearReactionType type_165 = MonteCarlo::N__P_EXCITED_STATE_24_REACTION;
    MonteCarlo::NuclearReactionType type_166 = MonteCarlo::N__P_EXCITED_STATE_25_REACTION;
    MonteCarlo::NuclearReactionType type_167 = MonteCarlo::N__P_EXCITED_STATE_26_REACTION;
    MonteCarlo::NuclearReactionType type_168 = MonteCarlo::N__P_EXCITED_STATE_27_REACTION;
    MonteCarlo::NuclearReactionType type_169 = MonteCarlo::N__P_EXCITED_STATE_28_REACTION;
    MonteCarlo::NuclearReactionType type_170 = MonteCarlo::N__P_EXCITED_STATE_29_REACTION;
    MonteCarlo::NuclearReactionType type_171 = MonteCarlo::N__P_EXCITED_STATE_30_REACTION;
    MonteCarlo::NuclearReactionType type_172 = MonteCarlo::N__P_EXCITED_STATE_31_REACTION;
    MonteCarlo::NuclearReactionType type_173 = MonteCarlo::N__P_EXCITED_STATE_32_REACTION;
    MonteCarlo::NuclearReactionType type_174 = MonteCarlo::N__P_EXCITED_STATE_33_REACTION;
    MonteCarlo::NuclearReactionType type_175 = MonteCarlo::N__P_EXCITED_STATE_34_REACTION;
    MonteCarlo::NuclearReactionType type_176 = MonteCarlo::N__P_EXCITED_STATE_35_REACTION;
    MonteCarlo::NuclearReactionType type_177 = MonteCarlo::N__P_EXCITED_STATE_36_REACTION;
    MonteCarlo::NuclearReactionType type_178 = MonteCarlo::N__P_EXCITED_STATE_37_REACTION;
    MonteCarlo::NuclearReactionType type_179 = MonteCarlo::N__P_EXCITED_STATE_38_REACTION;
    MonteCarlo::NuclearReactionType type_180 = MonteCarlo::N__P_EXCITED_STATE_39_REACTION;
    MonteCarlo::NuclearReactionType type_181 = MonteCarlo::N__P_EXCITED_STATE_40_REACTION;
    MonteCarlo::NuclearReactionType type_182 = MonteCarlo::N__P_EXCITED_STATE_41_REACTION;
    MonteCarlo::NuclearReactionType type_183 = MonteCarlo::N__P_EXCITED_STATE_42_REACTION;
    MonteCarlo::NuclearReactionType type_184 = MonteCarlo::N__P_EXCITED_STATE_43_REACTION;
    MonteCarlo::NuclearReactionType type_185 = MonteCarlo::N__P_EXCITED_STATE_44_REACTION;
    MonteCarlo::NuclearReactionType type_186 = MonteCarlo::N__P_EXCITED_STATE_45_REACTION;
    MonteCarlo::NuclearReactionType type_187 = MonteCarlo::N__P_EXCITED_STATE_46_REACTION;
    MonteCarlo::NuclearReactionType type_188 = MonteCarlo::N__P_EXCITED_STATE_47_REACTION;
    MonteCarlo::NuclearReactionType type_189 = MonteCarlo::N__P_EXCITED_STATE_48_REACTION;
    MonteCarlo::NuclearReactionType type_190 = MonteCarlo::N__P_CONTINUUM_REACTION;
    MonteCarlo::NuclearReactionType type_191 = MonteCarlo::N__D_EXCITED_STATE_0_REACTION;
    MonteCarlo::NuclearReactionType type_192 = MonteCarlo::N__D_EXCITED_STATE_1_REACTION;
    MonteCarlo::NuclearReactionType type_193 = MonteCarlo::N__D_EXCITED_STATE_2_REACTION;
    MonteCarlo::NuclearReactionType type_194 = MonteCarlo::N__D_EXCITED_STATE_3_REACTION;
    MonteCarlo::NuclearReactionType type_195 = MonteCarlo::N__D_EXCITED_STATE_4_REACTION;
    MonteCarlo::NuclearReactionType type_196 = MonteCarlo::N__D_EXCITED_STATE_5_REACTION;
    MonteCarlo::NuclearReactionType type_197 = MonteCarlo::N__D_EXCITED_STATE_6_REACTION;
    MonteCarlo::NuclearReactionType type_198 = MonteCarlo::N__D_EXCITED_STATE_7_REACTION;
    MonteCarlo::NuclearReactionType type_199 = MonteCarlo::N__D_EXCITED_STATE_8_REACTION;
    MonteCarlo::NuclearReactionType type_200 = MonteCarlo::N__D_EXCITED_STATE_9_REACTION;
    MonteCarlo::NuclearReactionType type_201 = MonteCarlo::N__D_EXCITED_STATE_10_REACTION;
    MonteCarlo::NuclearReactionType type_202 = MonteCarlo::N__D_EXCITED_STATE_11_REACTION;
    MonteCarlo::NuclearReactionType type_203 = MonteCarlo::N__D_EXCITED_STATE_12_REACTION;
    MonteCarlo::NuclearReactionType type_204 = MonteCarlo::N__D_EXCITED_STATE_13_REACTION;
    MonteCarlo::NuclearReactionType type_205 = MonteCarlo::N__D_EXCITED_STATE_14_REACTION;
    MonteCarlo::NuclearReactionType type_206 = MonteCarlo::N__D_EXCITED_STATE_15_REACTION;
    MonteCarlo::NuclearReactionType type_207 = MonteCarlo::N__D_EXCITED_STATE_16_REACTION;
    MonteCarlo::NuclearReactionType type_208 = MonteCarlo::N__D_EXCITED_STATE_17_REACTION;
    MonteCarlo::NuclearReactionType type_209 = MonteCarlo::N__D_EXCITED_STATE_18_REACTION;
    MonteCarlo::NuclearReactionType type_210 = MonteCarlo::N__D_EXCITED_STATE_19_REACTION;
    MonteCarlo::NuclearReactionType type_211 = MonteCarlo::N__D_EXCITED_STATE_20_REACTION;
    MonteCarlo::NuclearReactionType type_212 = MonteCarlo::N__D_EXCITED_STATE_21_REACTION;
    MonteCarlo::NuclearReactionType type_213 = MonteCarlo::N__D_EXCITED_STATE_22_REACTION;
    MonteCarlo::NuclearReactionType type_214 = MonteCarlo::N__D_EXCITED_STATE_23_REACTION;
    MonteCarlo::NuclearReactionType type_215 = MonteCarlo::N__D_EXCITED_STATE_24_REACTION;
    MonteCarlo::NuclearReactionType type_216 = MonteCarlo::N__D_EXCITED_STATE_25_REACTION;
    MonteCarlo::NuclearReactionType type_217 = MonteCarlo::N__D_EXCITED_STATE_26_REACTION;
    MonteCarlo::NuclearReactionType type_218 = MonteCarlo::N__D_EXCITED_STATE_27_REACTION;
    MonteCarlo::NuclearReactionType type_219 = MonteCarlo::N__D_EXCITED_STATE_28_REACTION;
    MonteCarlo::NuclearReactionType type_220 = MonteCarlo::N__D_EXCITED_STATE_29_REACTION;
    MonteCarlo::NuclearReactionType type_221 = MonteCarlo::N__D_EXCITED_STATE_30_REACTION;
    MonteCarlo::NuclearReactionType type_222 = MonteCarlo::N__D_EXCITED_STATE_31_REACTION;
    MonteCarlo::NuclearReactionType type_223 = MonteCarlo::N__D_EXCITED_STATE_32_REACTION;
    MonteCarlo::NuclearReactionType type_224 = MonteCarlo::N__D_EXCITED_STATE_33_REACTION;
    MonteCarlo::NuclearReactionType type_225 = MonteCarlo::N__D_EXCITED_STATE_34_REACTION;
    MonteCarlo::NuclearReactionType type_226 = MonteCarlo::N__D_EXCITED_STATE_35_REACTION;
    MonteCarlo::NuclearReactionType type_227 = MonteCarlo::N__D_EXCITED_STATE_36_REACTION;
    MonteCarlo::NuclearReactionType type_228 = MonteCarlo::N__D_EXCITED_STATE_37_REACTION;
    MonteCarlo::NuclearReactionType type_229 = MonteCarlo::N__D_EXCITED_STATE_38_REACTION;
    MonteCarlo::NuclearReactionType type_230 = MonteCarlo::N__D_EXCITED_STATE_39_REACTION;
    MonteCarlo::NuclearReactionType type_231 = MonteCarlo::N__D_EXCITED_STATE_40_REACTION;
    MonteCarlo::NuclearReactionType type_232 = MonteCarlo::N__D_EXCITED_STATE_41_REACTION;
    MonteCarlo::NuclearReactionType type_233 = MonteCarlo::N__D_EXCITED_STATE_42_REACTION;
    MonteCarlo::NuclearReactionType type_234 = MonteCarlo::N__D_EXCITED_STATE_43_REACTION;
    MonteCarlo::NuclearReactionType type_235 = MonteCarlo::N__D_EXCITED_STATE_44_REACTION;
    MonteCarlo::NuclearReactionType type_236 = MonteCarlo::N__D_EXCITED_STATE_45_REACTION;
    MonteCarlo::NuclearReactionType type_237 = MonteCarlo::N__D_EXCITED_STATE_46_REACTION;
    MonteCarlo::NuclearReactionType type_238 = MonteCarlo::N__D_EXCITED_STATE_47_REACTION;
    MonteCarlo::NuclearReactionType type_239 = MonteCarlo::N__D_EXCITED_STATE_48_REACTION;
    MonteCarlo::NuclearReactionType type_240 = MonteCarlo::N__D_CONTINUUM_REACTION;
    MonteCarlo::NuclearReactionType type_241 = MonteCarlo::N__T_EXCITED_STATE_0_REACTION;
    MonteCarlo::NuclearReactionType type_242 = MonteCarlo::N__T_EXCITED_STATE_1_REACTION;
    MonteCarlo::NuclearReactionType type_243 = MonteCarlo::N__T_EXCITED_STATE_2_REACTION;
    MonteCarlo::NuclearReactionType type_244 = MonteCarlo::N__T_EXCITED_STATE_3_REACTION;
    MonteCarlo::NuclearReactionType type_245 = MonteCarlo::N__T_EXCITED_STATE_4_REACTION;
    MonteCarlo::NuclearReactionType type_246 = MonteCarlo::N__T_EXCITED_STATE_5_REACTION;
    MonteCarlo::NuclearReactionType type_247 = MonteCarlo::N__T_EXCITED_STATE_6_REACTION;
    MonteCarlo::NuclearReactionType type_248 = MonteCarlo::N__T_EXCITED_STATE_7_REACTION;
    MonteCarlo::NuclearReactionType type_249 = MonteCarlo::N__T_EXCITED_STATE_8_REACTION;
    MonteCarlo::NuclearReactionType type_250 = MonteCarlo::N__T_EXCITED_STATE_9_REACTION;
    MonteCarlo::NuclearReactionType type_251 = MonteCarlo::N__T_EXCITED_STATE_10_REACTION;
    MonteCarlo::NuclearReactionType type_252 = MonteCarlo::N__T_EXCITED_STATE_11_REACTION;
    MonteCarlo::NuclearReactionType type_253 = MonteCarlo::N__T_EXCITED_STATE_12_REACTION;
    MonteCarlo::NuclearReactionType type_254 = MonteCarlo::N__T_EXCITED_STATE_13_REACTION;
    MonteCarlo::NuclearReactionType type_255 = MonteCarlo::N__T_EXCITED_STATE_14_REACTION;
    MonteCarlo::NuclearReactionType type_256 = MonteCarlo::N__T_EXCITED_STATE_15_REACTION;
    MonteCarlo::NuclearReactionType type_257 = MonteCarlo::N__T_EXCITED_STATE_16_REACTION;
    MonteCarlo::NuclearReactionType type_258 = MonteCarlo::N__T_EXCITED_STATE_17_REACTION;
    MonteCarlo::NuclearReactionType type_259 = MonteCarlo::N__T_EXCITED_STATE_18_REACTION;
    MonteCarlo::NuclearReactionType type_260 = MonteCarlo::N__T_EXCITED_STATE_19_REACTION;
    MonteCarlo::NuclearReactionType type_261 = MonteCarlo::N__T_EXCITED_STATE_20_REACTION;
    MonteCarlo::NuclearReactionType type_262 = MonteCarlo::N__T_EXCITED_STATE_21_REACTION;
    MonteCarlo::NuclearReactionType type_263 = MonteCarlo::N__T_EXCITED_STATE_22_REACTION;
    MonteCarlo::NuclearReactionType type_264 = MonteCarlo::N__T_EXCITED_STATE_23_REACTION;
    MonteCarlo::NuclearReactionType type_265 = MonteCarlo::N__T_EXCITED_STATE_24_REACTION;
    MonteCarlo::NuclearReactionType type_266 = MonteCarlo::N__T_EXCITED_STATE_25_REACTION;
    MonteCarlo::NuclearReactionType type_267 = MonteCarlo::N__T_EXCITED_STATE_26_REACTION;
    MonteCarlo::NuclearReactionType type_268 = MonteCarlo::N__T_EXCITED_STATE_27_REACTION;
    MonteCarlo::NuclearReactionType type_269 = MonteCarlo::N__T_EXCITED_STATE_28_REACTION;
    MonteCarlo::NuclearReactionType type_270 = MonteCarlo::N__T_EXCITED_STATE_29_REACTION;
    MonteCarlo::NuclearReactionType type_271 = MonteCarlo::N__T_EXCITED_STATE_30_REACTION;
    MonteCarlo::NuclearReactionType type_272 = MonteCarlo::N__T_EXCITED_STATE_31_REACTION;
    MonteCarlo::NuclearReactionType type_273 = MonteCarlo::N__T_EXCITED_STATE_32_REACTION;
    MonteCarlo::NuclearReactionType type_274 = MonteCarlo::N__T_EXCITED_STATE_33_REACTION;
    MonteCarlo::NuclearReactionType type_275 = MonteCarlo::N__T_EXCITED_STATE_34_REACTION;
    MonteCarlo::NuclearReactionType type_276 = MonteCarlo::N__T_EXCITED_STATE_35_REACTION;
    MonteCarlo::NuclearReactionType type_277 = MonteCarlo::N__T_EXCITED_STATE_36_REACTION;
    MonteCarlo::NuclearReactionType type_278 = MonteCarlo::N__T_EXCITED_STATE_37_REACTION;
    MonteCarlo::NuclearReactionType type_279 = MonteCarlo::N__T_EXCITED_STATE_38_REACTION;
    MonteCarlo::NuclearReactionType type_280 = MonteCarlo::N__T_EXCITED_STATE_39_REACTION;
    MonteCarlo::NuclearReactionType type_281 = MonteCarlo::N__T_EXCITED_STATE_40_REACTION;
    MonteCarlo::NuclearReactionType type_282 = MonteCarlo::N__T_EXCITED_STATE_41_REACTION;
    MonteCarlo::NuclearReactionType type_283 = MonteCarlo::N__T_EXCITED_STATE_42_REACTION;
    MonteCarlo::NuclearReactionType type_284 = MonteCarlo::N__T_EXCITED_STATE_43_REACTION;
    MonteCarlo::NuclearReactionType type_285 = MonteCarlo::N__T_EXCITED_STATE_44_REACTION;
    MonteCarlo::NuclearReactionType type_286 = MonteCarlo::N__T_EXCITED_STATE_45_REACTION;
    MonteCarlo::NuclearReactionType type_287 = MonteCarlo::N__T_EXCITED_STATE_46_REACTION;
    MonteCarlo::NuclearReactionType type_288 = MonteCarlo::N__T_EXCITED_STATE_47_REACTION;
    MonteCarlo::NuclearReactionType type_289 = MonteCarlo::N__T_EXCITED_STATE_48_REACTION;
    MonteCarlo::NuclearReactionType type_290 = MonteCarlo::N__T_CONTINUUM_REACTION;
    MonteCarlo::NuclearReactionType type_291 = MonteCarlo::N__HE3_EXCITED_STATE_0_REACTION;
    MonteCarlo::NuclearReactionType type_292 = MonteCarlo::N__HE3_EXCITED_STATE_1_REACTION;
    MonteCarlo::NuclearReactionType type_293 = MonteCarlo::N__HE3_EXCITED_STATE_2_REACTION;
    MonteCarlo::NuclearReactionType type_294 = MonteCarlo::N__HE3_EXCITED_STATE_3_REACTION;
    MonteCarlo::NuclearReactionType type_295 = MonteCarlo::N__HE3_EXCITED_STATE_4_REACTION;
    MonteCarlo::NuclearReactionType type_296 = MonteCarlo::N__HE3_EXCITED_STATE_5_REACTION;
    MonteCarlo::NuclearReactionType type_297 = MonteCarlo::N__HE3_EXCITED_STATE_6_REACTION;
    MonteCarlo::NuclearReactionType type_298 = MonteCarlo::N__HE3_EXCITED_STATE_7_REACTION;
    MonteCarlo::NuclearReactionType type_299 = MonteCarlo::N__HE3_EXCITED_STATE_8_REACTION;
    MonteCarlo::NuclearReactionType type_300 = MonteCarlo::N__HE3_EXCITED_STATE_9_REACTION;
    MonteCarlo::NuclearReactionType type_301 = MonteCarlo::N__HE3_EXCITED_STATE_10_REACTION;
    MonteCarlo::NuclearReactionType type_302 = MonteCarlo::N__HE3_EXCITED_STATE_11_REACTION;
    MonteCarlo::NuclearReactionType type_303 = MonteCarlo::N__HE3_EXCITED_STATE_12_REACTION;
    MonteCarlo::NuclearReactionType type_304 = MonteCarlo::N__HE3_EXCITED_STATE_13_REACTION;
    MonteCarlo::NuclearReactionType type_305 = MonteCarlo::N__HE3_EXCITED_STATE_14_REACTION;
    MonteCarlo::NuclearReactionType type_306 = MonteCarlo::N__HE3_EXCITED_STATE_15_REACTION;
    MonteCarlo::NuclearReactionType type_307 = MonteCarlo::N__HE3_EXCITED_STATE_16_REACTION;
    MonteCarlo::NuclearReactionType type_308 = MonteCarlo::N__HE3_EXCITED_STATE_17_REACTION;
    MonteCarlo::NuclearReactionType type_309 = MonteCarlo::N__HE3_EXCITED_STATE_18_REACTION;
    MonteCarlo::NuclearReactionType type_310 = MonteCarlo::N__HE3_EXCITED_STATE_19_REACTION;
    MonteCarlo::NuclearReactionType type_311 = MonteCarlo::N__HE3_EXCITED_STATE_20_REACTION;
    MonteCarlo::NuclearReactionType type_312 = MonteCarlo::N__HE3_EXCITED_STATE_21_REACTION;
    MonteCarlo::NuclearReactionType type_313 = MonteCarlo::N__HE3_EXCITED_STATE_22_REACTION;
    MonteCarlo::NuclearReactionType type_314 = MonteCarlo::N__HE3_EXCITED_STATE_23_REACTION;
    MonteCarlo::NuclearReactionType type_315 = MonteCarlo::N__HE3_EXCITED_STATE_24_REACTION;
    MonteCarlo::NuclearReactionType type_316 = MonteCarlo::N__HE3_EXCITED_STATE_25_REACTION;
    MonteCarlo::NuclearReactionType type_317 = MonteCarlo::N__HE3_EXCITED_STATE_26_REACTION;
    MonteCarlo::NuclearReactionType type_318 = MonteCarlo::N__HE3_EXCITED_STATE_27_REACTION;
    MonteCarlo::NuclearReactionType type_319 = MonteCarlo::N__HE3_EXCITED_STATE_28_REACTION;
    MonteCarlo::NuclearReactionType type_320 = MonteCarlo::N__HE3_EXCITED_STATE_29_REACTION;
    MonteCarlo::NuclearReactionType type_321 = MonteCarlo::N__HE3_EXCITED_STATE_30_REACTION;
    MonteCarlo::NuclearReactionType type_322 = MonteCarlo::N__HE3_EXCITED_STATE_31_REACTION;
    MonteCarlo::NuclearReactionType type_323 = MonteCarlo::N__HE3_EXCITED_STATE_32_REACTION;
    MonteCarlo::NuclearReactionType type_324 = MonteCarlo::N__HE3_EXCITED_STATE_33_REACTION;
    MonteCarlo::NuclearReactionType type_325 = MonteCarlo::N__HE3_EXCITED_STATE_34_REACTION;
    MonteCarlo::NuclearReactionType type_326 = MonteCarlo::N__HE3_EXCITED_STATE_35_REACTION;
    MonteCarlo::NuclearReactionType type_327 = MonteCarlo::N__HE3_EXCITED_STATE_36_REACTION;
    MonteCarlo::NuclearReactionType type_328 = MonteCarlo::N__HE3_EXCITED_STATE_37_REACTION;
    MonteCarlo::NuclearReactionType type_329 = MonteCarlo::N__HE3_EXCITED_STATE_38_REACTION;
    MonteCarlo::NuclearReactionType type_330 = MonteCarlo::N__HE3_EXCITED_STATE_39_REACTION;
    MonteCarlo::NuclearReactionType type_331 = MonteCarlo::N__HE3_EXCITED_STATE_40_REACTION;
    MonteCarlo::NuclearReactionType type_332 = MonteCarlo::N__HE3_EXCITED_STATE_41_REACTION;
    MonteCarlo::NuclearReactionType type_333 = MonteCarlo::N__HE3_EXCITED_STATE_42_REACTION;
    MonteCarlo::NuclearReactionType type_334 = MonteCarlo::N__HE3_EXCITED_STATE_43_REACTION;
    MonteCarlo::NuclearReactionType type_335 = MonteCarlo::N__HE3_EXCITED_STATE_44_REACTION;
    MonteCarlo::NuclearReactionType type_336 = MonteCarlo::N__HE3_EXCITED_STATE_45_REACTION;
    MonteCarlo::NuclearReactionType type_337 = MonteCarlo::N__HE3_EXCITED_STATE_46_REACTION;
    MonteCarlo::NuclearReactionType type_338 = MonteCarlo::N__HE3_EXCITED_STATE_47_REACTION;
    MonteCarlo::NuclearReactionType type_339 = MonteCarlo::N__HE3_EXCITED_STATE_48_REACTION;
    MonteCarlo::NuclearReactionType type_340 = MonteCarlo::N__HE3_CONTINUUM_REACTION;
    MonteCarlo::NuclearReactionType type_341 = MonteCarlo::N__ALPHA_EXCITED_STATE_0_REACTION;
    MonteCarlo::NuclearReactionType type_342 = MonteCarlo::N__ALPHA_EXCITED_STATE_1_REACTION;
    MonteCarlo::NuclearReactionType type_343 = MonteCarlo::N__ALPHA_EXCITED_STATE_2_REACTION;
    MonteCarlo::NuclearReactionType type_344 = MonteCarlo::N__ALPHA_EXCITED_STATE_3_REACTION;
    MonteCarlo::NuclearReactionType type_345 = MonteCarlo::N__ALPHA_EXCITED_STATE_4_REACTION;
    MonteCarlo::NuclearReactionType type_346 = MonteCarlo::N__ALPHA_EXCITED_STATE_5_REACTION;
    MonteCarlo::NuclearReactionType type_347 = MonteCarlo::N__ALPHA_EXCITED_STATE_6_REACTION;
    MonteCarlo::NuclearReactionType type_348 = MonteCarlo::N__ALPHA_EXCITED_STATE_7_REACTION;
    MonteCarlo::NuclearReactionType type_349 = MonteCarlo::N__ALPHA_EXCITED_STATE_8_REACTION;
    MonteCarlo::NuclearReactionType type_350 = MonteCarlo::N__ALPHA_EXCITED_STATE_9_REACTION;
    MonteCarlo::NuclearReactionType type_351 = MonteCarlo::N__ALPHA_EXCITED_STATE_10_REACTION;
    MonteCarlo::NuclearReactionType type_352 = MonteCarlo::N__ALPHA_EXCITED_STATE_11_REACTION;
    MonteCarlo::NuclearReactionType type_353 = MonteCarlo::N__ALPHA_EXCITED_STATE_12_REACTION;
    MonteCarlo::NuclearReactionType type_354 = MonteCarlo::N__ALPHA_EXCITED_STATE_13_REACTION;
    MonteCarlo::NuclearReactionType type_355 = MonteCarlo::N__ALPHA_EXCITED_STATE_14_REACTION;
    MonteCarlo::NuclearReactionType type_356 = MonteCarlo::N__ALPHA_EXCITED_STATE_15_REACTION;
    MonteCarlo::NuclearReactionType type_357 = MonteCarlo::N__ALPHA_EXCITED_STATE_16_REACTION;
    MonteCarlo::NuclearReactionType type_358 = MonteCarlo::N__ALPHA_EXCITED_STATE_17_REACTION;
    MonteCarlo::NuclearReactionType type_359 = MonteCarlo::N__ALPHA_EXCITED_STATE_18_REACTION;
    MonteCarlo::NuclearReactionType type_360 = MonteCarlo::N__ALPHA_EXCITED_STATE_19_REACTION;
    MonteCarlo::NuclearReactionType type_361 = MonteCarlo::N__ALPHA_EXCITED_STATE_20_REACTION;
    MonteCarlo::NuclearReactionType type_362 = MonteCarlo::N__ALPHA_EXCITED_STATE_21_REACTION;
    MonteCarlo::NuclearReactionType type_363 = MonteCarlo::N__ALPHA_EXCITED_STATE_22_REACTION;
    MonteCarlo::NuclearReactionType type_364 = MonteCarlo::N__ALPHA_EXCITED_STATE_23_REACTION;
    MonteCarlo::NuclearReactionType type_365 = MonteCarlo::N__ALPHA_EXCITED_STATE_24_REACTION;
    MonteCarlo::NuclearReactionType type_366 = MonteCarlo::N__ALPHA_EXCITED_STATE_25_REACTION;
    MonteCarlo::NuclearReactionType type_367 = MonteCarlo::N__ALPHA_EXCITED_STATE_26_REACTION;
    MonteCarlo::NuclearReactionType type_368 = MonteCarlo::N__ALPHA_EXCITED_STATE_27_REACTION;
    MonteCarlo::NuclearReactionType type_369 = MonteCarlo::N__ALPHA_EXCITED_STATE_28_REACTION;
    MonteCarlo::NuclearReactionType type_370 = MonteCarlo::N__ALPHA_EXCITED_STATE_29_REACTION;
    MonteCarlo::NuclearReactionType type_371 = MonteCarlo::N__ALPHA_EXCITED_STATE_30_REACTION;
    MonteCarlo::NuclearReactionType type_372 = MonteCarlo::N__ALPHA_EXCITED_STATE_31_REACTION;
    MonteCarlo::NuclearReactionType type_373 = MonteCarlo::N__ALPHA_EXCITED_STATE_32_REACTION;
    MonteCarlo::NuclearReactionType type_374 = MonteCarlo::N__ALPHA_EXCITED_STATE_33_REACTION;
    MonteCarlo::NuclearReactionType type_375 = MonteCarlo::N__ALPHA_EXCITED_STATE_34_REACTION;
    MonteCarlo::NuclearReactionType type_376 = MonteCarlo::N__ALPHA_EXCITED_STATE_35_REACTION;
    MonteCarlo::NuclearReactionType type_377 = MonteCarlo::N__ALPHA_EXCITED_STATE_36_REACTION;
    MonteCarlo::NuclearReactionType type_378 = MonteCarlo::N__ALPHA_EXCITED_STATE_37_REACTION;
    MonteCarlo::NuclearReactionType type_379 = MonteCarlo::N__ALPHA_EXCITED_STATE_38_REACTION;
    MonteCarlo::NuclearReactionType type_380 = MonteCarlo::N__ALPHA_EXCITED_STATE_39_REACTION;
    MonteCarlo::NuclearReactionType type_381 = MonteCarlo::N__ALPHA_EXCITED_STATE_40_REACTION;
    MonteCarlo::NuclearReactionType type_382 = MonteCarlo::N__ALPHA_EXCITED_STATE_41_REACTION;
    MonteCarlo::NuclearReactionType type_383 = MonteCarlo::N__ALPHA_EXCITED_STATE_42_REACTION;
    MonteCarlo::NuclearReactionType type_384 = MonteCarlo::N__ALPHA_EXCITED_STATE_43_REACTION;
    MonteCarlo::NuclearReactionType type_385 = MonteCarlo::N__ALPHA_EXCITED_STATE_44_REACTION;
    MonteCarlo::NuclearReactionType type_386 = MonteCarlo::N__ALPHA_EXCITED_STATE_45_REACTION;
    MonteCarlo::NuclearReactionType type_387 = MonteCarlo::N__ALPHA_EXCITED_STATE_46_REACTION;
    MonteCarlo::NuclearReactionType type_388 = MonteCarlo::N__ALPHA_EXCITED_STATE_47_REACTION;
    MonteCarlo::NuclearReactionType type_389 = MonteCarlo::N__ALPHA_EXCITED_STATE_48_REACTION;
    MonteCarlo::NuclearReactionType type_390 = MonteCarlo::N__ALPHA_CONTINUUM_REACTION;
    MonteCarlo::NuclearReactionType type_391 = MonteCarlo::N__2N_EXCITED_STATE_0_REACTION; 
    MonteCarlo::NuclearReactionType type_392 = MonteCarlo::N__2N_EXCITED_STATE_1_REACTION;
    MonteCarlo::NuclearReactionType type_393 = MonteCarlo::N__2N_EXCITED_STATE_2_REACTION;
    MonteCarlo::NuclearReactionType type_394 = MonteCarlo::N__2N_EXCITED_STATE_3_REACTION;
    MonteCarlo::NuclearReactionType type_395 = MonteCarlo::N__2N_EXCITED_STATE_4_REACTION;
    MonteCarlo::NuclearReactionType type_396 = MonteCarlo::N__2N_EXCITED_STATE_5_REACTION;
    MonteCarlo::NuclearReactionType type_397 = MonteCarlo::N__2N_EXCITED_STATE_6_REACTION;
    MonteCarlo::NuclearReactionType type_398 = MonteCarlo::N__2N_EXCITED_STATE_7_REACTION;
    MonteCarlo::NuclearReactionType type_399 = MonteCarlo::N__2N_EXCITED_STATE_8_REACTION;
    MonteCarlo::NuclearReactionType type_400 = MonteCarlo::N__2N_EXCITED_STATE_9_REACTION;
    MonteCarlo::NuclearReactionType type_401 = MonteCarlo::N__2N_EXCITED_STATE_10_REACTION;
    MonteCarlo::NuclearReactionType type_402 = MonteCarlo::N__2N_EXCITED_STATE_11_REACTION;
    MonteCarlo::NuclearReactionType type_403 = MonteCarlo::N__2N_EXCITED_STATE_12_REACTION;
    MonteCarlo::NuclearReactionType type_404 = MonteCarlo::N__2N_EXCITED_STATE_13_REACTION;
    MonteCarlo::NuclearReactionType type_405 = MonteCarlo::N__2N_EXCITED_STATE_14_REACTION;
    MonteCarlo::NuclearReactionType type_406 = MonteCarlo::N__2N_EXCITED_STATE_15_REACTION;
    MonteCarlo::NuclearReactionType type_407 = MonteCarlo::N__2N_CONTINUUM_REACTION;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_1 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_2 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_3 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_4 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_5 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_6 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_7 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_8 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_9 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_9a ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_9b ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_9c ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_10 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_11 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_12 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_12a ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_13 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_14 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_15 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_16 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_17 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_18 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_19 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_20 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_21 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_21a ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_22 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_23 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_24 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_25 ) );
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
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_68a ) );
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
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_87 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_88 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_89 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_90 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_91 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_92 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_93 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_94 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_95 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_96 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_97 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_98 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_99 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_100 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_101 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_102 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_103 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_104 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_105 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_106 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_107 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_108 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_109 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_110 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_111 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_112 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_113 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_114 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_115 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_116 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_117 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_118 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_119 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_120 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_121 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_122 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_123 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_124 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_125 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_126 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_127 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_128 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_129 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_130 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_131 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_132 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_133 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_134 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_135 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_136 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_137 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_138 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_139 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_140 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_141 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_142 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_143 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_144 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_145 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_146 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_147 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_148 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_149 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_150 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_151 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_152 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_153 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_154 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_155 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_156 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_157 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_158 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_159 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_160 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_161 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_162 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_163 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_164 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_165 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_166 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_167 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_168 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_169 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_170 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_171 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_172 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_173 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_174 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_175 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_176 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_177 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_178 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_179 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_180 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_181 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_182 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_183 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_184 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_185 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_186 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_187 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_188 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_189 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_190 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_191 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_192 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_193 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_194 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_195 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_196 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_197 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_198 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_199 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_200 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_201 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_202 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_203 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_204 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_205 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_206 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_207 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_208 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_209 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_210 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_211 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_212 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_213 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_214 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_215 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_216 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_217 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_218 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_219 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_220 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_221 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_222 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_223 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_224 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_225 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_226 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_227 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_228 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_229 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_230 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_231 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_232 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_233 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_234 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_235 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_236 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_237 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_238 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_239 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_240 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_241 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_242 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_243 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_244 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_245 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_246 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_247 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_248 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_249 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_250 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_251 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_252 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_253 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_254 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_255 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_256 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_257 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_258 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_259 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_260 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_261 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_262 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_263 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_264 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_265 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_266 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_267 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_268 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_269 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_270 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_271 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_272 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_273 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_274 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_275 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_276 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_277 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_278 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_279 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_280 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_281 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_282 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_283 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_284 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_285 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_286 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_287 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_288 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_289 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_290 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_291 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_292 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_293 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_294 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_295 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_296 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_297 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_298 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_299 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_300 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_301 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_302 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_303 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_304 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_305 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_306 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_307 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_308 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_309 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_310 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_311 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_312 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_313 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_314 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_315 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_316 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_317 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_318 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_319 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_320 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_321 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_322 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_323 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_324 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_325 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_326 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_327 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_328 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_329 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_330 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_331 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_332 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_333 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_334 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_335 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_336 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_337 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_338 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_339 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_340 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_341 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_342 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_343 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_344 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_345 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_346 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_347 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_348 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_349 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_350 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_351 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_352 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_353 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_354 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_355 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_356 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_357 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_358 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_359 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_360 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_361 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_362 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_363 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_364 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_365 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_366 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_367 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_368 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_369 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_370 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_371 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_372 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_373 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_374 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_375 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_376 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_377 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_378 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_379 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_380 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_381 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_382 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_383 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_384 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_385 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_386 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_387 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_388 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_389 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_390 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_391 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_392 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_393 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_394 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_395 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_396 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_397 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_398 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_399 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_400 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_401 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_402 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_403 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_404 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_405 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_406 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_407 ) );
  }

  {
    std::ofstream ofs( "test.out" );
    ofs << archive_ostream.str();
    ofs.close();
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::NuclearReactionType type_1, type_2, type_3, type_4, type_5,
    type_6, type_7, type_8, type_9, type_9a, type_9b, type_9c, type_10,
    type_11, type_12, type_12a, type_13, type_14, type_15, type_16, type_17,
    type_18, type_19, type_20, type_21, type_21a, type_22, type_23, type_24,
    type_25, type_27, type_28, type_29, type_30, type_31, type_32, type_33,
    type_34, type_35, type_36, type_37, type_38, type_39, type_40, type_41,
    type_42, type_43, type_44, type_45, type_46, type_47, type_48, type_49,
    type_50, type_51, type_52, type_53, type_54, type_55, type_56, type_57,
    type_58, type_59, type_60, type_61, type_62, type_63, type_64, type_65,
    type_66, type_67, type_68, type_68a, type_69, type_70, type_71, type_72,
    type_73, type_74, type_75, type_76, type_77, type_78, type_79, type_80,
    type_81, type_82, type_83, type_84, type_85, type_86, type_87, type_88,
    type_89, type_90, type_91, type_92, type_93, type_94, type_95, type_96,
    type_97, type_98, type_99, type_100, type_101, type_102, type_103,
    type_104, type_105, type_106, type_107, type_108, type_109, type_110,
    type_111, type_112, type_113, type_114, type_115, type_116, type_117,
    type_118, type_119, type_120, type_121, type_122, type_123, type_124,
    type_125, type_126, type_127, type_128, type_129, type_130, type_131,
    type_132, type_133, type_134, type_135, type_136, type_137, type_138,
    type_139, type_140, type_141, type_142, type_143, type_144, type_145,
    type_146, type_147, type_148, type_149, type_150, type_151, type_152,
    type_153, type_154, type_155, type_156, type_157, type_158, type_159,
    type_160, type_161, type_162, type_163, type_164, type_165, type_166,
    type_167, type_168, type_169, type_170, type_171, type_172, type_173,
    type_174, type_175, type_176, type_177, type_178, type_179, type_180,
    type_181, type_182, type_183, type_184, type_185, type_186, type_187,
    type_188, type_189, type_190, type_191, type_192, type_193, type_194,
    type_195, type_196, type_197, type_198, type_199, type_200, type_201,
    type_202, type_203, type_204, type_205, type_206, type_207, type_208,
    type_209, type_210, type_211, type_212, type_213, type_214, type_215,
    type_216, type_217, type_218, type_219, type_220, type_221, type_222,
    type_223, type_224, type_225, type_226, type_227, type_228, type_229,
    type_230, type_231, type_232, type_233, type_234, type_235, type_236,
    type_237, type_238, type_239, type_240, type_241, type_242, type_243,
    type_244, type_245, type_246, type_247, type_248, type_249, type_250,
    type_251, type_252, type_253, type_254, type_255, type_256, type_257,
    type_258, type_259, type_260, type_261, type_262, type_263, type_264,
    type_265, type_266, type_267, type_268, type_269, type_270, type_271,
    type_272, type_273, type_274, type_275, type_276, type_277, type_278,
    type_279, type_280, type_281, type_282, type_283, type_284, type_285,
    type_286, type_287, type_288, type_289, type_290, type_291, type_292,
    type_293, type_294, type_295, type_296, type_297, type_298, type_299,
    type_300, type_301, type_302, type_303, type_304, type_305, type_306,
    type_307, type_308, type_309, type_310, type_311, type_312, type_313,
    type_314, type_315, type_316, type_317, type_318, type_319, type_320,
    type_321, type_322, type_323, type_324, type_325, type_326, type_327,
    type_328, type_329, type_330, type_331, type_332, type_333, type_334,
    type_335, type_336, type_337, type_338, type_339, type_340, type_341,
    type_342, type_343, type_344, type_345, type_346, type_347, type_348,
    type_349, type_350, type_351, type_352, type_353, type_354, type_355,
    type_356, type_357, type_358, type_359, type_360, type_361, type_362,
    type_363, type_364, type_365, type_366, type_367, type_368, type_369,
    type_370, type_371, type_372, type_373, type_374, type_375, type_376,
    type_377, type_378, type_379, type_380, type_381, type_382, type_383,
    type_384, type_385, type_386, type_387, type_388, type_389, type_390,
    type_391, type_392, type_393, type_394, type_395, type_396, type_397,
    type_398, type_399, type_400, type_401, type_402, type_403, type_404,
    type_405, type_406, type_407;
  
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_1 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_2 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_3 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_4 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_5 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_6 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_7 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_8 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_9 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_9a ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_9b ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_9c ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_10 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_11 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_12 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_12a ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_13 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_14 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_15 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_16 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_17 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_18 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_19 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_20 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_21 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_21a ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_22 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_23 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_24 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_25 ) );
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
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_68a ) );
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
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_87 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_88 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_89 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_90 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_91 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_92 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_93 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_94 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_95 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_96 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_97 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_98 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_99 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_100 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_101 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_102 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_103 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_104 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_105 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_106 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_107 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_108 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_109 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_110 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_111 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_112 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_113 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_114 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_115 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_116 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_117 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_118 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_119 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_120 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_121 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_122 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_123 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_124 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_125 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_126 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_127 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_128 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_129 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_130 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_131 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_132 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_133 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_134 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_135 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_136 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_137 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_138 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_139 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_140 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_141 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_142 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_143 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_144 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_145 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_146 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_147 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_148 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_149 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_150 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_151 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_152 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_153 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_154 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_155 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_156 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_157 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_158 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_159 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_160 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_161 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_162 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_163 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_164 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_165 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_166 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_167 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_168 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_169 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_170 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_171 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_172 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_173 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_174 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_175 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_176 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_177 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_178 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_179 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_180 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_181 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_182 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_183 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_184 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_185 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_186 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_187 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_188 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_189 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_190 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_191 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_192 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_193 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_194 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_195 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_196 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_197 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_198 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_199 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_200 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_201 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_202 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_203 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_204 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_205 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_206 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_207 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_208 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_209 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_210 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_211 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_212 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_213 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_214 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_215 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_216 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_217 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_218 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_219 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_220 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_221 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_222 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_223 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_224 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_225 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_226 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_227 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_228 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_229 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_230 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_231 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_232 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_233 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_234 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_235 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_236 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_237 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_238 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_239 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_240 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_241 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_242 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_243 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_244 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_245 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_246 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_247 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_248 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_249 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_250 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_251 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_252 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_253 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_254 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_255 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_256 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_257 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_258 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_259 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_260 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_261 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_262 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_263 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_264 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_265 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_266 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_267 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_268 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_269 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_270 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_271 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_272 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_273 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_274 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_275 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_276 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_277 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_278 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_279 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_280 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_281 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_282 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_283 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_284 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_285 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_286 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_287 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_288 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_289 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_290 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_291 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_292 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_293 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_294 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_295 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_296 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_297 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_298 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_299 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_300 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_301 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_302 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_303 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_304 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_305 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_306 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_307 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_308 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_309 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_310 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_311 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_312 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_313 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_314 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_315 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_316 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_317 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_318 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_319 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_320 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_321 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_322 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_323 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_324 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_325 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_326 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_327 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_328 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_329 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_330 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_331 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_332 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_333 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_334 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_335 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_336 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_337 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_338 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_339 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_340 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_341 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_342 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_343 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_344 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_345 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_346 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_347 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_348 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_349 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_350 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_351 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_352 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_353 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_354 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_355 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_356 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_357 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_358 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_359 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_360 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_361 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_362 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_363 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_364 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_365 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_366 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_367 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_368 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_369 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_370 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_371 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_372 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_373 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_374 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_375 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_376 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_377 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_378 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_379 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_380 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_381 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_382 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_383 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_384 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_385 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_386 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_387 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_388 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_389 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_390 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_391 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_392 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_393 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_394 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_395 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_396 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_397 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_398 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_399 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_400 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_401 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_402 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_403 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_404 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_405 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_406 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_407 ) );

  iarchive.reset();
  
  FRENSIE_CHECK_EQUAL( type_1, MonteCarlo::N__TOTAL_REACTION );
  FRENSIE_CHECK_EQUAL( type_2, MonteCarlo::N__N_ELASTIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_3, MonteCarlo::N__N_NON_ELASTIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_4, MonteCarlo::N__N_INELASTIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_5, MonteCarlo::N__ANYTHING_REACTION );
  FRENSIE_CHECK_EQUAL( type_6, MonteCarlo::N__2N_D_REACTION );
  FRENSIE_CHECK_EQUAL( type_7, MonteCarlo::N__2N_REACTION );
  FRENSIE_CHECK_EQUAL( type_8, MonteCarlo::N__3N_REACTION );
  FRENSIE_CHECK_EQUAL( type_9, MonteCarlo::N__TOTAL_FISSION_REACTION );
  FRENSIE_CHECK_EQUAL( type_9a, MonteCarlo::N__FISSION_REACTION );
  FRENSIE_CHECK_EQUAL( type_9b, MonteCarlo::N__N_FISSION_REACTION );
  FRENSIE_CHECK_EQUAL( type_9c, MonteCarlo::N__2N_FISSION_REACTION );
  FRENSIE_CHECK_EQUAL( type_10, MonteCarlo::N__N_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_11, MonteCarlo::N__2N_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_12, MonteCarlo::N__3N_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_12a, MonteCarlo::N__TOTAL_ABSORPTION_REACTION );
  FRENSIE_CHECK_EQUAL( type_13, MonteCarlo::N__N_P_REACTION );
  FRENSIE_CHECK_EQUAL( type_14, MonteCarlo::N__N_2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_15, MonteCarlo::N__2N_2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_16, MonteCarlo::N__N_D_REACTION );
  FRENSIE_CHECK_EQUAL( type_17, MonteCarlo::N__N_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_18, MonteCarlo::N__N_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_19, MonteCarlo::N__N_D_2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_20, MonteCarlo::N__N_T_2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_21, MonteCarlo::N__4N_REACTION );
  FRENSIE_CHECK_EQUAL( type_21a, MonteCarlo::N__3N_FISSION_REACTION );
  FRENSIE_CHECK_EQUAL( type_22, MonteCarlo::N__2N_P_REACTION );
  FRENSIE_CHECK_EQUAL( type_23, MonteCarlo::N__3N_P_REACTION );
  FRENSIE_CHECK_EQUAL( type_24, MonteCarlo::N__N_2P_REACTION );
  FRENSIE_CHECK_EQUAL( type_25, MonteCarlo::N__N_P_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_27, MonteCarlo::N__N_EXCITED_STATE_1_REACTION );
  FRENSIE_CHECK_EQUAL( type_28, MonteCarlo::N__N_EXCITED_STATE_2_REACTION );
  FRENSIE_CHECK_EQUAL( type_29, MonteCarlo::N__N_EXCITED_STATE_3_REACTION );
  FRENSIE_CHECK_EQUAL( type_30, MonteCarlo::N__N_EXCITED_STATE_4_REACTION );
  FRENSIE_CHECK_EQUAL( type_31, MonteCarlo::N__N_EXCITED_STATE_5_REACTION );
  FRENSIE_CHECK_EQUAL( type_32, MonteCarlo::N__N_EXCITED_STATE_6_REACTION );
  FRENSIE_CHECK_EQUAL( type_33, MonteCarlo::N__N_EXCITED_STATE_7_REACTION );
  FRENSIE_CHECK_EQUAL( type_34, MonteCarlo::N__N_EXCITED_STATE_8_REACTION );
  FRENSIE_CHECK_EQUAL( type_35, MonteCarlo::N__N_EXCITED_STATE_9_REACTION );
  FRENSIE_CHECK_EQUAL( type_36, MonteCarlo::N__N_EXCITED_STATE_10_REACTION );
  FRENSIE_CHECK_EQUAL( type_37, MonteCarlo::N__N_EXCITED_STATE_11_REACTION );
  FRENSIE_CHECK_EQUAL( type_38, MonteCarlo::N__N_EXCITED_STATE_12_REACTION );
  FRENSIE_CHECK_EQUAL( type_39, MonteCarlo::N__N_EXCITED_STATE_13_REACTION );
  FRENSIE_CHECK_EQUAL( type_40, MonteCarlo::N__N_EXCITED_STATE_14_REACTION );
  FRENSIE_CHECK_EQUAL( type_41, MonteCarlo::N__N_EXCITED_STATE_15_REACTION );
  FRENSIE_CHECK_EQUAL( type_42, MonteCarlo::N__N_EXCITED_STATE_16_REACTION );
  FRENSIE_CHECK_EQUAL( type_43, MonteCarlo::N__N_EXCITED_STATE_17_REACTION );
  FRENSIE_CHECK_EQUAL( type_44, MonteCarlo::N__N_EXCITED_STATE_18_REACTION );
  FRENSIE_CHECK_EQUAL( type_45, MonteCarlo::N__N_EXCITED_STATE_19_REACTION );
  FRENSIE_CHECK_EQUAL( type_46, MonteCarlo::N__N_EXCITED_STATE_20_REACTION );
  FRENSIE_CHECK_EQUAL( type_47, MonteCarlo::N__N_EXCITED_STATE_21_REACTION );
  FRENSIE_CHECK_EQUAL( type_48, MonteCarlo::N__N_EXCITED_STATE_22_REACTION );
  FRENSIE_CHECK_EQUAL( type_49, MonteCarlo::N__N_EXCITED_STATE_23_REACTION );
  FRENSIE_CHECK_EQUAL( type_50, MonteCarlo::N__N_EXCITED_STATE_24_REACTION );
  FRENSIE_CHECK_EQUAL( type_51, MonteCarlo::N__N_EXCITED_STATE_25_REACTION );
  FRENSIE_CHECK_EQUAL( type_52, MonteCarlo::N__N_EXCITED_STATE_26_REACTION );
  FRENSIE_CHECK_EQUAL( type_53, MonteCarlo::N__N_EXCITED_STATE_27_REACTION );
  FRENSIE_CHECK_EQUAL( type_54, MonteCarlo::N__N_EXCITED_STATE_28_REACTION );
  FRENSIE_CHECK_EQUAL( type_55, MonteCarlo::N__N_EXCITED_STATE_29_REACTION );
  FRENSIE_CHECK_EQUAL( type_56, MonteCarlo::N__N_EXCITED_STATE_30_REACTION );
  FRENSIE_CHECK_EQUAL( type_57, MonteCarlo::N__N_EXCITED_STATE_31_REACTION );
  FRENSIE_CHECK_EQUAL( type_58, MonteCarlo::N__N_EXCITED_STATE_32_REACTION );
  FRENSIE_CHECK_EQUAL( type_59, MonteCarlo::N__N_EXCITED_STATE_33_REACTION );
  FRENSIE_CHECK_EQUAL( type_60, MonteCarlo::N__N_EXCITED_STATE_34_REACTION );
  FRENSIE_CHECK_EQUAL( type_61, MonteCarlo::N__N_EXCITED_STATE_35_REACTION );
  FRENSIE_CHECK_EQUAL( type_62, MonteCarlo::N__N_EXCITED_STATE_36_REACTION );
  FRENSIE_CHECK_EQUAL( type_63, MonteCarlo::N__N_EXCITED_STATE_37_REACTION );
  FRENSIE_CHECK_EQUAL( type_64, MonteCarlo::N__N_EXCITED_STATE_38_REACTION );
  FRENSIE_CHECK_EQUAL( type_65, MonteCarlo::N__N_EXCITED_STATE_39_REACTION );
  FRENSIE_CHECK_EQUAL( type_66, MonteCarlo::N__N_EXCITED_STATE_40_REACTION );
  FRENSIE_CHECK_EQUAL( type_67, MonteCarlo::N__N_CONTINUUM_REACTION );
  FRENSIE_CHECK_EQUAL( type_68, MonteCarlo::N__CAPTURE_REACTION );
  FRENSIE_CHECK_EQUAL( type_68a, MonteCarlo::N__GAMMA_REACTION );
  FRENSIE_CHECK_EQUAL( type_69, MonteCarlo::N__P_REACTION );
  FRENSIE_CHECK_EQUAL( type_70, MonteCarlo::N__D_REACTION );
  FRENSIE_CHECK_EQUAL( type_71, MonteCarlo::N__T_REACTION );
  FRENSIE_CHECK_EQUAL( type_72, MonteCarlo::N__HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_73, MonteCarlo::N__ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_74, MonteCarlo::N__2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_75, MonteCarlo::N__3ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_76, MonteCarlo::N__2P_REACTION );
  FRENSIE_CHECK_EQUAL( type_77, MonteCarlo::N__P_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_78, MonteCarlo::N__T_2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_79, MonteCarlo::N__D_2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_80, MonteCarlo::N__P_D_REACTION );
  FRENSIE_CHECK_EQUAL( type_81, MonteCarlo::N__P_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_82, MonteCarlo::N__D_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_83, MonteCarlo::N__5N_REACTION );
  FRENSIE_CHECK_EQUAL( type_84, MonteCarlo::N__6N_REACTION );
  FRENSIE_CHECK_EQUAL( type_85, MonteCarlo::N__2N_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_86, MonteCarlo::N__T_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_87, MonteCarlo::N__4N_P_REACTION );
  FRENSIE_CHECK_EQUAL( type_88, MonteCarlo::N__3N_D_REACTION );
  FRENSIE_CHECK_EQUAL( type_89, MonteCarlo::N__N_D_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_90, MonteCarlo::N__2N_P_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_91, MonteCarlo::N__7N_REACTION );
  FRENSIE_CHECK_EQUAL( type_92, MonteCarlo::N__8N_REACTION );
  FRENSIE_CHECK_EQUAL( type_93, MonteCarlo::N__5N_P_REACTION );
  FRENSIE_CHECK_EQUAL( type_94, MonteCarlo::N__6N_P_REACTION );
  FRENSIE_CHECK_EQUAL( type_95, MonteCarlo::N__7N_P_REACTION );
  FRENSIE_CHECK_EQUAL( type_96, MonteCarlo::N__4N_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_97, MonteCarlo::N__5N_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_98, MonteCarlo::N__6N_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_99, MonteCarlo::N__7N_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_100, MonteCarlo::N__4N_D_REACTION );
  FRENSIE_CHECK_EQUAL( type_101, MonteCarlo::N__5N_D_REACTION );
  FRENSIE_CHECK_EQUAL( type_102, MonteCarlo::N__6N_D_REACTION );
  FRENSIE_CHECK_EQUAL( type_103, MonteCarlo::N__3N_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_104, MonteCarlo::N__4N_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_105, MonteCarlo::N__5N_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_106, MonteCarlo::N__6N_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_107, MonteCarlo::N__2N_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_108, MonteCarlo::N__3N_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_109, MonteCarlo::N__4N_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_110, MonteCarlo::N__3N_2P_REACTION );
  FRENSIE_CHECK_EQUAL( type_111, MonteCarlo::N__3N_2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_112, MonteCarlo::N__3N_P_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_113, MonteCarlo::N__D_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_114, MonteCarlo::N__N_P_D_REACTION );
  FRENSIE_CHECK_EQUAL( type_115, MonteCarlo::N__N_P_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_116, MonteCarlo::N__N_D_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_117, MonteCarlo::N__N_P_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_118, MonteCarlo::N__N_D_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_119, MonteCarlo::N__N_T_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_120, MonteCarlo::N__N_T_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_121, MonteCarlo::N__2N_2P_REACTION );
  FRENSIE_CHECK_EQUAL( type_122, MonteCarlo::N__P_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_123, MonteCarlo::N__D_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_124, MonteCarlo::N__HE3_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_125, MonteCarlo::N__4N_2P_REACTION );
  FRENSIE_CHECK_EQUAL( type_126, MonteCarlo::N__4N_2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_127, MonteCarlo::N__4N_P_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_128, MonteCarlo::N__3P_REACTION );
  FRENSIE_CHECK_EQUAL( type_129, MonteCarlo::N__N_3P_REACTION );
  FRENSIE_CHECK_EQUAL( type_130, MonteCarlo::N__3N_2P_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_131, MonteCarlo::N__5N_2P_REACTION );
  FRENSIE_CHECK_EQUAL( type_132, MonteCarlo::N__TOTAL_N_PRODUCTION );
  FRENSIE_CHECK_EQUAL( type_133, MonteCarlo::N__TOTAL_GAMMA_PRODUCTION );
  FRENSIE_CHECK_EQUAL( type_134, MonteCarlo::N__TOTAL_P_PRODUCTION );
  FRENSIE_CHECK_EQUAL( type_135, MonteCarlo::N__TOTAL_D_PRODUCTION );
  FRENSIE_CHECK_EQUAL( type_136, MonteCarlo::N__TOTAL_T_PRODUCTION );
  FRENSIE_CHECK_EQUAL( type_137, MonteCarlo::N__TOTAL_HE3_PRODUCTION );
  FRENSIE_CHECK_EQUAL( type_138, MonteCarlo::N__TOTAL_ALPHA_PRODUCTION );
  FRENSIE_CHECK_EQUAL( type_139, MonteCarlo::N__AVERAGE_HEATING );
  FRENSIE_CHECK_EQUAL( type_140, MonteCarlo::N__DAMAGE );
  FRENSIE_CHECK_EQUAL( type_141, MonteCarlo::N__P_EXCITED_STATE_0_REACTION );
  FRENSIE_CHECK_EQUAL( type_142, MonteCarlo::N__P_EXCITED_STATE_1_REACTION );
  FRENSIE_CHECK_EQUAL( type_143, MonteCarlo::N__P_EXCITED_STATE_2_REACTION );
  FRENSIE_CHECK_EQUAL( type_144, MonteCarlo::N__P_EXCITED_STATE_3_REACTION );
  FRENSIE_CHECK_EQUAL( type_145, MonteCarlo::N__P_EXCITED_STATE_4_REACTION );
  FRENSIE_CHECK_EQUAL( type_146, MonteCarlo::N__P_EXCITED_STATE_5_REACTION );
  FRENSIE_CHECK_EQUAL( type_147, MonteCarlo::N__P_EXCITED_STATE_6_REACTION );
  FRENSIE_CHECK_EQUAL( type_148, MonteCarlo::N__P_EXCITED_STATE_7_REACTION );
  FRENSIE_CHECK_EQUAL( type_149, MonteCarlo::N__P_EXCITED_STATE_8_REACTION );
  FRENSIE_CHECK_EQUAL( type_150, MonteCarlo::N__P_EXCITED_STATE_9_REACTION );
  FRENSIE_CHECK_EQUAL( type_151, MonteCarlo::N__P_EXCITED_STATE_10_REACTION );
  FRENSIE_CHECK_EQUAL( type_152, MonteCarlo::N__P_EXCITED_STATE_11_REACTION );
  FRENSIE_CHECK_EQUAL( type_153, MonteCarlo::N__P_EXCITED_STATE_12_REACTION );
  FRENSIE_CHECK_EQUAL( type_154, MonteCarlo::N__P_EXCITED_STATE_13_REACTION );
  FRENSIE_CHECK_EQUAL( type_155, MonteCarlo::N__P_EXCITED_STATE_14_REACTION );
  FRENSIE_CHECK_EQUAL( type_156, MonteCarlo::N__P_EXCITED_STATE_15_REACTION );
  FRENSIE_CHECK_EQUAL( type_157, MonteCarlo::N__P_EXCITED_STATE_16_REACTION );
  FRENSIE_CHECK_EQUAL( type_158, MonteCarlo::N__P_EXCITED_STATE_17_REACTION );
  FRENSIE_CHECK_EQUAL( type_159, MonteCarlo::N__P_EXCITED_STATE_18_REACTION );
  FRENSIE_CHECK_EQUAL( type_160, MonteCarlo::N__P_EXCITED_STATE_19_REACTION );
  FRENSIE_CHECK_EQUAL( type_161, MonteCarlo::N__P_EXCITED_STATE_20_REACTION );
  FRENSIE_CHECK_EQUAL( type_162, MonteCarlo::N__P_EXCITED_STATE_21_REACTION );
  FRENSIE_CHECK_EQUAL( type_163, MonteCarlo::N__P_EXCITED_STATE_22_REACTION );
  FRENSIE_CHECK_EQUAL( type_164, MonteCarlo::N__P_EXCITED_STATE_23_REACTION );
  FRENSIE_CHECK_EQUAL( type_165, MonteCarlo::N__P_EXCITED_STATE_24_REACTION );
  FRENSIE_CHECK_EQUAL( type_166, MonteCarlo::N__P_EXCITED_STATE_25_REACTION );
  FRENSIE_CHECK_EQUAL( type_167, MonteCarlo::N__P_EXCITED_STATE_26_REACTION );
  FRENSIE_CHECK_EQUAL( type_168, MonteCarlo::N__P_EXCITED_STATE_27_REACTION );
  FRENSIE_CHECK_EQUAL( type_169, MonteCarlo::N__P_EXCITED_STATE_28_REACTION );
  FRENSIE_CHECK_EQUAL( type_170, MonteCarlo::N__P_EXCITED_STATE_29_REACTION );
  FRENSIE_CHECK_EQUAL( type_171, MonteCarlo::N__P_EXCITED_STATE_30_REACTION );
  FRENSIE_CHECK_EQUAL( type_172, MonteCarlo::N__P_EXCITED_STATE_31_REACTION );
  FRENSIE_CHECK_EQUAL( type_173, MonteCarlo::N__P_EXCITED_STATE_32_REACTION );
  FRENSIE_CHECK_EQUAL( type_174, MonteCarlo::N__P_EXCITED_STATE_33_REACTION );
  FRENSIE_CHECK_EQUAL( type_175, MonteCarlo::N__P_EXCITED_STATE_34_REACTION );
  FRENSIE_CHECK_EQUAL( type_176, MonteCarlo::N__P_EXCITED_STATE_35_REACTION );
  FRENSIE_CHECK_EQUAL( type_177, MonteCarlo::N__P_EXCITED_STATE_36_REACTION );
  FRENSIE_CHECK_EQUAL( type_178, MonteCarlo::N__P_EXCITED_STATE_37_REACTION );
  FRENSIE_CHECK_EQUAL( type_179, MonteCarlo::N__P_EXCITED_STATE_38_REACTION );
  FRENSIE_CHECK_EQUAL( type_180, MonteCarlo::N__P_EXCITED_STATE_39_REACTION );
  FRENSIE_CHECK_EQUAL( type_181, MonteCarlo::N__P_EXCITED_STATE_40_REACTION );
  FRENSIE_CHECK_EQUAL( type_182, MonteCarlo::N__P_EXCITED_STATE_41_REACTION );
  FRENSIE_CHECK_EQUAL( type_183, MonteCarlo::N__P_EXCITED_STATE_42_REACTION );
  FRENSIE_CHECK_EQUAL( type_184, MonteCarlo::N__P_EXCITED_STATE_43_REACTION );
  FRENSIE_CHECK_EQUAL( type_185, MonteCarlo::N__P_EXCITED_STATE_44_REACTION );
  FRENSIE_CHECK_EQUAL( type_186, MonteCarlo::N__P_EXCITED_STATE_45_REACTION );
  FRENSIE_CHECK_EQUAL( type_187, MonteCarlo::N__P_EXCITED_STATE_46_REACTION );
  FRENSIE_CHECK_EQUAL( type_188, MonteCarlo::N__P_EXCITED_STATE_47_REACTION );
  FRENSIE_CHECK_EQUAL( type_189, MonteCarlo::N__P_EXCITED_STATE_48_REACTION );
  FRENSIE_CHECK_EQUAL( type_190, MonteCarlo::N__P_CONTINUUM_REACTION );
  FRENSIE_CHECK_EQUAL( type_191, MonteCarlo::N__D_EXCITED_STATE_0_REACTION );
  FRENSIE_CHECK_EQUAL( type_192, MonteCarlo::N__D_EXCITED_STATE_1_REACTION );
  FRENSIE_CHECK_EQUAL( type_193, MonteCarlo::N__D_EXCITED_STATE_2_REACTION );
  FRENSIE_CHECK_EQUAL( type_194, MonteCarlo::N__D_EXCITED_STATE_3_REACTION );
  FRENSIE_CHECK_EQUAL( type_195, MonteCarlo::N__D_EXCITED_STATE_4_REACTION );
  FRENSIE_CHECK_EQUAL( type_196, MonteCarlo::N__D_EXCITED_STATE_5_REACTION );
  FRENSIE_CHECK_EQUAL( type_197, MonteCarlo::N__D_EXCITED_STATE_6_REACTION );
  FRENSIE_CHECK_EQUAL( type_198, MonteCarlo::N__D_EXCITED_STATE_7_REACTION );
  FRENSIE_CHECK_EQUAL( type_199, MonteCarlo::N__D_EXCITED_STATE_8_REACTION );
  FRENSIE_CHECK_EQUAL( type_200, MonteCarlo::N__D_EXCITED_STATE_9_REACTION );
  FRENSIE_CHECK_EQUAL( type_201, MonteCarlo::N__D_EXCITED_STATE_10_REACTION );
  FRENSIE_CHECK_EQUAL( type_202, MonteCarlo::N__D_EXCITED_STATE_11_REACTION );
  FRENSIE_CHECK_EQUAL( type_203, MonteCarlo::N__D_EXCITED_STATE_12_REACTION );
  FRENSIE_CHECK_EQUAL( type_204, MonteCarlo::N__D_EXCITED_STATE_13_REACTION );
  FRENSIE_CHECK_EQUAL( type_205, MonteCarlo::N__D_EXCITED_STATE_14_REACTION );
  FRENSIE_CHECK_EQUAL( type_206, MonteCarlo::N__D_EXCITED_STATE_15_REACTION );
  FRENSIE_CHECK_EQUAL( type_207, MonteCarlo::N__D_EXCITED_STATE_16_REACTION );
  FRENSIE_CHECK_EQUAL( type_208, MonteCarlo::N__D_EXCITED_STATE_17_REACTION );
  FRENSIE_CHECK_EQUAL( type_209, MonteCarlo::N__D_EXCITED_STATE_18_REACTION );
  FRENSIE_CHECK_EQUAL( type_210, MonteCarlo::N__D_EXCITED_STATE_19_REACTION );
  FRENSIE_CHECK_EQUAL( type_211, MonteCarlo::N__D_EXCITED_STATE_20_REACTION );
  FRENSIE_CHECK_EQUAL( type_212, MonteCarlo::N__D_EXCITED_STATE_21_REACTION );
  FRENSIE_CHECK_EQUAL( type_213, MonteCarlo::N__D_EXCITED_STATE_22_REACTION );
  FRENSIE_CHECK_EQUAL( type_214, MonteCarlo::N__D_EXCITED_STATE_23_REACTION );
  FRENSIE_CHECK_EQUAL( type_215, MonteCarlo::N__D_EXCITED_STATE_24_REACTION );
  FRENSIE_CHECK_EQUAL( type_216, MonteCarlo::N__D_EXCITED_STATE_25_REACTION );
  FRENSIE_CHECK_EQUAL( type_217, MonteCarlo::N__D_EXCITED_STATE_26_REACTION );
  FRENSIE_CHECK_EQUAL( type_218, MonteCarlo::N__D_EXCITED_STATE_27_REACTION );
  FRENSIE_CHECK_EQUAL( type_219, MonteCarlo::N__D_EXCITED_STATE_28_REACTION );
  FRENSIE_CHECK_EQUAL( type_220, MonteCarlo::N__D_EXCITED_STATE_29_REACTION );
  FRENSIE_CHECK_EQUAL( type_221, MonteCarlo::N__D_EXCITED_STATE_30_REACTION );
  FRENSIE_CHECK_EQUAL( type_222, MonteCarlo::N__D_EXCITED_STATE_31_REACTION );
  FRENSIE_CHECK_EQUAL( type_223, MonteCarlo::N__D_EXCITED_STATE_32_REACTION );
  FRENSIE_CHECK_EQUAL( type_224, MonteCarlo::N__D_EXCITED_STATE_33_REACTION );
  FRENSIE_CHECK_EQUAL( type_225, MonteCarlo::N__D_EXCITED_STATE_34_REACTION );
  FRENSIE_CHECK_EQUAL( type_226, MonteCarlo::N__D_EXCITED_STATE_35_REACTION );
  FRENSIE_CHECK_EQUAL( type_227, MonteCarlo::N__D_EXCITED_STATE_36_REACTION );
  FRENSIE_CHECK_EQUAL( type_228, MonteCarlo::N__D_EXCITED_STATE_37_REACTION );
  FRENSIE_CHECK_EQUAL( type_229, MonteCarlo::N__D_EXCITED_STATE_38_REACTION );
  FRENSIE_CHECK_EQUAL( type_230, MonteCarlo::N__D_EXCITED_STATE_39_REACTION );
  FRENSIE_CHECK_EQUAL( type_231, MonteCarlo::N__D_EXCITED_STATE_40_REACTION );
  FRENSIE_CHECK_EQUAL( type_232, MonteCarlo::N__D_EXCITED_STATE_41_REACTION );
  FRENSIE_CHECK_EQUAL( type_233, MonteCarlo::N__D_EXCITED_STATE_42_REACTION );
  FRENSIE_CHECK_EQUAL( type_234, MonteCarlo::N__D_EXCITED_STATE_43_REACTION );
  FRENSIE_CHECK_EQUAL( type_235, MonteCarlo::N__D_EXCITED_STATE_44_REACTION );
  FRENSIE_CHECK_EQUAL( type_236, MonteCarlo::N__D_EXCITED_STATE_45_REACTION );
  FRENSIE_CHECK_EQUAL( type_237, MonteCarlo::N__D_EXCITED_STATE_46_REACTION );
  FRENSIE_CHECK_EQUAL( type_238, MonteCarlo::N__D_EXCITED_STATE_47_REACTION );
  FRENSIE_CHECK_EQUAL( type_239, MonteCarlo::N__D_EXCITED_STATE_48_REACTION );
  FRENSIE_CHECK_EQUAL( type_240, MonteCarlo::N__D_CONTINUUM_REACTION );
  FRENSIE_CHECK_EQUAL( type_241, MonteCarlo::N__T_EXCITED_STATE_0_REACTION );
  FRENSIE_CHECK_EQUAL( type_242, MonteCarlo::N__T_EXCITED_STATE_1_REACTION );
  FRENSIE_CHECK_EQUAL( type_243, MonteCarlo::N__T_EXCITED_STATE_2_REACTION );
  FRENSIE_CHECK_EQUAL( type_244, MonteCarlo::N__T_EXCITED_STATE_3_REACTION );
  FRENSIE_CHECK_EQUAL( type_245, MonteCarlo::N__T_EXCITED_STATE_4_REACTION );
  FRENSIE_CHECK_EQUAL( type_246, MonteCarlo::N__T_EXCITED_STATE_5_REACTION );
  FRENSIE_CHECK_EQUAL( type_247, MonteCarlo::N__T_EXCITED_STATE_6_REACTION );
  FRENSIE_CHECK_EQUAL( type_248, MonteCarlo::N__T_EXCITED_STATE_7_REACTION );
  FRENSIE_CHECK_EQUAL( type_249, MonteCarlo::N__T_EXCITED_STATE_8_REACTION );
  FRENSIE_CHECK_EQUAL( type_250, MonteCarlo::N__T_EXCITED_STATE_9_REACTION );
  FRENSIE_CHECK_EQUAL( type_251, MonteCarlo::N__T_EXCITED_STATE_10_REACTION );
  FRENSIE_CHECK_EQUAL( type_252, MonteCarlo::N__T_EXCITED_STATE_11_REACTION );
  FRENSIE_CHECK_EQUAL( type_253, MonteCarlo::N__T_EXCITED_STATE_12_REACTION );
  FRENSIE_CHECK_EQUAL( type_254, MonteCarlo::N__T_EXCITED_STATE_13_REACTION );
  FRENSIE_CHECK_EQUAL( type_255, MonteCarlo::N__T_EXCITED_STATE_14_REACTION );
  FRENSIE_CHECK_EQUAL( type_256, MonteCarlo::N__T_EXCITED_STATE_15_REACTION );
  FRENSIE_CHECK_EQUAL( type_257, MonteCarlo::N__T_EXCITED_STATE_16_REACTION );
  FRENSIE_CHECK_EQUAL( type_258, MonteCarlo::N__T_EXCITED_STATE_17_REACTION );
  FRENSIE_CHECK_EQUAL( type_259, MonteCarlo::N__T_EXCITED_STATE_18_REACTION );
  FRENSIE_CHECK_EQUAL( type_260, MonteCarlo::N__T_EXCITED_STATE_19_REACTION );
  FRENSIE_CHECK_EQUAL( type_261, MonteCarlo::N__T_EXCITED_STATE_20_REACTION );
  FRENSIE_CHECK_EQUAL( type_262, MonteCarlo::N__T_EXCITED_STATE_21_REACTION );
  FRENSIE_CHECK_EQUAL( type_263, MonteCarlo::N__T_EXCITED_STATE_22_REACTION );
  FRENSIE_CHECK_EQUAL( type_264, MonteCarlo::N__T_EXCITED_STATE_23_REACTION );
  FRENSIE_CHECK_EQUAL( type_265, MonteCarlo::N__T_EXCITED_STATE_24_REACTION );
  FRENSIE_CHECK_EQUAL( type_266, MonteCarlo::N__T_EXCITED_STATE_25_REACTION );
  FRENSIE_CHECK_EQUAL( type_267, MonteCarlo::N__T_EXCITED_STATE_26_REACTION );
  FRENSIE_CHECK_EQUAL( type_268, MonteCarlo::N__T_EXCITED_STATE_27_REACTION );
  FRENSIE_CHECK_EQUAL( type_269, MonteCarlo::N__T_EXCITED_STATE_28_REACTION );
  FRENSIE_CHECK_EQUAL( type_270, MonteCarlo::N__T_EXCITED_STATE_29_REACTION );
  FRENSIE_CHECK_EQUAL( type_271, MonteCarlo::N__T_EXCITED_STATE_30_REACTION );
  FRENSIE_CHECK_EQUAL( type_272, MonteCarlo::N__T_EXCITED_STATE_31_REACTION );
  FRENSIE_CHECK_EQUAL( type_273, MonteCarlo::N__T_EXCITED_STATE_32_REACTION );
  FRENSIE_CHECK_EQUAL( type_274, MonteCarlo::N__T_EXCITED_STATE_33_REACTION );
  FRENSIE_CHECK_EQUAL( type_275, MonteCarlo::N__T_EXCITED_STATE_34_REACTION );
  FRENSIE_CHECK_EQUAL( type_276, MonteCarlo::N__T_EXCITED_STATE_35_REACTION );
  FRENSIE_CHECK_EQUAL( type_277, MonteCarlo::N__T_EXCITED_STATE_36_REACTION );
  FRENSIE_CHECK_EQUAL( type_278, MonteCarlo::N__T_EXCITED_STATE_37_REACTION );
  FRENSIE_CHECK_EQUAL( type_279, MonteCarlo::N__T_EXCITED_STATE_38_REACTION );
  FRENSIE_CHECK_EQUAL( type_280, MonteCarlo::N__T_EXCITED_STATE_39_REACTION );
  FRENSIE_CHECK_EQUAL( type_281, MonteCarlo::N__T_EXCITED_STATE_40_REACTION );
  FRENSIE_CHECK_EQUAL( type_282, MonteCarlo::N__T_EXCITED_STATE_41_REACTION );
  FRENSIE_CHECK_EQUAL( type_283, MonteCarlo::N__T_EXCITED_STATE_42_REACTION );
  FRENSIE_CHECK_EQUAL( type_284, MonteCarlo::N__T_EXCITED_STATE_43_REACTION );
  FRENSIE_CHECK_EQUAL( type_285, MonteCarlo::N__T_EXCITED_STATE_44_REACTION );
  FRENSIE_CHECK_EQUAL( type_286, MonteCarlo::N__T_EXCITED_STATE_45_REACTION );
  FRENSIE_CHECK_EQUAL( type_287, MonteCarlo::N__T_EXCITED_STATE_46_REACTION );
  FRENSIE_CHECK_EQUAL( type_288, MonteCarlo::N__T_EXCITED_STATE_47_REACTION );
  FRENSIE_CHECK_EQUAL( type_289, MonteCarlo::N__T_EXCITED_STATE_48_REACTION );
  FRENSIE_CHECK_EQUAL( type_290, MonteCarlo::N__T_CONTINUUM_REACTION );
  FRENSIE_CHECK_EQUAL( type_291, MonteCarlo::N__HE3_EXCITED_STATE_0_REACTION );
  FRENSIE_CHECK_EQUAL( type_292, MonteCarlo::N__HE3_EXCITED_STATE_1_REACTION );
  FRENSIE_CHECK_EQUAL( type_293, MonteCarlo::N__HE3_EXCITED_STATE_2_REACTION );
  FRENSIE_CHECK_EQUAL( type_294, MonteCarlo::N__HE3_EXCITED_STATE_3_REACTION );
  FRENSIE_CHECK_EQUAL( type_295, MonteCarlo::N__HE3_EXCITED_STATE_4_REACTION );
  FRENSIE_CHECK_EQUAL( type_296, MonteCarlo::N__HE3_EXCITED_STATE_5_REACTION );
  FRENSIE_CHECK_EQUAL( type_297, MonteCarlo::N__HE3_EXCITED_STATE_6_REACTION );
  FRENSIE_CHECK_EQUAL( type_298, MonteCarlo::N__HE3_EXCITED_STATE_7_REACTION );
  FRENSIE_CHECK_EQUAL( type_299, MonteCarlo::N__HE3_EXCITED_STATE_8_REACTION );
  FRENSIE_CHECK_EQUAL( type_300, MonteCarlo::N__HE3_EXCITED_STATE_9_REACTION );
  FRENSIE_CHECK_EQUAL( type_301, MonteCarlo::N__HE3_EXCITED_STATE_10_REACTION );
  FRENSIE_CHECK_EQUAL( type_302, MonteCarlo::N__HE3_EXCITED_STATE_11_REACTION );
  FRENSIE_CHECK_EQUAL( type_303, MonteCarlo::N__HE3_EXCITED_STATE_12_REACTION );
  FRENSIE_CHECK_EQUAL( type_304, MonteCarlo::N__HE3_EXCITED_STATE_13_REACTION );
  FRENSIE_CHECK_EQUAL( type_305, MonteCarlo::N__HE3_EXCITED_STATE_14_REACTION );
  FRENSIE_CHECK_EQUAL( type_306, MonteCarlo::N__HE3_EXCITED_STATE_15_REACTION );
  FRENSIE_CHECK_EQUAL( type_307, MonteCarlo::N__HE3_EXCITED_STATE_16_REACTION );
  FRENSIE_CHECK_EQUAL( type_308, MonteCarlo::N__HE3_EXCITED_STATE_17_REACTION );
  FRENSIE_CHECK_EQUAL( type_309, MonteCarlo::N__HE3_EXCITED_STATE_18_REACTION );
  FRENSIE_CHECK_EQUAL( type_310, MonteCarlo::N__HE3_EXCITED_STATE_19_REACTION );
  FRENSIE_CHECK_EQUAL( type_311, MonteCarlo::N__HE3_EXCITED_STATE_20_REACTION );
  FRENSIE_CHECK_EQUAL( type_312, MonteCarlo::N__HE3_EXCITED_STATE_21_REACTION );
  FRENSIE_CHECK_EQUAL( type_313, MonteCarlo::N__HE3_EXCITED_STATE_22_REACTION );
  FRENSIE_CHECK_EQUAL( type_314, MonteCarlo::N__HE3_EXCITED_STATE_23_REACTION );
  FRENSIE_CHECK_EQUAL( type_315, MonteCarlo::N__HE3_EXCITED_STATE_24_REACTION );
  FRENSIE_CHECK_EQUAL( type_316, MonteCarlo::N__HE3_EXCITED_STATE_25_REACTION );
  FRENSIE_CHECK_EQUAL( type_317, MonteCarlo::N__HE3_EXCITED_STATE_26_REACTION );
  FRENSIE_CHECK_EQUAL( type_318, MonteCarlo::N__HE3_EXCITED_STATE_27_REACTION );
  FRENSIE_CHECK_EQUAL( type_319, MonteCarlo::N__HE3_EXCITED_STATE_28_REACTION );
  FRENSIE_CHECK_EQUAL( type_320, MonteCarlo::N__HE3_EXCITED_STATE_29_REACTION );
  FRENSIE_CHECK_EQUAL( type_321, MonteCarlo::N__HE3_EXCITED_STATE_30_REACTION );
  FRENSIE_CHECK_EQUAL( type_322, MonteCarlo::N__HE3_EXCITED_STATE_31_REACTION );
  FRENSIE_CHECK_EQUAL( type_323, MonteCarlo::N__HE3_EXCITED_STATE_32_REACTION );
  FRENSIE_CHECK_EQUAL( type_324, MonteCarlo::N__HE3_EXCITED_STATE_33_REACTION );
  FRENSIE_CHECK_EQUAL( type_325, MonteCarlo::N__HE3_EXCITED_STATE_34_REACTION );
  FRENSIE_CHECK_EQUAL( type_326, MonteCarlo::N__HE3_EXCITED_STATE_35_REACTION );
  FRENSIE_CHECK_EQUAL( type_327, MonteCarlo::N__HE3_EXCITED_STATE_36_REACTION );
  FRENSIE_CHECK_EQUAL( type_328, MonteCarlo::N__HE3_EXCITED_STATE_37_REACTION );
  FRENSIE_CHECK_EQUAL( type_329, MonteCarlo::N__HE3_EXCITED_STATE_38_REACTION );
  FRENSIE_CHECK_EQUAL( type_330, MonteCarlo::N__HE3_EXCITED_STATE_39_REACTION );
  FRENSIE_CHECK_EQUAL( type_331, MonteCarlo::N__HE3_EXCITED_STATE_40_REACTION );
  FRENSIE_CHECK_EQUAL( type_332, MonteCarlo::N__HE3_EXCITED_STATE_41_REACTION );
  FRENSIE_CHECK_EQUAL( type_333, MonteCarlo::N__HE3_EXCITED_STATE_42_REACTION );
  FRENSIE_CHECK_EQUAL( type_334, MonteCarlo::N__HE3_EXCITED_STATE_43_REACTION );
  FRENSIE_CHECK_EQUAL( type_335, MonteCarlo::N__HE3_EXCITED_STATE_44_REACTION );
  FRENSIE_CHECK_EQUAL( type_336, MonteCarlo::N__HE3_EXCITED_STATE_45_REACTION );
  FRENSIE_CHECK_EQUAL( type_337, MonteCarlo::N__HE3_EXCITED_STATE_46_REACTION );
  FRENSIE_CHECK_EQUAL( type_338, MonteCarlo::N__HE3_EXCITED_STATE_47_REACTION );
  FRENSIE_CHECK_EQUAL( type_339, MonteCarlo::N__HE3_EXCITED_STATE_48_REACTION );
  FRENSIE_CHECK_EQUAL( type_340, MonteCarlo::N__HE3_CONTINUUM_REACTION );
  FRENSIE_CHECK_EQUAL( type_341, MonteCarlo::N__ALPHA_EXCITED_STATE_0_REACTION );
  FRENSIE_CHECK_EQUAL( type_342, MonteCarlo::N__ALPHA_EXCITED_STATE_1_REACTION );
  FRENSIE_CHECK_EQUAL( type_343, MonteCarlo::N__ALPHA_EXCITED_STATE_2_REACTION );
  FRENSIE_CHECK_EQUAL( type_344, MonteCarlo::N__ALPHA_EXCITED_STATE_3_REACTION );
  FRENSIE_CHECK_EQUAL( type_345, MonteCarlo::N__ALPHA_EXCITED_STATE_4_REACTION );
  FRENSIE_CHECK_EQUAL( type_346, MonteCarlo::N__ALPHA_EXCITED_STATE_5_REACTION );
  FRENSIE_CHECK_EQUAL( type_347, MonteCarlo::N__ALPHA_EXCITED_STATE_6_REACTION );
  FRENSIE_CHECK_EQUAL( type_348, MonteCarlo::N__ALPHA_EXCITED_STATE_7_REACTION );
  FRENSIE_CHECK_EQUAL( type_349, MonteCarlo::N__ALPHA_EXCITED_STATE_8_REACTION );
  FRENSIE_CHECK_EQUAL( type_350, MonteCarlo::N__ALPHA_EXCITED_STATE_9_REACTION );
  FRENSIE_CHECK_EQUAL( type_351, MonteCarlo::N__ALPHA_EXCITED_STATE_10_REACTION );
  FRENSIE_CHECK_EQUAL( type_352, MonteCarlo::N__ALPHA_EXCITED_STATE_11_REACTION );
  FRENSIE_CHECK_EQUAL( type_353, MonteCarlo::N__ALPHA_EXCITED_STATE_12_REACTION );
  FRENSIE_CHECK_EQUAL( type_354, MonteCarlo::N__ALPHA_EXCITED_STATE_13_REACTION );
  FRENSIE_CHECK_EQUAL( type_355, MonteCarlo::N__ALPHA_EXCITED_STATE_14_REACTION );
  FRENSIE_CHECK_EQUAL( type_356, MonteCarlo::N__ALPHA_EXCITED_STATE_15_REACTION );
  FRENSIE_CHECK_EQUAL( type_357, MonteCarlo::N__ALPHA_EXCITED_STATE_16_REACTION );
  FRENSIE_CHECK_EQUAL( type_358, MonteCarlo::N__ALPHA_EXCITED_STATE_17_REACTION );
  FRENSIE_CHECK_EQUAL( type_359, MonteCarlo::N__ALPHA_EXCITED_STATE_18_REACTION );
  FRENSIE_CHECK_EQUAL( type_360, MonteCarlo::N__ALPHA_EXCITED_STATE_19_REACTION );
  FRENSIE_CHECK_EQUAL( type_361, MonteCarlo::N__ALPHA_EXCITED_STATE_20_REACTION );
  FRENSIE_CHECK_EQUAL( type_362, MonteCarlo::N__ALPHA_EXCITED_STATE_21_REACTION );
  FRENSIE_CHECK_EQUAL( type_363, MonteCarlo::N__ALPHA_EXCITED_STATE_22_REACTION );
  FRENSIE_CHECK_EQUAL( type_364, MonteCarlo::N__ALPHA_EXCITED_STATE_23_REACTION );
  FRENSIE_CHECK_EQUAL( type_365, MonteCarlo::N__ALPHA_EXCITED_STATE_24_REACTION );
  FRENSIE_CHECK_EQUAL( type_366, MonteCarlo::N__ALPHA_EXCITED_STATE_25_REACTION );
  FRENSIE_CHECK_EQUAL( type_367, MonteCarlo::N__ALPHA_EXCITED_STATE_26_REACTION );
  FRENSIE_CHECK_EQUAL( type_368, MonteCarlo::N__ALPHA_EXCITED_STATE_27_REACTION );
  FRENSIE_CHECK_EQUAL( type_369, MonteCarlo::N__ALPHA_EXCITED_STATE_28_REACTION );
  FRENSIE_CHECK_EQUAL( type_370, MonteCarlo::N__ALPHA_EXCITED_STATE_29_REACTION );
  FRENSIE_CHECK_EQUAL( type_371, MonteCarlo::N__ALPHA_EXCITED_STATE_30_REACTION );
  FRENSIE_CHECK_EQUAL( type_372, MonteCarlo::N__ALPHA_EXCITED_STATE_31_REACTION );
  FRENSIE_CHECK_EQUAL( type_373, MonteCarlo::N__ALPHA_EXCITED_STATE_32_REACTION );
  FRENSIE_CHECK_EQUAL( type_374, MonteCarlo::N__ALPHA_EXCITED_STATE_33_REACTION );
  FRENSIE_CHECK_EQUAL( type_375, MonteCarlo::N__ALPHA_EXCITED_STATE_34_REACTION );
  FRENSIE_CHECK_EQUAL( type_376, MonteCarlo::N__ALPHA_EXCITED_STATE_35_REACTION );
  FRENSIE_CHECK_EQUAL( type_377, MonteCarlo::N__ALPHA_EXCITED_STATE_36_REACTION );
  FRENSIE_CHECK_EQUAL( type_378, MonteCarlo::N__ALPHA_EXCITED_STATE_37_REACTION );
  FRENSIE_CHECK_EQUAL( type_379, MonteCarlo::N__ALPHA_EXCITED_STATE_38_REACTION );
  FRENSIE_CHECK_EQUAL( type_380, MonteCarlo::N__ALPHA_EXCITED_STATE_39_REACTION );
  FRENSIE_CHECK_EQUAL( type_381, MonteCarlo::N__ALPHA_EXCITED_STATE_40_REACTION );
  FRENSIE_CHECK_EQUAL( type_382, MonteCarlo::N__ALPHA_EXCITED_STATE_41_REACTION );
  FRENSIE_CHECK_EQUAL( type_383, MonteCarlo::N__ALPHA_EXCITED_STATE_42_REACTION );
  FRENSIE_CHECK_EQUAL( type_384, MonteCarlo::N__ALPHA_EXCITED_STATE_43_REACTION );
  FRENSIE_CHECK_EQUAL( type_385, MonteCarlo::N__ALPHA_EXCITED_STATE_44_REACTION );
  FRENSIE_CHECK_EQUAL( type_386, MonteCarlo::N__ALPHA_EXCITED_STATE_45_REACTION );
  FRENSIE_CHECK_EQUAL( type_387, MonteCarlo::N__ALPHA_EXCITED_STATE_46_REACTION );
  FRENSIE_CHECK_EQUAL( type_388, MonteCarlo::N__ALPHA_EXCITED_STATE_47_REACTION );
  FRENSIE_CHECK_EQUAL( type_389, MonteCarlo::N__ALPHA_EXCITED_STATE_48_REACTION );
  FRENSIE_CHECK_EQUAL( type_390, MonteCarlo::N__ALPHA_CONTINUUM_REACTION );
  FRENSIE_CHECK_EQUAL( type_391, MonteCarlo::N__2N_EXCITED_STATE_0_REACTION ); 
  FRENSIE_CHECK_EQUAL( type_392, MonteCarlo::N__2N_EXCITED_STATE_1_REACTION );
  FRENSIE_CHECK_EQUAL( type_393, MonteCarlo::N__2N_EXCITED_STATE_2_REACTION );
  FRENSIE_CHECK_EQUAL( type_394, MonteCarlo::N__2N_EXCITED_STATE_3_REACTION );
  FRENSIE_CHECK_EQUAL( type_395, MonteCarlo::N__2N_EXCITED_STATE_4_REACTION );
  FRENSIE_CHECK_EQUAL( type_396, MonteCarlo::N__2N_EXCITED_STATE_5_REACTION );
  FRENSIE_CHECK_EQUAL( type_397, MonteCarlo::N__2N_EXCITED_STATE_6_REACTION );
  FRENSIE_CHECK_EQUAL( type_398, MonteCarlo::N__2N_EXCITED_STATE_7_REACTION );
  FRENSIE_CHECK_EQUAL( type_399, MonteCarlo::N__2N_EXCITED_STATE_8_REACTION );
  FRENSIE_CHECK_EQUAL( type_400, MonteCarlo::N__2N_EXCITED_STATE_9_REACTION );
  FRENSIE_CHECK_EQUAL( type_401, MonteCarlo::N__2N_EXCITED_STATE_10_REACTION );
  FRENSIE_CHECK_EQUAL( type_402, MonteCarlo::N__2N_EXCITED_STATE_11_REACTION );
  FRENSIE_CHECK_EQUAL( type_403, MonteCarlo::N__2N_EXCITED_STATE_12_REACTION );
  FRENSIE_CHECK_EQUAL( type_404, MonteCarlo::N__2N_EXCITED_STATE_13_REACTION );
  FRENSIE_CHECK_EQUAL( type_405, MonteCarlo::N__2N_EXCITED_STATE_14_REACTION );
  FRENSIE_CHECK_EQUAL( type_406, MonteCarlo::N__2N_EXCITED_STATE_15_REACTION );
  FRENSIE_CHECK_EQUAL( type_407, MonteCarlo::N__2N_CONTINUUM_REACTION );
}

//---------------------------------------------------------------------------//
// end tstNuclearReactionType.cpp
//---------------------------------------------------------------------------//
