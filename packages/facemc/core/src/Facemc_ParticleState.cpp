//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleState.cpp
//! \author Alex Robinson
//! \brief  Basic particle state class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleState.hpp"
#include "Utility_DirectionHelpers.hpp"

namespace Facemc{

// Constructor
  ParticleState::ParticleState( 
			 const ParticleState::historyNumberType history_number,
			 const ParticleType type )
    : Utility::PrintableObject( "ParticleState" ),
      d_core( history_number, 
	      type, 
	      0.0, 0.0, 0.0, 
	      0.0, 0.0, 0.0, 
	      0.0, 
	      0.0, 
	      0u,
	      0u,
	      1.0 ),
      d_cell( Geometry::ModuleTraits::invalid_internal_cell_handle ),
      d_lost( false ),
      d_gone( false ),
      d_ray( &d_core.x_position, &d_core.x_direction, false )
{ /* ... */ }

// Copy constructor
ParticleState::ParticleState( const ParticleState& existing_base_state,
			      const ParticleType new_type,
			      const bool increment_generation_number,
			      const bool reset_collision_number )
  : d_core( existing_base_state.d_core  ),
    d_cell( existing_base_state.d_cell ),
    d_lost( existing_base_state.d_lost ),
    d_gone( existing_base_state.d_gone ),
    d_ray( &d_core.x_position, &d_core.x_direction, false )
{
  // Reassign the particle type
  d_core.particle_type = new_type;
  
  // Increment the generation number if requested
  if( increment_generation_number )
    ++d_core.generation_number;

  // Reset the collision number if requested
  if( reset_collision_number )
    d_core.collision_number = 0u;
}

// Core constructor
ParticleState::ParticleState( const ParticleStateCore& core )
  : d_core( core ),
    d_cell( Geometry::ModuleTraits::invalid_internal_cell_handle ),
    d_lost( false ),
    d_gone( false ),
    d_ray( &d_core.x_position, &d_core.x_direction, false )
{ /* ... */ }

// Return the history number
ParticleState::historyNumberType ParticleState::getHistoryNumber() const
{
  return d_core.history_number;
}

// Return the particle type
ParticleType ParticleState::getParticleType() const
{
  return d_core.particle_type;
}

// Return the cell handle for the cell containing the particle
Geometry::ModuleTraits::InternalCellHandle ParticleState::getCell() const
{
  return d_cell;
}

// Set the cell containing the particle
void ParticleState::setCell( 
			const Geometry::ModuleTraits::InternalCellHandle cell )
{
  // Make sure the cell handle is valid
  testPrecondition( cell != 
		    Geometry::ModuleTraits::invalid_internal_cell_handle);
  
  d_cell = cell;
}

// Return the x position of the particle
double ParticleState::getXPosition() const
{
  return d_core.x_position;
}

// Return the y position of the particle
double ParticleState::getYPosition() const
{
  return d_core.y_position;
}

// Return the z position of the particle
double ParticleState::getZPosition() const
{
  return d_core.z_position;
}

// Return the position of the particle
const double* ParticleState::getPosition() const
{
  return &d_core.x_position;
}

// Set the position of the particle
void ParticleState::setPosition( const double x_position, 
				 const double y_position,
				 const double z_position )
{
  // Make sure the coordinates are valid
  testPrecondition( !ST::isnaninf( x_position ) );
  testPrecondition( !ST::isnaninf( y_position ) );
  testPrecondition( !ST::isnaninf( z_position ) );
  
  d_core.x_position = x_position;
  d_core.y_position = y_position;
  d_core.z_position = z_position;
}

// Return the x direction of the particle
double ParticleState::getXDirection() const
{
  return d_core.x_direction;
}

// Return the y direction of the particle
double ParticleState::getYDirection() const
{
  return d_core.y_direction;
}

// Return the z direction of the particle
double ParticleState::getZDirection() const
{
  return d_core.z_direction;
}

// Return the direction of the particle
const double* ParticleState::getDirection() const
{
  return &d_core.x_direction;
}

// Set the direction of the particle
void ParticleState::setDirection( const double x_direction,
				  const double y_direction,
				  const double z_direction )
{
  // Make sure the direction coordinates are valid
  testPrecondition( !ST::isnaninf( x_direction ) );
  testPrecondition( !ST::isnaninf( y_direction ) );
  testPrecondition( !ST::isnaninf( z_direction ) );
  // Make sure the direction is a unit vector
  testPrecondition( Utility::validDirection( x_direction, 
					     y_direction, 
					     z_direction ) );
  
  d_core.x_direction = x_direction;
  d_core.y_direction = y_direction;
  d_core.z_direction = z_direction;
}

// Advance the particle along its direction by the requested distance
void ParticleState::advance( const double distance )
{
  // Make sure the distance is valid
  testPrecondition( !ST::isnaninf( distance ) );
  
  d_core.x_position += d_core.x_direction*distance;
  d_core.y_position += d_core.y_direction*distance;
  d_core.z_position += d_core.z_direction*distance;

  // Compute the time to traverse the distance
  d_core.time += calculateTraversalTime( distance );
}

// Set the energy of the particle
/*! The default implementation is only valid for massless particles (It is
 * assumed that the speed of the particle does not change with the energy).
 */ 
void ParticleState::setEnergy( const ParticleState::energyType energy )
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );
  
  d_core.energy = energy;
}

// Return the time state of the particle
  ParticleState::timeType ParticleState::getTime() const
{
  return d_core.time;
}

// Set the time state of the particle
void ParticleState::setTime( const ParticleState::timeType time )
{
  d_core.time = time;
}

// Return the collision number of the particle
ParticleState::collisionNumberType ParticleState::getCollisionNumber() const
{
  return d_core.collision_number;
}

// Increment the collision number
void ParticleState::incrementCollisionNumber()
{
  ++d_core.collision_number;
}

// Return the generation number of the particle
ParticleState::generationNumberType ParticleState::getGenerationNumber() const
{
  return d_core.generation_number;
}

// Return the weight of the particle
double ParticleState::getWeight() const
{
  return d_core.weight;
}

// Set the weight of the particle
void ParticleState::setWeight( const double weight )
{
  d_core.weight = weight;
}

// Multiply the weight of the particle by a factor
void ParticleState::multiplyWeight( const double weight_factor )
{
  // Make sure that the current weight is valid
  testPrecondition( d_core.weight > 0.0 );
  
  d_core.weight *= weight_factor;
}

// Return if the particle is lost
bool ParticleState::isLost() const
{
  return d_lost;
}

// Set the particle as lost
void ParticleState::setAsLost()
{
  d_lost = true;
}

// Return if the particle is gone
bool ParticleState::isGone() const
{
  return d_gone;
}

// Set the particle as gone
void ParticleState::setAsGone()
{
  d_gone = true;
}

// Export the core (creating a copy of it)
ParticleStateCore ParticleState::exportCore() const
{
  return d_core;
}

// Print method implementation
void ParticleState::printImplementation( std::ostream& os ) const
{
  os.precision( 16 );
  os << "Cell: ";
  if( d_cell == Geometry::ModuleTraits::invalid_internal_cell_handle )
    os << "Invalid/Unknown" << std::endl;
  else
    os << d_cell << std::endl;
  os << "Position: {" << d_core.x_position << "," << d_core.y_position << ","
     << d_core.z_position << "}" << std::endl;
  os << "Direction: {" << d_core.x_direction << "," 
     << d_core.y_direction << ","
     << d_core.z_direction << "}" << std::endl;
  os << "Energy: " << d_core.energy << std::endl;
  os << "Time: " << d_core.time << std::endl;
  os << "Collision Number: " << d_core.collision_number << std::endl;
  os << "Generation Number: " << d_core.generation_number << std::endl;
  os << "Weight: " << d_core.weight << std::endl;
  os << "Lost: " << (d_lost ? "True" : "False") << std::endl;
  os << "Gone: " << (d_gone ? "True" : "False") << std::endl;
}

} // end Facemc

//---------------------------------------------------------------------------//
// end Facemc_ParticleState.cpp
//---------------------------------------------------------------------------//
