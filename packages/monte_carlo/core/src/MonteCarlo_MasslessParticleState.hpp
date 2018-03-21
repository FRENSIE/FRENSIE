//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MasslessParticleState.hpp
//! \author Alex Robinson
//! \brief  Massless particle state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MASSLESS_PARTICLE_STATE_HPP
#define MONTE_CARLO_MASSLESS_PARTICLE_STATE_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The massless particle state class
class MasslessParticleState : public ParticleState
{

private:

  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! Default constructor
  MasslessParticleState();

  //! Constructor
  MasslessParticleState( const historyNumberType history_number,
			 const ParticleType type,
			 const chargeType charge );

  //! Copy constructor (with possible creation of new generation)
  MasslessParticleState( const ParticleState& existing_base_state,
			 const ParticleType new_type,
			 const chargeType new_charge,
			 const bool increment_generation_number,
			 const bool reset_collision_number );

  //! Destructor
  virtual ~MasslessParticleState()
  { /* ... */ }

  //! Return the speed of the particle (cm/s)
  double getSpeed() const;

private:

  //! Calculate the time to traverse a distance
  ParticleState::timeType calculateTraversalTime( const double distance) const;

  // Save the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ParticleState);
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::MasslessParticleState );
BOOST_CLASS_VERSION( MonteCarlo::MasslessParticleState, 0 );
EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::MasslessParticleState );

#endif // end MONTE_CARLO_MASSLESS_PARTICLE_STATE_HPP

//---------------------------------------------------------------------------//
// end MontCarlo_MasslessParticleState.hpp
//---------------------------------------------------------------------------//
