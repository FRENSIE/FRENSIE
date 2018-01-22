//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronState.cpp
//! \author Luke Kersting
//! \brief  Positron state class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PositronState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ArchiveHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Default constructor
PositronState::PositronState()
  : MassiveParticleState()
{ /* ... */ }

// Constructor
PositronState::PositronState(
                        const ParticleState::historyNumberType history_number )
  : MassiveParticleState( history_number, POSITRON )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
PositronState::PositronState( const PositronState& existing_positron_state,
                              const bool increment_generation_number,
                              const bool reset_collision_number )
  : MassiveParticleState(existing_positron_state,
                         POSITRON,
                         Utility::PhysicalConstants::electron_rest_mass_energy,
                         increment_generation_number,
                         reset_collision_number )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
PositronState::PositronState( const ParticleState& existing_base_state,
                              const bool increment_generation_number,
                              const bool reset_collision_number )
  : MassiveParticleState(existing_base_state,
                         POSITRON,
                         Utility::PhysicalConstants::electron_rest_mass_energy,
                         increment_generation_number,
                         reset_collision_number )
{ /* ... */ }

// Return the rest mass energy of the positron (MeV)
double PositronState::getRestMassEnergy() const
{
  return Utility::PhysicalConstants::electron_rest_mass_energy;
}

// Clone the particle state (do not use to generate new particles!)
PositronState* PositronState::clone() const
{
  return new PositronState( *this, false, false );
}

// Print the positron state
void PositronState::print( std::ostream& os ) const
{
  os << "Particle Type: Positron" << std::endl;

  this->printImplementation<PositronState>( os );
}

} // end MonteCarlo namespace

UTILITY_CLASS_EXPORT_IMPLEMENT_SERIALIZE( MonteCarlo::PositronState );
BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PositronState );

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronState.cpp
//---------------------------------------------------------------------------//
