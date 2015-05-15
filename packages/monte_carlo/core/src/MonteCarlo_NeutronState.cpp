//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronState.cpp
//! \author Alex Robinson
//! \brief  Neutron state class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
NeutronState::NeutronState( 
		        const ParticleState::historyNumberType history_number )
  : MassiveParticleState( history_number, NEUTRON )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
NeutronState::NeutronState( const NeutronState& existing_neutron_state,
			    const bool increment_generation_number,
			    const bool reset_collision_number )
  : MassiveParticleState( existing_neutron_state, 
			  NEUTRON,
			  increment_generation_number,
			  reset_collision_number )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
NeutronState::NeutronState( const ParticleState& existing_base_state,
			    const bool increment_generation_number,
			    const bool reset_collision_number )
  : MassiveParticleState( existing_base_state, 
			  NEUTRON,
			  increment_generation_number,
			  reset_collision_number )
{ /* ... */ }

// Core constructor
NeutronState::NeutronState( const ParticleStateCore& core )
  : MassiveParticleState( core )
{
  // Make sure the core is a neutron core
  testPrecondition( core.particle_type == NEUTRON );
}

// Assignment operator
NeutronState& NeutronState::operator=( 
				   const NeutronState& existing_neutron_state )
{
  MassiveParticleState::operator=( existing_neutron_state );
}

// Return the rest mass energy of the neutron (MeV)
double NeutronState::getRestMassEnergy() const
{
  return Utility::PhysicalConstants::neutron_rest_mass_energy;
}

// Print the neutron state
void NeutronState::print( std::ostream& os ) const
{
  os << "Particle Type: Neutron" << std::endl;

  this->printImplementation( os );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronState.cpp
//---------------------------------------------------------------------------//
