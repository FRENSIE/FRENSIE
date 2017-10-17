//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom native factory class definition.
//!
//---------------------------------------------------------------------------//

//// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomNativeFactory.hpp"
//#include "Utility_StandardHashBasedGridSearcher.hpp"
//#include "Utility_SortAlgorithms.hpp"
//#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create an adjoint electroatom core
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

  // Create the elastic scattering reaction
  if ( properties.isAdjointElasticModeOn() )
  {
    std::shared_ptr<AdjointElectroatomicReaction> elastic_reaction;

    std::string elastic_interp =
            raw_adjoint_electroatom_data.getElasticTwoDInterpPolicy();

    if( elastic_interp == "Log-Log-Log" )
    {
      ThisType::createElasticElectroatomCore<Utility::LogLogCosLog,Utility::Correlated>(
                                                raw_adjoint_electroatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                elastic_reaction,
                                                scattering_reactions );
    }
    else if( elastic_interp == "Lin-Lin-Log" )
    {
      ThisType::createElasticElectroatomCore<Utility::LinLinLog,Utility::Correlated>(
                                                raw_adjoint_electroatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                elastic_reaction,
                                                scattering_reactions );
    }
    else if( elastic_interp == "Lin-Lin-Lin" )
    {
      ThisType::createElasticElectroatomCore<Utility::LinLinLin,Utility::Correlated>(
                                                raw_adjoint_electroatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                elastic_reaction,
                                                scattering_reactions );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Error: the 2D interpolation policy "
                       << elastic_interp <<
                       " is not currently supported!" );
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
  if ( properties.isAdjointBremsstrahlungModeOn() )
  {
    AdjointElectroatomCore::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION];

    std::string brem_interp =
        raw_adjoint_electroatom_data.getBremsstrahlungTwoDInterpPolicy();

    if( brem_interp == "Log-Log-Log" )
    {
      AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LogLogLog,Utility::Correlated>(
                        raw_adjoint_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getAdjointElectronEvaluationTolerance() );
    }
    else if( brem_interp == "Lin-Lin-Log" )
    {
      AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LinLinLog,Utility::Correlated>(
                        raw_adjoint_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getAdjointElectronEvaluationTolerance() );
    }
    else if( brem_interp == "Lin-Lin-Lin" )
    {
      AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LinLinLin,Utility::Correlated>(
                        raw_adjoint_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getAdjointElectronEvaluationTolerance() );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Error: the 2D interpolation policy "
                       << brem_interp <<
                       " is not currently supported!" );
    }
  }

  // Create the atomic excitation scattering reaction
  if ( properties.isAdjointAtomicExcitationModeOn() )
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
  if ( properties.isAdjointElectroionizationModeOn() )
  {
    std::vector<std::shared_ptr<AdjointElectroatomicReaction> >
        electroionization_reactions;

    std::string ionization_interp =
        raw_adjoint_electroatom_data.getElectroionizationTwoDInterpPolicy();

    if( ionization_interp == "Log-Log-Log" )
    {
      AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<Utility::LogLogLog,Utility::Correlated>(
                                raw_adjoint_electroatom_data,
                                energy_grid,
                                grid_searcher,
                                electroionization_reactions,
                                properties.getAdjointElectronEvaluationTolerance() );
    }
    else if( ionization_interp == "Lin-Lin-Log" )
    {
      AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<Utility::LinLinLog,Utility::Correlated>(
                                raw_adjoint_electroatom_data,
                                energy_grid,
                                grid_searcher,
                                electroionization_reactions,
                                properties.getAdjointElectronEvaluationTolerance() );
    }
    else if( ionization_interp == "Lin-Lin-Lin" )
    {
      AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<Utility::LinLinLin,Utility::Correlated>(
                                raw_adjoint_electroatom_data,
                                energy_grid,
                                grid_searcher,
                                electroionization_reactions,
                                properties.getAdjointElectronEvaluationTolerance() );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Error: the 2D interpolation policy "
                       << ionization_interp <<
                       " is not currently supported!" );
    }

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
                    const SimulationAdjointElectronProperties& properties,
                    Teuchos::RCP<AdjointElectroatom>& adjoint_electroatom )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );

  Teuchos::RCP<AdjointElectroatomCore> core;

  ThisType::createAdjointElectroatomCore( raw_adjoint_electroatom_data,
                                          properties,
                                          core);

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
