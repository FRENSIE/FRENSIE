//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnteringCellEventHandler.hpp
//! \author Alex Robinson
//! \brief  Particle entering cell event handler declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_HANDLER_HPP
#define MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_HANDLER_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/mpl/contains.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleEnteringCellEventDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

/*! The particle entering cell event handler class
 * \ingroup particle_entering_cell_event
 */
class ParticleEnteringCellEventHandler
{

public:

  //! Constructor
  ParticleEnteringCellEventHandler();

  //! Destructor
  virtual ~ParticleEnteringCellEventHandler()
  { /* ... */ }
  
  //! Return the particle entering cell event dispatcher
  ParticleEnteringCellEventDispatcher&
  getParticleEnteringCellEventDispatcher();

  //! Return the particle entering cell event dispatcher
  const ParticleEnteringCellEventDispatcher&
  getParticleEnteringCellEventDispatcher() const;

  //! Update the observers from a particle entering cell event
  void updateObserversFromParticleEnteringCellEvent(
              const ParticleState& particle,
              const Geometry::ModuleTraits::InternalCellHandle cell_entering );

protected:

  /*! \brief Register an observer with the appropriate particle entering cell 
   * event dispatcher.
   */
  template<typename Observer, typename EntityHandle>
  void registerObserverWithTag( const std::shared_ptr<Observer>& observer,
                                const Teuchos::Array<EntityHandle>& entity_ids,
                                ParticleEnteringCellEventObserver::EventTag );

private:

  // The particle entering cell event dispatcher
  ParticleEnteringCellEventDispatcher
  d_particle_entering_cell_event_dispatcher;
};

// Register an observer with the appropriate particle entering cell event
// dispatcher
template<typename Observer, typename EntityHandle>
inline void ParticleEnteringCellEventHandler::registerObserverWithTag( 
                                const std::shared_ptr<Observer>& observer,
                                const Teuchos::Array<EntityHandle>& entity_ids,
                                ParticleEnteringCellEventObserver::EventTag )
{
  // Make sure the Observer class has the corrent event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleEnteringCellEventObserver::EventTag>::value));
  
  std::shared_ptr<ParticleEnteringCellEventObserver> observer_base = 
    std::dynamic_pointer_cast<ParticleEnteringCellEventObserver>( observer );
  
  for( unsigned i = 0u; i < entity_ids.size(); ++i )
  {
    d_particle_entering_cell_event_dispatcher.attachObserver(entity_ids[i],
							     observer->getId(),
                                                             observer_base );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnteringCellEventHandler.hpp
//---------------------------------------------------------------------------//
