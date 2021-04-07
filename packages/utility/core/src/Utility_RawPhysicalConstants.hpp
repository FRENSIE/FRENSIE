//---------------------------------------------------------------------------//
//!
//! \file   Utility_RawPhysicalConstants.hpp
//! \author Alex Robinson
//! \brief  Decl. of class that stores a variety of physical constants
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_RAW_PHYSICAL_CONSTANTS_HPP
#define UTILITY_RAW_PHYSICAL_CONSTANTS_HPP

namespace Utility{

//! The raw physical constants class
class RawPhysicalConstants
{

public:

  //! Pi
  static constexpr double pi = 3.14159265358979323846;

  //! The speed of light (cm/s)
  static constexpr double speed_of_light = 29979245800;

  //! Planck's constant (MeV-s)
  static constexpr double planck_constant = 4.13566751691e-21;

  //! Planck's constant by pi (MeV-s)
  static constexpr double h_bar = 6.5821192815e-22;

  //! Avogadro constant (atom/mol)
  static constexpr double avogadro_constant = 6.0221412927e23;

  //! Rest mass energy of electron (MeV)
  static constexpr double electron_rest_mass_energy = 0.51099891013;

  //! Rest mass energy of neutron (MeV)
  static constexpr double neutron_rest_mass_energy = 939.56537821;

  //! Rest mass of neutron (amu)
  static constexpr double neutron_rest_mass_amu = 1.0086649160043;

  //! The classical electron radius (cm)
  static constexpr double classical_electron_radius = 2.8179403267e-13;

  //! The inverse fine structure constant (unitless)
  static constexpr double inverse_fine_structure_constant = 137.035999074;

  //! The fine structure constant (unitless)
  static constexpr double fine_structure_constant = 1.0/inverse_fine_structure_constant;

  //! The atomic momentum (kg-m/s)
  static constexpr double atomic_momentum = 1.992851882e-24;

  //! The boltzmann constant (MeV/K)
  static constexpr double boltzmann_constant = 8.617332478e-11;
};

} // end Utility namespace

#endif // end UTILITY_RAW_PHYSICAL_CONSTANTS_HPP

//---------------------------------------------------------------------------//
// end Utility_RawPhysicalConstants.hpp
//---------------------------------------------------------------------------//
