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

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
BremsstrahlungElectroatomicReaction<InterpPolicy,processed_cross_section>::BremsstrahlungElectroatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
              bremsstrahlung_distribution )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
                                                       incoming_energy_grid,
                                                       cross_section,
                                                       threshold_energy_index ),
    d_bremsstrahlung_distribution( bremsstrahlung_distribution )
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
  testPrecondition( bremsstrahlung_distribution.use_count() > 0 );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
BremsstrahlungElectroatomicReaction<InterpPolicy,processed_cross_section>::BremsstrahlungElectroatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       const std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
              bremsstrahlung_distribution )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
                incoming_energy_grid,
                cross_section,
                threshold_energy_index,
                grid_searcher ),
    d_bremsstrahlung_distribution( bremsstrahlung_distribution )
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
  testPrecondition( bremsstrahlung_distribution.use_count() > 0 );
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

// Return the differential cross section
template<typename InterpPolicy, bool processed_cross_section>
double BremsstrahlungElectroatomicReaction<InterpPolicy,processed_cross_section>::getDifferentialCrossSection(
    const double incoming_energy,
    const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy >= 0.0 );
  testPrecondition( outgoing_energy <= incoming_energy );

  if ( !this->isEnergyWithinEnergyGrid( incoming_energy ) )
    return 0.0;

  double outgoing_photon_energy = incoming_energy - outgoing_energy;

  // If the photon energy is less than the tables min photon energy return 0
  if ( outgoing_photon_energy < 1e-7 )
    return 0.0; 

  double cross_section = this->getCrossSection( incoming_energy );

  // Evaluate the PDF at a given incoming and outgoing energy
  double pdf =
    d_bremsstrahlung_distribution->evaluatePDF( incoming_energy,
                                                outgoing_photon_energy );

  return cross_section*pdf;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void BremsstrahlungElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
				     ElectronState& electron,
				     ParticleBank& bank,
				     Data::SubshellType& shell_of_interaction ) const
{
  d_bremsstrahlung_distribution->scatterElectron( electron,
                                                  bank,
                                                  shell_of_interaction);

  electron.incrementCollisionNumber();

  // The shell of interaction is currently ignored
  shell_of_interaction =Data::UNKNOWN_SUBSHELL;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
