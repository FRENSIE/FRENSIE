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
#include "Utility_ArchiveHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
NeutronState::NeutronState()
  : MassiveParticleState()
{ /* ... */ }

// Constructor
NeutronState::NeutronState( 
		        const ParticleState::historyNumberType history_number )
  : MassiveParticleState( history_number, NEUTRON )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
NeutronState::NeutronState( const ParticleState& existing_base_state,
			    const bool increment_generation_number,
			    const bool reset_collision_number )
  : MassiveParticleState( existing_base_state, 
			  NEUTRON,
			  Utility::PhysicalConstants::neutron_rest_mass_energy,
			  increment_generation_number,
			  reset_collision_number )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
NeutronState::NeutronState( const NeutronState& existing_state,
			    const bool increment_generation_number,
			    const bool reset_collision_number )
  : MassiveParticleState( existing_state, 
			  NEUTRON,
			  Utility::PhysicalConstants::neutron_rest_mass_energy,
			  increment_generation_number,
			  reset_collision_number )
{ /* ... */ }

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

// Clone the particle state (do not use to generate new particles!)
ParticleState::pointerType NeutronState::clone() const
{
  return pointerType( new NeutronState( *this, false, false ) );
}

// Print the neutron state
void NeutronState::print( std::ostream& os ) const
{
  os << "Particle Type: Neutron" << std::endl;

  this->printImplementation<NeutronState>( os );
}

} // end MonteCarlo namespace

UTILITY_CLASS_EXPORT_IMPLEMENT_SERIALIZE( MonteCarlo::NeutronState );
BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::NeutronState );

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronState.cpp
//---------------------------------------------------------------------------//
