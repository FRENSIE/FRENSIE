//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleBank.cpp
//! \author Alex Robinson
//! \brief  Particle bank base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleBank.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Default Constructor
ParticleBank::ParticleBank()
  : d_particle_states( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
{ /* ... */ }

// Check if the bank is empty
bool ParticleBank::empty() const
{
  // Make sure the bank has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() < 
		    d_particle_states.size() );
  
  return 
    d_particle_states[Utility::GlobalOpenMPSession::getThreadId()].size() == 0;
}

// The size of the bank
ParticleBank::size_type ParticleBank::size() const
{
  // Make sure the bank has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() < 
		    d_particle_states.size() );
  
  return d_particle_states[Utility::GlobalOpenMPSession::getThreadId()].size();
}

// Access the top element
ParticleBank::reference ParticleBank::top()
{
  // Make sure the bank has been set up correctly
  testPrecondition ( Utility::GlobalOpenMPSession::getThreadId() < 
		     d_particle_states.size() );
  
  return 
    d_particle_states[Utility::GlobalOpenMPSession::getThreadId()].front();
}

// Access the top element
ParticleBank::const_reference ParticleBank::top() const
{
  // Make sure the bank has been set up correctly
  testPrecondition ( Utility::GlobalOpenMPSession::getThreadId() < 
		     d_particle_states.size() );
  
  return 
    d_particle_states[Utility::GlobalOpenMPSession::getThreadId()].front();
}

// Push a particle to the bank
void ParticleBank::push( const ParticleBank::value_type& particle )
{
  // Make sure the particle is valid
  testPrecondition( particle.get() );
  // Make sure the bank has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() < 
		    d_particle_states.size() );
  
  d_particle_states[Utility::GlobalOpenMPSession::getThreadId()].push_back( 
								    particle );
}

// Push a neutron to the bank
/*! \details This function behaves identically to the push member function
 * that takes a Facemc::ParticleState base class pointer. It can be
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
  // Make sure the bank has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() < 
		    d_particle_states.size() );
  // Make sure there is another particle in the bank
  testPrecondition( d_particle_states[Utility::GlobalOpenMPSession::getThreadId()].size() > 0 );

  d_particle_states[Utility::GlobalOpenMPSession::getThreadId()].pop_front();
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleBank.cpp
//---------------------------------------------------------------------------//
