//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCrossingSurfaceEventHandler.hpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event handler declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_HANDLER_HPP
#define MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_HANDLER_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/mpl/contains.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleCrossingSurfaceEventDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

/*! The particle crossing surface event handler class
 * \ingroup particle_crossing_surface_event
 */
class ParticleCrossingSurfaceEventHandler
{

public:
  
  //! Constructor
  ParticleCrossingSurfaceEventHandler();

  //! Destructor
  virtual ~ParticleCrossingSurfaceEventHandler()
  { /* ... */ }

  //! Return the particle crossing surface event dispatcher
  ParticleCrossingSurfaceEventDispatcher&
  getParticleCrossingSurfaceEventDispatcher();

  //! Return the particle crossing surface event dispatcher
  const ParticleCrossingSurfaceEventDispatcher&
  getParticleCrossingSurfaceEventDispatcher() const;

  //! Update the observers from a surface intersection event
  void updateObserversFromParticleCrossingSurfaceEvent(
	  const ParticleState& particle,
          const Geometry::ModuleTraits::InternalSurfaceHandle surface_crossing,
	  const double surface_normal[3] );

protected:

  /*! \brief Register an observer with the appropriate particle crossing 
   * surface event dispatcher
   */
  template<typename Observer, typename EntityHandle>
  void registerObserverWithTag( 
                              const std::shared_ptr<Observer>& observer,
                              const Teuchos::Array<EntityHandle>& entity_ids,
                              ParticleCrossingSurfaceEventObserver::EventTag );

private:

  // The particle crossing surface event dispatcher
  ParticleCrossingSurfaceEventDispatcher
  d_particle_crossing_surface_event_dispatcher;
}; 

// Register an observer with the appropriate particle crossing 
// surface event dispatcher
template<typename Observer, typename EntityHandle>
inline void ParticleCrossingSurfaceEventHandler::registerObserverWithTag( 
                               const std::shared_ptr<Observer>& observer,
                               const Teuchos::Array<EntityHandle>& entity_ids,
                               ParticleCrossingSurfaceEventObserver::EventTag )
{
  // Make sure the Observer class has the corrent event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleCrossingSurfaceEventObserver::EventTag>::value));
  
  std::shared_ptr<ParticleCrossingSurfaceEventObserver> observer_base = 
    std::dynamic_pointer_cast<ParticleCrossingSurfaceEventObserver>( observer );
  
  for( unsigned i = 0u; i < entity_ids.size(); ++i )
  {
    d_particle_crossing_surface_event_dispatcher.attachObserver(
                                                             entity_ids[i],
							     observer->getId(),
							     observer_base );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCrossingSurfaceEventHandler.hpp
//---------------------------------------------------------------------------//
