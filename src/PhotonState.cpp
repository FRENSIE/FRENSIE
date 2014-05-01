//---------------------------------------------------------------------------//
//!
//! \file   PhotonState.hpp
//! \author Alex Robinson
//! \brief  Photon state class declaration
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "PhotonState.hpp"
#include "PhysicalConstants.hpp"
#include "ContractException.hpp"

namespace FACEMC{

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

// Assignment operator
PhotonState& PhotonState::operator=( const PhotonState& existing_photon_state)
{
  ParticleState::operator=( existing_photon_state );
}

// Return the speed of the particle (cm/s)
double PhotonState::getSpeed() const
{
  return PhysicalConstants::speed_of_light;
}

// Calculate the time to traverse a distance
ParticleState::timeType 
PhotonState::calculateTraversalTime( const double distance ) const
{
  return distance/PhysicalConstants::speed_of_light;
}

// Print the photon state
void PhotonState::print( std::ostream& os ) const
{
  os << "Particle Type: Photon" << std::endl;
  
  this->printImplementation( os );
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end PhotonState.cpp
//---------------------------------------------------------------------------//
