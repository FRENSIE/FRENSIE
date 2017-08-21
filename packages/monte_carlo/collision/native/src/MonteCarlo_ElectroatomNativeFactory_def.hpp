//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The electroatom native factory class template definition.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOM_NATIVE_FACTORY_DEF_HPP
#define MONTE_CARLO_ELECTROATOM_NATIVE_FACTORY_DEF_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomNativeFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the elastic reaction for a electroatom core
template <typename TwoDInterpPolicy>
void ElectroatomNativeFactory::createElasticElectroatomCore(
        const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
        const Teuchos::ArrayRCP<const double>& energy_grid,
        const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
        const SimulationElectronProperties& properties,
        Electroatom::ReactionMap& scattering_reactions )
{
  // Get the elastic distribution type
  ElasticElectronDistributionType distribution_type =
                            properties.getElasticElectronDistributionMode();

  if( distribution_type == COUPLED_DISTRIBUTION )
  {
    Electroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[COUPLED_ELASTIC_ELECTROATOMIC_REACTION];

    ElectroatomicReactionNativeFactory::createCoupledElasticReaction<TwoDInterpPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.isCorrelatedSamplingModeOn(),
                        properties.getElectronEvaluationTolerance() );
  }
  else if( distribution_type == DECOUPLED_DISTRIBUTION )
  {
    Electroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION];

    ElectroatomicReactionNativeFactory::createDecoupledElasticReaction<TwoDInterpPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.isCorrelatedSamplingModeOn(),
                        properties.getElectronEvaluationTolerance() );
  }
  else if( distribution_type == HYBRID_DISTRIBUTION )
  {
    // Create the coupled elastic scattering reaction (no moment preserving elastic scattering)
    if ( properties.getElasticCutoffAngleCosine() == 1.0 )
    {
      Electroatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION];

      ElectroatomicReactionNativeFactory::createDecoupledElasticReaction<TwoDInterpPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.isCorrelatedSamplingModeOn(),
                        properties.getElectronEvaluationTolerance() );
    }
    // Create the moment preserving elastic scattering reaction (no coupled elastic scattering)
    else if ( properties.getElasticCutoffAngleCosine() == -1.0 )
    {
      Electroatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION];

      ElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<TwoDInterpPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getElasticCutoffAngleCosine(),
                        properties.isCorrelatedSamplingModeOn(),
                        properties.getElectronEvaluationTolerance() );
    }
    // Create the hybrid elastic scattering reaction (if cutoff is within range)
    else
    {
      Electroatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[HYBRID_ELASTIC_ELECTROATOMIC_REACTION];

      ElectroatomicReactionNativeFactory::createHybridElasticReaction<TwoDInterpPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getElasticCutoffAngleCosine(),
                        properties.isCorrelatedSamplingModeOn(),
                        properties.getElectronEvaluationTolerance() );
    }
  }
  else if( distribution_type == CUTOFF_DISTRIBUTION )
  {
    Electroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[CUTOFF_ELASTIC_ELECTROATOMIC_REACTION];

    ElectroatomicReactionNativeFactory::createCutoffElasticReaction<TwoDInterpPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getElasticCutoffAngleCosine(),
                        properties.isCorrelatedSamplingModeOn(),
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

#endif // end MONTE_CARLO_ELECTROATOM_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomNativeFactory_def.hpp
//---------------------------------------------------------------------------//
