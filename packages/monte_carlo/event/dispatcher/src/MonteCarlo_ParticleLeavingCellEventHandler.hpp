//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleLeavingCellEventHandler.hpp
//! \author Alex Robinson
//! \brief  Particle leaving cell event handler declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_HANDLER_HPP
#define MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_HANDLER_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/mpl/contains.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleLeavingCellEventDispatcher.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! The particle leaving cell event handler class
 * \ingroup particle_leaving_cell_event
 */
class ParticleLeavingCellEventHandler
{

public:

  //! Constructor
  ParticleLeavingCellEventHandler();

  //! Destructor
  virtual ~ParticleLeavingCellEventHandler()
  { /* ... */ }

  //! Return the particle leaving cell event dispatcher
  ParticleLeavingCellEventDispatcher&
  getParticleLeavingCellEventDispatcher();

  //! Return the particle leaving cell event dispatcher
  const ParticleLeavingCellEventDispatcher&
  getParticleLeavingCellEventDispatcher() const;

  //! Update the observers from a particle leaving cell event
  void updateObserversFromParticleLeavingCellEvent(
               const ParticleState& particle,
               const Geometry::Model::EntityId cell_leaving );

protected:

  // Register an observer with the appropriate particle leaving cell event
  // dispatcher
  template<typename Observer, typename EntityHandle>
  void registerObserverWithTag( const std::shared_ptr<Observer>& observer,
                                const std::vector<EntityHandle>& entity_ids,
                                ParticleLeavingCellEventObserver::EventTag );

private:

  // The particle leaving cell event dispatcher
  ParticleLeavingCellEventDispatcher
  d_particle_leaving_cell_event_dispatcher;
};

// Register an observer with the appropriate particle leaving cell event
// dispatcher
template<typename Observer, typename EntityHandle>
inline void ParticleLeavingCellEventHandler::registerObserverWithTag(
                                const std::shared_ptr<Observer>& observer,
                                const std::vector<EntityHandle>& entity_ids,
                                ParticleLeavingCellEventObserver::EventTag )
{
  // Make sure the observer has the expected event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleLeavingCellEventObserver::EventTag>::value));

  std::shared_ptr<ParticleLeavingCellEventObserver> observer_base =
    std::dynamic_pointer_cast<ParticleLeavingCellEventObserver>( observer );

  for( unsigned i = 0u; i < entity_ids.size(); ++i )
  {
    d_particle_leaving_cell_event_dispatcher.attachObserver( entity_ids[i],
                                                             observer->getId(),
                                                             observer_base );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_LEAVING_CELL_EVENT_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleLeavingCellEventHandler.hpp
//---------------------------------------------------------------------------//
