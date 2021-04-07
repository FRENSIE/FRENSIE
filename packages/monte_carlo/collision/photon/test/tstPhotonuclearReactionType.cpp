//---------------------------------------------------------------------------//
//!
//! \file   tstPhotonuclearReactionType.cpp
//! \author Alex Robinson
//! \brief  Photonuclear reaction type helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearReactionType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a raw mt number can be converted to a photonuclear reaction
FRENSIE_UNIT_TEST( PhotonuclearReactionType,
                   convertMTNumberToPhotonuclearReactionType )
{
  MonteCarlo::PhotonuclearReactionType type =
    MonteCarlo::convertMTNumberToPhotonuclearReactionType( 1 );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__TOTAL_REACTION );

  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 2 );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__GAMMA_ELASTIC_REACTION );

  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 3 );

  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__GAMMA_NON_ELASTIC_REACTION );

  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 4 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_REACTION );

  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 5 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ANYTHING_REACTION );

  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 11 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_D_REACTION );

  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 16 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_REACTION );

  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 17 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__3N_REACTION );

  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 18 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__TOTAL_FISSION_REACTION );

  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 22 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_ALPHA_REACTION );

  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 24 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_ALPHA_REACTION );

  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 25 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__3N_ALPHA_REACTION );

  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 28 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_P_REACTION );

  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 29 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 30 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 32 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_D_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 33 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 34 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 35 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_D_2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 36 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_T_2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 37 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__4N_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 41 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_P_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 42 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__3N_P_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 44 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_2P_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 45 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_P_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 50 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 51 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_1_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 52 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_2_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 53 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 54 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_4_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 55 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_5_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 56 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_6_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 57 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_7_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 58 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_8_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 59 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_9_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 60 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_10_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 61 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_11_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 62 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_12_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 63 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_13_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 64 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_14_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 65 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_15_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 66 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_16_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 67 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_17_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 68 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_18_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 69 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_19_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 70 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_20_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 71 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_21_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 72 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_22_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 73 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_23_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 74 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_24_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 75 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_25_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 76 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_26_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 77 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_27_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 78 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_28_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 79 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_29_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 80 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_30_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 81 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_31_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 82 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_32_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 83 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_33_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 84 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_34_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 85 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_35_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 86 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_36_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 87 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_37_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 88 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_38_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 89 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_39_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 90 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_EXCITED_STATE_40_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 91 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_CONTINUUM_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 102 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__CAPTURE_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 103 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 104 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 105 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 106 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 107 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 108 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 109 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__3ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 111 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2P_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 112 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 113 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 114 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 115 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_D_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 116 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 117 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 152 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__5N_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 153 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__6N_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 154 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 155 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 156 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__4N_P_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 157 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__3N_D_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 158 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_D_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 159 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_P_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 160 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__7N_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 161 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__8N_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 162 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__5N_P_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 163 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__6N_P_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 164 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__7N_P_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 165 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__4N_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 166 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__5N_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 167 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__6N_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 168 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__7N_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 169 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__4N_D_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 170 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__5N_D_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 171 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__6N_D_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 172 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__3N_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 173 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__4N_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 174 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__5N_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 175 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__6N_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 176 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 177 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__3N_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 178 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__4N_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 179 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__3N_2P_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 180 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__3N_2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 181 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__3N_P_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 182 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 183 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_P_D_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 184 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_P_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 185 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_D_T_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 186 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_P_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 187 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_D_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 188 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_T_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 189 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_T_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 190 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_2P_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 191 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 192 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_HE3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 193 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 194 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__4N_2P_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 195 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__4N_2ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 196 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__4N_P_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 197 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__3P_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 198 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__N_3P_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 199 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__3N_2P_ALPHA_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 200 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__5N_2P_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 201 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__TOTAL_N_PRODUCTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 202 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__TOTAL_GAMMA_PRODUCTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 203 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__TOTAL_P_PRODUCTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 204 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__TOTAL_D_PRODUCTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 205 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__TOTAL_T_PRODUCTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 206 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__TOTAL_HE3_PRODUCTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 207 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__TOTAL_ALPHA_PRODUCTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 301 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__AVERAGE_HEATING );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 444 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__DAMAGE );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 600 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_0_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 601 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_1_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 602 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_2_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 603 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 604 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_4_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 605 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_5_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 606 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_6_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 607 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_7_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 608 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_8_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 609 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_9_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 610 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_10_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 611 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_11_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 612 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_12_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 613 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_13_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 614 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_14_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 615 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_15_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 616 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_16_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 617 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_17_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 618 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_18_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 619 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_19_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 620 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_20_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 621 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_21_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 622 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_22_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 623 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_23_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 624 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_24_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 625 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_25_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 626 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_26_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 627 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_27_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 628 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_28_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 629 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_29_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 630 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_30_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 631 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_31_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 632 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_32_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 633 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_33_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 634 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_34_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 635 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_35_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 636 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_36_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 637 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_37_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 638 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_38_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 639 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_39_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 640 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_40_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 641 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_41_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 642 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_42_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 643 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_43_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 644 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_44_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 645 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_45_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 646 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_46_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 647 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_47_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 648 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_EXCITED_STATE_48_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 649 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__P_CONTINUUM_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 650 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_0_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 651 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_1_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 652 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_2_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 653 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 654 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_4_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 655 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_5_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 656 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_6_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 657 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_7_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 658 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_8_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 659 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_9_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 660 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_10_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 661 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_11_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 662 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_12_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 663 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_13_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 664 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_14_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 665 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_15_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 666 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_16_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 667 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_17_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 668 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_18_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 669 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_19_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 670 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_20_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 671 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_21_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 672 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_22_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 673 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_23_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 674 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_24_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 675 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_25_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 676 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_26_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 677 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_27_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 678 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_28_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 679 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_29_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 680 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_30_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 681 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_31_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 682 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_32_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 683 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_33_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 684 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_34_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 685 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_35_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 686 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_36_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 687 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_37_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 688 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_38_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 689 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_39_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 690 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_40_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 691 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_41_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 692 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_42_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 693 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_43_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 694 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_44_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 695 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_45_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 696 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_46_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 697 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_47_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 698 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_EXCITED_STATE_48_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 699 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__D_CONTINUUM_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 700 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_0_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 701 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_1_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 702 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_2_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 703 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 704 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_4_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 705 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_5_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 706 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_6_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 707 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_7_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 708 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_8_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 709 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_9_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 710 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_10_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 711 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_11_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 712 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_12_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 713 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_13_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 714 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_14_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 715 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_15_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 716 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_16_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 717 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_17_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 718 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_18_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 719 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_19_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 720 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_20_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 721 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_21_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 722 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_22_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 723 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_23_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 724 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_24_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 725 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_25_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 726 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_26_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 727 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_27_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 728 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_28_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 729 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_29_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 730 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_30_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 731 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_31_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 732 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_32_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 733 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_33_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 734 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_34_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 735 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_35_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 736 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_36_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 737 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_37_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 738 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_38_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 739 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_39_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 740 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_40_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 741 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_41_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 742 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_42_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 743 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_43_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 744 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_44_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 745 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_45_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 746 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_46_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 747 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_47_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 748 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_EXCITED_STATE_48_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 749 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__T_CONTINUUM_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 750 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_0_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 751 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_1_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 752 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_2_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 753 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 754 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_4_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 755 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_5_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 756 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_6_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 757 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_7_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 758 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_8_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 759 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_9_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 760 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_10_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 761 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_11_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 762 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_12_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 763 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_13_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 764 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_14_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 765 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_15_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 766 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_16_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 767 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_17_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 768 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_18_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 769 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_19_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 770 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_20_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 771 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_21_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 772 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_22_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 773 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_23_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 774 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_24_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 775 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_25_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 776 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_26_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 777 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_27_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 778 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_28_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 779 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_29_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 780 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_30_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 781 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_31_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 782 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_32_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 783 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_33_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 784 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_34_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 785 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_35_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 786 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_36_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 787 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_37_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 788 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_38_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 789 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_39_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 790 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_40_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 791 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_41_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 792 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_42_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 793 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_43_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 794 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_44_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 795 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_45_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 796 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_46_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 797 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_47_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 798 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_EXCITED_STATE_48_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 799 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__HE3_CONTINUUM_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 800 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_0_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 801 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_1_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 802 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_2_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 803 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 804 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_4_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 805 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_5_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 806 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_6_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 807 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_7_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 808 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_8_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 809 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_9_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 810 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_10_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 811 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_11_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 812 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_12_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 813 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_13_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 814 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_14_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 815 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_15_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 816 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_16_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 817 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_17_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 818 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_18_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 819 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_19_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 820 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_20_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 821 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_21_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 822 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_22_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 823 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_23_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 824 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_24_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 825 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_25_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 826 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_26_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 827 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_27_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 828 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_28_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 829 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_29_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 830 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_30_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 831 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_31_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 832 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_32_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 833 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_33_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 834 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_34_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 835 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_35_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 836 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_36_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 837 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_37_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 838 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_38_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 839 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_39_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 840 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_40_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 841 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_41_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 842 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_42_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 843 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_43_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 844 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_44_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 845 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_45_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 846 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_46_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 847 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_47_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 848 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_48_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 849 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__ALPHA_CONTINUUM_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 875 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_EXCITED_STATE_0_REACTION ); 
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 876 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_EXCITED_STATE_1_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 877 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_EXCITED_STATE_2_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 878 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_EXCITED_STATE_3_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 879 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_EXCITED_STATE_4_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 880 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_EXCITED_STATE_5_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 881 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_EXCITED_STATE_6_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 882 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_EXCITED_STATE_7_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 883 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_EXCITED_STATE_8_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 884 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_EXCITED_STATE_9_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 885 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_EXCITED_STATE_10_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 886 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_EXCITED_STATE_11_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 887 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_EXCITED_STATE_12_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 888 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_EXCITED_STATE_13_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 889 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_EXCITED_STATE_14_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 890 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_EXCITED_STATE_15_REACTION );
  
  type = MonteCarlo::convertMTNumberToPhotonuclearReactionType( 891 );
  
  FRENSIE_CHECK_EQUAL( type, MonteCarlo::GAMMA__2N_CONTINUUM_REACTION );
}

//---------------------------------------------------------------------------//
// Check that a photonuclear reaction type can be converted to a string
FRENSIE_UNIT_TEST( PhotonuclearReactionType, toString )
{
  std::string type_string =
    Utility::toString( MonteCarlo::GAMMA__TOTAL_REACTION );
  
  FRENSIE_CHECK_EQUAL( type_string, "(gamma,total)" );

  type_string = Utility::toString( MonteCarlo::GAMMA__GAMMA_ELASTIC_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,elastic)" );

  type_string = Utility::toString( MonteCarlo::GAMMA__GAMMA_NON_ELASTIC_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,non-elastic)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ANYTHING_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,anything)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n-d)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__3N_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,3n)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__TOTAL_FISSION_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,fission)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__3N_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,3n-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-p)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n-2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-d)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-t)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-he3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_D_2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-d-2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_T_2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-t-2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__4N_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,4n)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n-p)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__3N_P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,3n-p)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_2P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-2p)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_P_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-p-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_0)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_1_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_1)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_2_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_2)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_4_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_4)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_5_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_5)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_6_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_6)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_7_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_7)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_8_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_8)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_9_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_9)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_10_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_10)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_11_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_11)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_12_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_12)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_13_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_13)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_14_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_14)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_15_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_15)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_16_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_16)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_17_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_17)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_18_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_18)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_19_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_19)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_20_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_20)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_21_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_21)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_22_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_22)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_23_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_23)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_24_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_24)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_25_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_25)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_26_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_26)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_27_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_27)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_28_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_28)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_29_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_29)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_30_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_30)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_31_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_31)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_32_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_32)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_33_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_33)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_34_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_34)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_35_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_35)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_36_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_36)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_37_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_37)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_38_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_38)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_39_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_39)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_EXCITED_STATE_40_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_40)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_CONTINUUM_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_continuum)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__CAPTURE_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,capture)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__3ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,3alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2p)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t-2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d-2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p-d)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p-t)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__5N_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,5n)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__6N_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,6n)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n-t)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__4N_P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,4n-p)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__3N_D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,3n-d)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_D_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-d-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_P_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n-p-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__7N_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,7n)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__8N_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,8n)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__5N_P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,5n-p)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__6N_P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,6n-p)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__7N_P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,7n-p)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__4N_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,4n-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__5N_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,5n-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__6N_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,6n-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__7N_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,7n-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__4N_D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,4n-d)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__5N_D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,5n-d)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__6N_D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,6n-d)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__3N_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,3n-t)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__4N_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,4n-t)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__5N_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,5n-t)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__6N_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,6n-t)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n-he3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__3N_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,3n-he3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__4N_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,4n-he3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__3N_2P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,3n-2p)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__3N_2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,3n-2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__3N_P_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,3n-p-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d-t)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_P_D_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-p-d)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_P_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-p-t)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_D_T_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-d-t)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_P_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-p-he3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_D_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-d-he3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_T_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-t-he3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_T_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-t-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_2P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n-2p)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p-he3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_HE3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d-he3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__4N_2P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,4n-2p)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__4N_2ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,4n-2alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__4N_P_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,4n-p-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__3P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,3p)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__N_3P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n-3p)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__3N_2P_ALPHA_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,3n-2p-alpha)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__5N_2P_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,5n-2p)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__TOTAL_N_PRODUCTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,n_production)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__TOTAL_GAMMA_PRODUCTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,gamma_production)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__TOTAL_P_PRODUCTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_production)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__TOTAL_D_PRODUCTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_production)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__TOTAL_T_PRODUCTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_production)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__TOTAL_HE3_PRODUCTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_production)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__TOTAL_ALPHA_PRODUCTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_production)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__AVERAGE_HEATING );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,heating)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__DAMAGE );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,damage)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_0_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_0)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_1_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_1)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_2_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_2)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_4_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_4)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_5_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_5)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_6_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_6)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_7_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_7)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_8_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_8)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_9_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_9)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_10_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_10)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_11_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_11)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_12_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_12)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_13_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_13)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_14_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_14)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_15_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_15)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_16_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_16)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_17_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_17)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_18_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_18)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_19_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_19)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_20_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_20)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_21_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_21)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_22_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_22)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_23_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_23)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_24_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_24)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_25_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_25)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_26_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_26)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_27_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_27)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_28_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_28)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_29_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_29)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_30_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_30)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_31_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_31)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_32_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_32)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_33_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_33)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_34_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_34)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_35_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_35)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_36_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_36)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_37_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_37)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_38_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_38)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_39_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_39)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_40_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_40)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_41_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_41)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_42_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_42)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_43_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_43)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_44_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_44)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_45_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_45)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_46_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_46)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_47_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_47)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__P_EXCITED_STATE_48_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_48)" );

  type_string = Utility::toString( MonteCarlo::GAMMA__P_CONTINUUM_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,p_continuum)" );

  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_0_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_0)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_1_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_1)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_2_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_2)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_4_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_4)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_5_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_5)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_6_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_6)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_7_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_7)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_8_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_8)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_9_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_9)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_10_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_10)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_11_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_11)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_12_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_12)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_13_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_13)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_14_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_14)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_15_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_15)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_16_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_16)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_17_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_17)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_18_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_18)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_19_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_19)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_20_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_20)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_21_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_21)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_22_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_22)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_23_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_23)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_24_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_24)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_25_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_25)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_26_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_26)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_27_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_27)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_28_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_28)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_29_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_29)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_30_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_30)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_31_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_31)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_32_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_32)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_33_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_33)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_34_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_34)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_35_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_35)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_36_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_36)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_37_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_37)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_38_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_38)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_39_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_39)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_40_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_40)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_41_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_41)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_42_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_42)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_43_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_43)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_44_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_44)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_45_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_45)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_46_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_46)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_47_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_47)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__D_EXCITED_STATE_48_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_48)" );

  type_string = Utility::toString( MonteCarlo::GAMMA__D_CONTINUUM_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,d_continuum)" );

  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_0_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_0)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_1_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_1)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_2_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_2)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_4_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_4)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_5_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_5)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_6_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_6)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_7_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_7)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_8_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_8)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_9_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_9)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_10_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_10)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_11_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_11)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_12_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_12)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_13_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_13)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_14_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_14)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_15_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_15)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_16_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_16)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_17_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_17)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_18_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_18)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_19_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_19)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_20_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_20)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_21_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_21)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_22_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_22)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_23_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_23)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_24_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_24)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_25_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_25)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_26_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_26)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_27_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_27)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_28_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_28)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_29_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_29)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_30_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_30)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_31_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_31)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_32_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_32)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_33_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_33)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_34_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_34)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_35_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_35)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_36_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_36)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_37_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_37)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_38_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_38)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_39_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_39)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_40_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_40)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_41_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_41)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_42_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_42)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_43_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_43)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_44_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_44)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_45_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_45)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_46_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_46)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_47_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_47)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__T_EXCITED_STATE_48_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_48)" );

  type_string = Utility::toString( MonteCarlo::GAMMA__T_CONTINUUM_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,t_continuum)" );

  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_0_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_0)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_1_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_1)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_2_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_2)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_4_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_4)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_5_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_5)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_6_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_6)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_7_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_7)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_8_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_8)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_9_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_9)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_10_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_10)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_11_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_11)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_12_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_12)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_13_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_13)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_14_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_14)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_15_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_15)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_16_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_16)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_17_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_17)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_18_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_18)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_19_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_19)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_20_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_20)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_21_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_21)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_22_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_22)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_23_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_23)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_24_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_24)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_25_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_25)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_26_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_26)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_27_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_27)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_28_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_28)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_29_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_29)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_30_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_30)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_31_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_31)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_32_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_32)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_33_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_33)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_34_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_34)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_35_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_35)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_36_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_36)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_37_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_37)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_38_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_38)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_39_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_39)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_40_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_40)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_41_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_41)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_42_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_42)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_43_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_43)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_44_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_44)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_45_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_45)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_46_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_46)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_47_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_47)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_EXCITED_STATE_48_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_48)" );

  type_string = Utility::toString( MonteCarlo::GAMMA__HE3_CONTINUUM_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,he3_continuum)" );

  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_0_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_0)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_1_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_1)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_2_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_2)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_4_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_4)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_5_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_5)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_6_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_6)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_7_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_7)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_8_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_8)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_9_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_9)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_10_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_10)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_11_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_11)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_12_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_12)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_13_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_13)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_14_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_14)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_15_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_15)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_16_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_16)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_17_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_17)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_18_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_18)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_19_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_19)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_20_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_20)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_21_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_21)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_22_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_22)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_23_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_23)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_24_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_24)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_25_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_25)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_26_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_26)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_27_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_27)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_28_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_28)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_29_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_29)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_30_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_30)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_31_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_31)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_32_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_32)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_33_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_33)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_34_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_34)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_35_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_35)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_36_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_36)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_37_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_37)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_38_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_38)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_39_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_39)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_40_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_40)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_41_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_41)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_42_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_42)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_43_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_43)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_44_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_44)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_45_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_45)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_46_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_46)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_47_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_47)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_48_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_48)" );

  type_string = Utility::toString( MonteCarlo::GAMMA__ALPHA_CONTINUUM_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,alpha_continuum)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_EXCITED_STATE_0_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_0)" ); 
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_EXCITED_STATE_1_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_1)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_EXCITED_STATE_2_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_2)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_EXCITED_STATE_3_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_3)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_EXCITED_STATE_4_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_4)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_EXCITED_STATE_5_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_5)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_EXCITED_STATE_6_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_6)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_EXCITED_STATE_7_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_7)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_EXCITED_STATE_8_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_8)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_EXCITED_STATE_9_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_9)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_EXCITED_STATE_10_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_10)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_EXCITED_STATE_11_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_11)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_EXCITED_STATE_12_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_12)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_EXCITED_STATE_13_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_13)" );

  type_string = Utility::toString( MonteCarlo::GAMMA__2N_EXCITED_STATE_14_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_14)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_EXCITED_STATE_15_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_15)" );
  
  type_string = Utility::toString( MonteCarlo::GAMMA__2N_CONTINUUM_REACTION );

  FRENSIE_CHECK_EQUAL( type_string, "(gamma,2n_continuum)" );
}

//---------------------------------------------------------------------------//
// Check that a photonuclear reaction type can be placed in a stream
FRENSIE_UNIT_TEST( PhotonuclearReactionType, ostream_operator )
{
  std::ostringstream oss;
  oss << MonteCarlo::GAMMA__TOTAL_REACTION;
  
  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,total)" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::GAMMA__GAMMA_ELASTIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,elastic)" );
  
  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::GAMMA__GAMMA_NON_ELASTIC_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,non-elastic)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ANYTHING_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,anything)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n-d)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__3N_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,3n)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__TOTAL_FISSION_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,fission)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__3N_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,3n-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-p)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-2alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n-2alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-d)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-t)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-he3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_D_2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-d-2alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_T_2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-t-2alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__4N_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,4n)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n-p)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__3N_P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,3n-p)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_2P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-2p)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_P_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-p-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_0)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_1_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_1)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_2_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_2)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_4_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_4)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_5_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_5)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_6_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_6)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_7_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_7)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_8_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_8)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_9_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_9)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_10_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_10)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_11_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_11)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_12_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_12)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_13_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_13)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_14_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_14)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_15_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_15)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_16_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_16)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_17_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_17)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_18_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_18)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_19_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_19)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_20_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_20)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_21_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_21)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_22_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_22)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_23_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_23)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_24_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_24)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_25_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_25)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_26_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_26)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_27_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_27)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_28_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_28)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_29_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_29)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_30_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_30)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_31_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_31)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_32_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_32)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_33_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_33)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_34_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_34)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_35_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_35)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_36_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_36)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_37_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_37)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_38_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_38)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_39_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_39)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_EXCITED_STATE_40_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_40)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_CONTINUUM_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_continuum)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__CAPTURE_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,capture)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__3ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,3alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2p)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t-2alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d-2alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p-d)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p-t)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__5N_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,5n)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__6N_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,6n)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n-t)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__4N_P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,4n-p)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__3N_D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,3n-d)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_D_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-d-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_P_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n-p-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__7N_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,7n)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__8N_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,8n)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__5N_P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,5n-p)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__6N_P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,6n-p)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__7N_P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,7n-p)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__4N_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,4n-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__5N_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,5n-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__6N_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,6n-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__7N_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,7n-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__4N_D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,4n-d)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__5N_D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,5n-d)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__6N_D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,6n-d)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__3N_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,3n-t)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__4N_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,4n-t)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__5N_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,5n-t)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__6N_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,6n-t)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n-he3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__3N_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,3n-he3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__4N_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,4n-he3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__3N_2P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,3n-2p)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__3N_2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,3n-2alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__3N_P_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,3n-p-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d-t)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_P_D_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-p-d)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_P_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-p-t)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_D_T_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-d-t)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_P_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-p-he3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_D_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-d-he3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_T_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-t-he3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_T_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-t-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_2P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n-2p)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p-he3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_HE3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d-he3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__4N_2P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,4n-2p)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__4N_2ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,4n-2alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__4N_P_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,4n-p-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__3P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,3p)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__N_3P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n-3p)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__3N_2P_ALPHA_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,3n-2p-alpha)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__5N_2P_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,5n-2p)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__TOTAL_N_PRODUCTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,n_production)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__TOTAL_GAMMA_PRODUCTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,gamma_production)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__TOTAL_P_PRODUCTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_production)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__TOTAL_D_PRODUCTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_production)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__TOTAL_T_PRODUCTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_production)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__TOTAL_HE3_PRODUCTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_production)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__TOTAL_ALPHA_PRODUCTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_production)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__AVERAGE_HEATING;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,heating)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__DAMAGE;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,damage)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_0_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_0)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_1_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_1)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_2_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_2)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_4_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_4)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_5_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_5)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_6_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_6)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_7_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_7)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_8_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_8)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_9_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_9)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_10_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_10)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_11_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_11)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_12_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_12)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_13_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_13)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_14_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_14)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_15_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_15)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_16_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_16)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_17_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_17)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_18_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_18)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_19_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_19)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_20_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_20)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_21_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_21)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_22_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_22)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_23_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_23)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_24_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_24)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_25_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_25)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_26_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_26)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_27_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_27)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_28_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_28)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_29_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_29)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_30_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_30)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_31_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_31)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_32_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_32)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_33_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_33)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_34_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_34)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_35_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_35)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_36_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_36)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_37_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_37)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_38_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_38)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_39_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_39)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_40_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_40)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_41_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_41)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_42_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_42)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_43_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_43)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_44_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_44)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_45_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_45)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_46_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_46)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_47_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_47)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__P_EXCITED_STATE_48_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_48)" );
  
  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::GAMMA__P_CONTINUUM_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,p_continuum)" );
  
  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_0_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_0)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_1_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_1)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_2_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_2)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_4_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_4)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_5_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_5)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_6_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_6)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_7_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_7)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_8_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_8)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_9_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_9)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_10_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_10)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_11_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_11)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_12_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_12)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_13_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_13)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_14_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_14)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_15_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_15)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_16_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_16)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_17_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_17)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_18_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_18)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_19_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_19)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_20_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_20)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_21_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_21)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_22_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_22)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_23_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_23)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_24_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_24)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_25_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_25)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_26_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_26)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_27_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_27)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_28_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_28)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_29_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_29)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_30_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_30)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_31_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_31)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_32_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_32)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_33_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_33)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_34_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_34)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_35_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_35)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_36_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_36)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_37_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_37)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_38_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_38)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_39_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_39)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_40_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_40)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_41_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_41)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_42_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_42)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_43_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_43)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_44_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_44)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_45_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_45)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_46_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_46)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_47_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_47)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__D_EXCITED_STATE_48_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_48)" );
  
  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::GAMMA__D_CONTINUUM_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,d_continuum)" );
  
  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_0_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_0)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_1_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_1)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_2_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_2)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_4_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_4)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_5_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_5)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_6_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_6)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_7_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_7)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_8_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_8)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_9_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_9)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_10_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_10)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_11_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_11)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_12_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_12)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_13_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_13)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_14_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_14)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_15_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_15)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_16_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_16)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_17_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_17)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_18_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_18)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_19_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_19)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_20_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_20)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_21_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_21)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_22_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_22)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_23_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_23)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_24_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_24)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_25_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_25)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_26_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_26)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_27_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_27)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_28_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_28)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_29_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_29)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_30_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_30)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_31_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_31)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_32_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_32)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_33_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_33)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_34_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_34)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_35_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_35)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_36_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_36)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_37_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_37)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_38_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_38)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_39_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_39)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_40_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_40)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_41_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_41)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_42_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_42)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_43_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_43)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_44_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_44)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_45_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_45)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_46_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_46)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_47_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_47)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__T_EXCITED_STATE_48_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_48)" );
  
  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::GAMMA__T_CONTINUUM_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,t_continuum)" );
  
  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_0_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_0)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_1_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_1)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_2_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_2)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_4_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_4)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_5_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_5)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_6_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_6)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_7_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_7)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_8_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_8)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_9_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_9)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_10_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_10)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_11_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_11)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_12_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_12)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_13_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_13)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_14_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_14)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_15_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_15)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_16_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_16)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_17_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_17)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_18_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_18)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_19_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_19)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_20_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_20)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_21_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_21)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_22_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_22)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_23_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_23)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_24_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_24)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_25_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_25)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_26_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_26)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_27_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_27)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_28_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_28)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_29_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_29)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_30_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_30)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_31_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_31)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_32_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_32)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_33_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_33)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_34_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_34)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_35_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_35)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_36_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_36)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_37_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_37)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_38_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_38)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_39_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_39)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_40_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_40)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_41_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_41)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_42_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_42)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_43_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_43)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_44_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_44)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_45_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_45)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_46_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_46)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_47_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_47)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__HE3_EXCITED_STATE_48_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_48)" );
  
  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::GAMMA__HE3_CONTINUUM_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,he3_continuum)" );
  
  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_0_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_0)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_1_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_1)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_2_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_2)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_4_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_4)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_5_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_5)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_6_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_6)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_7_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_7)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_8_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_8)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_9_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_9)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_10_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_10)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_11_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_11)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_12_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_12)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_13_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_13)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_14_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_14)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_15_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_15)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_16_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_16)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_17_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_17)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_18_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_18)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_19_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_19)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_20_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_20)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_21_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_21)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_22_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_22)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_23_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_23)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_24_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_24)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_25_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_25)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_26_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_26)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_27_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_27)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_28_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_28)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_29_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_29)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_30_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_30)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_31_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_31)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_32_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_32)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_33_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_33)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_34_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_34)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_35_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_35)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_36_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_36)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_37_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_37)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_38_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_38)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_39_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_39)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_40_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_40)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_41_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_41)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_42_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_42)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_43_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_43)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_44_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_44)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_45_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_45)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_46_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_46)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_47_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_47)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_48_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_48)" );
  
  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::GAMMA__ALPHA_CONTINUUM_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,alpha_continuum)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_EXCITED_STATE_0_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_0)" );
  
  oss.str( "" );
  oss.clear(); 
  
  oss << MonteCarlo::GAMMA__2N_EXCITED_STATE_1_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_1)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_EXCITED_STATE_2_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_2)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_EXCITED_STATE_3_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_3)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_EXCITED_STATE_4_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_4)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_EXCITED_STATE_5_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_5)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_EXCITED_STATE_6_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_6)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_EXCITED_STATE_7_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_7)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_EXCITED_STATE_8_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_8)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_EXCITED_STATE_9_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_9)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_EXCITED_STATE_10_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_10)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_EXCITED_STATE_11_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_11)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_EXCITED_STATE_12_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_12)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_EXCITED_STATE_13_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_13)" );
  
  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::GAMMA__2N_EXCITED_STATE_14_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_14)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_EXCITED_STATE_15_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_15)" );
  
  oss.str( "" );
  oss.clear();
  
  oss << MonteCarlo::GAMMA__2N_CONTINUUM_REACTION;

  FRENSIE_CHECK_EQUAL( oss.str(), "(gamma,2n_continuum)" );
}

//---------------------------------------------------------------------------//
// Check that a photonuclear reaction type can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( PhotonuclearReactionType,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_photonuclear_reaction_type" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::PhotonuclearReactionType type_1 = MonteCarlo::GAMMA__TOTAL_REACTION;
    MonteCarlo::PhotonuclearReactionType type_2 = MonteCarlo::GAMMA__GAMMA_ELASTIC_REACTION;
    MonteCarlo::PhotonuclearReactionType type_3 = MonteCarlo::GAMMA__GAMMA_NON_ELASTIC_REACTION;
    MonteCarlo::PhotonuclearReactionType type_4 = MonteCarlo::GAMMA__N_REACTION;
    MonteCarlo::PhotonuclearReactionType type_5 = MonteCarlo::GAMMA__ANYTHING_REACTION;
    MonteCarlo::PhotonuclearReactionType type_6 = MonteCarlo::GAMMA__2N_D_REACTION;
    MonteCarlo::PhotonuclearReactionType type_7 = MonteCarlo::GAMMA__2N_REACTION;
    MonteCarlo::PhotonuclearReactionType type_8 = MonteCarlo::GAMMA__3N_REACTION;
    MonteCarlo::PhotonuclearReactionType type_9 = MonteCarlo::GAMMA__TOTAL_FISSION_REACTION;
    MonteCarlo::PhotonuclearReactionType type_10 = MonteCarlo::GAMMA__N_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_11 = MonteCarlo::GAMMA__2N_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_12 = MonteCarlo::GAMMA__3N_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_13 = MonteCarlo::GAMMA__N_P_REACTION;
    MonteCarlo::PhotonuclearReactionType type_14 = MonteCarlo::GAMMA__N_2ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_15 = MonteCarlo::GAMMA__2N_2ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_16 = MonteCarlo::GAMMA__N_D_REACTION;
    MonteCarlo::PhotonuclearReactionType type_17 = MonteCarlo::GAMMA__N_T_REACTION;
    MonteCarlo::PhotonuclearReactionType type_18 = MonteCarlo::GAMMA__N_HE3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_19 = MonteCarlo::GAMMA__N_D_2ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_20 = MonteCarlo::GAMMA__N_T_2ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_21 = MonteCarlo::GAMMA__4N_REACTION;
    MonteCarlo::PhotonuclearReactionType type_22 = MonteCarlo::GAMMA__2N_P_REACTION;
    MonteCarlo::PhotonuclearReactionType type_23 = MonteCarlo::GAMMA__3N_P_REACTION;
    MonteCarlo::PhotonuclearReactionType type_24 = MonteCarlo::GAMMA__N_2P_REACTION;
    MonteCarlo::PhotonuclearReactionType type_25 = MonteCarlo::GAMMA__N_P_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_26 = MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION;
    MonteCarlo::PhotonuclearReactionType type_27 = MonteCarlo::GAMMA__N_EXCITED_STATE_1_REACTION;
    MonteCarlo::PhotonuclearReactionType type_28 = MonteCarlo::GAMMA__N_EXCITED_STATE_2_REACTION;
    MonteCarlo::PhotonuclearReactionType type_29 = MonteCarlo::GAMMA__N_EXCITED_STATE_3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_30 = MonteCarlo::GAMMA__N_EXCITED_STATE_4_REACTION;
    MonteCarlo::PhotonuclearReactionType type_31 = MonteCarlo::GAMMA__N_EXCITED_STATE_5_REACTION;
    MonteCarlo::PhotonuclearReactionType type_32 = MonteCarlo::GAMMA__N_EXCITED_STATE_6_REACTION;
    MonteCarlo::PhotonuclearReactionType type_33 = MonteCarlo::GAMMA__N_EXCITED_STATE_7_REACTION;
    MonteCarlo::PhotonuclearReactionType type_34 = MonteCarlo::GAMMA__N_EXCITED_STATE_8_REACTION;
    MonteCarlo::PhotonuclearReactionType type_35 = MonteCarlo::GAMMA__N_EXCITED_STATE_9_REACTION;
    MonteCarlo::PhotonuclearReactionType type_36 = MonteCarlo::GAMMA__N_EXCITED_STATE_10_REACTION;
    MonteCarlo::PhotonuclearReactionType type_37 = MonteCarlo::GAMMA__N_EXCITED_STATE_11_REACTION;
    MonteCarlo::PhotonuclearReactionType type_38 = MonteCarlo::GAMMA__N_EXCITED_STATE_12_REACTION;
    MonteCarlo::PhotonuclearReactionType type_39 = MonteCarlo::GAMMA__N_EXCITED_STATE_13_REACTION;
    MonteCarlo::PhotonuclearReactionType type_40 = MonteCarlo::GAMMA__N_EXCITED_STATE_14_REACTION;
    MonteCarlo::PhotonuclearReactionType type_41 = MonteCarlo::GAMMA__N_EXCITED_STATE_15_REACTION;
    MonteCarlo::PhotonuclearReactionType type_42 = MonteCarlo::GAMMA__N_EXCITED_STATE_16_REACTION;
    MonteCarlo::PhotonuclearReactionType type_43 = MonteCarlo::GAMMA__N_EXCITED_STATE_17_REACTION;
    MonteCarlo::PhotonuclearReactionType type_44 = MonteCarlo::GAMMA__N_EXCITED_STATE_18_REACTION;
    MonteCarlo::PhotonuclearReactionType type_45 = MonteCarlo::GAMMA__N_EXCITED_STATE_19_REACTION;
    MonteCarlo::PhotonuclearReactionType type_46 = MonteCarlo::GAMMA__N_EXCITED_STATE_20_REACTION;
    MonteCarlo::PhotonuclearReactionType type_47 = MonteCarlo::GAMMA__N_EXCITED_STATE_21_REACTION;
    MonteCarlo::PhotonuclearReactionType type_48 = MonteCarlo::GAMMA__N_EXCITED_STATE_22_REACTION;
    MonteCarlo::PhotonuclearReactionType type_49 = MonteCarlo::GAMMA__N_EXCITED_STATE_23_REACTION;
    MonteCarlo::PhotonuclearReactionType type_50 = MonteCarlo::GAMMA__N_EXCITED_STATE_24_REACTION;
    MonteCarlo::PhotonuclearReactionType type_51 = MonteCarlo::GAMMA__N_EXCITED_STATE_25_REACTION;
    MonteCarlo::PhotonuclearReactionType type_52 = MonteCarlo::GAMMA__N_EXCITED_STATE_26_REACTION;
    MonteCarlo::PhotonuclearReactionType type_53 = MonteCarlo::GAMMA__N_EXCITED_STATE_27_REACTION;
    MonteCarlo::PhotonuclearReactionType type_54 = MonteCarlo::GAMMA__N_EXCITED_STATE_28_REACTION;
    MonteCarlo::PhotonuclearReactionType type_55 = MonteCarlo::GAMMA__N_EXCITED_STATE_29_REACTION;
    MonteCarlo::PhotonuclearReactionType type_56 = MonteCarlo::GAMMA__N_EXCITED_STATE_30_REACTION;
    MonteCarlo::PhotonuclearReactionType type_57 = MonteCarlo::GAMMA__N_EXCITED_STATE_31_REACTION;
    MonteCarlo::PhotonuclearReactionType type_58 = MonteCarlo::GAMMA__N_EXCITED_STATE_32_REACTION;
    MonteCarlo::PhotonuclearReactionType type_59 = MonteCarlo::GAMMA__N_EXCITED_STATE_33_REACTION;
    MonteCarlo::PhotonuclearReactionType type_60 = MonteCarlo::GAMMA__N_EXCITED_STATE_34_REACTION;
    MonteCarlo::PhotonuclearReactionType type_61 = MonteCarlo::GAMMA__N_EXCITED_STATE_35_REACTION;
    MonteCarlo::PhotonuclearReactionType type_62 = MonteCarlo::GAMMA__N_EXCITED_STATE_36_REACTION;
    MonteCarlo::PhotonuclearReactionType type_63 = MonteCarlo::GAMMA__N_EXCITED_STATE_37_REACTION;
    MonteCarlo::PhotonuclearReactionType type_64 = MonteCarlo::GAMMA__N_EXCITED_STATE_38_REACTION;
    MonteCarlo::PhotonuclearReactionType type_65 = MonteCarlo::GAMMA__N_EXCITED_STATE_39_REACTION;
    MonteCarlo::PhotonuclearReactionType type_66 = MonteCarlo::GAMMA__N_EXCITED_STATE_40_REACTION;
    MonteCarlo::PhotonuclearReactionType type_67 = MonteCarlo::GAMMA__N_CONTINUUM_REACTION;
    MonteCarlo::PhotonuclearReactionType type_68 = MonteCarlo::GAMMA__CAPTURE_REACTION;
    MonteCarlo::PhotonuclearReactionType type_69 = MonteCarlo::GAMMA__P_REACTION;
    MonteCarlo::PhotonuclearReactionType type_70 = MonteCarlo::GAMMA__D_REACTION;
    MonteCarlo::PhotonuclearReactionType type_71 = MonteCarlo::GAMMA__T_REACTION;
    MonteCarlo::PhotonuclearReactionType type_72 = MonteCarlo::GAMMA__HE3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_73 = MonteCarlo::GAMMA__ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_74 = MonteCarlo::GAMMA__2ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_75 = MonteCarlo::GAMMA__3ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_76 = MonteCarlo::GAMMA__2P_REACTION;
    MonteCarlo::PhotonuclearReactionType type_77 = MonteCarlo::GAMMA__P_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_78 = MonteCarlo::GAMMA__T_2ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_79 = MonteCarlo::GAMMA__D_2ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_80 = MonteCarlo::GAMMA__P_D_REACTION;
    MonteCarlo::PhotonuclearReactionType type_81 = MonteCarlo::GAMMA__P_T_REACTION;
    MonteCarlo::PhotonuclearReactionType type_82 = MonteCarlo::GAMMA__D_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_83 = MonteCarlo::GAMMA__5N_REACTION;
    MonteCarlo::PhotonuclearReactionType type_84 = MonteCarlo::GAMMA__6N_REACTION;
    MonteCarlo::PhotonuclearReactionType type_85 = MonteCarlo::GAMMA__2N_T_REACTION;
    MonteCarlo::PhotonuclearReactionType type_86 = MonteCarlo::GAMMA__T_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_87 = MonteCarlo::GAMMA__4N_P_REACTION;
    MonteCarlo::PhotonuclearReactionType type_88 = MonteCarlo::GAMMA__3N_D_REACTION;
    MonteCarlo::PhotonuclearReactionType type_89 = MonteCarlo::GAMMA__N_D_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_90 = MonteCarlo::GAMMA__2N_P_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_91 = MonteCarlo::GAMMA__7N_REACTION;
    MonteCarlo::PhotonuclearReactionType type_92 = MonteCarlo::GAMMA__8N_REACTION;
    MonteCarlo::PhotonuclearReactionType type_93 = MonteCarlo::GAMMA__5N_P_REACTION;
    MonteCarlo::PhotonuclearReactionType type_94 = MonteCarlo::GAMMA__6N_P_REACTION;
    MonteCarlo::PhotonuclearReactionType type_95 = MonteCarlo::GAMMA__7N_P_REACTION;
    MonteCarlo::PhotonuclearReactionType type_96 = MonteCarlo::GAMMA__4N_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_97 = MonteCarlo::GAMMA__5N_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_98 = MonteCarlo::GAMMA__6N_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_99 = MonteCarlo::GAMMA__7N_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_100 = MonteCarlo::GAMMA__4N_D_REACTION;
    MonteCarlo::PhotonuclearReactionType type_101 = MonteCarlo::GAMMA__5N_D_REACTION;
    MonteCarlo::PhotonuclearReactionType type_102 = MonteCarlo::GAMMA__6N_D_REACTION;
    MonteCarlo::PhotonuclearReactionType type_103 = MonteCarlo::GAMMA__3N_T_REACTION;
    MonteCarlo::PhotonuclearReactionType type_104 = MonteCarlo::GAMMA__4N_T_REACTION;
    MonteCarlo::PhotonuclearReactionType type_105 = MonteCarlo::GAMMA__5N_T_REACTION;
    MonteCarlo::PhotonuclearReactionType type_106 = MonteCarlo::GAMMA__6N_T_REACTION;
    MonteCarlo::PhotonuclearReactionType type_107 = MonteCarlo::GAMMA__2N_HE3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_108 = MonteCarlo::GAMMA__3N_HE3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_109 = MonteCarlo::GAMMA__4N_HE3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_110 = MonteCarlo::GAMMA__3N_2P_REACTION;
    MonteCarlo::PhotonuclearReactionType type_111 = MonteCarlo::GAMMA__3N_2ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_112 = MonteCarlo::GAMMA__3N_P_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_113 = MonteCarlo::GAMMA__D_T_REACTION;
    MonteCarlo::PhotonuclearReactionType type_114 = MonteCarlo::GAMMA__N_P_D_REACTION;
    MonteCarlo::PhotonuclearReactionType type_115 = MonteCarlo::GAMMA__N_P_T_REACTION;
    MonteCarlo::PhotonuclearReactionType type_116 = MonteCarlo::GAMMA__N_D_T_REACTION;
    MonteCarlo::PhotonuclearReactionType type_117 = MonteCarlo::GAMMA__N_P_HE3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_118 = MonteCarlo::GAMMA__N_D_HE3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_119 = MonteCarlo::GAMMA__N_T_HE3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_120 = MonteCarlo::GAMMA__N_T_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_121 = MonteCarlo::GAMMA__2N_2P_REACTION;
    MonteCarlo::PhotonuclearReactionType type_122 = MonteCarlo::GAMMA__P_HE3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_123 = MonteCarlo::GAMMA__D_HE3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_124 = MonteCarlo::GAMMA__HE3_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_125 = MonteCarlo::GAMMA__4N_2P_REACTION;
    MonteCarlo::PhotonuclearReactionType type_126 = MonteCarlo::GAMMA__4N_2ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_127 = MonteCarlo::GAMMA__4N_P_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_128 = MonteCarlo::GAMMA__3P_REACTION;
    MonteCarlo::PhotonuclearReactionType type_129 = MonteCarlo::GAMMA__N_3P_REACTION;
    MonteCarlo::PhotonuclearReactionType type_130 = MonteCarlo::GAMMA__3N_2P_ALPHA_REACTION;
    MonteCarlo::PhotonuclearReactionType type_131 = MonteCarlo::GAMMA__5N_2P_REACTION;
    MonteCarlo::PhotonuclearReactionType type_132 = MonteCarlo::GAMMA__TOTAL_N_PRODUCTION;
    MonteCarlo::PhotonuclearReactionType type_133 = MonteCarlo::GAMMA__TOTAL_GAMMA_PRODUCTION;
    MonteCarlo::PhotonuclearReactionType type_134 = MonteCarlo::GAMMA__TOTAL_P_PRODUCTION;
    MonteCarlo::PhotonuclearReactionType type_135 = MonteCarlo::GAMMA__TOTAL_D_PRODUCTION;
    MonteCarlo::PhotonuclearReactionType type_136 = MonteCarlo::GAMMA__TOTAL_T_PRODUCTION;
    MonteCarlo::PhotonuclearReactionType type_137 = MonteCarlo::GAMMA__TOTAL_HE3_PRODUCTION;
    MonteCarlo::PhotonuclearReactionType type_138 = MonteCarlo::GAMMA__TOTAL_ALPHA_PRODUCTION;
    MonteCarlo::PhotonuclearReactionType type_139 = MonteCarlo::GAMMA__AVERAGE_HEATING;
    MonteCarlo::PhotonuclearReactionType type_140 = MonteCarlo::GAMMA__DAMAGE;
    MonteCarlo::PhotonuclearReactionType type_141 = MonteCarlo::GAMMA__P_EXCITED_STATE_0_REACTION;
    MonteCarlo::PhotonuclearReactionType type_142 = MonteCarlo::GAMMA__P_EXCITED_STATE_1_REACTION;
    MonteCarlo::PhotonuclearReactionType type_143 = MonteCarlo::GAMMA__P_EXCITED_STATE_2_REACTION;
    MonteCarlo::PhotonuclearReactionType type_144 = MonteCarlo::GAMMA__P_EXCITED_STATE_3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_145 = MonteCarlo::GAMMA__P_EXCITED_STATE_4_REACTION;
    MonteCarlo::PhotonuclearReactionType type_146 = MonteCarlo::GAMMA__P_EXCITED_STATE_5_REACTION;
    MonteCarlo::PhotonuclearReactionType type_147 = MonteCarlo::GAMMA__P_EXCITED_STATE_6_REACTION;
    MonteCarlo::PhotonuclearReactionType type_148 = MonteCarlo::GAMMA__P_EXCITED_STATE_7_REACTION;
    MonteCarlo::PhotonuclearReactionType type_149 = MonteCarlo::GAMMA__P_EXCITED_STATE_8_REACTION;
    MonteCarlo::PhotonuclearReactionType type_150 = MonteCarlo::GAMMA__P_EXCITED_STATE_9_REACTION;
    MonteCarlo::PhotonuclearReactionType type_151 = MonteCarlo::GAMMA__P_EXCITED_STATE_10_REACTION;
    MonteCarlo::PhotonuclearReactionType type_152 = MonteCarlo::GAMMA__P_EXCITED_STATE_11_REACTION;
    MonteCarlo::PhotonuclearReactionType type_153 = MonteCarlo::GAMMA__P_EXCITED_STATE_12_REACTION;
    MonteCarlo::PhotonuclearReactionType type_154 = MonteCarlo::GAMMA__P_EXCITED_STATE_13_REACTION;
    MonteCarlo::PhotonuclearReactionType type_155 = MonteCarlo::GAMMA__P_EXCITED_STATE_14_REACTION;
    MonteCarlo::PhotonuclearReactionType type_156 = MonteCarlo::GAMMA__P_EXCITED_STATE_15_REACTION;
    MonteCarlo::PhotonuclearReactionType type_157 = MonteCarlo::GAMMA__P_EXCITED_STATE_16_REACTION;
    MonteCarlo::PhotonuclearReactionType type_158 = MonteCarlo::GAMMA__P_EXCITED_STATE_17_REACTION;
    MonteCarlo::PhotonuclearReactionType type_159 = MonteCarlo::GAMMA__P_EXCITED_STATE_18_REACTION;
    MonteCarlo::PhotonuclearReactionType type_160 = MonteCarlo::GAMMA__P_EXCITED_STATE_19_REACTION;
    MonteCarlo::PhotonuclearReactionType type_161 = MonteCarlo::GAMMA__P_EXCITED_STATE_20_REACTION;
    MonteCarlo::PhotonuclearReactionType type_162 = MonteCarlo::GAMMA__P_EXCITED_STATE_21_REACTION;
    MonteCarlo::PhotonuclearReactionType type_163 = MonteCarlo::GAMMA__P_EXCITED_STATE_22_REACTION;
    MonteCarlo::PhotonuclearReactionType type_164 = MonteCarlo::GAMMA__P_EXCITED_STATE_23_REACTION;
    MonteCarlo::PhotonuclearReactionType type_165 = MonteCarlo::GAMMA__P_EXCITED_STATE_24_REACTION;
    MonteCarlo::PhotonuclearReactionType type_166 = MonteCarlo::GAMMA__P_EXCITED_STATE_25_REACTION;
    MonteCarlo::PhotonuclearReactionType type_167 = MonteCarlo::GAMMA__P_EXCITED_STATE_26_REACTION;
    MonteCarlo::PhotonuclearReactionType type_168 = MonteCarlo::GAMMA__P_EXCITED_STATE_27_REACTION;
    MonteCarlo::PhotonuclearReactionType type_169 = MonteCarlo::GAMMA__P_EXCITED_STATE_28_REACTION;
    MonteCarlo::PhotonuclearReactionType type_170 = MonteCarlo::GAMMA__P_EXCITED_STATE_29_REACTION;
    MonteCarlo::PhotonuclearReactionType type_171 = MonteCarlo::GAMMA__P_EXCITED_STATE_30_REACTION;
    MonteCarlo::PhotonuclearReactionType type_172 = MonteCarlo::GAMMA__P_EXCITED_STATE_31_REACTION;
    MonteCarlo::PhotonuclearReactionType type_173 = MonteCarlo::GAMMA__P_EXCITED_STATE_32_REACTION;
    MonteCarlo::PhotonuclearReactionType type_174 = MonteCarlo::GAMMA__P_EXCITED_STATE_33_REACTION;
    MonteCarlo::PhotonuclearReactionType type_175 = MonteCarlo::GAMMA__P_EXCITED_STATE_34_REACTION;
    MonteCarlo::PhotonuclearReactionType type_176 = MonteCarlo::GAMMA__P_EXCITED_STATE_35_REACTION;
    MonteCarlo::PhotonuclearReactionType type_177 = MonteCarlo::GAMMA__P_EXCITED_STATE_36_REACTION;
    MonteCarlo::PhotonuclearReactionType type_178 = MonteCarlo::GAMMA__P_EXCITED_STATE_37_REACTION;
    MonteCarlo::PhotonuclearReactionType type_179 = MonteCarlo::GAMMA__P_EXCITED_STATE_38_REACTION;
    MonteCarlo::PhotonuclearReactionType type_180 = MonteCarlo::GAMMA__P_EXCITED_STATE_39_REACTION;
    MonteCarlo::PhotonuclearReactionType type_181 = MonteCarlo::GAMMA__P_EXCITED_STATE_40_REACTION;
    MonteCarlo::PhotonuclearReactionType type_182 = MonteCarlo::GAMMA__P_EXCITED_STATE_41_REACTION;
    MonteCarlo::PhotonuclearReactionType type_183 = MonteCarlo::GAMMA__P_EXCITED_STATE_42_REACTION;
    MonteCarlo::PhotonuclearReactionType type_184 = MonteCarlo::GAMMA__P_EXCITED_STATE_43_REACTION;
    MonteCarlo::PhotonuclearReactionType type_185 = MonteCarlo::GAMMA__P_EXCITED_STATE_44_REACTION;
    MonteCarlo::PhotonuclearReactionType type_186 = MonteCarlo::GAMMA__P_EXCITED_STATE_45_REACTION;
    MonteCarlo::PhotonuclearReactionType type_187 = MonteCarlo::GAMMA__P_EXCITED_STATE_46_REACTION;
    MonteCarlo::PhotonuclearReactionType type_188 = MonteCarlo::GAMMA__P_EXCITED_STATE_47_REACTION;
    MonteCarlo::PhotonuclearReactionType type_189 = MonteCarlo::GAMMA__P_EXCITED_STATE_48_REACTION;
    MonteCarlo::PhotonuclearReactionType type_190 = MonteCarlo::GAMMA__P_CONTINUUM_REACTION;
    MonteCarlo::PhotonuclearReactionType type_191 = MonteCarlo::GAMMA__D_EXCITED_STATE_0_REACTION;
    MonteCarlo::PhotonuclearReactionType type_192 = MonteCarlo::GAMMA__D_EXCITED_STATE_1_REACTION;
    MonteCarlo::PhotonuclearReactionType type_193 = MonteCarlo::GAMMA__D_EXCITED_STATE_2_REACTION;
    MonteCarlo::PhotonuclearReactionType type_194 = MonteCarlo::GAMMA__D_EXCITED_STATE_3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_195 = MonteCarlo::GAMMA__D_EXCITED_STATE_4_REACTION;
    MonteCarlo::PhotonuclearReactionType type_196 = MonteCarlo::GAMMA__D_EXCITED_STATE_5_REACTION;
    MonteCarlo::PhotonuclearReactionType type_197 = MonteCarlo::GAMMA__D_EXCITED_STATE_6_REACTION;
    MonteCarlo::PhotonuclearReactionType type_198 = MonteCarlo::GAMMA__D_EXCITED_STATE_7_REACTION;
    MonteCarlo::PhotonuclearReactionType type_199 = MonteCarlo::GAMMA__D_EXCITED_STATE_8_REACTION;
    MonteCarlo::PhotonuclearReactionType type_200 = MonteCarlo::GAMMA__D_EXCITED_STATE_9_REACTION;
    MonteCarlo::PhotonuclearReactionType type_201 = MonteCarlo::GAMMA__D_EXCITED_STATE_10_REACTION;
    MonteCarlo::PhotonuclearReactionType type_202 = MonteCarlo::GAMMA__D_EXCITED_STATE_11_REACTION;
    MonteCarlo::PhotonuclearReactionType type_203 = MonteCarlo::GAMMA__D_EXCITED_STATE_12_REACTION;
    MonteCarlo::PhotonuclearReactionType type_204 = MonteCarlo::GAMMA__D_EXCITED_STATE_13_REACTION;
    MonteCarlo::PhotonuclearReactionType type_205 = MonteCarlo::GAMMA__D_EXCITED_STATE_14_REACTION;
    MonteCarlo::PhotonuclearReactionType type_206 = MonteCarlo::GAMMA__D_EXCITED_STATE_15_REACTION;
    MonteCarlo::PhotonuclearReactionType type_207 = MonteCarlo::GAMMA__D_EXCITED_STATE_16_REACTION;
    MonteCarlo::PhotonuclearReactionType type_208 = MonteCarlo::GAMMA__D_EXCITED_STATE_17_REACTION;
    MonteCarlo::PhotonuclearReactionType type_209 = MonteCarlo::GAMMA__D_EXCITED_STATE_18_REACTION;
    MonteCarlo::PhotonuclearReactionType type_210 = MonteCarlo::GAMMA__D_EXCITED_STATE_19_REACTION;
    MonteCarlo::PhotonuclearReactionType type_211 = MonteCarlo::GAMMA__D_EXCITED_STATE_20_REACTION;
    MonteCarlo::PhotonuclearReactionType type_212 = MonteCarlo::GAMMA__D_EXCITED_STATE_21_REACTION;
    MonteCarlo::PhotonuclearReactionType type_213 = MonteCarlo::GAMMA__D_EXCITED_STATE_22_REACTION;
    MonteCarlo::PhotonuclearReactionType type_214 = MonteCarlo::GAMMA__D_EXCITED_STATE_23_REACTION;
    MonteCarlo::PhotonuclearReactionType type_215 = MonteCarlo::GAMMA__D_EXCITED_STATE_24_REACTION;
    MonteCarlo::PhotonuclearReactionType type_216 = MonteCarlo::GAMMA__D_EXCITED_STATE_25_REACTION;
    MonteCarlo::PhotonuclearReactionType type_217 = MonteCarlo::GAMMA__D_EXCITED_STATE_26_REACTION;
    MonteCarlo::PhotonuclearReactionType type_218 = MonteCarlo::GAMMA__D_EXCITED_STATE_27_REACTION;
    MonteCarlo::PhotonuclearReactionType type_219 = MonteCarlo::GAMMA__D_EXCITED_STATE_28_REACTION;
    MonteCarlo::PhotonuclearReactionType type_220 = MonteCarlo::GAMMA__D_EXCITED_STATE_29_REACTION;
    MonteCarlo::PhotonuclearReactionType type_221 = MonteCarlo::GAMMA__D_EXCITED_STATE_30_REACTION;
    MonteCarlo::PhotonuclearReactionType type_222 = MonteCarlo::GAMMA__D_EXCITED_STATE_31_REACTION;
    MonteCarlo::PhotonuclearReactionType type_223 = MonteCarlo::GAMMA__D_EXCITED_STATE_32_REACTION;
    MonteCarlo::PhotonuclearReactionType type_224 = MonteCarlo::GAMMA__D_EXCITED_STATE_33_REACTION;
    MonteCarlo::PhotonuclearReactionType type_225 = MonteCarlo::GAMMA__D_EXCITED_STATE_34_REACTION;
    MonteCarlo::PhotonuclearReactionType type_226 = MonteCarlo::GAMMA__D_EXCITED_STATE_35_REACTION;
    MonteCarlo::PhotonuclearReactionType type_227 = MonteCarlo::GAMMA__D_EXCITED_STATE_36_REACTION;
    MonteCarlo::PhotonuclearReactionType type_228 = MonteCarlo::GAMMA__D_EXCITED_STATE_37_REACTION;
    MonteCarlo::PhotonuclearReactionType type_229 = MonteCarlo::GAMMA__D_EXCITED_STATE_38_REACTION;
    MonteCarlo::PhotonuclearReactionType type_230 = MonteCarlo::GAMMA__D_EXCITED_STATE_39_REACTION;
    MonteCarlo::PhotonuclearReactionType type_231 = MonteCarlo::GAMMA__D_EXCITED_STATE_40_REACTION;
    MonteCarlo::PhotonuclearReactionType type_232 = MonteCarlo::GAMMA__D_EXCITED_STATE_41_REACTION;
    MonteCarlo::PhotonuclearReactionType type_233 = MonteCarlo::GAMMA__D_EXCITED_STATE_42_REACTION;
    MonteCarlo::PhotonuclearReactionType type_234 = MonteCarlo::GAMMA__D_EXCITED_STATE_43_REACTION;
    MonteCarlo::PhotonuclearReactionType type_235 = MonteCarlo::GAMMA__D_EXCITED_STATE_44_REACTION;
    MonteCarlo::PhotonuclearReactionType type_236 = MonteCarlo::GAMMA__D_EXCITED_STATE_45_REACTION;
    MonteCarlo::PhotonuclearReactionType type_237 = MonteCarlo::GAMMA__D_EXCITED_STATE_46_REACTION;
    MonteCarlo::PhotonuclearReactionType type_238 = MonteCarlo::GAMMA__D_EXCITED_STATE_47_REACTION;
    MonteCarlo::PhotonuclearReactionType type_239 = MonteCarlo::GAMMA__D_EXCITED_STATE_48_REACTION;
    MonteCarlo::PhotonuclearReactionType type_240 = MonteCarlo::GAMMA__D_CONTINUUM_REACTION;
    MonteCarlo::PhotonuclearReactionType type_241 = MonteCarlo::GAMMA__T_EXCITED_STATE_0_REACTION;
    MonteCarlo::PhotonuclearReactionType type_242 = MonteCarlo::GAMMA__T_EXCITED_STATE_1_REACTION;
    MonteCarlo::PhotonuclearReactionType type_243 = MonteCarlo::GAMMA__T_EXCITED_STATE_2_REACTION;
    MonteCarlo::PhotonuclearReactionType type_244 = MonteCarlo::GAMMA__T_EXCITED_STATE_3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_245 = MonteCarlo::GAMMA__T_EXCITED_STATE_4_REACTION;
    MonteCarlo::PhotonuclearReactionType type_246 = MonteCarlo::GAMMA__T_EXCITED_STATE_5_REACTION;
    MonteCarlo::PhotonuclearReactionType type_247 = MonteCarlo::GAMMA__T_EXCITED_STATE_6_REACTION;
    MonteCarlo::PhotonuclearReactionType type_248 = MonteCarlo::GAMMA__T_EXCITED_STATE_7_REACTION;
    MonteCarlo::PhotonuclearReactionType type_249 = MonteCarlo::GAMMA__T_EXCITED_STATE_8_REACTION;
    MonteCarlo::PhotonuclearReactionType type_250 = MonteCarlo::GAMMA__T_EXCITED_STATE_9_REACTION;
    MonteCarlo::PhotonuclearReactionType type_251 = MonteCarlo::GAMMA__T_EXCITED_STATE_10_REACTION;
    MonteCarlo::PhotonuclearReactionType type_252 = MonteCarlo::GAMMA__T_EXCITED_STATE_11_REACTION;
    MonteCarlo::PhotonuclearReactionType type_253 = MonteCarlo::GAMMA__T_EXCITED_STATE_12_REACTION;
    MonteCarlo::PhotonuclearReactionType type_254 = MonteCarlo::GAMMA__T_EXCITED_STATE_13_REACTION;
    MonteCarlo::PhotonuclearReactionType type_255 = MonteCarlo::GAMMA__T_EXCITED_STATE_14_REACTION;
    MonteCarlo::PhotonuclearReactionType type_256 = MonteCarlo::GAMMA__T_EXCITED_STATE_15_REACTION;
    MonteCarlo::PhotonuclearReactionType type_257 = MonteCarlo::GAMMA__T_EXCITED_STATE_16_REACTION;
    MonteCarlo::PhotonuclearReactionType type_258 = MonteCarlo::GAMMA__T_EXCITED_STATE_17_REACTION;
    MonteCarlo::PhotonuclearReactionType type_259 = MonteCarlo::GAMMA__T_EXCITED_STATE_18_REACTION;
    MonteCarlo::PhotonuclearReactionType type_260 = MonteCarlo::GAMMA__T_EXCITED_STATE_19_REACTION;
    MonteCarlo::PhotonuclearReactionType type_261 = MonteCarlo::GAMMA__T_EXCITED_STATE_20_REACTION;
    MonteCarlo::PhotonuclearReactionType type_262 = MonteCarlo::GAMMA__T_EXCITED_STATE_21_REACTION;
    MonteCarlo::PhotonuclearReactionType type_263 = MonteCarlo::GAMMA__T_EXCITED_STATE_22_REACTION;
    MonteCarlo::PhotonuclearReactionType type_264 = MonteCarlo::GAMMA__T_EXCITED_STATE_23_REACTION;
    MonteCarlo::PhotonuclearReactionType type_265 = MonteCarlo::GAMMA__T_EXCITED_STATE_24_REACTION;
    MonteCarlo::PhotonuclearReactionType type_266 = MonteCarlo::GAMMA__T_EXCITED_STATE_25_REACTION;
    MonteCarlo::PhotonuclearReactionType type_267 = MonteCarlo::GAMMA__T_EXCITED_STATE_26_REACTION;
    MonteCarlo::PhotonuclearReactionType type_268 = MonteCarlo::GAMMA__T_EXCITED_STATE_27_REACTION;
    MonteCarlo::PhotonuclearReactionType type_269 = MonteCarlo::GAMMA__T_EXCITED_STATE_28_REACTION;
    MonteCarlo::PhotonuclearReactionType type_270 = MonteCarlo::GAMMA__T_EXCITED_STATE_29_REACTION;
    MonteCarlo::PhotonuclearReactionType type_271 = MonteCarlo::GAMMA__T_EXCITED_STATE_30_REACTION;
    MonteCarlo::PhotonuclearReactionType type_272 = MonteCarlo::GAMMA__T_EXCITED_STATE_31_REACTION;
    MonteCarlo::PhotonuclearReactionType type_273 = MonteCarlo::GAMMA__T_EXCITED_STATE_32_REACTION;
    MonteCarlo::PhotonuclearReactionType type_274 = MonteCarlo::GAMMA__T_EXCITED_STATE_33_REACTION;
    MonteCarlo::PhotonuclearReactionType type_275 = MonteCarlo::GAMMA__T_EXCITED_STATE_34_REACTION;
    MonteCarlo::PhotonuclearReactionType type_276 = MonteCarlo::GAMMA__T_EXCITED_STATE_35_REACTION;
    MonteCarlo::PhotonuclearReactionType type_277 = MonteCarlo::GAMMA__T_EXCITED_STATE_36_REACTION;
    MonteCarlo::PhotonuclearReactionType type_278 = MonteCarlo::GAMMA__T_EXCITED_STATE_37_REACTION;
    MonteCarlo::PhotonuclearReactionType type_279 = MonteCarlo::GAMMA__T_EXCITED_STATE_38_REACTION;
    MonteCarlo::PhotonuclearReactionType type_280 = MonteCarlo::GAMMA__T_EXCITED_STATE_39_REACTION;
    MonteCarlo::PhotonuclearReactionType type_281 = MonteCarlo::GAMMA__T_EXCITED_STATE_40_REACTION;
    MonteCarlo::PhotonuclearReactionType type_282 = MonteCarlo::GAMMA__T_EXCITED_STATE_41_REACTION;
    MonteCarlo::PhotonuclearReactionType type_283 = MonteCarlo::GAMMA__T_EXCITED_STATE_42_REACTION;
    MonteCarlo::PhotonuclearReactionType type_284 = MonteCarlo::GAMMA__T_EXCITED_STATE_43_REACTION;
    MonteCarlo::PhotonuclearReactionType type_285 = MonteCarlo::GAMMA__T_EXCITED_STATE_44_REACTION;
    MonteCarlo::PhotonuclearReactionType type_286 = MonteCarlo::GAMMA__T_EXCITED_STATE_45_REACTION;
    MonteCarlo::PhotonuclearReactionType type_287 = MonteCarlo::GAMMA__T_EXCITED_STATE_46_REACTION;
    MonteCarlo::PhotonuclearReactionType type_288 = MonteCarlo::GAMMA__T_EXCITED_STATE_47_REACTION;
    MonteCarlo::PhotonuclearReactionType type_289 = MonteCarlo::GAMMA__T_EXCITED_STATE_48_REACTION;
    MonteCarlo::PhotonuclearReactionType type_290 = MonteCarlo::GAMMA__T_CONTINUUM_REACTION;
    MonteCarlo::PhotonuclearReactionType type_291 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_0_REACTION;
    MonteCarlo::PhotonuclearReactionType type_292 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_1_REACTION;
    MonteCarlo::PhotonuclearReactionType type_293 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_2_REACTION;
    MonteCarlo::PhotonuclearReactionType type_294 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_295 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_4_REACTION;
    MonteCarlo::PhotonuclearReactionType type_296 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_5_REACTION;
    MonteCarlo::PhotonuclearReactionType type_297 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_6_REACTION;
    MonteCarlo::PhotonuclearReactionType type_298 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_7_REACTION;
    MonteCarlo::PhotonuclearReactionType type_299 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_8_REACTION;
    MonteCarlo::PhotonuclearReactionType type_300 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_9_REACTION;
    MonteCarlo::PhotonuclearReactionType type_301 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_10_REACTION;
    MonteCarlo::PhotonuclearReactionType type_302 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_11_REACTION;
    MonteCarlo::PhotonuclearReactionType type_303 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_12_REACTION;
    MonteCarlo::PhotonuclearReactionType type_304 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_13_REACTION;
    MonteCarlo::PhotonuclearReactionType type_305 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_14_REACTION;
    MonteCarlo::PhotonuclearReactionType type_306 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_15_REACTION;
    MonteCarlo::PhotonuclearReactionType type_307 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_16_REACTION;
    MonteCarlo::PhotonuclearReactionType type_308 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_17_REACTION;
    MonteCarlo::PhotonuclearReactionType type_309 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_18_REACTION;
    MonteCarlo::PhotonuclearReactionType type_310 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_19_REACTION;
    MonteCarlo::PhotonuclearReactionType type_311 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_20_REACTION;
    MonteCarlo::PhotonuclearReactionType type_312 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_21_REACTION;
    MonteCarlo::PhotonuclearReactionType type_313 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_22_REACTION;
    MonteCarlo::PhotonuclearReactionType type_314 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_23_REACTION;
    MonteCarlo::PhotonuclearReactionType type_315 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_24_REACTION;
    MonteCarlo::PhotonuclearReactionType type_316 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_25_REACTION;
    MonteCarlo::PhotonuclearReactionType type_317 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_26_REACTION;
    MonteCarlo::PhotonuclearReactionType type_318 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_27_REACTION;
    MonteCarlo::PhotonuclearReactionType type_319 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_28_REACTION;
    MonteCarlo::PhotonuclearReactionType type_320 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_29_REACTION;
    MonteCarlo::PhotonuclearReactionType type_321 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_30_REACTION;
    MonteCarlo::PhotonuclearReactionType type_322 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_31_REACTION;
    MonteCarlo::PhotonuclearReactionType type_323 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_32_REACTION;
    MonteCarlo::PhotonuclearReactionType type_324 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_33_REACTION;
    MonteCarlo::PhotonuclearReactionType type_325 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_34_REACTION;
    MonteCarlo::PhotonuclearReactionType type_326 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_35_REACTION;
    MonteCarlo::PhotonuclearReactionType type_327 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_36_REACTION;
    MonteCarlo::PhotonuclearReactionType type_328 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_37_REACTION;
    MonteCarlo::PhotonuclearReactionType type_329 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_38_REACTION;
    MonteCarlo::PhotonuclearReactionType type_330 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_39_REACTION;
    MonteCarlo::PhotonuclearReactionType type_331 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_40_REACTION;
    MonteCarlo::PhotonuclearReactionType type_332 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_41_REACTION;
    MonteCarlo::PhotonuclearReactionType type_333 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_42_REACTION;
    MonteCarlo::PhotonuclearReactionType type_334 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_43_REACTION;
    MonteCarlo::PhotonuclearReactionType type_335 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_44_REACTION;
    MonteCarlo::PhotonuclearReactionType type_336 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_45_REACTION;
    MonteCarlo::PhotonuclearReactionType type_337 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_46_REACTION;
    MonteCarlo::PhotonuclearReactionType type_338 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_47_REACTION;
    MonteCarlo::PhotonuclearReactionType type_339 = MonteCarlo::GAMMA__HE3_EXCITED_STATE_48_REACTION;
    MonteCarlo::PhotonuclearReactionType type_340 = MonteCarlo::GAMMA__HE3_CONTINUUM_REACTION;
    MonteCarlo::PhotonuclearReactionType type_341 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_0_REACTION;
    MonteCarlo::PhotonuclearReactionType type_342 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_1_REACTION;
    MonteCarlo::PhotonuclearReactionType type_343 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_2_REACTION;
    MonteCarlo::PhotonuclearReactionType type_344 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_345 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_4_REACTION;
    MonteCarlo::PhotonuclearReactionType type_346 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_5_REACTION;
    MonteCarlo::PhotonuclearReactionType type_347 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_6_REACTION;
    MonteCarlo::PhotonuclearReactionType type_348 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_7_REACTION;
    MonteCarlo::PhotonuclearReactionType type_349 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_8_REACTION;
    MonteCarlo::PhotonuclearReactionType type_350 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_9_REACTION;
    MonteCarlo::PhotonuclearReactionType type_351 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_10_REACTION;
    MonteCarlo::PhotonuclearReactionType type_352 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_11_REACTION;
    MonteCarlo::PhotonuclearReactionType type_353 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_12_REACTION;
    MonteCarlo::PhotonuclearReactionType type_354 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_13_REACTION;
    MonteCarlo::PhotonuclearReactionType type_355 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_14_REACTION;
    MonteCarlo::PhotonuclearReactionType type_356 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_15_REACTION;
    MonteCarlo::PhotonuclearReactionType type_357 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_16_REACTION;
    MonteCarlo::PhotonuclearReactionType type_358 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_17_REACTION;
    MonteCarlo::PhotonuclearReactionType type_359 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_18_REACTION;
    MonteCarlo::PhotonuclearReactionType type_360 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_19_REACTION;
    MonteCarlo::PhotonuclearReactionType type_361 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_20_REACTION;
    MonteCarlo::PhotonuclearReactionType type_362 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_21_REACTION;
    MonteCarlo::PhotonuclearReactionType type_363 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_22_REACTION;
    MonteCarlo::PhotonuclearReactionType type_364 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_23_REACTION;
    MonteCarlo::PhotonuclearReactionType type_365 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_24_REACTION;
    MonteCarlo::PhotonuclearReactionType type_366 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_25_REACTION;
    MonteCarlo::PhotonuclearReactionType type_367 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_26_REACTION;
    MonteCarlo::PhotonuclearReactionType type_368 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_27_REACTION;
    MonteCarlo::PhotonuclearReactionType type_369 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_28_REACTION;
    MonteCarlo::PhotonuclearReactionType type_370 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_29_REACTION;
    MonteCarlo::PhotonuclearReactionType type_371 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_30_REACTION;
    MonteCarlo::PhotonuclearReactionType type_372 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_31_REACTION;
    MonteCarlo::PhotonuclearReactionType type_373 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_32_REACTION;
    MonteCarlo::PhotonuclearReactionType type_374 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_33_REACTION;
    MonteCarlo::PhotonuclearReactionType type_375 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_34_REACTION;
    MonteCarlo::PhotonuclearReactionType type_376 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_35_REACTION;
    MonteCarlo::PhotonuclearReactionType type_377 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_36_REACTION;
    MonteCarlo::PhotonuclearReactionType type_378 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_37_REACTION;
    MonteCarlo::PhotonuclearReactionType type_379 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_38_REACTION;
    MonteCarlo::PhotonuclearReactionType type_380 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_39_REACTION;
    MonteCarlo::PhotonuclearReactionType type_381 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_40_REACTION;
    MonteCarlo::PhotonuclearReactionType type_382 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_41_REACTION;
    MonteCarlo::PhotonuclearReactionType type_383 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_42_REACTION;
    MonteCarlo::PhotonuclearReactionType type_384 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_43_REACTION;
    MonteCarlo::PhotonuclearReactionType type_385 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_44_REACTION;
    MonteCarlo::PhotonuclearReactionType type_386 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_45_REACTION;
    MonteCarlo::PhotonuclearReactionType type_387 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_46_REACTION;
    MonteCarlo::PhotonuclearReactionType type_388 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_47_REACTION;
    MonteCarlo::PhotonuclearReactionType type_389 = MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_48_REACTION;
    MonteCarlo::PhotonuclearReactionType type_390 = MonteCarlo::GAMMA__ALPHA_CONTINUUM_REACTION;
    MonteCarlo::PhotonuclearReactionType type_391 = MonteCarlo::GAMMA__2N_EXCITED_STATE_0_REACTION; 
    MonteCarlo::PhotonuclearReactionType type_392 = MonteCarlo::GAMMA__2N_EXCITED_STATE_1_REACTION;
    MonteCarlo::PhotonuclearReactionType type_393 = MonteCarlo::GAMMA__2N_EXCITED_STATE_2_REACTION;
    MonteCarlo::PhotonuclearReactionType type_394 = MonteCarlo::GAMMA__2N_EXCITED_STATE_3_REACTION;
    MonteCarlo::PhotonuclearReactionType type_395 = MonteCarlo::GAMMA__2N_EXCITED_STATE_4_REACTION;
    MonteCarlo::PhotonuclearReactionType type_396 = MonteCarlo::GAMMA__2N_EXCITED_STATE_5_REACTION;
    MonteCarlo::PhotonuclearReactionType type_397 = MonteCarlo::GAMMA__2N_EXCITED_STATE_6_REACTION;
    MonteCarlo::PhotonuclearReactionType type_398 = MonteCarlo::GAMMA__2N_EXCITED_STATE_7_REACTION;
    MonteCarlo::PhotonuclearReactionType type_399 = MonteCarlo::GAMMA__2N_EXCITED_STATE_8_REACTION;
    MonteCarlo::PhotonuclearReactionType type_400 = MonteCarlo::GAMMA__2N_EXCITED_STATE_9_REACTION;
    MonteCarlo::PhotonuclearReactionType type_401 = MonteCarlo::GAMMA__2N_EXCITED_STATE_10_REACTION;
    MonteCarlo::PhotonuclearReactionType type_402 = MonteCarlo::GAMMA__2N_EXCITED_STATE_11_REACTION;
    MonteCarlo::PhotonuclearReactionType type_403 = MonteCarlo::GAMMA__2N_EXCITED_STATE_12_REACTION;
    MonteCarlo::PhotonuclearReactionType type_404 = MonteCarlo::GAMMA__2N_EXCITED_STATE_13_REACTION;
    MonteCarlo::PhotonuclearReactionType type_405 = MonteCarlo::GAMMA__2N_EXCITED_STATE_14_REACTION;
    MonteCarlo::PhotonuclearReactionType type_406 = MonteCarlo::GAMMA__2N_EXCITED_STATE_15_REACTION;
    MonteCarlo::PhotonuclearReactionType type_407 = MonteCarlo::GAMMA__2N_CONTINUUM_REACTION;

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

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::PhotonuclearReactionType type_1, type_2, type_3, type_4, type_5,
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
    type_86, type_87, type_88, type_89, type_90, type_91, type_92, type_93,
    type_94, type_95, type_96, type_97, type_98, type_99, type_100, type_101,
    type_102, type_103, type_104, type_105, type_106, type_107, type_108,
    type_109, type_110, type_111, type_112, type_113, type_114, type_115,
    type_116, type_117, type_118, type_119, type_120, type_121, type_122,
    type_123, type_124, type_125, type_126, type_127, type_128, type_129,
    type_130, type_131, type_132, type_133, type_134, type_135, type_136,
    type_137, type_138, type_139, type_140, type_141, type_142, type_143,
    type_144, type_145, type_146, type_147, type_148, type_149, type_150,
    type_151, type_152, type_153, type_154, type_155, type_156, type_157,
    type_158, type_159, type_160, type_161, type_162, type_163, type_164,
    type_165, type_166, type_167, type_168, type_169, type_170, type_171,
    type_172, type_173, type_174, type_175, type_176, type_177, type_178,
    type_179, type_180, type_181, type_182, type_183, type_184, type_185,
    type_186, type_187, type_188, type_189, type_190, type_191, type_192,
    type_193, type_194, type_195, type_196, type_197, type_198, type_199,
    type_200, type_201, type_202, type_203, type_204, type_205, type_206,
    type_207, type_208, type_209, type_210, type_211, type_212, type_213,
    type_214, type_215, type_216, type_217, type_218, type_219, type_220,
    type_221, type_222, type_223, type_224, type_225, type_226, type_227,
    type_228, type_229, type_230, type_231, type_232, type_233, type_234,
    type_235, type_236, type_237, type_238, type_239, type_240, type_241,
    type_242, type_243, type_244, type_245, type_246, type_247, type_248,
    type_249, type_250, type_251, type_252, type_253, type_254, type_255,
    type_256, type_257, type_258, type_259, type_260, type_261, type_262,
    type_263, type_264, type_265, type_266, type_267, type_268, type_269,
    type_270, type_271, type_272, type_273, type_274, type_275, type_276,
    type_277, type_278, type_279, type_280, type_281, type_282, type_283,
    type_284, type_285, type_286, type_287, type_288, type_289, type_290,
    type_291, type_292, type_293, type_294, type_295, type_296, type_297,
    type_298, type_299, type_300, type_301, type_302, type_303, type_304,
    type_305, type_306, type_307, type_308, type_309, type_310, type_311,
    type_312, type_313, type_314, type_315, type_316, type_317, type_318,
    type_319, type_320, type_321, type_322, type_323, type_324, type_325,
    type_326, type_327, type_328, type_329, type_330, type_331, type_332,
    type_333, type_334, type_335, type_336, type_337, type_338, type_339,
    type_340, type_341, type_342, type_343, type_344, type_345, type_346,
    type_347, type_348, type_349, type_350, type_351, type_352, type_353,
    type_354, type_355, type_356, type_357, type_358, type_359, type_360,
    type_361, type_362, type_363, type_364, type_365, type_366, type_367,
    type_368, type_369, type_370, type_371, type_372, type_373, type_374,
    type_375, type_376, type_377, type_378, type_379, type_380, type_381,
    type_382, type_383, type_384, type_385, type_386, type_387, type_388,
    type_389, type_390, type_391, type_392, type_393, type_394, type_395,
    type_396, type_397, type_398, type_399, type_400, type_401, type_402,
    type_403, type_404, type_405, type_406, type_407;

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

  FRENSIE_CHECK_EQUAL( type_1, MonteCarlo::GAMMA__TOTAL_REACTION );
  FRENSIE_CHECK_EQUAL( type_2, MonteCarlo::GAMMA__GAMMA_ELASTIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_3, MonteCarlo::GAMMA__GAMMA_NON_ELASTIC_REACTION );
  FRENSIE_CHECK_EQUAL( type_4, MonteCarlo::GAMMA__N_REACTION );
  FRENSIE_CHECK_EQUAL( type_5, MonteCarlo::GAMMA__ANYTHING_REACTION );
  FRENSIE_CHECK_EQUAL( type_6, MonteCarlo::GAMMA__2N_D_REACTION );
  FRENSIE_CHECK_EQUAL( type_7, MonteCarlo::GAMMA__2N_REACTION );
  FRENSIE_CHECK_EQUAL( type_8, MonteCarlo::GAMMA__3N_REACTION );
  FRENSIE_CHECK_EQUAL( type_9, MonteCarlo::GAMMA__TOTAL_FISSION_REACTION );
  FRENSIE_CHECK_EQUAL( type_10, MonteCarlo::GAMMA__N_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_11, MonteCarlo::GAMMA__2N_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_12, MonteCarlo::GAMMA__3N_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_13, MonteCarlo::GAMMA__N_P_REACTION );
  FRENSIE_CHECK_EQUAL( type_14, MonteCarlo::GAMMA__N_2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_15, MonteCarlo::GAMMA__2N_2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_16, MonteCarlo::GAMMA__N_D_REACTION );
  FRENSIE_CHECK_EQUAL( type_17, MonteCarlo::GAMMA__N_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_18, MonteCarlo::GAMMA__N_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_19, MonteCarlo::GAMMA__N_D_2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_20, MonteCarlo::GAMMA__N_T_2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_21, MonteCarlo::GAMMA__4N_REACTION );
  FRENSIE_CHECK_EQUAL( type_22, MonteCarlo::GAMMA__2N_P_REACTION );
  FRENSIE_CHECK_EQUAL( type_23, MonteCarlo::GAMMA__3N_P_REACTION );
  FRENSIE_CHECK_EQUAL( type_24, MonteCarlo::GAMMA__N_2P_REACTION );
  FRENSIE_CHECK_EQUAL( type_25, MonteCarlo::GAMMA__N_P_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_26, MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION );
  FRENSIE_CHECK_EQUAL( type_27, MonteCarlo::GAMMA__N_EXCITED_STATE_1_REACTION );
  FRENSIE_CHECK_EQUAL( type_28, MonteCarlo::GAMMA__N_EXCITED_STATE_2_REACTION );
  FRENSIE_CHECK_EQUAL( type_29, MonteCarlo::GAMMA__N_EXCITED_STATE_3_REACTION );
  FRENSIE_CHECK_EQUAL( type_30, MonteCarlo::GAMMA__N_EXCITED_STATE_4_REACTION );
  FRENSIE_CHECK_EQUAL( type_31, MonteCarlo::GAMMA__N_EXCITED_STATE_5_REACTION );
  FRENSIE_CHECK_EQUAL( type_32, MonteCarlo::GAMMA__N_EXCITED_STATE_6_REACTION );
  FRENSIE_CHECK_EQUAL( type_33, MonteCarlo::GAMMA__N_EXCITED_STATE_7_REACTION );
  FRENSIE_CHECK_EQUAL( type_34, MonteCarlo::GAMMA__N_EXCITED_STATE_8_REACTION );
  FRENSIE_CHECK_EQUAL( type_35, MonteCarlo::GAMMA__N_EXCITED_STATE_9_REACTION );
  FRENSIE_CHECK_EQUAL( type_36, MonteCarlo::GAMMA__N_EXCITED_STATE_10_REACTION );
  FRENSIE_CHECK_EQUAL( type_37, MonteCarlo::GAMMA__N_EXCITED_STATE_11_REACTION );
  FRENSIE_CHECK_EQUAL( type_38, MonteCarlo::GAMMA__N_EXCITED_STATE_12_REACTION );
  FRENSIE_CHECK_EQUAL( type_39, MonteCarlo::GAMMA__N_EXCITED_STATE_13_REACTION );
  FRENSIE_CHECK_EQUAL( type_40, MonteCarlo::GAMMA__N_EXCITED_STATE_14_REACTION );
  FRENSIE_CHECK_EQUAL( type_41, MonteCarlo::GAMMA__N_EXCITED_STATE_15_REACTION );
  FRENSIE_CHECK_EQUAL( type_42, MonteCarlo::GAMMA__N_EXCITED_STATE_16_REACTION );
  FRENSIE_CHECK_EQUAL( type_43, MonteCarlo::GAMMA__N_EXCITED_STATE_17_REACTION );
  FRENSIE_CHECK_EQUAL( type_44, MonteCarlo::GAMMA__N_EXCITED_STATE_18_REACTION );
  FRENSIE_CHECK_EQUAL( type_45, MonteCarlo::GAMMA__N_EXCITED_STATE_19_REACTION );
  FRENSIE_CHECK_EQUAL( type_46, MonteCarlo::GAMMA__N_EXCITED_STATE_20_REACTION );
  FRENSIE_CHECK_EQUAL( type_47, MonteCarlo::GAMMA__N_EXCITED_STATE_21_REACTION );
  FRENSIE_CHECK_EQUAL( type_48, MonteCarlo::GAMMA__N_EXCITED_STATE_22_REACTION );
  FRENSIE_CHECK_EQUAL( type_49, MonteCarlo::GAMMA__N_EXCITED_STATE_23_REACTION );
  FRENSIE_CHECK_EQUAL( type_50, MonteCarlo::GAMMA__N_EXCITED_STATE_24_REACTION );
  FRENSIE_CHECK_EQUAL( type_51, MonteCarlo::GAMMA__N_EXCITED_STATE_25_REACTION );
  FRENSIE_CHECK_EQUAL( type_52, MonteCarlo::GAMMA__N_EXCITED_STATE_26_REACTION );
  FRENSIE_CHECK_EQUAL( type_53, MonteCarlo::GAMMA__N_EXCITED_STATE_27_REACTION );
  FRENSIE_CHECK_EQUAL( type_54, MonteCarlo::GAMMA__N_EXCITED_STATE_28_REACTION );
  FRENSIE_CHECK_EQUAL( type_55, MonteCarlo::GAMMA__N_EXCITED_STATE_29_REACTION );
  FRENSIE_CHECK_EQUAL( type_56, MonteCarlo::GAMMA__N_EXCITED_STATE_30_REACTION );
  FRENSIE_CHECK_EQUAL( type_57, MonteCarlo::GAMMA__N_EXCITED_STATE_31_REACTION );
  FRENSIE_CHECK_EQUAL( type_58, MonteCarlo::GAMMA__N_EXCITED_STATE_32_REACTION );
  FRENSIE_CHECK_EQUAL( type_59, MonteCarlo::GAMMA__N_EXCITED_STATE_33_REACTION );
  FRENSIE_CHECK_EQUAL( type_60, MonteCarlo::GAMMA__N_EXCITED_STATE_34_REACTION );
  FRENSIE_CHECK_EQUAL( type_61, MonteCarlo::GAMMA__N_EXCITED_STATE_35_REACTION );
  FRENSIE_CHECK_EQUAL( type_62, MonteCarlo::GAMMA__N_EXCITED_STATE_36_REACTION );
  FRENSIE_CHECK_EQUAL( type_63, MonteCarlo::GAMMA__N_EXCITED_STATE_37_REACTION );
  FRENSIE_CHECK_EQUAL( type_64, MonteCarlo::GAMMA__N_EXCITED_STATE_38_REACTION );
  FRENSIE_CHECK_EQUAL( type_65, MonteCarlo::GAMMA__N_EXCITED_STATE_39_REACTION );
  FRENSIE_CHECK_EQUAL( type_66, MonteCarlo::GAMMA__N_EXCITED_STATE_40_REACTION );
  FRENSIE_CHECK_EQUAL( type_67, MonteCarlo::GAMMA__N_CONTINUUM_REACTION );
  FRENSIE_CHECK_EQUAL( type_68, MonteCarlo::GAMMA__CAPTURE_REACTION );
  FRENSIE_CHECK_EQUAL( type_69, MonteCarlo::GAMMA__P_REACTION );
  FRENSIE_CHECK_EQUAL( type_70, MonteCarlo::GAMMA__D_REACTION );
  FRENSIE_CHECK_EQUAL( type_71, MonteCarlo::GAMMA__T_REACTION );
  FRENSIE_CHECK_EQUAL( type_72, MonteCarlo::GAMMA__HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_73, MonteCarlo::GAMMA__ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_74, MonteCarlo::GAMMA__2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_75, MonteCarlo::GAMMA__3ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_76, MonteCarlo::GAMMA__2P_REACTION );
  FRENSIE_CHECK_EQUAL( type_77, MonteCarlo::GAMMA__P_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_78, MonteCarlo::GAMMA__T_2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_79, MonteCarlo::GAMMA__D_2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_80, MonteCarlo::GAMMA__P_D_REACTION );
  FRENSIE_CHECK_EQUAL( type_81, MonteCarlo::GAMMA__P_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_82, MonteCarlo::GAMMA__D_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_83, MonteCarlo::GAMMA__5N_REACTION );
  FRENSIE_CHECK_EQUAL( type_84, MonteCarlo::GAMMA__6N_REACTION );
  FRENSIE_CHECK_EQUAL( type_85, MonteCarlo::GAMMA__2N_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_86, MonteCarlo::GAMMA__T_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_87, MonteCarlo::GAMMA__4N_P_REACTION );
  FRENSIE_CHECK_EQUAL( type_88, MonteCarlo::GAMMA__3N_D_REACTION );
  FRENSIE_CHECK_EQUAL( type_89, MonteCarlo::GAMMA__N_D_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_90, MonteCarlo::GAMMA__2N_P_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_91, MonteCarlo::GAMMA__7N_REACTION );
  FRENSIE_CHECK_EQUAL( type_92, MonteCarlo::GAMMA__8N_REACTION );
  FRENSIE_CHECK_EQUAL( type_93, MonteCarlo::GAMMA__5N_P_REACTION );
  FRENSIE_CHECK_EQUAL( type_94, MonteCarlo::GAMMA__6N_P_REACTION );
  FRENSIE_CHECK_EQUAL( type_95, MonteCarlo::GAMMA__7N_P_REACTION );
  FRENSIE_CHECK_EQUAL( type_96, MonteCarlo::GAMMA__4N_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_97, MonteCarlo::GAMMA__5N_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_98, MonteCarlo::GAMMA__6N_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_99, MonteCarlo::GAMMA__7N_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_100, MonteCarlo::GAMMA__4N_D_REACTION );
  FRENSIE_CHECK_EQUAL( type_101, MonteCarlo::GAMMA__5N_D_REACTION );
  FRENSIE_CHECK_EQUAL( type_102, MonteCarlo::GAMMA__6N_D_REACTION );
  FRENSIE_CHECK_EQUAL( type_103, MonteCarlo::GAMMA__3N_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_104, MonteCarlo::GAMMA__4N_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_105, MonteCarlo::GAMMA__5N_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_106, MonteCarlo::GAMMA__6N_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_107, MonteCarlo::GAMMA__2N_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_108, MonteCarlo::GAMMA__3N_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_109, MonteCarlo::GAMMA__4N_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_110, MonteCarlo::GAMMA__3N_2P_REACTION );
  FRENSIE_CHECK_EQUAL( type_111, MonteCarlo::GAMMA__3N_2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_112, MonteCarlo::GAMMA__3N_P_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_113, MonteCarlo::GAMMA__D_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_114, MonteCarlo::GAMMA__N_P_D_REACTION );
  FRENSIE_CHECK_EQUAL( type_115, MonteCarlo::GAMMA__N_P_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_116, MonteCarlo::GAMMA__N_D_T_REACTION );
  FRENSIE_CHECK_EQUAL( type_117, MonteCarlo::GAMMA__N_P_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_118, MonteCarlo::GAMMA__N_D_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_119, MonteCarlo::GAMMA__N_T_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_120, MonteCarlo::GAMMA__N_T_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_121, MonteCarlo::GAMMA__2N_2P_REACTION );
  FRENSIE_CHECK_EQUAL( type_122, MonteCarlo::GAMMA__P_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_123, MonteCarlo::GAMMA__D_HE3_REACTION );
  FRENSIE_CHECK_EQUAL( type_124, MonteCarlo::GAMMA__HE3_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_125, MonteCarlo::GAMMA__4N_2P_REACTION );
  FRENSIE_CHECK_EQUAL( type_126, MonteCarlo::GAMMA__4N_2ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_127, MonteCarlo::GAMMA__4N_P_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_128, MonteCarlo::GAMMA__3P_REACTION );
  FRENSIE_CHECK_EQUAL( type_129, MonteCarlo::GAMMA__N_3P_REACTION );
  FRENSIE_CHECK_EQUAL( type_130, MonteCarlo::GAMMA__3N_2P_ALPHA_REACTION );
  FRENSIE_CHECK_EQUAL( type_131, MonteCarlo::GAMMA__5N_2P_REACTION );
  FRENSIE_CHECK_EQUAL( type_132, MonteCarlo::GAMMA__TOTAL_N_PRODUCTION );
  FRENSIE_CHECK_EQUAL( type_133, MonteCarlo::GAMMA__TOTAL_GAMMA_PRODUCTION );
  FRENSIE_CHECK_EQUAL( type_134, MonteCarlo::GAMMA__TOTAL_P_PRODUCTION );
  FRENSIE_CHECK_EQUAL( type_135, MonteCarlo::GAMMA__TOTAL_D_PRODUCTION );
  FRENSIE_CHECK_EQUAL( type_136, MonteCarlo::GAMMA__TOTAL_T_PRODUCTION );
  FRENSIE_CHECK_EQUAL( type_137, MonteCarlo::GAMMA__TOTAL_HE3_PRODUCTION );
  FRENSIE_CHECK_EQUAL( type_138, MonteCarlo::GAMMA__TOTAL_ALPHA_PRODUCTION );
  FRENSIE_CHECK_EQUAL( type_139, MonteCarlo::GAMMA__AVERAGE_HEATING );
  FRENSIE_CHECK_EQUAL( type_140, MonteCarlo::GAMMA__DAMAGE );
  FRENSIE_CHECK_EQUAL( type_141, MonteCarlo::GAMMA__P_EXCITED_STATE_0_REACTION );
  FRENSIE_CHECK_EQUAL( type_142, MonteCarlo::GAMMA__P_EXCITED_STATE_1_REACTION );
  FRENSIE_CHECK_EQUAL( type_143, MonteCarlo::GAMMA__P_EXCITED_STATE_2_REACTION );
  FRENSIE_CHECK_EQUAL( type_144, MonteCarlo::GAMMA__P_EXCITED_STATE_3_REACTION );
  FRENSIE_CHECK_EQUAL( type_145, MonteCarlo::GAMMA__P_EXCITED_STATE_4_REACTION );
  FRENSIE_CHECK_EQUAL( type_146, MonteCarlo::GAMMA__P_EXCITED_STATE_5_REACTION );
  FRENSIE_CHECK_EQUAL( type_147, MonteCarlo::GAMMA__P_EXCITED_STATE_6_REACTION );
  FRENSIE_CHECK_EQUAL( type_148, MonteCarlo::GAMMA__P_EXCITED_STATE_7_REACTION );
  FRENSIE_CHECK_EQUAL( type_149, MonteCarlo::GAMMA__P_EXCITED_STATE_8_REACTION );
  FRENSIE_CHECK_EQUAL( type_150, MonteCarlo::GAMMA__P_EXCITED_STATE_9_REACTION );
  FRENSIE_CHECK_EQUAL( type_151, MonteCarlo::GAMMA__P_EXCITED_STATE_10_REACTION );
  FRENSIE_CHECK_EQUAL( type_152, MonteCarlo::GAMMA__P_EXCITED_STATE_11_REACTION );
  FRENSIE_CHECK_EQUAL( type_153, MonteCarlo::GAMMA__P_EXCITED_STATE_12_REACTION );
  FRENSIE_CHECK_EQUAL( type_154, MonteCarlo::GAMMA__P_EXCITED_STATE_13_REACTION );
  FRENSIE_CHECK_EQUAL( type_155, MonteCarlo::GAMMA__P_EXCITED_STATE_14_REACTION );
  FRENSIE_CHECK_EQUAL( type_156, MonteCarlo::GAMMA__P_EXCITED_STATE_15_REACTION );
  FRENSIE_CHECK_EQUAL( type_157, MonteCarlo::GAMMA__P_EXCITED_STATE_16_REACTION );
  FRENSIE_CHECK_EQUAL( type_158, MonteCarlo::GAMMA__P_EXCITED_STATE_17_REACTION );
  FRENSIE_CHECK_EQUAL( type_159, MonteCarlo::GAMMA__P_EXCITED_STATE_18_REACTION );
  FRENSIE_CHECK_EQUAL( type_160, MonteCarlo::GAMMA__P_EXCITED_STATE_19_REACTION );
  FRENSIE_CHECK_EQUAL( type_161, MonteCarlo::GAMMA__P_EXCITED_STATE_20_REACTION );
  FRENSIE_CHECK_EQUAL( type_162, MonteCarlo::GAMMA__P_EXCITED_STATE_21_REACTION );
  FRENSIE_CHECK_EQUAL( type_163, MonteCarlo::GAMMA__P_EXCITED_STATE_22_REACTION );
  FRENSIE_CHECK_EQUAL( type_164, MonteCarlo::GAMMA__P_EXCITED_STATE_23_REACTION );
  FRENSIE_CHECK_EQUAL( type_165, MonteCarlo::GAMMA__P_EXCITED_STATE_24_REACTION );
  FRENSIE_CHECK_EQUAL( type_166, MonteCarlo::GAMMA__P_EXCITED_STATE_25_REACTION );
  FRENSIE_CHECK_EQUAL( type_167, MonteCarlo::GAMMA__P_EXCITED_STATE_26_REACTION );
  FRENSIE_CHECK_EQUAL( type_168, MonteCarlo::GAMMA__P_EXCITED_STATE_27_REACTION );
  FRENSIE_CHECK_EQUAL( type_169, MonteCarlo::GAMMA__P_EXCITED_STATE_28_REACTION );
  FRENSIE_CHECK_EQUAL( type_170, MonteCarlo::GAMMA__P_EXCITED_STATE_29_REACTION );
  FRENSIE_CHECK_EQUAL( type_171, MonteCarlo::GAMMA__P_EXCITED_STATE_30_REACTION );
  FRENSIE_CHECK_EQUAL( type_172, MonteCarlo::GAMMA__P_EXCITED_STATE_31_REACTION );
  FRENSIE_CHECK_EQUAL( type_173, MonteCarlo::GAMMA__P_EXCITED_STATE_32_REACTION );
  FRENSIE_CHECK_EQUAL( type_174, MonteCarlo::GAMMA__P_EXCITED_STATE_33_REACTION );
  FRENSIE_CHECK_EQUAL( type_175, MonteCarlo::GAMMA__P_EXCITED_STATE_34_REACTION );
  FRENSIE_CHECK_EQUAL( type_176, MonteCarlo::GAMMA__P_EXCITED_STATE_35_REACTION );
  FRENSIE_CHECK_EQUAL( type_177, MonteCarlo::GAMMA__P_EXCITED_STATE_36_REACTION );
  FRENSIE_CHECK_EQUAL( type_178, MonteCarlo::GAMMA__P_EXCITED_STATE_37_REACTION );
  FRENSIE_CHECK_EQUAL( type_179, MonteCarlo::GAMMA__P_EXCITED_STATE_38_REACTION );
  FRENSIE_CHECK_EQUAL( type_180, MonteCarlo::GAMMA__P_EXCITED_STATE_39_REACTION );
  FRENSIE_CHECK_EQUAL( type_181, MonteCarlo::GAMMA__P_EXCITED_STATE_40_REACTION );
  FRENSIE_CHECK_EQUAL( type_182, MonteCarlo::GAMMA__P_EXCITED_STATE_41_REACTION );
  FRENSIE_CHECK_EQUAL( type_183, MonteCarlo::GAMMA__P_EXCITED_STATE_42_REACTION );
  FRENSIE_CHECK_EQUAL( type_184, MonteCarlo::GAMMA__P_EXCITED_STATE_43_REACTION );
  FRENSIE_CHECK_EQUAL( type_185, MonteCarlo::GAMMA__P_EXCITED_STATE_44_REACTION );
  FRENSIE_CHECK_EQUAL( type_186, MonteCarlo::GAMMA__P_EXCITED_STATE_45_REACTION );
  FRENSIE_CHECK_EQUAL( type_187, MonteCarlo::GAMMA__P_EXCITED_STATE_46_REACTION );
  FRENSIE_CHECK_EQUAL( type_188, MonteCarlo::GAMMA__P_EXCITED_STATE_47_REACTION );
  FRENSIE_CHECK_EQUAL( type_189, MonteCarlo::GAMMA__P_EXCITED_STATE_48_REACTION );
  FRENSIE_CHECK_EQUAL( type_190, MonteCarlo::GAMMA__P_CONTINUUM_REACTION );
  FRENSIE_CHECK_EQUAL( type_191, MonteCarlo::GAMMA__D_EXCITED_STATE_0_REACTION );
  FRENSIE_CHECK_EQUAL( type_192, MonteCarlo::GAMMA__D_EXCITED_STATE_1_REACTION );
  FRENSIE_CHECK_EQUAL( type_193, MonteCarlo::GAMMA__D_EXCITED_STATE_2_REACTION );
  FRENSIE_CHECK_EQUAL( type_194, MonteCarlo::GAMMA__D_EXCITED_STATE_3_REACTION );
  FRENSIE_CHECK_EQUAL( type_195, MonteCarlo::GAMMA__D_EXCITED_STATE_4_REACTION );
  FRENSIE_CHECK_EQUAL( type_196, MonteCarlo::GAMMA__D_EXCITED_STATE_5_REACTION );
  FRENSIE_CHECK_EQUAL( type_197, MonteCarlo::GAMMA__D_EXCITED_STATE_6_REACTION );
  FRENSIE_CHECK_EQUAL( type_198, MonteCarlo::GAMMA__D_EXCITED_STATE_7_REACTION );
  FRENSIE_CHECK_EQUAL( type_199, MonteCarlo::GAMMA__D_EXCITED_STATE_8_REACTION );
  FRENSIE_CHECK_EQUAL( type_200, MonteCarlo::GAMMA__D_EXCITED_STATE_9_REACTION );
  FRENSIE_CHECK_EQUAL( type_201, MonteCarlo::GAMMA__D_EXCITED_STATE_10_REACTION );
  FRENSIE_CHECK_EQUAL( type_202, MonteCarlo::GAMMA__D_EXCITED_STATE_11_REACTION );
  FRENSIE_CHECK_EQUAL( type_203, MonteCarlo::GAMMA__D_EXCITED_STATE_12_REACTION );
  FRENSIE_CHECK_EQUAL( type_204, MonteCarlo::GAMMA__D_EXCITED_STATE_13_REACTION );
  FRENSIE_CHECK_EQUAL( type_205, MonteCarlo::GAMMA__D_EXCITED_STATE_14_REACTION );
  FRENSIE_CHECK_EQUAL( type_206, MonteCarlo::GAMMA__D_EXCITED_STATE_15_REACTION );
  FRENSIE_CHECK_EQUAL( type_207, MonteCarlo::GAMMA__D_EXCITED_STATE_16_REACTION );
  FRENSIE_CHECK_EQUAL( type_208, MonteCarlo::GAMMA__D_EXCITED_STATE_17_REACTION );
  FRENSIE_CHECK_EQUAL( type_209, MonteCarlo::GAMMA__D_EXCITED_STATE_18_REACTION );
  FRENSIE_CHECK_EQUAL( type_210, MonteCarlo::GAMMA__D_EXCITED_STATE_19_REACTION );
  FRENSIE_CHECK_EQUAL( type_211, MonteCarlo::GAMMA__D_EXCITED_STATE_20_REACTION );
  FRENSIE_CHECK_EQUAL( type_212, MonteCarlo::GAMMA__D_EXCITED_STATE_21_REACTION );
  FRENSIE_CHECK_EQUAL( type_213, MonteCarlo::GAMMA__D_EXCITED_STATE_22_REACTION );
  FRENSIE_CHECK_EQUAL( type_214, MonteCarlo::GAMMA__D_EXCITED_STATE_23_REACTION );
  FRENSIE_CHECK_EQUAL( type_215, MonteCarlo::GAMMA__D_EXCITED_STATE_24_REACTION );
  FRENSIE_CHECK_EQUAL( type_216, MonteCarlo::GAMMA__D_EXCITED_STATE_25_REACTION );
  FRENSIE_CHECK_EQUAL( type_217, MonteCarlo::GAMMA__D_EXCITED_STATE_26_REACTION );
  FRENSIE_CHECK_EQUAL( type_218, MonteCarlo::GAMMA__D_EXCITED_STATE_27_REACTION );
  FRENSIE_CHECK_EQUAL( type_219, MonteCarlo::GAMMA__D_EXCITED_STATE_28_REACTION );
  FRENSIE_CHECK_EQUAL( type_220, MonteCarlo::GAMMA__D_EXCITED_STATE_29_REACTION );
  FRENSIE_CHECK_EQUAL( type_221, MonteCarlo::GAMMA__D_EXCITED_STATE_30_REACTION );
  FRENSIE_CHECK_EQUAL( type_222, MonteCarlo::GAMMA__D_EXCITED_STATE_31_REACTION );
  FRENSIE_CHECK_EQUAL( type_223, MonteCarlo::GAMMA__D_EXCITED_STATE_32_REACTION );
  FRENSIE_CHECK_EQUAL( type_224, MonteCarlo::GAMMA__D_EXCITED_STATE_33_REACTION );
  FRENSIE_CHECK_EQUAL( type_225, MonteCarlo::GAMMA__D_EXCITED_STATE_34_REACTION );
  FRENSIE_CHECK_EQUAL( type_226, MonteCarlo::GAMMA__D_EXCITED_STATE_35_REACTION );
  FRENSIE_CHECK_EQUAL( type_227, MonteCarlo::GAMMA__D_EXCITED_STATE_36_REACTION );
  FRENSIE_CHECK_EQUAL( type_228, MonteCarlo::GAMMA__D_EXCITED_STATE_37_REACTION );
  FRENSIE_CHECK_EQUAL( type_229, MonteCarlo::GAMMA__D_EXCITED_STATE_38_REACTION );
  FRENSIE_CHECK_EQUAL( type_230, MonteCarlo::GAMMA__D_EXCITED_STATE_39_REACTION );
  FRENSIE_CHECK_EQUAL( type_231, MonteCarlo::GAMMA__D_EXCITED_STATE_40_REACTION );
  FRENSIE_CHECK_EQUAL( type_232, MonteCarlo::GAMMA__D_EXCITED_STATE_41_REACTION );
  FRENSIE_CHECK_EQUAL( type_233, MonteCarlo::GAMMA__D_EXCITED_STATE_42_REACTION );
  FRENSIE_CHECK_EQUAL( type_234, MonteCarlo::GAMMA__D_EXCITED_STATE_43_REACTION );
  FRENSIE_CHECK_EQUAL( type_235, MonteCarlo::GAMMA__D_EXCITED_STATE_44_REACTION );
  FRENSIE_CHECK_EQUAL( type_236, MonteCarlo::GAMMA__D_EXCITED_STATE_45_REACTION );
  FRENSIE_CHECK_EQUAL( type_237, MonteCarlo::GAMMA__D_EXCITED_STATE_46_REACTION );
  FRENSIE_CHECK_EQUAL( type_238, MonteCarlo::GAMMA__D_EXCITED_STATE_47_REACTION );
  FRENSIE_CHECK_EQUAL( type_239, MonteCarlo::GAMMA__D_EXCITED_STATE_48_REACTION );
  FRENSIE_CHECK_EQUAL( type_240, MonteCarlo::GAMMA__D_CONTINUUM_REACTION );
  FRENSIE_CHECK_EQUAL( type_241, MonteCarlo::GAMMA__T_EXCITED_STATE_0_REACTION );
  FRENSIE_CHECK_EQUAL( type_242, MonteCarlo::GAMMA__T_EXCITED_STATE_1_REACTION );
  FRENSIE_CHECK_EQUAL( type_243, MonteCarlo::GAMMA__T_EXCITED_STATE_2_REACTION );
  FRENSIE_CHECK_EQUAL( type_244, MonteCarlo::GAMMA__T_EXCITED_STATE_3_REACTION );
  FRENSIE_CHECK_EQUAL( type_245, MonteCarlo::GAMMA__T_EXCITED_STATE_4_REACTION );
  FRENSIE_CHECK_EQUAL( type_246, MonteCarlo::GAMMA__T_EXCITED_STATE_5_REACTION );
  FRENSIE_CHECK_EQUAL( type_247, MonteCarlo::GAMMA__T_EXCITED_STATE_6_REACTION );
  FRENSIE_CHECK_EQUAL( type_248, MonteCarlo::GAMMA__T_EXCITED_STATE_7_REACTION );
  FRENSIE_CHECK_EQUAL( type_249, MonteCarlo::GAMMA__T_EXCITED_STATE_8_REACTION );
  FRENSIE_CHECK_EQUAL( type_250, MonteCarlo::GAMMA__T_EXCITED_STATE_9_REACTION );
  FRENSIE_CHECK_EQUAL( type_251, MonteCarlo::GAMMA__T_EXCITED_STATE_10_REACTION );
  FRENSIE_CHECK_EQUAL( type_252, MonteCarlo::GAMMA__T_EXCITED_STATE_11_REACTION );
  FRENSIE_CHECK_EQUAL( type_253, MonteCarlo::GAMMA__T_EXCITED_STATE_12_REACTION );
  FRENSIE_CHECK_EQUAL( type_254, MonteCarlo::GAMMA__T_EXCITED_STATE_13_REACTION );
  FRENSIE_CHECK_EQUAL( type_255, MonteCarlo::GAMMA__T_EXCITED_STATE_14_REACTION );
  FRENSIE_CHECK_EQUAL( type_256, MonteCarlo::GAMMA__T_EXCITED_STATE_15_REACTION );
  FRENSIE_CHECK_EQUAL( type_257, MonteCarlo::GAMMA__T_EXCITED_STATE_16_REACTION );
  FRENSIE_CHECK_EQUAL( type_258, MonteCarlo::GAMMA__T_EXCITED_STATE_17_REACTION );
  FRENSIE_CHECK_EQUAL( type_259, MonteCarlo::GAMMA__T_EXCITED_STATE_18_REACTION );
  FRENSIE_CHECK_EQUAL( type_260, MonteCarlo::GAMMA__T_EXCITED_STATE_19_REACTION );
  FRENSIE_CHECK_EQUAL( type_261, MonteCarlo::GAMMA__T_EXCITED_STATE_20_REACTION );
  FRENSIE_CHECK_EQUAL( type_262, MonteCarlo::GAMMA__T_EXCITED_STATE_21_REACTION );
  FRENSIE_CHECK_EQUAL( type_263, MonteCarlo::GAMMA__T_EXCITED_STATE_22_REACTION );
  FRENSIE_CHECK_EQUAL( type_264, MonteCarlo::GAMMA__T_EXCITED_STATE_23_REACTION );
  FRENSIE_CHECK_EQUAL( type_265, MonteCarlo::GAMMA__T_EXCITED_STATE_24_REACTION );
  FRENSIE_CHECK_EQUAL( type_266, MonteCarlo::GAMMA__T_EXCITED_STATE_25_REACTION );
  FRENSIE_CHECK_EQUAL( type_267, MonteCarlo::GAMMA__T_EXCITED_STATE_26_REACTION );
  FRENSIE_CHECK_EQUAL( type_268, MonteCarlo::GAMMA__T_EXCITED_STATE_27_REACTION );
  FRENSIE_CHECK_EQUAL( type_269, MonteCarlo::GAMMA__T_EXCITED_STATE_28_REACTION );
  FRENSIE_CHECK_EQUAL( type_270, MonteCarlo::GAMMA__T_EXCITED_STATE_29_REACTION );
  FRENSIE_CHECK_EQUAL( type_271, MonteCarlo::GAMMA__T_EXCITED_STATE_30_REACTION );
  FRENSIE_CHECK_EQUAL( type_272, MonteCarlo::GAMMA__T_EXCITED_STATE_31_REACTION );
  FRENSIE_CHECK_EQUAL( type_273, MonteCarlo::GAMMA__T_EXCITED_STATE_32_REACTION );
  FRENSIE_CHECK_EQUAL( type_274, MonteCarlo::GAMMA__T_EXCITED_STATE_33_REACTION );
  FRENSIE_CHECK_EQUAL( type_275, MonteCarlo::GAMMA__T_EXCITED_STATE_34_REACTION );
  FRENSIE_CHECK_EQUAL( type_276, MonteCarlo::GAMMA__T_EXCITED_STATE_35_REACTION );
  FRENSIE_CHECK_EQUAL( type_277, MonteCarlo::GAMMA__T_EXCITED_STATE_36_REACTION );
  FRENSIE_CHECK_EQUAL( type_278, MonteCarlo::GAMMA__T_EXCITED_STATE_37_REACTION );
  FRENSIE_CHECK_EQUAL( type_279, MonteCarlo::GAMMA__T_EXCITED_STATE_38_REACTION );
  FRENSIE_CHECK_EQUAL( type_280, MonteCarlo::GAMMA__T_EXCITED_STATE_39_REACTION );
  FRENSIE_CHECK_EQUAL( type_281, MonteCarlo::GAMMA__T_EXCITED_STATE_40_REACTION );
  FRENSIE_CHECK_EQUAL( type_282, MonteCarlo::GAMMA__T_EXCITED_STATE_41_REACTION );
  FRENSIE_CHECK_EQUAL( type_283, MonteCarlo::GAMMA__T_EXCITED_STATE_42_REACTION );
  FRENSIE_CHECK_EQUAL( type_284, MonteCarlo::GAMMA__T_EXCITED_STATE_43_REACTION );
  FRENSIE_CHECK_EQUAL( type_285, MonteCarlo::GAMMA__T_EXCITED_STATE_44_REACTION );
  FRENSIE_CHECK_EQUAL( type_286, MonteCarlo::GAMMA__T_EXCITED_STATE_45_REACTION );
  FRENSIE_CHECK_EQUAL( type_287, MonteCarlo::GAMMA__T_EXCITED_STATE_46_REACTION );
  FRENSIE_CHECK_EQUAL( type_288, MonteCarlo::GAMMA__T_EXCITED_STATE_47_REACTION );
  FRENSIE_CHECK_EQUAL( type_289, MonteCarlo::GAMMA__T_EXCITED_STATE_48_REACTION );
  FRENSIE_CHECK_EQUAL( type_290, MonteCarlo::GAMMA__T_CONTINUUM_REACTION );
  FRENSIE_CHECK_EQUAL( type_291, MonteCarlo::GAMMA__HE3_EXCITED_STATE_0_REACTION );
  FRENSIE_CHECK_EQUAL( type_292, MonteCarlo::GAMMA__HE3_EXCITED_STATE_1_REACTION );
  FRENSIE_CHECK_EQUAL( type_293, MonteCarlo::GAMMA__HE3_EXCITED_STATE_2_REACTION );
  FRENSIE_CHECK_EQUAL( type_294, MonteCarlo::GAMMA__HE3_EXCITED_STATE_3_REACTION );
  FRENSIE_CHECK_EQUAL( type_295, MonteCarlo::GAMMA__HE3_EXCITED_STATE_4_REACTION );
  FRENSIE_CHECK_EQUAL( type_296, MonteCarlo::GAMMA__HE3_EXCITED_STATE_5_REACTION );
  FRENSIE_CHECK_EQUAL( type_297, MonteCarlo::GAMMA__HE3_EXCITED_STATE_6_REACTION );
  FRENSIE_CHECK_EQUAL( type_298, MonteCarlo::GAMMA__HE3_EXCITED_STATE_7_REACTION );
  FRENSIE_CHECK_EQUAL( type_299, MonteCarlo::GAMMA__HE3_EXCITED_STATE_8_REACTION );
  FRENSIE_CHECK_EQUAL( type_300, MonteCarlo::GAMMA__HE3_EXCITED_STATE_9_REACTION );
  FRENSIE_CHECK_EQUAL( type_301, MonteCarlo::GAMMA__HE3_EXCITED_STATE_10_REACTION );
  FRENSIE_CHECK_EQUAL( type_302, MonteCarlo::GAMMA__HE3_EXCITED_STATE_11_REACTION );
  FRENSIE_CHECK_EQUAL( type_303, MonteCarlo::GAMMA__HE3_EXCITED_STATE_12_REACTION );
  FRENSIE_CHECK_EQUAL( type_304, MonteCarlo::GAMMA__HE3_EXCITED_STATE_13_REACTION );
  FRENSIE_CHECK_EQUAL( type_305, MonteCarlo::GAMMA__HE3_EXCITED_STATE_14_REACTION );
  FRENSIE_CHECK_EQUAL( type_306, MonteCarlo::GAMMA__HE3_EXCITED_STATE_15_REACTION );
  FRENSIE_CHECK_EQUAL( type_307, MonteCarlo::GAMMA__HE3_EXCITED_STATE_16_REACTION );
  FRENSIE_CHECK_EQUAL( type_308, MonteCarlo::GAMMA__HE3_EXCITED_STATE_17_REACTION );
  FRENSIE_CHECK_EQUAL( type_309, MonteCarlo::GAMMA__HE3_EXCITED_STATE_18_REACTION );
  FRENSIE_CHECK_EQUAL( type_310, MonteCarlo::GAMMA__HE3_EXCITED_STATE_19_REACTION );
  FRENSIE_CHECK_EQUAL( type_311, MonteCarlo::GAMMA__HE3_EXCITED_STATE_20_REACTION );
  FRENSIE_CHECK_EQUAL( type_312, MonteCarlo::GAMMA__HE3_EXCITED_STATE_21_REACTION );
  FRENSIE_CHECK_EQUAL( type_313, MonteCarlo::GAMMA__HE3_EXCITED_STATE_22_REACTION );
  FRENSIE_CHECK_EQUAL( type_314, MonteCarlo::GAMMA__HE3_EXCITED_STATE_23_REACTION );
  FRENSIE_CHECK_EQUAL( type_315, MonteCarlo::GAMMA__HE3_EXCITED_STATE_24_REACTION );
  FRENSIE_CHECK_EQUAL( type_316, MonteCarlo::GAMMA__HE3_EXCITED_STATE_25_REACTION );
  FRENSIE_CHECK_EQUAL( type_317, MonteCarlo::GAMMA__HE3_EXCITED_STATE_26_REACTION );
  FRENSIE_CHECK_EQUAL( type_318, MonteCarlo::GAMMA__HE3_EXCITED_STATE_27_REACTION );
  FRENSIE_CHECK_EQUAL( type_319, MonteCarlo::GAMMA__HE3_EXCITED_STATE_28_REACTION );
  FRENSIE_CHECK_EQUAL( type_320, MonteCarlo::GAMMA__HE3_EXCITED_STATE_29_REACTION );
  FRENSIE_CHECK_EQUAL( type_321, MonteCarlo::GAMMA__HE3_EXCITED_STATE_30_REACTION );
  FRENSIE_CHECK_EQUAL( type_322, MonteCarlo::GAMMA__HE3_EXCITED_STATE_31_REACTION );
  FRENSIE_CHECK_EQUAL( type_323, MonteCarlo::GAMMA__HE3_EXCITED_STATE_32_REACTION );
  FRENSIE_CHECK_EQUAL( type_324, MonteCarlo::GAMMA__HE3_EXCITED_STATE_33_REACTION );
  FRENSIE_CHECK_EQUAL( type_325, MonteCarlo::GAMMA__HE3_EXCITED_STATE_34_REACTION );
  FRENSIE_CHECK_EQUAL( type_326, MonteCarlo::GAMMA__HE3_EXCITED_STATE_35_REACTION );
  FRENSIE_CHECK_EQUAL( type_327, MonteCarlo::GAMMA__HE3_EXCITED_STATE_36_REACTION );
  FRENSIE_CHECK_EQUAL( type_328, MonteCarlo::GAMMA__HE3_EXCITED_STATE_37_REACTION );
  FRENSIE_CHECK_EQUAL( type_329, MonteCarlo::GAMMA__HE3_EXCITED_STATE_38_REACTION );
  FRENSIE_CHECK_EQUAL( type_330, MonteCarlo::GAMMA__HE3_EXCITED_STATE_39_REACTION );
  FRENSIE_CHECK_EQUAL( type_331, MonteCarlo::GAMMA__HE3_EXCITED_STATE_40_REACTION );
  FRENSIE_CHECK_EQUAL( type_332, MonteCarlo::GAMMA__HE3_EXCITED_STATE_41_REACTION );
  FRENSIE_CHECK_EQUAL( type_333, MonteCarlo::GAMMA__HE3_EXCITED_STATE_42_REACTION );
  FRENSIE_CHECK_EQUAL( type_334, MonteCarlo::GAMMA__HE3_EXCITED_STATE_43_REACTION );
  FRENSIE_CHECK_EQUAL( type_335, MonteCarlo::GAMMA__HE3_EXCITED_STATE_44_REACTION );
  FRENSIE_CHECK_EQUAL( type_336, MonteCarlo::GAMMA__HE3_EXCITED_STATE_45_REACTION );
  FRENSIE_CHECK_EQUAL( type_337, MonteCarlo::GAMMA__HE3_EXCITED_STATE_46_REACTION );
  FRENSIE_CHECK_EQUAL( type_338, MonteCarlo::GAMMA__HE3_EXCITED_STATE_47_REACTION );
  FRENSIE_CHECK_EQUAL( type_339, MonteCarlo::GAMMA__HE3_EXCITED_STATE_48_REACTION );
  FRENSIE_CHECK_EQUAL( type_340, MonteCarlo::GAMMA__HE3_CONTINUUM_REACTION );
  FRENSIE_CHECK_EQUAL( type_341, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_0_REACTION );
  FRENSIE_CHECK_EQUAL( type_342, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_1_REACTION );
  FRENSIE_CHECK_EQUAL( type_343, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_2_REACTION );
  FRENSIE_CHECK_EQUAL( type_344, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_3_REACTION );
  FRENSIE_CHECK_EQUAL( type_345, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_4_REACTION );
  FRENSIE_CHECK_EQUAL( type_346, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_5_REACTION );
  FRENSIE_CHECK_EQUAL( type_347, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_6_REACTION );
  FRENSIE_CHECK_EQUAL( type_348, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_7_REACTION );
  FRENSIE_CHECK_EQUAL( type_349, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_8_REACTION );
  FRENSIE_CHECK_EQUAL( type_350, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_9_REACTION );
  FRENSIE_CHECK_EQUAL( type_351, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_10_REACTION );
  FRENSIE_CHECK_EQUAL( type_352, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_11_REACTION );
  FRENSIE_CHECK_EQUAL( type_353, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_12_REACTION );
  FRENSIE_CHECK_EQUAL( type_354, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_13_REACTION );
  FRENSIE_CHECK_EQUAL( type_355, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_14_REACTION );
  FRENSIE_CHECK_EQUAL( type_356, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_15_REACTION );
  FRENSIE_CHECK_EQUAL( type_357, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_16_REACTION );
  FRENSIE_CHECK_EQUAL( type_358, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_17_REACTION );
  FRENSIE_CHECK_EQUAL( type_359, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_18_REACTION );
  FRENSIE_CHECK_EQUAL( type_360, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_19_REACTION );
  FRENSIE_CHECK_EQUAL( type_361, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_20_REACTION );
  FRENSIE_CHECK_EQUAL( type_362, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_21_REACTION );
  FRENSIE_CHECK_EQUAL( type_363, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_22_REACTION );
  FRENSIE_CHECK_EQUAL( type_364, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_23_REACTION );
  FRENSIE_CHECK_EQUAL( type_365, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_24_REACTION );
  FRENSIE_CHECK_EQUAL( type_366, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_25_REACTION );
  FRENSIE_CHECK_EQUAL( type_367, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_26_REACTION );
  FRENSIE_CHECK_EQUAL( type_368, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_27_REACTION );
  FRENSIE_CHECK_EQUAL( type_369, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_28_REACTION );
  FRENSIE_CHECK_EQUAL( type_370, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_29_REACTION );
  FRENSIE_CHECK_EQUAL( type_371, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_30_REACTION );
  FRENSIE_CHECK_EQUAL( type_372, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_31_REACTION );
  FRENSIE_CHECK_EQUAL( type_373, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_32_REACTION );
  FRENSIE_CHECK_EQUAL( type_374, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_33_REACTION );
  FRENSIE_CHECK_EQUAL( type_375, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_34_REACTION );
  FRENSIE_CHECK_EQUAL( type_376, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_35_REACTION );
  FRENSIE_CHECK_EQUAL( type_377, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_36_REACTION );
  FRENSIE_CHECK_EQUAL( type_378, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_37_REACTION );
  FRENSIE_CHECK_EQUAL( type_379, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_38_REACTION );
  FRENSIE_CHECK_EQUAL( type_380, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_39_REACTION );
  FRENSIE_CHECK_EQUAL( type_381, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_40_REACTION );
  FRENSIE_CHECK_EQUAL( type_382, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_41_REACTION );
  FRENSIE_CHECK_EQUAL( type_383, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_42_REACTION );
  FRENSIE_CHECK_EQUAL( type_384, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_43_REACTION );
  FRENSIE_CHECK_EQUAL( type_385, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_44_REACTION );
  FRENSIE_CHECK_EQUAL( type_386, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_45_REACTION );
  FRENSIE_CHECK_EQUAL( type_387, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_46_REACTION );
  FRENSIE_CHECK_EQUAL( type_388, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_47_REACTION );
  FRENSIE_CHECK_EQUAL( type_389, MonteCarlo::GAMMA__ALPHA_EXCITED_STATE_48_REACTION );
  FRENSIE_CHECK_EQUAL( type_390, MonteCarlo::GAMMA__ALPHA_CONTINUUM_REACTION );
  FRENSIE_CHECK_EQUAL( type_391, MonteCarlo::GAMMA__2N_EXCITED_STATE_0_REACTION ); 
  FRENSIE_CHECK_EQUAL( type_392, MonteCarlo::GAMMA__2N_EXCITED_STATE_1_REACTION );
  FRENSIE_CHECK_EQUAL( type_393, MonteCarlo::GAMMA__2N_EXCITED_STATE_2_REACTION );
  FRENSIE_CHECK_EQUAL( type_394, MonteCarlo::GAMMA__2N_EXCITED_STATE_3_REACTION );
  FRENSIE_CHECK_EQUAL( type_395, MonteCarlo::GAMMA__2N_EXCITED_STATE_4_REACTION );
  FRENSIE_CHECK_EQUAL( type_396, MonteCarlo::GAMMA__2N_EXCITED_STATE_5_REACTION );
  FRENSIE_CHECK_EQUAL( type_397, MonteCarlo::GAMMA__2N_EXCITED_STATE_6_REACTION );
  FRENSIE_CHECK_EQUAL( type_398, MonteCarlo::GAMMA__2N_EXCITED_STATE_7_REACTION );
  FRENSIE_CHECK_EQUAL( type_399, MonteCarlo::GAMMA__2N_EXCITED_STATE_8_REACTION );
  FRENSIE_CHECK_EQUAL( type_400, MonteCarlo::GAMMA__2N_EXCITED_STATE_9_REACTION );
  FRENSIE_CHECK_EQUAL( type_401, MonteCarlo::GAMMA__2N_EXCITED_STATE_10_REACTION );
  FRENSIE_CHECK_EQUAL( type_402, MonteCarlo::GAMMA__2N_EXCITED_STATE_11_REACTION );
  FRENSIE_CHECK_EQUAL( type_403, MonteCarlo::GAMMA__2N_EXCITED_STATE_12_REACTION );
  FRENSIE_CHECK_EQUAL( type_404, MonteCarlo::GAMMA__2N_EXCITED_STATE_13_REACTION );
  FRENSIE_CHECK_EQUAL( type_405, MonteCarlo::GAMMA__2N_EXCITED_STATE_14_REACTION );
  FRENSIE_CHECK_EQUAL( type_406, MonteCarlo::GAMMA__2N_EXCITED_STATE_15_REACTION );
  FRENSIE_CHECK_EQUAL( type_407, MonteCarlo::GAMMA__2N_CONTINUUM_REACTION );
}

//---------------------------------------------------------------------------//
// end tstPhotonuclearReactionType.cpp
//---------------------------------------------------------------------------//
