//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MasslessParticleState.hpp
//! \author Alex Robinson
//! \brief  Massless particle state class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_MasslessParticleState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
MasslessParticleState::MasslessParticleState( 
				        const historyNumberType history_number,
					const ParticleType type )
  : ParticleState( history_number, type )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
MasslessParticleState::MasslessParticleState( 
				      const ParticleState& existing_base_state,
				      const ParticleType new_type,
				      const bool increment_generation_number,
				      const bool reset_collision_number ) 
  : ParticleState( existing_base_state,
		   new_type,
		   increment_generation_number,
		   reset_collision_number )
{ /* ... */ }

// Core constructor
MasslessParticleState::MasslessParticleState( const ParticleStateCore& core )
  : ParticleState( core )
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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_MasslessParticleState.cpp
//---------------------------------------------------------------------------//
