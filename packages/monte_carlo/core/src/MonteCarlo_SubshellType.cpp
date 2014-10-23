//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellType.cpp
//! \author Alex Robinson
//! \brief  Electron subshell helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SubshellType.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Convert an ENDF designator to a Subshell enumeration
SubshellType convertENDFDesignatorToSubshellEnum( 
					       const unsigned endf_designator )
{
  switch( endf_designator )
  {
  case 1: return K_SUBSHELL;
  case 2: return L1_SUBSHELL;
  case 3: return L2_SUBSHELL;
  case 4: return L3_SUBSHELL;
  case 5: return M1_SUBSHELL;
  case 6: return M2_SUBSHELL;
  case 7: return M3_SUBSHELL;
  case 8: return M4_SUBSHELL;
  case 9: return M5_SUBSHELL;
  case 10: return N1_SUBSHELL;
  case 11: return N2_SUBSHELL;
  case 12: return N3_SUBSHELL;
  case 13: return N4_SUBSHELL;
  case 14: return N5_SUBSHELL;
  case 15: return N6_SUBSHELL;
  case 16: return N7_SUBSHELL;
  case 17: return O1_SUBSHELL;
  case 18: return O2_SUBSHELL;
  case 19: return O3_SUBSHELL;
  case 20: return O4_SUBSHELL;
  case 21: return O5_SUBSHELL;
  case 22: return O6_SUBSHELL;
  case 23: return O7_SUBSHELL;
  case 24: return O8_SUBSHELL;
  case 25: return O9_SUBSHELL;
  case 26: return P1_SUBSHELL;
  case 27: return P2_SUBSHELL;
  case 28: return P3_SUBSHELL;
  case 29: return P4_SUBSHELL;
  case 30: return P5_SUBSHELL;
  case 31: return P6_SUBSHELL;
  case 32: return P7_SUBSHELL;
  case 33: return P8_SUBSHELL;
  case 34: return P9_SUBSHELL;
  case 35: return P10_SUBSHELL;
  case 36: return P11_SUBSHELL;
  case 37: return Q1_SUBSHELL;
  case 38: return Q2_SUBSHELL;
  case 39: return Q3_SUBSHELL;
  default: return INVALID_SUBSHELL;
  }
}

// Convert an EADL designator to a Subshell enumeration
SubshellType convertEADLDesignatorToSubshellEnum( 
					       const unsigned eadl_designator )
{
  switch( eadl_designator )
  {
  case 1: return K_SUBSHELL;
  case 3: return L1_SUBSHELL;
  case 5: return L2_SUBSHELL;
  case 6: return L3_SUBSHELL;
  case 8: return M1_SUBSHELL;
  case 10: return M2_SUBSHELL;
  case 11: return M3_SUBSHELL;
  case 13: return M4_SUBSHELL;
  case 14: return M5_SUBSHELL;
  case 16: return N1_SUBSHELL;
  case 18: return N2_SUBSHELL;
  case 19: return N3_SUBSHELL;
  case 21: return N4_SUBSHELL;
  case 22: return N5_SUBSHELL;
  case 24: return N6_SUBSHELL;
  case 25: return N7_SUBSHELL;
  case 27: return O1_SUBSHELL;
  case 29: return O2_SUBSHELL;
  case 30: return O3_SUBSHELL;
  case 32: return O4_SUBSHELL;
  case 33: return O5_SUBSHELL;
  case 35: return O6_SUBSHELL;
  case 36: return O7_SUBSHELL;
  case 38: return O8_SUBSHELL;
  case 39: return O9_SUBSHELL;
  case 41: return P1_SUBSHELL;
  case 43: return P2_SUBSHELL;
  case 44: return P3_SUBSHELL;
  case 46: return P4_SUBSHELL;
  case 47: return P5_SUBSHELL;
  case 49: return P6_SUBSHELL;
  case 50: return P7_SUBSHELL;
  case 52: return P8_SUBSHELL;
  case 53: return P9_SUBSHELL;
  case 55: return P10_SUBSHELL;
  case 56: return P11_SUBSHELL;
  case 58: return Q1_SUBSHELL;
  case 60: return Q2_SUBSHELL;
  case 61: return Q3_SUBSHELL;
  default: return INVALID_SUBSHELL;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_Subshell.cpp
//---------------------------------------------------------------------------//

