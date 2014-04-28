//---------------------------------------------------------------------------//
//!
//! \file   NeutronState.cpp
//! \author Alex Robinson
//! \brief  Neutron state class definition
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "NeutronState.hpp"
#include "PhysicalConstants.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
NeutronState::NeutronState( const unsigned long long history_number )
  : ParticleState( history_number ),
    d_speed( 0.0 )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
NeutronState::NeutronState( const NeutronState& existing_neutron_state,
			    const bool increment_generation_number,
			    const bool reset_collision_number )
  : ParticleState( existing_neutron_state, 
		   increment_generation_number,
		   reset_collision_number ),
    d_speed( existing_neutron_state.d_speed )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
NeutronState::NeutronState( const ParticleState& existing_base_state,
			    const bool increment_generation_number,
			    const bool reset_collision_number )
  : ParticleState( existing_base_state, 
		   increment_generation_number,
		   reset_collision_number ),
    d_speed()
{
  d_speed = calculateSpeed( PhysicalConstants::neutron_rest_mass_energy,
			    this->getEnergy() );
}

// Assignment operator
NeutronState& NeutronState::operator=( 
				   const NeutronState& existing_neutron_state )
{
  ParticleState::operator=( existing_neutron_state );

  d_speed = existing_neutron_state.d_speed;
}

// Return the particle type
ParticleType NeutronState::getParticleType() const
{
  return NEUTRON;
}

// Set the energy of the neutron (MeV)
/*! \details The speed of the neutron will also be set
 */
void NeutronState::setEnergy( const ParticleState::energyType energy )
{
  ParticleState::setEnergy( energy );

  d_speed = calculateSpeed( PhysicalConstants::neutron_rest_mass_energy,
			    energy );
}

// Return the speed of the neutron (cm/s)
double NeutronState::getSpeed() const
{
  return d_speed;
}

// Set the speed of the neutron (cm/s)
void NeutronState::setSpeed( const double speed )
{
  // Make sure the speed is valid
  testPrecondition( !ST::isnaninf( speed ) );
  testPrecondition( speed > 0.0 );
  testPrecondition( speed < PhysicalConstants::speed_of_light );

  d_speed = speed;

  setEnergy( calculateKineticEnergy(
				  PhysicalConstants::neutron_rest_mass_energy,
				  speed) );
}

// Print the neutron state
void NeutronState::print( std::ostream& os ) const
{
  os << "Particle Type: Neutron" << std::endl;

  this->printImplementation( os );
}

// Calculate the time to traverse a distance
ParticleState::timeType 
NeutronState::calculateTraversalTime( const double distance ) const
{
  // Make sure the speed has been set
  testPrecondition( d_speed > 0.0 );

  return distance/d_speed;
}			    

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end NeutronState.cpp
//---------------------------------------------------------------------------//
