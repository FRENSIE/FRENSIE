//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonState.hpp
//! \author Alex Robinson
//! \brief  Adjoint photon state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTON_STATE_HPP
#define MONTE_CARLO_ADJOINT_PHOTON_STATE_HPP

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_MasslessParticleState.hpp"
#include "Utility_TypeNameTraits.hpp"

namespace MonteCarlo{

//! The adjoint photon state class
class AdjointPhotonState : public MasslessParticleState
{

public:

  // The adjoint photon tag
  struct AdjointPhotonTag{};

  // Typedef for the adjoint photon tag
  struct AdjointPhotonTag ParticleTag;

  //! The particle state type (for compile time usage)
  static const ParticleType type = ADJOINT_PHOTON;

  //! Default constructor
  AdjointPhotonState();

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

  //! Destructor
  virtual ~AdjointPhotonState()
  { /* ... */ }

  //! Check if this is a probe
  virtual bool isProbe() const;

  //! Clone the particle state (do not use to generate new particles!)
  virtual AdjointPhotonState* clone() const;

  //! Print the adjoint photon state
  virtual void toStream( std::ostream& os ) const;

protected:

  //! Probe constructor
  AdjointPhotonState( const ParticleState::historyNumberType history_number,
		      const ParticleType probe_type,
		      const chargeType probe_charge );

  //! Probe copy constructor
  AdjointPhotonState( const ParticleState& existing_base_state,
		      const ParticleType probe_type,
		      const chargeType probe_charge,
		      const bool increment_generation_number,
		      const bool reset_collision_number );

private:

  // Save the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(MasslessParticleState); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( AdjointPhotonState, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( AdjointPhotonState, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, AdjointPhotonState );
TYPE_NAME_TRAITS_QUICK_DECL2( AdjointPhotonState, MonteCarlo );

#endif // end MONTE_CARLO_ADJOINT_PHOTON_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonState.hpp
//---------------------------------------------------------------------------//
