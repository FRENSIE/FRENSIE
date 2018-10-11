//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronState.hpp
//! \author Luke Kersting
//! \brief  Adjoint electron state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTRON_STATE_HPP
#define MONTE_CARLO_ADJOINT_ELECTRON_STATE_HPP

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_ChargedParticleState.hpp"
#include "Utility_TypeNameTraits.hpp"

namespace MonteCarlo{

//! The adjoint electron state class
class AdjointElectronState : public ChargedParticleState
{

public:

  // The adjoint electron tag
  struct AdjointElectronTag{};

  // Typedef for the adjoint electron tag
  struct AdjointElectronTag ParticleTag;

  //! The particle state type (for compile time usage)
  static const ParticleType type = ADJOINT_ELECTRON;

  //! Default Constructor
  AdjointElectronState();

  //! Constructor
  AdjointElectronState( const ParticleState::historyNumberType history_number );

  //! Copy constructor (with possible creation of new generation)
  AdjointElectronState( const ParticleState& existing_base_state,
                        const bool increment_generation_number = false,
                        const bool reset_collision_number = false );

  //! Copy constructor (with possible creation of new generation)
  AdjointElectronState( const AdjointElectronState& existing_base_state,
                        const bool increment_generation_number = false,
                        const bool reset_collision_number = false );

  //! Destructor
  virtual ~AdjointElectronState()
  { /* ... */ }

  //! Check if this is a probe
  virtual bool isProbe() const;

  //! Clone the particle state (do not use to generate new particles!)
  virtual AdjointElectronState* clone() const;

  //! Return the rest mass energy of the electron (MeV)
  double getRestMassEnergy() const;

  //! Print the adjoint electron state
  virtual void toStream( std::ostream& os ) const;

protected:

  //! Probe constructor
  AdjointElectronState( const ParticleState::historyNumberType history_number,
                        const ParticleType probe_type,
                        const chargeType probe_charge );

  //! Probe copy constructor
  AdjointElectronState( const ParticleState& existing_base_state,
                        const ParticleType probe_type,
                        const chargeType probe_charge,
                        const bool increment_generation_number,
                        const bool reset_collision_number );

private:

  // Save the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ChargedParticleState); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( AdjointElectronState, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( AdjointElectronState, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, AdjointElectronState );
TYPE_NAME_TRAITS_QUICK_DECL2( AdjointElectronState, MonteCarlo );

#endif // end MONTE_CARLO_ADJOINT_ELECTRON_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronState.hpp
//---------------------------------------------------------------------------//
