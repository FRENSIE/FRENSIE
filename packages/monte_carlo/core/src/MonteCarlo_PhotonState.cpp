//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonState.hpp
//! \author Alex Robinson
//! \brief  Photon state class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ArchiveHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
PhotonState::PhotonState()
  : MasslessParticleState()
{ /* ... */ }

// Constructor
PhotonState::PhotonState(const ParticleState::historyNumberType history_number)
  : MasslessParticleState( history_number, PHOTON )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
PhotonState::PhotonState( const ParticleState& existing_base_state,
			  const bool increment_generation_number,
			  const bool reset_collision_number )
  : MasslessParticleState( existing_base_state,
			   PHOTON,
			   increment_generation_number,
			   reset_collision_number )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
PhotonState::PhotonState( const PhotonState& existing_base_state,
			  const bool increment_generation_number,
			  const bool reset_collision_number )
  : MasslessParticleState( existing_base_state,
			   PHOTON,
			   increment_generation_number,
			   reset_collision_number )
{ /* ... */ }

// Clone the particle state (do not use to generate new particles!)
PhotonState* PhotonState::clone() const
{
  return new PhotonState( *this, false, false );
}

// Print the photon state
void PhotonState::print( std::ostream& os ) const
{
  os << "Particle Type: Photon" << std::endl;

  this->printImplementation<PhotonState>( os );
}

} // end MonteCarlo namespace

UTILITY_CLASS_EXPORT_IMPLEMENT_SERIALIZE( MonteCarlo::PhotonState );
BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PhotonState );

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonState.cpp
//---------------------------------------------------------------------------//
