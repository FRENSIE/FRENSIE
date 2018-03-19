//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronState.cpp
//! \author Luke Kersting
//! \brief  Electron state class definition
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
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ArchiveHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Default constructor
ElectronState::ElectronState()
  : MassiveParticleState()
{ /* ... */ }

// Constructor
ElectronState::ElectronState(
                        const ParticleState::historyNumberType history_number )
  : MassiveParticleState( history_number, ELECTRON, -1 )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
ElectronState::ElectronState( const ElectronState& existing_electron_state,
                              const bool increment_generation_number,
                              const bool reset_collision_number )
  : MassiveParticleState(existing_electron_state,
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
  : MassiveParticleState(existing_base_state,
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

EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( ParticleState );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::ElectronState );

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronState.cpp
//---------------------------------------------------------------------------//
