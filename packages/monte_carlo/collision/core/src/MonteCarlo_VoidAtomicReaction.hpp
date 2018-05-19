//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidAtomicReaction.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The void atomic reaction class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_VOID_ATOMIC_REACTION_HPP
#define MONTE_CARLO_VOID_ATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_AtomicReaction.hpp"

namespace MonteCarlo{

//! The void atomic reaction class
template<typename BaseReactionType>
class VoidAtomicReaction : public BaseReactionType
{

public:

  //! Constructor
  VoidAtomicReaction()
  { /* ... */ }

  //! Destructor
  virtual ~VoidAtomicReaction()
  { /* ... */ }

  //! Test if two Atomic reactions share the same energy grid
  bool isEnergyGridShared( const Reaction& other_reaction ) const final override;

  //! Test if the energy falls within the energy grid
  bool isEnergyWithinEnergyGrid( const double energy ) const final override;

  //! Return the threshold energy
  double getThresholdEnergy() const final override;

  //! Return the max energy
  double getMaxEnergy() const final override;

  //! Return the cross section at the given energy
  double getCrossSection( const double energy ) const final override;

  //! Return the cross section at the given energy (efficient)
  double getCrossSection( const double energy,
                          const size_t bin_index ) const final override;

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const final override;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const final override;
  
  //! Return the number of positrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPositrons( const double energy ) const final override;

protected:

  //! Return the head of the energy grid
  const double* getEnergyGridHead() const override;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_VoidAtomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_VOID_ATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAtomicReaction.hpp
//---------------------------------------------------------------------------//
