//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ChargedParticleState.hpp
//! \author Luke Kersting
//! \brief  Charged particle state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CHARGED_PARTICLE_STATE_HPP
#define MONTE_CARLO_CHARGED_PARTICLE_STATE_HPP

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_MassiveParticleState.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The charged particle state class
class ChargedParticleState : public MonteCarlo::MassiveParticleState
{

private:

  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! Default Constructor
  ChargedParticleState();

  //! Constructor
  ChargedParticleState( const historyNumberType history_number,
                        const ParticleType type,
                        const chargeType charge );

  //! Copy constructor (with possible creation of new generation)
  ChargedParticleState( const ParticleState& existing_base_state,
                        const ParticleType new_type,
                        const chargeType new_charge,
                        const double new_rest_mass_energy,
                        const bool increment_generation_number,
                        const bool reset_collision_number );

  //! Copy constructor (with possible creation of new generation)
  ChargedParticleState( const ChargedParticleState& existing_state,
                        const ParticleType new_type,
                        const chargeType new_charge,
                        const double new_rest_mass_energy,
                        const bool increment_generation_number,
                        const bool reset_collision_number );

  //! Destructor
  virtual ~ChargedParticleState()
  { /* ... */ }

private:


  // Save the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(MassiveParticleState); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( ChargedParticleState, MonteCarlo );
BOOST_SERIALIZATION_CLASS_VERSION( ChargedParticleState, MonteCarlo, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ChargedParticleState );

#endif // end MONTE_CARLO_CHARGED_PARTICLE_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ChargedParticleState.hpp
//---------------------------------------------------------------------------//
