//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MassiveParticleState.cpp
//! \author Alex Robinson
//! \brief  Massive particle state class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "MonteCarlo_MassiveParticleState.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
MassiveParticleState::MassiveParticleState()
  : ParticleState(),
    d_speed( 0.0 )
{ /* ... */ }

// Constructor
MassiveParticleState::MassiveParticleState(
                                    const historyNumberType history_number,
                                    const ParticleType type,
                                    const chargeType charge )
  : ParticleState( history_number, type, charge ),
    d_speed( 0.0 )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
MassiveParticleState::MassiveParticleState(
                                    const ParticleState& existing_base_state,
                                    const ParticleType new_type,
                                    const chargeType new_charge,
                                    const double new_rest_mass_energy,
                                    const bool increment_generation_number,
                                    const bool reset_collision_number )
  : ParticleState( existing_base_state,
                   new_type,
                   new_charge,
                   increment_generation_number,
                   reset_collision_number,
                   existing_base_state.getRaySafetyDistance() ),
    d_speed( MonteCarlo::calculateRelativisticSpeed(
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
                                  const chargeType new_charge,
                                  const double new_rest_mass_energy,
                                  const bool increment_generation_number,
                                  const bool reset_collision_number )
  : ParticleState( existing_state,
                   new_type,
                   new_charge,
                   increment_generation_number,
                   reset_collision_number,
                   existing_state.getRaySafetyDistance() ),
    d_speed()
{
  // Make sure the new rest mass energy is valid
  testPrecondition( new_rest_mass_energy > 0.0 );

  if( existing_state.getParticleType() == this->getParticleType() )
    d_speed = existing_state.d_speed;
  else
  {
    MonteCarlo::calculateRelativisticSpeed( new_rest_mass_energy,
                                         this->getEnergy() );
  }
}

// Set the energy of the particle (MeV)
/*! \details The speed of the electron will also be set.
 */
void MassiveParticleState::setEnergy( const ParticleState::energyType energy )
{
  ParticleState::setEnergy( energy );

  d_speed = MonteCarlo::calculateRelativisticSpeed( this->getRestMassEnergy(),
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
  testPrecondition( !QT::isnaninf( speed ) );
  testPrecondition( speed > 0.0 );
  testPrecondition( speed < Utility::PhysicalConstants::speed_of_light );

  d_speed = speed;

  ParticleState::setEnergy( MonteCarlo::calculateRelativisticKineticEnergy(
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

EXPLICIT_CLASS_SERIALIZE_INST( MassiveParticleState );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_MassiveParticleState.cpp
//---------------------------------------------------------------------------//
