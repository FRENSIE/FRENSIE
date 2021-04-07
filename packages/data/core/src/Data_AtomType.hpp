//---------------------------------------------------------------------------//
//!
//! \file   Data_AtomType.hpp
//! \author Alex Robinson
//! \brief  Atom type enumeration and helper function declarations.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ATOM_TYPE_HPP
#define DATA_ATOM_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"

namespace Data{

/*! Atom identifiers
 * \details The mapped interger corresponds to the atomic numer
 */
enum AtomType{
  H_ATOM = 1,
  He_ATOM,
  Li_ATOM,
  Be_ATOM,
  B_ATOM,
  C_ATOM,
  N_ATOM,
  O_ATOM,
  F_ATOM,
  Ne_ATOM,
  Na_ATOM,
  Mg_ATOM,
  Al_ATOM,
  Si_ATOM,
  P_ATOM,
  S_ATOM,
  Cl_ATOM,
  Ar_ATOM,
  K_ATOM,
  Ca_ATOM,
  Sc_ATOM,
  Ti_ATOM,
  V_ATOM,
  Cr_ATOM,
  Mn_ATOM,
  Fe_ATOM,
  Co_ATOM,
  Ni_ATOM,
  Cu_ATOM,
  Zn_ATOM,
  Ga_ATOM,
  Ge_ATOM,
  As_ATOM,
  Se_ATOM,
  Br_ATOM,
  Kr_ATOM,
  Rb_ATOM,
  Sr_ATOM,
  Y_ATOM,
  Zr_ATOM,
  Nb_ATOM,
  Mo_ATOM,
  Tc_ATOM,
  Ru_ATOM,
  Rh_ATOM,
  Pd_ATOM,
  Ag_ATOM,
  Cd_ATOM,
  In_ATOM,
  Sn_ATOM,
  Sb_ATOM,
  Te_ATOM,
  I_ATOM,
  Xe_ATOM,
  Cs_ATOM,
  Ba_ATOM,
  La_ATOM,
  Ce_ATOM,
  Pr_ATOM,
  Nd_ATOM,
  Pm_ATOM,
  Sm_ATOM,
  Eu_ATOM,
  Gd_ATOM,
  Tb_ATOM,
  Dy_ATOM,
  Ho_ATOM,
  Er_ATOM,
  Tm_ATOM,
  Yb_ATOM,
  Lu_ATOM,
  Hf_ATOM,
  Ta_ATOM,
  W_ATOM,
  Re_ATOM,
  Os_ATOM,
  Ir_ATOM,
  Pt_ATOM,
  Au_ATOM,
  Hg_ATOM,
  Tl_ATOM,
  Pb_ATOM,
  Bi_ATOM,
  Po_ATOM,
  At_ATOM,
  Rn_ATOM,
  Fr_ATOM,
  Ra_ATOM,
  Ac_ATOM,
  Th_ATOM,
  Pa_ATOM,
  U_ATOM,
  Np_ATOM,
  Pu_ATOM,
  Am_ATOM,
  Cm_ATOM,
  Bk_ATOM,
  Cf_ATOM,
  Es_ATOM,
  Fm_ATOM
};

//! Convert an atomic number to an AtomType enumeration
AtomType convertAtomicNumberToAtomTypeEnum( const unsigned atomic_number );

} // end Data namespace

namespace Utility{

/*! Specialization of Utility::ToStringTraits for Data::AtomType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<Data::AtomType>
{
  //! Convert a Data::AtomType to a string
  static std::string toString( const Data::AtomType obj );

  //! Place the Data::AtomType in a stream
  static void toStream( std::ostream& os, const Data::AtomType obj );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing Data::AtomType enums
inline std::ostream& operator<<( std::ostream& os,
				 const Data::AtomType atom )
{
  Utility::toStream( os, atom );
  
  return os;
}

} // end std namespace

#endif // end DATA_ATOM_TYPE_HPP

//---------------------------------------------------------------------------//
// end Data_AtomType.hpp
//---------------------------------------------------------------------------//
