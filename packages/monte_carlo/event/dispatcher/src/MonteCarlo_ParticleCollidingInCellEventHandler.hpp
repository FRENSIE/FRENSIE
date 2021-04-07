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

// Boost Includes
#include <boost/mpl/contains.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleCollidingInCellEventDispatcher.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_Vector.hpp"

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
  template<typename Observer>
  void registerObserverWithTag(
                              const std::shared_ptr<Observer>& observer,
                              const std::set<uint64_t>& entity_ids,
                              const std::set<ParticleType>& particle_types,
                              ParticleCollidingInCellEventObserver::EventTag );

  /*! \brief Register an observer with the appropriate particle colliding in
   * cell event dispatcher.
   */
  template<typename Observer>
  void registerObserverWithTag(
                              const std::shared_ptr<Observer>& observer,
                              const std::set<uint64_t>& entity_ids,
                              ParticleCollidingInCellEventObserver::EventTag );

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The particle colliding in cell event dispatcher
  ParticleCollidingInCellEventDispatcher
  d_particle_colliding_in_cell_event_dispatcher;
};

// Register an observer with the appropriate particle colliding in
// cell event dispatcher.
template<typename Observer>
inline void ParticleCollidingInCellEventHandler::registerObserverWithTag(
                               const std::shared_ptr<Observer>& observer,
                               const std::set<uint64_t>& entity_ids,
                               const std::set<ParticleType>& particle_types,
                               ParticleCollidingInCellEventObserver::EventTag )
{
  // Make sure the Observer class has the correct event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleCollidingInCellEventObserver::EventTag>::value));

  std::shared_ptr<ParticleCollidingInCellEventObserver> observer_base =
    std::dynamic_pointer_cast<ParticleCollidingInCellEventObserver>( observer );

  for( auto&& entity_id : entity_ids )
  {
    d_particle_colliding_in_cell_event_dispatcher.attachObserver(
                                                               entity_id,
                                                               particle_types,
                                                               observer_base );
  }
}

// Register an observer with the appropriate particle colliding in
// cell event dispatcher.
template<typename Observer>
inline void ParticleCollidingInCellEventHandler::registerObserverWithTag(
                               const std::shared_ptr<Observer>& observer,
                               const std::set<uint64_t>& entity_ids,
                               ParticleCollidingInCellEventObserver::EventTag )
{
  // Make sure the Observer class has the correct event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleCollidingInCellEventObserver::EventTag>::value));

  std::shared_ptr<ParticleCollidingInCellEventObserver> observer_base =
    std::dynamic_pointer_cast<ParticleCollidingInCellEventObserver>( observer );

  for( auto&& entity_id : entity_ids )
  {
    d_particle_colliding_in_cell_event_dispatcher.attachObserver(
                                                               entity_id,
                                                               observer_base );
  }
}

// Serialize the observer
template<typename Archive>
void ParticleCollidingInCellEventHandler::serialize( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_particle_colliding_in_cell_event_dispatcher );
}

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleCollidingInCellEventHandler, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleCollidingInCellEventHandler );

#endif // end MONTE_CARLO_PARTICLE_COLLIDING_IN_CELL_EVENT_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCollidingInCellEventHandler.hpp
//---------------------------------------------------------------------------//
