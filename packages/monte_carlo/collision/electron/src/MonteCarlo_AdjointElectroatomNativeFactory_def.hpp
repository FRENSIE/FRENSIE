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
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create the elastic reaction for a electroatom core
template <typename TwoDInterpPolicy,
          template<typename> class TwoDGridPolicy>
void AdjointElectroatomNativeFactory::createElasticElectroatomCore(
        const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroatom_data,
        const std::shared_ptr<const std::vector<double> >& energy_grid,
        const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
        const SimulationAdjointElectronProperties& properties,
        std::shared_ptr<const AdjointElectroatomicReaction>& elastic_reaction,
        AdjointElectroatom::ConstReactionMap& scattering_reactions )
{
  // Get the elastic distribution type
  ElasticElectronDistributionType distribution_type =
                        properties.getAdjointElasticElectronDistributionMode();

  if( distribution_type == COUPLED_DISTRIBUTION )
  {
    AdjointElectroatom::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createCoupledElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        elastic_reaction,
                        properties.getAdjointCoupledElasticSamplingMode(),
                        properties.getAdjointElectronEvaluationTolerance() );

    reaction_pointer = elastic_reaction;
  }
  else if( distribution_type == DECOUPLED_DISTRIBUTION )
  {
    AdjointElectroatom::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createDecoupledElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        elastic_reaction,
                        properties.getAdjointElectronEvaluationTolerance() );

    reaction_pointer = elastic_reaction;
  }
  else if( distribution_type == HYBRID_DISTRIBUTION )
  {
    // Create the coupled elastic scattering reaction (no moment preserving elastic scattering)
    if ( properties.getAdjointElasticCutoffAngleCosine() == 1.0 )
    {
      AdjointElectroatom::ConstReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

      AdjointElectroatomicReactionNativeFactory::createDecoupledElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        elastic_reaction,
                        properties.getAdjointElectronEvaluationTolerance() );

      reaction_pointer = elastic_reaction;
    }
    // Create the moment preserving elastic scattering reaction (no coupled elastic scattering)
    else if ( properties.getAdjointElasticCutoffAngleCosine() == -1.0 )
    {
      AdjointElectroatom::ConstReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

      AdjointElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        elastic_reaction,
                        properties.getAdjointElasticCutoffAngleCosine(),
                        properties.getAdjointElectronEvaluationTolerance() );

      reaction_pointer = elastic_reaction;
    }
    // Create the hybrid elastic scattering reaction (if cutoff is within range)
    else
    {
      AdjointElectroatom::ConstReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

      AdjointElectroatomicReactionNativeFactory::createHybridElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        elastic_reaction,
                        properties.getAdjointElasticCutoffAngleCosine(),
                        properties.getAdjointElectronEvaluationTolerance() );

      reaction_pointer = elastic_reaction;
    }
  }
  else if( distribution_type == CUTOFF_DISTRIBUTION )
  {
    AdjointElectroatom::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION];

    AdjointElectroatomicReactionNativeFactory::createCutoffElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        elastic_reaction,
                        properties.getAdjointElasticCutoffAngleCosine(),
                        properties.getAdjointElectronEvaluationTolerance() );

    reaction_pointer = elastic_reaction;
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "elastic distribution type "
                     << distribution_type <<
                     " is not currently supported!" );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOM_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomNativeFactory_def.hpp
//---------------------------------------------------------------------------//
