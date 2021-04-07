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

constexpr double RawPhysicalConstants::pi;
constexpr double RawPhysicalConstants::speed_of_light;
constexpr double RawPhysicalConstants::planck_constant;
constexpr double RawPhysicalConstants::h_bar;
constexpr double RawPhysicalConstants::avogadro_constant;
constexpr double RawPhysicalConstants::electron_rest_mass_energy;
constexpr double RawPhysicalConstants::neutron_rest_mass_energy;
constexpr double RawPhysicalConstants::neutron_rest_mass_amu;
constexpr double RawPhysicalConstants::classical_electron_radius;
//! \todo update inverse fine structure constant and associated unit tests to newest version
constexpr double RawPhysicalConstants::inverse_fine_structure_constant;
constexpr double RawPhysicalConstants::fine_structure_constant;
const double RawPhysicalConstants::atomic_momentum;
const double RawPhysicalConstants::boltzmann_constant;

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_RawPhysicalConstants.cpp
//---------------------------------------------------------------------------//
