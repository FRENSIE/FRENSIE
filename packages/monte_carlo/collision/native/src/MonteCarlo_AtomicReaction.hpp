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
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_PhotoatomicReactionType.hpp"
#include "MonteCarlo_ElectroatomicReactionType.hpp"

namespace MonteCarlo{

//! The atomic reaction base class
class AtomicReaction
{

public:

  //! Constructor
  AtomicReaction()
  { /* ... */ }

  //! Destructor
  virtual ~AtomicReaction()
  { /* ... */ }
  
  //! Test if two Atomic reactions share the same energy grid
  bool isEnergyGridShared( const AtomicReaction& other_reaction ) const;
  
  //! Test if the energy falls within the energy grid
  virtual bool isEnergyWithinEnergyGrid( const double energy ) const = 0;

  //! Return the cross section at the given energy
  virtual double getCrossSection( const double energy ) const = 0;

  //! Return the cross section at the given energy (efficient)
  virtual double getCrossSection( const double energy,
				  const unsigned bin_index ) const = 0;

  //! Return the threshold energy
  virtual double getThresholdEnergy() const = 0;

  //! Return the number of photons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedPhotons( const double energy ) const = 0;

  //! Return the number of electrons emitted from the rxn at the given energy
  virtual unsigned getNumberOfEmittedElectrons( const double energy ) const = 0;

protected:

  //! Return the head of the energy grid
  virtual const double* getEnergyGridHead() const = 0;
};

// Test if two Atomic reactions share the same energy grid
inline bool AtomicReaction::isEnergyGridShared( 
			      const AtomicReaction& other_reaction ) const
{
  return this->getEnergyGridHead() == other_reaction.getEnergyGridHead();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicReaction.hpp
//---------------------------------------------------------------------------//
