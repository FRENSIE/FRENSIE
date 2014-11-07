//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicRelaxationModelACEFactory.cpp
//! \author Alex Robinson
//! \brief  The atomic relaxation model ACE factory class definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AtomicRelaxationModelACEFactory.hpp"
#include "MonteCarlo_DetailedSubshellRelaxationModel.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "MonteCarlo_DetailedAtomicRelaxationModel.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize static member data
const Teuchos::RCP<AtomicRelaxationModel> 
AtomicRelaxationModelACEFactory::default_void_model( 
                                               new VoidAtomicRelaxationModel );

// Create the atomic relaxation model
/*! \details If the use of atomic relaxation data is desired and that data
 * is available for the atom of interest, a detailed atomic relaxation model
 * will be created for the atom. Otherwise a "void" model, which essentially
 * ignores relaxation, will be created.
 */
void AtomicRelaxationModelACEFactory::createAtomicRelaxationModel(
                  const Data::XSSEPRDataExtractor& raw_photoatom_data,
		  Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
		  const bool use_atomic_relaxation_data )
{
  // Check if the model for this atom has already been created
  if( d_relaxation_models.find( raw_photoatom_data.extractAtomicNumber() ) !=
      d_relaxation_models.end() )
  {
    atomic_relaxation_model = 
      d_relaxation_models[raw_photoatom_data.extractAtomicNumber()];
  }
  else if( use_atomic_relaxation_data )
  {
    if( raw_photoatom_data.hasFluorescenceData() )
    {
      // Extract the subshell subshell ENDF designators
      Teuchos::ArrayView<const double> raw_subshell_endf_designators = 
	raw_photoatom_data.extractSubshellENDFDesignators();
      
      Teuchos::Array<MonteCarlo::SubshellType>
	subshells( raw_subshell_endf_designators.size() );
      
      for( unsigned i = 0; i < subshells.size(); ++i )
      {
	subshells[i] = MonteCarlo::convertENDFDesignatorToSubshellEnum(
					    raw_subshell_endf_designators[i] );
      }
      
      // Extract the number of transitions per subshell vacancy
      Teuchos::ArrayView<const double> subshell_transitions = 
	raw_photoatom_data.extractSubshellVacancyTransitionPaths();
      
      // Create a subshell transition model for each subshell
      Teuchos::ArrayView<const double> relo_block = 
	raw_photoatom_data.extractRELOBlock();
      
      Teuchos::ArrayView<const double> xprob_block =
	raw_photoatom_data.extractXPROBBlock();
      
      Teuchos::Array<Teuchos::RCP<SubshellRelaxationModel> >
	subshell_relaxation_models;
      
      this->createSubshellRelaxationModels( subshells,
					    subshell_transitions,
					    relo_block,
					    xprob_block,
					    subshell_relaxation_models );

      atomic_relaxation_model.reset( new DetailedAtomicRelaxationModel(
						subshell_relaxation_models ) );

      // Cache the relaxation model
      d_relaxation_models[raw_photoatom_data.extractAtomicNumber()] = 
	atomic_relaxation_model;
    }
    // No atomic relaxation date is available
    else
    {
      atomic_relaxation_model = 
	AtomicRelaxationModelACEFactory::default_void_model;
    }
  }
  // Ignore atomic relaxation
  else
  {
    atomic_relaxation_model = 
      AtomicRelaxationModelACEFactory::default_void_model;
  }
}

// Create the subshell relaxation models
void AtomicRelaxationModelACEFactory::createSubshellRelaxationModels(
		  const Teuchos::Array<SubshellType>& subshell_designators,
		  const Teuchos::ArrayView<const double>& subshell_transitions,
		  const Teuchos::ArrayView<const double>& relo_block,
		  const Teuchos::ArrayView<const double>& xprob_block,
		  Teuchos::Array<Teuchos::RCP<SubshellRelaxationModel> >&
		  subshell_relaxation_models )
{
  // Make sure the arrays are valid
  testPrecondition( subshell_designators.size() > 0 );
  testPrecondition( subshell_designators.size() ==
		    subshell_transitions.size() );
  testPrecondition( subshell_designators.size() ==
		    relo_block.size() );
  testPrecondition( xprob_block.size() > 0 );

  subshell_relaxation_models.clear();
		    
  for( unsigned i = 0; i < subshell_transitions.size(); ++i )
  {
    unsigned transitions = (unsigned)subshell_transitions[i];
    
    unsigned subshell_data_start = (unsigned)relo_block[i];
    
    // Only create a model if there is at least one transition path
    if( transitions > 0 )
    {
      // Extract the primary transition shells, secondary transition shells,
      // outgoing particle energies and transition CDF
      Teuchos::Array<SubshellType> 
	primary_transition_subshells( transitions );
      
      Teuchos::Array<SubshellType>
	secondary_transition_subshells( transitions );
      
      Teuchos::Array<double>
	outgoing_particle_energies( transitions );
      
      Teuchos::Array<double> transition_cdf( transitions );
      
      for( unsigned j = 0; j < transitions; ++j )
      {
	primary_transition_subshells[j] = 
	  convertENDFDesignatorToSubshellEnum(
					xprob_block[subshell_data_start+j*4] );
	
	secondary_transition_subshells[j] = 
	  convertENDFDesignatorToSubshellEnum(
				      xprob_block[subshell_data_start+j*4+1] );

	outgoing_particle_energies[j] = 
	  xprob_block[subshell_data_start+j*4+2];

	transition_cdf[j] = xprob_block[subshell_data_start+j*4+3];
      }

      Teuchos::RCP<SubshellRelaxationModel> subshell_model(
				        new DetailedSubshellRelaxationModel(
						subshell_designators[i],
						primary_transition_subshells,
						secondary_transition_subshells,
						outgoing_particle_energies,
						transition_cdf ) );

      subshell_relaxation_models.push_back( subshell_model );
    }
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicRelaxationModelACEFactory.cpp
//---------------------------------------------------------------------------//
