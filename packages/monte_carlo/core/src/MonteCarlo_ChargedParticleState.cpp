//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ChargedParticleState.cpp
//! \author Luke Kersting
//! \brief  Charged particle state class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "MonteCarlo_ChargedParticleState.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
ChargedParticleState::ChargedParticleState()
  : MassiveParticleState()
{ /* ... */ }

// Constructor
ChargedParticleState::ChargedParticleState(
      const historyNumberType history_number,
      const ParticleType type,
      const chargeType charge )
  : MassiveParticleState( history_number, type, charge )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
ChargedParticleState::ChargedParticleState(
      const ParticleState& existing_base_state,
      const ParticleType new_type,
      const chargeType new_charge,
      const double new_rest_mass_energy,
      const bool increment_generation_number,
      const bool reset_collision_number )
  : MassiveParticleState( existing_base_state,
                          new_type,
                          new_charge,
                          new_rest_mass_energy,
                          increment_generation_number,
                          reset_collision_number )
{ /* ... */ }

// Copy constructor (with possible creation of new generation)
ChargedParticleState::ChargedParticleState(
                  const ChargedParticleState& existing_state,
                  const ParticleType new_type,
                  const chargeType new_charge,
                  const double new_rest_mass_energy,
                  const bool increment_generation_number,
                  const bool reset_collision_number )
  : MassiveParticleState( existing_state,
                          new_type,
                          new_charge,
                          new_rest_mass_energy,
                          increment_generation_number,
                          reset_collision_number )
{ /* ... */ }

EXPLICIT_CLASS_SERIALIZE_INST( ChargedParticleState );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ChargedParticleState.cpp
//---------------------------------------------------------------------------//
