//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_NuclearReactionType.cpp
//! \author Alex Robinson
//! \brief  Nuclear reaction type helper function definitions.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>
#include <sstream>

// FRENSIE Includes
#include "Facemc_NuclearReactionType.hpp"

namespace Facemc{

// Convert an unsigned int to a NuclearReactionType
NuclearReactionType convertUnsignedToNuclearReactionType(
						      const unsigned reaction )
{
  switch( reaction )
  {
  case 1u: return N__TOTAL_REACTION;
  case 2u: return N__N_ELASTIC_REACTION;
  case 3u: return N__N_NON_ELASTIC_REACTION;
  case 4u: return N__N_INELASTIC_REACTION;
  case 11u: return N__2N_D_REACTION;
  case 16u: return N__2N_REACTION;
  case 17u: return N__3N_REACTION;
  case 18u: return N__TOTAL_FISSION_REACTION;
  case 19u: return N__FISSION_REACTION;
  case 20u: return N__N_FISSION_REACTION;
  case 21u: return N__2N_FISSION_REACTION;
  case 22u: return N__N_ALPHA_REACTION;
  case 23u: return N__N_3ALPHA_REACTION;
  case 24u: return N__2N_ALPHA_REACTION;
  case 25u: return N__3N_ALPHA_REACTION;
  case 27u: return N__TOTAL_ABSORPTION;
  case 28u: return N__N_P_REACTION;
  case 29u: return N__N_2ALPHA_REACTION;
  case 30u: return N__2N_2ALPHA_REACTION;
  case 32u: return N__N_D_REACTION;
  case 33u: return N__N_T_REACTION;
  case 34u: return N__N_HE3_REACTION;
  case 35u: return N__N_D_2ALPHA_REACTION;
  case 36u: return N__N_T_2ALPHA_REACTION;
  case 37u: return N__4N_REACTION;
  case 38u: return N__3N_FISSION_REACTION;
  case 41u: return N__2N_P_REACTION;
  case 42u: return N__3N_P_REACTION;
  case 44u: return N__N_2P_REACTION;
  case 45u: return N__N_P_ALPHA_REACTION;
  case 51u: return N__N_EXICTED_STATE_1_REACTION;
  case 52u: return N__N_EXCITED_STATE_2_REACTION;
  case 53u: return N__N_EXCITED_STATE_3_REACTION;
  case 54u: return N__N_EXCITED_STATE_4_REACTION;
  case 55u: return N__N_EXCITED_STATE_5_REACTION;
  case 56u: return N__N_EXCITED_STATE_6_REACTION;
  case 57u: return N__N_EXCITED_STATE_7_REACTION;
  case 58u: return N__N_EXCITED_STATE_8_REACTION;
  case 59u: return N__N_EXCITED_STATE_9_REACTION;
  case 60u: return N__N_EXCITED_STATE_10_REACTION;
  case 61u: return N__N_EXCITED_STATE_11_REACTION;
  case 62u: return N__N_EXCITED_STATE_12_REACTION;
  case 63u: return N__N_EXCITED_STATE_13_REACTION;
  case 64u: return N__N_EXCITED_STATE_14_REACTION;
  case 65u: return N__N_EXCITED_STATE_15_REACTION;
  case 66u: return N__N_EXCITED_STATE_16_REACTION;
  case 67u: return N__N_EXCITED_STATE_17_REACTION;
  case 68u: return N__N_EXCITED_STATE_18_REACTION;
  case 69u: return N__N_EXCITED_STATE_19_REACTION;
  case 70u: return N__N_EXCITED_STATE_20_REACTION;
  case 71u: return N__N_EXCITED_STATE_21_REACTION;
  case 72u: return N__N_EXCITED_STATE_22_REACTION;
  case 73u: return N__N_EXCITED_STATE_23_REACTION;
  case 74u: return N__N_EXCITED_STATE_24_REACTION;
  case 75u: return N__N_EXCITED_STATE_25_REACTION;
  case 76u: return N__N_EXCITED_STATE_26_REACTION;
  case 77u: return N__N_EXCITED_STATE_27_REACTION;
  case 78u: return N__N_EXCITED_STATE_28_REACTION;
  case 79u: return N__N_EXCITED_STATE_29_REACTION;
  case 80u: return N__N_EXCITED_STATE_30_REACTION;
  case 81u: return N__N_EXCITED_STATE_31_REACTION;
  case 82u: return N__N_EXCITED_STATE_32_REACTION;
  case 83u: return N__N_EXCITED_STATE_33_REACTION;
  case 84u: return N__N_EXCITED_STATE_34_REACTION;
  case 85u: return N__N_EXCITED_STATE_35_REACTION;
  case 86u: return N__N_EXCITED_STATE_36_REACTION;
  case 87u: return N__N_EXCITED_STATE_37_REACTION;
  case 88u: return N__N_EXCITED_STATE_38_REACTION;
  case 89u: return N__N_EXCITED_STATE_39_REACTION;
  case 90u: return N__N_EXCITED_STATE_40_REACTION;
  case 91u: return N__N_CONTINUUM_REACTION;
  case 101u: return N__CAPTURE_REACTION;
  case 102u: return N__GAMMA_REACTION;
  case 103u: return N__P_REACTION;
  case 104u: return N__D_REACTION;
  case 105u: return N__T_REACTION;
  case 106u: return N__HE3_REACTION;
  case 107u: return N__ALPHA_REACTION;
  case 108u: return N__2ALPHA_REACTION;
  case 109u: return N__3ALPHA_REACTION;
  case 111u: return N__2P_REACTION;
  case 112u: return N__P_ALPHA_REACTION;
  case 113u: return N__T_2ALPHA_REACTION;
  case 114u: return N__D_2ALPHA_REACTION;
  case 115u: return N__P_D_REACTION;
  case 116u: return N__P_T_REACTION;
  case 117u: return N__D_ALPHA_REACTION;
  case 152u: return N__5N_REACTION;
  case 153u: return N__6N_REACTION;
  case 154u: return N__2N_T_REACTION;
  case 155u: return N__T_ALPHA_REACTION;
  case 156u: return N__4N_P_REACTION;
  case 157u: return N__3N_D_REACTION;
  case 158u: return N__N_D_ALPHA_REACTION;
  case 159u: return N__2N_P_ALPHA_REACTION;
  case 160u: return N__7N_REACTION;
  case 161u: return N__8N_REACTION;
  case 162u: return N__5N_P_REACTION;
  case 163u: return N__6N_P_REACTION;
  case 164u: return N__7N_P_REACTION;
  case 165u: return N__4N_ALPHA_REACTION;
  case 166u: return N__5N_ALPHA_REACTION;
  case 167u: return N__6N_ALPHA_REACTION;
  case 168u: return N__7N_ALPHA_REACTION;
  case 169u: return N__4N_D_REACTION;
  case 170u: return N__5N_D_REACTION;
  case 171u: return N__6N_D_REACTION;
  case 172u: return N__3N_T_REACTION;
  case 173u: return N__4N_T_REACTION;
  case 174u: return N__5N_T_REACTION;
  case 175u: return N__6N_T_REACTION;
  case 176u: return N__2N_HE3_REACTION;
  case 177u: return N__3N_HE3_REACTION;
  case 178u: return N__4N_HE3_REACTION;
  case 179u: return N__3N_2P_REACTION;
  case 180u: return N__3N_2ALPHA_REACTION;
  case 181u: return N__3N_P_ALPHA_REACTION;
  case 182u: return N__D_T_REACTION;
  case 183u: return N__N_P_D_REACTION;
  case 184u: return N__N_P_T_REACTION;
  case 185u: return N__N_D_T_REACTION;
  case 186u: return N__N_P_HE3_REACTION;
  case 187u: return N__N_D_HE3_REACTION;
  case 188u: return N__N_T_HE3_REACTION;
  case 189u: return N__N_T_ALPHA_REACTION;
  case 190u: return N__2N_2P_REACTION;
  case 191u: return N__P_HE3_REACTION;
  case 192u: return N__D_HE3_REACTION;
  case 193u: return N__HE3_ALPHA_REACTION;
  case 194u: return N__4N_2P_REACTION;
  case 195u: return N__4N_2ALPHA_REACTION;
  case 196u: return N__4N_P_ALPHA_REACTION;
  case 197u: return N__3P_REACTION;
  case 198u: return N__N_3P_REACTION;
  case 199u: return N__3N_2P_ALPHA_REACTION;
  case 200u: return N__5N_2P_REACTION;
  case 201u: return N__TOTAL_N_PRODUCTION;
  case 202u: return N__TOTAL_GAMMA_PRODUCTION;
  case 203u: return N__TOTAL_P_PRODUCTION;
  case 204u: return N__TOTAL_D_PRODUCTION;
  case 205u: return N__TOTAL_T_PRODUCTION;
  case 206u: return N__TOTAL_HE3_PRODUCTION;
  case 207u: return N__TOTAL_ALPHA_PRODUCTION;
  case 301u: return N__AVERAGE_HEATING;
  case 444u: return N__DPA;
  default:
    std::stringstream ss;
    ss << "Error: ENDF reaction (MT #) " << reaction << " is unknown.";
    throw std::runtime_error( ss.str() );
  }
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_NuclearReactionType.cpp
//---------------------------------------------------------------------------//
