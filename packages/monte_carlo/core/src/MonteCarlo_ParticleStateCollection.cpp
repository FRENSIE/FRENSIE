//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleStateCollection
//! \author Alex Robinson
//! \brief  The particle state collection definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_ParticleStateCollection.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Check if the collection is empty
bool ParticleStateCollection::empty() const
{
  return d_particle_state_copies.size() == 0;
}

// The size of the collection
ParticleStateCollection::size_type ParticleStateCollection::size() const
{
  return d_particle_state_copies.size();
}

// Access the top element
ParticleStateCollection::reference ParticleStateCollection::top()
{
  // Make sure there is at least one particle in the collection
  testPrecondition( this->size() > 0 );
  
  return d_particle_state_copies.front();
}

// Access the top element
ParticleStateCollection::const_reference ParticleStateCollection::top() const
{
  // Make sure there is at least one particle in the collection
  testPrecondition( this->size() > 0 );
  
  return d_particle_state_copies.front();
}
  
// Insert a particle state copy into the collection
void ParticleStateCollection::push( const value_type& particle )
{
  // Make sure the particle is valid
  testPrecondition( particle.get() );
  
  // Create a copy of the particle to add to the collection
  value_type particle_copy = particle->clone();
  
  d_particle_state_copies.push_back( particle_copy );
}

// Pop a particle state from the collection
void ParticleStateCollection::pop()
{
  // Make sure the collection is not empty
  testPrecondition( !this->empty() );
  
  d_particle_state_copies.pop_front();
}

// Check if the collection is sorted by history number
bool ParticleStateCollection::isSorted() const
{
  return std::is_sorted( d_particle_state_copies.begin(),
			 d_particle_state_copies.end(),
			 ParticleStateCollection::compareStates );
}

// Sort the particle states in increasing history number order
void ParticleStateCollection::sort()
{
  d_particle_state_copies.sort( ParticleStateCollection::compareStates );
}

// Merge the collection with another collection
/*! \details The input collection will be emptied by this operation. Both
 * collections must be sorted before calling this method.
 */
void ParticleStateCollection::merge( ParticleStateCollection& other_collection )
{
  // Make sure the collections are sorted
  testPrecondition( this->isSorted() );
  testPrecondition( other_collection.isSorted() );
  
  d_particle_state_copies.merge( other_collection.d_particle_state_copies,
				 ParticleStateCollection::compareStates );
}

// Compare two particle states
bool ParticleStateCollection::compareStates( const value_type& state_a,
					     const value_type& state_b )
{
  return state_a->getHistoryNumber() < state_b->getHistoryNumber();
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleStateCollection.cpp
//---------------------------------------------------------------------------//
