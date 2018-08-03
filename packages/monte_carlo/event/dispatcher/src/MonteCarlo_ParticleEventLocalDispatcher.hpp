//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEventLocalDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle event dispatcher base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_EVENT_LOCAL_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_EVENT_LOCAL_DISPATCHER_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_Map.hpp"

namespace MonteCarlo{

//! The particle event dispatcher base class
template<typename Observer>
class ParticleEventLocalDispatcher
{

public:

  //! Typedef for Observer type
  typedef Observer ObserverType;

  //! Constructor
  ParticleEventLocalDispatcher( const uint64_t entity_id );

  //! Destructor
  virtual ~ParticleEventLocalDispatcher()
  { /* ... */ }

  //! Attach an observer to the dispatcher
  void attachObserver( const std::set<ParticleType>& particle_types,
                       const std::shared_ptr<Observer>& observer );

  //! Attach an observer to the dispatcher
  void attachObserver( const std::shared_ptr<Observer>& observer );

  //! Detach an observer from the dispatcher
  void detachObserver( const std::shared_ptr<Observer>& observer );

  //! Detach all observers
  void detachAllObservers();

  //! Get the entity id corresponding to this particle event dispatcher
  uint64_t getEntityId() const;

  //! Get the number of attached observers
  size_t getNumberOfObservers( const ParticleType particle_type ) const;

protected:

  // The observers set
  typedef std::set<std::shared_ptr<Observer> > ObserverSet;

  //! Default constructor
  ParticleEventLocalDispatcher();

  // Check if there is an observer set for the particle type
  bool hasObserverSet( const ParticleType particle_type ) const;

  // Get the observer map
  ObserverSet& getObserverSet( const ParticleType particle_type );

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The entity id for which the particle event will be dispatched
  uint64_t d_entity_id;

  // The particle type observer set
  std::map<int,ObserverSet> d_observer_sets;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS1_VERSION( ParticleEventLocalDispatcher, MonteCarlo, 0 );

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleEventLocalDispatcher_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PARTICLE_EVENT_LOCAL_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEventLocalDispatcher.hpp
//---------------------------------------------------------------------------//
