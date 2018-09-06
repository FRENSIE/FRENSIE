//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardSubshellDopplerBroadenedPhotonEnergyDistribution.cpp
//! \author Alex Robinson
//! \brief  The standard subshell Doppler broadened photon energy distribution
//!         instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_StandardSubshellDopplerBroadenedPhotonEnergyDistribution.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( StandardSubshellDopplerBroadenedPhotonEnergyDistribution<FullComptonProfilePolicy> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardSubshellDopplerBroadenedPhotonEnergyDistribution<HalfComptonProfilePolicy> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardSubshellDopplerBroadenedPhotonEnergyDistribution<DoubledHalfComptonProfilePolicy> );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardSubshellDopplerBroadenedPhotonEnergyDistribution.cpp
//---------------------------------------------------------------------------//
