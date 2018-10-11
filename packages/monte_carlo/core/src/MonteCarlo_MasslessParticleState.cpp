//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MasslessParticleState.hpp
//! \author Alex Robinson
//! \brief  Massless particle state class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_MasslessParticleState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
MasslessParticleState::MasslessParticleState()
  : ParticleState()
{ /* ... */ }

// Constructor
MasslessParticleState::MasslessParticleState(
                                    const historyNumberType history_number,
                                    const ParticleType type,
                                    const chargeType charge )
  : ParticleState( history_number, type, charge )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
MasslessParticleState::MasslessParticleState(
                                    const ParticleState& existing_base_state,
                                    const ParticleType new_type,
                                    const chargeType new_charge,
                                    const bool increment_generation_number,
                                    const bool reset_collision_number )
  : ParticleState( existing_base_state,
                   new_type,
                   new_charge,
                   increment_generation_number,
                   reset_collision_number,
                   existing_base_state.getRaySafetyDistance() )
{ /* ... */ }

// Return the speed of the particle (cm/s)
double MasslessParticleState::getSpeed() const
{
  return Utility::PhysicalConstants::speed_of_light;
}

// Calculate the time to traverse a distance
ParticleState::timeType
MasslessParticleState::calculateTraversalTime( const double distance ) const
{
  return distance/Utility::PhysicalConstants::speed_of_light;
}

EXPLICIT_CLASS_SERIALIZE_INST( MasslessParticleState );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_MasslessParticleState.cpp
//---------------------------------------------------------------------------//
