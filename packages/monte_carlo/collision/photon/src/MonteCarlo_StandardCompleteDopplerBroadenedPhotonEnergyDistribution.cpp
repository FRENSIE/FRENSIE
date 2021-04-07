//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//! \author Alex Robinson
//! \brief  The complete Doppler broadened photon energy distribution inst.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_StandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( StandardCompleteDopplerBroadenedPhotonEnergyDistribution<FullComptonProfilePolicy> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardCompleteDopplerBroadenedPhotonEnergyDistribution<HalfComptonProfilePolicy> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardCompleteDopplerBroadenedPhotonEnergyDistribution<DoubledHalfComptonProfilePolicy> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//---------------------------------------------------------------------------//
