//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomNativeFactory.hpp
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
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

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
          Teuchos::RCP<ElectroatomCore>& electroatom_core,
        const unsigned hash_grid_bins,
        const BremsstrahlungAngularDistributionType
          photon_distribution_function,
        const bool use_atomic_relaxation_data,
        const double cutoff_angle_cosine )
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
						     hash_grid_bins ) );

  // Create the analog elastic scattering reaction (no moment preserving elastic scattering)
  if ( cutoff_angle_cosine == 1.0 )
  {
    Electroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[ANALOG_ELASTIC_ELECTROATOMIC_REACTION];

    ElectroatomicReactionNativeFactory::createAnalogElasticReaction(
					   raw_electroatom_data,
					   energy_grid,
					   grid_searcher,
					   reaction_pointer );
  }
  // Create the moment preserving elastic scattering reaction (no analog elastic scattering)
  else if ( cutoff_angle_cosine == -1.0 )
  {
    Electroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION];

    ElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction(
					   raw_electroatom_data,
					   energy_grid,
					   grid_searcher,
					   reaction_pointer,
                       cutoff_angle_cosine );
  }
  // Create the hybrid elastic scattering reaction (if cutoff is within range)
  else
  {
    {
      Electroatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[CUTOFF_ELASTIC_ELECTROATOMIC_REACTION];

      ElectroatomicReactionNativeFactory::createCutoffElasticReaction(
					   raw_electroatom_data,
					   energy_grid,
					   grid_searcher,
					   reaction_pointer,
                       cutoff_angle_cosine );
    }
    {
      Electroatom::ReactionMap::mapped_type& reaction_pointer =
        scattering_reactions[MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION];

      ElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction(
					   raw_electroatom_data,
					   energy_grid,
					   grid_searcher,
					   reaction_pointer,
                       cutoff_angle_cosine );
    }
  }

  // Create the bremsstrahlung scattering reaction
  {
    Electroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[BREMSSTRAHLUNG_ELECTROATOMIC_REACTION];

    ElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
						 raw_electroatom_data,
						 energy_grid,
					     grid_searcher,
						 reaction_pointer,
                         photon_distribution_function );
  }

  // Create the atomic excitation scattering reaction
  {
    Electroatom::ReactionMap::mapped_type& reaction_pointer =
      scattering_reactions[ATOMIC_EXCITATION_ELECTROATOMIC_REACTION];

    ElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
                               raw_electroatom_data,
	                           energy_grid,
					           grid_searcher,
                               reaction_pointer );
  }

  Teuchos::Array<Teuchos::RCP<ElectroatomicReaction> > reaction_pointers;

  ElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions(
							   raw_electroatom_data,
							   energy_grid,
					           grid_searcher,
							   reaction_pointers );

  for( unsigned i = 0; i < reaction_pointers.size(); ++i )
  {
    scattering_reactions[reaction_pointers[i]->getReactionType()] =
        reaction_pointers[i];
  }

  // Create the electroatom core
  electroatom_core.reset( new ElectroatomCore( energy_grid,
                                               scattering_reactions,
                                               absorption_reactions,
                                               atomic_relaxation_model,
                                               false,
                                               Utility::LinLin() ) );
}

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
        const unsigned hash_grid_bins,
        const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
          Teuchos::RCP<Electroatom>& electroatom,
        const BremsstrahlungAngularDistributionType
          photon_distribution_function,
        const bool use_atomic_relaxation_data,
        const double cutoff_angle_cosine )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );

  Teuchos::RCP<ElectroatomCore> core;

  ElectroatomNativeFactory::createElectroatomCore(raw_electroatom_data,
                                                  atomic_relaxation_model,
                                                  core,
                                                  hash_grid_bins,
                                                  photon_distribution_function,
                                                  use_atomic_relaxation_data,
                                                  cutoff_angle_cosine );

  // Create the electroatom
  electroatom.reset(
    new Electroatom( electroatom_name,
                     raw_electroatom_data.getAtomicNumber(),
                     atomic_weight,
                     *core ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomNativeFactory.cpp
//---------------------------------------------------------------------------//
