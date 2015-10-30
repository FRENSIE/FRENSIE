//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomNativeFactory.cpp
//! \author Alex Robinson
//! \brief  The photoatom native factory class declaration.
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomNativeFactory.hpp"
#include "MonteCarlo_PhotoatomicReactionNativeFactory.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a photoatom core (using the provided atomic relaxation model)
void PhotoatomNativeFactory::createPhotoatomCore(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	 Teuchos::RCP<PhotoatomCore>& photoatom_core,
	 const unsigned hash_grid_bins,
	 const IncoherentModelType incoherent_model,
	 const double kahn_sampling_cutoff_energy,
	 const bool use_detailed_pair_production_data,
	 const bool use_atomic_relaxation_data )
{
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );

  photoatom_core.reset( new PhotoatomCore() );

  Photoatom::ReactionMap scattering_reactions, absorption_reactions;

  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( raw_photoatom_data.getPhotonEnergyGrid().begin(),
		      raw_photoatom_data.getPhotonEnergyGrid().end() );
  
  // Construct the hash-based grid searcher for this atom
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
						     energy_grid,
						     hash_grid_bins ) );

  // Create the incoherent scattering reaction(s)
  {
    Teuchos::Array<Teuchos::RCP<PhotoatomicReaction> > reaction_pointers;

    PhotoatomicReactionNativeFactory::createIncoherentReactions(
						 raw_photoatom_data,
						 energy_grid,
						 grid_searcher,
						 reaction_pointers,
						 incoherent_model,
						 kahn_sampling_cutoff_energy );

    for( unsigned i = 0; i < reaction_pointers.size(); ++i )
    {
      scattering_reactions[reaction_pointers[i]->getReactionType()] = 
	reaction_pointers[i];
    }
  }

  // Create the coherent scattering reaction
  {
    Photoatom::ReactionMap::mapped_type& reaction_pointer = 
      scattering_reactions[COHERENT_PHOTOATOMIC_REACTION];

    PhotoatomicReactionNativeFactory::createCoherentReaction( 
							    raw_photoatom_data,
							    energy_grid,
							    grid_searcher,
							    reaction_pointer );
  }

  // Create the pair production reaction
  {
    Photoatom::ReactionMap::mapped_type& reaction_pointer = 
      scattering_reactions[PAIR_PRODUCTION_PHOTOATOMIC_REACTION];

    PhotoatomicReactionNativeFactory::createPairProductionReaction(
					   raw_photoatom_data,
					   energy_grid,
					   grid_searcher,
					   reaction_pointer,
					   use_detailed_pair_production_data );
  }

  // Create the photoelectric reaction(s)
  if( use_atomic_relaxation_data )
  {
    Teuchos::Array<Teuchos::RCP<PhotoatomicReaction> > reaction_pointers;

    PhotoatomicReactionNativeFactory::createSubshellPhotoelectricReactions(
							   raw_photoatom_data,
							   energy_grid,
							   grid_searcher,
							   reaction_pointers );

    for( unsigned i = 0; i < reaction_pointers.size(); ++i )
    {
      absorption_reactions[reaction_pointers[i]->getReactionType()] = 
	reaction_pointers[i];
    }
  }
  else
  {
    Photoatom::ReactionMap::mapped_type& reaction_pointer = 
      absorption_reactions[TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION];

    PhotoatomicReactionNativeFactory::createTotalPhotoelectricReaction(
							    raw_photoatom_data,
							    energy_grid,
							    grid_searcher,
							    reaction_pointer );
  }

  // Create the heating reaction
  Photoatom::ReactionMap::mapped_type& reaction_pointer = 
    absorption_reactions[HEATING_PHOTOATOMIC_REACTION];

  PhotoatomicReactionNativeFactory::createHeatingReaction( raw_photoatom_data,
							   energy_grid,
							   grid_searcher,
							   reaction_pointer );

  // Create the photoatom core
  photoatom_core.reset( new PhotoatomCore( energy_grid,
					   grid_searcher,
					   scattering_reactions,
					   absorption_reactions,
					   atomic_relaxation_model,
					   false,
					   Utility::LinLin() ) );
}

// Create the photoatom (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * atom. Special care must be taken to assure that the model corresponds with
 * the atom of interest. If the use of atomic relaxation data has been 
 * requested, a photoelectric reaction for each subshell will be created.
 * Otherwise a single total photoelectric reaction will be created. If
 * impulse approximation data is requested, an incoherent reaction for each 
 * subshell will be created (can only be done with the impulse approximation). 
 * Otherwise a single incoherent reaction will be created (using the more
 * common Waller-Hartree theory).
 */
void PhotoatomNativeFactory::createPhotoatom(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 const std::string& photoatom_name,
	 const double atomic_weight,
	 const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	 Teuchos::RCP<Photoatom>& photoatom,
	 const unsigned hash_grid_bins,
	 const IncoherentModelType incoherent_model,
	 const double kahn_sampling_cutoff_energy,
	 const bool use_detailed_pair_production_data,
	 const bool use_atomic_relaxation_data )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );

  Teuchos::RCP<PhotoatomCore> core;

  PhotoatomNativeFactory::createPhotoatomCore( 
					     raw_photoatom_data,
					     atomic_relaxation_model,
					     core,
					     hash_grid_bins,
					     incoherent_model,
					     kahn_sampling_cutoff_energy,
					     use_detailed_pair_production_data,
					     use_atomic_relaxation_data );

  // Create the photoatom
  photoatom.reset( new Photoatom( photoatom_name,
				  raw_photoatom_data.getAtomicNumber(),
				  atomic_weight,
				  *core ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomNativeFactory.cpp
//---------------------------------------------------------------------------//
