//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomACEFactory.hpp
//! \author Alex Robinson
//! \brief  The photoatom ace factory class definition.
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomACEFactory.hpp"
#include "MonteCarlo_PhotoatomicReactionACEFactory.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a photoatom core (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this 
 * core. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been 
 * requested, a photoelectric reaction for each subshell will be created.
 * Otherwize a single total photoelectric reaction will be created.
 */
void PhotoatomACEFactory::createPhotoatomCore(
            const Data::XSSEPRDataExtractor& raw_photoatom_data,
	    const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	    Teuchos::RCP<PhotoatomCore>& photoatom_core,
	    const bool use_doppler_broadening_data,
	    const bool use_detailed_pair_production_data,
	    const bool use_atomic_relaxation_data )
{
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );

  photoatom_core.reset( new PhotoatomCore() );

  Photoatom::ReactionMap scattering_reactions, absorption_reactions;

  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( raw_photoatom_data.extractPhotonEnergyGrid() );

  // Create the incoherent scattering reaction
  {
    Photoatom::ReactionMap::mapped_type& reaction_pointer = 
      scattering_reactions[INCOHERENT_PHOTOATOMIC_REACTION];
    
    PhotoatomicReactionACEFactory::createIncoherentReaction(
						 raw_photoatom_data,
						 energy_grid,
						 reaction_pointer,
						 use_doppler_broadening_data );
  }
  
  // Create the coherent scattering reaction
  {
    Photoatom::ReactionMap::mapped_type& reaction_pointer = 
      scattering_reactions[COHERENT_PHOTOATOMIC_REACTION];
    
    PhotoatomicReactionACEFactory::createCoherentReaction( raw_photoatom_data,
							   energy_grid,
							   reaction_pointer );
  }
  
  // Create the pair production reaction
  {
    Photoatom::ReactionMap::mapped_type& reaction_pointer = 
      scattering_reactions[PAIR_PRODUCTION_PHOTOATOMIC_REACTION];

    PhotoatomicReactionACEFactory::createPairProductionReaction(
					   raw_photoatom_data,
					   energy_grid,
					   reaction_pointer,
					   use_detailed_pair_production_data );
  }
  
  // Create the photoelectric reaction(s)
  if( use_atomic_relaxation_data )
  {
    Teuchos::Array<Teuchos::RCP<PhotoatomicReaction> > reaction_pointers;

    PhotoatomicReactionACEFactory::createSubshellPhotoelectricReactions(
							   raw_photoatom_data,
							   energy_grid,
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

    PhotoatomicReactionACEFactory::createTotalPhotoelectricReaction(
							    raw_photoatom_data,
							    energy_grid,
							    reaction_pointer );
  }

  // Create the heating reaction
  Photoatom::ReactionMap::mapped_type& reaction_pointer = 
      absorption_reactions[HEATING_PHOTOATOMIC_REACTION];

  PhotoatomicReactionACEFactory::createHeatingReaction( raw_photoatom_data,
							energy_grid,
							reaction_pointer );
			
  // Create the photoatom core
  photoatom_core.reset( new PhotoatomCore( energy_grid,
					   scattering_reactions,
					   absorption_reactions,
					   atomic_relaxation_model,
					   true,
					   Utility::LogLog() ) );	   
}

// Create a photoatom (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * atom. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been
 * requested, a photoelectric reaction for each subshell will be created. 
 * Otherwise a single total photoelectric reaction will be created.
 */
void PhotoatomACEFactory::createPhotoatom(
	    const Data::XSSEPRDataExtractor& raw_photoatom_data,
	    const std::string& photoatom_name,
	    const double atomic_weight,
	    const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	    Teuchos::RCP<Photoatom>& photoatom,
	    const bool use_doppler_broadening_data,
	    const bool use_detailed_pair_production_data,
	    const bool use_atomic_relaxation_data )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );
  
  Teuchos::RCP<PhotoatomCore> core;

  PhotoatomACEFactory::createPhotoatomCore( raw_photoatom_data,
					    atomic_relaxation_model,
					    core,
					    use_doppler_broadening_data,
					    use_detailed_pair_production_data,
					    use_atomic_relaxation_data );
					    
  // Create the photoatom
  photoatom.reset( new Photoatom( photoatom_name,
				  raw_photoatom_data.extractAtomicNumber(),
				  atomic_weight,
				  *core ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomACEFactory.cpp
//---------------------------------------------------------------------------//
