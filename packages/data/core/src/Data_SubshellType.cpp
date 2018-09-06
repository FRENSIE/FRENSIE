//---------------------------------------------------------------------------//
//!
//! \file   Data_SubshellType.cpp
//! \author Alex Robinson
//! \brief  Electron subshell helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_SubshellType.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

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


// Convert an EADL designator to an ENDF designator
unsigned convertEADLDesignatorToENDFDesignator(
               const unsigned eadl_designator )
{
  switch( eadl_designator )
  {
  case 1: return 1;
  case 3: return 2;
  case 5: return 3;
  case 6: return 4;
  case 8: return 5;
  case 10: return 6;
  case 11: return 7;
  case 13: return 8;
  case 14: return 9;
  case 16: return 10;
  case 18: return 11;
  case 19: return 12;
  case 21: return 13;
  case 22: return 14;
  case 24: return 15;
  case 25: return 16;
  case 27: return 17;
  case 29: return 18;
  case 30: return 19;
  case 32: return 20;
  case 33: return 21;
  case 35: return 22;
  case 36: return 23;
  case 38: return 24;
  case 39: return 25;
  case 41: return 26;
  case 43: return 27;
  case 44: return 28;
  case 46: return 29;
  case 47: return 30;
  case 49: return 31;
  case 50: return 32;
  case 52: return 33;
  case 53: return 34;
  case 55: return 35;
  case 56: return 36;
  case 58: return 37;
  case 60: return 38;
  case 61: return 39;
  default:
    THROW_EXCEPTION( std::logic_error,
                     "The EADL subshell designator is invalid!" );
  }
}

} // end Data namespace

namespace Utility{

// Convert a Data::SubshellType to a string
std::string ToStringTraits<Data::SubshellType>::toString(
                                            const Data::SubshellType subshell )
{
  switch( subshell )
  {
  case Data::K_SUBSHELL: return "K";
  case Data::L1_SUBSHELL: return "L1";
  case Data::L2_SUBSHELL: return "L2";
  case Data::L3_SUBSHELL: return "L3";
  case Data::M1_SUBSHELL: return "M1";
  case Data::M2_SUBSHELL: return "M2";
  case Data::M3_SUBSHELL: return "M3";
  case Data::M4_SUBSHELL: return "M4";
  case Data::M5_SUBSHELL: return "M5";
  case Data::N1_SUBSHELL: return "N1";
  case Data::N2_SUBSHELL: return "N2";
  case Data::N3_SUBSHELL: return "N3";
  case Data::N4_SUBSHELL: return "N4";
  case Data::N5_SUBSHELL: return "N5";
  case Data::N6_SUBSHELL: return "N6";
  case Data::N7_SUBSHELL: return "N7";
  case Data::O1_SUBSHELL: return "O1";
  case Data::O2_SUBSHELL: return "O2";
  case Data::O3_SUBSHELL: return "O3";
  case Data::O4_SUBSHELL: return "O4";
  case Data::O5_SUBSHELL: return "O5";
  case Data::O6_SUBSHELL: return "O6";
  case Data::O7_SUBSHELL: return "O7";
  case Data::O8_SUBSHELL: return "O8";
  case Data::O9_SUBSHELL: return "O9";
  case Data::P1_SUBSHELL: return "P1";
  case Data::P2_SUBSHELL: return "P2";
  case Data::P3_SUBSHELL: return "P3";
  case Data::P4_SUBSHELL: return "P4";
  case Data::P5_SUBSHELL: return "P5";
  case Data::P6_SUBSHELL: return "P6";
  case Data::P7_SUBSHELL: return "P7";
  case Data::P8_SUBSHELL: return "P8";
  case Data::P9_SUBSHELL: return "P9";
  case Data::P10_SUBSHELL: return "P10";
  case Data::P11_SUBSHELL: return "P11";
  case Data::Q1_SUBSHELL: return "Q1";
  case Data::Q2_SUBSHELL: return "Q2";
  case Data::Q3_SUBSHELL: return "Q3";
  case Data::UNKNOWN_SUBSHELL: return "Unknown";
  case Data::INVALID_SUBSHELL: return "Invalid";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "The requested subshell type is not supported! " );
  }
}

// Place the Data::SubshellType in a stream
void ToStringTraits<Data::SubshellType>::toStream(
                               std::ostream& os, const Data::SubshellType obj )
{
  os << ToStringTraits<Data::SubshellType>::toString( obj );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Data_Subshell.cpp
//---------------------------------------------------------------------------//
