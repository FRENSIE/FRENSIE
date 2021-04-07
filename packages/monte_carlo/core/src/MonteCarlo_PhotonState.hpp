//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonState.hpp
//! \author Alex Robinson
//! \brief  Photon state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTON_STATE_HPP
#define MONTE_CARLO_PHOTON_STATE_HPP

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_MasslessParticleState.hpp"
#include "Utility_TypeNameTraitsDecl.hpp"

namespace MonteCarlo{

//! The photon state class
class PhotonState : public MasslessParticleState
{

private:

  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

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

  //! Clone the particle state (do not use to generate new particles!)
  PhotonState* clone() const;

  //! Print the photon state
  void toStream( std::ostream& os ) const;

private:

  // Save the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(MasslessParticleState); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( PhotonState, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PhotonState, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, PhotonState );
TYPE_NAME_TRAITS_QUICK_DECL2( PhotonState, MonteCarlo );

#endif // end MONTE_CARLO_PHOTON_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonState.hpp
//---------------------------------------------------------------------------//
