//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCrossingSurfaceEventDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher database class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleCrossingSurfaceEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleEventDispatcher.hpp"

namespace MonteCarlo{

/*! The particle crossing surface event dispatcher database class
 * \ingroup particle_crossing_surface_event
 */
class ParticleCrossingSurfaceEventDispatcher : public ParticleEventDispatcher<ParticleCrossingSurfaceEventLocalDispatcher>
{
  typedef ParticleEventDispatcher<ParticleCrossingSurfaceEventLocalDispatcher> BaseType;

public:

  //! Constructor
  ParticleCrossingSurfaceEventDispatcher()
  { /* ... */ }

  //! Destructor
  ~ParticleCrossingSurfaceEventDispatcher()
  { /* ... */ }

  //! Dispatch the particle crossing surface event to the observers
  void dispatchParticleCrossingSurfaceEvent(
                              const ParticleState& particle,
                              const Geometry::Model::EntityId surface_crossing,
                              const double angle_cosine );

private:

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleCrossingSurfaceEventDispatcher, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ParticleCrossingSurfaceEventDispatcher, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleCrossingSurfaceEventDispatcher );

#endif // end MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCrossingSurfaceEventDispatcher.hpp
//---------------------------------------------------------------------------//
