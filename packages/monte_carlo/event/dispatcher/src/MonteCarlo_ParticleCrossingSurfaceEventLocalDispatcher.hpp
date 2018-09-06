//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCrossingSurfaceEventLocalDispatcher.hpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_LOCAL_DISPATCHER_HPP
#define MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_LOCAL_DISPATCHER_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleEventLocalDispatcher.hpp"
#include "MonteCarlo_ParticleCrossingSurfaceEventObserver.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Geometry_Model.hpp"

namespace MonteCarlo{

/*! The particle crossing surface event dispatcher class
 * \ingroup particle_crossing_surface_event
 */
class ParticleCrossingSurfaceEventLocalDispatcher : public ParticleEventLocalDispatcher<ParticleCrossingSurfaceEventObserver>
{
  typedef ParticleEventLocalDispatcher<ParticleCrossingSurfaceEventObserver> BaseType;

public:

  //! Constructor
  ParticleCrossingSurfaceEventLocalDispatcher(
                                  const Geometry::Model::EntityId surface_id );

  //! Destructor
  ~ParticleCrossingSurfaceEventLocalDispatcher()
  { /* ... */ }

  //! Dispatch the new event to the observers
  void dispatchParticleCrossingSurfaceEvent(
                              const ParticleState& particle,
	                      const Geometry::Model::EntityId surface_crossing,
                              const double angle_cosine );

private:

  // Default constructor
  ParticleCrossingSurfaceEventLocalDispatcher();

  // Serialize the observer
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::ParticleCrossingSurfaceEventLocalDispatcher, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ParticleCrossingSurfaceEventLocalDispatcher, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleCrossingSurfaceEventLocalDispatcher );

#endif // end MONTE_CARLO_PARTICLE_CROSSING_SURFACE_EVENT_LOCAL_DISPATCHER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCrossingSurfaceEventLocalDispatcher.hpp
//---------------------------------------------------------------------------//
