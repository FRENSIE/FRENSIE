//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronatomNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The positron-atom native factory class template definition.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONATOM_NATIVE_FACTORY_DEF_HPP
#define MONTE_CARLO_POSITRONATOM_NATIVE_FACTORY_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_PositronatomNativeFactory.hpp"
#include "MonteCarlo_PositronatomicReactionNativeFactory.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_Vector.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a positron-atom core (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * core. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been
 * requested, a electroionization reaction for each subshell will be created.
 * Otherwise a single total electroionization reaction will be created.
 */
template <typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
void PositronatomNativeFactory::createPositronatomCore(
   const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
   const std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
   const SimulationElectronProperties& properties,
   std::shared_ptr<const PositronatomCore>& positronatom_core )
{
  // Make sure the atomic relaxation model is valid
  testPrecondition( atomic_relaxation_model.get() );

  positronatom_core.reset( new PositronatomCore() );

  Positronatom::ConstReactionMap scattering_reactions, absorption_reactions;

  // Extract the common energy grid used for this atom
  std::shared_ptr<const std::vector<double> > energy_grid(
    new std::vector<double>( raw_positronatom_data.getElectronEnergyGrid().begin(),
                             raw_positronatom_data.getElectronEnergyGrid().end() ) );

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
            ThisType::createElasticPositronatomCore<Utility::LogNudgedLogCosLog,Utility::Direct>(
                                                  raw_positronatom_data,
                                                  energy_grid,
                                                  grid_searcher,
                                                  properties,
                                                  scattering_reactions );
          }
          else
          {
            ThisType::createElasticPositronatomCore<Utility::LogLogCosLog,Utility::Direct>(
                                                  raw_positronatom_data,
                                                  energy_grid,
                                                  grid_searcher,
                                                  properties,
                                                  scattering_reactions );
          }
        }
      }
      else
      {
        ThisType::createElasticPositronatomCore<TwoDInterpPolicy,Utility::Direct>(
                                                raw_positronatom_data,
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
          ThisType::createElasticPositronatomCore<Utility::LogNudgedLogCosLog,Utility::Correlated>(
                                                  raw_positronatom_data,
                                                  energy_grid,
                                                  grid_searcher,
                                                  properties,
                                                  scattering_reactions );
        }
        else
        {
          ThisType::createElasticPositronatomCore<Utility::LogLogCosLog,Utility::Correlated>(
                                                  raw_positronatom_data,
                                                  energy_grid,
                                                  grid_searcher,
                                                  properties,
                                                  scattering_reactions );
        }
      }
      else
      {
        ThisType::createElasticPositronatomCore<TwoDInterpPolicy,Utility::Correlated>(
                                                raw_positronatom_data,
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
    Positronatom::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[BREMSSTRAHLUNG_POSITRONATOMIC_REACTION];

    PositronatomicReactionNativeFactory::createBremsstrahlungReaction<TwoDInterpPolicy,TwoDGridPolicy>(
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
    Positronatom::ConstReactionMap::mapped_type& reaction_pointer =
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
    std::vector<std::shared_ptr<const PositronatomicReaction> > reaction_pointers;

    PositronatomicReactionNativeFactory::createSubshellPositronionizationReactions<TwoDInterpPolicy,TwoDGridPolicy>(
                      raw_positronatom_data,
                      energy_grid,
                      grid_searcher,
                      reaction_pointers,
                      properties.getElectroionizationSamplingMode(),
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
template <typename TwoDInterpPolicy,template<typename> class TwoDGridPolicy>
void PositronatomNativeFactory::createElasticPositronatomCore(
      const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      const SimulationElectronProperties& properties,
      Positronatom::ConstReactionMap& scattering_reactions )
{
  // Get the elastic distribution type
  ElasticElectronDistributionType distribution_type =
                            properties.getElasticElectronDistributionMode();

  if( distribution_type == COUPLED_DISTRIBUTION )
  {
    Positronatom::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[COUPLED_ELASTIC_POSITRONATOMIC_REACTION];

    PositronatomicReactionNativeFactory::createCoupledElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
                        raw_positronatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getCoupledElasticSamplingMode(),
                        properties.getElectronEvaluationTolerance() );
  }
  else if( distribution_type == DECOUPLED_DISTRIBUTION )
  {
    Positronatom::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION];

    PositronatomicReactionNativeFactory::createDecoupledElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
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
      Positronatom::ConstReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION];

      PositronatomicReactionNativeFactory::createDecoupledElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
                        raw_positronatom_data,
                        energy_grid,
                        grid_searcher,
                        reaction_pointer,
                        properties.getElectronEvaluationTolerance() );
    }
    // Create the moment preserving elastic scattering reaction (no coupled elastic scattering)
    else if ( properties.getElasticCutoffAngleCosine() == -1.0 )
    {
      Positronatom::ConstReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[MOMENT_PRESERVING_ELASTIC_POSITRONATOMIC_REACTION];

      PositronatomicReactionNativeFactory::createMomentPreservingElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
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
      Positronatom::ConstReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[HYBRID_ELASTIC_POSITRONATOMIC_REACTION];

      PositronatomicReactionNativeFactory::createHybridElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
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
    Positronatom::ConstReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[CUTOFF_ELASTIC_POSITRONATOMIC_REACTION];

    PositronatomicReactionNativeFactory::createCutoffElasticReaction<TwoDInterpPolicy,TwoDGridPolicy>(
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
                     "elastic distribution type "
                     << distribution_type <<
                     " is not currently supported!" );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRONATOM_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomNativeFactory_def.hpp
//---------------------------------------------------------------------------//
