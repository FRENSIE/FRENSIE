//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointAtomicReaction.hpp
//! \author Alex Robinson
//! \brief  The adjoint atomic reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ATOMIC_REACTION_HPP
#define MONTE_CARLO_ADJOINT_ATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_Reaction.hpp"

namespace MonteCarlo{

//! The adjoint atomic reaction base class
class AdjointAtomicReaction : public Reaction
{

public:

  //! Constructor
  AdjointAtomicReaction()
  { /* ... */ }

  //! Destructor
  virtual ~AdjointAtomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedAdjointPhotons( const double energy ) const = 0;

  //! Return the number of electrons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedAdjointElectrons( const double energy ) const = 0;
  
  //! Return the number of positrons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedAdjointPositrons( const double energy ) const = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointAtomicReaction.hpp
//---------------------------------------------------------------------------//
