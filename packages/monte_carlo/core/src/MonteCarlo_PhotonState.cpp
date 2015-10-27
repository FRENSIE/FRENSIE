//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonState.hpp
//! \author Alex Robinson
//! \brief  Photon state class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
PhotonState::PhotonState(const ParticleState::historyNumberType history_number)
  : MasslessParticleState( history_number, PHOTON )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
PhotonState::PhotonState( const ParticleState& existing_base_state,
			  const bool increment_generation_number,
			  const bool reset_collision_number )
  : MasslessParticleState( existing_base_state, 
			   PHOTON,
			   increment_generation_number,
			   reset_collision_number )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
PhotonState::PhotonState( const PhotonState& existing_base_state,
			  const bool increment_generation_number,
			  const bool reset_collision_number )
  : MasslessParticleState( existing_base_state, 
			   PHOTON,
			   increment_generation_number,
			   reset_collision_number )
{ /* ... */ }

// Core constructor
PhotonState::PhotonState( const ParticleStateCore& core )
  : MasslessParticleState( core )
{
  // Make sure the core is a photon core
  testPrecondition( core.particle_type == PHOTON );
}

// Print the photon state
void PhotonState::print( std::ostream& os ) const
{
  os << "Particle Type: Photon" << std::endl;
  
  this->printImplementation( os );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonState.cpp
//---------------------------------------------------------------------------//
