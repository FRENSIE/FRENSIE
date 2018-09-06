//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleGlobalEventDispatcher.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Particle global event dispatcher base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_GLOBAL_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_GLOBAL_EVENT_DISPATCHER_HPP

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

//! The particle global event dispatcher base class
template<typename Observer>
class ParticleGlobalEventDispatcher
{

public:

  //! Typedef for Observer type
  typedef Observer ObserverType;

  //! Constructor
  ParticleGlobalEventDispatcher();

  //! Destructor
  virtual ~ParticleGlobalEventDispatcher()
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

  //! Get the number of attached observers
  size_t getNumberOfObservers( const ParticleType particle_type ) const;

protected:

  // The observer map
  typedef typename std::set<std::shared_ptr<Observer> > ObserverSet;

  // Check if there is an observer set for the particle type
  bool hasObserverSet( const ParticleType particle_type ) const;
  
  // Get the oberver map
  ObserverSet& getObserverSet( const ParticleType particle_type );

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  std::map<int,ObserverSet> d_observer_sets;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS1_VERSION( ParticleGlobalEventDispatcher, MonteCarlo, 0 );

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleGlobalEventDispatcher_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PARTICLE_GLOBAL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleGlobalEventDispatcher.hpp
//---------------------------------------------------------------------------//
