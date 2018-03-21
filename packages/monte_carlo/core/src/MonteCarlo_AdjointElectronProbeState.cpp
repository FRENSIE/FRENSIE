//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronProbeState.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron probe state class declaration
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronProbeState.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
AdjointElectronProbeState::AdjointElectronProbeState()
  : AdjointElectronState(),
    d_active( false )
{ /* ... */ }

// Constructor
AdjointElectronProbeState::AdjointElectronProbeState(
                       const ParticleState::historyNumberType history_number )
  : AdjointElectronState( history_number, ADJOINT_ELECTRON, -1 ),
    d_active( false )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
AdjointElectronProbeState::AdjointElectronProbeState(
                                      const ParticleState& existing_base_state,
                                      const bool increment_generation_number,
                                      const bool reset_collision_number )
  : AdjointElectronState( existing_base_state,
                          ADJOINT_ELECTRON,
                          -1,
                          increment_generation_number,
                          reset_collision_number ),
    d_active( false )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
AdjointElectronProbeState::AdjointElectronProbeState(
                            const AdjointElectronProbeState& existing_base_state,
                            const bool increment_generation_number,
                            const bool reset_collision_number )
  : AdjointElectronState( existing_base_state,
                          ADJOINT_ELECTRON,
                          -1,
                          increment_generation_number,
                          reset_collision_number ),
    d_active( false )
{ /* ... */ }


// Set the energy of the particle (MeV)
/*! \details An active probe particle gets killed when its energy changes. A
 * probe particle should only be activated after its initial energy has been
 * set.
 */
void AdjointElectronProbeState::setEnergy( const energyType energy )
{
  MassiveParticleState::setEnergy( energy );

  if( d_active )
    this->setAsGone();
}

// Check if this is a probe
bool AdjointElectronProbeState::isProbe() const
{
  return true;
}

// Activate the probe
/*! \details Once a probe has been activated the next call to set energy
 * will cause is to be killed.
 */
void AdjointElectronProbeState::activate()
{
  d_active = true;
}

// Returns if the probe is active
bool AdjointElectronProbeState::isActive() const
{
  return d_active;
}

// Clone the particle state (do not use to generate new particles!)
AdjointElectronProbeState* AdjointElectronProbeState::clone() const
{
  return new AdjointElectronProbeState( *this, false, false );
}


// Print the adjoint electron state
void AdjointElectronProbeState::toStream( std::ostream& os ) const
{
  os << "Particle Type: ";

  if( d_active )
    os << "Active ";
  else
    os << "Inactive ";

  os << "Adjoint Electron Probe" << std::endl;

  this->printImplementation<AdjointElectronProbeState>( os );
}

EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( AdjointElectronProbeState );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::AdjointElectronProbeState );

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronProbeState.cpp
//---------------------------------------------------------------------------//
