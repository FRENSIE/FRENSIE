//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidAdjointAtomicReaction_def.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The void adjoint atomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_VOID_ADJOINT_ATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_VOID_ADJOINT_ATOMIC_REACTION_DEF_HPP

// Std Lib Includes
#include <limits>

namespace MonteCarlo{

// Test if two Atomic reactions share the same energy grid
/*! \details This will return true for all reactions.
 */
template<typename BaseReactionType>
bool VoidAdjointAtomicReaction<BaseReactionType>::isEnergyGridShared( const Reaction& ) const
{
  return true;
}

// Test if the energy falls within the energy grid
template<typename BaseReactionType>
bool VoidAdjointAtomicReaction<BaseReactionType>::isEnergyWithinEnergyGrid( const double energy ) const
{
  return true;
}

// Return the threshold energy
template<typename BaseReactionType>
double VoidAdjointAtomicReaction<BaseReactionType>::getThresholdEnergy() const
{
  return 0.0;
}

// Return the max energy
template<typename BaseReactionType>
double VoidAdjointAtomicReaction<BaseReactionType>::getMaxEnergy() const
{
  return std::numeric_limits<double>::max();
}

// Return the cross section at the given energy
template<typename BaseReactionType>
double VoidAdjointAtomicReaction<BaseReactionType>::getCrossSection( const double ) const
{
  return 0.0;
}

// Return the cross section at the given energy (efficient)
template<typename BaseReactionType>
double VoidAdjointAtomicReaction<BaseReactionType>::getCrossSection( const double, const size_t ) const
{
  return 0.0;
}

// Return the number of photons emitted from the rxn at the given energy
template<typename BaseReactionType>
unsigned VoidAdjointAtomicReaction<BaseReactionType>::getNumberOfEmittedAdjointPhotons( const double ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename BaseReactionType>
unsigned VoidAdjointAtomicReaction<BaseReactionType>::getNumberOfEmittedAdjointElectrons( const double ) const
{
  return 0u;
}
  
// Return the number of positrons emitted from the rxn at the given energy
template<typename BaseReactionType>
unsigned VoidAdjointAtomicReaction<BaseReactionType>::getNumberOfEmittedAdjointPositrons( const double ) const
{
  return 0u;
}

// Return the head of the energy grid
template<typename BaseReactionType>
const double* VoidAdjointAtomicReaction<BaseReactionType>::getEnergyGridHead() const
{
  return nullptr;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_VOID_ATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAdjointAtomicReaction_def.hpp
//---------------------------------------------------------------------------//
