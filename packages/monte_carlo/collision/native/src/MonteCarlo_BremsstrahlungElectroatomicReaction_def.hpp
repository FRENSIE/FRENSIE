//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung electroatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor with simple analytical photon angular distribution
template<typename InterpPolicy, bool processed_cross_section>
BremsstrahlungElectroatomicReaction<InterpPolicy,processed_cross_section>::BremsstrahlungElectroatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution& 
              bremsstrahlung_scattering_distribution )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
                                                       incoming_energy_grid,
                                                       cross_section,
                                                       threshold_energy_index ),
    d_scattering_distribution( bremsstrahlung_scattering_distribution )
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
  // Make sure the bremsstrahlung scattering distribution data is valid
  testPrecondition( bremsstrahlung_scattering_distribution.size() > 0 );
}


// Constructor with detailed photon angular distribution
template<typename InterpPolicy, bool processed_cross_section>
BremsstrahlungElectroatomicReaction<InterpPolicy,processed_cross_section>::BremsstrahlungElectroatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution& 
              bremsstrahlung_scattering_distribution,
       const Teuchos::RCP<Utility::OneDDistribution>& angular_distribution,
       const double lower_cutoff_energy,
       const double upper_cutoff_energy )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
                                                       incoming_energy_grid,
                                                       cross_section,
                                                       threshold_energy_index ),
    d_scattering_distribution( bremsstrahlung_scattering_distribution,
                               angular_distribution,
                               lower_cutoff_energy,
                               upper_cutoff_energy )
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
  // Make sure the bremsstrahlung scattering distribution data is valid
  testPrecondition( bremsstrahlung_scattering_distribution.size() > 0 );
  // Make sure the angular distribution data is valid
  testPrecondition( !angular_distribution.is_null() );
  // Make sure the cuttoff energies data is valid
  testPrecondition( lower_cutoff_energy > 0 );
  testPrecondition( upper_cutoff_energy > 0 );
}

// Return the number of photons emitted from the rxn at the given energy
/*! \details This does not include photons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned BremsstrahlungElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
    return 1u;
  else
    return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned BremsstrahlungElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
ElectroatomicReactionType BremsstrahlungElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return BREMSSTRAHLUNG_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void BremsstrahlungElectroatomicReaction<InterpPolicy,processed_cross_section>::react( 
				     ElectronState& electron, 
				     ParticleBank& bank,
				     unsigned& shell_of_interaction ) const
{
  d_scattering_distribution.scatterElectron( electron, 
                                             bank, 
                                             shell_of_interaction);
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
