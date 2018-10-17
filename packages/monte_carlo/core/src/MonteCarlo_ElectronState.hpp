//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronState.hpp
//! \author Luke Kersting
//! \brief  Electron state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRON_STATE_HPP
#define MONTE_CARLO_ELECTRON_STATE_HPP

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_ChargedParticleState.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_TypeNameTraits.hpp"

namespace MonteCarlo{

//! The electron state class
class ElectronState : public MonteCarlo::ChargedParticleState
{

private:

  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  // The electron tag
  struct ElectronTag{};

  // Typedef for the electron tag
  typedef ElectronTag ParticleTag;

  //! The particle state type (for compile time usage)
  static const ParticleType type = ELECTRON;

  //! Default constructor
  ElectronState();

  //! Constructor
  ElectronState( const ParticleState::historyNumberType history_number );

  //! Copy constructor (with possible creation of new generation)
  ElectronState( const ElectronState& existing_electron_state,
		const bool increment_generation_number = false,
		const bool reset_collision_number = false );

  //! Copy constructor (with possible creation of new generation)
  ElectronState( const ParticleState& existing_base_state,
		const bool increment_generation_number = false,
		const bool reset_collision_number = false );

  //! Destructor
  ~ElectronState()
  { /* ... */ }

  //! Return the rest mass energy of the electron (MeV)
  double getRestMassEnergy() const;

  //! Clone the particle state (do not use to generate new particles!)
  ElectronState* clone() const;

  //! Print the electron state
  void toStream( std::ostream& os ) const;

private:

  // Save the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ChargedParticleState); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( ElectronState, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ElectronState, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ElectronState );
TYPE_NAME_TRAITS_QUICK_DECL2( ElectronState, MonteCarlo );

#endif // end MonteCarlo_ELECTRON_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronState.hpp
//---------------------------------------------------------------------------//
