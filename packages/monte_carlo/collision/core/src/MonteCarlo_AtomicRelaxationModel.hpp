//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicRelaxationModel.hpp
//! \author Alex Robinson
//! \brief  Atomic relaxation model base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_RELAXATION_MODEL_HPP
#define MONTE_CARLO_ATOMIC_RELAXATION_MODEL_HPP

// FRENSIE Includes
#include "Data_SubshellType.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleBank.hpp"

namespace MonteCarlo{

//! The atomic relaxation model base class
class AtomicRelaxationModel
{

public:

  //! Constructor
  AtomicRelaxationModel()
  { /* ... */ }

  //! Destructor
  virtual ~AtomicRelaxationModel()
  { /* ... */ }

  //! Relax atom
  virtual void relaxAtom( const Data::SubshellType vacancy_shell,
			  const ParticleState& particle,
			  ParticleBank& bank ) const = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_RELAXATION_MODEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicRelaxationModel.hpp
//---------------------------------------------------------------------------//



