//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronState.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron state class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronState.hpp"
#include "Utility_ArchiveHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
AdjointElectronState::AdjointElectronState()
  : MassiveParticleState()
{ /* ... */ }

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

// Check if this is a probe
bool AdjointElectronState::isProbe() const
{
  return false;
}

//! Clone the particle state (do not use to generate new particles!)
AdjointElectronState* AdjointElectronState::clone() const
{
  return new AdjointElectronState( *this, false, false );
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
  
  this->printImplementation<AdjointElectronState>( os );
}

} // end MonteCarl namespace

UTILITY_CLASS_EXPORT_IMPLEMENT_SERIALIZE( MonteCarlo::AdjointElectronState );
BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::AdjointElectronState );

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronState.cpp
//---------------------------------------------------------------------------//

