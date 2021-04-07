//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedAtomicRelaxationModel.cpp
//! \author Alex Robinson
//! \brief  Detailed atomic relaxation model class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DetailedAtomicRelaxationModel.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
/*! \details Use this constructor with elements that do not have relaxation
 * info
 */
DetailedAtomicRelaxationModel::DetailedAtomicRelaxationModel()
{ /* ... */ }

// Constructor
DetailedAtomicRelaxationModel::DetailedAtomicRelaxationModel(
            const std::vector<std::shared_ptr<const SubshellRelaxationModel> >&
	    subshell_relaxation_models,
            const double min_photon_energy,
            const double min_electron_energy)
  : d_subshell_relaxation_models(),
    d_min_photon_energy( min_photon_energy ),
    d_min_electron_energy( min_electron_energy )
{
  // Make sure that the array is valid
  //testPrecondition( subshell_reaction_models.size() > 0 );
  // Make sure the min photon energy is valid
  testPrecondition( min_photon_energy > 0.0 );
  // Make sure the min electron energy is valid
  testPrecondition( min_electron_energy > 0.0 );

  for( unsigned i = 0; i < subshell_relaxation_models.size(); ++i )
  {
    const std::shared_ptr<const SubshellRelaxationModel>& model =
      subshell_relaxation_models[i];

    // Neglect duplicate models
    if( d_subshell_relaxation_models.find( model->getVacancySubshell() ) ==
	d_subshell_relaxation_models.end() )
      d_subshell_relaxation_models[model->getVacancySubshell()] = model;
  }
}

// Relax the atom
void
DetailedAtomicRelaxationModel::relaxAtom(
                                        const Data::SubshellType vacancy_shell,
                                        const ParticleState& particle,
                                        ParticleBank& bank ) const
{
  // Check if the vacancy shell has relaxation data
  if( d_subshell_relaxation_models.find( vacancy_shell ) !=
      d_subshell_relaxation_models.end() )
  {
    // Recursively relax subshells
    Data::SubshellType primary_vacancy_shell, secondary_vacancy_shell;

    const std::shared_ptr<const SubshellRelaxationModel>& model =
      d_subshell_relaxation_models.find( vacancy_shell )->second;

    model->relaxSubshell( particle,
                          d_min_photon_energy,
                          d_min_electron_energy,
			  bank,
			  primary_vacancy_shell,
			  secondary_vacancy_shell );

    // Relax the new vacancy
    this->relaxAtom( primary_vacancy_shell, particle, bank );

    // Relax the secondary vacancy
    this->relaxAtom( secondary_vacancy_shell, particle, bank );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedAtomicRelaxationModel.cpp
//---------------------------------------------------------------------------//
