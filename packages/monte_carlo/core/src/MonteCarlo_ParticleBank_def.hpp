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
#include "Utility_DesignByContract.hpp"

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

  this->push( *particle );

  particle.reset();
}

// Insert a particle into the bank (Most Efficient/Recommended)
/*! \details The bank will take ownership of the particle passed into it. If
 * the particle pointer is unique (i.e. it has a use count of 1) the bank
 * will simply copy the pointer and the input pointer will be reset to
 * ensure sole ownership. Otherwise it will create a copy (clone) of the
 * particle and the input smart pointer will be reset.
 */
template<typename State>
void ParticleBank::push( std::shared_ptr<State>& particle )
{
  // Make sure the particle is valid
  testPrecondition( particle.get() );

  // If this pointer is unique we can simply take it
  if( particle.use_count() == 1 )
  {
    d_particle_states.push_back( particle );
  }
  // The pointer is not unique - make a clone
  else
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
			 const int reaction )
{
  // Make sure the particle is valid
  testPrecondition( neutron.get() );

  this->push( *neutron, reaction );
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
