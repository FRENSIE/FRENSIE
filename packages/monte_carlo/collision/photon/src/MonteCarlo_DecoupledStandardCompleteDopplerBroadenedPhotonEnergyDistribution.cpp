//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//! \author Alex Robinson
//! \brief  The decoupled complete Doppler broadened photon energy dist. inst.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<FullComptonProfilePolicy> );
EXPLICIT_TEMPLATE_CLASS_INST( DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<HalfComptonProfilePolicy> );
EXPLICIT_TEMPLATE_CLASS_INST( DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<DoubledHalfComptonProfilePolicy> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//---------------------------------------------------------------------------//
