//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedAtomicRelaxationModel.hpp
//! \author Alex Robinson
//! \brief  Detailed atomic relaxation model class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DETAILED_ATOMIC_RELAXATION_MODEL_HPP
#define MONTE_CARLO_DETAILED_ATOMIC_RELAXATION_MODEL_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_SubshellRelaxationModel.hpp"

namespace MonteCarlo{

/*! The detailed atomic relaxation model
 * \details This model accounts for all possible transitions to fill an
 * initial vacancy. It will also follow subsequent vacancies until the atom
 * has relaxed back to its ground state.
 */
class DetailedAtomicRelaxationModel : public AtomicRelaxationModel
{
  
public:

  //! Default constructor
  DetailedAtomicRelaxationModel();

  //! Constructor 
  DetailedAtomicRelaxationModel(
	    const Teuchos::Array<Teuchos::RCP<const SubshellRelaxationModel> >&
	    subshell_relaxtion_models ); 

  //! Destructor
  ~DetailedAtomicRelaxationModel()
  { /* ... */ }

  //! Relax the atom
  void relaxAtom( const SubshellType vacancy_shell,
		  const ParticleState& particle,
		  ParticleBank& bank ) const;

private:
  
  // The map of subshells and their relaxation data
  boost::unordered_map<SubshellType,
		       Teuchos::RCP<const SubshellRelaxationModel> >
  d_subshell_relaxation_models;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DETAILED_ATOMIC_RELAXATION_MODEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedAtomicRelaxationModel.hpp
//---------------------------------------------------------------------------//


