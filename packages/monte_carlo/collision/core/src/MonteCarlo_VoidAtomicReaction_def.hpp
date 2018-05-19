//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidAtomicReaction_def.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The void atomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_VOID_ATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_VOID_ATOMIC_REACTION_DEF_HPP

// Std Lib Includes
#include <limits>

namespace MonteCarlo{

// Test if two Atomic reactions share the same energy grid
/*! \details This will return true for all reactions.
 */
template<typename BaseReactionType>
bool VoidAtomicReaction<BaseReactionType>::isEnergyGridShared( const Reaction& ) const
{
  return true;
}

// Test if the energy falls within the energy grid
template<typename BaseReactionType>
bool VoidAtomicReaction<BaseReactionType>::isEnergyWithinEnergyGrid( const double energy ) const
{
  return true;
}

// Return the threshold energy
template<typename BaseReactionType>
double VoidAtomicReaction<BaseReactionType>::getThresholdEnergy() const
{
  return 0.0;
}

// Return the max energy
template<typename BaseReactionType>
double VoidAtomicReaction<BaseReactionType>::getMaxEnergy() const
{
  return std::numeric_limits<double>::max();
}

// Return the cross section at the given energy
template<typename BaseReactionType>
double VoidAtomicReaction<BaseReactionType>::getCrossSection( const double ) const
{
  return 0.0;
}

// Return the cross section at the given energy (efficient)
template<typename BaseReactionType>
double VoidAtomicReaction<BaseReactionType>::getCrossSection( const double, const size_t ) const
{
  return 0.0;
}

// Return the number of photons emitted from the rxn at the given energy
template<typename BaseReactionType>
unsigned VoidAtomicReaction<BaseReactionType>::getNumberOfEmittedPhotons( const double ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename BaseReactionType>
unsigned VoidAtomicReaction<BaseReactionType>::getNumberOfEmittedElectrons( const double ) const
{
  return 0u;
}
  
// Return the number of positrons emitted from the rxn at the given energy
template<typename BaseReactionType>
unsigned VoidAtomicReaction<BaseReactionType>::getNumberOfEmittedPositrons( const double ) const
{
  return 0u;
}

// Return the head of the energy grid
template<typename BaseReactionType>
const double* VoidAtomicReaction<BaseReactionType>::getEnergyGridHead() const
{
  return nullptr;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_VOID_ATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAtomicReaction_def.hpp
//---------------------------------------------------------------------------//
