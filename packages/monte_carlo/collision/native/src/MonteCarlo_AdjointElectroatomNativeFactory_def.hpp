//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom native factory class template definition.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOM_NATIVE_FACTORY_DEF_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOM_NATIVE_FACTORY_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create an adjoint electroatom core
template <typename TwoDInterpPolicy>
void AdjointElectroatomNativeFactory::createAdjointElectroatomCore(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const SimulationAdjointElectronProperties& properties,
        Teuchos::RCP<AdjointElectroatomCore>& adjoint_electroatom_core )
{
  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign(
    raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().begin(),
    raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher for this atom
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
    new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<double>,false>(
                     energy_grid,
                     properties.getNumberOfAdjointElectronHashGridBins() ) );

  // Create the scattering reactions
  AdjointElectroatomCore::ReactionMap scattering_reactions;
  std::shared_ptr<ElectroatomicReaction> total_forward_reaction;

  // Get the FullyTabularTwoDDistribution evaluation tolerance
  double evaluation_tol = properties.getAdjointElectronEvaluationTolerance();
  bool correlated_sampling_mode_on =
                            properties.isAdjointCorrelatedSamplingModeOn();
  bool unit_based_interpolation_mode_on =
                            properties.isAdjointUnitBasedInterpolationModeOn();

  // Create the elastic reaction
  {
    std::shared_ptr<AdjointElectroatomicReaction> elastic_reaction;

    // Get the elastic cutoff angle cosine
    double cutoff_cosine = properties.getAdjointElasticCutoffAngleCosine();

    // Create the coupled elastic scattering reaction (no moment preserving elastic scattering)
    if ( cutoff_cosine == 1.0 )
    {
      AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

      AdjointElectroatomicReactionNativeFactory::createCoupledElasticReaction<TwoDInterpPolicy>(
                        raw_adjoint_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        elastic_reaction,
                        correlated_sampling_mode_on,
                        evaluation_tol );

      reaction_pointer = elastic_reaction;
    }
    // Create the moment preserving elastic scattering reaction (no coupled elastic scattering)
    else if ( cutoff_cosine == -1.0 )
    {
      AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

      AdjointElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<TwoDInterpPolicy>(
                        raw_adjoint_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        elastic_reaction,
                        cutoff_cosine,
                        correlated_sampling_mode_on,
                        evaluation_tol );

      reaction_pointer = elastic_reaction;
    }
    // Create the hybrid elastic scattering reaction (if cutoff is within range)
    else
    {
      AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

      AdjointElectroatomicReactionNativeFactory::createHybridElasticReaction<TwoDInterpPolicy>(
                       raw_adjoint_electroatom_data,
                       energy_grid,
                       grid_searcher,
                       elastic_reaction,
                       cutoff_cosine,
                        correlated_sampling_mode_on,
                        evaluation_tol );

      reaction_pointer = elastic_reaction;
    }

    // Create the total forward reaction
      AdjointElectroatomicReactionNativeFactory::createTotalForwardReaction(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        elastic_reaction,
        total_forward_reaction );
  }

  // Create the bremsstrahlung scattering reaction
  {
    AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<TwoDInterpPolicy>(
                        raw_adjoint_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        correlated_sampling_mode_on,
                        unit_based_interpolation_mode_on,
                        evaluation_tol );
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

  AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<TwoDInterpPolicy>(
                                raw_adjoint_electroatom_data,
                                energy_grid,
                                grid_searcher,
                                electroionization_reactions,
                                correlated_sampling_mode_on,
                                unit_based_interpolation_mode_on,
                                evaluation_tol );

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

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOM_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomNativeFactory_def.hpp
//---------------------------------------------------------------------------//
