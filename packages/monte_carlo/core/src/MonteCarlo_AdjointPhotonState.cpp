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

// Copy constructor
AdjointPhotonState::AdjointPhotonState( 
				      const ParticleState& existing_base_state,
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
  // Make sure the core is a photon core
  testPrecondition( core.particle_type == ADJOINT_PHOTON );
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

