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
  : PrintableObject( "ParticleState" ),
    d_energy( 0.0 ),
    d_position(),
    d_direction(),
    d_type( PHOTON ),
    d_history_number( 0ull ),
    d_cell( 0 ),
    d_root_history( true ),
    d_lost( false ),
    d_gone( false )
{ /* ... */ }

// Constructor for a particular history
template<typename CellHandle>
ParticleState<CellHandle>::ParticleState( 
				       const unsigned long long history_number,
				       const ParticleType particle_type )
  : PrintableObject( "ParticleState" ),
    d_energy( 0.0 ),
    d_position(),
    d_direction(),
    d_type( particle_type ),
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
: d_energy( existing_particle_state.d_energy ),
  d_position( existing_particle_state.d_position ),
  d_direction( existing_particle_state.d_direction ),
  d_type( existing_particle_state.d_type ),
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
    d_energy = existing_particle_state.d_energy;
    d_position = existing_particle_state.d_position;
    d_direction = existing_particle_state.d_direction;
    d_type = existing_particle_state.d_type;
    d_history_number = existing_particle_state.d_history_number;
    d_cell = existing_particle_state.d_cell;
    d_root_history = existing_particle_state.d_root_history;
    d_lost = existing_particle_state.d_lost;
    d_gone = existing_particle_state.d_gone;
  }
  
  return *this;
}

// Return the energy of the particle
template<typename CellHandle>
double ParticleState<CellHandle>::getEnergy() const
{
  return d_energy;
}

// Set the energy of the particle
template<typename CellHandle>
void ParticleState<CellHandle>::setEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );
  
  d_energy = energy;
}

// Return the x position of the particle
template<typename CellHandle>
double ParticleState<CellHandle>::getXPosition() const
{
  return d_position[0];
}

// Return the y position of the particle
template<typename CellHandle>
double ParticleState<CellHandle>::getYPosition() const
{
  return d_position[1];
}

// Return the z position of the particle
template<typename CellHandle>
double ParticleState<CellHandle>::getZPosition() const
{
  return d_position[2];
}

// Return the position of the particle
template<typename CellHandle>
const double* ParticleState<CellHandle>::getPosition() const
{
  return d_position.data();
}

// Set the position of the particle
template<typename CellHandle>
void ParticleState<CellHandle>::setPosition( const double x_position, 
					     const double y_position,
					     const double z_position )
{
  // Make sure the coordinates are valid
  testPrecondition( !ST::isnaninf( x_position ) );
  testPrecondition( !ST::isnaninf( y_position ) );
  testPrecondition( !ST::isnaninf( z_position ) );
  
  d_position[0] = x_position;
  d_position[1] = y_position;
  d_position[2] = z_position;
}

// Return the x direction of the particle
template<typename CellHandle>
double ParticleState<CellHandle>::getXDirection() const
{
  return d_direction[0];
}

// Return the y direction of the particle
template<typename CellHandle>
double ParticleState<CellHandle>::getYDirection() const
{
  return d_direction[1];
}

// Return the z direction of the particle
template<typename CellHandle>
double ParticleState<CellHandle>::getZDirection() const
{
  return d_direction[2];
}

// Return the direction of the particle
template<typename CellHandle>
const double* ParticleState<CellHandle>::getDirection() const
{
  return d_direction.data();
}

// Set the direction of the particle
template<typename CellHandle>
void ParticleState<CellHandle>::setDirection( const double x_direction,
					      const double y_direction,
					      const double z_direction )
{
  // Make sure the direction coordinates are valid
  testPrecondition( !ST::isnaninf( x_direction ) );
  testPrecondition( !ST::isnaninf( y_direction ) );
  testPrecondition( !ST::isnaninf( z_direction ) );
  // Make sure the direction is a unit vector
  remember( double x_direction_sqr = x_direction*x_direction );
  remember( double y_direction_sqr = y_direction*y_direction );
  remember( double z_direction_sqr = z_direction*z_direction );
  remember( double argument = x_direction_sqr+y_direction_sqr+z_direction_sqr);
  remember( double norm_two_value = ST::squareroot( argument ) );
  testPrecondition( ST::magnitude( norm_two_value - 1.0 ) < ST::prec() );
  
  d_direction[0] = x_direction;
  d_direction[1] = y_direction;
  d_direction[2] = z_direction;
}

// Return the particle type
template<typename CellHandle>
ParticleType ParticleState<CellHandle>::getParticleType() const
{
  return d_type;
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

// Advance the particle along its direction by the requested distance
template<typename CellHandle>
void ParticleState<CellHandle>::advance( const double distance )
{
  // Make sure the distance is valid
  testPrecondition( !ST::isnaninf( distance ) );
  
  d_position[0] += d_direction[0]*distance;
  d_position[1] += d_direction[1]*distance;
  d_position[2] += d_direction[2]*distance;
}

// Spawn a child state (the history number will not change)
template<typename CellHandle>
Teuchos::RCP<ParticleState<CellHandle> >
ParticleState<CellHandle>::spawnChildState( 
			         const ParticleType child_particle_type ) const
{
  ParticleState<CellHandle>* child_particle = 
    new ParticleState<CellHandle>( d_history_number, child_particle_type );

  child_particle->setEnergy( d_energy );
  child_particle->setPosition( d_position[0], d_position[1], d_position[2] );
  child_particle->setDirection( d_position[0], d_position[1], d_position[2] );
  child_particle->setCell( d_cell );
  child_particle->setAsChildHistory();

  return Teuchos::RCP<ParticleState<CellHandle> >( child_particle );
}

// Spawn a child state that is the same type as the parent
template<typename CellHandle>
Teuchos::RCP<ParticleState<CellHandle> >
ParticleState<CellHandle>::spawnChildState() const
{
  return spawnChildState( d_type );
}

// Print method that defines the behavior of the std::stream << operator
template<typename CellHandle>
void ParticleState<CellHandle>::print( std::ostream& os ) const
{
  os << "History Number: " << d_history_number << std::endl;
  os << "Particle Type: " << d_type << std::endl;
  os << "Energy: " << d_energy << std::endl;
  os << "Position: {" << d_position[0] << "," << d_position[1] << ","
     << d_position[2] << "}" << std::endl;
  os << "Direction: {" << d_direction[0] << "," << d_direction[1] << ","
     << d_direction[2] << "}" << std::endl;
  os << "Cell: " << d_cell << std::endl;
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
