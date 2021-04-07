//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronState.cpp
//! \author Luke Kersting
//! \brief  Electron state class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
ElectronState::ElectronState()
  : ChargedParticleState()
{ /* ... */ }

// Constructor
ElectronState::ElectronState(
                        const ParticleState::historyNumberType history_number )
  : ChargedParticleState( history_number, ELECTRON, -1 )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
ElectronState::ElectronState( const ElectronState& existing_electron_state,
                              const bool increment_generation_number,
                              const bool reset_collision_number )
  : ChargedParticleState(existing_electron_state,
                         ELECTRON,
                         -1,
                         Utility::PhysicalConstants::electron_rest_mass_energy,
                         increment_generation_number,
                         reset_collision_number )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
ElectronState::ElectronState( const ParticleState& existing_base_state,
                              const bool increment_generation_number,
                              const bool reset_collision_number )
  : ChargedParticleState(existing_base_state,
                         ELECTRON,
                         -1,
                         Utility::PhysicalConstants::electron_rest_mass_energy,
                         increment_generation_number,
                         reset_collision_number )
{ /* ... */ }

// Return the rest mass energy of the electron (MeV)
double ElectronState::getRestMassEnergy() const
{
  return Utility::PhysicalConstants::electron_rest_mass_energy;
}

// Clone the particle state (do not use to generate new particles!)
ElectronState* ElectronState::clone() const
{
  return new ElectronState( *this, false, false );
}

// Print the electron state
void ElectronState::toStream( std::ostream& os ) const
{
  os << "Particle Type: Electron" << std::endl;

  this->printImplementation<ElectronState>( os );
}

EXPLICIT_CLASS_SERIALIZE_INST( ElectronState );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ElectronState );

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronState.cpp
//---------------------------------------------------------------------------//
