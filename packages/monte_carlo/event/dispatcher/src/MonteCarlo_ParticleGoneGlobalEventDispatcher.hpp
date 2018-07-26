//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleGoneGlobalEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle gone global event dispatcher declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_GONE_GLOBAL_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_GONE_GLOBAL_EVENT_DISPATCHER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleGlobalEventDispatcher.hpp"
#include "MonteCarlo_ParticleGoneGlobalEventObserver.hpp"
#include "MonteCarlo_ParticleState.hpp"

namespace MonteCarlo{

/*! The particle gone global event dispatcher class
 * \ingroup particle_gone_global_event
 */
class ParticleGoneGlobalEventDispatcher : public ParticleGlobalEventDispatcher<ParticleGoneGlobalEventObserver>
{
  typedef ParticleGlobalEventDispatcher<ParticleGoneGlobalEventObserver> BaseType;

public:

  //! Constructor
  ParticleGoneGlobalEventDispatcher()
  { /* ... */ }

  //! Destructor
  ~ParticleGoneGlobalEventDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleGoneGlobalEvent( const ParticleState& particle );

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};
  
} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleGoneGlobalEventDispatcher, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleGoneGlobalEventDispatcher );

#endif // end MONTE_CARLO_PARTICLE_GONE_GLOBAL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleGoneGlobalEventDispatcher.hpp
//---------------------------------------------------------------------------//
