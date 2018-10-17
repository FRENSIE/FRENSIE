//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronState.hpp
//! \author Luke Kersting
//! \brief  Positron state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRON_STATE_HPP
#define MONTE_CARLO_POSITRON_STATE_HPP

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_ChargedParticleState.hpp"
#include "Utility_TypeNameTraits.hpp"

namespace MonteCarlo{

//! The positron state class
class PositronState : public MonteCarlo::ChargedParticleState
{

private:

  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  // The positron tag
  struct PositronTag{};

  // Typedef for the positron tag
  typedef PositronTag ParticleTag;

  //! The particle state type (for compile time usage)
  static const ParticleType type = POSITRON;

  //! Default constructor
  PositronState();

  //! Constructor
  PositronState( const ParticleState::historyNumberType history_number );

  //! Copy constructor (with possible creation of new generation)
  PositronState( const PositronState& existing_positron_state,
                 const bool increment_generation_number = false,
                 const bool reset_collision_number = false );

  //! Copy constructor (with possible creation of new generation)
  PositronState( const ParticleState& existing_base_state,
                 const bool increment_generation_number = false,
                 const bool reset_collision_number = false );

  //! Destructor
  ~PositronState()
  { /* ... */ }

  //! Return the rest mass energy of the positron (MeV)
  double getRestMassEnergy() const;

  //! Clone the particle state (do not use to generate new particles!)
  PositronState* clone() const;

  //! Print the positron state
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

BOOST_SERIALIZATION_CLASS_VERSION( PositronState, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PositronState, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, PositronState );
TYPE_NAME_TRAITS_QUICK_DECL2( PositronState, MonteCarlo );

#endif // end MonteCarlo_POSITRON_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronState.hpp
//---------------------------------------------------------------------------//
