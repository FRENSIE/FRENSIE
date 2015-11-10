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

  //! Default constructor
  PhotonState();

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

  //! Destructor
  ~PhotonState()
  { /* ... */ }

  //! Print the photon state
  void print( std::ostream& os ) const;

private:

  // Save the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(MasslessParticleState);
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::PhotonState, 0 );

#endif // end MONTE_CARLO_PHOTON_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonState.hpp
//---------------------------------------------------------------------------//
