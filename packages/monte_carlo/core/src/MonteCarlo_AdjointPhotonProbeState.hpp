//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonProbeState.hpp
//! \author Alex Robinson
//! \brief  Adjoint photon probe state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTON_PROBE_STATE_HPP
#define MONTE_CARLO_ADJOINT_PHOTON_PROBE_STATE_HPP

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonState.hpp"
#include "Utility_TypeNameTraits.hpp"

namespace MonteCarlo{

/*! The adjoint photon probe state class
 * \details The probe state get killed when its energy changes (after being
 * activated).
 */
class AdjointPhotonProbeState : public AdjointPhotonState
{

public:

  // The adjoint photon probe tag
  struct AdjointPhotonProbeTag{};

  // Typedef for the adjoint photon probe tag
  struct AdjointPhotonProbeTag ParticleTag;

  //! Default constructor
  AdjointPhotonProbeState();

  //! Constructor
  AdjointPhotonProbeState(
		       const ParticleState::historyNumberType history_number );

  //! Copy constructor (with possible creation of new generation)
  AdjointPhotonProbeState( const ParticleState& existing_base_state,
			   const bool increment_generation_number = false,
			   const bool reset_collision_number = false );

  //! Copy constructor (with possible creation of new generation)
  AdjointPhotonProbeState( const AdjointPhotonProbeState& existing_base_state,
			   const bool increment_generation_number = false,
			   const bool reset_collision_number = false );

  //! Destructor
  ~AdjointPhotonProbeState()
  { /* ... */ }

  //! Set the energy of the particle (MeV)
  void setEnergy( const energyType energy );

  //! Check if this is a probe
  bool isProbe() const;

  //! Activate the probe
  void activate();

  //! Returns if the probe is active
  bool isActive() const;

  //! Clone the particle state (do not use to generate new particles!)
  AdjointPhotonProbeState* clone() const;

  //! Print the adjoint photon state
  void toStream( std::ostream& os ) const;

private:

  // Save the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(AdjointPhotonState);
    ar & BOOST_SERIALIZATION_NVP( d_active );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // Flag that indicates if the probe is active
  bool d_active;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::AdjointPhotonProbeState, 0 );
BOOST_CLASS_EXPORT_KEY2( MonteCarlo::AdjointPhotonProbeState, "AdjointPhotonProbeState" );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, AdjointPhotonProbeState );
TYPE_NAME_TRAITS_QUICK_DECL2( AdjointPhotonProbeState, MonteCarlo );

#endif // end MONTE_CARLO_ADJOINT_PHOTON_PROBE_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonProbeState.hpp
//---------------------------------------------------------------------------//
