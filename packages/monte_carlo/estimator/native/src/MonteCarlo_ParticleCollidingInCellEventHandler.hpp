//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCollidingInCellEventHandler.hpp
//! \author Alex Robinson
//! \brief  Particle colliding in cell event handler declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_HANDLER_HPP
#define MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_HANDLER_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// Boost Includes
#include <boost/mpl/contains.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleCollidingInCellEventDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

/*! The particle colliding in cell event handler class
 * \ingroup particle_colliding_in_cell_event
 */
class ParticleCollidingInCellEventHandler
{

public:

  //! Constructor
  ParticleCollidingInCellEventHandler();
  
  //! Destructor
  virtual ~ParticleCollidingInCellEventHandler()
  { /* ... */ }

  //! Return the particle colliding in cell event dispatcher
  ParticleCollidingInCellEventDispatcher& 
  getParticleCollidingInCellEventDispatcher();

  //! Return the particle colliding in cell event dispatcher
  const ParticleCollidingInCellEventDispatcher&
  getParticleCollidingInCellEventDispatcher() const;

  //! Update the observers from a particle colliding in cell event
  void updateObserversFromParticleCollidingInCellEvent(
                                    const ParticleState& particle,
                                    const double inverse_total_cross_section );

protected:

  /*! \brief Register an observer with the appropriate particle colliding in 
   * cell event dispatcher.
   */
  template<typename Observer, typename EntityHandle>
  void registerObserverWithTag( 
                              const std::shared_ptr<Observer>& observer,
                              const Teuchos::Array<EntityHandle>& entity_ids,
                              ParticleCollidingInCellEventObserver::EventTag );

private:

  // The particle colliding in cell event dispatcher
  ParticleCollidingInCellEventDispatcher
  d_particle_colliding_in_cell_event_dispatcher;
};

// Register an observer with the appropriate particle colliding in 
// cell event dispatcher.
template<typename Observer, typename EntityHandle>
inline void ParticleCollidingInCellEventHandler::registerObserverWithTag( 
                               const std::shared_ptr<Observer>& observer,
                               const Teuchos::Array<EntityHandle>& entity_ids,
                               ParticleCollidingInCellEventObserver::EventTag )
{
  // Make sure the Observer class has the correct event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleCollidingInCellEventObserver::EventTag>::value));
  
  std::shared_ptr<ParticleCollidingInCellEventObserver> observer_base = 
    std::dynamic_pointer_cast<ParticleCollidingInCellEventObserver>( observer );
  
  for( unsigned i = 0u; i < entity_ids.size(); ++i )
  {
    d_particle_colliding_in_cell_event_dispatcher.attachObserver(
                                                             entity_ids[i],
							     observer->getId(),
							     observer_base );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCollidingInCellEventHandler.hpp
//---------------------------------------------------------------------------//
