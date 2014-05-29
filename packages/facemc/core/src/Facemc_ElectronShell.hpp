//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ElectronShells.hpp
//! \author Alex Robinson
//! \brief  Electron shell enumeration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_EADL_SHELL_HPP
#define FACEMC_EADL_SHELL_HPP

namespace Facemc{

//! Electron shell identifiers
enum ElectronShell{
  EADLShell_MIN = 0,
  INVALID_SHELL = EADLShell_MIN,
  K_SHELL,
  L_SHELL,
  L1_SHELL,
  L23_SHELL,
  L2_SHELL,
  L3_SHELL,
  M_SHELL,
  M1_SHELL,
  M23_SHELL,
  M2_SHELL,
  M3_SHELL,
  M45_SHELL,
  M4_SHELL,
  M5_SHELL,
  N_SHELL,
  N1_SHELL,
  N23_SHELL,
  N2_SHELL,
  N3_SHELL,
  N45_SHELL,
  N4_SHELL,
  N5_SHELL,
  N67_SHELL,
  N6_SHELL,
  N7_SHELL,
  O_SHELL,
  O1_SHELL,
  O23_SHELL,
  O2_SHELL,
  O3_SHELL,
  O45_SHELL,
  O4_SHELL,
  O5_SHELL,
  O67_SHELL,
  O6_SHELL,
  O7_SHELL,
  O89_SHELL,
  O8_SHELL,
  O9_SHELL,
  P_SHELL,
  P1_SHELL,
  P23_SHELL,
  P2_SHELL,
  P3_SHELL,
  P45_SHELL,
  P4_SHELL,
  P5_SHELL,
  P67_SHELL,
  P6_SHELL,
  P7_SHELL,
  P89_SHELL,
  P8_SHELL,
  P9_SHELL,
  P1011_SHELL,
  P10_SHELL,
  P11_SHELL,
  Q_SHELL,
  Q1_SHELL,
  Q23_SHELL,
  Q2_SHELL,
  Q3_SHELL,
  EADLShell_MAX = Q3_SHELL
};
  
} // end Facemc namespace

#endif // end Facemc_ELECTRON_SHELL_HPP

//---------------------------------------------------------------------------//
// end Facemc_ElectronShell.hpp
//---------------------------------------------------------------------------//

