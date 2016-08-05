//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MassiveParticleState.cpp
//! \author Alex Robinson
//! \brief  Massive particle state class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_MassiveParticleState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Default constructor
MassiveParticleState::MassiveParticleState()
  : ParticleState(),
    d_speed( 0.0 )
{ /* ... */ }

// Constructor
MassiveParticleState::MassiveParticleState(
					const historyNumberType history_number,
					const ParticleType type )
  : ParticleState( history_number, type ),
    d_speed( 0.0 )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
MassiveParticleState::MassiveParticleState(
				      const ParticleState& existing_base_state,
				      const ParticleType new_type,
				      const double new_rest_mass_energy,
				      const bool increment_generation_number,
				      const bool reset_collision_number )
  : ParticleState( existing_base_state,
		   new_type,
		   increment_generation_number,
		   reset_collision_number ),
    d_speed( Utility::calculateRelativisticSpeed(
					    new_rest_mass_energy,
					    existing_base_state.getEnergy() ) )
{
  // Make sure the new rest mass energy is valid
  testPrecondition( new_rest_mass_energy > 0.0 );
}

// Copy constructor (with possible creation of new generation)
MassiveParticleState::MassiveParticleState(
			      const MassiveParticleState& existing_state,
			      const ParticleType new_type,
			      const double new_rest_mass_energy,
			      const bool increment_generation_number,
			      const bool reset_collision_number )
  : ParticleState( existing_state,
		   new_type,
		   increment_generation_number,
		   reset_collision_number ),
    d_speed()
{
  // Make sure the new rest mass energy is valid
  testPrecondition( new_rest_mass_energy > 0.0 );

  if( existing_state.getParticleType() == this->getParticleType() )
    d_speed = existing_state.d_speed;
  else
  {
    Utility::calculateRelativisticSpeed( new_rest_mass_energy,
					 this->getEnergy() );
  }
}

// Set the energy of the particle (MeV)
/*! \details The speed of the electron will also be set.
 */
void MassiveParticleState::setEnergy( const ParticleState::energyType energy )
{
  ParticleState::setEnergy( energy );

  d_speed = Utility::calculateRelativisticSpeed( this->getRestMassEnergy(),
						 energy );
}

// Return the speed of the particle (cm/s)
double MassiveParticleState::getSpeed() const
{
  return d_speed;
}

// Set the speed of the particle (cm/s)
/*! \details The energy of the particle will also be set.
 */
void MassiveParticleState::setSpeed( const double speed )
{
  // Make sure the speed is valid
  testPrecondition( !ST::isnaninf( speed ) );
  testPrecondition( speed > 0.0 );
  testPrecondition( speed < Utility::PhysicalConstants::speed_of_light );

  d_speed = speed;

  ParticleState::setEnergy( Utility::calculateRelativisticKineticEnergy(
						     this->getRestMassEnergy(),
						     d_speed ) );
}

// Calculate the time to traverse a distance
ParticleState::timeType
MassiveParticleState::calculateTraversalTime( const double distance ) const
{
  // Make sure the speed has been set
  testPrecondition( d_speed > 0.0 );

  return distance/d_speed;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_MassiveParticleState.cpp
//---------------------------------------------------------------------------//
