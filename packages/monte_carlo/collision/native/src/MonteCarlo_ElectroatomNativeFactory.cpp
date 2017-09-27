//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The electroatom native factory class definition.
//!
//---------------------------------------------------------------------------//

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

// Create a electroatom (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * atom. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been
 * requested, a electroionization reaction for each subshell will be created.
 * Otherwise a single total electroionization reaction will be created.
 */
void ElectroatomNativeFactory::createElectroatom(
       const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
       const std::string& electroatom_name,
       const double atomic_weight,
       const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
       const SimulationElectronProperties& properties,
       Teuchos::RCP<Electroatom>& electroatom )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );

  Teuchos::RCP<ElectroatomCore> core;

  // Create the electroatom core
  ElectroatomNativeFactory::createElectroatomCore(
            raw_electroatom_data,
            atomic_relaxation_model,
            properties,
            core );

  // Create the electroatom
  electroatom.reset( new Electroatom( electroatom_name,
                                      raw_electroatom_data.getAtomicNumber(),
                                      atomic_weight,
                                      *core ) );
}

// Create a electroatom core (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * core. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been
 * requested, a electroionization reaction for each subshell will be created.
 * Otherwize a single total electroionization reaction will be created.
 */
void ElectroatomNativeFactory::createElectroatomCore(
        const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
        const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
        const SimulationElectronProperties& properties,
        Teuchos::RCP<ElectroatomCore>& electroatom_core )
{
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );

  electroatom_core.reset( new ElectroatomCore() );

  Electroatom::ReactionMap scattering_reactions, absorption_reactions;

  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
                      raw_electroatom_data.getElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher for this atom
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                              energy_grid,
                              properties.getNumberOfElectronHashGridBins() ) );

  // Create the elastic scattering reaction
  if ( properties.isElasticModeOn() )
  {
    TwoDInterpolationType elastic_interp = properties.getElasticTwoDInterpPolicy();

    if( elastic_interp == LOGLOGLOG_INTERPOLATION )
    {
      ThisType::createElasticElectroatomCore<Utility::LogLogCosLog>(
                                                raw_electroatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                scattering_reactions );
    }
    else if( elastic_interp == LINLINLOG_INTERPOLATION )
    {
      ThisType::createElasticElectroatomCore<Utility::LinLinLog>(
                                                raw_electroatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                scattering_reactions );
    }
    else if( elastic_interp == LINLINLIN_INTERPOLATION )
    {
      ThisType::createElasticElectroatomCore<Utility::LinLinLin>(
                                                raw_electroatom_data,
                                                energy_grid,
                                                grid_searcher,
                                                properties,
                                                scattering_reactions );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Error: the 2D interpolation policy "
                       << elastic_interp <<
                       " is not currently supported!" );
    }
  }

  // Create the bremsstrahlung scattering reaction
  if ( properties.isBremsstrahlungModeOn() )
  {
    Electroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[BREMSSTRAHLUNG_ELECTROATOMIC_REACTION];

    TwoDInterpolationType brem_interp = properties.getBremsstrahlungTwoDInterpPolicy();

    if( brem_interp == LOGLOGLOG_INTERPOLATION )
    {
      ElectroatomicReactionNativeFactory::createBremsstrahlungReaction<ElectroatomicReaction,Utility::LogLogLog>(
                    raw_electroatom_data,
                    energy_grid,
                    grid_searcher,
                    reaction_pointer,
                    properties.getBremsstrahlungAngularDistributionFunction(),
                    properties.isCorrelatedSamplingModeOn(),
                    properties.isUnitBasedInterpolationModeOn(),
                    properties.getElectronEvaluationTolerance() );
    }
    else if( brem_interp == LINLINLOG_INTERPOLATION )
    {
      ElectroatomicReactionNativeFactory::createBremsstrahlungReaction<ElectroatomicReaction,Utility::LinLinLog>(
                    raw_electroatom_data,
                    energy_grid,
                    grid_searcher,
                    reaction_pointer,
                    properties.getBremsstrahlungAngularDistributionFunction(),
                    properties.isCorrelatedSamplingModeOn(),
                    properties.isUnitBasedInterpolationModeOn(),
                    properties.getElectronEvaluationTolerance() );
    }
    else if( brem_interp == LINLINLIN_INTERPOLATION )
    {
      ElectroatomicReactionNativeFactory::createBremsstrahlungReaction<ElectroatomicReaction,Utility::LinLinLin>(
                    raw_electroatom_data,
                    energy_grid,
                    grid_searcher,
                    reaction_pointer,
                    properties.getBremsstrahlungAngularDistributionFunction(),
                    properties.isCorrelatedSamplingModeOn(),
                    properties.isUnitBasedInterpolationModeOn(),
                    properties.getElectronEvaluationTolerance() );
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
  if ( properties.isAtomicExcitationModeOn() )
  {
    Electroatom::ReactionMap::mapped_type& reaction_pointer =
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
    std::vector<std::shared_ptr<ElectroatomicReaction> > reaction_pointers;

    TwoDInterpolationType ionization_interp =
                            properties.getElectroionizationTwoDInterpPolicy();

    if( ionization_interp == LOGLOGLOG_INTERPOLATION )
    {
      ElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<ElectroatomicReaction,Utility::LogLogLog>(
                       raw_electroatom_data,
                       energy_grid,
                       grid_searcher,
                       reaction_pointers,
                       properties.isCorrelatedSamplingModeOn(),
                       properties.isUnitBasedInterpolationModeOn(),
                       properties.getElectronEvaluationTolerance() );
    }
    else if( ionization_interp == LINLINLOG_INTERPOLATION )
    {
      ElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<ElectroatomicReaction,Utility::LinLinLog>(
                       raw_electroatom_data,
                       energy_grid,
                       grid_searcher,
                       reaction_pointers,
                       properties.isCorrelatedSamplingModeOn(),
                       properties.isUnitBasedInterpolationModeOn(),
                       properties.getElectronEvaluationTolerance() );
    }
    else if( ionization_interp == LINLINLIN_INTERPOLATION )
    {
      ElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<ElectroatomicReaction,Utility::LinLinLin>(
                       raw_electroatom_data,
                       energy_grid,
                       grid_searcher,
                       reaction_pointers,
                       properties.isCorrelatedSamplingModeOn(),
                       properties.isUnitBasedInterpolationModeOn(),
                       properties.getElectronEvaluationTolerance() );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Error: the 2D interpolation policy "
                       << ionization_interp <<
                       " is not currently supported!" );
    }

    for( unsigned i = 0; i < reaction_pointers.size(); ++i )
    {
      scattering_reactions[reaction_pointers[i]->getReactionType()] =
        reaction_pointers[i];
    }
  }

  // Create the electroatom core
  electroatom_core.reset( new ElectroatomCore( energy_grid,
                                               scattering_reactions,
                                               absorption_reactions,
                                               atomic_relaxation_model,
                                               false,
                                               Utility::LinLin() ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomNativeFactory.cpp
//---------------------------------------------------------------------------//
