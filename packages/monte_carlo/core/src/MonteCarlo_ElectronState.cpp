//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronState.cpp
//! \author Luke Kersting
//! \brief  Electron state class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Default constructor
ElectronState::ElectronState()
  : MassiveParticleState()
{ /* ... */ }

// Constructor
ElectronState::ElectronState( 
		        const ParticleState::historyNumberType history_number )
  : MassiveParticleState( history_number, ELECTRON )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
ElectronState::ElectronState( const ElectronState& existing_electron_state,
                              const bool increment_generation_number,
                              const bool reset_collision_number )
  : MassiveParticleState(existing_electron_state, 
			 ELECTRON,
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 increment_generation_number,
			 reset_collision_number )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
ElectronState::ElectronState( const ParticleState& existing_base_state,
                              const bool increment_generation_number,
                              const bool reset_collision_number )
  : MassiveParticleState(existing_base_state, 
			 ELECTRON,
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 increment_generation_number,
			 reset_collision_number )
{ /* ... */ }

// Assignment operator
ElectronState& ElectronState::operator=( 
				   const ElectronState& existing_electron_state )
{
  MassiveParticleState::operator=( existing_electron_state );
}

// Return the rest mass energy of the electron (MeV)
double ElectronState::getRestMassEnergy() const
{
  return Utility::PhysicalConstants::electron_rest_mass_energy;
}

// Print the electron state
void ElectronState::print( std::ostream& os ) const
{
  os << "Particle Type: Electron" << std::endl;

  this->printImplementation<ElectronState>( os );
}			    

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronState.cpp
//---------------------------------------------------------------------------//
