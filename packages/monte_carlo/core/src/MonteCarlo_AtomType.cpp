//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomType.cpp
//! \author Alex Robinson
//! \brief  Atom type helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AtomType.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Convert an atomic number to an AtomType enumeration
AtomType convertAtomicNumberToAtomTypeEnum( const unsigned atomic_number )
{
  switch( atomic_number )
  {
  case 1: return H_ATOM;
  case 2: return He_ATOM;
  case 3: return Li_ATOM;
  case 4: return Be_ATOM;
  case 5: return B_ATOM;
  case 6: return C_ATOM;
  case 7: return N_ATOM;
  case 8: return O_ATOM;
  case 9: return F_ATOM;
  case 10: return Ne_ATOM;
  case 11: return Na_ATOM;
  case 12: return Mg_ATOM;
  case 13: return Al_ATOM;
  case 14: return Si_ATOM;
  case 15: return P_ATOM;
  case 16: return S_ATOM;
  case 17: return Cl_ATOM;
  case 18: return Ar_ATOM;
  case 19: return K_ATOM;
  case 20: return Ca_ATOM;
  case 21: return Sc_ATOM;
  case 22: return Ti_ATOM;
  case 23: return V_ATOM;
  case 24: return Cr_ATOM;
  case 25: return Mn_ATOM;
  case 26: return Fe_ATOM;
  case 27: return Co_ATOM;
  case 28: return Ni_ATOM;
  case 29: return Cu_ATOM;
  case 30: return Zn_ATOM;
  case 31: return Ga_ATOM;
  case 32: return Ge_ATOM;
  case 33: return As_ATOM;
  case 34: return Se_ATOM;
  case 35: return Br_ATOM;
  case 36: return Kr_ATOM;
  case 37: return Rb_ATOM;
  case 38: return Sr_ATOM;
  case 39: return Y_ATOM;
  case 40: return Zr_ATOM;
  case 41: return Nb_ATOM;
  case 42: return Mo_ATOM;
  case 43: return Tc_ATOM;
  case 44: return Ru_ATOM;
  case 45: return Rh_ATOM;
  case 46: return Pd_ATOM;
  case 47: return Ag_ATOM;
  case 48: return Cd_ATOM;
  case 49: return In_ATOM;
  case 50: return Sn_ATOM;
  case 51: return Sb_ATOM;
  case 52: return Te_ATOM;
  case 53: return I_ATOM;
  case 54: return Xe_ATOM;
  case 55: return Cs_ATOM;
  case 56: return Ba_ATOM;
  case 57: return La_ATOM;
  case 58: return Ce_ATOM;
  case 59: return Pr_ATOM;
  case 60: return Nd_ATOM;
  case 61: return Pm_ATOM;
  case 62: return Sm_ATOM;
  case 63: return Eu_ATOM;
  case 64: return Gd_ATOM;
  case 65: return Tb_ATOM;
  case 66: return Dy_ATOM;
  case 67: return Ho_ATOM;
  case 68: return Er_ATOM;
  case 69: return Tm_ATOM;
  case 70: return Yb_ATOM;
  case 71: return Lu_ATOM;
  case 72: return Hf_ATOM;
  case 73: return Ta_ATOM;
  case 74: return W_ATOM;
  case 75: return Re_ATOM;
  case 76: return Os_ATOM;
  case 77: return Ir_ATOM;
  case 78: return Pt_ATOM;
  case 79: return Au_ATOM;
  case 80: return Hg_ATOM;
  case 81: return Tl_ATOM;
  case 82: return Pb_ATOM;
  case 83: return Bi_ATOM;
  case 84: return Po_ATOM;
  case 85: return At_ATOM;
  case 86: return Rn_ATOM;
  case 87: return Fr_ATOM;
  case 88: return Ra_ATOM;
  case 89: return Ac_ATOM;
  case 90: return Th_ATOM;
  case 91: return Pa_ATOM;
  case 92: return U_ATOM;
  case 93: return Np_ATOM;
  case 94: return Pu_ATOM;
  case 95: return Am_ATOM;
  case 96: return Cm_ATOM;
  case 97: return Bk_ATOM;
  case 98: return Cf_ATOM;
  case 99: return Es_ATOM;
  case 100: return Fm_ATOM;
  default:
    THROW_EXCEPTION( std::runtime_error,
		     "Error: atomic number " << atomic_number <<
		     "is not valid!" );
  }
}

// Convert an AtomType enumeration to a string
std::string convertAtomTypeEnumToString( const AtomType atom )
{
  switch( atom )
  {
  case H_ATOM: return "H";
  case He_ATOM: return "He";
  case Li_ATOM: return "Li";
  case Be_ATOM: return "Be";
  case B_ATOM: return "B";
  case C_ATOM: return "C";
  case N_ATOM: return "N";
  case O_ATOM: return "O";
  case F_ATOM: return "F";
  case Ne_ATOM: return "Ne";
  case Na_ATOM: return "Na";
  case Mg_ATOM: return "Mg";
  case Al_ATOM: return "Al";
  case Si_ATOM: return "Si";
  case P_ATOM: return "P";
  case S_ATOM: return "S";
  case Cl_ATOM: return "Cl";
  case Ar_ATOM: return "Ar";
  case K_ATOM: return "K";
  case Ca_ATOM: return "Ca";
  case Sc_ATOM: return "Sc";
  case Ti_ATOM: return "Ti";
  case V_ATOM: return "V";
  case Cr_ATOM: return "Cr";
  case Mn_ATOM: return "Mn";
  case Fe_ATOM: return "Fe";
  case Co_ATOM: return "Co";
  case Ni_ATOM: return "Ni";
  case Cu_ATOM: return "Cu";
  case Zn_ATOM: return "Zn";
  case Ga_ATOM: return "Ga";
  case Ge_ATOM: return "Ge";
  case As_ATOM: return "As";
  case Se_ATOM: return "Se";
  case Br_ATOM: return "Br";
  case Kr_ATOM: return "Kr";
  case Rb_ATOM: return "Rb";
  case Sr_ATOM: return "Sr";
  case Y_ATOM: return "Y";
  case Zr_ATOM: return "Zr";
  case Nb_ATOM: return "Nb";
  case Mo_ATOM: return "Mo";
  case Tc_ATOM: return "Tc";
  case Ru_ATOM: return "Ru";
  case Rh_ATOM: return "Rh";
  case Pd_ATOM: return "Pd";
  case Ag_ATOM: return "Ag";
  case Cd_ATOM: return "Cd";
  case In_ATOM: return "In";
  case Sn_ATOM: return "Sn";
  case Sb_ATOM: return "Sb";
  case Te_ATOM: return "Te";
  case I_ATOM: return "I";
  case Xe_ATOM: return "Xe";
  case Cs_ATOM: return "Cs";
  case Ba_ATOM: return "Ba";
  case La_ATOM: return "La";
  case Ce_ATOM: return "Ce";
  case Pr_ATOM: return "Pr";
  case Nd_ATOM: return "Nd";
  case Pm_ATOM: return "Pm";
  case Sm_ATOM: return "Sm";
  case Eu_ATOM: return "Eu";
  case Gd_ATOM: return "Gd";
  case Tb_ATOM: return "Tb";
  case Dy_ATOM: return "Dy";
  case Ho_ATOM: return "Ho";
  case Er_ATOM: return "Er";
  case Tm_ATOM: return "Tm";
  case Yb_ATOM: return "Yb";
  case Lu_ATOM: return "Lu";
  case Hf_ATOM: return "Hf";
  case Ta_ATOM: return "Ta";
  case W_ATOM: return "W";
  case Re_ATOM: return "Re";
  case Os_ATOM: return "Os";
  case Ir_ATOM: return "Ir";
  case Pt_ATOM: return "Pt";
  case Au_ATOM: return "Au";
  case Hg_ATOM: return "Hg";
  case Tl_ATOM: return "Tl";
  case Pb_ATOM: return "Pb";
  case Bi_ATOM: return "Bi";
  case Po_ATOM: return "Po";
  case At_ATOM: return "At";
  case Rn_ATOM: return "Rn";
  case Fr_ATOM: return "Fr";
  case Ra_ATOM: return "Ra";
  case Ac_ATOM: return "Ac";
  case Th_ATOM: return "Th";
  case Pa_ATOM: return "Pa";
  case U_ATOM: return "U";
  case Np_ATOM: return "Np";
  case Pu_ATOM: return "Pu";
  case Am_ATOM: return "Am";
  case Cm_ATOM: return "Cm";
  case Bk_ATOM: return "Bk";
  case Cf_ATOM: return "Cf";
  case Es_ATOM: return "Es";
  case Fm_ATOM: return "Fm";
  defalut:
    THROW_EXCEPTION( std::logic_error,
		     "Error: encountered an atom without an associated "
		     "string!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomType.cpp
//---------------------------------------------------------------------------//
