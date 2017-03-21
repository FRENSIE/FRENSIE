//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The electroatom native factory class template definition.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOM_NATIVE_FACTORY_DEF_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOM_NATIVE_FACTORY_DEF_HPP


namespace MonteCarlo{

// Create an adjoint electroatom core
//! \details Currently no atomic relaxation model will be used with the core.
template <typename SecondInterpPolicy>
void AdjointElectroatomNativeFactory::createAdjointElectroatomCore(
        const Data::AdjointElectronPhotonRelaxationDataContainer&
            raw_adjoint_electroatom_data,
        const SimulationElectronProperties& properties,
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
                             properties.getNumberOfElectronHashGridBins() ) );

  // Create the scattering reactions
  AdjointElectroatomCore::ReactionMap scattering_reactions;

  std::shared_ptr<AdjointElectroatomicReaction> elastic_reaction;

  // Create the analog elastic scattering reaction (no moment preserving elastic scattering)
  if ( properties.getElasticCutoffAngleCosine() == 1.0 )
  {
    AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createAnalogElasticReaction<SecondInterpPolicy>(
                        raw_adjoint_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        elastic_reaction,
                        properties.getElectronEvaluationTolerance() );

    reaction_pointer = elastic_reaction;
  }
  // Create the moment preserving elastic scattering reaction (no analog elastic scattering)
  else if ( properties.getElasticCutoffAngleCosine() == -1.0 )
  {
    AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<SecondInterpPolicy>(
                        raw_adjoint_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        elastic_reaction,
                        properties.getElasticCutoffAngleCosine(),
                        properties.getElectronEvaluationTolerance() );

    reaction_pointer = elastic_reaction;
  }
  // Create the hybrid elastic scattering reaction (if cutoff is within range)
  else
  {
    AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createHybridElasticReaction<SecondInterpPolicy>(
                       raw_adjoint_electroatom_data,
                       energy_grid,
                       grid_searcher,
                       elastic_reaction,
                       properties.getElasticCutoffAngleCosine(),
                       properties.getElectronEvaluationTolerance() );

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

    AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<SecondInterpPolicy>(
                         raw_adjoint_electroatom_data,
                         energy_grid,
                         grid_searcher,
                         reaction_pointer,
                         properties.getElectronEvaluationTolerance() );
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

  AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<SecondInterpPolicy>(
                               raw_adjoint_electroatom_data,
                               energy_grid,
                               grid_searcher,
                               electroionization_reactions,
                               properties.getElectronEvaluationTolerance() );

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
