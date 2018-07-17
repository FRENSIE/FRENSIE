//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCollidingGlobalEventActor.hpp
//! \author Alex Robinson
//! \brief  Particle colliding global event actor base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_COLLIDING_GLOBAL_EVENT_ACTOR_HPP
#define MONTE_CARLO_PARTICLE_COLLISING_GLOBAL_EVENT_ACTOR_HPP

// Std Lib Includes
#include <functional>

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleEventTags.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Geometry_Model.hpp"
#include "Utility_Vector.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

/*! The particle colliding global event actor base class
 * \ingroup particle_colliding_global_event
 */
class ParticleCollidingGlobalEventActor
{

public:

  //! Typedef for the actor event tag
  typedef ParticleCollidingGlobalEvent EventTag;

  //! This method can be used to simulate the collision of a generated particle
  typedef std::function<void(ParticleState&,ParticleBank&)> SimulateParticleCollision;

  //! Constructor
  ParticleCollidingGlobalEventActor()
  { /* ... */ }

  //! Destructor
  virtual ~ParticleCollidingGlobalEventActor()
  { /* ... */ }

  //! Update the particle state and bank
  virtual void updateFromGlobalParticleCollidingEvent(
                  const SimulateParticleCollision& simulate_particle_collision,
                  ParticleState& particle,
                  ParticleBank& bank ) const = 0;

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};
  
} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleCollidingGlobalEventActor, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::ParticleCollidingGlobalEventActor );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleCollidingGlobalEventActor );

#endif // end MONTE_CARLO_PARTICLE_COLLISING_GLOBAL_EVENT_ACTOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCollidingGlobalEventActor.hpp
//---------------------------------------------------------------------------//
