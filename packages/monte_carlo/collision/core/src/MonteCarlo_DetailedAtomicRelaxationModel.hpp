//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedAtomicRelaxationModel.hpp
//! \author Alex Robinson
//! \brief  Detailed atomic relaxation model class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DETAILED_ATOMIC_RELAXATION_MODEL_HPP
#define MONTE_CARLO_DETAILED_ATOMIC_RELAXATION_MODEL_HPP

// Std Lib Includes
#include <memory>
#include <unordered_map>

// FRENSIE Includes
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_SubshellRelaxationModel.hpp"
#include "Utility_Vector.hpp"

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
	    const std::vector<std::shared_ptr<const SubshellRelaxationModel> >&
	    subshell_relaxation_models,
            const double min_photon_energy,
            const double min_electron_energy );

  //! Destructor
  ~DetailedAtomicRelaxationModel()
  { /* ... */ }

  //! Relax the atom
  void relaxAtom( const Data::SubshellType vacancy_shell,
		  const ParticleState& particle,
		  ParticleBank& bank ) const;

private:

  // The map of subshells and their relaxation data
  std::unordered_map<Data::SubshellType,std::shared_ptr<const SubshellRelaxationModel> >
  d_subshell_relaxation_models;

  // The min photon energy
  double d_min_photon_energy;

  // The min electron energy
  double d_min_electron_energy;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DETAILED_ATOMIC_RELAXATION_MODEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedAtomicRelaxationModel.hpp
//---------------------------------------------------------------------------//


