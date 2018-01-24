//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronatomACEFactory.hpp
//! \author Luke Kersting
//! \brief  The positron-atom ace factory class definition.
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PositronatomACEFactory.hpp"
#include "MonteCarlo_PositronatomicReactionACEFactory.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a positron-atom core (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * core. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been
 * requested, a electroionization reaction for each subshell will be created.
 * Otherwise a single total electroionization reaction will be created.
 */
void PositronatomACEFactory::createPositronatomCore(
    const Data::XSSEPRDataExtractor& raw_positronatom_data,
    const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
    const SimulationElectronProperties& properties,
    Teuchos::RCP<PositronatomCore>& positronatom_core )
{
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );

  positronatom_core.reset( new PositronatomCore() );

  Positronatom::ReactionMap scattering_reactions, absorption_reactions;

  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( raw_positronatom_data.extractElectronEnergyGrid() );

  // Create a hash based energy grid searcher
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                      energy_grid,
                      properties.getNumberOfElectronHashGridBins() ) );

  // Create the elastic scattering reaction
  if ( properties.isElasticModeOn() ) // Create the decoupled elastic scattering reaction
  {
    // Check the ACE file version
    if( raw_positronatom_data.isEPRVersion14() )
    {
      Positronatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION];

      PositronatomicReactionACEFactory::createDecoupledElasticReaction(
        raw_positronatom_data,
        energy_grid,
        grid_searcher,
        reaction_pointer );
    }
    else // Create the cutoff elastic scattering reaction
    {
      Positronatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[CUTOFF_ELASTIC_POSITRONATOMIC_REACTION];

      PositronatomicReactionACEFactory::createCutoffElasticReaction(
        raw_positronatom_data,
        energy_grid,
        grid_searcher,
        reaction_pointer );
    }
  }

  // Create the bremsstrahlung scattering reaction
  if ( properties.isBremsstrahlungModeOn() )
  {
    Positronatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[BREMSSTRAHLUNG_POSITRONATOMIC_REACTION];

    PositronatomicReactionACEFactory::createBremsstrahlungReaction(
        raw_positronatom_data,
        energy_grid,
        grid_searcher,
        reaction_pointer,
        properties.getBremsstrahlungAngularDistributionFunction(),
        properties.getMinElectronEnergy() );
  }

  // Create the atomic excitation scattering reaction
  if ( properties.isAtomicExcitationModeOn() )
  {
    Positronatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[ATOMIC_EXCITATION_POSITRONATOMIC_REACTION];

    PositronatomicReactionACEFactory::createAtomicExcitationReaction(
        raw_positronatom_data,
        energy_grid,
        grid_searcher,
        reaction_pointer,
        properties.getMinElectronEnergy() );
  }

  // Create the subshell electroionization reaction(s)
  if ( properties.isElectroionizationModeOn() )
  {
    std::vector<std::shared_ptr<PositronatomicReaction> > reaction_pointers;

    PositronatomicReactionACEFactory::createSubshellPositronionizationReactions(
        raw_positronatom_data,
        energy_grid,
        grid_searcher,
        reaction_pointers,
        properties.getMinElectronEnergy() );

    for( unsigned i = 0u; i < reaction_pointers.size(); ++i )
    {
      scattering_reactions[reaction_pointers[i]->getReactionType()] =
        reaction_pointers[i];
    }
  }

  // Create the positron-atom core
  if( raw_positronatom_data.isEPRVersion14() )
  {
    positronatom_core.reset( new PositronatomCore( energy_grid,
                                                 grid_searcher,
                                                 scattering_reactions,
                                                 absorption_reactions,
                                                 atomic_relaxation_model,
                                                 false,
                                                 Utility::LogLog() ) );
  }
  else
  {
    positronatom_core.reset( new PositronatomCore( energy_grid,
                                                 grid_searcher,
                                                 scattering_reactions,
                                                 absorption_reactions,
                                                 atomic_relaxation_model,
                                                 false,
                                                 Utility::LinLin() ) );
  }
}

// Create a positron-atom (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * atom. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been
 * requested, a electroionization reaction for each subshell will be created.
 * Otherwise a single total electroionization reaction will be created.
 */
void PositronatomACEFactory::createPositronatom(
            const Data::XSSEPRDataExtractor& raw_positronatom_data,
            const std::string& positronatom_name,
            const double atomic_weight,
            const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
            const SimulationElectronProperties& properties,
            Teuchos::RCP<Positronatom>& positronatom )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );

  Teuchos::RCP<PositronatomCore> core;

  PositronatomACEFactory::createPositronatomCore( raw_positronatom_data,
                                                atomic_relaxation_model,
                                                properties,
                                                core );

  // Create the positron-atom
  positronatom.reset(
    new Positronatom( positronatom_name,
                     raw_positronatom_data.extractAtomicNumber(),
                     atomic_weight,
                     *core ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomACEFactory.cpp
//---------------------------------------------------------------------------//
