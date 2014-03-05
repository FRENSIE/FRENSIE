//---------------------------------------------------------------------------//
//!
//! \file   BasicParticleState.cpp
//! \author Alex Robinson
//! \brief  Basic particle state class definition.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "BasicParticleState.hpp"
#include "PhysicalConstants.hpp"
#include "DirectionHelpers.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Default constructor
BasicParticleState::BasicParticleState()
  : PrintableObject( "ParticleState" ),
    d_type( PHOTON ),
    d_position(),
    d_direction(),
    d_energy( 0.0 ),
    d_velocity( 0.0 ),
    d_time( 0.0 ),
    d_weight( 1.0 )
{
  // Set the velocity
  if( d_type == PHOTON || d_type == ADJOINT_PHOTON )
    d_velocity = PhysicalConstants::speed_of_light;
  else if( d_type == NEUTRON || d_type == ADJOINT_NEUTRON )
    d_velocity = 0.0;
}

// Constructor
BasicParticleState::BasicParticleState( const ParticleType type,
					const double position[3],
					const double direction[3],
					const double energy,
					const double time,
					const double weight )
  : PrintableObject( "ParticleState" ),
    d_type( type ),
    d_position(),
    d_direction(),
    d_energy( energy ),
    d_velocity(),
    d_time( time ),
    d_weight( weight )
{
  // Make sure that the position coordinates are valid
  testPrecondition( !ST::isnaninf( position[0] ) );
  testPrecondition( !ST::isnaninf( position[1] ) );
  testPrecondition( !ST::isnaninf( position[2] ) );
  // Make sure that the direction coordinates are valid
  testPrecondition( !ST::isnaninf( direction[0] ) );
  testPrecondition( !ST::isnaninf( direction[1] ) );
  testPrecondition( !ST::isnaninf( direction[2] ) );
  // Make sure that the direction is a unit vector
  testPrecondition( validDirection( direction ) )
  // Make sure that the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );
  // Make sure that the time is valid
  testPrecondition( !ST::isnaninf( time ) );
  testPrecondition( time >= 0.0 );

  // Deep copy of the position
  d_position[0] = position[0];
  d_position[1] = position[1];
  d_position[2] = position[2];

  // Deep copy of the direction
  d_direction[0] = direction[0];
  d_direction[1] = direction[1];
  d_direction[2] = direction[2];

  // Set the velocity
  if( d_type == PHOTON || d_type == ADJOINT_PHOTON )
    d_velocity = PhysicalConstants::speed_of_light;
  else if( d_type == NEUTRON || d_type == ADJOINT_NEUTRON )
    calculateNeutronVelocity();
}

// Copy constructor
BasicParticleState::BasicParticleState( 
			       const BasicParticleState& existing_basic_state )
  : d_type( existing_basic_state.d_type ),
    d_position(),
    d_direction(),
    d_energy( existing_basic_state.d_energy ),
    d_velocity( existing_basic_state.d_velocity ),
    d_time( existing_basic_state.d_time ),
    d_weight( existing_basic_state.d_weight )
{
  // Deep copy of the position
  d_position[0] = existing_basic_state.d_position[0];
  d_position[1] = existing_basic_state.d_position[1];
  d_position[2] = existing_basic_state.d_position[2];
  
  // Deep copy of the direction
  d_direction[0] = existing_basic_state.d_direction[0];
  d_direction[1] = existing_basic_state.d_direction[1];
  d_direction[2] = existing_basic_state.d_direction[2];
}

// Assignment operator
BasicParticleState& BasicParticleState::operator=(
			       const BasicParticleState& existing_basic_state )
{
  // Test if the existing basic state is the same as the target
  if( this != &existing_basic_state )
  {
    d_type = existing_basic_state.d_type;
    
    // Deep copy of the position
    d_position[0] = existing_basic_state.d_position[0];
    d_position[1] = existing_basic_state.d_position[1];
    d_position[2] = existing_basic_state.d_position[2];

    // Deep copy of the direction
    d_direction[0] = existing_basic_state.d_direction[0];
    d_direction[1] = existing_basic_state.d_direction[1];
    d_direction[2] = existing_basic_state.d_direction[2];

    d_energy = existing_basic_state.d_energy;
    d_velocity = existing_basic_state.d_velocity;
    d_time = existing_basic_state.d_time;
    d_weight = existing_basic_state.d_weight;
  }
}

// Return the particle type
ParticleType BasicParticleState::getParticleType() const
{
  return d_type;
}

// Set the particle type
ParticleType BasicParticleState::setParticleType( 
					     const ParticleType particle_type )
{
  d_type = particle_type;
}

// Return the x position of the particle
double BasicParticleState::getXPosition() const
{
  return d_position[0];
}

// Return the y position of the particle
double BasicParticleState::getYPosition() const
{
  return d_position[1];
}

// Return the z position of the particle
double BasicParticleState::getZPosition() const
{
  return d_position[2];
}

// Return the position of the particle
const double* BasicParticleState::getPosition() const
{
  return d_position;
}

// Set the position of the particle
void BasicParticleState::setPosition( const double x_position, 
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

// Set the position of the particle
void BasicParticleState::setPosition( const double position[3] )
{
  setPosition( position[0], position[1], position[2] );
}

// Return the x direction of the particle
double BasicParticleState::getXDirection() const
{
  return d_direction[0];
}

// Return the y direction of the particle
double BasicParticleState::getYDirection() const
{
  return d_direction[1];
}

// Return the z direction of the particle
double BasicParticleState::getZDirection() const
{
  return d_direction[2];
}

// Return the direction of the particle
const double* BasicParticleState::getDirection() const
{
  return d_direction;
}

// Set the direction of the particle
void BasicParticleState::setDirection( const double x_direction,
				       const double y_direction,
				       const double z_direction )
{
  // Make sure the direction coordinates are valid
  testPrecondition( !ST::isnaninf( x_direction ) );
  testPrecondition( !ST::isnaninf( y_direction ) );
  testPrecondition( !ST::isnaninf( z_direction ) );
  // Make sure the direction is a unit vector
  testPrecondition( validDirection( x_direction, y_direction, z_direction ) );
  
  d_direction[0] = x_direction;
  d_direction[1] = y_direction;
  d_direction[2] = z_direction;
}

// Set the direction of the particle
void BasicParticleState::setDirection( const double direction[3] )
{
  setDirection( direction[0], direction[1], direction[2] );
}

// Advance the particle along its direction by the requested distance
void BasicParticleState::advance( const double distance )
{
  // Make sure the distance is valid
  testPrecondition( !ST::isnaninf( distance ) );
  // Make sure that the particle velocity is valid
  testPrecondition( d_velocity > 0.0 );
  
  d_position[0] += d_direction[0]*distance;
  d_position[1] += d_direction[1]*distance;
  d_position[2] += d_direction[2]*distance;

  // Compute the time to traverse the distance
  d_time += distance/d_velocity;
}

// Return the energy of the particle
double BasicParticleState::getEnergy() const
{
  return d_energy;
}

// Set the energy of the particle
void BasicParticleState::setEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );
  
  d_energy = energy;
  
  // set the velocity
  if( d_type == NEUTRON || d_type == ADJOINT_NEUTRON )
    calculateNeutronVelocity();
}

// Return the time state of the particle
double BasicParticleState::getTime() const
{
  return d_time;
}

// Set the time state of the particle
void BasicParticleState::setTime( const double time )
{
  d_time = time;
}

// Return the weight of the particle
double BasicParticleState::getWeight() const
{
  return d_weight;
}

// Set the weight of the particle
void BasicParticleState::setWeight( const double weight )
{
  d_weight = weight;
}

// Multiply the weight of the particle by a factor
void BasicParticleState::multiplyWeight( const double weight_factor )
{
  // Make sure that the current weight is valid
  testPrecondition( d_weight > 0.0 );
  
  d_weight *= weight_factor;
}

// Print method that defines the behavior of the std::stream << operator
void BasicParticleState::print( std::ostream& os ) const
{
  printImplementation( os );
}

// Print method implementation
void BasicParticleState::printImplementation( std::ostream& os ) const
{
  os << "Particle Type: ";
  switch( d_type )
  {
  case PHOTON: 
    os << "photon";
    break;
  case NEUTRON:
    os << "neutron";
    break;
  case ADJOINT_PHOTON:
    os << "adjoint photon";
    break;
  case ADJOINT_NEUTRON:
    os << "adjoint neutron";
    break;
  }
  os << std::endl;
  
  os << "Position: {" << d_position[0] << "," << d_position[1] << ","
     << d_position[2] << "}" << std::endl;
  os << "Direction: {" << d_direction[0] << "," << d_direction[1] << ","
     << d_direction[2] << "}" << std::endl;
  os << "Energy: " << d_energy << std::endl;
  os << "Time: " << d_time << std::endl;
  os << "Weight: " << d_weight << std::endl;
}

// Calculate the neutron velocity
void BasicParticleState::calculateNeutronVelocity()
{
  d_velocity = d_energy*PhysicalConstants::speed_of_light/
    sqrt( PhysicalConstants::neutron_rest_mass_energy*
	  PhysicalConstants::neutron_rest_mass_energy + d_energy*d_energy );
}

} // end FACEMC

//---------------------------------------------------------------------------//
// end BasicParticleState.cpp
//---------------------------------------------------------------------------//
