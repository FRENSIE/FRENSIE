//---------------------------------------------------------------------------//
//!
//! \file   Utility_PhyscialConstants.hpp
//! \author Alex Robinson
//! \brief  Decl. of class that stores a variety of physical constants
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PHYSICAL_CONSTANTS_HPP
#define UTILITY_PHYSICAL_CONSTANTS_HPP

namespace Utility{

//! Physical constants class
class PhysicalConstants
{

public:

  //! Pi
  static const double pi;

  //! The speed of light (cm/s)
  static const double speed_of_light;

  //! Planck's constant (MeV-s)
  static const double planck_constant;

  //! Planck's constant by pi (MeV-s)
  static const double h_bar;

  //! Avogadro constant (mol)
  static const double avogadro_constant;

  //! Rest mass energy of electron (MeV)
  static const double electron_rest_mass_energy;

  //! Rest mass energy of neutron (MeV)
  static const double neutron_rest_mass_energy;

  //! Rest mass of neutron (amu)
  static const double neutron_rest_mass_amu;

  //! The classical electron radius (cm)
  static const double classical_electron_radius;

  //! The inverse fine structure constant (unitless)
  static const double inverse_fine_structure_constant;
};

} // end Utility namespace

#endif // end UTILITY_PHYSICAL_CONSTANTS_HPP

//---------------------------------------------------------------------------//
// end Utility_PhysicalConstants.hpp
//---------------------------------------------------------------------------//
