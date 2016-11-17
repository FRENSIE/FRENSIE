//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom native factory class definition.
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomNativeFactory.hpp"
#include "MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a adjoint electroatom core (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * core. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been
 * requested, a electroionization reaction for each subshell will be created.
 * Otherwize a single total electroionization reaction will be created.
 */
void AdjointElectroatomNativeFactory::createAdjointElectroatomCore(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
          Teuchos::RCP<AdjointElectroatomCore>& adjoint_electroatom_core,
        const unsigned hash_grid_bins,
        const bool use_atomic_relaxation_data,
        const double cutoff_angle_cosine )
{
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );

  adjoint_electroatom_core.reset( new AdjointElectroatomCore() );

  AdjointElectroatom::ReactionMap scattering_reactions, absorption_reactions;

  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign(
    raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().begin(),
    raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher for this atom
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                             energy_grid,
                             hash_grid_bins ) );

  // Create the analog elastic scattering reaction (no moment preserving elastic scattering)
  if ( cutoff_angle_cosine == 1.0 )
  {
    AdjointElectroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createAnalogElasticReaction(
                       raw_adjoint_electroatom_data,
                       energy_grid,
                       grid_searcher,
                       reaction_pointer );
  }
  // Create the moment preserving elastic scattering reaction (no analog elastic scattering)
  else if ( cutoff_angle_cosine == -1.0 )
  {
    AdjointElectroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction(
                       raw_adjoint_electroatom_data,
                       energy_grid,
                       grid_searcher,
                       reaction_pointer,
                       cutoff_angle_cosine );
  }
  // Create the hybrid elastic scattering reaction (if cutoff is within range)
  else
  {
    AdjointElectroatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createHybridElasticReaction(
                       raw_adjoint_electroatom_data,
                       energy_grid,
                       grid_searcher,
                       reaction_pointer,
                       cutoff_angle_cosine );

  }

  // Create the bremsstrahlung scattering reaction
  {
    AdjointElectroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
                         raw_adjoint_electroatom_data,
                         energy_grid,
                         grid_searcher,
                         reaction_pointer );
  }

  // Create the atomic excitation scattering reaction
  {
    AdjointElectroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
                               raw_adjoint_electroatom_data,
                               energy_grid,
                               grid_searcher,
                               reaction_pointer );
  }

  // Create the subshell electroionization reactions
  {
  std::vector<std::shared_ptr<AdjointElectroatomicReaction> > reaction_pointers;

  AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions(
                               raw_adjoint_electroatom_data,
                               energy_grid,
                               grid_searcher,
                               reaction_pointers );

  for( unsigned i = 0; i < reaction_pointers.size(); ++i )
  {
    scattering_reactions[reaction_pointers[i]->getReactionType()] =
        reaction_pointers[i];
  }
  }

  // Create the electroatom core
  adjoint_electroatom_core.reset(
    new AdjointElectroatomCore( energy_grid,
                                scattering_reactions,
                                absorption_reactions,
                                atomic_relaxation_model,
                                false,
                                Utility::LinLin() ) );
}

// Create a adjoint electroatom (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * atom. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been
 * requested, a electroionization reaction for each subshell will be created.
 * Otherwise a single total electroionization reaction will be created.
 */
void AdjointElectroatomNativeFactory::createAdjointElectroatom(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const std::string& electroatom_name,
        const double atomic_weight,
        const unsigned hash_grid_bins,
        const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
          Teuchos::RCP<AdjointElectroatom>& electroatom,
        const bool use_atomic_relaxation_data,
        const double cutoff_angle_cosine )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );

  Teuchos::RCP<AdjointElectroatomCore> core;

  AdjointElectroatomNativeFactory::createAdjointElectroatomCore(
    raw_adjoint_electroatom_data,
    atomic_relaxation_model,
    core,
    hash_grid_bins,
    use_atomic_relaxation_data,
        cutoff_angle_cosine );

  // Create the electroatom
  electroatom.reset(
    new AdjointElectroatom( electroatom_name,
                            raw_adjoint_electroatom_data.getAtomicNumber(),
                            atomic_weight,
                            *core ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomNativeFactory.cpp
//---------------------------------------------------------------------------//
