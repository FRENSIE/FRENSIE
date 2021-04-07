//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidAtomicReaction.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The void adjoint atomic reaction class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_VOID_ADJOINT_ATOMIC_REACTION_HPP
#define MONTE_CARLO_VOID_ADJOINT_ATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointAtomicReaction.hpp"

namespace MonteCarlo{

//! The void adjoint atomic reaction class
template<typename BaseReactionType>
class VoidAdjointAtomicReaction : public BaseReactionType
{

public:

  //! Constructor
  VoidAdjointAtomicReaction()
  { /* ... */ }

  //! Destructor
  virtual ~VoidAdjointAtomicReaction()
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
  unsigned getNumberOfEmittedAdjointPhotons( const double energy ) const final override;

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedAdjointElectrons( const double energy ) const final override;
  
  //! Return the number of positrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedAdjointPositrons( const double energy ) const final override;

protected:

  //! Return the head of the energy grid
  const double* getEnergyGridHead() const override;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_VoidAdjointAtomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_VOID_ADJOINT_ATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAdjointAtomicReaction.hpp
//---------------------------------------------------------------------------//
