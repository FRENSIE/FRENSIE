//---------------------------------------------------------------------------//
//!
//! \file   Utility_PhysicalConstants.cpp
//! \author Alex Robinson
//! \brief  Def. of class that stores a variety of physical constants w/units
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_PhysicalConstants.hpp"

namespace Utility{

// The speed of light (cm/s)
const boost::units::quantity<boost::units::cgs::velocity> PhysicalConstants::speed_of_light_q =
  Utility::RawPhysicalConstants::speed_of_light*
  boost::units::cgs::centimeter/boost::units::cgs::second;

// Planck's constant (MeV-s)
const boost::units::quantity<PhysicalConstants::MeVSecond> PhysicalConstants::planck_constant_q =
  Utility::RawPhysicalConstants::planck_constant*
  Units::MeV*boost::units::cgs::second;

// Plank's constant by pi (MeV-s)
const boost::units::quantity<PhysicalConstants::MeVSecond> PhysicalConstants::h_bar_q =
  Utility::RawPhysicalConstants::h_bar*
  Units::MeV*boost::units::cgs::second;

// Rest mass energy of electron (MeV)
const boost::units::quantity<Units::MegaElectronVolt> PhysicalConstants::electron_rest_mass_energy_q =
  Utility::RawPhysicalConstants::electron_rest_mass_energy*Units::MeV;

// Rest mass energy of neutron (MeV)
const boost::units::quantity<Units::MegaElectronVolt> PhysicalConstants::neutron_rest_mass_energy_q =
  Utility::RawPhysicalConstants::neutron_rest_mass_energy*Units::MeV;

// The rest mass of neutron (amu)
const boost::units::quantity<Units::AtomicMass> PhysicalConstants::neutron_rest_mass_amu_q =
  Utility::RawPhysicalConstants::neutron_rest_mass_amu*Units::amu;

// The classical electron radius (cm)
const boost::units::quantity<boost::units::cgs::length> PhysicalConstants::classical_electron_radius_q =
  Utility::RawPhysicalConstants::classical_electron_radius*
  boost::units::cgs::centimeter;

// The boltzmann constant (MeV/K)
const boost::units::quantity<PhysicalConstants::MeVPerK> PhysicalConstants::boltzmann_constant_q =
  Utility::RawPhysicalConstants::boltzmann_constant*
  Units::MeV/boost::units::si::kelvin;

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_PhysicalConstants.cpp
//---------------------------------------------------------------------------//
