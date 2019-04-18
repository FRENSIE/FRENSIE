//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The electroatom native factory class template definition.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOM_NATIVE_FACTORY_DEF_HPP
#define MONTE_CARLO_ELECTROATOM_NATIVE_FACTORY_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroatomNativeFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a electroatom core (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * core. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been
 * requested, a electroionization reaction for each subshell will be created.
 * Otherwise a single total electroionization reaction will be created.
 */
template <typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
void ElectroatomNativeFactory::createElectroatomCore(
        const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
        const std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
        const SimulationElectronProperties& properties,
        std::shared_ptr<const ElectroatomCore>& electroatom_core )
{
  // Make sure the atomic relaxation model is valid
  testPrecondition( atomic_relaxation_model.get() );

  electroatom_core.reset( new ElectroatomCore() );

  Electroatom::ConstReactionMap scattering_reactions, absorption_reactions;

  // Extract the common energy grid used for this atom
  std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );
  energy_grid->assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
                       raw_electroatom_data.getElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher for this atom
  std::shared_ptr<const Utility::HashBasedGridSearcher<double>> grid_searcher(
        new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                              energy_grid,
                              properties.getNumberOfElectronHashGridBins() ) );

// Create the elastic scattering reaction
  if ( properties.isElasticModeOn() )
  {
    if( TwoDGridPolicy<TwoDInterpPolicy>::name() == "Unit-base" || TwoDGridPolicy<TwoDInterpPolicy>::name() == "Direct" )
    {
      if( TwoDInterpPolicy::name() == "LogLogLog" )
      {
        if( properties.getElasticElectronDistributionMode() == COUPLED_DISTRIBUTION &&
            properties.getCoupledElasticSamplingMode() == MODIFIED_TWO_D_UNION )
        {
          THROW_EXCEPTION( std::runtime_error, "the bivariate grid policy "
                       << TwoDGridPolicy<TwoDInterpPolicy>::name() << " is not currently supported "
                       << "with a " << properties.getCoupledElasticSamplingMode()
                       << " coupled elastic sampling mode!" );
        }
        else
        {
          if( properties.getElasticElectronDistributionMode() == COUPLED_DISTRIBUTION ||
              ( properties.getElasticElectronDistributionMode() == HYBRID_DISTRIBUTION &&
                properties.getElasticCutoffAngleCosine() < 1.0 ) )
          {
            ThisType::createElasticElectroatomCore<Utility::LogNudgedLogCosLog,Utility::Direct>(
                                                  raw_electroatom_data,
                                                  energy_grid,
                                                  grid_searcher,
                                                  properties,
                                                  scattering_reactions );
          }
          else
          {
            ThisType::createElasticElectroatomCore<Utility::LogLogCosLog,Utility::Direct>(
                                                  raw_electroatom_data,
                                                  energy_grid,
                                                  grid_searcher,
                                                  properties,
                                                  scattering_reactions );
          }
        }
      }
      else
      {
        ThisType::createElasticElectroatomCore<TwoDInterpPolicy,Utility::Direct>(
                                                raw_electroatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                scattering_reactions );
      }
    }
    else if( TwoDGridPolicy<TwoDInterpPolicy>::name() == "Unit-base Correlated" || TwoDGridPolicy<TwoDInterpPolicy>::name() == "Correlated" )
    {
      if( TwoDInterpPolicy::name() == "LogLogLog" )
      {
        if( properties.getElasticElectronDistributionMode() == COUPLED_DISTRIBUTION ||
            ( properties.getElasticElectronDistributionMode() == HYBRID_DISTRIBUTION &&
              properties.getElasticCutoffAngleCosine() < 1.0 ) )
        {
          ThisType::createElasticElectroatomCore<Utility::LogNudgedLogCosLog,Utility::Correlated>(
                                                  raw_electroatom_data,
                                                  energy_grid,
                                                  grid_searcher,
                                                  properties,
                                                  scattering_reactions );
        }
        else
        {
          ThisType::createElasticElectroatomCore<Utility::LogLogCosLog,Utility::Correlated>(
                                                  raw_electroatom_data,
                                                  energy_grid,
                                                  grid_searcher,
                                                  properties,
                                                  scattering_reactions );
        }
      }
      else
      {
        ThisType::createElasticElectroatomCore<TwoDInterpPolicy,Utility::Correlated>(
                                                raw_electroatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                scattering_reactions );
      }
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error, "Error: the bivariate grid policy "
                       << TwoDGridPolicy<TwoDInterpPolicy>::name() << " is not currently supported!" );
    }
  }

  // Create the bremsstrahlung scattering reaction
  if ( properties.isBremsstrahlungModeOn() )
  {
    Electroatom::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[BREMSSTRAHLUNG_ELECTROATOMIC_REACTION];

    ElectroatomicReactionNativeFactory::createBremsstrahlungReaction<TwoDInterpPolicy,TwoDGridPolicy>(
                  raw_electroatom_data,
                  energy_grid,
                  grid_searcher,
                  reaction_pointer,
                  properties.getBremsstrahlungAngularDistributionFunction(),
                  properties.getElectronEvaluationTolerance() );
  }

  // Create the atomic excitation scattering reaction
  if ( properties.isAtomicExcitationModeOn() )
  {
    Electroatom::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[ATOMIC_EXCITATION_ELECTROATOMIC_REACTION];

    ElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
                               raw_electroatom_data,
                               energy_grid,
                               grid_searcher,
                               reaction_pointer );
  }

  // Create the subshell electroionization reactions
  if ( properties.isElectroionizationModeOn() )
  {
    std::vector<std::shared_ptr<const ElectroatomicReaction> > reaction_pointers;

    ElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<TwoDInterpPolicy,TwoDGridPolicy>(
                      raw_electroatom_data,
                      energy_grid,
                      grid_searcher,
                      reaction_pointers,
                      properties.getElectroionizationSamplingMode(),
                      properties.getElectronEvaluationTolerance() );

    for( size_t i = 0; i < reaction_pointers.size(); ++i )
    {
      scattering_reactions[reaction_pointers[i]->getReactionType()] =
        reaction_pointers[i];
    }
  }

  // Create the electroatom core
  electroatom_core.reset( new ElectroatomCore( energy_grid,
                                               grid_searcher,
                                               scattering_reactions,
                                               absorption_reactions,
                                               atomic_relaxation_model,
                                               false,
                                               Utility::LogLog() ) );
}

// Create the elastic reaction for a electroatom core
template <typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
void ElectroatomNativeFactory::createElasticElectroatomCore(
        const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
        const std::shared_ptr<const std::vector<double> >& energy_grid,
        const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
        const SimulationElectronProperties& properties,
        Electroatom::ConstReactionMap& scattering_reactions )
{
  // Get the elastic distribution type
  ElasticElectronDistributionType distribution_type =
                            properties.getElasticElectronDistributionMode();

  if( distribution_type == COUPLED_DISTRIBUTION )
  {
    Electroatom::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[COUPLED_ELASTIC_ELECTROATOMIC_REACTION];

    ElectroatomicReactionNativeFactory::createCoupledElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getCoupledElasticSamplingMode(),
                        properties.getElectronEvaluationTolerance() );
  }
  else if( distribution_type == DECOUPLED_DISTRIBUTION )
  {
    Electroatom::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION];

    ElectroatomicReactionNativeFactory::createDecoupledElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
                        raw_electroatom_data,
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
      Electroatom::ConstReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION];

      ElectroatomicReactionNativeFactory::createDecoupledElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getElectronEvaluationTolerance() );
    }
    // Create the moment preserving elastic scattering reaction (no coupled elastic scattering)
    else if ( properties.getElasticCutoffAngleCosine() == -1.0 )
    {
      Electroatom::ConstReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION];

      ElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getElasticCutoffAngleCosine(),
                        properties.getElectronEvaluationTolerance() );
    }
    // Create the hybrid elastic scattering reaction (if cutoff is within range)
    else
    {
      Electroatom::ConstReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[HYBRID_ELASTIC_ELECTROATOMIC_REACTION];

      ElectroatomicReactionNativeFactory::createHybridElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getElasticCutoffAngleCosine(),
                        properties.getElectronEvaluationTolerance() );
    }
  }
  else if( distribution_type == CUTOFF_DISTRIBUTION )
  {
    Electroatom::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[CUTOFF_ELASTIC_ELECTROATOMIC_REACTION];

    ElectroatomicReactionNativeFactory::createCutoffElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
                        raw_electroatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getElasticCutoffAngleCosine(),
                        properties.getElectronEvaluationTolerance() );
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

#endif // end MONTE_CARLO_ELECTROATOM_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomNativeFactory_def.hpp
//---------------------------------------------------------------------------//
