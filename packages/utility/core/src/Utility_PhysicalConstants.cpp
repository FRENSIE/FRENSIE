//---------------------------------------------------------------------------//
//!
//! \file   Utility_PhysicalConstants.cpp
//! \author Alex Robinson
//! \brief  Def. of class that stores a variety of physical constants.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_PhysicalConstants.hpp"

namespace Utility{

const double PhysicalConstants::pi = 3.14159265358979323846;
const double PhysicalConstants::speed_of_light = 29979245800;
const double PhysicalConstants::planck_constant = 4.13566751691e-21;
const double PhysicalConstants::h_bar = 6.5821192815e-22;
const double PhysicalConstants::avogadro_constant = 6.0221412927e23;
const double PhysicalConstants::electron_rest_mass_energy = 0.51099891013;
const double PhysicalConstants::neutron_rest_mass_energy = 939.56537821;
const double PhysicalConstants::neutron_rest_mass_amu = 1.0086649160043;
const double PhysicalConstants::classical_electron_radius = 2.8179403267e-13;
//! \todo update inverse fine structure constant and associated unit tests to newest version
const double PhysicalConstants::inverse_fine_structure_constant = 137.035999074;
const double PhysicalConstants::fine_structure_constant = 
                                            1.0/inverse_fine_structure_constant;
const double PhysicalConstants::boltzmann_constant = 8.617332478e-11;

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_PhysicalConstants.cpp
//---------------------------------------------------------------------------//
