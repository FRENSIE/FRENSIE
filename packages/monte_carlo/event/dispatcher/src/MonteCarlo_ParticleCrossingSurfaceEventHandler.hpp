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

// FRENSIE Includes
#include "MonteCarlo_ParticleCrossingSurfaceEventDispatcher.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_Vector.hpp"

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
                              const Geometry::Model::EntityId surface_crossing,
                              const double surface_normal[3] );

protected:

  /*! \brief Register an observer with the appropriate particle crossing
   * surface event dispatcher
   */
  template<typename Observer>
  void registerObserverWithTag(
                              const std::shared_ptr<Observer>& observer,
                              const std::set<uint64_t>& entity_ids,
                              const std::set<ParticleType>& particle_types,
                              ParticleCrossingSurfaceEventObserver::EventTag );

  /*! \brief Register an observer with the appropriate particle crossing
   * surface event dispatcher
   */
  template<typename Observer>
  void registerObserverWithTag(
                              const std::shared_ptr<Observer>& observer,
                              const std::set<uint64_t>& entity_ids,
                              ParticleCrossingSurfaceEventObserver::EventTag );

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The particle crossing surface event dispatcher
  ParticleCrossingSurfaceEventDispatcher
  d_particle_crossing_surface_event_dispatcher;
};

// Register an observer with the appropriate particle crossing
// surface event dispatcher
template<typename Observer>
inline void ParticleCrossingSurfaceEventHandler::registerObserverWithTag(
                               const std::shared_ptr<Observer>& observer,
                               const std::set<uint64_t>& entity_ids,
                               const std::set<ParticleType>& particle_types,
                               ParticleCrossingSurfaceEventObserver::EventTag )
{
  // Make sure the Observer class has the corrent event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleCrossingSurfaceEventObserver::EventTag>::value));

  std::shared_ptr<ParticleCrossingSurfaceEventObserver> observer_base =
    std::dynamic_pointer_cast<ParticleCrossingSurfaceEventObserver>( observer );

  for( auto&& entity_id : entity_ids )
  {
    d_particle_crossing_surface_event_dispatcher.attachObserver(
                                                               entity_id,
                                                               particle_types,
                                                               observer_base );
  }
}

// Register an observer with the appropriate particle crossing
// surface event dispatcher
template<typename Observer>
inline void ParticleCrossingSurfaceEventHandler::registerObserverWithTag(
                               const std::shared_ptr<Observer>& observer,
                               const std::set<uint64_t>& entity_ids,
                               ParticleCrossingSurfaceEventObserver::EventTag )
{
  // Make sure the Observer class has the corrent event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleCrossingSurfaceEventObserver::EventTag>::value));

  std::shared_ptr<ParticleCrossingSurfaceEventObserver> observer_base =
    std::dynamic_pointer_cast<ParticleCrossingSurfaceEventObserver>( observer );

  for( auto&& entity_id : entity_ids )
  {
    d_particle_crossing_surface_event_dispatcher.attachObserver(
                                                               entity_id,
                                                               observer_base );
  }
}

// Serialize the observer
template<typename Archive>
void ParticleCrossingSurfaceEventHandler::serialize( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_particle_crossing_surface_event_dispatcher );
}

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleCrossingSurfaceEventHandler, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleCrossingSurfaceEventHandler );

#endif // end MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCrossingSurfaceEventHandler.hpp
//---------------------------------------------------------------------------//
