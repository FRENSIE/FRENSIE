//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Particle subtrack ending global event dispatcher
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_DISPATCHER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleGlobalEventDispatcher.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventObserver.hpp"
#include "MonteCarlo_ParticleState.hpp"

namespace MonteCarlo{

/*! The particle subtrack ending global event dispatcher class
 * \ingroup particle_subtrack_ending_global_event
 */
class ParticleSubtrackEndingGlobalEventDispatcher : public ParticleGlobalEventDispatcher<ParticleSubtrackEndingGlobalEventObserver>
{
  typedef ParticleGlobalEventDispatcher<ParticleSubtrackEndingGlobalEventObserver> BaseType;

public:

  //! Constructor
  ParticleSubtrackEndingGlobalEventDispatcher()
  { /* ... */ }

  //! Destructor
  ~ParticleSubtrackEndingGlobalEventDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleSubtrackEndingGlobalEvent( const ParticleState& particle,
                                                  const double start_point[3],
                                                  const double end_point[3] );

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleSubtrackEndingGlobalEventDispatcher );

#endif // end MONTE_CARLO_PARTICLE_SUBTRACK_ENDING_GLOBAL_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.hpp
//---------------------------------------------------------------------------//
