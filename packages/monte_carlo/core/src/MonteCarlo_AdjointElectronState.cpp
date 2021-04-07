//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronState.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron state class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
AdjointElectronState::AdjointElectronState()
  : ChargedParticleState()
{ /* ... */ }

// Constructor
AdjointElectronState::AdjointElectronState(
                         const ParticleState::historyNumberType history_number )
  : ChargedParticleState( history_number, ADJOINT_ELECTRON, -1 )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
AdjointElectronState::AdjointElectronState(
				      const ParticleState& existing_base_state,
				      const bool increment_generation_number,
				      const bool reset_collision_number )
  : ChargedParticleState( existing_base_state,
                          ADJOINT_ELECTRON,
                          -1,
                          Utility::PhysicalConstants::electron_rest_mass_energy,
                          increment_generation_number,
                          reset_collision_number )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
AdjointElectronState::AdjointElectronState(
				 const AdjointElectronState& existing_base_state,
				 const bool increment_generation_number,
				 const bool reset_collision_number )
  : ChargedParticleState( existing_base_state,
                          ADJOINT_ELECTRON,
                          -1,
                          Utility::PhysicalConstants::electron_rest_mass_energy,
                          increment_generation_number,
                          reset_collision_number )
{ /* ... */ }

// Probe constructor
AdjointElectronState::AdjointElectronState(
			 const ParticleState::historyNumberType history_number,
			 const ParticleType probe_type,
			 const chargeType probe_charge )
  : ChargedParticleState( history_number, probe_type, probe_charge )
{ /* ... */ }

// Probe copy constructor
AdjointElectronState::AdjointElectronState(
				     const ParticleState& existing_base_state,
				     const ParticleType probe_type,
				     const chargeType probe_charge,
				     const bool increment_generation_number,
				     const bool reset_collision_number )
  : ChargedParticleState( existing_base_state,
                          probe_type,
                          probe_charge,
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
void AdjointElectronState::toStream( std::ostream& os ) const
{
  os << "Particle Type: Adjoint Electron" << std::endl;

  this->printImplementation<AdjointElectronState>( os );
}

EXPLICIT_CLASS_SERIALIZE_INST( AdjointElectronState );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::AdjointElectronState );

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronState.cpp
//---------------------------------------------------------------------------//

