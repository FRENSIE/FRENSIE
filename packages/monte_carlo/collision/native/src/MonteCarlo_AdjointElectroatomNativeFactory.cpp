//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom native factory class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>
#include <list>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomNativeFactory.hpp"
#include "MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create an adjoint electroatom core
//! \details Currently no atomic relaxation model will be used with the core.
void AdjointElectroatomNativeFactory::createAdjointElectroatomCore(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        Teuchos::RCP<AdjointElectroatomCore>& adjoint_electroatom_core,
        const double cutoff_angle_cosine,
        const unsigned hash_grid_bins )
{
  // Make sure the hash grid bins are valid
  testPrecondition( hash_grid_bins > 0u );

  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign(
    raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().begin(),
    raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher for this atom
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
    new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<double>,false>(
                             energy_grid,
                             hash_grid_bins ) );

  // Create the scattering reactions
  AdjointElectroatomCore::ReactionMap scattering_reactions;

  std::shared_ptr<AdjointElectroatomicReaction> elastic_reaction;

  // Create the analog elastic scattering reaction (no moment preserving elastic scattering)
  if ( cutoff_angle_cosine == 1.0 )
  {
    AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createAnalogElasticReaction(
                       raw_adjoint_electroatom_data,
                       energy_grid,
                       grid_searcher,
                       elastic_reaction );
    reaction_pointer = elastic_reaction;
  }
  // Create the moment preserving elastic scattering reaction (no analog elastic scattering)
  else if ( cutoff_angle_cosine == -1.0 )
  {
    AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction(
                       raw_adjoint_electroatom_data,
                       energy_grid,
                       grid_searcher,
                       elastic_reaction,
                       cutoff_angle_cosine );
    reaction_pointer = elastic_reaction;
  }
  // Create the hybrid elastic scattering reaction (if cutoff is within range)
  else
  {
    AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createHybridElasticReaction(
                       raw_adjoint_electroatom_data,
                       energy_grid,
                       grid_searcher,
                       elastic_reaction,
                       cutoff_angle_cosine );
    reaction_pointer = elastic_reaction;
  }


  // Create the total forward reaction
  std::shared_ptr<ElectroatomicReaction> total_forward_reaction;
    AdjointElectroatomicReactionNativeFactory::createTotalForwardReaction(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        elastic_reaction,
        total_forward_reaction );

  // Create the bremsstrahlung scattering reaction
  {
    AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
                         raw_adjoint_electroatom_data,
                         energy_grid,
                         grid_searcher,
                         reaction_pointer );
  }

  // Create the atomic excitation scattering reaction
  {
    AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
                               raw_adjoint_electroatom_data,
                               energy_grid,
                               grid_searcher,
                               reaction_pointer );
  }

  // Create the subshell electroionization reactions
  {
  std::vector<std::shared_ptr<AdjointElectroatomicReaction> >
    electroionization_reactions;

  AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions(
                               raw_adjoint_electroatom_data,
                               energy_grid,
                               grid_searcher,
                               electroionization_reactions );

    for( size_t i = 0; i < electroionization_reactions.size(); ++i )
    {
      scattering_reactions[electroionization_reactions[i]->getReactionType()] =
        electroionization_reactions[i];
    }
  }

  // Create the electroatom core
  adjoint_electroatom_core.reset(
    new AdjointElectroatomCore( grid_searcher,
                                total_forward_reaction,
                                scattering_reactions,
                                AdjointElectroatomCore::ReactionMap() ) );
}

// Create a adjoint electroatom
void AdjointElectroatomNativeFactory::createAdjointElectroatom(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const std::string& adjoint_electroatom_name,
        const double atomic_weight,
        Teuchos::RCP<AdjointElectroatom>& electroatom,
        const double cutoff_angle_cosine,
        const unsigned hash_grid_bins )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure the hash grid bins are valid
  testPrecondition( hash_grid_bins > 0u );

  Teuchos::RCP<AdjointElectroatomCore> core;

  AdjointElectroatomNativeFactory::createAdjointElectroatomCore(
    raw_adjoint_electroatom_data,
    core,
    cutoff_angle_cosine,
    hash_grid_bins );

  // Create the electroatom
  electroatom.reset(
    new AdjointElectroatom( adjoint_electroatom_name,
                            raw_adjoint_electroatom_data.getAtomicNumber(),
                            atomic_weight,
                            *core ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomNativeFactory.cpp
//---------------------------------------------------------------------------//
