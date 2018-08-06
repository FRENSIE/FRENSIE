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

// FRENSIE Includes
#include "MonteCarlo_ParticleSubtrackEndingInCellEventDispatcher.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_Vector.hpp"

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
                              const Geometry::Model::EntityId cell_of_subtrack,
                              const double particle_subtrack_length );

protected:

  /*! \brief Register an observer with the appropriate particle subtrack ending
   * in cell event dispatcher.
   */
  template<typename Observer>
  void registerObserverWithTag(
                         const std::shared_ptr<Observer>& observer,
			 const std::set<uint64_t>& entity_ids,
                         const std::set<ParticleType>& particle_types,
			 ParticleSubtrackEndingInCellEventObserver::EventTag );

  /*! \brief Register an observer with the appropriate particle subtrack ending
   * in cell event dispatcher.
   */
  template<typename Observer>
  void registerObserverWithTag(
                         const std::shared_ptr<Observer>& observer,
			 const std::set<uint64_t>& entity_ids,
			 ParticleSubtrackEndingInCellEventObserver::EventTag );

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The particle colliding in cell event dispatcher
  ParticleSubtrackEndingInCellEventDispatcher
  d_particle_subtrack_ending_in_cell_event_dispatcher;
};

// Register an observer with the appropriate particle subtrack ending
// cell event dispatcher.
template<typename Observer>
inline void ParticleSubtrackEndingInCellEventHandler::registerObserverWithTag(
                          const std::shared_ptr<Observer>& observer,
                          const std::set<uint64_t>& entity_ids,
                          const std::set<ParticleType>& particle_types,
			  ParticleSubtrackEndingInCellEventObserver::EventTag )
{
  // Make sure the Observer class has the expected event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleSubtrackEndingInCellEventObserver::EventTag>::value));

  std::shared_ptr<ParticleSubtrackEndingInCellEventObserver> observer_base =
    std::dynamic_pointer_cast<ParticleSubtrackEndingInCellEventObserver>(
								    observer );

  for( auto&& entity_id : entity_ids )
  {
    d_particle_subtrack_ending_in_cell_event_dispatcher.attachObserver(
                                                             entity_id,
                                                             particle_types,
                                                             observer_base );
  }
}

// Register an observer with the appropriate particle subtrack ending in cell
// event dispatcher
template<typename Observer>
inline void ParticleSubtrackEndingInCellEventHandler::registerObserverWithTag(
                          const std::shared_ptr<Observer>& observer,
                          const std::set<uint64_t>& entity_ids,
                          ParticleSubtrackEndingInCellEventObserver::EventTag )
{
  // Make sure the Observer class has the expected event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleSubtrackEndingInCellEventObserver::EventTag>::value));

  std::shared_ptr<ParticleSubtrackEndingInCellEventObserver> observer_base =
    std::dynamic_pointer_cast<ParticleSubtrackEndingInCellEventObserver>(
								    observer );

  for( auto&& entity_id : entity_ids )
  {
    d_particle_subtrack_ending_in_cell_event_dispatcher.attachObserver(
                                                             entity_id,
                                                             observer_base );
  }
}

// Serialize the observer
template<typename Archive>
void ParticleSubtrackEndingInCellEventHandler::serialize( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_particle_subtrack_ending_in_cell_event_dispatcher );
}

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleSubtrackEndingInCellEventHandler, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleSubtrackEndingInCellEventHandler );

#endif // end MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_IN_CELL_EVENT_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingInCellEventHandler.hpp
//---------------------------------------------------------------------------//
