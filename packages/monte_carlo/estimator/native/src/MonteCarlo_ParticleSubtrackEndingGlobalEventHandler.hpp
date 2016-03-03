//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingGlobalEventHandler.hpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending global event handler declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_HANDLER_HPP
#define MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_HANDLER_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/mpl/contains.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

/*! The particle subtrack ending global event handler class
 * \ingroup particle_subtrack_ending_global_event
 */
class ParticleSubtrackEndingGlobalEventHandler
{

public:

  //! Constructor
  ParticleSubtrackEndingGlobalEventHandler();

  //! Destructor
  virtual ~ParticleSubtrackEndingGlobalEventHandler()
  { /* ... */ }

  //! Return the particle subtrack ending global event dispatcher
  ParticleSubtrackEndingGlobalEventDispatcher&
  getParticleSubtrackEndingGlobalEventDispatcher();

  //! Return the particle subtrack ending global event dispatcher
  const ParticleSubtrackEndingGlobalEventDispatcher&
  getParticleSubtrackEndingGlobalEventDispatcher() const;

  //! Update the global estimators from a subtrack ending event
  void updateObserversFromParticleSubtrackEndingGlobalEvent(
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] );
protected:

  // Register a global observer with the appropraite particle subtrack ending
  // global event dispatcher
  template<typename Observer>
  void registerGlobalObserverWithTag( 
			 const std::shared_ptr<Observer>& observer,
			 ParticleSubtrackEndingGlobalEventObserver::EventTag );

private:

  // The particle subtrack ending global event dispatcher
  ParticleSubtrackEndingGlobalEventDispatcher
  d_particle_subtrack_ending_global_event_dispatcher;
};

// Register a global observer with the appropraite particle subtrack ending
// global event dispatcher
template<typename Observer>
void ParticleSubtrackEndingGlobalEventHandler::registerGlobalObserverWithTag( 
			 const std::shared_ptr<Observer>& observer,
			 ParticleSubtrackEndingGlobalEventObserver::EventTag )
{
  // Make sure the Observer class has the expected event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleSubtrackEndingGlobalEventObserver::EventTag>::value));

  std::shared_ptr<ParticleSubtrackEndingGlobalEventObserver> observer_base = 
    observer;

  d_particle_subtrack_ending_global_event_dispatcher.attachObserver(
							     observer->getId(),
							     observer_base );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingGlobalEventHandler.hpp
//---------------------------------------------------------------------------//
