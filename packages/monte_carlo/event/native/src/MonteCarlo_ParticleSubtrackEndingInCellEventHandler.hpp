//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingInCellEventHandler.hpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event handler declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_HANDLER_HPP
#define MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_HANDLER_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/mpl/contains.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSubtrackEndingInCellEventDispatcher.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

/*! The particle subtrack ending in cell event handler class
 * \ingroup particle_subtrack_ending_in_cell_event
 */
class ParticleSubtrackEndingInCellEventHandler
{

public:

  //! Constructor
  ParticleSubtrackEndingInCellEventHandler();

  //! Destructor
  virtual ~ParticleSubtrackEndingInCellEventHandler()
  { /* ... */ }

  //! Return the particle subtrack ending in cell event dispatcher
  ParticleSubtrackEndingInCellEventDispatcher&
  getParticleSubtrackEndingInCellEventDispatcher();

  //! Return the particle subtrack ending in cell event dispatcher
  const ParticleSubtrackEndingInCellEventDispatcher&
  getParticleSubtrackEndingInCellEventDispatcher() const;

  //! Update the observers from a particle subtrack ending in cell event
  void updateObserversFromParticleSubtrackEndingInCellEvent(
             const ParticleState& particle,
             const Geometry::ModuleTraits::InternalCellHandle cell_of_subtrack,
             const double particle_subtrack_length,
             const double subtrack_start_time );

protected:

  /*! \brief Register an observer with the appropriate particle subtrack ending
   * in cell event dispatcher.
   */
  template<typename Observer, typename EntityHandle>
  void registerObserverWithTag( 
                         const std::shared_ptr<Observer>& observer,
			 const Teuchos::Array<EntityHandle>& entity_ids,
			 ParticleSubtrackEndingInCellEventObserver::EventTag );

private:

  // The particle colliding in cell event dispatcher
  ParticleSubtrackEndingInCellEventDispatcher
  d_particle_subtrack_ending_in_cell_event_dispatcher;
};

// Register an observer with the appropriate particle subtrack ending in cell
// event dispatcher
template<typename Observer, typename EntityHandle>
inline void ParticleSubtrackEndingInCellEventHandler::registerObserverWithTag( 
                          const std::shared_ptr<Observer>& observer,
                          const Teuchos::Array<EntityHandle>& entity_ids,
                          ParticleSubtrackEndingInCellEventObserver::EventTag )
{
  // Make sure the Observer class has the expected event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleSubtrackEndingInCellEventObserver::EventTag>::value));
  
  std::shared_ptr<ParticleSubtrackEndingInCellEventObserver> observer_base = 
    std::dynamic_pointer_cast<ParticleSubtrackEndingInCellEventObserver>( 
								    observer );
  
  for( unsigned i = 0u; i < entity_ids.size(); ++i )
  {
    d_particle_subtrack_ending_in_cell_event_dispatcher.attachObserver(
							     entity_ids[i],
							     observer->getId(),
							     observer_base );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingInCellEventHandler
//---------------------------------------------------------------------------//
