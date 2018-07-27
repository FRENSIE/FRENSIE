//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCollidingGlobalEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending global event dispatcher
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_DISPATCHER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleGlobalEventDispatcher.hpp"
#include "MonteCarlo_ParticleCollidingGlobalEventObserver.hpp"
#include "MonteCarlo_ParticleState.hpp"

namespace MonteCarlo{

/*! The particle subtrack ending global event dispatcher class
 * \ingroup particle_subtrack_ending_global_event
 */
class ParticleCollidingGlobalEventDispatcher : public ParticleGlobalEventDispatcher<ParticleCollidingGlobalEventObserver>
{
  typedef ParticleGlobalEventDispatcher<ParticleCollidingGlobalEventObserver> BaseType;

public:

  //! Constructor
  ParticleCollidingGlobalEventDispatcher()
  { /* ... */ }

  //! Destructor
  ~ParticleCollidingGlobalEventDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleCollidingGlobalEvent( const ParticleState& particle,
                                                  const double start_point[3],
                                                  const double end_point[3] );

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleCollidingGlobalEventDispatcher, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleCollidingGlobalEventDispatcher );

#endif // end MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCollidingGlobalEventDispatcher.hpp
//---------------------------------------------------------------------------//
