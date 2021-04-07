//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicReaction.hpp
//! \author Luke Kersting
//! \brief  The atomic reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_REACTION_HPP
#define MONTE_CARLO_ATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_Reaction.hpp"

namespace MonteCarlo{

//! The atomic reaction base class
class AtomicReaction : public Reaction
{

public:

  //! Constructor
  AtomicReaction()
  { /* ... */ }

  //! Destructor
  virtual ~AtomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedPhotons( const double energy ) const = 0;

  //! Return the number of electrons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedElectrons( const double energy ) const = 0;
  
  //! Return the number of positrons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedPositrons( const double energy ) const = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicReaction.hpp
//---------------------------------------------------------------------------//
