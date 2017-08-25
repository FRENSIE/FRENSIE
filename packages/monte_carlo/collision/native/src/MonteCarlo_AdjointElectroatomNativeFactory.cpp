//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom native factory class definition.
//!
//---------------------------------------------------------------------------//

//// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomNativeFactory.hpp"
//#include "MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp"
//#include "Utility_StandardHashBasedGridSearcher.hpp"
//#include "Utility_SortAlgorithms.hpp"
//#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//// Create an adjoint electroatom core
//void AdjointElectroatomNativeFactory::createAdjointElectroatomCore(
//        const Data::AdjointElectronPhotonRelaxationDataContainer&
//            raw_adjoint_electroatom_data,
//        const SimulationAdjointElectronProperties& properties,
//        Teuchos::RCP<AdjointElectroatomCore>& adjoint_electroatom_core )
//{
//  // Extract the common energy grid used for this atom
//  Teuchos::ArrayRCP<double> energy_grid;
//  energy_grid.assign(
//    raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().begin(),
//    raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().end() );





//  // Construct the hash-based grid searcher for this atom
//  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
//    new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<double>,false>(
//                     energy_grid,
//                     properties.getNumberOfAdjointElectronHashGridBins() ) );

//  // Create the scattering reactions
//  AdjointElectroatomCore::ReactionMap scattering_reactions;
//  std::shared_ptr<ElectroatomicReaction> total_forward_reaction;

//  // Create the elastic reaction
//  {
//    std::shared_ptr<AdjointElectroatomicReaction> elastic_reaction;

//    // Create the coupled elastic scattering reaction (no moment preserving elastic scattering)
//    if ( properties.getElasticCutoffAngleCosine() == 1.0 )
//    {
//      AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
//        scattering_reactions[COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

//      AdjointElectroatomicReactionNativeFactory::createCoupledElasticReaction<TwoDInterpPolicy>(
//                        raw_adjoint_electroatom_data,
//                        energy_grid,
//                        grid_searcher,
//                        elastic_reaction,
//                        properties.getElectronEvaluationTolerance() );

//      reaction_pointer = elastic_reaction;
//    }
//    // Create the moment preserving elastic scattering reaction (no coupled elastic scattering)
//    else if ( properties.getElasticCutoffAngleCosine() == -1.0 )
//    {
//      AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
//        scattering_reactions[MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

//      AdjointElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<TwoDInterpPolicy>(
//                        raw_adjoint_electroatom_data,
//                        energy_grid,
//                        grid_searcher,
//                        elastic_reaction,
//                        properties.getElasticCutoffAngleCosine(),
//                        properties.getElectronEvaluationTolerance() );

//      reaction_pointer = elastic_reaction;
//    }
//    // Create the hybrid elastic scattering reaction (if cutoff is within range)
//    else
//    {
//      AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
//        scattering_reactions[HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

//      AdjointElectroatomicReactionNativeFactory::createHybridElasticReaction<TwoDInterpPolicy>(
//                       raw_adjoint_electroatom_data,
//                       energy_grid,
//                       grid_searcher,
//                       elastic_reaction,
//                       properties.getElasticCutoffAngleCosine(),
//                       properties.getElectronEvaluationTolerance() );

//      reaction_pointer = elastic_reaction;
//    }

//    // Create the total forward reaction
//      AdjointElectroatomicReactionNativeFactory::createTotalForwardReaction(
//        raw_adjoint_electroatom_data,
//        energy_grid,
//        grid_searcher,
//        elastic_reaction,
//        total_forward_reaction );
//  }

//  // Create the bremsstrahlung scattering reaction
//  {
//    AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
//      scattering_reactions[BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION];

//    AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<TwoDInterpPolicy>(
//                         raw_adjoint_electroatom_data,
//                         energy_grid,
//                         grid_searcher,
//                         reaction_pointer,
//                         properties.getElectronEvaluationTolerance() );
//  }

//  // Create the atomic excitation scattering reaction
//  {
//    AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
//      scattering_reactions[ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION];

//    AdjointElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
//                               raw_adjoint_electroatom_data,
//                               energy_grid,
//                               grid_searcher,
//                               reaction_pointer );
//  }

//  // Create the subshell electroionization reactions
//  {
//  std::vector<std::shared_ptr<AdjointElectroatomicReaction> >
//    electroionization_reactions;

//  AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<TwoDInterpPolicy>(
//                               raw_adjoint_electroatom_data,
//                               energy_grid,
//                               grid_searcher,
//                               electroionization_reactions,
//                               properties.getElectronEvaluationTolerance() );

//    for( size_t i = 0; i < electroionization_reactions.size(); ++i )
//    {
//      scattering_reactions[electroionization_reactions[i]->getReactionType()] =
//        electroionization_reactions[i];
//    }
//  }

//  // Create the electroatom core
//  adjoint_electroatom_core.reset(
//    new AdjointElectroatomCore( grid_searcher,
//                                total_forward_reaction,
//                                scattering_reactions,
//                                AdjointElectroatomCore::ReactionMap() ) );
//}

// Create a adjoint electroatom
void AdjointElectroatomNativeFactory::createAdjointElectroatom(
                    const Data::AdjointElectronPhotonRelaxationDataContainer&
                        raw_adjoint_electroatom_data,
                    const std::string& adjoint_electroatom_name,
                    const double atomic_weight,
                    const SimulationAdjointElectronProperties& properties,
                    Teuchos::RCP<AdjointElectroatom>& adjoint_electroatom )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );

  Teuchos::RCP<AdjointElectroatomCore> core;

  if( raw_adjoint_electroatom_data.isElectronLinLinLogInterpolationModeOn() )
  {
    ThisType::createAdjointElectroatomCore<Utility::LinLinLog>(
                                                raw_adjoint_electroatom_data,
                                                properties,
                                                core);
  }
  else
  {
    ThisType::createAdjointElectroatomCore<Utility::LinLinLin>(
                                                raw_adjoint_electroatom_data,
                                                properties,
                                                core);
  }

  // Create the adjoint electroatom
  adjoint_electroatom.reset( new AdjointElectroatom(
                                adjoint_electroatom_name,
                                raw_adjoint_electroatom_data.getAtomicNumber(),
                                atomic_weight,
                                *core ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomNativeFactory.cpp
//---------------------------------------------------------------------------//