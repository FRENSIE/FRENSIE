//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidAtomicRelaxationModel.hpp
//! \author Alex Robinson
//! \brief  Void atomic relaxation model class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_VOID_ATOMIC_RELAXATION_MODEL_HPP
#define MONTE_CARLO_VOID_ATOMIC_RELAXATION_MODEL_HPP

// FRENSIE Includes
#include "MonteCarlo_AtomicRelaxationModel.hpp"

namespace MonteCarlo{

/*! The void atomic relaxation model class
 * \details This class can be used to ignore atomic relaxation.
 */
class VoidAtomicRelaxationModel : public AtomicRelaxationModel
{

public:

  //! Constructor
  VoidAtomicRelaxationModel()
  { /* ... */ }

  //! Destructor
  ~VoidAtomicRelaxationModel()
  { /* ... */ }

  //! Relax atom
  void relaxAtom( const Data::SubshellType vacancy_shell,
                  const ParticleState& particle,
                  ParticleBank& bank ) const;
};

// Relax atom
inline void VoidAtomicRelaxationModel::relaxAtom(
					      const Data::SubshellType vacancy_shell,
					      const ParticleState& particle,
					      ParticleBank& bank ) const
{ /* ... */ }

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_VOID_ATOMIC_RELAXATION_MODEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAtomicRelaxationModel.hpp
//---------------------------------------------------------------------------//
