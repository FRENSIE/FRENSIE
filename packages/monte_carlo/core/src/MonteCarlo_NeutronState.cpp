//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronState.cpp
//! \author Alex Robinson
//! \brief  Neutron state class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_KinematicHelpers.hpp"

namespace MonteCarlo{

// Constructor
NeutronState::NeutronState( 
		        const ParticleState::historyNumberType history_number )
  : ParticleState( history_number, NEUTRON ),
    d_speed( 0.0 )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
NeutronState::NeutronState( const NeutronState& existing_neutron_state,
			    const bool increment_generation_number,
			    const bool reset_collision_number )
  : ParticleState( existing_neutron_state, 
		   NEUTRON,
		   increment_generation_number,
		   reset_collision_number ),
    d_speed( existing_neutron_state.d_speed )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
NeutronState::NeutronState( const ParticleState& existing_base_state,
			    const bool increment_generation_number,
			    const bool reset_collision_number )
  : ParticleState( existing_base_state, 
		   NEUTRON,
		   increment_generation_number,
		   reset_collision_number ),
    d_speed()
{
  d_speed = Utility::calculateRelativisticSpeed( 
			  Utility::PhysicalConstants::neutron_rest_mass_energy,
			  this->getEnergy() );
}

// Core constructor
NeutronState::NeutronState( const ParticleStateCore& core )
  : ParticleState( core ),
    d_speed()
{
  // Make sure the core is a neutron core
  testPrecondition( core.particle_type == NEUTRON );
  
  d_speed = Utility::calculateRelativisticSpeed( 
			  Utility::PhysicalConstants::neutron_rest_mass_energy,
			  this->getEnergy() );
}

// Assignment operator
NeutronState& NeutronState::operator=( 
				   const NeutronState& existing_neutron_state )
{
  ParticleState::operator=( existing_neutron_state );

  d_speed = existing_neutron_state.d_speed;
}

// Set the energy of the neutron (MeV)
/*! \details The speed of the neutron will also be set
 */
void NeutronState::setEnergy( const ParticleState::energyType energy )
{
  ParticleState::setEnergy( energy );

  d_speed = Utility::calculateRelativisticSpeed( 
			  Utility::PhysicalConstants::neutron_rest_mass_energy,
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
  testPrecondition( speed < Utility::PhysicalConstants::speed_of_light );

  d_speed = speed;

  setEnergy( Utility::calculateRelativisticKineticEnergy(
			  Utility::PhysicalConstants::neutron_rest_mass_energy,
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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronState.cpp
//---------------------------------------------------------------------------//
