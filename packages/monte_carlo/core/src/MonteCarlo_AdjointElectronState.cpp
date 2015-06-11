//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronState.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron state class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronState.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
AdjointElectronState::AdjointElectronState( 
                         const ParticleState::historyNumberType history_number )
  : MassiveParticleState( history_number, ADJOINT_ELECTRON )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
AdjointElectronState::AdjointElectronState( 
				      const ParticleState& existing_base_state,
				      const bool increment_generation_number,
				      const bool reset_collision_number )
  : MassiveParticleState( existing_base_state,
                          ADJOINT_ELECTRON,
                          Utility::PhysicalConstants::electron_rest_mass_energy,
                          increment_generation_number,
                          reset_collision_number )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
AdjointElectronState::AdjointElectronState( 
				 const AdjointElectronState& existing_base_state,
				 const bool increment_generation_number,
				 const bool reset_collision_number )
  : MassiveParticleState( existing_base_state,
                          ADJOINT_ELECTRON,
                          Utility::PhysicalConstants::electron_rest_mass_energy,
                          increment_generation_number,
                          reset_collision_number )
{ /* ... */ }

// Core constructor
AdjointElectronState::AdjointElectronState( const ParticleStateCore& core )
  : MassiveParticleState( core,
                          Utility::PhysicalConstants::electron_rest_mass_energy )
{
  // Make sure the core is an adjoint electron core
  testPrecondition( core.particle_type == ADJOINT_ELECTRON );
}

// Probe constructor
AdjointElectronState::AdjointElectronState( 
			 const ParticleState::historyNumberType history_number,
			 const ParticleType probe_type )
  : MassiveParticleState( history_number, probe_type ) 
{ /* ... */ }

// Probe copy constructor
AdjointElectronState::AdjointElectronState( 
				     const ParticleState& existing_base_state,
				     const ParticleType probe_type,
				     const bool increment_generation_number,
				     const bool reset_collision_number )
  : MassiveParticleState( existing_base_state,
                          probe_type,
                          Utility::PhysicalConstants::electron_rest_mass_energy,
                          increment_generation_number,
                          reset_collision_number )
{ /* ... */ }

// Probe core constructor
AdjointElectronState::AdjointElectronState( const ParticleStateCore& core,
                                            const ParticleType probe_type )
  : MassiveParticleState( core,
                          Utility::PhysicalConstants::electron_rest_mass_energy )
{ /* ... */ }

// Check if this is a probe
bool AdjointElectronState::isProbe() const
{
  return false;
}

// Return the rest mass energy of the electron (MeV)
double AdjointElectronState::getRestMassEnergy() const
{
  return Utility::PhysicalConstants::electron_rest_mass_energy;
}

// Print the adjoint electron state
void AdjointElectronState::print( std::ostream& os ) const
{
  os << "Particle Type: Adjoint Electron" << std::endl;
  
  this->printImplementation( os );
}

} // end MonteCarl namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronState.cpp
//---------------------------------------------------------------------------//

