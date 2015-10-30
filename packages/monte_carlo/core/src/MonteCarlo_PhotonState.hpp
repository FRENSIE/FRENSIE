//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonState.hpp
//! \author Alex Robinson
//! \brief  Photon state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTON_STATE_HPP
#define MONTE_CARLO_PHOTON_STATE_HPP

// FRENSIE Includes
#include "MonteCarlo_MasslessParticleState.hpp"

namespace MonteCarlo{

//! The photon state class
class PhotonState : public MasslessParticleState
{

private:

  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:
  
  // The photon tag
  struct PhotonTag{};

  // Typedef for the photon tag
  struct PhotonTag ParticleTag;

  //! The particle state type (for compile time usage)
  static const ParticleType type = PHOTON;

  //! Constructor
  PhotonState( const ParticleState::historyNumberType history_number );

  //! Copy constructor (with possible creation of new generation)
  PhotonState( const ParticleState& existing_base_state,
	       const bool increment_generation_number = false,
	       const bool reset_collision_number = false );

  //! Copy constructor (with possible creation of new generation)
  PhotonState( const PhotonState& existing_base_state,
	       const bool increment_generation_number = false,
	       const bool reset_collision_number = false );

  //! Core constructor
  PhotonState( const ParticleStateCore& core );

  //! Destructor
  ~PhotonState()
  { /* ... */ }

  //! Print the photon state
  void print( std::ostream& os ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTON_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonState.hpp
//---------------------------------------------------------------------------//
