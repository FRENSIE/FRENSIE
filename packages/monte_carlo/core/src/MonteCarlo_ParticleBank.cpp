//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleBank.cpp
//! \author Alex Robinson
//! \brief  Particle bank base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default Constructor
ParticleBank::ParticleBank()
  : d_particle_states()
{ /* ... */ }

// Check if the bank is empty
bool ParticleBank::isEmpty() const
{
  return d_particle_states.size() == 0;
}

// The size of the bank
unsigned long long ParticleBank::size() const
{
  return d_particle_states.size();
}

// Access the top element
ParticleState& ParticleBank::top()
{
  // Make sure there is at least one particle in the bank
  testPrecondition( this->size() > 0 );

  return *d_particle_states.front();
}

// Access the top element
const ParticleState& ParticleBank::top() const
{
  // Make sure there is at least one particle in the bank
  testPrecondition( this->size() > 0 );

  return *d_particle_states.front();
}

// Push a particle to the bank
/*! \details The bank will take ownership of the particle passed into it. To
 * ensure that it has ownership it will create a copy (clone) of the particle.
 */
void ParticleBank::push( const ParticleState& particle )
{
  d_particle_states.emplace_back( particle.clone() );
}

// Insert a neutron into the bank after an interaction (Most Efficient/Recommended)
/*! \details This function behaves identically to the push member function
 * that takes a MonteCarlo::ParticleState base class pointer. It can be
 * overridden in a derived class that needs to store a neutron in a secondary
 * bank if a specific reaction occurs (i.e. fission bank).
 */
void ParticleBank::push( std::shared_ptr<NeutronState>& neutron,
                         const int reaction )
{
  this->push( neutron );
}

// Push a neutron to the bank
/*! \details This function behaves identically to the push member function
 * that takes a MonteCarlo::ParticleState base class pointer. It can be
 * overridden in a derived class that needs to store a neutron in a secondary
 * bank if a specific reaction occurs (i.e. fission bank).
 */
void ParticleBank::push( const NeutronState& neutron,
			 const int )
{
  this->push( neutron );
}

// Pop a particle from the bank
void ParticleBank::pop()
{
  // Make sure the bank is not empty
  testPrecondition( !this->isEmpty() );

  d_particle_states.pop_front();
}

// Check if the bank is sorted
bool ParticleBank::isSorted( const CompareFunctionType& compare_function )
{
  return std::is_sorted( d_particle_states.begin(),
			 d_particle_states.end(),
			 std::bind<bool>(compare_function,
					   std::bind<const ParticleState&>(ParticleBank::dereference, std::placeholders::_1),
					   std::bind<const ParticleState&>(ParticleBank::dereference, std::placeholders::_2) ) );
}

// Sort the particle states
bool ParticleBank::sort( const CompareFunctionType& compare_function )
{
  d_particle_states.sort( std::bind<bool>(compare_function,
					    std::bind<const ParticleState&>(ParticleBank::dereference, std::placeholders::_1),
					    std::bind<const ParticleState&>(ParticleBank::dereference, std::placeholders::_2) ) );
}

// Merge the bank with another bank
/*! Both banks must be sorted before calling this method. The input bank will
 * be emptied by this operation.
 */
void ParticleBank::merge( ParticleBank& other_bank,
			  const CompareFunctionType& compare_function )
{
  // Make sure the states are sorted
  testPrecondition( this->isSorted( compare_function ) );
  testPrecondition( other_bank.isSorted( compare_function ) );

  d_particle_states.merge( other_bank.d_particle_states,
			   std::bind<bool>(compare_function,
					     std::bind<const ParticleState&>(ParticleBank::dereference, std::placeholders::_1),
					     std::bind<const ParticleState&>(ParticleBank::dereference, std::placeholders::_2) ) );
}

// Splice the bank with another bank
/*! The contents of the input bank are added to the end of this bank. The
 * input bank will be emptied by this operation.
 */
void ParticleBank::splice( ParticleBank& other_bank )
{
  d_particle_states.splice( d_particle_states.end(),
			    other_bank.d_particle_states );
}

EXPLICIT_CLASS_SERIALIZE_INST( ParticleBank );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleBank.cpp
//---------------------------------------------------------------------------//
