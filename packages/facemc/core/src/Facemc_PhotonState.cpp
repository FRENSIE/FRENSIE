//---------------------------------------------------------------------------//
//!
//! \file   Facemc_PhotonState.hpp
//! \author Alex Robinson
//! \brief  Photon state class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_PhotonState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
PhotonState::PhotonState(const ParticleState::historyNumberType history_number)
  : ParticleState( history_number, PHOTON )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
PhotonState::PhotonState( const ParticleState& existing_base_state,
			  const bool increment_generation_number,
			  const bool reset_collision_number )
  : ParticleState( existing_base_state, 
		   PHOTON,
		   increment_generation_number,
		   reset_collision_number )
{ /* ... */ }

// Core constructor
PhotonState::PhotonState( const ParticleStateCore& core )
  : ParticleState( core )
{
  // Make sure the core is a photon core
  testPrecondition( core.particle_type == PHOTON );
}

// Return the speed of the particle (cm/s)
double PhotonState::getSpeed() const
{
  return Utility::PhysicalConstants::speed_of_light;
}

// Calculate the time to traverse a distance
ParticleState::timeType 
PhotonState::calculateTraversalTime( const double distance ) const
{
  return distance/Utility::PhysicalConstants::speed_of_light;
}

// Print the photon state
void PhotonState::print( std::ostream& os ) const
{
  os << "Particle Type: Photon" << std::endl;
  
  this->printImplementation( os );
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_PhotonState.cpp
//---------------------------------------------------------------------------//
