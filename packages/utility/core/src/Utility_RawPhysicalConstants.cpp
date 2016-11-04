//---------------------------------------------------------------------------//
//!
//! \file   Utility_RawPhysicalConstants.cpp
//! \author Alex Robinson
//! \brief  Def. of class that stores a variety of physical constants.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_RawPhysicalConstants.hpp"

namespace Utility{

const double RawPhysicalConstants::pi = 3.14159265358979323846;
const double RawPhysicalConstants::speed_of_light = 29979245800;
const double RawPhysicalConstants::planck_constant = 4.13566751691e-21;
const double RawPhysicalConstants::h_bar = 6.5821192815e-22;
const double RawPhysicalConstants::avogadro_constant = 6.0221412927e23;
const double RawPhysicalConstants::electron_rest_mass_energy = 0.51099891013;
const double RawPhysicalConstants::neutron_rest_mass_energy = 939.56537821;
const double RawPhysicalConstants::neutron_rest_mass_amu = 1.0086649160043;
const double RawPhysicalConstants::classical_electron_radius = 2.8179403267e-13;
//! \todo update inverse fine structure constant and associated unit tests to newest version
const double RawPhysicalConstants::inverse_fine_structure_constant = 137.035999074;
const double RawPhysicalConstants::fine_structure_constant =
                                            1.0/inverse_fine_structure_constant;
const double RawPhysicalConstants::atomic_momentum = 1.992851882e-24;
const double RawPhysicalConstants::boltzmann_constant = 8.617332478e-11;

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_RawPhysicalConstants.cpp
//---------------------------------------------------------------------------//
