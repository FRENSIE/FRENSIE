//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MasslessParticleState.hpp
//! \author Alex Robinson
//! \brief  Massless particle state class definition
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
#include "MonteCarlo_MasslessParticleState.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Default constructor
MasslessParticleState::MasslessParticleState()
  : ParticleState()
{ /* ... */ }

// Constructor
MasslessParticleState::MasslessParticleState(
                                        const historyNumberType history_number,
                                        const ParticleType type,
                                        const chargeType charge )
  : ParticleState( history_number, type, charge )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
MasslessParticleState::MasslessParticleState(
                                      const ParticleState& existing_base_state,
                                      const ParticleType new_type,
                                      const chargeType new_charge,
                                      const bool increment_generation_number,
                                      const bool reset_collision_number )
  : ParticleState( existing_base_state,
                   new_type,
                   new_charge,
                   increment_generation_number,
                   reset_collision_number )
{ /* ... */ }

// Return the speed of the particle (cm/s)
double MasslessParticleState::getSpeed() const
{
  return Utility::PhysicalConstants::speed_of_light;
}

// Calculate the time to traverse a distance
ParticleState::timeType
MasslessParticleState::calculateTraversalTime( const double distance ) const
{
  return distance/Utility::PhysicalConstants::speed_of_light;
}

EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MasslessParticleState );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_MasslessParticleState.cpp
//---------------------------------------------------------------------------//
