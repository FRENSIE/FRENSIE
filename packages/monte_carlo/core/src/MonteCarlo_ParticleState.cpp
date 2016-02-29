//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleState.cpp
//! \author Alex Robinson
//! \brief  Basic particle state class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DirectionHelpers.hpp"

namespace MonteCarlo{

// Default constructor
/*! \details The default constructor should only be called before loading the
 * particle state from an archive.
 */
ParticleState::ParticleState()
  : d_history_number( 0 ),
    d_particle_type(),
    d_position(),
    d_direction{0.0,0.0,1.0},
    d_energy( 0.0 ),
    d_time( 0.0 ),
    d_collision_number( 0 ),
    d_generation_number( 0 ),
    d_weight( 1.0 ),
    d_cell( Geometry::ModuleTraits::invalid_internal_cell_handle ),
    d_lost( false ),
    d_gone( false ),
    d_ray( d_position, d_direction, false )
{ /* ... */ }

// Constructor
ParticleState::ParticleState( 
			 const ParticleState::historyNumberType history_number,
			 const ParticleType type )
  : d_history_number( history_number ),
    d_particle_type( type ),
    d_position(),
    d_direction(),
    d_energy( 0.0 ),
    d_time( 0.0 ),
    d_collision_number( 0 ),
    d_generation_number( 0 ),
    d_weight( 1.0 ),
    d_cell( Geometry::ModuleTraits::invalid_internal_cell_handle ),
    d_lost( false ),
    d_gone( false ),
    d_ray( d_position, d_direction, false )
{ /* ... */ }

// Copy constructor
/*! \details When copied, the new particle is assumed to not be lost and
 * not be gone.
 */
ParticleState::ParticleState( const ParticleState& existing_base_state,
			      const ParticleType new_type,
			      const bool increment_generation_number,
			      const bool reset_collision_number )
  : d_history_number( existing_base_state.d_history_number ),
    d_particle_type( new_type ),
    d_position{existing_base_state.d_position[0],
               existing_base_state.d_position[1],
               existing_base_state.d_position[2]},
    d_direction{existing_base_state.d_direction[0],
	        existing_base_state.d_direction[1],
	        existing_base_state.d_direction[2]},
    d_energy( existing_base_state.d_energy ),
    d_time( existing_base_state.d_time ),
    d_collision_number( existing_base_state.d_collision_number ),
    d_generation_number( existing_base_state.d_generation_number ),
    d_weight( existing_base_state.d_weight ),
    d_cell( existing_base_state.d_cell ),
    d_lost( false ),
    d_gone( false ),
    d_ray( d_position, d_direction, false )
{
  // Increment the generation number if requested
  if( increment_generation_number )
    ++d_generation_number;

  // Reset the collision number if requested
  if( reset_collision_number )
    d_collision_number = 0u;
}

// Clone the particle state but change the history number
/*! \details This method returns a heap-allocated pointer. It is only safe
 * to call this method inside of a smart pointer constructor or reset method.
 * The clone will only need a new history number in very rare circumstances
 * (e.g. state source).
 */
ParticleState* ParticleState::clone( 
	      const ParticleState::historyNumberType new_history_number ) const
{
  ParticleState* clone_state = this->clone();
  
  clone_state->d_history_number = new_history_number;

  return clone_state;
}

// Return the history number
ParticleState::historyNumberType ParticleState::getHistoryNumber() const
{
  return d_history_number;
}

// Return the particle type
ParticleType ParticleState::getParticleType() const
{
  return d_particle_type;
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
  return d_position[0];
}

// Return the y position of the particle
double ParticleState::getYPosition() const
{
  return d_position[1];
}

// Return the z position of the particle
double ParticleState::getZPosition() const
{
  return d_position[2];
}

// Return the position of the particle
const double* ParticleState::getPosition() const
{
  return d_position;
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
  
  d_position[0] = x_position;
  d_position[1] = y_position;
  d_position[2] = z_position;
}

// Return the x direction of the particle
double ParticleState::getXDirection() const
{
  return d_direction[0];
}

// Return the y direction of the particle
double ParticleState::getYDirection() const
{
  return d_direction[1];
}

// Return the z direction of the particle
double ParticleState::getZDirection() const
{
  return d_direction[2];
}

// Return the direction of the particle
const double* ParticleState::getDirection() const
{
  return d_direction;
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
  
  d_direction[0] = x_direction;
  d_direction[1] = y_direction;
  d_direction[2] = z_direction;
}

// Rotate the direction of the particle using polar a. cosine and azimuthal a.
/*! \details The polar angle cosine and azimuthal angle are w.r.t. the
 * current particle direction and not the global coordinate system. These
 * are the variables the commonly occur when sampling a new direction
 * for the particle from a scattering distribution. This function is therefore
 * meant to avoid duplicate code that would otherwise arise when determining
 * the new particle direction
 */
void ParticleState::rotateDirection( const double polar_angle_cosine,
				     const double azimuthal_angle )
{
  // Make sure the current particle direction is valid (initialized)
  testPrecondition( Utility::validDirection( this->getDirection() ) );
  // Make sure the polar angle cosine is valid
  testPrecondition( polar_angle_cosine >= -1.0 );
  testPrecondition( polar_angle_cosine <= 1.0 );
  // Make sure the azimuthal angle is valid
  testPrecondition( azimuthal_angle >= 0.0 );
  testPrecondition( azimuthal_angle <= 2*Utility::PhysicalConstants::pi );
  
  double outgoing_direction[3];

  Utility::rotateDirectionThroughPolarAndAzimuthalAngle( polar_angle_cosine,
							 azimuthal_angle,
							 this->getDirection(),
							 outgoing_direction );
  
  this->setDirection( outgoing_direction );
}

// Advance the particle along its direction by the requested distance
void ParticleState::advance( const double distance )
{
  // Make sure the distance is valid
  testPrecondition( !ST::isnaninf( distance ) );
  
  d_position[0] += d_direction[0]*distance;
  d_position[1] += d_direction[1]*distance;
  d_position[2] += d_direction[2]*distance;

  // Compute the time to traverse the distance
  d_time += calculateTraversalTime( distance );
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
  
  d_energy = energy;
}

// Return the time state of the particle
ParticleState::timeType ParticleState::getTime() const
{
  return d_time;
}

// Set the time state of the particle
void ParticleState::setTime( const ParticleState::timeType time )
{
  d_time = time;
}

// Return the collision number of the particle
ParticleState::collisionNumberType ParticleState::getCollisionNumber() const
{
  return d_collision_number;
}

// Increment the collision number
void ParticleState::incrementCollisionNumber()
{
  ++d_collision_number;
}

// Reset the collision number
/*! \details This should rarely be used - try to rely on the contructor to
 * reset the collision number. 
 */
void ParticleState::resetCollisionNumber()
{
  d_collision_number = 0u;
}

// Return the generation number of the particle
ParticleState::generationNumberType ParticleState::getGenerationNumber() const
{
  return d_generation_number;
}

// Increment the generation number
void ParticleState::incrementGenerationNumber()
{
  ++d_generation_number;
}

// Return the weight of the particle
double ParticleState::getWeight() const
{
  return d_weight;
}

// Set the weight of the particle
void ParticleState::setWeight( const double weight )
{
  d_weight = weight;
}

// Multiply the weight of the particle by a factor
void ParticleState::multiplyWeight( const double weight_factor )
{
  // Make sure that the current weight is valid
  testPrecondition( d_weight > 0.0 );
  
  d_weight *= weight_factor;
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

} // end MonteCarlo

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleState.cpp
//---------------------------------------------------------------------------//
