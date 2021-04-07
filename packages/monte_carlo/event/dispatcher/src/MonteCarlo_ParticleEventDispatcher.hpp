//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle event dispatcher database base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_EVENT_DISPATCHER_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_Map.hpp"

namespace MonteCarlo{

//! The particle event dispatcher database base class
template<typename Dispatcher>
class ParticleEventDispatcher
{

public:

  // Constructor
  ParticleEventDispatcher();

  // Destructor
  virtual ~ParticleEventDispatcher()
  { /* ... */ }

  //! Get the appropriate local dispatcher for the given entity id
  Dispatcher& getLocalDispatcher( const uint64_t entity_id );

  //! Attach an observer to the appropriate dispatcher
  void attachObserver(
          const uint64_t entity_id,
          const std::set<ParticleType>& particle_types,
	  const std::shared_ptr<typename Dispatcher::ObserverType>& observer );

  //! Attach an observer to the appropriate dispatcher
  void attachObserver(
          const uint64_t entity_id,
	  const std::shared_ptr<typename Dispatcher::ObserverType>& observer );

  //! Detach an observer from the appropriate local dispatcher
  void detachObserver( const uint64_t entity_id,
                       const std::shared_ptr<typename Dispatcher::ObserverType>& observer );

  //! Detach the observer from all local dispatchers
  void detachObserver( const std::shared_ptr<typename Dispatcher::ObserverType>& observer );

  //! Detach all observers
  void detachAllObservers();

protected:

  // Typedef for the dispatcher map
  typedef typename std::unordered_map<uint64_t,std::unique_ptr<Dispatcher> >
  DispatcherMap;

  //! Get the dispatcher map
  DispatcherMap& getDispatcherMap();

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  DispatcherMap d_dispatcher_map;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS1_VERSION( ParticleEventDispatcher, MonteCarlo, 0 );

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleEventDispatcher_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PARTICLE_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEventDispatcher.hpp
//---------------------------------------------------------------------------//
