//---------------------------------------------------------------------------//
//!
//! \file   Data_AtomType.cpp
//! \author Alex Robinson
//! \brief  Atom type helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_AtomType.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

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
		     "Atomic number " << atomic_number <<
		     " is not valid!" );
  }
}

} // end Data namespace

namespace Utility{

// Convert an AtomType enumeration to a string
  std::string ToStringTraits<Data::AtomType>::toString(
                                                    const Data::AtomType atom )
{
  switch( atom )
  {
  case Data::H_ATOM:  return "H";
  case Data::He_ATOM: return "He";
  case Data::Li_ATOM: return "Li";
  case Data::Be_ATOM: return "Be";
  case Data::B_ATOM:  return "B";
  case Data::C_ATOM:  return "C";
  case Data::N_ATOM:  return "N";
  case Data::O_ATOM:  return "O";
  case Data::F_ATOM:  return "F";
  case Data::Ne_ATOM: return "Ne";
  case Data::Na_ATOM: return "Na";
  case Data::Mg_ATOM: return "Mg";
  case Data::Al_ATOM: return "Al";
  case Data::Si_ATOM: return "Si";
  case Data::P_ATOM:  return "P";
  case Data::S_ATOM:  return "S";
  case Data::Cl_ATOM: return "Cl";
  case Data::Ar_ATOM: return "Ar";
  case Data::K_ATOM:  return "K";
  case Data::Ca_ATOM: return "Ca";
  case Data::Sc_ATOM: return "Sc";
  case Data::Ti_ATOM: return "Ti";
  case Data::V_ATOM:  return "V";
  case Data::Cr_ATOM: return "Cr";
  case Data::Mn_ATOM: return "Mn";
  case Data::Fe_ATOM: return "Fe";
  case Data::Co_ATOM: return "Co";
  case Data::Ni_ATOM: return "Ni";
  case Data::Cu_ATOM: return "Cu";
  case Data::Zn_ATOM: return "Zn";
  case Data::Ga_ATOM: return "Ga";
  case Data::Ge_ATOM: return "Ge";
  case Data::As_ATOM: return "As";
  case Data::Se_ATOM: return "Se";
  case Data::Br_ATOM: return "Br";
  case Data::Kr_ATOM: return "Kr";
  case Data::Rb_ATOM: return "Rb";
  case Data::Sr_ATOM: return "Sr";
  case Data::Y_ATOM:  return "Y";
  case Data::Zr_ATOM: return "Zr";
  case Data::Nb_ATOM: return "Nb";
  case Data::Mo_ATOM: return "Mo";
  case Data::Tc_ATOM: return "Tc";
  case Data::Ru_ATOM: return "Ru";
  case Data::Rh_ATOM: return "Rh";
  case Data::Pd_ATOM: return "Pd";
  case Data::Ag_ATOM: return "Ag";
  case Data::Cd_ATOM: return "Cd";
  case Data::In_ATOM: return "In";
  case Data::Sn_ATOM: return "Sn";
  case Data::Sb_ATOM: return "Sb";
  case Data::Te_ATOM: return "Te";
  case Data::I_ATOM:  return "I";
  case Data::Xe_ATOM: return "Xe";
  case Data::Cs_ATOM: return "Cs";
  case Data::Ba_ATOM: return "Ba";
  case Data::La_ATOM: return "La";
  case Data::Ce_ATOM: return "Ce";
  case Data::Pr_ATOM: return "Pr";
  case Data::Nd_ATOM: return "Nd";
  case Data::Pm_ATOM: return "Pm";
  case Data::Sm_ATOM: return "Sm";
  case Data::Eu_ATOM: return "Eu";
  case Data::Gd_ATOM: return "Gd";
  case Data::Tb_ATOM: return "Tb";
  case Data::Dy_ATOM: return "Dy";
  case Data::Ho_ATOM: return "Ho";
  case Data::Er_ATOM: return "Er";
  case Data::Tm_ATOM: return "Tm";
  case Data::Yb_ATOM: return "Yb";
  case Data::Lu_ATOM: return "Lu";
  case Data::Hf_ATOM: return "Hf";
  case Data::Ta_ATOM: return "Ta";
  case Data::W_ATOM:  return "W";
  case Data::Re_ATOM: return "Re";
  case Data::Os_ATOM: return "Os";
  case Data::Ir_ATOM: return "Ir";
  case Data::Pt_ATOM: return "Pt";
  case Data::Au_ATOM: return "Au";
  case Data::Hg_ATOM: return "Hg";
  case Data::Tl_ATOM: return "Tl";
  case Data::Pb_ATOM: return "Pb";
  case Data::Bi_ATOM: return "Bi";
  case Data::Po_ATOM: return "Po";
  case Data::At_ATOM: return "At";
  case Data::Rn_ATOM: return "Rn";
  case Data::Fr_ATOM: return "Fr";
  case Data::Ra_ATOM: return "Ra";
  case Data::Ac_ATOM: return "Ac";
  case Data::Th_ATOM: return "Th";
  case Data::Pa_ATOM: return "Pa";
  case Data::U_ATOM:  return "U";
  case Data::Np_ATOM: return "Np";
  case Data::Pu_ATOM: return "Pu";
  case Data::Am_ATOM: return "Am";
  case Data::Cm_ATOM: return "Cm";
  case Data::Bk_ATOM: return "Bk";
  case Data::Cf_ATOM: return "Cf";
  case Data::Es_ATOM: return "Es";
  case Data::Fm_ATOM: return "Fm";
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Encountered an AtomType without an associated "
		     "string!" );
  }
}

// Place the Data::AtomType in a stream
void ToStringTraits<Data::AtomType>::toStream( std::ostream& os,
                                               const Data::AtomType atom )
{
  os << ToStringTraits<Data::AtomType>::toString( atom );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Data_AtomType.cpp
//---------------------------------------------------------------------------//
