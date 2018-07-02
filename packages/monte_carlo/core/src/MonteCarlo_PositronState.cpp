//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronState.cpp
//! \author Luke Kersting
//! \brief  Positron state class definition
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
#include "MonteCarlo_PositronState.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
PositronState::PositronState()
  : MassiveParticleState()
{ /* ... */ }

// Constructor
PositronState::PositronState(
                        const ParticleState::historyNumberType history_number )
  : MassiveParticleState( history_number, POSITRON, 1 )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
PositronState::PositronState( const PositronState& existing_positron_state,
                              const bool increment_generation_number,
                              const bool reset_collision_number )
  : MassiveParticleState(existing_positron_state,
                         POSITRON,
                         1,
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
                         1,
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
void PositronState::toStream( std::ostream& os ) const
{
  os << "Particle Type: Positron" << std::endl;

  this->printImplementation<PositronState>( os );
}

EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( PositronState );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::PositronState );

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronState.cpp
//---------------------------------------------------------------------------//
