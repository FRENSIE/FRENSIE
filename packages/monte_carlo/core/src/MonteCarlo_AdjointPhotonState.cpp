//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonState.cpp
//! \author Alex Robinson
//! \brief  Adjoint photon state class definition
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
#include "MonteCarlo_AdjointPhotonState.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_ArchiveHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
AdjointPhotonState::AdjointPhotonState()
  : MasslessParticleState()
{ /* ... */ }

// Constructor
AdjointPhotonState::AdjointPhotonState(
		        const ParticleState::historyNumberType history_number )
  : MasslessParticleState( history_number, ADJOINT_PHOTON, 0 )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
AdjointPhotonState::AdjointPhotonState(
				      const ParticleState& existing_base_state,
				      const bool increment_generation_number,
				      const bool reset_collision_number )
  : MasslessParticleState( existing_base_state,
			   ADJOINT_PHOTON,
			   0,
			   increment_generation_number,
			   reset_collision_number )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
AdjointPhotonState::AdjointPhotonState(
				 const AdjointPhotonState& existing_base_state,
				 const bool increment_generation_number,
				 const bool reset_collision_number )
  : MasslessParticleState( existing_base_state,
			   ADJOINT_PHOTON,
			   0,
			   increment_generation_number,
			   reset_collision_number )
{ /* ... */ }

// Probe constructor
AdjointPhotonState::AdjointPhotonState(
			 const ParticleState::historyNumberType history_number,
			 const ParticleType probe_type,
			 const chargeType probe_charge )
  : MasslessParticleState( history_number, probe_type, probe_charge )
{ /* ... */ }

// Probe copy constructor
AdjointPhotonState::AdjointPhotonState(
				     const ParticleState& existing_base_state,
				     const ParticleType probe_type,
				     const chargeType probe_charge,
				     const bool increment_generation_number,
				     const bool reset_collision_number )
  : MasslessParticleState( existing_base_state,
			   probe_type,
			   probe_charge,
			   increment_generation_number,
			   reset_collision_number )
{ /* ... */ }

// Check if this is a probe
bool AdjointPhotonState::isProbe() const
{
  return false;
}

//! Clone the particle state (do not use to generate new particles!)
AdjointPhotonState* AdjointPhotonState::clone() const
{
  return new AdjointPhotonState( *this, false, false );
}

// Print the adjoint photon state
void AdjointPhotonState::toStream( std::ostream& os ) const
{
  os << "Particle Type: Adjoint Photon" << std::endl;

  this->printImplementation<AdjointPhotonState>( os );
}

EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( AdjointPhotonState );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::AdjointPhotonState );

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonState.cpp
//---------------------------------------------------------------------------//

