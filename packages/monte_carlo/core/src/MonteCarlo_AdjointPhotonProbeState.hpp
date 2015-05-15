//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonProbeState.hpp
//! \author Alex Robinson
//! \brief  Adjoint photon probe state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTON_STATE_HPP
#define MONTE_CARLO_ADJOINT_PHOTON_STATE_HPP

// FRENSIE Includes
#Include "MonteCarlo_AdjointPhotonState.hpp"

namespace MonteCarlo{

//! The adjoint photon probe state class
class AdjointPhotonProbeState : public AdjointPhotonState
{

public:

  // The adjoint photon probe tag
  struct AdjointPhotonProbeTag{};

  // Typedef for the adjoint photon probe tag
  struct AdjointPhotonProbeTag ParticleTag;

  //! Constructor
  AdjointPhotonProbeState( 
		       const ParticleState::historyNumberType history_number );

  //! Copy constructor
  AdjointPhotonProbeState( const ParticleState& existing_base_state,
			   const bool increment_generation_number = false,
			   const bool reset_collision_number = false );

  //! Core constructor
  AdjointPhotonProbeState( const ParticleStateCore& core );

  //! Destructor
  ~AdjointPhotonProbeState()
  { /* ... */ }

  //! Set the energy of the particle (MeV)
  void setEnergy( const energyType energy );

  //! Print the adjoint photon state
  void print( std::ostream& os ) const;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonProbeState.hpp
//---------------------------------------------------------------------------//
