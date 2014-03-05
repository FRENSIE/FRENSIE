//---------------------------------------------------------------------------//
//!
//! \file   ParticleState_def.hpp
//! \author Alex Robinson
//! \brief  Particle state class definition.
//!
//---------------------------------------------------------------------------//

#ifndef PARTICLE_STATE_DEF_HPP
#define PARTICLE_STATE_DEF_HPP

// FACEMC Includes
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
template<typename CellHandle>
ParticleState<CellHandle>::ParticleState()
  : BasicParticleState(),
    d_history_number( 0ull ),
    d_cell( 0 ),
    d_root_history( true ),
    d_lost( false ),
    d_gone( false )
{ /* ... */ }

// Constructor for a particular history
template<typename CellHandle>
ParticleState<CellHandle>::ParticleState( 
				      const unsigned long long history_number )
  : BasicParticleState(),
    d_history_number( history_number ),
    d_cell( 0 ),
    d_root_history( true ),
    d_lost( false ),
    d_gone( false )
{ /* ... */ }

// Copy constructor
template<typename CellHandle>
ParticleState<CellHandle>::ParticleState( 
		     const ParticleState<CellHandle>& existing_particle_state )
  : BasicParticleState( existing_particle_state ),
    d_history_number( existing_particle_state.d_history_number ),
    d_cell( existing_particle_state.d_cell ),
    d_root_history( existing_particle_state.d_root_history ),
    d_lost( existing_particle_state.d_lost ),
    d_gone( existing_particle_state.d_gone )
{ /* ... */ }

// Assignment operator
template<typename CellHandle>
ParticleState<CellHandle>&
ParticleState<CellHandle>::operator=(
		     const ParticleState<CellHandle>& existing_particle_state )
{
  // Test if the existing particle state is the same as the target
  if( this != &existing_particle_state )
  {
    BasicParticleState::operator=( existing_particle_state );
    
    d_history_number = existing_particle_state.d_history_number;
    d_cell = existing_particle_state.d_cell;
    d_root_history = existing_particle_state.d_root_history;
    d_lost = existing_particle_state.d_lost;
    d_gone = existing_particle_state.d_gone;
  }
  
  return *this;
}

// Return the history number
template<typename CellHandle>
unsigned long long ParticleState<CellHandle>::getHistoryNumber() const
{
  return d_history_number;
}

// Return the cell handle for the cell containing the particle
template<typename CellHandle>
CellHandle ParticleState<CellHandle>::getCell() const
{
  return d_cell;
}

// Set the cell handle for the cell containing the particle
template<typename CellHandle>
void ParticleState<CellHandle>::setCell( const CellHandle& cell )
{
  d_cell = cell;
}

// Return if the history is the root
template<typename CellHandle>
bool ParticleState<CellHandle>::isRootHistory() const
{
  return d_root_history;
}

// Return if the particle is lost
template<typename CellHandle>
bool ParticleState<CellHandle>::isLost() const
{
  return d_lost;
}

// Set the particle as lost
template<typename CellHandle>
void ParticleState<CellHandle>::setAsLost()
{
  d_lost = true;
}

// Return if the particle is gone
template<typename CellHandle>
bool ParticleState<CellHandle>::isGone() const
{
  return d_gone;
}

// Set the particle as gone
template<typename CellHandle>
void ParticleState<CellHandle>::setAsGone()
{
  d_gone = true;
}

// Spawn a child state (the history number will not change)
template<typename CellHandle>
typename ParticleState<CellHandle>::ParticleStatePtr
ParticleState<CellHandle>::spawnChildState( 
			         const ParticleType child_particle_type ) const
{
  ParticleState<CellHandle>* child_particle = 
    new ParticleState<CellHandle>( d_history_number );
  
  *child_particle = *this;
  child_particle->setParticleType( child_particle_type );
  child_particle->setAsChildHistory();

  return Teuchos::RCP<ParticleState<CellHandle> >( child_particle );
}

// Spawn a child state that is the same type as the parent
template<typename CellHandle>
inline typename ParticleState<CellHandle>::ParticleStatePtr
ParticleState<CellHandle>::spawnChildState() const
{
  return spawnChildState( getParticleType() );
}

// Print method that defines the behavior of the std::stream << operator
template<typename CellHandle>
void ParticleState<CellHandle>::print( std::ostream& os ) const
{
  os << "History Number: " << d_history_number << std::endl;
  
  BasicParticleState::printImplementation( os );
  
  os << "Cell Handle: " << d_cell << std::endl;
  os << "Root: " << (d_root_history ? "yes":"no") << std::endl;
  os << "Lost: " << (d_lost ? "yes":"no") << std::endl;
  os << "Gone: " << (d_gone ? "yes":"no") << std::endl;
}

// Set the history as a child
template<typename CellHandle>
void ParticleState<CellHandle>::setAsChildHistory()
{
  d_root_history = false;
}

} // end FACEMC namespace

#endif // end PARTICLE_STATE_DEF_HPP

//---------------------------------------------------------------------------//
// end ParticleState_def.hpp
//---------------------------------------------------------------------------//
