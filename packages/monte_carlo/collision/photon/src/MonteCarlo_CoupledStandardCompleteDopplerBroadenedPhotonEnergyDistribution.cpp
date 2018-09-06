//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//! \author Alex Robinson
//! \brief  The coupled complete Doppler broadened photon energy dist. inst.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<FullComptonProfilePolicy> );
EXPLICIT_TEMPLATE_CLASS_INST( CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<HalfComptonProfilePolicy> );
EXPLICIT_TEMPLATE_CLASS_INST( CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution<DoubledHalfComptonProfilePolicy> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.cpp
//---------------------------------------------------------------------------//
