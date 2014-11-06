//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The atomic excitation electroatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_EXCITATION_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_ATOMIC_EXCITATION_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
AtomicExcitationElectroatomicReaction<InterpPolicy,processed_cross_section>::AtomicExcitationElectroatomicReaction(
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const unsigned threshold_energy_index)
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
						          incoming_energy_grid,
						          cross_section,
						          threshold_energy_index )
{

}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AtomicExcitationElectroatomicReaction<InterpPolicy,processed_cross_section>::
           getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void AtomicExcitationElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
						     ElectronState& photon,
						     ParticleBank& bank ) const
{
  // Make sure it is energetically possible for this reaction to occur
  testPrecondition( electron.getEnergy() >= this->getThresholdEnergy() );
/* \todo Finish Atomic Excitation Reaction Def
  // Scatter Electron
  electron.setEnergy( electron.getEnergy() - energy_loss );
*/
  // Increment the original electron generation number
  electron.incrementCollisionNumber();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_EXCITATION_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
