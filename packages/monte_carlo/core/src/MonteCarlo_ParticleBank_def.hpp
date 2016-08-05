//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleBank_def.hpp
//! \author Alex Robinson
//! \brief  The particle bank class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_BANK_DEF_HPP
#define MONTE_CARLO_PARTICLE_BANK_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Push a particle to the bank
/*! \details The bank will take ownership of the particle passed into it. To
 * ensure that it has ownership it will create a copy (clone) of the particle
 * and the input smart pointer will be reset.
 */
template<template<typename> class SmartPointer, typename State>
void ParticleBank::push( SmartPointer<State>& particle )
{
  // Make sure the particle is valid
  testPrecondition( particle.get() );
  // Check that use count is 1
  // testPrecondition( particle.count() == 1 );

  this->push( *particle );

  particle.reset();
}

// Push a neutron into the bank after an interaction
/*! \details The bank will take ownership of the particle passed into it. To
 * ensure that it has ownership it will create a copy (clone) of the particle
 * and the input smart pointer will be reset. The smart pointer must point to
 * a NeutronState.
 */
template<template<typename> class SmartPointer>
void ParticleBank::push( SmartPointer<NeutronState>& neutron,
			 const NuclearReactionType reaction )
{
  // Make sure the particle is valid
  testPrecondition( neutron.get() );
  // Check that use count is 1
  // testPrecondition( particle.count() == 1 );

  this->push( *neutron, reaction );

  neutron.reset();
}

// Pop the top particle from the bank and store it in the smart pointer
template<template<typename> class SmartPointer>
void ParticleBank::pop( SmartPointer<ParticleState>& particle )
{
  // Make sure the bank is not empty
  testPrecondition( !this->isEmpty() );

  particle.reset( this->top().clone() );

  this->pop();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_BANK_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleBank_def.hpp
//---------------------------------------------------------------------------//
