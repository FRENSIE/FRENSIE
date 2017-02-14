//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The electroatom native factory class template definition.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_ELECTRON_PROPERTIES_DEF_HPP
#define MONTE_CARLO_SIMULATION_ELECTRON_PROPERTIES_DEF_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomNativeFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a electroatom core (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * core. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been
 * requested, a electroionization reaction for each subshell will be created.
 * Otherwize a single total electroionization reaction will be created.
 */
template <typename SecondInterpPolicy>
void ElectroatomNativeFactory::createElectroatomCore(
        const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
        const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
        const SimulationElectronProperties& properties,
        Teuchos::RCP<ElectroatomCore>& electroatom_core )
{
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );

  electroatom_core.reset( new ElectroatomCore() );

  Electroatom::ReactionMap scattering_reactions, absorption_reactions;

  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
                      raw_electroatom_data.getElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher for this atom
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                              energy_grid,
                              properties.getNumberOfElectronHashGridBins() ) );

  // Create the elastic scattering reaction
  if ( properties.isElasticModeOn() )
  {
    // Create the analog elastic scattering reaction (no moment preserving elastic scattering)
    if ( properties.getElasticCutoffAngleCosine() == 1.0 )
    {
      Electroatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[ANALOG_ELASTIC_ELECTROATOMIC_REACTION];

      ElectroatomicReactionNativeFactory::createAnalogElasticReaction(
                       raw_electroatom_data,
                       energy_grid,
                       grid_searcher,
                       reaction_pointer,
                       properties.isLinLinLogInterpolationModeOn() );
    }
    // Create the moment preserving elastic scattering reaction (no analog elastic scattering)
    else if ( properties.getElasticCutoffAngleCosine() == -1.0 )
    {
      Electroatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION];

      ElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<SecondInterpPolicy>(
                       raw_electroatom_data,
                       energy_grid,
                       grid_searcher,
                       reaction_pointer,
                       properties.getElasticCutoffAngleCosine() );
    }
    // Create the hybrid elastic scattering reaction (if cutoff is within range)
    else
    {
      Electroatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[HYBRID_ELASTIC_ELECTROATOMIC_REACTION];

      ElectroatomicReactionNativeFactory::createHybridElasticReaction(
                       raw_electroatom_data,
                       energy_grid,
                       grid_searcher,
                       reaction_pointer,
                       properties.getElasticCutoffAngleCosine(),
                       properties.isLinLinLogInterpolationModeOn() );
    }
  }

  // Create the bremsstrahlung scattering reaction
  if ( properties.isBremsstrahlungModeOn() )
  {
    Electroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[BREMSSTRAHLUNG_ELECTROATOMIC_REACTION];

    ElectroatomicReactionNativeFactory::createBremsstrahlungReaction<ElectroatomicReaction, SecondInterpPolicy>(
                    raw_electroatom_data,
                    energy_grid,
                    grid_searcher,
                    reaction_pointer,
                    properties.getBremsstrahlungAngularDistributionFunction(),
                    properties.isWeightedInterpolationModeOn() );
  }

  // Create the atomic excitation scattering reaction
  if ( properties.isAtomicExcitationModeOn() )
  {
    Electroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[ATOMIC_EXCITATION_ELECTROATOMIC_REACTION];

    ElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
                               raw_electroatom_data,
                               energy_grid,
                               grid_searcher,
                               reaction_pointer );
  }

  // Create the subshell electroionization reactions
  if ( properties.isElectroionizationModeOn() )
  {
  std::vector<std::shared_ptr<ElectroatomicReaction> > reaction_pointers;

  ElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<ElectroatomicReaction, SecondInterpPolicy>(
                               raw_electroatom_data,
                               energy_grid,
                               grid_searcher,
                               reaction_pointers,
                               properties.isWeightedInterpolationModeOn() );

    for( unsigned i = 0; i < reaction_pointers.size(); ++i )
    {
      scattering_reactions[reaction_pointers[i]->getReactionType()] =
        reaction_pointers[i];
    }
  }

  // Create the electroatom core
  electroatom_core.reset( new ElectroatomCore( energy_grid,
                                               scattering_reactions,
                                               absorption_reactions,
                                               atomic_relaxation_model,
                                               false,
                                               Utility::LinLin() ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROATOM_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomNativeFactory_def.hpp
//---------------------------------------------------------------------------//
