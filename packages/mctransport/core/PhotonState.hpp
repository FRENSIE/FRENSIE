//---------------------------------------------------------------------------//
//!
//! \file   PhotonState.hpp
//! \author Alex Robinson
//! \brief  Photon state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PHOTON_STATE_HPP
#define PHOTON_STATE_HPP

// FACEMC Includes
#include "ParticleState.hpp"

namespace FACEMC{

//! The photon state class
class PhotonState : public ParticleState
{

private:

  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  PhotonState( const ParticleState::historyNumberType history_number );

  //! Copy constructor (with possible creation of new generation)
  PhotonState( const ParticleState& existing_base_state,
	       const bool increment_generation_number = false,
	       const bool reset_collision_number = false );

  //! Core constructor
  PhotonState( const ParticleStateCore& core );

  //! Assignment operator
  PhotonState& operator=( const PhotonState& existing_photon_state );

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

} // end FACEMC namespace

#endif // end PHOTON_STATE_HPP

//---------------------------------------------------------------------------//
// end PhotonState.hpp
//---------------------------------------------------------------------------//
