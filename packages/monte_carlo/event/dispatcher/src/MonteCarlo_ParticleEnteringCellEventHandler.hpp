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

// FRENSIE Includes
#include "MonteCarlo_ParticleEnteringCellEventDispatcher.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_Vector.hpp"

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
                               const Geometry::Model::EntityId cell_entering );

protected:

  /*! \brief Register an observer with the appropriate particle entering cell
   * event dispatcher.
   */
  template<typename Observer>
  void registerObserverWithTag( const std::shared_ptr<Observer>& observer,
                                const std::set<uint64_t>& entity_ids,
                                const std::set<ParticleType>& particle_types,
                                ParticleEnteringCellEventObserver::EventTag );

  /*! \brief Register an observer with the appropriate particle entering cell
   * event dispatcher.
   */
  template<typename Observer>
  void registerObserverWithTag( const std::shared_ptr<Observer>& observer,
                                const std::set<uint64_t>& entity_ids,
                                ParticleEnteringCellEventObserver::EventTag );

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The particle entering cell event dispatcher
  ParticleEnteringCellEventDispatcher
  d_particle_entering_cell_event_dispatcher;
};

// Register an observer with the appropriate particle entering cell event
// dispatcher
template<typename Observer>
inline void ParticleEnteringCellEventHandler::registerObserverWithTag(
                                  const std::shared_ptr<Observer>& observer,
                                  const std::set<uint64_t>& entity_ids,
                                  const std::set<ParticleType>& particle_types,
                                  ParticleEnteringCellEventObserver::EventTag )
{
  // Make sure the Observer class has the corrent event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleEnteringCellEventObserver::EventTag>::value));

  std::shared_ptr<ParticleEnteringCellEventObserver> observer_base =
    std::dynamic_pointer_cast<ParticleEnteringCellEventObserver>( observer );

  for( auto&& entity_id : entity_ids )
  {
    d_particle_entering_cell_event_dispatcher.attachObserver( entity_id,
                                                              particle_types,
                                                              observer_base );
  }
}
  
// Register an observer with the appropriate particle entering cell event
// dispatcher
template<typename Observer>
inline void ParticleEnteringCellEventHandler::registerObserverWithTag(
                                  const std::shared_ptr<Observer>& observer,
                                  const std::set<uint64_t>& entity_ids,
                                  ParticleEnteringCellEventObserver::EventTag )
{
  // Make sure the Observer class has the corrent event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleEnteringCellEventObserver::EventTag>::value));

  std::shared_ptr<ParticleEnteringCellEventObserver> observer_base =
    std::dynamic_pointer_cast<ParticleEnteringCellEventObserver>( observer );

  for( auto&& entity_id : entity_ids )
  {
    d_particle_entering_cell_event_dispatcher.attachObserver( entity_id,
                                                              observer_base );
  }
}

// Serialize the observer
template<typename Archive>
void ParticleEnteringCellEventHandler::serialize( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_particle_entering_cell_event_dispatcher );
}

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleEnteringCellEventHandler, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleEnteringCellEventHandler );

#endif // end MONTE_CARLO_PARTICLE_ENTERING_CELL_EVENT_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnteringCellEventHandler.hpp
//---------------------------------------------------------------------------//
