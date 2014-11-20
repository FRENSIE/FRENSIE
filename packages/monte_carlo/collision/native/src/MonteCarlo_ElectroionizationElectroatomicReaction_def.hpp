//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The electroionization electroatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_ELECTROIONIZATION_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor 
template<typename InterpPolicy, bool processed_cross_section>
ElectroionizationElectroatomicReaction<InterpPolicy,processed_cross_section>::ElectroionizationElectroatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const Teuchos::RCP<Utility::OneDDistribution>& 
               electroionization_subshell_cross_sections,
       const ElectroionizationElectronScatteringDistribution::ElectroionizationDistribution& 
               electroionization_scattering_distribution )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
                                                       incoming_energy_grid,
                                                       cross_section,
                                                       threshold_energy_index ),
    d_scattering_distribution( electroionization_subshell_cross_sections,
                               electroionization_scattering_distribution )
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
  // Make sure the electroionization subshell cross sections data is valid
  testPrecondition( !electroionization_subshell_cross_sections.is_null() );
  // Make sure the electroionization scattering distribution data is valid
  testPrecondition( electroionization_scattering_distribution.size() > 0 );
}

// Return the number of photons emitted from the rxn at the given energy
/*! \details This does not include photons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned ElectroionizationElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned ElectroionizationElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
    return 1u;
  else
    return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
ElectroatomicReactionType ElectroionizationElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return ELECTROIONIZATION_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void ElectroionizationElectroatomicReaction<InterpPolicy,processed_cross_section>::react( 
				     ElectronState& electron, 
				     ParticleBank& bank,
				     unsigned& shell_of_interaction ) const
{
  d_scattering_distribution.scatterElectron( electron, 
                                             bank, 
                                             shell_of_interaction);
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
