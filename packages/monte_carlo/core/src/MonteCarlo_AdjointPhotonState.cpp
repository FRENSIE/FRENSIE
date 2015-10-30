//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonState.cpp
//! \author Alex Robinson
//! \brief  Adjoint photon state class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonState.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
AdjointPhotonState::AdjointPhotonState( 
		        const ParticleState::historyNumberType history_number )
  : MasslessParticleState( history_number, ADJOINT_PHOTON )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
AdjointPhotonState::AdjointPhotonState( 
				      const ParticleState& existing_base_state,
				      const bool increment_generation_number,
				      const bool reset_collision_number )
  : MasslessParticleState( existing_base_state,
			   ADJOINT_PHOTON,
			   increment_generation_number,
			   reset_collision_number )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
AdjointPhotonState::AdjointPhotonState( 
				 const AdjointPhotonState& existing_base_state,
				 const bool increment_generation_number,
				 const bool reset_collision_number )
  : MasslessParticleState( existing_base_state,
			   ADJOINT_PHOTON,
			   increment_generation_number,
			   reset_collision_number )
{ /* ... */ }

// Core constructor
AdjointPhotonState::AdjointPhotonState( const ParticleStateCore& core )
  : MasslessParticleState( core )
{
  // Make sure the core is an adjoint photon core
  testPrecondition( core.particle_type == ADJOINT_PHOTON );
}

// Probe constructor
AdjointPhotonState::AdjointPhotonState( 
			 const ParticleState::historyNumberType history_number,
			 const ParticleType probe_type )
  : MasslessParticleState( history_number, probe_type ) 
{ /* ... */ }

// Probe copy constructor
AdjointPhotonState::AdjointPhotonState( 
				     const ParticleState& existing_base_state,
				     const ParticleType probe_type,
				     const bool increment_generation_number,
				     const bool reset_collision_number )
  : MasslessParticleState( existing_base_state,
			   probe_type,
			   increment_generation_number,
			   reset_collision_number )
{ /* ... */ }

// Probe core constructor
AdjointPhotonState::AdjointPhotonState( const ParticleStateCore& core,
					const ParticleType probe_type )
  : MasslessParticleState( core )
{ /* ... */ }

// Check if this is a probe
bool AdjointPhotonState::isProbe() const
{
  return false;
}

// Print the adjoint photon state
void AdjointPhotonState::print( std::ostream& os ) const
{
  os << "Particle Type: Adjoint Photon" << std::endl;
  
  this->printImplementation( os );
}

} // end MonteCarl namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonState.cpp
//---------------------------------------------------------------------------//

