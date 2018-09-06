//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonState.hpp
//! \author Alex Robinson
//! \brief  Photon state class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must be included first
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
PhotonState::PhotonState()
  : MasslessParticleState()
{ /* ... */ }

// Constructor
PhotonState::PhotonState(const ParticleState::historyNumberType history_number)
  : MasslessParticleState( history_number, PHOTON, 0 )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
PhotonState::PhotonState( const ParticleState& existing_base_state,
			  const bool increment_generation_number,
			  const bool reset_collision_number )
  : MasslessParticleState( existing_base_state,
			   PHOTON,
			   0,
			   increment_generation_number,
			   reset_collision_number )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
PhotonState::PhotonState( const PhotonState& existing_base_state,
			  const bool increment_generation_number,
			  const bool reset_collision_number )
  : MasslessParticleState( existing_base_state,
			   PHOTON,
			   0,
			   increment_generation_number,
			   reset_collision_number )
{ /* ... */ }

// Clone the particle state (do not use to generate new particles!)
PhotonState* PhotonState::clone() const
{
  return new PhotonState( *this, false, false );
}

// Print the photon state
void PhotonState::toStream( std::ostream& os ) const
{
  os << "Particle Type: Photon" << std::endl;

  this->printImplementation<PhotonState>( os );
}

EXPLICIT_CLASS_SERIALIZE_INST( PhotonState );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PhotonState );

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonState.cpp
//---------------------------------------------------------------------------//
