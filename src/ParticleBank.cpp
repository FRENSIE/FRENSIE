//---------------------------------------------------------------------------//
//!
//! \file   ParticleBank.cpp
//! \author Alex Robinson
//! \brief  Particle bank base class definition
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "ParticleBank.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Default Constructor
ParticleBank::ParticleBank()
  : d_particle_states()
{ /* ... */ }

// Check if the bank is empty
bool ParticleBank::empty() const
{
  return d_particle_states.size() == 0;
}

// The size of the bank
ParticleBank::size_type ParticleBank::size() const
{
  return d_particle_states.size();
}

// Access the top element
ParticleBank::reference ParticleBank::top()
{
  return d_particle_states.front();
}

// Access the top element
ParticleBank::const_reference ParticleBank::top() const
{
  return d_particle_states.front();
}

// Push a particle to the bank
void ParticleBank::push( const ParticleBank::value_type& particle )
{
  // Make sure the particle is valid
  testPrecondition( particle.get() );
  
  d_particle_states.push_front( particle );
}

// Push a neutron to the bank
/*! \details This function behaves identically to the push member function
 * that takes a FACEMC::ParticleState base class pointer. It can be
 * overridden in a derived class that needs to store a neutron in a secondary
 * bank if a specific reaction occurs (i.e. fission bank).
 */
void ParticleBank::push( const ParticleBank::value_type& neutron,
			 const NuclearReactionType )
{
  push( neutron );
}

// Pop a particle from the bank
void ParticleBank::pop()
{
  // Make sure there is another particle in the bank
  testPrecondition( d_particle_states.size() > 0 );

  d_particle_states.pop_front();
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end ParticleBank.cpp
//---------------------------------------------------------------------------//
