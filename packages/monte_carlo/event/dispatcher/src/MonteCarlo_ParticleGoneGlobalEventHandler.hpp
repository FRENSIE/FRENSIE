//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleGoneGlobalEventHandler.hpp
//! \author Alex Robinson
//! \brief  Particle gone global event handler declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_GONE_GLOBAL_EVENT_HANDLER_HPP
#define MONTE_CARLO_PARTICLE_GONE_GLOBAL_EVENT_HANDLER_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/mpl/contains.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleGoneGlobalEventDispatcher.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! The particle gone global event handler class
 * \ingroup particle_gone_global_event
 */
class ParticleGoneGlobalEventHandler
{

public:

  //! Constructor
  ParticleGoneGlobalEventHandler();

  //! Destructor
  virtual ~ParticleGoneGlobalEventHandler()
  { /* ... */ }

  //! Return the particle subtrack ending global event dispatcher
  ParticleGoneGlobalEventDispatcher&
  getParticleGoneGlobalEventDispatcher();

  //! Return the particle subtrack ending global event dispatcher
  const ParticleGoneGlobalEventDispatcher&
  getParticleGoneGlobalEventDispatcher() const;

  //! Update the global estimators from a subtrack ending event
  void updateObserversFromParticleGoneGlobalEvent( const ParticleState& particle );

protected:

  // Register a global observer with the appropraite particle subtrack ending
  // global event dispatcher
  template<typename Observer>
  void registerGlobalObserverWithTag(
			 const std::shared_ptr<Observer>& observer,
                         const std::set<ParticleType>& particle_types,
			 ParticleGoneGlobalEventObserver::EventTag );

  // Register a global observer with the appropraite particle subtrack ending
  // global event dispatcher
  template<typename Observer>
  void registerGlobalObserverWithTag(
			 const std::shared_ptr<Observer>& observer,
			 ParticleGoneGlobalEventObserver::EventTag );

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The particle subtrack ending global event dispatcher
  ParticleGoneGlobalEventDispatcher
  d_particle_gone_global_event_dispatcher;
};

// Register a global observer with the appropraite particle subtrack ending
// global event dispatcher
template<typename Observer>
void ParticleGoneGlobalEventHandler::registerGlobalObserverWithTag(
			          const std::shared_ptr<Observer>& observer,
                                  const std::set<ParticleType>& particle_types,
                                  ParticleGoneGlobalEventObserver::EventTag )
{
  // Make sure the Observer class has the expected event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleGoneGlobalEventObserver::EventTag>::value));

  std::shared_ptr<ParticleGoneGlobalEventObserver> observer_base = observer;

  d_particle_gone_global_event_dispatcher.attachObserver( particle_types,
                                                          observer_base );
}

// Register a global observer with the appropraite particle subtrack ending
// global event dispatcher
template<typename Observer>
void ParticleGoneGlobalEventHandler::registerGlobalObserverWithTag(
                                    const std::shared_ptr<Observer>& observer,
			            ParticleGoneGlobalEventObserver::EventTag )
{
  // Make sure the Observer class has the expected event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleGoneGlobalEventObserver::EventTag>::value));

  std::shared_ptr<ParticleGoneGlobalEventObserver> observer_base = observer;

  d_particle_gone_global_event_dispatcher.attachObserver( observer_base );
}

// Serialize the observer
template<typename Archive>
void ParticleGoneGlobalEventHandler::serialize( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_particle_gone_global_event_dispatcher );
}

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleGoneGlobalEventHandler, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleGoneGlobalEventHandler );

#endif // end MONTE_CARLO_PARTICLE_GONE_GLOBAL_EVENT_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleGoneGlobalEventHandler.hpp
//---------------------------------------------------------------------------//
