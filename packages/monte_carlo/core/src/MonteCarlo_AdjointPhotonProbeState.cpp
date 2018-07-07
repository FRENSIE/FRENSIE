//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonProbeState.cpp
//! \author Alex Robinson
//! \brief  Adjoint photon probe state class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
AdjointPhotonProbeState::AdjointPhotonProbeState()
  : AdjointPhotonState(),
    d_active( false )
{ /* ... */ }

// Constructor
AdjointPhotonProbeState::AdjointPhotonProbeState(
		       const ParticleState::historyNumberType history_number )
  : AdjointPhotonState( history_number, ADJOINT_PHOTON, 0 ),
    d_active( false )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
AdjointPhotonProbeState::AdjointPhotonProbeState(
			              const ParticleState& existing_base_state,
				      const bool increment_generation_number,
				      const bool reset_collision_number )
  : AdjointPhotonState( existing_base_state,
			ADJOINT_PHOTON,
			0,
			increment_generation_number,
			reset_collision_number ),
    d_active( false )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
AdjointPhotonProbeState::AdjointPhotonProbeState(
			    const AdjointPhotonProbeState& existing_base_state,
			    const bool increment_generation_number,
			    const bool reset_collision_number )
  : AdjointPhotonState( existing_base_state,
			ADJOINT_PHOTON,
			0,
			increment_generation_number,
			reset_collision_number ),
    d_active( false )
{ /* ... */ }

// Set the energy of the particle (MeV)
/*! \details An active probe particle gets killed when its energy changes. A
 * probe particle should only be activated after its initial energy has been
 * set.
 */
void AdjointPhotonProbeState::setEnergy( const energyType energy )
{
  ParticleState::setEnergy( energy );

  if( d_active )
    this->setAsGone();
}

// Check if this is a probe
bool AdjointPhotonProbeState::isProbe() const
{
  return true;
}

// Activate the probe
/*! \details Once a probe has been activated the next call to set energy
 * will cause is to be killed.
 */
void AdjointPhotonProbeState::activate()
{
  d_active = true;
}

// Returns if the probe is active
bool AdjointPhotonProbeState::isActive() const
{
  return d_active;
}

// Clone the particle state (do not use to generate new particles!)
AdjointPhotonProbeState* AdjointPhotonProbeState::clone() const
{
  return new AdjointPhotonProbeState( *this, false, false );
}

// Print the adjoint photon state
void AdjointPhotonProbeState::toStream( std::ostream& os ) const
{
  os << "Particle Type: ";

  if( d_active )
    os << "Active ";
  else
    os << "Inactive ";

  os << "Adjoint Photon Probe" << std::endl;

  this->printImplementation<AdjointPhotonProbeState>( os );
}

EXPLICIT_CLASS_SERIALIZE_INST( AdjointPhotonProbeState );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::AdjointPhotonProbeState );

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonProbeState.cpp
//---------------------------------------------------------------------------//
