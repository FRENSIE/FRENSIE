//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonProbeState.cpp
//! \author Alex Robinson
//! \brief  Adjoint photon probe state class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
AdjointPhotonProbeState::AdjointPhotonProbeState( 
		       const ParticleState::historyNumberType history_number )
  : AdjointPhotonState( history_number, ADJOINT_PHOTON_PROBE ),
    d_initial_energy_set( false )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
AdjointPhotonProbeState::AdjointPhotonProbeState( 
			              const ParticleState& existing_base_state,
				      const bool increment_generation_number,
				      const bool reset_collision_number )
  : AdjointPhotonState( existing_base_state,
			ADJOINT_PHOTON_PROBE,
			increment_generation_number,
			reset_collision_number ),
    d_initial_energy_set( true )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
AdjointPhotonProbeState::AdjointPhotonProbeState( 
			    const AdjointPhotonProbeState& existing_base_state,
			    const bool increment_generation_number,
			    const bool reset_collision_number )
  : AdjointPhotonState( existing_base_state,
			ADJOINT_PHOTON_PROBE,
			increment_generation_number,
			reset_collision_number ),
    d_initial_energy_set( true )
{ /* ... */ }

// Core constructor
AdjointPhotonProbeState::AdjointPhotonProbeState( 
					        const ParticleStateCore& core )
  : AdjointPhotonState( core, ADJOINT_PHOTON_PROBE ),
    d_initial_energy_set( true )
{
  // Make sure the core is an adjoint photon probe core
  testPrecondition( core.particle_type == ADJOINT_PHOTON_PROBE );
}

// Set the energy of the particle (MeV)
/*! \details The probe particle gets killed when its energy changes. This
 * does not include the initial setting of the particles energy (either
 * from a copy constructor, core constructor or the basic constructor 
 * followed by the first call to setEnergy).
 */
void AdjointPhotonProbeState::setEnergy( const energyType energy )
{
  ParticleState::setEnergy( energy );

  if( d_initial_energy_set )
    this->setAsGone();
  else
    d_initial_energy_set = true;
}

// Print the adjoint photon state
void AdjointPhotonProbeState::print( std::ostream& os ) const
{
  os << "Particle Type: Adjoint Photon Probe" << std::endl;
  
  this->printImplementation( os );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonProbeState.cpp
//---------------------------------------------------------------------------//
