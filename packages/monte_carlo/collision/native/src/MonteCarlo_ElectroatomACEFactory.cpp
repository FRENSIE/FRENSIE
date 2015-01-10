//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomACEFactory.hpp
//! \author Luke Kersting
//! \brief  The electroatom ace factory class definition.
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomACEFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionACEFactory.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a electroatom core (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this 
 * core. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been 
 * requested, a electroionization reaction for each subshell will be created.
 * Otherwize a single total electroionization reaction will be created.
 */
void ElectroatomACEFactory::createElectroatomCore(
            const Data::XSSEPRDataExtractor& raw_electroatom_data,
            const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
            Teuchos::RCP<ElectroatomCore>& electroatom_core,
            const bool use_atomic_relaxation_data )
{
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );

  electroatom_core.reset( new ElectroatomCore() );

  Electroatom::ReactionMap scattering_reactions, absorption_reactions;

  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( raw_electroatom_data.extractElectronEnergyGrid() );

  // Create the bremsstrahlung scattering reaction
  {
    Electroatom::ReactionMap::mapped_type& reaction_pointer = 
      scattering_reactions[BREMSSTRAHLUNG_ELECTROATOMIC_REACTION];
    
    ElectroatomicReactionACEFactory::createBremsstrahlungReaction(
						 raw_electroatom_data,
						 energy_grid,
						 reaction_pointer,
						 use_doppler_broadening_data );
  }
  
  // Create the atomic excitation scattering reaction
  {
    Electroatom::ReactionMap::mapped_type& reaction_pointer = 
      scattering_reactions[ATOMIC_EXCITATION_ELECTROATOMIC_REACTION];
    
    ElectroatomicReactionACEFactory::createAtomicExcitationReaction( 
                               raw_electroatom_data,
	                           energy_grid,
                               reaction_pointer );
  }
  
  // Create the pair production reaction
  {
    Electroatom::ReactionMap::mapped_type& reaction_pointer = 
      scattering_reactions[PAIR_PRODUCTION_ELECTROATOMIC_REACTION];

    ElectroatomicReactionACEFactory::createPairProductionReaction(
					   raw_electroatom_data,
					   energy_grid,
					   reaction_pointer,
					   use_detailed_pair_production_data );
  }
  
  // Create the photoelectric reaction(s)
  if( use_atomic_relaxation_data )
  {
    Teuchos::Array<Teuchos::RCP<ElectroatomicReaction> > reaction_pointers;

    ElectroatomicReactionACEFactory::createSubshellElectroelectricReactions(
							   raw_electroatom_data,
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
    Electroatom::ReactionMap::mapped_type& reaction_pointer = 
      absorption_reactions[TOTAL_ELECTROELECTRIC_ELECTROATOMIC_REACTION];

    ElectroatomicReactionACEFactory::createTotalElectroelectricReaction(
							    raw_electroatom_data,
							    energy_grid,
							    reaction_pointer );
  }

  // Create the heating reaction
  Electroatom::ReactionMap::mapped_type& reaction_pointer = 
      absorption_reactions[HEATING_ELECTROATOMIC_REACTION];

  ElectroatomicReactionACEFactory::createHeatingReaction( raw_electroatom_data,
							energy_grid,
							reaction_pointer );
			
  // Create the electroatom core
  electroatom_core.reset( new ElectroatomCore( energy_grid,
					   scattering_reactions,
					   absorption_reactions,
					   atomic_relaxation_model,
					   true,
					   Utility::LogLog() ) );	   
}

// Create a electroatom (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * atom. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been
 * requested, a photoelectric reaction for each subshell will be created. 
 * Otherwise a single total photoelectric reaction will be created.
 */
void ElectroatomACEFactory::createElectroatom(
	    const Data::XSSEPRDataExtractor& raw_electroatom_data,
	    const std::string& electroatom_name,
	    const double atomic_weight,
	    const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	    Teuchos::RCP<Electroatom>& electroatom,
	    const bool use_doppler_broadening_data,
	    const bool use_detailed_pair_production_data,
	    const bool use_atomic_relaxation_data )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );
  
  Teuchos::RCP<ElectroatomCore> core;

  ElectroatomACEFactory::createElectroatomCore( raw_electroatom_data,
					    atomic_relaxation_model,
					    core,
					    use_doppler_broadening_data,
					    use_detailed_pair_production_data,
					    use_atomic_relaxation_data );
					    
  // Create the electroatom
  electroatom.reset( new Electroatom( electroatom_name,
				  raw_electroatom_data.extractAtomicNumber(),
				  atomic_weight,
				  *core ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomACEFactory.cpp
//---------------------------------------------------------------------------//
