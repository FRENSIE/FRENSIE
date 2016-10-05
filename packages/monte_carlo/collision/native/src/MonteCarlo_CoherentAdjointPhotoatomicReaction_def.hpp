//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentAdjointPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The coherent adjoint photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_ADJOINT_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_COHERENT_ADJOINT_PHOTOATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
CoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::CoherentAdjointPhotoatomicReaction(
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const unsigned threshold_energy_index,
		   const std::shared_ptr<const CoherentScatteringDistribution>&
		   scattering_distribution )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
    d_scattering_distribution( scattering_distribution )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() > 0 );
  testPrecondition( cross_section.size() ==
		    incoming_energy_grid.size() - threshold_energy_index );
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid.size() );
  // Make sure the form factor is valid
  testPrecondition( scattering_distribution.get() );
}

// Return the number of adjoint photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned CoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() && energy <= this->getMaxEnergy() )
    return 1u;
  else
    return 0u;
}

// Return the number of adjoint electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned CoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
AdjointPhotoatomicReactionType CoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return COHERENT_ADJOINT_PHOTOATOMIC_REACTION;
}
  
// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void CoherentAdjointPhotoatomicReaction<InterpPolicy,processed_cross_section>::react(
                               AdjointPhotonState& adjoint_photon,
                               ParticleBank& bank,
                               Data::SubshellType& shell_of_interaction ) const
{
  d_scattering_distribution->scatterAdjointPhoton( adjoint_photon,
                                                   bank,
                                                   shell_of_interaction );

  adjoint_photon.incrementCollisionNumber();

  shell_of_interaction = Data::UNKNOWN_SUBSHELL;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COHERENT_ADJOINT_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentAdjointPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
