//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronatomNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The positron-atom native factory class template definition.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONATOM_NATIVE_FACTORY_DEF_HPP
#define MONTE_CARLO_POSITRONATOM_NATIVE_FACTORY_DEF_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PositronatomNativeFactory.hpp"
#include "MonteCarlo_PositronatomicReactionNativeFactory.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a positron-atom core (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * core. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been
 * requested, a electroionization reaction for each subshell will be created.
 * Otherwise a single total electroionization reaction will be created.
 */
template <typename TwoDGridPolicy>
void PositronatomNativeFactory::createPositronatomCore(
        const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
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
  energy_grid.assign( raw_positronatom_data.getElectronEnergyGrid().begin(),
                      raw_positronatom_data.getElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher for this atom
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                              energy_grid,
                              properties.getNumberOfElectronHashGridBins() ) );

  // Create the elastic scattering reaction
  if ( properties.isElasticModeOn() )
  {
    if( TwoDGridPolicy::name() == "Unit-base" )
    {
      if( TwoDGridPolicy::TwoDInterpPolicy::name() == "LogLogLog" )
      {
        ThisType::createElasticPositronatomCore<Utility::Direct<Utility::LogLogCosLog> >(
                                                raw_positronatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                scattering_reactions );
      }
      else
      {
        ThisType::createElasticPositronatomCore<Utility::Direct<typename TwoDGridPolicy::TwoDInterpPolicy> >(
                                                raw_positronatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                scattering_reactions );
      }
    }
    else if( TwoDGridPolicy::name() == "Unit-base Correlated" )
    {
      if( TwoDGridPolicy::TwoDInterpPolicy::name() == "LogLogLog" )
      {
        ThisType::createElasticPositronatomCore<Utility::Correlated<Utility::LogLogCosLog> >(
                                                raw_positronatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                scattering_reactions );
      }
      else
      {
        ThisType::createElasticPositronatomCore<Utility::Correlated<typename TwoDGridPolicy::TwoDInterpPolicy> >(
                                                raw_positronatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                scattering_reactions );
      }
    }
    else if( TwoDGridPolicy::name() == "Correlated" )
    {
      if( TwoDGridPolicy::TwoDInterpPolicy::name() == "LogLogLog" )
      {
        ThisType::createElasticPositronatomCore<Utility::Correlated<Utility::LogLogCosLog> >(
                                                raw_positronatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                scattering_reactions );
      }
      else
      {
        ThisType::createElasticPositronatomCore<Utility::Correlated<typename TwoDGridPolicy::TwoDInterpPolicy> >(
                                                raw_positronatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                scattering_reactions );
      }
    }
    else if( TwoDGridPolicy::name() == "Direct" )
    {
      if( TwoDGridPolicy::TwoDInterpPolicy::name() == "LogLogLog" )
      {
        ThisType::createElasticPositronatomCore<Utility::Direct<Utility::LogLogCosLog> >(
                                                raw_positronatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                scattering_reactions );
      }
      else
      {
        ThisType::createElasticPositronatomCore<Utility::Direct<typename TwoDGridPolicy::TwoDInterpPolicy> >(
                                                raw_positronatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                scattering_reactions );
      }
    }
  }

  // Create the bremsstrahlung scattering reaction
  if ( properties.isBremsstrahlungModeOn() )
  {
    Positronatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[BREMSSTRAHLUNG_POSITRONATOMIC_REACTION];

    PositronatomicReactionNativeFactory::createBremsstrahlungReaction<PositronatomicReaction,TwoDGridPolicy>(
                  raw_positronatom_data,
                  energy_grid,
                  grid_searcher,
                  reaction_pointer,
                  properties.getBremsstrahlungAngularDistributionFunction(),
                  properties.getElectronEvaluationTolerance() );
  }

  // Create the atomic excitation scattering reaction
  if ( properties.isAtomicExcitationModeOn() )
  {
    Positronatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[ATOMIC_EXCITATION_POSITRONATOMIC_REACTION];

    PositronatomicReactionNativeFactory::createAtomicExcitationReaction(
                  raw_positronatom_data,
                  energy_grid,
                  grid_searcher,
                  reaction_pointer );
  }

  // Create the subshell electroionization reactions
  if ( properties.isElectroionizationModeOn() )
  {
    std::vector<std::shared_ptr<PositronatomicReaction> > reaction_pointers;

    PositronatomicReactionNativeFactory::createSubshellPositronionizationReactions<PositronatomicReaction,TwoDGridPolicy>(
                      raw_positronatom_data,
                      energy_grid,
                      grid_searcher,
                      reaction_pointers,
                      properties.getElectronEvaluationTolerance() );

    for( unsigned i = 0; i < reaction_pointers.size(); ++i )
    {
      scattering_reactions[reaction_pointers[i]->getReactionType()] =
        reaction_pointers[i];
    }
  }

  // Create the positron-atom core
  positronatom_core.reset( new PositronatomCore( energy_grid,
                                               grid_searcher,
                                               scattering_reactions,
                                               absorption_reactions,
                                               atomic_relaxation_model,
                                               false,
                                               Utility::LogLog() ) );
}

// Create the elastic reaction for a positron-atom core
template <typename TwoDGridPolicy>
void PositronatomNativeFactory::createElasticPositronatomCore(
        const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
        const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
        const SimulationElectronProperties& properties,
        Positronatom::ReactionMap& scattering_reactions )
{
  // Get the elastic distribution type
  ElasticElectronDistributionType distribution_type =
                            properties.getElasticElectronDistributionMode();

  if( distribution_type == COUPLED_DISTRIBUTION )
  {
    Positronatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[COUPLED_ELASTIC_POSITRONATOMIC_REACTION];

    PositronatomicReactionNativeFactory::createCoupledElasticReaction<TwoDGridPolicy>(
                        raw_positronatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getCoupledElasticSamplingMode(),
                        properties.getElectronEvaluationTolerance() );
  }
  else if( distribution_type == DECOUPLED_DISTRIBUTION )
  {
    Positronatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION];

    PositronatomicReactionNativeFactory::createDecoupledElasticReaction<TwoDGridPolicy>(
                        raw_positronatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getElectronEvaluationTolerance() );
  }
  else if( distribution_type == HYBRID_DISTRIBUTION )
  {
    // Create the coupled elastic scattering reaction (no moment preserving elastic scattering)
    if ( properties.getElasticCutoffAngleCosine() == 1.0 )
    {
      Positronatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION];

      PositronatomicReactionNativeFactory::createDecoupledElasticReaction<TwoDGridPolicy>(
                        raw_positronatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getElectronEvaluationTolerance() );
    }
    // Create the moment preserving elastic scattering reaction (no coupled elastic scattering)
    else if ( properties.getElasticCutoffAngleCosine() == -1.0 )
    {
      Positronatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[MOMENT_PRESERVING_ELASTIC_POSITRONATOMIC_REACTION];

      PositronatomicReactionNativeFactory::createMomentPreservingElasticReaction<TwoDGridPolicy>(
                        raw_positronatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getElasticCutoffAngleCosine(),
                        properties.getElectronEvaluationTolerance() );
    }
    // Create the hybrid elastic scattering reaction (if cutoff is within range)
    else
    {
      Positronatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[HYBRID_ELASTIC_POSITRONATOMIC_REACTION];

      PositronatomicReactionNativeFactory::createHybridElasticReaction<TwoDGridPolicy>(
                        raw_positronatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getElasticCutoffAngleCosine(),
                        properties.getElectronEvaluationTolerance() );
    }
  }
  else if( distribution_type == CUTOFF_DISTRIBUTION )
  {
    Positronatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[CUTOFF_ELASTIC_POSITRONATOMIC_REACTION];

    PositronatomicReactionNativeFactory::createCutoffElasticReaction<TwoDGridPolicy>(
                        raw_positronatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getElasticCutoffAngleCosine(),
                        properties.getElectronEvaluationTolerance() );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: elastic distribution type "
                     << distribution_type <<
                     " is not currently supported!" );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRONATOM_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomNativeFactory_def.hpp
//---------------------------------------------------------------------------//