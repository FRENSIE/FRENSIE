//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronState.hpp
//! \author Alex Robinson
//! \brief  Neutron state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_STATE_HPP
#define MONTE_CARLO_NEUTRON_STATE_HPP

// FRENSIE Includes
#include "MonteCarlo_MassiveParticleState.hpp"

namespace MonteCarlo{

//! The neutron state class
class NeutronState : public MassiveParticleState
{

private:

  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  // The neutron tag
  struct NeutronTag{};

  // Typedef for the neutron tag
  typedef NeutronTag ParticleTag;

  //! The particle state type (for compile time usage)
  static const ParticleType type = NEUTRON;

  //! Default constructor
  NeutronState();

  //! Constructor
  NeutronState( const ParticleState::historyNumberType history_number );

  //! Copy constructor (with possible creation of new generation)
  NeutronState( const ParticleState& existing_base_state,
		const bool increment_generation_number = false,
		const bool reset_collision_number = false );

  //! Copy constructor (with possible creation of new generation)
  NeutronState( const NeutronState& existing_base_state,
		const bool increment_generation_number = false,
		const bool reset_collision_number = false );

  //! Destructor
  ~NeutronState()
  { /* ... */ }

  //! Return the rest mass energy of the neutron (MeV)
  double getRestMassEnergy() const;

  //! Clone the particle state (do not use to generate new particles!)
  NeutronState* clone() const;

  //! Print the neutron state
  void print( std::ostream& os ) const;

private:

  // Save the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(MassiveParticleState);
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::NeutronState, 0 );
BOOST_CLASS_EXPORT_KEY2( MonteCarlo::NeutronState, "NeutronState" );

#endif // end MonteCarlo_NEUTRON_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronState.hpp
//---------------------------------------------------------------------------//
