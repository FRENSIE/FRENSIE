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
#include "Utility_KinematicHelpers.hpp"

namespace MonteCarlo{

// Constructor
ElectronState::ElectronState( 
		        const ParticleState::historyNumberType history_number )
  : ParticleState( history_number, ELECTRON ),
    d_speed( 0.0 )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
ElectronState::ElectronState( const ElectronState& existing_electron_state,
			    const bool increment_generation_number,
			    const bool reset_collision_number )
  : ParticleState( existing_electron_state, 
		   ELECTRON,
		   increment_generation_number,
		   reset_collision_number ),
    d_speed( existing_electron_state.d_speed )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
ElectronState::ElectronState( const ParticleState& existing_base_state,
			    const bool increment_generation_number,
			    const bool reset_collision_number )
  : ParticleState( existing_base_state, 
		   ELECTRON,
		   increment_generation_number,
		   reset_collision_number ),
    d_speed()
{
  d_speed = Utility::calculateRelativisticSpeed( 
			  Utility::PhysicalConstants::electron_rest_mass_energy,
			  this->getEnergy() );
}

// Core constructor
ElectronState::ElectronState( const ParticleStateCore& core )
  : ParticleState( core ),
    d_speed()
{
  // Make sure the core is a electron core
  testPrecondition( core.particle_type == ELECTRON );
  
  d_speed = Utility::calculateRelativisticSpeed( 
			  Utility::PhysicalConstants::electron_rest_mass_energy,
			  this->getEnergy() );
}

// Assignment operator
ElectronState& ElectronState::operator=( 
				   const ElectronState& existing_electron_state )
{
  ParticleState::operator=( existing_electron_state );

  d_speed = existing_electron_state.d_speed;
}

// Set the energy of the electron (MeV)
/*! \details The speed of the electron will also be set
 */
void ElectronState::setEnergy( const ParticleState::energyType energy )
{
  ParticleState::setEnergy( energy );

  d_speed = Utility::calculateRelativisticSpeed( 
			  Utility::PhysicalConstants::electron_rest_mass_energy,
			  energy );
}

// Return the speed of the electron (cm/s)
double ElectronState::getSpeed() const
{
  return d_speed;
}

// Set the speed of the electron (cm/s)
void ElectronState::setSpeed( const double speed )
{
  // Make sure the speed is valid
  testPrecondition( !ST::isnaninf( speed ) );
  testPrecondition( speed > 0.0 );
  testPrecondition( speed < Utility::PhysicalConstants::speed_of_light );

  d_speed = speed;

  setEnergy( Utility::calculateRelativisticKineticEnergy(
			  Utility::PhysicalConstants::electron_rest_mass_energy,
			  speed) );
}

// Print the electron state
void ElectronState::print( std::ostream& os ) const
{
  os << "Particle Type: Electron" << std::endl;

  this->printImplementation( os );
}

// Calculate the time to traverse a distance
ParticleState::timeType 
ElectronState::calculateTraversalTime( const double distance ) const
{
  // Make sure the speed has been set
  testPrecondition( d_speed > 0.0 );

  return distance/d_speed;
}			    

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronState.cpp
//---------------------------------------------------------------------------//
