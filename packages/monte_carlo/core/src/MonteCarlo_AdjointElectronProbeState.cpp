//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronProbeState.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron probe state class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronProbeState.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
AdjointElectronProbeState::AdjointElectronProbeState( 
		       const ParticleState::historyNumberType history_number )
  : AdjointElectronState( history_number, ADJOINT_ELECTRON_PROBE ),
    d_initial_energy_set( false )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
AdjointElectronProbeState::AdjointElectronProbeState( 
			              const ParticleState& existing_base_state,
				      const bool increment_generation_number,
				      const bool reset_collision_number )
  : AdjointElectronState( existing_base_state,
			ADJOINT_ELECTRON_PROBE,
			increment_generation_number,
			reset_collision_number ),
    d_initial_energy_set( true )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
AdjointElectronProbeState::AdjointElectronProbeState( 
			    const AdjointElectronProbeState& existing_base_state,
			    const bool increment_generation_number,
			    const bool reset_collision_number )
  : AdjointElectronState( existing_base_state,
			ADJOINT_ELECTRON_PROBE,
			increment_generation_number,
			reset_collision_number ),
    d_initial_energy_set( true )
{ /* ... */ }

// Core constructor
AdjointElectronProbeState::AdjointElectronProbeState( 
					        const ParticleStateCore& core )
  : AdjointElectronState( core, ADJOINT_ELECTRON_PROBE ),
    d_initial_energy_set( true )
{
  // Make sure the core is an adjoint electron probe core
  testPrecondition( core.particle_type == ADJOINT_ELECTRON_PROBE );
}

// Set the energy of the particle (MeV)
/*! \details The probe particle gets killed when its energy changes. This
 * does not include the initial setting of the particles energy (either
 * from a copy constructor, core constructor or the basic constructor 
 * followed by the first call to setEnergy).
 */
void AdjointElectronProbeState::setEnergy( const energyType energy )
{
  ParticleState::setEnergy( energy );

  if( d_initial_energy_set )
    this->setAsGone();
  else
    d_initial_energy_set = true;
}

// Print the adjoint electron state
void AdjointElectronProbeState::print( std::ostream& os ) const
{
  os << "Particle Type: Adjoint Electron Probe" << std::endl;
  
  this->printImplementation( os );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronProbeState.cpp
//---------------------------------------------------------------------------//
