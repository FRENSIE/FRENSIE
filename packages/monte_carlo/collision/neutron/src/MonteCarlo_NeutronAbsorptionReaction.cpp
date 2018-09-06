//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronAbsorptionReaction.cpp
//! \author Alex Robinson
//! \brief  The neutron absorption reaction class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NeutronAbsorptionReaction.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Return the number of neutrons emitted from the rxn at the given energy
unsigned NeutronAbsorptionReaction::getNumberOfEmittedParticles(
						    const double energy ) const
{
  return 0u;
}

// Simulate the reaction
void NeutronAbsorptionReaction::react( NeutronState& neutron,
				       ParticleBank& bank ) const
{
  neutron.setAsGone();
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronAbsorptionReaction.cpp
//---------------------------------------------------------------------------//
