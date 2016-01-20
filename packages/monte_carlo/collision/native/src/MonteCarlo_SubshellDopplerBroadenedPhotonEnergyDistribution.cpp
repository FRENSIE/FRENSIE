//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.cpp
//! \author Alex Robinson
//! \brief  The subshell Doppler broadened photon energy distribution decl.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
SubshellDopplerBroadenedPhotonEnergyDistribution::SubshellDopplerBroadenedPhotonEnergyDistribution(
		                       const SubshellType interaction_subshell,
                                       const double subshell_occupancy,
                                       const double subshell_binding_energy )
  : d_interaction_subshell( interaction_subshell ),
    d_subshell_occupancy( subshell_occupancy ),
    d_subshell_binding_energy( subshell_binding_energy )
{
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != INVALID_SUBSHELL &&
                    interaction_subshell != UNKNOWN_SUBSHELL );
  // Make sure the subshell occupancy is valid
  testPrecondition( subshell_occupancy > 0.0 );
  // Make sure the subshell binding energy is valid
  testPrecondition( subshell_binding_energy > 0.0 );
}

// Check if the distribution is complete (all subshells)
bool SubshellDopplerBroadenedPhotonEnergyDistribution::isComplete() const
{
  return false;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
