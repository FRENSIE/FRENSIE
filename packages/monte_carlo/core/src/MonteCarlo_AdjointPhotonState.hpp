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

  //! Copy constructor
  AdjointPhotonState( const ParticleState& existing_base_state,
		      const bool increment_generation_number = false,
		      const bool reset_collision_number = false );

  //! Core constructor
  AdjointPhotonState( const ParticleStateCore& core );

  //! Destructor
  virtual ~AdjointPhotonState()
  { /* ... */ }

  //! Print the adjoint photon state
  virtual void print( std::ostream& os ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTON_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonState.hpp
//---------------------------------------------------------------------------//
