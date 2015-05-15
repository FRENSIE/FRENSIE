//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonState.hpp
//! \author Alex Robinson
//! \brief  Adjoint photon state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTON_STATE_HPP
#define MONTE_CARLO_ADJOINT_PHOTON_STATE_HPP

// FRENSIE Includes
#include "MonteCarlo_MasslessParticleState.hpp"

namespace MonteCarlo{

//! The adjoint photon state class
class AdjointPhotonState : public MasslessParticleState
{

public:

  // The adjoint photon tag
  struct AdjointPhotonTag{};

  // Typedef for the adjoint photon tag
  struct AdjointPhotonTag ParticleTag;

  //! Constructor
  AdjointPhotonState( const ParticleState::historyNumberType history_number );

  //! Copy constructor (with possible creation of new generation)
  AdjointPhotonState( const ParticleState& existing_base_state,
		      const bool increment_generation_number = false,
		      const bool reset_collision_number = false );

  //! Copy constructor (with possible creation of new generation)
  AdjointPhotonState( const AdjointPhotonState& existing_base_state,
		      const bool increment_generation_number = false,
		      const bool reset_collision_number = false );

  //! Core constructor
  AdjointPhotonState( const ParticleStateCore& core );

  //! Destructor
  virtual ~AdjointPhotonState()
  { /* ... */ }

  //! Print the adjoint photon state
  virtual void print( std::ostream& os ) const;

protected:

  //! Probe constructor
  AdjointPhotonState( const ParticleState::historyNumberType history_number,
		      const ParticleType probe_type );

  //! Probe copy constructor
  AdjointPhotonState( const ParticleState& existing_base_state,
		      const ParticleType probe_type,
		      const bool increment_generation_number,
		      const bool reset_collision_number );

  //! Probe core constructor
  AdjointPhotonState( const ParticleStateCore& core,
		      const ParticleType probe_type );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTON_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonState.hpp
//---------------------------------------------------------------------------//
