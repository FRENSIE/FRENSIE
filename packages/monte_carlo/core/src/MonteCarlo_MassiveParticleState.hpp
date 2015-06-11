//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MassiveParticleState.hpp
//! \author Alex Robinson
//! \brief  Massive particle state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MASSIVE_PARTICLE_STATE_HPP
#define MONTE_CARLO_MASSIVE_PARTICLE_STATE_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"

namespace MonteCarlo{

//! The massive particle state class
class MassiveParticleState : public ParticleState
{

private:
  
  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  MassiveParticleState( const historyNumberType history_number,
			const ParticleType type );

  //! Copy constructor (with possible creation of new generation)
  MassiveParticleState( const ParticleState& existing_base_state,
			const ParticleType new_type,
			const double new_rest_mass_energy,
			const bool increment_generation_number,
			const bool reset_collision_number );

  //! Copy constructor (with possible creation of new generation)
  MassiveParticleState( const MassiveParticleState& existing_state,
			const ParticleType new_type,
			const double new_rest_mass_energy,
			const bool increment_generation_number,
			const bool reset_collision_number );

  //! Core constructor
  MassiveParticleState( const ParticleStateCore& core,
			const double new_rest_mass_energy );

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

  // The speed of the particle
  double d_speed;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_MASSIVE_PARTICLE_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_MassiveParticleState.hpp
//---------------------------------------------------------------------------//

