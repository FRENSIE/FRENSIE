//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedAtomicRelaxationModel.cpp
//! \author Alex Robinson
//! \brief  Detailed atomic relaxation model class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DetailedAtomicRelaxationModel.hpp"
#include "Utility_ContractException.hpp"

// Default constructor
/*! \details Use this constructor with elements that do not have relaxation
 * info
 */ 
DetailedAtomicRelaxationModel::DetailedAtomicRelaxationModel()
{ /* ... */ }

// Constructor 
DetailedAtomicRelaxationModel::DetailedAtomicRelaxationModel(
                  const Teuchos::Array<Teuchos::RCP<SubshellRelaxationModel> >&
		  subshell_relaxation_models )
{
  // Make sure that the array is valid
  //testPrecondition( subshell_reaction_models.size() > 0 );
  
  for( unsigned i = 0; i < subshell_relaxation_models.size(); ++i )
  {
    const Teuchos::RCP<SubshellRelaxationModel>& model = 
      subshell_relaxation_models[i];
    
    // Neglect duplicate models
    if( d_subshell_relaxation_model.find( model->getVacancySubshell() ) ==
	d_subshell_relaxation_model.end() )
      d_subshell_relaxation_model[model->getVacancySubshell()] = model;
  }
}

// Relax the atom
void 
DetailedAtomicRelaxationModel::relaxAtom( const SubshellType vacancy_shell,
					  const ParticleState& particle,
					  ParticleBank& bank ) const
{
  // Check if the vacancy shell has relaxation data
  if( d_subshell_relaxation_models.find( vacancy_shell ) !=
      d_subshell_relaxation_models.end() )
  {
    // Recursively relax subshells
    SubshellType primary_vacancy_shell, secondary_vacancy_shell;

    const Teuchos::RCP<SubshellRelaxationModel>& model = 
      d_subshell_relaxation_models.find( vacancy_shell )->second;

    model->relaxSubshell( particle, 
			  bank, 
			  primary_vacancy_shell, 
			  secondary_vacancy_shell );

    // Relax the new vacancy
    this->relaxAtom( primary_vacancy_shell, particle, bank );
    
    // Relas the secondary vacancy
    this->relaxAtom( secondary_vacancy_shell, particle, bank );
  }
}

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedAtomicRelaxationModel.cpp
//---------------------------------------------------------------------------//
