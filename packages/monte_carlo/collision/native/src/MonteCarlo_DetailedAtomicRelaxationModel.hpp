//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicRelaxationModel.hpp
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

// FRENSIE Includes
#include "MonteCarlo_AtomicRelaxationModel.hpp"

/*! The detailed atomic relaxation model
 * \details This model accounts for all possible transitions to fill an
 * initial vacancy. It will also follow subsequent vacancies until the atom
 * has relaxed back to its ground state.
 */
class DetailedAtomicRelaxationModel : public AtomicRelaxationModel
{
  
public:

  //! Constructor for ACE data
  DetailedAtomicRelaxationModel(
			 const Teuchos::Array<SubshellType>& subshell_order,
			 const Teuchos::Array<double>& transition_per_subshell,
			 const Teuchos::Array<double>& raw_relaxation_data );
  { /* ... */ }

  //! Destructor
  ~DetailedAtomicRelaxationModel()
  { /* ... */ }

  //! Relax the atom
  void relaxAtom( const SubshellType vacancy_shell,
		  ParticleBank& bank ) const;

protected:

  //! Subshell relaxation class
  class DetailedSubshellRelaxationModel
  {
    
  };

private:

  // The map of subshells and their relaxation data
  boost::unordered_map<SubshellType,DetailedSubshellRelaxationModel>
  d_subshell_relaxation_models;
}

#endif // end MONTE_CARLO_DETAILED_ATOMIC_RELAXATION_MODEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedAtomicRelaxationModel.hpp
//---------------------------------------------------------------------------//


