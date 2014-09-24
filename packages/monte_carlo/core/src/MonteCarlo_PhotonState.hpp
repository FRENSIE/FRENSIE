//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonState.hpp
//! \author Alex Robinson
//! \brief  Photon state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PHOTON_STATE_HPP
#define FACEMC_PHOTON_STATE_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"

namespace MonteCarlo{

//! The photon state class
class PhotonState : public ParticleState
{

private:

  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:
  
  // The photon tag
  struct PhotonTag{};

  // Typedef for the photon tag
  struct PhotonTag ParticleTag;

  //! Constructor
  PhotonState( const ParticleState::historyNumberType history_number );

  //! Copy constructor (with possible creation of new generation)
  PhotonState( const ParticleState& existing_base_state,
	       const bool increment_generation_number = false,
	       const bool reset_collision_number = false );

  //! Core constructor
  PhotonState( const ParticleStateCore& core );

  //! Destructor
  ~PhotonState()
  { /* ... */ }

  //! Return the speed of the particle (cm/s)
  double getSpeed() const;

  //! Print the photon state
  void print( std::ostream& os ) const;

private:
  
  //! Calculate the time to traverse a distance
  ParticleState::timeType calculateTraversalTime( const double distance) const;
};

} // end MonteCarlo namespace

#endif // end FACEMC_PHOTON_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonState.hpp
//---------------------------------------------------------------------------//
