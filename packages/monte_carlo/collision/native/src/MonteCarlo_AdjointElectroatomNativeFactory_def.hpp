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
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the elastic reaction for a electroatom core
template <typename TwoDInterpPolicy>
void AdjointElectroatomNativeFactory::createElasticElectroatomCore(
        const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroatom_data,
        const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
        const SimulationAdjointElectronProperties& properties,
        std::shared_ptr<AdjointElectroatomicReaction>& elastic_reaction,
        AdjointElectroatom::ReactionMap& scattering_reactions )
{
  // Get the elastic distribution type
  ElasticElectronDistributionType distribution_type =
                        properties.getAdjointElasticElectronDistributionMode();

  if( distribution_type == COUPLED_DISTRIBUTION )
  {
    AdjointElectroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createCoupledElasticReaction<TwoDInterpPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        elastic_reaction,
                        properties.getAdjointCoupledElasticSamplingMode(),
                        properties.isAdjointCorrelatedSamplingModeOn(),
                        properties.getAdjointElectronEvaluationTolerance() );

    reaction_pointer = elastic_reaction;
  }
  else if( distribution_type == DECOUPLED_DISTRIBUTION )
  {
    AdjointElectroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createDecoupledElasticReaction<TwoDInterpPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        elastic_reaction,
                        properties.isAdjointCorrelatedSamplingModeOn(),
                        properties.getAdjointElectronEvaluationTolerance() );

    reaction_pointer = elastic_reaction;
  }
  else if( distribution_type == HYBRID_DISTRIBUTION )
  {
    // Create the coupled elastic scattering reaction (no moment preserving elastic scattering)
    if ( properties.getAdjointElasticCutoffAngleCosine() == 1.0 )
    {
      AdjointElectroatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

      AdjointElectroatomicReactionNativeFactory::createDecoupledElasticReaction<TwoDInterpPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        elastic_reaction,
                        properties.isAdjointCorrelatedSamplingModeOn(),
                        properties.getAdjointElectronEvaluationTolerance() );

      reaction_pointer = elastic_reaction;
    }
    // Create the moment preserving elastic scattering reaction (no coupled elastic scattering)
    else if ( properties.getAdjointElasticCutoffAngleCosine() == -1.0 )
    {
      AdjointElectroatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

      AdjointElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<TwoDInterpPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        elastic_reaction,
                        properties.getAdjointElasticCutoffAngleCosine(),
                        properties.isAdjointCorrelatedSamplingModeOn(),
                        properties.getAdjointElectronEvaluationTolerance() );

      reaction_pointer = elastic_reaction;
    }
    // Create the hybrid elastic scattering reaction (if cutoff is within range)
    else
    {
      AdjointElectroatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

      AdjointElectroatomicReactionNativeFactory::createHybridElasticReaction<TwoDInterpPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        elastic_reaction,
                        properties.getAdjointElasticCutoffAngleCosine(),
                        properties.isAdjointCorrelatedSamplingModeOn(),
                        properties.getAdjointElectronEvaluationTolerance() );

      reaction_pointer = elastic_reaction;
    }
  }
  else if( distribution_type == CUTOFF_DISTRIBUTION )
  {
    AdjointElectroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createCutoffElasticReaction<TwoDInterpPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        elastic_reaction,
                        properties.getAdjointElasticCutoffAngleCosine(),
                        properties.isAdjointCorrelatedSamplingModeOn(),
                        properties.getAdjointElectronEvaluationTolerance() );

    reaction_pointer = elastic_reaction;
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

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOM_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomNativeFactory_def.hpp
//---------------------------------------------------------------------------//
