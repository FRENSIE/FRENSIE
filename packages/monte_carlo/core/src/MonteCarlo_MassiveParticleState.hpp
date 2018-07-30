//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MassiveParticleState.hpp
//! \author Alex Robinson
//! \brief  Massive particle state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MASSIVE_PARTICLE_STATE_HPP
#define MONTE_CARLO_MASSIVE_PARTICLE_STATE_HPP

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The massive particle state class
class MassiveParticleState : public MonteCarlo::ParticleState
{

private:

  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! Default Constructor
  MassiveParticleState();

  //! Constructor
  MassiveParticleState( const historyNumberType history_number,
			const ParticleType type,
			const chargeType charge );

  //! Copy constructor (with possible creation of new generation)
  MassiveParticleState( const ParticleState& existing_base_state,
			const ParticleType new_type,
			const chargeType new_charge,
			const double new_rest_mass_energy,
			const bool increment_generation_number,
			const bool reset_collision_number );

  //! Copy constructor (with possible creation of new generation)
  MassiveParticleState( const MassiveParticleState& existing_state,
			const ParticleType new_type,
			const chargeType new_charge,
			const double new_rest_mass_energy,
			const bool increment_generation_number,
			const bool reset_collision_number );

  //! Destructor
  virtual ~MassiveParticleState()
  { /* ... */ }

  //! Set the energy of the particle (MeV)
  virtual void setEnergy( const ParticleState::energyType energy );

  //! Return the speed of the particle (cm/s)
  double getSpeed() const;

  //! Set the speed of the particle (cm/s)
  virtual void setSpeed( const double speed );

  //! Return the rest mass energy of the particle (MeV)
  virtual double getRestMassEnergy() const = 0;

private:

  // Calculate the time to traverse a distance
  ParticleState::timeType calculateTraversalTime( const double distance) const;

  // Save the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ParticleState);
    ar & BOOST_SERIALIZATION_NVP( d_speed );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The speed of the particle
  double d_speed;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( MassiveParticleState, MonteCarlo );
BOOST_SERIALIZATION_CLASS_VERSION( MassiveParticleState, MonteCarlo, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, MassiveParticleState );

#endif // end MONTE_CARLO_MASSIVE_PARTICLE_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_MassiveParticleState.hpp
//---------------------------------------------------------------------------//
